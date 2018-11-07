	.x64
	option casemap:none
	option win64:11
	option frame:auto
	option STACKBASE:RSP
	option evex:1
		
	ExitProcess proto :DWORD

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

;TopXY PROTO wDim:QWord, sDim:QWord

;ObjRender      PROTO node:BYTE, depth:DWORD, s:REAL4, wx:REAL4, wy:REAL4, wz:REAL4
Scene8_Recurse PROTO VECTORCALL node:BYTE, depth:DWORD, s:REAL4, opos:__m128

; Declare prototypes for a range of different r-vectorcall combinations.
; Disassembly of the invocation of these procedures will help to understand the calling convention and ABI.		
;TestProc      PROTO a:DWORD, b:REAL4
;TestProc2     PROTO a:DWORD, b:QWORD
;TestProc3     PROTO VECTORCALL a:DWORD, b:REAL4, cc:__m128
;TestProc4     PROTO VECTORCALL a:hfa2
;TestProc5     PROTO VECTORCALL a:hfa3, b:REAL4
;TestProc6     PROTO VECTORCALL a:hfa4
;TestProc7     PROTO VECTORCALL a:DWORD, b:REAL4, cc:__m128f, e:DWORD, f:DWORD, cd:__m128
;TestProc8     PROTO VECTORCALL a:hfa5
;TestProc9     PROTO VECTORCALL a:hfa6
;TestProc10    PROTO VECTORCALL a:hfa7
;TestProc11    PROTO VECTORCALL a:DWORD, b:REAL4, cc:__m128, d:__m128, e:hva2, f:__m128f
;TestProc12    PROTO VECTORCALL a:hfa4, b:hfa4
;TestProc13    PROTO VECTORCALL a:hfa4, b:REAL4, cc:REAL4, d:REAL4
;TestProc14    PROTO VECTORCALL a:hfa4, b:DWORD, cc:DWORD, d:DWORD, e:DWORD
;TestProc15    PROTO VECTORCALL a:hfa4, b:DWORD, cc:DWORD, d:DWORD, e:DWORD, f:DWORD
;TestProc16    PROTO VECTORCALL a:DWORD, b:DWORD, cc:DWORD, d:DWORD, e:REAL4, f:REAL4, g:REAL4, h:REAL4
;TestProc17    PROTO VECTORCALL a:hfa4, b:REAL4, cc:REAL4, d:REAL4, e:REAL4
;TestProc18    PROTO VECTORCALL a:__m128f, b:DWORD, cc:DWORD, d:__m128f
;TestProc19    PROTO VECTORCALL a:hfa4, b:DWORD, cc:DWORD, d:__m128f
;TestProc20    PROTO VECTORCALL a:hva4, b:hva2, cc:__m128f
;TestProc21    PROTO VECTORCALL a:__m128f, b:hva2
;TestProcHVA1  PROTO VECTORCALL a:hva2
;TestProcHVA2  PROTO VECTORCALL a:hva4
;TestProcHVA3  PROTO VECTORCALL a:hva22
;TestProcHVA4  PROTO VECTORCALL a:hva42
;TestProcHVA5  PROTO VECTORCALL a:hva3
;TestProcHVA1x PROTO VECTORCALL i:DWORD, a:hva2
;TestProcHVA2x PROTO VECTORCALL i:DWORD, a:hva4
;TestProcHVA3x PROTO VECTORCALL i:DWORD, a:hva22
;TestProcHVA4x PROTO VECTORCALL i:DWORD, a:hva42
;TestProcHVA5x PROTO VECTORCALL i:DWORD, a:REAL4, b:REAL8, cc:REAL4, d:hva42
;TestProc22    PROTO VECTORCALL a:DWORD, b:REAL4, cc:hfa4, d:hfa4
;TestProc23    PROTO VECTORCALL a:DWORD, b:REAL4, c1:__m128, c2:__m128,c3:__m128,c4:__m128,c5:__m128
;TestProc24    PROTO VECTORCALL a:DWORD, b:REAL4, c1:__m128, c2:__m128,c3:__m128,c4:__m128,c5:__m128, c6:__m128f
;TestProc25    PROTO VECTORCALL a:DWORD, b:REAL4, cc:__m128f, d:__m128
;;Dumb          PROTO
;TestProc26    PROTO a:REAL4, b:REAL4, cc:QWORD, d:VARARG
;;GenRNDVoxelData PROTO
;InitGradient PROTO pGradient:PTR Gradient, stops:DWORD, pad0:DWORD, pad1:DWORD, stopData:VARARG
;AddColorStop PROTO pGradient:PTR Gradient, position:REAL4, color:DWORD


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
	
	align 16
	av REAL4 0.0
	ab REAL4 0.0
	ad QWORD 0
	
	Particle STRUCT
		x REAL4 0.0
		y REAL4 0.0
	Particle ends
	
	align 16
	voxel db (12*12*12) DUP (0)
	
	align 64
	ZMM_BITS30 DD 3FFFFFFFh,0,3FFFFFFFh,0,3FFFFFFFh,0,3FFFFFFFh,0
               DD 3FFFFFFFh,0,3FFFFFFFh,0,3FFFFFFFh,0,3FFFFFFFh,0
	YMM_BITS30 YMMWORD 1.23456

