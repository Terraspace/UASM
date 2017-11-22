
;--- memory operands with "any" size

	.686p
	.k3d
	.xmm
	.model flat
	option casemap:none

	.data

m08	db 0
m16	dw 0
m32	dd 0
m48	df 0
m64	dq 0
m80	dt 0
m128 OWORD 0

	.code

;--- since v2.06, xlat accepts byte type only
	xlat
	xlat m08
	xlatb
	xlatb m08	;according to intel this is invalid, but Masm accepts

testany macro memop

	sgdt   memop
	sidt   memop
	invlpg memop

	fldenv  memop
	fnstenv memop
	fstenv  memop
	frstor  memop
	fnsave  memop
	fsave   memop

	fxrstor memop
	fxsave  memop

	clflush     memop
	prefetchnta memop
	prefetcht0  memop
	prefetcht1  memop
	prefetcht2  memop

	prefetch  memop
	prefetchw memop
	endm

	testany m08
	testany m16
	testany m32
	testany m48
	testany m64
	testany m80
	testany m128

	end
