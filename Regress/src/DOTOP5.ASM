
;--- the member part in a "dot"-expression may be enclosed in ()
;--- note: still won't work in v2.10

	.386
	.model flat

S1 STRUC
	DD ?
f1	DD ?
S1 ENDS

S2 STRUC
	DW ?
f2	DD ?
S2 ENDS

	.code

	MOV [ebp].S1.f1,ESI
	MOV [ebp](S1.f1),ESI
	MOV [ebp][S1.f1],ESI
	MOV [ebp].S1.(f1),ESI       ;jwasm 2.09: structure field expected
	MOV [ebp].S1.((f1)),ESI     ;jwasm 2.09: structure field expected

	assume ebp:ptr S1
	MOV [ebp].f1,ESI
	MOV [ebp].(f1),ESI          ;jwasm 2.09: structure field expected

	MOV [ebp].S1.f1,ESI
	MOV [ebp](S1.f1),ESI        ;jwasm 2.09: operands must be same size
	MOV [ebp][S1.f1],ESI        ;jwasm 2.09: operands must be same size
	MOV [ebp].S1.(f1),ESI       ;jwasm 2.09: structure field expected

	assume ebp:ptr S1
	MOV [ebp](S2.f2),ESI        ;jwasm: symbol not defined: S1.S2
	MOV [ebp][S2.f2],ESI        ;jwasm 2.09: operands must be same size

	assume ebp:nothing

END
