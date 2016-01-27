
;--- operators SIZEOF, LENGTHOF, SIZE, LENGTH, TYPE
;--- for INTERNALS

	option casemap:none

S1X struct
	db ?,?
S1X ends

S1 struct
f1 db ?
f2 db ?,?
f3 db 3 dup (?)
f4 S1X <>
S1 ends

_TEXT segment word public 'CODE'
pr1 proc near
	ret
pr1 endp
pr2 proc far
	ret
pr2 endp
lb1 label near
lb2 label far
_TEXT ends

_DATA segment word public 'DATA'

vb1	db 1
vb2	db 1,2,3
vb3	db "abc"
vb4	db "abc","def"
vb5	db 4 dup (3), 2 dup (4)
	dw vb1, vb2, vb3, vb4
	db sizeof vb1, lengthof vb1, size vb1, length vb1, type vb1
	db sizeof vb2, lengthof vb2, size vb2, length vb2, type vb2
	db sizeof vb3, lengthof vb3, size vb3, length vb3, type vb3
	db sizeof vb4, lengthof vb4, size vb4, length vb4, type vb4
	db sizeof vb5, lengthof vb5, size vb5, length vb5, type vb5
	db sizeof vb5, lengthof vb5, size vb5, length vb5, type vb5

	db sizeof S1.f1, lengthof S1.f1, size S1.f1, length S1.f1, type S1.f1
	db sizeof S1.f2, lengthof S1.f2, size S1.f2, length S1.f2, type S1.f2
	db sizeof S1.f3, lengthof S1.f3, size S1.f3, length S1.f3, type S1.f3
	db sizeof S1.f4, lengthof S1.f4, size S1.f4, length S1.f4, type S1.f4

;--- no sizeof, lengthof for code labels

	dw size pr1, length pr1, type pr1
	dw size pr2, length pr2, type pr2
	dw size lb1, length lb1, type lb1
	dw size lb2, length lb2, type lb2
	dw opattr vb1, .type vb1
	dw opattr pr1, .type pr1
	dw opattr lb1, .type lb1

_DATA ends

	END
