
;--- argument 2 or 3 (immediate values) are forward references
;--- prior to v2.10, there were problems with argument 3.

	.286

_TEXT segment 'CODE'

	imul ax, E1
	imul ax, sizeof S1

;--- jwasm had problems with arg3
	imul ax, bx, E2
	imul ax, bx, sizeof S2	;this worked in v2.06-2.09 (accidentally)

_TEXT ends

E1 = 2
E2 = 2

S1 struc
f1 dw ?
S1 ends

S2 struc
f2 dw ?
S2 ends

end

