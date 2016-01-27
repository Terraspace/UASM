
;--- absolute externals with type coercion for PUSHW and PUSHD

	.286
	.model small
	.386
	option casemap:none
	.dosseg

	.stack 400h

externdef value1:abs

	includelib <extern1.lib>

_TEXT32 segment use32 'CODE'

;--- for pushw and pushd, Masm+JWasm differ

;--- pushw; all variants create an opcode prefix 66h

	pushw 1                     ;Masm+JWasm: 6Ah opcode
	pushw byte ptr 1            ;Masm: 68h opcode; JWasm: 6Ah opcode
	pushw value1                ;Masm+JWasm: 68h opcode
	pushw byte ptr value1       ;Masm: 68h opcode; JWasm: 6Ah opcode

	pushd 1                     ;Masm+JWasm: 6Ah opcode
	pushd byte ptr 1            ;Masm: 68h opcode; JWasm: 6Ah opcode
	pushd value1                ;Masm+JWasm: 68h opcode
	pushd byte ptr value1       ;Masm: 68h opcode; JWasm: 6Ah opcode

_TEXT32 ends

	.code

start:
	mov ah,4ch
	int 21h

end start
