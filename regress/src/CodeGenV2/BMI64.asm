
option flat:1

.data

dbVar db 10
dwVar dw 10
ddVar dd 10
ddVarA dd 10 DUP (0)

.code

	use64
	
	andn   ebx, ecx, edx           
	andn   rbx, rcx, rdx           
	andn   ebx, ecx, DWORD PTR [rdx]
	andn   rbx, rcx, QWORD PTR [rdx]
	
	bextr ebx, ecx, edx
	bextr ebx,[rsp],edx
	bextr rbx, rcx, rdx
	bextr rbx, [rsp], rdx