
;--- invoke with function pointers, MEDIUM model

	.model medium, stdcall
	.386
	.stack

type_call_c    typedef proto c s1:ptr, s2:ptr, argb:byte, argw:word
type_call_nc   typedef proto near c s1:ptr, s2:ptr, argb:byte, argw:word
ptr_call_nc    typedef ptr type_call_nc
ptr_call_fc    typedef ptr type_call_c

	.data

tbl_nc ptr_call_nc p1n, p2n
tbl_fc ptr_call_fc p1f, p2f

	.code

	assume ds:DGROUP

p1n proc near
	ret
p1n endp
p2n proc near
	ret
p2n endp
p1f proc
	ret
p1f endp
p2f proc
	ret
p2f endp

main proc
	mov ax,@data
	mov ds,ax
	invoke tbl_nc[0],1,2,3,4
	invoke tbl_fc[0],1,2,3,4
	mov ah,4ch
	int 21h
main endp

	end main
