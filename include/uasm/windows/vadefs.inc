
; / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
; / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
; / /                                                                               / /
; / /    Copyright 2020 UASM macro library for the Open Source Initiative           / /
; / /                                                                               / /
; / /    Licensed under the Apache License, Version 2.0 (the "License");            / /
; / /    you may not use this file except in compliance with the License.           / /
; / /    You may obtain a copy of the License at                                    / /
; / /                                                                               / /
; / /        http://www.apache.org/licenses/LICENSE-2.0                             / /
; / /                                                                               / /
; / /    Unless required by applicable law or agreed to in writing, software        / /
; / /    distributed under the License is distributed on an "AS IS" BASIS,          / /
; / /    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   / /
; / /    See the License for the specific language governing permissions and        / /
; / /    limitations under the License.                                             / /
; / /                                                                               / /
; / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
; / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /

ifdef WITHMACROLIB

ifndef _VADEFS_INC
define _VADEFS_INC

ifndef MACROLIB_INC
.err <"_VADEFS_INC must be included by MACROLIB_INC">
endif

ifndef DEFINES_INC
.err <"_VADEFS_INC requires DEFINES_INC">
endif

ifndef TYPES_INC
.err <"_VADEFS_INC requires TYPES_INC">
endif

ifndef MACROS_INC
.err <"_VADEFS_INC requires MACROS_INC">
endif

ifndef __X86ORX64__
.err <"_VADEFS_INC requires x86 or x64 platform type">
endif

ifndef CASEMAPNONE
.err <"_VADEFS_INC requires CASEMAPNONE">
endif

ifndef _INC_VADEFS
define _INC_VADEFS
endif

ifndef _MSC_VER
    define _MSC_VER, 1926
endif

ifndef _MSC_VER
    define _MSC_FULL_VER, 192628808
endif

ifndef __PTR32
    define __PTR32, PTR32, text
    define __ptr32, __PTR32, text
endif

ifndef __PTR64
    define __PTR64, PTR64, text
    define __ptr64, __PTR64, text
endif

ifndef __INT64
    define __INT64, QWORD, text
    define __int64, __INT64, text
endif

ifndef __INT32
    define __INT32, DWORD, text
    define __int32, __INT32, text
endif

ifndef __INT16
    define __INT16, WORD, text
    define __int16, __INT6, text
endif

ifndef __INT8
    define __INT8, BYTE, text
    define __int8, __INT8, text
endif

ifndef __CDECL
    define __CDECL, CDECL, text
    define __cdecl, __CDECL, text
endif

ifndef __STDCALL
    define __STDCALL, STDCALL, text
    define __stdcall, __STDCALL, text
endif

ifndef __FASTCALL
    define __FASTCALL, FASTCALL, text
    define __fastcall, __FASTCALL, text
endif

ifndef __THISCALL
    define __THISCALL, THISCALL, text
    define __thiscall, __THISCALL, text
endif

ifndef __VECTORCALL
    define __VECTORCALL, VECTORCALL, text
    define __vectorcall, __VECTORCALL, text
endif

ifndef __REGCALL
    define __REGCALL, REGCALL, text
    define __regcall, __REGCALL, text
endif

ifndef UNSIGNED
    define UNSIGNED, < >, text
    define unsigned, UNSIGNED, text
endif

ifndef __ALIGNOF
    define __ALIGNOF, <ALIGNOF>, text
    define __alignof, __ALIGNOF, text
endif

ifndef _CRT_PACKING 
    define _CRT_PACKING, 8
endif

ifndef _W64
define _W64
endif

ifndef _UINTPTR_T_DEFINED
    define _UINTPTR_T_DEFINED
    ifndef uintptr_t
        ifdef _WIN64
            uintptr_t typedef unsigned __int64
        else
            uintptr_t typedef unsigned __int32
        endif
    endif
endif

ifndef _VA_LIST_DEFINED
    define _VA_LIST_DEFINED
     ifndef VA_LIST
        define VA_LIST, PTR_CHAR, text
        define VA_LISTP, CHAR_PTR, text
        define va_list, VA_LIST, text
        define va_listp, VA_LISTP, text
     endif
endif

ifndef _ADDRESSOF
    define _ADDRESSOF, ADDRESSOF, text
    define _addressof, _ADDRESSOF, text
endif

ifndef _SLOTSIZEOF
_SLOTSIZEOF macro t
    exitm <sizeof(t)>
endm
    define _slotsizeof, _SLOTSIZEOF, text
endif

ifndef _APALIGN
_APALIGN macro t, aparg
    exitm <__alignof(t)>
endm
    define _apalign, _APALIGN, text
endif

if defined(_M_X64)
    __va_start proto __cdecl (void) :va_list, :vararg
    ifndef __crt_va_start_a
    __crt_va_start_a macro aparg, xarg:vararg
        start_afnex textequ <invoke __va_start, &aparg&, &xarg&>
        start_afnex
    endm
    endif
    ifndef __crt_va_arg
    __crt_va_arg macro aparg, targ
        local revtarg, sizeofrevtarg, eqsizeofrevtarg, saverret
        .data?
        revtarg targ ?
        saverret size_t ?
        sizeofrevtarg = sizeof(revtarg) - sizeof(revtarg)
        eqsizeofrevtarg equ sizeofrevtarg
        .code
        mov saverret, rret()
        ;;if ((sizeof(revtarg) gt int64_size) or (sizeof(revtarg) and (sizeof(revtarg) - 1) ne 0))
        ;;    mov rret(),    aparg
        ;;    add rret(), eqsizeofrevtarg
        ;;    mov aparg,    rret()
        ;;else
        mov rret(),    aparg
        add rret(), eqsizeofrevtarg
        mov aparg,    rret()
        ;;endif
        if sizeof(revtarg) eq int8_size
            mov revtarg, bret()
        elseif sizeof(revtarg) eq int16_size
            mov revtarg, wret()
        elseif sizeof(revtarg) eq int32_size
            mov revtarg, dret()
        elseif sizeof(revtarg) ge int64_size
            mov revtarg, rret()
        endif
        mov rret(), saverret
        exitm <revtarg>
    endm
    endif
    ifndef __crt_va_end
    __crt_va_end macro aparg
        va_endfnex textequ <mov &aparg&, 0>
        va_endfnex
    endm
    endif
    ifndef __crt_va_start
    define __crt_va_start, __crt_va_start_a, text
    endif
endif

endif    ;_VADEFS_INC

endif    ;WITHMACROLIB
