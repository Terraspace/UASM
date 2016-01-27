
	.386
	.model flat

	.code
	fadd  st, st
	fadd  st(1), st
	fmul  st, st
	fmul  st(1), st
	fdiv  st, st
	fdiv  st(1), st
	fdivr st, st
	fdivr st(1), st
	fsub  st, st
	fsub  st(1), st
	fsubr st, st
	fsubr st(1), st

end
