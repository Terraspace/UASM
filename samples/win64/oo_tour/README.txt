UASM WIN64 OO TOUR
=================
A refreshed, self-contained version of the Person/Company example.
BUILD AND DEBUG
Requires this experimental namespace-enabled UASM build and Visual Studio C++
x64 tools with the Windows SDK. No third-party ASM includes or runtime assets.
In an x64 Native Tools Command Prompt, change to this folder and run:

  build.cmd C:\path\to\UASM.exe
  test.cmd C:\path\to\UASM.exe

Inside the UASM source tree, the assembler argument can be omitted; the default
is ..\..\..\x64\Release\UASM.exe. UASM environment variable also overrides it.
When extracting the standalone ZIP, pass your assembler path explicitly.

Open the .sln in Visual Studio and select Debug / x64. For a standalone copy,
set Configuration Properties > NMake > Build Command Line to call build.cmd
with the full assembler path (also update Rebuild), or supply /p:UasmPath=...
to MSBuild. Build and press F5. The EXE and PDB are in build/.
The project uses -Zi8, /DEBUG:FULL and /INCREMENTAL:NO for source-level debugging.

RUN AND EXPECTATIONS
build\oo_tour.exe prints one PASS line and returns zero. test.cmd exercises both
RSP and RBP frames with WIN64:15, then restores the normal RSP debugger build.

FEATURES DEMONSTRATED
* Model namespace: CLASS, METHOD, STATICMETHOD, VECMETHOD and OINTERFACE.
* Constructor returns this in RAX; Person allocates its owned Company inside Init.
* Names are borrowed static strings, not copied or freed by Person.
* _NEW copies the class template; _DELETE invokes Destroy and releases memory.
  Caller preserves RSI/RDI for _NEW and R15 for virtual dispatch.
* LOCAL typed pointers retain their values across calls and destructors.
* Arrow calls through globals, LOCAL/interface pointers, ASSUME register pointers,
  pointer slots ([rbx]), and explicit typed pointer-slot memory.
* Namespace-qualified _INVOKE / _I (including no-argument methods) and
  _VINVOKE / _V (vtable).
* Static C-style calls and _STATIC; address-of & and string literals.
* Typed nested results (integer and REAL4), siblings and maximum depth three.
* Chained person->company->Adjust(2.0) dispatch and a nested method result
  assigned directly by MOVSS result,person->Calc(FloatIdentity(1.0)).
* VTABLE:OFF direct dispatch and VTABLE:ON virtual dispatch on the same object.
* Vectorcall VectorSum consumes XMM1/XMM2 (This is RCX) and returns XMM0.
  It checks all four output lanes. It needs only baseline x64 SSE instructions.

DEBUGGER TOUR
Break in Start after the allocations and in Model::_Person_SetAge,
Model::_Person_Calc and Model::_Person_VectorSum. Near the "Debugger checkpoint"
comment, inspect person, other, typedEntity, result, and the global vecOut.
Pointers become invalid after cleanup; the sample clears owning pointers.
Do not expect uninitialized LOCALs to have meaningful values at entry.

BOUNDARIES
This is assembler-level object support, not C++ inheritance or automatic ownership.
Entity is an explicit compatible layout view; unlike COM, it has two leading
constructor/destructor slots. Its methods must match Person's order exactly.
-> is for OO/COM/RAW method dispatch, not arbitrary plain-STRUCT field access.
Use ordinary [register].Type.field expressions for data fields.
Nested calls require explicit non-void return types and an automatic PROC frame;
volatile register operands that survive an earlier nested call are rejected.
Returns are spilled; arbitrary user registers are not automatically preserved.
Float results are checked with UCOMISS, not integer comparisons of register names.

The previously documented constructor, chained-arrow, nested assignment and
zero-argument _I limitations are fixed in this build. OO/COM arrow calls also
check the number of explicit arguments before packing the receiver and arguments.
Use this updated assembler to build the revised tour.
