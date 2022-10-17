
; AVX-VNNI, AVX512-VNNI and Galois Field Instructions
; UASM 2.56 Oct 2022

; See: https://en.wikipedia.org/wiki/AVX-512

;VPDPBUSD	Multiply and add unsigned and signed bytes
;VPDPBUSDS	Multiply and add unsigned and signed bytes with saturation
;VPDPWSSD	Multiply and add signed word integers
;VPDPWSSDS	Multiply and add word integers with saturation

;VGF2P8AFFINEINVQB	Galois field affine transformation inverse
;VGF2P8AFFINEQB	Galois field affine transformation
;VGF2P8MULB	Galois field multiply bytes

    .x64
    .model flat
    option evex:1
    .code

	vpbroadcastd xmm0,r8d	; These all require AVX512F / EVEX encoding
	vpbroadcastd ymm0,r8d
	vpbroadcastd zmm0,r8d
	vpbroadcastd xmm0,xmm1	; this is fine for AVX2
	{evex} vpbroadcastd xmm0,xmm1

	vpbroadcastq xmm0,r8	; These all require AVX512F / EVEX encoding
	vpbroadcastq ymm0,rax
	vpbroadcastq zmm0,r8
	vpbroadcastq xmm0,xmm1	; this is fine for AVX2
	{evex} vpbroadcastq xmm0,xmm1
	
	;avx-vnni
	;vpdpbusds xmm0,xmm1,xmm2
	;vpdpbusds xmm0,xmm1,[rdi]
	;vpdpbusds ymm0,ymm1,ymm2
	;vpdpbusds ymm0,ymm1,[rdi]

	;promoted to avx-512 versions
	;{evex} vpdpbusds xmm0,xmm1,xmm2
	;{evex} vpdpbusds ymm0,ymm1,ymm2
	;{evex} vpdpbusds ymm0,ymm1,[rdi]
	
	;vpdpbusds xmm0{k1},xmm1,xmm2
	;vpdpbusds xmm0{k1},xmm1,[rdi]
	;vpdpbusds ymm0{k2},ymm1,ymm2
	;vpdpbusds ymm0{k2},ymm1,[rdi]
	;vpdpbusds zmm0,zmm1,zmm2
	;vpdpbusds zmm0,zmm1,[rdi]
	
    end