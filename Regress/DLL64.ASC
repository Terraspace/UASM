
;--- 64-bit dll

ifdef __JWASM__
    .x64
    .MODEL FLAT, fastcall
endif

    .CODE

Export1 proc export

    mov eax,12345678h
    ret

Export1 endp

Export2 proc export pParm:ptr DWORD

    mov rcx, pParm
    mov dword ptr [rcx], 87654321h
    mov eax,1
    ret

Export2 endp

_DllMainCRTStartup proc hModule:ptr, dwReason:dword, dwReserved:ptr

    mov eax,1
    ret

_DllMainCRTStartup endp

    END

