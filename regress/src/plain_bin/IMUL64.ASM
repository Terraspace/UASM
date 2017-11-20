
if type near eq 0ff02h
	.x64
	.model flat
endif

	.data

vb	label byte
vw	label word
vd	label dword
vq	dq 0

	.code

main proc
	imul  [vb]
	imul  [vw]
	imul  [vd]
	imul  [vq]
	imul  bl
	imul  r9b
	imul  bx
	imul  r9w
	imul  ebx
	imul  r9d
	imul  rbx

	imul  ax,bx
	imul  r9w,r11w
	imul  eax,ebx
	imul  r9d,r8d
	imul  rax,rbx
	imul  ax,[vw]
	imul  eax,[vd]
	imul  rax,[vq]
	imul  r9,[vq]

;--- the 2-operand form with immediate is actually
;--- a 3-operand form with implicite [E|R]AX register as first op.
	imul  ax,3
	imul  r9w,5
	imul  eax,3
	imul  r9d,5
	imul  rax,3
	imul  rsi,5
	imul  r11,5

	imul  ax,1234h
	imul  r9w,1234h
	imul  eax,12345678h
	imul  r9d,12345678h
	imul  rax,12345678h
	imul  rsi,12345678h
	imul  r11,12345678h

	imul  ax,bx,3
	imul  r9w,bx,3
	imul  eax,ebx,3
	imul  r9d,ebx,3

	imul  ax,bx,1234h
	imul  r9w,bx,1234h
	imul  eax,ebx,12345678h
	imul  r9d,ebx,12345678h

	ret
main endp

    END
