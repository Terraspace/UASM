
;--- an undefined member in a critical expression must emit an error in pass one

	.386
	.model flat, stdcall

	.code

S1 struct
f1 db ?
S1 ends

myvar S1 <>
nostruct db ?

	if type(nostruct.foo) eq BYTE
		db 0
	elseif type(nostruct.foo[ecx]) eq BYTE
		db 1
	else
		db 2
	endif

	if type(myvar.f2) eq BYTE
		db 0
	elseif type(myvar.f2[ecx]) eq BYTE
		db 1
	else
		db 2
	endif

end
