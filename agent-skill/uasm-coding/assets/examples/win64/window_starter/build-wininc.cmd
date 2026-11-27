@echo off
setlocal
if "%~1"=="" (echo Usage: build.cmd path-to-UASM.exe& exit /b 1)
set "ASSEMBLER=%~f1"
set UASM=
pushd "%~dp0"
if not exist build mkdir build
"%ASSEMBLER%" -q -win64 -Zp8 -Zi8 -Fobuild\wininc.obj wininc.asm
if errorlevel 1 goto failed
link /nologo /debug:full /incremental:no /subsystem:windows /machine:x64 /entry:Start /out:build\wininc.exe build\wininc.obj
if errorlevel 1 goto failed
"%ASSEMBLER%" -q -win64 -Zp8 -Zi8 -DSMOKE_TEST=1 -Fobuild\wininc-smoke.obj wininc.asm
if errorlevel 1 goto failed
link /nologo /debug:full /incremental:no /subsystem:windows /machine:x64 /entry:Start /out:build\wininc-smoke.exe build\wininc-smoke.obj
if errorlevel 1 goto failed
popd
exit /b 0
:failed
popd
exit /b 1

