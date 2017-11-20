
;--- VMX Extension
;--- added in v2.09

	.386
	.model flat

	.data

m32	label dword
m64	label qword
m128 label oword

	.code

	.686p  ;privileged instructions

	vmlaunch
	vmresume
	vmxoff

	vmxon m64
	vmclear m64
	vmptrld m64
	vmptrst m64

	vmread eax,ebx
	vmread m32,eax
	vmwrite eax, ebx
	vmwrite eax, m32

if 1
;--- not supported by Masm v8 and v9, needs v10
	invept eax, m128
	invept ebx, m128
	invvpid eax, m128
	invvpid ebx, m128
endif

	.686

	vmcall

end
