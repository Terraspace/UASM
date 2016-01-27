
;--- too large string initializer for a simple byte type
;--- wasn't checked prior to v2.07

	.386
	.model flat

S1 STRUCT
f1 BYTE ?
S1 ENDS

	.DATA

v1	S1 <"ab">

end
