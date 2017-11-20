
;--- test redefinition of assembly time variables

.model small
;.stack
.code
v1 = 18
mov al,v1   ;must be 18
mov cl,v2   ;must be 16
v1 = 17
mov ah,4Ch
int 21h
v1 = 16
v2 = 16
end
