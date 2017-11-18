
;--- A simple Windows GUI program that creates an empty window;
;--- Similar to Win64_3, but unlike that variant this version 
;--- uses hll directives, so it cannot be assembled
;--- with Masm64. Also, OPTION FRAME:AUTO is used.
;---
;--- assemble:
;---   JWasm -win64 Win64_3e.asm
;--- link:
;---   MS Link: link Win64_3e.obj libpath:\wininc\lib64
;---   JWlink:  jwlink format win pe f Win64_3e.obj libpath \wininc\lib64

    option casemap:none
    option frame:auto    ;generate SEH-compatible prologues and epilogues
    option win64:11       ;reserve stack space once per procedure
    option STACKBASE:RSP
     OPTION ARCH:AVX
    includelib kernel32.lib
    includelib user32.lib

HINSTANCE typedef QWORD
HWND      typedef QWORD
HMENU     typedef QWORD
HICON     typedef QWORD
HBRUSH    typedef QWORD
HCURSOR   typedef QWORD
WPARAM    typedef QWORD
LPARAM    typedef QWORD
LPSTR     typedef QWORD
LPVOID    typedef QWORD
UINT      typedef DWORD

NULL           equ 0
WS_OVERLAPPEDWINDOW equ 0CF0000h
CW_USEDEFAULT  equ 80000000h
SW_SHOWDEFAULT equ 10
SW_SHOWNORMAL  equ 1
IDC_ARROW      equ 32512
IDI_APPLICATION equ 32512
WM_DESTROY     equ 2
CS_VREDRAW     equ 1
CS_HREDRAW     equ 2
COLOR_WINDOW   equ 5

proto_WNDPROC typedef proto :HWND,:QWORD,:WPARAM,:LPARAM
WNDPROC typedef ptr proto_WNDPROC

WNDCLASSEXA struct 8
cbSize          DWORD   ?
style           DWORD   ?
lpfnWndProc     WNDPROC ?
cbClsExtra      DWORD   ?
cbWndExtra      DWORD   ?
hInstance       HINSTANCE ?
hIcon           HICON   ?
hCursor         HCURSOR ?
hbrBackground   HBRUSH  ?
lpszMenuName    LPSTR   ?
lpszClassName   LPSTR   ?
hIconSm         HICON   ?
WNDCLASSEXA ends

POINT   struct
x   SDWORD  ?
y   SDWORD  ?
POINT   ends

MSG struct 8
hwnd    HWND    ?
message DWORD   ?
wParam  WPARAM  ?
lParam  LPARAM  ?
time    DWORD   ?
pt      POINT   <>
MSG ends

GetModuleHandleA proto :LPSTR
GetCommandLineA  proto
ExitProcess      proto :UINT
LoadIconA        proto :HINSTANCE, :LPSTR
LoadCursorA      proto :HINSTANCE, :LPSTR
RegisterClassExA proto :ptr WNDCLASSEXA
CreateWindowExA  proto :DWORD, :LPSTR, :LPSTR, :DWORD, :SDWORD, :SDWORD, :SDWORD, :SDWORD, :HWND, :HMENU, :HINSTANCE, :LPVOID
ShowWindow       proto :HWND, :SDWORD
UpdateWindow     proto :HWND
GetMessageA      proto :ptr MSG, :HWND, :SDWORD, :SDWORD
TranslateMessage proto :ptr MSG
DispatchMessageA proto :ptr MSG
PostQuitMessage  proto :SDWORD
DefWindowProcA   proto :HWND, :UINT, :WPARAM, :LPARAM

WinMain proto :HINSTANCE, :HINSTANCE, :LPSTR, :UINT

;num4 dq 0x0706050403020100
;mHigh dq 0x0f0e0d0c0b0a0908              ;0E0D0C0B0A0908070605003402010000

    op_type MACRO arg:REQ
      LOCAL result
      result = opattr(arg)
        IF result eq 37         ;; label, either local or global
          EXITM %1
        ELSEIF result eq 42     ;; GLOBAL var
          EXITM %2
        ELSEIF result eq 98     ;; LOCAL  var
          EXITM %3
        ELSEIF result eq 36     ;; immediate operand or constant
          EXITM %4
        ELSEIF result eq 48     ;; register
          EXITM %5
        ELSEIF result eq 805    ;; local procedure in code
          EXITM %6
        ELSEIF result eq 933    ;; external procedure or API call
          EXITM %7
        ENDIF
      EXITM %0                  ;; anything else
    ENDM

