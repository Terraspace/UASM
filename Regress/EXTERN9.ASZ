
;--- contains externals with alternate names
;--- that are also externals.
;--- this was a problem before v2.09.

;--- note: masm v6.15 cannot handle the case when
;--- multiple externals have the same weak external

	.286
	.model small
	.dosseg
	.stack 400h

	includelib <extern9.lib>

	public a1
extern e1 (a1):near  ;this will actually ignore a1, since e1 will be found
extern e2 (a1):near
extern e3 (e1):near  ;refer to another external
extern e4 (e1):near  ;refer to another external

	.code

start:
	mov ax,@data
	mov ds,ax
	call e1
	call e2
	call e3
	call e4
	mov ah,4ch
	int 21h

a1:
	ret

end start