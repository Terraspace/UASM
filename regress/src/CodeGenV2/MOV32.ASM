
option flat:1

.data

dbVar db 10
dwVar dw 10
ddVar dd 10
ddVarA dd 10 DUP (0)

.code

	use32

	;---------------------------------------------------------------------------------------------------
	; Index only form
	;---------------------------------------------------------------------------------------------------
	mov eax,[edi*2]
	
	;---------------------------------------------------------------------------------------------------
	; Array style
	;---------------------------------------------------------------------------------------------------
	mov al,byte ptr ddVarA[ebx]
	mov eax,ddVarA[eax*4]
	mov byte ptr ddVarA[ebx],al
	mov ddVarA[eax*4+10],eax
	
	;---------------------------------------------------------------------------------------------------
	; OFFSETS
	;---------------------------------------------------------------------------------------------------
	mov eax,OFFSET ddVar 
	
	;---------------------------------------------------------------------------------------------------
	; Mixed and sized immediates
	;---------------------------------------------------------------------------------------------------
	mov al,10
	mov al,130
	mov cl,-25
	mov dh,120
	mov bl,0xff
	mov ah,32
	mov ax,10
	mov ax,0x20
	mov cx,25
	mov eax,10
	mov eax,0x20
	mov ecx,25
	mov eax,10
	
	; (8bit immediates)
	mov al,10
	mov al,0x20
	mov cl,25
	mov dh,120
	mov bl,01010101b
	mov ah,32
	
	; (16bit immediates)
	mov ax,10
	mov ax,0x20
	mov cx,25
	
	; (32bit immediates)
	mov eax,10
	mov eax,0x20
	mov ecx,25
	mov eax,1.0
	
	;---------------------------------------------------------------------------------------------------
	; Special MOFFSET mov modes
	; JWASM was wrong, 64bit does support encoding of segment registers with moffset
	;---------------------------------------------------------------------------------------------------
	movabs al,[0x00]
	movabs al,[0x0000]
	movabs al,[0x00000000]
	movabs al,es:[0x20]
	movabs al,fs:[0x2020]
	movabs al,[0x10203040]

	movabs [0x00],al
	movabs [0x0000],al
	movabs [0x00000000],al
	movabs es:[0x20],al
	movabs fs:[0x2020],al
	movabs [0x10203040],al

	movabs ax,[0x00]
	movabs ax,[0x0000]
	movabs ax,[0x00000000]
	movabs ax,es:[0x20]
	movabs ax,fs:[0x2020]
	movabs ax,[0x10203040]

	movabs [0x00],ax
	movabs [0x0000],ax
	movabs [0x00000000],ax
	movabs es:[0x20],ax
	movabs fs:[0x2020],ax
	movabs [0x10203040],ax

	movabs eax,[0x00]
	movabs eax,[0x0000]
	movabs eax,[0x00000000]
	movabs eax,es:[0x20]
	movabs eax,fs:[0x2020]
	movabs eax,[0x10203040]

	movabs [0x00],eax
	movabs [0x0000],eax
	movabs [0x00000000],eax
	movabs es:[0x20],eax
	movabs fs:[0x2020],eax
	movabs [0x10203040],eax

	;---------------------------------------------------------------------------------------------------
	; Displacement Only addressing modes
	;---------------------------------------------------------------------------------------------------
	mov cl,[0]
	mov ch,[10]
	mov ax,[32]
	mov eax,[0x100]

	mov [0],cl
	mov [10],ch
	mov [32],ax
	mov [0x100],eax

	;---------------------------------------------------------------------------------------------------
	; MEM/REG Combination Modes (Base/Index/Scale/Disp) 8bit
	;---------------------------------------------------------------------------------------------------
	mov [eax],al
	mov [eax+eax],bl
	mov [eax+eax*4],cl
	mov [eax+32],ah

	mov [ecx],al
	mov [ecx+ecx],bl
	mov [ecx+ecx*4],cl
	mov [ecx+32],ah
	
	mov [eax],al
	mov [eax+eax],bl
	mov [eax+eax*4],cl
	mov [eax+32],ah

	mov [eax],al
	mov [eax+ecx],bl
	mov [eax+edx*4],cl
	mov [ebx+32],ah
	mov [esi],al
	mov [eax+esi],bl
	mov [edx+edi*4],cl
	mov [edi+32000],ah

	mov [eax],al
	mov [ebx+32],ah
	mov [esi],al
	mov [edx+edi*4],cl
	
	mov fs:[eax],al
	mov gs:[eax+eax],bl
	
	; Compatibility 32bit addressing 8bit
	mov [eax],al
	mov [ebx],ch
	
	; Basic indirect memory 8bit
	mov [eax],al
	mov [ebx],al
	mov [ecx],al
	mov [edx],al
	mov [esi],al
	mov [edi],al
	mov [esp],al
	mov [ebp],al
