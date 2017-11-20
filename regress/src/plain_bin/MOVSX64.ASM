
;--- test 64bit MOVSX/MOVSXD

ifdef __JWASM__
	.x64
	.model flat
endif

	.data

vb	db 0
vw	dw 0
vd	dd 0

	.code

main proc

;--- destination WORD, source  BYTE

	movsx ax,al
	movsx ax,ah
	movsx r9w,al
;	movsx r9w,ah	;not allowed
	movsx r9w,sil
	movsx  ax,[vb]
	movsx r9w,[vb]
	movsx  ax,byte ptr [ebx]
	movsx r9w,byte ptr [ebx]
	movsx  ax,byte ptr [rbx]
	movsx r9w,byte ptr [rbx]

;--- destination DWORD, source  BYTE

	movsx eax,al
	movsx r15d,al
	movsx eax,ah
;	movsx r15d,ah	;not allowed
	movsx r15d,sil
	movsx  eax,[vb]
	movsx r15d,[vb]
	movsx  eax,byte ptr [ebx]
	movsx r15d,byte ptr [ebx]
	movsx  eax,byte ptr [rbx]
	movsx r15d,byte ptr [rbx]

;--- destination DWORD, source  WORD

	movsx eax,ax
	movsx r15d,ax
	movsx eax,r9w
	movsx r15d,r9w
	movsx  eax,[vw]
	movsx r15d,[vw]
	movsx  eax,word ptr [ebx]
	movsx r15d,word ptr [ebx]
	movsx  eax,word ptr [rbx]
	movsx r15d,word ptr [rbx]

;--- destination QWORD, source  BYTE

	movsx rax,al
	movsx r15,al
;	movsx rax,ch		;not allowed
	movsx rax,sil
	movsx rax,[vb]
	movsx r15,[vb]
	movsx rax,byte ptr [ebx]
	movsx r15,byte ptr [ebx]
	movsx rax,byte ptr [rbx]
	movsx r15,byte ptr [rbx]

;--- destination QWORD, source  WORD

	movsx rax,cx
	movsx r15,cx
	movsx rax,r8w
	movsx r15,r8w
	movsx rax,[vw]
	movsx r15,[vw]
	movsx rax,word ptr [ebx]
	movsx r15,word ptr [ebx]
	movsx rax,word ptr [rbx]
	movsx r15,word ptr [rbx]

;--- destination QWORD, source  DWORD

;	movsx rax,eax	;rejected
	movsxd rax,ecx
	movsxd r15,ecx
	movsxd rax,r8d
	movsxd r15,r8d
	movsxd rax,[vd]
	movsxd r15,[vd]
	movsxd rax,dword ptr [ebx]
	movsxd r15,dword ptr [ebx]
	movsxd rax,dword ptr [rbx]
	movsxd r15,dword ptr [rbx]
	ret

main endp

    END
