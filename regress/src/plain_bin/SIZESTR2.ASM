
;--- INSTR
;--- empty search string, space as search string

	.386
	.model flat
	option casemap:none

	.data

n1	SizeStr <ab!cd>
x	textequ %n1
;%echo x
	db n1

n1	SizeStr <>
x	textequ %n1
;%echo x
	db n1

x	textequ %@SizeStr( <ab!cd> )
;%echo x

x	textequ %@SizeStr( <> )
;%echo x
	db x

;--- space not enclosed in <>
x	textequ %@SizeStr( ab!cd )
;%echo x
	db x

x	textequ %@SizeStr( ab cd! )
;%echo x
	db x

x	textequ %@SizeStr( ! )
;%echo x
	db x

x	textequ %@SizeStr(  )
;%echo x
	db x

	END
