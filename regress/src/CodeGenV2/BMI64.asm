
option flat:1

.data

dbVar db 10
dwVar dw 10
ddVar dd 10
ddVarA dd 10 DUP (0)

.code

	use64

	bextr ebx, ecx, edx
	bextr ebx,[rsp],edx
	bextr rbx, rcx, rdx
	bextr rbx, [rsp], rdx
	
	andn   ebx, ecx, edx           
	andn   rbx, rcx, rdx           
	andn   ebx, ecx, DWORD PTR [rdx]
	andn   rbx, rcx, QWORD PTR [rdx]
	andn   ebx, r8d, edx           
	andn   rbx, rcx, r9
	andn   r10d, r8d, edx           
	andn   rbx, r12, r9
	andn   ebx, ecx, DWORD PTR [rsi+rdx]
	andn   rbx, rcx, QWORD PTR [rdi+rdx]
	andn   ebx, ecx, DWORD PTR [rsi+rdx*2]
	andn   rbx, rcx, QWORD PTR [rdi+rdx*4]
	andn   r12d, ecx, DWORD PTR [rsi+rdx*2]
	andn   r11, rcx, QWORD PTR [rdi+rdx*4]
	andn   r12d, r8d, DWORD PTR [rsi+rdx*2]
	andn   r11, r9, QWORD PTR [rdi+rdx*4]
