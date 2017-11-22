
;--- 16bit invoke test with register arguments
;--- for 8086, 80186|80286 and 80386
;--- no error expected

	.MODEL small, stdcall

	.CODE

prb proc a1:byte, a2:byte
prb endp
prw proc a1:word, a2:word
prw endp
prd proc a1:dword, a2:dword
prd endp
prf proc a1:fword, a2:fword
prf endp

if 1
	.8086

;	invoke prb, al, bl	;JWasm works, Masm: register value overwritten
	invoke prb, cl, bl

;	invoke prw, al, bl	;register value overwritten
	invoke prw, cl, bl
;	invoke prw, ax, bx	;register value overwritten
	invoke prw, cx, bx

;	invoke prd, al, bl	;register value overwritten
	invoke prd, cl, bl
;	invoke prd, ax, bx	;register value overwritten
	invoke prd, cx, bx

	.186

;	invoke prb, al, bl	;JWasm works, Masm: register value overwritten
	invoke prb, cl, bl

;	invoke prw, al, bl	;register value overwritten
	invoke prw, cl, bl
;	invoke prw, ax, bx	;register value overwritten
	invoke prw, cx, bx

;	invoke prd, al, bl	;register value overwritten
	invoke prd, cl, bl
;	invoke prd, ax, bx	;register value overwritten
	invoke prd, cx, bx

	.386

;	invoke prb, al, bl	;JWasm works, Masm: register value overwritten
	invoke prb, cl, bl

;	invoke prw, al, bl	;register value overwritten
	invoke prw, cl, bl
;	invoke prw, ax, bx	;register value overwritten
	invoke prw, cx, bx

;	invoke prd, al, bl	;register value overwritten
	invoke prd, cl, bl
;	invoke prd, ax, bx	;register value overwritten
	invoke prd, cx, bx
	invoke prd, ecx, ebx
endif

	.386

_TEXT32 segment use32 'CODE'
prbx proc a1:byte, a2:byte
prbx endp
prwx proc a1:word, a2:word
prwx endp
prdx proc a1:dword, a2:dword
prdx endp

;	invoke prbx, al, bl	;JWasm works, Masm: register value overwritten
	invoke prbx, cl, bl

;	invoke prwx, al, bl	;register value overwritten
	invoke prwx, cl, bl
;	invoke prwx, ax, bx	;register value overwritten
	invoke prwx, cx, bx

;	invoke prdx, al, bl	;register value overwritten
	invoke prdx, cl, bl
;	invoke prdx, ax, bx	;register value overwritten
	invoke prdx, cx, bx
	invoke prdx, ecx, ebx

_TEXT32 ends

	END


