
;--- ALIGN and characteristics segment attributes must not change

	.486
	.model flat, stdcall
	option casemap:none

	.code

_DATA1 segment ALIGN(4)
	db 1
_DATA1 ends 
_DATA1 segment ALIGN(8)
	db 1
_DATA1 ends 

_DATA2 segment read
	db 1
_DATA2 ends 
_DATA2 segment read write
	db 1
_DATA2 ends 

_DATA3 segment read write
	db 1
_DATA3 ends 
_DATA3 segment read  ;this was accepted before v2.09
	db 1
_DATA3 ends 

_DATA4 segment
	db 1
_DATA4 ends 
_DATA4 segment read
	db 1
_DATA4 ends 

_DATA5 segment read write
	db 1
_DATA5 ends 
_DATA5 segment
	db 1
_DATA5 ends 

	end
