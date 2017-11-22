; v2.22 (eax || edx) && ecx -- !(eax || edx) && ecx
;
; posted by powershadow 2016-12-28
; http://masm32.com/board/index.php?topic=5896.msg62670#msg62670
;
	.486
	.model flat
	.code

	.if (eax || edx) && ecx
		nop
	.endif

	.if !(eax || edx) && ecx
		nop
	.endif

	.while (eax || edx) && ecx
		nop
	.endw

	.while !(eax || edx) && ecx
		nop
	.endw

	.repeat
		nop
	.until (eax || edx) && ecx

	.repeat
		nop
	.until !(eax || edx) && ecx

ifdef __ASMC__
	.switch
          .case  (eax || edx) && ecx : nop : .endc
          .case !(eax || edx) && ecx : nop : .endc
        .endsw
endif
	END
