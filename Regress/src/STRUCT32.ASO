
;--- structs/unions with size 0 cannot be instanced
;--- error since v2.09

S1 struct  ;has size 0
struct
ends
S1 ends

S2 struct
	db ?
	S1 <>  ;error
S2 ends

U1 union   ;has size 0
struct
ends
struct
ends
U1 ends

U2 struct
	U1 <>  ;error
	db ?
U2 ends

_DATA segment
	S1 <>  ;error
	U1 <>  ;error
_DATA ends

	end
