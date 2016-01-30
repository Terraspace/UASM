
;--- 64-bit call and jumps
;--- there are some problems:
;--- - Masm (ML64) doesn't encode the 16-bit far calls/jumps correctly
;--- - Masm (ML64) doesn't accept the 64-bit far calls/jumps correctly

ifdef __JWASM__
	.x64
	.model flat
endif

	.data

PF16 typedef ptr far16

v16n    dw 0   ;16-bit indirect near branch (not allowed)
v16f    PF16 0 ;16-bit indirect far branch
v32n    dd 0   ;32-bit indirect near branch (not allowed)
v32f    df 0   ;32-bit indirect far branch
v64n    dq 0   ;64-bit indirect near branch
v64f    dt 0   ;64-bit indirect far branch

	.code

;	call v16n	;Masm accepts, but not allowed
	call v16f	;Masm accepts, but encodes wrong
;	call v32n	;not allowed
	call v32f
	call v64n
ifdef __JWASM__
	call v64f	;Masm rejects
endif
	call v16fl
	call v32fl
	call v64nl

;	call ax		;Masm accepts, but not allowed
;	call eax    ;not allowed
	call rax
	call r9

;	jmp v16n	;Masm accepts, but not allowed
	jmp v16f	;Masm accepts, but encodes wrong
;	jmp v32n	;not allowed
	jmp v32f
	jmp v64n
ifdef __JWASM__
	jmp v64f	;Masm rejects
endif
	jmp v16fl
	jmp v32fl
	jmp v64nl

;	jmp ax
;	jmp eax
	jmp rax
	jmp r9

	ret

	.data

v16fl   PF16 0
v32fl   df 0
v64nl   dq 0

    END
