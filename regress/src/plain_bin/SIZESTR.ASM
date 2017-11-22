
TE1 textequ <abcde>
TE2 textequ <fghij>

E1	sizestr <abc>	;3
E2	sizestr <%TE1>	;4 - % within angle brackets has no meaning
E3	sizestr TE1		;5
%E4	sizestr <TE1>	;5
%E5	sizestr <TE1 >	;6
%E6	sizestr < TE1 >	;7

;%E7 sizestr TE1		;error, abcde isn't a text equate identifier

;--- this is accepted by Masm, but
;--- the second item is silently skipped.
;E8	sizestr TE1 TE2

E9   sizestr <TE1 TE2>	;7
E10  sizestr <%TE1 TE2>	;8
%E11 sizestr <TE1 TE2>	;11

_DATA segment
	db E1,E2,E3,E4,E5,E6
	db E9,E10,E11
_DATA ends

	end
