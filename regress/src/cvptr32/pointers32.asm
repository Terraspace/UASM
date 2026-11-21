.386
.model flat,c
option casemap:none
PBYTE typedef ptr byte
PSBYTE typedef ptr sbyte
PVOID typedef ptr
Item STRUCT
 value DWORD ?
Item ENDS
PITEM typedef ptr Item
PNODE typedef ptr Node
Node STRUCT
 next PNODE ?
 item PITEM ?
Node ENDS
Holder STRUCT
 pb PBYTE ?
 ps PSBYTE ?
 pv PVOID ?
 pi PITEM ?
 pn PNODE ?
Holder ENDS
.data
sample Holder <>
nodeValue Node <>
.code
entry PROC
 ret
entry ENDP
END
