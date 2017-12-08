
;--- invoke with function pointers, COMPACT model

	.model compact, stdcall
	.386
	.stack

type_call_c    typedef proto c s1:ptr, s2:ptr, argb:byte, argw:word
type_call_fc   typedef proto far c s1:ptr, s2:ptr, argb:byte, argw:word
ptr_call_nc    typedef ptr type_call_c
ptr_call_fc    typedef ptr type_call_fc

;ptr_ptr_call_c typedef ptr ptr type_call_c

	.data

tbl_nc ptr_call_nc p1n, p2n
tbl_fc ptr_call_fc p1f, p2f

;tbl_pc ptr_ptr_call_c type_call_c,type_call_c

	.code

	assume ds:DGROUP

p1n proc
	ret
p1n endp
p2n proc
	ret
p2n endp
p1f proc far
	ret
p1f endp
p2f proc far
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
