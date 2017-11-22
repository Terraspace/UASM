
;--- local var + [ESP]
;--- was rejected until v2.07
;--- it's probably not very useful, but Masm accepts it.

	.386
	.model flat

	.code

p1 	proc

local l1:dword

	mov eax, l1[esp]
	mov eax, [esp+l1]

p1  endp

	END
