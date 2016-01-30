@echo off

REM
REM BUILDEXP [<JWASM>[<JWLINK>[<LINK>]]]
REM
REM Use a version that passed the test as base
REM
SET MLBASE=\JWASM\jwasm.exe
if NOT (%1)==() SET MLBASE=%1
REM
REM Optional linker for the test
REM
REM SET OWLINK=\JWASM\jwlink.exe
if NOT (%2)==() SET OWLINK=%2
REM MS LINK >= 8.0 is needed for testing SAFESEH.
REM SET MSLINK=\VC80\bin\link.exe
if NOT (%3)==() SET MSLINK=%3

cd ..
if not exist tmp md tmp
cd tmp

for %%f in (..\src\*.asm) do call :cmpbin %%f
for %%f in (..\src\*.asn) do call :cmpmz  %%f
for %%f in (..\src\*.aso) do call :cmperr %%f
for %%f in (..\src\*.asz) do call :lnkomf %%f
for %%q in (safeseh coff coffdbg elf ifdef omf pe zne zg zd bin) do call :%%q
del *.obj
del *.err
cd ..\exp
exit

:cmpbin
%MLBASE% -q -bin -Fo ..\exp\%~n1.EXP %1
goto end

:cmpmz
%MLBASE% -q -mz -Fo ..\exp\%~n1.EXP %1
goto end

:cmperr
%MLBASE% -q -omf %1 > ..\exp\%~n1.EXP
goto end

:lnkomf
if (%OWLINK%) == () goto end
%MLBASE% -q -omf %1
%OWLINK% n ..\exp\%~n1.EXP op q,nofar format dos LIBPath ..\lib file %~n1.OBJ
goto end

:safeseh
if (%MSLINK%) == () goto end
%MLBASE% -q -coff -safeseh ..\src\SAFESEH.ASC
%MSLINK% /out:..\exp\SAFESEH.EXP /nologo /SAFESEH SAFESEH.OBJ ..\lib\SAFESEH.LIB
goto end

:coff
REM
REM ALIAS segment attribute
REM
%MLBASE% -q -coff -Fo ..\exp\SEGALIAS.EXP ..\src\SEGALIAS.ASC
REM
REM ALIGN and characteristics segment attributes
REM
%MLBASE% -q -coff -eq ..\src\SEGALIGN.ASC
type SEGALIGN.err > ..\exp\SEGALIGN.EXP
REM
REM 64-bit dll
REM
%MLBASE% -q -coff -Fo ..\exp\DLL64.EXP ..\src\DLL64.ASC
%MLBASE% -q -coff -Fo ..\exp\SEH64.EXP ..\src\SEH64.ASC
%MLBASE% -q -coff -Fo ..\exp\SEH642.EXP ..\src\SEH642.ASC
%MLBASE% -q -win64 -Fo ..\exp\MOV643.EXP ..\src\MOV643.ASC
%MLBASE% -q -win64 -Fo ..\exp\PROC641.EXP ..\src\PROC641.ASC
%MLBASE% -q -win64 -Fo ..\exp\PROC643.EXP ..\src\PROC643.ASC

REM
REM unsupported directives in COFF
REM
%MLBASE% -q -coff -eq ..\src\UNSUPP1.ASC
type UNSUPP1.err > ..\exp\UNSUPP1.EXP
%MLBASE% -q -coff -Fo ..\exp\DATA10.EXP ..\src\DATA10.ASC
%MLBASE% -q -coff -Fo ..\exp\COFFOP.EXP ..\src\COFFOP.ASC
REM
REM invalid operands for COFF operators
REM
%MLBASE% -q -coff -eq ..\src\COFFOP2.ASC
type COFFOP2.err > ..\exp\COFFOP2.EXP
REM
REM invalid segment attribute (ALIAS) changes
REM
%MLBASE% -q -coff -eq ..\src\ALIAS2.ASC
type ALIAS2.err > ..\exp\ALIAS2.EXP
REM
REM COMDAT errors
REM
%MLBASE% -q -coff -eq ..\src\COMDAT1.ASC
type COMDAT1.err > ..\exp\COMDAT1.EXP
REM
REM COMDAT object module
REM
%MLBASE% -q -coff -Fo ..\exp\COMDAT2.EXP ..\src\COMDAT2.ASC
REM
REM 64-bit SEH unwind errors
REM
%MLBASE% -q -coff -eq ..\src\PROC644.ASC
type PROC644.err > ..\exp\PROC644.EXP
REM
REM CV4 debug info and multiple code sections
REM
%MLBASE% -q -coff -Zi ..\src\CVCOFF1.ASC
ren CVCOFF1.OBJ CVCOFF1.EXP
copy CVCOFF1.EXP ..\exp >NUL
del CVCOFF1.EXP
%MLBASE% -q -coff -Fo ..\exp\PROC645.EXP ..\src\PROC645.ASC
%MLBASE% -q -coff -Fo ..\exp\COFF1.EXP ..\src\COFF1.ASC
REM
REM option dllimport
REM
if (%OWLINK%) == () goto Weak_externals
%MLBASE% -q -coff -Fd ..\src\DLLIMP.ASC
%OWLINK% name ..\exp\DLLIMP.EXP format win pe f DLLIMP.OBJ op q,noreloc

:Weak_externals
%MLBASE% -q -coff -Fo ..\exp\EXTERN11.EXP ..\src\EXTERN11.ASC
if (%MSLINK%) == () goto end
%MLBASE% -q -coff ..\src\EXTERN4.ASC
%MSLINK% /out:..\exp\EXTERN4.EXP /nologo /subsystem:console EXTERN4.OBJ
goto end

:coffdbg
%MLBASE% -q -Zi -coff ..\src\DBGCV.ASC
ren DBGCV.OBJ DBGCV.EXP
copy DBGCV.EXP ..\exp >NUL
del DBGCV.EXP
goto end

:ifdef
%MLBASE% -q -zlc -zld -Fo ..\exp\ISDEF.EXP ..\src\ISDEF.ASC
goto end

:elf
%MLBASE% -q -elf -Fo ..\exp\ELF1.EXP ..\src\ELF1.ASC
goto end

:omf
%MLBASE% -q -Cu -Fo ..\exp\CASEMAP1.EXP ..\src\CASEMAP1.ASC
%MLBASE% -q -Fo ..\exp\EXTERN14.EXP ..\src\EXTERN14.ASC
%MLBASE% -q -Fo ..\exp\PUBLIC2.EXP ..\src\PUBLIC2.ASC
%MLBASE% -q -Fo ..\exp\EXTERN15.EXP ..\src\EXTERN15.ASC
goto end

:pe
%MLBASE% -q -pe -Fo ..\exp\PE1.EXP ..\src\PE1.ASC
goto end

:zne
%MLBASE% -q -eq -Zne ..\src\OVERRID3.ASC
type OVERRID3.err > ..\exp\OVERRID3.EXP
goto end

:zg
%MLBASE% -q -Zg -bin -Fo ..\exp\LOCAL3.EXP ..\src\LOCAL3.ASC
%MLBASE% -q -Zg -bin -Fo ..\exp\INVOKE21.EXP ..\src\INVOKE21.ASC
goto end

:zd
%MLBASE% -q -Zd -omf -Fo ..\exp\LINNUM.EXP ..\src\LINNUM.ASC
goto end

:bin
%MLBASE% -q -eq -bin ..\src\STARTUP4.ASC
type STARTUP4.err > ..\exp\STARTUP4.EXP

:end
