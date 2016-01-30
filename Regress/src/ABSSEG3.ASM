
;--- absolute segments with -bin
;--- didn't fully work prior to v2.10

	.386

_0010 segment at 0010h
org 87654321h
l87654321:
_0010 ends

_TEXT segment 'CODE'

	jmp _0010:l87654321

_TEXT ends

end
