
.x64
option casemap:none
option stackbase:rbp
option literals:on

include misc/xmmtypes.inc

.data

myVar1 dd 1
myVar2 REAL4 2.3

align 16
myVec  __m128.i32 { <0,1,2,3> }

align 32
myVec2 __m256.i32 { <0,1,2,3,4,5,6,7> }

MYSTRUCTt struct
	f1 QWORD ?
	f2 REAL4 ?
	f3 REAL8 ?
	f4 BYTE  ?
MYSTRUCTt ends

MYSTRUCT MYSTRUCTt <?>

.code

 ;TESTCASE: empty proc, frame pointer omission.
testProc1 PROC SYSTEMV
	ret
testProc1 ENDP

 ;TESTCASE: simple.
testProc2 PROC SYSTEMV var1:DWORD
	mov eax,var1
	ret
testProc2 endp

 ;TESTCASE: simple all gpr registers.
testProc3 PROC SYSTEMV var1:QWORD, var2:WORD, var3:BYTE, var4:DWORD, var5:PTR, var6:DWORD
	mov rax,var1
	mov bx,var2
	mov cl,var3
	mov eax,var4
	mov rax,var5
	mov eax,var6
	ret
testProc3 endp

; TESTCASE: all 6gprs used, 3 stack arguments
testProc4 PROC SYSTEMV USES rbx r10 xmm0 var1:QWORD, var2:WORD, var3:BYTE, var4:DWORD, var5:PTR, var6:DWORD, var7:DWORD, var8:QWORD, var9:WORD
	LOCAL aVar:DWORD
	LOCAL bVar:QWORD
	mov rax,var1
	mov bx,var2
	mov cl,var3
	mov eax,var4
	mov rax,var5
	mov eax,var6
	mov eax,var7
	mov rax,var8
	mov ax,var9
	ret
testProc4 endp

; TESTCASE: 5+6 test ordering of registers, must allocated on demand rather than by ordinal.
testProc5 PROC SYSTEMV var1:QWORD, var2:QWORD, var3:REAL4, var4:REAL4
	mov rax,var1
	mov rbx,var2
	movss xmm0,var3
	movss xmm1,var4
	ret
testProc5 ENDP

testProc6 PROC SYSTEMV var1:REAL4, var2:REAL4, var3:QWORD, var4:QWORD
	mov rax,var3
	mov rbx,var4
	movss xmm0,var1
	movss xmm1,var2
	ret
testProc6 ENDP

; TESTCASE: Combinations of multiple types including vectors, uses and locals
testProc7 PROC SYSTEMV USES rbx r10 xmm0 fl1:REAL4, fl2:REAL4, fl3:REAL8, vec1:XMMWORD, vec3:__m128, var1:QWORD, var2:WORD, var3:BYTE, var4:DWORD, var5:PTR, var6:DWORD, var7:DWORD, var8:QWORD, var9:WORD
	LOCAL aVar:DWORD
	LOCAL bVar:QWORD
	mov rax,var1
	mov bx,var2
	mov cl,var3
	mov eax,var4
	mov rax,var5
	mov eax,var6
	mov eax,var7
	mov rax,var8
	mov ax,var9
	
	vmovaps xmm0,vec1
	vmovaps xmm1,vec3
	
	mov eax,aVar
	mov rbx,bVar
	
	ret
testProc7 endp

; TESTCASE: Combinations of multiple types including vectors, uses and locals
testProc8 PROC SYSTEMV USES rbx r10 xmm0 fl1:REAL4, fl2:REAL4, fl3:REAL8, vec1:XMMWORD, vec2:YMMWORD, vec3:__m128, var1:QWORD, var2:WORD, var3:BYTE, var4:DWORD, var5:PTR, var6:DWORD, var7:DWORD, var8:QWORD, var9:WORD
	LOCAL aVar:DWORD
	LOCAL bVar:QWORD
	mov rax,var1
	mov bx,var2
	mov cl,var3
	mov eax,var4
	mov rax,var5
	mov eax,var6
	mov eax,var7
	mov rax,var8
	mov ax,var9
	
	vmovaps xmm0,vec1
	vmovaps xmm1,vec3
	vmovups ymm1,vec2
	
	ret
testProc8 endp

; TESTCASE: Variadic procedure, RAX contains count of used vector registers
testProc9 PROC SYSTEMV var1:QWORD, var2:REAL4, var3:VARARG
	ret
testProc9 ENDP

