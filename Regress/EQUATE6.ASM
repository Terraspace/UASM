
;--- test equates which are labels (=aliases)!

	.386
	.model flat

;--- same label

E1	EQU offset label1
E1	EQU offset label1

;--- different labels, same offsets

E2	EQU offset label1
E2	EQU offset label2

;--- different labels, different offsets

E3	EQU offset label2
E3	EQU offset label3	;ok, because it's a text macro

	.code
label1:
label2:
	mov al, 1
label3:
    RET

;--- same variations, but this time AFTER the labels are defined
;--- same label

X1	EQU offset label1
X1	EQU offset label1	;ok, because it's a text macro

;--- different labels, same offsets

X2	EQU offset label1
X2	EQU offset label2	;ok, because it's a text macro

;--- different labels, different offsets

X3	EQU offset label2
X3	EQU offset label3	;ok, because it's a text macro

	db @CatStr(!", %E1, !")
	db @CatStr(!", %E3, !")
	db @CatStr(!", %X1, !")
	db @CatStr(!", %X3, !")

END
