; Minimal Win64 API declarations used by the OO assembly fixtures.
; These fixtures assemble objects only; no SDK or import libraries are needed.
NULL EQU 0
STD_OUTPUT_HANDLE EQU -11
pfn_GetStdHandle TYPEDEF PROTO :DWORD
EXTERNDEF __imp_GetStdHandle:PTR pfn_GetStdHandle
GetStdHandle EQU <__imp_GetStdHandle>
pfn_lstrlenA TYPEDEF PROTO :PTR
EXTERNDEF __imp_lstrlenA:PTR pfn_lstrlenA
lstrlenA EQU <__imp_lstrlenA>
pfn_WriteConsoleA TYPEDEF PROTO :QWORD, :PTR, :DWORD, :PTR, :PTR
EXTERNDEF __imp_WriteConsoleA:PTR pfn_WriteConsoleA
WriteConsoleA EQU <__imp_WriteConsoleA>
pfn_GetProcessHeap TYPEDEF PROTO 
EXTERNDEF __imp_GetProcessHeap:PTR pfn_GetProcessHeap
GetProcessHeap EQU <__imp_GetProcessHeap>
pfn_HeapAlloc TYPEDEF PROTO :QWORD, :DWORD, :QWORD
EXTERNDEF __imp_HeapAlloc:PTR pfn_HeapAlloc
HeapAlloc EQU <__imp_HeapAlloc>
pfn_HeapFree TYPEDEF PROTO :QWORD, :DWORD, :PTR
EXTERNDEF __imp_HeapFree:PTR pfn_HeapFree
HeapFree EQU <__imp_HeapFree>
lstrlen EQU <lstrlenA>
WriteConsole EQU <WriteConsoleA>
