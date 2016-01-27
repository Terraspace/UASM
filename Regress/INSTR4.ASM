
;--- INSTR
;--- source contains !

	.386
	.model flat
	option casemap:none

	.data

x INSTR 1,<a!!!bc>,<!b>
	db x
	db @InStr( 1,<a!!!bc>,<!b> )

x INSTR 1,<a!bc>,<b>
	db x
	db @InStr( 1,<a!bc>,<b> )

	END
