
;--- test records
;--- the default value of record types is the record's mask!
;--- ( this didn't work with Masm v6, needs Masm v8+ )

	.386
	.model flat

R1	RECORD	f1:4,f2:16,f3:8

	.DATA

v1	R1 <>

	.CODE

	mov  eax, R1		;must return the MASK value!
	mov  eax, mask R1
	mov  eax, sizeof R1
	mov  eax, type R1
;--- won't work currently with JWasm
;	mov  eax, R1 <1,2,3>
;	mov  v1, R1 <1,2,3>
	mov  eax, sizeof v1
	mov  eax, type v1

	END
