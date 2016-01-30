
	.386

_TEXT16 segment use16 'CODE'
	enter 0,0
	enter 1000h,5
	enter 0ffffh,255
	enter 0ffffh,-1
	enter word ptr 0,0
_TEXT16 ends

_TEXT32 segment use32 'CODE'
	enter 0,0
	enter 1000h,5
	enter -1,-1
	enter word ptr 0,0
_TEXT32 ends

	end
