
;--- expansion
;--- multiple macro functions in a line
;--- the function returns a text macro (same name, different value)

	.386
	.model flat, stdcall
	option casemap:none

literal_number macro lit_num
local_num textequ @CatStr(<NUM_>, <lit_num> )
;    .data
local_num dd lit_num
;    .code
    exitm <local_num>
endm

CNum macro lit_num
     exitm <literal_number(lit_num)>
endm


    .code

p2  proc  a1:dword, a2:dword
p2  endp

    invoke  p2, CNum(1), CNum(2)

end