
;--- expression variant
;--- works since v2.08

	.386
	.model flat, stdcall

POINT struct
x	dd ?
y	dd ?
POINT ends

pMRB equ <[4+ebx.POINT]>


	.code

lbl1:
	mov eax,[4 + ebx.POINT].y
	mov eax,[ecx + ebx.POINT].y
	mov eax,[offset lbl1 + ebx.POINT].y ;Masm rejects this (probably a bug)
	mov eax,pMRB.y
end

