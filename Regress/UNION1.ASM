
;--- unions with array members
;--- didn't work correctly prior to v2.06

U1 union
mbr1 db ?,?
mbr2 db ?,?,?
U1 ends

U2 union
mbr1 db 1,2
mbr2 db 11h,12h,13h
U2 ends

U3 union
mbr1 db 2 dup (?)
mbr2 db 3 dup (?)
U3 ends

U4 union
mbr1 db 2 dup (55h)
mbr2 db 3 dup (0AAh)
U4 ends

U5 union
mbr1 db 2 dup (?,?,?)
mbr2 db 3 dup (?,?,?)
U5 ends

U6 union
mbr1 db 2 dup (1,2,3)
mbr2 db 3 dup (4,5,6)
U6 ends

_DATA segment

v1	U1 <>
v2	U2 <>
v3	U3 <>
v4	U4 <>
v5	U5 <>
v6	U6 <>

_DATA ends

	end
