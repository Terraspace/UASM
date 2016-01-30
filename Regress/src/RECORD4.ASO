
;--- test records
;--- the default value of record types is the record's mask!
;--- ( this didn't work with Masm v6, needs Masm v8+ )

	.386
	.model flat

R1	RECORD			;syntax error - record without bits
R2	RECORD	bf2:0	;0 bits for bitfield not allowed
R3	RECORD	bf3:65	;too many bits
R4	RECORD	bf4:1=	;missing initial value
R5	RECORD	bf5:4=123	;initial value too high (no error here)

	.DATA

v1	R5 <>	;initializer magnitude too large

	END
