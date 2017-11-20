
;--- unlike masm, jwasm needs no QWORD PTR for untyped memory

	.286
	.MODEL small
	.686

	.CODE

v1	dq 0

	cmpxchg8b [v1]
	cmpxchg8b qword ptr ds:[0]
	cmpxchg8b qword ptr [bx]
	cmpxchg8b qword ptr [bp]
	cmpxchg8b qword ptr [bp+4]
	cmpxchg8b qword ptr [ebx]

	END
