; Preferred Windows x64 starter. Assemble with -win64 -Zp8 -Zi8.
; Requires WinInc on the include search path.
.x64
option casemap:none
option literals:on
option arch:avx
option evex:1
option stackbase:rsp
option win64:15
option frame:auto

.nolist
.nocref
WIN32_LEAN_AND_MEAN EQU 1
; UNICODE EQU 1
_WIN64 EQU 1
include windows.inc
.list
.cref

; Fail assembly rather than let a mismatched OS layout corrupt the stack.
.errnz SIZEOF WNDCLASSEXW - 80
.errnz SIZEOF MSG - 48
.errnz MSG.wParam - 16
.errnz MSG.lParam - 24
.errnz MSG.pt - 36

includelib <kernel32.lib>
includelib <user32.lib>
option proc:private

namespace App
WndProc PROTO (SQWORD) hWnd:QWORD,message:DWORD,wParam:QWORD,lParam:QWORD
Run PROTO (DWORD)
.const
 ClassName DW 'U','a','s','m','S','t','a','r','t','e','r',0
.data
 windowClass WNDCLASSEXW <>
.code
Run PROC FRAME
 LOCAL instance:QWORD,window:QWORD,msg:MSG
 GetModuleHandleW(0)
 .if rax == 0
  jmp failed
 .endif
 mov instance,rax
 mov windowClass.cbSize,SIZEOF WNDCLASSEXW
 mov windowClass.hInstance,rax
 lea rax,WndProc
 mov windowClass.lpfnWndProc,rax
 lea rax,ClassName
 mov windowClass.lpszClassName,rax
 mov windowClass.hbrBackground,COLOR_WINDOW+1
 LoadCursorW(0,IDC_ARROW)
 mov windowClass.hCursor,rax
 RegisterClassExW(&windowClass)
 .if ax == 0
  jmp failed
 .endif
 CreateWindowExW(0,&ClassName,L"Hello from UASM x64",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,800,500,0,0,instance,0)
 .if rax == 0
  jmp failed
 .endif
 mov window,rax
IFNDEF SMOKE_TEST
 ShowWindow(window,SW_SHOWNORMAL)
 UpdateWindow(window)
ELSE
 ; Exercise WM_CLOSE -> DefWindowProcW -> WM_DESTROY -> WM_QUIT without UI.
 PostMessageW(window,WM_CLOSE,0,0)
 .if eax == 0
  jmp failed
 .endif
ENDIF
 .while 1
  GetMessageW(&msg,0,0,0)
  .if eax == -1
   jmp failed
  .elseif eax == 0
   mov eax,DWORD PTR msg.wParam
   ret
  .endif
  TranslateMessage(&msg)
  DispatchMessageW(&msg)
 .endw
failed:
 mov eax,1
 ret
Run ENDP

WndProc PROC FRAME hWnd:QWORD,message:DWORD,wParam:QWORD,lParam:QWORD
 .if message == WM_DESTROY
  PostQuitMessage(0)
  xor eax,eax
  ret
 .endif
 DefWindowProcW(hWnd,message,wParam,lParam)
 ret
WndProc ENDP
endnamespace

PUBLIC Start
Start PROC FRAME
 App::Run()
 ExitProcess(eax)
 ret
Start ENDP
END
