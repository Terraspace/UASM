
;--- test LEA

	.model small
	.386

	.data

vw	dw     0
vsw SWORD  0
vd	dd     0
vsd SDWORD 0

	.code

main proc
	lea  ax,[bx]
	lea  eax,[bx]
	lea  bx,[vw]
	lea  ebx,[vw]
	lea  cx,[bx][si]
	lea  ecx,[bx][si]
	lea  dx,[vw+1]
	lea  edx,[vw+1]
	lea  si, offset vw
	lea  esi, offset vw
	lea  di,[ebx]
	lea  edi,[ebx]
	lea  ax,[ebx*2]
	lea  eax,[ebx*2]
	lea  bx,[ebx*2+ecx]
	lea  ebx,[ebx*4+ecx]
	lea  cx,[ebx*2+ecx+1]
	lea  ecx,[ebx*4+ecx+1]
	lea  cx,[ebx*2+vd]
	lea  ecx,[ebx*4+vd]
	ret
main endp

    END
