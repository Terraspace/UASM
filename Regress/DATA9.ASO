
;--- data item redefinition

	.386
	.model flat

    .data

extern var1:byte
var1 db 1 ;error 'symbol redefinition'

var2 label byte
var2 db 1 ;no error

var3 db 1
var3 db 1 ;error 'symbol already defined'

externdef var4:byte
var4 db 1 ;no error

externdef var5:byte
var5 dw 1 ;error 'symbol type conflict'


    END
