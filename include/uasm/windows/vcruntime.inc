;//
;// vcruntime.h
;//
;//      Copyright (c) Microsoft Corporation. All rights reserved.
;//
;// Declarations used throughout the VCRuntime library.
;//
;#pragma once
;//
;// Note on use of "deprecate":
;//
;// Various places in this header and other headers use
;// __declspec(deprecate) or macros that have the term DEPRECATE in them.
;// We use "deprecate" here ONLY to signal the compiler to emit a warning
;// about these items. The use of "deprecate" should NOT be taken to imply
;// that any standard committee has deprecated these functions from the
;// relevant standards.  In fact, these functions are NOT deprecated from
;// the standard.
;//
;// Full details can be found in our documentation by searching for
;// "Security Enhancements in the CRT".
;//
    IFNDEF _VCRUNTIME_INC
    _VCRUNTIME_INC EQU 1
    
    IFDEF WITHMACROLIB

    IFNDEF MACROLIB_INC
    .ERR <"_VCRUNTIME_INC must be included by MACROLIB_INC">
    ENDIF
    
    IFNDEF DEFINES_INC
    .ERR <"_VCRUNTIME_INC requires DEFINES_INC">
    ENDIF
    
    IFNDEF TYPES_INC
    .ERR <"_VCRUNTIME_INC requires TYPES_INC">
    ENDIF
    
    IFNDEF MACROS_INC
    .ERR <"_VCRUNTIME_INC requires MACROS_INC">
    ENDIF
    
    IFNDEF __X86ORX64__
    .ERR <"_VCRUNTIME_INC requires one x86 or x64 platform type">
    ENDIF
    
    IFNDEF _VCRT_COMPILER_PREPROCESSOR
;// Many VCRuntime headers avoid exposing their contents to non-compilers like
;// the Windows resource compiler and Qt's meta-object compiler (moc).
    IF (RC_INVOKED EQ 1 OR Q_MOC_RUN EQ 1)
    _VCRT_COMPILER_PREPROCESSOR EQU 0
    ELSE
    _VCRT_COMPILER_PREPROCESSOR EQU 1
    ENDIF
    ENDIF ; // _VCRT_COMPILER_PREPROCESSOR

    IFNDEF _UCRT
    _UCRT EQU 1
    ENDIF

    IFNDEF __INT64
    __INT64 TEXTEQU <QWORD>
    IFDEF CASEMAPNONE
    __int64 TEXTEQU <__INT64>
    ENDIF
    ENDIF

    IFNDEF __INT32
    __INT32 TEXTEQU <DWORD>
    IFDEF CASEMAPNONE
    __int32 TEXTEQU <__INT32>
    ENDIF
    ENDIF

    IFNDEF __INT16
    __INT16 TEXTEQU <WORD>
    IFDEF CASEMAPNONE
    __int16 TEXTEQU <__INT6>
    ENDIF
    ENDIF

    IFNDEF __INT8
    __INT8 TEXTEQU <BYTE>
    IFDEF CASEMAPNONE
    __int8 TEXTEQU <__INT8>
    ENDIF
    ENDIF
    
    IFNDEF __CDECL
    __CDECL TEXTEQU <CDECL>
    IFDEF CASEMAPNONE
    __cdecl TEXTEQU <__CDECL>
    ENDIF
    ENDIF
    
    IFNDEF __STDCALL
    __STDCALL TEXTEQU <STDCALL>
    IFDEF CASEMAPNONE
    __stdcall TEXTEQU <__STDCALL>
    ENDIF
    ENDIF
    
    IFNDEF __FASTCALL
    __FASTCALL TEXTEQU <FASTCALL>
    IFDEF CASEMAPNONE
    __fastcall TEXTEQU <__FASTCALL>
    ENDIF
    ENDIF
    
    IFNDEF __THISCALL
    __THISCALL TEXTEQU <THISCALL>
    IFDEF CASEMAPNONE
    __thiscall TEXTEQU <__THISCALL>
    ENDIF
    ENDIF
    
    IFNDEF __VECTORCALL
    __VECTORCALL TEXTEQU <VECTORCALL>
    IFDEF CASEMAPNONE
    __vectorcall TEXTEQU <__VECTORCALL>
    ENDIF
    ENDIF
    
    IFNDEF __REGCALL
    __REGCALL TEXTEQU <REGCALL>
    IFDEF CASEMAPNONE
    __regcall TEXTEQU <__REGCALL>
    ENDIF
    ENDIF
    
