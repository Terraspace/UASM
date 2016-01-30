
;--- forward references of FAR procs
;--- which also have associated PROTOs.
;--- handling of "far call optimization"

;--- jwasm v2.01 had a problem because the internal
;--- handling of PROTOs was changed in this version.

;--- if the .EXP file is created with a linker, the NOFARcall
;--- option must be set, because JWasm's -mz option also won't
;--- apply it.

	.286
	.model small, stdcall
	.386

	.stack

p1 proto far
p2 proto far
p3 proto far
externdef p4:far

	includelib <p3.lib>

	.code

p1 proc far   ;procedure defined BEFORE it's used
	ret
p1 endp

start:
	jmp @F
	call p1
	db 123 dup (0)
@@:
	jmp @F
	call p2
	db 123 dup (0)
@@:
	jmp @F
	call p3   ;true EXTERN procedure 
	db 123 dup (0)
@@:
	jmp @F
	call p4
	db 123 dup (0)
@@:
	mov ah,4Ch
	int 21h

p2 proc far   ;procedure with PROTO defined AFTER it's used
	ret
p2 endp

p4 proc far   ;procedure with EXTERNDEF defined AFTER it's used
	ret
p4 endp

	end start
