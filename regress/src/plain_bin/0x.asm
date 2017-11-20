;
; v2.21 allow 0x prefix for numbers
;
	.486
	.model	flat
	.code

	mov	al,0x0F
	mov	al,0xa0
	mov	ax,0x0FFF
	mov	eax,0xFFFFFFFF

	if ( 0x00abcdef ne 0xabcdef \
	  OR 0xabcdef ne 0Xabcdef OR 0Xabcdef ne 0XAbcdef \
	  OR 0XAbcdef ne 0XABcdef OR 0XABcdef ne 0XABCdef \
	  OR 0XABCdef ne 0XABCDef OR 0XABCDef ne 0XABCDEf \
	  OR 0XABCDEf ne 0XABCDEF OR 0xABCDEF ne 11259375 )
		.err <radix 10 0x>
	endif

	.radix 8

	if ( 0x08 ne 010 \
	  OR 0x10 ne 020 \
	  OR 0x18 ne 030 \
	  OR 0x20 ne 040 \
	  OR 0x28 ne 050 \
	  OR 0x30 ne 060 \
	  OR 0x38 ne 070 \
	  OR 0x40 ne 0100 \
	  OR 0x48 ne 0110 \
	  OR 0x50 ne 0120 \
	  OR 0x09 ne 0011 \
	  OR 0x11 ne 0021 \
	  OR 0x19 ne 0031 \
	  OR 0x21 ne 0041 \
	  OR 0x29 ne 0051 \
	  OR 0x31 ne 0061 \
	  OR 0x39 ne 0071 \
	  OR 0x41 ne 0101 \
	  OR 0x49 ne 0111 \
	  OR 0x51 ne 0121 )
		.err <radix 8>
	endif

	end
