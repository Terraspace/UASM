; 64-BIT
; Builds with MASM:
; ml64 -c -Zp8 except.asm
; link /SUBSYSTEM:console /ENTRY:main /MACHINE:X64 except.obj
; Can also be built with JWASM without change:
; jwasm -c -Zp8 -win64 except.asm
; link /SUBSYSTEM:console /ENTRY:main /MACHINE:X64 except.obj
; And can also be built with UASM without change:
; uasm -c -Zp8 -win64 except.asm
; link /SUBSYSTEM:console /ENTRY:main /MACHINE:X64 except.obj

; To link for Windows XP 64, as well (if you have a recent link.exe)
; link /SUBSYSTEM:console,5.02 /entry:main /MACHINE:X64 except.obj

.nolist
include seh64_manual.inc
include exceptHelper_manual.inc
.list

; Libraries can be obtained from http://www.masm32.com ,as we did, or from other places.
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
	
	; Count blocks to allow us to calculate the required allocation space.
	mov ebx,0 
	mov rsi, dataexcpStart
@loop1start:	
	cmp QWORD PTR [rsi], 204E4445h ; End of all Blocks?
	je @loop1exit
		cmp QWORD PTR [rsi], 544F4C53h
		jne @F
			inc ebx
@@:
		add rsi,8
		jmp @loop1start
@loop1exit:
	
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
	mov rdi, rax ; Pointer to start of allocated area.
	mov rsi, dataexcpStart
@loop2start:
	cmp QWORD PTR [rsi], 204E4445h ; Signature for end of all Blocks.
	je @loop2exit
		cmp QWORD PTR [rsi],544F4C53h
		jne @loop2_0
			mov r10, rsi ; Save position.
			mov rbx, [rsi+SIZEOF QWORD] ; Get try level.
			mov rcx, 3
			rep movsq ; Copy first 3 fields of Catch Block to allocated space.
			mov r9,0
@loop2_1Start:	
			cmp r9,2
			jae @loop2_1End
@loop2_2Start:
				; Look for catch and endCatch block fields.
				cmp QWORD PTR [rsi],544F4C53h
				jne @F
					add rsi, 3*SIZEOF QWORD
					jmp @loop2_2Start
@@:				
				cmp QWORD PTR [rsi],rbx ; Copy next 2 fields?
				jne @F
					mov rcx, 2
					rep movsq
					jmp @loop2_2End
@@:
				add rsi,2*SIZEOF QWORD
				jmp @loop2_2Start
@loop2_2End:				
				inc r9
				jmp @loop2_1Start
@loop2_1End:			
			mov rsi, r10
@loop2_0:		
		add rsi,8
		jmp @loop2start
@loop2exit:	
	; Move de-nested blocks back to the .data segment.
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

; ***This is a "catch-all" Language Specific Handler for all our PROCEDURES***
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

	; Copy Contexts as they unwind. This serves also for reporting purposes.
	mov rdi, OFFSET originalExceptContext
	mov rax, pDispatcherContext
	mov rsi, (DISPATCHER_CONTEXT ptr [rax]).ContextRecord
	mov rcx, SIZEOF CONTEXT / 8
	rep movsq

	mov rcx,pExceptionRecord  
	cmp DWORD PTR [rcx].EXCEPTION_RECORD.ExceptionFlags, EXCEPTION_NONCONTINUABLE
	jne @F
		; Bail out
		mov rcx,0
		call ExitProcess
@@:	
	test DWORD PTR [rcx].EXCEPTION_RECORD.ExceptionFlags, EXCEPTION_UNWIND
	jnz @F 
		; On first pass of each exception, save data structures
		; pointed to by arguments, so we can report if wanted, 
		; otherwise may be skipped. 
		sub rsp, 20h
		mov rcx, pExceptionRecord
		mov rdx, pContextRecord
		call saveContextAndExceptRecs
		add rsp, 20h
