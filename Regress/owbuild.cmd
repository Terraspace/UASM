@echo off

SET SRC=\hjwasm\src
if not exist %SRC%\h\globals.h goto end

if (%WATCOM%)==() SET WATCOM=\WATCOM

for %%q in (%SRC%\*.c) do %WATCOM%\binnt\wcc386 -q -bt=nt -bc -zc -I%WATCOM%\h;%SRC%\h -3r -obmilrt -s -DNDEBUG %%q >NUL
%WATCOM%\binnt\wlink N hjwasm.exe OP q, m System nt file { *.obj } >NUL
del *.obj

if exist hjwasm.exe runtest ..\hjwasm.exe

:end

