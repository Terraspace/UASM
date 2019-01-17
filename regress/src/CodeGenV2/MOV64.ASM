
option flat:1

.data

dbVar db 10
dwVar dw 10
ddVar dd 10
dqVar dq 10

.code

	use64

	;---------------------------------------------------------------------------------------------------
	; OFFSETS
	;---------------------------------------------------------------------------------------------------
	mov rax,OFFSET ddVar
	mov eax,OFFSET ddVar 
	
	;---------------------------------------------------------------------------------------------------
	; Mixed and sized immediates
	;---------------------------------------------------------------------------------------------------
	mov rax,10  ; sign-extended 32bit imm.
	mov al,10
	mov al,130
	mov cl,-25
	mov dh,120
	mov bl,0xff
	mov r10b,22
	mov ah,32
	mov ax,10
	mov ax,0x20
	mov cx,25
	mov r10w,22
	mov r8w,0x0f0f
	mov eax,10
	mov eax,0x20
	mov ecx,25
	mov r10d,22
	mov r8d,16
	mov eax,10
	mov rax,10
	mov rax,0x20
	mov rcx,25
	mov r10,22
	mov r8,16 
	mov rax,0x1234123412341234
	mov rbx,0x1234123412341234
	mov r10,0x1234123412341234
	
	; (8bit immediates)
	mov al,10
	mov al,0x20
	mov cl,25
	mov dh,120
	mov bl,01010101b
	mov r10b,22
	mov ah,32
	
	; (16bit immediates)
	mov ax,10
	mov ax,0x20
	mov cx,25
	mov r10w,22
	mov r8w,1111000011110000b
	
	; (32bit immediates)
	mov eax,10
	mov eax,0x20
	mov ecx,25
	mov r10d,22
	mov r8d,(1 SHL 4)
	mov eax,1.0
	
	; (64bit immediates)
	mov rax,10
	mov rax,0x20
	mov rcx,25
	mov r10,22
	mov r8,(1 SHL 4)
	mov rax,1.0
	mov rax,1234123412341234h
	mov rbx,1234123412341234h
	mov r10,1234123412341234h

	;---------------------------------------------------------------------------------------------------
	; Special MOFFSET mov modes
	; JWASM was wrong, 64bit does support encoding of segment registers with moffset
	;---------------------------------------------------------------------------------------------------
	movabs al,[0x00]
	movabs al,[0x0000]
	movabs al,[0x00000000]
	movabs al,[0x0000000000000000]
	movabs al,es:[0x20]
	movabs al,fs:[0x2020]
	movabs al,[0x10203040]
	movabs al,[0x1234567812345678]

	movabs [0x00],al
	movabs [0x0000],al
	movabs [0x00000000],al
	movabs [0x0000000000000000],al
	movabs es:[0x20],al
	movabs fs:[0x2020],al
	movabs [0x10203040],al
	movabs [0x1234567812345678],al

	movabs ax,[0x00]
	movabs ax,[0x0000]
	movabs ax,[0x00000000]
	movabs ax,[0x0000000000000000]
	movabs ax,es:[0x20]
	movabs ax,fs:[0x2020]
	movabs ax,[0x10203040]
	movabs ax,[0x1234567812345678]

	movabs [0x00],ax
	movabs [0x0000],ax
	movabs [0x00000000],ax
	movabs [0x0000000000000000],ax
	movabs es:[0x20],ax
	movabs fs:[0x2020],ax
	movabs [0x10203040],ax
	movabs [0x1234567812345678],ax

	movabs eax,[0x00]
	movabs eax,[0x0000]
	movabs eax,[0x00000000]
	movabs eax,[0x0000000000000000]
	movabs eax,es:[0x20]
	movabs eax,fs:[0x2020]
	movabs eax,[0x10203040]
	movabs eax,[0x1234567812345678]

	movabs [0x00],eax
	movabs [0x0000],eax
	movabs [0x00000000],eax
	movabs [0x0000000000000000],eax
	movabs es:[0x20],eax
	movabs fs:[0x2020],eax
	movabs [0x10203040],eax
	movabs [0x1234567812345678],eax

	movabs rax,[0x00]
	movabs rax,[0x0000]
	movabs rax,[0x00000000]
	movabs rax,[0x0000000000000000]
	movabs rax,es:[0x20]
	movabs rax,fs:[0x2020]
	movabs rax,[0x10203040]
	movabs rax,[0x1234567812345678]

	movabs [0x00],rax
	movabs [0x0000],rax
	movabs [0x00000000],rax
	movabs [0x0000000000000000],rax
	movabs es:[0x20],rax
	movabs fs:[0x2020],rax
	movabs [0x10203040],rax
	movabs [0x1234567812345678],rax

	;---------------------------------------------------------------------------------------------------
	; Displacement Only addressing modes
	;---------------------------------------------------------------------------------------------------
	mov cl,[0]
	mov ch,[10]
	mov ax,[32]
	mov eax,[0x100]
	mov rax,[0x1000]
	mov r8d,[20]

	mov [0],cl
	mov [10],ch
	mov [32],ax
	mov [0x100],eax
	mov [0x1000],rax
	mov [20],r8d

	;---------------------------------------------------------------------------------------------------
	; MEM/REG Combination Modes (Base/Index/Scale/Disp) 8bit
	;---------------------------------------------------------------------------------------------------

	mov [rax+rax*4+0xc80],r8b
	
	mov [rax],al
	mov [rax+rax],bl
	mov [rax+rax*4],cl
	mov [rax+32],ah
	mov [rax+rax+32],sil
	mov [rax+rax*4+32],r8b

	mov [rcx],al
	mov [rcx+rcx],bl
	mov [rcx+rcx*4],cl
	mov [rcx+32],ah
	mov [rcx+rcx+32],sil
	mov [rcx+rcx*4+32],r8b
	
	mov [rax],al
	mov [rax+rax],bl
	mov [rax+rax*4],cl
	mov [rax+32],ah
	mov [rax+rax+3200],sil
	mov [rax+rax*4+3200],r8b

	mov [rax],al
	mov [rax+rcx],bl
	mov [rax+rdx*4],cl
	mov [rbx+32],ah
	mov [rax+rdx+32],dil
	mov [rdx+rbx*4+32],r8b
	mov [rsi],al
	mov [rax+rsi],bl
	mov [rdx+rdi*4],cl
	mov [rdi+32000],ah
	mov [rax+rbp+32],sil
	mov [rsp+rbp*4+32],r8b

	mov [rax],al
	mov [rax+r8],bl
	mov [r10+rdx*4],cl
	mov [rbx+32],ah
	mov [rax+r9+32],dil
	mov [rdx+rbx*4+32],r8b
	mov [rsi],al
	mov [r12+rsi],bl
	mov [rdx+rdi*4],cl
	mov [r8+rbp+32],sil
	mov [rsp+r8*4+32],r8b
	mov [rsp+r10*4+32],r8b
	
	mov fs:[rax],al
	mov gs:[rax+rax],bl
	mov fs:[r8],al
	
	; Compatibility 32bit addressing 8bit
	mov [eax],al
	mov [ebx],ch
	
	; Basic indirect memory 8bit
	mov [rax],al
	mov [rbx],al
	mov [rcx],al
	mov [rdx],al
	mov [rsi],al
	mov [rdi],al
	mov [rsp],al
	mov [rbp],al
	mov [rip],al
	mov [r8],al
	mov [r9],al
	mov [r10],al
	mov [r11],al
	mov [r12],al
	mov [r13],al
	mov [r14],al
	mov [r15],al

	;---------------------------------------------------------------------------------------------------
	; MEM/REG Combination Modes (Base/Index/Scale/Disp) 16bit
	;---------------------------------------------------------------------------------------------------
	mov [rax+rax*4+0xc80],r8w
	
	mov [rax],ax
	mov [rax+rax],bx
	mov [rax+rax*4],cx
	mov [rax+32],ax
	mov [rax+rax+32],si
	mov [rax+rax*4+32],r8w

	mov [rcx],ax
	mov [rcx+rcx],bx
	mov [rcx+rcx*4],cx
	mov [rcx+32],ax
	mov [rcx+rcx+32],si
	mov [rcx+rcx*4+32],r8w
	
	mov [rax],ax
	mov [rax+rax],bx
	mov [rax+rax*4],cx
	mov [rax+32],ax
	mov [rax+rax+3200],si
	mov [rax+rax*4+3200],r8w

	mov [rax],ax
	mov [rax+rcx],bx
	mov [rax+rdx*4],cx
	mov [rbx+32],ax
	mov [rax+rdx+32],di
	mov [rdx+rbx*4+32],r8w
	mov [rsi],ax
	mov [rax+rsi],bx
	mov [rdx+rdi*4],cx
	mov [rdi+32000],ax
	mov [rax+rbp+32],si
	mov [rsp+rbp*4+32],r8w

	mov [rax],ax
	mov [rax+r8],bx
	mov [r10+rdx*4],cx
	mov [rbx+32],ax
	mov [rax+r9+32],di
	mov [rdx+rbx*4+32],r8w
	mov [rsi],ax
	mov [r12+rsi],bx
	mov [rdx+rdi*4],cx
	mov [r8+rbp+32],si
	mov [rsp+r8*4+32],r8w
	mov [rsp+r10*4+32],r8w
	
	mov fs:[rax],ax
	mov gs:[rax+rax],bx
	mov fs:[r8],ax
	
	; Compatibility 32bit addressing 16bit
	mov [eax],ax
	mov [ebx],cx
	
	; Basic indirect memory 16bit
	mov [rax],ax
	mov [rbx],ax
	mov [rcx],ax
	mov [rdx],ax
	mov [rsi],ax
	mov [rdi],ax
	mov [rsp],ax
	mov [rbp],ax
	mov [rip],ax
	mov [r8],ax
	mov [r9],ax
	mov [r10],ax
	mov [r11],ax
	mov [r12],ax
	mov [r13],ax
	mov [r14],ax
	mov [r15],ax

	;---------------------------------------------------------------------------------------------------
	; MEM/REG Combination Modes (Base/Index/Scale/Disp) 32bit
	;---------------------------------------------------------------------------------------------------
	mov [rax+rax*4+0xc80],r8d
	
	mov [rax],eax
	mov [rax+rax],ebx
	mov [rax+rax*4],ecx
	mov [rax+32],eax
	mov [rax+rax+32],esi
	mov [rax+rax*4+32],r8d

	mov [rcx],eax
	mov [rcx+rcx],ebx
	mov [rcx+rcx*4],ecx
	mov [rcx+32],eax
	mov [rcx+rcx+32],esi
	mov [rcx+rcx*4+32],r8d
	
	mov [rax],eax
	mov [rax+rax],ebx
	mov [rax+rax*4],ecx
	mov [rax+32],eax
	mov [rax+rax+3200],esi
	mov [rax+rax*4+3200],r8d

	mov [rax],eax
	mov [rax+rcx],ebx
	mov [rax+rdx*4],ecx
	mov [rbx+32],eax
	mov [rax+rdx+32],edi
	mov [rdx+rbx*4+32],r8d
	mov [rsi],eax
	mov [rax+rsi],ebx
	mov [rdx+rdi*4],ecx
	mov [rdi+32000],eax
	mov [rax+rbp+32],esi
	mov [rsp+rbp*4+32],r8d

	mov [rax],eax
	mov [rax+r8],ebx
	mov [r10+rdx*4],ecx
	mov [rbx+32],eax
	mov [rax+r9+32],edi
	mov [rdx+rbx*4+32],r8d
	mov [rsi],eax
	mov [r12+rsi],ebx
	mov [rdx+rdi*4],ecx
	mov [r8+rbp+32],esi
	mov [rsp+r8*4+32],r8d
	mov [rsp+r10*4+32],r8d
	
	mov fs:[rax],eax
	mov gs:[rax+rax],ebx
	mov fs:[r8],eax
	
	; Compatibility 32bit addressing 32bit
	mov [eax],eax
	mov [ebx],ecx
	
	; Basic indirect memory 32bit
	mov [rax],eax
	mov [rbx],eax
	mov [rcx],eax
	mov [rdx],eax
	mov [rsi],eax
	mov [rdi],eax
	mov [rsp],eax
	mov [rbp],eax
	mov [rip],eax
	mov [r8],eax
	mov [r9],eax
	mov [r10],eax
	mov [r11],eax
	mov [r12],eax
	mov [r13],eax
	mov [r14],eax
	mov [r15],eax

	;---------------------------------------------------------------------------------------------------
	; MEM/REG Combination Modes (Base/Index/Scale/Disp) 64bit
	;---------------------------------------------------------------------------------------------------
	mov [rax+rax*4+0xc80],r8
	
	mov [rax],rax
	mov [rax+rax],rbx
	mov [rax+rax*4],rcx
	mov [rax+32],rax
	mov [rax+rax+32],rsi
	mov [rax+rax*4+32],r8

	mov [rcx],rax
	mov [rcx+rcx],rbx
	mov [rcx+rcx*4],rcx
	mov [rcx+32],rax
	mov [rcx+rcx+32],rsi
	mov [rcx+rcx*4+32],r8
	
	mov [rax],rax
	mov [rax+rax],rbx
	mov [rax+rax*4],rcx
	mov [rax+32],rax
	mov [rax+rax+3200],rsi
	mov [rax+rax*4+3200],r8

	mov [rax],rax
	mov [rax+rcx],rbx
	mov [rax+rdx*4],rcx
	mov [rbx+32],rax
	mov [rax+rdx+32],rdi
	mov [rdx+rbx*4+32],r8
	mov [rsi],rax
	mov [rax+rsi],rbx
	mov [rdx+rdi*4],rcx
	mov [rdi+32000],rax
	mov [rax+rbp+32],rsi
	mov [rsp+rbp*4+32],r8

	mov [rax],rax
	mov [rax+r8],rbx
	mov [r10+rdx*4],rcx
	mov [rbx+32],rax
	mov [rax+r9+32],rdi
	mov [rdx+rbx*4+32],r8
	mov [rsi],rax
	mov [r12+rsi],rbx
	mov [rdx+rdi*4],rcx
	mov [r8+rbp+32],rsi
	mov [rsp+r8*4+32],r8
	mov [rsp+r10*4+32],r8
	
	mov fs:[rax],rax
	mov gs:[rax+rax],rbx
	mov fs:[r8],rax
	
	; Compatibility 32bit addressing 64bit
	mov [eax],rax
	mov [ebx],rcx
	
	; Basic indirect memory 64bit
	mov [rax],rax
	mov [rbx],rax
	mov [rcx],rax
	mov [rdx],rax
	mov [rsi],rax
	mov [rdi],rax
	mov [rsp],rax
	mov [rbp],rax
	mov [rip],rax
	mov [r8],rax
	mov [r9],rax
	mov [r10],rax
	mov [r11],rax
	mov [r12],rax
	mov [r13],rax
	mov [r14],rax
	mov [r15],rax
	
	;---------------------------------------------------------------------------------------------------
	; REG/MEM Combination Modes (Base/Index/Scale/Disp) 8bit
	;---------------------------------------------------------------------------------------------------
	mov r8b,BYTE PTR [rax+rax*4+0xc80]
	
	mov al,[rax]
	mov bl,[rax+rax]
	mov cl,[rax+rax*4]
	mov ah,[rax+32]
	mov sil,[rax+rax+32]
	mov r8b,[rax+rax*4+32]

	mov al,[rcx]
	mov bl,[rcx+rcx]
	mov cl,[rcx+rcx*4]
	mov ah,[rcx+32]
	mov sil,[rcx+rcx+32]
	mov r8b,[rcx+rcx*4+32]
	
	mov al,[rax]
	mov bl,[rax+rax]
	mov cl,[rax+rax*4]
	mov ah,[rax+32]
	mov sil,[rax+rax+3200]
	mov r8b,[rax+rax*4+3200]	

	mov al,[rax]
	mov bl,[rax+rcx]
	mov cl,[rax+rdx*4]
	mov ah,[rbx+32]
	mov dil,[rax+rdx+32]
	mov r8b,[rdx+rbx*4+32]
	mov al,[rsi]
	mov bl,[rax+rsi]
	mov cl,[rdx+rdi*4]
	mov ah,[rdi+32000]
	mov sil,[rax+rbp+32]
	mov r8b,[rsp+rbp*4+32]	

	mov al,[rax]
	mov bl,[rax+r8]
	mov cl,[r10+rdx*4]
	mov ah,[rbx+32]
	mov dil,[rax+r9+32]
	mov r8b,[rdx+rbx*4+32]
	mov al,[rsi]
	mov bl,[r12+rsi]
	mov cl,[rdx+rdi*4]
	mov sil,[r8+rbp+32]
	mov r8b,[rsp+r8*4+32]	
	mov r8b,[rsp+r10*4+32]	
	
	mov al,fs:[rax]
	mov bl,gs:[rax+rax]
	mov al,fs:[r8]
	
	; Compatibility 32bit addressing 8bit
	mov al,[eax]
	mov ch,[ebx]
	
	; Basic indirect memory 8bit
	mov al,[rax]
	mov al,[rbx]
	mov al,[rcx]
	mov al,[rdx]
	mov al,[rsi]
	mov al,[rdi]
	mov al,[rsp]
	mov al,[rbp]
	mov al,[rip]
	mov al,[r8]
	mov al,[r9]
	mov al,[r10]
	mov al,[r11]
	mov al,[r12]
	mov al,[r13]
	mov al,[r14]
	mov al,[r15]

	;---------------------------------------------------------------------------------------------------
	; Combination Modes (Base/Index/Scale/Disp) 16bit
	;---------------------------------------------------------------------------------------------------
	mov r8w,WORD PTR [rax+rax*4+0xc80]
	
	mov ax,[rax]
	mov bx,[rax+rax]
	mov cx,[rax+rax*4]
	mov ax,[rax+32]
	mov si,[rax+rax+32]
	mov r8w,[rax+rax*4+32]

	mov ax,[rcx]
	mov bx,[rcx+rcx]
	mov cx,[rcx+rcx*4]
	mov ax,[rcx+32]
	mov si,[rcx+rcx+32]
	mov r8w,[rcx+rcx*4+32]
	
	mov ax,[rax]
	mov bx,[rax+rax]
	mov cx,[rax+rax*4]
	mov ax,[rax+32]
	mov si,[rax+rax+3200]
	mov r8w,[rax+rax*4+3200]	

	mov ax,[rax]
	mov bx,[rax+rcx]
	mov cx,[rax+rdx*4]
	mov ax,[rbx+32]
	mov di,[rax+rdx+32]
	mov r8w,[rdx+rbx*4+32]
	mov ax,[rsi]
	mov bx,[rax+rsi]
	mov cx,[rdx+rdi*4]
	mov ax,[rdi+32000]
	mov si,[rax+rbp+32]
	mov r8w,[rsp+rbp*4+32]	

	mov ax,[rax]
	mov bx,[rax+r8]
	mov cx,[r10+rdx*4]
	mov ax,[rbx+32]
	mov di,[rax+r9+32]
	mov r8w,[rdx+rbx*4+32]
	mov ax,[rsi]
	mov bx,[r12+rsi]
	mov cx,[rdx+rdi*4]
	mov si,[r8+rbp+32]
	mov r8w,[rsp+r8*4+32]	
	mov r8w,[rsp+r10*4+32]	
	
	mov ax,fs:[rax]
	mov bx,gs:[rax+rax]
	mov ax,fs:[r8]
	
	; Compatibility 32bit addressing 16bit
	mov ax,[eax]
	mov cx,[ebx]
	
	; Basic indirect memory 16bit
	mov ax,[rax]
	mov ax,[rbx]
	mov ax,[rcx]
	mov ax,[rdx]
	mov ax,[rsi]
	mov ax,[rdi]
	mov ax,[rsp]
	mov ax,[rbp]
	mov ax,[rip]
	mov ax,[r8]
	mov ax,[r9]
	mov ax,[r10]
	mov ax,[r11]
	mov ax,[r12]
	mov ax,[r13]
	mov ax,[r14]
	mov ax,[r15]
	
	;---------------------------------------------------------------------------------------------------
	; Combination Modes (Base/Index/Scale/Disp) 32bit
	;---------------------------------------------------------------------------------------------------
	mov r8d,DWORD PTR [rax+rax*4+0xc80]
	
	mov eax,[rax]
	mov ebx,[rax+rax]
	mov ecx,[rax+rax*4]
	mov eax,[rax+32]
	mov esi,[rax+rax+32]
	mov r8d,[rax+rax*4+32]

	mov eax,[rcx]
	mov ebx,[rcx+rcx]
	mov ecx,[rcx+rcx*4]
	mov eax,[rcx+32]
	mov esi,[rcx+rcx+32]
	mov r8d,[rcx+rcx*4+32]
	
	mov eax,[rax]
	mov ebx,[rax+rax]
	mov ecx,[rax+rax*4]
	mov eax,[rax+32]
	mov esi,[rax+rax+3200]
	mov r8d,[rax+rax*4+3200]	

	mov eax,[rax]
	mov ebx,[rax+rcx]
	mov ecx,[rax+rdx*4]
	mov eax,[rbx+32]
	mov edi,[rax+rdx+32]
	mov r8d,[rdx+rbx*4+32]
	mov eax,[rsi]
	mov ebx,[rax+rsi]
	mov ecx,[rdx+rdi*4]
	mov eax,[rdi+32000]
	mov esi,[rax+rbp+32]
	mov r8d,[rsp+rbp*4+32]	

	mov eax,[rax]
	mov ebx,[rax+r8]
	mov ecx,[r10+rdx*4]
	mov eax,[rbx+32]
	mov edi,[rax+r9+32]
	mov r8d,[rdx+rbx*4+32]
	mov eax,[rsi]
	mov ebx,[r12+rsi]
	mov ecx,[rdx+rdi*4]
	mov esi,[r8+rbp+32]
	mov r8d,[rsp+r8*4+32]	
	mov r8d,[rsp+r10*4+32]	
	
	mov eax,fs:[rax]
	mov ebx,gs:[rax+rax]
	mov eax,fs:[r8]
	
	; Compatibility 32bit addressing 32bit
	mov eax,[eax]
	mov ecx,[ebx]
	
	; Basic indirect memory 32bit
	mov eax,[rax]
	mov eax,[rbx]
	mov eax,[rcx]
	mov eax,[rdx]
	mov eax,[rsi]
	mov eax,[rdi]
	mov eax,[rsp]
	mov eax,[rbp]
	mov eax,[rip]
	mov eax,[r8]
	mov eax,[r9]
	mov eax,[r10]
	mov eax,[r11]
	mov eax,[r12]
	mov eax,[r13]
	mov eax,[r14]
	mov eax,[r15]

	;---------------------------------------------------------------------------------------------------
	; Combination Modes (Base/Index/Scale/Disp) 64bit
	;---------------------------------------------------------------------------------------------------
	mov r8,QWORD PTR [rax+rax*4+0xc80]
	
	mov rax,[rax]
	mov rbx,[rax+rax]
	mov rcx,[rax+rax*4]
	mov rax,[rax+32]
	mov rsi,[rax+rax+32]
	mov r8,[rax+rax*4+32]

	mov rax,[rcx]
	mov rbx,[rcx+rcx]
	mov rcx,[rcx+rcx*4]
	mov rax,[rcx+32]
	mov rsi,[rcx+rcx+32]
	mov r8,[rcx+rcx*4+32]
	
	mov rax,[rax]
	mov rbx,[rax+rax]
	mov rcx,[rax+rax*4]
	mov rax,[rax+32]
	mov rsi,[rax+rax+3200]
	mov r8,[rax+rax*4+3200]	

	mov rax,[rax]
	mov rbx,[rax+rcx]
	mov rcx,[rax+rdx*4]
	mov rax,[rbx+32]
	mov rdi,[rax+rdx+32]
	mov r8,[rdx+rbx*4+32]
	mov rax,[rsi]
	mov rbx,[rax+rsi]
	mov rcx,[rdx+rdi*4]
	mov rax,[rdi+32000]
	mov rsi,[rax+rbp+32]
	mov r8,[rsp+rbp*4+32]	

	mov rax,[rax]
	mov rbx,[rax+r8]
	mov rcx,[r10+rdx*4]
	mov rax,[rbx+32]
	mov rdi,[rax+r9+32]
	mov r8,[rdx+rbx*4+32]
	mov rax,[rsi]
	mov rbx,[r12+rsi]
	mov rcx,[rdx+rdi*4]
	mov rsi,[r8+rbp+32]
	mov r8,[rsp+r8*4+32]	
	mov r8,[rsp+r10*4+32]	
	
	mov rax,fs:[rax]
	mov rbx,gs:[rax+rax]
	mov rax,fs:[r8]
	
	; Compatibility 32bit addressing 64bit
	mov rax,[eax]
	mov rcx,[ebx]
	
	; Basic indirect memory 64bit
	mov rax,[rax]
	mov rax,[rbx]
	mov rax,[rcx]
	mov rax,[rdx]
	mov rax,[rsi]
	mov rax,[rdi]
	mov rax,[rsp]
	mov rax,[rbp]
	mov rax,[rip]
	mov rax,[r8]
	mov rax,[r9]
	mov rax,[r10]
	mov rax,[r11]
	mov rax,[r12]
	mov rax,[r13]
	mov rax,[r14]
	mov rax,[r15]
		
	; Segment Register Moves (64bit allowed)
	mov ax,cs		; 0x66 0x8c 0xc8
	mov ax,fs		; 0x66 0x8c 0xe0
	mov r8w,cs		;
	mov r12w,ds		;
	mov eax,gs		;
	mov eax,fs		;
	mov r10d,ds		;
	mov rax,cs		;
	mov rax,es
	mov rdi,cs
	mov r9,cs
	mov cs,ax		;
	mov fs,ax		;
	mov es,r8w		;
	mov gs,eax		;
	mov fs,eax		;
	mov fs,r10d		;
	mov cs,rax		;
	mov es,rax
	mov cs,rdi
	mov ds,r9		;
	mov fs,r10
	
	; Special Moves (CR/DR)
	mov rax,cr0		; 0x0f 0x20 0xc0
	mov rcx,cr2		; 0x0f 0x20 0xd1
	mov r8,cr4		; 0x0f 0x20 0xe0
	mov r12,cr8		; 0x45 0x0f 0x20 0xc4 (CR8 is 64bit only == TPR).
	mov cr8,r8		; 0x45 0x0f 0x22 0xc0
	mov cr0,rax		; 0x0f 0x22 0xc0
	mov rax,dr0		; 0x0f 0x21 0xc0
	mov rcx,dr1
	mov r8,dr7		; 0x41 0x0f 0x21 0xf8
	mov dr7,r12
	mov dr0,rax
	
	; 64 bit R/R moves
	mov rax,rax		; 0x48 0x89 0xc0
	mov rax,rbx
	mov r10,rdx		; 0x49 0x89 0xd2
	mov rsi,rdi
	mov r9,rax
	mov rbx,rcx
	mov rax,rbp
	mov rbx,r12		; 0x4c 0x89 0xe3
	mov r13,r9		; 0x4d 0x89 0xcd
	
	; 32 bit R/R moves
	mov eax,eax		; 0x89 0xc0
	mov ebx,eax		; 0x89 0xc3
	mov ecx,edx		;
	mov edx,eax		;
	mov eax,r9d		; 0x44 0x89 0xc8
	mov ecx,r12d	; 0x44 0x89 0xe1
	mov r8d,eax		; 0x41 0x89 0xc0
	mov r9d,edx
	mov r10d,esi
	mov r12d,edi
	mov r13d,ebp	
	mov eax,esp
	mov r8d,esp
	
	; 16 bit R/R moves
	mov ax,bx		; 0x66 0x89 0xd8
	mov si,dx		; 0x66 0x89 0xd6
	mov dx,di		; 0x66 0x89 0xfa
	mov bp,ax		; 0x66 0x89 0xc5
	mov ax,r9w		; 0x66 0x44 0x89 0xc8
	mov cx,r12w		; 0x66 0x44 0x89 0xe1
	mov r8w,ax		; 0x66 0x41 0x89 0xc0
	mov r9w,dx
	mov r10w,si
	mov r12w,di
	mov r13w,bp
	mov bx,sp
	mov ax,ax
	
	; 8 bit R/R moves
	mov al,al 		; 0x88 0xc0	
	mov al,bl 		; 0x88 0xd8
	mov cl,dl 		; 0x88 0xd1
	mov al,ah 		; 0x88 0xe0
	mov ch,bl 		; 0x88 0xdd
	mov bh,dh 		; 0x88 0xf7
	mov r10b,al
	mov ch,al
	mov al,r8b		; 0x44 0x88 0xc0
	mov r9b,r12b	; 0x45 0x88 0xe1
	mov sil,al		; 0x40 0x88 0xc6
	mov dil,dl		; 0x40 0x88 0xd7
	mov bpl,al		;
	mov spl,al		;
	mov sil,dil		;
	mov bpl,spl		;
	mov r14b,r15b	;
	
	;---------------------------------------------------------------------------------------------------
	; Memory/Immediate Forms
	;---------------------------------------------------------------------------------------------------
	mov ddVar,10
	mov [ddVar],1000
	mov ddVar,0xffff1234
	mov ddVar,0x12341234
	mov dwVar,20
	mov dwVar,1000
	mov dbVar,10
	mov dqVar,0x12341234
	mov dqVar,0x100
	
	mov dwVarF,20
	mov dwVarF,1000
	mov dbVarF,10
	mov dqVarF,0x12341234
	mov dqVarF,0x100
	
	; Should be RIP relative, thus allow displacement.
	mov ddVar+20,10
	mov [ddVar-20],1000
	mov [ddVar+20],0xffff1234
	mov ddVar-20,0x12341234
	mov dwVar+20,20
	mov dwVar+20,1000
	mov [dbVar+20],10	

	mov byte ptr ddVar,10
	mov dword ptr dbVar,10
	
  	mov qword ptr [rdi],0x12341234
	mov qword ptr [rdi],10
	mov dword ptr [rsi],0x20
	mov word ptr [rsi],2000
	mov dword ptr [rdi],0xffff1223
	mov dword ptr [rdi],0xffff1223
	mov qword ptr [rdi],0xffff1223
		
	mov byte ptr [rax],3
	mov byte ptr [rcx],0x10
	mov word ptr [rsi+rax],10
	mov byte ptr [rsi+rax*4],10
	mov byte ptr [rdi+rax*4+0x20],10
	mov byte ptr [r8+rax],10
	mov byte ptr [r8+rax*4],10
	
	mov byte ptr [rsp+0x10],10
	mov byte ptr [rbp-0x10],10	

.data

dbVarF db 10
dwVarF dw 10
ddVarF dd 10
dqVarF dq 10
ddArrF dd 100 DUP (0)
