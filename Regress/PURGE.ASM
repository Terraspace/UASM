
;--- purge test
;--- since v2.05, purge arguments are expanded, so it's now possible
;--- to use a text macro or a macro function invocation as arguments.

	.386
	.model flat, stdcall

m1 macro
	db 1
endm
m2 macro
	db 2
endm
m3 macro
	db 3
endm

tm1	textequ <m2>

mf1 macro
	exitm <m3>
	endm

	.code
	m1
	m2
	m3
	purge m1,tm1,mf1()
	purge mf1	;now purge the macro function
	m1
	m2
	m3
	db -1
	end
