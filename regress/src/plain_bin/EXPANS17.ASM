
;--- problem: text macro evaluating to void

;--- with v2.05, commas at the end of instruction lines won't
;--- cause a concatenation anymore! This is Masm-compatible.
;--- But with directives, it must work.

	.286
	.model small

TE1	textequ <>

	.code

p1 proc stdcall a1:word
	ret
p1 endp

	invoke p1,TE1
		cx

end

