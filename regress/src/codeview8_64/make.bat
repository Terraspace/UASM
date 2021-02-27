..\..\..\x64\release\uasm -Zi8 -Zd -Zf -coff -c -win64 -Zp8 cv8_2.asm
link /debug /subsystem:console /machine:x64 /entry:mainCRTStartup cv8_2.obj
devenv -debugexe cv8_2.exe 