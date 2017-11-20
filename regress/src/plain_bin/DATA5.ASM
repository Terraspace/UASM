
;--- size of array in structure defined by initializer.
;--- must be padded with spaces ( except if curr segment is bss)!

	.386
	.model flat

S1 STRUCT
f1     BYTE 'abcdefgh'
f2     WORD -1
S1 ENDS

	.DATA

v1   S1 <>
v2   S1 <'xxxxx', 1234h>
v3   S1 <"", >

	.DATA?

;--- Masm will fail to define this item correctly!
v4   S1 <<?>,?>

end
