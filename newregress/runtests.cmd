@echo off
setlocal
rem Temporary PR #241 runner. Optional first argument: assembler executable.
set "ASMX=%~dp0..\x64\Release\UASM.exe"
if not "%~1"=="" set "ASMX=%~f1"
if not exist "%ASMX%" (
    echo Assembler not found: "%ASMX%"
    exit /b 1
)
if not exist "%~dp0result" mkdir "%~dp0result"
if not exist "%~dp0result" exit /b 1
pushd "%~dp0result" || exit /b 1
"%ASMX%" -c -q -win64 "..\test\pr241_evex_state.asm"
set "RESULT=%ERRORLEVEL%"
if "%RESULT%"=="0" echo Created "%~dp0result\pr241_evex_state.obj"
popd
exit /b %RESULT%
