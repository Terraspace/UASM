
; Structure Sizes 1-9 test case for 64bit.
; 1,2,4,8 should be passed in register, all other sizes as reference.

.x64
option win64:8
option stackbase:rbp

StructA STRUCT
	val1 db ?
StructA ENDS

StructB STRUCT
	val1 dw ?
StructB ENDS

StructC STRUCT
	val1 db ?
	val2 dw ?
StructC ENDS

StructD STRUCT
	val1 dd ?
StructD ENDS

StructE STRUCT
	val1 dd ?
	val2 db ?
StructE ENDS

StructF STRUCT
	val1 dd ?
	val2 dw ?
StructF ENDS

StructG STRUCT
	val1 dd ?
	val2 dw ?
	val3 db ?
StructG ENDS

StructH STRUCT
	val1 dq ?
StructH ENDS

StructI STRUCT
	val1 dq ?
	val2 db ?
StructI ENDS

Start  PROTO
SProc1 PROTO :StructA
SProc2 PROTO :StructB
SProc3 PROTO :StructC
SProc4 PROTO :StructD
SProc5 PROTO :StructE
SProc6 PROTO :StructF
SProc7 PROTO :StructG
SProc8 PROTO :StructH
SProc9 PROTO :StructI

GSProc1 PROTO :StructA
GSProc2 PROTO :StructB
GSProc3 PROTO :PTR
GSProc4 PROTO :StructD
GSProc5 PROTO :PTR StructE
GSProc6 PROTO :PTR StructF
GSProc7 PROTO :PTR
GSProc8 PROTO :StructH
GSProc9 PROTO :PTR

.data

s1 StructA <?>
s2 StructB <?>
s3 StructC <?>
s4 StructD <?>
s5 StructE <?>
s6 StructF <?>
s7 StructG <?>
s8 StructH <?>
s9 StructI <?>

.code

Start PROC FRAME

; GOOD
	invoke GSProc1, s1
	invoke GSProc2, s2
	invoke GSProc3, ADDR s3
	invoke GSProc4, s4
	invoke GSProc5, ADDR s5
	invoke GSProc6, ADDR s6
	invoke GSProc7, ADDR s7
	invoke GSProc8, s8
	invoke GSProc9, ADDR s9

; BAD
	invoke SProc1, s1
	invoke SProc2, s2
	invoke SProc3, s3
	invoke SProc4, s4
	invoke SProc5, s5
	invoke SProc6, s6
	invoke SProc7, s7
	invoke SProc8, s8
	invoke SProc9, s9 ; Not ideal, but allowed by UASM 2.48 and lower
	
	
	ret
Start ENDP

GSProc1 PROC strt:StructA
	; strt by value
	mov al,strt
	ret
GSProc1 ENDP

GSProc2 PROC strt:StructB
	; strt by value
	mov ax,strt
	ret
GSProc2 ENDP

GSProc3 PROC strt:PTR
	; strt by reference!!!! USE ADDR
	mov rax,strt
	ret
GSProc3 ENDP

GSProc4 PROC strt:StructD
	; strt by value
	mov eax,strt
	ret
GSProc4 ENDP

GSProc5 PROC strt:PTR StructE
	; strt by reference!!!! USE ADDR
	mov rax,strt
	ret
GSProc5 ENDP

GSProc6 PROC strt:PTR StructF
	; strt by reference!!!! USE ADDR
	mov rax,strt
	ret
GSProc6 ENDP

GSProc7 PROC strt:PTR
	; strt by reference!!!! USE ADDR
	mov rax,strt
	ret
GSProc7 ENDP

GSProc8 PROC strt:StructH
	; strt by value
	mov rax,strt
	ret
GSProc8 ENDP

GSProc9 PROC strt:PTR
	; strt by reference!!!! (>9 is compatible with UASM 2.48 and lower)
	mov rax,strt
	ret
GSProc9 ENDP

SProc1 PROC strt:StructA
	; strt by value
	mov al,strt
	ret
SProc1 ENDP

SProc2 PROC strt:StructB
	; strt by value
	mov ax,strt
	ret
SProc2 ENDP

SProc3 PROC strt:StructC
	; strt by reference!!!! ERROR
	ret
SProc3 ENDP

SProc4 PROC strt:StructD
	; strt by value
	mov eax,strt
	ret
SProc4 ENDP

SProc5 PROC strt:StructE
	; strt by reference!!!! ERROR
	ret
SProc5 ENDP

SProc6 PROC strt:StructF
	; strt by reference!!!! ERROR
	ret
SProc6 ENDP

SProc7 PROC strt:StructG
	; strt by reference!!!! ERROR
	ret
SProc7 ENDP

SProc8 PROC strt:StructH
	; strt by value
	mov rax,strt
	ret
SProc8 ENDP

SProc9 PROC strt:StructI
	; strt by reference!!!! (>9 is compatible with UASM 2.48 and lower)
	mov rax,strt
	ret
SProc9 ENDP

END Start
