
;--- rejected assume definitions

	.286
	.model small
	.data
v1	dw 0
	.code
	assume es:[bx]
	assume es:_DATA:[bx]
	assume es:bx
	assume es:DGROUP:[1]
	assume es:DGROUP:v1
	assume es:_DATA+1
	assume es:offset _DATA
	assume es:FLAT
	assume es:_DATA          ;ok
	assume es:SEG _DATA      ;ok
	assume es:DGROUP         ;ok
	assume es:ds             ;ok
	mov ax,v1
end
