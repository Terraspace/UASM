
option flat:1

.data

.code

	use64
	
	; Stack type operations
	
	mov QWORD PTR [rbp-0x8],rax
    mov rcx,QWORD PTR [rbp-0x8]
	
	mov QWORD PTR [rsp-0x8],rax
    mov rcx,QWORD PTR [rsp-0x8]
	
aProc PROC
	LOCAL aVar:QWORD
	
	mov rax,aVar
	mov aVar,rax
	
ret
aProc ENDP
