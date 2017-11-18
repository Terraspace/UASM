; uasm64 -bin -Fo bin64.exe bin64.asm
.x64
option casemap:none
option stackbase:rbp
option win64:7

.nolist
include winnt64.inc   ; Modification for 64-bit of winnt.inc from Sample folder of UASM.
.list

STD_OUTPUT_HANDLE equ -11
HANDLE typedef ptr  
HWND typedef ptr  
NULL equ 0

IMAGEBASE equ 140000000h
_IMAGE equ 0

PEHDR segment dword FLAT

;--- define the DOS "MZ" header

    ORG _IMAGE

    IMAGE_DOS_HEADER <"ZM", 80h, 1, 0,4,0,-1,0,200h,0,0,0,0,0,<0>,0,0,<0>,IMAGEREL PEHdr>

    db 0Eh         ;push cs
    db 1Fh         ;pop ds
    db 0BAh,0Eh,0  ;mov dx,text
    db 0B4h,09h    ;mov ah,9
    db 0CDh,21h    ;int 21h
    db 0B8h,01h,4Ch;mov ax,4c01h
    db 0CDh,21h    ;int 21h
    db "This program cannot be run in DOS mode",13,10,'$'

    ORG _IMAGE+80h

;--- define the Win32 "PE" header

PEHdr label byte
    db "PE",0,0
    IMAGE_FILE_HEADER <IMAGE_FILE_MACHINE_AMD64, num_sections, 0, 0, 0, sizeof IMAGE_OPTIONAL_HEADER64,\
        IMAGE_FILE_RELOCS_STRIPPED or IMAGE_FILE_EXECUTABLE_IMAGE or IMAGE_FILE_LARGE_ADDRESS_AWARE or IMAGE_FILE_LOCAL_SYMS_STRIPPED>

    IMAGE_OPTIONAL_HEADER64 { 20Bh, ;magic
        0Eh,0Ah,                        ;linker major, minor
        1000h,1000h,0,              ;sizeof code, initialized data, uninitialized data
        IMAGEREL startapp,    ;entry point
        IMAGEREL start_text,  ;baseof code
        IMAGEBASE,    ;imagebase
        1000h,200h,   ;section alignment, file alignment
        6,0,          ;OS major, minor
        0,0,          ;Image major, minor
        6,0,          ;Subsys major, minor
        0,            ;win32 version
        3000h,        ;sizeof image
        1000h,        ;sizeof header
        0,            ;checksum
        IMAGE_SUBSYSTEM_WINDOWS_CUI,
        0,            ;dll characteristics
        100000h,1000h,;stack res,com
        100000h,1000h,;heap res, com
        0,            ;loader flags
        16,           ;number of directories
        < <0,0>,\        ;0 exports
        < IMAGEREL start_idata, SECTIONREL endof_idata >,\ ;1 imports
        <0,0>,<0,0>,\    ;2 resource, 3 exception
        <>,<>,<>,<>,\    ;4 security, 5 baserelocs, 6 debug, 7 architecture
        <>,<>,<>,<>,\    ;8 globalptr, 9 tls, 10 load_config, 11 bound_import
        <>,<>,<>,<> >}   ;12 iat, 13 delay_import, 14 com descriptor, 15 reserved

;--- define the section table

sectiontable label byte
    IMAGE_SECTION_HEADER <".text", <sizeof_text>, IMAGEREL start_text, sizeof_text,\
        200h, 0, 0, 0, 0, 060000020h >
    IMAGE_SECTION_HEADER <".rdata", <SECTIONREL endof_idata+ sizeof_const>, IMAGEREL start_rdata, SECTIONREL endof_idata+ sizeof_const,\
        400h, 0, 0, 0, 0, 040000040h >
num_sections equ ( $ -  sectiontable ) / sizeof IMAGE_SECTION_HEADER

    ORG _IMAGE+200h   ;forces physical size of header to 200h and sets VA to 400200h

PEHDR ends

ALIGN1 segment dword public FLAT 'DATA'
    ORG 0E00h   ; change pc to RVA 1000h
