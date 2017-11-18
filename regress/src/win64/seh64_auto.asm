; uasm -c -Zp8 -win64 except.asm
; link /SUBSYSTEM:console /ENTRY:main /MACHINE:X64 except.obj
OPTION FRAME:AUTO
OPTION WIN64:3

.NOLIST
include seh64_auto.inc
include exceptHelper_auto.inc
.LIST

; Libraries can be obtained from http://www.masm32.com , or from other places.
includelib c:\jwasm\wininc\lib64\msvcrt.lib
printf PROTO :PTR, :VARARG
includelib c:\jwasm\wininc\lib64\kernel32.lib
RtlUnwindEx PROTO :PTR, :PTR, :PTR, :PTR, :PTR, :QWORD
RtlLookupFunctionEntry PROTO :PTR, :PTR, :PTR
ExitProcess PROTO :DWORD
RaiseException PROTO :DWORD, :DWORD, :DWORD, :PTR

CATCHBLOCKS STRUCT
	mark QWORD ?
	levelTry QWORD ?
	try QWORD ?
	levelCatch QWORD ?
	catch QWORD ?
	levelEndcatch QWORD ?
	endCatch QWORD ?
CATCHBLOCKS ENDS	
	
.data
align 16
	originalExceptContext CONTEXT <> 
	exceptContext CONTEXT <>
	exceptRecord EXCEPTION_RECORD <>
	LSHretValue QWORD ?
.code

OPTION PROLOGUE:NONE 
OPTION EPILOGUE:NONE
denestCatchBlocks PROC
	push rbp
	mov rbp, rsp
	
	; Count blocks to allow us to calculate the space we will need to allocate
	mov ebx,0 
	mov rsi, dataexcpStart
	.WHILE QWORD PTR [rsi]!=204E4445h ; End of all Blocks?
		.IF QWORD PTR [rsi] == 544F4C53h ; New Slot?
			inc ebx
		.ENDIF
		add rsi,8
	.ENDW
	
	cmp ebx,0
	je @exit
	mov eax, SIZEOF CATCHBLOCKS
	mul ebx
	mov r12d, eax ; save
	mov ecx, eax
	mov edx, 10h

	; Dynamic stack allocation (this method is overkill for the needs,
	; simply subtracting and aligning would suffice in our case).
	; We will not create shadow space in the callee.
	; RAX will return the start of the allocated space
	call _alloca
	
	; Search for blocks and de-nest them as needed.
	mov rdi, rax ; Pointer to start of allocated area
	mov rsi, dataexcpStart
	.WHILE QWORD PTR [rsi]!=204E4445h ; Signature for end of all Blocks
		.IF QWORD PTR [rsi]==544F4C53h 
			mov r10, rsi ; Save position
			mov rbx, [rsi+SIZEOF QWORD] ; Get try level
			mov rcx, 3
			rep movsq ; Copy first 3 fields of Catch Block to allocated space
			mov r9,0
			.WHILE r9<2
				.WHILE 1
					; Look for catch and endcatch block fields
					.IF QWORD PTR [rsi]==544F4C53h
						add rsi, 3*SIZEOF QWORD
					.ELSE
						.IF QWORD PTR [rsi]==rbx ; Copy next 2 fields?
							mov rcx, 2
							rep movsq
							inc r9
							.break
						.ELSE
							add rsi,2*SIZEOF QWORD
						.ENDIF	
					.ENDIF
				.ENDW
			.ENDW
			mov rsi, r10
		.ENDIF
		add rsi,8
	.ENDW

	; Move de-nested blocks back to .data segment
	mov rsi, rax
	mov rdi, dataexcpStart
	mov rcx, r12
	rep movsb
@exit:	
	mov rsp, rbp
	pop rbp
	ret
denestCatchBlocks ENDP

