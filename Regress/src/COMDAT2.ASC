
	.486
	.model flat, stdcall

_TEXT_x1 segment flat comdat(1) alias(".text")
x1 proc c
	mov eax,1
	ret
x1 endp
_TEXT_x1 ends

_DATA_x1A segment flat comdat(5,_TEXT_x1) alias(".data")
	db 1,2,3,4,5
_DATA_x1A ends

_TEXT_x2 segment flat comdat(1) alias(".text")
x2 proc c private
	mov eax,2
	ret
x2 endp
_TEXT_x2 ends

_TEXT_x3 segment flat comdat(1) alias(".text")
x3 proc c
	mov eax,3
	ret
x3 endp
_TEXT_x3 ends

ExitProcess proto stdcall :dword

_TEXT_mainCRTStartup segment flat comdat(1) alias(".text")
mainCRTStartup proc c
	call x1
	invoke ExitProcess, 0
	ret
mainCRTStartup endp
_TEXT_mainCRTStartup ends

end mainCRTStartup
