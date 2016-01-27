
;--- unsupported directives in COFF

	.486
	.model flat, stdcall
	option casemap:none

;--- .DOSSEG is ignored with -coff or -elf
	.DOSSEG

;--- GROUP is not supported 
XX  GROUP _TEXT

	.code

	ret

	end
