
KMASK equ <k3>

TITLE setup
OPTION EVEX:1
OPTION FLAT:1

zfmsubpd MACRO reg, mask, reg2, reg3, reg4
ENDM

.code
USE64

;--------------------------------------------------------

vsubpd zmm0 {KMASK}, zmm1, zmm2 ; direct macro substitution works.

;--------------------------------------------------------

znoconst_rounding_single_nottp MACRO zmmval, zmmcarry, kwritemask
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

