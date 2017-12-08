
;--- test more complicated externals

	.286
	.model small,c
	.386
	option casemap:none
	.stack 100h

	includelib <extern6.lib>

NPSTR typedef ptr SBYTE
LPSTR typedef far ptr SBYTE
NPSTR32 typedef near32 ptr SBYTE
LPSTR32 typedef far32  ptr SBYTE

externdef ps1:NPSTR
externdef ps2:LPSTR
externdef ps3:NPSTR32
externdef ps4:LPSTR32

externdef ps5:ptr SBYTE
externdef ps6:far ptr SBYTE
externdef ps7:near32 ptr SBYTE
externdef ps8:far32 ptr SBYTE

externdef ps9:near ptr SBYTE
externdef ps10:far16 ptr SBYTE

	.code

	mov ax,ps1
	lds ax,ps2
	mov eax,ps3
	lds eax,ps4

	mov ax,ps5
	lds ax,ps6
	mov eax,ps7
	lds eax,ps8

	mov ax,ps9
	lds ax,ps10

start:
	mov ah,4ch
	int 21h

	end start
