
;--- some string macro usages ( found in ObjAsm32 )

	.model small

	.data

FloatName textequ <ABC>
Params1 textequ <>
Params2 catstr <pSheet>, <!,>, Params1
Params3 catstr <offset label1 + 4>, <!,>, Params2
Params4 catstr <FloatName>, <!,>, Params3
Params5 substr Params4, 1, @SizeStr(%Params4) - 1  

;%echo Params2
;%echo Params3
;%echo Params4
;%echo Params5
	db @CatStr(!",%Params5,!")

PDef textequ <dw >
S1  textequ <X>
S2  textequ <Y>
S3  textequ <Z>
Params1 textequ @catstr(PDef, < S1 >, <S2 >, <S3 > )
Params2 textequ @catstr(Params1, < S1 >, <S2 >, <S3 > )
Params3 textequ @CatStr(%Params2, <#>)
;%echo Params1.
;%echo Params2.
;%echo Params3.
	db @CatStr(!",%Params3,!")

IEnumConnectionPoints_Inherit textequ <IUnknown>
ObjName textequ <IEnumConnectionPoints>
Params1 textequ @CatStr(<externdef TPL_>, %@CatStr(%ObjName, <_Inherit>), <:>, %ObjName, <_Struc>)
;%echo Params1
	db @CatStr(!",%Params1,!")

Primer_Inherit textequ <>
ObjName textequ <Primer>
Params1 textequ @CatStr(<externdef TPL_>, %@CatStr(%ObjName, <_Inherit>), <:>, %ObjName, <_Struc>)
;%echo Params1
	db @CatStr(!",%Params1,!")

Result_equate textequ <the_final_value>
Result_a textequ <Result_>
Result_b textequ <equate>
Res1 textequ Result_equate
Res2 textequ Result_a, Result_b     ;Res2=Result_equate
Res3 textequ Res2                   ;Res3=the_final_value
	db @CatStr(!",%Res3,!")


SrcLine textequ <dw >
Quote   textequ <!">
QChar CatStr Quote, <C>, Quote                    ;"C"
Sentence textequ @CatStr(%SrcLine, <QChar>, <,>)  ;dw QChar,
SrcLine textequ Sentence                          ;dw "C",
QChar CatStr Quote, <D>, Quote                    ;"D"
Sentence textequ @CatStr(%SrcLine, <QChar>, <,>)  ;dw "C",QChar,
SrcLine textequ Sentence                          ;dw "C","D",
QChar CatStr Quote, <E>, Quote                    ;"E"
Sentence textequ @CatStr(%SrcLine, <QChar>, <,>)  ;dw "C","D",QChar,
SrcLine textequ Sentence                          ;dw "C","D","E",
;%echo SrcLine
	@CatStr(%SrcLine)

END
