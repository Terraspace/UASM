; Microsoft vectorcall requires a fixed prototype; VARARG is not permitted.
option casemap:none
bad_proto proto vectorcall :qword,:vararg
.code
bad_proc proc vectorcall first:qword,rest:vararg
ret
bad_proc endp
end
