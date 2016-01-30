
;--- floating-point for cpu < 80286
;--- check FWAIT generation

	.8086
	.model small
	.dosseg
	.stack 200h
	option casemap:none

	.code

start:
	fclex   	;AP_FWAIT set, FWAIT always added
	fmul		;automatic FWAIT added if cpu < 80286
	fnclex		;AP_NO_FWAIT set, NO FWAIT added
	fwait		;nothing added
	.186
	fmul		;automatic FWAIT added if cpu < 80286
	.286
	fclex
	fmul		;nothing added here!
	fnclex
	fwait
	fsetpm		;the only instruction for 287 without AP prefix
	mov ah,4Ch
	int 21h

	End start
