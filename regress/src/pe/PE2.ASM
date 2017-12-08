
;--- -pe format test
;--- program uses imports, empty sections
;--- and linker info section .drectve

	.386
	.model flat, stdcall	;-pe requires a .model flat directive

;--- define 2 import directories
ifdef __ASMC__
	option dllimport:<kernel32.dll>
endif
ExitProcess proto :dword
ifdef __ASMC__
	option dllimport:<user32.dll>
endif
IsCharUpperA proto :dword
ifdef __ASMC__
	option dllimport:none
endif

;--- linker info - must not appear in the binary
	option dotname
.drectve segment info
	db "-subsystem:console "
.drectve ends

;--- empty section - must not appear in the binary
XXX	segment
XXX	ends

	.code
start:
	mov eax,'a'
	invoke IsCharUpperA, eax
	invoke ExitProcess, eax
	ret
end start
