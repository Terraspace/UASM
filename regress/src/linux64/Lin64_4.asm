;------------------------------------------------------------------------------------------------------------------
; Socket Server Example for Linux 64
;
; -> errno reporting via GLIBC is based on Ubuntu method. Refer to your errno.h if different.
; Test with: echo "some data" | nc 127.0.0.1 5000
; https://github.com/cyrus-and/gdb-dashboard (An indispensable addition to make GDB less awful)
; Assemble: ./uasm -elf64 Lin64_4.asm
; Link:     gcc -o Lin64_4 Lin64_4.o
;------------------------------------------------------------------------------------------------------------------

OPTION LITERALS:ON

; Include libc and sockets headers
;********************************************************************************************
include libc.inc
include linux64_sys.inc
include socket.inc

; Declare our procedures
;********************************************************************************************
SocketStartup  PROTO
ClientHandler  PROTO clientfd:DWORD

;********************************************************************************************
; DATA SECTION
;********************************************************************************************
.data

listenfd    dd          0
serv_addr   sockaddr_in <?>
client_addr sockaddr    <?>
MAX_CONN    =           100
threadMsg   db "In thread handler..",10,0

;********************************************************************************************
; CODE SECTION
;********************************************************************************************
.code

main PROC
    invoke printf, "Starting Socket Server..\n"
    invoke SocketStartup
    invoke exit,0
    ret
main ENDP

SocketStartup PROC
	LOCAL addrLen:QWORD
	LOCAL clientfd:DWORD

	invoke socket, AF_INET, SOCK_STREAM, 0
	.if(sdword ptr eax == -1)
		invoke printf, CStr("Failed to create socket: %d",10), eax
		ret
	.endif
	mov listenfd, eax

	lea rdi, serv_addr
	xor eax,eax
	mov ecx, sizeof(serv_addr)
	rep stosb

	mov serv_addr.sin_family, AF_INET
	mov serv_addr.sin_addr.s_addr,INADDR_ANY
	mov ax,5000
	xchg al,ah
	mov serv_addr.sin_port,ax

	invoke bind, listenfd, ADDR serv_addr, sizeof(serv_addr)
	.if(sdword ptr eax == -1)
		invoke __errno_location
		mov r10d,[rax]
		invoke printf, CStr("Failed to bind socket: %d error: %d",10), listenfd, r10d
		ret
	.endif

	invoke listen, listenfd, MAX_CONN
	.if(sdword ptr eax == -1)
		invoke printf, CStr("Faild to listen to socket: %d error: %d",10), listenfd, eax
		ret
	.endif

	.while(1)
		mov addrLen,sizeof(client_addr)
		invoke accept, listenfd, ADDR client_addr, ADDR addrLen
		.if(sdword ptr eax == -1)
			invoke __errno_location
			mov r10d,[rax]
			invoke printf, CStr("Faild to accept client connection on socket: %d error: %d",10), listenfd, r10d
			ret
		.endif
		mov clientfd,eax
		invoke printf, "Client connectioned accepted: ... %d\n",eax
		invoke ClientHandler, clientfd
	.endw

	ret
SocketStartup ENDP

ClientHandler PROC clientfd:DWORD

	LOCAL recvBuffer[16]:BYTE
	LOCAL _clientfd:DWORD	; As SystemV ABI doesn't provide home-space, the parameters when referenced by name actually refer to registers, so lets make a copy of EDI now.
	LOCAL tspec:timespec
	LOCAL startms:QWORD

	mov _clientfd,edi	

	pxor xmm0,xmm0
	movdqa recvBuffer,xmm0

	invoke clock_gettime, CLOCK_MONOTONIC, ADDR tspec
	cvtsi2ss xmm0,tspec.tv_nsec
	divss xmm0,FP4(1000000.0)
	cvttss2si rax,xmm0
	mov startms,rax
	mov rax,tspec.tv_sec
	imul rax,1000
	add startms,rax

	invoke printf, "Reading from socket fd: %d\n", _clientfd

	invoke recv, _clientfd, ADDR recvBuffer, 8, 0
	.if(sdword ptr eax == -1)
		invoke __errno_location
		mov r10d,[rax]
		invoke printf, "Error reading socket: %d\n",r10d
	.else
		invoke printf, "%s ...\n", ADDR recvBuffer
	.endif
	invoke close, _clientfd

	lea rdi,ThreadProc
	call thread_create

	invoke clock_gettime, CLOCK_MONOTONIC, ADDR tspec
	cvtsi2ss xmm0,tspec.tv_nsec
	divss xmm0,FP4(1000000.0)
	cvttss2si rax,xmm0
	mov rbx,tspec.tv_sec
	imul rbx,1000
	add rax,rbx
	sub rax,startms
	invoke printf, "Elapsed ms..%d\n",eax

	ret
ClientHandler ENDP

ThreadProc PROC
	lea rdi,threadMsg
	call puts
	mov rax, SYS_exit
	syscall
	ret
ThreadProc ENDP

end
