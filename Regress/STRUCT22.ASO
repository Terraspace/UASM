
;--- an empty byte array in a struct

	.386
	.model flat

S1 STRUCT
  f1 db ?
  f2 db "a"
S1 ENDS

S2 STRUCT
  f1 db ?
  f2 db ""
S2 ENDS

	.DATA

v1	S1 <"a","bc">
v2	S2 <"a","b">

end
