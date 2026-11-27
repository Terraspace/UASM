@echo off
setlocal
rem Run in an x64 Native Tools Command Prompt for Visual Studio.
set "ASSEMBLER=%~dp0..\..\..\x64\Release\UASM.exe"
if not "%~1"=="" set "ASSEMBLER=%~f1"
pushd "%~dp0"
if not exist build mkdir build
"%ASSEMBLER%" -q -win64 -Zi8 -Fobuild\main.obj main.asm
if errorlevel 1 goto failed
link /nologo /debug:full /incremental:no /subsystem:console /entry:Start /pdb:build\nested_calls.pdb /out:build\nested_calls.exe build\main.obj kernel32.lib
if errorlevel 1 goto failed
build\nested_calls.exe
if errorlevel 1 goto failed
popd
exit /b 0
:failed
popd
exit /b 1
