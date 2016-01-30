
;--- some expression issues. Assembles with errors!

	.386
	.model flat
	option casemap:none

	.data
v1	dd 0
	.code

	mov eax,dword
	mov eax,dword+1
	mov eax,[ebx+dword]
	mov eax,4[ebx]
	mov eax,[4][ebx]
	mov eax,[dword][ebx]
	mov eax,dword+1[ebx]
	mov eax,[ebx][dword]
	mov eax,dword + v1
	mov eax,dword[2]
	mov eax,dword[word]
	mov eax,dword ptr [ebx]
	mov eax,dword ptr ebx
	mov eax,(ebx)

	mov eax,dword[ebx]	;invalid (syntax error in expression)
	mov eax,1+dword[ebx];invalid (syntax error in expression)
	mov eax,dword [v1]	;invalid (syntax error in expression)
	mov eax,dword (v1)	;invalid (syntax error in expression)
	mov eax,dword v1	;invalid (missing operator)
	mov eax,dword (ebx)	;invalid (invalid use of register)

    end

