
option flat:1

.data

.code

	use64
	
	; Stack type operations 2
	
	mov    QWORD PTR [rsp+0x68],rax
	mov    DWORD PTR [rsp+0x70],0x0
	
	mov    DWORD PTR [rsp+0x74],0x0
	
	mov    QWORD PTR [rsp+0x78],rcx
	mov    QWORD PTR [rsp+0x90],0x6
	
	mov    QWORD PTR [rsp+0x98],0x0