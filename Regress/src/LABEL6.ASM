
;--- define a data label twice, with LABEL and data directive
;--- then check that sizeof and lengthof are ok
;--- there was a problem in v2.07-v2.08a

	.386
	.model flat,c

	.code

xxx label byte
E1	= sizeof xxx
E2	= lengthof xxx
xxx db 1,2
	dw E1, sizeof xxx	;must be 2,2
	dw E2, lengthof xxx	;must be 2,2

	end
