
;--- test + operator with 2 forward references

code segment 'code'
	mov dx,offset buf+bufsize	;sum of 2 forward references
	mov ax,4c00h
	int 21h
buf equ $
bufsize equ 200
code ends
    end
