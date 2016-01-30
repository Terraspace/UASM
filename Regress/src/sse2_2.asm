
;--- v2.07: more compatible Masm SSE syntax check for mem ops
;
	.686p
	.model flat
	.xmm

	.code

	paddb    mm6,byte ptr  [ebx]	;new
	paddb    mm6,qword ptr [ebx]
	paddb   xmm6,byte ptr  [ebx]	;new
	paddb   xmm6,oword ptr [ebx]
	paddsb   mm6,byte ptr  [ebx]	;new
	paddsb   mm6,qword ptr [ebx]
	paddsb  xmm6,byte ptr  [ebx]	;new
	paddsb  xmm6,oword ptr [ebx]
	paddusb  mm6,byte ptr  [ebx]	;new
	paddusb  mm6,qword ptr [ebx]
	paddusb xmm6,byte ptr  [ebx]	;new
	paddusb xmm6,oword ptr [ebx]

	paddw    mm6,word ptr  [ebx]	;new
	paddw    mm6,qword ptr [ebx]
	paddw   xmm6,word ptr  [ebx]	;new
	paddw   xmm6,oword ptr [ebx]
	paddsw   mm6,word ptr  [ebx]	;new
	paddsw   mm6,qword ptr [ebx]
	paddsw  xmm6,word ptr  [ebx]	;new
	paddsw  xmm6,oword ptr [ebx]
	paddusw  mm6,word ptr  [ebx]	;new
	paddusw  mm6,qword ptr [ebx]
	paddusw xmm6,word ptr  [ebx]	;new
	paddusw xmm6,oword ptr [ebx]

	paddd    mm6,dword ptr [ebx]	;new
	paddd    mm6,qword ptr [ebx]
	paddd   xmm6,dword ptr [ebx]	;new
	paddd   xmm6,oword ptr [ebx]

	paddq   xmm6,qword ptr [ebx]	;new
	paddq   xmm6,oword ptr [ebx]

    end
