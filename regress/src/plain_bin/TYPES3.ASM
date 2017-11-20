
;--- type expressions with EQ/NE operator

	.386
	.model flat

UINT typedef DWORD
PUINT typedef ptr DWORD
PVOID typedef ptr

	.code

	db (type(dword ptr [edx])) eq DWORD
	db (type(dword ptr [edx])) eq REAL4
	db (type(byte ptr [edx]))  eq BYTE
	db (type(byte ptr [edx]))  eq SBYTE
	db (type(sword ptr [edx])) eq SWORD
	db (type(sword ptr [edx])) eq WORD
	db (type(real4 ptr [edx])) ne REAL8
	db (type(qword ptr [edx])) ne qword
	db (type(UINT ptr [edx]))  eq UINT
	db (type(DWORD ptr [edx])) eq UINT	;exp: TRUE
	db (type(SDWORD ptr [edx])) eq UINT
	db (type(PUINT ptr [edx])) eq PUINT
	db (type(PVOID ptr [edx])) eq PVOID
	db (type(PVOID ptr [edx])) eq PUINT	;exp: FALSE

	end
