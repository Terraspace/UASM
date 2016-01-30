
;--- no near type coercion for Jcc if cpu is < 80386
;--- jwasm  < v2.11: jump out of range by -4 byte(s)
;--- jwasm >= v2.11: jump distance not possible ...

_TEXT segment 'CODE'
	jz near ptr lbl1
lbl1:
_TEXT ends

end