;// The _CRTIMP macro is not used in the VCRuntime or the CoreCRT anymore, but
;// there is a lot of existing code that declares CRT functions using this macro,
;// and if we remove its definition, we break that existing code.  It is thus
;// defined here only for compatibility.
    IFNDEF _CRTIMP
    _VCRT_DEFINED_CRTIMP EQU 1
    ;#if defined CRTDLL && defined _CRTBLD
    ;    #define _CRTIMP __declspec(dllexport)
    ;#else
    ;    #ifdef _DLL
    ;        #define _CRTIMP __declspec(dllimport)
    ;    #else
    ;        #define _CRTIMP
    ;    #endif
    ;#endif
    _CRTIMP EQU 1
    ENDIF

;INCLUDE sal.inc
    INCLUDE vadefs.inc

;#pragma warning(push)
;#pragma warning(disable: _VCRUNTIME_DISABLED_WARNINGS)

;// All C headers have a common prologue and epilogue, to enclose the header in
;// an extern "C" declaration when the header is #included in a C++ translation
;// unit and to push/pop the packing.
;#if defined __cplusplus

;    #define _CRT_BEGIN_C_HEADER            \
;        __pragma(pack(push, _CRT_PACKING)) \
;        extern "C" {

;    #define _CRT_END_C_HEADER \
;        }                     \
;        __pragma(pack(pop))

;#elif defined __midl

;    #define _CRT_BEGIN_C_HEADER                         \
;        cpp_quote("__pragma(pack(push, _CRT_PACKING))") \
;        cpp_quote("extern \"C\" {")

;    #define _CRT_END_C_HEADER            \
;        cpp_quote("}")                   \
;        cpp_quote("__pragma(pack(pop))")

;#else

;    #define _CRT_BEGIN_C_HEADER            \
;        __pragma(pack(push, _CRT_PACKING))

;    #define _CRT_END_C_HEADER \
;        __pragma(pack(pop))

;#endif

;_CRT_BEGIN_C_HEADER



IFNDEF _HAS_EXCEPTIONS ;// Predefine as 0 to disable exceptions
    IFDEF _KERNEL_MODE
         _HAS_EXCEPTIONS EQU 0
    ELSE
         _HAS_EXCEPTIONS EQU 1
    ENDIF ;/* _KERNEL_MODE */
ENDIF ;/* _HAS_EXCEPTIONS */


_CRT_STRINGIZE_ MACRO x
    EXITM %x
ENDM
_CRT_STRINGIZE TEXTEQU <_CRT_STRINGIZE_>

#define _CRT_WIDE_(s) L ## s
#define _CRT_WIDE(s) _CRT_WIDE_(s)

#define _CRT_CONCATENATE_(a, b) a ## b
#define _CRT_CONCATENATE(a, b)  _CRT_CONCATENATE_(a, b)

#define _CRT_UNPARENTHESIZE_(...) __VA_ARGS__
#define _CRT_UNPARENTHESIZE(...)  _CRT_UNPARENTHESIZE_ __VA_ARGS__

#ifndef _VCRTIMP
    #if defined _CRTIMP && !defined _VCRT_DEFINED_CRTIMP
        #define _VCRTIMP _CRTIMP
    #elif defined _VCRT_BUILD && defined CRTDLL && !defined _VCRT_SAT_1
        #define _VCRTIMP __declspec(dllexport)
    #else
        #define _VCRTIMP
    #endif
#endif

#ifndef _MRTIMP
    #if defined MRTDLL && defined _CRTBLD && !defined _M_CEE_PURE
        #define _MRTIMP __declspec(dllexport)
    #else
        #define _MRTIMP
    #endif
#endif

// Definitions of calling conventions used code sometimes compiled as managed
#if defined _M_CEE_PURE || defined MRTDLL
    #define __CLRCALL_OR_CDECL __clrcall
    #define __CLR_OR_THIS_CALL __clrcall
