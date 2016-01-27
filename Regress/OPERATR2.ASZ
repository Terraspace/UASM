
;--- operator SIZEOF, SIZE, LENGTHOF, LENGTH
;--- for EXTERNALS

	.286
	.model small,stdcall
	.stack 100h

	includelib <operatr2.lib>

	.code

extern e1: byte
extern e2: word
extern e3: ptr ptr byte
extern e4: near
extern e5: far
extern e6: proto :dword

comm c1: byte
comm c2: byte : 3

p1 proc a1:near, a2:far

	dw sizeof e1
	dw sizeof e2
	dw sizeof e3
;	dw sizeof e4	;needs data label
;	dw sizeof e5
;	dw sizeof e6
	dw sizeof c1
	dw sizeof c2

;--- SIZE for externals was wrong before v2.05
	dw size e1
	dw size e2
	dw size e3
	dw size e4
	dw size e5
	dw size e6
	dw size c1
	dw size c2
	dw size a1
	dw size a2

	dw lengthof e1	;non-comm should always return 1
	dw lengthof e2
	dw lengthof e3
;	dw lengthof e4	;needs data label
;	dw lengthof e5
;	dw lengthof e6
	dw lengthof c1
	dw lengthof c2

	dw length e1	;should always return 1
	dw length e2
	dw length e3
	dw length e4
	dw length e5
	dw length e6
	dw length c1
	dw length c2

p1 endp

start:
	mov ah,4ch
	int 21h

	END start
