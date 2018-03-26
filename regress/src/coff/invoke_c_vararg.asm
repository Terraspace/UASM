; Regression test for reported masm32 forum case of Jimg / January 2018.
; EQU is evaluating structure reference as an address instead of embedding it as a masm compatible text equate.

.nolist
.386
.model flat, stdcall
option casemap:none

include C:\masm32\include\windows.inc
include C:\masm32\include\kernel32.inc
include C:\masm32\include\user32.inc

includelib user32.lib
includelib kernel32.lib
.list
.data
MsgCaption db "equtest",0
.data?
    dbuf db 1000 dup (?)
    hx dd ?
    wr RECT <?>
    wx equ wr.left
.code

Program:
    mov hx,8888
    mov wr.left,10
    mov wr.right,90
    mov wr.top,20
    .data
    dbgfmt db 'hx=%d',10
        db 'wr.left=%d',10
        db 'hx=%d',10
        db 'wx left=%d',10
        db 'hx=%d',10
        db 0
    .code
    invoke wsprintf,addr dbuf,addr dbgfmt, \
       hx,wr.left,hx,wx,hx
    
	invoke MessageBox, 0,addr dbuf, addr MsgCaption, MB_OK
	invoke ExitProcess,0
end Program