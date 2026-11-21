; Issue #231: conditional broadcast must not contaminate vmovapd.
; The following FMA must retain its own broadcast decorator.
; https://github.com/Terraspace/UASM/issues/231
.x64
OPTION EVEX:1
SZPTR EQU 8
_TEXT SEGMENT USE64
issue231 MACRO operand
    IF (OPATTR (operand)) AND 10000b
        nop
    ELSE
        vmovapd zmm23,zmm10
        vfmadd132pd zmm23,zmm29,[operand]{1to8}
    ENDIF
ENDM
issue231 QWORD PTR [r11+48*SZPTR+576+10*SZPTR+34*8]
; Explicit decorated OPATTR triggers the stale state independently of expansion.
IF (OPATTR (QWORD PTR [r11+48*SZPTR+576+10*SZPTR+34*8]{1to8})) AND 10000b
    nop
ELSE
    vmovapd zmm23,zmm10
    vfmadd132pd zmm23,zmm29,[QWORD PTR [r11+48*SZPTR+576+10*SZPTR+34*8]]{1to8}
ENDIF
_TEXT ENDS
END
