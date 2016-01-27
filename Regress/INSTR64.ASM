
;--- test 64bit specific instructions

ifdef __JWASM__
	.x64
	.model flat
endif

	.code

main proc

	CWDE
	CDQE
	CDQ
	CQO
	IRETQ
	CMPSQ
	LODSQ
	MOVSQ
	SCASQ
	STOSQ
	SWAPGS
	bswap eax
	bswap rax
	ret

main endp

    END
