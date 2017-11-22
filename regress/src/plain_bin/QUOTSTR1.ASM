
	.286
	.model small

m1 macro text
	db text,0
	endm

	.data

	db "abc \; def",0	;sequence '\;' is no problem in a quoted string

;--- this isn't supposed to work
;	db "abc \
;	def"

;--- this works with Masm only
if 0
	m1 "abc \
	def"
endif
;--- a semi-colon alone is no problem

	m1 "abc ; def"

;--- a backslash alone is also no problem

	m1 "abc \ def"

;--- sequence of backslash and semi-colon is a problem.
;--- it's accepted if the semi-colon is preceded by a '!', but
;--- the '!' will become part of the string then.

	m1 "abc \!; def"

;--- this won't be accepted by either Masm or JWasm v2.05+
;--- it is accepted by JWasm v2.04 and below.
;	m1 "abc \; def"

	end
