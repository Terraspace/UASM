
;--- test float instructions

	.286
	.model small
	.686

	.data

m16	label word
m32	label dword
m64 label qword
m80 label tbyte

	.code

	fadd st(0), st(1)
	fadd st(2), st(0)
	fadd m32
	fadd m64
	fadd
	faddp st(1), st(0)
	fdiv st(0), st(2)
	fdiv st(2), st(0)
	fdiv m32
	fdiv m64
	fdiv
	fdivp st(2), st(0)
	fdivr st(0), st(2)
	fdivr st(2), st(0)
	fdivr m32
	fdivr m64
	fdivr
	fdivrp st(2), st(0)
	fmul st(0), st(2)
	fmul st(2), st(0)
	fmul m32
	fmul m64
	fmul
	fmulp st(2), st(0)
	fsub st(0), st(2)
	fsub st(2), st(0)
	fsub m32
	fsub m64
	fsub
	fsubp st(2), st(0)
	fsubr st(0), st(2)
	fsubr st(2), st(0)
	fsubr m32
	fsubr m64
	fsubr
	fsubrp st(2), st(0)

	fbld m80
	fbld [bx]	;ok, since just m80 is allowed
	fbstp m80
	fbstp [bx]	;ok, since just m80 is allowed
	fcmovb   st(0), st(1)
	fcmovbe  st(0), st(2)
	fcmove   st(0), st(3)
	fcmovnb  st(0), st(4)
	fcmovnbe st(0), st(5)
	fcmovne  st(0), st(6)
	fcmovnu  st(0), st(7)
	fcmovu   st(0), st(0)
	fcomp st(2)
	fcom m32
	fcom m64
	fcom
	fcomi st(0), st(1)
	fcomip st(0), st(1)
	fcomp st(2)
	fcomp m32
	fcomp m64
	fcomp
	ffree st(1)

	fiadd m32
	fiadd m16
	ficom m32
	ficom m16
	ficomp m32
	ficomp m16
	fidiv m32
	fidiv m16
	fidivr m32
	fidivr m16
	fimul m32
	fimul m16
	fisub m32
	fisub m16
	fisubr m32
	fisubr m16

	fild m16
	fild m32
	fild m64
	fistp m16
	fistp m32
	fistp m64

	fld st(1)
	fld m32
	fld m64
	fld m80
;	fld [bx]	;error
	fstp st(1)
	fstp m32
	fstp m64
	fstp m80

;--- undocumented
;	ffreep st(2)	;is ffree st(2) + pop

	END
