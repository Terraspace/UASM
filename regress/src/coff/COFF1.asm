
;--- regression in v2.10-2.11
;--- full segment directives in COFF
;--- might have confused jwasm if a BSS segment
;--- didn't have the "adequate" class name.

	.386

_TEXT segment flat 'CODE'
	xor eax, eax
lbl1:
	ret
_TEXT ends

_BSS segment flat	;<--- no class name
;--- in v2.10-2.11, this segment was assumed "uninitialized"
;--- in the coff section table, but section data was
;--- nevertheless written.
;--- since v2.12, no section data is written.
	db 20h dup (?)
_BSS ends

;--- segment behind _BSS, contains relocations 

_DATA segment flat 'DATA'
	dd lbl1, imagerel lbl1
_DATA ends

	END
