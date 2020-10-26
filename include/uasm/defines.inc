
; / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
; / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
; / /                                                                               / /
; / /                Copyright 2020 (c) UASM macro assembly library                 / /
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

    IFNDEF DEFINES_INC
    DEFINES_INC EQU 1
    
    IFDEF WITHMACROLIB

    IFNDEF MACROLIB_INC
    .ERR <"DEFINES_INC must be included by MACROLIB_INC">
    ENDIF

    IF @Platform EQ 0
    IFNDEF WIN32
    WIN32 EQU 1
    ENDIF
    IFNDEF _WIN32
    _WIN32 EQU 1
    ENDIF
    IFNDEF __WIN32
    __WIN32 EQU 1
    ENDIF
    IFNDEF __WIN32__
    __WIN32__ EQU 1
    ENDIF
    IFNDEF _M_IX86
    _M_IX86 EQU 1
    ENDIF
    IFNDEF __X86__
    __X86__ EQU 1
    ENDIF
    IFNDEF __X86
    __X86 EQU 1
    ENDIF
    IFNDEF X86
    X86 EQU 1
    ENDIF
    IFNDEF __X86ORX64__
    __X86ORX64__ EQU 1
    ENDIF
    IFNDEF __X86ORX64
    __X86ORX64 EQU 1
    ENDIF
    IFNDEF X86ORX64
    X86ORX64 EQU 1
    ENDIF
    IFNDEF WINDOWS
    WINDOWS EQU 1
    ENDIF
    IFNDEF _WINDOWS
    _WINDOWS EQU 1
    ENDIF
    IFNDEF __WINDOWS
    __WINDOWS EQU 1
    ENDIF
    IFNDEF __WINDOWS__
    __WINDOWS__ EQU 1
    ENDIF
    IFNDEF __X32__
    __X32__ EQU 1
    ENDIF
    IFNDEF __X32
    __X32 EQU 1
    ENDIF
    IFNDEF X32
    X32 EQU 1
    ENDIF
    IFDEF __KNC__
    .ERR <"KNC not available in windows">
    ENDIF
    IFDEF __MIC__
    .ERR <"MIC not available in windows">
    ENDIF
    ENDIF ;@Platform EQ 0

    IF @Platform EQ 1
    IFNDEF WIN64
    WIN64 EQU 1
    ENDIF
    IFNDEF _WIN64
    _WIN64 EQU 1
    ENDIF
    IFNDEF __WIN64
    __WIN64 EQU 1
    ENDIF
    IFNDEF __WIN64__
    __WIN64__ EQU 1
    ENDIF
    IFNDEF _M_AMD64
    _M_AMD64 EQU 1
    ENDIF
    IFNDEF __X86_64__
    __X86_64__ EQU 1
    ENDIF
    IFNDEF __X86_64
    __X86_64 EQU 1
    ENDIF
    IFNDEF X86_64
    X86_64 EQU 1
    ENDIF
    IFNDEF __X86ORX64__
    __X86ORX64__ EQU 1
    ENDIF
    IFNDEF __X86ORX64
    __X86ORX64 EQU 1
    ENDIF
    IFNDEF X86ORX64
    X86ORX64 EQU 1
    ENDIF
    IFNDEF WINDOWS
    WINDOWS EQU 1
    ENDIF
    IFNDEF _WINDOWS
    _WINDOWS EQU 1
    ENDIF
    IFNDEF __WINDOWS
    __WINDOWS EQU 1
    ENDIF
    IFNDEF __WINDOWS__
    __WINDOWS__ EQU 1
    ENDIF
    IFNDEF __X64__
    __X64__ EQU 1
    ENDIF
    IFNDEF __X64
    __X64 EQU 1
    ENDIF
    IFNDEF X64
    X64 EQU 1
    ENDIF
    IFDEF __KNC__
    .ERR <"KNC not available in windows">
    ENDIF
    IFDEF __MIC__
    .ERR <"MIC not available in windows">
    ENDIF
    ENDIF ;@Platform EQ 1

    IF @Platform EQ 2
    IFNDEF __I386__
    __I386__ EQU 1
    ENDIF
    IFNDEF __I386
    __I386 EQU 1
    ENDIF
    IFNDEF __X86__
    __X86__ EQU 1
    ENDIF
    IFNDEF __X86
    __X86 EQU 1
    ENDIF
    IFNDEF X86
    X86 EQU 1
    ENDIF
    IFNDEF __X86ORX64__
    __X86ORX64__ EQU 1
    ENDIF
    IFNDEF __X86ORX64
    __X86ORX64 EQU 1
    ENDIF
    IFNDEF X86ORX64
    X86ORX64 EQU 1
    ENDIF
    IFNDEF UNIX32
    UNIX32 EQU 1
    ENDIF
    IFNDEF __UNIX32__
    __UNIX32__ EQU 1
    ENDIF
    IFNDEF __UNIX32
    __UNIX32 EQU 1
    ENDIF
    IFNDEF UNIX
    UNIX EQU 1
    ENDIF
    IFNDEF __UNIX__
    __UNIX__ EQU 1
    ENDIF
    IFNDEF __UNIX
    __UNIX EQU 1
    ENDIF
    IFNDEF LINUX32
    LINUX32 EQU 1
    ENDIF
    IFNDEF __LINUX32__
    __LINUX32__ EQU 1
    ENDIF
    IFNDEF __LINUX32
    __LINUX32 EQU 1
    ENDIF
    IFNDEF LINUX
    LINUX EQU 1
    ENDIF
    IFNDEF __LINUX__
    __LINUX__ EQU 1
    ENDIF
    IFNDEF __LINUX
    __LINUX EQU 1
    ENDIF
    IFNDEF __X32__
    __X32__ EQU 1
    ENDIF
    IFNDEF __X32
    __X32 EQU 1
    ENDIF
    IFNDEF X32
    X32 EQU 1
    ENDIF
    IFDEF __KNC__
    .ERR <"KNC not available in unix/linux 32-bits">
    ENDIF
    IFDEF __MIC__
    .ERR <"MIC not available in unix/linux 32-bits">
    ENDIF
    ENDIF ;@Platform EQ 2

    IF @Platform EQ 3
    IFNDEF __X86_64__
    __X86_64__ EQU 1
    ENDIF
    IFNDEF __X86_64
    __X86_64 EQU 1
    ENDIF
    IFNDEF X86_64
    X86_64 EQU 1
    ENDIF
    IFNDEF __X86ORX64__
    __X86ORX64__ EQU 1
    ENDIF
    IFNDEF __X86ORX64
    __X86ORX64 EQU 1
    ENDIF
    IFNDEF X86ORX64
    X86ORX64 EQU 1
    ENDIF
    IFNDEF UNIX64
    UNIX64 EQU 1
    ENDIF
    IFNDEF __UNIX64__
    __UNIX64__ EQU 1
    ENDIF
    IFNDEF __UNIX64
    __UNIX64 EQU 1
    ENDIF
    IFNDEF UNIX
    UNIX EQU 1
    ENDIF
    IFNDEF __UNIX__
    __UNIX__ EQU 1
    ENDIF
    IFNDEF __UNIX
    __UNIX EQU 1
    ENDIF
    IFNDEF LINUX64
    LINUX64 EQU 1
    ENDIF
    IFNDEF __LINUX64__
    __LINUX64__ EQU 1
    ENDIF
    IFNDEF __LINUX64
    __LINUX64 EQU 1
    ENDIF
    IFNDEF LINUX
    LINUX EQU 1
    ENDIF
    IFNDEF __LINUX__
    __LINUX__ EQU 1
    ENDIF
    IFNDEF __LINUX
    __LINUX EQU 1
    ENDIF
    IFNDEF __X64__
    __X64__ EQU 1
    ENDIF
    IFNDEF __X64
    __X64 EQU 1
    ENDIF
    IFNDEF X64
    X64 EQU 1
    ENDIF
    ENDIF ;@Platform EQ 3

    IF @Platform EQ 4
    IFNDEF __X86_64__
    __X86_64__ EQU 1
    ENDIF
    IFNDEF __X86_64
    __X86_64 EQU 1
    ENDIF
    IFNDEF X86_64
    X86_64 EQU 1
    ENDIF
    IFNDEF __X86ORX64__
    __X86ORX64__ EQU 1
    ENDIF
    IFNDEF __X86ORX64
    __X86ORX64 EQU 1
    ENDIF
    IFNDEF X86ORX64
    X86ORX64 EQU 1
    ENDIF
    IFNDEF UNIX64
    UNIX64 EQU 1
    ENDIF
    IFNDEF __UNIX64__
    __UNIX64__ EQU 1
    ENDIF
    IFNDEF __UNIX64
    __UNIX64 EQU 1
    ENDIF
    IFNDEF UNIX
    UNIX EQU 1
    ENDIF
    IFNDEF __UNIX__
    __UNIX__ EQU 1
    ENDIF
    IFNDEF __UNIX
    __UNIX EQU 1
    ENDIF
    IFNDEF MACH
    MACH EQU 1
    ENDIF
    IFNDEF __MACH
    __MACH EQU 1
    ENDIF
    IFNDEF __MACH__
    __MACH__ EQU 1
    ENDIF
    IFNDEF MAC
    MAC EQU 1
    ENDIF
    IFNDEF _MAC
    _MAC EQU 1
    ENDIF
    IFNDEF __MAC
    __MAC EQU 1
    ENDIF
    IFNDEF __MAC__
    __MAC__ EQU 1
    ENDIF
    IFNDEF APPLE
    APPLE EQU 1
    ENDIF
    IFNDEF __APPLE
    __APPLE EQU 1
    ENDIF
    IFNDEF __APPLE__
    __APPLE__ EQU 1
    ENDIF
    IFNDEF __X64__
    __X64__ EQU 1
    ENDIF
    IFNDEF __X64
    __X64 EQU 1
    ENDIF
    IFNDEF X64
    X64 EQU 1
    ENDIF
    IFDEF __KNC__
    .ERR <"KNC not available in MAC OS">
    ENDIF
    IFDEF __MIC__
    .ERR <"MIC not available in MAC OS">
    ENDIF
    ENDIF ;@Platform EQ 4
    
    IF (@Platform GT 4 OR @Platform LT 0)
    IFNDEF UNDEFINED_PLATFORM
    UNDEFINED_PLATFORM EQU 1
    ENDIF
    ENDIF ;@Platform EQ 4

    IFNDEF ARCH_SSE
    ARCH_SSE EQU 0
    ENDIF
    
    IFNDEF ARCH_AVX
    ARCH_AVX EQU 1
    ENDIF
    
    IFNDEF RET_BYTE
    RET_BYTE EQU 0
    ENDIF

    IFNDEF RET_SBYTE
    RET_SBYTE EQU 0x40
    ENDIF

    IFNDEF RET_WORD
    RET_WORD EQU 1
    ENDIF

    IFNDEF RET_SWORD
    RET_SWORD EQU 0x41
    ENDIF

    IFNDEF RET_DWORD
    RET_DWORD EQU 2
    ENDIF

    IFNDEF RET_SDWORD
    RET_SDWORD EQU 0x42
    ENDIF

    IFNDEF RET_QWORD
    RET_QWORD EQU 3
    ENDIF
    
    IFNDEF RET_SQWORD
    RET_SQWORD EQU 0x43
    ENDIF

    IFNDEF RET_PTR
    RET_PTR EQU 0xc3
    ENDIF

    IFNDEF RET_XMMWORD
    RET_XMMWORD EQU 6
    ENDIF
    IFNDEF RET_XMM
    RET_XMM EQU 6
    ENDIF

    IFNDEF RET_YMMWORD
    RET_YMMWORD EQU 7
    ENDIF
    IFNDEF RET_YMM
    RET_YMM EQU 7
    ENDIF

    IFNDEF RET_ZMMWORD
    RET_ZMMWORD EQU 8
    ENDIF
    IFNDEF RET_ZMM
    RET_ZMM EQU 8
    ENDIF
    
    IFNDEF RET_REAL4
    RET_REAL4 EQU 0x22
    ENDIF

    IFNDEF RET_REAL8
    RET_REAL8 EQU 0x23
    ENDIF

    IFNDEF RET_NONE
    RET_NONE EQU 0x100
    ENDIF
    
    IFNDEF LANG_NONE
    LANG_NONE       EQU 0
    ENDIF
    
    IFNDEF LANG_C
    LANG_C          EQU 1
    ENDIF
    
    IFNDEF LANG_SYSCALL
    LANG_SYSCALL    EQU 2
    ENDIF
    
    IFNDEF LANG_STDCALL
    LANG_STDCALL    EQU 3
    ENDIF
    
    IFNDEF LANG_PASCAL
    LANG_PASCAL     EQU 4
    ENDIF
    
    IFNDEF LANG_FORTRAN
    LANG_FORTRAN    EQU 5
    ENDIF
    
    IFNDEF LANG_BASIC
    LANG_BASIC      EQU 6
    ENDIF
    
    IFNDEF LANG_FASTCALL
    LANG_FASTCALL   EQU 7
    ENDIF
    
    IFNDEF LANG_VECTORCALL
    LANG_VECTORCALL EQU 8
    ENDIF
    
    IFNDEF LANG_SYSVCALL
    LANG_SYSVCALL   EQU 9
    ENDIF
    
    IFNDEF LANG_REGCALL
    LANG_REGCALL    EQU 10
    ENDIF
    
    IFNDEF LANG_THISCALL
    LANG_THISCALL   EQU 11
    ENDIF
    
    IFNDEF LANG_DELPHICALL
    LANG_DELPHICALL EQU 12
    ENDIF
    
    IFDEF __UNICODE__
      IFNDEF _UNICODE
      _UNICODE EQU 1
      ENDIF
      IFNDEF UNICODE
      UNICODE EQU 1
      ENDIF
    ENDIF

    IFDEF _UNICODE
      IFNDEF __UNICODE__
      __UNICODE__ EQU 1
      ENDIF
      IFNDEF UNICODE
      UNICODE EQU 1
      ENDIF
    ENDIF
    
    IFDEF UNICODE
      IFNDEF __UNICODE__
      __UNICODE__ EQU 1
      ENDIF
      IFNDEF _UNICODE
      _UNICODE EQU 1
      ENDIF
    ENDIF

    IFDEF CASEMAPNONE

    IFDEF WINDOWS
    windows EQU WINDOWS
    ENDIF
    IFDEF _WINDOWS
    _windows EQU _WINDOWS
    ENDIF
    IFDEF __WINDOWS
    __windows EQU __WINDOWS
    ENDIF
    IFDEF __WINDOWS__
    __windows__ EQU __WINDOWS__
    ENDIF

    IFDEF WIN32
    win32 EQU WIN32
    ENDIF
    IFDEF _WIN32
    _win32 EQU _WIN32
    ENDIF
    IFDEF __WIN32
    __win32 EQU __WIN32
    ENDIF
    IFDEF __WIN32__
    __win32__ EQU __WIN32__
    ENDIF
    IFDEF _M_IX86
    _m_ix86 EQU _M_IX86
    ENDIF

    IFDEF WIN64
    win64 EQU WIN64
    ENDIF
    IFDEF _WIN64
    _win64 EQU _WIN64
    ENDIF
    IFDEF __WIN64
    __win64 EQU __WIN64
    ENDIF
    IFDEF __WIN64__
    __win64__ EQU __WIN64__
    ENDIF
    IFDEF _M_AMD64
    _m_amd64 EQU _M_AMD64
    ENDIF

    IFDEF UNIX
    unix EQU UNIX
    ENDIF
    IFDEF __UNIX__
    __unix__ EQU __UNIX__
    ENDIF
    IFDEF __UNIX
    __unix EQU __UNIX
    ENDIF

    IFDEF UNIX32
    unix32 EQU UNIX32
    ENDIF
    IFDEF __UNIX32__
    __unix32__ EQU __UNIX32__
    ENDIF
    IFDEF __UNIX32
    __unix32 EQU __UNIX32
    ENDIF

    IFDEF UNIX64
    unix64 EQU UNIX64
    ENDIF
    IFDEF __UNIX64__
    __unix64__ EQU __UNIX64__
    ENDIF
    IFDEF __UNIX64
    __unix64 EQU __UNIX64
    ENDIF

    IFDEF LINUX
    linux EQU LINUX
    ENDIF
    IFDEF __LINUX__
    __linux__ EQU __LINUX__
    ENDIF
    IFDEF __LINUX
    __linux EQU __LINUX
    ENDIF

    IFDEF LINUX32
    linux32 EQU LINUX32
    ENDIF
    IFDEF __LINUX32__
    __linux32__ EQU __LINUX32__
    ENDIF
    IFDEF __LINUX32
    __linux32 EQU __LINUX32
    ENDIF

    IFDEF LINUX64
    linux64 EQU LINUX64
    ENDIF
    IFDEF __LINUX64__
    __linux64__ EQU __LINUX64__
    ENDIF
    IFDEF __LINUX64
    __linux64 EQU __LINUX64
    ENDIF

    IFDEF MACH
    mach EQU MACH
    ENDIF
    IFDEF __MACH
    __mach EQU __MACH
    ENDIF
    IFDEF __MACH__
    __mach__ EQU __MACH__
    ENDIF
    IFDEF MAC
    mac EQU MAC
    ENDIF
    IFDEF _MAC
    _mac EQU _MAC
    ENDIF
    IFDEF __MAC
    __mac EQU __MAC
    ENDIF
    IFDEF __MAC__
    __mac__ EQU __MAC__
    ENDIF
    IFDEF APPLE
    apple EQU APPLE
    ENDIF
    IFDEF __APPLE
    __apple EQU __APPLE
    ENDIF
    IFDEF __APPLE__
    __apple__ EQU __APPLE__
    ENDIF

    IFDEF __I386__
    __i386__ EQU __I386__
    ENDIF
    IFDEF __I386
    __i386 EQU __I386
    ENDIF
    IFDEF __X86__
    __x86__ EQU __X86__
    ENDIF
    IFDEF __X86
    __x86 EQU __X86
    ENDIF
    IFDEF X86
    x86 EQU X86
    ENDIF
    IFDEF __X32__
    __x32__ EQU __X32__
    ENDIF
    IFDEF __X32
    __x32 EQU __X32
    ENDIF
    IFDEF X32
    x32 EQU X32
    ENDIF

    IFDEF __X86_64__
    __x86_64__ EQU __X86_64__
    ENDIF
    IFDEF __X86_64
    __x86_64 EQU __X86_64
    ENDIF
    IFDEF X86_64
    x86_64 EQU X86_64
    ENDIF
    IFDEF __X64__
    __x64__ EQU __X64__
    ENDIF
    IFDEF __X64
    __x64 EQU __X64
    ENDIF
    IFDEF X64
    x64 EQU X64
    ENDIF
    IFDEF __X86ORX64__
    __x86orx64__ EQU 1
    ENDIF
    IFDEF __X86ORX64
    __x86orx64 EQU 1
    ENDIF
    IFDEF X86ORX64
    x86orx64 EQU 1
    ENDIF
    IFDEF UNDEFINED_PLATFORM
    undefined_platform EQU UNDEFINED_PLATFORM
    ENDIF
    IFDEF ARCH_SSE
    arch_sse EQU ARCH_SSE
    ENDIF
    IFDEF ARCH_AVX
    arch_avx EQU ARCH_AVX
    ENDIF
    
    IFDEF RET_BYTE
    ret_byte EQU RET_BYTE
    ENDIF

    IFDEF RET_SBYTE
    ret_sbyte EQU RET_SBYTE
    ENDIF

    IFDEF RET_WORD
    ret_word EQU RET_WORD
    ENDIF

    IFDEF RET_SWORD
    ret_sword EQU RET_SWORD
    ENDIF

    IFDEF RET_DWORD
    ret_dword EQU RET_DWORD
    ENDIF

    IFDEF RET_SDWORD
    ret_sdword EQU RET_SDWORD
    ENDIF

    IFDEF RET_QWORD
    ret_qword EQU RET_QWORD
    ENDIF
    
    IFDEF RET_SQWORD
    ret_sqword EQU RET_SQWORD
    ENDIF

    IFDEF RET_PTR
    ret_ptr EQU RET_PTR
    ENDIF

    IFDEF RET_XMMWORD
    ret_xmmword EQU RET_XMMWORD
    ENDIF
    IFDEF RET_XMM
    ret_xmm EQU RET_XMM
    ENDIF

    IFDEF RET_YMMWORD
    ret_ymmword EQU RET_YMMWORD
    ENDIF
    IFDEF RET_YMM
    ret_ymm EQU RET_YMM
    ENDIF

    IFDEF RET_ZMMWORD
    ret_zmmword EQU RET_ZMMWORD
    ENDIF
    IFDEF RET_ZMM
    ret_zmm EQU RET_ZMM
    ENDIF
    
    IFDEF RET_REAL4
    ret_real4 EQU RET_REAL4
    ENDIF

    IFDEF RET_REAL8
    ret_real8 EQU RET_REAL8
    ENDIF

    IFDEF RET_NONE
    ret_none EQU RET_NONE
    ENDIF
    
    IFDEF LANG_NONE
    lang_none       EQU LANG_NONE
    ENDIF
    
    IFDEF LANG_C
    lang_c          EQU LANG_C
    ENDIF
    
    IFDEF LANG_SYSCALL
    lang_syscall    EQU LANG_SYSCALL
    ENDIF
    
    IFDEF LANG_STDCALL
    lang_stdcall    EQU LANG_STDCALL
    ENDIF
    
    IFDEF LANG_PASCAL
    lang_pascall     EQU LANG_PASCAL
    ENDIF
    
    IFDEF LANG_FORTRAN
    lang_fortran    EQU LANG_FORTRAN
    ENDIF
    
    IFDEF LANG_BASIC
    lang_basic      EQU LANG_BASIC
    ENDIF
    
    IFDEF LANG_FASTCALL
    lang_fastcall   EQU LANG_FASTCALL
    ENDIF
    
    IFDEF LANG_VECTORCALL
    lang_vectorcall EQU LANG_VECTORCALL
    ENDIF
    
    IFDEF LANG_SYSVCALL
    lang_sysvcall   EQU LANG_SYSVCALL
    ENDIF
    
    IFDEF LANG_REGCALL
    lang_regcall    EQU LANG_REGCALL
    ENDIF
    
    IFDEF LANG_THISCALL
    lang_thiscall   EQU LANG_THISCALL
    ENDIF
    
    IFDEF LANG_DELPHICALL
    lang_delphicall EQU LANG_DELPHICALL
    ENDIF
    
    IFDEF __UNICODE__
      IFNDEF __unicode__
      __unicode__ EQU __UNICODE__
      ENDIF
    ENDIF
    
    IFDEF _UNICODE
      IFNDEF _unicode
      _unicode EQU _UNICODE
      ENDIF
    ENDIF
    
    IFDEF UNICODE
      IFNDEF _unicode
      unicode EQU UNICODE
      ENDIF
    ENDIF
    
    IFDEF __unicode__
      IFNDEF _unicode
      _unicode EQU 1
      ENDIF
      IFNDEF unicode
      unicode EQU 1
      ENDIF
      IFNDEF __UNICODE__
      __UNICODE__ EQU __unicode__
      ENDIF
    ENDIF

    IFDEF _unicode
      IFNDEF __unicode__
      __unicode__ EQU 1
      ENDIF
      IFNDEF unicode
      unicode EQU 1
      ENDIF
      IFNDEF _UNICODE
      _UNICODE EQU _unicode
      ENDIF
    ENDIF
    
    IFDEF unicode
      IFNDEF __unicode__
      __unicode__ EQU 1
      ENDIF
      IFNDEF _unicode
      _unicode EQU 1
      ENDIF
      IFNDEF UNICODE
      UNICODE EQU unicode
      ENDIF
    ENDIF

    ENDIF ;CASEMAPNONE

    ENDIF ;WITHMACROLIB

    ENDIF    ;DEFINES_INC