;MOV128 MACRO dst:REQ, immLo:REQ,immHi:REQ
;  MOV64 dst, imm
;  MOV64 dst + 8, immHi
;ENDM

.data?
dstHi QWORD ?
dstLo QWORD ?
numptr QWORD ?

COLOR  RECORD blink:8, back:8, intense:8, fore:8,blink1:8, back1:8, intense1:8, fore1:8
COLOR1 RECORD ablink:8, aback:8, aintense:8, afore:8
COLOR2  RECORD ack:8, een:8, blow:8, awhite:8,ablue:8, ared:8, abrown:8, apink:8,ablack1:8, agreen1:8, ajelow1:8, awhite1:8,ablue1:8, ared1:8, abrown1:8, pink1:8
COLOR3  RECORD black:4, green:4, jelow:4, white:4,blue:4, red:4, brown:4, pink:4,black1:4, green1:4, jelow1:4, white1:4,blue1:4, red1:4, brown1:4, pink2:4,\
               lack3:4, reen:4, elow:4, hite:4,lue:4, ed:4, rown:4, ink:4,lack1:4, reen1:4, elow1:4, hite1:4,lue1:4, ed1:4, rown1:4, ink2:2,br2:2
MYREC128 RECORD B00:1,B01:1,B02:1,B03:1,B04:1,B05:1,B06:1,B07:1,B08:1,B09:1,B0a:1,B0b:1,B0c:1,B0d:1,B0e:1,B0f:1,\
                B10:1,B11:1,B12:1,B13:1,B14:1,B15:1,B16:1,B17:1,B18:1,B19:1,B1a:1,B1b:1,B1c:1,B1d:1,B1e:1,B1f:1,\
                B20:1,B21:1,B22:1,B23:1,B24:1,B25:1,B26:1,B27:1,B28:1,B29:1,B2a:1,B2b:1,B2c:1,B2d:1,B2e:1,B2f:1,\
                B30:1,B31:1,B32:1,B33:1,B34:1,B35:1,B36:1,B37:1,B38:1,B39:1,B3a:1,B3b:1,B3c:1,B3d:1,B3e:1,B3f:1,\
                B40:1,B41:1,B42:1,B43:1,B44:1,B45:1,B46:1,B47:1,B48:1,B49:1,B4a:1,B4b:1,B4c:1,B4d:1,B4e:1,B4f:1,\
                B50:1,B51:1,B52:1,B53:1,B54:1,B55:1,B56:1,B57:1,B58:1,B59:1,B5a:1,B5b:1,B5c:1,B5d:1,B5e:1,B5f:1,\
                B60:1,B61:1,B62:1,B63:1,B64:1,B65:1,B66:1,B67:1,B68:1,B69:1,B6a:1,B6b:1,B6c:1,B6d:1,B6e:1,B6f:1,\
                B70:1,B71:1,B72:1,B73:1,B74:1,B75:1,B76:1,B77:1,B78:1,B79:1,B7a:1,B7b:1,B7c:1,B7d:1,B7e:1,B7f:1
               
COBALT STRUCT 
    pntr QWORD ?
    rc   COLOR <>
COBALT ENDS
SAFIR STRUCT 
    pntr QWORD ?
    rc   COLOR1 <>
SAFIR ENDS
RUBI STRUCT 
    pntr QWORD ?
   rc   COLOR2 <>
RUBI ENDS
REGISTERX STRUCT 
    pntr QWORD ?
   rc   MYREC128 <>
REGISTERX ENDS
    .data

;OMASK OWORD 0x00ffff00000000000000000000000000
terra    MYREC128 <0,0,0,0, 1,1,1,1,\ ;BYTE 15  ;0F0E0D0C0B0A09080706050403020100
         0,0,0,0, 1,1,1,0,\ ;BYTE 14
         0,0,0,0, 1,1,0,1,\ ;BYTE 13
         0,0,0,0, 1,1,0,0,\ ;BYTE 12
         0,0,0,0, 1,0,1,1,\ ;BYTE 11
         0,0,0,0, 1,0,1,0,\ ;BYTE 10
         0,0,0,0, 1,0,0,1,\ ;BYTE 9
         0,0,0,0, 1,0,0,0,\ ;BYTE 8
         0,0,0,0, 0,1,1,1,\ ;BYTE 7
         0,0,0,0, 0,1,1,0,\ ;BYTE 6
         0,0,0,0, 0,1,0,1,\ ;BYTE 5
         0,0,0,0, 0,1,0,0,\ ;BYTE 4
         0,0,0,0, 0,0,1,1,\ ;BYTE 3
         0,0,0,0, 0,0,1,0,\ ;BYTE 2
         0,0,0,0, 0,0,0,1,\ ;BYTE 1
         0,0,0,0, 0,0,0,0> ;BYTE 0  this is the lovest byte in xmm register

