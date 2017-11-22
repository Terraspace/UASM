
	.386
	.model flat, stdcall
	option casemap:none

FOO struct
m1 DWORD ?
m2 DWORD ?
FOO ends

	.data

s FOO <>

	dw opattr s.foo
	dw opattr FOO.foo
	dw opattr [eax].FOO.foo

    END
