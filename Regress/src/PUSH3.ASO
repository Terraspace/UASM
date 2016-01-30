
;--- PUSH/POP memory operands with invalid sizes

	.386
	.model flat

	.data
vb	db 0
vw	dw 0
vd	dd 0
vq	dq 0

S1 struct
	dw ?
	db ?
S1 ends
S2 struct
	dw ?
	dw ?
S2 ends

vs1 S1 <>
vs2 S2 <>

T1 typedef WORD
T2 typedef DWORD
T3 typedef FWORD

vt1 T1 0
vt2 T2 0
vt3 T3 0

	.code

	push vb	;error
	push vw
	push vd
	push vq	;error
	push vs1;error (Masm v6/7 ok, Masmv8+ error, JWasm error)
	push vs2
	push vt1
	push vt2
	push vt3;error

	pop vb	;error
	pop vw
	pop vd
	pop vq	;error
	pop vs1	;error (Masm v6/7 ok, Masmv8+ error, JWasm error)
	pop vs2
	pop vt1
	pop vt2
	pop vt3	;error

end
