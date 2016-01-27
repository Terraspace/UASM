
;--- INVOKE with FASTCALL, 16-bit

	.286
	.model small

	.data

b1	db 0
w1	dw 0

	.code

fast1 proc fastcall a1:word
	mov ax,a1
	ret
fast1 endp

fast2 proc fastcall a1:word, a2:word
	mov ax,a1
	add ax,a2
	ret
fast2 endp

fast3 proc fastcall a1:word, a2:byte, a3:word
	mov ax,a1
	add ax,a2
	add ax,a3
	ret
fast3 endp

fast4 proc fastcall a1:word, a2:word, a3:word, a4:word
	mov ax,a1
	add ax,a2
	add ax,a3
	add ax,a4
	ret
fast4 endp

fast5 proc fastcall a1:word, a2:byte, a3:word, a4:word, a5:word
	mov ax,a1
	add ax,a2
	add ax,a3
	add ax,a4
	add ax,a5
	ret
fast5 endp

start:
	invoke fast1, 1
	invoke fast2, 1, 2
	invoke fast3, ax, b1, 3
	invoke fast4, ax, w1, 3, 4
	invoke fast5, 1, 2, 3, 4, w1
	mov ah,4Ch
	int 21h

end start
