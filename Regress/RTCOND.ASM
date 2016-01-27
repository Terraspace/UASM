
;---  run-time conditionals

	.386
	.model flat

REGV = 0
res macro
	REGV = REGV + 1
	exitm <REGV>
	endm

    .code

	.if 0
		mov al,res()
	.endif

	.if 1
		mov al,res()
	.endif

	.if CARRY?
		mov al,res()
	.endif

	.if ZERO?
		mov al,res()
	.endif

	.if SIGN?
		mov al,res()
	.endif

	.if !ZERO?
		mov al,res()
	.endif

	.if eax == 1
		mov al,res()
	.endif

	.if (eax == 1)
		mov al,res()
	.endif

	.if ((eax == 1))
		mov al,res()
	.endif

	.if (((eax == 1)))
		mov al,res()
	.endif

	.if (!(eax == 1))
		mov al,res()
	.endif

	.if (!!(eax == 1))
		mov al,res()
	.endif

	.if (eax > 1) 
		mov al,res()
	.endif

	.if (eax == 1) && (ebx > 1)
		mov al,res()
	.endif

	.if (!(eax == 1) && !(ebx > 1))
		mov al,res()
	.endif

	.if (!(eax == 1 && ebx == 1))
		mov al,res()
	.endif

	.if ((eax < 1) && (ebx > 1))
		mov al,res()
	.endif

	.if ( eax == 1 && ( ebx == 2 || ecx == 3 ))
		mov al,res()
	.endif

	.if (( eax == 1 || eax == 2 ) && ebx == 3 )
		mov al,res()
	.endif

	.if (!(eax == 1 || ebx == 1))
		mov al,res()
	.endif

	.if ( (eax == 1 || eax == 2) && ( ebx == 3 || ebx == 4 ))
		mov al,res()
	.endif

	.if ( eax == 1 && ebx == 2 && ecx == 3 )
		mov al,res()
	.endif

	.if ( eax == 1 || eax == 2 || eax == 3 )
		mov al,res()
	.endif

	.if ( eax == 1 && ebx == 2 && ecx == 3 ) || ( eax == 4 && ebx == 5 && ecx == 6 )
		mov al,res()
	.endif

	.if ( eax == 1 && ebx == 2 && ecx == 3 ) || (( eax == 4 && ebx == 5 && ecx == 6 ) || ( eax == 7 && ebx == 8 && ecx == 9 ))
		mov al,res()
	.endif

;------------------------------------------------

	.if eax == 1
		mov al,res()
	.else
		mov al,res()
	.endif

	.if eax == 1
		mov al,res()
	.elseif ( eax == 2 )
		mov al,res()
	.endif

	.if eax == 1
		mov al,res()
	.elseif ( eax == 2 )
		mov al,res()
	.elseif ( eax == 3 )
		mov al,res()
	.endif

	.if ( eax == 1 || eax == 2 )
		mov al,res()
	.elseif ( eax == 3 || eax == 4 )
		mov al,res()
	.elseif ( eax == 5 || eax == 6 )
		mov al,res()
	.endif

;------------------------------------------------

	.while 0
		mov al,res()
	.endw

	.while 1
		mov al,res()
	.endw

	.while OVERFLOW?
		mov al,res()
	.endw

	.while eax == 1
		mov al,res()
	.endw

	.while eax == 1 && ebx == 2
		mov al,res()
	.endw

	.while !(eax == 1 && ebx == 2)
		mov al,res()
	.endw

	.while eax == 1 && ebx == 2 && ecx == 3
		mov al,res()
	.endw

	.while eax == 1 || ebx == 2
		mov al,res()
	.endw

	.while !(eax == 1 || ebx == 2)
		mov al,res()
	.endw

	.while eax == 1 || ebx == 2 || ecx == 3
		mov al,res()
	.endw

	.while (eax == 1 || (ebx == 2 && ecx == 3))
		mov al,res()
	.endw

	.while (eax == 1 && ebx == 2) || (eax == 3 && ebx == 4)
		mov al,res()
	.endw

	.while 1
		mov al,res()
		.break
	.endw

	.while 1
		mov al,res()
		.break .if ( eax == 1 )
	.endw

	.while eax >= 1
		mov al,res()
		.break .if ( eax == 1 )
	.endw

	.while 1
		mov al,res()
		.continue
	.endw

	.while 1
		mov al,res()
		.continue .if ( eax == 1 )
	.endw

	.while eax >= 1
		mov al,res()
		.continue .if ( eax == 1 )
	.endw

	.while eax >= 1
		mov al,res()
		.continue .if ( eax == 1 ) || eax == 2
	.endw

;------------------------------------------------

	.repeat
		mov al,res()
	.until 0

	.repeat
		mov al,res()
	.until 1

	.repeat
		mov al,res()
	.until ZERO?

	.repeat
		mov al,res()
	.until eax == 1

	.repeat
		mov al,res()
	.until eax == 1 && ebx == 2

	.repeat
		mov al,res()
	.until !(eax == 1 && ebx == 2)

	.repeat
		mov al,res()
	.until eax == 1 && ebx == 2 && ecx == 3

	.repeat
		mov al,res()
	.until eax == 1 || ebx == 2

	.repeat
		mov al,res()
	.until !(eax == 1 || ebx == 2)

	.repeat
		mov al,res()
	.until eax == 1 || ebx == 2 || ecx == 3

	.repeat
		mov al,res()
	.until (eax == 1 || (ebx == 2 && ecx == 3))

	.repeat
		mov al,res()
	.until (eax == 1 && ebx == 2) || (eax == 3 && ebx == 4)

	.repeat
		mov al,res()
		.break
	.until 0

	.repeat
		mov al,res()
		.break .if ( eax == 1 )
	.until 1

	.repeat
		mov al,res()
		.break .if ( eax == 1 )
	.untilcxz

	.repeat
		mov al,res()
		.continue
	.until eax > 10

	.repeat
		mov al,res()
		.continue .if ( eax == 1 )
	.until eax > 10

	.repeat
		mov al,res()
		.continue .if ( eax == 1 ) || ( eax == 2 )
	.until eax > 10

	.repeat
		mov al,res()
		.continue .if !( eax == 1 && ebx == 2 )
	.until eax > 10

	.repeat
		mov al,res()
	.untilcxz

	.repeat
		mov al,res()
	.untilcxz edx == 2

	end
