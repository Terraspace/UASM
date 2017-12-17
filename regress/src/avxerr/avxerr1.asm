
option evex:1
option flat:1

.code

use64

korw k1, k2   ;these should generate an error.
kandw k1, k5

;korw k7, k2, k7 ; 0000 _ C5 EC: 45. FF
;add ch, al ; 0004 _ 00. C5
;?_001:
; Error: This instruction is not allowed in 64 bit mode
; aam 65 ; 0006 _ D4, 41
;db 0D4H, 41H
; Note: Function does not end with ret or jmp
; inc dword ptr [rax] ; 0008 _ FF. 00
;db 0FFH, 00H
; Reported by Gwoltman 13th Dec 2017


vfmsub231sd xmm1, xmm2, zmm3
;assembles as
;vfmsub231sd xmm1, xmm2, xmm3 ; 0013 _ 62 F2 ED 08: BB. CB
;It should raise an error instead.
;Reported by Gwoltman 14th Dec 2017