
;--- v2.08: accept OFFSET OFFSET <label>

	.386
	.model flat, stdcall
	option casemap:none

	.data

data1 db 0

	.code

p1 proc
p1 endp

lbl1:

	mov eax,offset offset data1
	mov eax,offset offset p1
	mov eax,offset offset lbl1
	mov eax,offset offset 1
	mov eax,offset offset ds:[4]

end

