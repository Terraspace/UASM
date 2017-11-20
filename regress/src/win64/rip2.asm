ifdef __JWASM__
_TEXT segment PARA FLAT PUBLIC 'CODE'
_TEXT ends
_DATA segment PARA FLAT PUBLIC 'DATA'
_DATA ends
assume cs:flat,ds:flat,ss:flat,es:flat,fs:_DATA,gs:nothing
endif

_DATA segment
var dd 1
_DATA ends

_TEXT segment
	lea rcx,gs:[1234h]
	lea rax,var
	lea rdx,fs:[var]
	lea eax,var
	lea edx,fs:[var]
	mov edi,fs:[var]
_TEXT ends

    end