; TESTCASE: structure members are extracted and assigned to registers individually, remaining ones are pushed to stack. STRUCTS are passed by-value
;testProc10 PROC SYSTEMV var1:QWORD, var2:MYSTRUCTt

;	ret
;testProc10 ENDP

; TESTCASE: float going to stack.
testProc12 PROC SYSTEMV var1:REAL4, var2:REAL4, var3:REAL4, var4:REAL4, var5:REAL4, var6:REAL4, var7:REAL4, var8:REAL4, var9:REAL4, var10:REAL4

	ret
testProc12 ENDP

; TESTCASE: double going to stack.
testProc13 PROC SYSTEMV var1:REAL8, var2:REAL8, var3:REAL8, var4:REAL8, var5:REAL8, var6:REAL8, var7:REAL8, var8:REAL8, var9:REAL8, var10:REAL8

	ret
testProc13 ENDP

; TESTCASE: argument ADDR to stack.
testProc14 PROC SYSTEMV var1:DWORD, var2:DWORD, var3:DWORD, var4:DWORD, var5:DWORD, var6:REAL8, var7:REAL8, var8:REAL8, var9:REAL8, var10:REAL8, var11:PTR, var12:QWORD

	ret
testProc14 ENDP

testProc15 PROC SYSTEMV var1:DWORD, var2:DWORD, var3:DWORD, var4:DWORD, var5:DWORD, var6:DWORD,    var7:DWORD, var8:BYTE, var9:WORD, var10:QWORD

	ret
testProc15 ENDP

testProc16 PROC SYSTEMV var1:DWORD, var2:DWORD, var3:DWORD, var4:DWORD, var5:DWORD, var6:DWORD,    var7:DWORD, var8:QWORD, var9:BYTE, var10:DWORD

	ret
testProc16 ENDP

testProc17 PROC SYSTEMV var1:REAL4, var2:REAL4, var3:REAL4, var4:REAL4, var5:REAL4, var6:REAL4, var7:REAL4, var8:XMMWORD, var9:__m256, var10:__m128, var11:YMMWORD

	ret
testProc17 ENDP

testProc18 PROC SYSTEMV val1:DWORD, val2:DWORD, val3:DWORD, val4:DWORD, val5:DWORD, val6:DWORD, val7:DWORD, val8:DWORD, val9:DWORD
	ret	
testProc18 ENDP

testProc19 PROC SYSTEMV ival1:DWORD, ival2:DWORD, ival3:DWORD, ival4:DWORD, ival5:DWORD, ival6:DWORD, val1:REAL4, val2:REAL4, val3:REAL4, val4:REAL4, val5:REAL4, val6:REAL4, val7:REAL4, val8:REAL4, val9:XMMWORD, val10:QWORD
	ret	
testProc19 ENDP

testProc20 PROC SYSTEMV ival1:DWORD, ival2:DWORD, ival3:DWORD, ival4:DWORD, ival5:DWORD, ival6:DWORD, val1:REAL4, val2:REAL4, val3:REAL4, val4:REAL4, val5:REAL4, val6:REAL4, val7:REAL4, val8:REAL4, val10:QWORD, val9:XMMWORD
	ret	
testProc20 ENDP

; TESTCASE: redzone optimisation.
OPTION REDZONE:YES
testProc11 PROC SYSTEMV

	ret
testProc11 endp
OPTION REDZONE:NO

proc1 PROC SYSTEMV a:QWORD,b:QWORD,z:QWORD,d:QWORD,e:QWORD,f:QWORD,g:QWORD,h:QWORD
LOCAL bob:QWORD
LOCAL bab:QWORD
   mov bab, r10
   mov bob, r11
   mov rax,a
   mov rax,b
   mov rax,z
   mov rax,d
   mov rax,e
   mov rax,f
   ret
proc1 ENDP

proc4 PROC SYSTEMV a:DWORD, b:REAL4, cc:REAL4, d:REAL4, e:REAL4, f:REAL4;, g:REAL4;, h:REAL4, i:REAL4
	mov eax,a
	vmovss xmm9,xmm9,b
	vmovss xmm9,xmm9,cc
	vmovss xmm9,xmm9,d
	vmovss xmm9,xmm9,e
	vmovss xmm9,xmm9,f
;	vmovss xmm9,g
;	vmovss xmm9,h
;	vmovss xmm9,i
	ret
proc4 ENDP

WriteToConsole PROC SYSTEMV pString:PTR, strLen:DWORD, outHandle:DWORD
    LOCAL handle:DWORD

    mov handle, outHandle ; this is allowed as outHandle evaluates as a register operand.
    mov edx, strLen
    mov rsi, pString
    mov edi, handle
    mov eax, 0
    syscall
    ret
