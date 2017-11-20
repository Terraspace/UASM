
;--- LABEL attribute of macro parameter 1

	.286
	.model small

m1 macro x:label,y
	db 0
x	db y
	endm

	.data

v1	m1 1
v2	m1 2
v3	m1 3
	m1 4

end
