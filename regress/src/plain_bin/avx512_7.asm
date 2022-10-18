
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

	vpslld ymm15, ymm0, 0
	vpsrld ymm15, ymm0, 0
	vpsrad ymm15, ymm0, 0

	vpsllw ymm15, ymm0, 0
	vpsrlw ymm15, ymm0, 0
	vpsraw ymm15, ymm0, 0

	vpsllq ymm15, ymm0, 0
	vpsrlq ymm15, ymm0, 0
	
	vpsraq ymm15, ymm0, 0	
	{evex} vpslld ymm15, ymm0, 0
	
	vpslldq xmm6, xmm1, 2
	vpslldq ymm6, ymm1, 0
	vpslldq ymm15, ymm1, 0
	vpslldq zmm6, zmm1, 0
	{evex} vpslldq xmm6, xmm1, 0
	
    end
	
;4:  c5 85 72 f0 00          vpslld ymm15,ymm0,0x0
;9:  c5 85 72 d0 00          vpsrld ymm15,ymm0,0x0
;e:  c5 85 72 e0 00          vpsrad ymm15,ymm0,0x0
;13: c5 85 71 f0 00          vpsllw ymm15,ymm0,0x0
;18: c5 85 71 d0 00          vpsrlw ymm15,ymm0,0x0
;1d: c5 85 71 e0 00          vpsraw ymm15,ymm0,0x0
;22: c5 85 73 f0 00          vpsllq ymm15,ymm0,0x0
;27: c5 85 73 d0 00          vpsrlq ymm15,ymm0,0x0
;2c: 62 f1 85 28 72 e0 00    vpsraq ymm15,ymm0,0x0
;33: 62 f1 05 28 72 f0 00    vpslld ymm15,ymm0,0x0
;3a: c5 c9 73 f9 02          vpslldq xmm6,xmm1,0x2
;3f: c5 cd 73 f9 00          vpslldq ymm6,ymm1,0x0
;44: c5 85 73 f9 00          vpslldq ymm15,ymm1,0x0
;49: 62 f1 4d 48 73 f9 00    vpslldq zmm6,zmm1,0x0
;50: 62 f1 4d 08 73 f9 00    vpslldq xmm6,xmm1,0x0