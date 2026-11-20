; PR #241 / issue #231: EVEX broadcast state leaking from a preprocessor line.
; Source: https://github.com/Terraspace/UASM/pull/241#issuecomment-6940821359
; Based on the standalone OPATTR reproducer supplied by MarkRose.
;
; Run from this directory (no includes, libraries, linker, or execution needed):
;   ..\..\x64\Release\UASM.exe -c -q -win64 pr241_evex_state.asm
;
; Regression contract for the future Go runner:
;   Exit code 0; no diagnostics; COFF .text bytes exactly:
;   62 C1 FD 48 28 FA C3  (vmovapd zmm23,zmm10 followed by ret)
;   Compare the section bytes, not the whole timestamped COFF object.
;
; Unpatched 2.59: exit 1, A2018 and A2023 on vmovapd.
; With PR #241's three resets in Tokenize(start == 0): exit 0, bytes above.
; The condition examines a memory operand, so its register bit (10000b) is
; clear and ELSE is selected. Its {1to8} must not affect the next instruction.
; Keep the decorated OPATTR expression: an unused macro or IF 0 alone is not
; an equivalent reproducer. This case exercises broadflags leakage; the PR
; also resets decoflags and evexflag. No AVX-512-capable CPU is needed.
;
; Validated against the local 2.59 source and a scratch build with the PR fix.
; The source fix resets decorator state at the start of each new line.

OPTION EVEX:1
_TEXT SEGMENT
pr241_evex_state PROC
    IF (OPATTR (QWORD PTR [r11]{1to8})) AND 10000b
        nop
    ELSE
        vmovapd zmm23, zmm10
    ENDIF
    ret
pr241_evex_state ENDP
_TEXT ENDS
END
