
;--- line concatenation inside macros.
;--- internal handling has changed with v2.05

	.386
	.model flat

m1 macro
local x,y,\
z
x	db 1
y	db 2
z   db 3
	endm

	.code

	m1
	m1

	end
