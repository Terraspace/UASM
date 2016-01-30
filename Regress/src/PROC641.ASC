
;--- check xmm auto register saving

if 0;def __JWASM__
	.x64
	.model flat,fastcall
endif

	option casemap:none
	option frame:auto

	.CODE

;--- 2 GPRs, 1 xmm

p01 proc FRAME uses rbx rsi xmm6
	ret
p01 endp

p02 proc FRAME uses rbx rsi xmm6
local lcl1:DWORD
	mov eax, lcl1
	ret
p02 endp

p03 proc FRAME uses rbx rsi xmm6
local lcl1:QWORD
	mov rax, lcl1
	ret
p03 endp

p04 proc FRAME uses rbx rsi xmm6
local lcl1:OWORD
	movdqa xmm6, lcl1
	ret
p04 endp

;--- 3 GPRs, 1 xmm

p11 proc FRAME uses rbx rsi rdi xmm6
	ret
p11 endp

p12 proc FRAME uses rbx rsi rdi xmm6
local lcl1:DWORD
	mov eax, lcl1
	ret
p12 endp

p13 proc FRAME uses rbx rsi rdi xmm6
local lcl1:QWORD
	mov rax, lcl1
	ret
p13 endp

p14 proc FRAME uses rbx rsi rdi xmm6
local lcl1:OWORD
	movdqa xmm6, lcl1
	ret
p14 endp

;--- second proc with 2 GPRs, 1 xmm

p21 proc FRAME uses rbx rsi xmm6
	ret
p21 endp

p22 proc FRAME uses rbx rsi xmm6
local lcl1:DWORD
	mov eax, lcl1
	ret
p22 endp

p23 proc FRAME uses rbx rsi xmm6
local lcl1:QWORD
	mov rax, lcl1
	ret
p23 endp

p24 proc FRAME uses rbx rsi xmm6
local lcl1:OWORD
	movdqa xmm6, lcl1
	ret
p24 endp

;--- 2 GPRs, 2 xmms

p31 proc FRAME uses rbx rsi xmm6 xmm7
	ret
p31 endp

p32 proc FRAME uses rbx rsi xmm6 xmm7
local lcl1:DWORD
	mov eax, lcl1
	ret
p32 endp

p33 proc FRAME uses rbx rsi xmm6 xmm7
local lcl1:QWORD
	mov rax, lcl1
	ret
p33 endp

p34 proc FRAME uses rbx rsi xmm6 xmm7
local lcl1:OWORD
	movdqa xmm6, lcl1
	ret
p34 endp

	END
