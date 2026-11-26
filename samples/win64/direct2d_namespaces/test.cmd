@echo off
setlocal
pushd "%~dp0"
set UASM_SAMPLE_FLAGS=-DSELFTEST=1
call build.cmd "%~1"
if errorlevel 1 goto failed
start "" /wait build\direct2d_namespaces.exe
if errorlevel 1 goto failed
echo PASS: Direct2D factory, QueryInterface, window, paint and COM cleanup
set UASM_SAMPLE_FLAGS=
call build.cmd "%~1"
if errorlevel 1 goto failed
popd
exit /b 0
:failed
popd
exit /b 1
