; Issue #104: dependency-free Win64 probes.
option casemap:none
option frame:auto
option stackbase:rsp
option win64:15
.code
vectors proc vectorcall uses xmm6 xmm7, a:real8,b:real8,arg3:real8,d:real8,e:real8,f:real8
 local storage[65536]:byte
 mov storage[0],1
 ret
vectors endp
end