OPTION PROLOGUE:PROLOGUEDEF
OPTION EPILOGUE:EPILOGUEDEF
saveContextAndExceptRecs PROC pExceptionRecord:PTR, pContextRecord:PTR
	cld
	mov r9, rcx
	mov r10, rdx
	lea rdi, exceptRecord
	mov rsi, r9
	mov rcx, SIZEOF EXCEPTION_RECORD / 4
	rep movsd
	lea rdi, exceptContext
	mov rsi, r10
	mov rcx, SIZEOF CONTEXT / 8
	rep movsq
	ret
saveContextAndExceptRecs ENDP

; ***This "catch-all" Exception Handler will serve all our procedures***
defAsmSpecificHandler PROC USES rbx rsi rdi r12 r13 r14 r15 pExceptionRecord:PTR, pEstablisherFrame:PTR, pContextRecord:PTR, pDispatcherContext:PTR
	LOCAL imgBase : PTR
	LOCAL targetGp : PTR
	LOCAL BeginAddress : PTR
	LOCAL EndAddress : PTR
	LOCAL catchHandler : PTR
	mov pExceptionRecord, rcx
	mov pEstablisherFrame, rdx
	mov pContextRecord, r8
	mov pDispatcherContext, r9
	; Copy Contexts as they unwind. This will be used by RtlUnwindEx
	mov rdi, OFFSET originalExceptContext
	mov rax, pDispatcherContext
	mov rsi, (DISPATCHER_CONTEXT PTR [rax]).ContextRecord
	mov rcx, SIZEOF CONTEXT / 8
	rep movsq

	mov rcx,pExceptionRecord
	.IF DWORD PTR [rcx].EXCEPTION_RECORD.ExceptionFlags==EXCEPTION_NONCONTINUABLE
		; Bail out
		INVOKE ExitProcess,1
	.ENDIF
	test DWORD PTR [rcx].EXCEPTION_RECORD.ExceptionFlags, EXCEPTION_UNWIND
	.IF ZERO?
		; On first pass of each exception save data structures
		; pointed to by arguments, so we can report if wanted,
		; otherwise may be skipped. 
		INVOKE saveContextAndExceptRecs, pExceptionRecord, pContextRecord
	.ENDIF
	
	; De-nest Catch Blocks
	.IF BLOCKSDenested ==0 ; Previously done?
		INVOKE denestCatchBlocks
		mov BLOCKSDenested, 1
	.ENDIF
	
	mov rcx,pExceptionRecord  
	test DWORD PTR [rcx].EXCEPTION_RECORD.ExceptionFlags, EXCEPTION_UNWIND
	.IF !Zero?
		mov eax, ExceptionContinueSearch
		jmp @exit
	.ENDIF
	
	; Search for a valid IMAGE_RUNTIME_FUNCTION_ENTRY
	; that corresponds to the RIP value of the exception
	; or where it left the PROCEDURE.
	mov rax, pDispatcherContext
	mov rcx, (DISPATCHER_CONTEXT PTR [rax]).ControlPc

	INVOKE RtlLookupFunctionEntry, rcx, addr imgBase, addr targetGp
	.IF rax==0 ; Is return value valid?
		; We shouldn't came here (even with leaf functions)
		INVOKE ExitProcess,1
	.ENDIF
	
	mov r13, imgBase
	mov r11d, (IMAGE_RUNTIME_FUNCTION_ENTRY PTR [rax]).BeginAddress
	add r11, r13
	mov BeginAddress, r11
	mov r11d, (IMAGE_RUNTIME_FUNCTION_ENTRY PTR [rax]).EndAddress
	add r11, r13
	mov EndAddress, r11

	; Search for the (innermost) Catch Block in range (in case of nested blocks).
	mov rsi, dataexcpStart
	mov r11, pDispatcherContext
	mov r11, (DISPATCHER_CONTEXT PTR [r11]).ControlPc
	
	mov catchHandler,0 ; Zero it, in order to know in the end if we got something
	mov r12, 7FFFFFFFh ; Enter a big enough value in r12.

	.WHILE QWORD PTR [rsi] != 204E4445h ; End of all Blocks?
		.IF QWORD PTR [rsi] ==544F4C53h ; New slot signature?
			mov r14, QWORD PTR [rsi].CATCHBLOCKS.try
			.IF (r14>=BeginAddress) && (r14<=r11)
				mov r13, QWORD PTR [rsi].CATCHBLOCKS.catch
				.IF (r13<=EndAddress) && (r13>=r11)
					mov rax, r13
					sub rax, r14
					.IF r12>=rax
						; Got one
						mov r12, rax
						mov catchHandler, r13
					.ENDIF
				.ENDIF
			.ENDIF
		.ENDIF
		add rsi, SIZEOF CATCHBLOCKS
	.ENDW
	
	.IF catchHandler==0
		; No Catch Block, continue searching in parent procedures
		mov eax, ExceptionContinueSearch
		jmp @exit
	.ENDIF

	mov rax, pDispatcherContext
	mov r11, [rax].DISPATCHER_CONTEXT.HistoryTable
	mov LSHretValue, 66h ; Any value. Let's test it in Proc1.
	
	; Must not return. If it returns there is an error
	INVOKE RtlUnwindEx, pEstablisherFrame, catchHandler, pExceptionRecord, addr LSHretValue, addr originalExceptContext, r11
	INVOKE ExitProcess, 1
