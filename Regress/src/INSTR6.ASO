
;--- INSTR errors

n1	InStr 2,<a>,<a>	;index too high
n1	InStr 2,<!!>,<!!>
n1	InStr <ab>,<abc>
n1	InStr 0,<ab>,<a>	;index 0, ignored (set to 1 internally)
n1	InStr -1,<ab>,<a>	;index negative
n1	InStr <>,<a>		;empty string (masm: constant value too large)

	END