num4 db "The actual order" 
num2 db "The actual order" 
num3 dq 0x0f0e0d0c0b0a0908                    ;0E0D0C0B0A0908070605003402010000
num1 dq 0x0f0e0d0c0b0a0908
myoword OWORD 0xffffffffffffffffffffffffffffffff
pos dd 78h 
var dd 28
ClassName db "SimpleWinClass",0
AppName  db "Our First Window",0
registerx REGISTERX <>
;LOADXMMR128 MACRO dst:REQ, imm:REQ
 ;   MOV128 registerx.rc,imm
;    vmovups dst,registerx.rc
;ENDM

rubi RUBI <>
cobalt COBALT <>
safir SAFIR <>
gold COLOR2 <65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80>    ; E0E1E20E

    .data?
;GMASK OWORD ?
hInstance HINSTANCE ?
CommandLine LPSTR ?

    .code

WinMainCRTStartup proc FRAME
    REGS15STORAGE
    invoke GetModuleHandleA, NULL
    mov    hInstance, rax
    invoke GetCommandLineA
    mov    CommandLine, rax
    invoke WinMain, hInstance, NULL, CommandLine, SW_SHOWDEFAULT
    invoke ExitProcess, eax

WinMainCRTStartup endp

WinMain proc FRAME hInst:HINSTANCE, hPrevInst:HINSTANCE, CmdLine:LPSTR, CmdShow:UINT
    ;LOCAL OMASK : OWORD
    LOCAL wc:WNDCLASSEXA
    LOCAL msg:MSG
    LOCAL hwnd:HWND
;--- init the "shadow variable". Alternatively, one may set bit 0 
;--- of OPTION WIN64, then this is done automatically.
;num4 dq 0x0706050403020100
;num3 dq 0x0f0e0d0c0b0a0908              ;0E0D0C0B0A0908070605003402010000
   lea rax,terra 
   ;vmovups xmm0, [rax]
   MOVXMMR128  xmm1,  MYREC128 <0,0,0,0, 1,1,1,1,\ ;BYTE 15  0F0E0D0C0B0A09080706050403020100
                                   0,0,0,0, 1,1,1,0,\ ;BYTE 14
                                   0,0,0,0, 1,1,0,1,\ ;BYTE 13
                                   0,0,0,0, 1,1,0,0,\ ;BYTE 12
                                   0,0,0,0, 1,0,1,1,\ ;BYTE 11
                                   0,0,0,0, 1,0,1,0,\ ;BYTE 10
                                   0,0,0,0, 1,0,0,1,\ ;BYTE 9
                                   0,0,0,0, 1,0,0,0,\ ;BYTE 8
                                   0,0,0,0, 0,1,1,1,\ ;BYTE 7
                                   0,0,0,0, 0,1,1,0,\ ;BYTE 6
                                   0,0,0,0, 0,1,0,1,\ ;BYTE 5
                                   0,0,0,0, 0,1,0,0,\ ;BYTE 4
                                   0,0,0,0, 0,0,1,1,\ ;BYTE 3
                                   0,0,0,0, 0,0,1,0,\ ;BYTE 2
                                   0,0,0,0, 0,0,0,1,\ ;BYTE 1
                                   0,0,0,0, 0,0,0,0> ;BYTE 0  this is the lovest byte in xmm register
   MOVXMMR128  xmm0,  MYREC128 <0,0,0,0, 1,1,1,1,\ ;BYTE 15  0F0E0D0C0B0A09080706050403020100
                                   0,0,0,0, 1,1,1,0,\ ;BYTE 14
                                   0,0,0,0, 1,1,0,1,\ ;BYTE 13
                                   0,0,0,0, 1,1,0,0,\ ;BYTE 12
                                   0,0,0,0, 1,0,1,1,\ ;BYTE 11
                                   0,0,0,0, 1,0,1,0,\ ;BYTE 10
                                   0,0,0,0, 1,0,0,1,\ ;BYTE 9
                                   0,0,0,0, 1,0,0,0,\ ;BYTE 8
                                   0,0,0,0, 0,1,1,1,\ ;BYTE 7
                                   0,0,0,0, 0,1,1,0,\ ;BYTE 6
                                   0,0,0,0, 0,1,0,1,\ ;BYTE 5
                                   0,0,0,0, 0,1,0,0,\ ;BYTE 4
                                   0,0,0,0, 0,0,1,1,\ ;BYTE 3
                                   0,0,0,0, 0,0,1,0,\ ;BYTE 2
                                   0,0,0,0, 0,0,0,1,\ ;BYTE 1
                                   0,0,0,0, 0,0,0,0> ;BYTE 0  this is the lovest byte in xmm register
 ;por xmm5, MASK blow
 vmovups xmm5, MASK blow
 pxor xmm2,myoword
