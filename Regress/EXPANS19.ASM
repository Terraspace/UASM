
;--- & operator in "line expansion" lines

	.386
	.MODEL FLAT, stdcall
	option casemap:none

te1 textequ <4>
te2 textequ <3>
te3 textequ <2>

	.code

;--- all variants are valid syntax

%	mov eax,te1&te2&te3
%	mov eax,&te1&te2&te3
%	mov eax,&te1&te2&te3&
%	mov eax,&te1&&te2&te3&
%	mov eax,&te1&&te2&&te3&

	end
