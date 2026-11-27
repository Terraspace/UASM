option casemap:none

namespace Demo

Point STRUCT
    x REAL4 ?
    y REAL4 ?
    NameSpace DWORD ?
Point ENDS

PPoint TYPEDEF PTR Point

CLASS Counter
    CMETHOD Add
ENDMETHODS
    value DWORD 0
ENDCLASS

METHOD Counter,Add,<DWORD>,<>,amount:DWORD
    mov eax,amount
    ret
ENDMETHOD

COMINTERFACE Shell
    CVIRTUAL NameSpace,<SDWORD>,item:PTR BYTE
ENDCOMINTERFACE

PShell TYPEDEF PTR Shell

RAWINTERFACE BootServices
    STDFUNC Open,<QWORD>,pThis:PTR,path:PTR WORD
ENDRAWINTERFACE

PBootServices TYPEDEF PTR BootServices

    namespace Child
        VALUE EQU 7
    endnamespace

endnamespace

namespace Win32
    WriteFile PROTO (DWORD) handle:QWORD,buffer:PTR,count:DWORD,written:PTR,overlapped:PTR
endnamespace