@exit:
	; The default epilog will restore non-volatile registers	
	ret
defAsmSpecificHandler ENDP

; TEST CASES
; Case 1: Exception in procedure with FRAME with exception handler.
proc1 PROC FRAME:defAsmSpecificHandler USES rdi rsi rbx
__TRY	
	; Enter some values to confirm they will not change with the exception.
	mov rbx, 33h
	mov rsi, 44h
	mov rdi, 55h
	sub rsp, 30h ; We can modify the stack outside the prologue because there is a non-RSP frame pointer
	mov rax, 0 ; Causes an Access Violation.
	mov rax, [rax]
__EXCEPT
	mov rbx, rax ; Save
	printItA "***Exception 0x%x at 0x%llx trapped in proc1***", exceptRecord.ExceptionCode, exceptRecord.ExceptionAddress
	printItA "\tCurrent Registers: RBX=0x%llx, RSI=0x%llx, RDI=0x%llx", originalExceptContext._Rbx, originalExceptContext._Rsi, originalExceptContext._Rdi
	printItA "\tValue returned from LSH=0x%llx\n", QWORD PTR [rbx]
__FINALLY
	ret
proc1 ENDP

; Case 2 - Exception in a procedure with FRAME but without exception handler, 
; called by a procedure with a FRAME and exception handler.
proc2_1 PROC FRAME USES xmm15 rsi
	
	sub rsp, 30h ; We can modify the stack outside the prologue because there is a non-RSP frame pointer	
	mov rsi, 33h ; Change rsi to confirm it will be restored in the caller.
	movaps xmm15, XMMWORD PTR Real8ToXmm(1.0, -1.0) ; Change xmm15 as well.
	mov rcx, 0 ; cause divide by zero exception
	div rcx

	ret
proc2_1 ENDP

proc2_0 PROC FRAME:defAsmSpecificHandler USES xmm15 rsi
	LOCAL tempXMM : XMMWORD
__TRY
	sub rsp, 30h ; We can modify the stack outside the prologue because there is a non-RSP frame pointer
	mov rsi, 10h ; It will change in the callee.
	movaps xmm15, XMMWORD PTR Real8ToXmm(50.0, 60.0) ; In the callee it will change as well.
	INVOKE proc2_1
__EXCEPT
	printItA "***Exception 0x%x at 0x%llx trapped in proc2_0***", exceptRecord.ExceptionCode, exceptRecord.ExceptionAddress
	printItA "\tRSI at point of exception=0x%llx, original RSI=0x%llx, current RSI=0x%llx", exceptContext._Rsi, originalExceptContext._Rsi, rsi
	printItA "\tXMM15 (low/high) at point of exception= %f/%f",exceptContext._Xmm15._Low, exceptContext._Xmm15._High
	printItA "\tXMM15 original= %f/%f",originalExceptContext._Xmm15._Low, originalExceptContext._Xmm15._High
			
	movaps tempXMM, xmm15
	printItA "\tXMM15 current= %f/%f\n",QWORD PTR tempXMM, QWORD PTR [tempXMM+8]