.code

;Update_Time PROC FRAME
;	Local S_T:SYSTEMTIME
 ;   Invoke GetLocalTime, Addr S_T
    Ret
;Update_Time ENDP

;GenRNDVoxelData PROC FRAME
;	LOCAL ix:QWORD
;	LOCAL iy:QWORD
;	LOCAL iz:QWORD
;	
;	lea rsi,voxel
;	xor rax,rax
;	mov ix,rax
;	mov iy,rax
;	mov iz,rax
;
;xloop:
;	rdrand eax
;	.if(eax > 0x80000000)
;		mov al,11111111b
;	.else
;		xor eax,eax
;	.endif
;	.if(ix == 0 || ix == 127 || iy == 0 || iy == 127 || iz == 0 || iz == 127)
;		mov al,10000000b
;	.endif
;	mov rbx,ix
;	mov rcx,iy
;	mov rdx,iz
;	shl rcx,7
;	shl rdx,14
;	add rbx,rcx
;	add rbx,rdx
;	mov [rsi+rbx],al
;	inc ix
;	cmp ix,128
;	jl short xloop
;	xor rax,rax
;	mov ix,rax
;	inc iy
;	cmp iy,128
;	jl xloop
;	mov iy,rax
;	inc iz
;	cmp iz,128
;	jl xloop
;		
;	ret
;GenRNDVoxelData ENDP
;
;Dumb PROC FRAME
;
;    xor eax,eax
;    mov ebx,eax
;    
;	ret
;Dumb endp

;WndProc Proto hWin:QWord, uMsg:QWord, wParam:QWord, lParam:QWord
;WndProc2 Proto hWin:QWord, uMsg:QWord, wParam:QWord, lParam:QWord
;ECInitProc proto hInst:QWord,hPrevInst:QWord,CmdLine:QWord,CmdShow:QWord

