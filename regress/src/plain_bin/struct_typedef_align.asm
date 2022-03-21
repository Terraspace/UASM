.x64
.model flat

.code

OPTION FIELDALIGN:16

INNER1 struct
a1 QWORD ?
a2 QWORD ?
INNER1 ends

INNER2 typedef INNER1

S1 struct
foo QWORD ?
inn INNER1  <>      ;member offset = 0x8
S1 ends

S2 struct
foo QWORD ?
inn INNER2 <>       ;member offset = 0x10 (should be 0x8)
S2 ends

end