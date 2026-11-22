@echo off
setlocal
rem Run from an x64 Native Tools Command Prompt for Visual Studio.
rem Optional first argument selects a different UASM executable.
set "ASSEMBLER=%~dp0..\..\x64\Release\UASM.exe"
if not "%~1"=="" set "ASSEMBLER=%~f1"
if not exist "%~dp0..\results\win64-unwind" mkdir "%~dp0..\results\win64-unwind"
pushd "%~dp0..\results\win64-unwind"
"%ASSEMBLER%" -q -win64 -Fo=unwind_smart.obj "%~dp0..\src\win64\unwind_smart.asm"
if errorlevel 1 goto failed
cl /nologo /W4 /O2 /MT "%~dp0win64_unwind_driver.c" unwind_smart.obj /Fewin64-unwind.exe
if errorlevel 1 goto failed
win64-unwind.exe
if errorlevel 1 goto failed
popd
exit /b 0
:failed
popd
exit /b 1
