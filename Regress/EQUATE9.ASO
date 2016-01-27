
;--- test EQU redefinitions

    .386
    .model flat

	.data
vbl label byte
vwl label word
vb	db 0

	.code

vbc	db 0
l1:
l2:

E1	equ a	;is text equate
E1	equ 1	;remains a text equate!

E2	equ 1	;is number
E2	equ <1> ;symbol redefinition

E3	equ l1	;is alias
E3	equ <1> ;symbol redefinition

E4	equ l2-l1	;is number
E4	equ 0		;ok since value wont change

E5	equ vb
E5	equ vbc		;symbol redefinition (offset is equal, but segment changed)

E6	equ vb
E6	equ vbl		;ok (both offset + segment equal)

E7	equ vb
E7	equ vwl		;ok (both offset + segment equal, type different)

E8	equ l1	;is alias (code)
E8	equ 1	;ok ( alias -> number is ok if value won't change )

E9	equ vb	;is alias (data)
E9	equ 0	;ok ( alias -> number is ok if value won't change )

E10	equ 1	;is number
E10	equ l1  ;symbol redefinition ( number -> alias is always rejected )

E11	equ -0FFFFFFFFh
E11	equ 0FFFFFFFFh ;symbol redefinition (sign changed)

E12	equ 123456789h
E12	equ 223456789h	;ok, since symbol is stored as text equate

    END
