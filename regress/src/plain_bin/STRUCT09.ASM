
;--- struct access.
;--- this emitted a warning ( and produced wrong code )
;--- prior to v2.04

	.386
	.model flat,stdcall

LIST struct
pPrev	dd ?
pNext	dd ?
LIST ends

ITEM struct
dValue	dd ?
      	db ?	;make sure the struct's size isn't "scalar"
ITEM ends

	.code

	mov [eax-sizeof LIST](LIST.pNext),1
;--- assume shouldn't matter here
	assume eax:ptr ITEM
	mov [eax-sizeof LIST](LIST.pNext),2

	end
