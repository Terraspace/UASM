	.x64
	option casemap:none
	option win64:11
	option frame:auto
	option STACKBASE:RSP
	
	ExitProcess proto :DWORD

	CStr macro Text:VARARG
		local szText
	    .data
	szText  db Text,0
	    .code
	    exitm <ADDR szText>
	endm
	
	FP4 MACRO value
        LOCAL vname
        .data
        align 4
          vname REAL4 value
        .code
        EXITM <vname>
    ENDM

    FP8 MACRO value
        LOCAL vname
        .data
        align 8
          vname REAL8 value
        .code
        EXITM <vname>
    ENDM
      
	include xmmtypes.inc
	
    includelib <kernel32.lib>
    includelib <user32.lib>


; Define an HVA 2 element structure.
; Both elements are 128bit XMM types.		
	hva2 struct
		a __m128f <>
		b __m128f <>
	hva2 ends

; Define an HVA 3 element structure.
; All elements are 128bit XMM types.	
	hva3 struct
		a __m128f <>
		b __m128f <>
		cc __m128f <>		
	hva3 ends

; Define an HVA 4 element structure.
; All elements are 128bit XMM types.	
	hva4 struct
		a __m128f <>
		b __m128f <>
		cc __m128f <>
		d __m128f <>
	hva4 ends

; Define an HVA 2 element structure.
; All elements are 256bit YMM types.	
	hva22 struct
		a __m256f <>
		b __m256f <>
	hva22 ends

; Define an HVA 4 element structure.
; All elements are 256bit YMM types.	
	hva42 struct
		a __m256f <>
		b __m256f <>
		cc __m256f <>
		d __m256f <>
	hva42 ends

; Define an HFA 2 element structure.
; All elements are floats.	
	hfa2 struct
		f0 real4 0.0
		f1 real4 0.0
	hfa2 ends

; Define an HFA 3 element structure.
; All elements are floats.
	hfa3 struct
		f0 real4 0.0
		f1 real4 0.0
		f2 real4 0.0
	hfa3 ends

; Define an HFA 4 element structure.
; All elements are floats.	
	hfa4 struct
		f0 real4 0.0
		f1 real4 1.0
		f2 real4 2.0
		f3 real4 3.0
	hfa4 ends

; Define an HFA 2 element structure.
; All elements are doubles.	
	hfa5 struct
		d0 real8 0.0
		d1 real8 0.0
	hfa5 ends

; Define an HFA 3 element structure.
; All elements are doubles.
	hfa6 struct
		d0 real8 0.0
		d1 real8 0.0
		d2 real8 0.0
	hfa6 ends

; Define an HFA 4 element structure.
; All elements are doubles.	
	hfa7 struct
		d0 real8 0.0
		d1 real8 0.0
		d2 real8 0.0
		d3 real8 0.0		
	hfa7 ends	

