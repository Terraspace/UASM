
;--- arithmetic instructions
;--- second operand is immediate and too large

	.386
	.model flat

	.code

vb	label byte
vw	label word
vd	label dword

	add al,100h
	add cl,100h
	add vb,100h

	add ax,10000h	;accepted by Masm
	add cx,10000h	;accepted by Masm
	add vw,10000h	;accepted by Masm

	add eax,100000000h
	add ecx,100000000h
	add vd, 100000000h

	end
