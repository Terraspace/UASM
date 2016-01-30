
;--- imagerel and sectionrel operators
;--- not for OMF

	.386
	.model flat
	option casemap:none

	.code

;--- imagerel and sectionrel accept relocatable labels only!

	push offset 0		;ok
	push offset DWORD	;ok
	push offset ds:[0]	;ok
	push imagerel 0
	push imagerel DWORD
	push imagerel ds:[0]	;should be rejected
	push sectionrel 0
	push sectionrel DWORD
	push sectionrel ds:[0]	;should be rejected

end
