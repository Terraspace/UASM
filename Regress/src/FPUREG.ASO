
;--- anonymous labels in hll expressions didn't fully work prior to v2.06

	.386
	.MODEL FLAT, stdcall
	option casemap:none

	.code

	fadd st,st[1+2]
	fadd st,st[1][2]
	fadd st,st[1]+2
	fadd st,st[1
	fadd st,st(1+2)
	fadd st,st(1)(2)
	fadd st,st(1)+2
	fadd st,st(1
	end
