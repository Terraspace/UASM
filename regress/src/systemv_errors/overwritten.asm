.code
p proto SYSTEMV a:qword,b:qword
q proto SYSTEMV a1:qword,a2:qword,a3:qword,a4:qword,a5:qword,a6:qword,a7:qword,f:real8
run_tests proc SYSTEMV
invoke p,1,[rbx+rdi]
invoke q,1,2,3,4,5,6,rax,1.5
invoke q,1,2,3,4,5,6,rsp,1.5
ret
run_tests endp
end
