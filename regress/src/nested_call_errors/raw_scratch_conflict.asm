option casemap:none
option stackbase:rsp
option win64:15
option frame:auto
option vtable:on
Identity proto (dword) :dword
COMINTERFACE ITest
ENDCOMINTERFACE
RAWINTERFACE Raw
 STDFUNC Value, <DWORD>, :DWORD
 STDFUNC Nothing, <VOIDARG>
ENDRAWINTERFACE
PRaw typedef ptr Raw
PExample typedef ptr ITest
.data
rawPtr PRaw 0
obj PExample 0
.code
RunCase proc frame
 rawPtr->Value(r11d)
 ret
RunCase endp
end
