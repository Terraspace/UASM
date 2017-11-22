
;--- test PUSHCONTEXT, POPCONTEXT

	.386
	.model flat

	.code

	pushcontext all
	db 0
	.radix 16
	popcontext all
	db 10

	pushcontext radix, listing
	.radix 16
	popcontext radix, listing
	db 10

	pushcontext radix
	pushcontext listing
	.radix 16
	popcontext listing
	popcontext radix
	db 10

	pushcontext all
	.radix 16
	popcontext radix
	db 10

	end
