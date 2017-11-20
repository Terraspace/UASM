
.686p
.mmx
.xmm

Code SEGMENT

_start:
	
	IF @Platform EQ 0
		xor eax,eax
		echo 'im 32bit windows'
	ELSEIF @Platform EQ 1
		xor rax,rax
		echo 'im 64bit windows'
	ELSEIF @Platform EQ 2
		xor ebx,ebx
		echo 'im 32bit linux'
	ELSEIF @Platform EQ 3
		xor rbx,rbx
		echo 'im 64bit linux'
	ENDIF

Code ENDS
end _start