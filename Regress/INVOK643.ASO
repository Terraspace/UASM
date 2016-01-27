
;--- test invoke "register value overwritten" with 64-bit

ifdef __JWASM__
	.x64
	.model flat, fastcall
endif

	.code

p1 proc a1:qword,a2:dword,a3:word,a4:byte,a5:qword,a6:dword
p1  endp

;--- error: ecx overwritten
	invoke p1,1,2,3,4,5,ecx
;--- error: ecx overwritten
	invoke p1,1,ecx,3,4,5,6
;--- error: ecx overwritten, r8 overwritten
	invoke p1,addr [edx],eax,3,4,addr [ecx],addr [r8]
;--- error: eax overwritten
	invoke p1, rbx,ebx,bx,bl,addr [esi],eax

	end
