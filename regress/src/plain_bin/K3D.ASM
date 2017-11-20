
;--- K3D instruction test

	.586
	.model flat, stdcall
	.k3d

	.data

m64	dq 0

	.code

start:
	femms
	prefetch  m64		;accepts any memory operand
	prefetchw m64		;accepts any memory operand
	pavgusb mm0,mm1
	pavgusb mm0,m64
	pf2id   mm0,mm1
	pf2id   mm0,m64
	pf2iw   mm0,mm1
	pf2iw   mm0,m64
	pfacc   mm0,mm1
	pfacc   mm0,m64
	pfadd   mm0,mm1
	pfadd   mm0,m64
	pfcmpeq mm0,mm1
	pfcmpeq mm0,m64
	pfcmpge mm0,mm1
	pfcmpge mm0,m64
	pfcmpgt mm0,mm1
	pfcmpgt mm0,m64
	pfmax   mm0,mm1
	pfmax   mm0,m64
	pfmin   mm0,mm1
	pfmin   mm0,m64
	pfmul   mm0,mm1
	pfmul   mm0,m64
	pfnacc  mm0,mm1
	pfnacc  mm0,m64
	pfpnacc mm0,mm1
	pfpnacc mm0,m64
	pfrcp   mm0,mm1
	pfrcp   mm0,m64
	pfrcpit1 mm0,mm1
	pfrcpit1 mm0,m64
	pfrcpit2 mm0,mm1
	pfrcpit2 mm0,m64
	pfrsqit1 mm0,mm1
	pfrsqit1 mm0,m64
	pfrsqrt mm0,mm1
	pfrsqrt mm0,m64
	pfsub   mm0,mm1
	pfsub   mm0,m64
	pfsubr  mm0,mm1
	pfsubr  mm0,m64
	pi2fd   mm0,mm1
	pi2fd   mm0,m64
	pmulhrw mm0,mm1
	pmulhrw mm0,m64
	pswapd  mm0,mm1
	pswapd  mm0,m64
	ret

	End start
