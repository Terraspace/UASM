
;--- must be 2 entries for "CODE" and "code" in lnames
;--- and no complains about segment attribute changes

	option casemap:none

_TEXT segment 'CODE'
	mov al,0
_TEXT ends
_TEXT segment 'code'
	mov al,0
_TEXT ends
_TEXT segment 'XXX_CODE'
	mov al,0
_TEXT ends
_TEXT segment 'DATA'
	mov al,0
_TEXT ends

end
