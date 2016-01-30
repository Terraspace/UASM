
;--- segment attribute change

_TEXT1 segment byte 
_TEXT1 ends
_TEXT1 segment word
_TEXT1 ends

_TEXT2 segment public
_TEXT2 ends
_TEXT2 segment stack
_TEXT2 ends

	.386

_TEXT3 segment use16
_TEXT3 ends
_TEXT3 segment use32
_TEXT3 ends

;--- readonly is no problem, because it's not a true segment attribute

_TEXT4 segment
_TEXT4 ends
_TEXT4 segment readonly
_TEXT4 ends

    END
