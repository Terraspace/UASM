option casemap : none
option frame : auto; generate SEH - compatible prologues and epilogues
option win64 : 11; init shadow space, reserve stack at PROC level
option literals : ON
option evex:1
 includelib msvcrt.lib
 printf proto : vararg;
includelib kernel32.lib
includelib user32.lib

ExitProcess   proto : dword
MessageBoxExW proto : ptr, : ptr, : ptr, : dword, : word
MessageBoxExA proto : ptr, : ptr, : ptr, : dword, : word
testi proto :dword, :dword
; wprintf proto : QWORD
; swprintf_l proto : QWORD, : QWORD, : word
; swprintf(buf, 100, L"%s", L"Hello\xffff world");
; SetConsoleOutputCP proto : dword
; SetConsoleCP  proto : dword
  

.data
;mylab dq myadr1,myadr2,myadr3
one dw  "Kuća", 0
two dw "abcdef", 0
three dw "Am mulți bani", 0; 
four dw "У меня много денег",0
five dw "Sok pénzem van",0
format db "%s", 13, 10, 0
; 0x0419 Russian(ru)    0x19    LANG_RUSSIAN    Russia(RU) 0x01    SUBLANG_RUSSIAN_RUSSIA
; WINAPI MessageBoxEx(
; _In_opt_ HWND    hWnd,
; _In_opt_ LPCTSTR lpText,
; _In_opt_ LPCTSTR lpCaption,
; _In_     UINT    uType,
; _In_     WORD    wLanguageId

    .code
    main proc
   ; mov edx,2
    ;lea    rax,mylab
    ;jmp QWORD PTR[rax+rdx*8]
    invoke MessageBoxExA, 0, "This is a test", "heading", 0, 0
    invoke MessageBoxExW, 0, L"У меня много денег", ADDR one, 0, 0
myadr1:    
    invoke MessageBoxExW, 0, L"لدي الكثير من المال", ADDR four, 0, 0
    invoke MessageBoxExW, 0, L"Kuća", ADDR three, 0, 0
    invoke MessageBoxExW, 0, L"Imam puno novaca", ADDR two, 0, 0
    invoke MessageBoxExW, 0, L"我有很多钱", ADDR three, 0, 0
    invoke MessageBoxExW, 0, L"Имам пуно новаца", ADDR five, 0, 0
.data
mylab dq myadr1,myadr2,myadr3
.code

myadr2:
    invoke MessageBoxExW, 0, L"Sok pénzem van", ADDR three, 0, 0
    invoke MessageBoxExW, 0, L"Am mulți bani", ADDR three, 0, 0
    invoke MessageBoxExW, 0, L"Tengo mucho dinero", ADDR three, 0, 0
    invoke MessageBoxExW, 0, L"Tengo mucho dinero", ADDR three, 0, 0
myadr3:
    invoke MessageBoxExW, 0, L"Kuća", ADDR three, 0, 0
    invoke MessageBoxExW, 0, L"Sok pénzem van", ADDR three, 0, 0
    invoke MessageBoxExW, 0, L"Am mulți bani", ADDR three, 0, 0
    ;invoke printf, addr format, lengthof three
    ;invoke printf, addr format, lengthof four
    invoke ExitProcess, 0
    ret
    main endp
    end