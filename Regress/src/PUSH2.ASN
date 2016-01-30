
;--- test PUSH with segment + group addresses

	.286
	.model small

	.stack
	.data

	db -1

	.code

start:
	push DGROUP
	push _TEXT
	push _DATA
	mov ah,4Ch
	int 21h
	db 10 dup (55h)

    END start
