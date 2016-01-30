
;--- -pe format test
;--- simplest program, just a 1-byte code section

	.386
	.model flat, stdcall	;-pe requires a .model flat directive
	.code
start:
	ret
end start
