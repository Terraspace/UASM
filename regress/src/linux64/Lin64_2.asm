;--- "hello world" for 64-bit Linux, using SYSCALL and SYSVCALL convention.
;--- assemble: HJWasm -elf64 -Fo=Lin64_2.o Lin64_2.asm
;--- link:     gcc Lin64_2.o -o Lin64_2
;---           ld -o Lin64_2  -dynamic-linker /lib64/l4.so.2   /usr/lib/x86_64-linux-gnu/crt1.o   /usr/lib/x86_64-linux-gnu/crti.o   -lc Lin64_2.o   /usr/lib/x86_64-linux-gnu/crtn.o

OPTION LITERALS:ON

stdout    equ 1
SYS_WRITE equ 1
SYS_EXIT  equ 60

malloc PROTO SYSTEMV memSize:QWORD
free   PROTO SYSTEMV memPtr:QWORD

WriteToConsole PROTO SYSTEMV pString:PTR, strLen:DWORD, outHandle:DWORD

.data

aMsg db 10,"This is text!",10,0

.code

main PROC SYSTEMV
    MEMALLOC(200)
    MEMFREE(rax)
    invoke WriteToConsole, ADDR aMsg, 15, stdout
    invoke WriteToConsole, "Hello, world!", 15, stdout
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