option casemap : none
option frame : auto; generate SEH - compatible prologues and epilogues
option win64 : 11; init shadow space, reserve stack at PROC level
option literals : ON
option evex:1
 includelib msvcrt.lib
 printf proto : vararg;
includelib kernel32.lib
includelib user32.lib

ExitProcess   proto :dword
MessageBoxExW proto :dword, :ptr, :ptr, :dword, :word
MessageBoxExA proto :dword, :dword, :ptr, :dword, :word
 

.data

one dw  "Kuća", 0

.code

    main proc
		invoke MessageBoxExA, 0, "This is a test", "heading", 0, 0 ; error if literal string not used with ptr type
		invoke MessageBoxExW, 0, L"У меня много денег", ADDR one, 0, 0 ; ""
		invoke ExitProcess, 0
    ret
    main endp

end