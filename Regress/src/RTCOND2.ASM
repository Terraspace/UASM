
;---  signed run-time conditionals

	.386
	.model flat

REGV = 0
res macro
	REGV = REGV + 1
	exitm <REGV>
	endm

    .code

	.if (sdword ptr eax > 1) 
		mov al,res()
	.endif

	.if (eax == 1) && (sdword ptr ebx > 1)
		mov al,res()
	.endif

	.if (!(eax == 1) && !(sdword ptr ebx > 1))
		mov al,res()
	.endif

	.if ((sdword ptr eax < 1) && (sdword ptr ebx > 1))
		mov al,res()
	.endif


	.while sdword ptr eax >= 1
		mov al,res()
		.break .if ( eax == 1 )
	.endw

	.while sdword ptr eax >= 1
		mov al,res()
		.continue .if ( eax == 1 )
	.endw

	.while sdword ptr eax >= 1
		mov al,res()
		.continue .if ( eax == 1 ) || eax == 2
	.endw

;------------------------------------------------

	end
