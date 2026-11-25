.x64
.model flat,fastcall
option stackbase:rsp
option win64:15
option frame:auto
option casemap:none
.data
data_name dd 1234h
.code
label_name:
 nop
constant_name equ 9
type_name typedef dword
RecordName record record_field:8
StructName struct
 field dd ?
StructName ends
helper proto
First proto :dword,:dword,:dword,:dword
First proc data_name:dword,constant_name:dword,type_name:dword,label_name:dword
 LOCAL helper:dword,StructName:dword,record_field:dword
 mov eax,data_name
 add eax,1
 mov eax,constant_name
 add eax,2
 mov eax,type_name
 add eax,3
 mov eax,label_name
 add eax,4
 mov helper,eax
 mov eax,helper
 mov StructName,eax
 mov eax,StructName
 mov record_field,eax
 mov eax,record_field
 ret
First endp
Second proc data_name:dword
 LOCAL constant_name:dword
 mov eax,data_name
 mov constant_name,eax
 ret
Second endp
 mov eax,data_name
 mov eax,constant_name
 mov eax,TYPE type_name
 mov eax,SIZEOF StructName
 mov eax,MASK record_field
end
