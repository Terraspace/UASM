
S1 struct
b1	db ?
w1	dw ?
d1	dd ?
S1 ends

T1 typedef WORD

_TEXT segment 'CODE'
	assume ds:_TEXT

S1tab equ this S1
T1tab equ this T1
btab  db 8 dup (0)

	mov al,btab[2]
	mov ax,S1tab.w1
	mov ax,T1tab

_TEXT ends

	end
