;
; v2.26 - default to 64-bit fastcall if no .model/language defined
;
option  dllimport:<msvcrt>
exit    proto :dword

    .code

main proc
     exit(0)
main endp

    end main
