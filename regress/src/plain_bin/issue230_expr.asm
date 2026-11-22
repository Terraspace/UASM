.386
.model flat
DBW RECORD hibyte:8,lobyte:8
COLOR RECORD blink:1,back:3,intense:1,fore:3
DEFREC RECORD upper:8=12h,lower:8=34h
.code
value equ (DBW <1,2>)+3
.errnz value-105h
mov ax,DBW <0ah,' '>
mov ax,(DBW <0ah,20h>)
mov ax,DBW <0ah,20h>+1
mov al,HIGH DBW <0ah,20h>
mov ax,DBW <COLOR<>,12h>
mov ax,DBW <COLOR<1,2,1,3>,12h>
mov ax,DBW <(2+3)*2,LOW (1234h+1)>
mov ax,DEFREC <>
mov ax,DEFREC <,56h>
mov ax,DEFREC <78h,>
mov ax,2*DBW <1,2>+3
mov ax,DBW <1,2>+DBW <3,4>
mov ax,LOWWORD (DBW <1,2> SHL 4)
mov ax,DBW <1,2> OR 8000h
mov ax,DBW {1,2}
mov ax,DBW <-1,256>
mov ax,DBW <256,-1>
dw (DBW <2,3>)+1
mov eax,DBW <0,256>
mov eax,DBW <0,-1>
mov eax,DBW <256,0>
end
