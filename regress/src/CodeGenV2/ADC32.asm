
option flat:1

.data

dbVar db 10
dwVar dw 10
ddVar dd 10
ddVarA dd 10 DUP (0)

.code

	use32
	
	;80 /2 ib
	adc al,4
	adc dl,5
	adc bl,6
	
	;66 + 83 /2 ib
	adc ax,4
	adc dx,5
	adc bx,6
	
	;83 /2 ib
	adc eax,4
	adc edx,5
	adc ebx,6
	