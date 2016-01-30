
;--- test TYPE operator
;--- added in v2.03

    .386
    .model flat
    option casemap:none

TrueType MACRO arg
	if (type (arg) eq BYTE)
		exitm <1>
	endif
	if (type (arg) eq DWORD)
		exitm <2>
	endif
	if (type (arg) eq SDWORD)
		exitm <3>
	endif
	if (type (arg) eq REAL4)
		exitm <4>
	endif
	ENDM

FLOAT typedef REAL4

    .data

b1	db 0
b2	db "abc"
d1	dd 0
sd1	SDWORD 0
f1	real4 1.0
f2	FLOAT 2.0

	db TrueType( b1  )
	db TrueType( b2  )
	db TrueType( d1  )
	db TrueType( sd1 )
	db TrueType( f1  )
	db TrueType( f2  )
	db TrueType( al  )
	db TrueType( eax )

    end

