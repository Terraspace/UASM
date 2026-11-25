@echo off
setlocal
rem Run in an x64 Native Tools Command Prompt for Visual Studio.
rem Optional argument: full path to experimental UASM.exe.
set "ASSEMBLER=%~dp0..\..\..\x64\Release\UASM.exe"
if not "%~1"=="" set "ASSEMBLER=%~f1"
pushd "%~dp0"
if not exist build mkdir build
"%ASSEMBLER%" -q -win64 -Zi8 -Fobuild\main.obj main.asm
if errorlevel 1 goto failed
"%ASSEMBLER%" -q -win64 -Zi8 -Fobuild\services.obj services.asm
if errorlevel 1 goto failed
link /nologo /debug:full /incremental:no /subsystem:console /entry:Start /pdb:build\namespaces.pdb /out:build\namespaces.exe build\main.obj build\services.obj kernel32.lib
if errorlevel 1 goto failed
build\namespaces.exe
if errorlevel 1 goto failed
popd
exit /b 0
:failed
popd
exit /b 1
