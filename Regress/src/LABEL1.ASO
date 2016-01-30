
;--- 1. error: label redefinition of a proto
;--- 2. error: local label redefinition of an externdef

	.286
	.model tiny

bar proto pascal
externdef foo:near

_text segment

bar:
ret

p1 proc

foo:
	ret

p1 endp

_text ends

end
