
;--- test backslash
;--- no error expected

	.386
	.model flat

OFN_EXPLORER     equ 1
OFN_HIDEREADONLY equ 2
OFN_ENABLEHOOK   equ 4
OFN_PATHMUSTEXIST equ 8
OFN_ENABLESIZING equ 16

	.code

    db 1,2,3,  \  
    4,5,6,7,8

N1	equ 1
N2	equ 2

E1	textequ <abc\
	def>

E2	equ abc \
	def()

E3	equ N1 or\
	N2

E4	equ N1 or \
	N2

	db @CatStr(!",%E1,!")
	db @CatStr(!",%E2,!")
	db @CatStr(!",%E3,!")
	db @CatStr(!",%E4,!")

;--- this works with JWasm, but not with Masm.
;--- Masm does NOT insert a blank in this case.
E5	equ OFN_EXPLORER or OFN_HIDEREADONLY\
	or OFN_ENABLEHOOK or OFN_PATHMUSTEXIST or OFN_ENABLESIZING

	db E5

;--- this works for both JWasm and Masm. A white space is inserted.
	db OFN_EXPLORER or OFN_HIDEREADONLY\
	or OFN_ENABLEHOOK or OFN_PATHMUSTEXIST or OFN_ENABLESIZING

	END
