
;--- this is for format -bin only
;--- the second section should not be written to disk,
;--- but should affect "current" offset.

    .386

S1 segment FLAT	;file offset 0
    db 1
S1 ends

S2 segment FLAT
    org 40h
S2 ends

S3 segment FLAT	;file offset 10h, offset 50h
vb  db 2
S3 ends

_TEXT segment FLAT 'CODE'
    mov eax, offset vb
_TEXT ends

    END
