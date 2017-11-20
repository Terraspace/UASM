
;--- INSTR directive 
;--- also a test of OWFCHLP.INC

;--- @StoreArg: helper macro defined in OWFCHLP.INC

@StoreArg macro dst, src
local displ, typ
?Reg1End InStr src,<::>
if ?Reg1End
  ?Reg2End InStr ?Reg1End+2, src, <::>
  if ?Reg2End
	?Reg3End InStr ?Reg2End+2, src, <::>
  else
	?Reg3End = 0
  endif
  if @WordSize eq 4
	typ equ <dword>
  else
	typ equ <word>
  endif
  if ?Reg3End
	mov typ ptr dst, @SubStr( %src, ?Reg3End+2 )
	mov typ ptr dst+@WordSize, @SubStr( %src, ?Reg2End+2, ?Reg3End-(?Reg2End+2) )
	displ = 2*@WordSize
  else
	displ = 0
  endif
  if ?Reg2End
	mov typ ptr dst+displ, @SubStr( %src, ?Reg1End+2, ?Reg2End-(?Reg1End+2) )
  else
	mov typ ptr dst+displ, @SubStr( %src, ?Reg1End+2 )
  endif
	mov typ ptr dst+displ+@WordSize, @SubStr( %src, 1, ?Reg1End-1 )
else
	mov dst, src
endif
	endm

TM0	textequ <ax>
TM1	textequ <ax::dx>
TM2	textequ <ax::bx::cx::dx>

M1 macro arg
%E1	instr <arg>,<::>
	db E1
	endm

M2 macro arg
E1	instr arg,<::>
	db E1
	endm

_TEXT segment word public 'CODE'

	assume ds:_TEXT

%E1	instr <TM1>,<::>
	db E1
;%E1	instr TM1,<::>    ;this won't work, since TM1 is expanded without brackets
E1	instr TM1,<::>
	db E1

	M1 <ax::bx::cx::dx>
	M1 TM2
	M2 <<ax::bx::cx::dx>>
	M2 TM2                ;this works because the argument is NOT expanded
;	M2 %TM2               ;this won't work because the argument IS expanded


dq1 label qword
dd1	label dword
dw1	label word
	db 8 dup (0)

	@StoreArg dw1,TM0
	@StoreArg dd1,TM1
	@StoreArg dq1,TM2

_TEXT ends

	END
