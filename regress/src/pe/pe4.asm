;
; PE64 import/invoke test: select UASM's 64-bit fastcall model explicitly.
.x64
.model flat, fastcall
;
option  dllimport:<msvcrt>
exit    proto :dword

    .code

main proc
     exit(0)
main endp

    end main
