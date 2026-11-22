@echo off
setlocal
rem Run from an x64 Native Tools Command Prompt for Visual Studio.
set "ASSEMBLER=%~dp0..\..\x64\Release\UASM.exe"
if not "%~1"=="" set "ASSEMBLER=%~f1"
if not exist "%~dp0..\results\win64-abi" mkdir "%~dp0..\results\win64-abi"
pushd "%~dp0..\results\win64-abi"
"%ASSEMBLER%" -q -win64 -Fo=abi_scalar.obj "%~dp0..\src\win64\abi_scalar.asm"
if errorlevel 1 goto failed
ml64 /nologo /c /Foscalar_capture.obj "%~dp0win64_scalar_capture.asm"
if errorlevel 1 goto failed
cl /nologo /W4 /O2 /MT /Foscalar_driver.obj "%~dp0win64_scalar_driver.c" abi_scalar.obj scalar_capture.obj /Fewin64-scalar.exe
if errorlevel 1 goto failed
win64-scalar.exe
if errorlevel 1 goto failed
popd
exit /b 0
:failed
popd
exit /b 1
