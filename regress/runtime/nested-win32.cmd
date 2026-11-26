@echo off
setlocal
set "ASSEMBLER=%~dp0..\..\x64\Release\UASM.exe"
if not "%~1"=="" set "ASSEMBLER=%~f1"
pushd "%~dp0"
if not exist results mkdir results
for %%T in (runtime) do (
  "%ASSEMBLER%" -q -coff -Foresults\%%T.obj ..\src\nested_calls32\%%T.asm
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
