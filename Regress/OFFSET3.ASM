
;--- test: are segment offsets used for segments in groups
;--- if OPTION OFFSET:SEGMENT is set?

	option m510

cgroup  group   _work,_data,_base,_code

_work   segment
wstop   db      "0123456789"
_work   ends

_data   segment
dstop   db      "0123456789"
_data   ends

_base   segment
bstop   db      "0123456789"
_base   ends

_code segment

	assume ds:cgroup
	mov cx,offset ds:wstop
	mov cx,offset ds:dstop
	mov cx,offset ds:bstop

; Masm 5.1 cannot assemble next line
;	dw offset ds:wstop, offset ds:dstop, offset ds:bstop

;--- if DS isn't assumed, JWasm behaves truely
;--- like Masm 5.1 here. Unlike Masm v6!

	assume ds:nothing
	mov cx,offset ds:wstop
	mov cx,offset ds:dstop
	mov cx,offset ds:bstop

; Masm 5.1 cannot assemble next line
;	dw offset ds:wstop, offset ds:dstop, offset ds:bstop

_code ends

	End
