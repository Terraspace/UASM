@echo off
setlocal
pushd "%~dp0"
set UASM_SAMPLE_FLAGS=
call build.cmd "%~1"
if errorlevel 1 goto failed
build\oo_tour.exe
if errorlevel 1 goto failed
set UASM_SAMPLE_FLAGS=-DSTACK_RBP=1
call build.cmd "%~1"
if errorlevel 1 goto failed
build\oo_tour.exe
if errorlevel 1 goto failed
set UASM_SAMPLE_FLAGS=
call build.cmd "%~1"
if errorlevel 1 goto failed
popd
exit /b 0
:failed
popd
exit /b 1
