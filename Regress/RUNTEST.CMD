@echo off
REM
REM Set version to test
REM
SET ASMX=%1
if (%1)==() SET ASMX=\HJWASM\hjwasm.exe
REM
REM Optional linker for the test
REM
REM SET OWLINK=\JWASM\jwlink.exe
REM SET OWLINK=\ASMC\linkw.exe
REM
REM MS LINK >= 8.0 is needed for testing SAFESEH.
REM
REM SET MSLINK=\VC80\bin\link.exe

if not exist tmp md tmp
cd tmp

for %%f in (..\src\*.asm) do call :cmpbin %%f
for %%f in (..\src\*.asn) do call :cmpmz  %%f
for %%f in (..\src\*.aso) do call :cmperr %%f
for %%f in (..\src\*.asz) do call :lnkomf %%f
for %%q in (safeseh coff coffdbg elf ifdef omf pe zne zg zd bin) do call :%%q

cd ..
exit

:cmpbin
%ASMX% -q -bin %1
..\fcmp.exe %~n1.BIN ..\exp\%~n1.EXP
if errorlevel 1 goto end
del %~n1.BIN
goto end

:cmpmz
%ASMX% -q -mz %1
..\fcmp.exe %~n1.EXE ..\exp\%~n1.EXP
if errorlevel 1 goto end
del %~n1.EXE
goto end

:cmperr
%ASMX% -q -omf %1 >NUL
..\fcmp.exe %~n1.ERR ..\exp\%~n1.EXP
if errorlevel 1 goto end
del %~n1.err
if exist %~n1.obj del %~n1.obj
goto end

:cmpobj
%ASMX% -q -omf %1
if errorlevel 1 goto end
..\fcmp.exe %~n1.obj ..\exp\%~n1.EXP
if errorlevel 1 goto end
del %~n1.OBJ
goto end

:lnkomf
if (%OWLINK%) == () goto end
%ASMX% -q -omf %1
if errorlevel 1 goto end
%OWLINK% op q,nofar format dos LIBPath ..\lib file %~n1.OBJ
..\fcmp.exe %~n1.EXE ..\exp\%~n1.EXP
if errorlevel 1 goto end
del %~n1.OBJ
del %~n1.EXE
goto end

:safeseh
if (%MSLINK%) == () goto end
%ASMX% -q -coff -safeseh ..\src\SAFESEH.ASC
if errorlevel 1 goto end
%MSLINK% /nologo /SAFESEH SAFESEH.OBJ ..\lib\SAFESEH.LIB
..\fcmp.exe -p SAFESEH.EXE ..\exp\SAFESEH.EXP
if errorlevel 1 goto end
del SAFESEH.EXE
del SAFESEH.OBJ
goto end

:coff
REM
REM ALIAS segment attribute
REM
%ASMX% -q -coff ..\src\SEGALIAS.ASC
if errorlevel 1 goto end
..\fcmp.exe -coff SEGALIAS.OBJ ..\exp\SEGALIAS.EXP
if errorlevel 1 goto end
del SEGALIAS.OBJ
REM
REM ALIGN and characteristics segment attributes
REM
%ASMX% -q -coff -eq ..\src\SEGALIGN.ASC
..\fcmp.exe SEGALIGN.ERR ..\exp\SEGALIGN.EXP
if errorlevel 1 goto end
del SEGALIGN.ERR
REM
REM 64-bit dll
REM
%ASMX% -q -coff ..\src\DLL64.ASC
if errorlevel 1 goto end
..\fcmp.exe -c DLL64.OBJ ..\exp\DLL64.EXP
if errorlevel 1 goto end
del DLL64.OBJ

%ASMX% -q -coff ..\src\SEH64.ASC
if errorlevel 1 goto end
..\fcmp.exe -c SEH64.OBJ ..\exp\SEH64.EXP
if errorlevel 1 goto end
del SEH64.OBJ

%ASMX% -q -coff ..\src\SEH642.ASC
if errorlevel 1 goto end
..\fcmp.exe -c SEH642.OBJ ..\exp\SEH642.EXP
if errorlevel 1 goto end
del SEH642.OBJ