; Declare prototypes for a range of different r-vectorcall combinations.
; Disassembly of the invocation of these procedures will help to understand the calling convention and ABI.		
TestProc      PROTO a:DWORD, b:REAL4
TestProc2     PROTO a:DWORD, b:QWORD
TestProc3     PROTO VECTORCALL a:DWORD, b:REAL4, cc:__m128
TestProc4     PROTO VECTORCALL a:hfa2
TestProc5     PROTO VECTORCALL a:hfa3, b:REAL4
TestProc6     PROTO VECTORCALL a:hfa4
TestProc7     PROTO VECTORCALL a:DWORD, b:REAL4, cc:__m128f, e:DWORD, f:DWORD, cd:__m128
TestProc8     PROTO VECTORCALL a:hfa5
TestProc9     PROTO VECTORCALL a:hfa6
TestProc10    PROTO VECTORCALL a:hfa7
TestProc11    PROTO VECTORCALL a:DWORD, b:REAL4, cc:__m128, d:__m128, e:hva2, f:__m128f
TestProc12    PROTO VECTORCALL a:hfa4, b:hfa4
TestProc13    PROTO VECTORCALL a:hfa4, b:REAL4, cc:REAL4, d:REAL4
TestProc14    PROTO VECTORCALL a:hfa4, b:DWORD, cc:DWORD, d:DWORD, e:DWORD
TestProc15    PROTO VECTORCALL a:hfa4, b:DWORD, cc:DWORD, d:DWORD, e:DWORD, f:DWORD
TestProc16    PROTO VECTORCALL a:DWORD, b:DWORD, cc:DWORD, d:DWORD, e:REAL4, f:REAL4, g:REAL4, h:REAL4
TestProc17    PROTO VECTORCALL a:hfa4, b:REAL4, cc:REAL4, d:REAL4, e:REAL4
TestProc18    PROTO VECTORCALL a:__m128f, b:DWORD, cc:DWORD, d:__m128f
TestProc19    PROTO VECTORCALL a:hfa4, b:DWORD, cc:DWORD, d:__m128f
TestProc20    PROTO VECTORCALL a:hva4, b:hva2, cc:__m128f
TestProc21    PROTO VECTORCALL a:__m128f, b:hva2
TestProcHVA1  PROTO VECTORCALL a:hva2
TestProcHVA2  PROTO VECTORCALL a:hva4
TestProcHVA3  PROTO VECTORCALL a:hva22
TestProcHVA4  PROTO VECTORCALL a:hva42
TestProcHVA5  PROTO VECTORCALL a:hva3
TestProcHVA1x PROTO VECTORCALL i:DWORD, a:hva2
TestProcHVA2x PROTO VECTORCALL i:DWORD, a:hva4
TestProcHVA3x PROTO VECTORCALL i:DWORD, a:hva22
TestProcHVA4x PROTO VECTORCALL i:DWORD, a:hva42
TestProcHVA5x PROTO VECTORCALL i:DWORD, a:REAL4, b:REAL8, cc:REAL4, d:hva42
TestProc22    PROTO VECTORCALL a:DWORD, b:REAL4, cc:hfa4, d:hfa4
TestProc23    PROTO VECTORCALL a:DWORD, b:REAL4, c1:__m128, c2:__m128,c3:__m128,c4:__m128,c5:__m128
TestProc24    PROTO VECTORCALL a:DWORD, b:REAL4, c1:__m128, c2:__m128,c3:__m128,c4:__m128,c5:__m128, c6:__m128f
TestProc25    PROTO VECTORCALL a:DWORD, b:REAL4, cc:__m128f, d:__m128

.data
	
	align 16
	MyVector __m128 { <1.0, 2.0, 3.0, 4.0> }							; Declare a 4-element float SIMD type.
	MyVec4   __m128 { <00001111r, 00002222r, 00003333r, 00004444r> }	; Declare a 4-element float SIMD type (using hex notation).
	MyVector2 __m128f <5.0, 6.0, 7.0, 8.0>								; Declare a 4-element float SIMD type.
	align 16	
	hf1 hfa2 < 9.0, 10.0 >
	align 16	
	hf2 hfa3 < 11.0, 12.0, 13.0 >
	align 16	
	hf3 hfa4 < 4.0, 5.0, 6.0, 7.0 >										; Declare a 4-element float HFA type.
	hf5 hfa5 < 1.0, 2.0 >
	hf6 hfa6 < 1.0, 2.0, 3.0 >
	hf7 hfa7 < 4.0, 5.0, 6.0, 7.0 >	
	align 16	
	hv1 hva2 { <1.0, 2.0, 3.0, 4.0>, <1.0, 2.0, 3.0, 4.0> }
	align 16	
	hv2 hva4 < <1.0, 2.0, 3.0, 4.0>, <1.0, 2.0, 3.0, 4.0>, <1.0, 2.0, 3.0, 4.0>, <1.0, 2.0, 3.0, 4.0> >
	align 32
	hv3 hva22 < <1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0>, <1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0> >
	align 32
	hv4 hva42 < <1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0>, <1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0>, <1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0>, <1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0> >
	hv5 hva3 < <1.0, 2.0, 3.0, 4.0>, <1.0, 2.0, 3.0, 4.0>, <1.0, 2.0, 3.0, 4.0> >
	mvar dd 0
	
.code

