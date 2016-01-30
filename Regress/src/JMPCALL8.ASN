
;--- jmp segment overrides

	.286
	.dosseg

STACK segment stack 'STACK'
	db 400h dup (?)
STACK ends

CGROUP group _TEXT1, _TEXT2

_TEXTX segment 'CODE'
labelx:
	retf
_TEXTX ends

_TEXT1 segment 'CODE'

start:
	jmp _TEXT2:label2	;far jmp
	jmp CGROUP:label2	;near jmp
	jmp label2			;near jmp
	call _TEXT2:label2	;far call
	call CGROUP:label2	;optimized far call
	call label2			;near call
label1:
;	call labelx         ;rejected
	call _TEXTX:labelx
;	call CGROUP:labelx	;rejected
	mov ah,4ch
	int 21h
_TEXT1 ends

_TEXT2 segment 'CODE'
label2:
	jmp _TEXT1:label1	;far jmp
	jmp CGROUP:label1	;near jmp
	jmp label1			;near jmp
	call _TEXT1:label1	;far call
	call CGROUP:label1	;optimized far call
	call label1 		;near call
_TEXT2 ends

	end start
