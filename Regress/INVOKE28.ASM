
;--- register AH-DH as arguments for byte params, 32-bit code

	.386
	.model flat

	.code

myproc proc stdcall x:byte
	ret
myproc endp

	invoke myproc,bh
	invoke myproc,ch
	invoke myproc,dh
	invoke myproc,ah

	end
