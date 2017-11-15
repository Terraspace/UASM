@echo off

echo ===============================
echo ---> UASM Regression Tests <---
echo ===============================

SET ASMX=%1
if (%1)==() SET ASMX=..\..\x64\release\uasm.exe
SET FCMP=..\fcmp.exe

if not exist result md result
cd result

for %%f in (..\src\*.asm) do call :cmpbin %%f

cd ..
echo exit

:cmpbin
%ASMX% -q -bin %1
%FCMP% %~n1.bin ..\exp\%~n1.bin
if errorlevel 1 goto end
del %~n1.bin
goto end

:end
