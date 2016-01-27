
;--- test little-endian storage and DUP
;--- prior to v2.06, every second repetition was wrong

_DATA segment para

	dw 2 dup ("ab")
	align 4
	dw 3 dup ("a")
	align 4

	dd 2 dup ("abcd")
	align 4
	dd 3 dup ("abc")
	align 4

ifdef __JWASM__ ;Masm rejects if string size > 4
	df 2 dup ("abcdef")
	align 4
endif
	df 3 dup ("abc")
	align 4

	dq 2 dup ("abcdefgh")
	align 4
	dq 3 dup ("abc")
	align 4

;--- Masm 8/9 will define max 8 bytes for DT and OWORD

	dt 2 dup ("abcdefghij")
	align 4
	dt 3 dup ("abcde")
	align 4

if 1
	OWORD 2 dup ("abcdefghijklmnop")
	align 4
	OWORD 3 dup ("abcdefg")
	align 4
endif

_DATA ends

	end
