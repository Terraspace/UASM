
if type near eq 0ff02h
	.x64
	.model flat
endif

	.code

	movsb
	movsb byte ptr [edi], [esi]
	movsb byte ptr [rdi], [rsi]
	movsw
	movsd
	movsq qword ptr [edi], [esi]
	movsq qword ptr [rdi], [rsi]
	movs byte ptr [edi], [esi]
	movs byte ptr [rdi], [rsi]
	movs m08, m08
	movs m16, m16
	movs m64, m64

	stosb
	stosb byte ptr [edi]
	stosb byte ptr [rdi]
	stosw
	stosd
	stosq
	stos byte ptr [edi]
	stos byte ptr [rdi]
	stos m08
	stos m16
	stos m64

	ins byte  ptr [edi],dx
	ins word  ptr [edi],dx
	ins dword ptr [edi],dx
	ins byte  ptr [rdi],dx
	ins word  ptr [rdi],dx
	ins dword ptr [rdi],dx
	ins m08,dx
	ins m16,dx
	ins m32,dx

	insb
	insw
	insd
	insb [edi],dx
	insw [edi],dx
	insd [edi],dx
	insb [rdi],dx
	insw [rdi],dx
	insd [rdi],dx

	outs dx, byte  ptr [esi]
	outs dx, word  ptr [esi]
	outs dx, dword ptr [esi]
	outs dx, byte  ptr [rsi]
	outs dx, word  ptr [rsi]
	outs dx, dword ptr [rsi]
	outs dx,m08
	outs dx,m16
	outs dx,m32

	outsb
	outsw
	outsd
	outsb dx,[esi]
	outsw dx,[esi]
	outsd dx,[esi]
	outsb dx,[rsi]
	outsw dx,[rsi]
	outsd dx,[rsi]

	outsb dx,[esi]
	outsw dx,[esi]
	outsd dx,[esi]
	outsb dx,[rsi]
	outsw dx,[rsi]
	outsd dx,[rsi]

m08 label byte
m16 label word
m32 label dword
m64 label qword

	end
