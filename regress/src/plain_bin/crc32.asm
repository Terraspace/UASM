;
; CRC32
;
    .x64
    .model flat
    .code

	crc32 eax,cx   ; ok reg32, rm16
	crc32 rax,cl   ; ok reg64, rm8
	crc32 eax,ebx  ; ok reg32, rm32
	crc32 rax,cl   ; ok reg64, rm8
	crc32 rax,rcx  ; ok reg64, rm64
	
	crc32 eax,word ptr [rdi]   ; ok reg32, rm16     
	crc32 eax,[rdi]   ; ok reg32, rm32
	crc32 rax,byte ptr [rdi]   ; ok reg64, rm8
	crc32 rax,[rdi]   ; ok reg64, rm8      SIZE warn
	crc32 rax,qword ptr [rdi]   ; ok reg64, rm64
	
	; Not valid
	crc32 rax,cx   
	crc32 rax,ecx
	

; UASM < 2.55 incorrect encoding	
;0:  f2 66 0f 38 f1 c1       crc32  eax,cx
;6:  f2 48 0f 38 f0 c1       crc32  rax,cl
;c:  f2 0f 38 f1 c3          crc32  eax,ebx
;11: f2 48 0f 38 f0 c1       crc32  rax,cl
;17: f2 48 0f 38 f1 c1       crc32  rax,rcx
;1d: f2 0f 38 f0 07          crc32  eax,BYTE PTR [rdi]
;22: f2 0f 38 f0 07          crc32  eax,BYTE PTR [rdi]
;27: f2 48 0f 38 f0 07       crc32  rax,BYTE PTR [rdi]
;2d: f2 48 0f 38 f0 07       crc32  rax,BYTE PTR [rdi]
;33: f2 48 0f 38 f0 07       crc32  rax,BYTE PTR [rdi]
;39: f2 66 48 0f 38 f1 c1    data16 crc32 rax,rcx
;40: f2 48 0f 38 f1 c1       crc32  rax,rcx

    end
