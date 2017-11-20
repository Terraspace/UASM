del *.exe
del *.pdb
del *.ilk
del *.obj
c:\jwasm\uasm64 -c -win64 -Zp8 rip.asm
echo "C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Tools\MSVC\14.10.25017\bin\HostX86\x64\link.exe" /subsystem:console /machine:x64 /Libpath:"d:\winsdk\v7.1\Lib\x64" /debug c_invoke.obj msvcrt.lib



