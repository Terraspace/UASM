
;--- struct access test

	.dosseg

s1 struct
v1		db ?
v2		db ?
struct
v3		db ?
v4		db ?
ends
s1 ends

char typedef byte

s2 struct
	s1 <>	;member of type s1
s1	db ?	;member with name s1. Valid Masm syntax!
s2 ends

s3 struct
v1	db 4 dup (?)
v2	db 3 dup (?)
s1	char ?	;member with name s1, arbitrary type
s3 ends

s4 struct
m1	s1 <>
s4 ends

mac1 macro value
	exitm <value*2>
	endm

DISKIORM struct
startsec dd ?
sectors  dw ?
buffofs  dw ?
buffseg  dw ?
DISKIORM ends

_DATA segment word public 'DATA'
var1	s1 {}
var2	s1 {1,2,{3,4}}
var3	s1 {1,2,{}}
var4    s2 {<55,66,<>>}
var5    s2 {<0AAh,0BBh,<0CCh,0DDh>>,0FFh}
var6    s2 {<0AAh,mac1(44),<mac1(66),mac1(77)>>,0FFh}
var7	s3 {<1>,<2>}
_DATA ends

_TEXT segment word public 'CODE'

	assume ds:_DATA

main:
	mov ds:[DISKIORM.buffofs],offset 200h	;direct memory access
	mov al,var1.v1
	mov bl,var1.v2
	mov cl,var1.v3
	mov dl,var1.v4
	mov si,sizeof s1
	mov di,sizeof var1
	mov bp,sizeof var1.v3
	mov si,type s1
	mov si,type s2
	mov si,type s1.v4
	mov al,[bx].s1.v2
	mov al,s1.v1[bx]
	mov al, [bx].s4.m1.v1
	mov al, s4.m1.v1[bx]
	ret

_TEXT ends

	END
