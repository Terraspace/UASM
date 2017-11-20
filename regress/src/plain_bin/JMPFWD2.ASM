
;--- test forward jumps and backpatching
;--- this tests a pattern with 2 forward jumps, where
;--- the destination of the second jump is BEHIND the
;--- destination of the first jump.

;--- 16bit, 8086 cpu

_TEXT segment para 'CODE'
    jmp lbl1
    jnz lbl2
    db 126 dup (?)  ;distance lbl2 - ref(lbl2) is <= 127
lbl1:
    ret
lbl2:
    ret

    jmp lbl3
    jnz lbl4
    db 127 dup (?)  ;distance lbl4 - ref(lbl4) is 128
lbl3:
    ret
lbl4:
    ret
_TEXT ends

    .386

;--- 16bit, 80386 cpu

_TEXT16 segment use16 para 'CODE'
    jmp lblw1
    jnz lblw2
    db 126 dup (?)  ;distance lblw2 - ref(lblw2) is <= 127
lblw1:
    ret
lblw2:

    jmp lblw3
    jnz lblw4
    db 127 dup (?)  ;distance lblw4 - ref(lblw4) is 128
lblw3:
    ret
lblw4:
    ret
_TEXT16 ends

;--- 32bit, 80386 cpu

_TEXT32 segment use32 para 'CODE'
    jmp lblx1
    jnz lblx2
    db 126 dup (?)  ;distance lblx2 - ref(lblx2) is <= 127
lblx1:
    ret
lblx2:

    jmp lblx3
    jnz lblx4
    db 127 dup (?)  ;distance lblx4 - ref(lblx4) is 128
lblx3:
    ret
lblx4:
    ret
_TEXT32 ends

    end
