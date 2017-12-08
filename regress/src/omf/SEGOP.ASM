
;--- problem with SEG operator, if operand is a struct member.
;--- addend was wrong in object module.
;--- fixed in v2.07.

.model small
.stack 128

foo struc
c_b1 db ?
c_b2 db ?
foo ends

.data
 db 5 dup (?)
bar foo <?>
.code
start:
mov ax,seg bar.c_b2
sub ax,seg _DATA
mov ah,4Ch
int 21h
end start
