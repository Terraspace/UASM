
;--- prior to v2.04, there was a problem in Result2, because
;--- JWasm swallowed the blank between ??Sentence and TE1
;--- "trailing" blanks as behind ??Sentence in Result3 were no problem

	 .386
	 .model flat

	.data

TE1	textequ <1>
??Sentence textequ <szProp dw TE1>

Result1	textequ @CatStr(%??Sentence, <,>, TE1 )
Result2	textequ @CatStr(%??Sentence TE1, <TE1>)
Result3	textequ @CatStr(%??Sentence  , <TE1>)

	Result1
	db @CatStr(!",%Result2,!")
	db @CatStr(!",%Result3,!")

	END
