
;--- test external with PROTO qualified type
;--- gives assembly errors

	.386
	.model flat, stdcall

externdef p1: proto :dword, :dword
externdef p2: proto :dword, :dword
extern    p3: proto :dword, :dword
extern    p4: proto :dword, :dword

	.code

p1 proc a1:dword, a2:dword
	ret
p1 endp

p3 proc a1:dword, a2:dword
	ret
p3 endp

	end
