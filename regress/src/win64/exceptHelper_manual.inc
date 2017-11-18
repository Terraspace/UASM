
; Part of this macro is a modification of the cfm$ macro from
; www.masm32.com SDK

cfm2$ MACRO pInfo:VARARG
	LOCAL cfmtxt, char, nu$, flag
	nu$ equ <>
	flag = 0
	
	FORC char,<pInfo>                  
		IFIDN <char>,<\>               
			flag = flag + 1
		ENDIF

		IF flag EQ 0
			nu$ CATSTR nu$,<char>
		ENDIF

		IF flag EQ 1
			IFIDN <char>,<n>
				nu$ CATSTR nu$,<",10,"> 
				flag = 0
			ENDIF
			IFIDN <char>,<t>
				nu$ CATSTR nu$,<",9,"> 
				flag = 0
			ENDIF
		ENDIF
	ENDM
	nu$ CATSTR nu$,<,0,0,0> 

	cpos INSTR nu$,<"",>
	IF cpos EQ 1
		nu$ SUBSTR nu$,4
	ENDIF

	cpos INSTR nu$,<"",>

	WHILE cpos
		lbuf SUBSTR nu$,1,cpos-1
		rbuf SUBSTR nu$,cpos+3
		nu$ equ <>            
		nu$ CATSTR lbuf,rbuf
		cpos INSTR nu$,<"",>
	ENDM

	sln SIZESTR nu$
	nu$ SUBSTR nu$,1,sln-6
	.data
		cfmtxt BYTE nu$,10,0
	.code
	EXITM <offset cfmtxt> 	
ENDM	

printItA MACRO pInfo:REQ, arg1, arg2, arg3
	mov rcx, cfm2$(pInfo)

	IFNB <arg1>
		mov rdx, QWORD PTR arg1
	ENDIF
	IFNB <arg2>
		mov r8, QWORD PTR arg2
	ENDIF
	IFNB <arg3>
		mov r9, QWORD PTR arg3
	ENDIF
	sub rsp, 20h	
	call printf
	add rsp, 20h
ENDM

printItB MACRO pInfo:REQ, arg1, arg2, arg3
	mov rcx, cfm2$(pInfo)

	IFNB <arg1>
		mov rdx, QWORD PTR arg1
	ENDIF
	IFNB <arg2>
		mov r8, QWORD PTR arg2
	ENDIF
	IFNB <arg3>
		mov r9, QWORD PTR arg3
	ENDIF
	call printf
ENDM

Real8ToXmm MACRO par1, par2
Local xmmValue
  .data
  align 16
  xmmValue dq par1, par2
  .code
  EXITM <xmmValue>
ENDM	

dataexcp SEGMENT PARA ".data"
	blocksDenested QWORD 0
	dataexcpStart LABEL near
	QWORD 204E4445h ; Signature for END of all blocks
	ORG $-8 ; Overwrite END, if there are catch blocks
dataexcp ENDS

_ExceptionBlock TEXTEQU <0>
__TRY MACRO
	LOCAL tryPos, level
	
	tryPos EQU $

	level TEXTEQU @SizeStr(%_ExceptionBlock)
	level TEXTEQU %(level -1)

	_ExceptionBlock CATSTR _ExceptionBlock, level
	
	dataexcp SEGMENT
		QWORD 544F4C53h ;; Signature for new slot
		QWORD level
		QWORD tryPos
	dataexcp ENDS
ENDM

__EXCEPT MACRO
	LOCAL catchPos, level
	
	catchPos EQU $+5 ;; 5 is the size of the "jmp near" instruction

	level TEXTEQU @SizeStr(%_ExceptionBlock)
	level TEXTEQU %(level -2)
	
	dataexcp SEGMENT
		QWORD level	
		QWORD catchPos
	dataexcp ENDS

	.code

	 %jmp near ptr @catch&_ExceptionBlock&_end
	 %@catch&_ExceptionBlock&_start:
ENDM	

__FINALLY MACRO
	LOCAL endCatchPos, count, level, temp
	endCatchPos EQU $
	
	level TEXTEQU @SizeStr(%_ExceptionBlock)
	level TEXTEQU %(level -2)
	dataexcp SEGMENT
		QWORD level	
		QWORD endCatchPos
		QWORD 204E4445h ;; Signature for end of all blocks
		ORG $-8 ;; Ready to be overwriten, if more Blocks
	dataexcp ENDS
	count TEXTEQU @SizeStr(%_ExceptionBlock)
	count TEXTEQU %(count -1)

	.code
%@catch&_ExceptionBlock&_end:
	.data

	_ExceptionBlock TEXTEQU @SubStr(%_ExceptionBlock, 1, count)

	IF count EQ 1
	    temp TEXTEQU %(_ExceptionBlock +1)
	    BYTE temp
	    IF temp EQ 9
		 _ExceptionBlock TEXTEQU <0>
	    ELSE 
	        _ExceptionBlock TEXTEQU <temp>
	    ENDIF 
	ENDIF	
	.code
ENDM

.code
OPTION PROLOGUE:NONE 
OPTION EPILOGUE:NONE 

; rcx=thesize
; rdx=alignm

_alloca PROC thesize:DWORD, alignm:DWORD
  mov r9, [rsp] ; return address
  mov ecx, ecx ; zero-extend 
  mov edx, edx ; zero-extend 
  
  cmp rdx, 16
  jge @F
  mov rdx, 16 ; Minimum alignment to consider in Win 64 is 16 bytes
@@: 
  cmp rdx, 4096
  jle @F
  mov rdx, 4096
@@: 
  lea rax, [rcx]

  lea r10, [rsp+8]
  sub r10, rax
  neg rdx
  and r10, rdx
  
  xor r11, r11
  lea rax, [rsp+8h]
  sub rax, r10
  
  cmovb r10,r11 
  mov r11,qword ptr gs:[10h] ; Register gs points to the TEB in Windows 64-bit.
           ; TEB's StackLimit is in gs:[10h]. See below.
  cmp  r10,r11
  jae @exit
  and r10w,0F000h 
@@: 
  lea  r11,[r11-1000h] 
  mov byte ptr [r11],0 
  cmp r10,r11
  jne @B
@exit:
  sub rsp, rax
  
  mov [rsp], r9
  mov rax, rsp
  add rax, 8
  ret
_alloca ENDP

OPTION PROLOGUE:PROLOGUEDEF
OPTION EPILOGUE:EPILOGUEDEF