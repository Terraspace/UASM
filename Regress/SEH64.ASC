
;--- SEH in 64-bit code
;--- needs coff output format

ifdef __JWASM__
	.x64
	.model flat,fastcall
	option frame:auto
endif

	.code

p1 proc frame

ifndef __JWASM__
	push rbp
	.pushreg rbp
	mov rbp, rsp
	.setframe rbp, 0
	.endprolog
endif
	xor rax,rax
ifndef __JWASM__
	add rsp,0
	pop rbp
endif
	ret

p1 endp

	END
