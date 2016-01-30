
;--- COMDAT regression test

	.386

;--- selection must be 1-6
_TEXT1 segment comdat(0) alias(".text")
_TEXT1 ends

;--- selection must be 1-6
_TEXT2 segment comdat(7) alias(".text")
_TEXT2 ends

;--- selection 5 requires a segment ref
_TEXT3 segment comdat(5) alias(".text")
_TEXT3 ends

;--- second argument must be a segment ref
_TEXT4 segment comdat(5,abc) alias(".text")
_TEXT4 ends

_TEXT5A segment comdat(1)
_TEXT5A ends

;--- second argument must be a ref to another COMDAT ( without selection 5 )
_TEXT5 segment comdat(5,_TEXT5A) alias(".text")
_TEXT5 ends

end