ALIGN1 ends

_TEXT segment dword public FLAT 'CODE'
_TEXT ends

ALIGN2 segment dword public FLAT 'DATA'
    ORG 0E00h   ; change pc to RVA 2000h
ALIGN2 ends

_IDATA segment dword public FLAT 'DATA'
start_rdata label byte
start_idata label byte
;--- import descriptors go here
_IDATA ends
_IDATA$1 segment dword public FLAT 'DATA'
    IMAGE_IMPORT_DESCRIPTOR <<0>,0,0,0,0>
;--- ILT entries go here
_IDATA$1 ends
_IDATA$2 segment dword public FLAT 'DATA'
    dq 0    ;--- end of last ILT 
;--- IAT entries go here
_IDATA$2 ends
_IDATA$3 segment dword public FLAT 'DATA'
    dd 0    ;--- end of last IAT
;--- import name strings go here
_IDATA$3 ends
_IDATA$4 segment dword public FLAT 'DATA'
endof_idata equ $
_IDATA$4 ends

CONST segment dword public FLAT 'DATA'
start_const label byte
CONST ends

DefineImpDll macro name
_IDATA segment
    IMAGE_IMPORT_DESCRIPTOR <<IMAGEREL name&ILT>,0,0,IMAGEREL name, IMAGEREL name&IAT>
_IDATA ends
_IDATA$1 segment
ifdef ImportDefined
    dq 0  ;terminate previous ILT
endif
name&ILT label dword
_IDATA$1 ends
_IDATA$2 segment
ifdef ImportDefined
    dq 0  ;terminate previous IAT
endif
name&IAT label dword
_IDATA$2 ends
_IDATA$3 segment
name db @CatStr(!",name, !"),0
    align 4
_IDATA$3 ends
ImportDefined equ 1
    endm

DefineImport macro name
_IDATA$1 segment
    dq IMAGEREL n&name 
_IDATA$1 ends
_IDATA$2 segment
lp&name typedef ptr pr&name
name    lp&name IMAGEREL n&name
_IDATA$2 ends
_IDATA$3 segment
n&name dw 0
    db @CatStr(!",name, !"),0
    align 4
_IDATA$3 ends
    endm

; When the FASTCALL specifier is not there it reports error LANGUAGE specifier is not there.
; If FASTCALL is there, as is now, it assumes 32-bit FASTCALL not the 64-bit ABI
; I placed FASTCALL just to make it assemble because it will not be possible to use INVOKE correctly.     
prWriteConsoleA typedef proto :HANDLE, :ptr, :dword, :ptr, :ptr
prGetStdHandle  typedef proto :dword
prExitProcess   typedef proto :dword

    DefineImpDll kernel32
    DefineImport ExitProcess
    DefineImport WriteConsoleA
    DefineImport GetStdHandle

;if 0 ;if further dlls are to be imported
prMessageBoxA   typedef proto :HWND, :ptr, :ptr, :dword

    DefineImpDll user32
    DefineImport MessageBoxA
;endif

CONST segment

string1  db 13,10,"hello, Console World.",13,10
string2  db "hello, Windows World.",0
caption db "Hello",0

sizeof_const equ $ - start_const

CONST ends

_TEXT segment

start_text label near
;--- start of program

; ***Procedures build without PROLOGUEs or EPILOGUEs***
main proc
LOCAL dwWritten:dword 
LOCAL hConsole:HANDLE
	invoke  GetStdHandle, STD_OUTPUT_HANDLE
    mov hConsole, rax
	invoke  WriteConsoleA, hConsole, addr string1, sizeof string1, addr dwWritten, NULL
    ret
main endp

;--- entry

startapp proc
    call main
    mov rcx,0
    lea rdx, string2
    lea r8, caption
    mov r9, 0
    sub rsp, 20h
    call MessageBoxA
    add rsp, 20h
    xor rcx, rcx    
    call  ExitProcess	
startapp endp	

sizeof_text equ $ - start_text

    ORG 200h    ;align size of _TEXT to next 512 byte boundary
_TEXT ends

end