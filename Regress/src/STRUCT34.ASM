
;--- struct forward ref
;--- added in v2.10

_TEXT segment para 'CODE'
    mov si,offset S1   ;causes additional confusion for assembler
    mov ax,[si].S1.f1

S1  struct
f1  dw ?
f2  dw ?
S1  ends

_TEXT ends
end
