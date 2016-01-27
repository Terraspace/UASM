
;--- absolute segments with -bin
;--- didn't fully work prior to v2.10

	.286

_07C0 segment at 07C0h
org 100h
l100:
_07C0 ends

_TEXT segment 'CODE'

	jmp _07C0:l100

_TEXT ends

end
