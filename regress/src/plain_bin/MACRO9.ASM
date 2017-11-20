
;--- no error
;--- there was a problem with the usage of an uninitialized variable
;--- with the .TYPE and OPATTR operator, and this sample
;--- revealed it. Fixed in v2.05

@error macro
	call error
	endm

@strout macro xx,yy
if ( (.TYPE xx) and 0018h )
??TYPE = 1
endif
    endm

_TEXT segment 'CODE'

error:
	ret

	@error

	@strout

_TEXT ends

	END

