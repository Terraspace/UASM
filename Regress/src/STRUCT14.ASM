
;--- calculation of field offset if 
;--- the base is a type (not a variable) and the
;--- first member also has a struct type.
;--- was a problem in v2.05-

	.386
	.model flat,stdcall

S1 struct
	db ?
f2	dd ?
S1 ends

S2 struct
	dw ?
f1	dd ?
m2	S1 <>
S2 ends

S3 struct
	dd ?
m1	S2 <>
S3 ends

	.code

	mov eax, offset S3.m1.f1
	mov eax, S3.m1.f1

	mov eax, offset S3.m1.m2.f2
	mov eax, S3.m1.m2.f2
	ret

	end
