
;--- invoke variants

	.386
	.MODEL flat
	option casemap:none

	includelib <invoke20.lib>

p0 proto stdcall :dword

externdef stdcall p2:proto stdcall :dword

p3 typedef proto stdcall :dword
lp3 typedef ptr p3

S1 struct
f1	lp3 ?
S1 ends

externdef stdcall v2:S1

	.CODE

v1	S1 <>

p1 proc c a1
	ret
p1 endp

lbl1 label dword	;masm doesn't like forward references in invoke

	invoke p0, 1
	invoke p1, 1
	invoke p2, 1
	assume eax:ptr p3
	invoke eax,1
	invoke [eax],1
	assume eax:nothing
;	invoke [eax].p3, 1			;masm rejects (structure field expected)
	invoke p3 ptr [eax], 1
	invoke p3 ptr lbl1[eax], 1
	invoke lp3 ptr [eax], 1
	invoke lp3 ptr eax, 1
	assume eax:lp3
	invoke eax, 1
	assume eax:nothing
	invoke [eax].S1.f1, 1
	invoke [eax+lbl1].S1.f1, 1
	invoke (S1 ptr [eax]).f1, 1
	invoke v1.f1, 1
	invoke v2.f1, 1

	.stack 100
start:
	mov ah,4ch
	int 21h
	END start
