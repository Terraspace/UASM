
;--- test various macro features

    .386
    .model flat, stdcall

    .data

;--- GOTO

m1  MACRO start
E1  = start
:next
    db E1
E1  = E1 + 1
if E1 LT start+5
    goto next
endif
    ENDM

;--- EXITM + conditional directives

m2 MACRO arg
   IFIDN <arg>,<2>
      EXITM <1>
   ELSE
      EXITM <2>
   ENDIF
   ENDM

;--- & operator

m3  macro num
N&num equ num
    endm

;--- substitution inside strings

m4  macro num
    db "num = 5"
    db "&num = 5"
    endm

;--- & operator

m5  macro prefix, suffix
prefix&&suffix equ 1
    endm

;--- empty macro

m6 macro
	endm

    .CODE

    m1 1
    m1 20
    mov al,m2(2)
    m3 5
    db N5
    m4 5
    m5 pfx,sfx
    db pfxsfx
    m6
    purge m6
    m6

    END

