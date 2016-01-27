
;--- test invoke with stack arguments
;--- was a problem in v2.03 for -win64

ifdef __JWASM__
	.x64
	.model flat, fastcall
endif

	.code

p2 proc a1:qword,a2:dword,a3:dword,a4:qword,a5:dword,a6:dword,a7:qword
p2  endp

p1 proc pFname:qword, dAccess:dword, dShare:dword, pSecurity:qword, dDist:dword, dAttrib:dword, hTemplate:qword
	invoke p2, pFname, dAccess, dShare, pSecurity, dDist, dAttrib, hTemplate
	ret
p1 endp

	end
