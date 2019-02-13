
option flat:1
option evex:1

.code

	use64

	vblendmpd zmm26{k6}, zmm1, zmm30
	vblendmpd ymm26{k6}, ymm1, ymm30
	vblendmpd xmm26{k6}{z}, xmm1, xmm30
	vblendmpd zmm26{k6}, zmm1, [rdi]
	vblendmpd ymm26{k6}, ymm1, [rdi+32]
	vblendmpd xmm26{k6}{z}, xmm1, [rdx-64]
	vblendmpd zmm16{k6}, zmm1, [rdi]{1to8}
	vblendmpd ymm6{k6}, ymm1, [rdi+32]{1to4}
	vblendmpd xmm2{k6}{z}, xmm1, [rdx-64]{1to2}
	
	vpmovzxbq zmm30{k7},QWORD PTR [rdx+0x3f8]   
    vpmovzxbq zmm30{k7},qword ptr [rdx+0x400]
    vpmovzxbq zmm30{k7},qword ptr [rdx-0x400]
    vpmovzxbq zmm30{k7},qword ptr [rdx-0x408]
	
	vbroadcastsd zmm23, [r11+8]
	vbroadcastsd zmm2, xmm2
	vbroadcastsd ymm12, xmm2 ; this one is actually avx2, although not listed in the intel manuals!
	
	{evex} vbroadcastsd ymm2, dword ptr myVector
	
.data

align 32
myVector __m256f <1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0>