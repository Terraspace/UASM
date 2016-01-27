
;--- END inside macro is no error

m1 macro
	end
endm

_DATA segment
	db 0
_DATA ends

	m1