WriteToConsole ENDP

NixProc PROC SYSTEMV USES rbx

	ret
NixProc ENDP

entryPt PROC 
	LOCAL myLocalVar1:DWORD
	LOCAL myLocalFlt:REAL4
	
	mov rax, real8 ptr 123.456
	
	;SYSV regs are:
	;rdi,rsi,rdx,rcx,r8,r9

	invoke NixProc	
	invoke WriteToConsole, "test", 4, 20
	
	invoke testProc1
	
	invoke testProc2, eax
	invoke testProc2, 10
	invoke testProc2, myVar1
	invoke testProc2, myLocalVar1
	
	;invoke testProc3, 10, 20, 30, 40, QWORD PTR 50, 60		 	 	 ; OK
	;invoke testProc3, 10, 20, 30, myVar1, 50, 60   		 	 	 	 ; Argument 5 size mismatch passing a constant to a PTR type.
	;invoke testProc3, 10, 20, 30, myVar1, QWORD PTR 50, 60	 	 	 ; OK
	;invoke testProc3, 10, 20, 30, myVar1, ADDR myLocalVar1, 60	 	 ; OK
	;invoke testProc3, 10, 20, 30, myVar1, ADDR myVar1, 60	 	 	 ; OK
	;invoke testProc3, 10, 20, 30, [rbp-4], ADDR myVar1, 60	 	 	 ; OK
	;invoke testProc3, 10, 20, 30, [rax], ADDR myVar1, 60	 	 	 ; OK
	;invoke testProc3, 10, 20, 30, [rcx+rax*4-10], ADDR myVar1, 60 	 ; OK
	
	invoke testProc3, 10, 20, 30, [rax], "String literals yay", 60 	 ; OK -> Testing string literals
	
	invoke testProc4, 10, 20, 30, 40, QWORD PTR 50, 60, 70, 80, 90
	
	invoke testProc5, 10, 20, 1.0, 2.0
	invoke testProc6, 1.0, 2.0, 10, 20
	invoke testProc5, 10, 20, 1.0, myVar2
	invoke testProc6, 1.0, myVar2, 10, 20
	invoke testProc5, 0, 0, 2.5, 3.5
	
	vmovq xmm0,rax													; TEST VMOVQ.
	;vmovss xmm0,xmm2												; Invalid requires 3 args.
	;vmovsd xmm9,xmm2												; Invalid requires 3 args.
		
	invoke testProc7, 1.0, myVar2, 3.0, xmm5, myVec, 10, 20, 30, myVar1, QWORD PTR 50, 60, 70, 80, 90
	invoke testProc8, 1.0, myVar2, 3.0, xmm6, ymm9, myVec, 10, 20, 30, myVar1, QWORD PTR 50, 60, 70, 80, 90
    
	;invoke proc1,1,2,3,4,5,6,7,8
    ;invoke proc1,rdi,rsi,rdx,rcx,r8,r9,7,8
    ;invoke proc1,rsi,rsi,rdx,rcx,r8,r9,7,8	
  	;invoke proc1,rdi,rsi,rdx,rcx,r8,rdi,7,8
	;invoke proc1,rdi,rsi,rdx,rcx,r8,r8,7,8
    ;invoke proc1,rsi,rsi,r9,rcx,r8,r9,7,8	
	;invoke proc1,rsi,rsi,r8,rcx,r8,r9,7,8		    
   	;invoke proc1,rdi,rsi,rdi,rcx,r8,r9,7,8
   	;invoke proc1,rdi,2,rdx,rdi,r8,r9,7,8
	;invoke proc1,rdi,2,rdx,rdi,r8,r10,7,r9
	;invoke proc1,rax,rbx,r8,rcx,r8,r9,7,8
	;invoke proc1,rsi,rdi,r8,rcx,r8,r9,7,8	   						; Register overwrite on RDI. 	

 	;invoke proc4,10,xmm9,xmm10,xmm11,xmm12,xmm9						; OK	
 	;invoke proc4,10,xmm9,xmm2,xmm0,xmm12,xmm9						; XMM overwrite test (XMM0)
 	
 	;invoke testProc10, 10, MYSTRUCT								; Error reporting of usage of direct struct type
 	
 	;invoke testProc9, 10, xmm0, 10, 20, 30							; Vararg CONST test
 	;invoke testProc9, 10, xmm0, 10, 2.0, 30, 4.0					; Vararg CONST + FLOAT test
	;invoke testProc9, 10, xmm0, WORD PTR 10, 2.0, 30, 4.0			; Vararg CONST + FLOAT test.. testing that overriding the constant size updates the vararg register type that is used.

	;invoke testProc9, 10, xmm0, 10, rax, ebx, xmm4					; Vararg REG + VEC
	;invoke testProc9, 10, xmm0, 10, [rax], dword ptr [rbx], xmm4	; Vararg REG indirect + VEC
	;invoke testProc9, 10, xmm0, 10, 2.0, myVar1, ymm4				; Vararg FLOAT + VEC and EXPR_ADDR / Symbol.
	
	;invoke testProc9, 10, xmm0, 10, 2.0, myVar1, myVec				; Vararg FLOAT + VEC type and EXPR_ADDR / Symbol.
	
	;invoke testProc9, 10, xmm0, ADDR myVar1, 2.0, 30, ymm4			; Vararg FLOAT + VEC + ADDR
	;invoke testProc9, 10, xmm0, ADDR myLocalVar1, 2.0, 30, myVec	; Vararg FLOAT + VEC via __M128 + ADDR iof local
 	
 	;invoke testProc9, 10, xmm0, 10, 20, 30, 40, 50, 60, 80										; Vararg CONST test going to stack
 	;invoke testProc9, 10, xmm0, 10, 2.0, 30, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 	; Vararg CONST + FLOAT going to stack test
 	
 	;invoke testProc9, 10, xmm0, 10, 2.0, 30, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, rax, ebx, cl, xmm12, ymm14 	; Vararg CONST + Direct Registers going to stack test
 	
 	;invoke testProc9, 10, xmm0, 10, 2.0, 30, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, [rax], dword ptr [rbx], [rax], [rcx], dword ptr [rcx]   ; Vararg CONST + Indirect Registers going to stack test
	;invoke testProc9, 10, xmm0, 10, 2.0, 30, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, [r10], dword ptr [rbx], [r11], [r12], dword ptr [r13], myVec, myVec2   ; Vararg CONST + Indirect Registers AND Direct Vector Memory Types going to stack test

	;invoke testProc12, 1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,xmm12						; float const and register to stack via normal argument.
	;invoke testProc12, 1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,real8 ptr 9.0,xmm12				; float const and register to stack via normal argument. SHOULD ERROR due to REAL8/double not float.
	;invoke testProc12, 1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,myLocalFlt,myVar2				; local variable and global variable to stack via normal argument.
	
	;invoke testProc13, 1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,xmm12								; double const and register to stack via normal argument.
	;invoke testProc13, 1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,myLocalFlt,myVar2						; double local variable and global variable to stack via normal argument. Should Error due to floats not doubles on arg9/10.
	;invoke testProc13, 1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,real8 ptr myLocalFlt,real8 ptr myVar2	; double local variable and global variable to stack via normal argument. Should Error due to floats not doubles on arg9/10.

	;invoke testProc14, 1,2,3,4,5,6.0,7.0,8.0,real8 ptr myLocalFlt,real8 ptr myVar2, ADDR myVar1, ADDR myVar2		; ADDR going to stack.
	
	;invoke testProc15,1,2,3,4,5,6,7,8,9,10 		; constant to stack
	;invoke testProc15,1,2,3,4,5,6,7,8,9,10000000000 ; 64bit constant to stack
	
	;invoke testProc16,1,2,3,4,5,6,7,rax,r10b,r11d      							  ; direct register to stack
	;invoke testProc16,1,2,3,4,5,6,7,[rax],[rbx],[r10]  								  ; indirect register to stack , assumed sized
	;invoke testProc16,1,2,3,4,5,6,7,qword ptr [rax], byte ptr [rbx], dword ptr [r10]  ; indirect register to stack, specified size
	;invoke testProc16,1,2,3,4,5,6,7,qword ptr [rax], byte ptr [rbx], qword ptr [r10]  ; indirect register to stack, specified size, should fail on last QWORD incorrect type.
		
	;invoke testProc17,1,2,3,4,5,6,7,xmm9,ymm10,myVec,myVec2		; xmm, ymm to stack via register and memory type ... Also demonstrates integer to float promotion.
	
	;invoke testProc18,1,2,3,4,5,6,7,8,9 										;test std. argument stack alignment
	;invoke testProc19,1,2,3,4,5,6,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,xmm12,8 		;test std. argument stack alignment
	;invoke testProc20,1,2,3,4,5,6,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,8,xmm12 		;test std. argument stack alignment
	
	ret
entryPt ENDP

end entryPt