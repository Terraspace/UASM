option casemap:none
option frame:auto
option stackbase:rsp
option win64:15
ExitProcess proto (void) :dword
NextValue proto (dword)
Sum32 proto (dword) :dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword
.data
counter dword 0
.code
NextValue proc
 inc counter
 mov eax,counter
 mov ecx,1234
 mov edx,5678
 ret
NextValue endp
Sum32 proc a0:dword,a1:dword,a2:dword,a3:dword,a4:dword,a5:dword,a6:dword,a7:dword,a8:dword,a9:dword,a10:dword,a11:dword,a12:dword,a13:dword,a14:dword,a15:dword,a16:dword,a17:dword,a18:dword,a19:dword,a20:dword,a21:dword,a22:dword,a23:dword,a24:dword,a25:dword,a26:dword,a27:dword,a28:dword,a29:dword,a30:dword,a31:dword
 xor eax,eax
 add eax,a0
 add eax,a1
 add eax,a2
 add eax,a3
 add eax,a4
 add eax,a5
 add eax,a6
 add eax,a7
 add eax,a8
 add eax,a9
 add eax,a10
 add eax,a11
 add eax,a12
 add eax,a13
 add eax,a14
 add eax,a15
 add eax,a16
 add eax,a17
 add eax,a18
 add eax,a19
 add eax,a20
 add eax,a21
 add eax,a22
 add eax,a23
 add eax,a24
 add eax,a25
 add eax,a26
 add eax,a27
 add eax,a28
 add eax,a29
 add eax,a30
 add eax,a31
 ret
Sum32 endp
Start proc frame
 invoke Sum32,NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue(),NextValue()
 cmp eax,528
 jne failed
 invoke ExitProcess,0
failed:
 invoke ExitProcess,1
 ret
Start endp
end
