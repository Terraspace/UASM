
;--- equates with text macro as value
;--- since v2.08, jwasm's EQU accepts 64-bit expressions as numeric,
;--- but only 32-bit if the argument is a plain number.

	.386
	.model flat
	option casemap:none

	.code

	db 0	;ensures that EQUates are handled in pass 1 AND 2.

;E1	equ 100000000h	;will be text <100000000h>

TM1	textequ <7f000000h>
E2	equ TM1			;will be a number (value of TM1), no reference to TM1 anymore
TM1 textequ <55aah>	;doesn't matter

TM2	textequ <100000000h>
E3	equ TM2			;will be text <TM2>
TM2 textequ <55aah>	;does matter

;	mov eax,E1	;error 'constant value too large'
	mov eax,E2
;--- the following line is accepted, because E3 just references TM2,
;--- and TM2 has been redefined to a 16-bit value.
	mov eax,E3

	END
