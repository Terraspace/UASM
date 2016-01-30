
;--- SSE 4.2 instructions
;--- CRC, POPCNT

	.686
	.model small
	.xmm

	.dosseg
	.data

vo	oword 0
vq	dq 0
vd	dd 0
vw	dw 0
vb	db 0

	.code
if 1
	crc32 eax, al
	crc32 eax, ah
	crc32 eax, vb
	crc32 eax, byte ptr [ebx]
	crc32 eax, byte ptr [ebx+8]
	crc32 eax, byte ptr [ebx+1000]
	crc32 eax, byte ptr [esp]
	crc32 eax, byte ptr [esp+8]
	crc32 eax, byte ptr [esp+1000]

	crc32 eax, ax
	crc32 eax, vw
	crc32 eax, word ptr [ebx]
	crc32 eax, word ptr [ebx+8]
	crc32 eax, word ptr [ebx+1000]
	crc32 eax, word ptr [esp]
	crc32 eax, word ptr [esp+8]
	crc32 eax, word ptr [esp+1000]

	crc32 eax, eax
	crc32 eax, vd
	crc32 eax, dword ptr [ebx]
	crc32 eax, dword ptr [ebx+8]
	crc32 eax, dword ptr [ebx+1000]
	crc32 eax, dword ptr [esp]
	crc32 eax, dword ptr [esp+8]
	crc32 eax, dword ptr [esp+1000]

	popcnt ax, ax
	popcnt ax, vw
	popcnt ax, word ptr [ebx]
	popcnt ax, word ptr [ebx+8]
	popcnt ax, word ptr [esp]
	popcnt ax, word ptr [esp+8]

	popcnt eax, eax
	popcnt eax, vd
	popcnt eax, dword ptr [ebx]
	popcnt eax, dword ptr [ebx+8]
	popcnt eax, dword ptr [esp]
	popcnt eax, dword ptr [esp+8]
endif
	ret

_TEXT16 segment use16 public 'CODE'

;--- CRC32 and POPCNT are among the few SSE instructions
;--- which know the OPSIZE prefix byte.

	crc32 eax, al
	crc32 eax, ah
	crc32 eax, vb
	crc32 eax, byte ptr [bx]

	crc32 eax, ax
	crc32 eax, vw
	crc32 eax, word ptr [bx]

	crc32 eax, eax
	crc32 eax, vd
	crc32 eax, dword ptr [bx]

	popcnt ax, ax
	popcnt ax, vw
	popcnt ax, word ptr [bx]

	popcnt eax, eax
	popcnt eax, vd
	popcnt eax, dword ptr [bx]

_TEXT16 ends

end
