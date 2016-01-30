
;--- alignment values in 16-bit

code segment dword 'CODE'
	nop
	align 4
	nop
	nop
	align 4	;since v2.11, jwasm emits 8B C0 ( like Masm ); previously it was 89 C0
	nop
	nop
	nop
	align 4
code ends

end
