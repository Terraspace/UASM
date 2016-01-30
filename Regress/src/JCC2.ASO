
;--- no near/far type coercion for JxxZ or LOOPx 
;--- jwasm  < v2.11: jump out of range by n byte(s)
;--- jwasm >= v2.11: Only SHORT jump distance is allowed

	.286
	.model small

	.code
start:
	jcxz near ptr start
	loop near ptr start

end start
