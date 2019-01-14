
option flat:1
.code

	use64

	; not encodable in 64bit
	daa
	das
	lahf
	