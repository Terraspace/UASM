    .386
    .MODEL FLAT, stdcall
    option casemap:none

    pushcontext listing ;suppress listing of includes
    .nolist
    .nocref
WIN32_LEAN_AND_MEAN equ 1 ;this is to reduce assembly time
    include c:\jwasm\wininc\include\windows.inc
    popcontext listing

includelib <kernel32.lib>
includelib <user32.lib>

    .const

string   db 13,10,"hello, world.",13,10
wstring  dw "A wide string",0
bMsg     db "An utf8 string: 䌣吲敃ሴ癔蝥⍅⍧㑖",10,0

    .code

main proc c

local dwWritten:dword
local hConsole:dword

invoke  GetStdHandle, STD_OUTPUT_HANDLE
mov     hConsole, eax

invoke  WriteConsoleA, hConsole, @CSTR("ASCII"), 9, addr dwWritten, 0
invoke  WriteConsoleW, hConsole, @WSTR("Unicode"), 7, addr dwWritten, 0
invoke WriteConsoleW, hConsole, addr wstring, 13, addr dwWritten, 0
invoke  WriteConsoleA, hConsole, addr string, sizeof string, addr dwWritten, 0
invoke  WriteConsoleA, hConsole, addr bMsg, sizeof bMsg, addr dwWritten, 0

    xor     eax,eax
    ret
main endp

;--- entry

mainCRTStartup proc c

    invoke  main
    invoke  ExitProcess, eax

mainCRTStartup endp

    END mainCRTStartup