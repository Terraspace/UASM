
;--- dllimport and jwasm option -Fd
;--- for -Fd to work, it must be linked with jwlink

    .386
    .MODEL FLAT, stdcall
    option casemap:none

   option dllimport:<kernel32>
ExitProcess   proto :dword
   option dllimport:<none>

    .CODE

start:
    invoke  ExitProcess, 0

    END start
