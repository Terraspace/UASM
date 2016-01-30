
;--- test ALIAS (OMF)
;--- no error expected

    .286
	.model small
	.dosseg

	.stack 200h

	includelib <alias1.lib>

	.data

externdef var1:byte
externdef var2:byte

	.code
start:
	mov al,var1
	mov al,var2
	mov ah,4Ch
	int 21h

    END start