; lea rax,OMASK
 vmovups xmm1, MASK MYREC128

 pxor xmm3,xmm2
 pxor xmm1,xmm2
 vmovups xmm1,xmm2
 pandn xmm4,xmm5
 por    xmm1,myoword
 pand   xmm1,myoword
 pandn  xmm0,myoword
 ;mov eax, WIDTH blow
;vmovups RXMM0,xmm1
  ;vmovups xmm2, MASK blow
  ;por xmm0, xmm2
  vmovups RXMM0,xmm1
  ;vmovups xmm2, MASK NOT awhite
  ;por   xmm0,RXMM0
  ;por   xmm1,myoword
  vmovups xmm1, registerx.rc
  lea rax,registerx.rc
  vmovups xmm0, [rax]
  ;and word ptr[rax], NOT MASK B32
   SHIFTLEFT128  rax,16
  MOV128  num2,0001020304050607h,08090a0b0c0d0e0fh
  ;num4 db "The actual order"
  ;num2 db "The actual order"
  lea rax,num4
  lea rcx,num2
  ;SHIFTLEFT128  rax,16
  ;SHIFTLEFT128  rax,72
  SHIFTRIGHT128  rax,16
  SHIFTRIGHT128  rcx,72
  MOVXMMR128  xmm0, "redroeht","desreveR"
  MOVXMMR128  xmm1, "redroeht","desreveR"
  ;SRXMMR  xmm0, 16
  ;SRXMMR  xmm1, 0x48
  vmovups  RXMM0,xmm0
  vmovups  RXMM1,xmm1
  vmovups RXMM0,xmm0
  vmovups RXMM1,xmm1
  MOVXMMR128  xmm0, "redroeht","desreveR"
  MOVXMMR128  xmm1, "redroeht","desreveR"
  MOV64    num2,102030405060708h
  lea rax,num4
;  SHIFTRIGHT128  rax,0x48

;  MOVIMM128   num4," subaH v","alsinarB"
;  SRXMMR  xmm0,16
  vmovups  RXMM0,xmm0
  lea rax,num4
;  SHIFTLEFT128  rax,16
;  MOVIMM128 num4,"Branisla","v Habus "    ;4272616E69736C617620486162757320
  MOV128   num4," subaH v","alsinarB"     ;0f0e0d0c0b0a0908h,0706050403020100h
  ;MOVIMM128 xmm0,"v subaH ","alsinarB"
  lea rax, num4
  vmovups  xmm1, [rax]
  vmovups  xmm0, [rax]
;  MOVIMM128   num4," subaH v","alsinarB"
;  SRXMMR  xmm0,0x48
  ;SHIFTLEFT128  mem4,16
  vmovups  RXMM0,xmm0
  vmovups  RXMM1,xmm1
  mov ecx,48h
  lea rax, num4
  vmovups xmm0,OWORD PTR[rax]
  ;SHIFTLEFT128  xmm0,0x48
  lea rax,num4
  shl num3,cl
  shl num4,cl
  neg cl
  shr rax, cl
  or num3,rax
  mov rax, num1
;  mov rdx, num2
  shl rax,cl
  mov r10,rdx
  shl rdx,cl
  not cl
  shr r10,cl
  or  rax,r10
  mov num1,rax
