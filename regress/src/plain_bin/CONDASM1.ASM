
;--- labels preceding conditional assembly directives

_TEXT segment 'CODE'

l1:if 1
	mov al,1
l2:else
  if 1
	mov al,2
  else
	mov al,3
  endif
endif ;no label possible

if 0
	mov al,1
else  ;no label possible
	mov al,3
l4:endif

_TEXT ends

	end
