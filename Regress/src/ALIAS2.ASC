
;--- ALIAS segment attribute changes

	.386
	.model flat

W	segment ALIAS("abc")
W	ends
W	segment ALIAS("abc")
W	ends

X	segment ALIAS("abc")
X	ends
X	segment ALIAS("def")	;should be an error
X	ends

Y	segment ALIAS("abc")
Y	ends
Y	segment
Y	ends

Z	segment
Z	ends
Z	segment ALIAS("abc")	;should be an error
Z	ends

	End