;  mov num2,rdx
  shl num3,cl
  shl num4,cl
  ;mov num,rax
  lea   r9,gold 
  xor eax,eax
  mov dstHi,rax
  mov dstLo,rax

    MOV64    num2,102030405060708h
   ; MOV64    rubi.rc+8,0E0E1E20EE0E1E20Eh
   ; MOV128   rubi.rc, COLOR3<0,1,2,3,1,2,3,0, 0,1,2,3,1,2,3,0, 0,1,2,3,1,2,3,0, 0,1,2,3,1,2,3,0, 0,1,2,3,1,2,3,0, 0,1,2,3,1,2,3,0, 0,1,2,3,1,2,3,0, 0,1,2,3,1,2,3,0>
    MOV128   rubi.rc, COLOR2<1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16>                        ; E0E1E20EE0E1E20E
    MOV128   rubi.rc,0E0E1E20EE0E1E20Eh,0E0E1E20EE0E1E20Eh
    ;MOV64    cobalt.rc,COLOR <224, 225, 226, 14, 224, 225, 226, 14>
    mov      safir.rc,COLOR1 <224, 225, 226, 14>
    
    mov rax,807060504030201h
    mov rdx, 90A0B0C0D0E0F10h
    mov ecx,16
    ;SHIFTRIGHT128  rax,rdx,ecx
    mov dstLo,rax
    mov dstHi,rdx
    mov rax,807060504030201h
    mov rdx, 90A0B0C0D0E0F10h
    mov ecx,16
   ; SHIFTLEFT128  rax,rdx,ecx
    mov dstLo,rax
    mov dstHi,rdx

  .for (r11=0,r8=15,r10=78h:r11 < 16:r11++,r8--,r10-=8)
    movzx rax,BYTE PTR[r9+r8]
    mov rcx,r10
    xor edx,edx
;SHIFTLEFT128 rax,rdx,ecx
    or dstHi,rdx
    or dstLo,rax
  .endfor
    lea  rax,dstHi
    lea rax,dstLo
    mov   rax, RRAX
    mov   safir.rc,COLOR1 <224, 225, 226, 14>                                     ; E0E1E20E
    ;lea rax,safir
    ;mov   BYTE PTR[rax].SAFIR.rc.ablink, 10
    ;mov   safir.rc.ablink, 10
    ;mov   al,ablink
    ;mov   al,aback
    ;mov   al,aintense
    ;mov   al,afore
    ;lea   rax,rubi.rc
    mov  QWORD PTR[rax], 0E0E1E20EE0E1E20Eh
    mov  QWORD PTR[rax+8], 0E0E1E20EE0E1E20Eh
    ;mov128  rubi.rc,COLOR2 <1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16>
    mov   rax,COLOR <224, 225, 226, 14, 224, 225, 226, 14>                        ; E0E1E20EE0E1E20E
    ;mov   safir.rc,COLOR1 <224, 225, 226, 14>                                     ; E0E1E20E
    mov   hInst, rcx
    mov   wc.cbSize, SIZEOF WNDCLASSEXA
    mov   wc.style, CS_HREDRAW or CS_VREDRAW
    lea   rax, [WndProc]
    mov   wc.lpfnWndProc, rax
    mov   wc.cbClsExtra, 0
    mov   wc.cbWndExtra, 0
    mov   wc.hInstance, rcx
    mov   wc.hbrBackground, COLOR_WINDOW+1
    mov   wc.lpszMenuName, NULL
    lea   rax, [ClassName]
    mov   wc.lpszClassName, rax
    invoke LoadIconA, NULL, IDI_APPLICATION
    mov   wc.hIcon, rax
    mov   wc.hIconSm, rax
    invoke LoadCursorA, NULL, IDC_ARROW
    mov   wc.hCursor,rax
    invoke RegisterClassExA, addr wc
    invoke CreateWindowExA, NULL, ADDR ClassName, ADDR AppName,\
           WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,\
           CW_USEDEFAULT, CW_USEDEFAULT,CW_USEDEFAULT, NULL, NULL,\
           hInst, NULL
    mov   hwnd,rax
    invoke ShowWindow, hwnd, SW_SHOWNORMAL
    invoke UpdateWindow, hwnd
    .while (1)
        invoke GetMessageA, ADDR msg, NULL, 0, 0
        .break .if (!eax)
        invoke TranslateMessage, ADDR msg
        invoke DispatchMessageA, ADDR msg
    .endw
    mov   rax, msg.wParam
    ret
WinMain endp

WndProc proc FRAME hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .if ( edx == WM_DESTROY )
        invoke PostQuitMessage, NULL
        xor rax,rax
    .else
        invoke DefWindowProcA, rcx, edx, r8, r9
    .endif
    ret
WndProc endp

end WinMainCRTStartup
