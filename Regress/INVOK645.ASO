
;--- test invoke "argument type mismatch" with 64-bit
;--- v2.11: there's now an automatic expansion for integers implemented,
;--- that's why the old errors are gone.

ifdef __JWASM__
	.x64
	.model flat, fastcall
	option win64:2
endif

	.code

if 0
p1 proc a1:qword,a2:dword,a3:word,a4:byte,a5:qword,a6:dword
p1  endp

;--- error: parameter 1
	invoke p1,eax,2,3,4,5,0
;--- error: parameter 2+3
	invoke p1,1,ax,bx,4,5,6
;--- error: parameter 5
	invoke p1,1,2,3,4, r11b, 6
;--- error: parameter 6
	invoke p1,rbx,ebx,bx,bl,0,word ptr [rsi]
endif

p1 proc a1:ptr, a2:byte, a3:byte, a4:byte, a5:ptr
p1  endp

;--- error: parameter 1
	invoke p1,eax,2,3,4,rax
	invoke p1,low32 p1,2,3,4,rax
;--- error: parameter 5
	invoke p1,rax,2,3,4,eax
	invoke p1,rax,2,3,4,low32 p1

	end