;
;TopXY Proc FRAME wDim:QWord, sDim:QWord
;    ; ----------------------------------------------------
;    ; This procedure calculates the top X & Y co-ordinates
;    ; for the CreateWindowEx call in the WinMain procedure
;    ; ----------------------------------------------------
;    Mov wDim, Rcx
;    Mov sDim, Rdx
;    
;    shr sDim, 1      ; divide screen dimension by 2
;    shr wDim, 1      ; divide window dimension by 2
;    Mov rax, wDim    ; copy window dimension into eax
;    Sub sDim, rax    ; sub half win dimension from half screen dimension
;    Mov rax, sDim
;    Ret
;TopXY EndP
;
;
;ECInitProc proc Frame uses rbx rdi rsi hInst:QWord,hPrevInst:QWord,CmdLine:QWord,CmdShow:QWord
;	local bOnIdle:qword,lCount:qword,msg[5]:QWORD
;	
;	mov hInst,rcx
;	mov hPrevInst,rdx
;	mov CmdLine,r8
;	mov CmdShow,r9
;	
;	xor eax,eax
;	mov bOnIdle,1
;	
;
;	ret
;ECInitProc ENDP
;
;WndProc Proc Frame USES rsi rdi rbx hWin:QWord, uMsg:QWord, wParam:QWord, lParam:QWord
;     Mov hWin, Rcx
;     Mov uMsg, Rdx
;     Mov wParam, R8
;     Mov lParam, R9
;
;	invoke TopXY,8,4
;	
;     Ret 
;WndProc EndP
;
;WndProc2 Proc Frame hWin:QWord, uMsg:QWord, wParam:QWord, lParam:QWord
;     Mov hWin, Rcx
;     Mov uMsg, Rdx
;     Mov wParam, R8
;     Mov lParam, R9
;
;	invoke TopXY,8,4
;	
;     Ret 
;WndProc2 EndP
;
;Refresh_Static Proto FastCall Private hWnd:QWord
;
;Refresh_Static Proc FastCall Private Frame Uses Rdi hWnd:QWord
;       Mov hWnd, Rcx
;
;     ;  Invoke GetWindowRect, hWnd, Addr hRECT
;      ;   Mov Eax, hRECT.left
;         ;Sub hRECT.right, Eax
;         ;Mov Eax, hRECT.top
;         ;Sub hRECT.bottom, Eax
;       ;Invoke GetParent, hWnd
;       ;Mov Rdi, Rax
;       ;Invoke ScreenToClient, Rdi, Addr hRECT
;         ;Mov Eax, hRECT.left
;         ;Add hRECT.right, Eax
;         ;Mov Eax, hRECT.top
;         ;Add hRECT.bottom, Eax
;       ;Invoke RedrawWindow, Rdi, Addr hRECT, NULL, (RDW_ERASE Or RDW_INVALIDATE  Or RDW_ALLCHILDREN)
;            Ret
;Refresh_Static EndP
;
;SSECheck PROTO rev:DWORD
;
;SSECheck PROC FRAME rev:DWORD
;	
;	mov rax,1
;	cpuid			;ecx bit0=sse3, bit19=sse4.1, bit20=sse4.2             edx bit25=sse, bit26=sse2
;
;	.if rev == 0
;		and ecx,00000000000000000000000000000001b
;		.if ecx == 0
;			mov eax,1
;			ret
;		.else
;			xor eax,eax
;			ret			
;		.endif
;	.endif
;	
;	.if rev == 1
;		and ecx,00000000000010000000000000000000b
;		.if ecx == 0
;			mov eax,1
;			ret
;		.else
;			xor eax,eax
;			ret			
;		.endif	
;	.endif
;	
;	.if rev == 2
;		and ecx,00000000000100000000000000000000b 
;		.if ecx == 0
;			mov rax,1
;			ret
;		.else
;			xor rax,rax
;			ret			
;		.endif	
;	.endif
;	
;	ret
;SSECheck ENDP
;
;
;ObjRender PROC node:BYTE, depth:DWORD, s:REAL4, wx:REAL4, wy:REAL4, wz:REAL4
;
;	ret
;ObjRender ENDP


align 16
Scene8_Recurse PROC VECTORCALL node:BYTE, depth:DWORD, s:REAL4, vpos:__m128
	LOCAL depthMod:BYTE	
;	inc nodeCount
	vpshufd xmm1,xmm3,11101010b     ; xmm1 = wz
	vmulss xmm3,xmm2,xmm5			; s(xmm2) * flen(xmm5)
	vdivss xmm3,xmm3,xmm1			; xmm3 = s*flen/wz
	.if(dl > 10 || xmm3 < xmm4)
;		add rsp,0x38
		ret
	.endif
	vmulss xmm2,xmm2,xmm6			; s *= 0.5
	vmovss s,xmm2
	inc edx
	mov depth,edx	
	and edx,1
	not edx
	inc edx
	mov depthMod,dl
i = 0
REPT 8
	mov al,node
	mov bl,1
	shl bl,i
	test al,bl
	.if(!ZERO?)
		mov rbx,vpos
		vmovaps xmm0,[rbx]
		mov eax,depth
		shl rax,7
		mov bl,[rsi+i]
		or bl,depthMod
		vaddps xmm0,xmm0,[rdi+rax-128+(i*16)]
		invoke Scene8_Recurse, bl, depth, s, xmm0
	.endif
	i = i + 1
ENDM
;	add rsp,0x38
	ret