@@:
	; De-nest Catch Blocks.
	cmp blocksDenested,0 ; Previously done?
	jne @F
		sub rsp, 20h
		call denestCatchBlocks
		add rsp, 20h
		mov blocksDenested, 1
@@:
	mov rcx,pExceptionRecord 
	test DWORD PTR [rcx].EXCEPTION_RECORD.ExceptionFlags, EXCEPTION_UNWIND

	mov eax, ExceptionContinueSearch
	jnz @exit
	
	; Search for a valid IMAGE_RUNTIME_FUNCTION_ENTRY
	; that corresponds to the RIP value of the exception
	; or where it left the PROCEDURE.
	mov rax, pDispatcherContext
	mov rcx, (DISPATCHER_CONTEXT PTR [rax]).ControlPc

	lea rdx, imgBase
	lea r8, targetGp
	sub rsp, 20h
	call RtlLookupFunctionEntry
	add rsp, 20h
	cmp rax, 0 ; Is return value valid?
	jnz @F
		; We shouldn't come here (even with leaf functions).
		mov ecx, 1
		call ExitProcess 
@@:	
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
	mov r11, (DISPATCHER_CONTEXT ptr [r11]).ControlPc
	
	mov qword ptr catchHandler,0 ; Zero it, in order to know in the end if we got something.
	mov r12, 7FFFFFFFh ; Enter a big enough number in r12.

@loopStart:
	cmp QWORD PTR [rsi], 204E4445h ; End of all Blocks?
	je @loopEnd
	cmp QWORD PTR [rsi], 544F4C53h ; New slot signature?
	jne @ifEnd
		mov r14, QWORD PTR [rsi].CATCHBLOCKS.try
		cmp r14, BeginAddress
		jb @ifEnd
		cmp r14, r11
		ja @ifEnd
			mov r13, QWORD PTR [rsi].CATCHBLOCKS.catch
			cmp r13, EndAddress
			ja @ifEnd
			cmp r13, r11
			jb @ifEnd
				mov rax, r13
				sub rax, r14
				cmp r12, rax
				jbe @ifEnd
					; Got one
					mov r12, rax
					mov catchHandler, r13
					jmp @ifEnd
@ifEnd:			
	add rsi, SIZEOF CATCHBLOCKS
	jmp @loopStart
@loopEnd:

	cmp qword ptr catchHandler, 0 
	jne @F
		; No Catch Block, continue searching in parent procedures.
		mov eax, ExceptionContinueSearch
		jmp @exit
@@:	

	mov rcx, pEstablisherFrame
	mov rdx, catchHandler
	mov r8, pExceptionRecord
	mov LSHretValue, 66h ; Any value. Let's test it in Proc1.
	lea r9, LSHretValue 

	sub rsp, 30h
	mov rax, pDispatcherContext
      mov rax, [rax].DISPATCHER_CONTEXT.HistoryTable
      mov [rsp+28h], rax	
	lea rax, originalExceptContext 
	mov [rsp+20h], rax

	call RtlUnwindEx ; Must not return. If it returns there is an error.
	add rsp, 30h ; We don't expect to come here, but anyway.
	mov ecx, 1
	call ExitProcess 

@exit:
	; The default epilog will restore non-volatile registers.	
	ret
defAsmSpecificHandler ENDP

; TEST CASES
; Case 1: Exception in procedure with FRAME with exception handler.
proc1 PROC FRAME:defAsmSpecificHandler
	push rbp
	.pushreg rbp
	mov rbp, rsp
	.setframe rbp, 0	
	push rdi
	.pushreg rdi
	push rsi
	.pushreg rsi
	push rbx
	.pushreg rbx
	sub rsp, 8
	.allocstack 8 ; Align stack
	.endprolog
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
	printItA "\tValue returned from LSH=0x%llx\n", QWORD ptr [rbx]
__FINALLY
	lea rsp, [rbp-18h]
	pop rbx
	pop rsi
	pop rdi
	pop rbp
	ret
proc1 ENDP

