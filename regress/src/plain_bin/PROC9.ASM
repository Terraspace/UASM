
;--- problem in v2.10-2.11
;--- if a fastcall procedure was prototyped, a "general failure" occured

	.386
	.model flat,stdcall
	option casemap:none

	.code

F1 proto fastcall :dword, :dword

F1 proc fastcall wParam:DWORD,lParam:DWORD
ret
F1 endp

end
