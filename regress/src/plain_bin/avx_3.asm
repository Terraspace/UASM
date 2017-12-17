;
; AVX-3
;
    .x64
    .model flat
    .code

    option evex:1

	vmovsd qword ptr [r11+380H], xmm0

	; vmovsd qword ptr [r11+380H], xmm0 ; 0000 _ C4 C1 FB: 11. 83, 00000380
	; should be:
	; vmovsd qword ptr [r11+380H], xmm0 ; 0000 _ C4 C1 7B: 11. 83, 00000380
	; Both versions execute (at least on Knights Landing). However, debugging is a real pain because GDB does not recognize the UASM version. Go to https://defuse.ca/online-x86-assembler.htm#disassembly2 and you'll see this GDB disassembly:

	; 0: c4 c1 fb 11 (bad)
	; 4: 83 00 00 add DWORD PTR [rax],0x0
	; 7: 03 .byte 0x3
	; 8: 80 .byte 0x80
	; reported by gwoltman, 14th Dec 2017

	;also requires 7B
	vmovsd xmm0,qword ptr [r11+380H]

	vmovd xmm0,dword ptr [r11+380H]
	vmovq xmm0,qword ptr [r11+380H]
	vmovd dword ptr [r11+380H],xmm0
	vmovq qword ptr [r11+380H],xmm0

	vmovsd xmm14, xmm17, xmm17
	;assembles as:
	;vmovsd xmm14, xmm17, xmm1 ; 0000 _ 62 71 F7 00: 10. F1

    end
