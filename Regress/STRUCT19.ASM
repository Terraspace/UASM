
;--- DUP with initialized structures
;--- + macro in initializer

;--- there is (or better: was) a difference between Masm and JWasm.
;--- in Masm, macro TM1() is called ONCE,
;--- in JWasm prior to v2.09, macro TM1() is called 300 times!
;--- hence the output differs significantly:
;--- - Masm: 300 * 06
;--- - JWasm 2.08 and below: 06,07,08,...,305
;--- JWasm 2.09 behaves like Masm

	.386
	.MODEL FLAT, stdcall
	option casemap:none

S1 struct
	db ?
S1 ends

TM1 macro
	E1=E1+1
	exitm <E1>
	endm

	.data

E1 = 0
	S1 300 dup (<LOW (TM1()+002+003)>)

	end