;	mov [eip],al

	;---------------------------------------------------------------------------------------------------
	; MEM/REG Combination Modes (Base/Index/Scale/Disp) 16bit
	;---------------------------------------------------------------------------------------------------
	mov [eax],ax
	mov [eax+eax],bx
	mov [eax+eax*4],cx
	mov [eax+32],ax
	mov [eax+eax+32],si

	mov [ecx],ax
	mov [ecx+ecx],bx
	mov [ecx+ecx*4],cx
	mov [ecx+32],ax
	mov [ecx+ecx+32],si
	
	mov [eax],ax
	mov [eax+eax],bx
	mov [eax+eax*4],cx
	mov [eax+32],ax
	mov [eax+eax+3200],si

	mov [eax],ax
	mov [eax+ecx],bx
	mov [eax+edx*4],cx
	mov [ebx+32],ax
	mov [eax+edx+32],di
	mov [esi],ax
	mov [eax+esi],bx
	mov [edx+edi*4],cx
	mov [edi+32000],ax
	mov [eax+ebp+32],si

	mov [eax],ax
	mov [ebx+32],ax
	mov [eax+edx+32],di
	mov [esi],ax
	mov [edx+edi*4],cx
	
	mov fs:[eax],ax
	mov gs:[eax+eax],bx
	
	; Compatibility 32bit addressing 16bit
	mov [eax],ax
	mov [ebx],cx
	
	; Basic indirect memory 16bit
	mov [eax],ax
	mov [ebx],ax
	mov [ecx],ax
	mov [edx],ax
	mov [esi],ax
	mov [edi],ax
	mov [esp],ax
	mov [ebp],ax
	;mov [eip],ax

	;---------------------------------------------------------------------------------------------------
	; MEM/REG Combination Modes (Base/Index/Scale/Disp) 32bit
	;---------------------------------------------------------------------------------------------------
	mov [eax],eax
	mov [eax+eax],ebx
	mov [eax+eax*4],ecx
	mov [eax+32],eax
	mov [eax+eax+32],esi

	mov [ecx],eax
	mov [ecx+ecx],ebx
	mov [ecx+ecx*4],ecx
	mov [ecx+32],eax
	mov [ecx+ecx+32],esi
	
	mov [eax],eax
	mov [eax+eax],ebx
	mov [eax+eax*4],ecx
	mov [eax+32],eax
	mov [eax+eax+3200],esi

	mov [eax],eax
	mov [eax+ecx],ebx
	mov [eax+edx*4],ecx
	mov [ebx+32],eax
	mov [eax+edx+32],edi
	mov [esi],eax
	mov [eax+esi],ebx
	mov [edx+edi*4],ecx
	mov [edi+32000],eax
	mov [eax+ebp+32],esi

	mov [eax],eax
	mov [eax+ebx],ebx
	mov [ebx+32],eax
	mov [eax+ecx+32],edi
	mov [esi],eax
	mov [edx+edi*4],ecx
	
	mov fs:[eax],eax
	mov gs:[eax+eax],ebx
	
	; Compatibility 32bit addressing 32bit
	mov [eax],eax
	mov [ebx],ecx
	
	; Basic indirect memory 32bit
	mov [eax],eax
	mov [ebx],eax
	mov [ecx],eax
	mov [edx],eax
	mov [esi],eax
	mov [edi],eax
	mov [esp],eax
	mov [ebp],eax