#else
    #define __CLRCALL_OR_CDECL __cdecl
    #define __CLR_OR_THIS_CALL
#endif

#ifdef _M_CEE_PURE
    #define __CLRCALL_PURE_OR_CDECL __clrcall
#else
    #define __CLRCALL_PURE_OR_CDECL __cdecl
#endif

#define __CRTDECL __CLRCALL_PURE_OR_CDECL

// Definitions of common __declspecs
#define _VCRT_NOALIAS __declspec(noalias)
#define _VCRT_RESTRICT __declspec(restrict)

#if !defined _MSC_VER || _MSC_VER >= 1900
    #define _VCRT_ALLOCATOR __declspec(allocator)
#else
    #define _VCRT_ALLOCATOR
#endif

#if defined _M_CEE && defined _M_X64
    #define _VCRT_JIT_INTRINSIC __declspec(jitintrinsic)
#else
    #define _VCRT_JIT_INTRINSIC
#endif

#ifdef __midl
    #define _VCRT_ALIGN(x)
#else
    #define _VCRT_ALIGN(x) __declspec(align(x))
#endif

#ifndef _CONST_RETURN
    #ifdef __cplusplus
        #define _CRT_CONST_CORRECT_OVERLOADS
        #define _CONST_RETURN  const
    #else
      #define _CONST_RETURN
    #endif
#endif

// For backwards compatibility
#define _WConst_return _CONST_RETURN

// Definitions of common types
#ifdef _WIN64
    typedef unsigned __int64 size_t;
    typedef __int64          ptrdiff_t;
    typedef __int64          intptr_t;
#else
    typedef unsigned int     size_t;
    typedef int              ptrdiff_t;
    typedef int              intptr_t;
#endif

#if defined __cplusplus
    typedef bool  __vcrt_bool;
#elif defined __midl
    // MIDL understands neither bool nor _Bool.  Use char as a best-fit
    // replacement (the differences won't matter in practice).
    typedef char __vcrt_bool;
#else
    typedef _Bool __vcrt_bool;
#endif

// Indicate that these common types are defined
#ifndef _SIZE_T_DEFINED
    #define _SIZE_T_DEFINED
#endif

#ifndef _PTRDIFF_T_DEFINED
    #define _PTRDIFF_T_DEFINED
#endif

#ifndef _INTPTR_T_DEFINED
    #define _INTPTR_T_DEFINED
#endif

// Provide a typedef for wchar_t for use under /Zc:wchar_t-
#ifndef _WCHAR_T_DEFINED
    #define _WCHAR_T_DEFINED
    typedef unsigned short wchar_t;
#endif

#ifndef NULL
    #ifdef __cplusplus
        #define NULL 0
    #else
        #define NULL ((void *)0)
    #endif
#endif

#if defined _M_X64 || defined _M_ARM || defined _M_ARM64
    #define _UNALIGNED __unaligned
#else
    #define _UNALIGNED
#endif

#ifdef __cplusplus
    extern "C++"
    {
        template <typename _CountofType, size_t _SizeOfArray>
        char (*__countof_helper(_UNALIGNED _CountofType (&_Array)[_SizeOfArray]))[_SizeOfArray];

        #define __crt_countof(_Array) (sizeof(*__countof_helper(_Array)) + 0)
    }
#else
    #define __crt_countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#endif

#if defined(_M_IX86) && defined(_CRT_LEGACY_X86_FLT_EXCEPTIONS) && !defined(_M_CEE_PURE)
    #pragma comment(lib, "legacy_x86_flt_exceptions")
#endif

