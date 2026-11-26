@echo off
setlocal
set "ASSEMBLER=%~dp0..\..\x64\Release\UASM.exe"
if not "%~1"=="" set "ASSEMBLER=%~f1"
pushd "%~dp0"
if not exist results mkdir results
for %%T in (constant one_inner siblings_args siblings_noargs float_siblings reentrant stack_arguments misaligned siblings_noargs_rbp float_siblings_rbp reentrant_rbp stack_arguments_rbp invoke_children oo_runtime thirtytwo_results) do (
  "%ASSEMBLER%" -q -win64 -Foresults\%%T.obj ..\src\nested_calls64\%%T.asm
  if errorlevel 1 goto failed
  link /nologo /subsystem:console /entry:Start /out:results\%%T.exe results\%%T.obj kernel32.lib
  if errorlevel 1 goto failed
  results\%%T.exe
  if errorlevel 1 goto failed
  echo PASS %%T
)
popd
exit /b 0
:failed
popd
exit /b 1
