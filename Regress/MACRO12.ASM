
;--- problem: blank macro argument might
;--- cause a line concatenation (happened in v2.05 rc).

	.286
	.model small

;--- m1: Masm ok, JWasm complain
;--- if the a2 is removed in "mov eax,a2", Masm will
;--- also complain, even if macro m1 isn't used at all.

m1 macro a1,a2
	mov ax,a1
	exitm
if 1	;the if-block is here to make the <endif> "disappear".
	mov ax,a2
endif
	endm

	.code

	m1 cx

end

