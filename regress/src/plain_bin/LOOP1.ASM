
;--- test assembly-time loop directives

	.386
    .model flat, stdcall

TE1	textequ <literal1>
TE2	textequ <1+2>

	.data

	FORC chr, <ab%cdefg>
    ifidn <chr>,<f>
       exitm
	endif
    ifidn <chr>,<%>
	db "%"
	else
	db @CatStr(!",chr,!")
	endif
	ENDM

	FOR item, <abc,def,1+2,TE1,1+2*2,3+TE2,TE1>
	db @CatStr(!",item,!")
	ENDM

%	FOR item, <abc,def,1+2,TE1,1+2*2,3+TE2,TE1>
	db @CatStr(!",item,!")
	ENDM

	FOR item, <abc,def,%1+2,%TE1,1+%2*2,%3+TE2,TE1>
	db @CatStr(!",item,!")
	ENDM

	E1 = 0
	WHILE TE2 GT E1
	db E1
	E1 = E1+1
	ENDM

    END

