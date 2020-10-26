
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

    IFNDEF TYPES_INC
    TYPES_INC EQU 1
    
    IFDEF WITHMACROLIB

    IFNDEF MACROLIB_INC
    .ERR <"TYPES_INC must be included by MACROLIB_INC">
    ENDIF
    
    IFNDEF X86ORX64
    .ERR <"TYPES_INC requires one x86 or x64 platform type">
    ENDIF
    
    CHAR TEXTEQU <BYTE>
    INT8 TEXTEQU <BYTE>
    UINT8 TEXTEQU <BYTE>
    SCHAR TEXTEQU <SBYTE>
    SINT8 TEXTEQU <SBYTE>
    CHAR8_T TEXTEQU <BYTE>
    INT8_T TEXTEQU <BYTE>
    UINT8_T TEXTEQU <BYTE>
    SCHAR8_T TEXTEQU <SBYTE>
    SINT8_T TEXTEQU <SBYTE>
    INT16 TEXTEQU <WORD>
    UINT16 TEXTEQU <WORD>
    SINT16 TEXTEQU <SWORD>
    CHAR16_T TEXTEQU <WORD>
    INT16_T TEXTEQU <WORD>
    UINT16_T TEXTEQU <WORD>
    SCHAR16_T TEXTEQU <SWORD>
    SINT16_T TEXTEQU <SWORD>
    WCHAR_T TEXTEQU <WORD>
    IFDEF UNICODE
    TCHAR TEXTEQU <WORD>
    ELSE
    TCHAR TEXTEQU <BYTE>
    ENDIF
   ;/INT TEXTEQU <DWORD> cannot be used instruction type*/
    BOOL TEXTEQU <DWORD>
    LONG TEXTEQU <DWORD>
    INT32 TEXTEQU <DWORD>
    UINT32 TEXTEQU <DWORD>
    SLONG TEXTEQU <SDWORD>
    SINT32 TEXTEQU <SDWORD>
    CHAR32_T TEXTEQU <DWORD>
    INT32_T TEXTEQU <DWORD>
    UINT32_T TEXTEQU <DWORD>
    SCHAR32_T TEXTEQU <SDWORD>
    SINT32_T TEXTEQU <SDWORD>
    LONGLONG TEXTEQU <QWORD>
    INT64 TEXTEQU <QWORD>
    UINT64 TEXTEQU <QWORD>
    SLONGLONG TEXTEQU <SQWORD>
    SINT64 TEXTEQU <SQWORD>
    INT64_T TEXTEQU <QWORD>
    UINT64_T TEXTEQU <QWORD>
    SINT64_T TEXTEQU <SQWORD>
    FLOAT16 TEXTEQU <WORD>
    BFLOAT16 TEXTEQU <WORD>
    FLT16 TEXTEQU <WORD>
    BFLT16 TEXTEQU <WORD>
    FLOAT TEXTEQU <REAL4>
    FLT TEXTEQU <REAL4>
    FLOAT32 TEXTEQU <REAL4>
    FLT32 TEXTEQU <REAL4>
    DOUBLE TEXTEQU <REAL8>
    DBL TEXTEQU <REAL8>
    FLOAT64 TEXTEQU <REAL8>
    FLT64 TEXTEQU <REAL8>
    XM128 TEXTEQU <XMMWORD>
    XM256 TEXTEQU <YMMWORD>
    XM512 TEXTEQU <ZMMWORD>
    M128 TEXTEQU <__m128>
    M256 TEXTEQU <__m256>
    M512 TEXTEQU <__m512>
    FLOAT128 TEXTEQU <__m128f>
    FLOAT256 TEXTEQU <__m256f>
    FLOAT512 TEXTEQU <__m512f>
    DOUBLE128 TEXTEQU <__m128d>
    DOUBLE256 TEXTEQU <__m256d>
    DOUBLE512 TEXTEQU <__m512d>
    FLT128 TEXTEQU <__m128f>
    FLT256 TEXTEQU <__m256f>
    FLT512 TEXTEQU <__m512f>
    DBL128 TEXTEQU <__m128d>
    DBL256 TEXTEQU <__m256d>
    DBL512 TEXTEQU <__m512d>
    INT8_128 TEXTEQU <__m128b>
    INT8_256 TEXTEQU <__m256b>
    INT8_512 TEXTEQU <__m512b>
    INT16_128 TEXTEQU <__m128w>
    INT16_256 TEXTEQU <__m256w>
    INT16_512 TEXTEQU <__m512w>
    INT32_128 TEXTEQU <__m128i>
    INT32_256 TEXTEQU <__m256i>
    INT32_512 TEXTEQU <__m512i>
    INT64_128 TEXTEQU <__m128q>
    INT64_256 TEXTEQU <__m256q>
    INT64_512 TEXTEQU <__m512q>
    VOID TEXTEQU <VOIDARG>
    
    ICHAR TEXTEQU <DB>
    IINT8 TEXTEQU <DB>
    IUINT8 TEXTEQU <DB>
    ISCHAR TEXTEQU <DB>
    ISINT8 TEXTEQU <DB>
    ICHAR8_T TEXTEQU <DB>
    IINT8_T TEXTEQU <DB>
    IUINT8_T TEXTEQU <DB>
    ISCHAR8_T TEXTEQU <DB>
    ISINT8_T TEXTEQU <DB>
    IINT16 TEXTEQU <DW>
    IUINT16 TEXTEQU <DW>
    ISINT16 TEXTEQU <DW>
    ICHAR16_T TEXTEQU <DW>
    IINT16_T TEXTEQU <DW>
    IUINT16_T TEXTEQU <DW>
    ISCHAR16_T TEXTEQU <DW>
    ISINT16_T TEXTEQU <DW>
    IWCHAR_T TEXTEQU <DW>
    IFDEF UNICODE
    ITCHAR TEXTEQU <DW>
    ELSE
    ITCHAR TEXTEQU <DB>
    ENDIF
   ;/IINT TEXTEQU <DWORD> cannot be used instruction type*/
    IBOOL TEXTEQU <DD>
    ILONG TEXTEQU <DD>
    IINT32 TEXTEQU <DD>
    IUINT32 TEXTEQU <DD>
    ISLONG TEXTEQU <DD>
    ISINT32 TEXTEQU <DD>
    ICHAR32_T TEXTEQU <DD>
    IINT32_T TEXTEQU <DD>
    IUINT32_T TEXTEQU <DD>
    ISCHAR32_T TEXTEQU <DD>
    ISINT32_T TEXTEQU <DD>
    ILONGLONG TEXTEQU <DQ>
    IINT64 TEXTEQU <DQ>
    IUINT64 TEXTEQU <DQ>
    ISLONGLONG TEXTEQU <DQ>
    ISINT64 TEXTEQU <DQ>
    IINT64_T TEXTEQU <DQ>
    IUINT64_T TEXTEQU <DQ>
    ISINT64_T TEXTEQU <DQ>
    IFLOAT16 TEXTEQU <DW>
    IBFLOAT16 TEXTEQU <DW>
    IFLT16 TEXTEQU <DW>
    IBFLT16 TEXTEQU <DW>
    IFLOAT TEXTEQU <REAL4>
    IFLT TEXTEQU <REAL4>
    IFLOAT32 TEXTEQU <REAL4>
    IFLT32 TEXTEQU <REAL4>
    IDOUBLE TEXTEQU <REAL8>
    IDBL TEXTEQU <REAL8>
    IFLOAT64 TEXTEQU <REAL8>
    IFLT64 TEXTEQU <REAL8>
    IXM128 TEXTEQU <XMMWORD>
    IXM256 TEXTEQU <YMMWORD>
    IXM512 TEXTEQU <ZMMWORD>
    IM128 TEXTEQU <__m128>
    IM256 TEXTEQU <__m256>
    IM512 TEXTEQU <__m512>
    IFLOAT128 TEXTEQU <__m128f>
    IFLOAT256 TEXTEQU <__m256f>
    IFLOAT512 TEXTEQU <__m512f>
    IDOUBLE128 TEXTEQU <__m128d>
    IDOUBLE256 TEXTEQU <__m256d>
    IDOUBLE512 TEXTEQU <__m512d>
    IFLT128 TEXTEQU <__m128f>
    IFLT256 TEXTEQU <__m256f>
    IFLT512 TEXTEQU <__m512f>
    IDBL128 TEXTEQU <__m128d>
    IDBL256 TEXTEQU <__m256d>
    IDBL512 TEXTEQU <__m512d>
    IINT8_128 TEXTEQU <__m128b>
    IINT8_256 TEXTEQU <__m256b>
    IINT8_512 TEXTEQU <__m512b>
    IINT16_128 TEXTEQU <__m128w>
    IINT16_256 TEXTEQU <__m256w>
    IINT16_512 TEXTEQU <__m512w>
    IINT32_128 TEXTEQU <__m128i>
    IINT32_256 TEXTEQU <__m256i>
    IINT32_512 TEXTEQU <__m512i>
    IINT64_128 TEXTEQU <__m128q>
    IINT64_256 TEXTEQU <__m256q>
    IINT64_512 TEXTEQU <__m512q>

    IFDEF __X64__
    SIZE_T TEXTEQU <QWORD>
    PTRDIFF_T TEXTEQU <QWORD>
    INTPTR_T TEXTEQU <QWORD>
    UINTPTR_T TEXTEQU <QWORD>
    ISIZE_T TEXTEQU <DQ>
    PTR_SIZE_T TEXTEQU <PTR QWORD>
    SIZE_T_PTR TEXTEQU <QWORD PTR>
    PTR32 TEXTEQU <QWORD>
    PTR64 TEXTEQU <QWORD>
    ENDIF ;/*__X64__*/

    IFDEF __X32__
    SIZE_T TEXTEQU <DWORD>
    PTRDIFF_T TEXTEQU <DWORD>
    INTPTR_T TEXTEQU <DWORD>
    UINTPTR_T TEXTEQU <DWORD>
    ISIZE_T TEXTEQU <DD>
    PTR_SIZE_T TEXTEQU <PTR DWORD>
    SIZE_T_PTR TEXTEQU <DWORD PTR>
    PTR32 TEXTEQU <DWORD>
    PTR64 TEXTEQU <DWORD>
    ENDIF ;/*__X32__*/

    INT8_PTR TEXTEQU <BYTE PTR>
    UINT8_PTR TEXTEQU <BYTE PTR>
    SINT8_PTR TEXTEQU <SBYTE PTR>
    INT8_T_PTR TEXTEQU <BYTE PTR>
    UINT8_T_PTR TEXTEQU <BYTE PTR>
    SINT8_T_PTR TEXTEQU <SBYTE PTR>
    CHAR_PTR TEXTEQU <BYTE PTR>
    CHAR8_T_PTR TEXTEQU <BYTE PTR>
    INT16_PTR TEXTEQU <WORD PTR>
    UINT16_PTR TEXTEQU <WORD PTR>
    SINT16_PTR TEXTEQU <SWORD PTR>
    INT16_T_PTR TEXTEQU <WORD PTR>
    UINT16_T_PTR TEXTEQU <WORD PTR>
    SINT16_T_PTR TEXTEQU <SWORD PTR>
    CHAR16_T_PTR TEXTEQU <WORD PTR>
    WCHAR_T_PTR TEXTEQU <WORD PTR>
    IFDEF UNICODE
    TCHAR_PTR TEXTEQU <WORD PTR>
    ELSE
    TCHAR_PTR TEXTEQU <BYTE PTR>
    ENDIF
   ;/INT TEXTEQU <DWORD> cannot be used instruction type*/
    INT32_PTR TEXTEQU <DWORD PTR>
    UINT32_PTR TEXTEQU <DWORD PTR>
    SINT32_PTR TEXTEQU <SDWORD PTR>
    INT32_T_PTR TEXTEQU <DWORD PTR>
    UINT32_T_PTR TEXTEQU <DWORD PTR>
    SINT32_T_PTR TEXTEQU <SDWORD PTR>
    CHAR32_T_PTR TEXTEQU <DWORD PTR>
    INT64_PTR TEXTEQU <QWORD PTR>
    UINT64_PTR TEXTEQU <QWORD PTR>
    SINT64_PTR TEXTEQU <SQWORD PTR>
    INT64_T_PTR TEXTEQU <QWORD PTR>
    UINT64_T_PTR TEXTEQU <QWORD PTR>
    SINT64_T_PTR TEXTEQU <SQWORD PTR>
    FLOAT16_PTR TEXTEQU <WORD PTR>
    BFLOAT16_PTR TEXTEQU <WORD PTR>
    FLT16_PTR TEXTEQU <WORD PTR>
    BFLT16_PTR TEXTEQU <WORD PTR>
    FLOAT_PTR TEXTEQU <REAL4 PTR>
    FLT_PTR TEXTEQU <REAL4 PTR>
    FLOAT32_PTR TEXTEQU <REAL4 PTR>
    FLT32_PTR TEXTEQU <REAL4 PTR>
    DOUBLE_PTR TEXTEQU <REAL8 PTR>
    DBL_PTR TEXTEQU <REAL8 PTR>
    FLOAT64_PTR TEXTEQU <REAL8 PTR>
    FLT64_PTR TEXTEQU <REAL8 PTR>
    XM128_PTR TEXTEQU <XMMWORD PTR>
    XM256_PTR TEXTEQU <YMMWORD PTR>
    XM512_PTR TEXTEQU <ZMMWORD PTR>
    M128_PTR TEXTEQU <__m128 PTR>
    M256_PTR TEXTEQU <__m256 PTR>
    M512_PTR TEXTEQU <__m512 PTR>
    FLOAT128_PTR TEXTEQU <__m128f PTR>
    FLOAT256_PTR TEXTEQU <__m256f PTR>
    FLOAT512_PTR TEXTEQU <__m512f PTR>
    DOUBLE128_PTR TEXTEQU <__m128d PTR>
    DOUBLE256_PTR TEXTEQU <__m256d PTR>
    DOUBLE512_PTR TEXTEQU <__m512d PTR>
    FLT128_PTR TEXTEQU <__m128f PTR>
    FLT256_PTR TEXTEQU <__m256f PTR>
    FLT512_PTR TEXTEQU <__m512f PTR>
    DBL128_PTR TEXTEQU <__m128d PTR>
    DBL256_PTR TEXTEQU <__m256d PTR>
    DBL512_PTR TEXTEQU <__m512d PTR>
    INT8_128_PTR TEXTEQU <__m128b PTR>
    INT8_256_PTR TEXTEQU <__m256b PTR>
    INT8_512_PTR TEXTEQU <__m512b PTR>
    INT16_128_PTR TEXTEQU <__m128w PTR>
    INT16_256_PTR TEXTEQU <__m256w PTR>
    INT16_512_PTR TEXTEQU <__m512w PTR>
    INT32_128_PTR TEXTEQU <__m128i PTR>
    INT32_256_PTR TEXTEQU <__m256i PTR>
    INT32_512_PTR TEXTEQU <__m512i PTR>
    INT64_128_PTR TEXTEQU <__m128q PTR>
    INT64_256_PTR TEXTEQU <__m256q PTR>
    INT64_512_PTR TEXTEQU <__m512q PTR>

    PTR_INT8 TEXTEQU <PTR BYTE>
    PTR_UINT8 TEXTEQU <PTR BYTE>
    PTR_SINT8 TEXTEQU <PTR SBYTE>
    PTR_INT8_T TEXTEQU <PTR BYTE>
    PTR_UINT8_T TEXTEQU <PTR BYTE>
    PTR_SINT8_T TEXTEQU <PTR SBYTE>
    PTR_CHAR TEXTEQU <PTR BYTE>
    PTR_CHAR8_T TEXTEQU <PTR BYTE>
    PTR_INT16 TEXTEQU <PTR WORD>
    PTR_UINT16 TEXTEQU <PTR WORD>
    PTR_SINT16 TEXTEQU <PTR SWORD>
    PTR_INT16_T TEXTEQU <PTR WORD>
    PTR_UINT16_T TEXTEQU <PTR WORD>
    PTR_SINT16_T TEXTEQU <PTR SWORD>
    PTR_CHAR16_T TEXTEQU <PTR WORD>
    PTR_WCHAR_T TEXTEQU <PTR WORD>
    IFDEF UNICODE
    PTR_TCHAR TEXTEQU <PTR WORD>
    ELSE
    PTR_TCHAR TEXTEQU <PTR BYTE>
    ENDIF
   ;/INT TEXTEQU <DWORD> cannot be used instruction type*/
    PTR_INT32 TEXTEQU <PTR DWORD>
    PTR_UINT32 TEXTEQU <PTR DWORD>
    PTR_SINT32 TEXTEQU <PTR SDWORD>
    PTR_INT32_T TEXTEQU <PTR DWORD>
    PTR_UINT32_T TEXTEQU <PTR DWORD>
    PTR_SINT32_T TEXTEQU <PTR SDWORD>
    PTR_CHAR32_T TEXTEQU <PTR DWORD>
    PTR_INT64 TEXTEQU <PTR QWORD>
    PTR_UINT64 TEXTEQU <PTR QWORD>
    PTR_SINT64 TEXTEQU <PTR SQWORD>
    PTR_INT64_T TEXTEQU <PTR QWORD>
    PTR_UINT64_T TEXTEQU <PTR QWORD>
    PTR_SINT64_T TEXTEQU <PTR SQWORD>
    PTR_FLOAT16 TEXTEQU <PTR WORD>
    PTR_BFLOAT16 TEXTEQU <PTR WORD>
    PTR_FLT16 TEXTEQU <PTR WORD>
    PTR_BFLT16 TEXTEQU <PTR WORD>
    PTR_FLOAT TEXTEQU <PTR REAL4>
    PTR_FLT TEXTEQU <PTR REAL4>
    PTR_FLOAT32 TEXTEQU <PTR REAL4>
    PTR_FLT32 TEXTEQU <PTR REAL4>
    PTR_DOUBLE TEXTEQU <PTR REAL8>
    PTR_DBL TEXTEQU <PTR REAL8>
    PTR_FLOAT64 TEXTEQU <PTR REAL8>
    PTR_FLT64 TEXTEQU <PTR REAL8>
    PTR_XM128 TEXTEQU <PTR XMMWORD>
    PTR_XM256 TEXTEQU <PTR YMMWORD>
    PTR_XM512 TEXTEQU <PTR ZMMWORD>
    PTR_M128 TEXTEQU <PTR __m128>
    PTR_M256 TEXTEQU <PTR __m256>
    PTR_M512 TEXTEQU <PTR __m512>
    PTR_FLOAT128 TEXTEQU <PTR __m128f>
    PTR_FLOAT256 TEXTEQU <PTR __m256f>
    PTR_FLOAT512 TEXTEQU <PTR __m512f>
    PTR_DOUBLE128 TEXTEQU <PTR __m128d>
    PTR_DOUBLE256 TEXTEQU <PTR __m256d>
    PTR_DOUBLE512 TEXTEQU <PTR __m512d>
    PTR_FLT128 TEXTEQU <PTR __m128f>
    PTR_FLT256 TEXTEQU <PTR __m256f>
    PTR_FLT512 TEXTEQU <PTR __m512f>
    PTR_DBL128 TEXTEQU <PTR __m128d>
    PTR_DBL256 TEXTEQU <PTR __m256d>
    PTR_DBL512 TEXTEQU <PTR __m512d>
    PTR_INT8_128 TEXTEQU <PTR __m128b>
    PTR_INT8_256 TEXTEQU <PTR __m256b>
    PTR_INT8_512 TEXTEQU <PTR __m512b>
    PTR_INT16_128 TEXTEQU <PTR __m128w>
    PTR_INT16_256 TEXTEQU <PTR __m256w>
    PTR_INT16_512 TEXTEQU <PTR __m512w>
    PTR_INT32_128 TEXTEQU <PTR __m128i>
    PTR_INT32_256 TEXTEQU <PTR __m256i>
    PTR_INT32_512 TEXTEQU <PTR __m512i>
    PTR_INT64_128 TEXTEQU <PTR __m128q>
    PTR_INT64_256 TEXTEQU <PTR __m256q>
    PTR_INT64_512 TEXTEQU <PTR __m512q>
    
    IFDEF CASEMAPNONE
    char TEXTEQU <CHAR>
    int8 TEXTEQU <INT8>
    uint8 TEXTEQU <UINT8>
    schar TEXTEQU <SCHAR>
    sint8 TEXTEQU <SINT8>
    char8_t TEXTEQU <CHAR8_T>
    int8_t TEXTEQU <INT8_T>
    uint8_t TEXTEQU <UINT8_T>
    schar8_t TEXTEQU <SCHAR8_T>
    sint8_t TEXTEQU <SINT8_T>
    int16 TEXTEQU <INT16>
    uint16 TEXTEQU <UINT16>
    sint16 TEXTEQU <SINT16>
    char16_t TEXTEQU <CHAR16_T>
    int16_t TEXTEQU <INT16_T>
    uint16_t TEXTEQU <UINT16_T>
    schar16_t TEXTEQU <SCHAR16_T>
    sint16_t TEXTEQU <SINT16_T>
    wchar_t TEXTEQU <WCHAR_T>
    tchar TEXTEQU <TCHAR>
   ;/*int TEXTEQU <INT> cannot be used instruction type*/
    bool TEXTEQU <BOOL>
    long TEXTEQU <LONG>
    int32 TEXTEQU <INT32>
    uint32 TEXTEQU <UINT32>
    slong TEXTEQU <SLONG>
    sint32 TEXTEQU <SINT32>
    char32_t TEXTEQU <CHAR32_T>
    int32_t TEXTEQU <INT32_T>
    uint32_t TEXTEQU <UINT32_T>
    schar32_t TEXTEQU <SCHAR32_T>
    sint32_t TEXTEQU <SINT32_T>
    longlong TEXTEQU <LONGLONG>
    int64 TEXTEQU <INT64>
    uint64 TEXTEQU <UINT64>
    slonglong TEXTEQU <SLONGLONG>
    sint64 TEXTEQU <SINT64>
    int64_t TEXTEQU <INT64_T>
    uint64_t TEXTEQU <UINT64_T>
    sint64_t TEXTEQU <SINT64_T>
    float16 TEXTEQU <FLOAT16>
    bfloat16 TEXTEQU <BFLOAT16>
    flt16 TEXTEQU <FLT16>
    bflt16 TEXTEQU <BFLT16>
    float TEXTEQU <FLOAT>
    flt TEXTEQU <FLT>
    float32 TEXTEQU <FLOAT32>
    flt32 TEXTEQU <FLT32>
    double TEXTEQU <DOUBLE>
    dbl TEXTEQU <DBL>
    float64 TEXTEQU <FLOAT64>
    flt64 TEXTEQU <FLT64>
    xm128 TEXTEQU <XM128>
    xm256 TEXTEQU <XM256>
    xm512 TEXTEQU <XM512>
    m128 TEXTEQU <M128>
    m256 TEXTEQU <M256>
    m512 TEXTEQU <M512>
    float128 TEXTEQU <FLOAT128>
    float256 TEXTEQU <FLOAT256>
    float512 TEXTEQU <FLOAT512>
    double128 TEXTEQU <DOUBLE128>
    double256 TEXTEQU <DOUBLE256>
    double512 TEXTEQU <DOUBLE512>
    flt128 TEXTEQU <FLT128>
    flt256 TEXTEQU <FLT256>
    flt512 TEXTEQU <FLT512>
    dbl128 TEXTEQU <DBL128>
    dbl256 TEXTEQU <DBL256>
    dbl512 TEXTEQU <DBL512>
    int8_128 TEXTEQU <INT8_128>
    int8_256 TEXTEQU <INT8_256>
    int8_512 TEXTEQU <INT8_512>
    int16_128 TEXTEQU <INT16_128>
    int16_256 TEXTEQU <INT16_256>
    int16_512 TEXTEQU <INT16_512>
    int32_128 TEXTEQU <INT32_128>
    int32_256 TEXTEQU <INT32_256>
    int32_512 TEXTEQU <INT32_512>
    int64_128 TEXTEQU <INT64_128>
    int64_256 TEXTEQU <INT64_256>
    int64_512 TEXTEQU <INT64_512>
    void TEXTEQU <VOID>
    
    ichar TEXTEQU <ICHAR>
    iint8 TEXTEQU <IINT8>
    iuint8 TEXTEQU <IUINT8>
    ischar TEXTEQU <ISCHAR>
    isint8 TEXTEQU <ISINT8>
    ichar8_t TEXTEQU <ICHAR8_T>
    iint8_t TEXTEQU <IINT8_T>
    iuint8_t TEXTEQU <IUINT8_T>
    ischar8_t TEXTEQU <ISCHAR8_T>
    isint8_t TEXTEQU <ISINT8_T>
    iint16 TEXTEQU <IINT16>
    iuint16 TEXTEQU <IUINT16>
    isint16 TEXTEQU <ISINT16>
    ichar16_t TEXTEQU <ICHAR16_T>
    iint16_t TEXTEQU <IINT16_T>
    iuint16_t TEXTEQU <IUINT16_T>
    ischar16_t TEXTEQU <ISCHAR16_T>
    isint16_t TEXTEQU <ISINT16_T>
    iwchar_t TEXTEQU <IWCHAR_T>
    itchar TEXTEQU <ITCHAR>
   ;/*AddLineQueue("iint TEXTEQU <IINT> cannot be used instruction type*/
    ibool TEXTEQU <IBOOL>
    ilong TEXTEQU <ILONG>
    iint32 TEXTEQU <IINT32>
    iuint32 TEXTEQU <IUINT32>
    islong TEXTEQU <ISLONG>
    isint32 TEXTEQU <ISINT32>
    ichar32_t TEXTEQU <ICHAR32_T>
    iint32_t TEXTEQU <IINT32_T>
    iuint32_t TEXTEQU <IUINT32_T>
    ischar32_t TEXTEQU <ISCHAR32_T>
    isint32_t TEXTEQU <ISINT32_T>
    ilonglong TEXTEQU <ILONGLONG>
    iint64 TEXTEQU <IINT64>
    iuint64 TEXTEQU <IUINT64>
    islonglong TEXTEQU <ISLONGLONG>
    isint64 TEXTEQU <ISINT64>
    iint64_t TEXTEQU <IINT64_T>
    iuint64_t TEXTEQU <IUINT64_T>
    isint64_t TEXTEQU <ISINT64_T>    
    ifloat16 TEXTEQU <IFLOAT16>
    ibfloat16 TEXTEQU <IBFLOAT16>
    iflt16 TEXTEQU <IFLT16>
    ibflt16 TEXTEQU <IBFLT16>
    ifloat TEXTEQU <IFLOAT>
    iflt TEXTEQU <IFLT>
    ifloat32 TEXTEQU <IFLOAT32>
    iflt32 TEXTEQU <IFLT32>
    idouble TEXTEQU <IDOUBLE>
    idbl TEXTEQU <IDBL>
    ifloat64 TEXTEQU <IFLOAT64>
    iflt64 TEXTEQU <IFLT64>
    ixm128 TEXTEQU <IXM128>
    ixm256 TEXTEQU <IXM256>
    ixm512 TEXTEQU <IXM512>
    im128 TEXTEQU <IM128>
    im256 TEXTEQU <IM256>
    im512 TEXTEQU <IM512>
    ifloat128 TEXTEQU <IFLOAT128>
    ifloat256 TEXTEQU <IFLOAT256>
    ifloat512 TEXTEQU <IFLOAT512>
    idouble128 TEXTEQU <IDOUBLE128>
    idouble256 TEXTEQU <IDOUBLE256>
    idouble512 TEXTEQU <IDOUBLE512>
    iflt128 TEXTEQU <IFLT128>
    iflt256 TEXTEQU <IFLT256>
    iflt512 TEXTEQU <IFLT512>
    idbl128 TEXTEQU <IDBL128>
    idbl256 TEXTEQU <IDBL256>
    idbl512 TEXTEQU <IDBL512>
    iint8_128 TEXTEQU <IINT8_128>
    iint8_256 TEXTEQU <IINT8_256>
    iint8_512 TEXTEQU <IINT8_512>
    iint16_128 TEXTEQU <IINT16_128>
    iint16_256 TEXTEQU <IINT16_256>
    iint16_512 TEXTEQU <IINT16_512>
    iint32_128 TEXTEQU <IINT32_128>
    iint32_256 TEXTEQU <IINT32_256>
    iint32_512 TEXTEQU <IINT32_512>
    iint64_128 TEXTEQU <IINT64_128>
    iint64_256 TEXTEQU <IINT64_256>
    iint64_512 TEXTEQU <IINT64_512>

    size_t TEXTEQU <SIZE_T>
    ptrdiff_t TEXTEQU <PTRDIFF_T>
    intptr_t TEXTEQU <INTPTR_T>
    uintptr_t TEXTEQU <UINTPTR_T>
    isize_t TEXTEQU <ISIZE_T>
    ptr_size_t TEXTEQU <PTR_SIZE_T>
    size_t_ptr TEXTEQU <SIZE_T_PTR>
    
    int8_ptr TEXTEQU <INT8_PTR>
    uint8_ptr TEXTEQU <UINT8_PTR>
    sint8_ptr TEXTEQU <SINT8_PTR>
    int8_t_ptr TEXTEQU <INT8_T_PTR>
    uint8_t_ptr TEXTEQU <UINT8_T_PTR>
    sint8_t_ptr TEXTEQU <SINT8_T_PTR>
    char_ptr TEXTEQU <CHAR_PTR>
    char8_t_ptr TEXTEQU <CHAR8_T_PTR>
    int16_ptr TEXTEQU <INT16_PTR>
    uint16_ptr TEXTEQU <UINT16_PTR>
    sint16_ptr TEXTEQU <SINT16_PTR>
    int16_t_ptr TEXTEQU <INT16_T_PTR>
    uint16_t_ptr TEXTEQU <UINT16_T_PTR>
    sint16_t_ptr TEXTEQU <SINT16_T_PTR>
    char16_t_ptr TEXTEQU <CHAR16_T_PTR>
    wchar_t_ptr TEXTEQU <WCHAR_T_PTR>
    tchar_ptr TEXTEQU <TCHAR_PTR>
  ; /*int TEXTEQU <INT> cannot be used instruction type*/
    int32_ptr TEXTEQU <INT32_PTR>
    uint32_ptr TEXTEQU <UINT32_PTR>
    sint32_ptr TEXTEQU <SINT32_PTR>
    int32_t_ptr TEXTEQU <INT32_T_PTR>
    uint32_t_ptr TEXTEQU <UINT32_T_PTR>
    sint32_t_ptr TEXTEQU <SINT32_T_PTR>
    char32_t_ptr TEXTEQU <CHAR32_T_PTR>
    int64_ptr TEXTEQU <INT64_PTR>
    uint64_ptr TEXTEQU <UINT64_PTR>
    sint64_ptr TEXTEQU <SINT64_PTR>
    int64_t_ptr TEXTEQU <INT64_T_PTR>
    uint64_t_ptr TEXTEQU <UINT64_T_PTR>
    sint64_t_ptr TEXTEQU <SINT64_T_PTR>
    float16_ptr TEXTEQU <FLOAT16_PTR>
    bfloat16_ptr TEXTEQU <BFLOAT16_PTR>
    flt16_ptr TEXTEQU <FLT16_PTR>
    bflt16_ptr TEXTEQU <BFLT16_PTR>
    float_ptr TEXTEQU <FLOAT_PTR>
    flt_ptr TEXTEQU <FLT_PTR>
    float32_ptr TEXTEQU <FLOAT32_PTR>
    flt32_ptr TEXTEQU <FLT32_PTR>
    double_ptr TEXTEQU <DOUBLE_PTR>
    dbl_ptr TEXTEQU <DBL_PTR>
    float64_ptr TEXTEQU <FLOAT64_PTR>
    flt64_ptr TEXTEQU <FLT64_PTR>
    xm128_ptr TEXTEQU <XM128_PTR>
    xm256_ptr TEXTEQU <XM256_PTR>
    xm512_ptr TEXTEQU <XM512_PTR>
    m128_ptr TEXTEQU <M128_PTR>
    m256_ptr TEXTEQU <M256_PTR>
    m512_ptr TEXTEQU <M512_PTR>
    float128_ptr TEXTEQU <FLOAT128_PTR>
    float256_ptr TEXTEQU <FLOAT256_PTR>
    float512_ptr TEXTEQU <FLOAT512_PTR>
    double128_ptr TEXTEQU <DOUBLE128_PTR>
    double256_ptr TEXTEQU <DOUBLE256_PTR>
    double512_ptr TEXTEQU <DOUBLE512_PTR>
    flt128_ptr TEXTEQU <FLT128_PTR>
    flt256_ptr TEXTEQU <FLT256_PTR>
    flt512_ptr TEXTEQU <FLT512_PTR>
    dbl128_ptr TEXTEQU <DBL128_PTR>
    dbl256_ptr TEXTEQU <DBL256_PTR>
    dbl512_ptr TEXTEQU <DBL512_PTR>
    int8_128_ptr TEXTEQU <INT8_128_PTR>
    int8_256_ptr TEXTEQU <INT8_256_PTR>
    int8_512_ptr TEXTEQU <INT8_512_PTR>
    int16_128_ptr TEXTEQU <INT16_128_PTR>
    int16_256_ptr TEXTEQU <INT16_256_PTR>
    int16_512_ptr TEXTEQU <INT16_512_PTR>
    int32_128_ptr TEXTEQU <INT32_128_PTR>
    int32_256_ptr TEXTEQU <INT32_256_PTR>
    int32_512_ptr TEXTEQU <INT32_512_PTR>
    int64_128_ptr TEXTEQU <INT64_128_PTR>
    int64_256_ptr TEXTEQU <INT64_256_PTR>
    int64_512_ptr TEXTEQU <INT64_512_PTR>

    ptr_int8 TEXTEQU <PTR_INT8>
    ptr_uint8 TEXTEQU <PTR_UINT8>
    ptr_sint8 TEXTEQU <PTR_SINT8>
    ptr_int8_t TEXTEQU <PTR_INT8_T>
    ptr_uint8_t TEXTEQU <PTR_UINT8_T>
    ptr_sint8_t TEXTEQU <PTR_SINT8_T>
    ptr_char TEXTEQU <PTR_CHAR>
    ptr_char8_t TEXTEQU <PTR_CHAR8_T>
    ptr_int16 TEXTEQU <PTR_INT16>
    ptr_uint16 TEXTEQU <PTR_UINT16>
    ptr_sint16 TEXTEQU <PTR_SINT16>
    ptr_int16_t TEXTEQU <PTR_INT16_T>
    ptr_uint16_t TEXTEQU <PTR_UINT16_T>
    ptr_sint16_t TEXTEQU <PTR_SINT16_T>
    ptr_char16_t TEXTEQU <PTR_CHAR16_T>
    ptr_wchar_t TEXTEQU <PTR_WCHAR_T>
    ptr_tchar TEXTEQU <PTR_TCHAR>
  ; /*int TEXTEQU <INT> cannot be used instruction type*/
    ptr_int32 TEXTEQU <PTR_INT32>
    ptr_uint32 TEXTEQU <PTR_UINT32>
    ptr_sint32 TEXTEQU <PTR_SINT32>
    ptr_int32_t TEXTEQU <PTR_INT32_T>
    ptr_uint32_t TEXTEQU <PTR_UINT32_T>
    ptr_sint32_t TEXTEQU <PTR_SINT32_T>
    ptr_char32_t TEXTEQU <PTR_CHAR32_T>
    ptr_int64 TEXTEQU <PTR_INT64>
    ptr_uint64 TEXTEQU <PTR_UINT64>
    ptr_sint64 TEXTEQU <PTR_SINT64>
    ptr_int64_t TEXTEQU <PTR_INT64_T>
    ptr_uint64_t TEXTEQU <PTR_UINT64_T>
    ptr_sint64_t TEXTEQU <PTR_SINT64_T>
    ptr_float16 TEXTEQU <PTR_FLOAT16>
    ptr_bfloat16 TEXTEQU <PTR_BFLOAT16>
    ptr_flt16 TEXTEQU <PTR_FLT16>
    ptr_bflt16 TEXTEQU <PTR_BFLT16>
    ptr_float TEXTEQU <PTR_FLOAT>
    ptr_flt TEXTEQU <PTR_FLT>
    ptr_float32 TEXTEQU <PTR_FLOAT32>
    ptr_flt32 TEXTEQU <PTR_FLT32>
    ptr_double TEXTEQU <PTR_DOUBLE>
    ptr_dbl TEXTEQU <PTR_DBL>
    ptr_float64 TEXTEQU <PTR_FLOAT64>
    ptr_flt64 TEXTEQU <PTR_FLT64>
    ptr_xm128 TEXTEQU <PTR_XM128>
    ptr_xm256 TEXTEQU <PTR_XM256>
    ptr_xm512 TEXTEQU <PTR_XM512>
    ptr_m128 TEXTEQU <PTR_M128>
    ptr_m256 TEXTEQU <PTR_M256>
    ptr_m512 TEXTEQU <PTR_M512>
    ptr_float128 TEXTEQU <PTR_FLOAT128>
    ptr_float256 TEXTEQU <PTR_FLOAT256>
    ptr_float512 TEXTEQU <PTR_FLOAT512>
    ptr_double128 TEXTEQU <PTR_DOUBLE128>
    ptr_double256 TEXTEQU <PTR_DOUBLE256>
    ptr_double512 TEXTEQU <PTR_DOUBLE512>
    ptr_flt128 TEXTEQU <PTR_FLT128>
    ptr_flt256 TEXTEQU <PTR_FLT256>
    ptr_flt512 TEXTEQU <PTR_FLT512>
    ptr_dbl128 TEXTEQU <PTR_DBL128>
    ptr_dbl256 TEXTEQU <PTR_DBL256>
    ptr_dbl512 TEXTEQU <PTR_DBL512>
    ptr_int8_128 TEXTEQU <PTR_INT8_128>
    ptr_int8_256 TEXTEQU <PTR_INT8_256>
    ptr_int8_512 TEXTEQU <PTR_INT8_512>
    ptr_int16_128 TEXTEQU <PTR_INT16_128>
    ptr_int16_256 TEXTEQU <PTR_INT16_256>
    ptr_int16_512 TEXTEQU <PTR_INT16_512>
    ptr_int32_128 TEXTEQU <PTR_INT32_128>
    ptr_int32_256 TEXTEQU <PTR_INT32_256>
    ptr_int32_512 TEXTEQU <PTR_INT32_512>
    ptr_int64_128 TEXTEQU <PTR_INT64_128>
    ptr_int64_256 TEXTEQU <PTR_INT64_256>
    ptr_int64_512 TEXTEQU <PTR_INT64_512>
    ENDIF ;CASEMAPNONE

    ENDIF ;WITHMACROLIB

    ENDIF    ;TYPES_INC