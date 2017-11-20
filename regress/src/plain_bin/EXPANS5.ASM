
;--- see also MACRO56.ASM

	.386
	.model flat, stdcall
	.code

EFUNC proc a1:dword, a2:dword, a3:dword
	ret
EFUNC endp

PARMS textequ <,eax,ebx>

;--- The equates are ok, no difference

TE1  textequ @CatStr(<invoke EFUNC,>,<2>,PARMS)
TE2  textequ @CatStr(<invoke EFUNC,>,<2>,<PARMS>)
TE3  textequ @CatStr(<invoke EFUNC,>,<2>,%PARMS)
TE4  textequ @CatStr(<invoke EFUNC,>,<2>,<%PARMS>)

TE11 CATSTR  @CatStr(<invoke EFUNC,>,<2>,PARMS)
TE12 CATSTR  @CatStr(<invoke EFUNC,>,<2>,<PARMS>)
TE13 CATSTR  @CatStr(<invoke EFUNC,>,<2>,%PARMS)
TE14 CATSTR  @CatStr(<invoke EFUNC,>,<2>,<%PARMS>)

;--- @CatStr works differently if used stand-alone?

	@CatStr(<invoke EFUNC,>,<2>,PARMS)	;won't work with JWasm < v2.05
	@CatStr(<invoke EFUNC,>,<2>,<PARMS>);won't work with JWasm < v2.05
	@CatStr(<invoke EFUNC,>,<2>,%PARMS)
	@CatStr(<invoke EFUNC,>,<2>,<%PARMS>)

FIRST textequ <invoke EFUNC, >

;	@CatStr(FIRST,   <2, eax, ebx>)	;doesn't work with Masm+JWasm
;	@CatStr(<FIRST>, <2, eax, ebx>)	;doesn't work with Masm+JWasm
	@CatStr(%FIRST,  <2, eax, ebx>)
	@CatStr(<%FIRST>,<2, eax, ebx>)

;--- with @SubStr, there's no difference between Masm and JWasm

CMD textequ <_nop>

TE21 CATSTR  @SubStr( CMD,  2)
TE22 CATSTR  @SubStr(<CMD>, 2)
TE23 CATSTR  @SubStr(%CMD,  2)
TE24 CATSTR  @SubStr(<%CMD>,2)

;	@SubStr(CMD,   2)	;doesn't work with Masm+JWasm!
;	@SubStr(<CMD>, 2)	;doesn't work with Masm+JWasm!
	@SubStr(%CMD,  2)
	@SubStr(<%CMD>,2)

end
