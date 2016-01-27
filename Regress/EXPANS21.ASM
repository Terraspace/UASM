
;--- numbers followed by text macro identifiers 
;--- and % operator at location 0.

T	textequ <1>
QE1	textequ <2>
TE1	textequ <3>

TW	catstr %1T			;1T is <1>
TX	textequ %1T			;1T is <1>
TY	textequ @CatStr(%1T);but here 1T is 11

MF1 macro x
	exitm %x
	endm

_DATA segment

%	dw 1QE1
%	dw 1TE1		;'T' is also a valid number suffix
%	dw 1T		;this is 11 with expansion op!
	dw TW,TX,TY
%	dw MF1(5T)  ;5T is 5
	dw MF1(%5T) ;5T is 51
	dw MF1(%1TE1) ;1TE1 is 13

_DATA ends

	END
