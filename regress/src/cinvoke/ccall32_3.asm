.686p
.mmx
.xmm
.model flat,stdcall
option casemap:none
option literals:on

ExitProcess PROTO :DWORD


includelib  kernel32.lib
includelib  user32.lib
includelib  msvcrt.lib

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