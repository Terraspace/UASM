
;--- ALIAS segment attribute for COFF/ELF

	.486
	.model flat, stdcall
	option casemap:none

	.code

pdata1 segment ALIAS(".pdata")
	db 1
pdata1 ends 

pdata2 segment ALIAS(".pdata")
	db 2
pdata2 ends 

pdata3 segment ALIAS(".pdata")
	db 3
pdata3 ends 

	end
