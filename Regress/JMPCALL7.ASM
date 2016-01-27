
;--- an indirect branch with JMP/CALL doesn't need
;--- a size if a NEAR/FAR label is found in the expression

	.386

_TEXT16 segment use16 'CODE'
calltable16 label near
_TEXT16 ends

_TEXT segment use32 'CODE'

calltable label near

	assume ds:_TEXT
	call [offset calltable + esi*4]
	call [calltable + esi*4]
	call [esi*4][calltable]
	assume ds:_TEXT16
	call [esi*2][calltable16]

;--- type coercion
	assume ds:_TEXT
	call dword ptr [esi*4][calltable]
	call near32 ptr [esi*4][calltable]
	assume ds:_TEXT16
	call word ptr [esi*4][calltable16]
	call near16 ptr [esi*4][calltable16]

;--- these need a size
	call dword ptr [esi*4]
	call near ptr [esi*4]
	call near16 ptr [esi*2]
	call far16 ptr [esi*4]   ;Masm won't do it right (NEAR32)

;--- error
;	call [esi*4]

_TEXT ends

	end
