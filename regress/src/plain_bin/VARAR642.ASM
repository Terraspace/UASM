
;--- VARARG in 64-bit, with win64:1
;--- in the printf-prologue, all 4 registers
;--- have to be stored in shadow space.
;--- works since v2.09.

	.x64
	.model flat, fastcall

	option casemap:none
	option win64:3

	.CODE

szFmt1 db "number: %u", 10, 0
szFmt2 db "numbers: %u %u", 10, 0
	nop
	nop
	nop
	nop

printf proc szFmt:ptr byte, args:VARARG
	ret
	align 8
printf endp

;--- main()

main proc

	invoke printf, addr szFmt1, 1
	invoke printf, addr szFmt2, 1, 2
	invoke printf, addr szFmt2, 1, 2, 3
	invoke printf, addr szFmt2, 1, 2, 3, 4
	ret
	align 8

main endp

	END
