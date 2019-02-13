
    .x64
    .model flat
    option evex:1
    .code

	; wont assemble, reported by Gwoltman, 27th November 2018.
	vpmovzxbq zmm31, xmm0			
	vpmovzxbq zmm31, QWORD PTR [r11]
	
	{evex} vpmovzxbq xmm2, xmm3
	{evex} vpmovzxbq xmm12, xmm3
	{evex} vpmovzxbq xmm3, xmm12
	{evex} vpmovzxbq xmm12, xmm13
	{evex} vpmovzxbq xmm2, [rdi]
	{evex} vpmovzxbq xmm12, [rsi]
	
	vpmovzxbq xmm2, xmm3 ; avx versions
	vpmovzxbq xmm12, xmm3
	vpmovzxbq xmm3, xmm12
	vpmovzxbq xmm12, xmm13
	vpmovzxbq xmm2, [rdi]
	vpmovzxbq xmm12, [rsi]
	
    end