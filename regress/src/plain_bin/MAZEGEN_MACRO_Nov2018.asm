.X64
.MODEL FLAT
.LISTALL
.LISTMACROALL

; JMP encodings are not correctly processed when inside .DATA

.DATA
ASSUME cs:_DATA

context_public_label MACRO postfix:REQ
 PUBLIC label_&postfix
 EXITM <label_&postfix:>
ENDM

context_public_label (test)

jmp label_test ; this should be a jmp rel8 (-2)

stuff db 1000 DUP (0x0)

jmp label_test ; this should need a jmp rel32 (-1007)

.CODE

context_public_label (test2)

jmp label_test2 ; this should be a jmp rel8

stuff2 db 1000 DUP (0x90)

jmp label_test2 ; this should need a 32bit ofs (jmp rel32)

END
