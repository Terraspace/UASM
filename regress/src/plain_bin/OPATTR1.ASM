
;--- OPATTR test

	.dosseg
	.286
	.model small
	.386

E1	equ 1
E2	equ 1
TE1	equ <abc>
TE2	equ <E2>

externdef stdcall ExitProcess:proc

	.data

label2 label byte
var1 db 0
externdef var2:byte
var5 SBYTE 0

	.code

main proc c

local var3:dword

label1:
var4	db 0

	.data

	dw OPATTR var1          ;internal var
;	dw OPATTR var2          ;external var
	dw OPATTR var3          ;local var
	dw OPATTR label1        ;code label
	dw OPATTR var4			;data label in code seg
	dw OPATTR var5			;signed internal var
	dw OPATTR label2
	dw OPATTR undefined_var ;undefined var
	dw OPATTR main          ;PROC c
;	dw OPATTR ExitProcess   ;external PROC stdcall
	dw OPATTR E1            ;constant
	dw OPATTR ecx           ;register
	dw OPATTR [ecx]         ;indirect memory
	dw OPATTR 1             ;number
	dw OPATTR TE1           ;text macro
	dw OPATTR TE2           ;text macro
	dw OPATTR <abc>         ;literal
	dw OPATTR               ;void
	dw OPATTR 1 eq 2        ;logical expression
	dw OPATTR (dword ptr [esp+16])
	dw OPATTR (offset var1)
	dw OPATTR ()
	dw OPATTR []

	.code

main endp

	END
