
;--- INSTR directive and @InStr function.
;--- no error expected

	.386
	.model flat

	.data

E1	INSTR <Hello world>,<world>
	db E1

E2	INSTR <Hello world>,<worldx>
	db E2

E11 equ @INSTR(1,<CString.Function1>,<.>)
	db E11

E12	equ @INSTR(1,<#!"&/()=!<!>>,<!>>)
	db E12

IFE @INSTR(1,<CString.Function1>,<.>) eq 0
	db -1
ENDIF

	END
