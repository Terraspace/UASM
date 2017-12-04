
AF_INET     equ 2
SOCK_STREAM equ 1
INADDR_ANY  equ 0

in_addr STRUCT
    s_addr dd ?
in_addr ENDS

sockaddr STRUCT
    sa_family dw ?   
    sa_data   db 14 DUP (?)
sockaddr ENDS

sockaddr_in STRUCT
    sin_family dw ?   ;eg AF_INET
    sin_port   dw ?   ;eg htons(3490)
    sin_addr   in_addr <?>
    sin_zero   db 8 DUP(?)  ;zero this if you want to
sockaddr_in ENDS

socket PROTO SYSTEMV domain:DWORD, sockType:DWORD, protocol:DWORD
bind   PROTO SYSTEMV sockfd:DWORD, pSockAddr:QWORD, socklen:DWORD
listen PROTO SYSTEMV sockfd:DWORD, backlog:DWORD
accept PROTO SYSTEMV sockfd:DWORD, pSockAddr:QWORD, pSocklen:QWORD
recv PROTO SYSTEMV sockfd:DWORD, pBuffer:QWORD, plen:DWORD, flags:DWORD

HTONL MACRO reg:REQ
    bswap reg
ENDM

HTONS MACRO
    xchg al,ah
ENDM

