@echo off

echo ****************************************************************
echo UASM REGRESSION TEST SUITE
echo ****************************************************************
echo .
echo .

cd regress

SET ASMX=%1
if (%1)==() SET ASMX=..\..\x64\release\uasm.exe
SET FCMP=..\fcmp.exe

if not exist result md result
cd result
del /Q *.*

for %%f in (..\src\plain_bin\*.asm) do call :cmpbin %%f
for %%f in (..\src\pe64_bin\*.asm) do call :cmppebin %%f
for %%f in (..\src\win64\*.asm) do call :cmpwin64 %%f
for %%f in (..\src\flat\*.asm) do call :cmpflat %%f
for %%f in (..\src\coff\*.asm) do call :cmpcoff %%f
for %%f in (..\src\oo\*.asm) do call :cmpoo %%f
for %%f in (..\src\ooerr\*.asm) do call :cmpooerr %%f
for %%f in (..\src\literals\*.asm) do call :cmpliterals %%f

cd ..
echo .
echo .
echo ****************************************************************
echo  REGRESSION TESTS COMPLETED
echo ****************************************************************
echo .
echo .
goto :end

:cmpbin
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -q -bin %1
%FCMP% %~n1.bin ..\exp\plain_bin\%~n1.bin
if errorlevel 1 goto end
del %~n1.bin
goto end

:cmppebin
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -q -bin -Fo %~n1.exe %1
%FCMP% %~n1.exe ..\exp\pe64_bin\%~n1.exe
if errorlevel 1 goto end
del %~n1.exe
goto end

:cmpwin64
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -c -q -win64 -Zp8 %1
%FCMP% /O16 %~n1.obj ..\exp\win64\%~n1.obj
if errorlevel 1 goto end
del %~n1.obj
goto end

:cmpflat
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -q -bin %1
%FCMP% %~n1.bin ..\exp\flat\%~n1.bin
if errorlevel 1 goto end
del %~n1.bin
goto end

:cmpcoff
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -q -coff %1
%FCMP% /O16 %~n1.obj ..\exp\coff\%~n1.obj
if errorlevel 1 goto end
del %~n1.obj
goto end

:cmpoo
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -q -win64 -Zp8 -Zi -Zd -Zf %1
%FCMP% /O16 %~n1.obj ..\exp\oo\%~n1.obj
if errorlevel 1 goto end
del %~n1.obj
goto end

:cmpooerr
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -q -win64 -Zp8 -Zi -Zd -Zf %1
%FCMP% %~n1.err ..\exp\ooerr\%~n1.err
if errorlevel 1 goto end
del %~n1.obj
del %~n1.err
goto end

:cmpliterals
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -q -win64 -Zp8 %1
%FCMP% /O16 %~n1.obj ..\exp\literals\%~n1.obj
if errorlevel 1 goto end
del %~n1.obj
goto end

:end
