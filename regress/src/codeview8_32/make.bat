..\..\..\x64\release\uasm -Zi8 -Zd -Zf -coff -c cv8_1.asm
link /debug /subsystem:console /entry:mainCRTStartup cv8_1.obj
devenv -debugexe cv8_1.exe 