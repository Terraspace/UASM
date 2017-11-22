
;--- arithm. instruction with signed immediates

_text segment 'CODE'

v1  db 0ffh
v2  dw 0ffffh
v3  dd 0ffffffffh

	assume ds:_text

	and al,1
	and al,byte ptr 1
	and al,-1
	and al,byte ptr -1
	and bl,2
	and bl,byte ptr 2
	and bl,-2
	and bl,byte ptr -2
	and v1,3
	and v1,byte ptr 3
	and v1,-3
	and v1,byte ptr -3

	and ax,1
	and ax,word ptr 1
	and ax,0fff1h
	and ax,word ptr 0fff1h
	and ax,-1
	and ax,word ptr -1
	and bx,2
	and bx,word ptr 2
	and bx,0fff2h
	and bx,word ptr 0fff2h
	and bx,-2
	and bx,word ptr -2
	and v2,3
	and v2,word ptr 3
	and v2,0fff3h
	and v2,word ptr 0fff3h
	and v2,sword ptr 0fff3h
	and v2,-3
	and v2,word ptr -3
	.386
	and eax,4
	and eax,dword ptr 4
	and eax,0fffffff4h
	and eax,dword ptr 0fffffff4h
	and eax,-4
	and eax,dword ptr -4
	and ebx,5
	and ebx,dword ptr 5
	and ebx,0fffffff5h
	and ebx,dword ptr 0fffffff5h
	and ebx,-5
	and ebx,dword ptr -5
	and v3,6
	and v3,dword ptr 6
	and v3,0fffffff6h
	and v3,dword ptr 0fffffff6h
	and v3,-6
	and v3,dword ptr -6
_text ends

	End
