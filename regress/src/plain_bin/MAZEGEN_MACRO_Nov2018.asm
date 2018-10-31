.X64
.MODEL FLAT
.LISTALL
.LISTMACROALL

.DATA
ASSUME cs:_DATA

context_public_label MACRO postfix:REQ
 PUBLIC label_&postfix
 EXITM <label_&postfix:>
ENDM

context_public_label (test)

jmp qword ptr label_test
END
