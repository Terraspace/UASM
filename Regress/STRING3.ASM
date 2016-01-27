
	.386
	.model flat

	.code

	lods byte  ptr cs:[esi]
	lods word  ptr ds:[esi] ;DS prefix is to be suppressed!
	lods dword ptr [esi]
	lods vb
	lods cs:vw
	lods ds:vd        ;DS prefix is to be suppressed!

	lodsb
	lodsw
	lodsd
	lodsb ds:[esi]    ;DS prefix is to be suppressed!
	lodsw ds:[esi]
	lodsd cs:[esi]

vb	db 0
vw	dw 0
vd	dd 0

	end
