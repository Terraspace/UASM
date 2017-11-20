
;--- test ALIGNMENT

    .386

S1	struct
f1  db ?
    align 4
f2  dw ?
S1	ends

S2	struct 4
f1  db ?
    align
f2  dw ?
S2	ends

_TEXT segment para public 'CODE'

	int 3
	align 8
	int 3
	int 3
	align 8
	int 3
	int 3
	int 3
	align 8
	int 3
	int 3
	int 3
	int 3
	align 8
	int 3
	int 3
	int 3
	int 3
	int 3
	align 8
	int 3
	int 3
	int 3
	int 3
	int 3
	int 3
	align 8
	int 3
	int 3
	int 3
	int 3
	int 3
	int 3
	int 3
	align 8

	S1 <1,2>
	S2 <1,2>

_TEXT ends

    END
