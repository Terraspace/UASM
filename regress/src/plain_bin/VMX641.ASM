
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

	vmlaunch
	vmresume
	vmxoff

	vmxon m64
	vmclear m64
	vmptrld m64
	vmptrst m64

;--- single WIDE-bit (prefix==48h) is to be suppressed
	vmread rax, rbx
	vmread m64, rax
	vmwrite rax, rbx
	vmwrite rax, m64
	vmread r8, r9
	vmread m64, r8
	vmwrite r8, r9
	vmwrite r8, m64
if 1
;--- not supported by Masm v8 and v9, needs v10
	invept rax, m128
	invept rbx, m128
	invvpid rax, m128
	invvpid rbx, m128

	invept eax, m128
	invept ebx, m128
	invvpid eax, m128
	invvpid ebx, m128
endif

ifdef __JWASM__
	.x64
endif

	vmcall

end