; Case 2 - Exception in a procedure with FRAME but without exception handler, 
; called by a procedure with a FRAME and exception handler.
proc2_1 PROC FRAME
	push rbp
	.pushreg rbp
	sub rsp, 020h  
	.allocstack 020h	
	lea rbp, [rsp+20h]	
	.setframe rbp, 20h
	movaps [rsp+10h], xmm15
	.savexmm128 xmm15, 10h
	mov [rsp+8h], rsi
	.savereg rsi, 8h
	.endprolog

	sub rsp, 30h ; We can modify the stack outside the prologue because there is a non-RSP frame pointer	
	mov rsi, 33h ; Change rsi to confirm it will be restored in the caller.
	movaps xmm15, XMMWORD PTR Real8ToXmm(1.0, -1.0) ; Change xmm15 as well.

	mov rcx, 0 ; cause divide by zero exception
	div rcx

	movaps xmm15, [rbp-10h]
	mov rsi, [rbp-18h]
	mov rsp, rbp
	pop rbp
	ret
proc2_1 ENDP

proc2_0 PROC FRAME:defAsmSpecificHandler
	push rbp
	.pushreg rbp
	sub rsp, 030h  
	.allocstack 030h	; Note that we are allocating as well 16 bytes for a temporary variable.
	lea rbp, [rsp+30h]	
	.setframe rbp, 30h
	movaps [rsp+20h], xmm15
	.savexmm128 xmm15, 20h
	mov [rsp+18h], rsi
	.savereg rsi, 18h
	.endprolog
__TRY
	sub rsp, 30h ; We can modify the stack outside the prologue because there is a non-RSP frame pointer
	mov rsi, 10h ; It will change in the callee.
	movaps xmm15, XMMWORD PTR Real8ToXmm(50.0, 60.0) ; It in the callee will change as well.
	sub rsp, 20h
	call proc2_1
	add rsp, 20h
__EXCEPT
	printItA "***Exception 0x%x at 0x%llx trapped in proc2_0***", exceptRecord.ExceptionCode, exceptRecord.ExceptionAddress
	printItA "\tRSI at point of exception=0x%llx, original RSI=0x%llx, current RSI=0x%llx", exceptContext._Rsi, originalExceptContext._Rsi, rsi
	printItA "\tXMM15 (low/high) at point of exception= %f/%f",exceptContext._Xmm15._Low, exceptContext._Xmm15._High
	printItA "\tXMM15 original= %f/%f",originalExceptContext._Xmm15._Low, originalExceptContext._Xmm15._High
	movaps [rbp-30h], xmm15
	printItA "\tXMM15 current= %f/%f\n",[rbp-30h], [rbp-28h]
__FINALLY
	movaps xmm15, [rbp-10h]
	mov rsi, [rbp-18h]
	mov rsp, rbp
	pop rbp
	
	ret
proc2_0 ENDP

; Case 3 - Similar to Case 2, but when RSP is the frame pointer.
proc3_1 PROC FRAME
	sub rsp,18h
	.allocstack 18h
	.setframe rsp, 0
	mov [rsp+10h], rsi
	.savereg rsi, 10h
	mov [rsp+8], rdi
	.savereg rdi, 8h
	.endprolog
	mov rsi, 11h ; Change rsi to confirm it will be restored in the caller.
	mov rdi, 22h ; Change rdi as well.
	mov rax, 0 ; Cause an Access Violation.
	mov rax, [rax]

	mov rsi, [rsp+10h]
	mov rdi, [rsp+8]
	add rsp,18h
	ret
proc3_1 ENDP

proc3_0 PROC FRAME:defAsmSpecificHandler
	; When the frame pointer is RSP, it must be static throughtout the procedure
	; So, we allocate here space for the shadow space of the function calls
	; and for 2 non-volatile registers we will be using.
	sub  rsp, 38h
	.allocstack 38h
	.setframe rsp, 0
	mov [rsp+30h], rsi
	.savereg rsi, 30h	
	mov [rsp+28], rdi
	.savereg rdi, 28h
	.endprolog
