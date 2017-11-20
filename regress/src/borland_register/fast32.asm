
.686p
.model flat,BORLAND
option casemap:none
.mmx
.xmm

.data 
myreal REAL8 1.2

source db 'delphi is fun',0

TmyRecord struct
   myArray  real4 129 dup (?) ; not used
   myInt    sdword ?          ; not used
   myResult real4 ?           ; for the exercise we are only interested  in this
   myBigInt qword ?           ; not used
TmyRecord ends
    
res TmyRecord <>

.data?
destiny db 64 dup(?)

FP4 macro value:REQ
  local vname
  .data
  align 4
  vname REAL4 value
  .code
  exitm <vname>
endm

.code

   proc7 proc public val1 : sword
   mov cx, val1 ; Error A2048: Operands must be the same size: 2 - 4
   ret
   proc7 endp
   
   proc8 proc public val1 : sbyte
   mov cl, val1 ; Error A2048: Operands must be the same size: 1 - 4
   ret
   proc8 endp

; function proc1(float1:single; int1:integer; float2:single; int2:integer; float3:single):TmyRecord;register;external;
; Large structures are sent by reference.
; See Note 1 below
; The exercise is to calculate (float1*float2*float3) * (int1*int2) and return result into some member of the structure
procX proc public float1 :real4, int1:sdword, float2:real4, int2:sdword, float3:real4, retVal:ptr
   movss xmm0, float1 ; all floats came displaced because retVal was pushed on the stack
   movss xmm1, float2 ; ditto
   movss xmm2, float3 ; ditto
   mulss xmm0, xmm1
   mulss xmm0, xmm2
   cvtsi2ss xmm3, int1
   cvtsi2ss xmm4, int2
   mulss xmm0, xmm3
   mulss xmm0, xmm4
   mov eax, retVal ; We expected retVal to come in ECX but it arrives in the stack. See Note 2
   assume eax : ptr TmyRecord
   movss [eax].myResult, xmm0
   ret
procX endp
   
   
proc3 proc BORLAND public Val1:dword, Val2:word, Val3:byte, Val4:word
	mov eax,Val1
	mov bx,Val2
	mov cl,Val3
	ret
proc3 endp

proc2 proc BORLAND public Val1:dword, Val2:real4, Val3:dword, Val4:dword
	mov eax, Val1
	add eax, Val2
	add eax, Val3
	add eax, Val4
	ret
proc2 endp

proc4 proc BORLAND public Val1:dword, Val2:dword, Val3:dword, Val4:dword
	mov eax, Val1
	add eax, Val2
	add eax, Val3
	add eax, Val4
	ret
proc4 endp

proc5 proc BORLAND public Val1:dword, Val2:real8, Val3:dword, Val4:dword
	mov eax, Val1
	fld Val2
	add eax, Val3
	add eax, Val4
	ret
proc5 endp

CopyString PROC public  USES ebx cnt:PTR,dest:DWORD,src:DWORD,num:PTR
    mov ebx,num
    mov ecx,src
    mov edx,dest
    mov ebx,cnt
@@:
    movzx   ebx,BYTE PTR [ecx+eax]
    mov     BYTE PTR [edx+eax],bl
    sub     eax,1
    jns     @b
    ret
CopyString  ENDP

CopyString2 PROC public  USES ebx cnt:DWORD,dest:PTR,src:DWORD,num:PTR
    mov ebx,num
    mov ecx,src
    mov edx,dest
    mov ebx,cnt
@@:
    movzx   ebx,BYTE PTR [ecx+eax]
    mov     BYTE PTR [edx+eax],bl
    sub     eax,1
    jns     @b
    ret
CopyString2  ENDP

proc6 proc BORLAND public Val1:dword, Val2:dword, Val3:dword, Val4:dword, val5:dword, val6:dword, val7:dword
	mov eax, Val1
	add eax, Val2
	add eax, Val3
	add eax, Val4
	add eax, val5
	add eax, val6
	add eax, val7
	ret
proc6 endp

WinMainCRTStartup proc uses EBX
local bob:DWORD
local bob1:DWORD

	invoke proc7,-20
	invoke proc8,-10
	invoke proc6,1, 2, 3, 4, 5, 6, 7
	invoke procX, 2.5, 5, 3.2, 7, 3.5, ADDR res
	
    mov bob,15
	invoke proc3,1,2,3,4
	invoke proc5,OFFSET myreal,23.45,3,5
    invoke proc2,OFFSET myreal,1.2, 3, 4
    invoke CopyString,ADDR bob1,OFFSET destiny,OFFSET source,ADDR bob
    invoke CopyString2,10,ADDR destiny,OFFSET source,ADDR bob
	invoke proc4,1,2,3,4
	invoke proc4,1,2,3,4000	
	invoke proc5,OFFSET myreal,myreal,3,5
	
mov eax,LOW32(2.5)
mov eax,HIGH32(2.5)
	
    ret
WinMainCRTStartup endp

END