__FINALLY
	ret
proc2_0 ENDP

OPTION STACKBASE:RSP
; Case 3 - Similar to Case 2, but when RSP is the frame pointer.
proc3_1 PROC FRAME USES rsi rdi

	mov rsi, 11h ; Change rsi to confirm it will be restored in the caller.
	mov rdi, 22h ; Change rdi as well.
	mov rax, 0 ; Cause an Access Violation.
	mov rax, [rax]
	ret
proc3_1 ENDP

proc3_0 PROC FRAME:defAsmSpecificHandler uses rsi rdi
	; When the frame pointer is RSP, it must be static throughtout the procedure
	; So, we allocate here space for the shadow space of the function calls
	; and for 2 non-volatile registers we will be using.
__TRY 
	mov rsi, 15h ; It will change in the callee.
	mov rdi, 25h ; In the callee it will change as well.
	INVOKE proc3_1
	mov r10, 12
__EXCEPT
	printItB "***Exception 0x%x at 0x%llx trapped in proc3_0***", exceptRecord.ExceptionCode, exceptRecord.ExceptionAddress
	printItB "\tRSI at point of exception=0x%llx, original RSI=0x%llx, current RSI=0x%llx", exceptContext._Rsi, originalExceptContext._Rsi, rsi
	printItB "\tRDI at point of exception=0x%llx, original RDI=0x%llx, current RDI=0x%llx\n", exceptContext._Rdi, originalExceptContext._Rdi, rdi
__FINALLY
	ret
proc3_0 ENDP

OPTION STACKBASE:RBP
; Case 4 - Nested exceptions.
proc4 PROC FRAME:defAsmSpecificHandler
__TRY
	__TRY
		__TRY
			; A third nested exception (Invalid Opcode).
			db 0Fh
			db 0Bh
		__EXCEPT
			printItA "***Exception 0x%x at 0x%llx trapped in Innermost proc4***", exceptRecord.ExceptionCode, exceptRecord.ExceptionAddress	
		__FINALLY
		
		;int 3 ; Breakpoint exception (It will pause execution under a debugger).
	__EXCEPT
		printItA "***Exception 0x%x at 0x%llx trapped in Inner proc4***", exceptRecord.ExceptionCode, exceptRecord.ExceptionAddress	
	__FINALLY
	; Raise a continuable exception.
	INVOKE RaiseException, 0FFh, 0, 0, 0
__EXCEPT
	printItA "***Exception 0x%x at 0x%llx trapped in Outer proc4***\n", exceptRecord.ExceptionCode, exceptRecord.ExceptionAddress
__FINALLY
	ret
proc4 ENDP

; Case 5 - Multiple (non-nested) exceptions in the same procedure
proc5 PROC FRAME:defAsmSpecificHandler
__TRY
	; Make stack unaligned for a vector instruction.
	; We can modify the stack because we have a frame pointer.
	sub rsp, 18h
	movaps xmm0, XMMWORD PTR [rsp]
__EXCEPT
	printItA "***Exception 0x%x at 0x%llx trapped in proc5 - 1st Catch Block***", exceptRecord.ExceptionCode, exceptRecord.ExceptionAddress
__FINALLY

__TRY
	hlt ; cause another exception
__EXCEPT
	printItA "***Exception 0x%x at 0x%llx trapped in proc5 - 2nd Catch Block***\n", exceptRecord.ExceptionCode, exceptRecord.ExceptionAddress
__FINALLY
	ret
proc5 ENDP

; Case 6 - Exception in function with parameters 7 parameters, when stackframe is RSP
OPTION STACKBASE:RSP
proc6_1 PROC FRAME USES rbx param1_1:QWORD, param2_1:QWORD, param3_1:QWORD, param4_1:QWORD, param5_1:QWORD, param6_1:QWORD, param7_1:QWORD
	mov param1_1, rcx
	mov param2_1, rdx
	mov param3_1, r8
	mov param4_1, r9

	mov rax, param5_1 ; rax->5
	mul QWORD ptr param4_1 ; rax->20
	add rax, param2_1 ; rax->22
	sub rax, param3_1 ; rax->19
	add rax, param5_1 ; rax->24
	sub rax, param6_1 ; rax->18
	mul QWORD PTR param7_1 ; rax->126

	mov rbx, rax ; Save value in rbx
	mov r12, rax ; Save value in r12
	mov rax,0
	div rax ; cause divide by zero exception
	
	ret
