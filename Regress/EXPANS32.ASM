
;--- more expansion

	.model small

	.data

M1	macro p3:vararg
	for x,<p3>
;	echo x
ifb <x>
	db "_"
else
%	db "&x"
endif
	endm
	endm

	M1 1,2,< >
	M1 1, ,3
	M1  ,2,3

END
