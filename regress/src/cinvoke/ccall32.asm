.386
.model flat,stdcall
option casemap:none

ExitProcess PROTO :DWORD


includelib  kernel32.lib
includelib  user32.lib
includelib  msvcrt.lib

printf      PROTO C :DWORD,:VARARG
sum         PROTO :DWORD,:DWORD

.data

str1        db '%u',0

.code

start:

    sum(90,sum(20,10))
    printf( ADDR str1,sum( 80,20 ) )
    invoke  ExitProcess,0

sum PROC x:DWORD,y:DWORD

    mov     eax,x
    add     eax,y
    ret

sum ENDP

END start