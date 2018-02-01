;--- "hello world" for 64-bit Linux, using SYSCALL and SYSVCALL convention.
;--- assemble: HJWasm -elf64 -Fo=Lin64_2.o Lin64_2.asm
;--- link:     ld Lin64_2.o -o Lin64_2
;---           ld -o Lin64_2  -dynamic-linker /lib64/l4.so.2   /usr/lib/x86_64-linux-gnu/crt1.o   /usr/lib/x86_64-linux-gnu/crti.o   -lc Lin64_2.o   /usr/lib/x86_64-linux-gnu/crtn.o
;              gcc -o Lin64_2 Lin64_2.o

option casemap:none
option literals:on
option win64:7

stdout    equ 1
SYS_WRITE equ 1
SYS_EXIT  equ 60

malloc PROTO SYSTEMV memSize:QWORD
free   PROTO SYSTEMV memPtr:QWORD
WriteToConsole PROTO SYSTEMV pString:PTR, strLen:DWORD, outHandle:DWORD

;=====================================================================================================================================================
;	
; CLASS Definition inclusion guard.
;
;=====================================================================================================================================================
IFNDEF _CLASS_PERSON_
_CLASS_PERSON_ EQU 1

OINTERFACE Entity
	CVIRTUAL PrintName, <VOIDARG>
	CVIRTUAL SetName, <VOIDARG>
ENDMETHODS
ENDOINTERFACE

;---------------------------------------------------------------------------------------------------------------
; Define our Person class with 2 instance methods, 1 static method and 3 member fields.
;---------------------------------------------------------------------------------------------------------------
CLASS Person
	CMETHOD PrintName
	CMETHOD SetName
	CSTATIC IsHuman
ENDMETHODS
	pName   dq 0
	age     db 0
	human   db 0	
	handle  dq 0
ENDCLASS

; A Pointer to Object type.
pPerson TYPEDEF PTR Person

;---------------------------------------------------------------------------------------------------------------
; Constructor
; Can take optional arguments.
;---------------------------------------------------------------------------------------------------------------
METHOD Person, Init, <VOIDARG>, <USES rbx r10>, age:BYTE, ptrName:PTR
	LOCAL isAlive:DWORD
	ret
ENDMETHOD

;---------------------------------------------------------------------------------------------------------------
; Destructor
; Takes no arguments.
;---------------------------------------------------------------------------------------------------------------
METHOD Person, Destroy, <VOIDARG>, <>
	mov [rdi].age,0
	ret
ENDMETHOD

;---------------------------------------------------------------------------------------------------------------
; Print the persons name to the console.
;---------------------------------------------------------------------------------------------------------------
METHOD Person, PrintName, <VOIDARG>, <USES rbx>
	invoke WriteToConsole, ADDR aMsg, 15, stdout
	ret
ENDMETHOD

;---------------------------------------------------------------------------------------------------------------
; Set person name.
;---------------------------------------------------------------------------------------------------------------
METHOD Person, SetName, <VOIDARG>, <USES rbx>, pNameStr:QWORD
	mov rax,pNameStr
	mov [rdi].pName,rax
	ret
ENDMETHOD

;---------------------------------------------------------------------------------------------------------------
; Static method to check if a person is a human.
;---------------------------------------------------------------------------------------------------------------
STATICMETHOD Person, IsHuman, <qword>, <USES rbx>, somebody:PTR Person
	ret
ENDMETHOD

ENDIF

.data

aMsg db 10,"This is text!",10,0
person1 pPerson 0		; A global variable to hold a reference to a Person type.

.code

main PROC SYSTEMV
    MEMALLOC(200)
    MEMFREE(rax)
    invoke WriteToConsole, "Hello, world!", 15, stdout
    mov person1, _NEW(Person, 30, "Jane Doe")
    _INVOKE Person, PrintName, person1		; Direct call (Type, Method, arguments)
    _DELETE(person1)
    mov eax, SYS_EXIT
    syscall
    ret
main ENDP

WriteToConsole PROC SYSTEMV pString:PTR, strLen:DWORD, outHandle:DWORD
    LOCAL handle:DWORD
    mov handle, outHandle ; this is allowed as outHandle evaluates as a register operand.
    mov edx, strLen
    mov rsi, pString
    mov edi, handle
    mov eax, SYS_WRITE
    syscall
    ret
WriteToConsole ENDP

end
