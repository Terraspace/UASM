
;--- trigger "nesting level too deep" error

	.386
	.MODEL small

m1 macro arg
;	echo arg
	m1 <arg,x>
	endm
	m1 0
	end
