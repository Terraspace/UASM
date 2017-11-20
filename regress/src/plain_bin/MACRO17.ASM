
;--- VARARG macro functions
;--- missing VARARG argument

	.286
	.model small

	.data

MF1 macro arg1, argv:vararg
	for x,<argv>
	echo argument: x
	endm
	exitm <arg1>
	endm

	db MF1(1)

end

