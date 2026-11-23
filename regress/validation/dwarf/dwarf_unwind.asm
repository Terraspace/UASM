option casemap:none
ifdef PRESERVEFLAGS
 option framepreserveflags:on
endif
option sysvhome:0
option redzone:yes
.code
; No RBP frame: deliberately overwrite RBP after its USES save.
NoFrame proc uses rbp rbx r12 xmm6
 mov rbp,12345678h
 mov rbx,1234h
 mov r12,5678h
 pxor xmm6,xmm6
 test edi,edi
 jz other_return
 nop
 ret
other_return:
 nop
 ret
NoFrame endp
option sysvhome:1
Homed proc uses rbx r12 value:qword
 local storage[40]:qword
 mov rbx,55h
 mov r12,66h
 mov storage[0],rbx
 invoke NoFrame
 mov rax,value
 ret
Homed endp
option sysvhome:0
Aliased proc uses r13 value:qword, arg2:qword,arg3:qword,arg4:qword,arg5:qword,arg6:qword,stack_value:qword
 local scratch:qword
 mov rax,stack_value
 mov scratch,rax
 mov r13,77h
 invoke Homed,123
 mov rax,scratch
 ret
Aliased endp
; Red-zone leaf: no stack allocation but a real RBP frame.
option sysvhome:1
RedLeaf proc value:qword
 local scratch:qword
 mov rax,value
 mov scratch,rax
 ret
RedLeaf endp
option sysvhome:0
public main
main proc uses rbx r12 r13 r14 r15
 mov eax,1234h
 movq xmm6,rax
 mov rbx,111h
 mov r12,222h
 mov r13,333h
 mov r14,444h
 mov r15,555h
 invoke Aliased,1,2,3,4,5,6,7
 xor edi,edi
 invoke NoFrame
 invoke RedLeaf,42
 xor eax,eax
 ret
main endp
end
