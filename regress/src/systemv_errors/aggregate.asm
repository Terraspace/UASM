pair struct
x qword ?
y qword ?
pair ends
.code
p proc SYSTEMV value:pair
ret
p endp
sink proto SYSTEMV tag:qword,args:vararg
.data
value pair <>
.code
invoke sink,0,value
end
