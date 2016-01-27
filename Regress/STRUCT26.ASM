
;--- use default initializer of an embedded struct.
;--- there was a temporary error in v2.08pre that wasn't
;--- covered by regression test yet.

	.286
	.MODEL small

xxx STRUCT
m1	db ?
m2	db ?
m3	db ?
xxx ENDS

yyy STRUCT
s1	xxx {1,2,3}
m4	db ?
s2	xxx {4,5,6}
m5	db ?
yyy ENDS

	.data

v1	yyy <{3,3,3},1,{6,6,6},2>
v2	yyy <>

	end
