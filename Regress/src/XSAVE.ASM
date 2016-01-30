
;--- xsave, xrstor, xgetbv, xsetbv

	.686p
	.MODEL flat
	option casemap:none
	.xmm

	.data

buffer label byte

	.code

	fxsave buffer
	fxrstor buffer
;--- new since v2.06
	xsave buffer
	xsave [ebx]
	xrstor buffer
	xrstor [ebx]
	xgetbv
	xsetbv	;privileged instruction!

	end
