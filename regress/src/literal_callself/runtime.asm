option casemap:none
option literals:on
exit proto SYSTEMV :dword
Check proto SYSTEMV :ptr,:ptr,:dword
.data
want0 label byte
 db 65,0
want1 label byte
 db 97,0
want2 label byte
 db 97,34,98,0
want3 label byte
 db 0
want4 label byte
 db 0,0
want5 label byte
 db 97,0,10,0,98,0,13,0,99,0,9,0,100,0,0,0
want6 label byte
 db 75,0,117,0,7,1,97,0,61,216,0,222,0,0
want7 label byte
 db 120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0
 db 120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0
 db 120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0
 db 120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0
 db 120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0
 db 120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0
 db 120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0
 db 120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0
 db 120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0
 db 120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0
 db 120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0
 db 120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0
 db 120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,120,0,0,0
.code
Check proc SYSTEMV p:ptr,expected:ptr,count:dword
 mov r10,p
 mov r11,expected
 mov eax,count
nextByte:
 mov dl,[r10]
 cmp dl,[r11]
 jne failed
 inc r10
 inc r11
 dec eax
 jnz nextByte
 ret
failed:
 invoke exit,1
 ret
Check endp
public main
main proc SYSTEMV 
 invoke Check,"A",ADDR want0,2
 Check("A",&want0,2)
 invoke Check,"a",ADDR want1,2
 Check("a",&want1,2)
 invoke Check,"a""b",ADDR want2,4
 Check("a""b",&want2,4)
 invoke Check,"",ADDR want3,1
 Check("",&want3,1)
 invoke Check,L"",ADDR want4,2
 Check(L"",&want4,2)
 invoke Check,L"a\nb\rc\td",ADDR want5,16
 Check(L"a\nb\rc\td",&want5,16)
 invoke Check,L"Kuća😀",ADDR want6,14
 Check(L"Kuća😀",&want6,14)
 invoke Check,L"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",ADDR want7,802
 Check(L"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",&want7,802)
 xor eax,eax
 ret
main endp
end
