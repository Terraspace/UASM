; MASM-compatible byte immediates, including negative values below -128.
.x64
_TEXT SEGMENT USE64
mov al,-255
mov al,-200
mov al,-129
mov al,-128
mov al,-1
mov al,0
mov al,127
mov al,128
mov al,255
mov cl,-255
mov cl,-200
mov cl,-129
mov cl,-128
mov cl,-1
mov cl,0
mov cl,127
mov cl,128
mov cl,255
mov r8b,-255
mov r8b,-200
mov r8b,-129
mov r8b,-128
mov r8b,-1
mov r8b,0
mov r8b,127
mov r8b,128
mov r8b,255
mov byte ptr [rax],-255
mov byte ptr [rax],-200
mov byte ptr [rax],-129
mov byte ptr [rax],-128
mov byte ptr [rax],-1
mov byte ptr [rax],0
mov byte ptr [rax],127
mov byte ptr [rax],128
mov byte ptr [rax],255
_TEXT ENDS
END
