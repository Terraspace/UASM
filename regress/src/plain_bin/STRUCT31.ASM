
;--- works since jwasm v2.09
;--- older versions complained with 'too many initial values...'

	.286
	.model small

S1 struct
	dd ?,?
S1 ends

MF1 macro
	mov ax,bx
;	echo inside MF1()
	exitm <1,2>
endm

	.code

	S1 3 dup (<<MF1()>>)

	end
