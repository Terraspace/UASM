
;--- regression in v2.08-2.09: EQU float operand was stored as number 0.
;--- must become a text instead.

    .386
    .MODEL FLAT
    .CODE

F1  EQU  1000.
F2  EQU  1000.0

    .DATA

%	db "&F1", "&F2"

END
