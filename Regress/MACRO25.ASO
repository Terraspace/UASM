
;--- warning too many arguments in macro call

	.386
	.model flat

m1 macro x
	db x
endm

m2 macro x
	exitm <x+1>
endm

	.data

	m1 1,2,3
	db m2(1,2,3)
	db m2(1,2,3), m2(1,2)

end
