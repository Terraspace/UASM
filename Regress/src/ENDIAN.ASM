
;--- test little-endian storage of string items

_DATA segment para

	db "a"
	align 4
	db "abc"
	align 4
	db "abcd"
	align 4

	dw "ab"
	align 4
	dw "cd"
	align 4

	dd "abcd"
	align 4
	dd "abc"
	align 4

ifdef __JWASM__ ;Masm rejects
	df "abcdef"
	align 4
	df "abcde"
	align 4
endif

	dq "abcdefgh"
	align 4
	dq "abcde"
	align 4

;--- Masm 8/9 will define max 8 bytes for DT and OWORD

	dt "abcdefghij"
	align 4
	dt "abcdefg"
	align 4

	OWORD "abcdefghijklmnop"
	align 4
	OWORD "abcdefghijk"
	align 4

_DATA ends

	end