%ASMX% -q -win64 ..\src\MOV643.ASC
if errorlevel 1 goto end
..\fcmp.exe -c MOV643.OBJ ..\exp\MOV643.EXP
if errorlevel 1 goto end
del MOV643.OBJ

%ASMX% -q -win64 ..\src\PROC641.ASC
if errorlevel 1 goto end
..\fcmp.exe -c PROC641.OBJ ..\exp\PROC641.EXP
if errorlevel 1 goto end
del PROC641.OBJ

%ASMX% -q -win64 ..\src\PROC643.ASC
if errorlevel 1 goto end
..\fcmp.exe -c PROC643.OBJ ..\exp\PROC643.EXP
if errorlevel 1 goto end
del PROC643.OBJ
REM
REM option dllimport
REM
if (%OWLINK%) == () goto Weak_externals

%ASMX% -q -coff -Fd ..\src\DLLIMP.ASC
if errorlevel 1 goto end
%OWLINK% format win pe f DLLIMP.OBJ op q,noreloc
..\fcmp.exe -pe DLLIMP.EXE ..\exp\DLLIMP.EXP
if errorlevel 1 goto end
del DLLIMP.EXE
del DLLIMP.OBJ

:Weak_externals
REM
REM unsupported directives in COFF
REM
%ASMX% -q -coff -eq ..\src\UNSUPP1.ASC
..\fcmp.exe UNSUPP1.ERR ..\exp\UNSUPP1.EXP
if errorlevel 1 goto end
del UNSUPP1.ERR

%ASMX% -q -coff ..\src\DATA10.ASC
if errorlevel 1 goto end
..\fcmp.exe -c DATA10.OBJ ..\exp\DATA10.EXP
if errorlevel 1 goto end
del DATA10.OBJ

%ASMX% -q -coff ..\src\COFFOP.ASC
if errorlevel 1 goto end
..\fcmp.exe -c COFFOP.OBJ ..\exp\COFFOP.EXP
if errorlevel 1 goto end
del COFFOP.OBJ
REM
REM invalid operands for COFF operators
REM
%ASMX% -q -coff -eq ..\src\COFFOP2.ASC
..\fcmp.exe COFFOP2.ERR ..\exp\COFFOP2.EXP
if errorlevel 1 goto end
del COFFOP2.ERR
REM
REM invalid segment attribute (ALIAS) changes
REM
%ASMX% -q -coff -eq ..\src\ALIAS2.ASC
..\fcmp.exe ALIAS2.ERR ..\exp\ALIAS2.EXP
if errorlevel 1 goto end
del ALIAS2.ERR
REM
REM COMDAT errors
REM
%ASMX% -q -coff -eq ..\src\COMDAT1.ASC
..\fcmp.exe COMDAT1.ERR ..\exp\COMDAT1.EXP
if errorlevel 1 goto end
del COMDAT1.ERR
REM
REM COMDAT object module
REM
%ASMX% -q -coff ..\src\COMDAT2.ASC
if errorlevel 1 goto end
..\fcmp.exe -c COMDAT2.OBJ ..\exp\COMDAT2.EXP
if errorlevel 1 goto end
del COMDAT2.OBJ
REM
REM 64-bit SEH unwind errors
REM
%ASMX% -q -coff -eq ..\src\PROC644.ASC
..\fcmp.exe PROC644.ERR ..\exp\PROC644.EXP
if errorlevel 1 goto end
del PROC644.ERR
REM
REM CV4 debug info and multiple code sections
REM
%ASMX% -q -coff -Zi ..\src\CVCOFF1.ASC
if errorlevel 1 goto end
..\fcmp.exe -c CVCOFF1.OBJ ..\exp\CVCOFF1.EXP
if errorlevel 1 goto end
del CVCOFF1.OBJ

%ASMX% -q -coff ..\src\PROC645.ASC
if errorlevel 1 goto end
..\fcmp.exe -c PROC645.OBJ ..\exp\PROC645.EXP
if errorlevel 1 goto end
del PROC645.OBJ

