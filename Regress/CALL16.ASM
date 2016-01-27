
;--- for indirect calls/jmps, a displacement in form of a mbr
;--- didn't set the type of the call/jmp in v1.94-2.02

	.286
	.model tiny

cmOPTION struc
  optchar	db ?
  optmask	dw 0
  optproc@	dw ?
cmOPTION ends

.code

	call [bx + cmOPTION.optproc@]
	call [bx + offset cmOPTION.optproc@]

end
