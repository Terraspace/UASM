@echo off
setlocal
rem Run from an x64 Native Tools Command Prompt for Visual Studio.
set "ASSEMBLER=%~dp0..\..\..\x64\Release\UASM.exe"
if defined UASM set "ASSEMBLER=%UASM%"
if not "%~1"=="" set "ASSEMBLER=%~f1"
pushd "%~dp0"
if not exist build mkdir build
"%ASSEMBLER%" -q -win64 -Zp8 -Zi8 %UASM_SAMPLE_FLAGS% -Fobuild\main.obj main.asm
if errorlevel 1 goto failed
link /nologo /debug:full /incremental:no /subsystem:console /entry:Start /pdb:build\oo_tour.pdb /out:build\oo_tour.exe build\main.obj kernel32.lib
if errorlevel 1 goto failed
popd
exit /b 0
:failed
popd
exit /b 1
