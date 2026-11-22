@echo off
setlocal
rem Run from an x64 Native Tools Command Prompt for Visual Studio.
rem DIA SDK ships with Visual Studio. The indirect/vector check needs AVX.
set "ASSEMBLER=%~dp0..\..\x64\Release\UASM.exe"
if not "%~1"=="" set "ASSEMBLER=%~f1"
set "DIA=%VSINSTALLDIR%DIA SDK"
if not exist "%DIA%\include\dia2.h" (
 echo Run from an x64 Native Tools prompt with the Visual Studio DIA SDK installed.
 exit /b 1
)
if not exist "%~dp0..\results\codeview-locations" mkdir "%~dp0..\results\codeview-locations"
pushd "%~dp0..\results\codeview-locations"
cl /nologo /W3 /O2 /MT /EHsc /I"%DIA%\include" "%~dp0codeview_locations_driver.cpp" ole32.lib oleaut32.lib /Fe:codeview-locations.exe
if errorlevel 1 goto failed
call :one cvlocals8 locations -Zi8 30 300
if errorlevel 1 goto failed
call :one cvlocals4 locations -Zi 30 300
if errorlevel 1 goto failed
call :one cvlocals8 vectors -Zi8 9 76
if errorlevel 1 goto failed
call :one cvlocals8 indirect -Zi8 4 6
if errorlevel 1 goto failed
popd
exit /b 0
:one
"%ASSEMBLER%" -q -win64 %3 -Fo=%1-%2.obj "%~dp0..\src\%1\%2.asm"
if errorlevel 1 exit /b 1
link /nologo /debug:full /incremental:no /entry:Main /subsystem:console /out:%1-%2.exe %1-%2.obj kernel32.lib
if errorlevel 1 exit /b 1
codeview-locations.exe "%CD%\%1-%2.exe" "%CD%\%1-%2.pdb" "%DIA%\bin\amd64\msdia140.dll" %4 %5
exit /b %errorlevel%
:failed
popd
exit /b 1
