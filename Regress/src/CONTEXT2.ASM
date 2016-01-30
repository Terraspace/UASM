
;--- more tests of PUSHCONTEXT, POPCONTEXT
;--- this works since v2.10

	.386
	.model flat

	.code

;--- it's allowed to mix the types to push/pop
	pushcontext cpu
	pushcontext radix
	.radix 16
	popcontext cpu
	popcontext radix

	db 10

;--- masm allowes to push single items and pop them alltogether
;--- with jwasm, there was a problem because it knows an additional
;--- type ( alignment ). Since v2.10, ALIGNMENT is no longer included
;--- in ALL.
;
	pushcontext cpu
	pushcontext radix
	pushcontext listing
	pushcontext assumes
	.radix 16
	popcontext all

	db 10

	end
