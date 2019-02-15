
KMASK equ <k3>

TITLE setup
OPTION EVEX:1
OPTION FLAT:1

zfmsubpd MACRO reg, mask, reg2, reg3, reg4
ENDM

.code

USE64

zfmsubpd zmm15 {k7}{z}, zmm15, zmm27, zmm11 ; works directly when passed to macro.

;--------------------------------------------------------

vsubpd zmm0 {KMASK}, zmm1, zmm2 ; direct macro substitution works.

;--------------------------------------------------------

znoconst_rounding_single_nottp MACRO zmmval, zmmcarry, kwritemask

zfmsubpd zmm15 {k7}{z}, zmm15, zmm27, zmm11 ; works directly when passed to macro from INSIDE a macro.

zfmsubpd zmmcarry, {kwritemask}, zmmval, zmm24, zmm20
zfmsubpd zmm16, {kwritemask}, zmmcarry, zmm26, zmm22
vsubpd zmmval {kwritemask}, zmmval, zmm16
ENDM

;--------------------------------------------------------

znoconst MACRO zmmval, kwritemask


vsubpd zmmval {kwritemask}, zmmval, zmm16
	
; multiple elements can be substituted in the macro, include 
; placeholder for register and decorator.

vsubpd zmm2 {kwritemask}, zmmval, zmm16

; register + expanded decorator from macro parameter works.

ENDM

;--------------------------------------------------------

znoconst_rounding_single_nottp zmm3, zmm4, k6
znoconst zmm2, k1

;--------------------------------------------------------
; simplified example of passing a full reg + writemask
;--------------------------------------------------------

simplemacro2 MACRO zreg
vsubpd zreg, zmm10, zmm11
ENDM

simplemacro1 MACRO kwritemask
simplemacro2 zmm16 {kwritemask}
ENDM

simplemacro1 k6

;As proof that passing "zmm16 {k6}" as one argument to a macro is valid,
;consider that the following does work:

simplemacro3 MACRO zreg, kwritemask
simplemacro2 zreg {kwritemask}
ENDM

simplemacro3 zmm16, k6

;The above should expand to the valid "vsubpd zmm16 {k6}, zmm10, zmm11"
