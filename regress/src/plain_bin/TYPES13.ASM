
;--- some more type compares
;--- support added in v2.10

.386
.model flat, stdcall
option casemap :none

S1 struct
x DWORD ?
S1 ends
PS1 typedef ptr S1
PPS1 typedef ptr PS1

	.data?
g_pS1	PS1 ?
g_ppS1	PPS1 ?
	.code
main proc
	LOCAL l_pS1:PS1
	LOCAL l_pS1i:ptr S1
	LOCAL l_ppS1:PPS1
	LOCAL l_ppS1i:ptr PS1

	dw (type g_pS1)   EQ (type PS1)
	dw (type l_pS1)   EQ (type PS1)
	dw (type l_pS1i)  EQ (type PS1)
	dw (type PS1 ptr esi) EQ (type PS1)
	dw (type g_ppS1)  EQ (type PPS1)
	dw (type l_ppS1)  EQ (type PPS1)
	dw (type l_ppS1i) EQ (type PPS1)
	dw (type PPS1 ptr esi) EQ (type PPS1)
	dw (type [PS1 ptr esi]) EQ (type S1)

main endp
end