%ASMX% -q -coff ..\src\COFF1.ASC
if errorlevel 1 goto end
..\fcmp.exe -c COFF1.OBJ ..\exp\COFF1.EXP
if errorlevel 1 goto end
del COFF1.OBJ
REM
REM Weak externals
REM
REM [ ALIAS <> = <> ]
REM
%ASMX% -q -coff ..\src\EXTERN11.ASC
if errorlevel 1 goto end
..\fcmp.exe -c EXTERN11.OBJ ..\exp\EXTERN11.EXP
if errorlevel 1 goto end
del EXTERN11.OBJ
REM
REM [ extern sym (altname) ...]
REM
if (%MSLINK%) == () goto end
%ASMX% -q -coff ..\src\EXTERN4.ASC
if errorlevel 1 goto end
%MSLINK% /nologo /subsystem:console EXTERN4.OBJ
..\fcmp.exe -pe EXTERN4.EXE ..\exp\EXTERN4.EXP
if errorlevel 1 goto end
del EXTERN4.EXE
del EXTERN4.OBJ
goto end

:coffdbg
%ASMX% -q -Zi -coff ..\src\DBGCV.ASC
if errorlevel 1 goto end
..\fcmp.exe -c DBGCV.OBJ ..\exp\DBGCV.EXP
if errorlevel 1 goto end
del DBGCV.OBJ
goto end

:ifdef
%ASMX% -q -zlc -zld ..\src\ISDEF.ASC
if errorlevel 1 goto end
..\fcmp.exe ISDEF.OBJ ..\exp\ISDEF.EXP
if errorlevel 1 goto end
del ISDEF.OBJ
goto end

:elf
%ASMX% -q -elf ..\src\ELF1.ASC
if errorlevel 1 goto end
..\fcmp.exe ELF1.OBJ ..\exp\ELF1.EXP
if errorlevel 1 goto end
del ELF1.OBJ
goto end

:omf
%ASMX% -q -Cu ..\src\CASEMAP1.ASC
if errorlevel 1 goto end
..\fcmp.exe CASEMAP1.OBJ ..\exp\CASEMAP1.EXP
if errorlevel 1 goto end
del CASEMAP1.OBJ

%ASMX% -q ..\src\EXTERN14.ASC
if errorlevel 1 goto end
..\fcmp.exe EXTERN14.OBJ ..\exp\EXTERN14.EXP
if errorlevel 1 goto end
del EXTERN14.OBJ

%ASMX% -q ..\src\PUBLIC2.ASC
if errorlevel 1 goto end
..\fcmp.exe PUBLIC2.OBJ ..\exp\PUBLIC2.EXP
if errorlevel 1 goto end
del PUBLIC2.OBJ

%ASMX% -q ..\src\EXTERN15.ASC
if errorlevel 1 goto end
..\fcmp.exe EXTERN15.OBJ ..\exp\EXTERN15.EXP
if errorlevel 1 goto end
del EXTERN15.OBJ
goto end

:pe
%ASMX% -q -pe ..\src\PE1.ASC
..\fcmp.exe -pe PE1.EXE ..\exp\PE1.EXP
if errorlevel 1 goto end
del PE1.EXE
goto end

:zne
%ASMX% -q -eq -Zne ..\src\OVERRID3.ASC
..\fcmp.exe OVERRID3.ERR ..\exp\OVERRID3.EXP
if errorlevel 1 goto end
del OVERRID3.ERR
goto end

:zg
%ASMX% -q -Zg -bin ..\src\LOCAL3.ASC
..\fcmp.exe LOCAL3.BIN ..\exp\LOCAL3.EXP
if errorlevel 1 goto end
del LOCAL3.BIN

%ASMX% -q -Zg -bin ..\src\INVOKE21.ASC
..\fcmp.exe INVOKE21.BIN ..\exp\INVOKE21.EXP
if errorlevel 1 goto end
del INVOKE21.BIN
goto end

:zd
%ASMX% -q -Zd -omf ..\src\LINNUM.ASC
..\fcmp.exe LINNUM.OBJ ..\exp\LINNUM.EXP
if errorlevel 1 goto end
del LINNUM.OBJ
goto end

:bin
%ASMX% -q -eq -bin ..\src\STARTUP4.ASC
..\fcmp.exe STARTUP4.ERR ..\exp\STARTUP4.EXP
if errorlevel 1 goto end
del STARTUP4.ERR
goto end

:end

