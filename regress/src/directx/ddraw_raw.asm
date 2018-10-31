OPTION SCOPED ; Local labels are enabled, global labels inside
; PROC should be defined with double colons (LABEL::)
OPTION CASEMAP:NONE ; case sensitivity enabled
.686
.XMM
.MODEL FLAT,STDCALL
INCLUDE kernel32.inc
INCLUDE user32.inc
INCLUDELIB kernel32.lib
INCLUDELIB user32.lib
WinMain PROTO :DWORD, :DWORD, :DWORD, :DWORD
WinProc PROTO :DWORD, :DWORD, :DWORD, :DWORD
NULL EQU 0 ; null pointer
RECT STRUCT
left DWORD ?
top DWORD ?
right DWORD ?
bottom DWORD ?
RECT ENDS
PRECT TYPEDEF PTR RECT
LPRECT TYPEDEF FAR PTR RECT
POINT STRUCT
x DWORD ?
y DWORD ?
POINT ENDS
PPOINT TYPEDEF PTR POINT
LPPOINT TYPEDEF FAR PTR POINT
MSG STRUCT
hwnd DWORD ?
message DWORD ?
wParam DWORD ?
lParam DWORD ?
time DWORD ?
pt POINT <>
MSG ENDS
PMSG TYPEDEF PTR MSG
LPMSG TYPEDEF FAR PTR MSG
DD_OK EQU 0
DDBLT_WAIT EQU 001000000h
DDLOCK_WAIT EQU 000000001h
DDLOCK_WRITEONLY EQU 000000020h
DirectDrawCreate PROTO :DWORD, :DWORD, :DWORD
LPDIRECTDRAW TYPEDEF PTR IDirectDraw
LPDIRECTDRAWSURFACE TYPEDEF PTR IDirectDrawSurface
LPDIRECTDRAWPALETTE TYPEDEF PTR IDirectDrawPalette
LPDIRECTDRAWCLIPPER TYPEDEF PTR IDirectDrawClipper
LPPALETTEENTRY TYPEDEF PTR PALETTEENTRY
DDCOLORKEY STRUCT
dwColorSpaceLowValue DWORD ?
dwColorSpaceHighValue DWORD ?
DDCOLORKEY ENDS
LPDDCOLORKEY TYPEDEF PTR DDCOLORKEY
DDSCAPS STRUCT
dwCaps DWORD ?
DDSCAPS ENDS
LPDDSCAPS TYPEDEF PTR DDSCAPS
DDPIXELFORMAT STRUCT
dwSize DWORD ?
dwFlags DWORD ?
dwFourCC DWORD ?
UNION
dwRGBBitCount DWORD ?
dwYUVBitCount DWORD ?
dwZBufferBitDepth DWORD ?
dwAlphaBitDepth DWORD ?
ENDS
UNION
dwRBitMask DWORD ?
dwYBitMask DWORD ?
ENDS
UNION
dwGBitMask DWORD ?
dwUBitMask DWORD ?
ENDS
UNION
dwBBitMask DWORD ?
dwVBitMask DWORD ?
ENDS
UNION
dwRGBAlphaBitMask DWORD ?
dwYUVAlphaBitMask DWORD ?
ENDS
DDPIXELFORMAT ENDS
LPDDPIXELFORMAT TYPEDEF PTR DDPIXELFORMAT
DDSURFACEDESC STRUCT
dwSize DWORD ?
dwFlags DWORD ?
dwHeight DWORD ?
dwWidth DWORD ?
lPitch DWORD ?
dwBackBufferCount DWORD ?
UNION
dwMipMapCount DWORD ?
dwZBufferBitDepth DWORD ?
dwRefreshRate DWORD ?
ENDS
dwAlphaBitDepth DWORD ?
dwReserved DWORD ?
lpSurface DWORD ?
ddckCKDestOverlay DDCOLORKEY <>
ddckCKDestBlt DDCOLORKEY <>
ddckCKSrcOverlay DDCOLORKEY <>
ddckCKSrcBlt DDCOLORKEY <>
ddpfPixelFormat DDPIXELFORMAT <>
ddsCaps DDSCAPS <>
DDSURFACEDESC ENDS
LPDDSURFACEDESC TYPEDEF PTR DDSURFACEDESC
STDMETHOD MACRO name, argl:VARARG
LOCAL @tmp_a
LOCAL @tmp_b
@tmp_a TYPEDEF PROTO argl
@tmp_b TYPEDEF PTR @tmp_a
name @tmp_b ?
ENDM
IDirectDrawSurfaceVtbl STRUCT
STDMETHOD QueryInterface, :PTR IDirectDrawSurface, :PTR, :PTR PTR
STDMETHOD AddRef, :PTR IDirectDrawSurface
STDMETHOD Release, :PTR IDirectDrawSurface
STDMETHOD AddAttachedSurface, :PTR IDirectDrawSurface, :LPDIRECTDRAWSURFACE
STDMETHOD AddOverlayDirtyRect, :PTR IDirectDrawSurface, :LPRECT
STDMETHOD Blt, :PTR IDirectDrawSurface, :LPRECT, :LPDIRECTDRAWSURFACE, :LPRECT, :DWORD, :DWORD
STDMETHOD BltBatch, :PTR IDirectDrawSurface, :DWORD, :DWORD, :DWORD
STDMETHOD BltFast, :PTR IDirectDrawSurface, :DWORD, :DWORD, :LPDIRECTDRAWSURFACE, :LPRECT, :DWORD
STDMETHOD DeleteAttachedSurface, :PTR IDirectDrawSurface, :DWORD, :LPDIRECTDRAWSURFACE
STDMETHOD EnumAttachedSurfaces, :PTR IDirectDrawSurface, :PTR, :PTR
STDMETHOD EnumOverlayZOrders, :PTR IDirectDrawSurface, :DWORD, :PTR, :PTR
STDMETHOD Flip, :PTR IDirectDrawSurface, :LPDIRECTDRAWSURFACE, :DWORD
STDMETHOD GetAttachedSurface, :PTR IDirectDrawSurface, :LPDDSCAPS, :PTR LPDIRECTDRAWSURFACE
STDMETHOD GetBltStatus, :PTR IDirectDrawSurface, :DWORD
STDMETHOD GetCaps, :PTR IDirectDrawSurface, :LPDDSCAPS
STDMETHOD GetClipper, :PTR IDirectDrawSurface, :PTR LPDIRECTDRAWCLIPPER
STDMETHOD GetColorKey, :PTR IDirectDrawSurface, :DWORD, :LPDDCOLORKEY
STDMETHOD GetDC, :PTR IDirectDrawSurface, :PTR HDC
STDMETHOD GetFlipStatus, :PTR IDirectDrawSurface, :DWORD
STDMETHOD GetOverlayPosition, :PTR IDirectDrawSurface, :PTR DWORD, :PTR DWORD
STDMETHOD GetPalette, :PTR IDirectDrawSurface, :PTR LPDIRECTDRAWPALETTE
STDMETHOD GetPixelFormat, :PTR IDirectDrawSurface, :LPDDPIXELFORMAT
STDMETHOD GetSurfaceDesc, :PTR IDirectDrawSurface, :LPDDSURFACEDESC
STDMETHOD Initialize, :PTR IDirectDrawSurface, :LPDIRECTDRAW, :LPDDSURFACEDESC
STDMETHOD IsLost, :PTR IDirectDrawSurface
STDMETHOD mLock, :PTR IDirectDrawSurface, :LPRECT, :LPDDSURFACEDESC, :DWORD, :PTR
STDMETHOD ReleaseDC, :PTR IDirectDrawSurface, :HDC
STDMETHOD Restore, :PTR IDirectDrawSurface
STDMETHOD SetClipper, :PTR IDirectDrawSurface, :LPDIRECTDRAWCLIPPER
STDMETHOD SetColorKey, :PTR IDirectDrawSurface, :DWORD, :LPDDCOLORKEY
STDMETHOD SetOverlayPosition, :PTR IDirectDrawSurface, :SDWORD, :SDWORD
STDMETHOD SetPalette, :PTR IDirectDrawSurface, :LPDIRECTDRAWPALETTE
STDMETHOD Unlock, :PTR IDirectDrawSurface, :PTR
STDMETHOD UpdateOverlay, :PTR IDirectDrawSurface, :LPRECT, :LPDIRECTDRAWSURFACE, :LPRECT, :DWORD, :DWORD
STDMETHOD UpdateOverlayDisplay, :PTR IDirectDrawSurface, :DWORD
STDMETHOD UpdateOverlayZOrder, :PTR IDirectDrawSurface, :DWORD, :LPDIRECTDRAWSURFACE
IDirectDrawSurfaceVtbl ENDS
IDirectDraw STRUCT
lpVtbl DWORD ?
IDirectDraw ENDS
IDirectDrawSurface STRUCT
lpVtbl DWORD ?
IDirectDrawSurface ENDS
IDirectDrawPalette STRUCT
lpVtbl DWORD ?
IDirectDrawPalette ENDS
IDirectDrawClipper STRUCT
lpVtbl DWORD ?
IDirectDrawClipper ENDS
MINVOKE MACRO this:REQ, interfaceVtbl:REQ, function:REQ, arglist:VARARG
mov ecx, this
mov ecx, DWORD PTR [ecx]
IFNB 
INVOKE [ecx].interfaceVtbl.function, this, arglist
ELSE
INVOKE [ecx].interfaceVtbl.function, this
ENDIF
ENDM
.DATA
pIDirectDraw DWORD 0
pIDDSurfaceFront DWORD 0
pIDDSurfaceBack DWORD 0
.CODE
start:
INVOKE GetModuleHandle, NULL
INVOKE WinMain, eax, NULL, NULL, NULL
INVOKE ExitProcess, eax
ALIGN DWORD
;===============================================================================
WinMain PROC hInst:DWORD, hPrevInst:DWORD, CmdLine:DWORD, CmdShow:DWORD
;-------------------------------------------------------------------------------
LOCAL msg:MSG, rc:RECT, hWnd:DWORD, ddsd:DDSURFACEDESC
INVOKE RtlZeroMemory, ADDR ddsd, SIZEOF DDSURFACEDESC
mov ddsd.dwSize, SIZEOF DDSURFACEDESC
MINVOKE pIDDSurfaceBack, IDirectDrawSurfaceVtbl, mLock, NULL, ADDR ddsd, DDLOCK_WAIT OR DDLOCK_WRITEONLY, NULL
.IF eax != DD_OK
    nop
.ENDIF

MINVOKE pIDDSurfaceFront, IDirectDrawSurfaceVtbl, Blt, ADDR rc, pIDDSurfaceBack, NULL, DDBLT_WAIT, NULL
.IF eax != DD_OK
    nop
.ENDIF

ret
WinMain ENDP
ALIGN DWORD
;================================================================================
WndProc PROC hWnd:DWORD, uMsg:DWORD, wParam:DWORD, lParam:DWORD
;================================================================================
INVOKE DefWindowProc, hWnd, uMsg, wParam, lParam
ret
WndProc ENDP
END start
