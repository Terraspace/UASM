
	.386
	.model flat,stdcall
	option casemap:none

FOO STRUCT
  bar dd 0
FOO ENDS

	.code

bar dd 0

	push [foo.bar]    ;<--- Error: structure field expected in v2.08-2.10

foo FOO <>

end
