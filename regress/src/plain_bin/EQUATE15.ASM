
;--- assembly-time variables.
;--- since Masm v8, they store 64-bits internally,
;--- but only the lower 32-bits are displayed.
;--- additionally, one cannot set the upper 32-bits
;--- directly with a plain number.
;--- this works since jwasm v2.08

	.386
	.model flat
	option casemap:none

	.data

	.radix 16

;--- 1. assembly time variables

;C1	= 100000000h	;is rejected

C1	= 0ffffffffh + 1t	;result needs 33-bit
TM1	textequ %C1
;%echo TM1
C2	= C1 shr 2t
TM1	textequ %C2
;%echo TM1
	dd C2
	dd HIGH32 C1

;--- shifts

C1	= 1 shl 32t
TM1	textequ %C1
;%echo TM1
C2	= C1 shr 2t
TM1	textequ %C2
;%echo TM1
	dd C2
	dd HIGH32 C1

C1	= 1 shl 63t		;still fits in 64-bit
TM1	textequ %C1
;%echo TM1
C2	= C1 shr 33t
TM1	textequ %C2
;%echo TM1
	dd C2
	dd HIGH32 C1

C1	= 1 shl 64t		;beyond 64-bit
TM1	textequ %C1
;%echo TM1
C2	= C1 shr 34t	;1-bit has "vanished"
TM1	textequ %C2
;%echo TM1
	dd C2
	dd HIGH32 C1

;--- 2. EQUates
;--- unlike variables, numbers that don't fit into 32-bits
;--- are not rejected, but stored as text.

E1	equ 0ffffffffh + 1t
C2	= E1 shr 2
	dd C2
	dd HIGH32 E1

E2	equ 1 shl 32t
C2	= E2 shr 2
	dd C2
	dd HIGH32 E2
E3	equ 1 shl 63t
C2	= E3 shr 33t
	dd C2
	dd HIGH32 E3
E4	equ 1 shl 64t
C2	= E4 shr 34t
	dd C2
	dd HIGH32 E4

E5	equ 100000000h
;C2	= E5 shr 2 		;Masm v8 rejects this 'constant value too large'
;	dd C2
	END
