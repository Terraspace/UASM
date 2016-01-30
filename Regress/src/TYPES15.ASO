
;--- prototype types

	.286
	.MODEL small
	.386

p1 typedef proto near   stdcall :word
p1 typedef proto near   stdcall :word	;should be ok
p1 typedef proto near16 stdcall :word	;should be ok

p1 typedef proto far    stdcall :word	;near/far
p1 typedef proto near32 stdcall :word	;near16/near32
p1 typedef proto near   c       :word	;stdcall/c
p1 typedef proto near   stdcall :dword	;word/dword

END
