option casemap:none
PNode typedef ptr Node
Node struct
 count sdword ?
 ratio real8 ?
 link PNode ?
 values sdword 3 dup (?)
Node ends
PPNode typedef ptr PNode
SignedCount typedef sqword
Choice union
 bits qword ?
 number real8 ?
Choice ends
Flags record lowbits:4, middlebits:4, highbits:8
.data
public GlobalScalar,GlobalDouble,GlobalArray,NodeInstance,GlobalPointer,DoublePointer,GlobalChoice,GlobalFlags
GlobalScalar SignedCount -7
GlobalDouble real8 3.25
GlobalFloat real4 1.5
GlobalArray sdword -1,2,-3
NodeInstance Node <123,6.5,0,<1,2,3>>
GlobalPointer PNode NodeInstance
DoublePointer PPNode GlobalPointer
GlobalChoice Choice <401a000000000000h>
GlobalFlags Flags <3,5,7>
align 16
GlobalVector oword 112233445566778899aabbccddeeff00h
.code
Params1 proto :qword,:real8,:ptr Node,:real4,:sqword,:qword,:qword,:qword,:qword
Clobber proc
 xor edi,edi
 xor esi,esi
 xor edx,edx
 xor ecx,ecx
 xor r8d,r8d
 xor r9d,r9d
 pxor xmm0,xmm0
 pxor xmm1,xmm1
 ret
Clobber endp
option sysvhome:0
Params0 proc arg_i:qword,arg_d:real8,arg_ptr:ptr Node,arg_f:real4,arg_s:sqword,unused:qword,extra:qword,more:qword,stackarg:qword
local local_i:SignedCount,local_d:real8,local_ptr:PNode,local_arr[3]:sdword,local_node:Node
 mov local_i,-42
 movsd xmm2,GlobalDouble
 movsd local_d,xmm2
 mov rax,arg_ptr
 mov local_ptr,rax
 mov local_arr[0],-11
 mov local_arr[4],22
 mov local_arr[8],-33
 mov local_node.count,321
 mov local_node.ratio,0
 mov local_node.link,rax
 mov local_node.values[0],4
 mov local_node.values[4],5
 mov local_node.values[8],6
 mov rax,arg_i
 movsd xmm2,arg_d
 movss xmm2,arg_f
 mov rax,arg_s
 mov rax,stackarg
public Params0Ready
Params0Ready::
 nop
 xor eax,eax
 ret
Params0 endp
option sysvhome:1
Params1 proc arg_i:qword,arg_d:real8,arg_ptr:ptr Node,arg_f:real4,arg_s:sqword,unused:qword,extra:qword,more:qword,stackarg:qword
local local_i:SignedCount,local_d:real8,local_ptr:PNode,local_arr[3]:sdword,local_node:Node
 invoke Clobber
 mov local_i,-42
 movsd xmm2,GlobalDouble
 movsd local_d,xmm2
 mov rax,arg_ptr
 mov local_ptr,rax
 mov local_arr[0],-11
 mov local_arr[4],22
 mov local_arr[8],-33
 mov local_node.count,321
 mov local_node.ratio,0
 mov local_node.link,rax
 mov local_node.values[0],4
 mov local_node.values[4],5
 mov local_node.values[8],6
 mov rax,arg_i
 movsd xmm2,arg_d
 movss xmm2,arg_f
 mov rax,arg_s
 mov rax,stackarg
public Params1Ready
Params1Ready::
 nop
 xor eax,eax
 ret
Params1 endp
option sysvhome:1
VectorHome proc vec:oword
 local local_vec:oword
 invoke Clobber
 movdqu xmm2,vec
 movdqu local_vec,xmm2
public VectorReady
VectorReady::
 nop
 xor eax,eax
 ret
VectorHome endp
option sysvhome:0
Unused0 proc untouched:qword
 mov rax,rdi
 ret
Unused0 endp
option sysvhome:1
Unused1 proc untouched:qword
 mov rax,rdi
 ret
Unused1 endp
option redzone:yes
option sysvhome:1
HomeLeaf proc input_value:qword
 local leaf_value:qword
 mov rax,input_value
 inc rax
 mov leaf_value,rax
public HomeLeafReady
HomeLeafReady::
 nop
 ret
HomeLeaf endp
FloatStack proc a0:real8,a1:real8,a2:real8,a3:real8,a4:real8,a5:real8,a6:real8,a7:real8,a8:real8
 movsd xmm9,a8
public FloatStackReady
FloatStackReady::
 nop
 ret
FloatStack endp
option sysvhome:0
public main
main proc
 invoke Params0,42,GlobalDouble,addr NodeInstance,GlobalFloat,-9,77,88,99,1234
 invoke Params1,42,GlobalDouble,addr NodeInstance,GlobalFloat,-9,77,88,99,1234
 invoke VectorHome,GlobalVector
 invoke HomeLeaf,42
 invoke FloatStack,GlobalDouble,GlobalDouble,GlobalDouble,GlobalDouble,GlobalDouble,GlobalDouble,GlobalDouble,GlobalDouble,GlobalDouble
 xor eax,eax
 ret
main endp
end
