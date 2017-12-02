
;--- to move segments with the FLAT attribute to another group
;--- was rejected prior to v2.09.
;--- Since Masm allows this, this is now ok.

	.386

CODE1 segment BYTE flat 'CODE'
	db 1
CODE1 ends

CODE2 segment BYTE flat 'CODE'
	db 2
CODE2 ends

CGROUP group CODE1, CODE2

end
