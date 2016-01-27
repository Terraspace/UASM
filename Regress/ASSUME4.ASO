
;--- type assumes
;--- a part of this file is now assume7.aso

	.386
	.model flat, stdcall

S1 struct
f1	dd ?
S1 ends

SDEF struct
f1	dd ?
SDEF ends

	.code

;--- assume a defined struct
	assume ecx:ptr SDEF
	mov eax,[ecx].f1		;Masm ok, JWasm ok
	mov eax,[ecx].S1.f1		;Masm error, JWasm error (p1)

if 0
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

endif

	end
