
;--- struct field name matches arbitrary type name

S1 struct
v1	db ?
v2	db ?
S1 ends

S2 struct
v3	db ?
S2 ends

S3 struct
S1	BYTE ?
S2	db ?
S3 ends

_TEXT segment word public 'CODE'

	mov al,[bx].S3.S1
	mov ah,[bx].S3.S2
	ret

_TEXT ends

	END
