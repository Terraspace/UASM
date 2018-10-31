
	.386
	.model flat
	.code

push 1234567890.1234567890    	; OK

mov REAL4 ptr [esp], 789.654    ; OK
add REAL4 ptr [esp], 111.111    ; fails
fld dword ptr [esp]

end