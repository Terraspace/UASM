@echo off
setlocal
rem Run from an x64 Native Tools Command Prompt for Visual Studio.
set "ASSEMBLER=%~dp0..\..\x64\Release\UASM.exe"
if not "%~1"=="" set "ASSEMBLER=%~f1"
if not exist "%~dp0..\results\win64-abi" mkdir "%~dp0..\results\win64-abi"
pushd "%~dp0..\results\win64-abi"
rem Vector runtime checks require an AVX-capable CPU and OS.
"%ASSEMBLER%" -q -win64 -Fo=abi_vector.obj "%~dp0..\src\win64\abi_vector.asm"
if errorlevel 1 goto failed
cl /nologo /W4 /Od /MT /arch:AVX /Fowin64_vector_driver.obj "%~dp0win64_vector_driver.c" abi_vector.obj /Feabi_vector.exe
if errorlevel 1 goto failed
abi_vector.exe
if errorlevel 1 goto failed
"%ASSEMBLER%" -q -win64 -Fo=abi_vector_edges.obj "%~dp0..\src\win64\abi_vector_edges.asm"
if errorlevel 1 goto failed
cl /nologo /W4 /Od /MT /arch:AVX /Fowin64_vector_edges_driver.obj "%~dp0win64_vector_edges_driver.c" abi_vector_edges.obj /Feabi_vector_edges.exe
if errorlevel 1 goto failed
abi_vector_edges.exe
if errorlevel 1 goto failed
popd
exit /b 0
:failed
popd
exit /b 1
