
;--- there was a (temporary) problem in v2.06, where the unary +/-
;--- operator strings were destroyed.

	.386
	.MODEL small

	.data

args label dword

	.code

	.if dword ptr [esi]==-124 && args[4*ebx-4]==127
		nop
	.endif

	end
