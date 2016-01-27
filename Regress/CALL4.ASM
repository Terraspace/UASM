
;--- calling an external with a MT_PTR coercion
;--- didn't work in v2.06-2.09. See parser.c, SetPtrMemtype().

	.386
	.model flat, stdcall

proto_func TYPEDEF PROTO C :DWORD
LPFNFUNC TYPEDEF PTR proto_func

EXTERNDEF extf1:DWORD

	.code

	call LPFNFUNC ptr extf1

extf1 dd 0

end
