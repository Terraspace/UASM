
option flat:1

.data

.code

	use64
	
	LOADSD xmm0, 1.0
	LOADSD xmm1, 2.0
	LOADSD xmm3, 1.0
	
	; Verify opnd immediate size reductions
	bt eax,20				; Simple case, 20 is a signed byte
	bt eax,200				; Catch - 200 is > signed byte but is valid unsigned and should be allowed
	
	; Assumed unsized mem/imm moves
	mov [rsi],23			; Warning assumed byte
	mov [rsi],300			; Warning assumed word
	mov [rsi],0xfffff		; Warning assumed dword
	
	; Normal ranges
	mov al,0
	mov al,-100
	mov al,100
	mov al,-128
	mov al,127
	
	mov cl,0
	mov cl,-100
	mov cl,100
	mov cl,-128
	mov cl,127

	; Ensure a value which is >127 (signed byte) but <= 255 (unsigned) is still mapped as a byte
	mov al,200
	mov cl,200
