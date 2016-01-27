
;--- text macro contains EQU and ';'.
;--- consequently, LNAME_TXT is supposed to become a number (=1)
;--- jwasm prior to v2.10 made it a text.

	.386
	.model flat

	.data

DBB	equ <EQU 1;>

LNAME_TXT DBB LENGTHOF LNAME_TXT-1,'Lname'

	db LNAME_TXT

end
