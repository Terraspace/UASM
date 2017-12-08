
;--- if an assembly time
;--- variable was used to create data with fixup,
;--- the fixup info was lost in OMF/MZ format
;--- if the variable's value was changed to a number
;--- afterwards.
;--- in OMF, v2.04-v2.07: error "no segment information to create fixup"
;--- in MZ, v2.07: wrong fixup data

	.model small
	.stack 200
	.code

start:
	mov ah,4ch
	int 21h
sos:

Link = sos
	DD Link		;create data with FAR16 fixup 
Link = 0		;change assembly-time variable to number

end start
