
if type near eq 0ff02h
	.x64
	.model flat
	assume gs:nothing
endif

	.data

m64	label qword

	.code

	lea ax,m64
	lea eax,m64
	lea rax,m64

;	lea ax,[bx]
	lea ax,[ebx]
	lea ax,[rbx]
	lea eax,[ebx]
	lea eax,[rbx]
	lea rax,[ebx]
	lea rax,[rbx]

	lea ax,gs:[1234h]
	lea eax,gs:[1234h]
	lea rax,gs:[1234h]
	ret

	end
