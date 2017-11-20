
;--- Masm v8-v10 create invalid code with -omf
;--- case v4 works since jwasm v2.09.

_DATA segment

v1	db "abc","x"
	dw size v1, length v1, sizeof v1, lengthof v1	;expected: 1,1,4,4

v2	db 3 dup ('a'),"x"
	dw size v2, length v2, sizeof v2, lengthof v2	;expected: 3,3,4,4

v3	db 3 dup ('ab'),"x"
	dw size v3, length v3, sizeof v3, lengthof v3	;expected: 3,3,7,7

v4	db 3 dup (3 dup ('a')),"x"
	dw size v4, length v4, sizeof v4, lengthof v4	;expected: 3,3,10,10

_DATA ends

	end