MainCRT PROC FRAME
	
	local aba:__m128f

	invoke TestProc12, hf3, hf3                				
	
	invoke TestProc11, 10, 2.0, MyVector2, MyVector, hv1, xmm6	
	invoke TestProc23, 10, 2.0, xmm7, xmm7, xmm7, xmm7, MyVector2
	invoke TestProcHVA5x, mvar, 2.0, FP8(3.0), 4.0, hv4		
	;invoke TestProc25, 1, 1.0, xmm1, xmm2		; overwritten by invoke test
	invoke TestProc22, 2, 1.0, hf3, hf3	
	invoke TestProc24, 10, 2.0, xmm7, xmm7, xmm7, xmm7, MyVector2, MyVector
	invoke TestProc19, hf3, 2, 3, xmm3		    				
	invoke TestProc21, MyVector, hv1
	invoke TestProc15, hf3, 1, 2, 3, 4, 5	    				
	invoke TestProc13, hf3, 1.0, 2.0, 3.0      				
	invoke TestProc18, MyVector, 2, 3, xmm3    				
	invoke TestProc17, hf3, 1.0, 2.0, 3.0, 4.0					
	invoke TestProc16, 1, 2, 3, 4, 1.0, 2.0, 3.0, 4.0			
	invoke TestProc14, hf3, 1, 2, 3, 4							
	invoke TestProc2, 32, CStr("this is text")					
	invoke TestProc3, 40, FP4(1.0), xmm3						
	invoke TestProc3, 40, FP4(1.0), aba						
	invoke TestProc3, 40, FP4(1.0), MyVector2					
	invoke TestProc4, hf1										
	invoke TestProc5, hf2, 1.0 										
	invoke TestProc8, hf5										
	invoke TestProc9, hf6										
	invoke TestProc10, hf7										
	invoke TestProc6, hf3										
	invoke TestProc7, 30, 1.0, MyVector, 10, 20, MyVector2		 
	invoke TestProcHVA1, hv1									
	invoke TestProcHVA2, hv2									
	invoke TestProcHVA3, hv3									
	invoke TestProcHVA4, hv4									
	invoke TestProcHVA5, hv5									
	invoke TestProcHVA1x, eax, hv1								
	invoke TestProcHVA2x, 20, hv2								
	invoke TestProcHVA3x, ebx, hv3								
	invoke TestProcHVA4x, mvar, hv4							
	invoke TestProc20, hv2, hv1, xmm3							
		
	invoke ExitProcess,0

	ret
MainCRT ENDP

TestProc21 PROC VECTORCALL FRAME a:__m128f, b:hva2

	mov rax,a
	vmovups xmm9,[rax]
	mov rax,b
	vmovups xmm10,[rax]
	vmovups xmm11,[rax+16]
	
	ret
TestProc21 endp

TestProc20 PROC VECTORCALL FRAME a:hva4, b:hva2, cc:__m128f

	ret
TestProc20 endp

; Standard PROC
TestProc PROC FRAME a:DWORD, b:REAL4

	movss xmm10,b
	  
	ret	
TestProc ENDP

; TEST: m128 and m256 local types.
TestProc2 PROC FRAME a:DWORD, b:QWORD
	LOCAL bob2:__m256
	LOCAL bob:__m128
	
	movaps xmm0,bob    ;this should be fine.
	vmovaps xmm0,bob   ;so should this.
	vmovups ymm2,bob2  ;this should be fine always.
	
	mov eax,a
	mov rdi,b
	
	ret	
TestProc2 ENDP

TestProc3 PROC VECTORCALL FRAME uses  xmm7 ymm8 rbx a:DWORD, b:REAL4, cc:__m128
	LOCAL dummy:QWORD

	Mov eax,a   ; this will work.. a will = [rsp+n]  … although smart people would probably just use ecx knowing the argument order…
	mov dummy,rax
	
	;In fastcall b would have been in xmm0, but under vectorcall it's position dependant so would be xmm1
	movss xmm10,b          ;

;	mov rax,cc ; this still needs a QWORD PTR ?
	mov rax,qword ptr cc
	movups xmm11,[rax]  ;

	mov rax,dummy
	
	ret
TestProc3 ENDP

TestProc4 PROC VECTORCALL FRAME a:hfa2

	vmovups xmm0,a ; ensure that a is used to verify it's written correct to shadow space.
	
	ret
TestProc4 ENDP

TestProc8 PROC VECTORCALL FRAME a:hfa5

	vmovups xmm0,a ; ensure that a is used to verify it's written correct to shadow space.
	
	ret
