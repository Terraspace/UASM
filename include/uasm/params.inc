
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

    IFNDEF PARAMS_INC
    PARAMS_INC EQU 1
    
    IFDEF WITHMACROLIB

    IFNDEF MACROLIB_INC
    .ERR <"PARAMS_INC must be included by MACROLIB_INC">
    ENDIF

    IFNDEF DEFINES_INC
    .ERR <"PARAMS_INC requires DEFINES_INC">
    ENDIF
    
    IFNDEF X86ORX64
    .ERR <"PARAMS_INC requires one x86 or x64 platform type">
    ENDIF
    
    ;
    ; GRP uses case:  GRP(reg-pos,regsize)
    ;
    IFNDEF GRP
    GRP MACRO num:REQ, regsize:REQ
        LOCAL cnt, arg
        rptxt TEXTEQU <-1>
        IF num LT 0
            .ERR <num "That don't work. Please use a decimal number as argument for argument's passing from 0 to 16.">
            EXITM <rptxt>
        ENDIF
        IF num GE 16
            .ERR <num "!!!UNIMPLEMENTED!!! Please kindle ask in masm32 dot com sub-forum UASM <http://masm32.com/board/index.php?board=51.0> for aditional Parameters implementation">
            EXITM <rptxt>
        ENDIF
        IF regsize LT BYTE_SIZE
            .ERR <regsize "That don't work. No data type is know with less than BYTE_SIZE." >
            EXITM <rptxt>
        ENDIF
        IF regsize EQ 3 OR regsize EQ 5 OR regsize EQ 6 OR regsize EQ 7
            .ERR <regsize "That don't work. Unknown data type exist with this size. Please use power off 2 for register size.">
            EXITM <rptxt>
        ENDIF
        IF regsize GT SIZE_T_SIZE
            .ERR <regsize "That don't work. Please use good know data bytes sizes from BYTE_SIZE to DWORD_SIZE in 32bits from BYTE_SIZE TO QWORD_SIZE in 64bits.">
            EXITM <rptxt>
        ENDIF
        IF regsize EQ BYTE_SIZE
            IFDEF __WIN64__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<AL,CL,DL,DIL,SIL,R8B,R9B,R11B,R12B,R14B,R15B,SPL,SPL,SPL,SPL,SPL>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<CL,DL,R8B,R9B,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__WIN64__
            IFDEF __UNIX64__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<AL,CL,DL,DIL,SIL,R8B,R9B,R10B,R11B,R12B,R14B,R15B,SPL,SPL,SPL,SPL>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSEIF @LangType EQ LANG_SYSCALL
                    cnt = -1
                    FOR arg,<DIL,SIL,DL,R10B,R8B,R9B,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<DIL,SIL,DL,CL,R8B,R9B,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__UNIX64__
            IFDEF __WIN32__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<CL,DL,DIL,SIL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSEIF @LangType EQ LANG_FASTSCALL OR @LangType EQ LANG_VECTORCALL
                    cnt = -1
                    FOR arg,<CL,DL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSEIF @LangType EQ LANG_THISCALL
                    cnt = -1
                    FOR arg,<CL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__WIN32__
            IFDEF __UNIX32__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<AL,CL,DL,DIL,SIL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL,SPL>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__UNIX32__
            EXITM
        ELSEIF regsize EQ WORD_SIZE
            IFDEF __WIN64__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<AX,CX,DX,DI,SI,R8W,R9W,R11W,R12W,R14W,R15W,SP,SP,SP,SP,SP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<CX,DX,R8W,R9W,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__WIN64__
            IFDEF __UNIX64__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<AX,CX,DX,DI,SI,R8W,R9W,R10W,R11W,R12W,R14W,R15W,SP,SP,SP,SP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSEIF @LangType EQ LANG_SYSCALL
                    cnt = -1
                    FOR arg,<DI,SI,DX,R10W,R8W,R9W,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<DI,SI,DX,CX,R8W,R9W,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__UNIX64__
            IFDEF __WIN32__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<CX,DX,DI,SI,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSEIF @LangType EQ LANG_FASTSCALL OR @LangType EQ LANG_VECTORCALL
                    cnt = -1
                    FOR arg,<CX,DX,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSEIF @LangType EQ LANG_THISCALL
                    cnt = -1
                    FOR arg,<CX,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__WIN32__
            IFDEF __UNIX32__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<AX,CX,DX,DI,SI,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP,SP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__UNIX32__
            EXITM
        ELSEIF regsize EQ DWORD_SIZE
            IFDEF __WIN64__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<EAX,ECX,EDX,EDI,ESI,R8D,R9D,R11D,R12D,R14D,R15D,ESP,ESP,ESP,ESP,ESP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<ECX,EDX,R8D,R9D,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__WIN64__
            IFDEF __UNIX64__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<EAX,ECX,EDX,EDI,ESI,R8D,R9D,R10D,R11D,R12D,R14D,R15D,ESP,ESP,ESP,ESP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSEIF @LangType EQ LANG_SYSCALL
                    cnt = -1
                    FOR arg,<EDI,ESI,EDX,R10D,R8D,R9D,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<EDI,ESI,EDX,ECX,R8D,R9D,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__UNIX64__
            IFDEF __WIN32__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<ECX,EDX,EDI,ESI,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSEIF @LangType EQ LANG_FASTSCALL OR @LangType EQ LANG_VECTORCALL
                    cnt = -1
                    FOR arg,<ECX,EDX,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSEIF @LangType EQ LANG_THISCALL
                    cnt = -1
                    FOR arg,<ECX,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__WIN32__
            IFDEF __UNIX32__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<EAX,ECX,EDX,EDI,ESI,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP,ESP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__UNIX32__
            EXITM
        ELSEIF regsize EQ QWORD_SIZE
            IFDEF __WIN64__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<RAX,RCX,RDX,RDI,RSI,R8,R9,R11,R12,R14,R15,RSP,RSP,RSP,RSP,RSP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<RCX,RDX,R8,R9,RSP,RSP,RSP,RSP,RSP,RSP,RSP,RSP,RSP,RSP,RSP,RSP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__WIN64__
            IFDEF __UNIX64__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<RAX,RCX,RDX,RDI,RSI,R8,R9,R10,R11,R12,R14,R15,RSP,RSP,RSP,RSP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSEIF @LangType EQ LANG_SYSCALL
                    cnt = -1
                    FOR arg,<RDI,RSI,RDX,R10,R8,R9,RSP,RSP,RSP,RSP,RSP,RSP,RSP,RSP,RSP,RSP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<RDI,RSI,RDX,RCX,R8,R9,RSP,RSP,RSP,RSP,RSP,RSP,RSP,RSP,RSP,RSP>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__UNIX64__
        ENDIF ;; regsize EQ QWORD_SIZE
        EXITM <rptxt>
    ENDM
    ENDIF ;GRP
    
    ;
    ; PRP uses case:  PRP(reg-pos,regsize,ptr-offset)
    ;
    IFNDEF PRP
    PRP MACRO num:REQ, regsize:REQ, pf:REQ
        LOCAL cnt, arg
        rptxt TEXTEQU <-1>
        IF num LT 0
            .ERR <num "That don't work. Please use a decimal number as argument for argument's passing from 0 to 16.">
            EXITM <rptxt>
        ENDIF
        IF num GE 16
            .ERR <num "!!!UNIMPLEMENTED!!! Please kindle ask in masm32 dot com sub-forum UASM <http://masm32.com/board/index.php?board=51.0> for aditional Parameters implementation">
            EXITM <rptxt>
        ENDIF
        IF regsize LT BYTE_SIZE
            .ERR <regsize "That don't work. No data type is know with less than BYTE_SIZE." >
            EXITM <rptxt>
        ENDIF
        IF regsize EQ 3 OR regsize EQ 5 OR regsize EQ 6 OR regsize EQ 7
            .ERR <regsize "That don't work. Unknown data type exist with this size. Please use power off 2 for register size.">
            EXITM <rptxt>
        ENDIF
        IF regsize GT SIZE_T_SIZE
            .ERR <regsize "That don't work. Please use good know data bytes sizes from BYTE_SIZE to DWORD_SIZE in 32bits from BYTE_SIZE TO QWORD_SIZE in 64bits.">
            EXITM <rptxt>
        ENDIF
        IF regsize EQ BYTE_SIZE
            IFDEF __WIN64__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<[AL+pf],[CL+pf],[DL+pf],[DIL+pf],[SIL+pf],[R8B+pf],[R9B+pf],[R11B+pf],[R12B+pf],[R14B+pf],[R15B+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<[CL+pf],[DL+pf],[R8B+pf],[R9B+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__WIN64__
            IFDEF __UNIX64__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<[AL+pf],[CL+pf],[DL+pf],[DIL+pf],[SIL+pf],[R8B+pf],[R9B+pf],[SPL+pf],[R11B+pf],[R12B+pf],[R14B+pf],[R15B+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSEIF @LangType EQ LANG_SYSCALL
                    cnt = -1
                    FOR arg,<[DIL+pf],[SIL+pf],[DL+pf],[R10B+pf],[R8B+pf],[R9B+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<[DIL+pf],[SIL+pf],[DL+pf],[CL+pf],[R8B+pf],[R9B+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__UNIX64__
            IFDEF __WIN32__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<[CL+pf],[DL+pf],[DIL+pf],[SIL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSEIF @LangType EQ LANG_FASTSCALL OR @LangType EQ LANG_VECTORCALL
                    cnt = -1
                    FOR arg,<[CL+pf],[DL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSEIF @LangType EQ LANG_THISCALL
                    cnt = -1
                    FOR arg,<[CL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__WIN32__
            IFDEF __UNIX32__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<[AL+pf],[CL+pf],[DL+pf],[DIL+pf],[SIL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf],[SPL+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__UNIX32__
            EXITM
        ELSEIF regsize EQ WORD_SIZE
            IFDEF __WIN64__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<[AX+pf],[CX+pf],[DX+pf],[DI+pf],[SI+pf],[R8W+pf],[R9W+pf],[R11W+pf],[R12W+pf],[R14W+pf],[R15W+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<[CX+pf],[DX+pf],[R8W+pf],[R9W+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__WIN64__
            IFDEF __UNIX64__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<[AX+pf],[CX+pf],[DX+pf],[DI+pf],[SI+pf],[R8W+pf],[R9W+pf],[R10W+pf],[R11W+pf],[R12W+pf],[R14W+pf],[R15W+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSEIF @LangType EQ LANG_SYSCALL
                    cnt = -1
                    FOR arg,<[DI+pf],[SI+pf],[DX+pf],[R10W+pf],[R8W+pf],[R9W+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<[DI+pf],[SI+pf],[DX+pf],[CX+pf],[R8W+pf],[R9W+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__UNIX64__
            IFDEF __WIN32__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<[CX+pf],[DX+pf],[DI+pf],[SI+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSEIF @LangType EQ LANG_FASTSCALL OR @LangType EQ LANG_VECTORCALL
                    cnt = -1
                    FOR arg,<[CX+pf],[DX+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSEIF @LangType EQ LANG_THISCALL
                    cnt = -1
                    FOR arg,<[CX+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__WIN32__
            IFDEF __UNIX32__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<[AX+pf],[CX+pf],[DX+pf],[DI+pf],[SI+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__UNIX32__
            EXITM
        ELSEIF regsize EQ DWORD_SIZE
            IFDEF __WIN64__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<[EAX+pf],[ECX+pf],[EDX+pf],[EDI+pf],[ESI+pf],[R8D+pf],[R9D+pf],[R11D+pf],[R12D+pf],[R14D+pf],[R15D+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<[ECX+pf],[EDX+pf],[R8D+pf],[R9D+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__WIN64__
            IFDEF __UNIX64__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<[EAX+pf],[ECX+pf],[EDX+pf],[EDI+pf],[ESI+pf],[R8D+pf],[R9D+pf],[R10D+pf],[R11D+pf],[R12D+pf],[R14D+pf],[R15D+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSEIF @LangType EQ LANG_SYSCALL
                    cnt = -1
                    FOR arg,<[EDI+pf],[ESI+pf],[EDX+pf],[R10D+pf],[R8D+pf],[R9D+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<[EDI+pf],[ESI+pf],[EDX+pf],[ECX+pf],[R8D+pf],[R9D+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__UNIX64__
            IFDEF __WIN32__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<[ECX+pf],[EDX+pf],[EDI+pf],[ESI+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSEIF @LangType EQ LANG_FASTSCALL OR @LangType EQ LANG_VECTORCALL
                    cnt = -1
                    FOR arg,<[ECX+pf],[EDX+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSEIF @LangType EQ LANG_THISCALL
                    cnt = -1
                    FOR arg,<[ECX+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__WIN32__
            IFDEF __UNIX32__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<[EAX+pf],[ECX+pf],[EDX+pf],[EDI+pf],[ESI+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf],[ESP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__UNIX32__
            EXITM
        ELSEIF regsize EQ QWORD_SIZE
            IFDEF __WIN64__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<[RAX+pf],[RCX+pf],[RDX+pf],[RDI+pf],[RSI+pf],[R8+pf],[R9+pf],[R11+pf],[R12+pf],[R14+pf],[R15+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<[RCX+pf],[RDX+pf],[R8+pf],[R9+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__WIN64__
            IFDEF __UNIX64__
                IF @LangType EQ LANG_REGCALL
                    cnt = -1
                    FOR arg,<[RAX+pf],[RCX+pf],[RDX+pf],[RDI+pf],[RSI+pf],[R8+pf],[R9+pf],[R10+pf],[R11+pf],[R12+pf],[R14+pf],[R15+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSEIF @LangType EQ LANG_SYSCALL
                    cnt = -1
                    FOR arg,<[RDI+pf],[RSI+pf],[RDX+pf],[R10+pf],[R8+pf],[R9+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ELSE
                    cnt = -1
                    FOR arg,<[RDI+pf],[RSI+pf],[RDX+pf],[RCX+pf],[R8+pf],[R9+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf],[RSP+pf]>
                        cnt = cnt + 1
                        IF cnt EQ num
                            rptxt TEXTEQU <arg>
                            EXITM
                        ENDIF
                    ENDM
                ENDIF ;;@LangType
            ENDIF ;;__UNIX64__
        ENDIF ;; regsize EQ QWORD_SIZE
        EXITM <rptxt>
    ENDM
    ENDIF ;PRP
    
    IFNDEF RRET
    RRET MACRO
        IFDEF __X64__
            EXITM <RAX>
        ENDIF
        IFDEF __X32__
            EXITM <EAX>
        ENDIF
    ENDM
    ENDIF ;RRET
    
    IFNDEF RRETURN
    RRETURN MACRO
        IFDEF __X64__
            EXITM <RAX>
        ENDIF
        IFDEF __X32__
            EXITM <EAX>
        ENDIF
    ENDM
    ENDIF ;RRETURN
    
    IFNDEF RSIDX
    RSIDX MACRO
        IFDEF __X64__
            EXITM <RSI>
        ENDIF
        IFDEF __X32__
            EXITM <ESI>
        ENDIF
    ENDM
    ENDIF ;RSIDX
    
    IFNDEF RDIDX
    RDIDX MACRO
        IFDEF __X64__
            EXITM <RDI>
        ENDIF
        IFDEF __X32__
            EXITM <EDI>
        ENDIF
    ENDM
    ENDIF ;RDIDX
    
    IFNDEF RBPTR
    RBPTR MACRO
        IFDEF __X64__
            EXITM <RBP>
        ENDIF
        IFDEF __X32__
            EXITM <EBP>
        ENDIF
    ENDM
    ENDIF ;RBPTR
    
    IFNDEF RSPTR
    RSPTR MACRO
        IFDEF __X64__
            EXITM <RSP>
        ENDIF
        IFDEF __X32__
            EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;RSPTR
    
    IFNDEF RBASE
    RBASE MACRO
        IFDEF __X64__
            EXITM <RBX>
        ENDIF
        IFDEF __X32__
            EXITM <EBX>
        ENDIF
    ENDM
    ENDIF ;RBASE
    
    IFNDEF RCOUNT
    RCOUNT MACRO
        IFDEF __X64__
            EXITM <RCX>
        ENDIF
        IFDEF __X32__
            EXITM <ECX>
        ENDIF
    ENDM
    ENDIF ;RCOUNT
    
    IFNDEF RTHIS
    RTHIS MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <RAX>
            ELSE
                EXITM <RCX>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <RAX>
            ELSE
                EXITM <RDI>
            ENDIF
        ENDIF
        IFDEF __WIN32__
            IF @LangType EQ LANG_FASTSCALL OR @LangType EQ LANG_VECTORCALL OR @LangType EQ LANG_REGCALL OR @LangType EQ LANG_THISCALL
                EXITM <ECX>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <EAX>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;RTHIS
    
    IFNDEF RP0
    RP0 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <RAX>
            ELSE
                EXITM <RCX>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <RAX>
            ELSE
                EXITM <RDI>
            ENDIF
        ENDIF
        IFDEF __WIN32__
            IF @LangType EQ LANG_FASTSCALL OR @LangType EQ LANG_VECTORCALL OR @LangType EQ LANG_REGCALL OR @LangType EQ LANG_THISCALL
                EXITM <ECX>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <EAX>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;RP0

    IFNDEF RP1
    RP1 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <RCX>
            ELSE
                EXITM <RDX>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <RCX>
            ELSE
                EXITM <RSI>
            ENDIF
        ENDIF
        IFDEF __WIN32__
            IF @LangType EQ LANG_FASTSCALL OR @LangType EQ LANG_VECTORCALL OR @LangType EQ LANG_REGCALL
                EXITM <EDX>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <ECX>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;RP1
    
    IFNDEF RP2
    RP2 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <RDX>
            ELSE
                EXITM <R8>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
                EXITM <RDX>
        ENDIF
        IFDEF __WIN32__
            IF @LangType EQ LANG_REGCALL
                EXITM <EDI>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <EDX>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;RP2
    
    IFNDEF RP3
    RP3 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <RDI>
            ELSE
                EXITM <R9>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <RDI>
            ELSEIF @LangType EQ LANG_SYSCALL
                EXITM <R10>
            ELSE
                EXITM <RCX>
            ENDIF
        ENDIF
        IFDEF __WIN32__
            IF @LangType EQ LANG_REGCALL
                EXITM <ESI>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <EDI>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;RP3
    
    IFNDEF RP4
    RP4 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <RSI>
            ELSE
                EXITM <RSP>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <RSI>
            ELSE
                EXITM <R8>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <ESI>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;RP4
    
    IFNDEF RP5
    RP5 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R8>
            ELSE
                EXITM <RSP>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R8>
            ELSE
                EXITM <R9>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;RP5
    
    IFNDEF RP6
    RP6 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R9>
            ELSE
                EXITM <RSP>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R9>
            ELSE
                EXITM <RSP>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;RP6
    
    IFNDEF RP7
    RP7 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R11>
            ELSE
                EXITM <RSP>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R10>
            ELSE
                EXITM <RSP>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;RP7
    
    IFNDEF RP8
    RP8 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R12>
            ELSE
                EXITM <RSP>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R11>
            ELSE
                EXITM <RSP>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;RP8
    
    IFNDEF RP9
    RP9 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R14>
            ELSE
                EXITM <RSP>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R12>
            ELSE
                EXITM <RSP>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;RP9
    
    IFNDEF RP10
    RP10 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R15>
            ELSE
                EXITM <RSP>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R14>
            ELSE
                EXITM <RSP>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;RP10
    
    IFNDEF RP11
    RP11 MACRO
        IFDEF __WIN64__
                EXITM <RSP>
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R15>
            ELSE
                EXITM <RSP>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;RP11
    
    IFNDEF RP12
    RP12 MACRO
        IFDEF __WIN64__
                EXITM <RSP>
        ENDIF
        IFDEF __UNIX64__
                EXITM <RSP>
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;RP12
    
    IFNDEF RP13
    RP13 MACRO
        IFDEF __WIN64__
                EXITM <RSP>
        ENDIF
        IFDEF __UNIX64__
                EXITM <RSP>
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;RP13
    
    IFNDEF RP14
    RP14 MACRO
        IFDEF __WIN64__
                EXITM <RSP>
        ENDIF
        IFDEF __UNIX64__
                EXITM <RSP>
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;RP14
    
    IFNDEF RP15
    RP15 MACRO
        IFDEF __WIN64__
                EXITM <RSP>
        ENDIF
        IFDEF __UNIX64__
                EXITM <RSP>
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;RP15
    
    IFNDEF DRET
    DRET MACRO
            EXITM <EAX>
    ENDM
    ENDIF ;DRET
    
    IFNDEF DRETURN
    DRETURN MACRO
            EXITM <EAX>
    ENDM
    ENDIF ;DRETURN
    
    IFNDEF DSIDX
    DSIDX MACRO
            EXITM <ESI>
    ENDM
    ENDIF ;DSIDX
    
    IFNDEF DDIDX
    DDIDX MACRO
            EXITM <EDI>
    ENDM
    ENDIF ;DDIDX
    
    IFNDEF DBPTR
    DBPTR MACRO
            EXITM <EBP>
    ENDM
    ENDIF ;DBPTR
    
    IFNDEF DSPTR
    DSPTR MACRO
            EXITM <ESP>
    ENDM
    ENDIF ;DSPTR
    
    IFNDEF DBASE
    DBASE MACRO
            EXITM <EBX>
    ENDM
    ENDIF ;DBASE
    
    IFNDEF DCOUNT
    DCOUNT MACRO
            EXITM <ECX>
    ENDM
    ENDIF ;DCOUNT
    
    IFNDEF DTHIS
    DTHIS MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <EAX>
            ELSE
                EXITM <ECX>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <EAX>
            ELSE
                EXITM <EDI>
            ENDIF
        ENDIF
        IFDEF __WIN32__
            IF @LangType EQ LANG_FASTSCALL OR @LangType EQ LANG_VECTORCALL OR @LangType EQ LANG_REGCALL OR @LangType EQ LANG_THISCALL
                EXITM <ECX>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <EAX>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;DTHIS
    
    IFNDEF DP0
    DP0 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <EAX>
            ELSE
                EXITM <ECX>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <EAX>
            ELSE
                EXITM <EDI>
            ENDIF
        ENDIF
        IFDEF __WIN32__
            IF @LangType EQ LANG_FASTSCALL OR @LangType EQ LANG_VECTORCALL OR @LangType EQ LANG_REGCALL OR @LangType EQ LANG_THISCALL
                EXITM <ECX>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <EAX>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;DP0

    IFNDEF DP1
    DP1 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <ECX>
            ELSE
                EXITM <EDX>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <ECX>
            ELSE
                EXITM <ESI>
            ENDIF
        ENDIF
        IFDEF __WIN32__
            IF @LangType EQ LANG_FASTSCALL OR @LangType EQ LANG_VECTORCALL OR @LangType EQ LANG_REGCALL
                EXITM <EDX>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <ECX>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;DP1
    
    IFNDEF DP2
    DP2 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <EDX>
            ELSE
                EXITM <R8D>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
                EXITM <EDX>
        ENDIF
        IFDEF __WIN32__
            IF @LangType EQ LANG_REGCALL
                EXITM <EDI>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <EDX>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;DP2
    
    IFNDEF DP3
    DP3 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <EDI>
            ELSE
                EXITM <R9D>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <EDI>
            ELSEIF @LangType EQ LANG_SYSCALL
                EXITM <R10D>
            ELSE
                EXITM <ECX>
            ENDIF
        ENDIF
        IFDEF __WIN32__
            IF @LangType EQ LANG_REGCALL
                EXITM <ESI>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <EDI>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;DP3
    
    IFNDEF DP4
    DP4 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <ESI>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <ESI>
            ELSE
                EXITM <R8D>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <ESI>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;DP4
    
    IFNDEF DP5
    DP5 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R8D>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R8D>
            ELSE
                EXITM <R9D>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;DP5
    
    IFNDEF DP6
    DP6 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R9D>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R9D>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;DP6
    
    IFNDEF DP7
    DP7 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R11D>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R10D>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;DP7
    
    IFNDEF DP8
    DP8 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R12D>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R11D>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;DP8
    
    IFNDEF DP9
    DP9 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R14D>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R12D>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;DP9
    
    IFNDEF DP10
    DP10 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R15D>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R14D>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;DP10
    
    IFNDEF DP11
    DP11 MACRO
        IFDEF __WIN64__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R15D>
            ELSE
                EXITM <ESP>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;DP11
    
    IFNDEF DP12
    DP12 MACRO
        IFDEF __WIN64__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX64__
                EXITM <ESP>
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;DP12
    
    IFNDEF DP13
    DP13 MACRO
        IFDEF __WIN64__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX64__
                EXITM <ESP>
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;DP13
    
    IFNDEF DP14
    DP14 MACRO
        IFDEF __WIN64__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX64__
                EXITM <ESP>
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;DP14
    
    IFNDEF DP15
    DP15 MACRO
        IFDEF __WIN64__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX64__
                EXITM <ESP>
        ENDIF
        IFDEF __WIN32__
                EXITM <ESP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <ESP>
        ENDIF
    ENDM
    ENDIF ;DP15
    
    IFNDEF WRET
    WRET MACRO
            EXITM <AX>
    ENDM
    ENDIF ;WRET
    
    IFNDEF WRETURN
    WRETURN MACRO
            EXITM <AX>
    ENDM
    ENDIF ;WRETURN
    
    IFNDEF WSIDX
    WSIDX MACRO
            EXITM <SI>
    ENDM
    ENDIF ;WSIDX
    
    IFNDEF WDIDX
    WDIDX MACRO
            EXITM <DI>
    ENDM
    ENDIF ;WDIDX
    
    IFNDEF WBPTR
    WBPTR MACRO
            EXITM <BP>
    ENDM
    ENDIF ;WBPTR
    
    IFNDEF WSPTR
    WSPTR MACRO
            EXITM <SP>
    ENDM
    ENDIF ;WSPTR
    
    IFNDEF WBASE
    WBASE MACRO
            EXITM <BX>
    ENDM
    ENDIF ;WBASE
    
    IFNDEF WCOUNT
    WCOUNT MACRO
            EXITM <CX>
    ENDM
    ENDIF ;WCOUNT
    
    IFNDEF WTHIS
    WTHIS MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <AX>
            ELSE
                EXITM <CX>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <AX>
            ELSE
                EXITM <DI>
            ENDIF
        ENDIF
        IFDEF __WIN32__
            IF @LangType EQ LANG_FASTSCALL OR @LangType EQ LANG_VECTORCALL OR @LangType EQ LANG_REGCALL OR @LangType EQ LANG_THISCALL
                EXITM <CX>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <AX>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;WTHIS
    
    IFNDEF WP0
    WP0 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <AX>
            ELSE
                EXITM <CX>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <AX>
            ELSE
                EXITM <DI>
            ENDIF
        ENDIF
        IFDEF __WIN32__
            IF @LangType EQ LANG_FASTSCALL OR @LangType EQ LANG_VECTORCALL OR @LangType EQ LANG_REGCALL OR @LangType EQ LANG_THISCALL
                EXITM <CX>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <AX>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;WP0

    IFNDEF WP1
    WP1 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <CX>
            ELSE
                EXITM <DX>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <CX>
            ELSE
                EXITM <SI>
            ENDIF
        ENDIF
        IFDEF __WIN32__
            IF @LangType EQ LANG_FASTSCALL OR @LangType EQ LANG_VECTORCALL OR @LangType EQ LANG_REGCALL
                EXITM <DX>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <CX>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;WP1
    
    IFNDEF WP2
    WP2 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <DX>
            ELSE
                EXITM <R8W>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
                EXITM <DX>
        ENDIF
        IFDEF __WIN32__
            IF @LangType EQ LANG_REGCALL
                EXITM <DI>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <DX>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;WP2
    
    IFNDEF WP3
    WP3 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <DI>
            ELSE
                EXITM <R9W>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <DI>
            ELSEIF @LangType EQ LANG_SYSCALL
                EXITM <R10W>
            ELSE
                EXITM <CX>
            ENDIF
        ENDIF
        IFDEF __WIN32__
            IF @LangType EQ LANG_REGCALL
                EXITM <SI>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <DI>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;WP3
    
    IFNDEF WP4
    WP4 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <SI>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <SI>
            ELSE
                EXITM <R8W>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <SP>
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <SI>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;WP4
    
    IFNDEF WP5
    WP5 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R8W>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R8W>
            ELSE
                EXITM <R9W>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <SP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <SP>
        ENDIF
    ENDM
    ENDIF ;WP5
    
    IFNDEF WP6
    WP6 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R9W>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R9W>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <SP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <SP>
        ENDIF
    ENDM
    ENDIF ;WP6
    
    IFNDEF WP7
    WP7 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R11W>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R10W>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <SP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <SP>
        ENDIF
    ENDM
    ENDIF ;WP7
    
    IFNDEF WP8
    WP8 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R12W>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R11W>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <SP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <SP>
        ENDIF
    ENDM
    ENDIF ;WP8
    
    IFNDEF WP9
    WP9 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R14W>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R12W>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <SP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <SP>
        ENDIF
    ENDM
    ENDIF ;WP9
    
    IFNDEF WP10
    WP10 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R15W>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R14W>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <SP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <SP>
        ENDIF
    ENDM
    ENDIF ;WP10
    
    IFNDEF WP11
    WP11 MACRO
        IFDEF __WIN64__
                EXITM <SP>
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R15W>
            ELSE
                EXITM <SP>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <SP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <SP>
        ENDIF
    ENDM
    ENDIF ;WP11
    
    IFNDEF WP12
    WP12 MACRO
        IFDEF __WIN64__
                EXITM <SP>
        ENDIF
        IFDEF __UNIX64__
                EXITM <SP>
        ENDIF
        IFDEF __WIN32__
                EXITM <SP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <SP>
        ENDIF
    ENDM
    ENDIF ;WP12
    
    IFNDEF WP13
    WP13 MACRO
        IFDEF __WIN64__
                EXITM <SP>
        ENDIF
        IFDEF __UNIX64__
                EXITM <SP>
        ENDIF
        IFDEF __WIN32__
                EXITM <SP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <SP>
        ENDIF
    ENDM
    ENDIF ;WP13
    
    IFNDEF WP14
    WP14 MACRO
        IFDEF __WIN64__
                EXITM <SP>
        ENDIF
        IFDEF __UNIX64__
                EXITM <SP>
        ENDIF
        IFDEF __WIN32__
                EXITM <SP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <SP>
        ENDIF
    ENDM
    ENDIF ;WP14
    
    IFNDEF WP15
    WP15 MACRO
        IFDEF __WIN64__
                EXITM <SP>
        ENDIF
        IFDEF __UNIX64__
                EXITM <SP>
        ENDIF
        IFDEF __WIN32__
                EXITM <SP>
        ENDIF
        IFDEF __UNIX32__
                EXITM <SP>
        ENDIF
    ENDM
    ENDIF ;WP15
    
    IFNDEF BRET
    BRET MACRO
            EXITM <AL>
    ENDM
    ENDIF ;BRET
    
    IFNDEF BRETURN
    BRETURN MACRO
            EXITM <AL>
    ENDM
    ENDIF ;BRETURN
    
    IFNDEF BSIDX
    BSIDX MACRO
            EXITM <SIL>
    ENDM
    ENDIF ;BSIDX
    
    IFNDEF BDIDX
    BDIDX MACRO
            EXITM <DIL>
    ENDM
    ENDIF ;BDIDX
    
    IFNDEF BBPTR
    BBPTR MACRO
            EXITM <BPL>
    ENDM
    ENDIF ;BBPTR
    
    IFNDEF BSPTR
    BSPTR MACRO
            EXITM <SPL>
    ENDM
    ENDIF ;BSPTR
    
    IFNDEF BBASE
    BBASE MACRO
            EXITM <BL>
    ENDM
    ENDIF ;BBASE
    
    IFNDEF BCOUNT
    BCOUNT MACRO
            EXITM <CL>
    ENDM
    ENDIF ;BCOUNT
    
    IFNDEF BTHIS
    BTHIS MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <AL>
            ELSE
                EXITM <CL>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <AL>
            ELSE
                EXITM <DIL>
            ENDIF
        ENDIF
        IFDEF __WIN32__
            IF @LangType EQ LANG_FASTSCALL OR @LangType EQ LANG_VECTORCALL OR @LangType EQ LANG_REGCALL OR @LangType EQ LANG_THISCALL
                EXITM <CL>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <AL>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;BTHIS
    
    IFNDEF BP0
    BP0 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <AL>
            ELSE
                EXITM <CL>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <AL>
            ELSE
                EXITM <DIL>
            ENDIF
        ENDIF
        IFDEF __WIN32__
            IF @LangType EQ LANG_FASTSCALL OR @LangType EQ LANG_VECTORCALL OR @LangType EQ LANG_REGCALL OR @LangType EQ LANG_THISCALL
                EXITM <CL>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <AL>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;BP0

    IFNDEF BP1
    BP1 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <CL>
            ELSE
                EXITM <DL>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <CL>
            ELSE
                EXITM <SIL>
            ENDIF
        ENDIF
        IFDEF __WIN32__
            IF @LangType EQ LANG_FASTSCALL OR @LangType EQ LANG_VECTORCALL OR @LangType EQ LANG_REGCALL
                EXITM <DL>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <CL>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;BP1
    
    IFNDEF BP2
    BP2 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <DL>
            ELSE
                EXITM <R8B>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
                EXITM <DL>
        ENDIF
        IFDEF __WIN32__
            IF @LangType EQ LANG_REGCALL
                EXITM <DIL>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <DL>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;BP2
    
    IFNDEF BP3
    BP3 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <DIL>
            ELSE
                EXITM <R9B>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <DIL>
            ELSEIF @LangType EQ LANG_SYSCALL
                EXITM <R10B>
            ELSE
                EXITM <CL>
            ENDIF
        ENDIF
        IFDEF __WIN32__
            IF @LangType EQ LANG_REGCALL
                EXITM <SIL>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <DIL>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;BP3
    
    IFNDEF BP4
    BP4 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <SIL>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <SIL>
            ELSE
                EXITM <R8B>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <SPL>
        ENDIF
        IFDEF __UNIX32__
            IF @LangType EQ LANG_REGCALL
                EXITM <SIL>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
    ENDM
    ENDIF ;BP4
    
    IFNDEF BP5
    BP5 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R8B>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R8B>
            ELSE
                EXITM <R9B>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <SPL>
        ENDIF
        IFDEF __UNIX32__
                EXITM <SPL>
        ENDIF
    ENDM
    ENDIF ;BP5
    
    IFNDEF BP6
    BP6 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R9B>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R9B>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <SPL>
        ENDIF
        IFDEF __UNIX32__
                EXITM <SPL>
        ENDIF
    ENDM
    ENDIF ;BP6
    
    IFNDEF BP7
    BP7 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R11B>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R10B>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <SPL>
        ENDIF
        IFDEF __UNIX32__
                EXITM <SPL>
        ENDIF
    ENDM
    ENDIF ;BP7
    
    IFNDEF BP8
    BP8 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R12B>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R11B>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <SPL>
        ENDIF
        IFDEF __UNIX32__
                EXITM <SPL>
        ENDIF
    ENDM
    ENDIF ;BP8
    
    IFNDEF BP9
    BP9 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R14B>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R12B>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <SPL>
        ENDIF
        IFDEF __UNIX32__
                EXITM <SPL>
        ENDIF
    ENDM
    ENDIF ;BP9
    
    IFNDEF BP10
    BP10 MACRO
        IFDEF __WIN64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R15B>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R14B>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <SPL>
        ENDIF
        IFDEF __UNIX32__
                EXITM <SPL>
        ENDIF
    ENDM
    ENDIF ;BP10
    
    IFNDEF BP11
    BP11 MACRO
        IFDEF __WIN64__
                EXITM <SPL>
        ENDIF
        IFDEF __UNIX64__
            IF @LangType EQ LANG_REGCALL
                EXITM <R15B>
            ELSE
                EXITM <SPL>
            ENDIF
        ENDIF
        IFDEF __WIN32__
                EXITM <SPL>
        ENDIF
        IFDEF __UNIX32__
                EXITM <SPL>
        ENDIF
    ENDM
    ENDIF ;BP11
    
    IFNDEF BP12
    BP12 MACRO
        IFDEF __WIN64__
                EXITM <SPL>
        ENDIF
        IFDEF __UNIX64__
                EXITM <SPL>
        ENDIF
        IFDEF __WIN32__
                EXITM <SPL>
        ENDIF
        IFDEF __UNIX32__
                EXITM <SPL>
        ENDIF
    ENDM
    ENDIF ;BP12
    
    IFNDEF BP13
    BP13 MACRO
        IFDEF __WIN64__
                EXITM <SPL>
        ENDIF
        IFDEF __UNIX64__
                EXITM <SPL>
        ENDIF
        IFDEF __WIN32__
                EXITM <SPL>
        ENDIF
        IFDEF __UNIX32__
                EXITM <SPL>
        ENDIF
    ENDM
    ENDIF ;BP13
    
    IFNDEF BP14
    BP14 MACRO
        IFDEF __WIN64__
                EXITM <SPL>
        ENDIF
        IFDEF __UNIX64__
                EXITM <SPL>
        ENDIF
        IFDEF __WIN32__
                EXITM <SPL>
        ENDIF
        IFDEF __UNIX32__
                EXITM <SPL>
        ENDIF
    ENDM
    ENDIF ;BP14
    
    IFNDEF BP15
    BP15 MACRO
        IFDEF __WIN64__
                EXITM <SPL>
        ENDIF
        IFDEF __UNIX64__
                EXITM <SPL>
        ENDIF
        IFDEF __WIN32__
                EXITM <SPL>
        ENDIF
        IFDEF __UNIX32__
                EXITM <SPL>
        ENDIF
    ENDM
    ENDIF ;BP15
    
    IFDEF UNDEFINED_PLATFORM
    .ERR <"No platform defined for Parameters">
    ENDIF ;/*UNDEFINED_PLATFORM
    
    IFDEF CASEMAPNONE
   ;/* norm reg bits*/
    grp TEXTEQU <GRP>
    prp TEXTEQU <PRP>
    rret TEXTEQU <RRET>
    rreturn TEXTEQU <RRETURN>
    rsidx TEXTEQU <RSIDX>
    rdidx TEXTEQU <RDIDX>
    rbptr TEXTEQU <RBPTR>
    rsptr TEXTEQU <RSPTR>
    rbase TEXTEQU <RBASE>
    rcount TEXTEQU <RCOUNT>
    rthis TEXTEQU <RTHIS>
    rp0 TEXTEQU <RP0>
    rp1 TEXTEQU <RP1>
    rp2 TEXTEQU <RP2>
    rp3 TEXTEQU <RP3>
    rp4 TEXTEQU <RP4>
    rp5 TEXTEQU <RP5>
    rp6 TEXTEQU <RP6>
    rp7 TEXTEQU <RP7>
    rp8 TEXTEQU <RP8>
    rp9 TEXTEQU <RP9>
    rp10 TEXTEQU <RP10>
    rp11 TEXTEQU <RP11>
    rp12 TEXTEQU <RP12>
    rp13 TEXTEQU <RP13>
    rp14 TEXTEQU <RP14>
    rp15 TEXTEQU <RP15>
   ;/* 32bits*/
    dret TEXTEQU <DRET>
    dreturn TEXTEQU <DRETURN>
    dsidx TEXTEQU <DSIDX>
    ddidx TEXTEQU <DDIDX>
    dbptr TEXTEQU <DBPTR>
    dsptr TEXTEQU <DSPTR>
    dbase TEXTEQU <DBASE>
    dcount TEXTEQU <DCOUNT>
    dthis TEXTEQU <DTHIS>
    dp0 TEXTEQU <DP0>
    dp1 TEXTEQU <DP1>
    dp2 TEXTEQU <DP2>
    dp3 TEXTEQU <DP3>
    dp4 TEXTEQU <DP4>
    dp5 TEXTEQU <DP5>
    dp6 TEXTEQU <DP6>
    dp7 TEXTEQU <DP7>
    dp8 TEXTEQU <DP8>
    dp9 TEXTEQU <DP9>
    dp10 TEXTEQU <DP10>
    dp11 TEXTEQU <DP11>
    dp12 TEXTEQU <DP12>
    dp13 TEXTEQU <DP13>
    dp14 TEXTEQU <DP14>
    dp15 TEXTEQU <DP15>
   ;/* 16bits*/
    wret TEXTEQU <WRET>
    wreturn TEXTEQU <WRETURN>
    wsidx TEXTEQU <WSIDX>
    wdidx TEXTEQU <WDIDX>
    wbptr TEXTEQU <WBPTR>
    wsptr TEXTEQU <WSPTR>
    wbase TEXTEQU <WBASE>
    wcount TEXTEQU <WCOUNT>
    wthis TEXTEQU <WTHIS>
    wp0 TEXTEQU <WP0>
    wp1 TEXTEQU <WP1>
    wp2 TEXTEQU <WP2>
    wp3 TEXTEQU <WP3>
    wp4 TEXTEQU <WP4>
    wp5 TEXTEQU <WP5>
    wp6 TEXTEQU <WP6>
    wp7 TEXTEQU <WP7>
    wp8 TEXTEQU <WP8>
    wp9 TEXTEQU <WP9>
    wp10 TEXTEQU <WP10>
    wp11 TEXTEQU <WP11>
    wp12 TEXTEQU <WP12>
    wp13 TEXTEQU <WP13>
    wp14 TEXTEQU <WP14>
    wp15 TEXTEQU <WP15>
   ;/* 8bits*/
    bret TEXTEQU <BRET>
    breturn TEXTEQU <BRETURN>
    bsidx TEXTEQU <BSIDX>
    bdidx TEXTEQU <BDIDX>
    bbptr TEXTEQU <BBPTR>
    bsptr TEXTEQU <BSPTR>
    bbase TEXTEQU <BBASE>
    bcount TEXTEQU <BCOUNT>
    bthis TEXTEQU <BTHIS>
    bp0 TEXTEQU <BP0>
    bp1 TEXTEQU <BP1>
    bp2 TEXTEQU <BP2>
    bp3 TEXTEQU <BP3>
    bp4 TEXTEQU <BP4>
    bp5 TEXTEQU <BP5>
    bp6 TEXTEQU <BP6>
    bp7 TEXTEQU <BP7>
    bp8 TEXTEQU <BP8>
    bp9 TEXTEQU <BP9>
    bp10 TEXTEQU <BP10>
    bp11 TEXTEQU <BP11>
    bp12 TEXTEQU <BP12>
    bp13 TEXTEQU <BP13>
    bp14 TEXTEQU <BP14>
    bp15 TEXTEQU <BP15>
    ENDIF ;CASEMAPNONE

    ENDIF ;WITHMACROLIB

    ENDIF    ;PARAMS_INC
