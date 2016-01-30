
;--- test equates with numeric argument that became text macros

X1 equ 112233445566h
X3 equ -1

X2 catstr X1	;catstr works with text items only

_DATA segment
	dq X1
	dq X3
_DATA ends

	end
