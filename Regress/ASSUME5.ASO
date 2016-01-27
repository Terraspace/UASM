
;--- masm accepts 1,3; rejects 2,4
;--- jwasm v2.06 (and pred.) accepts 1,2,3,4
;--- jwasm v2.07pre rejects 3,4
;--- jwasm v2.07 rejects 4 in p1, 2 in p2
;--- jwasm v2.08 splitted test case (errors in P2 now in assume9.aso)

	.386
	.model flat
	option casemap:none

S1 STRUCT
lParam dd ?
S1 ENDS

S2 STRUCT
left dd ?
S2 ENDS

S3 STRUCT
x  dd ?
S3 ENDS

	.code

	assume ebx:ptr S2
	mov eax, [ebx].left      ;1. ok
;--- override the ASSUME
	mov eax, [ebx.S1.lParam] ;3. ok
	mov eax, [ebx].S1.lParam ;4. rejected (p1)
;--- special
	mov eax, [ebx+ecx].left         ;ok
	mov eax, [ebx+1].left           ;ok
	mov eax, [ebx][1].left          ;ok
	mov eax, S1.lParam[ebx]         ;ok

	assume ecx:ptr S3
	mov eax, [ecx][ebx].left        ;ok
	mov eax, [ecx+ebx].left         ;ok
	mov eax, [ebx+ecx].left         ;rejected (p1)
	mov eax, [ebx][ecx].left        ;rejected (p1)

	end