#if !defined(_HAS_CXX17) && !defined(_HAS_CXX20)
    #if defined(_MSVC_LANG)
        #define _STL_LANG _MSVC_LANG
    #elif defined(__cplusplus) // ^^^ use _MSVC_LANG / use __cplusplus vvv
        #define _STL_LANG __cplusplus
    #else  // ^^^ use __cplusplus / no C++ support vvv
        #define _STL_LANG 0L
    #endif // ^^^ no C++ support ^^^

    #if _STL_LANG > 201703L
        #define _HAS_CXX17 1
        #define _HAS_CXX20 1
    #elif _STL_LANG > 201402L
        #define _HAS_CXX17 1
        #define _HAS_CXX20 0
    #else // _STL_LANG <= 201402L
        #define _HAS_CXX17 0
        #define _HAS_CXX20 0
    #endif // Use the value of _STL_LANG to define _HAS_CXX17 and _HAS_CXX20

    #undef _STL_LANG
#endif // !defined(_HAS_CXX17) && !defined(_HAS_CXX20)

#if !defined(_HAS_CXX17) || !defined(_HAS_CXX20) || _HAS_CXX20 && !_HAS_CXX17
    #error _HAS_CXX17 and _HAS_CXX20 must both be defined, and _HAS_CXX20 must imply _HAS_CXX17
#endif // Verify _HAS_CXX17 and _HAS_CXX20

// [[nodiscard]] attributes on STL functions
#ifndef _HAS_NODISCARD
    #ifndef __has_cpp_attribute
        #define _HAS_NODISCARD 0
    #elif __has_cpp_attribute(nodiscard) >= 201603L // TRANSITION, VSO#939899 (need toolset update)
        #define _HAS_NODISCARD 1
    #else
        #define _HAS_NODISCARD 0
    #endif
#endif // _HAS_NODISCARD

#if _HAS_NODISCARD
    #define _NODISCARD [[nodiscard]]
#else // ^^^ CAN HAZ [[nodiscard]] / NO CAN HAZ [[nodiscard]] vvv
    #define _NODISCARD
#endif // _HAS_NODISCARD

// See note on use of "deprecate" at the top of this file
#define _CRT_DEPRECATE_TEXT(_Text) __declspec(deprecated(_Text))

#if defined _CRT_SECURE_NO_DEPRECATE && !defined _CRT_SECURE_NO_WARNINGS
    #define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _CRT_INSECURE_DEPRECATE
    #ifdef _CRT_SECURE_NO_WARNINGS
        #define _CRT_INSECURE_DEPRECATE(_Replacement)
    #else
        #define _CRT_INSECURE_DEPRECATE(_Replacement) _CRT_DEPRECATE_TEXT(    \
            "This function or variable may be unsafe. Consider using "        \
            #_Replacement                                                     \
            " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " \
            "See online help for details.")
    #endif
#endif

#if defined _CRT_SECURE_DEPRECATE_MEMORY && !defined _CRT_SECURE_WARNINGS_MEMORY
    #define _CRT_SECURE_WARNINGS_MEMORY
#endif

#ifndef _CRT_INSECURE_DEPRECATE_MEMORY
    #ifndef _CRT_SECURE_WARNINGS_MEMORY
        #define _CRT_INSECURE_DEPRECATE_MEMORY(_Replacement)
    #else
        #define _CRT_INSECURE_DEPRECATE_MEMORY(_Replacement) \
            _CRT_INSECURE_DEPRECATE(_Replacement)
    #endif
#endif

#if !defined _M_CEE && !defined __midl
    void __cdecl __security_init_cookie(void);

    #ifdef _M_IX86
        void __fastcall __security_check_cookie(_In_ uintptr_t _StackCookie);
        __declspec(noreturn) void __cdecl __report_gsfailure(void);
    #else  /* _M_IX86 */
        void __cdecl __security_check_cookie(_In_ uintptr_t _StackCookie);
        __declspec(noreturn) void __cdecl __report_gsfailure(_In_ uintptr_t _StackCookie);
    #endif
#endif

extern uintptr_t __security_cookie;

#ifndef _VCRT_BUILD
    #define __vcrt_malloc_normal(_Size) malloc(_Size)
    #define __vcrt_calloc_normal(_Count, _Size) calloc(_Count, _Size)
    #define __vcrt_free_normal(_Memory) free(_Memory)
#endif

_CRT_END_C_HEADER

#pragma warning(pop) // _VCRUNTIME_DISABLED_WARNINGS

    ENDIF    ;WITHMACROLIB

    ENDIF ;// _VCRUNTIME_INC
