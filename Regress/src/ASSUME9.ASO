
;--- masm accepts 1,3; rejects 2,4
;--- jwasm v2.06 (and pred.) accepts 1,2,3,4
;--- jwasm v2.07pre rejects 3,4
;--- jwasm v2.07 rejects 4 in p1, 2 in p2
;--- jwasm v2.08: errors of assume5 in pass 2 (undefined symbol)

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
	mov eax, [ebx.left]      ;2. rejected, 'symbol not defined'
;--- override the ASSUME
	mov eax, [ebx.S1.lParam] ;3. ok
;--- special
	mov eax, [ebx.S1.lParam].left   ;rejected, 'symbol not defined'
	mov eax, S1.lParam[ebx]         ;ok
	mov eax, S1.lParam[ebx].left    ;Masm rejected, 'symbol not defined'; jwasm v2.08: ok
	mov eax, S1.lParam[ebx.left]    ;rejected, 'symbol not defined'

	end
