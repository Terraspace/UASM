
    .x64
    .model flat
    option evex:1
    .code

	;While you are at it, I found this bad code:
	vmovsd [rsi], zmm8

	;assembling as:
	;62 31 7F 08: 11. 06
	;which defuse.ca says is:
	;0: 62 31 7f 08 11 (bad)
	;5: 06 (bad)

	vmovsd	[rsi+128], xmm16

	;is assembling as;
	;62 E1 7F 08: 11. 46, 20
	;which defuse.ca is:
	;0: 62 e1 7f 08 11 (bad)
	;5: 46 rex.RX
	;6: 20 .byte 0x20

	;reported by gwoltman 28-3-2018

    end