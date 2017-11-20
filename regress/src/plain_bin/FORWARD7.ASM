
        .286

_TEXT	segment 'CODE'

        shr     [bp].S1.byte1,1
        shl     v1.byte2,4

S1 struct
union
struct
byte1   db ?
byte2   db ?
ends
word1   dw ?
ends
S1 ends

v1 S1 <<<1,2>>>

_TEXT   ends

end
