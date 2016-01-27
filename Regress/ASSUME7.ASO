
;--- type assumes
;--- for v2.08, this was part of assume4.aso. It has been
;--- split because some errors occur now in pass 2 only.

	.386
	.model flat, stdcall

S1 struct
f1	dd ?
S1 ends

	.code

;--- assume an undefined struct
	assume ecx:ptr SUNDEF
	mov eax,[ecx].f1		;Masm error, JWasm error (p2)
	mov eax,[ecx].S1.f1		;Masm ok, JWasm ok

;--- assume a not yet defined struct
	assume ecx:ptr SFWD
	mov eax,[ecx].f1		;Masm ok, JWasm8 ok, JWasm7 error
	mov eax,[ecx].S1.f1		;Masm ok, JWasm8 error (p2), JWasm7 ok 

SFWD struct
f1	dd ?
SFWD ends

	end
