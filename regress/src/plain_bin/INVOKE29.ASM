
;--- register AH-DH as arguments for byte params, 16-bit code

	.286
	.model small

	.code

myproc proc stdcall x:byte
	ret
myproc endp

	invoke myproc,ah
	invoke myproc,bh
	invoke myproc,ch
	invoke myproc,dh
	.386
	invoke myproc,ah
	invoke myproc,bh
	invoke myproc,ch
	invoke myproc,dh

	end
