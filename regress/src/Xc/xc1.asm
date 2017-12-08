;
; asmc /Xc - v2.22 -- HSE
;
; Disable extended HLL directives
;
	.486
	.model flat
	.code

	option dotname

.switch macro arg
	mov	eax,arg
	endm
.case	macro arg
	mov	eax,arg
	endm
.endc	macro arg
	mov	eax,arg
	endm
.default macro arg
	mov	eax,arg
	endm
.endsw	macro arg
	mov	eax,arg
	endm
.ifb	macro arg
	mov	eax,arg
	endm
.ifw	macro arg
	mov	eax,arg
	endm
.ifd	macro arg
	mov	eax,arg
	endm
.assert macro arg
	mov	eax,arg
	endm
.assertb macro arg
	mov	eax,arg
	endm
.assertw macro arg
	mov	eax,arg
	endm
.assertd macro arg
	mov	eax,arg
	endm

.switch	 ecx
.case	 ecx
.endc	 ecx
.default ecx
.endsw	 ecx
.ifb	 ecx
.ifw	 ecx
.ifd	 ecx
.assert	 ecx
.assertb ecx
.assertw ecx
.assertd ecx

	END
