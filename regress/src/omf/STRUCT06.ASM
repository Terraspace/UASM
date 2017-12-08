
;--- another Masm 5.1 structure access test

	.286
	.model small

	OPTION OLDSTRUCTS

	includelib <regext.lib>

	.stack

extern stdDeviceAssignTable:near

STDREDIREC struc
stdDriverName   db '????????'
stdIOHandle     dw ?
stdDevInfo      dw ?
STDREDIREC ends

	.code

start:
	mov ax, ds:[ 1 * sizeof STDREDIREC ]. stdDeviceAssignTable. stdIOHandle
	mov ah, 4Ch
	int 21h

	End start
