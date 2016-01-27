
;--- expansion operator (%) for macro arguments

	.286
	.model small

;--- m1: Masm ok, JWasm complain
;--- if the a2 is removed in "mov eax,a2", Masm will
;--- also complain, even if macro m1 isn't used at all.

TE1	textequ <+1+2>

TM1 macro base
	exitm <base+1>
	endm

m1 macro a1,a2
	mov al,a1
	mov cl,a2+E1
	endm

	.code

	E1 = 0
	m1 %1+2,%2+3
	m1 TE1,%TE1 + 1
	m1 <TE1>,<%TE1 + 1>
	m1 %TM1(1),%TM1(2)
	while TE1
		m1 1,2
		E1 = E1+1
		if E1 gt 2
			exitm
		endif
	endm
	E1 = 0
	while TM1(2)
		m1 1,2
		E1 = E1+1
		if E1 gt 2
			exitm
		endif
	endm

end

