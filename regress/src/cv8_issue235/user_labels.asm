option casemap:none
named MACRO
macro_label:
 nop
ENDM
.code
public entry_point
entry_point:
named
@CFEED:
 nop
@@:
 nop
 jmp @F
@@:
 ret
.data
anonymous_address dq @B
named_address dq @CFEED
end
