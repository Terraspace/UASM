
;--- VMX Extension, 64-bit
;--- added in v2.09

ifdef __JWASM__
	.x64
	.model flat
endif

	.data

m32	label dword
m64	label qword
m128 label oword

	.code

ifdef __JWASM__
	.x64p  ;privileged instructions
endif

	vmxon m32
	vmread eax,ebx
	vmread m32,eax
	vmwrite eax, ebx
	vmwrite eax, m32
	invept rax, m64

end
