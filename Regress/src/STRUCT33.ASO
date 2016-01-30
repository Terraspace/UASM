
;--- errors
;--- 1. union redefined as struct
;--- 2. struct redefined as struct, but different members
;--- 3. embedded struct contained twice
;--- 4. struct redefined as typedef

	.386
	.model flat, stdcall
	option casemap:none

;--- case 1

S1 union
f1 db ?
f2 db ?
S1 ends

S1 struct
f1 db ?
f2 db ?
S1 ends

;--- case 2a (member name differs)

S2A struct
f1 db ?
S2A ends

S2A struct
f2 db ?
S2A ends

;--- case 2b (member size differs)

S2B struct
f1 db ?
S2B ends

S2B struct
f1 dw ?
S2B ends

;--- case 2c (just the sign differs, this is accepted)

S2C struct
f1 BYTE ?
S2C ends

S2C struct
f1 SBYTE ?
S2C ends

;--- case 3

S3 struct
struct ES1
f1 db ?
ends
struct ES1
f2 db ?
ends
S3 ends

S4 struct
	db ?
S4 ends

S4 typedef BYTE

	end
