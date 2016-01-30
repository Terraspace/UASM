
;--- SIZE, LENGTH operators with externals
;--- also external prototypes and function pointers

	.286
	.model small, stdcall
	.dosseg
	.386
	option casemap:none

	.stack 100h

	includelib <extern7.lib>

VOID struct
VOID ends
S1 struct
F1 db 5 dup (?)
S1 ends
S2 struct
F2 db 5 dup (?)
S2 ends

TP1 typedef proto :word
TP2 typedef proto far :word
TP3 typedef proto far16 :word
TP4 typedef proto far32 :dword
PTP1 typedef ptr TP1
PTP2 typedef ptr TP2
PTP3 typedef ptr TP3
PTP4 typedef ptr TP4

extern    e1:byte
extern    e3:ptr byte
extern    e3:near ptr byte
extern    e4:far ptr byte
extern    e5:S1
extern    e6:VOID
extern    e10:TP1
extern    e11:TP2
extern    e12:TP3
extern    e13:TP4
extern    e14:PTP1
extern    e15:PTP2
extern    e16:PTP3
extern    e17:PTP4
extern    e20:proto :WORD
extern    e21:proto far :WORD
extern    e22:proto far16 :WORD
extern    e23:proto far32 :DWORD

extern    e1:byte
extern    e2:ptr byte
extern    e3:near ptr byte
extern    e4:far ptr byte
extern    e5:S1
extern    e6:VOID
extern    e10:TP1
extern    e11:TP2
extern    e12:TP3
extern    e13:TP4
extern    e14:PTP1
extern    e15:PTP2
extern    e16:PTP3
extern    e17:PTP4
extern    e20:proto :WORD
extern    e21:proto far :WORD
extern    e22:proto far16 :WORD
extern    e23:proto far32 :DWORD

	.code

	dw length e1,    size e1
	dw length e2,    size e2
	dw length e3,    size e3
	dw length e4,    size e4
	dw length e5,    size e5
	dw length e6,    size e6
	dw length e10,   size e10
	dw length e11,   size e11
	dw length e12,   size e12
	dw length e13,   size e13
	dw length e14,   size e14
	dw length e15,   size e15
	dw length e16,   size e16
	dw length e17,   size e17
	dw length e20,   size e20
	dw length e21,   size e21
	dw length e22,   size e22
	dw length e23,   size e23

	invoke e10, ax
	invoke e11, ax
	invoke e12, ax
	invoke e13, eax
	invoke e14, ax
	invoke e15, ax
	invoke e16, ax
	invoke e17, eax
	invoke e20, ax
	invoke e21, ax
	invoke e22, ax
	invoke e23, eax

start:
	mov ah,4ch
	int 21h

	end start
