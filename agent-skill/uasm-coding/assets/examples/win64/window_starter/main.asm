; UASM 2.60: self-contained Windows API GUI starter, x64, no CRT.
; build.cmd C:\tools\UASM.exe from an x64 Native Tools Command Prompt.
.x64
option casemap:none
option stackbase:rsp
option win64:15
option frame:auto
option arch:avx
option evex:1
option literals:on
option proc:private
includelib <kernel32.lib>
includelib <user32.lib>

; Win64 layouts; no third-party windows.inc/kernel32.inc/user32.inc needed.
WNDCLASSEXW STRUCT
 cbSize DWORD 0
 style DWORD 0
 lpfnWndProc QWORD 0
 cbClsExtra DWORD 0
 cbWndExtra DWORD 0
 hInstance QWORD 0
 hIcon QWORD 0
 hCursor QWORD 0
 hbrBackground QWORD 0
 lpszMenuName QWORD 0
 lpszClassName QWORD 0
 hIconSm QWORD 0
WNDCLASSEXW ENDS
MSG STRUCT
 hwnd QWORD ?
 message DWORD ?
 padding DWORD ?
 wParam QWORD ?
 lParam QWORD ?
 time DWORD ?
 ptX SDWORD ?
 ptY SDWORD ?
 lPrivate DWORD ?
MSG ENDS
.errnz SIZEOF WNDCLASSEXW - 80
.errnz SIZEOF MSG - 48

WM_DESTROY EQU 2
WM_CLOSE EQU 10h
COLOR_WINDOW EQU 5
IDC_ARROW EQU 32512
WS_OVERLAPPEDWINDOW EQU 00CF0000h
CW_USEDEFAULT EQU 80000000h
SW_SHOWNORMAL EQU 1

namespace Win32
GetModuleHandleW PROTO (QWORD) :PTR
LoadCursorW PROTO (QWORD) :QWORD,:PTR
RegisterClassExW PROTO (WORD) :PTR
CreateWindowExW PROTO (QWORD) :DWORD,:PTR,:PTR,:DWORD,:SDWORD,:SDWORD,:SDWORD,:SDWORD,:QWORD,:QWORD,:QWORD,:PTR
ShowWindow PROTO (DWORD) :QWORD,:SDWORD
UpdateWindow PROTO (DWORD) :QWORD
GetMessageW PROTO (SDWORD) :PTR,:QWORD,:DWORD,:DWORD
TranslateMessage PROTO (DWORD) :PTR
DispatchMessageW PROTO (SQWORD) :PTR
DefWindowProcW PROTO (SQWORD) :QWORD,:DWORD,:QWORD,:QWORD
PostQuitMessage PROTO (void) :SDWORD
PostMessageW PROTO (DWORD) :QWORD,:DWORD,:QWORD,:QWORD
ExitProcess PROTO (void) :DWORD
endnamespace

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
 Win32::GetModuleHandleW(0)
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
 Win32::LoadCursorW(0,IDC_ARROW)
 mov windowClass.hCursor,rax
 Win32::RegisterClassExW(&windowClass)
 .if ax == 0
  jmp failed
 .endif
 Win32::CreateWindowExW(0,&ClassName,L"Hello from UASM x64",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,800,500,0,0,instance,0)
 .if rax == 0
  jmp failed
 .endif
 mov window,rax
IFNDEF SMOKE_TEST
 Win32::ShowWindow(window,SW_SHOWNORMAL)
 Win32::UpdateWindow(window)
ELSE
 ; Exercise WM_CLOSE -> DefWindowProcW -> WM_DESTROY -> WM_QUIT without UI.
 Win32::PostMessageW(window,WM_CLOSE,0,0)
 .if eax == 0
  jmp failed
 .endif
ENDIF
 .while 1
  Win32::GetMessageW(&msg,0,0,0)
  .if eax == -1
   jmp failed
  .elseif eax == 0
   mov eax,DWORD PTR msg.wParam
   ret
  .endif
  Win32::TranslateMessage(&msg)
  Win32::DispatchMessageW(&msg)
 .endw
failed:
 mov eax,1
 ret
Run ENDP

WndProc PROC FRAME hWnd:QWORD,message:DWORD,wParam:QWORD,lParam:QWORD
 .if message == WM_DESTROY
  Win32::PostQuitMessage(0)
  xor eax,eax
  ret
 .endif
 Win32::DefWindowProcW(hWnd,message,wParam,lParam)
 ret
WndProc ENDP
endnamespace

PUBLIC Start
Start PROC FRAME
 App::Run()
 Win32::ExitProcess(eax)
 ret
Start ENDP
END
