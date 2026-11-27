; C-style operators must emit the same code as INVOKE expressions.
; EXP: pre-fix INVOKE equivalents; final nested call uses constants 95,8,5,2.
; Each expression is exercised in every argument position.
option casemap:none
option sysvhome:1
MB_OK equ 0
MB_ICONERROR equ 40h
Flags equ 55h
Bits equ 0fh
namespace Ns
Value equ 100h
endnamespace
ItemType struct
 value dd ?
ItemType ends
.data
item ItemType <7>
array dd 1,2,3
.code
Target proto SYSTEMV :dword,:dword,:dword,:dword
Inner proto SYSTEMV (dword) :dword
Caller proc SYSTEMV 
 Target(MB_OK or MB_ICONERROR,5,7,9)
 Target(3,MB_OK or MB_ICONERROR,7,9)
 Target(3,5,MB_OK or MB_ICONERROR,9)
 Target(3,5,7,MB_OK or MB_ICONERROR)
 Target(Flags AND Bits,5,7,9)
 Target(3,Flags AND Bits,7,9)
 Target(3,5,Flags AND Bits,9)
 Target(3,5,7,Flags AND Bits)
 Target(Flags XOR Bits,5,7,9)
 Target(3,Flags XOR Bits,7,9)
 Target(3,5,Flags XOR Bits,9)
 Target(3,5,7,Flags XOR Bits)
 Target(NOT Bits,5,7,9)
 Target(3,NOT Bits,7,9)
 Target(3,5,NOT Bits,9)
 Target(3,5,7,NOT Bits)
 Target(1 SHL 5,5,7,9)
 Target(3,1 SHL 5,7,9)
 Target(3,5,1 SHL 5,9)
 Target(3,5,7,1 SHL 5)
 Target(128 SHR 2,5,7,9)
 Target(3,128 SHR 2,7,9)
 Target(3,5,128 SHR 2,9)
 Target(3,5,7,128 SHR 2)
 Target(17 MOD 5,5,7,9)
 Target(3,17 MOD 5,7,9)
 Target(3,5,17 MOD 5,9)
 Target(3,5,7,17 MOD 5)
 Target(Flags EQ Bits,5,7,9)
 Target(3,Flags EQ Bits,7,9)
 Target(3,5,Flags EQ Bits,9)
 Target(3,5,7,Flags EQ Bits)
 Target(Flags NE Bits,5,7,9)
 Target(3,Flags NE Bits,7,9)
 Target(3,5,Flags NE Bits,9)
 Target(3,5,7,Flags NE Bits)
 Target(Flags LT Bits,5,7,9)
 Target(3,Flags LT Bits,7,9)
 Target(3,5,Flags LT Bits,9)
 Target(3,5,7,Flags LT Bits)
 Target(Flags LE Bits,5,7,9)
 Target(3,Flags LE Bits,7,9)
 Target(3,5,Flags LE Bits,9)
 Target(3,5,7,Flags LE Bits)
 Target(Flags GT Bits,5,7,9)
 Target(3,Flags GT Bits,7,9)
 Target(3,5,Flags GT Bits,9)
 Target(3,5,7,Flags GT Bits)
 Target(Flags GE Bits,5,7,9)
 Target(3,Flags GE Bits,7,9)
 Target(3,5,Flags GE Bits,9)
 Target(3,5,7,Flags GE Bits)
 Target(SIZEOF item,5,7,9)
 Target(3,SIZEOF item,7,9)
 Target(3,5,SIZEOF item,9)
 Target(3,5,7,SIZEOF item)
 Target(TYPE item,5,7,9)
 Target(3,TYPE item,7,9)
 Target(3,5,TYPE item,9)
 Target(3,5,7,TYPE item)
 Target(LENGTHOF array,5,7,9)
 Target(3,LENGTHOF array,7,9)
 Target(3,5,LENGTHOF array,9)
 Target(3,5,7,LENGTHOF array)
 Target(LOW 1234h,5,7,9)
 Target(3,LOW 1234h,7,9)
 Target(3,5,LOW 1234h,9)
 Target(3,5,7,LOW 1234h)
 Target(HIGH 1234h,5,7,9)
 Target(3,HIGH 1234h,7,9)
 Target(3,5,HIGH 1234h,9)
 Target(3,5,7,HIGH 1234h)
 Target(LOWWORD 12345678h,5,7,9)
 Target(3,LOWWORD 12345678h,7,9)
 Target(3,5,LOWWORD 12345678h,9)
 Target(3,5,7,LOWWORD 12345678h)
 Target(HIGHWORD 12345678h,5,7,9)
 Target(3,HIGHWORD 12345678h,7,9)
 Target(3,5,HIGHWORD 12345678h,9)
 Target(3,5,7,HIGHWORD 12345678h)
 Target((Flags OR Bits) AND NOT 2,5,7,9)
 Target(3,(Flags OR Bits) AND NOT 2,7,9)
 Target(3,5,(Flags OR Bits) AND NOT 2,9)
 Target(3,5,7,(Flags OR Bits) AND NOT 2)
 Target((1 SHL 4) + (17 MOD 5),5,7,9)
 Target(3,(1 SHL 4) + (17 MOD 5),7,9)
 Target(3,5,(1 SHL 4) + (17 MOD 5),9)
 Target(3,5,7,(1 SHL 4) + (17 MOD 5))
 Target(DWORD PTR item.value,5,7,9)
 Target(3,DWORD PTR item.value,7,9)
 Target(3,5,DWORD PTR item.value,9)
 Target(3,5,7,DWORD PTR item.value)
 Target(item.value,5,7,9)
 Target(3,item.value,7,9)
 Target(3,5,item.value,9)
 Target(3,5,7,item.value)
 Target(Ns::Value OR Flags,5,7,9)
 Target(3,Ns::Value OR Flags,7,9)
 Target(3,5,Ns::Value OR Flags,9)
 Target(3,5,7,Ns::Value OR Flags)
 Target(Inner(Flags OR Bits),1 SHL 3,Flags AND Bits,17 MOD 5)
 ret
Caller endp
end
