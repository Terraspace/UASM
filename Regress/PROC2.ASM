
;--- test pointer types in params and locals

	.286
	.model small,c
	.386
;	.dosseg
;	.stack 200h

void struct
void ends

	.code

@MOV macro prefix
	for chr,<prefix>
	mov chr&1,-1
	mov chr&2,-1
	mov chr&3,-1
	les eax,chr&4
	endm
	endm

@OPS macro prefix
	for chr,<prefix>
	dw sizeof chr&1, lengthof chr&1, size chr&1, length chr&1
	dw sizeof chr&2, lengthof chr&2, size chr&2, length chr&2
	dw sizeof chr&3, lengthof chr&3, size chr&3, length chr&3
	dw sizeof chr&4, lengthof chr&4, size chr&4, length chr&4
	dw type chr&1, type chr&2, type chr&3, type chr&4
	endm
	endm

pr proc a1:near16,          a2:near32,          a3:far16,          a4:far32,
        b1:ptr near16,      b2:ptr near32,      b3:ptr far16,      b4:ptr far32,
        c1:near16 ptr,      c2:near32 ptr,      c3:far16 ptr,      c4:far32 ptr,
        d1:near16 ptr WORD, d2:near32 ptr WORD, d3:far16 ptr WORD, d4:far32 ptr WORD
local l1:near16
local l2:near32
local l3:far16
local l4:far32
local m1:ptr near16
local m2:ptr near32
local m3:ptr far16
local m4:ptr far32
local n1:near16 ptr
local n2:near32 ptr
local n3:far16 ptr
local n4:far32 ptr
local o1:near16 ptr WORD
local o2:near32 ptr WORD
local o3:far16 ptr WORD
local o4:far32 ptr WORD
local p1[1]:near16
local p2[1]:near32
local p3[1]:far16
local p4[1]:far32
local q1[2]:near16
local q2[2]:near32
local q3[2]:far16
local q4[2]:far32
local r1[0]:near16
local r2[0]:near32
local r3[0]:far16
local r4[0]:far32
local s1:void
local s2[0]:void
local s3[1]:void
local s4[2]:void
local t1:ptr void
local t2[0]:ptr void
local t3[1]:ptr void
local t4[2]:ptr void

	@MOV <a,b,c,d,l,m,n,o,p,q>
	@OPS <a,b,c,d,l,m,n,o,p,q,r,s,t>

	ret
pr endp

start:
	invoke pr,0,1,2,3,4,5,6,7,0,-1,-2,-3,-4,-5,-6,-7
	mov ah,4Ch
	int 21h

	end start
