@echo off
setlocal
if "%~1"=="" (echo Usage: build.cmd path-to-UASM.exe& exit /b 1)
set "ASSEMBLER=%~f1"
set UASM=
pushd "%~dp0"
if not exist build mkdir build
"%ASSEMBLER%" -q -win64 -Zp8 -Zi8 -Fobuild\main.obj main.asm
if errorlevel 1 goto failed
link /nologo /debug:full /incremental:no /subsystem:windows /machine:x64 /entry:Start /out:build\window_starter.exe build\main.obj kernel32.lib user32.lib
if errorlevel 1 goto failed
"%ASSEMBLER%" -q -win64 -Zp8 -Zi8 -DSMOKE_TEST=1 -Fobuild\smoke.obj main.asm
if errorlevel 1 goto failed
link /nologo /debug:full /incremental:no /subsystem:windows /machine:x64 /entry:Start /out:build\smoke.exe build\smoke.obj kernel32.lib user32.lib
if errorlevel 1 goto failed
popd
exit /b 0
:failed
popd
exit /b 1
