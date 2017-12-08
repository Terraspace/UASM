
;--- test 16-bit FP fixups

	.model small,c
	.8087
	.dosseg
	.stack 200h

	option emulator

	includelib <fpfixup.lib>

	.data

fl1 real4 1.0
fl2 real4 2.0

	.code

	fwait		;fwait, cpu=8086 (additional NOP)
	nop			;all NOPs added just for better disassembly
	fnop		;not emulated, but fixup generated
	nop
	fld fl1
	nop
	fadd fl2
	nop
	fadd cs:fl2	;prefix causes creation of additional secondary fixup
	nop
	fnclex		;no wait, no fixup generated
	nop
	fclex		;with wait, fixup generated
	nop
	.286
	fsetpm		;the only instruction for 287 without AP prefix
	nop
	.386
	fwait		;fwait, cpu=80386 (no additional NOP prior to JWasm v2.04)
start:
	mov ah,4Ch
	int 21h

;--- no fixups generated for 32-bit segments

	.386

_TEXT32 segment use32 public 'CODE'
	fwait
	nop
	fnop
	nop
	fld fl1
_TEXT32 ends

	end start
