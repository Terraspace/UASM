@echo off
rem tools: jwasm, jwlink, jfc, ms link (COFF)
jwasm -q -bin *.asm
for %%f in (*.asm) do call :cmpbin %%f
jwasm -q -mz *.asn
for %%f in (*.asn) do call :cmpmz  %%f
jwasm -q -omf -eq *.aso
for %%f in (*.aso) do call :cmperr %%f
jwasm -q -omf *.asz
for %%f in (*.asz) do call :lnkomf %%f
call :safeseh
call :coff
call :coffdbg
rem ifdef calls jwasmr ( won't run in 64-bit Windows )
call :ifdef
call :omf
call :pe
call :zne
call :zg
call :zd
call :bin
exit

:cmpbin
..\tools\jfc %~n1.BIN %~n1.EXP
goto end

:cmpmz
..\tools\jfc %~n1.EXE %~n1.EXP
goto end

:cmperr
..\tools\jfc %~n1.ERR %~n1.EXP
goto end

:lnkomf
..\tools\jwlink op q,nofar format dos file %~n1.OBJ
..\tools\jfc %~n1.EXE %~n1.EXP
goto end

:safeseh
jwasm -q -coff -safeseh SAFESEH.ASC
if errorlevel 1 goto end
..\tools\link /nologo /SAFESEH SAFESEH.OBJ SAFESEH.LIB
..\tools\jfc -pe SAFESEH.EXE SAFESEH.EXP
goto end

:coff
rem weak externals [ extern sym (altname) ...]
jwasm -q -coff EXTERN4.ASC
if errorlevel 1 goto end
..\tools\link /nologo /subsystem:console EXTERN4.OBJ
..\tools\jfc -pe EXTERN4.EXE EXTERN4.EXP

rem weak externals [ ALIAS <> = <> ]
jwasm -q -coff EXTERN11.ASC
if errorlevel 1 goto end
..\tools\jfc -co EXTERN11.OBJ EXTERN11.EXP

rem ALIAS segment attribute
jwasm -q -coff SEGALIAS.ASC
if errorlevel 1 goto end
..\tools\jfc -co SEGALIAS.OBJ SEGALIAS.EXP

rem ALIGN and characteristics segment attributes
jwasm -q -coff -eq SEGALIGN.ASC
..\tools\jfc SEGALIGN.ERR SEGALIGN.EXP

rem 64-bit dll
jwasm -q -coff DLL64.ASC
if errorlevel 1 goto end
..\tools\jfc -co DLL64.OBJ DLL64.EXP

jwasm -q -coff SEH64.ASC
if errorlevel 1 goto end
..\tools\jfc -co SEH64.OBJ SEH64.EXP

jwasm -q -coff SEH642.ASC
if errorlevel 1 goto end
..\tools\jfc -co SEH642.OBJ SEH642.EXP

jwasm -q -win64 MOV643.ASC
if errorlevel 1 goto end
..\tools\jfc -co MOV643.OBJ MOV643.EXP

jwasm -q -win64 PROC641.ASC
if errorlevel 1 goto end
..\tools\jfc -co PROC641.OBJ PROC641.EXP

jwasm -q -coff PROC643.ASC
if errorlevel 1 goto end
..\tools\jfc -co PROC643.OBJ PROC643.EXP

rem option dllimport
jwasm -q -coff -Fd DLLIMP.ASC
if errorlevel 1 goto end
..\tools\jwlink2 format win pe f DLLIMP.OBJ op q,noreloc
..\tools\jfc -pe DLLIMP.EXE DLLIMP.EXP

rem unsupported directives in COFF
jwasm -q -coff -eq UNSUPP1.ASC
..\tools\jfc UNSUPP1.ERR UNSUPP1.EXP

jwasm -q -coff DATA10.ASC
if errorlevel 1 goto end
..\tools\jfc -co DATA10.OBJ DATA10.EXP

jwasm -q -coff COFFOP.ASC
if errorlevel 1 goto end
..\tools\jfc -co COFFOP.OBJ COFFOP.EXP

rem invalid operands for COFF operators
jwasm -q -coff -eq COFFOP2.ASC
..\tools\jfc COFFOP2.ERR COFFOP2.EXP

rem invalid segment attribute (ALIAS) changes
jwasm -q -coff -eq ALIAS2.ASC
..\tools\jfc ALIAS2.ERR ALIAS2.EXP

rem COMDAT errors
jwasm -q -coff -eq COMDAT1.ASC
..\tools\jfc COMDAT1.ERR COMDAT1.EXP

rem COMDAT object module
jwasm -q -coff COMDAT2.ASC
..\tools\jfc -co COMDAT2.OBJ COMDAT2.EXP

rem 64-bit SEH unwind errors
jwasm -q -coff -eq PROC644.ASC
..\tools\jfc PROC644.ERR PROC644.EXP

rem CV4 debug info and multiple code sections 
jwasm -q -coff -Zi CVCOFF1.ASC
..\tools\jfc -co CVCOFF1.OBJ CVCOFF1.EXP

goto end

:coffdbg
jwasm -q -Zi -coff DBGCV.ASC
if errorlevel 1 goto end
..\tools\jfc -co DBGCV.OBJ DBGCV.EXP
goto end

:ifdef
..\owdos16r\jwasmr -q -zlc -zld ISDEF.ASC
if errorlevel 1 goto end
..\tools\jfc ISDEF.OBJ ISDEF.EXP
goto end

:omf
jwasm -q -Cu CASEMAP1.ASC
if errorlevel 1 goto end
..\tools\jfc CASEMAP1.OBJ CASEMAP1.EXP

jwasm -q EXTERN14.ASC
if errorlevel 1 goto end
..\tools\jfc EXTERN14.OBJ EXTERN14.EXP

jwasm -q PUBLIC2.ASC
if errorlevel 1 goto end
..\tools\jfc PUBLIC2.OBJ PUBLIC2.EXP

jwasm -q EXTERN15.ASC
if errorlevel 1 goto end
..\tools\jfc EXTERN15.OBJ EXTERN15.EXP
goto end

:pe
jwasm -q -pe PE1.ASC
..\tools\jfc -pe PE1.EXE PE1.EXP
goto end

:zne
jwasm -q -eq -Zne OVERRID3.ASC
..\tools\jfc OVERRID3.ERR OVERRID3.EXP
goto end

:zg
jwasm -q -Zg -bin LOCAL3.ASC
..\tools\jfc LOCAL3.BIN LOCAL3.EXP

jwasm -q -Zg -bin INVOKE21.ASC
..\tools\jfc INVOKE21.BIN INVOKE21.EXP
goto end

:zd
jwasm -q -Zd -omf LINNUM.ASC
..\tools\jfc LINNUM.OBJ LINNUM.EXP
goto end

:bin
jwasm -q -eq -bin STARTUP4.ASC
..\tools\jfc STARTUP4.ERR STARTUP4.EXP
goto end

:end