;	mov [eip],eax

	;---------------------------------------------------------------------------------------------------
	; REG/MEM Combination Modes (Base/Index/Scale/Disp) 8bit
	;---------------------------------------------------------------------------------------------------
	mov al,[eax]
	mov bl,[eax+eax]
	mov cl,[eax+eax*4]
	mov ah,[eax+32]

	mov al,[ecx]
	mov bl,[ecx+ecx]
	mov cl,[ecx+ecx*4]
	mov ah,[ecx+32]
	
	mov al,[eax]
	mov bl,[eax+eax]
	mov cl,[eax+eax*4]
	mov ah,[eax+32]

	mov al,[eax]
	mov bl,[eax+ecx]
	mov cl,[eax+edx*4]
	mov ah,[ebx+32]
	mov al,[esi]
	mov bl,[eax+esi]
	mov cl,[edx+edi*4]
	mov ah,[edi+32000]

	mov al,[eax]
	mov bl,[eax+ebx]
	mov ah,[ebx+32]
	mov al,[esi]
	mov cl,[edx+edi*4]
	
	mov al,fs:[eax]
	mov bl,gs:[eax+eax]
	
	; Compatibility 32bit addressing 8bit
	mov al,[eax]
	mov ch,[ebx]
	
	; Basic indirect memory 8bit
	mov al,[eax]
	mov al,[ebx]
	mov al,[ecx]
	mov al,[edx]
	mov al,[esi]
	mov al,[edi]
	mov al,[esp]
	mov al,[ebp]
;	mov al,[eip]

	;---------------------------------------------------------------------------------------------------
	; Combination Modes (Base/Index/Scale/Disp) 16bit
	;---------------------------------------------------------------------------------------------------
	mov ax,[eax]
	mov bx,[eax+eax]
	mov cx,[eax+eax*4]
	mov ax,[eax+32]
	mov si,[eax+eax+32]

	mov ax,[ecx]
	mov bx,[ecx+ecx]
	mov cx,[ecx+ecx*4]
	mov ax,[ecx+32]
	mov si,[ecx+ecx+32]
	
	mov ax,[eax]
	mov bx,[eax+eax]
	mov cx,[eax+eax*4]
	mov ax,[eax+32]
	mov si,[eax+eax+3200]

	mov ax,[eax]
	mov bx,[eax+ecx]
	mov cx,[eax+edx*4]
	mov ax,[ebx+32]
	mov di,[eax+edx+32]
	mov ax,[esi]
	mov bx,[eax+esi]
	mov cx,[edx+edi*4]
	mov ax,[edi+32000]
	mov si,[eax+ebp+32]

	mov ax,[eax]
	mov bx,[eax+ebx]
	mov cx,[eax+edx*4]
	mov ax,[ebx+32]
	mov di,[eax+ecx+32]
	mov ax,[esi]
	mov cx,[edx+edi*4]
	mov si,[edx+ebp+32]
	
	mov ax,fs:[eax]
	mov bx,gs:[eax+eax]
	
	; Compatibility 32bit addressing 16bit
	mov ax,[eax]
	mov cx,[ebx]
	
	; Basic indirect memory 16bit
	mov ax,[eax]
	mov ax,[ebx]
	mov ax,[ecx]
	mov ax,[edx]
	mov ax,[esi]
	mov ax,[edi]
	mov ax,[esp]
	mov ax,[ebp]
