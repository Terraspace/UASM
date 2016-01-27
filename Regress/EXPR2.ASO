
;--- -Zm switch expression differences
;--- [] and () have another precedence
;--- ( 9 instead of 1 ) if -Zm is set.

	.286
	.model small
	.code
v1	dw 0
;--- errors without -Zm
	mov ax,-5[bx]
	mov ax,+5[bx]
	mov ax,v1-5[bx]
	mov ax,v1+5[bx] ;this is always ok

;--- ok with -Zm
	option m510
	mov ax,-5[bx]
	mov ax,+5[bx]
	mov ax,v1-5[bx]
	mov ax,v1+5[bx] ;this is always ok

    end

