@echo off

SET VC=\vc
SET SRC=\hjwasm\src

if not exist %SRC%\h\globals.h goto end
if not exist %VC%\bin\cl.exe goto end

%VC%\bin\cl -c -nologo -Zm200 -I%SRC%\h -I\vc\include -O2 -DNDEBUG %SRC%\*.c >NUL
%VC%\bin\link /out:hjwasm.exe /map /subsystem:console /libpath:%VC%\lib *.obj >NUL
@del *.obj

if exist hjwasm.exe runtest ..\hjwasm.exe

:end
