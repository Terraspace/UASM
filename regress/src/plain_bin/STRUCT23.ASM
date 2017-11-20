
;--- struct contains fields with negative offsets
;--- didn't fully work prior to v2.07

	.286
	.model small

S1 struct 
	org -8
	dd ?
f1  dd ?
f2	dd ?
S1	ends

	.code

	mov ax,sizeof S1
	mov ax,S1
	mov ax,S1.f1

	end
