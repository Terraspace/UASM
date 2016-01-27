
;--- if bits 32-63 are set to something != NULL in
;--- an equate, it was (up to v2.08) rejected to change the value
;--- to a relocatable value

	.286
	.model small

	.code

hNext = offset X
dw hNext
hNext = -1
db hNext
hNext = offset X	;error 'initializer magnitude too large' did happen
dw hNext
X:

	end
