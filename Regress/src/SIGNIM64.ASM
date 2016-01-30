
;--- arithmetic op with signed op and forward memory reference

ifdef __JWASM__
if type near eq 0ff02h
	.x64
	.model flat
endif
endif

	.code

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

	cmp digd,255
	cmp digd,256
	cmp digd,7fffffffh
	cmp digd,0ffffffffh
	cmp digd,-1
	cmp digd,-128
	cmp digd,dword ptr -1

	cmp digq,255
	cmp digq,256
	cmp digq,7fffffffh
	cmp digq,0ffffffffh
	cmp digq,-1
	cmp digq,-128
	cmp digq,dword ptr -1

	.data

digb label byte
digw label word
digd label dword
digq label qword

	End
