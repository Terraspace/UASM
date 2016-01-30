
;--- test various LABEL arguments

	.286
	.model small, stdcall
	option casemap:none
	.386

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
PTP1 typedef ptr TP1
PTP2 typedef ptr TP2
PTP3 typedef ptr TP3

	.code

l1	label byte
l2	label ptr byte
l3	label near ptr byte
l4	label far ptr byte
l5	label S1
l6	label VOID
l10	label TP1
l11	label TP2
l12	label TP3
l13	label PTP1
l14	label PTP2
l15	label PTP3

	invoke l10, ax
	invoke l11, ax
	invoke l12, ax
	invoke l13, ax
	invoke l14, ax
	invoke l15, ax

	end
