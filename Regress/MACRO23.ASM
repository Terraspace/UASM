
;--- macro labels

	.286
	.model small

m1 macro x,y
%	db "&x,&y"
	endm

	.code

	m1 1,!
	m1 1,! 
	m1 !,,! 

end