TestProc8 ENDP


TestProc9 PROC VECTORCALL FRAME a:hfa6

	vmovups xmm0,a ; ensure that a is used to verify it's written correct to shadow space.
	
	ret
TestProc9 ENDP


TestProc10 PROC VECTORCALL FRAME a:hfa7

	vmovups xmm0,a ; ensure that a is used to verify it's written correct to shadow space.
	
	ret
TestProc10 ENDP


TestProc11 PROC VECTORCALL FRAME a:DWORD, b:REAL4, cc:__m128, d:__m128, e:hva2, f:__m128f

	ret
TestProc11 ENDP

TestProc12 PROC VECTORCALL FRAME a:hfa4, b:hfa4

	; In this case, a should have come through in xmm0-xmm3
	mov rax,a
	vmovss xmm9,[rax]
	vmovss xmm10,[rax+4]
	vmovss xmm11,[rax+8]
	vmovss xmm12,[rax+12]
	
	; b should have been passed by reference in rdx
	mov rax,b
	vmovss xmm9,[rax]
	vmovss xmm10,[rax+4]
	vmovss xmm11,[rax+8]
	vmovss xmm12,[rax+12]	
	
	vmovss xmm9,[rdx]
	vmovss xmm10,[rdx+4]
	vmovss xmm11,[rdx+8]
	vmovss xmm12,[rdx+12]
		
	ret
TestProc12 ENDP

TestProc13 PROC VECTORCALL FRAME a:hfa4, b:REAL4, cc:REAL4, d:REAL4

	ret
TestProc13 ENDP

TestProc14 PROC VECTORCALL FRAME a:hfa4, b:DWORD, cc:DWORD, d:DWORD, e:DWORD
	ret
TestProc14 endp

TestProc15 PROC VECTORCALL FRAME a:hfa4, b:DWORD, cc:DWORD, d:DWORD, e:DWORD, f:DWORD

	mov rax,a
	vmovss xmm9,[rax].hfa4.f0
	vmovss xmm10,[rax].hfa4.f1
	vmovss xmm11,[rax].hfa4.f2
	vmovss xmm12,[rax].hfa4.f3
	
	mov ebx,b
	mov ebx,cc
	mov ebx,d
	mov ebx,e
	mov ebx,f
	
	ret
TestProc15 endp

TestProc16 PROC VECTORCALL FRAME a:DWORD, b:DWORD, cc:DWORD, d:DWORD, e:REAL4, f:REAL4, g:REAL4, h:REAL4
	ret
TestProc16 endp

TestProc17 PROC VECTORCALL FRAME a:hfa4, b:REAL4, cc:REAL4, d:REAL4, e:REAL4
	ret
TestProc17 endp

TestProc18 PROC VECTORCALL FRAME a:__m128f, b:DWORD, cc:DWORD, d:__m128f
	ret
TestProc18 endp

TestProc19 PROC VECTORCALL FRAME a:hfa4, b:DWORD, cc:DWORD, d:__m128f
	
	mov rax,a
	
	ret
TestProc19 endp

TestProc5 PROC VECTORCALL FRAME a:hfa3, b:REAL4

	vmovups xmm0,a  ; This ssould be bad.. as HFA3 would have been passed in xmm0, xmm1, xmm2.. as individual floats.
	mov rdi,a       ; This shouldn't be very useful.
	vmovss xmm0,b
	
	ret
TestProc5 ENDP

TestProc6 PROC VECTORCALL FRAME a:hfa4

	vmovups xmm0,a ;ensure that a is used so is written to shadow space.
	
	ret
TestProc6 ENDP

TestProc7 PROC VECTORCALL FRAME uses  xmm7 ymm8 rbx a:DWORD, b:REAL4, cc:__m128f, e:DWORD, f:DWORD, cd:__m128
	LOCAL dummy:QWORD

	Mov eax,a   ; this will work.. a will = [rsp+n]  … although smart people would probably just use ecx knowing the argument order…
	mov dummy,rax
	
	;In fastcall b would have been in xmm0, but under vectorcall it's position dependant so would be xmm1
	movss xmm10,b          ;

