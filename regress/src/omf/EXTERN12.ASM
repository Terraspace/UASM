
;--- absolute externals with type coercion
;--- for PUSHW and PUSHD, see extern13.asz.

	.286
	.model small
	.386
	option casemap:none
	.dosseg

	.stack 400h

externdef value1:abs

	includelib <extern1.lib>

_TEXT32 segment use32 'CODE'

;--- arithmetic instructions ( cmp, add, sub, ... )

;--- Masm: type coercion makes Masm generate the "unsigned" version.
;--- JWasm: internal constant: type coercion IS NOT ignored.
;---        external constant ( extern:ABS ): type coercion IS ignored.

	cmp eax,1
	cmp eax,value1
	cmp eax,byte ptr 1
	cmp eax,byte ptr value1
	cmp eax,word ptr 1       ;constant value will be extended to DWORD size
	cmp eax,word ptr value1
	cmp eax,dword ptr 1
	cmp eax,dword ptr value1

	cmp ax,1
	cmp ax,value1
	cmp ax,byte ptr 1
	cmp ax,byte ptr value1	;wrong code in v2.06-2.09 - prefix 66h not generated
	cmp ax,word ptr 1
	cmp ax,word ptr value1

;--- if a memory op is first operand, type coercion is not ignored

	mov [ebx],byte ptr 1
	mov [ebx],byte ptr value1	;creates a byte-fixup!
	mov [ebx],word ptr 1
	mov [ebx],word ptr value1
	mov [ebx],dword ptr 1
	mov [ebx],dword ptr value1

;--- for push, type coercion is not ignored

	push 1
	push word ptr 1
	push value1
	push byte ptr value1		;creates a byte-fixup! - short "signed" push format is used
	push word ptr value1        ;a word is pushed

_TEXT32 ends

	.code

start:
	mov ah,4ch
	int 21h

end start
