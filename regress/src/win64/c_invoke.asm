
.x64
option literals:on
option frame:auto
option casemap:none
option stackbase:rbp
option win64:7

includelib kernel32.lib
ExitProcess PROTO :dword
printf      PROTO :ptr, :vararg

MYTYPE TYPEDEF QWORD

MyProc  PROTO (dword) :dword, :qword
MyProc2 PROTO :PTR
MyProc3 PROTO (dword)
MyProc4 PROTO
MyProc5 PROTO (real4) :real4
MyProc6 PROTO (byte) :byte
MyProc7 PROTO (dword) :byte, :word, :dword, :qword, :real4, :qword
MyProc8 PROTO (byte)
MyProc9 PROTO (real4) :byte, :word, :dword, :qword, :real4, :qword
MyProc10 PROTO (dword) :REAL4, :QWORD
MyProc11 PROTO (real4)
MyProc12 PROTO (MYTYPE)
MyProc13 PROTO :dword, :dword
MyProc14 PROTO (qword) :dword, :dword

.data

myVar  dd 11
myVar2 dq 21

nameString db "Mr Bubbles",0

.code

start:

	; This case should generate an error of MAX CALLS allowed.
	;.if( MyProc(10,20) == MyProc3() )
   	;   xor eax,eax
	;.endif

	.if ( MyProc6( MyProc8() ) == 7 )
	   xor eax,eax
	.endif

	mov eax,MyProc(10, 20)
	lea rsi,myVar
	mov eax,[rsi + MyProc12()]
	mov myVar,MyProc(11,12)
	mov myVar2,MyProc12()
	vmovaps xmm1,MyProc5(1.0)

	MyProc3()
	MyProc(10,20)
	MyProc(10,ADDR MyProc)
	MyProc2("this is a literal")

	; Test C-Style Address-Of operator
	MyProc2(&nameString)

	.if( MyProc(10,20) == 30 )
	   xor eax,eax
	.endif

	.if( MyProc5(1.0) == FP4(2.0) )
	   xor eax,eax
	.endif

	.if ( MyProc6(7) == 7 )
	   xor eax,eax
	.endif

	MyProc(MyProc3(), 20)	
	MyProc(10, MyProc4())	
	MyProc(MyProc3(), MyProc4())
	MyProc(MyProc3(), MyProc2("stringy"))

	MyProc10(MyProc11(), MyProc2("stringy"))

	MyProc7( 10, 20, myVar, myVar2, 2.0, 30 )

	MyProc( MyProc( MyProc3(), 10 ), 20)	

	.if ( MyProc6( MyProc8() ) == 7 )
	   xor eax,eax
	.endif

	MyProc7( 10, 20, myVar, myVar2,	MyProc9( 10, 20, myVar, myVar2, 2.0, 30 ), 30 )

	MyProc7( 10, 
		 20, 
		 myVar, 
		 myVar2, 
		 2.0, 
		 30 )

	invoke ExitProcess,0

MyProc PROC (dword) aVar:DWORD, bVar:QWORD
   movsxd rax,aVar
   add rax,bVar
   ret
MyProc ENDP

MyProc2 PROC FRAME strPtr:PTR
   mov eax,10
   printf("a formatted string : %d \n", eax)
   printf(strPtr)
   ret
MyProc2 ENDP

MyProc3 PROC (dword) FRAME 
   mov eax,10
   ret
MyProc3 ENDP

MyProc4 PROC FRAME
   mov eax,20
   ret
MyProc4 ENDP

MyProc5 PROC (real4) FRAME aVar:REAL4
   mov eax,1.0
   vmovd xmm1,eax
   vaddss xmm0,xmm0,xmm1
   ret
MyProc5 ENDP

MyProc6 PROC (byte) FRAME aVar:BYTE
   xor al,al
   add al,cl
   ret
MyProc6 ENDP

MyProc7 PROC (dword) FRAME aVar:byte, bVar:word, cVar:dword, dVar:qword, eVar:real4, fVar:qword
   mov eax,1
   ret
MyProc7 ENDP

MyProc8 PROC (byte) FRAME
   mov al,7
   ret
MyProc8 ENDP

MyProc9 PROC (real4) FRAME aVar:byte, bVar:word, cVar:dword, dVar:qword, eVar:real4, fVar:qword
   LOADSS xmm0,2.5
   ret
MyProc9 ENDP

MyProc10 PROC FRAME aVar:REAL4, bVar:QWORD
   xor rax,rax
   ret
MyProc10 ENDP

MyProc11 PROC (real4) FRAME 
   LOADSS xmm0,3.0
   ret
MyProc11 ENDP

MyProc12 PROC (MYTYPE) FRAME 
   xor rax,rax
   ret
MyProc12 ENDP

; Default for un-typed arguments
MyProc13 PROC FRAME aVar, bVar
   xor rax,rax
   ret
MyProc13 ENDP

; Default for un-typed arguments with return and no frame
MyProc14 PROC (qword) aVar, bVar
   xor rax,rax
   ret
MyProc14 ENDP

end start
