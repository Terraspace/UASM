; Three stack arguments plus alignment require 32 bytes of cleanup.
.code
callee proc SYSTEMV a1:qword,a2:qword,a3:qword,a4:qword,a5:qword,a6:qword,a7:qword,a8:qword,a9:qword
ret
callee endp
caller proc SYSTEMV
invoke callee,1,2,3,4,5,6,7,8,9
ret
caller endp
end

