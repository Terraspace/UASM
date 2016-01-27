
;--- field names of anonymous struct/union members

	.286
	.model small

S1 struct
mbr1	dw ?
mbr2	dw ?
S1 ends

S2 struct
mbr1	dw ?
mbr2	dw ?
S2 ends

S12 struct
	S1 <>
	S2 <>
S12 ends

	.data

v1	S12 <>

	end
