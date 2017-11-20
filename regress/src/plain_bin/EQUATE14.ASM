
;--- equates/assembly time variables with type

	.286
	.model small

eq_b equ byte ptr 1
eq_w equ word ptr -2
at_b = byte ptr 1
at_w = word ptr -2

	.code

	mov al,byte ptr -1
	mov al,eq_b
	mov ax,eq_w
	mov al,at_b
	mov ax,at_w

	imul [bp+eq_w]
	add [bp+at_w], 70Ah

end

