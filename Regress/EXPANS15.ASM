
;--- SIZESTR expansion

_DATA segment
TE1 textequ <ABC>
TE1	sizestr <x>
	db TE1

TE1 textequ <DEFG>
TE1	sizestr TE1
	db TE1
_DATA ends
        END
