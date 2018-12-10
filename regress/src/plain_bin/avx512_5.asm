
    .x64
    .model flat
    option evex:1
    .code

	; wont assemble, reported by Gwoltman, 27th November 2018.
	vpmovzxbq zmm31, xmm0			
	vpmovzxbq zmm31, QWORD PTR [r11]

    end