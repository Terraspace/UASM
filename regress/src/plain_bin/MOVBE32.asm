	.686p
	.model flat, stdcall

	.data

	.code

	movbe            ax, word ptr [edi+0x5]  
	movbe            word ptr [edi+0x5], ax  
	movbe            eax, dword ptr [edi+0x5]  
	movbe            dword ptr [edi+0x5], eax  

end
