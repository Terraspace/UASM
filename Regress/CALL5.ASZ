
;--- type coercion far -> near and change in offset size

	.386

	includelib <call5.lib>

externdef xxx:far

_TEXT16 segment use16 'CODE'
start:
    call near32 ptr xxx
_TEXT16 ends

_TEXT32 segment use32 'CODE'
    call near16 ptr xxx
_TEXT32 ends

_STACK segment stack 'STACK'
	db 100h dup (?)
_STACK ends

end start
