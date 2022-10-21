
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

	;-------------------------------------------
	;avx-vnni
	vpdpbusds xmm0,xmm1,xmm2
	vpdpbusds xmm0,xmm1,[rdi]
	vpdpbusds ymm0,ymm1,ymm2
	vpdpbusds ymm0,ymm1,[rdi]

	;promoted to avx-512 versions
	{evex} vpdpbusds xmm0,xmm1,xmm2
	{evex} vpdpbusds ymm0,ymm1,ymm2
	{evex} vpdpbusds ymm0,ymm1,[rdi]
	
	vpdpbusds xmm0{k1},xmm1,xmm2
	vpdpbusds xmm0{k1},xmm1,[rdi]
	vpdpbusds ymm0{k2},ymm1,ymm2
	vpdpbusds ymm0{k2},ymm1,[rdi]
	vpdpbusds zmm0,zmm1,zmm2
	vpdpbusds zmm0,zmm1,[rdi]

	;-------------------------------------------
	;avx-vnni
	vpdpbusd xmm0,xmm1,xmm2
	vpdpbusd xmm0,xmm1,[rdi]
	vpdpbusd ymm0,ymm1,ymm2
	vpdpbusd ymm0,ymm1,[rdi]

	;promoted to avx-512 versions
	{evex} vpdpbusd xmm0,xmm1,xmm2
	{evex} vpdpbusd ymm0,ymm1,ymm2
	{evex} vpdpbusd ymm0,ymm1,[rdi]
	
	vpdpbusd xmm0{k1},xmm1,xmm2
	vpdpbusd xmm0{k1},xmm1,[rdi]
	vpdpbusd ymm0{k2},ymm1,ymm2
	vpdpbusd ymm0{k2},ymm1,[rdi]
	vpdpbusd zmm0,zmm1,zmm2
	vpdpbusd zmm0,zmm1,[rdi]	
	
	;-------------------------------------------
	;avx-vnni
	vpdpwssds xmm0,xmm1,xmm2
	vpdpwssds xmm0,xmm1,[rdi]
	vpdpwssds ymm0,ymm1,ymm2
	vpdpwssds ymm0,ymm1,[rdi]

	;promoted to avx-512 versions
	{evex} vpdpwssds xmm0,xmm1,xmm2
	{evex} vpdpwssds ymm0,ymm1,ymm2
	{evex} vpdpwssds ymm0,ymm1,[rdi]
	
	vpdpwssds xmm0{k1},xmm1,xmm2
	vpdpwssds xmm0{k1},xmm1,[rdi]
	vpdpwssds ymm0{k2},ymm1,ymm2
	vpdpwssds ymm0{k2},ymm1,[rdi]
	vpdpwssds zmm0,zmm1,zmm2
	vpdpwssds zmm0,zmm1,[rdi]	
	
	;-------------------------------------------
	;avx-vnni
	vpdpwssd xmm0,xmm1,xmm2
	vpdpwssd xmm0,xmm1,[rdi]
	vpdpwssd ymm0,ymm1,ymm2
	vpdpwssd ymm0,ymm1,[rdi]

	;promoted to avx-512 versions
	{evex} vpdpwssd xmm0,xmm1,xmm2
	{evex} vpdpwssd ymm0,ymm1,ymm2
	{evex} vpdpwssd ymm0,ymm1,[rdi]
	
	vpdpwssd xmm0{k1},xmm1,xmm2
	vpdpwssd xmm0{k1},xmm1,[rdi]
	vpdpwssd ymm0{k2},ymm1,ymm2
	vpdpwssd ymm0{k2},ymm1,[rdi]
	vpdpwssd zmm0,zmm1,zmm2
	vpdpwssd zmm0,zmm1,[rdi]		
	
	;-------------------------------------------
	; gfni
	vgf2p8mulb xmm0,xmm1,xmm2
	vgf2p8mulb ymm0,ymm1,ymm2
	vgf2p8mulb xmm0,xmm1,[rdi]
	vgf2p8mulb ymm0,ymm1,[rdi]	
	vgf2p8mulb zmm0,zmm1,zmm2
	{evex} vgf2p8mulb xmm0,xmm1,xmm2
	{evex} vgf2p8mulb ymm0,ymm1,ymm2
	vgf2p8mulb xmm0{k1},xmm1,xmm2
	vgf2p8mulb ymm0{k1},ymm1,ymm2
	vgf2p8mulb zmm0{k2},zmm1,[rdi]

	vgf2p8affineqb xmm0,xmm1,xmm2,1
	vgf2p8affineqb ymm0,ymm1,ymm2,1
	vgf2p8affineqb xmm0,xmm1,[rdi],1
	vgf2p8affineqb ymm0,ymm1,[rdi],1
	vgf2p8affineqb zmm0,zmm1,zmm2,1
	{evex} vgf2p8affineqb xmm0,xmm1,xmm2,1
	{evex} vgf2p8affineqb ymm0,ymm1,ymm2,1
	vgf2p8affineqb xmm0{k1},xmm1,xmm2,1
	vgf2p8affineqb ymm0{k1},ymm1,ymm2,1
	vgf2p8affineqb zmm0{k2},zmm1,[rdi],1
	
	vgf2p8affineinvqb xmm0,xmm1,xmm2,1
	vgf2p8affineinvqb ymm0,ymm1,ymm2,1
	vgf2p8affineinvqb xmm0,xmm1,[rdi],1
	vgf2p8affineinvqb ymm0,ymm1,[rdi],1
	vgf2p8affineinvqb zmm0,zmm1,zmm2,1
	{evex} vgf2p8affineinvqb xmm0,xmm1,xmm2,1
	{evex} vgf2p8affineinvqb ymm0,ymm1,ymm2,1
	vgf2p8affineinvqb xmm0{k1},xmm1,xmm2,1
	vgf2p8affineinvqb ymm0{k1},ymm1,ymm2,1
	vgf2p8affineinvqb zmm0{k2},zmm1,[rdi],1	
	
    end