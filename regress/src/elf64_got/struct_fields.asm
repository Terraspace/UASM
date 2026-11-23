option casemap:none
option elfpic:1
Payload struct
 tag dd ?
 value dd ?
Payload ends
extern item:Payload
.code
 mov eax,GOT(item.value,r11)
 mov GOT(item.value,r11),eax
 ret
end
