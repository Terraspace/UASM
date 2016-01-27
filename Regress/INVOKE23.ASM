
;--- type arguments for VARARG
;--- didn't always work prior to v2.10

	.386
	.MODEL FLAT, stdcall
	option casemap:none

S1 struct
f1  dd ?
f2  dd ?
S1 ends

T1  typedef QWORD
T1P typedef ptr QWORD
T2  typedef S1
T2P typedef ptr S1

	.CODE

printf proc c args:vararg
	ret
printf endp

	invoke printf, DWORD
	invoke printf, QWORD
	invoke printf, T1
	invoke printf, T1P
	invoke printf, S1
	invoke printf, T2
	invoke printf, T2P
	invoke printf, S1.f1, S1.f2

END