;	mov rax,cc ; this still needs a QWORD PTR ?
	mov rax,qword ptr cc
	movups xmm11,[rax]  ;

	mov ebx,e
	mov ecx,f
	
	mov rax,dummy
	
	ret
TestProc7 ENDP

TestProcHVA1 PROC VECTORCALL FRAME uses rbx rsi a:hva2

	ret
TestProcHVA1 ENDP

TestProcHVA2 PROC VECTORCALL FRAME a:hva4

	vmovups xmm0,a
		
	ret
TestProcHVA2 ENDP


TestProcHVA3 PROC VECTORCALL FRAME uses rdi a:hva22

	ret
TestProcHVA3 ENDP

TestProcHVA4 PROC VECTORCALL FRAME a:hva42

	vmovups ymm7,a
	
	ret
TestProcHVA4 endp

TestProcHVA5 PROC VECTORCALL FRAME a:hva3

	vmovups ymm7,a
	
	ret
TestProcHVA5 endp

TestProcHVA1x PROC VECTORCALL FRAME uses rbx rsi i:DWORD, a:hva2

	ret
TestProcHVA1x ENDP

TestProcHVA2x PROC VECTORCALL FRAME i:DWORD, a:hva4

	vmovups xmm0,a
		
	ret
TestProcHVA2x ENDP


TestProcHVA3x PROC VECTORCALL FRAME uses rdi i:DWORD, a:hva22

	ret
TestProcHVA3x ENDP

TestProcHVA4x PROC VECTORCALL FRAME i:DWORD, a:hva42

	vmovups ymm7,a
	
	ret
TestProcHVA4x endp

TestProcHVA5x PROC VECTORCALL FRAME i:DWORD, a:REAL4, b:REAL8, cc:REAL4, d:hva42

	mov eax,i
	vmovss xmm9,a
	vmovsd xmm10,b
	vmovss xmm11,cc
	
	vmovups ymm12,d.a
	vmovups ymm13,d.b
	vmovups ymm14,d.cc
	vmovups ymm15,d.d
	
	ret
TestProcHVA5x endp

TestProc22 PROC VECTORCALL FRAME a:DWORD, b:REAL4, cc:hfa4, d:hfa4

	mov rax,d     ;d should already be in r9
	vmovss xmm11,[rax].hfa4.f0
	vmovss xmm11,[rax].hfa4.f1
	vmovss xmm11,[rax].hfa4.f2
	vmovss xmm11,[rax].hfa4.f3
	
	mov ebx,a
	vmovss xmm11,b
	mov rax,cc
	vmovss xmm11,[rax].hfa4.f0
	vmovss xmm11,[rax].hfa4.f1
	vmovss xmm11,[rax].hfa4.f2
	vmovss xmm11,[rax].hfa4.f3
	
	ret
TestProc22 endp

TestProc23 PROC VECTORCALL FRAME a:DWORD, b:REAL4, c1:__m128, c2:__m128,c3:__m128,c4:__m128,c5:__m128

	mov eax,a
	vmovss xmm9,b
	
	mov rax,c1
	vmovaps xmm0,[rax]
	mov rax,c2
	vmovaps xmm1,[rax]
	mov rax,c3
	vmovaps xmm2,[rax]
	mov rax,c4
	vmovaps xmm3,[rax]
	mov rax,c5
	vmovaps xmm5,[rax]
	
	ret
TestProc23 endp


TestProc24 PROC VECTORCALL FRAME a:DWORD, b:REAL4, c1:__m128, c2:__m128,c3:__m128,c4:__m128,c5:__m128, c6:__m128f

	mov eax,a
	vmovss xmm9,b
	
	mov rax,c1
	vmovaps xmm0,[rax]
	mov rax,c2
	vmovaps xmm1,[rax]
	mov rax,c3
	vmovaps xmm2,[rax]
	mov rax,c4
	vmovaps xmm3,[rax]
	mov rax,c5
	vmovaps xmm5,[rax]
	
	ret
TestProc24 endp

TestProc25 PROC VECTORCALL FRAME a:DWORD, b:REAL4, cc:__m128f, d:__m128

	mov rax,cc
	vmovaps xmm0,[rax]
	mov rax,d
	vmovaps xmm1,[rax]
	
	ret
TestProc25 ENDP

end MainCRT
