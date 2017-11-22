
;--- arithmetic op with signed op and forward memory reference

_text segment 'CODE'

	assume ds:_data

	cmp digb,255
	cmp digb,-1
	cmp digb,-128

	cmp digw,255
	cmp digw,256
	cmp digw,32768
	cmp digw,65535
	cmp digw,-1
	cmp digw,-128
	cmp digw,word ptr -1

	.386
	cmp digd,255
	cmp digd,256
	cmp digd,7fffffffh
	cmp digd,0ffffffffh
	cmp digd,-1
	cmp digd,-128
	cmp digd,dword ptr -1

_text ends

_data segment 'DATA'
digb label byte
digw label word
digd label dword
_data ends

	End
