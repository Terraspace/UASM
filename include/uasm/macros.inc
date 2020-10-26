
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

    IFNDEF MACROS_INC
    MACROS_INC EQU 1
    
    IFDEF WITHMACROLIB

    IFNDEF MACROLIB_INC
    .ERR <"MACROS_INC must be included by MACROLIB_INC">
    ENDIF
    
    IFNDEF DEFINES_INC
    .ERR <"MACROS_INC requires DEFINES_INC">
    ENDIF
    
    IFNDEF LIMITS_INC
    .ERR <"MACROS_INC requires LIMITS_INC">
    ENDIF
    
    IFNDEF X86ORX64
    .ERR <"MACROS_INC requires one x86 OR x64 platform type">
    ENDIF

    IFNDEF CDECL
    CDECL TEXTEQU <C>
    ENDIF
    
    IFNDEF CDECLOPT
    CDECLOPT TEXTEQU <OPTION LANGUAGE:C>
    ENDIF

    IFDEF __WIN64__
    IFNDEF VECTORCALLOPT
    VECTORCALLOPT TEXTEQU <OPTION LANGUAGE:VECTORCALL>
    ENDIF
    IFNDEF FASTCALLOPT
    FASTCALLOPT TEXTEQU < >
    ENDIF
    IFNDEF SYSTEMVOPT
    SYSTEMVOPT TEXTEQU < >
    ENDIF
    IFNDEF REGCALLOPT
    REGCALLOPT TEXTEQU <OPTION LANGUAGE:REGCALL>
    ENDIF
    IFNDEF CALLCONV
    CALLCONV TEXTEQU <VECTORCALL>
    ENDIF
    IFNDEF CALLCONVOPT
    CALLCONVOPT TEXTEQU <OPTION LANGUAGE:VECTORCALL>
    ENDIF
    IFNDEF STDCALLOPT
    STDCALLOPT TEXTEQU < >
    ENDIF
    IFNDEF THISCALLOPT
    THISCALLOPT TEXTEQU < >
    ENDIF
    IFNDEF SYSCALLOPT
    SYSCALLOPT TEXTEQU < >
    ENDIF
    ENDIF ;__WIN64__
    
    IFDEF __WIN32__
    IFNDEF VECTORCALLOPT
    VECTORCALLOPT TEXTEQU <OPTION LANGUAGE:VECTORCALL>
    ENDIF
    IFNDEF FASTCALLOPT
    FASTCALLOPT TEXTEQU <OPTION LANGUAGE:FASTCALL>
    ENDIF
    IFNDEF REGCALLOPT
    REGCALLOPT TEXTEQU <OPTION LANGUAGE:REGCALL>
    ENDIF
    IFNDEF CALLCONV
    CALLCONV TEXTEQU <VECTORCALL>
    ENDIF
    IFNDEF CALLCONVOPT
    CALLCONVOPT TEXTEQU <OPTION LANGUAGE:VECTORCALL>
    ENDIF
    IFNDEF SYSTEMVOPT
    SYSTEMVOPT TEXTEQU < >
    ENDIF
    IFNDEF STDCALLOPT
    STDCALLOPT TEXTEQU <OPTION LANGUAGE:STDCALL>
    ENDIF
    IFNDEF THISCALLOPT
    THISCALLOPT TEXTEQU <OPTION LANGUAGE:THISCALL>
    ENDIF
    IFNDEF SYSCALLOPT
    SYSCALLOPT TEXTEQU < >
    ENDIF
    ENDIF ;__WIN32__
    
    IFDEF __UNIX64__
    IFNDEF SYSTEMVOPT
    SYSTEMVOPT TEXTEQU <OPTION LANGUAGE:SYSTEMV>
    ENDIF
    IFNDEF REGCALLOPT
    REGCALLOPT TEXTEQU <OPTION LANGUAGE:REGCALL>
    ENDIF
    IFNDEF CALLCONV
    CALLCONV TEXTEQU <SYSTEMV>
    ENDIF
    IFNDEF CALLCONVOPT
    CALLCONVOPT TEXTEQU <OPTION LANGUAGE:SYSTEMV>
    ENDIF
    IFNDEF VECTORCALLOPT
    VECTORCALLOPT TEXTEQU < >
    ENDIF
    IFNDEF FASTCALLOPT
    FASTCALLOPT TEXTEQU < >
    ENDIF
    IFNDEF STDCALLOPT
    STDCALLOPT TEXTEQU < >
    ENDIF
    IFNDEF THISCALLOPT
    THISCALLOPT TEXTEQU < >
    ENDIF
    IFNDEF SYSCALLOPT
    SYSCALLOPT TEXTEQU <OPTION LANGUAGE:SYSCALL>
    ENDIF
    ENDIF ;__UNIX64__
    
    IFDEF __UNIX32__
    IFNDEF SYSTEMVOPT
    SYSTEMVOPT TEXTEQU <OPTION LANGUAGE:SYSTEMV>
    ENDIF
    IFNDEF REGCALLOPT
    REGCALLOPT TEXTEQU <OPTION LANGUAGE:REGCALL>
    ENDIF
    IFNDEF VECTORCALLOPT
    VECTORCALLOPT TEXTEQU < >
    ENDIF
    IFNDEF FASTCALLOPT
    FASTCALLOPT TEXTEQU < >
    ENDIF
    IFNDEF CALLCONV
    CALLCONV TEXTEQU <SYSTEMV>
    ENDIF
    IFNDEF CALLCONVOPT
    CALLCONVOPT TEXTEQU <OPTION LANGUAGE:SYSTEMV>
    ENDIF
    IFNDEF STDCALLOPT
    STDCALLOPT TEXTEQU < >
    ENDIF
    IFNDEF THISCALLOPT
    THISCALLOPT TEXTEQU < >
    ENDIF
    IFNDEF SYSCALLOPT
    SYSCALLOPT TEXTEQU < >
    ENDIF
    ENDIF ;__UNIX32__

    IFNDEF DEFINE
    DEFINE MACRO DefName:REQ, defargs, textargs
        deffnex TEXTEQU <>
        deffnex CATSTR deffnex, <&DefName& >
        IFB <textargs>
            IFB <defargs>
                deffnex CATSTR deffnex, <EQU 1>
            ELSE
                deffnex CATSTR deffnex, <EQU defargs>
            ENDIF
        ELSE
                deffnex CATSTR deffnex, <TEXTEQU <defargs>>
        ENDIF
        deffnex
    ENDM
    ENDIF

    IFNDEF DEFINED
    DEFINED MACRO defarg
        IFDEF defarg
            EXITM <-1>
        ELSE
            EXITM <0>
        ENDIF
    ENDM
    ENDIF

    IFNDEF NOTDEFINED
    NOTDEFINED MACRO defarg
        IFNDEF defarg
            EXITM <-1>
        ELSE
            EXITM <0>
        ENDIF
    ENDM
    ENDIF

    IFNDEF ALIGNSTACK
    ALIGNSTACK MACRO
        IFDEF __X64__
            ALIGN 16
        ENDIF
        IFDEF __X32__
            ALIGN 8
        ENDIF
    ENDM
    ENDIF

    IFNDEF ALIGNSIZE_T
    ALIGNSIZE_T MACRO
        IFDEF __X64__
            ALIGN 8
        ENDIF
        IFDEF __X32__
            ALIGN 4
        ENDIF
    ENDM
    ENDIF
    
    IFNDEF ALIGNPTR
    ALIGNPTR MACRO
        IFDEF __X64__
            ALIGN 8
        ENDIF
        IFDEF __X32__
            ALIGN 4
        ENDIF
    ENDM
    ENDIF
    
    IFNDEF ALIGNMM
    ALIGNMM MACRO
        ALIGN 8
    ENDM
    ENDIF
    
    IFNDEF ALIGNXMM
    ALIGNXMM MACRO
        ALIGN 16
    ENDM
    ENDIF
    
    IFNDEF ALIGNYMM
    ALIGNYMM MACRO
        ALIGN 32
    ENDM
    ENDIF
    
    IFNDEF ALIGNZMM
    ALIGNZMM MACRO
        ALIGN 64
    ENDM
    ENDIF
    
    IFNDEF ALIGNFIELD
    ALIGNFIELD MACRO AlignSize
        OPTION FIELDALIGN:AlignSize
    ENDM
    ENDIF
    
    IFNDEF ALIGNSTACKFIELD
    ALIGNSTACKFIELD MACRO
        IFDEF __X64__
            OPTION FIELDALIGN:16
        ENDIF
        IFDEF __X32__
            OPTION FIELDALIGN:8
        ENDIF
    ENDM
    ENDIF
    
    IFNDEF ALIGNSIZE_TFIELD
    ALIGNSIZE_TFIELD MACRO
        IFDEF __X64__
            OPTION FIELDALIGN:8
        ENDIF
        IFDEF __X32__
            OPTION FIELDALIGN:4
        ENDIF
    ENDM
    ENDIF
    
    IFNDEF ALIGNPTRFIELD
    ALIGNPTRFIELD MACRO
        IFDEF __X64__
            OPTION FIELDALIGN:8
        ENDIF
        IFDEF __X32__
            OPTION FIELDALIGN:4
        ENDIF
    ENDM
    ENDIF
    
    IFNDEF ALIGNMMFIELD
    ALIGNMMFIELD MACRO
        OPTION FIELDALIGN:MM_SIZE
    ENDM
    ENDIF
    
    IFNDEF ALIGNXMMFIELD
    ALIGNXMMFIELD MACRO
        OPTION FIELDALIGN:XMM_SIZE
    ENDM
    ENDIF
    
    IFNDEF ALIGNYMMFIELD
    ALIGNYMMFIELD MACRO
        OPTION FIELDALIGN:YMM_SIZE
    ENDM
    ENDIF
    
    IFNDEF ALIGNZMMFIELD
    ALIGNZMMFIELD MACRO
        OPTION FIELDALIGN:ZMM_SIZE
    ENDM
    ENDIF
    
    IFNDEF
    ALIGNPROC MACRO AlignSize
        OPTION PROCALIGN:AlignSize
    ENDM
    ENDIF
    
    IFNDEF ALIGNSTACKPROC
    ALIGNSTACKPROC MACRO
        IFDEF __X64__
            OPTION PROCALIGN:16
        ENDIF
        IFDEF __X32__
            OPTION PROCALIGN:8
        ENDIF
    ENDM
    ENDIF
    
    IFNDEF ALIGNSIZE_TPROC
    ALIGNSIZE_TPROC MACRO
        IFDEF __X64__
            OPTION PROCALIGN:8
        ENDIF
        IFDEF __X32__
            OPTION PROCALIGN:4
        ENDIF
    ENDM
    ENDIF
    
    IFNDEF ALIGNPTRPROC
    ALIGNPTRPROC MACRO
        IFDEF __X64__
            OPTION PROCALIGN:8
        ENDIF
        IFDEF __X32__
            OPTION PROCALIGN:4
        ENDIF
    ENDM
    ENDIF
    
    IFNDEF ALIGNMMPROC
    ALIGNMMPROC MACRO
        OPTION PROCALIGN:MM_SIZE
    ENDM
    ENDIF
    
    IFNDEF ALIGNXMMPROC
    ALIGNXMMPROC MACRO
        OPTION PROCALIGN:XMM_SIZE
    ENDM
    ENDIF
    
    IFNDEF ALIGNYMMPROC
    ALIGNYMMPROC MACRO
        OPTION PROCALIGN:YMM_SIZE
    ENDM
    ENDIF
    
    IFNDEF ALIGNZMMPROC
    ALIGNZMMPROC MACRO
        OPTION PROCALIGN:ZMM_SIZE
    ENDM
    ENDIF
    
    IFNDEF ALIGNFIELDPROC
    ALIGNFIELDPROC MACRO AlignSize
        OPTION FIELDALIGN:AlignSize
        OPTION PROCALIGN:AlignSize
    ENDM
    ENDIF

    IFNDEF ALIGNSTACKFIELDPROC
    ALIGNSTACKFIELDPROC MACRO
        IFDEF __X64__
            OPTION FIELDALIGN:16
            OPTION PROCALIGN:16
        ENDIF
        IFDEF __X32__
            OPTION FIELDALIGN:8
            OPTION PROCALIGN:8
        ENDIF
    ENDM
    ENDIF

    IFNDEF ALIGNSIZE_TFIELDPROC
    ALIGNSIZE_TFIELDPROC MACRO
        IFDEF __X64__
            OPTION FIELDALIGN:8
            OPTION PROCALIGN:8
        ENDIF
        IFDEF __X32__
            OPTION FIELDALIGN:4
            OPTION PROCALIGN:4
        ENDIF
    ENDM
    ENDIF
    
    IFNDEF ALIGNPTRFIELDPROC
    ALIGNPTRFIELDPROC MACRO
        IFDEF __X64__
            OPTION FIELDALIGN:8
            OPTION PROCALIGN:8
        ENDIF
        IFDEF __X32__
            OPTION FIELDALIGN:4
            OPTION PROCALIGN:4
        ENDIF
    ENDM
    ENDIF
    
    IFNDEF ALIGNMMFIELDPROC
    ALIGNMMFIELDPROC MACRO
        OPTION FIELDALIGN:MM_SIZE
        OPTION PROCALIGN:MM_SIZE
    ENDM
    ENDIF
    
    IFNDEF ALIGNXMMFIELDPROC
    ALIGNXMMFIELDPROC MACRO
        OPTION FIELDALIGN:XMM_SIZE
        OPTION PROCALIGN:XMM_SIZE
    ENDM
    ENDIF
    
    IFNDEF ALIGNYMMFIELDPROC
    ALIGNYMMFIELDPROC MACRO
        OPTION FIELDALIGN:YMM_SIZE
        OPTION PROCALIGN:YMM_SIZE
    ENDM
    ENDIF
    
    IFNDEF ALIGNZMMFIELDPROC
    ALIGNZMMFIELDPROC MACRO
        OPTION FIELDALIGN:ZMM_SIZE
        OPTION PROCALIGN:ZMM_SIZE
    ENDM
    ENDIF
    
    IFNDEF PROCSTART
    PROCSTART MACRO functionName:REQ, callconvType:REQ, retType:REQ, inpFrame:REQ, usesStr:REQ, args:VARARG
        _currfunctionName_ TEXTEQU <functionName>
        _currargs_ TEXTEQU <args>
        fnexproto TEXTEQU <>
        fnexproto CATSTR fnexproto, <&functionName&>
        fnexproto CATSTR fnexproto, < PROTO >, <&callconvType&>, < >, <(&retType&)>, < >, <&args&>
        fnexproc TEXTEQU <>
        fnexproc CATSTR fnexproc, <&functionName&>
        fnexproc CATSTR fnexproc, < PROC >, <&callconvType&>, < >, <(&retType&)>, < >, <&inpFrame&>, < >, <&usesStr&>, < >, <&args&>
        fnexproto
        fnexproc
    ENDM
    ENDIF
    
    IFNDEF PROCEND
    PROCEND MACRO
        fnexprocend TEXTEQU <>
        fnexprocend CATSTR fnexprocend, _currfunctionName_
        fnexprocend CATSTR fnexprocend, < ENDP>
        fnexprocend
    ENDM
    ENDIF
    
    IFNDEF SHUFFLE4
    SHUFFLE4 MACRO V3, V2, V1, V0
        EXITM %((V3 SHL 6) OR (V2 SHL 4) OR (V1 SHL 2) OR (V0))
    ENDM
    ENDIF
    
    IFNDEF SHUFFLER4
    SHUFFLER4 MACRO V0, V1, V2, V3
        EXITM %((V0) OR (V1 SHL 2) OR (V2 SHL 4) OR (V3 SHL 6))
    ENDM
    ENDIF
    
    IFNDEF SHUFFLE2
    SHUFFLE2 MACRO V1, V0
        EXITM %((V1 SHL 1) OR (V0))
    ENDM
    ENDIF
    
    IFNDEF SHUFFLER2
    SHUFFLER2 MACRO V0, V1
        EXITM %((V0) OR (V1 SHL 1))
    ENDM
    ENDIF
    
    IFNDEF V64CI
    V64CI MACRO functionName:REQ, vectorType:REQ, V1:REQ
        mm64fnex TEXTEQU <>
        mm64fnex CATSTR mm64fnex, <&functionName&>
        PUBLIC mm64fnex
        mm64fnex CATSTR mm64fnex, < vectorType>,  < { V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1 } >
        mm64fnex
    ENDM
    ENDIF
    
    IFNDEF V64CI64
    V64CI64 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ, V3:REQ, V4:REQ, V5:REQ, V6:REQ, V7:REQ, V8:REQ, V9:REQ, V10:REQ, V11:REQ, V12:REQ, V13:REQ, V14:REQ, V15:REQ, V16:REQ, V17:REQ, V18:REQ, V19:REQ, V20:REQ, V21:REQ, V22:REQ, V23:REQ, V24:REQ, V25:REQ, V26:REQ, V27:REQ, V28:REQ, V29:REQ, V30:REQ, V31:REQ, V32:REQ, V33:REQ, V34:REQ, V35:REQ, V36:REQ, V37:REQ, V38:REQ, V39:REQ, V40:REQ, V41:REQ, V42:REQ, V43:REQ, V44:REQ, V45:REQ, V46:REQ, V47:REQ, V48:REQ, V49:REQ, V50:REQ, V51:REQ, V52:REQ, V53:REQ, V54:REQ, V55:REQ, V56:REQ, V57:REQ, V58:REQ, V59:REQ, V60:REQ, V61:REQ, V62:REQ, V63:REQ, V64:REQ
        mm64fnex64 TEXTEQU <>
        mm64fnex64 CATSTR mm64fnex64, <&functionName&>
        PUBLIC mm64fnex64
        mm64fnex64 CATSTR mm64fnex64, < vectorType>, < { V1, V2, V3, V4, V5, V6, V7, V8, V9, V10, V11, V12, V13, V14, V15, V16, V17, V18, V19, V20, V21, V22, V23, V24, V25, V26, V27, V28, V29, V30, V31, V32, V33, V34, V35, V36, V37, V38, V39, V40, V41, V42, V43, V44, V45, V46, V47, V48, V49, V50, V51, V52, V53, V54, V55, V56, V57, V58, V59, V60, V61, V62, V63, V64 } >
        mm64fnex64
    ENDM
    ENDIF
    
    IFNDEF V32CI
    V32CI MACRO functionName:REQ, vectorType:REQ, V1:REQ
        mm32fnex TEXTEQU <>
        mm32fnex CATSTR mm32fnex, <&functionName&>
        PUBLIC mm32fnex
        mm32fnex CATSTR mm32fnex, < vectorType>,  < { V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1 } >
        mm32fnex
    ENDM
    ENDIF
    
    IFNDEF V32CI32
    V32CI32 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ, V3:REQ, V4:REQ, V5:REQ, V6:REQ, V7:REQ, V8:REQ, V9:REQ, V10:REQ, V11:REQ, V12:REQ, V13:REQ, V14:REQ, V15:REQ, V16:REQ, V17:REQ, V18:REQ, V19:REQ, V20:REQ, V21:REQ, V22:REQ, V23:REQ, V24:REQ, V25:REQ, V26:REQ, V27:REQ, V28:REQ, V29:REQ, V30:REQ, V31:REQ, V32:REQ
        mm32fnex32 TEXTEQU <>
        mm32fnex32 CATSTR mm32fnex32, <&functionName&>
        PUBLIC mm32fnex32
        mm32fnex32 CATSTR mm32fnex32, < vectorType>, < { V1, V2, V3, V4, V5, V6, V7, V8, V9, V10, V11, V12, V13, V14, V15, V16, V17, V18, V19, V20, V21, V22, V23, V24, V25, V26, V27, V28, V29, V30, V31, V32 } >
        mm32fnex32
    ENDM
    ENDIF
    
    IFNDEF V16CI
    V16CI MACRO functionName:REQ, vectorType:REQ, V1:REQ
        mm16fnex TEXTEQU <>
        mm16fnex CATSTR mm16fnex, <&functionName&>
        PUBLIC mm16fnex
        mm16fnex CATSTR mm16fnex, < vectorType>,  < { V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1 } >
        mm16fnex
    ENDM
    ENDIF
    
    IFNDEF V16CI16
    V16CI16 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ, V3:REQ, V4:REQ, V5:REQ, V6:REQ, V7:REQ, V8:REQ, V9:REQ, V10:REQ, V11:REQ, V12:REQ, V13:REQ, V14:REQ, V15:REQ, V16:REQ
        mm16fnex16 TEXTEQU <>
        mm16fnex16 CATSTR mm16fnex16, <&functionName&>
        PUBLIC mm16fnex16
        mm16fnex16 CATSTR mm16fnex16, < vectorType>, < { V1, V2, V3, V4, V5, V6, V7, V8, V9, V10, V11, V12, V13, V14, V15, V16 } >
        mm16fnex16
    ENDM
    ENDIF
    
    IFNDEF V8CI
    V8CI MACRO functionName:REQ, vectorType:REQ, V1:REQ
        mm8fnex TEXTEQU <>
        mm8fnex CATSTR mm8fnex, <&functionName&>
        PUBLIC mm8fnex
        mm8fnex CATSTR mm8fnex, < vectorType>,  < { V1, V1, V1, V1, V1, V1, V1, V1 } >
        mm8fnex
    ENDM
    ENDIF
    
    IFNDEF V8CI8
    V8CI8 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ, V3:REQ, V4:REQ, V5:REQ, V6:REQ, V7:REQ, V8:REQ
        mm8fnex8 TEXTEQU <>
        mm8fnex8 CATSTR mm8fnex8, <&functionName&>
        PUBLIC mm8fnex8
        mm8fnex8 CATSTR mm8fnex8, < vectorType>, < { V1, V2, V3, V4, V5, V6, V7, V8 } >
        mm8fnex8
    ENDM
    ENDIF
    
    IFNDEF V4CI
    V4CI MACRO functionName:REQ, vectorType:REQ, V1:REQ
        mm4fnex TEXTEQU <>
        mm4fnex CATSTR mm4fnex, <&functionName&>
        PUBLIC mm4fnex
        mm4fnex CATSTR mm4fnex, < vectorType>,  < { V1, V1, V1, V1 } >
        mm4fnex
    ENDM
    ENDIF
    
    IFNDEF V4CI4
    V4CI4 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ, V3:REQ, V4:REQ
        mm4fnex4 TEXTEQU <>
        mm4fnex4 CATSTR mm4fnex4, <&functionName&>
        PUBLIC mm4fnex4
        mm4fnex4 CATSTR mm4fnex4, < vectorType>, < { V1, V2, V3, V4 } >
        mm4fnex4
    ENDM
    ENDIF
    
    IFNDEF V2CI
    V2CI MACRO functionName:REQ, vectorType:REQ, V1:REQ
        mm2fnex TEXTEQU <>
        mm2fnex CATSTR mm2fnex, <&functionName&>
        PUBLIC mm2fnex
        mm2fnex CATSTR mm2fnex, < vectorType>,  < { V1, V1 } >
        mm2fnex
    ENDM
    ENDIF
    
    IFNDEF V2CI2
    V2CI2 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ
        mm2fnex2 TEXTEQU <>
        mm2fnex2 CATSTR mm2fnex2, <&functionName&>
        PUBLIC mm2fnex2
        mm2fnex2 CATSTR mm2fnex2, < vectorType>, < { V1, V2 } >
        mm2fnex2
    ENDM
    ENDIF
    
    IFNDEF VV64CI
    VV64CI MACRO functionName:REQ, vectorType:REQ, V1:REQ
        vmm64fnex TEXTEQU <>
        vmm64fnex CATSTR vmm64fnex, <&functionName&>
        PUBLIC vmm64fnex
        vmm64fnex CATSTR vmm64fnex, < vectorType>,  < { <V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1> } >
        vmm64fnex
    ENDM
    ENDIF
    
    IFNDEF VV64CI64
    VV64CI64 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ, V3:REQ, V4:REQ, V5:REQ, V6:REQ, V7:REQ, V8:REQ, V9:REQ, V10:REQ, V11:REQ, V12:REQ, V13:REQ, V14:REQ, V15:REQ, V16:REQ, V17:REQ, V18:REQ, V19:REQ, V20:REQ, V21:REQ, V22:REQ, V23:REQ, V24:REQ, V25:REQ, V26:REQ, V27:REQ, V28:REQ, V29:REQ, V30:REQ, V31:REQ, V32:REQ, V33:REQ, V34:REQ, V35:REQ, V36:REQ, V37:REQ, V38:REQ, V39:REQ, V40:REQ, V41:REQ, V42:REQ, V43:REQ, V44:REQ, V45:REQ, V46:REQ, V47:REQ, V48:REQ, V49:REQ, V50:REQ, V51:REQ, V52:REQ, V53:REQ, V54:REQ, V55:REQ, V56:REQ, V57:REQ, V58:REQ, V59:REQ, V60:REQ, V61:REQ, V62:REQ, V63:REQ, V64:REQ
        vmm64fnex64 TEXTEQU <>
        vmm64fnex64 CATSTR vmm64fnex64, <&functionName&>
        PUBLIC vmm64fnex64
        vmm64fnex64 CATSTR vmm64fnex64, < vectorType>, < { <V1, V2, V3, V4, V5, V6, V7, V8, V9, V10, V11, V12, V13, V14, V15, V16, V17, V18, V19, V20, V21, V22, V23, V24, V25, V26, V27, V28, V29, V30, V31, V32, V33, V34, V35, V36, V37, V38, V39, V40, V41, V42, V43, V44, V45, V46, V47, V48, V49, V50, V51, V52, V53, V54, V55, V56, V57, V58, V59, V60, V61, V62, V63, V64> } >
        vmm64fnex64
    ENDM
    ENDIF
    
    IFNDEF VV32CI
    VV32CI MACRO functionName:REQ, vectorType:REQ, V1:REQ
        vmm32fnex TEXTEQU <>
        vmm32fnex CATSTR vmm32fnex, <&functionName&>
        PUBLIC vmm32fnex
        vmm32fnex CATSTR vmm32fnex, < vectorType>,  < { <V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1> } >
        vmm32fnex
    ENDM
    ENDIF
    
    IFNDEF VV32CI32
    VV32CI32 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ, V3:REQ, V4:REQ, V5:REQ, V6:REQ, V7:REQ, V8:REQ, V9:REQ, V10:REQ, V11:REQ, V12:REQ, V13:REQ, V14:REQ, V15:REQ, V16:REQ, V17:REQ, V18:REQ, V19:REQ, V20:REQ, V21:REQ, V22:REQ, V23:REQ, V24:REQ, V25:REQ, V26:REQ, V27:REQ, V28:REQ, V29:REQ, V30:REQ, V31:REQ, V32:REQ
        vmm32fnex32 TEXTEQU <>
        vmm32fnex32 CATSTR vmm32fnex32, <&functionName&>
        PUBLIC vmm32fnex32
        vmm32fnex32 CATSTR vmm32fnex32, < vectorType>, < { <V1, V2, V3, V4, V5, V6, V7, V8, V9, V10, V11, V12, V13, V14, V15, V16, V17, V18, V19, V20, V21, V22, V23, V24, V25, V26, V27, V28, V29, V30, V31, V32> } >
        vmm32fnex32
    ENDM
    ENDIF
    
    IFNDEF VV16CI
    VV16CI MACRO functionName:REQ, vectorType:REQ, V1:REQ
        vmm16fnex TEXTEQU <>
        vmm16fnex CATSTR vmm16fnex, <&functionName&>
        PUBLIC vmm16fnex
        vmm16fnex CATSTR vmm16fnex, < vectorType>,  < { <V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1> } >
        vmm16fnex
    ENDM
    ENDIF
    
    IFNDEF VV16CI16
    VV16CI16 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ, V3:REQ, V4:REQ, V5:REQ, V6:REQ, V7:REQ, V8:REQ, V9:REQ, V10:REQ, V11:REQ, V12:REQ, V13:REQ, V14:REQ, V15:REQ, V16:REQ
        vmm16fnex16 TEXTEQU <>
        vmm16fnex16 CATSTR vmm16fnex16, <&functionName&>
        PUBLIC vmm16fnex16
        vmm16fnex16 CATSTR vmm16fnex16, < vectorType>, < { <V1, V2, V3, V4, V5, V6, V7, V8, V9, V10, V11, V12, V13, V14, V15, V16> } >
        vmm16fnex16
    ENDM
    ENDIF
    
    IFNDEF VV8CI
    VV8CI MACRO functionName:REQ, vectorType:REQ, V1:REQ
        vmm8fnex TEXTEQU <>
        vmm8fnex CATSTR vmm8fnex, <&functionName&>
        PUBLIC vmm8fnex
        vmm8fnex CATSTR vmm8fnex, < vectorType>,  < { <V1, V1, V1, V1, V1, V1, V1, V1> } >
        vmm8fnex
    ENDM
    ENDIF
    
    IFNDEF VV8CI8
    VV8CI8 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ, V3:REQ, V4:REQ, V5:REQ, V6:REQ, V7:REQ, V8:REQ
        vmm8fnex8 TEXTEQU <>
        vmm8fnex8 CATSTR vmm8fnex8, <&functionName&>
        PUBLIC vmm8fnex8
        vmm8fnex8 CATSTR vmm8fnex8, < vectorType>, < { <V1, V2, V3, V4, V5, V6, V7, V8> } >
        vmm8fnex8
    ENDM
    ENDIF
    
    IFNDEF VV4CI
    VV4CI MACRO functionName:REQ, vectorType:REQ, V1:REQ
        vmm4fnex TEXTEQU <>
        vmm4fnex CATSTR vmm4fnex, <&functionName&>
        PUBLIC vmm4fnex
        vmm4fnex CATSTR vmm4fnex, < vectorType>,  < { <V1, V1, V1, V1> } >
        vmm4fnex
    ENDM
    ENDIF
    
    IFNDEF VV4CI4
    VV4CI4 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ, V3:REQ, V4:REQ
        vmm4fnex4 TEXTEQU <>
        vmm4fnex4 CATSTR vmm4fnex4, <&functionName&>
        PUBLIC vmm4fnex4
        vmm4fnex4 CATSTR vmm4fnex4, < vectorType>, < { <V1, V2, V3, V4> } >
        vmm4fnex4
    ENDM
    ENDIF
    
    IFNDEF VV2CI
    VV2CI MACRO functionName:REQ, vectorType:REQ, V1:REQ
        vmm2fnex TEXTEQU <>
        vmm2fnex CATSTR vmm2fnex, <&functionName&>
        PUBLIC vmm2fnex
        vmm2fnex CATSTR vmm2fnex, < vectorType>,  < { <V1, V1> } >
        vmm2fnex
    ENDM
    ENDIF
    
    IFNDEF VV2CI2
    VV2CI2 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ
        vmm2fnex2 TEXTEQU <>
        vmm2fnex2 CATSTR vmm2fnex2, <&functionName&>
        PUBLIC vmm2fnex2
        vmm2fnex2 CATSTR vmm2fnex2, < vectorType>, < { <V1, V2> } >
        vmm2fnex2
    ENDM
    ENDIF
    
    IFNDEF V1CI
    V1CI MACRO functionName:REQ, vectorType:REQ, V1:REQ
        mm1fnex TEXTEQU <>
        mm1fnex CATSTR mm1fnex, <&functionName&>
        PUBLIC mm1fnex
        mm1fnex CATSTR mm1fnex, < vectorType>,  < V1 >
        mm1fnex
    ENDM
    ENDIF

    IFNDEF NOTMASK128
    NOTMASK128 MACRO reg:REQ, field:REQ
        IFNDEF GMASK
            .DATA
            GMASK OWORD 0
        ENDIF
        IFNDEF NOTMASK
            .DATA
            NOTMASK OWORD (-1)
        ENDIF
        .CODE
        IF @Arch EQ ARCH_AVX
            VMOVUPS reg, MASK field
            VPXOR reg, reg, NOTMASK
        ELSE
            MOVUPS reg, MASK field
            PXOR reg, NOTMASK
        ENDIF
    ENDM
    ENDIF ;NOTMASK128
    
    IFNDEF GETMASK128
    GETMASK128 MACRO reg:REQ, field:REQ
        IFNDEF GMASK
            .DATA
            GMASK OWORD 0
        ENDIF
        .CODE
        IF @Arch EQ ARCH_AVX
            VMOVUPS reg, MASK field
        ELSE
            MOVUPS reg, MASK field
        ENDIF
    ENDM
    ENDIF ;GETMASK128
    
    IFDEF __X64__
    IFNDEF REGS15STORAGE
    REGS15STORAGE MACRO
    IFNDEF RRAX
        .DATA?
        RRP0 SIZE_T ?
        RRP1 SIZE_T ?
        RRP2 SIZE_T ?
        RRP3 SIZE_T ?
        RRP4 SIZE_T ?
        RRP5 SIZE_T ?
        RRP6 SIZE_T ?
        RRP7 SIZE_T ?
        RRP8 SIZE_T ?
        RRP9 SIZE_T ?
        RRP10 SIZE_T ?
        RRP11 SIZE_T ?
        RRP12 SIZE_T ?
        RRP13 SIZE_T ?
        RRP14 SIZE_T ?
        RRP15 SIZE_T ?
        RRAX SIZE_T ?
        RRCX SIZE_T ?
        RRDX SIZE_T ?
        RRBX SIZE_T ?
        RRDI SIZE_T ?
        RRSI SIZE_T ?
        RRBP SIZE_T ?
        RRSP SIZE_T ?
        RR8  SIZE_T ?
        RR9  SIZE_T ?
        RR10 SIZE_T ?
        RR11 SIZE_T ?
        RR12 SIZE_T ?
        RR13 SIZE_T ?
        RR14 SIZE_T ?
        RR15 SIZE_T ?
        RXMM0 OWORD ?
        RXMM1 OWORD ?
        RXMM2 OWORD ?
        RXMM3 OWORD ?
        RXMM4 OWORD ?
        RXMM5 OWORD ?
        RXMM6 OWORD ?
        RXMM7 OWORD ?
        IF @Arch EQ ARCH_AVX
        RYMM0 OWORD ?
        RYMM1 OWORD ?
        RYMM2 OWORD ?
        RYMM3 OWORD ?
        RYMM4 OWORD ?
        RYMM5 OWORD ?
        RYMM6 OWORD ?
        RYMM7 OWORD ?
        RZMM0 OWORD ?
        RZMM1 OWORD ?
        RZMM2 OWORD ?
        RZMM3 OWORD ?
        RZMM4 OWORD ?
        RZMM5 OWORD ?
        RZMM6 OWORD ?
        RZMM7 OWORD ?
        ENDIF
    ENDIF
    .CODE
    ENDM
    ENDIF ;REGS15STORAGE
    ENDIF ;__X64__
    
    IFNDEF MOV64
    MOV64 MACRO dst:REQ, imm:REQ
        MOV DWORD PTR dst, LOW32(imm)
        MOV DWORD PTR dst + 4, HIGH32(imm)
    ENDM
    ENDIF ;MOV64
    
    IFNDEF MOV128
    MOV128 MACRO dst:REQ, immLo:REQ,immHi:REQ
        MOV64 dst, immHi
        MOV64 dst + 8, immLo
    ENDM
    ENDIF ;MOV128
    
    IFNDEF MOVXMMR128
    MOVXMMR128 MACRO dst:REQ, immLo:REQ,immHi:REQ
        LOCAL savexmm
        .DATA?
        savexmm OWORD ?
        .CODE
        MOV64 savexmm, immHi
        MOV64 savexmm + 8, immLo
        VMOVUPS dst,savexmm
    ENDM
    ENDIF ;MOVXMMR128
    
    IFNDEF SLXMMR
    SLXMMR MACRO xmm128:REQ,cnt:REQ
    IFDEF __X64__
        LOCAL mmr,saverax,savercx,saversi
        .DATA?
        saverax QWORD ?
        savercx QWORD ?
        saversi QWORD ?
        mmr OWORD ?
        .CODE
        MOV saverax,RAX
        MOV savercx,RCX
        MOV saversi,RSI
        MOV ECX, cnt
        AND ECX,7fh
        VMOVUPS mmr, xmm128
        LEA  RSI,mmr
        .IF (CL >=  0x40)
        MOV RAX, QWORD PTR[RSI+8]
        MOV QWORD PTR[RSI],RAX
        SUB ECX, 64
        SHR QWORD PTR[RSI], CL
        XOR EAX,EAX
        MOV QWORD PTR[RSI+8],RAX
        .ELSE
        MOV RAX,QWORD PTR[RSI+8]
        SHR QWORD PTR[RSI],CL
        SHR QWORD PTR[RSI+8],CL
        NEG CL
        SHL RAX, CL
        OR QWORD PTR[RSI],RAX
        .ENDIF
        MOV RAX,saverax
        MOV RCX,savercx
        MOV RSI,saversi
        VMOVUPS xmm128,mmr
    ELSE
        LOCAL mmr,savedLo,savedxmm1,savedxmm0
        .DATA?
        savedLo  QWORD ?
        mmr OWORD ?
        savedxmm1 OWORD ?
        savedxmm0 OWORD ?
        .CODE
        PUSH EAX
        PUSH ECX
        PUSH ESI
        MOVUPS savedxmm1,XMM1
        MOVUPS savedxmm0,XMM0
        MOVUPS mmr,XMM0
        MOV ECX,cnt
        AND ECX,7fh
        LEA EAX,mmr
        MOVQ XMM0,[EAX+8]
        .IF (ECX >=  0x40)
        SUB ECX,64
        MOVD XMM1,ECX
        PSRLQ XMM0,XMM1
        MOVQ [EAX],XMM0
        PXOR XMM0,XMM0
        MOVQ [EAX+8],XMM0
        .ELSE
        MOVQ savedLo,XMM0
        MOVD XMM1,ECX
        PSRLQ	XMM0, XMM1
        MOVQ [EAX+8],XMM0
        MOVQ XMM0,[EAX]
        PSRLQ	XMM0, XMM1
        MOVQ [EAX],XMM0
        NEG ECX
        AND ECX,7fh
        SUB ECX,64
        MOVD XMM1,ECX
        MOVQ XMM0,savedLo
        PSLLQ XMM0,XMM1
        MOVQ XMM1,[EAX]
        POR XMM0,XMM1
        MOVQ [EAX],XMM0
        .ENDIF
        MOVUPS XMM0,mmr
        MOVUPS XMM1,savedxmm1
        IFDIFI <XMM0>,<xmm128>
        MOVUPS XMM0,savedxmm0
        ENDIF
        POP ESI
        POP ECX
        POP EAX
    ENDIF ;__X64__
    ENDM
    ENDIF ;SLXMMR
    
    IFNDEF SHIFTLEFT128
    SHIFTLEFT128 MACRO mmr:REQ,cnt:REQ
    IFDEF __X64__
        LOCAL saverax,savercx,saversi
        .DATA?
        saverax QWORD ?
        savercx QWORD ?
        saversi QWORD ?
        .CODE
        MOV saverax,RAX
        MOV savercx,RCX
        MOV saversi,RSI
        MOV  RSI,mmr
        MOV ECX, cnt
        AND ECX,7fh
        .IF (CL >=  0x40)
        MOV RAX, QWORD PTR[RSI+8]
        MOV QWORD PTR[RSI],RAX
        SUB ECX, 64
        SHR QWORD PTR[RSI], CL
        XOR EAX,EAX
        MOV QWORD PTR[RSI+8],RAX
        .ELSE
        MOV RAX,QWORD PTR[RSI+8]
        SHR QWORD PTR[RSI],CL
        SHR QWORD PTR[RSI+8],CL
        NEG CL
        SHL RAX, CL
        OR QWORD PTR[RSI],RAX
        .ENDIF
        MOV RAX,saverax
        MOV RCX,savercx
        MOV RCX,saversi
    ELSE
        LOCAL savedLo,savedxmm1,savedxmm0
        .DATA?
        savedLo QWORD ?
        savedxmm1 OWORD ?
        savedxmm0 OWORD ?
        .CODE
        PUSH EAX
        PUSH ECX
        MOVUPS savedxmm1,XMM1
        MOVUPS savedxmm0,XMM0
        MOV ECX,cnt
        AND ECX,7fh
        MOV EAX,mmr
        MOVQ XMM0,[EAX+8]
        .IF (ECX >=  0x40)
        SUB ECX,64
        MOVD XMM1,ECX
        PSRLQ XMM0,XMM1
        MOVQ [EAX],XMM0
        PXOR XMM0,XMM0
        MOVQ [EAX+8],XMM0
        .ELSE
        MOVQ savedLo,XMM0
        MOVD XMM1,ECX
        PSRLQ XMM0, XMM1
        MOVQ [EAX+8],XMM0
        MOVQ XMM0,[EAX]
        PSRLQ XMM0, XMM1
        MOVQ [EAX],XMM0
        NEG ECX
        AND ECX,7fh
        SUB ECX,64
        MOVD XMM1,ECX
        MOVQ XMM0,savedLo
        PSLLQ XMM0,XMM1
        MOVQ XMM1,[EAX]
        POR XMM0,XMM1
        MOVQ [EAX],XMM0
        .ENDIF
        MOVUPS XMM1,savedxmm1
        MOVUPS XMM0,savedxmm0
        POP ECX
        POP EAX
    ENDIF ;__X64__
    ENDM
    ENDIF ;SHIFTLEFT128
    
    IFNDEF SRXMMR
    SRXMMR MACRO xmm128:REQ,cnt:REQ
    IFDEF __X64__
        LOCAL mmr,saverax,savercx,saversi
        .DATA?
        saverax QWORD ?
        savercx QWORD ?
        saversi QWORD ?
        mmr OWORD ?
        .CODE
        MOV saverax,RAX
        MOV savercx,RCX
        MOV saversi,RSI
        MOV ECX, cnt
        AND ECX,7fh
        VMOVUPS mmr, xmm128
        LEA  RSI,mmr
        .IF (CL >=  0x40)
        MOV RAX, QWORD PTR[RSI]
        MOV QWORD PTR[RSI+8],RAX
        SUB ECX, 64
        SHL QWORD PTR[RSI+8], CL
        XOR EAX,EAX
        MOV QWORD PTR[RSI],RAX
        .ELSE
        MOV RAX,QWORD PTR[RSI]
        SHL QWORD PTR[RSI],CL
        SHL QWORD PTR[RSI+8],CL
        NEG CL
        SHR RAX, CL
        OR QWORD PTR[RSI+8],RAX
        .ENDIF
        MOV RAX,saverax
        MOV RCX,savercx
        MOV RSI,saversi
        VMOVUPS xmm128,mmr
    ELSE
        LOCAL mmr,savedLo,savedxmm1,savedxmm0
        .DATA?
        savedLo  QWORD ?
        mmr OWORD ?
        savedxmm1 OWORD ?
        savedxmm0 OWORD ?
        .CODE
        PUSH EAX
        PUSH ECX
        PUSH ESI
        MOVUPS savedxmm1,XMM1
        MOVUPS savedxmm0,XMM0
        MOVUPS mmr,XMM0
        MOV ECX,cnt
        AND ECX,7fh
        LEA EAX,mmr
        MOVQ XMM0,[EAX]
        .IF (ECX >=  0x40)
        SUB ECX,64
        MOVD XMM1,ECX
        PSLLQ XMM0,XMM1
        MOVQ [EAX+8],XMM0
        PXOR XMM0,XMM0
        MOVQ [EAX],XMM0
        .ELSE
        MOVQ savedLo,XMM0
        MOVD XMM1,ECX
        PSLLQ XMM0, XMM1
        MOVQ [EAX],XMM0
        MOVQ XMM0,[EAX+8]
        PSLLQ	XMM0, XMM1
        MOVQ [EAX+8],XMM0
        NEG ECX
        AND ECX,7fh
        SUB ECX,64
        MOVD XMM1,ECX
        MOVQ XMM0,savedLo
        PSRLQ XMM0,XMM1
        MOVQ XMM1,[EAX+8]
        POR XMM0,XMM1
        MOVQ [EAX+8],XMM0
        .ENDIF
        MOVUPS XMM0,mmr
        MOVUPS XMM1,savedxmm1
        IFDIFI <XMM0>,<xmm128>
        MOVUPS XMM0,savedxmm0
        ENDIF
        POP ESI
        POP ECX
        POP EAX
    ENDIF ;__X64__
    ENDM
    ENDIF ;SRXMMR
    
    IFNDEF SHIFTRIGHT128
    SHIFTRIGHT128 MACRO mmr:REQ,cnt:REQ
    IFDEF __X64__
        LOCAL saverax,savercx,saversi
        .DATA?
        saverax QWORD ?
        savercx QWORD ?
        saversi QWORD ?
        .CODE
        MOV saverax,RAX
        MOV savercx,RCX
        MOV saversi,RSI
        MOV RSI,mmr
        MOV ECX, cnt
        AND ECX,7fh
        .IF (CL >=  0x40)
        MOV RAX, QWORD PTR[RSI]
        MOV QWORD PTR[RSI+8],RAX
        SUB ECX, 64
        SHL QWORD PTR[RSI+8], CL
        XOR EAX,EAX
        MOV QWORD PTR[RSI],RAX
        .ELSE
        MOV RAX,QWORD PTR[RSI]
        SHL QWORD PTR[RSI],CL
        SHL QWORD PTR[RSI+8],CL
        NEG CL
        SHR RAX, CL
        OR QWORD PTR[RSI+8],RAX
        .ENDIF
        MOV RAX,saverax
        MOV RCX,savercx
        MOV RSI,saversi
    ELSE
        LOCAL savedHi,savedxmm1,savedxmm0
        .DATA?
        savedHi   QWORD ?
        savedxmm1 OWORD ?
        savedxmm0 OWORD ?
        .CODE
        PUSH EAX
        PUSH ECX
        MOVUPS savedxmm1,XMM1
        MOVUPS savedxmm0,XMM0
        MOV ECX,cnt
        AND ECX,7fh
        MOV EAX,mmr
        MOVQ XMM0,[EAX]
        .IF (ECX >=  0x40)
        SUB ECX,64
        MOVD XMM1,ECX
        PSLLQ XMM0,XMM1
        MOVQ [EAX+8],XMM0
        PXOR XMM0,XMM0
        MOVQ [EAX],XMM0
        .ELSE
        MOVQ savedHi,XMM0
        MOVD XMM1,ECX
        PSLLQ	XMM0, XMM1
        MOVQ [EAX],XMM0
        MOVQ XMM0,[EAX+8]
        PSLLQ	XMM0, XMM1
        MOVQ [EAX+8],XMM0
        NEG ECX
        AND ECX,7fh
        SUB ECX,64
        MOVD XMM1,ECX
        MOVQ XMM0,savedHi
        PSRLQ XMM0,XMM1
        MOVQ XMM1,[EAX+8]
        POR XMM0,XMM1
        MOVQ [EAX+8],XMM0
        .ENDIF
        MOVUPS XMM1,savedxmm1
        MOVUPS XMM0,savedxmm0
        POP ECX
        POP EAX
    ENDIF ;__X64__
    ENDM
    ENDIF ;SHIFTRIGHT128
    
    IFNDEF FP4
    FP4 MACRO value:REQ
        LOCAL vname
        .DATA
        ALIGN 4
        vname REAL4 value
        .CODE
        EXITM <vname>
    ENDM
    ENDIF ;FP4
    
    IFNDEF FP8
    FP8 MACRO value:REQ
        LOCAL vname
        .DATA
        ALIGN 8
        vname REAL8 value
        .CODE
        EXITM <vname>
    ENDM
    ENDIF ;FP8
    
    IFNDEF FP10
    FP10 MACRO value:REQ
        LOCAL vname
        .DATA
        ALIGN 8
        vname REAL10 value
        .CODE
        EXITM <vname>
    ENDM
    ENDIF ;FP10
    
    IFNDEF LOADSS
    LOADSS MACRO reg, val
        LOCAL savedeax
        .DATA?
        savedeax ISIZE_T ?
        .CODE
        MOV savedeax, RRET()
    IF @Arch EQ ARCH_AVX
        MOV EAX, val
        VMOVD reg, EAX
    ELSE
        MOV EAX, val
        MOVD reg, EAX
    ENDIF
        MOV RRET(), savedeax
    ENDM
    ENDIF ;LOADSS
    
    IFNDEF LOAD1PS
    LOAD1PS MACRO reg, val
        LOCAL savedeax
        .DATA?
        savedeax ISIZE_T ?
        .CODE
        MOV savedeax, RRET()
    IF @Arch EQ ARCH_AVX
        MOV EAX, val
        VMOVD reg, EAX
        VPSHUFD reg, reg, 0
    ELSE
        MOV EAX, val
        MOVD reg, EAX
        PSHUFD reg, reg, 0
    ENDIF
        MOV RRET(), savedeax
    ENDM
    ENDIF ;LOAD1PS
    
    IFNDEF LOADPS
    LOADPS MACRO reg, val3, val2, val1, val0
        LOCAL savedeax
        IFDIFI <reg>, <XMM3>
        LOCAL savedxmm3
        ENDIF
        IFDIFI <reg>, <XMM2>
        LOCAL savedxmm2
        ENDIF
        IFDIFI <reg>, <XMM1>
        LOCAL savedxmm1
        ENDIF
        IFDIFI <reg>, <XMM0>
        LOCAL savedxmm0
        ENDIF
        .DATA?
        savedeax ISIZE_T ?
        IFDIFI <reg>, <XMM3>
        savedxmm3 OWORD ?
        ENDIF
        IFDIFI <reg>, <XMM2>
        savedxmm2 OWORD ?
        ENDIF
        IFDIFI <reg>, <XMM1>
        savedxmm1 OWORD ?
        ENDIF
        IFDIFI <reg>, <XMM0>
        savedxmm0 OWORD ?
        ENDIF
        .CODE
        MOV savedeax, RRET()
    IF @Arch EQ ARCH_AVX
        IFDIFI <reg>, <XMM3>
        VMOVDQU savedxmm3, XMM3
        ENDIF
        IFDIFI <reg>, <XMM2>
        VMOVDQU savedxmm2, XMM2
        ENDIF
        IFDIFI <reg>, <XMM1>
        VMOVDQU savedxmm1, XMM1
        ENDIF
        IFDIFI <reg>, <XMM0>
        VMOVDQU savedxmm0, XMM0
        ENDIF
        MOV               EAX,           val3
        VMOVD            XMM3,           EAX
        MOV               EAX,           val2
        VMOVD            XMM2,           EAX
        MOV               EAX,           val1
        VMOVD            XMM1,           EAX
        MOV               EAX,           val0
        VMOVD            XMM0,           EAX
        VPUNPCKLDQ       XMM2,      XMM2,           XMM3        ;;shuffle4(3,2,3,2)
        VPUNPCKLDQ       XMM0,      XMM0,           XMM1        ;;shuffle4(1,0,1,0)
        VPUNPCKLQDQ      XMM0,      XMM0,           XMM2        ;;shuffle2(1,0) (1:3,2|0:1,0)
        IFDIFI <reg>, <XMM3>
        VMOVDQU XMM3, savedxmm3
        ENDIF
        IFDIFI <reg>, <XMM2>
        VMOVDQU XMM2, savedxmm2
        ENDIF
        IFDIFI <reg>, <XMM1>
        VMOVDQU XMM1, savedxmm1
        ENDIF
        IFDIFI <reg>, <XMM0>
        VMOVDQU            reg,           XMM0
        VMOVDQU XMM0, savedxmm0
        ENDIF
    ELSE ;;ARCH_AVX
        IFDIFI <reg>, <XMM3>
        MOVDQU savedxmm3, XMM3
        ENDIF
        IFDIFI <reg>, <XMM2>
        MOVDQU savedxmm2, XMM2
        ENDIF
        IFDIFI <reg>, <XMM1>
        MOVDQU savedxmm1, XMM1
        ENDIF
        IFDIFI <reg>, <XMM0>
        MOVDQU savedxmm0, XMM0
        ENDIF
        MOV              EAX,           val3
        MOVD            XMM3,           EAX
        MOV              EAX,           val2
        MOVD            XMM2,           EAX
        MOV              EAX,           val1
        MOVD            XMM1,           EAX
        MOV              EAX,           val0
        MOVD            XMM0,           EAX
        PUNPCKLDQ       XMM2,           XMM3        ;;shuffle4(3,2,3,2)
        PUNPCKLDQ       XMM0,           XMM1        ;;shuffle4(1,0,1,0)
        PUNPCKLQDQ      XMM0,           XMM2        ;;shuffle2(1,0) (1:3,2|0:1,0)
        IFDIFI <reg>, <XMM3>
        MOVDQU XMM3, savedxmm3
        ENDIF
        IFDIFI <reg>, <XMM2>
        MOVDQU XMM2, savedxmm2
        ENDIF
        IFDIFI <reg>, <XMM1>
        MOVDQU XMM1, savedxmm1
        ENDIF
        IFDIFI <reg>, <XMM0>
        MOVDQU           reg,           XMM0
        MOVDQU XMM0, savedxmm0
        ENDIF
    ENDIF ;;ARCH_SSE
        MOV RRET(), savedeax
    ENDM
    ENDIF ;LOADPS
    
    IFDEF __X64__
    IFNDEF LOADSD
    LOADSD MACRO reg, val
        LOCAL savedeax
        .DATA?
        savedeax ISIZE_T ?
        .CODE
        MOV savedeax, RRET()
    IF @Arch EQ ARCH_AVX
        MOV RAX, REAL8 PTR val
        VMOVQ reg, RAX
    ELSE
        MOV RAX, REAL8 PTR val
        MOVQ reg, RAX
    ENDIF
        MOV RRET(), savedeax
    ENDM
    ENDIF ;LOADSD
    
    IFNDEF LOAD1PD
    LOAD1PD MACRO reg, val
        LOCAL savedeax
        .DATA?
        savedeax ISIZE_T ?
        .CODE
        MOV savedeax, RRET()
    IF @Arch EQ ARCH_AVX
        MOV RAX, val
        VMOVQ reg, RAX
        VPUNPCKLQDQ      reg,      reg,           reg        ;;shuffle2(0,0)
    ELSE
        MOV RAX, val
        MOVQ reg, RAX
        PUNPCKLQDQ      reg,           reg        ;;shuffle2(0,0)
    ENDIF
        MOV RRET(), savedeax
    ENDM
    ENDIF ;LOAD1PD
   
    IFNDEF LOADPD
    LOADPD MACRO reg, val1, val0
        LOCAL savedeax
        IFDIFI <reg>, <XMM1>
        LOCAL savedxmm1
        ENDIF
        IFDIFI <reg>, <XMM0>
        LOCAL savedxmm0
        ENDIF
        .DATA?
        savedeax ISIZE_T ?
        IFDIFI <reg>, <XMM1>
        savedxmm1 OWORD ?
        ENDIF
        IFDIFI <reg>, <XMM0>
        savedxmm0 OWORD ?
        ENDIF
        .CODE
        MOV savedeax, RRET()
    IF @Arch EQ ARCH_AVX
        IFDIFI <reg>, <XMM1>
        VMOVDQU savedxmm1, XMM1
        ENDIF
        IFDIFI <reg>, <XMM0>
        VMOVDQU savedxmm0, XMM0
        ENDIF
        MOV               RAX,           val1
        VMOVQ            XMM1,           RAX
        MOV               RAX,           val0
        VMOVQ            XMM0,           RAX
        VPUNPCKLQDQ      XMM0,      XMM0,           XMM1        ;;shuffle2(1,0)
        IFDIFI <reg>, <XMM1>
        VMOVDQU XMM1, savedxmm1
        ENDIF
        IFDIFI <reg>, <XMM0>
        VMOVDQU            reg,           XMM0
        VMOVDQU XMM0, savedxmm0
        ENDIF
    ELSE ;;ARCH_AVX
        IFDIFI <reg>, <XMM1>
        MOVDQU savedxmm1, XMM1
        ENDIF
        IFDIFI <reg>, <XMM0>
        MOVDQU savedxmm0, XMM0
        ENDIF
        MOV              RAX,           val1
        MOVQ            XMM1,           RAX
        MOV              RAX,           val0
        MOVQ            XMM0,           RAX
        PUNPCKLQDQ      XMM0,           XMM1            ;;shuffle2(1,0)
        IFDIFI <reg>, <XMM1>
        MOVDQU XMM1, savedxmm1
        ENDIF
        IFDIFI <reg>, <XMM0>
        MOVDQU           reg,           XMM0
        MOVDQU XMM0, savedxmm0
        ENDIF
    ENDIF ;;ARCH_SSE
        MOV RRET(), savedeax
    ENDM
    ENDIF ;LOADPD
    ENDIF ;__X64__
    
    IFNDEF ALIGNADDR
    ALIGNADDR MACRO reg, number
        ADD reg, number-1
        AND reg, -number,
    ENDM
    ENDIF ;ALIGNADDR
    
    IFNDEF CSTR
    CSTR MACRO Text:VARARG
        LOCAL szText
        .DATA
        szText DB Text,0
        ALIGN SIZE_T_SIZE
        .CODE
          EXITM <ADDR szText>
    ENDM
    ENDIF ;CSTR
    
    IFNDEF WSTR
    WSTR MACRO Text:VARARG
        LOCAL szText
        .DATA
        szText DW Text,0
        ALIGN SIZE_T_SIZE
        .CODE
          EXITM <ADDR szText>
    ENDM
    ENDIF ;WSTR
    
    IFNDEF CHR$
    CHR$ MACRO Text:VARARG
        LOCAL szText
        .DATA
        IFDEF UNICODE
          szText DW Text,0
        ELSE
          szText DB Text,0
        ENDIF
        ALIGN SIZE_T_SIZE
        .CODE
          EXITM <ADDR szText>
    ENDM
    ENDIF ;CHR$
    
    IFNDEF TCHR
    TCHR TEXTEQU <CHR$>
    ENDIF ;TCHR
    
    IFNDEF REPARG
    REPARG MACRO arg
        LOCAL nustr,quot
        quot SUBSTR <arg>, 1, 1
        IFIDN quot, <\">
          .DATA
          IFDEF UNICODE
            nustr DW arg, 0
          ELSE
            nustr DB arg, 0
          ENDIF
          ALIGN SIZE_T_SIZE
          .CODE
            EXITM <ADDR nustr>
        ELSE
          EXITM <ADDR arg>
        ENDIF
    ENDM
    ENDIF ;REPARG
    
    IFNDEF REPARGV
    REPARGV MACRO arg
        LOCAL nustr,quot
        quot SUBSTR <arg>, 1, 1
        IFIDN quot, <\">
          .DATA
          IFDEF UNICODE
            nustr DW arg, 0
          ELSE
            nustr DB arg, 0
          ENDIF
          ALIGN SIZE_T_SIZE
          .CODE
            MOV RRET(), ADDR nustr
          EXITM <RRET()>
        ELSE
          MOV RRET(), arg
          EXITM <RRET()>
        ENDIF
    ENDM
    ENDIF ;REPARGV

    IFNDEF EXPAND_PREFIX
    EXPAND_PREFIX MACRO txtitm
        LOCAL prefix1,wrd,nu,varname
        prefix1 SUBSTR <txtitm>, 1, 1
        IFIDN prefix1, <&>
          nu SUBSTR <txtitm>, 2
          wrd CATSTR <ADDR >, nu
          EXITM <wrd>
        ENDIF
        IFIDN prefix1, <*>
          nu SUBSTR <txtitm>, 2
          .DATA?
          varname ISIZE_T ?
          .CODE
          MOV RRET(), nu
          MOV RRET(), [RRET()]
          MOV varname, RRET()
          EXITM <varname>
        ENDIF
        EXITM <txtitm>
    ENDM
    ENDIF ;EXPAND_PREFIX
    
    IFNDEF RV
    RV MACRO FuncName:REQ, args:VARARG
        arg TEXTEQU <INVOKE FuncName>
        FOR var, <args>
        arg CATSTR arg, <, EXPAND_PREFIX(REPARG(var))>
        ENDM
        arg
        EXITM <RRET()>
    ENDM
    ENDIF ;RV
    
    IFNDEF TSTARG
    TSTARG MACRO arg
      LOCAL quot
      quot SUBSTR <arg>,1,1
      IFIDN quot,<\">
        .ERR <"In TSTARG macro, argument = arg, valid memory buffer address required">
        EXITM <arg>
      ELSE
        EXITM <arg>
      ENDIF
    ENDM
    ENDIF ;TSTARG
    
    IFNDEF NUM2STR
    NUM2STR MACRO arg
      EXITM % arg
    ENDM
    ENDIF ;NUM2STR
    
    IFNDEF ARGCOUNT
    ARGCOUNT MACRO args:VARARG
      LOCAL cnt
      cnt = 0
      FOR item, <args>
        cnt = cnt + 1
      ENDM
      EXITM %cnt
    ENDM
    ENDIF ;ARGCOUNT
    
    IFNDEF GETARG
    GETARG MACRO num:REQ,args:VARARG
      LOCAL cnt, txt
      cnt = 0
      FOR arg, <args>
        cnt = cnt + 1
        IF cnt EQ num
          txt TEXTEQU <arg>
          EXITM
        ENDIF
      ENDM
      IFNDEF txt
        txt TEXTEQU <-1>
      ENDIF
      EXITM txt
    ENDM
    ENDIF ;GETARG

    IFNDEF ARGREV
    ARGREV MACRO args:VARARG
      LOCAL acnt,buff
      buff TEXTEQU <>
      acnt = ARGCOUNT(args)
      WHILE acnt GT 0
        buff CATSTR buff,<,>,GETARG(acnt,args)
        acnt = acnt - 1
      ENDM
      buff SUBSTR buff, 2
      EXITM <buff>
    ENDM
    ENDIF ;ARGREV
    
        ;IFNDEF HeapFree
        ;    PROTO BOOL HeapFree hHeap:HANDLE, dwFlags:DWORD, lpMem:LPVOID
        ;ENDIF

    IFNDEF MEMALLOC
    MEMALLOC MACRO aSize:REQ
    IFDEF WINDOWS
        INVOKE HeapAlloc,RV(GetProcessHeap),0,aSize
    ELSE
        INVOKE malloc,aSize
    ENDIF
        ALIGNADDR RRET(), 16
    ENDM
    ENDIF ;MEMALLOC
    
    IFNDEF MEMFREE
    MEMFREE MACRO memPtr:REQ
    IFDEF WINDOWS
        INVOKE HeapFree,RV(GetProcessHeap),0,memPtr
    ELSE
        INVOKE free,memPtr
    ENDIF
    ENDM
    ENDIF ;MEMFREE
    
    IFNDEF LOADMSS
    LOADMSS MACRO reg, value
        LOCAL vname
        .DATA
        ALIGN 4
        vname DD value
        .CODE
        IF @Arch EQ ARCH_AVX
        VMOVSS reg, vname
        ELSE
        MOVSS reg, vname
        ENDIF
    ENDM
    ENDIF ;LOADMSS
    
    IFNDEF LOADMSD
    LOADMSD MACRO reg, value
        LOCAL bname
        .DATA
        ALIGN 8
        bname DQ value
        .CODE
        IF @Arch EQ ARCH_AVX
        VMOVSD reg, bname
        ELSE
        MOVSD reg, bname
        ENDIF
    ENDM
    ENDIF ;LOADMSD
    
    ;IF @LastReturnType EQ 0            ;; BYTE
    ;ELSEIF @LastReturnType EQ 0x40     ;; SIGNED BYTE
    ;ELSEIF @LastReturnType EQ 1        ;; WORD
    ;ELSEIF @LastReturnType EQ 0x41     ;; SIGNED WORD
    ;ELSEIF @LastReturnType EQ 2        ;; DWORD
    ;ELSEIF @LastReturnType EQ 0x42     ;; SIGNED DWORD
    ;ELSEIF @LastReturnType EQ 3        ;; QWORD
    ;ELSEIF @LastReturnType EQ 0x43     ;; SIGNED QWORD
    ;ELSEIF @LastReturnType EQ 0xc3     ;; PTR
    ;ELSEIF @LastReturnType EQ 6        ;; XMM
    ;ELSEIF @LastReturnType EQ 7        ;; YMM
    ;ELSEIF @LastReturnType EQ 8        ;; ZMM
    ;ELSEIF @LastReturnType EQ 0x22     ;; REAL4
    ;ELSEIF @LastReturnType EQ 0x23     ;; REAL8
    ;ELSE
    ;ENDIF
    
    IFNDEF RET_TYPE
    RET_TYPE MACRO retype:REQ
        IF retype EQ RET_BYTE
            IF @LastReturnType EQ RET_BYTE
            EXITM %(1)
            ELSE
            EXITM %(0)
            ENDIF
        ELSEIF retype EQ RET_SBYTE
            IF @LastReturnType EQ RET_SBYTE
            EXITM %(1)
            ELSE
            EXITM %(0)
            ENDIF
        ELSEIF retype EQ RET_WORD
            IF @LastReturnType EQ RET_WORD
            EXITM %(1)
            ELSE
            EXITM %(0)
            ENDIF
        ELSEIF retype EQ RET_SWORD
            IF @LastReturnType EQ RET_SWORD
            EXITM %(1)
            ELSE
            EXITM %(0)
            ENDIF
        ELSEIF retype EQ RET_DWORD
            IF @LastReturnType EQ RET_DWORD
            EXITM %(1)
            ELSE
            EXITM %(0)
            ENDIF
        ELSEIF retype EQ RET_SDWORD
            IF @LastReturnType EQ RET_SDWORD
            EXITM %(1)
            ELSE
            EXITM %(0)
            ENDIF
        ELSEIF retype EQ RET_QWORD
            IF @LastReturnType EQ RET_QWORD
            EXITM %(1)
            ELSE
            EXITM %(0)
            ENDIF
        ELSEIF retype EQ RET_PTR
            IF @LastReturnType EQ RET_PTR
            EXITM %(1)
            ELSE
            EXITM %(0)
            ENDIF
        ELSEIF retype EQ RET_XMM
            IF @LastReturnType EQ RET_XMM
            EXITM %(1)
            ELSE
            EXITM %(0)
            ENDIF
        ELSEIF retype EQ RET_YMM
            IF @LastReturnType EQ RET_YMM
            EXITM %(1)
            ELSE
            EXITM %(0)
            ENDIF
        ELSEIF retype EQ RET_ZMM
            IF @LastReturnType EQ RET_ZMM
            EXITM %(1)
            ELSE
            EXITM %(0)
            ENDIF
        ELSEIF retype EQ RET_REAL4
            IF @LastReturnType EQ RET_REAL4
            EXITM %(1)
            ELSE
            EXITM %(0)
            ENDIF
        ELSEIF retype EQ RET_REAL8
            IF @LastReturnType EQ RET_REAL8
            EXITM %(1)
            ELSE
            EXITM %(0)
            ENDIF
        ELSEIF retype EQ RET_NONE
            IF @LastReturnType EQ RET_NONE
            EXITM %(1)
            ELSE
            EXITM %(0)
            ENDIF
        ENDIF
    ENDM
    ENDIF ;RET_TYPE
    
    IFNDEF UINVOKE
    UINVOKE MACRO func:REQ, args:VARARG
         IFB <args>
         INVOKE func
         ELSE
         INVOKE func, args
         ENDIF
         IF @LastReturnType EQ 0            ;; BYTE
         EXITM <BRET()>
         ELSEIF @LastReturnType EQ 0x40     ;; SIGNED BYTE
         EXITM <BRET()>
         ELSEIF @LastReturnType EQ 1        ;; WORD
         EXITM <WRET()>
         ELSEIF @LastReturnType EQ 0x41     ;; SIGNED WORD
         EXITM <WRET()>
         ELSEIF @LastReturnType EQ 2        ;; DWORD
         EXITM <DRET()>
         ELSEIF @LastReturnType EQ 0x42     ;; SIGNED DWORD
         EXITM <DRET()>
         ELSEIF @LastReturnType EQ 3        ;; QWORD
         EXITM <RRET()>
         ELSEIF @LastReturnType EQ 0x43     ;; SIGNED QWORD
         EXITM <RRET()>
         ELSEIF @LastReturnType EQ 0xc3     ;; PTR
         EXITM <RRET()>
         ELSEIF @LastReturnType EQ 6        ;; XMM
         EXITM <XMM0>
         ELSEIF @LastReturnType EQ 7        ;; YMM
         EXITM <YMM0>
         ELSEIF @LastReturnType EQ 8        ;; ZMM
         EXITM <ZMM0>
         ELSEIF @LastReturnType EQ 0x22     ;; REAL4
         EXITM <XMM0>
         ELSEIF @LastReturnType EQ 0x23     ;; REAL8
         EXITM <XMM0>
         ELSE
         EXITM <DRET()>
         ENDIF
    ENDM
    ENDIF ;UINVOKE
    
    IFNDEF ASFLOAT
    ASFLOAT MACRO  reg:REQ
         EXITM <REAL4 PTR reg>
    ENDM
    ENDIF ;ASFLOAT

    IFNDEF ASDOUBLE
    ASDOUBLE MACRO reg:REQ
         EXITM <REAL8 PTR reg>
    ENDM
    ENDIF ;ASDOUBLE

    IFNDEF R4P
    R4P MACRO reg:REQ
         EXITM <REAL4 PTR reg>
    ENDM
    ENDIF ;R4P

    IFNDEF R8P
    R8P MACRO reg:REQ
         EXITM <REAL8 PTR reg>
    ENDM
    ENDIF ;R8P
    
    IFNDEF ARGINVOKE
    ARGINVOKE MACRO argNo:REQ, invCount:REQ, func:REQ, args:VARARG
    IFDEF __X64__
        LOCAL dstSize, stackPos, argNum
        REGS15STORAGE
        IFB <args>
            INVOKE func
        ELSE
            IF invCount GE 2
                IF argNo EQ 2
                    MOV RRP0,RP0()
                        IF @Arch EQ ARCH_AVX
                            VMOVAPS RXMM0,XMM0
                        ELSE
                            MOVAPS RXMM0,XMM0
                        ENDIF
                ELSEIF argNo EQ 3
                    MOV RRP0,RP0()
                    MOV RRP1,RP1()
                    IF @Arch EQ ARCH_AVX
                        VMOVAPS RXMM0,XMM0
                        VMOVAPS RXMM1,XMM1
                    ELSE
                        MOVAPS RXMM0,XMM0
                    MOVAPS RXMM1,XMM1
                    ENDIF
                ELSEIF argNo EQ 4
                    MOV RRP0,RP0()
                    MOV RRP1,RP1()
                    MOV RRP2,RP2()
                    IF @Arch EQ ARCH_AVX
                        VMOVAPS RXMM0,XMM0
                        VMOVAPS RXMM1,XMM1
                        VMOVAPS RXMM2,XMM2
                    ELSE
                        MOVAPS RXMM0,XMM0
                        MOVAPS RXMM1,XMM1
                        MOVAPS RXMM2,XMM2
                    ENDIF
                ELSEIF argNo EQ 5
                    MOV RRP0,RP0()
                    MOV RRP1,RP1()
                    MOV RRP2,RP2()
                    MOV RRP3,RP3()
                    IF @Arch EQ ARCH_AVX
                        VMOVAPS RXMM0,XMM0
                        VMOVAPS RXMM1,XMM1
                        VMOVAPS RXMM2,XMM2
                        VMOVAPS RXMM3,XMM3
                    ELSE
                        MOVAPS RXMM0,XMM0
                        MOVAPS RXMM1,XMM1
                        MOVAPS RXMM2,XMM2
                        MOVAPS RXMM3,XMM3
                    ENDIF
                ELSEIF argNo EQ 6
                    MOV RRP0,RP0()
                    MOV RRP1,RP1()
                    MOV RRP2,RP2()
                    MOV RRP3,RP3()
                    MOV RRP4,RP4()
                    IF @Arch EQ ARCH_AVX
                        VMOVAPS RXMM0,XMM0
                        VMOVAPS RXMM1,XMM1
                        VMOVAPS RXMM2,XMM2
                        VMOVAPS RXMM3,XMM3
                        VMOVAPS RXMM4,XMM4
                    ELSE
                        MOVAPS RXMM0,XMM0
                        MOVAPS RXMM1,XMM1
                        MOVAPS RXMM2,XMM2
                        MOVAPS RXMM3,XMM3
                        MOVAPS RXMM4,XMM4
                    ENDIF
                ELSEIF argNo GE 7
                    MOV RRP0,RP0()
                    MOV RRP1,RP1()
                    MOV RRP2,RP2()
                    MOV RRP3,RP3()
                    MOV RRP4,RP4()
                    MOV RRP5,RP5()
                    IF @Arch EQ ARCH_AVX
                        VMOVAPS RXMM0,XMM0
                        VMOVAPS RXMM1,XMM1
                        VMOVAPS RXMM2,XMM2
                        VMOVAPS RXMM3,XMM3
                        VMOVAPS RXMM4,XMM4
                        VMOVAPS RXMM5,XMM5
                    ELSE
                        MOVAPS RXMM0,XMM0
                        MOVAPS RXMM1,XMM1
                        MOVAPS RXMM2,XMM2
                        MOVAPS RXMM3,XMM3
                        MOVAPS RXMM4,XMM4
                        MOVAPS RXMM5,XMM5
                    ENDIF
            ENDIF ;; IF invCount
            INVOKE func, args
            IF invCount GE 2
                IF argNo EQ 2
                    MOV RP0(),RRP0
                    IF @Arch EQ ARCH_AVX
                        VMOVAPS XMM0,RXMM0
                    ELSE
                        MOVAPS XMM0,RXMM0
                    ENDIF
                ELSEIF argNo EQ 3
                    MOV RP0(),RRP0
                    MOV RP1(),RRP1
                    IF @Arch EQ ARCH_AVX
                        VMOVAPS XMM0,RXMM0
                        VMOVAPS XMM1,RXMM1
                    ELSE
                        MOVAPS XMM0,RXMM0
                        MOVAPS XMM1,RXMM1
                    ENDIF
                ELSEIF argNo EQ 4
                    MOV RP0(),RRP0
                    MOV RP1(),RRP1
                    MOV RP2(),RRP2
                    IF @Arch EQ ARCH_AVX
                        VMOVAPS XMM0,RXMM0
                        VMOVAPS XMM1,RXMM1
                        VMOVAPS XMM2,RXMM2
                    ELSE
                        MOVAPS XMM0,RXMM0
                        MOVAPS XMM1,RXMM1
                        MOVAPS XMM2,RXMM2
                    ENDIF
                ELSEIF argNo EQ 5
                    MOV RP0(),RRP0
                    MOV RP1(),RRP1
                    MOV RP2(),RRP2
                    MOV RP3(),RRP3
                    IF @Arch EQ ARCH_AVX
                        VMOVAPS XMM0,RXMM0
                        VMOVAPS XMM1,RXMM1
                        VMOVAPS XMM2,RXMM2
                        VMOVAPS XMM3,RXMM3
                    ELSE
                        MOVAPS XMM0,RXMM0
                        MOVAPS XMM1,RXMM1
                        MOVAPS XMM2,RXMM2
                        MOVAPS XMM3,RXMM3
                    ENDIF
                ELSEIF argNo EQ 6
                    MOV RP0(),RRP0
                    MOV RP1(),RRP1
                    MOV RP2(),RRP2
                    MOV RP3(),RRP3
                    MOV RP4(),RRP4
                    IF @Arch EQ ARCH_AVX
                        VMOVAPS XMM0,RXMM0
                        VMOVAPS XMM1,RXMM1
                        VMOVAPS XMM2,RXMM2
                        VMOVAPS XMM3,RXMM3
                        VMOVAPS XMM4,RXMM4
                    ELSE
                        MOVAPS XMM0,RXMM0
                        MOVAPS XMM1,RXMM1
                        MOVAPS XMM2,RXMM2
                        MOVAPS XMM3,RXMM3
                        MOVAPS XMM4,RXMM4
                    ENDIF
                ELSEIF argNo GE 7
                    MOV RP0(),RRP0
                    MOV RP1(),RRP1
                    MOV RP2(),RRP2
                    MOV RP3(),RRP3
                    MOV RP4(),RRP4
                    MOV RP5(),RRP5
                    IF @Arch EQ ARCH_AVX
                        VMOVAPS XMM0,RXMM0
                        VMOVAPS XMM1,RXMM1
                        VMOVAPS XMM2,RXMM2
                        VMOVAPS XMM3,RXMM3
                        VMOVAPS XMM4,RXMM4
                        VMOVAPS XMM5,RXMM5
                    ELSE
                        MOVAPS XMM0,RXMM0
                        MOVAPS XMM1,RXMM1
                        MOVAPS XMM2,RXMM2
                        MOVAPS XMM3,RXMM3
                        MOVAPS XMM4,RXMM4
                        MOVAPS XMM5,RXMM5
                    ENDIF
                ENDIF ;; IF argNo
            ENDIF ;; IF invCount
        ENDIF ;; IFB <args>
        IF @LastReturnType EQ 0            ;; BYTE
          dstSize = 1
        ELSEIF @LastReturnType EQ 0x40     ;; SIGNED BYTE
          dstSize = 1
        ELSEIF @LastReturnType EQ 1        ;; WORD
          dstSize = 2
        ELSEIF @LastReturnType EQ 0x41     ;; SIGNED WORD
          dstSize = 2
        ELSEIF @LastReturnType EQ 2        ;; DWORD
          dstSize = 4
        ELSEIF @LastReturnType EQ 0x42     ;; SIGNED DWORD
          dstSize = 4
        ELSEIF @LastReturnType EQ 3        ;; QWORD
          dstSize = 8
        ELSEIF @LastReturnType EQ 0x43     ;; SIGNED QWORD
          dstSize = 8
        ELSEIF @LastReturnType EQ 0xc3     ;; PTR
          dstSize = 8
        ELSEIF @LastReturnType EQ 6        ;; XMM
          dstSize = 16
        ELSEIF @LastReturnType EQ 7        ;; YMM
          dstSize = 32
        ELSEIF @LastReturnType EQ 8        ;; ZMM
          dstSize = 64
        ELSEIF @LastReturnType EQ 0x22     ;; REAL4
          dstSize = 16
        ELSEIF @LastReturnType EQ 0x23     ;; REAL8
          dstSize = 16
        ELSE
          dstSize = 4
        ENDIF
        IF argNo EQ 1
            IF dstSize EQ 1
                MOV BP0(),BRET()
                EXITM <BP0()>
            ELSEIF dstSize EQ 2
                MOV WP0(),WRET()
                EXITM <WP0()>
            ELSEIF dstSize EQ 4
                MOV DP0(),DRET()
                EXITM <DP0()>
            ELSEIF dstSize EQ 8
                MOV RP0(),RRET()
                EXITM <RP0()>
            ELSEIF dstSize EQ 16
                EXITM <XMM0>
            ELSEIF dstSize EQ 32
                EXITM <YMM0>
            ELSEIF dstSize EQ 64
                EXITM <ZMM0>
            ENDIF
        ELSEIF argNo EQ 2
            IF dstSize EQ 1
                MOV BP1(),BRET()
                EXITM <BP1()>
            ELSEIF dstSize EQ 2
                MOV WP1(),WRET()
                EXITM <WP1()>
            ELSEIF dstSize EQ 4
                MOV DP1(),DRET()
                EXITM <DP1()>
            ELSEIF dstSize EQ 8
                MOV RP1(),RRET()
                EXITM <RP1()>
            ELSEIF dstSize EQ 16
                IF @Arch EQ ARCH_AVX
                    VMOVDQA XMM1,XMM0
                ELSE
                    MOVDQA XMM1,XMM0
                ENDIF
                EXITM <XMM1>
            ELSEIF dstSize EQ 32
                VMOVDQA YMM1,YMM0
                EXITM <YMM1>
            ELSEIF dstSize EQ 64
                VMOVDQA ZMM1,ZMM0
                EXITM <ZMM1>
            ENDIF
        ELSEIF argNo EQ 3
            IF dstSize EQ 1
                MOV BP2(),BRET()
                EXITM <BP2()>
            ELSEIF dstSize EQ 2
                MOV WP2(),WRET()
                EXITM <WP2()>
            ELSEIF dstSize EQ 4
                MOV DP2(),DRET()
                EXITM <DP2()>
            ELSEIF dstSize EQ 8
                MOV RP2(),RRET()
                EXITM <RP2()>
            ELSEIF dstSize EQ 16
                IF @Arch EQ ARCH_AVX
                    VMOVDQA XMM2,XMM0
                ELSE
                    MOVDQA XMM2,XMM0
                ENDIF
                EXITM <XMM2>
            ELSEIF dstSize EQ 32
                VMOVDQA YMM2,YMM0
                EXITM <YMM2>
            ELSEIF dstSize EQ 64
                VMOVDQA ZMM2,ZMM0
                EXITM <ZMM2>
            ENDIF
        ELSEIF argNo EQ 4
            IF dstSize EQ 1
                MOV BP3(),BRET()
                EXITM <BP3()>
            ELSEIF dstSize EQ 2
                MOV WP3(),WRET()
                EXITM <WP3()>
            ELSEIF dstSize EQ 4
                MOV DP3(),DRET()
                EXITM <DP3()>
            ELSEIF dstSize EQ 8
                MOV RP3(),RRET()
                EXITM <RP3()>
            ELSEIF dstSize EQ 16
                IF @Arch EQ ARCH_AVX
                    VMOVDQA XMM3,XMM0
                ELSE
                    MOVDQA XMM3,XMM0
                ENDIF
                EXITM <XMM3>
            ELSEIF dstSize EQ 32
                VMOVDQA YMM3,YMM0
                EXITM <YMM3>
            ELSEIF dstSize EQ 64
                VMOVDQA ZMM3,ZMM0
                EXITM <ZMM3>
            ENDIF
        ELSEIF(argNo EQ 5) AND (@LangType EQ LANG_REGCALL OR @LangType EQ LANG_SYSVCALL OR @LangType EQ LANG_SYSCALL)
                argNum = 5
            IF dstSize EQ 1
                MOV BP4(),BRET()
                EXITM <BP4()>
            ELSEIF dstSize EQ 2
                MOV WP4(),WRET()
                EXITM <WP4()>
            ELSEIF dstSize EQ 4
                MOV DP4(),DRET()
                EXITM <DP4()>
            ELSEIF dstSize EQ 8
                MOV RP4(),RRET()
                EXITM <RP4()>
            ELSEIF dstSize EQ 16
                IF @Arch EQ ARCH_AVX
                    VMOVDQA XMM4,XMM0
                ELSE
                    MOVDQA XMM4,XMM0
                ENDIF
                EXITM <XMM4>
            ELSEIF dstSize EQ 32
                VMOVDQA YMM4,YMM0
                EXITM <YMM4>
            ELSEIF dstSize EQ 64
                VMOVDQA ZMM4,ZMM0
                EXITM <ZMM4>
            ENDIF
        ELSEIF(argNo EQ 6) AND (@LangType EQ LANG_REGCALL OR @LangType EQ LANG_SYSVCALL OR @LangType EQ LANG_SYSCALL)
                argNum = 6
            IF dstSize EQ 1
                MOV BP5(),BRET()
                EXITM <BP5()>
            ELSEIF dstSize EQ 2
                MOV WP5(),WRET()
                EXITM <WP5()>
            ELSEIF dstSize EQ 4
                MOV DP5(),DRET()
                EXITM <DP5()>
            ELSEIF dstSize EQ 8
                MOV RP5(),RRET()
                EXITM <RP5()>
            ELSEIF dstSize EQ 16
                IF @Arch EQ ARCH_AVX
                    VMOVDQA XMM5,XMM0
                ELSE
                    MOVDQA XMM5,XMM0
                ENDIF
                EXITM <XMM5>
            ELSEIF dstSize EQ 32
                VMOVDQA YMM5,YMM0
                EXITM <YMM5>
            ELSEIF dstSize EQ 64
                VMOVDQA ZMM5,ZMM0
                EXITM <ZMM5>
            ENDIF
        ELSE
            IF argNo EQ 5
                argNum = 5
            ELSEIF argNo EQ 6
                argNum = 6
            ELSE
                argNum = 7
            ENDIF
            IF dstSize EQ 1
                MOV      [RSPTR() + ((argNo-1)*SIZE_T_SIZE) + ((argNo - argNum) * SIZE_T_SIZE)],BRET()
            ELSEIF dstSize EQ 2
                MOV      [RSPTR() + ((argNo-1)*SIZE_T_SIZE) + ((argNo - argNum) * SIZE_T_SIZE)],WRET()
            ELSEIF dstSize EQ 4
                MOV      [RSPTR() + ((argNo-1)*SIZE_T_SIZE) + ((argNo - argNum) * SIZE_T_SIZE)],DRET()
            ELSEIF dstSize EQ 8
                MOV      [RSPTR() + ((argNo-1)*SIZE_T_SIZE) + ((argNo - argNum) * SIZE_T_SIZE)],RRET()
            ELSEIF(dstSize EQ 16) OR (dstSize EQ 32) OR (dstSize EQ 64)
                IF @Arch EQ ARCH_AVX
                    VMOVSD     [RSPTR() + ((argNo-1)*SIZE_T_SIZE) + ((argNo - argNum) * SIZE_T_SIZE)],XMM0
                ELSE
                    MOVSD      [RSPTR() + ((argNo-1)*SIZE_T_SIZE) + ((argNo - argNum) * SIZE_T_SIZE)],XMM0
                ENDIF
            ENDIF
            EXITM <[RSPTR() + ((argNo-1)*SIZE_T_SIZE) + ((argNo - argNum) * SIZE_T_SIZE)]>
        ENDIF
    ELSE
        LOCAL arg
        arg TEXTEQU <INVOKE func>
        FOR var, <args>
        arg CATSTR arg, <, var>
        ENDM
        arg
        IF @LastReturnType EQ 0
        EXITM <BRET()>
        ELSEIF @LastReturnType EQ 0x40
        EXITM <BRET()>
        ELSEIF @LastReturnType EQ 1
        EXITM <WRET()>
        ELSEIF @LastReturnType EQ 0x41
        EXITM <WRET()>
        ELSEIF @LastReturnType EQ 2
        EXITM <DRET()>
        ELSEIF @LastReturnType EQ 0x42
        EXITM <DRET()>
        ELSEIF @LastReturnType EQ 3
        EXITM <RRET()>
        ELSEIF @LastReturnType EQ 0x43
        EXITM <RRET()>
        ELSEIF @LastReturnType EQ 0xc3
        EXITM <RRET()>
        ELSEIF @LastReturnType EQ 6
        EXITM <XMM0>
        ELSEIF @LastReturnType EQ 7
        EXITM <YMM0>
        ELSEIF @LastReturnType EQ 8
        EXITM <ZMM0>
        ELSEIF @LastReturnType EQ 0x22
        EXITM <XMM0>
        ELSEIF @LastReturnType EQ 0x23
        EXITM <XMM0>
        ELSE
        EXITM <DRET()>
        ENDIF
    ENDIF ;__X64__
    ENDM
    ENDIF ;ARGINVOKE
    
    IFNDEF CVIRTUAL
    CVIRTUAL MACRO method:REQ, retType:REQ, protoDef:VARARG
        LOCAL sz1, sz2
        pDef CATSTR <TYPEDEF PROTO >,<(&retType&)>,< thisPtr:PTR>
        IFNB <protoDef>
        pDef CATSTR pDef, <, >, <&protoDef>
        ENDIF
        sz2 CATSTR <_>, curClass, <_&method>, <Pto>
        % &sz2 &pDef
        % sz1 TYPEDEF PTR &sz2
        % method sz1 0
        % __&curClass&_size = __&curClass&_size + SIZE_T_SIZE
        cvfnex TEXTEQU <_>
        cvfnex CATSTR cvfnex, curClass, <_>, <&method&>, < PROTO >, <(&retType&)>, < thisPtr:PTR>, curClass
        IFNB <&protoDef>
        cvfnex CATSTR cvfnex, <, >, <&protoDef&>
        ELSE
        ENDIF
        cvfnex
    ENDM
    ENDIF ;CVIRTUAL

    IFNDEF COMINTERFACE
    COMINTERFACE MACRO CName:REQ
        curClass TEXTEQU <CName>
        % __&CName&_size = 3*SIZE_T_SIZE
        @CatStr(CName, <vtbl COMSTRUCT >)
        ptrDefS TEXTEQU <PTR>
        ptrDefS CATSTR ptrDefS, <&curClass&>, < TYPEDEF PTR >, <&curClass&>
        % ptrDefS
        CVIRTUAL QueryInterface, <SIZE_T>, :PTR
        CVIRTUAL AddRef, <DWORD>
        CVIRTUAL Release, <DWORD>
    ENDM
    ENDIF ;COMINTERFACE
    
    IFNDEF ENDMETHODS
    ENDMETHODS MACRO
        LOCAL evtbl
        % evtbl CATSTR <&curClass&>,<vtbl>,< ENDS>
        evtbl
        @CatStr(curClass, < CSTRUCT >)
        % pVtbl ISIZE_T OFFSET _stat&curClass&vtbl
    ENDM
    ENDIF ;ENDMETHODS
    
    IFNDEF ENDCOMINTERFACE
    ENDCOMINTERFACE MACRO
        ENDMETHODS
        curClass ENDS
        .DATA
        % _stat&curClass&vtbl &curClass&vtbl <>
        % _stat&curClass& curClass <>
    ENDM
    ENDIF ;ENDCOMINTERFACE
    
    IFNDEF _VINVOKE
    _VINVOKE MACRO pInterface:REQ, Interface:REQ, Function:REQ, args:VARARG
        LOCAL SAVERP1
        InterfacePtr TEXTEQU <_>
        InterfacePtr CATSTR InterfacePtr, <&Interface>, <_>, <&Function>, <Pto>
        .DATA?
        SAVERP1 ISIZE_T ?
        .CODE
        MOV SAVERP1, RP1()
        IF(OPATTR(pInterface)) AND 00010000b
            IFNB <args>
                IFDIFI <&pInterface>,<RTHIS()>
                    MOV RTHIS(),&pInterface
                ENDIF
                MOV RP1(),[RTHIS()]
                INVOKE(InterfacePtr PTR[RP1()].&Interface&vtbl.&Function), RTHIS(), &args
            ELSE
                IFDIFI <&pInterface>,<RTHIS()>
                    MOV RTHIS(),&pInterface
                ENDIF
                MOV RP1(),[RTHIS()]
                INVOKE(InterfacePtr PTR[RP1()].&Interface&vtbl.&Function), RTHIS()
            ENDIF
        ELSE
            IFDIFI <&pInterface>,<RTHIS()>
                MOV RTHIS(),pInterface
            ENDIF
            MOV RP1(),[RTHIS()]
            IFNB <args>
                FOR arg, <args>
                    IFIDNI <&arg>, <RTHIS()>
                        .ERR <RTHIS()" is not allowed as a Method parameter with indirect object label">
                    ENDIF
                ENDM
                INVOKE(InterfacePtr PTR[RP1()].&Interface&vtbl.&Function), RTHIS(), &args
            ELSE
                INVOKE(InterfacePtr PTR[RP1()].&Interface&vtbl.&Function), RTHIS()
            ENDIF
        ENDIF
        MOV RP1(), SAVERP1
    ENDM
    ENDIF ;_VINVOKE
    
    IFNDEF _V
    _V MACRO pInterface:REQ, Interface:REQ, Function:REQ, args:VARARG
        LOCAL SAVERP1
        InterfacePtr TEXTEQU <_>
        InterfacePtr CATSTR InterfacePtr, <&Interface>, <_>, <&Function>, <Pto>
        .DATA?
        SAVERP1 ISIZE_T ?
        .CODE
        MOV SAVERP1, RP1()
        IF(OPATTR(pInterface)) AND 00010000b
            IFNB <args>
                IFDIFI <&pInterface>,<RTHIS()>
                    MOV RTHIS(),&pInterface
                ENDIF
                MOV RP1(),[RTHIS()]
                INVOKE(InterfacePtr PTR[RP1()].&Interface&vtbl.&Function), RTHIS(), &args
            ELSE
                IFDIFI <&pInterface>,<RTHIS()>
                    MOV RTHIS(),&pInterface
                ENDIF
                MOV RP1(),[RTHIS()]
                INVOKE(InterfacePtr PTR[RP1()].&Interface&vtbl.&Function), RTHIS()
            ENDIF
        ELSE
            IFDIFI <&pInterface>,<RTHIS()>
                MOV RTHIS(),pInterface
            ENDIF
            MOV RP1(),[RTHIS()]
            IFNB <args>
                FOR arg, <args>
                    IFIDNI <&arg>, <RTHIS()>
                    .ERR <RTHIS()" is not allowed as a Method parameter with indirect object label">
                    ENDIF
                ENDM
                INVOKE(InterfacePtr PTR[RP1()].&Interface&vtbl.&Function), RTHIS(), &args
            ELSE
                INVOKE(InterfacePtr PTR[RP1()].&Interface&vtbl.&Function), RTHIS()
            ENDIF
        ENDIF
        MOV RP1(), SAVERP1
        IF @LastReturnType EQ 0
            EXITM <BRET()>
        ELSEIF @LastReturnType EQ 0x40
            EXITM <BRET()>
        ELSEIF @LastReturnType EQ 1
            EXITM <WRET()>
        ELSEIF @LastReturnType EQ 0x41
            EXITM <WRET()>
        ELSEIF @LastReturnType EQ 2
            EXITM <DRET()>
        ELSEIF @LastReturnType EQ 0x42
            EXITM <DRET()>
        ELSEIF @LastReturnType EQ 3
            EXITM <RRET()
        ELSEIF @LastReturnType EQ 0x43
            EXITM <RRET()>
        ELSEIF @LastReturnType EQ 0xc3
            EXITM <RRET()>
        ELSEIF @LastReturnType EQ 6
            EXITM <XMM0>
        ELSEIF @LastReturnType EQ 7
            EXITM <YMM0>
        ELSEIF @LastReturnType EQ 8
            EXITM <ZMM0>
        ELSEIF @LastReturnType EQ 0x22
            EXITM <XMM0>
        ELSEIF @LastReturnType EQ 0x23
            EXITM <XMM0>
        ELSE
            EXITM <DRET()>
        ENDIF
    ENDM
    ENDIF ;_V
    
    IFNDEF _ARRAY
     _ARRAY MACRO arrType:REQ,sizeArr:REQ
        LOCAL SAVERP1
        cdef TEXTEQU <__&arrType&_def>
        .DATA?
        SAVERP1 ISIZE_T ?
        .CODE
        MOV SAVERP1, RP1()
        % IFDEF cdef
            MOV RP1(), SIZE_T_SIZE
        ELSE
            MOV RP1(),SIZEOF(arrType)
        ENDIF
        IMUL RP1(),sizeArr
        MEMALLOC(RP1())
        MOV RP1(), SAVERP1
        EXITM <RRET()>
    ENDM
    ENDIF ;_ARRAY
    
    IFNDEF _DELETEARRAY
    _DELETEARRAY MACRO arrPtr:REQ
        MEMFREE(arrPtr)
    ENDM
    ENDIF ;_DELETEARRAY
    
    IFNDEF OINTERFACE
    OINTERFACE MACRO CName:REQ
        % __&CName&_def EQU 1
        % __&CName&_size = 16
        curClass TEXTEQU <CName>
        @CatStr(CName, <vtbl CSTRUCT >)
        __0 ISIZE_T 0
        __1 ISIZE_T 0
        ptrDefS TEXTEQU <PTR>
        ptrDefS CATSTR ptrDefS, <&curClass&>, < TYPEDEF PTR >, <&curClass&>
        % ptrDefS
    ENDM
    ENDIF ;OINTERFACE

    IFNDEF ENDOINTERFACE
    ENDOINTERFACE MACRO
        curClass ENDS
    ENDM
    ENDIF ;ENDOINTERFACE

    IFNDEF CLASS
    CLASS MACRO CName:REQ
        % __&CName&_def = 1
        % __&CName&_size = 16
        curClass TEXTEQU <CName>
        @CatStr(CName, <vtbl CSTRUCT >)
        ctorS TEXTEQU <ctor ISIZE_T OFFSET _&CName&_Init>
        dtorS TEXTEQU <dtor ISIZE_T OFFSET _&CName&_Destroy>
        ctorS
        dtorS
    ENDM
    ENDIF ;CLASS

    IFNDEF ENDCLASS
    ENDCLASS MACRO
        curClass ENDS
        .DATA
        ALIGN 16
        % _stat&curClass&vtbl &curClass&vtbl <>
        ALIGN 16
        % _stat&curClass& curClass <>
        ptrDefS TEXTEQU <PTR>
        ptrDefS CATSTR ptrDefS, <&curClass&>, < TYPEDEF PTR >, <&curClass&>
        % ptrDefS
        ptrDefS2 TEXTEQU <PTR>
        ptrDefS2 CATSTR ptrDefS2, <&curClass&vtbl>, < TYPEDEF PTR >, <&curClass&vtbl>
        % ptrDefS2
        .CODE
    ENDM
    ENDIF ;ENDCLASS
    
    IFNDEF CMETHOD
    CMETHOD MACRO method:REQ
        LOCAL sz1, sz2
        sz2 CATSTR <_>, curClass, <_&method>, <Pto>
        % sz1 TYPEDEF PTR &sz2
        % method sz1 OFFSET _&curClass&_&method&
        % __&curClass&_size = __&curClass&_size + SIZE_T_SIZE
    ENDM
    ENDIF ;CMETHOD

    IFNDEF METHOD
    METHOD MACRO className:REQ, method:REQ, retType:=<dword>, usesStr:=<USES RBASE() RSIDX() RDIDX()>, args:VARARG
        curClass TEXTEQU <className>
        curMethod TEXTEQU <method>
        methodfnex TEXTEQU <_>
        methodfnex CATSTR methodfnex, <&className&>
        methodfnex CATSTR methodfnex, <_>
        methodfnex CATSTR methodfnex, <&method&>
        methodfnex CATSTR methodfnex, < PROTO >, <(&retType&)> , < thisPtr:PTR>, <&className&>
        IFNB <args>
            methodfnex CATSTR methodfnex, <, >, <&args&>
        ELSE
        ENDIF
        methodfnex
        methodfnex TEXTEQU <_>
        methodfnex CATSTR methodfnex, <&className&>
        methodfnex CATSTR methodfnex, <_>
        methodfnex CATSTR methodfnex, <&method&>
        methodfnex CATSTR methodfnex, <Pto TYPEDEF PROTO >,<(&retType&)>,< thisPtr:PTR>, <&className&>
        IFNB <args>
            methodfnex CATSTR methodfnex, <, >, <&args&>
        ELSE
        ENDIF
        methodfnex
        methodfnex TEXTEQU <_>
        methodfnex CATSTR methodfnex, <&className&>
        methodfnex CATSTR methodfnex, <_>
        methodfnex CATSTR methodfnex, <&method&>
        methodfnex CATSTR methodfnex,< PROC >, <(&retType&)>, < >, <&usesStr&>, < thisPtr:PTR>, <&className&>
        IFNB <args>
        methodfnex CATSTR methodfnex, <, >, <&args&>
        ELSE
        ENDIF
        assume RTHIS():PTR curClass
        ALIGN 16
        methodfnex
    ENDM
    ENDIF ;METHOD

    IFNDEF STATICMETHOD
    STATICMETHOD MACRO className:REQ, method:REQ, retType:=<dword>, usesStr:=<USES RBASE() RSIDX() RDIDX()>, args:VARARG
        curClass TEXTEQU <className>
        curMethod TEXTEQU <method>
        stmethodfnex TEXTEQU <_>
        stmethodfnex CATSTR stmethodfnex, <&className&>
        stmethodfnex CATSTR stmethodfnex, <_>
        stmethodfnex CATSTR stmethodfnex, <&method&>
        stmethodfnex CATSTR stmethodfnex, < PROTO >, <(&retType&)>
        IFNB <args>
            stmethodfnex CATSTR stmethodfnex, < >, <&args&>
        ELSE
        ENDIF
        stmethodfnex
        stmethodfnex TEXTEQU <_>
        stmethodfnex CATSTR stmethodfnex, <&className&>
        stmethodfnex CATSTR stmethodfnex, <_>
        stmethodfnex CATSTR stmethodfnex, <&method&>
        stmethodfnex CATSTR stmethodfnex, <Pto TYPEDEF PROTO >,<(&retType&)>
        IFNB <args>
            stmethodfnex CATSTR stmethodfnex, < >, <&args&>
        ELSE
        ENDIF
        stmethodfnex
        stmethodfnex TEXTEQU <_>
        stmethodfnex CATSTR stmethodfnex, <&className&>
        stmethodfnex CATSTR stmethodfnex, <_>
        stmethodfnex CATSTR stmethodfnex, <&method&>
        stmethodfnex CATSTR stmethodfnex,< PROC >, <(&retType&)>, < >, <&usesStr&>
        IFNB <args>
            stmethodfnex CATSTR stmethodfnex, < >, <&args&>
        ELSE
        ENDIF
        assume RTHIS():PTR curClass
        ALIGN 16
        stmethodfnex
    ENDM
    ENDIF ;STATICMETHOD

    IFNDEF VECMETHOD
    VECMETHOD MACRO className:REQ, method:REQ, retType:=<dword>, usesStr:=<USES RBASE() RSIDX() RDIDX()>, args:VARARG
        curClass TEXTEQU <className>
        curMethod TEXTEQU <method>
        vecmethodfnex TEXTEQU <_>
        vecmethodfnex CATSTR vecmethodfnex, <&className&>
        vecmethodfnex CATSTR vecmethodfnex, <_>
        vecmethodfnex CATSTR vecmethodfnex, <&method&>
        vecmethodfnex CATSTR vecmethodfnex, < PROTO CALLCONV >, <(&retType&)> , < thisPtr:PTR>, <&className&>
        IFNB <args>
            vecmethodfnex CATSTR vecmethodfnex, <, >, <&args&>
        ELSE
        ENDIF
        vecmethodfnex
        vecmethodfnex TEXTEQU <_>
        vecmethodfnex CATSTR vecmethodfnex, <&className&>
        vecmethodfnex CATSTR vecmethodfnex, <_>
        vecmethodfnex CATSTR vecmethodfnex, <&method&>
        vecmethodfnex CATSTR vecmethodfnex, <Pto TYPEDEF PROTO CALLCONV >,<(&retType&)>,< thisPtr:PTR>, <&className&>
        IFNB <args>
            vecmethodfnex CATSTR vecmethodfnex, <, >, <&args&>
        ELSE
        ENDIF
        vecmethodfnex
        vecmethodfnex TEXTEQU <_>
        vecmethodfnex CATSTR vecmethodfnex, <&className&>
        vecmethodfnex CATSTR vecmethodfnex, <_>
        vecmethodfnex CATSTR vecmethodfnex, <&method&>
        vecmethodfnex CATSTR vecmethodfnex,< PROC CALLCONV >, <(&retType&)>, < >, <&usesStr&>, < thisPtr:PTR>, <&className&>
        IFNB <args>
            vecmethodfnex CATSTR vecmethodfnex, <, >, <&args&>
        ELSE
        ENDIF
        assume RTHIS():PTR curClass
        ALIGN 16
        vecmethodfnex
    ENDM
    ENDIF ;VECMETHOD
    
    IFNDEF STATICVECMETHOD
    STATICVECMETHOD MACRO className:REQ, method:REQ, retType:=<dword>, usesStr:=<USES RBASE() RSIDX() RDIDX()>, args:VARARG
        curClass TEXTEQU <className>
        curMethod TEXTEQU <method>
        stvecmethodfnex TEXTEQU <_>
        stvecmethodfnex CATSTR stvecmethodfnex, <&className&>
        stvecmethodfnex CATSTR stvecmethodfnex, <_>
        stvecmethodfnex CATSTR stvecmethodfnex, <&method&>
        stvecmethodfnex CATSTR stvecmethodfnex, < PROTO CALLCONV >, <(&retType&)>
        IFNB <args>
            stvecmethodfnex CATSTR stvecmethodfnex, < >, <&args&>
        ELSE
        ENDIF
        stvecmethodfnex
        stvecmethodfnex TEXTEQU <_>
        stvecmethodfnex CATSTR stvecmethodfnex, <&className&>
        stvecmethodfnex CATSTR stvecmethodfnex, <_>
        stvecmethodfnex CATSTR stvecmethodfnex, <&method&>
        stvecmethodfnex CATSTR stvecmethodfnex, <Pto TYPEDEF PROTO CALLCONV >,<(&retType&)>
        IFNB <args>
            stvecmethodfnex CATSTR stvecmethodfnex, < >, <&args&>
        ELSE
        ENDIF
        stvecmethodfnex
        stvecmethodfnex TEXTEQU <_>
        stvecmethodfnex CATSTR stvecmethodfnex, <&className&>
        stvecmethodfnex CATSTR stvecmethodfnex, <_>
        stvecmethodfnex CATSTR stvecmethodfnex, <&method&>
        stvecmethodfnex CATSTR stvecmethodfnex,< PROC CALLCONV >, <(&retType&)>, < >, <&usesStr&>
        IFNB <args>
            stvecmethodfnex CATSTR stvecmethodfnex, < >, <&args&>
        ELSE
        ENDIF
        assume RTHIS():PTR curClass
        ALIGN 16
        stvecmethodfnex
    ENDM
    ENDIF ;STATICVECMETHOD

    IFNDEF ENDMETHOD
    ENDMETHOD MACRO
        assume RTHIS():nothing
        endmethodfnex TEXTEQU <_>
        endmethodfnex CATSTR endmethodfnex, curClass
        endmethodfnex CATSTR endmethodfnex, <_>
        endmethodfnex CATSTR endmethodfnex, curMethod
        endmethodfnex CATSTR endmethodfnex, < ENDP>
        endmethodfnex
    ENDM
    ENDIF ;ENDMETHOD

    IFNDEF _DECLARE
    _DECLARE MACRO varName:REQ, typeName:VARARG
        ldef TEXTEQU <LOCAL &varName&>
        ldef CATSTR ldef, < : >
        ldef CATSTR ldef, <typeName>
        % ldef
    ENDM
    ENDIF ;_DECLARE

    IFNDEF _STATICREF
    _STATICREF MACRO reg:REQ, classType:REQ
        % LEA reg, _stat&classType&
    ENDM
    ENDIF ;_STATICREF
    
    IFNDEF _NEW
    _NEW MACRO className:REQ, ctorArgs:VARARG
        LOCAL SAVERP1,SAVERCOUNT
        .DATA?
        SAVERP1 ISIZE_T ?
        SAVERCOUNT ISIZE_T ?
        .CODE
        MOV SAVERP1, RP1()
        MOV SAVERCOUNT, RCOUNT()
        % MOV RP1(), SIZEOF(className)
        MEMALLOC(RP1())
        .IF (RRET() != 0)
            MOV RDIDX(),RRET()
            % LEA RSIDX(),_stat&className
            % MOV RCOUNT(), SIZEOF(className)
            REP MOVSB
            fnex TEXTEQU <_>
            fnex CATSTR fnex, <&className&>
            fnex CATSTR fnex, <_>
            fnex CATSTR fnex, <Init>
            IFNB <ctorArgs>
                fnex2 TEXTEQU <INVOKE fnex, RRET(), ctorArgs>
            ELSE
                fnex2 TEXTEQU <INVOKE fnex, RRET()>
            ENDIF
            fnex2
        .ENDIF
        MOV RCOUNT(), SAVERCOUNT
        MOV RP1(), SAVERP1
        EXITM <RRET()>
    ENDM
    ENDIF ;_NEW

    IFNDEF _RBXNEW
    _RBXNEW MACRO className:REQ, ctorArgs:VARARG
        LOCAL SAVERP1,SAVERCOUNT
        .DATA?
        SAVERP1 ISIZE_T ?
        SAVERCOUNT ISIZE_T ?
        .CODE
        MOV SAVERP1, RP1()
        MOV SAVERCOUNT, RCOUNT()
        % MOV RP1(), SIZEOF(className)
        MEMALLOC(RP1())
        .IF (RRET() != 0)
            MOV RDIDX(),RRET()
            % LEA RSIDX(),_stat&className
            % MOV RCOUNT(), SIZEOF(className)
            REP MOVSB
            fnex TEXTEQU <_>
            fnex CATSTR fnex, <&className&>
            fnex CATSTR fnex, <_>
            fnex CATSTR fnex, <Init>
            IFNB <ctorArgs>
                fnex2 TEXTEQU <INVOKE fnex, RRET(), ctorArgs>
            ELSE
                fnex2 TEXTEQU <INVOKE fnex, RRET()>
            ENDIF
            fnex2
            MOV RBASE(), RRET()
        .ENDIF
        MOV RCOUNT(), SAVERCOUNT
        MOV RP1(), SAVERP1
        EXITM <RBASE()>
    ENDM
    ENDIF ;_RBXNEW

    IFNDEF _ITEM
    _ITEM MACRO objPtr:REQ, idx:REQ
        EXITM <[_V(objPtr, Iterator, Items, idx)]>
    ENDM
    ENDIF ;_ITEM
    
    IFNDEF _ITEMR
    _ITEMR MACRO objPtr:REQ, idx:REQ
        EXITM <_V(objPtr, Iterator, Items, idx)>
    ENDM
    ENDIF ;_ITEMR

    IFNDEF _INVOKE
    _INVOKE MACRO className:REQ, method:REQ, objPtr:REQ, args:VARARG
        fnex TEXTEQU <_>
        fnex CATSTR fnex, <&className&>
        fnex CATSTR fnex, <_>
        fnex CATSTR fnex, <&method&>
        IFNB <args>
            fnex2 TEXTEQU <INVOKE fnex, &objPtr&, &args&>
        ELSE
            fnex2 TEXTEQU <INVOKE fnex, &objPtr&>
        ENDIF
        fnex2
    ENDM
    ENDIF ;_INVOKE

    IFNDEF _I
    _I MACRO className:REQ, method:REQ, objPtr:REQ, args:VARARG
        fnex TEXTEQU <_>
        fnex CATSTR fnex, <&className&>
        fnex CATSTR fnex, <_>
        fnex CATSTR fnex, <&method&>
        fnex2 TEXTEQU <INVOKE fnex, &objPtr&, &args&>
        fnex2
        IF @LastReturnType EQ 0
        EXITM <BRET()>
        ELSEIF @LastReturnType EQ 0x40
        EXITM <BRET()>
        ELSEIF @LastReturnType EQ 1
        EXITM <WRET()>
        ELSEIF @LastReturnType EQ 0x41
        EXITM <WRET()>
        ELSEIF @LastReturnType EQ 2
        EXITM <DRET()>
        ELSEIF @LastReturnType EQ 0x42
        EXITM <DRET()>
        ELSEIF @LastReturnType EQ 3
        EXITM <RRET()>
        ELSEIF @LastReturnType EQ 0x43
        EXITM <RRET()>
        ELSEIF @LastReturnType EQ 0xc3
        EXITM <RRET()>
        ELSEIF @LastReturnType EQ 6
        EXITM <XMM0>
        ELSEIF @LastReturnType EQ 7
        EXITM <YMM0>
        ELSEIF @LastReturnType EQ 8
        EXITM <ZMM0>
        ELSEIF @LastReturnType EQ 0x22
        EXITM <XMM0>
        ELSEIF @LastReturnType EQ 0x23
        EXITM <XMM0>
        ELSE
        EXITM <DRET()>
        ENDIF
    ENDM
    ENDIF ;_I

    IFNDEF _STATIC
    _STATIC MACRO className:REQ, method:REQ, args:VARARG
        fnex TEXTEQU <_>
        fnex CATSTR fnex, <&className&>
        fnex CATSTR fnex, <_>
        fnex CATSTR fnex, <&method&>
        fnex2 TEXTEQU <INVOKE fnex, &args&>
        fnex2
        IF @LastReturnType EQ 0
        EXITM <BRET()>
        ELSEIF @LastReturnType EQ 0x40
        EXITM <BRET()>
        ELSEIF @LastReturnType EQ 1
        EXITM <WRET()>
        ELSEIF @LastReturnType EQ 0x41
        EXITM <WRET()>
        ELSEIF @LastReturnType EQ 2
        EXITM <DRET()>
        ELSEIF @LastReturnType EQ 0x42
        EXITM <DRET()>
        ELSEIF @LastReturnType EQ 3
        EXITM <RRET()>
        ELSEIF @LastReturnType EQ 0x43
        EXITM <RRET()>
        ELSEIF @LastReturnType EQ 0xc3
        EXITM <RRET()>
        ELSEIF @LastReturnType EQ 6
        EXITM <XMM0>
        ELSEIF @LastReturnType EQ 7
        EXITM <YMM0>
        ELSEIF @LastReturnType EQ 8
        EXITM <ZMM0>
        ELSEIF @LastReturnType EQ 0x22
        EXITM <XMM0>
        ELSEIF @LastReturnType EQ 0x23
        EXITM <XMM0>
        ELSE
        EXITM <DRET()>
        ENDIF
    ENDM
    ENDIF ;_STATIC

    IFNDEF _DELETE
    _DELETE MACRO objPtr:REQ
        MOV RTHIS(), objPtr
        MOV RRET(),[RTHIS()]
        CALL SIZE_T PTR[RRET() + SIZE_T_SIZE]
        MEMFREE(objPtr)
    ENDM
    ENDIF ;_DELETE

    IFNDEF CSTATIC
    CSTATIC MACRO method:REQ
        LOCAL sz1, sz2
        sz2 CATSTR <_>, curClass, <_&method>, <Pto>
        % sz1 TYPEDEF PTR &sz2
        % method sz1 OFFSET _&curClass&_&method&
        % __&curClass&_size = __&curClass&_size + SIZE_T_SIZE
    ENDM
    ENDIF ;CSTATIC

    IFNDEF _DEREF
    _DEREF MACRO itype:REQ, iproc:REQ, argCount:REQ, argsAndRefs:VARARG
        LOCAL i, ptrstr, typestr, argstr, SAVERP1
        argstr TEXTEQU < >
        i = 0
        FOR dref, <argsAndRefs>
            IF i LT argCount+1
                IF i GT 0
                    argstr CATSTR argstr, <,>, <&dref&>
                ENDIF
            ELSE
                IF(i - argCount) MOD 2 EQ 1
                ptrstr TEXTEQU <&dref&>
                ELSE
                typestr TEXTEQU <&dref&>
                    IF(i - argCount) EQ 1
                        % IF(OPATTR(ptrstr)) EQ 0x30
                            % MOV RTHIS(), &ptrstr&
                          ELSE
                            % MOV RTHIS(), @CatStr(<[>, <&ptrstr&>, <].>, <&typestr&>)
                          ENDIF
                    ELSE
                        % MOV RTHIS(), @CatStr(<[>, <&ptrstr&>, <].>, <&typestr&>)
                    ENDIF
                ENDIF
            ENDIF
            i = i + 1
        ENDM
        % IF @SizeStr(<%&argstr&>) GT 3
            argstr SUBSTR argstr, 3
        ENDIF
        IF argCount EQ 0
            argstr TEXTEQU <>
        ENDIF
        .DATA?
        SAVERP1 ISIZE_T ?
        .CODE
        MOV SAVERP1, RP1()
        IF argCount GT 0
            InterfacePtr TEXTEQU <_>
            InterfacePtr CATSTR InterfacePtr, <&itype>, <_>, <&iproc>, <Pto>
            IF(OPATTR(RTHIS())) AND 00010000b
                % IF argCount GT 0
                    MOV RP1(),[RTHIS()]
                    % INVOKE(InterfacePtr PTR[RP1()].&itype&vtbl.&iproc), RTHIS(), &argstr
                  ELSE
                    MOV RP1(),[RTHIS()]
                    % INVOKE(InterfacePtr PTR[RP1()].&itype&vtbl.&iproc), RTHIS()
                  ENDIF
            ELSE
                MOV RP1(),[RTHIS()]
                IF argCount GT 0
                    FOR arg, <argstr>
                        IFIDNI <&arg>, <RTHIS()>
                           .ERR <RTHIS()" is not allowed as a Method parameter with indirect object label">
                        ENDIF
                    ENDM
                        % INVOKE(InterfacePtr PTR[RP1()].&itype&vtbl.&iproc), RTHIS(), &argstr
                ELSE
                    INVOKE(InterfacePtr PTR[RP1()].&itype&vtbl.&iproc), RTHIS()
                ENDIF
            ENDIF
        ELSE
            InterfacePtr TEXTEQU <_>
            InterfacePtr CATSTR InterfacePtr, <&itype>, <_>, <&iproc>, <Pto>
            IF(OPATTR(RTHIS())) AND 00010000b
                IF argCount GT 0
                    MOV RP1(),[RTHIS()]
                    % INVOKE(InterfacePtr PTR[RP1()].&itype&vtbl.&iproc), RTHIS(), &argstr
                ELSE
                    MOV RP1(),[RTHIS()]
                    INVOKE(InterfacePtr PTR[RP1()].&itype&vtbl.&iproc), RTHIS()
                ENDIF
            ELSE
                MOV RP1(),[RTHIS()]
                IF argCount GT 0
                    FOR arg, <argstr>
                        IFIDNI <&arg>, <RTHIS()>
                            .ERR <RTHIS()" is not allowed as a Method parameter with indirect object label">
                        ENDIF
                    ENDM
                    % INVOKE(InterfacePtr PTR[RP1()].&itype&vtbl.&iproc), RTHIS(), &argstr
                ELSE
                    INVOKE(InterfacePtr PTR[RP1()].&itype&vtbl.&iproc), RTHIS()
                ENDIF
            ENDIF
        ENDIF
        MOV RP1(), SAVERP1
    ENDM
    ENDIF ;_DEREF
    
    IFNDEF _DEREFI
    _DEREFI MACRO itype:REQ, iproc:REQ, argCount:REQ, argsAndRefs:VARARG
        LOCAL i, ptrstr, typestr, argstr, SAVERP1
        argstr TEXTEQU < >
        i = 0
        FOR dref, <argsAndRefs>
            IF i LT argCount+1
                IF i GT 0
                    argstr CATSTR argstr, <,>, <&dref&>
                ENDIF
            ELSE
                IF(i - argCount) MOD 2 EQ 1
                    ptrstr TEXTEQU <&dref&>
                ELSE
                    typestr TEXTEQU <&dref&>
                        IF(i - argCount) EQ 1
                            % IF(OPATTR(ptrstr)) EQ 0x30
                                % MOV RTHIS(), &ptrstr&
                              ELSE
                                % MOV RTHIS(), @CatStr(<[>, <&ptrstr&>, <].>, <&typestr&>)
                              ENDIF
                        ELSE
                            % MOV RTHIS(), @CatStr(<[>, <&ptrstr&>, <].>, <&typestr&>)
                        ENDIF
                ENDIF
            ENDIF
            i = i + 1
        ENDM
        % IF @SizeStr(<%&argstr&>) GT 3
            argstr SUBSTR argstr, 3
          ENDIF
        IF argCount EQ 0
            argstr TEXTEQU <>
        ENDIF
        .DATA?
        SAVERP1 ISIZE_T ?
        .CODE
        MOV SAVERP1, RP1()
        IF argCount GT 0
            InterfacePtr TEXTEQU <_>
            InterfacePtr CATSTR InterfacePtr, <&itype>, <_>, <&iproc>, <Pto>
            IF(OPATTR(RTHIS())) AND 00010000b
                % IF argCount GT 0
                     MOV RP1(),[RTHIS()]
                     % INVOKE(InterfacePtr PTR[RP1()].&itype&vtbl.&iproc), RTHIS(), &argstr
                  ELSE
                     MOV RP1(),[RTHIS()]
                     % INVOKE(InterfacePtr PTR[RP1()].&itype&vtbl.&iproc), RTHIS()
                  ENDIF
            ELSE
                MOV RP1(),[RTHIS()]
                IF argCount GT 0
                    FOR arg, <argstr>
                        IFIDNI <&arg>, <RTHIS()>
                            .ERR <RTHIS()" is not allowed as a Method parameter with indirect object label">
                        ENDIF
                    ENDM
                    % INVOKE(InterfacePtr PTR[RP1()].&itype&vtbl.&iproc), RTHIS(), &argstr
                ELSE
                    INVOKE(InterfacePtr PTR[RP1()].&itype&vtbl.&iproc), RTHIS()
                ENDIF
            ENDIF
        ELSE
            InterfacePtr TEXTEQU <_>
            InterfacePtr CATSTR InterfacePtr, <&itype>, <_>, <&iproc>, <Pto>
            IF(OPATTR(RTHIS())) AND 00010000b
                IF argCount GT 0
                    MOV RP1(),[RTHIS()]
                    % INVOKE(InterfacePtr PTR[RP1()].&itype&vtbl.&iproc), RTHIS(), &argstr
                ELSE
                    MOV RP1(),[RTHIS()]
                    INVOKE(InterfacePtr PTR[RP1()].&itype&vtbl.&iproc), RTHIS()
                ENDIF
            ELSE
                MOV RP1(),[RTHIS()]
                IF argCount GT 0
                    FOR arg, <argstr>
                        IFIDNI <&arg>, <RTHIS()>
                            .ERR <RTHIS()" is not allowed as a Method parameter with indirect object label">
                        ENDIF
                    ENDM
                    % INVOKE(InterfacePtr PTR[RP1()].&itype&vtbl.&iproc), RTHIS(), &argstr
                ELSE
                    INVOKE(InterfacePtr PTR[RP1()].&itype&vtbl.&iproc), RTHIS()
                ENDIF
            ENDIF
        ENDIF
        MOV RP1(), SAVERP1
        IF @LastReturnType EQ 0
        EXITM <BRET()>
        ELSEIF @LastReturnType EQ 0x40
        EXITM <BRET()>
        ELSEIF @LastReturnType EQ 1
        EXITM <WRET()>
        ELSEIF @LastReturnType EQ 0x41
        EXITM <WRET()>
        ELSEIF @LastReturnType EQ 2
        EXITM <DRET()>
        ELSEIF @LastReturnType EQ 0x42
        EXITM <DRET()>
        ELSEIF @LastReturnType EQ 3
        EXITM <RRET()>
        ELSEIF @LastReturnType EQ 0x43
        EXITM <RRET()>
        ELSEIF @LastReturnType EQ 0xc3
        EXITM <RRET()>
        ELSEIF @LastReturnType EQ 6
        EXITM <XMM0>
        ELSEIF @LastReturnType EQ 7
        EXITM <YMM0>
        ELSEIF @LastReturnType EQ 8
        EXITM <ZMM0>
        ELSEIF @LastReturnType EQ 0x22
        EXITM <XMM0>
        ELSEIF @LastReturnType EQ 0x23
        EXITM <XMM0>
        ELSE
        EXITM <DRET()>
        ENDIF
    ENDM
    ENDIF ;_DEREFI

    IFNDEF _SINVOKE
    _SINVOKE MACRO className:REQ, method:REQ, args:VARARG
        fnex TEXTEQU <_>
        fnex CATSTR fnex, <&className&>
        fnex CATSTR fnex, <_>
        fnex CATSTR fnex, <&method&>
        IFNB <args>
            fnex2 TEXTEQU <INVOKE fnex, &args&>
        ELSE
            fnex2 TEXTEQU <INVOKE fnex>
        ENDIF
        fnex2
    ENDM
    ENDIF ;_SINVOKE

    IFNDEF RAWINTERFACE
    RAWINTERFACE MACRO CName:REQ
        curClass TEXTEQU <CName>
        % __&CName&_size = 0
        @CatStr(CName, < RAWSTRUCT >)
        ptrDefS TEXTEQU <PTR>
        ptrDefS CATSTR ptrDefS, <&curClass&>, < TYPEDEF PTR >, <&curClass&>
        % ptrDefS
    ENDM
    ENDIF ;RAWINTERFACE

    IFNDEF ENDRAWINTERFACE
    ENDRAWINTERFACE MACRO
        curClass ENDS
    ENDM
    ENDIF ;ENDRAWINTERFACE

    IFNDEF _DEREFR
    _DEREFR MACRO dref:REQ, itype:REQ, iproc:REQ, argCount:REQ, argsAndRefs:VARARG
        LOCAL argstr
        argstr TEXTEQU <>
        IFNB <&argsAndRefs&>
            MOV RRET(),dref
            % INVOKE [RRET()].&itype.&iproc, &argsAndRefs
        ELSE
            % INVOKE [RRET()].&itype.&iproc
        ENDIF
    ENDM
    ENDIF ;_DEREFR

    IFNDEF _DEREFRR
    _DEREFRR MACRO dref:REQ, itype:REQ, iproc:REQ, argCount:REQ, argsAndRefs:VARARG
        LOCAL argstr
        argstr TEXTEQU <>
        % INVOKE &dref&.&itype.&iproc, &argsAndRefs
    ENDM
    ENDIF ;_DEREFRR

    IFNDEF STDFUNC
    STDFUNC MACRO method:REQ, retType:REQ, protoDef:VARARG
        LOCAL sz1, sz2
        pDef CATSTR <TYPEDEF PROTO >,<(&retType&) >
        IFNB <protoDef>
            pDef CATSTR pDef, <, >, <&protoDef>
        ENDIF
        sz2 CATSTR <_>, curClass, <_&method>, <Pto>
        % &sz2 &pDef
        % sz1 TYPEDEF PTR &sz2
        % method sz1 0
        % __&curClass&_size = __&curClass&_size + SIZE_T_SIZE
        fnex TEXTEQU <_>
        fnex CATSTR fnex, curClass, <_>, <&method&>, < PROTO >, <(&retType&) >
        IFNB <&protoDef>
            fnex CATSTR fnex, <, >, <&protoDef&>
        ELSE
        ENDIF
        fnex
    ENDM
    ENDIF ;STDFUNC

    IFNDEF ADDRESSOF
    ADDRESSOF MACRO argaddress
        EXITM <ADDR argaddress>
    ENDM
    ENDIF ;ADDRESSOF

    IFNDEF ALIGNOF
    ALIGNOF MACRO argaddress
        EXITM <SIZEOF argaddress>
    ENDM
    ENDIF ;ADDRESSOF


    IFDEF CASEMAPNONE
    IFDEF CDECL
    cdecl TEXTEQU <CDECL>
    ENDIF
    IFDEF CDECLOPT
    cdeclopt TEXTEQU <CDECLOPT>
    ENDIF
    IFDEF VECTORCALLOPT
    vectorcallopt TEXTEQU <VECTORCALLOPT>
    ENDIF
    IFDEF SYSTEMVOPT
    systemvopt TEXTEQU <SYSTEMVOPT>
    ENDIF
    IFDEF REGCALLOPT
    regcallopt TEXTEQU <REGCALLOPT>
    ENDIF
    IFDEF FASTCALLOPT
    fastcallopt TEXTEQU <FASTCALLOPT>
    ENDIF
    IFDEF CALLCONVOPT
    callconvopt TEXTEQU <CALLCONVOPT>
    ENDIF
    IFDEF CALLCONV
    callconv TEXTEQU <CALLCONV>
    ENDIF
    IFDEF STDCALLOPT
    stdcallopt TEXTEQU <CALLCONVOPT>
    ENDIF
    IFDEF THISCALLOPT
    thiscallopt TEXTEQU <CALLCONVOPT>
    ENDIF
    IFDEF SYSCALLOPT
    syscallopt TEXTEQU <SYSCALLOPT>
    ENDIF
    IFDEF DEFINE
    define TEXTEQU <DEFINE>
    ENDIF
    IFDEF DEFINED
    defined TEXTEQU <DEFINED>
    ENDIF
    IFDEF NOTDEFINED
    notdefined TEXTEQU <NOTDEFINED>
    ENDIF
    IFDEF ALIGNSTACK
    alignstack TEXTEQU <ALIGNSTACK>
    ENDIF
    IFDEF ALIGNSIZE_T
    alignsize_t TEXTEQU <ALIGNSIZE_T>
    ENDIF
    IFDEF ALIGNPTR
    alignptr TEXTEQU <ALIGNPTR>
    ENDIF
    IFDEF ALIGNMM
    alignmm TEXTEQU <ALIGNMM>
    ENDIF
    IFDEF ALIGNXMM
    alignxmm TEXTEQU <ALIGNXMM>
    ENDIF
    IFDEF ALIGNYMM
    alignymm TEXTEQU <ALIGNYMM>
    ENDIF
    IFDEF ALIGNZMM
    alignzmm TEXTEQU <ALIGNZMM>
    ENDIF
    IFDEF ALIGNFIELD
    alignfield TEXTEQU <ALIGNFIELD>
    ENDIF
    IFDEF ALIGNSTACKFIELD
    alignstackfield TEXTEQU <ALIGNSTACKFIELD>
    ENDIF
    IFDEF ALIGNSIZE_TFIELD
    alignsize_tfield TEXTEQU <ALIGNSIZE_TFIELD>
    ENDIF
    IFDEF ALIGNPTRFIELD
    alignptrfield TEXTEQU <ALIGNPTRFIELD>
    ENDIF
    IFDEF ALIGNMMFIELD
    alignmmfield TEXTEQU <ALIGNMMFIELD>
    ENDIF
    IFDEF ALIGNXMMFIELD
    alignxmmfield TEXTEQU <ALIGNXMMFIELD>
    ENDIF
    IFDEF ALIGNYMMFIELD
    alignymmfield TEXTEQU <ALIGNYMMFIELD>
    ENDIF
    IFDEF ALIGNZMMFIELD
    alignzmmfield TEXTEQU <ALIGNZMMFIELD>
    ENDIF
    IFDEF ALIGNPROC
    alignproc TEXTEQU <ALIGNPROC>
    ENDIF
    IFDEF ALIGNSTACKPROC
    alignstackproc TEXTEQU <ALIGNSTACKPROC>
    ENDIF
    IFDEF ALIGNSIZE_TPROC
    alignsize_tproc TEXTEQU <ALIGNSIZE_TPROC>
    ENDIF
    IFDEF ALIGNPTRPROC
    alignptrproc TEXTEQU <ALIGNPTRPROC>
    ENDIF
    IFDEF ALIGNMMPROC
    alignmmproc TEXTEQU <ALIGNMMPROC>
    ENDIF
    IFDEF ALIGNXMMPROC
    alignxmmproc TEXTEQU <ALIGNXMMPROC>
    ENDIF
    IFDEF ALIGNYMMPROC
    alignymmproc TEXTEQU <ALIGNYMMPROC>
    ENDIF
    IFDEF ALIGNZMMPROC
    alignzmmproc TEXTEQU <ALIGNZMMPROC>
    ENDIF
    IFDEF ALIGNFIELDPROC
    alignfieldproc TEXTEQU <ALIGNFIELDPROC>
    ENDIF
    IFDEF ALIGNSTACKFIELDPROC
    alignstackfieldproc TEXTEQU <ALIGNSTACKFIELDPROC>
    ENDIF
    IFDEF ALIGNSIZE_TFIELDPROC
    alignsize_tfieldproc TEXTEQU <ALIGNSIZE_TFIELDPROC>
    ENDIF
    IFDEF ALIGNPTRFIELDPROC
    alignptrfieldproc TEXTEQU <ALIGNPTRFIELDPROC>
    ENDIF
    IFDEF ALIGNMMFIELDPROC
    alignmmfieldproc TEXTEQU <ALIGNMMFIELDPROC>
    ENDIF
    IFDEF ALIGNXMMFIELDPROC
    alignxmmfieldproc TEXTEQU <ALIGNXMMFIELDPROC>
    ENDIF
    IFDEF ALIGNYMMFIELDPROC
    alignymmfieldproc TEXTEQU <ALIGNYMMFIELDPROC>
    ENDIF
    IFDEF ALIGNZMMFIELDPROC
    alignzmmfieldproc TEXTEQU <ALIGNZMMFIELDPROC>
    ENDIF
    IFDEF PROCSTART
    procstart TEXTEQU <PROCSTART>
    ENDIF
    IFDEF PROCEND
    procend TEXTEQU <PROCEND>
    ENDIF
    
    IFDEF SHUFFLE4
    shuffle4 TEXTEQU <SHUFFLE4>
    ENDIF
    IFDEF SHUFFLER4
    shuffler4 TEXTEQU <SHUFFLER4>
    ENDIF
    IFDEF SHUFFLE2
    shuffle2 TEXTEQU <SHUFFLE2>
    ENDIF
    IFDEF SHUFFLER2
    shuffler2 TEXTEQU <SHUFFLER2>
    ENDIF
    
    IFDEF V64CI
    v64ci TEXTEQU <V64CI>
    ENDIF
    IFDEF V64CI64
    v64ci64 TEXTEQU <V64CI64>
    ENDIF
    IFDEF V32CI
    v32ci TEXTEQU <V32CI>
    ENDIF
    IFDEF V32CI32
    v32ci32 TEXTEQU <V32CI32>
    ENDIF
    IFDEF V16CI
    v16ci TEXTEQU <V16CI>
    ENDIF
    IFDEF V16CI16
    v16ci16 TEXTEQU <V16CI16>
    ENDIF
    IFDEF V8CI
    v8ci TEXTEQU <V8CI>
    ENDIF
    IFDEF V8CI8
    v8ci8 TEXTEQU <V8CI8>
    ENDIF
    IFDEF V4CI
    v4ci TEXTEQU <V4CI>
    ENDIF
    IFDEF V4CI4
    v4ci4 TEXTEQU <V4CI4>
    ENDIF
    IFDEF V2CI
    v2ci TEXTEQU <V2CI>
    ENDIF
    IFDEF V2CI2
    v2ci2 TEXTEQU <V2CI2>
    ENDIF
    IFDEF VV64CI
    vv64ci TEXTEQU <VV64CI>
    ENDIF
    IFDEF VV64CI64
    vv64ci64 TEXTEQU <VV64CI64>
    ENDIF
    IFDEF VV32CI
    vv32ci TEXTEQU <VV32CI>
    ENDIF
    IFDEF VV32CI32
    vv32ci32 TEXTEQU <VV32CI32>
    ENDIF
    IFDEF VV16CI
    vv16ci TEXTEQU <VV16CI>
    ENDIF
    IFDEF VV16CI16
    vv16ci16 TEXTEQU <VV16CI16>
    ENDIF
    IFDEF VV8CI
    vv8ci TEXTEQU <VV8CI>
    ENDIF
    IFDEF VV8CI8
    vv8ci8 TEXTEQU <VV8CI8>
    ENDIF
    IFDEF VV4CI
    vv4ci TEXTEQU <VV4CI>
    ENDIF
    IFDEF VV4CI4
    vv4ci4 TEXTEQU <VV4CI4>
    ENDIF
    IFDEF VV2CI
    vv2ci TEXTEQU <VV2CI>
    ENDIF
    IFDEF VV2CI2
    vv2ci2 TEXTEQU <VV2CI2>
    ENDIF
    IFDEF V1CI
    v1ci TEXTEQU <V1CI>
    ENDIF
    
    IFDEF NOTMASK128
    notmask128 TEXTEQU <NOTMASK128>
    ENDIF
    IFDEF GETMASK128
    getmask128 TEXTEQU <GETMASK128>
    ENDIF
    IFDEF REGS15STORAGE
    regs15storage TEXTEQU <REGS15STORAGE>
    ENDIF
    IFDEF MOV64
    mov64 TEXTEQU <MOV64>
    ENDIF
    IFDEF MOV128
    mov128 TEXTEQU <MOV128>
    ENDIF
    IFDEF MOVXMMR128
    movxmmr128 TEXTEQU <MOVXMMR128>
    ENDIF
    IFDEF SLXMMR
    slxmmr TEXTEQU <SLXMMR>
    ENDIF
    IFDEF SHIFTLEFT128
    shiftleft128 TEXTEQU <SHIFTLEFT128>
    ENDIF
    IFDEF SRXMMR
    srxmmr TEXTEQU <SRXMMR>
    ENDIF
    IFDEF SHIFTRIGHT128
    shiftright128 TEXTEQU <SHIFTRIGHT128>
    ENDIF
    IFDEF FP4
    fp4 TEXTEQU <FP4>
    ENDIF
    IFDEF FP8
    fp8 TEXTEQU <FP8>
    ENDIF
    IFDEF FP10
    fp10 TEXTEQU <FP10>
    ENDIF
    IFDEF LOADSS
    loadss TEXTEQU <LOADSS>
    ENDIF
    IFDEF LOAD1PS
    load1ps TEXTEQU <LOAD1PS>
    ENDIF
    IFDEF LOADPS
    loadps TEXTEQU <LOADPS>
    ENDIF
    IFDEF LOADSD
    loadsd TEXTEQU <LOADSD>
    ENDIF
    IFDEF LOAD1PD
    load1pd TEXTEQU <LOAD1PD>
    ENDIF
    IFDEF LOADPD
    loadpd TEXTEQU <LOADPD>
    ENDIF
    IFDEF ALIGNADDR
    alignaddr TEXTEQU <ALIGNADDR>
    ENDIF
    IFDEF CSTR
    cstr TEXTEQU <CSTR>
    ENDIF
    IFDEF WSTR
    wstr TEXTEQU <WSTR>
    ENDIF
    IFDEF CHR$
    chr$ TEXTEQU <CHR$>
    ENDIF
    IFDEF TCHR
    tchr TEXTEQU <TCHR>
    ENDIF
    IFDEF REPARG
    reparg TEXTEQU <REPARG>
    ENDIF
    IFDEF REPARGV
    repargv TEXTEQU <REPARGV>
    ENDIF
    IFDEF EXPAND_PREFIX
    expand_prefix TEXTEQU <EXPAND_PREFIX>
    ENDIF
    IFDEF RV
    rv TEXTEQU <RV>
    ENDIF
    IFDEF TSTARG
    tstarg TEXTEQU <TSTARG>
    ENDIF
    IFDEF NUM2STR
    num2str TEXTEQU <NUM2STR>
    ENDIF
    IFDEF ARGCOUNT
    argcount TEXTEQU <ARGCOUNT>
    ENDIF
    IFDEF GETARG
    getarg TEXTEQU <GETARG>
    ENDIF
    IFDEF ARGREV
    argrev TEXTEQU <ARGREV>
    ENDIF
    IFDEF MEMALLOC
    memalloc TEXTEQU <MEMALLOC>
    ENDIF
    IFDEF MEMFREE
    memfree TEXTEQU <MEMFREE>
    ENDIF
    IFDEF LOADMSS
    loadmss TEXTEQU <LOADMSS>
    ENDIF
    IFDEF LOADMSD
    loadmss TEXTEQU <LOADMSD>
    ENDIF
    IFDEF RET_TYPE
    ret_type TEXTEQU <RET_TYPE>
    ENDIF
    IFDEF UINVOKE
    uinvoke TEXTEQU <UINVOKE>
    ENDIF
    IFDEF ASFLOAT
    asfloat TEXTEQU <ASFLOAT>
    ENDIF
    IFDEF ASDOUBLE
    asdouble TEXTEQU <ASDOUBLE>
    ENDIF
    IFDEF R4P
    r4p TEXTEQU <R4P>
    ENDIF
    IFDEF R8P
    r8p TEXTEQU <R8P>
    ENDIF
    IFDEF ARGINVOKE
    arginvoke TEXTEQU <ARGINVOKE>
    ENDIF
    IFDEF CVIRTUAL
    cvirtual TEXTEQU <CVIRTUAL>
    ENDIF
    IFDEF COMINTERFACE
    cominterface TEXTEQU <COMINTERFACE>
    ENDIF
    IFDEF ENDMETHODS
    endmethods TEXTEQU <ENDMETHODS>
    ENDIF
    IFDEF ENDCOMINTERFACE
    endcominterface TEXTEQU <ENDCOMINTERFACE>
    ENDIF
    IFDEF _VINVOKE
    _vinvoke TEXTEQU <_VINVOKE>
    ENDIF
    IFDEF _V
    _v TEXTEQU <_V>
    ENDIF
    IFDEF _ARRAY
    _array TEXTEQU <_ARRAY>
    ENDIF
    IFDEF _DELETEARRAY
    _deletearray TEXTEQU <_DELETEARRAY>
    ENDIF
    IFDEF OINTERFACE
    ointerface TEXTEQU <OINTERFACE>
    ENDIF
    IFDEF ENDOINTERFACE
    endointerface TEXTEQU <ENDOINTERFACE>
    ENDIF
    IFDEF CLASS
    class TEXTEQU <CLASS>
    ENDIF
    IFDEF ENDCLASS
    endclass TEXTEQU <ENDCLASS>
    ENDIF
    IFDEF CMETHOD
    cmethod TEXTEQU <CMETHOD>
    ENDIF
    IFDEF METHOD
    method TEXTEQU <METHOD>
    ENDIF
    IFDEF STATICMETHOD
    staticmethod TEXTEQU <STATICMETHOD>
    ENDIF
    IFDEF VECMETHOD
    vecmethod TEXTEQU <VECMETHOD>
    ENDIF
    IFDEF STATICVECMETHOD
    staticvecmethod TEXTEQU <STATICVECMETHOD>
    ENDIF
    IFDEF ENDMETHOD
    endmethod TEXTEQU <ENDMETHOD>
    ENDIF
    IFDEF _DECLARE
    _declare TEXTEQU <_DECLARE>
    ENDIF
    IFDEF _STATICREF
    _staticref TEXTEQU <_STATICREF>
    ENDIF
    IFDEF _NEW
    _new TEXTEQU <_NEW>
    ENDIF
    IFDEF _RBXNEW
    _rbxnew TEXTEQU <_RBXNEW>
    ENDIF
    IFDEF _ITEM
    _item TEXTEQU <_ITEM>
    ENDIF
    IFDEF _ITEMR
    _itemr TEXTEQU <_ITEMR>
    ENDIF
    IFDEF _INVOKE
    _invoke TEXTEQU <_INVOKE>
    ENDIF
    IFDEF _I
    _i TEXTEQU <_I>
    ENDIF
    IFDEF _STATIC
    _static TEXTEQU <_STATIC>
    ENDIF
    IFDEF _DELETE
    _delete TEXTEQU <_DELETE>
    ENDIF
    IFDEF CSTATIC
    cstatic TEXTEQU <CSTATIC>
    ENDIF
    IFDEF _DEREF
    _deref TEXTEQU <_DEREF>
    ENDIF
    IFDEF _DEREFI
    _derefi TEXTEQU <_DEREFI>
    ENDIF
    IFDEF _SINVOKE
    _sinvoke TEXTEQU <_SINVOKE>
    ENDIF
    IFDEF RAWINTERFACE
    rawinterface TEXTEQU <RAWINTERFACE>
    ENDIF
    IFDEF ENDRAWINTERFACE
    endrawinterface TEXTEQU <ENDRAWINTERFACE>
    ENDIF
    IFDEF _DEREFR
    _derefr TEXTEQU <_DEREFR>
    ENDIF
    IFDEF _DEREFRR
    _derefrr TEXTEQU <_DEREFRR>
    ENDIF
    IFDEF STDFUNC
    stdfunc TEXTEQU <STDFUNC>
    ENDIF
    IFDEF ADDRESSOF
    addressof TEXTEQU <ADDRESSOF>
    ENDIF
    IFDEF ALIGNOF
    alignof TEXTEQU <ALIGNOF>
    ENDIF

    ENDIF ;CASEMAPNONE

    ENDIF ;WITHMACROLIB

    ENDIF    ; MACROS_INC