;	mov ax,[eip]
	
	;---------------------------------------------------------------------------------------------------
	; Combination Modes (Base/Index/Scale/Disp) 32bit
	;---------------------------------------------------------------------------------------------------
	mov eax,[eax]
	mov ebx,[eax+eax]
	mov ecx,[eax+eax*4]
	mov eax,[eax+32]
	mov esi,[eax+eax+32]

	mov eax,[ecx]
	mov ebx,[ecx+ecx]
	mov ecx,[ecx+ecx*4]
	mov eax,[ecx+32]
	mov esi,[ecx+ecx+32]
	
	mov eax,[eax]
	mov ebx,[eax+eax]
	mov ecx,[eax+eax*4]
	mov eax,[eax+32]
	mov esi,[eax+eax+3200]

	mov eax,[eax]
	mov ebx,[eax+ecx]
	mov ecx,[eax+edx*4]
	mov eax,[ebx+32]
	mov edi,[eax+edx+32]
	mov eax,[esi]
	mov ebx,[eax+esi]
	mov ecx,[edx+edi*4]
	mov eax,[edi+32000]
	mov esi,[eax+ebp+32]

	mov eax,[eax]
	mov ebx,[eax+ecx]
	mov ecx,[eax+edx*4]
	mov eax,[ebx+32]
	mov edi,[eax+edx+32]
	mov eax,[esi]
	mov ebx,[edx+esi]
	mov ecx,[edx+edi*4]
	mov esi,[eax+ebp+32]
	
	mov eax,fs:[eax]
	mov ebx,gs:[eax+eax]
	
	; Compatibility 32bit addressing 32bit
	mov eax,[eax]
	mov ecx,[ebx]
	
	; Basic indirect memory 32bit
	mov eax,[eax]
	mov eax,[ebx]
	mov eax,[ecx]
	mov eax,[edx]
	mov eax,[esi]
	mov eax,[edi]
	mov eax,[esp]
	mov eax,[ebp]
;	mov eax,[eip]

		
	; Segment Register Moves (64bit allowed)
	mov ax,cs		; 0x66 0x8c 0xc8
	mov ax,fs		; 0x66 0x8c 0xe0
	mov eax,gs		;
	mov eax,fs		;
	mov eax,cs		;
	mov eax,es
	mov edi,cs
	mov cs,ax		;
	mov fs,ax		;
	mov gs,eax		;
	mov fs,eax		;
	mov cs,eax		;
	mov es,eax
	mov cs,edi

	; Special Moves (CR/DR)
	mov eax,cr0		; 0x0f 0x20 0xc0
	mov ecx,cr2		; 0x0f 0x20 0xd1
	mov cr0,eax		; 0x0f 0x22 0xc0
	mov eax,dr0		; 0x0f 0x21 0xc0
	mov ecx,dr1
	mov dr0,eax
	
	
	; 32 bit R/R moves
	mov eax,eax		; 0x89 0xc0
	mov ebx,eax		; 0x89 0xc3
	mov ecx,edx		;
	mov edx,eax		;
	mov eax,esp
	
	; 16 bit R/R moves
	mov ax,bx		; 0x66 0x89 0xd8
	mov si,dx		; 0x66 0x89 0xd6
	mov dx,di		; 0x66 0x89 0xfa
	mov bp,ax		; 0x66 0x89 0xc5
	mov bx,sp
	mov ax,ax
	
	; 8 bit R/R moves
	mov al,al 		; 0x88 0xc0	
	mov al,bl 		; 0x88 0xd8
	mov cl,dl 		; 0x88 0xd1
	mov al,ah 		; 0x88 0xe0
	mov ch,bl 		; 0x88 0xdd
	mov bh,dh 		; 0x88 0xf7
	mov ch,al
	
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
	
	mov dwVarF,20
	mov dwVarF,1000
	mov dbVarF,10
	
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
	
	mov word ptr [esi],2000
	mov dword ptr [edi],0xffff1223
	
	mov byte ptr [eax],3
	mov byte ptr [ecx],0x10
	mov word ptr [esi+eax],10
	mov byte ptr [esi+eax*4],10
	mov byte ptr [edi+eax*4+0x20],10
	
	mov byte ptr [esp+0x10],10
	mov byte ptr [ebp-0x10],10	
	
	;---------------------------------------------------------------------------------------------------
	; Address Size override memory access in 32bit.
	;---------------------------------------------------------------------------------------------------
	mov al,[si]				; 16bit addressing via 67h in 32bit code, historically broken in jwasm.
	; codegen v2: 67 8a 04                mov    al,BYTE PTR [si]
	; jwasm     : 67 8a 06 00 00          mov    al,BYTE PTR ds:0x0
	
.data

dbVarF db 10
dwVarF dw 10
ddVarF dd 10

