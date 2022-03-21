.x64
.model flat

something STRUCT
	myproc dq ?
something ENDS

.code

myproc proto

mov [(type something.myproc) ptr [rax]], rax

a db 0

myproc PROC
  RET
myproc ENDP

end