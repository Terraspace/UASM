
; -- - Win32 "hello world" console application.
; -- - assemble: HJWasm - coff Win32_1.ASM
; -- - link:     JWlink format win pe file Win32_1.OBJ lib kernel32.lib
; -- - or , linking with MS link :
; -- - link Win32_1.obj kernel32.lib

.486
.MODEL FLAT, stdcall
option casemap : none
; option DOTNAME
STD_OUTPUT_HANDLE equ - 11
NUMBER EQU 252
WriteConsoleA proto : dword, : dword, : dword, : dword, : dword
GetStdHandle  proto : dword
ExitProcess   proto : dword

.CONST
 
string  db 13, 10, "hello, world.", 13, 10

.CODE

main proc c

local   dwWritten : dword
local   hConsole : dword
local   var1     : dword
int 3
mov var1, 253
mov ecx, 254
.switch ecx
.case 252
mov  edx, 252
.break
.case 253
mov  edx, 253
.break
.case 254
mov  edx, 254
.break
.default
mov edx, 0
.break
.endswitch
mov eax, 252
.switch eax
.case 273
mov  edx, 273
.break
.case 280
mov  edx, 280
.break
.case 252
mov  edx, 252
.break
.case 274
mov edx, 274
.break
.case 277
mov  edx, 277
.break
.case 281
mov  edx, 281
.break
.case 269
mov  edx, 269
.break
.case 282
mov  edx, 282
.break
.case 283
mov  edx, 283
.break
.case 286
mov  edx, 286
.break
.default
mov edx, 0
.break
.endswitch

.switch NUMBER
.case 252
  mov  edx, 252
.break
.default
  mov edx, 0
.break
.endswitch

.switch var1
.case 252
mov  edx, 252
.break
.case 253
mov  edx, 253
.break
.default
mov edx, 0
.break
.endswitch

mov ecx, 254
.switch ecx
.case 252
mov  edx, 252
.break
.case 253
mov  edx, 253
.break
.case 254
mov  edx, 254
.break
.default
mov edx, 0
.break
.endswitch
mov eax, 252
.switch eax
.case 273
mov  edx, 273
.break
.case 280
mov  edx, 280
.break
.case 252
mov  edx, 252
.break
.case 274
mov edx, 274
.break
.case 277
mov  edx, 277
.break
.case 281
mov  edx, 281
.break
.case 269
mov  edx, 269
.break
.case 282
mov  edx, 282
.break
.case 283
mov  edx, 283
.break
.case 286
mov  edx, 286
.break
.default
mov edx, 0
.break
.endswitch

xor eax,eax
mov al, 'A'
.switch eax
.case 'B'
.case 'C'
.case 'A'
mov  dl, 'a'
.break
.case 'D'
mov  dl, 'd'
.break
.case 'E'
mov dl, 'e'
.break
.case 'F'
mov dl, 'f'
.break
.default
mov edx, 0
.break
.endswitch



mov eax, ((NOT 7) + ('c' SHL 8))
.switch eax
.case 2
mov  edx, 2
.break
.case ((NOT 7) + ('c' SHL 8))
mov  edx, ((NOT 7) + ('c' SHL 8))
.break
.case 252
mov  edx, 252
.break
.case 274
mov edx, 274
.break
.case 277
mov  edx, 277
.break
.case 281
mov  edx, 281
.break
.case 269
mov  edx, 269
.break
.case 282
mov  edx, 282
.break
.case 283
mov  edx, 283
.break
.case 286
mov  edx, 286
.break
.default
mov edx, 0
.break
.endswitch

mov ecx, 254
.switch ecx
.case 252
mov  edx, 252
.break
.case 253
mov  edx, 253
.break
.case 254
mov  edx, 254
.break
.default
mov edx, 0
.break
.endswitch

mov eax, 252
.switch eax
.case 273
mov  edx, 273
.break
.case 280
mov  edx, 280
.break
.case 252
mov  edx, 252
.break
.case 274
mov edx, 274
.break
.case 277
mov  edx, 277
.break
.case 281
mov  edx, 281
.break
.case 269
mov  edx, 269
.break
.case 282
mov  edx, 282
.break
.case 283
mov  edx, 283
.break
.case 286
mov  edx, 286
.break
.default
mov edx, 0
.break
.endswitch
mov eax, 'ABCF'
.switch eax
.case 'ABCC'
mov  edx, 'ABCG'
.break
.case 'ABCF'
mov  edx, 'ABCF'
.break
.case 'ABCI'
mov edx, 'ABCI'
.break
.case 'ABCJ'
mov edx, 'ABCJ'
.break
.default
mov edx, 0
.break
.endswitch

invoke  GetStdHandle, STD_OUTPUT_HANDLE
mov     hConsole, eax

invoke  WriteConsoleA, hConsole, addr string, sizeof string, addr dwWritten, 0

xor eax, eax
ret
main endp

; -- - entry

mainCRTStartup proc c

invoke  main
invoke  ExitProcess, eax

mainCRTStartup endp

END mainCRTStartup

