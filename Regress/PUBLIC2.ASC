
;--- publics for OMF

	.286
	.model small
	.386

	public E1, E2, E3, E4, E5

E1  equ 1
E2  equ 10000h
E3  equ -1
E4  equ 0ffffffffh

s1 segment 'code'
p11 proc
	ret
p11 endp
p12 proc
	ret
p12 endp
s1 ends
s2 segment use32 'code'
	org 10000h
p21 proc
	ret
p21 endp
p22 proc
	ret
p22 endp
s2 ends
s3 segment use32 'code'
	org 0ffffh
p31 proc
	ret
p31 endp
p32 proc
	ret
p32 endp
p33 proc
	ret
p33 endp
s3 ends

E5 equ p33

end
