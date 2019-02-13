
option flat:1
option evex:1

.code

	use64

	vbroadcastsd zmm23, [r11+8]{1to8} ; unsupported broadcast options
	vblendmpd zmm16{k6}, zmm1, [rdi]{1to16} ; unsupported broadcast options
	vblendmpd ymm6{k6}, ymm1, [rdi+32]{1to8} ; unsupported broadcast options
	vblendmpd xmm2{k6}{z}, xmm1, [rdx-64]{1to4}	; unsupported broadcast options
	
.data

