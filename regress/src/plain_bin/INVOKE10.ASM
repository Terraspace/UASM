
;--- test invoke with "double" register argument

	.386
	.model flat,stdcall

	.data

	.code

_mul64 proc p1:qword, p2:dword
	ret
_mul64 endp

_mul32 proc p1:dword, p2:dword
	ret
_mul32 endp

pr1 proc p1:ptr far
	ret
pr1 endp

	invoke _mul64, edx::eax, 10000
	invoke _mul32, dx::ax, 10000
	invoke pr1, ds::eax

	end
