
;--- conditional assembly directive that
;--- appears AFTER expansion only.
;--- didn't work prior to v2.08

	.model small

	.code

TM1	textequ <if 1>

TM1
;	echo gotcha!
	nop
endif

end
