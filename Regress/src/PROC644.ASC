
;--- 64-bit SEH errors

ifdef __JWASM__
	.x64
	.model flat,fastcall
endif
	option casemap:none

	.CODE

p1 proc FRAME

	mov rbp,rsp
;--- too many unwind codes for PROC FRAME
	repeat 256
		.setframe rbp,0
	endm
	.endprolog
	ret
p1 endp

p2 proc FRAME

	push rbp
	.pushreg rbp
	mov rbp,rsp
	.setframe rbp,0
	ret
;--- missing .ENDPROLOG
p2 endp

p3 proc

	push rbp
	.pushreg rbp	; missing FRAME
	ret
p3 endp

p4 proc FRAME

	push rbp
	.pushreg rbp
	mov rbp,rsp
	.setframe rbp,3 ; bad alignment
	.endprolog
	ret
p4 endp

p5 proc FRAME

	push rbp
	.pushreg rbp
	mov rbp,rsp
	.setframe rbp,256	; value > 240
	.endprolog
	ret
p5 endp

;--- v2.12: added

p6 proc FRAME

	sub rsp,40
	.allocstack 40
	.savexmm128 xmm7, 24  ;bad alignment
	.endprolog
	ret
p6 endp

	END
