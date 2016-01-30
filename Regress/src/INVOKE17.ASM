
;--- prototype with VARARG: 
;--- INVOKE of a member param that
;--- 1) is a structure of size 4/8 (DWORD/QWORD). Didn't work prior to v2.07
;--- 2) is a structure of size > 8. Didn't work prior to v2.07

	.286
	.MODEL small
	option casemap:none
	option proc:private

S32 struct
f1	dw ?
f2	dw ?
S32 ends

S64 struct
f1	dd ?
f2	dd ?
S64 ends

S128 struct
f1	dq ?
f2	dq ?
S128 ends

S1 struct
fm32	DWORD ?
fm32s	S32 <?,?>
fm64	QWORD ?
fm64s	S64 <?,?>
fm128   OWORD ?
fm128s	S128 <?,?>
S1 ends

	.CONST

szFmt32 db "%lX",10, 0
szFmt64 db "%I64X",10, 0

	.DATA?

v1	S1 <>

	.CODE

printf proc c fmt:ptr byte, args:VARARG
	ret
printf endp

	invoke printf, addr szFmt32, v1.fm32s
	invoke printf, addr szFmt64, v1.fm64s
;	invoke printf, addr szFmt64, v1.fm128	;Masm has problems with OWORD
	invoke printf, addr szFmt64, v1.fm128s	;req. Masm v8+
	ret

	END
