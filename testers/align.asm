option casemap : none
option win64 : 11
option frame : auto
option STACKBASE : RSP
option EVEX : 1          ;//this line is for EVEX instructions
;option DOTNAME
;option ZEROLOCALS : 1
;.ZMM
WIN32_LEAN_AND_MEAN equ 1
_WIN64    EQU 1
include windows.inc
include winnt.inc
;include switch.inc

extern __ImageBase:QWORD

WinMain proto :HINSTANCE, :HINSTANCE, :LPSTR, :UINT

.data?
align 32
testloc3 XMMWORD ?
align 32
testloc2 YMMWORD ?
stackstore dq ?
hInstance HINSTANCE ?
CommandLine LPSTR ?

.data
ClassName db "SimpleWinClass",0
AppName  db "Our First Window",0
align 32
testloc YMMWORD 0
test1 dq 0
align 32
testloc1 YMMWORD 0

    .code
align 16

 
probe PROC FRAME
  xor eax,eax
  ret
probe ENDP

subrutine PROC FRAME uses rbx  a:QWORD,b:QWORD 
    LOCAL baba:QWORD
    LOCAL deda:QWORD
    LOCAL mama:QWORD
    invoke probe
  ret
subrutine ENDP
WinMainCRTStartup proc FRAME
    ;// Because the system doesn't provide 32 byte alignment
    ;// This four lines will ensure that alignment in next procedures
    mov  rax, [rsp]               ;// keep return address in rax
    add rsp, 32                   ;// make sure wee don't delete some important data on the stack
    and rsp, 0FFFFFFFFFFFFFFE0h   ;// align it to 32 byte
    mov [rsp], rax                ;// put return addres again on the stack
    invoke GetModuleHandleA, NULL
    mov    hInstance, rax
    invoke GetCommandLine
    mov    CommandLine, rax
    invoke subrutine, rcx,rdx
    mov rax,rbx
    invoke WinMain, hInstance, NULL, CommandLine, SW_SHOWDEFAULT
    invoke ExitProcess, eax
WinMainCRTStartup endp

WinMain proc FRAME uses rbx ymm6 ymm7  hInst:HINSTANCE, hPrevInst:HINSTANCE, CmdLine:LPSTR, CmdShow:UINT
    LOCAL baba:YMMWORD
    LOCAL deda:YMMWORD
    LOCAL wc:WNDCLASSEXA
    LOCAL msg:MSG
    LOCAL var:QWORD
    LOCAL hwnd:HWND

;--- init the "shadow variable". Alternatively, one may set bit 0 
;--- of OPTION WIN64, then this is done automatically.
    lea rax,__ImageBase
    lea r10,testloc
    lea r11,test1
    lea rax,testloc1
    lea r8,testloc2 
    vmovdqa testloc1,ymm1
    lea rax,deda
    vmovdqa deda,ymm2
    mov   hInst, rcx
    invoke probe
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
    invoke LoadCursor, NULL, IDC_ARROW
    mov   wc.hCursor,rax
    invoke RegisterClassEx, addr wc
    invoke CreateWindowEx, NULL, ADDR ClassName, ADDR AppName,\
           WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,\
           CW_USEDEFAULT, CW_USEDEFAULT,CW_USEDEFAULT, NULL, NULL,\
           hInst, NULL
    mov   hwnd,rax
    invoke ShowWindow, hwnd, SW_SHOWNORMAL
    invoke UpdateWindow, hwnd
    .for(::)
        invoke GetMessage, ADDR msg, NULL, 0, 0
        .break .if (!eax)
        invoke TranslateMessage, ADDR msg
        invoke DispatchMessage, ADDR msg
        xor eax,eax
    .endfor
    mov   rax, msg.wParam
    ret
WinMain endp

WndProc proc FRAME uses rbp rsi rdi hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
;LOCAL var1:qword 

 mov rax,'ABCF'
	.switch eax 
	  .case 'ABCC'
     mov  rdx,'ABCG'
     .break
    .case 'ABCF'
     mov  rdx,'ABCF'
    .break
	  .case 'ABCI'
     mov rdx,'ABCI'
    .break
	  .case 'ABCJ'
     mov rdx,'ABCJ'
    .break
	  .default
     mov rdx,0
     .break
	.endswitch

 mov rcx, ((NOT 7) + ('c' SHL 8))
