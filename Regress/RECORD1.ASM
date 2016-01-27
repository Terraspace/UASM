
;--- test records
;--- - the infamous "padding byte for RECORD" error in v2.00-2.02

	.286

RECORD1 record	RF1:2,RF2:1,RF3:1,RF4:3,RF5:1,RF6:2,RF7:2,RF8:1,RF9:1,RF10:1,RF11:1
;--- test duplicate definition
RECORD1 record	RF1:2,RF2:1,RF3:1,RF4:3,RF5:1,RF6:2,RF7:2,RF8:1,RF9:1,RF10:1,RF11:1

BIOS segment page at 0

IVT	dd 256 dup(?)

comports	dw ?,?,?,?	; 400: 4 serial port bases
lptports	dw ?,?,?	; 408: 3 parallel port bases
XBDAsegm	dw ?		; 40E: segment of eXtended BIOS data area
equipmnt	RECORD1 <>	; 410: equipment list
	db ?
basemem_K	dw ?		; 413: base memory size in Kb

	org 04F0h
IAC		db 16 dup(?)	; Communication Area
BIOS ends

	.model tiny

	.code
	mov ax, offset equipmnt

	ret

	end
