
;--- MACRO VARARG parameter test
;--- no error expected

	.286
	.MODEL small, stdcall

m1	macro p1:req,p2:vararg
	mov ax,p1
	for arg:vararg,<p2>
		db @CatStr(!",arg,!"),0
	endm
	for arg:vararg,<1 , 2 >
		db @CatStr(!",arg,!"),0
	endm
	endm

	.CODE

	m1 1,2 ,3

	END