proc6_1 ENDP

proc6_0 PROC FRAME:defAsmSpecificHandler USES rbx r12 param1_1:QWORD, param2_1:QWORD, param3_1:QWORD, param4_1:QWORD, param5_1:QWORD, param6_1:QWORD, param7_1:QWORD

__TRY	
	mov rbx, 11h ; Change rbx to confirm if it will be restored
	INVOKE proc6_1, param1_1, param2_1, param3_1, param4_1, param5_1, param6_1, param7_1
__EXCEPT
	printItB "***Exception 0x%x at 0x%llx trapped in proc6_0***", exceptRecord.ExceptionCode, exceptRecord.ExceptionAddress
	printItB "\tRBX at point of exception=0x%llx, original RBX=0x%llx, current RBX=0x%llx", exceptContext._Rbx, originalExceptContext._Rbx, rbx
	printItB "\tR12 at point of exception=0x%llx, original R12=0x%llx, current R12=0x%llx\n", exceptContext._R12, originalExceptContext._R12, r12
__FINALLY	
	ret
proc6_0 ENDP

; Case 7 - rbp in the middle of stack area.
; NO EQUIVALENT in AUTO MODE?
OPTION FRAME:NOAUTO
OPTION STACKBASE:RBP
proc7 PROC FRAME:defAsmSpecificHandler 
	push    rbp
	.pushreg rbp
	push    rbx 
	.pushreg rbx
	sub rsp, 028h
	.allocstack 028h
	lea rbp, [rsp+10h]
	.setframe rbp, 10h
	.endprolog
__TRY	
	hlt
__EXCEPT
	printItA "***Exception 0x%x at 0x%llx trapped in proc7***", exceptRecord.ExceptionCode, exceptRecord.ExceptionAddress
__FINALLY		
	lea rsp, [rbp+18h]
	pop rbx
	pop rbp
	ret
proc7 ENDP

OPTION FRAME:AUTO
; Case 8- Exception in a Leaf procedure, there is no Catch Block in caller,
; the exception will be passed to caller's parent, which in this case
; is main and the program will terminate normally.
proc8_1 PROC
	hlt ; Prileged instruction.
	ret
proc8_1 ENDP

proc8_0 PROC FRAME:defAsmSpecificHandler
	INVOKE proc8_1
	ret
proc8_0 ENDP

main PROC FRAME:defAsmSpecificHandler
__TRY 
;int 3
	; Case 1 - Exception in procedure with FRAME with exception handler.
	INVOKE proc1 

	; Case 2 - Exception in procedure with FRAME but without exception handler, 
	; called by a procedure with a FRAME and exception handler.
	INVOKE proc2_0 
	
	; Case 3 - Similar to Case 2, but when RSP is the frame pointer.
	INVOKE proc3_0 
	
	; Case 4 - Nested exceptions.
	INVOKE proc4 

	; Case 5 - Multiple (non-nested) exceptions in the same procedure.
	INVOKE proc5

	; Case 6 - Exception in function with parameters 7 parameters, when stackframe is RSP
	INVOKE proc6_0, 1,2,3,4,5,6,7
	
	; Case 7 - rbp in the middle of stack area.
	INVOKE proc7
	
	; Case 8- Exception in Leaf procedure, no Catch Block in caller,
	; the exception will be passed to caller's parent.
	INVOKE proc8_0
	
__EXCEPT
	printItB "***Exception 0x%x at 0x%llx trapped in Main***", exceptRecord.ExceptionCode, exceptRecord.ExceptionAddress
__FINALLY
	INVOKE ExitProcess,0
	ret
main ENDP

end 
