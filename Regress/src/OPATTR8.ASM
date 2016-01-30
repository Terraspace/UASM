
;--- OPATTR with a magnitude of constant value beyond 32 
;--- behaves differently in jwasm

	.386
	.model flat
	.code

.code

	dw opattr "abcd"				;string <= 4: masm = 24h, jwasm = 24h
	dw opattr "abcdef"				;string > 4: masm = 0, jwasm = 24h
	dw opattr 123456789h			;64-bit constant: masm = 0, jwasm = 24h
	dw opattr 112233445566778899aabbccddeeffh	;128-bit constant: masm = 0, jwasm = 24h

end