__TRY 
	mov rsi, 15h ; It will change in the callee.
	mov rdi, 25h ; In the callee it will change as well.
	call proc3_1
	mov r10, 12
__EXCEPT
	printItB "***Exception 0x%x at 0x%llx trapped in proc3_0***", exceptRecord.ExceptionCode, exceptRecord.ExceptionAddress
	printItB "\tRSI at point of exception=0x%llx, original RSI=0x%llx, current RSI=0x%llx", exceptContext._Rsi, originalExceptContext._Rsi, rsi
	printItB "\tRDI at point of exception=0x%llx, original RDI=0x%llx, current RDI=0x%llx\n", exceptContext._Rdi, originalExceptContext._Rdi, rdi
__FINALLY
	mov rsi, [rsp+30h]
	mov rdi, [rsp+28h]
	add rsp,38h
	ret
proc3_0 ENDP

; Case 4 - Nested exceptions.
proc4 PROC FRAME:defAsmSpecificHandler
	push rbp
	.pushreg rbp
	mov rbp, rsp
	.setframe rbp, 0	
	.endprolog
__TRY
	__TRY
		__TRY
			; A third nested exception (Invalid Opcode).
			db 0Fh
			db 0Bh
		__EXCEPT
			printItA "***Exception 0x%x at 0x%llx trapped in Innermost proc4***", exceptRecord.ExceptionCode, exceptRecord.ExceptionAddress	
		__FINALLY
		
		int 3 ; Breakpoint exception (It will pause execution under a debugger).
	__EXCEPT
		printItA "***Exception 0x%x at 0x%llx trapped in Inner proc4***", exceptRecord.ExceptionCode, exceptRecord.ExceptionAddress	
	__FINALLY
	; Raise a continuable exception.
	sub rsp, 20h
	mov rcx,0FFh
	mov rdx,0
	mov r8,0
	mov r9,0
	call RaiseException
	add rsp, 20h
__EXCEPT
	printItA "***Exception 0x%x at 0x%llx trapped in Outer proc4***\n", exceptRecord.ExceptionCode, exceptRecord.ExceptionAddress
__FINALLY
	mov rsp, rbp
	pop rbp
	ret
proc4 ENDP

; Case 5 - Multiple (non-nested) exceptions in the same procedure
proc5 PROC FRAME:defAsmSpecificHandler
	push rbp
	.pushreg rbp
	mov rbp, rsp
	.setframe rbp, 0	
	.endprolog
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
	mov rsp, rbp
	pop rbp
	ret
proc5 ENDP

; Case 6 - Exception in function with 7 parameters, when stackframe is RSP
rcxHome TEXTEQU <rsp+8h>
rdxHome TEXTEQU <rsp+10h>
r8Home TEXTEQU <rsp+18h>
r9Home TEXTEQU <rsp+20h>
param5_1 TEXTEQU <rsp+28h>
param6_1 TEXTEQU <rsp+30h>
param7_1 TEXTEQU <rsp+38h>
proc6_1 PROC FRAME
	sub rsp, 8h
	.allocstack 8h
	.setframe rsp, 0
	mov [rsp], rbx 
	.savereg rbx, 0h
	.endprolog
	mov [rcxHome+8], rcx
	mov [rdxHome+8], rdx
	mov [r8Home+8], r8
	mov [r9Home+8], r9
	mov rax, [param5_1+8] ; rax->5
	mul QWORD PTR [r9Home+8] ; rax->=20
	add rax, [rdxHome+8] ; rax->22
	sub rax, [r8Home+8] ; rax -> 19
	add rax, [param5_1+8] ; rax -> 24
	sub rax, [param6_1+8] ; rax -> 18
	mul QWORD PTR [param7_1+8] ; rax-> 126
	mov rbx, rax ; Save value in rbx
	mov r12, rax ; Save value in r12
	mov rax,0
	div rax ; cause divide by zero exception
	
	mov rbx, [rsp]
	add rsp, 8
	ret
