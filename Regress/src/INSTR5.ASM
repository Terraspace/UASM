
;--- INSTR
;--- empty search string, space as search string

	.386
	.model flat
	option casemap:none

	.data

;--- 1. empty searchstring

n1	InStr 1,<ab!cd>,<>
;x	textequ %n1
;%echo x
	db n1

x	textequ %@InStr( 1,<ab!cd>,<> )
;%echo x
	db x

;--- 2. a space as searchstring

n1	InStr 1,<ab cd>,< >
;x	textequ %n1
;%echo x
	db n1

x	textequ %@InStr( 1,<ab cd>,< >)
;%echo x
	db x

;--- space not enclosed in <>
x	textequ %@InStr( 1,<ab cd>,! )
;%echo x
	db x

	END