.switch rcx
.case 2
mov  rdx, 2
.break
.case ((NOT 7) + ('c' SHL 8))
mov  rdx, ((NOT 7) + ('c' SHL 8))
.break
.case 252
mov  rdx, 252
.break
.case 274
mov rdx, 274
.break
.case 277
mov  rdx, 277
.break
.case 281
mov  rdx, 281
.break
.case 269
mov  rdx, 269
.break
.case 282
mov  rdx, 282
.break
.case 283
mov  rdx, 283
.break
.case 286
mov  rdx, 286
.break
.default
mov rdx, 0
.break
.endswitch


 mov eax, 'A'
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
   
   mov rax, "stringa"
  .switch rax
  .case "stringa"
  mov  rdx, "stringa"
  .break
  .default
  mov edx, 0
  .break
  .endswitch

  mov rax, "stringa"
  .switch rax
  .case "stringb"
  mov  rdx, "stringb"
  .break
  .case "stringa"
  mov  rdx, "stringa"
  .break
  .default
  mov edx, 0
  .break
  .endswitch

  mov rax, "stringa"
  .switch rax
  .case "stringb"
  mov  rdx, "stringb"
  .break
  .case "stringa"
  mov  rdx, "stringa"
  .break
  .case "stringc"
  mov rdx, "stringc"
  .break
  .default
  mov edx, 0
  .break
  .endswitch

 
 mov rax, "oword"
  .switch rax
  .case "byte"
  mov  rdx, "byte"
  .break
  .case "word"
  mov  rdx, "word"
  .break
  .case "dword"
  mov rdx, "dword"
  .break
  .case "qword"
  mov rdx, "qword"
  .break
  .case "oword"
  mov rdx, "oword"
  .break
  .default
  mov edx, 0
  .break
  .endswitch

  mov rax, "stringa"
  .switch rax
  .case "stringb"
  mov  rdx, "stringb"
  .break
  .case "stringa"
  mov  rdx, "stringa"
  .break
  .case "stringc"
  mov rdx, "stringc"
  .break
  .case "stringd"
  mov rdx, "stringd"
  .break
  .default
  mov edx, 0
  .break
  .endswitch
 
    mov rax, "astringa"
  .switch rax
  .case "astringb"
  mov  rdx, "bstringb"
  .break
  .case "astringa"
  mov  rdx, "astringa"
  .break
  .case "cstringc"
  mov rdx, "cstringc"
  .break
  .case "dstringd"
  mov rdx, "dstringd"
  .break
  .default
  mov edx, 0
  .break
  .endswitch


   mov eax,252+1
	.switch eax 
	  .case 234
     mov  edx,234  
     .break
    .case 280
     mov  edx,280  
    .break
	  .case 253
     mov  edx,253  
    .break
	  .case 274
      mov edx,274
    .break
	  .case 277
     mov  edx,277 
    .break
	  .case 281
     mov  edx,281  
    .break
	  .case 269
     mov  edx,269 
    .break
	  .case 282
     mov  edx,282 
    .break
	  .case 283
     mov  edx,283 
    .break
	  .case 286
     mov  edx,286 
    .break
	  .default
     mov edx,0
     .break
	.endswitch

  mov eax,-252
	.switch eax 
	  .case 273
     mov  edx,273  
     .break
    .case 280
     mov  edx,280  
    .break
	  .case -252
     mov  edx,252  
    .break
	  .case 274
      mov edx,274
    .break
	  .case 277
     mov  edx,277 
    .break
	  .case 281
     mov  edx,281  
    .break
	  .case 269
     mov  edx,269 
    .break
	  .case 282
     mov  edx,282 
    .break
	  .case 283
     mov  edx,283 
    .break
	  .case 286
     mov  edx,286 
    .break
	  .default
     mov edx,0
     .break
	.endswitch
 mov rax,'ABCF'
	.switch eax 
	  .case 'ABCC'
     mov  rdx,'ABCG'
     .break
    .case 'ABCF'
     mov  rdx,'ABCF'
    .break
	  .case 'ABCI'
     mov rdx,'ABCI'
    .break
	  .case 'ABCJ'
     mov rdx,'ABCJ'
    .break
	  .default
     mov rdx,0
     .break
	.endswitch



    .if ( edx == WM_DESTROY )
        invoke PostQuitMessage, NULL
        xor rax,rax
    .else
        invoke DefWindowProc, rcx, edx, r8, r9
    .endif
    ret
WndProc endp

end WinMainCRTStartup
