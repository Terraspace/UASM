
x MACRO Params:VARARG
	db '&Params'
ENDM

code segment 'CODE'
	x "A:",A," ",,
code ends
end
