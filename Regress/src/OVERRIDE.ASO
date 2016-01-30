
	.386
	.MODEL flat

	.code

lbl1:
	mov eax,[cs:ebx]                     ;mf      znef
	mov eax,[cs:ebx+edx]                 ;mf      znef
	mov eax,[ebx+es:edx]                 ;mf      znef
	mov eax,[cs:ebx+es:edx]              ;mf jf   znef

	mov eax,[ebx+es:lbl1]                ;
	mov eax,[cs:ebx+es:lbl1]             ;mf jf   znef
	mov eax,[ebx+offset es:lbl1]         ;
	mov eax,[cs:ebx+offset es:lbl1]      ;mf jf   znef

	mov eax,[ebx+FLAT:lbl1]
	mov eax,[cs:ebx+FLAT:lbl1]           ;mf jf   znef    ( was ok with v2.07a )
	mov eax,[ebx+offset FLAT:lbl1]
	mov eax,[cs:ebx+offset FLAT:lbl1]    ;mf jf   znef    ( was ok with v2.07a ) 

	end