Scene8_Recurse ENDP

MainCRT PROC FRAME
	
	local aba:__m128f

	;invoke ObjRender, 0xff, 0, 2.0, xmm0, xmm1, xmm2
	invoke Scene8_Recurse, 0xff, 0, 2.0, xmm0
	
;	lea rsi,av
;	invoke TestProc26, [rsi], [rsi].Particle.y, ad
;	
;	invoke TestProc12, hf3, hf3                				
;	invoke TestProc11, 10, 2.0, MyVector2, MyVector, hv1, xmm6	
;	invoke TestProc23, 10, 2.0, xmm7, xmm7, xmm7, xmm7, MyVector2
;	invoke TestProcHVA5x, mvar, 2.0, FP8(3.0), 4.0, hv4		
;	;invoke TestProc25, 1, 1.0, xmm1, xmm2		; overwritten by invoke test
;	invoke TestProc22, 2, 1.0, hf3, hf3	
;	invoke TestProc24, 10, 2.0, xmm7, xmm7, xmm7, xmm7, MyVector2, MyVector
;	invoke TestProc19, hf3, 2, 3, xmm3		    				
;	invoke TestProc21, MyVector, hv1
;	invoke TestProc15, hf3, 1, 2, 3, 4, 5	    				
;	invoke TestProc13, hf3, 1.0, 2.0, 3.0      				
;	invoke TestProc18, MyVector, 2, 3, xmm3    				
;	invoke TestProc17, hf3, 1.0, 2.0, 3.0, 4.0					
;	invoke TestProc16, 1, 2, 3, 4, 1.0, 2.0, 3.0, 4.0			
;	invoke TestProc14, hf3, 1, 2, 3, 4							
;	invoke TestProc2, 32, CStr("this is text")					
;	invoke TestProc3, 40, FP4(1.0), xmm3						
;	invoke TestProc3, 40, FP4(1.0), aba						
;	invoke TestProc3, 40, FP4(1.0), MyVector2					
;	invoke TestProc4, hf1										
;	invoke TestProc5, hf2, 1.0 										
;	invoke TestProc8, hf5										
;	invoke TestProc9, hf6										
;	invoke TestProc10, hf7										
;	invoke TestProc6, hf3										
;	invoke TestProc7, 30, 1.0, MyVector, 10, 20, MyVector2		 
;	invoke TestProcHVA1, hv1									
;	invoke TestProcHVA2, hv2									
;	invoke TestProcHVA3, hv3									
;	invoke TestProcHVA4, hv4									
;	invoke TestProcHVA5, hv5									
;	invoke TestProcHVA1x, eax, hv1								
;	invoke TestProcHVA2x, 20, hv2								
;	invoke TestProcHVA3x, ebx, hv3								
;	invoke TestProcHVA4x, mvar, hv4							
;	invoke TestProc20, hv2, hv1, xmm3	
;	
;	invoke Refresh_Static,0
;	
;	call Update_Time
;
;	vpmovmskb rbx, ymm3 ; 39A8 _ C4 E1 FC:D7. DB
;	vpmovmskb rbx, ymm9 ; 39B2 _ C4 C1 FC:D7. D9
;
;	vpsllq ymm11, ymm11, xmm0 
;	;vpsllq zmm11, zmm11, xmm0 
;
;	vptest ymm8, ymm6
;	vpmuludq ymm8, ymm6, ymmword ptr [r11+10]
;	vpsrlq ymm9, ymm7, xmmword ptr [r11+20H] 
;
;	invoke WndProc2,0,1,2,3
;	invoke WndProc,0,1,2,3
;	invoke ECInitProc,1,2,3,4
;	
;	
;VPSLLDQ ymm9, ymm7, 3
;	vmovss xmm15,[r13+r11*4]
;	vcvttss2si r8,xmm2
;	;000000013F6B7098 C4 41 FA 2C C2       vcvttss2si  r8,xmm10  
;	vsubss xmm10,xmm2,xmm10		;xmm10 = fy = y-(int)y
;	;000000013F6B7104 C4 61 6A 5C D2       vsubss      xmm10,xmm2,xmm2  
;	vmulss xmm13,xmm2,xmm10
;	;000000013F6B7123 C4 61 6A 59 EA       vmulss      xmm13,xmm2,xmm2 
;  	vmulss xmm14,xmm6,xmm10
;	;000000013F6B7128 C4 61 4A 59 F2       vmulss      xmm14,xmm6,xmm2
;
;	invoke TopXY, rax, rdx
;	invoke SSECheck,2
;	
;	vmovdqa zmm1, ZMMWORD PTR ZMM_BITS30 ;work
;	;vmovdqa zmm1, YMMWORD PTR ZMM_BITS30 ;fail
;	vmovdqa ymm1, YMMWORD PTR YMM_BITS30 ;work
;	;vmovdqa zmm1, ZMM_BITS30 ;fail
;	;vmovdqa ymm1, YMM_BITS30 ;work
;		
;	vmovaps xmm1,xmm7
;	vmovdqa xmm3,xmm7
;	vmovdqa xmm9,xmm6
;	vmovdqa xmm3,xmm11
;	vmovdqa xmm11,xmm4
;	
;	VPSLLDQ ymm9, ymm7, 3
;	VPSLLDQ xmm3, xmm8, 3
;	
;	vpsrlq ymm9, ymm7, 4
;	vpsllq ymm9, ymm7, 4
;
;
;;	;here is what it produces:
;;	;vmovdqa ymm1, ymmword ptr [?_006]               ; 40001030 _ C5 FD: 6F. 0D, 00203248 (rel)     
;;	;vmovdqa32 zmm1 {k1}{z}, zmmword ptr [?_005]; 40001038 _ 62 F1 7D C9: 6F. 0D, 002031FE (rel)
;;
;;	;ML64 disassembled:
;;	;?_204: vpsrlq ymm3, ymm1, 3 ; 3878 _ C5 E5: 73. D1, 03
;;	;vpand ymm0, ymm3, ymm15 ; 387D _ C4 C1 65: DB. C7
;;	;HJWASM disassembled (registers reversed, scary error message):
;;	;?_204: vpsrlq ymm1, ymm3, 3 ; 3878 _ C5 F5: 73. D3, 03
;;	;; Note: Prefix bit or byte has no meaning in this context
;;	;vpand ymm0, ymm3, ymm15 ; 387D _ C4 C1 E5: DB. C7
;	vpsrlq ymm3,ymm1,3
;	vpsllq ymm4,ymm5,1
;	vpand ymm0,ymm3,ymm15
;;	
;;	;ML64:
;;	;vpsrlq ymm9, ymm7, 3 ; 3899 _ C5 B5: 73. D7, 03
;;	;HJWASM (wrong register & scary message):
;;	;; Note: Prefix bit or byte has no meaning in this context
;;	;vpsrlq ymm9, ymm15, 3 ; 3899 _ C4 C1 B5: 73. D7, 03
;;	;vpaddq, vpmuludq instructions also generate scary error message
;	vpsrlq ymm9, ymm7, 4
;	vpaddq ymm0, ymm6,ymm7
;	vpmuludq ymm7,ymm8,ymm9
;	vpaddq ymm0, ymm1, ymm2
;	vpmuludq ymm0, ymm1, ymm2
;;	
;;	;ML64:
;;	;vpxor ymm2, ymm2, ymm2 ; 3973 _ C5 ED: EF. D2
;;	;vpcmpeqq ymm3, ymm3, ymm2 ; 3977 _ C4 E2 65: 29. DA
;;	;HJWASM:
;;	;vpxor ymm2, ymm2, ymm2 ; 3974 _ C5 ED: EF. D2
;;	;; Note: Prefix bit or byte has no meaning in this context
;;	;; Note: Unknown opcode reserved for future extensions
;;	;; Note: VEX prefix bits not allowed here
;;	;UNDEFINED UNKNOWN REGISTER TYPE 3, ; 3978 _ C4 E3 E5: 1F. DA, 00
;	vpxor ymm2,ymm2,ymm2
;	vpcmpeqq ymm3,ymm3,ymm2
;;	
;;	lea rsi,av
;;	mov rax,rsi
;;	mov [rsi],rax
;;	invoke InitGradient,[rsi],4,0,0,1.0,0xff0000bb,0.5,0xff000000,0.0,0,0.5,2
;;	invoke InitGradient,[rsi],2,0,0,1.0,0xff0000bb,0.5,0xff000000
;;	
;;	invoke InitGradient,[rsi],2,0,0,1.0,0xff0000bb,0.5,0xff000000
;			
;	;invoke GenRNDVoxelData
;	
;					
;;		
;;	invoke ExitProcess,0

	ret
