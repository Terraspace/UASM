UASM experimental namespaces — Win64 debugger sample
====================================================
Requires the v2.60b experimental assembler, Visual Studio with C++ desktop
build/debug tools, and the Windows SDK. No third-party assembly includes or
libraries are required. Namespace support is always enabled on this branch.

BUILD AND RUN
Open an x64 Native Tools Command Prompt for Visual Studio, then:

  cd /d D:\uasm\UASM\samples\win64\namespaces
  build.cmd

An alternative assembler can be supplied as the first argument:

  build.cmd "C:\path\to\UASM.exe"

The script assembles main.asm and services.asm with -win64 -Zi8, links with
kernel32.lib and /DEBUG:FULL, and executes the result. Successful execution
prints PASS and exits with status 0. Artifacts are under build/:
  namespaces.exe, namespaces.pdb, main.obj, services.obj

The program has its own Start entry point and exits through ExitProcess;
it does not require a C runtime startup object.

SOURCE TOUR
api.inc        Shared namespaced types, procedure prototypes and Win32 imports.
main.asm       Nested scopes, expansion-site macro lookup, high-level calls,
               qualified data addresses, instance calls and runtime checks.
services.asm   Two private Calculate procedures with the same leaf name,
               plus a public ComputeTotal called across object files.
counter.inc    A namespaced CLASS with static and instance methods.

The configuration uses WIN64:15, RSP stackbase, automatic frames and private
procedures by default. This retains smart parameter homing and stack allocation.
PUBLIC Start and PUBLIC ComputeTotal opt the two required exports back in.

MANUAL VISUAL STUDIO DEBUGGING
1. Build first. Open build\namespaces.exe using File > Open > Project/Solution
   in Visual Studio (an executable can be opened as a debugging project).
2. Open main.asm, services.asm and counter.inc using File > Open > File.
3. Set a source breakpoint on `mov pair.first,5` in Start and press F5.
   If necessary, check Debug > Windows > Modules: namespaces.exe should load
   the adjacent namespaces.pdb produced by this build. Use the current source
   files and binary together; stale PDBs or source copies will mislead stepping.
4. Step over both pair assignments. Expand pair in Locals: first=5, second=7.
5. Set source breakpoints inside BOTH Calculate functions in services.asm.
   Continue/step into Services::ComputeTotal. The Scaled function calls the
   Plain function: both should be independently identifiable in Call Stack,
   despite their matching leaf name. Inspect first=5 and second=7 once the
   automatic prologue has executed. Plain returns EAX=12; Scaled returns 24.
6. In CheckBias, step through the macro expansion. EAX starts at 10, becomes
   13 using Demo::bias, then 14 after adding ::bias from global scope.
   Macro expansion may share a source line; use Disassembly for individual
   instructions if source stepping skips over it.
7. Break in Counter's NextValue body in counter.inc. inputValue is 40;
   after INC EAX the result is 41.
8. After initializing obj and counterPtr in Start, inspect obj.value=42 and
   counterPtr pointing at obj. Step into counterPtr->GetValue(). RCX is the
   object address; the return value is EAX=42. The typed pointer local is
   deliberate: this is a pointer to the object, not a pointer to another pointer.
9. Continue: the console prints PASS and the process exits normally.

Use the Registers window for return values. A return value in EAX only remains
valid until later instructions overwrite it. Constants such as bias are assembly
constants, not necessarily debugger variables. Namespace-qualified UASM names
are not C++ namespace declarations: use source breakpoints and locals first;
Visual Studio's expression parser may not accept every qualified UASM spelling.
The sample has been built and run automatically; these interactive VS steps
are intended for manual confirmation.

NAMESPACE RULES EXERCISED
- NAMESPACE name / ENDNAMESPACE nest and can reopen an existing scope.
- A::B::name resolves through named scopes; ::name starts at global scope.
- Unqualified lookup checks procedure locals, current namespace, enclosing
  namespaces, then global scope. Declarations belong to the current scope.
- Define symbols inside namespace blocks; qualified definitions are rejected.
- A macro's unqualified references resolve where it expands, not where defined.
- Namespace changes are prohibited inside procedures, structures and macros.
  Includes inherit the current namespace and must return with it balanced.
- PROTO and the matching definition belong in the same namespace. Source
  qualification is preserved across INVOKE and high-level function calls.
- PUBLIC/EXTERN linkage retains the ordinary leaf name and normal decoration.
  Namespaces do not make two identical external linker names distinct: duplicate
  exported identities in one module are rejected. Cross-module collisions are
  diagnosed by the linker. Private names remain distinct.
- PROC defaults were not changed. Use OPTION PROC:PRIVATE when same-named
  procedures in different namespaces must coexist without duplicate exports.
- Write `Label:: MacroCall` with whitespace after :: for a public/unscoped
  label. `Label::MacroCall` is now qualification. Existing INVOKE register-pair
  syntax such as edx::eax remains supported.
- Namespace modules support FASTPASS. Cached lines retain their namespace
  context, including the caller scope of expanded macros.

REGRESSION COVERAGE
regress/src/namespaces contains five independently checked binary cases and
eleven diagnostic cases: nested/reopened/global scopes, macro lookup, forward
references, types/records, public labels, includes, collisions and invalid scopes.
Run the full suite from the repository's regress folder with `go run .` after
building the experimental assembler into x64/Release/UASM.exe.
