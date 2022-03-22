.x64p

dSeg STRUCT
someVar dd 0
dSeg ENDS

segment1 SEGMENT BYTE USE64
    ASSUME ds:FLAT, es:FLAT
    ORG 0

	;...code...code...
	xor eax,eax
	
    mov rbx, OFFSET myProc    ;The offending line, the wrong value is returned
	lea rbx,myProc
    add rdx, rbx    ;rdx contains the base address for segment2
    call rdx
	
	;...code...code...
	xor eax,eax
	
segment1 ENDS

segment2 SEGMENT BYTE USE64
    ASSUME ds:FLAT, es:FLAT
    ORG 0
data dSeg <> ;dSeg is an uninitialised struc, a static data area within segment2
    ORG $

	;...code...code...
	nop
	
myProc PROC
	ret
myProc ENDP
segment2 ENDS