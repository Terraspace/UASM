.386
.model flat,stdcall
option casemap:none

include     c:\masm32\include\windows.inc
include     c:\masm32\include\kernel32.inc
include     c:\masm32\include\user32.inc

includelib  c:\masm32\lib\kernel32.lib
includelib  c:\masm32\lib\user32.lib
includelib  c:\masm32\lib\msvcrt.lib

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