UASM WIN64 DIRECT2D / COM / NAMESPACES
====================================
A native resizable Win32 window drawing a cyan rounded rectangle and ellipse
on a dark background, entirely in assembly. No wrapper library or image files.
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
Run build\direct2d_namespaces.exe, resize it, then close it normally.
test.cmd builds a short-lived test variant which paints a real window, validates
successful QueryInterface and at least one EndDraw, closes on a timer, and
returns zero. It then rebuilds the normal interactive version for F5 debugging.
The test needs an interactive Windows desktop; it is not a headless renderer.

SOURCE LAYOUT
api.inc: minimal Win32 structures/prototypes and Direct2D COM layouts.
main.asm: Graphics namespace manages COM resources; App owns the window callback;
Start creates the factory, tests QueryInterface and runs the message loop.
Win32 and D2D namespaces hold API names without changing their external linkage.

COM DETAILS
COMINTERFACE supplies QueryInterface / AddRef / Release in slots 0..2.
QueryInterface returns a 32-bit HRESULT and accepts both REFIID and void** after
implicit This. A real factory QueryInterface(IID_IUnknown, &unknown) is exercised.
-> dispatch supplies This; HRESULT checks test EAX as a signed 32-bit value.
Objects come from Direct2D, so they are released with Release, NEVER _DELETE.
The render target and brush are recreated after D2DERR_RECREATE_TARGET.
WM_SIZE resizes the pixel target, WM_PAINT uses BeginPaint/EndPaint around drawing,
and WM_DESTROY releases objects before posting WM_QUIT.

Only methods used by this sample have CVIRTUAL signatures. Unused inherited
methods occupy named QWORD slots to retain the actual SDK vtable offsets.
Those untyped placeholders are NOT supported calls. Add a correct signature
before calling one; do not remove or reorder slots. Assembly assertions verify
the used offsets and all Win32/Direct2D structure sizes.
The brush declaration exposes only IUnknown; later brush slots are not used.
Reference: Windows SDK d2d1.h and unknwn.h.

DEBUGGER TOUR
Set breakpoints in App::WindowProc, Graphics::EnsureTarget and Graphics::Paint.
Inspect the callback's named arguments, local paintInfo and the Graphics pointers.
Step over Windows/Direct2D calls unless you have their matching system symbols.
The object pointer references a COM interface; its first QWORD is a vtable pointer.
Changing a class namespace does not change the external Windows DLL export names.

Uses standard x64 Windows APIs, Direct2D 1.0, no AVX/AVX-512 instructions.
Window drawing uses fixed device-independent coordinates (not a UI layout engine).
Factory creation is single-threaded; all rendering and cleanup happen on the UI thread.
