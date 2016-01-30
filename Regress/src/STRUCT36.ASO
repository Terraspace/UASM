
;--- regression in v2.09
;--- a struct member with type struct/union requires a literal
;--- as initialization.

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

foo1 FOO <0>	;correct syntax is <<0>>

end
