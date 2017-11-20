
;--- CMOVcc test

	.686
	.model flat

	.data

m8	label byte
m16	label word
m32	label dword

	.code

	cmova	ax,bx
	cmovae	bx,word ptr m16
	cmovb	ax,di
	cmovbe	ebp,dword ptr m32
	cmovc	si,di
	cmove	edx,ebp
	cmovg	ecx,m32
	cmovge	ebx,dword ptr m32
	cmovl	sp,m16
	cmovle	ecx,esp

	cmovna	eax,ebx
	cmovnae	eax,ecx
	cmovnb	eax,edx
	cmovnbe	eax,esi
	cmovnc	eax,edi
	cmovne	eax,ebp
	cmovng	ebx,m32
	cmovnge	ecx,dword ptr m32
	cmovnl	edx,m32
	cmovnle	ebp,dword ptr m32
	cmovno	esp,m32
	cmovnp	edi,dword ptr m32
	cmovns	dx,si
	cmovnz	ax,bx

	cmovo	edx,eax
	cmovp	edi,esi
	cmovpe	edi,eax
	cmovpo	edi,ebx
	cmovs	cx,bx
	cmovz	cx,si

	end
