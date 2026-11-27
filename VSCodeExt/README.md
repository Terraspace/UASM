# UASM IntelliSense

Type-aware editing for UASM and MASM source. This extension adds completions, parameter hints, hover information, go-to-definition, an outline and syntax colouring. It does not assemble or execute your project.

## Install and build

Install the VSIX from `dist/uasm-intellisense.vsix` using VS Code's **Extensions: Install from VSIX** command, or run `install.cmd`. Reload VS Code after replacing an installed version.

To build from source, install Node.js 22.12 or newer, then run `build.cmd`. It restores locked development dependencies, runs the semantic tests, generates instruction vocabulary from the parent UASM checkout and packages the VSIX. A standalone copy can reuse the checked-in vocabulary. Internet access is needed to restore development dependencies; the installed extension has no runtime npm dependencies.

- `build.cmd`: test and package.
- `install.cmd`: install/replace this extension in your normal VS Code profile.
- `redeploy.cmd`: build, then install.
- `uninstall.cmd`: uninstall this extension only.
- `clean.cmd`: remove generated `dist` and isolated test data; retain source and dependencies.
The packaging tool currently has a scoped `minimatch` 11.0.9 override for [GHSA-g3hv-75wg-m249](https://github.com/advisories/GHSA-g3hv-75wg-m249). Remove the override once `@vscode/vsce` requires a patched version itself; verify with `npm ci`, `npm audit` and `npm run package`. This dependency is not included in the installed extension.

- `npm test`: semantic engine tests.
- `npm run test:host`: actual VS Code provider tests, using an isolated profile and extension directory. Downloads a test copy of VS Code by default; set `VSCODE_EXECUTABLE` to use an existing executable.

The publisher identifier `terraspace` is a local package identity, not a claim that this package has been published on the Marketplace.

## Project setup

Open your assembly project folder and select the **UASM** language mode for `.asm` and `.inc` files. Providers also support documents whose language ID is `asm`, `masm` or `assembly`. If another assembly extension also provides suggestions, disable its IntelliSense for the workspace to avoid duplicates.

The index follows the current document's INCLUDE graph in source order. Unrelated assembly files are not combined into one global symbol table. Put shared declarations in include files, as you would for assembly. An include opened by itself has no knowledge of the source files which include it.

Example `.vscode/settings.json`:

```json
{
  "uasm.includePaths": ["${workspaceFolder}/include", "${env:WININC}/Include"],
  "uasm.defines": {"_WIN64": 1},
  "uasm.maxCompletions": 200,
  "uasm.largeNamespaceThreshold": 1000,
  "uasm.namespaceMinPrefix": 2
}
```

Relative include paths are workspace-relative. INCLUDE first searches the including file's directory, then the entry file's directory, then configured include directories. Unsaved changes to open source/include files are used. **UASM: Rebuild IntelliSense Index** forces a fresh disk read; **UASM: Show Index Status** reports files, symbols and incomplete-index notices.

## Types and member access

Supported declarations include STRUCT/STRUC/UNION, nested and anonymous aggregates, TYPEDEF and pointer aliases, PROC parameters and LOCAL variables, CLASS, OINTERFACE, COMINTERFACE, RAWINTERFACE, CSTRUCT and RAWSTRUCT. Completion details show the declared type or callable signature. Locals and parameters take precedence over globals in their procedure.

```asm
Point STRUCT
    x DWORD ?
    y DWORD ?
Point ENDS
PPoint TYPEDEF PTR Point
.data
point Point <>
pPoint PPoint ?
.code
Demo PROC p:PPoint
    LOCAL localPoint:Point
    ASSUME rax:PTR Point
    ; Complete after these prefixes:
    ; point.
    ; pPoint.
    ; localPoint.
    ; p.
    ; [rax].
    ; [rax].Point.
    ; (Point PTR [rax]).
    ret
Demo ENDP
```

ASSUME changes are tracked in source order, including register reset and NOTHING. The index follows declared pointer/typedef types; it does not infer a register's type from MOV instructions.

For OO/interface values, `object->` suggests methods and OO-typed fields used in chains. Regular structure fields use dot syntax; arrow syntax is not added to ordinary structs. Known macrolib helpers are modelled directly, including implicit object parameters and standard COM IUnknown methods. RAW signatures retain their explicit parameters, including explicit `pThis` where declared. CMETHOD signatures are enriched when their METHOD implementation is present; otherwise the extension indicates that the signature is unavailable.

## Namespaces and calls

```asm
namespace Win32
    WriteFile PROTO :PTR, :PTR, :DWORD, :PTR, :PTR
endnamespace

; Win32:: lists members and child namespaces.
; Win32::Wr narrows to matching names.
invoke Win32::WriteFile, handle, buffer, length, ADDR written, 0
```

Namespace lookup searches the current namespace and its ancestors; leading `::` selects the global namespace. Qualified access lists only that namespace's immediate contents. Procedures, macros, types, constants and variables have distinct completion categories. OPTION CASEMAP influences symbol resolution.

Signature help supports INVOKE, C-style calls, nested calls, method arrows, typed function pointers and macro arguments. Nested parentheses and quoted commas do not advance the outer argument index. Backslash line continuations are supported. The editor scans a bounded window of 40 preceding lines for signature help. It does not validate ABI register conflicts or generate call code.

## Large headers and performance

A namespace larger than 1,000 entries requires at least two characters after `::` before returning members. For example, type `Win32::Cr` rather than scrolling through every Windows declaration. At most 200 matches are returned. Truncated completion lists are marked incomplete so VS Code requests fresh matches as you type. All three limits are configurable.

Namespace names are stored in sorted prefix indexes. Parsing runs in a worker thread, edit requests are debounced, and disk contents and recent indexes are cached. Stale workers are cancelled on changes. Default limits are 1,000 include files, 2 MB per disk source, and 250,000 expanded source lines; exceeding a limit is reported in index status.

## Scope and limitations

This is an editor-oriented declaration parser, not a second UASM compiler. It understands common declarations and the named UASM OO/interface helpers, but does not execute arbitrary macros, expand arbitrary TEXTEQU-generated syntax or implement every conditional assembly expression. Simple IF/IFDEF/IFNDEF are evaluated; unknown conditions are indexed conservatively and reported, so mutually exclusive declarations may be ambiguous. Configure predefined symbols to match your build.

PUBLIC and EXTERN are indexed as declarations, not linker validation. Namespace-qualified editor names do not imply a change to the assembler's external naming rules. Unsupported forms should be added as small parser fixtures rather than guessed from binary output. Remote URI-based virtual workspaces are not supported; local files and local include paths are supported.

`examples/tour.asm` and `examples/types.inc` are a small editing tour, not a runnable application. The engine tests cover types, scopes, interfaces, namespaces, calls, includes and a 20,000-symbol namespace. Extension-host tests exercise the real completion/signature/navigation APIs and unsaved include changes.

Development references: [VS Code API](https://code.visualstudio.com/api/references/vscode-api), [packaging extensions](https://code.visualstudio.com/api/working-with-extensions/publishing-extension).
