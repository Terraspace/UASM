
;--- ELF format: ensure that bss sections aren't included in object module

	.386

_TEXT segment flat 'CODE'
	ret
_TEXT ends

_BSS segment flat 'BSS'
	db 20h dup (?)
_BSS ends

_DATA segment flat 'DATA'
_DATA ends

_TEXT2 segment flat 'CODE'
	ret
_TEXT2 ends

	END
