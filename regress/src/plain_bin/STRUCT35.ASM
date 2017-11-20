
;--- regression in v2.09
;--- if a struct member was an alias for another struct/union
;--- it was not properly initialized.

	.386
	.model flat, stdcall
	option casemap:none

PRTL_CRITICAL_SECTION_DEBUG typedef ptr
HANDLE typedef ptr
ULONG_PTR typedef DWORD

RTL_CRITICAL_SECTION struct
DebugInfo       PRTL_CRITICAL_SECTION_DEBUG ?
LockCount       SDWORD ?
RecursionCount  SDWORD ?
OwningThread    HANDLE ?
LockSemaphore   HANDLE ?
SpinCount       ULONG_PTR ?
RTL_CRITICAL_SECTION ends

CRITICAL_SECTION typedef RTL_CRITICAL_SECTION

FOO STRUCT QWORD
f1	CRITICAL_SECTION <>
FOO ENDS

	.data

foo1 FOO <>
foo2 FOO <<0,1,2,0,0,5>>

end
