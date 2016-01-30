
;--- TYPE operator with GPR ASSUME
;--- prior to v2.10, TYPE ignored ASSUMEs for GPRs
;--- (unless the GPR was used inside [])

	.386
	.model flat, stdcall

PREAL8 typedef ptr REAL8

	.data

assume eax:PREAL8

	dw (type eax ) EQ (type DWORD)	;0
	dw (type [eax] ) EQ (type REAL8);-1
	dw (type eax ) EQ (type PREAL8)	;-1

assume eax:nothing

	dw (type eax ) EQ (type DWORD)	;-1
	dw (type eax ) EQ (type PREAL8)	;0

end
