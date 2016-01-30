
;--- binary operators ':' and PTR (same precedence)
;--- when does the "type expression" change to an address?

	.286
	.model small

NEHDR struct
ne_magic	dw	?		;+00
ne_count	dw	?		;+02
ne_enttab	dw	?		;+04
ne_cbenttab dw	?		;+06
DGROFS		dw	?		;+08
FINFO		dw	?		;+0A
PGMFLGS		db	?		;+0C
APPFLGS		db	?		;+0D
NEHDR ends

	.data

	dw 0
d_type db 0

	.code

	cmp es:byte ptr d_type,'d'
	cmp byte ptr es:d_type,'d'
	test es:[NEHDR.APPFLGS],01
	test byte ptr es:[NEHDR.APPFLGS],01
	test es:[byte ptr NEHDR.APPFLGS],01
	test es:byte ptr [NEHDR.APPFLGS],01
	test es:byte ptr NEHDR.APPFLGS,01

	end

