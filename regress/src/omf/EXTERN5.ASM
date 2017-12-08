
;--- test weak externals for OMF

	.286
	.model small,c
	.stack 200h

	.data

v1	dw 1234h
;extern xxx:word
extern v1e ( v1 ) : word
extern v1ee ( v1 ) : word

	.code

	public v1

extern p1e ( p1 ) : proto

p1 proc
	ret
p1 endp

;externdef v1: word

start:
	mov ax,@data
	mov ds,ax
	mov ax,v1e
	call p1e
	mov ah,4Ch
	int 21h

	end start