proc6_1 ENDP

proc6_0 PROC FRAME:defAsmSpecificHandler
	sub rsp, 48h
	.allocstack 48h
	.setframe rsp, 0
	mov [rsp+40h], rbx
	.savereg rbx, 40h
	mov [rsp+38h], r12
	.savereg r12, 38h
	.endprolog
__TRY	
	mov rbx, 11h ; Change rbx to confirm if it will be restored
	; rcx,rdx,r8 and r9 were not modified.
	; We need only to transfer what came in the stack.
	mov rax, [param5_1+48h] 
	mov [rsp+20h],rax
	mov rax, [param6_1+48h]
	mov [rsp+28h], rax
	mov rax, [param7_1+48h]
	mov [rsp+30h], rax
	call proc6_1
__EXCEPT
	printItB "***Exception 0x%x at 0x%llx trapped in proc6_0***", exceptRecord.ExceptionCode, exceptRecord.ExceptionAddress
	printItB "\tRBX at point of exception=0x%llx, original RBX=0x%llx, current RBX=0x%llx", exceptContext._Rbx, originalExceptContext._Rbx, rbx
	printItB "\tR12 at point of exception=0x%llx, original R12=0x%llx, current R12=0x%llx\n", exceptContext._R12, originalExceptContext._R12, r12
__FINALLY	
	mov r12, [rsp+38h]
	mov rbx, [rsp+40h]
	add rsp, 48h
	ret
proc6_0 ENDP

; Case 7 - rbp in the middle of stack area.
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


; Case 8- Exception in a Leaf procedure, there is no Catch Block in caller,
; the exception will be passed to caller's parent, which in this case
; is main and the program will terminate normally.
proc8_1 PROC
	hlt ; Prileged instruction.
	ret
proc8_1 ENDP

proc8_0 PROC FRAME:defAsmSpecificHandler
	push rbp
	.pushreg rbp
	mov rbp, rsp
	.setframe rbp, 0	
	.endprolog

	sub rsp,20h
	call proc8_1
	add rsp, 20h

	mov rsp, rbp
	pop rbp
	ret
proc8_0 ENDP

main PROC FRAME:defAsmSpecificHandler
	push    rbp
	.pushreg rbp
	mov rbp, rsp
	.setframe rbp, 0
	sub rsp, 40h ; Shadow space for all calls+3 variables passed on the stack (proc 7) keeping alignment.
	.allocstack 40h 
	.endprolog
__TRY 
	; Case 1 - Exception in procedure with FRAME with exception handler.
	call proc1 

	; Case 2 - Exception in procedure with FRAME but without exception handler, 
	; called by a procedure with a FRAME and exception handler.
	call proc2_0 
	
	; Case 3 - Similar to Case 2, but when RSP is the frame pointer.
	call proc3_0 
	
	; Case 4 - Nested exceptions.
	call proc4 

	; Case 5 - Multiple (non-nested) exceptions in the same procedure.
	call proc5
	
	; Case 6 - Exception in function with parameters 7 parameters, when stackframe is RSP
	
	; This is not for the shadow space (it was allocated previously).
	; and we must keep the stack aligned.
	mov rcx,1
	mov rdx,2
	mov r8,3
	mov r9,4 
	mov QWORD PTR [rsp+20h],5
	mov QWORD PTR [rsp+28h],6
	mov QWORD PTR [rsp+30h],7
	call proc6_0
	

	call proc7

	
	; Case 8- Exception in Leaf procedure, no Catch Block in caller,
	; the exception will be passed to caller's parent.
	call proc8_0

	

__EXCEPT
	printItB "***Exception 0x%x at 0x%llx trapped in Main***", exceptRecord.ExceptionCode, exceptRecord.ExceptionAddress
__FINALLY
	mov rsp, rbp
	pop rbp
	mov rcx, 0
	call ExitProcess
	ret
main ENDP

END
