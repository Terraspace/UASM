;
; http://masm32.com/board/index.php?topic=6171.msg65539#msg65539
;
	.386
	.model flat
	.code

	row = -1
	REPT 8
	    row = row SHR 4
	    mov eax,row
	ENDM

	end
