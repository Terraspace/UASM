.686p
.mmx
.xmm
.model flat,stdcall
option casemap:none
option literals:on

include     c:\masm32\include\windows.inc
include     c:\masm32\include\kernel32.inc
include     c:\masm32\include\user32.inc

includelib  c:\masm32\lib\kernel32.lib
includelib  c:\masm32\lib\user32.lib
includelib  c:\masm32\lib\msvcrt.lib

printf      PROTO C :PTR, :VARARG
sum         PROTO :DWORD, :DWORD
sumAsFlt    PROTO (REAL4) :DWORD, :DWORD

.data

str1        db '%u',13,10,0
str2        db '%f',13,10,0

.code

start:

    sum( 90, sum( 20, 10 ) )
    printf( ADDR str1, sum( 80, 20 ) )
	printf( ADDR str2, 1.0 )
	printf( "%f\n", sumAsFlt( 20, 30 ) )
	
    invoke  ExitProcess,0

sum PROC x:DWORD, y:DWORD
    mov eax,x
    add eax,y
    ret
sum ENDP

sumAsFlt PROC (REAL4) x:DWORD, y:DWORD
	mov eax,x
	add eax,y
	cvtsi2ss xmm0,eax
	ret
sumAsFlt ENDP

END start