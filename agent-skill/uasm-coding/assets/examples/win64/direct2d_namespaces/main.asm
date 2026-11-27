; Native Win64 window + Direct2D. No C/C++ wrapper or external ASM headers.
include api.inc
namespace Graphics
EnsureTarget proto (dword) :qword
Paint proto (dword) :qword
DiscardTarget proto (void)
Shutdown proto (void)
.data
; Typed aliases make globals, LOCALs and interface metadata unambiguous.
PFactory typedef ptr D2D::Factory
factory PFactory 0
PTarget typedef ptr D2D::WindowTarget
PBrush typedef ptr D2D::Brush
renderTarget PTarget 0
brush PBrush 0
background D2D::Color <0.035,0.055,0.09,1.0>
accent D2D::Color <0.10,0.72,0.85,1.0>
rounded D2D::RoundedRectangle <70.0,65.0,455.0,255.0,24.0,24.0>
ellipse D2D::Ellipse <550.0,160.0,65.0,65.0>
frames dword 0
.code
DiscardTarget proc uses r15
 .if brush
  brush->Release()
  mov brush,0
 .endif
 .if renderTarget
  renderTarget->Release()
  mov renderTarget,0
 .endif
 ret
DiscardTarget endp
Shutdown proc uses r15
 DiscardTarget()
 .if factory
  factory->Release()
  mov factory,0
 .endif
 ret
Shutdown endp
EnsureTarget proc uses rbx r15 window:qword
 LOCAL client:RECT,properties:D2D::RenderProperties,winProperties:D2D::WindowProperties
 .if renderTarget
  xor eax,eax
  ret
 .endif
 Win32::GetClientRect(window,&client)
 .if eax == 0
  mov eax,80004005h
  ret
 .endif
 ; Fully initialize both descriptor structures (no uninitialized stack fields).
 xor eax,eax
 mov properties.kind,eax
 mov properties.format,eax
 mov properties.alphaMode,eax
 mov dword ptr properties.dpiX,eax
 mov dword ptr properties.dpiY,eax
 mov properties.usage,eax
 mov properties.minLevel,eax
 mov winProperties.options,eax
 mov winProperties.padding,eax
 mov rax,window
 mov winProperties.hwnd,rax
 mov eax,client.right
 mov winProperties.pixelWidth,eax
 mov eax,client.bottom
 mov winProperties.pixelHeight,eax
 factory->CreateHwndRenderTarget(&properties,&winProperties,&renderTarget)
 test eax,eax
 js done
 renderTarget->CreateSolidColorBrush(&accent,0,&brush)
 .if sdword ptr eax < 0
  mov ebx,eax
  DiscardTarget()
  mov eax,ebx
 .endif
 done:
 ret
EnsureTarget endp
Paint proc uses r15 window:qword
 EnsureTarget(window)
 test eax,eax
 js done
 renderTarget->BeginDraw()
 renderTarget->Clear(&background)
 renderTarget->FillRoundedRectangle(&rounded,brush)
 renderTarget->FillEllipse(&ellipse,brush)
 renderTarget->EndDraw(0,0)
 .if eax == 8899000ch ; D2DERR_RECREATE_TARGET: recreate device-dependent objects
  DiscardTarget()
  Win32::InvalidateRect(window,0,0)
  xor eax,eax
 .elseif sdword ptr eax >= 0
  inc frames
 .endif
 done:
 ret
Paint endp
endnamespace

namespace App
WindowProc proto (qword) :qword,:dword,:qword,:qword
.data
className dw 'U','A','S','M','D','2','D',0
; Windows SDK IID_ID2D1Factory: 06152247-6F50-465A-9245-118BFD3B6007.
factoryIID dd 06152247h
 dw 06f50h,0465ah
 db 092h,045h,011h,08bh,0fdh,03bh,060h,007h
unknownIID dd 0
 dw 0,0
 db 0c0h,0,0,0,0,0,0,046h
exitCode dword 0
wc WNDCLASSEXW <>
.code
WindowProc proc frame uses rbx r15 window:qword,message:dword,wParam:qword,lParam:qword
 LOCAL paintInfo:PAINTSTRUCT,newSize:qword
 .if message == 0fh ; WM_PAINT
  Win32::BeginPaint(window,&paintInfo)
  Graphics::Paint(window)
  .if sdword ptr eax < 0
   mov exitCode,1
  .endif
  Win32::EndPaint(window,&paintInfo)
  xor eax,eax
 .elseif message == 5 ; WM_SIZE
  .if Graphics::renderTarget
   mov eax,dword ptr lParam
   mov edx,eax
   and eax,0ffffh
   shr edx,16
   .if eax && edx
    mov dword ptr newSize,eax
    mov dword ptr newSize[4],edx
    Graphics::renderTarget->Resize(&newSize)
    .if sdword ptr eax < 0
     Graphics::DiscardTarget()
    .endif
   .endif
  .endif
  Win32::InvalidateRect(window,0,0)
  xor eax,eax
 .elseif message == 113h ; WM_TIMER, used only by test build
  ifdef SELFTEST
   .if Graphics::frames == 0
    mov exitCode,1
   .endif
   Win32::DestroyWindow(window)
  endif
  xor eax,eax
 .elseif message == 2 ; WM_DESTROY
  Graphics::Shutdown()
  Win32::PostQuitMessage(exitCode)
  xor eax,eax
 .else
  Win32::DefWindowProcW(window,message,wParam,lParam)
 .endif
 ret
WindowProc endp
endnamespace

.code
Start proc frame uses rbx rsi rdi r15
 LOCAL window:qword,instance:qword,msg:MSG,unknown:ptr D2D::IUnknown
 mov unknown,0
 D2D::D2D1CreateFactory(0,&App::factoryIID,0,&Graphics::factory)
 test eax,eax
 js failed
 ; Real QueryInterface test: HRESULT in EAX, interface output through void**.
 Graphics::factory->QueryInterface(&App::unknownIID,&unknown)
 test eax,eax
 js failed
 .if unknown == 0
  jmp failed
 .endif
 unknown->Release()
 mov unknown,0
 Win32::GetModuleHandleW(0)
 mov instance,rax
 mov App::wc.hInstance,rax
 mov App::wc.cbSize,sizeof WNDCLASSEXW
 mov App::wc.style,3
 lea rax,App::WindowProc
 mov App::wc.lpfnWndProc,rax
 lea rax,App::className
 mov App::wc.lpszClassName,rax
 Win32::LoadCursorW(0,32512)
 mov App::wc.hCursor,rax
 Win32::RegisterClassExW(&App::wc)
 test ax,ax
 jz failed
 Win32::CreateWindowExW(0,&App::className,L"UASM - namespaces, COM arrows and Direct2D",0cf0000h,80000000h,80000000h,800,440,0,0,instance,0)
 mov window,rax
 test rax,rax
 jz failed
 Win32::ShowWindow(window,5)
 Win32::UpdateWindow(window)
 ifdef SELFTEST
  Win32::SetTimer(window,1,700,0)
  test rax,rax
  jz failed
 endif
messageLoop:
 Win32::GetMessageW(&msg,0,0,0)
 cmp eax,-1
 je failed
 test eax,eax
 jz finished
 Win32::TranslateMessage(&msg)
 Win32::DispatchMessageW(&msg)
 jmp messageLoop
finished:
 Win32::ExitProcess(App::exitCode)
failed:
 Graphics::Shutdown()
 Win32::ExitProcess(1)
 ret
Start endp
end
