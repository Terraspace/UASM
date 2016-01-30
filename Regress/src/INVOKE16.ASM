
;--- invoke member, base register AFTER struct.type

	.386
	.model flat, stdcall

NULL equ 0

prCreateDevice   typedef proto :PTR ,:dword,:dword,:dword
lpCreateDevice   typedef ptr prCreateDevice

IDirectInputA struct
		dd ?
		dd ?
		dd ?
CreateDevice lpCreateDevice ?
IDirectInputA ends

	.code

if 1 ;this always worked
	INVOKE [edx].IDirectInputA.CreateDevice, NULL, NULL, NULL, NULL
endif
if 1 ;this didn't work in v2.05 (GPF) and v1.96-v2.04
	INVOKE IDirectInputA.CreateDevice[edx], NULL, NULL, NULL, NULL
endif
	ret

end
