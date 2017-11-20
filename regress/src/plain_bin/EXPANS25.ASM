
	.386
	.model flat

TestMac MACRO arg
;echo >arg<
%	db "&arg"
ENDM

.code
TestMac abc|def  ; oops, there are tabs before the comment!
;exit

end

