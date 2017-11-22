
;--- test weak externals with ALIAS for COFF.
;--- this doesn't really work with Masm, because
;--- a) the value field in the symbol table may be wrong
;--- b) wrong relocations are emitted ( DIR16 )

	.386
	.model flat,c

	.data

;--- define a few bytes to ensure that current offset is > 0.
;--- because Masm erroneously will emit the offset of v1 as value for v1e
	db 10h dup (0)

;--- v1: target is internal
	public v1
v1	dw 0
alias <v1e> = <v1>

;--- v2: target is external
externdef v2:word
alias <v2e> = <v2>

	.code

start:
	mov ax,v1
	mov ax,v1e
	mov ax,v2
	mov ax,v2e
	ret

	end start
