
;--- % operator in a macro argument, only parts of the argument
;--- can be evaluated. didnt work in v2.07 and below.

.386
.model flat,stdcall
.code

foo macro arg1,arg2
;echo <arg1> <arg2>
	dw arg1,arg2
EXITM <>
endm

E1 = 122
E2 equ 322
E3 equ "12"

foo(123,<%E1+1,456>)
foo(123,<654,%E2-1>)
foo(123,<%E3+1,%E2-1,%E1+1>)

end

