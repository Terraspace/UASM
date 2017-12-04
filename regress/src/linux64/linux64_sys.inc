
; http://nullprogram.com/blog/2015/05/15/
; http://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/

; sys/syscall.h
SYS_write  = 1
SYS_mmap   = 9
SYS_munmap = 11
SYS_clone  = 56
SYS_exit   = 60

; unistd.h
STDIN  = 0
STDOUT = 1
STDERR = 2

; sched.h
CLONE_VM	= 0x00000100
CLONE_FS	= 0x00000200
CLONE_FILES	= 0x00000400
CLONE_SIGHAND	= 0x00000800
CLONE_PARENT	= 0x00008000
CLONE_THREAD	= 0x00010000
CLONE_IO	= 0x80000000

; sys/mman.h
MAP_GROWSDOWN	= 0x00100		;/* Stack-like segment.  */
MAP_DENYWRITE	= 0x00800		;/* ETXTBSY */
MAP_EXECUTABLE	= 0x01000		;/* Mark it as an executable.  */
MAP_LOCKED	= 0x02000		;/* Lock the mapping.  */
MAP_NORESERVE	= 0x04000		;/* Don't check for reservations.  */
MAP_POPULATE	= 0x08000		;/* Populate (prefault) pagetables.  */
MAP_NONBLOCK	= 0x10000		;/* Do not block on IO.  */
MAP_STACK	= 0x20000		;/* Allocation is for a stack.  */
MAP_HUGETLB	= 0x40000		;/* Create huge page mapping.  */
MAP_ANONYMOUS	= 0x0020

MAP_SHARED      = 0x0001
MAP_PRIVATE	= 0x0002

PROT_READ	= 0x1
PROT_WRITE	= 0x2
PROT_EXEC	= 0x4
PROT_NONE       = 0x0

THREAD_FLAGS = CLONE_VM OR CLONE_FS OR CLONE_FILES OR CLONE_SIGHAND OR CLONE_PARENT OR CLONE_THREAD OR CLONE_IO

STACK_SIZE = (4096 * 1024)

.code

; void puts(char *)
puts:
	mov rsi, rdi
	mov rdx, -1
pcount:	inc rdx
	cmp byte ptr [rsi + rdx], 0
	jne pcount
	mov rdi, STDOUT
	mov rax, SYS_write
	syscall
	ret

; long thread_create(void (*)(void))
thread_create:
	push rdi
	call stack_create
	lea rsi, [rax + STACK_SIZE - 8]
	pop qword ptr [rsi]
	mov rdi, THREAD_FLAGS
	mov rax, SYS_clone
	syscall
	ret

; void *stack_create(void)
stack_create:
	xor rdi, rdi
	mov rsi, STACK_SIZE
	mov rdx, PROT_WRITE OR PROT_READ
	mov r10, MAP_PRIVATE OR MAP_ANONYMOUS OR MAP_STACK OR MAP_GROWSDOWN
	mov r8,-1
	xor r9,r9
	mov rax, SYS_mmap
	syscall
	ret

