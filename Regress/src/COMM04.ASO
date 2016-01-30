
;--- the size & count values must not be a forward references
;--- prior to v2.10, error was "Constant expected'

	.386
	.model flat, stdcall

COMM c1: E1: 1		;error 'E1 not defined' (both Masm +JWasm)
COMM c2: byte: E2	;error 'E2 not defined' (both Masm +JWasm)

E1 = 2
E2 = 2

	end