MainCRT ENDP
;
;TestProc21 PROC VECTORCALL FRAME a:__m128f, b:hva2
;
;	mov rax,a
;	vmovups xmm9,[rax]
;	mov rax,b
;	vmovups xmm10,[rax]
;	vmovups xmm11,[rax+16]
;	
;	ret
;TestProc21 endp
;
;TestProc20 PROC VECTORCALL FRAME a:hva4, b:hva2, cc:__m128f
;
;	ret
;TestProc20 endp
;
;; Standard PROC
;TestProc PROC FRAME a:DWORD, b:REAL4
;
;	movss xmm10,b
;	  
;	ret	
;TestProc ENDP
;
;; TEST: m128 and m256 local types.
;TestProc2 PROC FRAME a:DWORD, b:QWORD
;	LOCAL bob2:__m256
;	LOCAL bob:__m128
;	
;	movaps xmm0,bob    ;this should be fine.
;	vmovaps xmm0,bob   ;so should this.
;	vmovups ymm2,bob2  ;this should be fine always.
;	
;	mov eax,a
;	mov rdi,b
;	
;	ret	
;TestProc2 ENDP
;
;TestProc3 PROC VECTORCALL FRAME uses  xmm7 ymm8 rbx a:DWORD, b:REAL4, cc:__m128
;	LOCAL dummy:QWORD
;
;	Mov eax,a   ; this will work.. a will = [rsp+n]  … although smart people would probably just use ecx knowing the argument order…
;	mov dummy,rax
;	
;	;In fastcall b would have been in xmm0, but under vectorcall it's position dependant so would be xmm1
;	movss xmm10,b          ;
;
;;	mov rax,cc ; this still needs a QWORD PTR ?
;	mov rax,qword ptr cc
;	movups xmm11,[rax]  ;
;
;	mov rax,dummy
;	
;	ret
;TestProc3 ENDP
;
;TestProc4 PROC VECTORCALL FRAME a:hfa2
;
;	vmovups xmm0,a ; ensure that a is used to verify it's written correct to shadow space.
;	
;	ret
;TestProc4 ENDP
;
;TestProc8 PROC VECTORCALL FRAME a:hfa5
;
;	vmovups xmm0,a ; ensure that a is used to verify it's written correct to shadow space.
;	
;	ret
;TestProc8 ENDP
;
;
;TestProc9 PROC VECTORCALL FRAME a:hfa6
;
;	vmovups xmm0,a ; ensure that a is used to verify it's written correct to shadow space.
;	
;	ret
;TestProc9 ENDP
;
;
;TestProc10 PROC VECTORCALL FRAME a:hfa7
;
;	vmovups xmm0,a ; ensure that a is used to verify it's written correct to shadow space.
;	
;	ret
;TestProc10 ENDP
;
;
;TestProc11 PROC VECTORCALL FRAME a:DWORD, b:REAL4, cc:__m128, d:__m128, e:hva2, f:__m128f
;
;	ret
;TestProc11 ENDP
;
;TestProc12 PROC VECTORCALL FRAME a:hfa4, b:hfa4
;
;	; In this case, a should have come through in xmm0-xmm3
;	mov rax,a
;	vmovss xmm9,[rax]
;	vmovss xmm10,[rax+4]
;	vmovss xmm11,[rax+8]
;	vmovss xmm12,[rax+12]
;	
;	; b should have been passed by reference in rdx
;	mov rax,b
;	vmovss xmm9,[rax]
;	vmovss xmm10,[rax+4]
;	vmovss xmm11,[rax+8]
;	vmovss xmm12,[rax+12]	
;	
;	vmovss xmm9,[rdx]
;	vmovss xmm10,[rdx+4]
;	vmovss xmm11,[rdx+8]
;	vmovss xmm12,[rdx+12]
;		
;	ret
;TestProc12 ENDP
;
;TestProc13 PROC VECTORCALL FRAME a:hfa4, b:REAL4, cc:REAL4, d:REAL4
;
;	ret
;TestProc13 ENDP
;
;TestProc14 PROC VECTORCALL FRAME a:hfa4, b:DWORD, cc:DWORD, d:DWORD, e:DWORD
;	ret
;TestProc14 endp
;
;TestProc15 PROC VECTORCALL FRAME a:hfa4, b:DWORD, cc:DWORD, d:DWORD, e:DWORD, f:DWORD
;
;	mov rax,a
;	vmovss xmm9,[rax].hfa4.f0
;	vmovss xmm10,[rax].hfa4.f1
;	vmovss xmm11,[rax].hfa4.f2
;	vmovss xmm12,[rax].hfa4.f3
;	
;	mov ebx,b
;	mov ebx,cc
;	mov ebx,d
;	mov ebx,e
;	mov ebx,f
;	
;	ret
;TestProc15 endp
;
;TestProc16 PROC VECTORCALL FRAME a:DWORD, b:DWORD, cc:DWORD, d:DWORD, e:REAL4, f:REAL4, g:REAL4, h:REAL4
;	ret
;TestProc16 endp
;
;TestProc17 PROC VECTORCALL FRAME a:hfa4, b:REAL4, cc:REAL4, d:REAL4, e:REAL4
;	ret
;TestProc17 endp
;
;TestProc18 PROC VECTORCALL FRAME a:__m128f, b:DWORD, cc:DWORD, d:__m128f
;	ret
;TestProc18 endp
;
;TestProc19 PROC VECTORCALL FRAME a:hfa4, b:DWORD, cc:DWORD, d:__m128f
;	
;	mov rax,a
;	
;	ret
;TestProc19 endp
;
;TestProc5 PROC VECTORCALL FRAME a:hfa3, b:REAL4
;
;	vmovups xmm0,a  ; This ssould be bad.. as HFA3 would have been passed in xmm0, xmm1, xmm2.. as individual floats.
;	mov rdi,a       ; This shouldn't be very useful.
;	vmovss xmm0,b
;	
;	ret
;TestProc5 ENDP
;
;TestProc6 PROC VECTORCALL FRAME a:hfa4
;
;	vmovups xmm0,a ;ensure that a is used so is written to shadow space.
;	
;	ret
;TestProc6 ENDP
;
;TestProc7 PROC VECTORCALL FRAME uses  xmm7 ymm8 rbx a:DWORD, b:REAL4, cc:__m128f, e:DWORD, f:DWORD, cd:__m128
;	LOCAL dummy:QWORD
;
;	Mov eax,a   ; this will work.. a will = [rsp+n]  … although smart people would probably just use ecx knowing the argument order…
;	mov dummy,rax
;	
;	;In fastcall b would have been in xmm0, but under vectorcall it's position dependant so would be xmm1
;	movss xmm10,b          ;
;
;;	mov rax,cc ; this still needs a QWORD PTR ?
;	mov rax,qword ptr cc
;	movups xmm11,[rax]  ;
;
;	mov ebx,e
;	mov ecx,f
;	
;	mov rax,dummy
;	
;	ret
;TestProc7 ENDP
;
;TestProcHVA1 PROC VECTORCALL FRAME uses rbx rsi a:hva2
;
;	ret
;TestProcHVA1 ENDP
;
;TestProcHVA2 PROC VECTORCALL FRAME a:hva4
;
;	vmovups xmm0,a
;		
;	ret
;TestProcHVA2 ENDP
;
;
;TestProcHVA3 PROC VECTORCALL FRAME uses rdi a:hva22
;
;	ret
;TestProcHVA3 ENDP
;
;TestProcHVA4 PROC VECTORCALL FRAME a:hva42
;
;	vmovups ymm7,a
;	
;	ret
;TestProcHVA4 endp
;
;TestProcHVA5 PROC VECTORCALL FRAME a:hva3
;
;	vmovups ymm7,a
;	
;	ret
;TestProcHVA5 endp
;
;TestProcHVA1x PROC VECTORCALL FRAME uses rbx rsi i:DWORD, a:hva2
;
;	ret
;TestProcHVA1x ENDP
;
;TestProcHVA2x PROC VECTORCALL FRAME i:DWORD, a:hva4
;
;	vmovups xmm0,a
;		
;	ret
;TestProcHVA2x ENDP
;
;
;TestProcHVA3x PROC VECTORCALL FRAME uses rdi i:DWORD, a:hva22
;
;	ret
;TestProcHVA3x ENDP
;
;TestProcHVA4x PROC VECTORCALL FRAME i:DWORD, a:hva42
;
;	vmovups ymm7,a
;	
;	ret
;TestProcHVA4x endp
;
;TestProcHVA5x PROC VECTORCALL FRAME i:DWORD, a:REAL4, b:REAL8, cc:REAL4, d:hva42
;
;	mov eax,i
;	vmovss xmm9,a
;	vmovsd xmm10,b
;	vmovss xmm11,cc
;	
;	vmovups ymm12,d.a
;	vmovups ymm13,d.b
;	vmovups ymm14,d.cc
;	vmovups ymm15,d.d
;	
;	ret
;TestProcHVA5x endp
;
;TestProc22 PROC VECTORCALL FRAME a:DWORD, b:REAL4, cc:hfa4, d:hfa4
;
;	mov rax,d     ;d should already be in r9
;	vmovss xmm11,[rax].hfa4.f0
;	vmovss xmm11,[rax].hfa4.f1
;	vmovss xmm11,[rax].hfa4.f2
;	vmovss xmm11,[rax].hfa4.f3
;	
;	mov ebx,a
;	vmovss xmm11,b
;	mov rax,cc
;	vmovss xmm11,[rax].hfa4.f0
;	vmovss xmm11,[rax].hfa4.f1
;	vmovss xmm11,[rax].hfa4.f2
;	vmovss xmm11,[rax].hfa4.f3
;	
;	ret
;TestProc22 endp
;
;TestProc23 PROC VECTORCALL FRAME a:DWORD, b:REAL4, c1:__m128, c2:__m128,c3:__m128,c4:__m128,c5:__m128
;
;	mov eax,a
;	vmovss xmm9,b
;	
;	mov rax,c1
;	vmovaps xmm0,[rax]
;	mov rax,c2
;	vmovaps xmm1,[rax]
;	mov rax,c3
;	vmovaps xmm2,[rax]
;	mov rax,c4
;	vmovaps xmm3,[rax]
;	mov rax,c5
;	vmovaps xmm5,[rax]
;	
;	ret
;TestProc23 endp
;
;
;TestProc24 PROC VECTORCALL FRAME a:DWORD, b:REAL4, c1:__m128, c2:__m128,c3:__m128,c4:__m128,c5:__m128, c6:__m128f
;
;	mov eax,a
;	vmovss xmm9,b
;	
;	mov rax,c1
;	vmovaps xmm0,[rax]
;	mov rax,c2
;	vmovaps xmm1,[rax]
;	mov rax,c3
;	vmovaps xmm2,[rax]
;	mov rax,c4
;	vmovaps xmm3,[rax]
;	mov rax,c5
;	vmovaps xmm5,[rax]
;	
;	ret
;TestProc24 endp
;
;TestProc25 PROC VECTORCALL FRAME a:DWORD, b:REAL4, cc:__m128f, d:__m128
;
;	mov rax,cc
;	vmovaps xmm0,[rax]
;	mov rax,d
;	vmovaps xmm1,[rax]
;	
;	ret
;TestProc25 ENDP
;
;TestProc26 PROC FRAME a:REAL4, b:REAL4, cc:QWORD, d:VARARG
;
;	ret
;TestProc26 ENDP
;
;
;AddColorStop PROC FRAME USES rbx rdx rsi pGradient:PTR Gradient, position:REAL4, color:DWORD
;
;	ret
;AddColorStop ENDP
;
;InitGradient PROC FRAME USES rbx rsi pGradient:PTR Gradient, stops:DWORD, pad0:DWORD, pad1:DWORD, stopData:VARARG
;
;	mov rsi,pGradient
;	invoke AddColorStop, pGradient, [rsi], [rsi+4]
;	
;	ret	
;InitGradient ENDP


end MainCRT
