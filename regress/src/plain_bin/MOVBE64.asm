
.x64
.model flat

	.data

	.code

	movbe            ax, word ptr [rdi+0x5]  
	movbe            word ptr [rdi+0x5], ax  
	movbe            eax, dword ptr [rdi+0x5]  
	movbe            dword ptr [rdi+0x5], eax  
	movbe            rax, qword ptr [rdi+0x5]
	movbe			 qword ptr [rdi+0x5], rax
	
end
