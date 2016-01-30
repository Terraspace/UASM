
;--- struct access test with -Zm

	option m510

s1 struct
v1		db ?
v2		db ?
struct
v3		db ?
v4		db ?
ends
s1 ends

_TEXT segment word public 'CODE'

main:
	mov al,[bx.v2]
	mov al,[bx+v2]
	mov al,[bx.v4]
	mov al,[bx+v4]
	mov al,[bx+s1]
	mov al,v4
	ret

_TEXT ends

	END
