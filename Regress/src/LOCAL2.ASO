
;--- symbol name l1 is referenced in proc1, but the symbol isn't defined.
;--- error msg should be "undefined symbol" ( at line "mov ax,l1" ).
;--- However, if the very same symbol name was used later in a LOCAL directive,
;--- jwasm did emit "symbol already defined" ( al line "local l1:word" in proc2 ).
;--- Reason: the first missing local did define a "not yet defined" forward ref symbol.
;--- fixed in v2.10 ( see also: proc5.aso ).

	.286
	.model small, c

	.code

proc1 proc p1:word
;local l1:word
	mov ax,l1
	ret
proc1 endp

proc2 proc p1:word
local l1:word
local l2:word
	ret
proc2 endp


end

