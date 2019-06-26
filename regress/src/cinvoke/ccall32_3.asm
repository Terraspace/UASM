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

.data

str1        db '%u',13,10,0
str2        db '%f',13,10,0

.code

start:

	;This builds OK:
	mov edx, dword ptr [esp]
	printf("Computed sum = %.1f.\n", edx)
	;This produces Error A2102: Symbol not defined : qwordptr
    printf("Computed sum = %.1f.\n", dword ptr [esp])
	
    invoke  ExitProcess,0

END start