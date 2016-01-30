
;--- test weak externals for COFF
;--- this is to be linked with MS coff linker

	.386
	.model flat,c

	.data

extern v1e ( v1 ) : word
extern v1ee ( v1 ) : word	;another external with same altname
;externdef v1: word			;alt symbol may be external
v1	dw 0

	.code

;--- for coff, internal symbols used to resolve weak externals
;--- must be public.

	public v1

extern p1e ( p1 ) : proto

p1 proc
	ret
p1 endp

start:
	mov ax,v1
	mov ax,v1e
	call p1e
	ret

	end start
