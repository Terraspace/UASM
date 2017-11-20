
;--- test symbolic numeric constants
;--- Masm constants range from -4294967295 to 4294967295

	.model small

	.data

	a1 equ -4294967295
	a2 equ a1 + 1
	a3 equ -2147483649
	a4 equ -2
	a5 equ a4 + 1
	a6 equ a5 + 1
	a7 equ a6 + 7fffffffh
	a8 equ a7 + 1
	a9 equ a8 + 1
	a10 equ 4294967295
	a11 equ a10 - 1
;	a12 equ -4294967296


	db @CatStr(!", %(a1), !")
	db @CatStr(!", %(a2), !")
	db @CatStr(!", %(a3), !")
	db @CatStr(!", %(a4), !")
	db @CatStr(!", %(a5), !")
	db @CatStr(!", %(a6), !")
	db @CatStr(!", %(a7), !")
	db @CatStr(!", %(a8), !")
	db @CatStr(!", %(a9), !")
	db @CatStr(!", %(a10), !")
	db @CatStr(!", %(a11), !")
;	db @CatStr(!", %(a12), !")

;	a = -4294967296
;	db @CatStr(!", %(a), !")
	a = -4294967295
	db @CatStr(!", %(a), !")
	a = a + 1
	db @CatStr(!", %(a), !")
	a = -2147483649
	db @CatStr(!", %(a), !")
	a = -2
	db @CatStr(!", %(a), !")
	a = a + 1
	db @CatStr(!", %(a), !")
	a = a + 1
	db @CatStr(!", %(a), !")
	a = a + 7fffffffh
	db @CatStr(!", %(a), !")
	a = a + 1
	db @CatStr(!", %(a), !")
	a = a + 1
	db @CatStr(!", %(a), !")
	a = 4294967295
	db @CatStr(!", %(a), !")
	a = a - 1
	db @CatStr(!", %(a), !")

end
