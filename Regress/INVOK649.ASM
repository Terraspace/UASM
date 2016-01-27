
;--- test invoke with VARARG for register params (arguments 1-4)
;--- didn't work in v2.05-v2.06

ifdef __JWASM__
	.x64
	.model flat, fastcall
	option win64:2
endif

	.data

m08	label byte

	.code

proc0 proc a1:qword, a2:vararg
	mov rax,a1
	ret
proc0 endp

main proc
	invoke proc0, 1
	invoke proc0, 1, 2
	invoke proc0, 1, 2, 3
	invoke proc0, 1, addr m08, 3
	invoke proc0, 1, 2, addr m08
	invoke proc0, 1, addr m08, addr m08, addr m08
main endp

    END
