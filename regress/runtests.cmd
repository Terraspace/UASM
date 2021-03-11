@echo off

echo ****************************************************************
echo UASM REGRESSION TEST SUITE
echo ****************************************************************
echo .
echo .

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
for %%f in (..\src\coffdbg\*.asm) do call :cmpcoffdbg %%f
for %%f in (..\src\oo\*.asm) do call :cmpoo %%f
for %%f in (..\src\ooerr\*.asm) do call :cmpooerr %%f
for %%f in (..\src\literals\*.asm) do call :cmpliterals %%f
for %%f in (..\src\literalerr\*.asm) do call :cmpliteralerr %%f
for %%f in (..\src\linux64\*.asm) do call :cmplinux64 %%f
for %%f in (..\src\macho64\*.asm) do call :cmpmacho64 %%f
for %%f in (..\src\cinvoke\*.asm) do call :cmpcinvoke %%f
for %%f in (..\src\mz\*.asm) do call :cmpmz %%f
for %%f in (..\src\flat16\*.asm) do call :flat16 %%f
for %%f in (..\src\avxerr\*.asm) do call :avxerr %%f
for %%f in (..\src\invoke64err\*.asm) do call :invoke64err %%f
for %%f in (..\src\avx512\*.asm) do call :cmpavx512 %%f
for %%f in (..\src\vcall\*.asm) do call :vectorcall %%f
for %%f in (..\src\CodeGenV2\*.asm) do call :cgv2 %%f
for %%f in (..\src\CodeGenV2Error\*.asm) do call :cgv2err %%f
for %%f in (..\src\codeview8_32\*.asm) do call :cv832 %%f
for %%f in (..\src\codeview8_64\*.asm) do call :cv864 %%f
cd ..
echo .
echo .
echo ****************************************************************
echo  REGRESSION TESTS COMPLETED
echo ****************************************************************
echo .
echo .
goto :end

:cv832
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -c -coff -Zi8 -Zd -Zf %1
%FCMP% /O16 %~n1.obj ..\exp\codeview8_32\%~n1.obj
if errorlevel 1 goto end
del %~n1.obj
goto end

:cv864
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -c -win64 -Zi8 -Zd -Zf %1
%FCMP% /O16 %~n1.obj ..\exp\codeview8_64\%~n1.obj
if errorlevel 1 goto end
del %~n1.obj
goto end

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
%FCMP% %~n1.err ..\exp\plain_bin\%~n1.err
if errorlevel 1 goto end
del %~n1.err
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
%FCMP% %~n1.err ..\exp\pe64_bin\%~n1.err
if errorlevel 1 goto end
del %~n1.err
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
%FCMP% %~n1.err ..\exp\win64\%~n1.err
if errorlevel 1 goto end
del %~n1.err
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

:cmpcoffdbg
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -q -coff -Zi %1
%FCMP% /O16 %~n1.obj ..\exp\coffdbg\%~n1.obj
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
%FCMP% %~n1.err ..\exp\literals\%~n1.err
if errorlevel 1 goto end
del %~n1.err
goto end

:cmpliteralerr
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -q -win64 -Zp8 -Zi -Zd -Zf %1
%FCMP% %~n1.err ..\exp\literalerr\%~n1.err
if errorlevel 1 goto end
del %~n1.obj
del %~n1.err
goto end

:cmplinux64
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -q -elf64 %1
%FCMP% /O16 %~n1.obj ..\exp\linux64\%~n1.o
if errorlevel 1 goto end
del %~n1.obj
goto end

:cmpmacho64
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -q -macho64 %1
%FCMP% /O16 %~n1.obj ..\exp\macho64\%~n1.o
if errorlevel 1 goto end
del %~n1.obj
goto end

:cmpcinvoke
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -q -coff %1
%FCMP% /O16 %~n1.obj ..\exp\cinvoke\%~n1.obj
if errorlevel 1 goto end
del %~n1.obj
goto end

:cmpmz
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -q -mz %1
%FCMP% %~n1.exe ..\exp\mz\%~n1.exe
if errorlevel 1 goto end
del %~n1.exe
%FCMP% %~n1.err ..\exp\mz\%~n1.err
if errorlevel 1 goto end
del %~n1.err
goto end

:flat16
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -q -bin %1
%FCMP% %~n1.bin ..\exp\flat16\%~n1.bin
if errorlevel 1 goto end
del %~n1.bin
goto end

:avxerr
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -q -bin %1
%FCMP% %~n1.err ..\exp\avxerr\%~n1.err
if errorlevel 1 goto end
del %~n1.err
goto end

:invoke64err
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -q -win64 -Zp8 %1
%FCMP% %~n1.err ..\exp\invoke64err\%~n1.err
if errorlevel 1 goto end
del %~n1.err
goto end

:cmpavx512
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -q -bin %1
%FCMP% %~n1.bin ..\exp\avx512\%~n1.bin
if errorlevel 1 goto end
del %~n1.bin
goto end

:vectorcall
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -c -win64 -Zp8 %1
%FCMP% /O32 %~n1.obj ..\exp\vcall\%~n1.obj
if errorlevel 1 goto end
del %~n1.obj
%FCMP% %~n1.err ..\exp\vcall\%~n1.err
if errorlevel 1 goto end
del %~n1.err
goto end

:cgv2
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -c -bin %1
%FCMP% %~n1.bin ..\exp\CodeGenV2\%~n1.bin
if errorlevel 1 goto end
del %~n1.bin
%FCMP% %~n1.err ..\exp\CodeGenV2\%~n1.err
if errorlevel 1 goto end
del %~n1.err
goto end

:cgv2err
echo ****************************************************************
ECHO %1
echo ****************************************************************
echo .
echo .
%ASMX% -c -bin %1
%FCMP% %~n1.err ..\exp\CodeGenV2Error\%~n1.err
if errorlevel 1 goto end
del %~n1.err
goto end

:end
