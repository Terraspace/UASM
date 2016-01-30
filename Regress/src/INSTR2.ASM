
;--- since INSTR value is a number (similar to SIZESTR),
;--- it's ok to use a text macro as label!
;--- didn't work prior to v2.08

	.model small

	.data

TM1	catstr <abc>
TM1	instr 1,<abcdefg>,<cd>

	db TM1

end
