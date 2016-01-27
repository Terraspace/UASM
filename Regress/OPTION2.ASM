
;--- test OPTION directive

	.286
	.model small

	option nokeyword:<short>,dotname,proc:private
	option mz: ::1:1	;syntax since v2.06

.text segment
.text ends

	.code
start:
	mov ah,4Ch
	int 21h

	END start
