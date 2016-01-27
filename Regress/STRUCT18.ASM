
;--- field names of anonymous struct/union members

	.286
	.model small

LARGE_INTEGER union

struct
LowPart  DWORD  0
HighPart SDWORD 0
ends

struct u
LowPart  DWORD  ?
HighPart SDWORD ?
ends

QuadPart QWORD  ?
LARGE_INTEGER ends

	.data

v1	LARGE_INTEGER <>

	end
