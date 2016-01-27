
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

	mov cx,offset cgroup:wstop
	mov cx,offset cgroup:dstop
	mov cx,offset cgroup:bstop
	mov cx,offset  _work:wstop
	mov cx,offset  _data:dstop
	mov cx,offset  _base:bstop
	mov cx,offset wstop
	mov cx,offset dstop
	mov cx,offset bstop

	dw offset cgroup:wstop, offset cgroup:dstop, offset cgroup:bstop
	dw offset  _work:wstop, offset  _data:dstop, offset  _base:bstop
	dw offset        wstop, offset        dstop, offset        bstop
	dw               wstop,               dstop,               bstop

_code ends

	End
