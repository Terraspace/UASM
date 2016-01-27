
;--- contains both weak externals and communal variables.
;--- this was a problem before v2.09.

	.286
	.model small
	.dosseg
	.stack 400h

comm zzz:word
	public a1
	public a2
extern e1 (a1):near
extern e2 (a2):near

	.code

start:
	mov ax,@data
	mov ds,ax
	mov ax,zzz
	call e1
	call e2
	mov ah,4ch
	int 21h

a1:
a2:
	ret

end start