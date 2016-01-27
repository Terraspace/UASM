
;--- invalid operator arguments

	.286
	.model small

	.code

v1	db 0

	mov ax, type  0	;ok

	mov ax, seg    0
	mov ax, offset 0;ok

	mov ax, length 0
	mov ax, size   0
	mov ax, lengthof 0
	mov ax, sizeof 0

	mov ax, seg    bx
	mov ax, offset bx
	mov ax, length bx
	mov ax, size   bx
	mov ax, lengthof bx
	mov ax, sizeof bx
	mov al, HIGH   bx
	mov al, LOW    bx]
	mov ax, HIGHWORD bx
	mov ax, LOWWORD  bx

	mov ax, seg    [bx]
	mov ax, offset [bx]
	mov ax, length [bx]
	mov ax, size   [bx]
	mov ax, lengthof [bx]
	mov ax, sizeof [bx]
	mov al, HIGH   [bx]
	mov al, LOW    [bx]
	mov ax, HIGHWORD [bx]
	mov ax, LOWWORD  [bx]

	mov ax, seg    _TEXT	;ok
	mov ax, offset _TEXT    ;ok
	mov ax, length _TEXT	;expected data label
	mov ax, size   _TEXT    ;expected data label
	mov ax, lengthof _TEXT  ;expected data label
	mov ax, sizeof _TEXT    ;expected data label
	mov al, HIGH   _TEXT	;should be an error
	mov al, LOW    _TEXT	;should be an error
	mov ax, HIGHWORD _TEXT
	mov ax, LOWWORD  _TEXT	;should be an error

	mov ax, length (v1+1)	;should be an error, but is currently accepted

	end
