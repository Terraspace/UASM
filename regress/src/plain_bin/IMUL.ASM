
;--- due to its 3 argument format,
;--- IMUL needs special treatment in the parser.

	.286
	.model small

	.data

vb  label byte
vw  label word
vd	label dword

	.code

	imul  bl
	imul  [vb]	;byte operand is only valid in the one-operand format
	imul  [vw]
	imul  [vwx]

	imul  ax,3
	imul  ax,-127
	imul  ax,1234h
	imul  ax,-129
	.386
	imul  eax,3
	imul  eax,-127
	imul  eax,12345678h
	imul  eax,-129
	imul  [vd]
	imul  [vdx]

if 0
;--- if first operand is memory, no second op is allowed
;--- this was accepted by JWasm v2.05-
	imul [vb],1
	imul [vw],2
	imul [vd],3
endif
if 0
;--- byte operand is only allowed if single
;--- this was also accepted by JWasm v2.05-
	imul  al,bl
	imul  al,[vb]
	imul  al,[vbx]
endif
	imul  ax,bx
	imul  ax,[vw]
	imul  ax,[vwx]
	imul  eax,ebx
	imul  eax,[vd]
	imul  eax,[vdx]

;--- 3. operand is (imm8)
	imul  ax,bx,2
	imul  ax,[vw],2
	imul  ax,[vwx],2
	imul  ax,bx,-127
	imul  ax,[vw],-127
	imul  ax,[vwx],-127
	imul  eax,ebx,127
	imul  eax,[vd],127
	imul  eax,[vdx],127
	imul  eax,ebx,-128
	imul  eax,[vd],-128
	imul  eax,[vdx],-128

;--- 3. operand is (imm16/32)
	imul  ax,bx,128
	imul  ax,[vw],128
	imul  ax,[vwx],128
	imul  ax,bx,1234h
	imul  ax,[vw],1234h
	imul  ax,[vwx],1234h
	imul  ax,bx,-129
	imul  ax,[vw],-129
	imul  ax,[vwx],-129
	imul  eax,ebx,12345678h
	imul  eax,[vd],12345678h
	imul  eax,[vdx],12345678h
	imul  eax,ebx,-129
	imul  eax,[vd],-129
	imul  eax,[vdx],-129

	ret

	.data

vbx	label byte
vwx	label word
vdx	label dword

    END
