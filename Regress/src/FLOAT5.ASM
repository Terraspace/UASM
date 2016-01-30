
;--- float instructions with 0, 1? or 2 operands
;--- 

	.386
	.model flat

	.data

m32	label real4
m64	label real8

	.code

	fadd  st(2), st
	fadd  st,    st(2)
	fadd  m32
	fadd  m64
	fadd
	faddp st(2), st
	faddp                ;failed prior to v2.07

	fmul  st(2), st
	fmul  st,    st(2)
	fmul  m32
	fmul  m64
	fmul
	fmulp st(2), st
	fmulp                ;failed prior to v2.07

	fdiv  st(2), st
	fdiv  st,    st(2)
	fdiv  m32
	fdiv  m64
	fdiv
	fdivp st(2), st
	fdivp                ;failed prior to v2.07

	fdivr  st(2), st
	fdivr  st,    st(2)
	fdivr  m32
	fdivr  m64
	fdivr
	fdivrp st(2), st
	fdivrp               ;failed prior to v2.07

	fsub  st(2), st
	fsub  st,    st(2)
	fsub  m32        
	fsub  m64
	fsub
	fsubp st(2), st
	fsubp                ;failed prior to v2.07

	fsubr  st(2), st
	fsubr  st,    st(2)
	fsubr  m32
	fsubr  m64
	fsubr
	fsubrp st(2), st
	fsubrp               ;failed prior to v2.07

	public _start
_start:
	ret

	END _start
