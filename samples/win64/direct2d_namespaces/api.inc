; Minimal declarations for this sample, checked against Windows SDK d2d1.h.
; Unused COM methods remain named slots, NOT callable typed declarations.
option casemap:none
option stackbase:rsp
option win64:15
option frame:auto
option literals:on
option vtable:on
RECT struct
 left sdword ?
 top sdword ?
 right sdword ?
 bottom sdword ?
RECT ends
WNDCLASSEXW struct
 cbSize dword ?
 style dword ?
 lpfnWndProc qword ?
 cbClsExtra dword ?
 cbWndExtra dword ?
 hInstance qword ?
 hIcon qword ?
 hCursor qword ?
 hbrBackground qword ?
 lpszMenuName qword ?
 lpszClassName qword ?
 hIconSm qword ?
WNDCLASSEXW ends
PAINTSTRUCT struct
 hdc qword ?
 fErase dword ?
 rcPaint RECT <>
 fRestore dword ?
 fIncUpdate dword ?
 rgbReserved byte 32 dup(?)
 pad dword ?
PAINTSTRUCT ends
MSG struct
 hwnd qword ?
 message dword ?
 pad dword ?
 wParam qword ?
 lParam qword ?
 time dword ?
 ptX sdword ?
 ptY sdword ?
 lPrivate dword ?
MSG ends
namespace Win32
GetModuleHandleW proto (qword) :ptr
GetLastError proto (dword)
ExitProcess proto (void) :dword
RegisterClassExW proto (word) :ptr
CreateWindowExW proto (qword) :dword,:ptr,:ptr,:dword,:sdword,:sdword,:sdword,:sdword,:qword,:qword,:qword,:ptr
DefWindowProcW proto (qword) :qword,:dword,:qword,:qword
ShowWindow proto (dword) :qword,:sdword
UpdateWindow proto (dword) :qword
GetMessageW proto (sdword) :ptr,:qword,:dword,:dword
TranslateMessage proto (dword) :ptr
DispatchMessageW proto (qword) :ptr
PostQuitMessage proto (void) :sdword
BeginPaint proto (qword) :qword,:ptr
EndPaint proto (dword) :qword,:ptr
GetClientRect proto (dword) :qword,:ptr
LoadCursorW proto (qword) :qword,:ptr
SetTimer proto (qword) :qword,:qword,:dword,:ptr
DestroyWindow proto (dword) :qword
InvalidateRect proto (dword) :qword,:ptr,:dword
endnamespace
namespace D2D
D2D1CreateFactory proto (dword) :dword,:ptr,:ptr,:ptr
RenderProperties struct
 kind dword 0
 format dword 0
 alphaMode dword 0
 dpiX real4 0.0
 dpiY real4 0.0
 usage dword 0
 minLevel dword 0
RenderProperties ends
WindowProperties struct
 hwnd qword 0
 pixelWidth dword 0
 pixelHeight dword 0
 options dword 0
 padding dword 0
WindowProperties ends
Color struct
 red real4 0.0
 green real4 0.0
 blue real4 0.0
 alpha real4 1.0
Color ends
RoundedRectangle struct
 left real4 0.0
 top real4 0.0
 right real4 0.0
 bottom real4 0.0
 radiusX real4 0.0
 radiusY real4 0.0
RoundedRectangle ends
Ellipse struct
 centerX real4 0.0
 centerY real4 0.0
 radiusX real4 0.0
 radiusY real4 0.0
Ellipse ends
COMINTERFACE IUnknown
ENDCOMINTERFACE
COMINTERFACE Factory
 ReloadSystemMetrics qword 0
 GetDesktopDpi qword 0
 CreateRectangleGeometry qword 0
 CreateRoundedRectangleGeometry qword 0
 CreateEllipseGeometry qword 0
 CreateGeometryGroup qword 0
 CreateTransformedGeometry qword 0
 CreatePathGeometry qword 0
 CreateStrokeStyle qword 0
 CreateDrawingStateBlock qword 0
 CreateWicBitmapRenderTarget qword 0
 CVIRTUAL CreateHwndRenderTarget, <DWORD>, :PTR,:PTR,:PTR
 CreateDxgiSurfaceRenderTarget qword 0
 CreateDCRenderTarget qword 0
ENDCOMINTERFACE
COMINTERFACE WindowTarget
 GetFactory qword 0
 CreateBitmap qword 0
 CreateBitmapFromWicBitmap qword 0
 CreateSharedBitmap qword 0
 CreateBitmapBrush qword 0
 CVIRTUAL CreateSolidColorBrush, <DWORD>, :PTR,:PTR,:PTR
 CreateGradientStopCollection qword 0
 CreateLinearGradientBrush qword 0
 CreateRadialGradientBrush qword 0
 CreateCompatibleRenderTarget qword 0
 CreateLayer qword 0
 CreateMesh qword 0
 DrawLine qword 0
 DrawRectangle qword 0
 FillRectangle qword 0
 DrawRoundedRectangle qword 0
 CVIRTUAL FillRoundedRectangle, <VOIDARG>, :PTR,:PTR
 DrawEllipse qword 0
 CVIRTUAL FillEllipse, <VOIDARG>, :PTR,:PTR
 DrawGeometry qword 0
 FillGeometry qword 0
 FillMesh qword 0
 FillOpacityMask qword 0
 DrawBitmap qword 0
 DrawText qword 0
 DrawTextLayout qword 0
 DrawGlyphRun qword 0
 SetTransform qword 0
 GetTransform qword 0
 SetAntialiasMode qword 0
 GetAntialiasMode qword 0
 SetTextAntialiasMode qword 0
 GetTextAntialiasMode qword 0
 SetTextRenderingParams qword 0
 GetTextRenderingParams qword 0
 SetTags qword 0
 GetTags qword 0
 PushLayer qword 0
 PopLayer qword 0
 Flush qword 0
 SaveDrawingState qword 0
 RestoreDrawingState qword 0
 PushAxisAlignedClip qword 0
 PopAxisAlignedClip qword 0
 CVIRTUAL Clear, <VOIDARG>, :PTR
 CVIRTUAL BeginDraw, <VOIDARG>
 CVIRTUAL EndDraw, <DWORD>, :PTR,:PTR
 GetPixelFormat qword 0
 SetDpi qword 0
 GetDpi qword 0
 GetSize qword 0
 GetPixelSize qword 0
 GetMaximumBitmapSize qword 0
 IsSupported qword 0
 CheckWindowState qword 0
 CVIRTUAL Resize, <DWORD>, :PTR
 GetHwnd qword 0
ENDCOMINTERFACE
; Only IUnknown methods are used on the brush; its later methods are omitted.
COMINTERFACE Brush
ENDCOMINTERFACE
.errnz Factoryvtbl.CreateHwndRenderTarget - 14*8
.errnz WindowTargetvtbl.CreateSolidColorBrush - 8*8
.errnz WindowTargetvtbl.FillRoundedRectangle - 19*8
.errnz WindowTargetvtbl.FillEllipse - 21*8
.errnz WindowTargetvtbl.Clear - 47*8
.errnz WindowTargetvtbl.BeginDraw - 48*8
.errnz WindowTargetvtbl.EndDraw - 49*8
.errnz WindowTargetvtbl.Resize - 58*8
.errnz sizeof RenderProperties - 28
.errnz sizeof WindowProperties - 24
endnamespace
.errnz sizeof WNDCLASSEXW - 80
.errnz sizeof PAINTSTRUCT - 72
.errnz sizeof MSG - 48
