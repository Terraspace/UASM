
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
            .ERR <num "!!!UNIMPLEMENTED!!! Please kindle ask in masm32 dot com sub-forum UASM <http://masm32.com/board/index.php?board=51.0> for aditional parameters implementation">
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
            .ERR <num "!!!UNIMPLEMENTED!!! Please kindle ask in masm32 dot com sub-forum UASM <http://masm32.com/board/index.php?board=51.0> for aditional parameters implementation">
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
                ELSE
                    cnt = -1
                    FOR arg,<[DI+pf],[SI+pf],DX,[CX+pf],[R8W+pf],[R9W+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf],[SP+pf]>
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
    
    IFDEF __WIN64__
    ;/* norm reg bits for x64 and vectorcall*/
    RRET TEXTEQU <RAX>
    RRETURN TEXTEQU <RAX>
    RSIDX TEXTEQU <RSI>
    RDIDX TEXTEQU <RDI>
    RBPTR TEXTEQU <RBP>
    RSPTR TEXTEQU <RSP>
    RBASE TEXTEQU <RBX>
    RTHIS TEXTEQU <RCX>
    RPARAM0 TEXTEQU <RCX>
    RPARAM1 TEXTEQU <RDX>
    RPARAM2 TEXTEQU <R8>
    RPARAM3 TEXTEQU <R9>
    RPARAM4 TEXTEQU <[RSP+40]>
    RPARAM5 TEXTEQU <[RSP+48]>
    RPARAM6 TEXTEQU <[RSP+56]>
    RPARAM7 TEXTEQU <[RSP+64]>
    RPARAM8 TEXTEQU <[RSP+72]>
    RPARAM9 TEXTEQU <[RSP+80]>
    RPARAM10 TEXTEQU <[RSP+88]>
    RPARAM11 TEXTEQU <[RSP+96]>
    RPARAM12 TEXTEQU <[RSP+104]>
    RPARAM13 TEXTEQU <[RSP+112]>
    RPARAM14 TEXTEQU <[RSP+120]>
    RPARAM15 TEXTEQU <[RSP+128]>
    RPARAM16 TEXTEQU <[RSP+136]>
    RPARAM17 TEXTEQU <[RSP+144]>
    RPARAM18 TEXTEQU <[RSP+152]>
    RPARAM19 TEXTEQU <[RSP+160]>
    RPARAM20 TEXTEQU <[RSP+168]>
    RPARAM21 TEXTEQU <[RSP+176]>
    RPARAM22 TEXTEQU <[RSP+184]>
    RPARAM23 TEXTEQU <[RSP+192]>
    RPARAM24 TEXTEQU <[RSP+200]>
    RPARAM25 TEXTEQU <[RSP+208]>
    RPARAM26 TEXTEQU <[RSP+216]>
    RPARAM27 TEXTEQU <[RSP+224]>
    RPARAM28 TEXTEQU <[RSP+232]>
    RPARAM29 TEXTEQU <[RSP+240]>
    RPARAM30 TEXTEQU <[RSP+248]>
    RPARAM31 TEXTEQU <[RSP+256]>
    RPARAM32 TEXTEQU <[RSP+264]>
    RPARAM33 TEXTEQU <[RSP+272]>
    RPARAM34 TEXTEQU <[RSP+280]>
    RPARAM35 TEXTEQU <[RSP+288]>
    RPARAM36 TEXTEQU <[RSP+296]>
    RPARAM37 TEXTEQU <[RSP+304]>
    RPARAM38 TEXTEQU <[RSP+312]>
    RPARAM39 TEXTEQU <[RSP+320]>
    RPARAM40 TEXTEQU <[RSP+328]>
    RPARAM41 TEXTEQU <[RSP+336]>
    RPARAM42 TEXTEQU <[RSP+344]>
    RPARAM43 TEXTEQU <[RSP+352]>
    RPARAM44 TEXTEQU <[RSP+360]>
    RPARAM45 TEXTEQU <[RSP+368]>
    RPARAM46 TEXTEQU <[RSP+376]>
    RPARAM47 TEXTEQU <[RSP+384]>
    RPARAM48 TEXTEQU <[RSP+392]>
    RPARAM49 TEXTEQU <[RSP+400]>
    RPARAM50 TEXTEQU <[RSP+408]>
    RPARAM51 TEXTEQU <[RSP+416]>
    RPARAM52 TEXTEQU <[RSP+424]>
    RPARAM53 TEXTEQU <[RSP+432]>
    RPARAM54 TEXTEQU <[RSP+440]>
    RPARAM55 TEXTEQU <[RSP+448]>
    RPARAM56 TEXTEQU <[RSP+456]>
    RPARAM57 TEXTEQU <[RSP+464]>
    RPARAM58 TEXTEQU <[RSP+472]>
    RPARAM59 TEXTEQU <[RSP+480]>
    RPARAM60 TEXTEQU <[RSP+488]>
    RPARAM61 TEXTEQU <[RSP+496]>
    RPARAM62 TEXTEQU <[RSP+504]>
    RPARAM63 TEXTEQU <[RSP+512]>
    ;/* 32bits*/
    DRET TEXTEQU <EAX>
    DRETURN TEXTEQU <EAX>
    DSIDX TEXTEQU <ESI>
    DDIDX TEXTEQU <EDI>
    DBPTR TEXTEQU <EBP>
    DSPTR TEXTEQU <ESP>
    DBASE TEXTEQU <EBX>
    DTHIS TEXTEQU <ECX>
    DPARAM0 TEXTEQU <ECX>
    DPARAM1 TEXTEQU <EDX>
    DPARAM2 TEXTEQU <R8D>
    DPARAM3 TEXTEQU <R9D>
    DPARAM4 TEXTEQU <[ESP+20]>
    DPARAM5 TEXTEQU <[ESP+24]>
    DPARAM6 TEXTEQU <[ESP+28]>
    DPARAM7 TEXTEQU <[ESP+32]>
    DPARAM8 TEXTEQU <[ESP+36]>
    DPARAM9 TEXTEQU <[ESP+40]>
    DPARAM10 TEXTEQU <[ESP+44]>
    DPARAM11 TEXTEQU <[ESP+48]>
    DPARAM12 TEXTEQU <[ESP+52]>
    DPARAM13 TEXTEQU <[ESP+56]>
    DPARAM14 TEXTEQU <[ESP+60]>
    DPARAM15 TEXTEQU <[ESP+64]>
    DPARAM16 TEXTEQU <[ESP+68]>
    DPARAM17 TEXTEQU <[ESP+72]>
    DPARAM18 TEXTEQU <[ESP+76]>
    DPARAM19 TEXTEQU <[ESP+80]>
    DPARAM20 TEXTEQU <[ESP+84]>
    DPARAM21 TEXTEQU <[ESP+88]>
    DPARAM22 TEXTEQU <[ESP+92]>
    DPARAM23 TEXTEQU <[ESP+96]>
    DPARAM24 TEXTEQU <[ESP+100]>
    DPARAM25 TEXTEQU <[ESP+104]>
    DPARAM26 TEXTEQU <[ESP+108]>
    DPARAM27 TEXTEQU <[ESP+112]>
    DPARAM28 TEXTEQU <[ESP+116]>
    DPARAM29 TEXTEQU <[ESP+120]>
    DPARAM30 TEXTEQU <[ESP+124]>
    DPARAM31 TEXTEQU <[ESP+128]>
    DPARAM32 TEXTEQU <[ESP+132]>
    DPARAM33 TEXTEQU <[ESP+136]>
    DPARAM34 TEXTEQU <[ESP+140]>
    DPARAM35 TEXTEQU <[ESP+144]>
    DPARAM36 TEXTEQU <[ESP+148]>
    DPARAM37 TEXTEQU <[ESP+152]>
    DPARAM38 TEXTEQU <[ESP+156]>
    DPARAM39 TEXTEQU <[ESP+160]>
    DPARAM40 TEXTEQU <[ESP+164]>
    DPARAM41 TEXTEQU <[ESP+168]>
    DPARAM42 TEXTEQU <[ESP+172]>
    DPARAM43 TEXTEQU <[ESP+176]>
    DPARAM44 TEXTEQU <[ESP+180]>
    DPARAM45 TEXTEQU <[ESP+184]>
    DPARAM46 TEXTEQU <[ESP+188]>
    DPARAM47 TEXTEQU <[ESP+192]>
    DPARAM48 TEXTEQU <[ESP+196]>
    DPARAM49 TEXTEQU <[ESP+200]>
    DPARAM50 TEXTEQU <[ESP+204]>
    DPARAM51 TEXTEQU <[ESP+208]>
    DPARAM52 TEXTEQU <[ESP+212]>
    DPARAM53 TEXTEQU <[ESP+216]>
    DPARAM54 TEXTEQU <[ESP+220]>
    DPARAM55 TEXTEQU <[ESP+224]>
    DPARAM56 TEXTEQU <[ESP+228]>
    DPARAM57 TEXTEQU <[ESP+232]>
    DPARAM58 TEXTEQU <[ESP+236]>
    DPARAM59 TEXTEQU <[ESP+240]>
    DPARAM60 TEXTEQU <[ESP+244]>
    DPARAM61 TEXTEQU <[ESP+248]>
    DPARAM62 TEXTEQU <[ESP+252]>
    DPARAM63 TEXTEQU <[ESP+256]>
    ;/* 16bits*/
    WRET TEXTEQU <AX>
    WRETURN TEXTEQU <AX>
    WSIDX TEXTEQU <SI>
    WDIDX TEXTEQU <DI>
    WBPTR TEXTEQU <BP>
    WSPTR TEXTEQU <SP>
    WBASE TEXTEQU <BX>
    WTHIS TEXTEQU <CX>
    WPARAM0 TEXTEQU <CX>
    WPARAM1 TEXTEQU <DX>
    WPARAM2 TEXTEQU <R8W>
    WPARAM3 TEXTEQU <R9W>
    WPARAM4 TEXTEQU <[SP+10]>
    WPARAM5 TEXTEQU <[SP+12]>
    WPARAM6 TEXTEQU <[SP+14]>
    WPARAM7 TEXTEQU <[SP+16]>
    WPARAM8 TEXTEQU <[SP+18]>
    WPARAM9 TEXTEQU <[SP+20]>
    WPARAM10 TEXTEQU <[SP+22]>
    WPARAM11 TEXTEQU <[SP+24]>
    WPARAM12 TEXTEQU <[SP+26]>
    WPARAM13 TEXTEQU <[SP+28]>
    WPARAM14 TEXTEQU <[SP+30]>
    WPARAM15 TEXTEQU <[SP+32]>
    WPARAM16 TEXTEQU <[SP+34]>
    WPARAM17 TEXTEQU <[SP+36]>
    WPARAM18 TEXTEQU <[SP+38]>
    WPARAM19 TEXTEQU <[SP+40]>
    WPARAM20 TEXTEQU <[SP+42]>
    WPARAM21 TEXTEQU <[SP+44]>
    WPARAM22 TEXTEQU <[SP+46]>
    WPARAM23 TEXTEQU <[SP+48]>
    WPARAM24 TEXTEQU <[SP+50]>
    WPARAM25 TEXTEQU <[SP+52]>
    WPARAM26 TEXTEQU <[SP+54]>
    WPARAM27 TEXTEQU <[SP+56]>
    WPARAM28 TEXTEQU <[SP+58]>
    WPARAM29 TEXTEQU <[SP+60]>
    WPARAM30 TEXTEQU <[SP+62]>
    WPARAM31 TEXTEQU <[SP+64]>
    WPARAM32 TEXTEQU <[SP+66]>
    WPARAM33 TEXTEQU <[SP+68]>
    WPARAM34 TEXTEQU <[SP+70]>
    WPARAM35 TEXTEQU <[SP+72]>
    WPARAM36 TEXTEQU <[SP+74]>
    WPARAM37 TEXTEQU <[SP+76]>
    WPARAM38 TEXTEQU <[SP+78]>
    WPARAM39 TEXTEQU <[SP+80]>
    WPARAM40 TEXTEQU <[SP+82]>
    WPARAM41 TEXTEQU <[SP+84]>
    WPARAM42 TEXTEQU <[SP+86]>
    WPARAM43 TEXTEQU <[SP+88]>
    WPARAM44 TEXTEQU <[SP+90]>
    WPARAM45 TEXTEQU <[SP+92]>
    WPARAM46 TEXTEQU <[SP+94]>
    WPARAM47 TEXTEQU <[SP+96]>
    WPARAM48 TEXTEQU <[SP+98]>
    WPARAM49 TEXTEQU <[SP+100]>
    WPARAM50 TEXTEQU <[SP+102]>
    WPARAM51 TEXTEQU <[SP+104]>
    WPARAM52 TEXTEQU <[SP+106]>
    WPARAM53 TEXTEQU <[SP+108]>
    WPARAM54 TEXTEQU <[SP+110]>
    WPARAM55 TEXTEQU <[SP+112]>
    WPARAM56 TEXTEQU <[SP+114]>
    WPARAM57 TEXTEQU <[SP+116]>
    WPARAM58 TEXTEQU <[SP+118]>
    WPARAM59 TEXTEQU <[SP+120]>
    WPARAM60 TEXTEQU <[SP+122]>
    WPARAM61 TEXTEQU <[SP+124]>
    WPARAM62 TEXTEQU <[SP+126]>
    WPARAM63 TEXTEQU <[SP+128]>
    ;/* 8bits*/
    BRET TEXTEQU <AL>
    BRETURN TEXTEQU <AL>
    BSIDX TEXTEQU <SIL>
    BDIDX TEXTEQU <DIL>
    BBPTR TEXTEQU <BPL>
    BSPTR TEXTEQU <SPL>
    BBASE TEXTEQU <BL>
    BTHIS TEXTEQU <CL>
    BPARAM0 TEXTEQU <CL>
    BPARAM1 TEXTEQU <DL>
    BPARAM2 TEXTEQU <R8B>
    BPARAM3 TEXTEQU <R9B>
    BPARAM4 TEXTEQU <[SPL+5]>
    BPARAM5 TEXTEQU <[SPL+6]>
    BPARAM6 TEXTEQU <[SPL+7]>
    BPARAM7 TEXTEQU <[SPL+8]>
    BPARAM8 TEXTEQU <[SPL+9]>
    BPARAM9 TEXTEQU <[SPL+10]>
    BPARAM10 TEXTEQU <[SPL+11]>
    BPARAM11 TEXTEQU <[SPL+12]>
    BPARAM12 TEXTEQU <[SPL+13]>
    BPARAM13 TEXTEQU <[SPL+14]>
    BPARAM14 TEXTEQU <[SPL+15]>
    BPARAM15 TEXTEQU <[SPL+16]>
    BPARAM16 TEXTEQU <[SPL+17]>
    BPARAM17 TEXTEQU <[SPL+18]>
    BPARAM18 TEXTEQU <[SPL+19]>
    BPARAM19 TEXTEQU <[SPL+20]>
    BPARAM20 TEXTEQU <[SPL+21]>
    BPARAM21 TEXTEQU <[SPL+22]>
    BPARAM22 TEXTEQU <[SPL+23]>
    BPARAM23 TEXTEQU <[SPL+24]>
    BPARAM24 TEXTEQU <[SPL+25]>
    BPARAM25 TEXTEQU <[SPL+26]>
    BPARAM26 TEXTEQU <[SPL+27]>
    BPARAM27 TEXTEQU <[SPL+28]>
    BPARAM28 TEXTEQU <[SPL+29]>
    BPARAM29 TEXTEQU <[SPL+30]>
    BPARAM30 TEXTEQU <[SPL+31]>
    BPARAM31 TEXTEQU <[SPL+32]>
    BPARAM32 TEXTEQU <[SPL+33]>
    BPARAM33 TEXTEQU <[SPL+34]>
    BPARAM34 TEXTEQU <[SPL+35]>
    BPARAM35 TEXTEQU <[SPL+36]>
    BPARAM36 TEXTEQU <[SPL+37]>
    BPARAM37 TEXTEQU <[SPL+38]>
    BPARAM38 TEXTEQU <[SPL+39]>
    BPARAM39 TEXTEQU <[SPL+40]>
    BPARAM40 TEXTEQU <[SPL+41]>
    BPARAM41 TEXTEQU <[SPL+42]>
    BPARAM42 TEXTEQU <[SPL+43]>
    BPARAM43 TEXTEQU <[SPL+44]>
    BPARAM44 TEXTEQU <[SPL+45]>
    BPARAM45 TEXTEQU <[SPL+46]>
    BPARAM46 TEXTEQU <[SPL+47]>
    BPARAM47 TEXTEQU <[SPL+48]>
    BPARAM48 TEXTEQU <[SPL+49]>
    BPARAM49 TEXTEQU <[SPL+50]>
    BPARAM50 TEXTEQU <[SPL+51]>
    BPARAM51 TEXTEQU <[SPL+52]>
    BPARAM52 TEXTEQU <[SPL+53]>
    BPARAM53 TEXTEQU <[SPL+54]>
    BPARAM54 TEXTEQU <[SPL+55]>
    BPARAM55 TEXTEQU <[SPL+56]>
    BPARAM56 TEXTEQU <[SPL+57]>
    BPARAM57 TEXTEQU <[SPL+58]>
    BPARAM58 TEXTEQU <[SPL+59]>
    BPARAM59 TEXTEQU <[SPL+60]>
    BPARAM60 TEXTEQU <[SPL+61]>
    BPARAM61 TEXTEQU <[SPL+62]>
    BPARAM62 TEXTEQU <[SPL+63]>
    BPARAM63 TEXTEQU <[SPL+64]>

    ;/* norm reg bits for regcall*/
    RRRET TEXTEQU <RAX>
    RRRETURN TEXTEQU <RAX>
    RRSIDX TEXTEQU <RSI>
    RRDIDX TEXTEQU <RDI>
    RRBPTR TEXTEQU <RBP>
    RRSPTR TEXTEQU <RSP>
    RRBASE TEXTEQU <RBX>
    RRTHIS TEXTEQU <RAX>
    RRPARAM0 TEXTEQU <RAX>
    RRPARAM1 TEXTEQU <RCX>
    RRPARAM2 TEXTEQU <RDX>
    RRPARAM3 TEXTEQU <RDI>
    RRPARAM4 TEXTEQU <RSI>
    RRPARAM5 TEXTEQU <R8>
    RRPARAM6 TEXTEQU <R9>
    RRPARAM7 TEXTEQU <R11>
    RRPARAM8 TEXTEQU <R12>
    RRPARAM9 TEXTEQU <R14>
    RRPARAM10 TEXTEQU <R15>
    RRPARAM11 TEXTEQU <[RSP+96]>
    RRPARAM12 TEXTEQU <[RSP+104]>
    RRPARAM13 TEXTEQU <[RSP+112]>
    RRPARAM14 TEXTEQU <[RSP+120]>
    RRPARAM15 TEXTEQU <[RSP+128]>
    RRPARAM16 TEXTEQU <[RSP+136]>
    RRPARAM17 TEXTEQU <[RSP+144]>
    RRPARAM18 TEXTEQU <[RSP+152]>
    RRPARAM19 TEXTEQU <[RSP+160]>
    RRPARAM20 TEXTEQU <[RSP+168]>
    RRPARAM21 TEXTEQU <[RSP+176]>
    RRPARAM22 TEXTEQU <[RSP+184]>
    RRPARAM23 TEXTEQU <[RSP+192]>
    RRPARAM24 TEXTEQU <[RSP+200]>
    RRPARAM25 TEXTEQU <[RSP+208]>
    RRPARAM26 TEXTEQU <[RSP+216]>
    RRPARAM27 TEXTEQU <[RSP+224]>
    RRPARAM28 TEXTEQU <[RSP+232]>
    RRPARAM29 TEXTEQU <[RSP+240]>
    RRPARAM30 TEXTEQU <[RSP+248]>
    RRPARAM31 TEXTEQU <[RSP+256]>
    RRPARAM32 TEXTEQU <[RSP+264]>
    RRPARAM33 TEXTEQU <[RSP+272]>
    RRPARAM34 TEXTEQU <[RSP+280]>
    RRPARAM35 TEXTEQU <[RSP+288]>
    RRPARAM36 TEXTEQU <[RSP+296]>
    RRPARAM37 TEXTEQU <[RSP+304]>
    RRPARAM38 TEXTEQU <[RSP+312]>
    RRPARAM39 TEXTEQU <[RSP+320]>
    RRPARAM40 TEXTEQU <[RSP+328]>
    RRPARAM41 TEXTEQU <[RSP+336]>
    RRPARAM42 TEXTEQU <[RSP+344]>
    RRPARAM43 TEXTEQU <[RSP+352]>
    RRPARAM44 TEXTEQU <[RSP+360]>
    RRPARAM45 TEXTEQU <[RSP+368]>
    RRPARAM46 TEXTEQU <[RSP+376]>
    RRPARAM47 TEXTEQU <[RSP+384]>
    RRPARAM48 TEXTEQU <[RSP+392]>
    RRPARAM49 TEXTEQU <[RSP+400]>
    RRPARAM50 TEXTEQU <[RSP+408]>
    RRPARAM51 TEXTEQU <[RSP+416]>
    RRPARAM52 TEXTEQU <[RSP+424]>
    RRPARAM53 TEXTEQU <[RSP+432]>
    RRPARAM54 TEXTEQU <[RSP+440]>
    RRPARAM55 TEXTEQU <[RSP+448]>
    RRPARAM56 TEXTEQU <[RSP+456]>
    RRPARAM57 TEXTEQU <[RSP+464]>
    RRPARAM58 TEXTEQU <[RSP+472]>
    RRPARAM59 TEXTEQU <[RSP+480]>
    RRPARAM60 TEXTEQU <[RSP+488]>
    RRPARAM61 TEXTEQU <[RSP+496]>
    RRPARAM62 TEXTEQU <[RSP+504]>
    RRPARAM63 TEXTEQU <[RSP+512]>
    ;/* 32bits*/
    RDRET TEXTEQU <EAX>
    RDRETURN TEXTEQU <EAX>
    RDSIDX TEXTEQU <ESI>
    RDDIDX TEXTEQU <EDI>
    RDBPTR TEXTEQU <EBP>
    RDSPTR TEXTEQU <ESP>
    RDBASE TEXTEQU <EBX>
    RDTHIS TEXTEQU <EAX>
    RDPARAM0 TEXTEQU <EAX>
    RDPARAM1 TEXTEQU <ECX>
    RDPARAM2 TEXTEQU <EDX>
    RDPARAM3 TEXTEQU <EDI>
    RDPARAM4 TEXTEQU <ESI>
    RDPARAM5 TEXTEQU <R8D>
    RDPARAM6 TEXTEQU <R9D>
    RDPARAM7 TEXTEQU <R11D>
    RDPARAM8 TEXTEQU <R12D>
    RDPARAM9 TEXTEQU <R14D>
    RDPARAM10 TEXTEQU <R15D>
    RDPARAM11 TEXTEQU <[ESP+48]>
    RDPARAM12 TEXTEQU <[ESP+52]>
    RDPARAM13 TEXTEQU <[ESP+56]>
    RDPARAM14 TEXTEQU <[ESP+60]>
    RDPARAM15 TEXTEQU <[ESP+64]>
    RDPARAM16 TEXTEQU <[ESP+68]>
    RDPARAM17 TEXTEQU <[ESP+72]>
    RDPARAM18 TEXTEQU <[ESP+76]>
    RDPARAM19 TEXTEQU <[ESP+80]>
    RDPARAM20 TEXTEQU <[ESP+84]>
    RDPARAM21 TEXTEQU <[ESP+88]>
    RDPARAM22 TEXTEQU <[ESP+92]>
    RDPARAM23 TEXTEQU <[ESP+96]>
    RDPARAM24 TEXTEQU <[ESP+100]>
    RDPARAM25 TEXTEQU <[ESP+104]>
    RDPARAM26 TEXTEQU <[ESP+108]>
    RDPARAM27 TEXTEQU <[ESP+112]>
    RDPARAM28 TEXTEQU <[ESP+116]>
    RDPARAM29 TEXTEQU <[ESP+120]>
    RDPARAM30 TEXTEQU <[ESP+124]>
    RDPARAM31 TEXTEQU <[ESP+128]>
    RDPARAM32 TEXTEQU <[ESP+132]>
    RDPARAM33 TEXTEQU <[ESP+136]>
    RDPARAM34 TEXTEQU <[ESP+140]>
    RDPARAM35 TEXTEQU <[ESP+144]>
    RDPARAM36 TEXTEQU <[ESP+148]>
    RDPARAM37 TEXTEQU <[ESP+152]>
    RDPARAM38 TEXTEQU <[ESP+156]>
    RDPARAM39 TEXTEQU <[ESP+160]>
    RDPARAM40 TEXTEQU <[ESP+164]>
    RDPARAM41 TEXTEQU <[ESP+168]>
    RDPARAM42 TEXTEQU <[ESP+172]>
    RDPARAM43 TEXTEQU <[ESP+176]>
    RDPARAM44 TEXTEQU <[ESP+180]>
    RDPARAM45 TEXTEQU <[ESP+184]>
    RDPARAM46 TEXTEQU <[ESP+188]>
    RDPARAM47 TEXTEQU <[ESP+192]>
    RDPARAM48 TEXTEQU <[ESP+196]>
    RDPARAM49 TEXTEQU <[ESP+200]>
    RDPARAM50 TEXTEQU <[ESP+204]>
    RDPARAM51 TEXTEQU <[ESP+208]>
    RDPARAM52 TEXTEQU <[ESP+212]>
    RDPARAM53 TEXTEQU <[ESP+216]>
    RDPARAM54 TEXTEQU <[ESP+220]>
    RDPARAM55 TEXTEQU <[ESP+224]>
    RDPARAM56 TEXTEQU <[ESP+228]>
    RDPARAM57 TEXTEQU <[ESP+232]>
    RDPARAM58 TEXTEQU <[ESP+236]>
    RDPARAM59 TEXTEQU <[ESP+240]>
    RDPARAM60 TEXTEQU <[ESP+244]>
    RDPARAM61 TEXTEQU <[ESP+248]>
    RDPARAM62 TEXTEQU <[ESP+252]>
    RDPARAM63 TEXTEQU <[ESP+256]>
    ;/* 16bits*/
    RWRET TEXTEQU <AX>
    RWRETURN TEXTEQU <AX>
    RWSIDX TEXTEQU <SI>
    RWDIDX TEXTEQU <DI>
    RWBPTR TEXTEQU <BP>
    RWSPTR TEXTEQU <SP>
    RWBASE TEXTEQU <BX>
    RWTHIS TEXTEQU <AX>
    RWPARAM0 TEXTEQU <AX>
    RWPARAM1 TEXTEQU <CX>
    RWPARAM2 TEXTEQU <DX>
    RWPARAM3 TEXTEQU <DI>
    RWPARAM4 TEXTEQU <SI>
    RWPARAM5 TEXTEQU <R8W>
    RWPARAM6 TEXTEQU <R9W>
    RWPARAM7 TEXTEQU <R11W>
    RWPARAM8 TEXTEQU <R12W>
    RWPARAM9 TEXTEQU <R14W>
    RWPARAM10 TEXTEQU <R15W>
    RWPARAM11 TEXTEQU <[SP+24]>
    RWPARAM12 TEXTEQU <[SP+26]>
    RWPARAM13 TEXTEQU <[SP+28]>
    RWPARAM14 TEXTEQU <[SP+30]>
    RWPARAM15 TEXTEQU <[SP+32]>
    RWPARAM16 TEXTEQU <[SP+34]>
    RWPARAM17 TEXTEQU <[SP+36]>
    RWPARAM18 TEXTEQU <[SP+38]>
    RWPARAM19 TEXTEQU <[SP+40]>
    RWPARAM20 TEXTEQU <[SP+42]>
    RWPARAM21 TEXTEQU <[SP+44]>
    RWPARAM22 TEXTEQU <[SP+46]>
    RWPARAM23 TEXTEQU <[SP+48]>
    RWPARAM24 TEXTEQU <[SP+50]>
    RWPARAM25 TEXTEQU <[SP+52]>
    RWPARAM26 TEXTEQU <[SP+54]>
    RWPARAM27 TEXTEQU <[SP+56]>
    RWPARAM28 TEXTEQU <[SP+58]>
    RWPARAM29 TEXTEQU <[SP+60]>
    RWPARAM30 TEXTEQU <[SP+62]>
    RWPARAM31 TEXTEQU <[SP+64]>
    RWPARAM32 TEXTEQU <[SP+66]>
    RWPARAM33 TEXTEQU <[SP+68]>
    RWPARAM34 TEXTEQU <[SP+70]>
    RWPARAM35 TEXTEQU <[SP+72]>
    RWPARAM36 TEXTEQU <[SP+74]>
    RWPARAM37 TEXTEQU <[SP+76]>
    RWPARAM38 TEXTEQU <[SP+78]>
    RWPARAM39 TEXTEQU <[SP+80]>
    RWPARAM40 TEXTEQU <[SP+82]>
    RWPARAM41 TEXTEQU <[SP+84]>
    RWPARAM42 TEXTEQU <[SP+86]>
    RWPARAM43 TEXTEQU <[SP+88]>
    RWPARAM44 TEXTEQU <[SP+90]>
    RWPARAM45 TEXTEQU <[SP+92]>
    RWPARAM46 TEXTEQU <[SP+94]>
    RWPARAM47 TEXTEQU <[SP+96]>
    RWPARAM48 TEXTEQU <[SP+98]>
    RWPARAM49 TEXTEQU <[SP+100]>
    RWPARAM50 TEXTEQU <[SP+102]>
    RWPARAM51 TEXTEQU <[SP+104]>
    RWPARAM52 TEXTEQU <[SP+106]>
    RWPARAM53 TEXTEQU <[SP+108]>
    RWPARAM54 TEXTEQU <[SP+110]>
    RWPARAM55 TEXTEQU <[SP+112]>
    RWPARAM56 TEXTEQU <[SP+114]>
    RWPARAM57 TEXTEQU <[SP+116]>
    RWPARAM58 TEXTEQU <[SP+118]>
    RWPARAM59 TEXTEQU <[SP+120]>
    RWPARAM60 TEXTEQU <[SP+122]>
    RWPARAM61 TEXTEQU <[SP+124]>
    RWPARAM62 TEXTEQU <[SP+126]>
    RWPARAM63 TEXTEQU <[SP+128]>
    ;/* 8bits*/
    RBRET TEXTEQU <AL>
    RBRETURN TEXTEQU <AL>
    RBSIDX TEXTEQU <SIL>
    RBDIDX TEXTEQU <DIL>
    RBBPTR TEXTEQU <BPL>
    RBSPTR TEXTEQU <SPL>
    RBBASE TEXTEQU <BL>
    RBTHIS TEXTEQU <AL>
    RBPARAM0 TEXTEQU <AL>
    RBPARAM1 TEXTEQU <CL>
    RBPARAM2 TEXTEQU <DL>
    RBPARAM3 TEXTEQU <DIL>
    RBPARAM4 TEXTEQU <SIL>
    RBPARAM5 TEXTEQU <R8B>
    RBPARAM6 TEXTEQU <R9B>
    RBPARAM7 TEXTEQU <R11B>
    RBPARAM8 TEXTEQU <R12B>
    RBPARAM9 TEXTEQU <R14B>
    RBPARAM10 TEXTEQU <R15B>
    RBPARAM11 TEXTEQU <[SPL+12]>
    RBPARAM12 TEXTEQU <[SPL+13]>
    RBPARAM13 TEXTEQU <[SPL+14]>
    RBPARAM14 TEXTEQU <[SPL+15]>
    RBPARAM15 TEXTEQU <[SPL+16]>
    RBPARAM16 TEXTEQU <[SPL+17]>
    RBPARAM17 TEXTEQU <[SPL+18]>
    RBPARAM18 TEXTEQU <[SPL+19]>
    RBPARAM19 TEXTEQU <[SPL+20]>
    RBPARAM20 TEXTEQU <[SPL+21]>
    RBPARAM21 TEXTEQU <[SPL+22]>
    RBPARAM22 TEXTEQU <[SPL+23]>
    RBPARAM23 TEXTEQU <[SPL+24]>
    RBPARAM24 TEXTEQU <[SPL+25]>
    RBPARAM25 TEXTEQU <[SPL+26]>
    RBPARAM26 TEXTEQU <[SPL+27]>
    RBPARAM27 TEXTEQU <[SPL+28]>
    RBPARAM28 TEXTEQU <[SPL+29]>
    RBPARAM29 TEXTEQU <[SPL+30]>
    RBPARAM30 TEXTEQU <[SPL+31]>
    RBPARAM31 TEXTEQU <[SPL+32]>
    RBPARAM32 TEXTEQU <[SPL+33]>
    RBPARAM33 TEXTEQU <[SPL+34]>
    RBPARAM34 TEXTEQU <[SPL+35]>
    RBPARAM35 TEXTEQU <[SPL+36]>
    RBPARAM36 TEXTEQU <[SPL+37]>
    RBPARAM37 TEXTEQU <[SPL+38]>
    RBPARAM38 TEXTEQU <[SPL+39]>
    RBPARAM39 TEXTEQU <[SPL+40]>
    RBPARAM40 TEXTEQU <[SPL+41]>
    RBPARAM41 TEXTEQU <[SPL+42]>
    RBPARAM42 TEXTEQU <[SPL+43]>
    RBPARAM43 TEXTEQU <[SPL+44]>
    RBPARAM44 TEXTEQU <[SPL+45]>
    RBPARAM45 TEXTEQU <[SPL+46]>
    RBPARAM46 TEXTEQU <[SPL+47]>
    RBPARAM47 TEXTEQU <[SPL+48]>
    RBPARAM48 TEXTEQU <[SPL+49]>
    RBPARAM49 TEXTEQU <[SPL+50]>
    RBPARAM50 TEXTEQU <[SPL+51]>
    RBPARAM51 TEXTEQU <[SPL+52]>
    RBPARAM52 TEXTEQU <[SPL+53]>
    RBPARAM53 TEXTEQU <[SPL+54]>
    RBPARAM54 TEXTEQU <[SPL+55]>
    RBPARAM55 TEXTEQU <[SPL+56]>
    RBPARAM56 TEXTEQU <[SPL+57]>
    RBPARAM57 TEXTEQU <[SPL+58]>
    RBPARAM58 TEXTEQU <[SPL+59]>
    RBPARAM59 TEXTEQU <[SPL+60]>
    RBPARAM60 TEXTEQU <[SPL+61]>
    RBPARAM61 TEXTEQU <[SPL+62]>
    RBPARAM62 TEXTEQU <[SPL+63]>
    RBPARAM63 TEXTEQU <[SPL+64]>
    
   ;/* Undefined call or cdecl*/
    URRET TEXTEQU <RAX>
    URRETURN TEXTEQU <RAX>
    URSIDX TEXTEQU <RSI>
    URDIDX TEXTEQU <RDI>
    URBPTR TEXTEQU <RBP>
    URSPTR TEXTEQU <RSP>
    URBASE TEXTEQU <RBX>
    URTHIS TEXTEQU <RCX>
    URPARAM0 TEXTEQU <RCX>
    URPARAM1 TEXTEQU <RDX>
    URPARAM2 TEXTEQU <R8>
    URPARAM3 TEXTEQU <R9>
    URPARAM4 TEXTEQU <[RSP+40]>
    URPARAM5 TEXTEQU <[RSP+48]>
    URPARAM6 TEXTEQU <[RSP+56]>
    URPARAM7 TEXTEQU <[RSP+64]>
    URPARAM8 TEXTEQU <[RSP+72]>
    URPARAM9 TEXTEQU <[RSP+80]>
    URPARAM10 TEXTEQU <[RSP+88]>
    URPARAM11 TEXTEQU <[RSP+96]>
    URPARAM12 TEXTEQU <[RSP+104]>
    URPARAM13 TEXTEQU <[RSP+112]>
    URPARAM14 TEXTEQU <[RSP+120]>
    URPARAM15 TEXTEQU <[RSP+128]>
    URPARAM16 TEXTEQU <[RSP+136]>
    URPARAM17 TEXTEQU <[RSP+144]>
    URPARAM18 TEXTEQU <[RSP+152]>
    URPARAM19 TEXTEQU <[RSP+160]>
    URPARAM20 TEXTEQU <[RSP+168]>
    URPARAM21 TEXTEQU <[RSP+176]>
    URPARAM22 TEXTEQU <[RSP+184]>
    URPARAM23 TEXTEQU <[RSP+192]>
    URPARAM24 TEXTEQU <[RSP+200]>
    URPARAM25 TEXTEQU <[RSP+208]>
    URPARAM26 TEXTEQU <[RSP+216]>
    URPARAM27 TEXTEQU <[RSP+224]>
    URPARAM28 TEXTEQU <[RSP+232]>
    URPARAM29 TEXTEQU <[RSP+240]>
    URPARAM30 TEXTEQU <[RSP+248]>
    URPARAM31 TEXTEQU <[RSP+256]>
    URPARAM32 TEXTEQU <[RSP+264]>
    URPARAM33 TEXTEQU <[RSP+272]>
    URPARAM34 TEXTEQU <[RSP+280]>
    URPARAM35 TEXTEQU <[RSP+288]>
    URPARAM36 TEXTEQU <[RSP+296]>
    URPARAM37 TEXTEQU <[RSP+304]>
    URPARAM38 TEXTEQU <[RSP+312]>
    URPARAM39 TEXTEQU <[RSP+320]>
    URPARAM40 TEXTEQU <[RSP+328]>
    URPARAM41 TEXTEQU <[RSP+336]>
    URPARAM42 TEXTEQU <[RSP+344]>
    URPARAM43 TEXTEQU <[RSP+352]>
    URPARAM44 TEXTEQU <[RSP+360]>
    URPARAM45 TEXTEQU <[RSP+368]>
    URPARAM46 TEXTEQU <[RSP+376]>
    URPARAM47 TEXTEQU <[RSP+384]>
    URPARAM48 TEXTEQU <[RSP+392]>
    URPARAM49 TEXTEQU <[RSP+400]>
    URPARAM50 TEXTEQU <[RSP+408]>
    URPARAM51 TEXTEQU <[RSP+416]>
    URPARAM52 TEXTEQU <[RSP+424]>
    URPARAM53 TEXTEQU <[RSP+432]>
    URPARAM54 TEXTEQU <[RSP+440]>
    URPARAM55 TEXTEQU <[RSP+448]>
    URPARAM56 TEXTEQU <[RSP+456]>
    URPARAM57 TEXTEQU <[RSP+464]>
    URPARAM58 TEXTEQU <[RSP+472]>
    URPARAM59 TEXTEQU <[RSP+480]>
    URPARAM60 TEXTEQU <[RSP+488]>
    URPARAM61 TEXTEQU <[RSP+496]>
    URPARAM62 TEXTEQU <[RSP+504]>
    URPARAM63 TEXTEQU <[RSP+512]>
    ;/* 32bits*/
    UDRET TEXTEQU <EAX>
    UDRETURN TEXTEQU <EAX>
    UDSIDX TEXTEQU <ESI>
    UDDIDX TEXTEQU <EDI>
    UDBPTR TEXTEQU <EBP>
    UDSPTR TEXTEQU <ESP>
    UDBASE TEXTEQU <EBX>
    UDTHIS TEXTEQU <ECX>
    UDPARAM0 TEXTEQU <ECX>
    UDPARAM1 TEXTEQU <EDX>
    UDPARAM2 TEXTEQU <R8D>
    UDPARAM3 TEXTEQU <R9D>
    UDPARAM4 TEXTEQU <[ESP+20]>
    UDPARAM5 TEXTEQU <[ESP+24]>
    UDPARAM6 TEXTEQU <[ESP+28]>
    UDPARAM7 TEXTEQU <[ESP+32]>
    UDPARAM8 TEXTEQU <[ESP+36]>
    UDPARAM9 TEXTEQU <[ESP+40]>
    UDPARAM10 TEXTEQU <[ESP+44]>
    UDPARAM11 TEXTEQU <[ESP+48]>
    UDPARAM12 TEXTEQU <[ESP+52]>
    UDPARAM13 TEXTEQU <[ESP+56]>
    UDPARAM14 TEXTEQU <[ESP+60]>
    UDPARAM15 TEXTEQU <[ESP+64]>
    UDPARAM16 TEXTEQU <[ESP+68]>
    UDPARAM17 TEXTEQU <[ESP+72]>
    UDPARAM18 TEXTEQU <[ESP+76]>
    UDPARAM19 TEXTEQU <[ESP+80]>
    UDPARAM20 TEXTEQU <[ESP+84]>
    UDPARAM21 TEXTEQU <[ESP+88]>
    UDPARAM22 TEXTEQU <[ESP+92]>
    UDPARAM23 TEXTEQU <[ESP+96]>
    UDPARAM24 TEXTEQU <[ESP+100]>
    UDPARAM25 TEXTEQU <[ESP+104]>
    UDPARAM26 TEXTEQU <[ESP+108]>
    UDPARAM27 TEXTEQU <[ESP+112]>
    UDPARAM28 TEXTEQU <[ESP+116]>
    UDPARAM29 TEXTEQU <[ESP+120]>
    UDPARAM30 TEXTEQU <[ESP+124]>
    UDPARAM31 TEXTEQU <[ESP+128]>
    UDPARAM32 TEXTEQU <[ESP+132]>
    UDPARAM33 TEXTEQU <[ESP+136]>
    UDPARAM34 TEXTEQU <[ESP+140]>
    UDPARAM35 TEXTEQU <[ESP+144]>
    UDPARAM36 TEXTEQU <[ESP+148]>
    UDPARAM37 TEXTEQU <[ESP+152]>
    UDPARAM38 TEXTEQU <[ESP+156]>
    UDPARAM39 TEXTEQU <[ESP+160]>
    UDPARAM40 TEXTEQU <[ESP+164]>
    UDPARAM41 TEXTEQU <[ESP+168]>
    UDPARAM42 TEXTEQU <[ESP+172]>
    UDPARAM43 TEXTEQU <[ESP+176]>
    UDPARAM44 TEXTEQU <[ESP+180]>
    UDPARAM45 TEXTEQU <[ESP+184]>
    UDPARAM46 TEXTEQU <[ESP+188]>
    UDPARAM47 TEXTEQU <[ESP+192]>
    UDPARAM48 TEXTEQU <[ESP+196]>
    UDPARAM49 TEXTEQU <[ESP+200]>
    UDPARAM50 TEXTEQU <[ESP+204]>
    UDPARAM51 TEXTEQU <[ESP+208]>
    UDPARAM52 TEXTEQU <[ESP+212]>
    UDPARAM53 TEXTEQU <[ESP+216]>
    UDPARAM54 TEXTEQU <[ESP+220]>
    UDPARAM55 TEXTEQU <[ESP+224]>
    UDPARAM56 TEXTEQU <[ESP+228]>
    UDPARAM57 TEXTEQU <[ESP+232]>
    UDPARAM58 TEXTEQU <[ESP+236]>
    UDPARAM59 TEXTEQU <[ESP+240]>
    UDPARAM60 TEXTEQU <[ESP+244]>
    UDPARAM61 TEXTEQU <[ESP+248]>
    UDPARAM62 TEXTEQU <[ESP+252]>
    UDPARAM63 TEXTEQU <[ESP+256]>
    ;/* 16bits*/
    UWRET TEXTEQU <AX>
    UWRETURN TEXTEQU <AX>
    UWSIDX TEXTEQU <SI>
    UWDIDX TEXTEQU <DI>
    UWBPTR TEXTEQU <BP>
    UWSPTR TEXTEQU <SP>
    UWBASE TEXTEQU <BX>
    UWTHIS TEXTEQU <CX>
    UWPARAM0 TEXTEQU <CX>
    UWPARAM1 TEXTEQU <DX>
    UWPARAM2 TEXTEQU <R8W>
    UWPARAM3 TEXTEQU <R9W>
    UWPARAM4 TEXTEQU <[SP+10]>
    UWPARAM5 TEXTEQU <[SP+12]>
    UWPARAM6 TEXTEQU <[SP+14]>
    UWPARAM7 TEXTEQU <[SP+16]>
    UWPARAM8 TEXTEQU <[SP+18]>
    UWPARAM9 TEXTEQU <[SP+20]>
    UWPARAM10 TEXTEQU <[SP+22]>
    UWPARAM11 TEXTEQU <[SP+24]>
    UWPARAM12 TEXTEQU <[SP+26]>
    UWPARAM13 TEXTEQU <[SP+28]>
    UWPARAM14 TEXTEQU <[SP+30]>
    UWPARAM15 TEXTEQU <[SP+32]>
    UWPARAM16 TEXTEQU <[SP+34]>
    UWPARAM17 TEXTEQU <[SP+36]>
    UWPARAM18 TEXTEQU <[SP+38]>
    UWPARAM19 TEXTEQU <[SP+40]>
    UWPARAM20 TEXTEQU <[SP+42]>
    UWPARAM21 TEXTEQU <[SP+44]>
    UWPARAM22 TEXTEQU <[SP+46]>
    UWPARAM23 TEXTEQU <[SP+48]>
    UWPARAM24 TEXTEQU <[SP+50]>
    UWPARAM25 TEXTEQU <[SP+52]>
    UWPARAM26 TEXTEQU <[SP+54]>
    UWPARAM27 TEXTEQU <[SP+56]>
    UWPARAM28 TEXTEQU <[SP+58]>
    UWPARAM29 TEXTEQU <[SP+60]>
    UWPARAM30 TEXTEQU <[SP+62]>
    UWPARAM31 TEXTEQU <[SP+64]>
    UWPARAM32 TEXTEQU <[SP+66]>
    UWPARAM33 TEXTEQU <[SP+68]>
    UWPARAM34 TEXTEQU <[SP+70]>
    UWPARAM35 TEXTEQU <[SP+72]>
    UWPARAM36 TEXTEQU <[SP+74]>
    UWPARAM37 TEXTEQU <[SP+76]>
    UWPARAM38 TEXTEQU <[SP+78]>
    UWPARAM39 TEXTEQU <[SP+80]>
    UWPARAM40 TEXTEQU <[SP+82]>
    UWPARAM41 TEXTEQU <[SP+84]>
    UWPARAM42 TEXTEQU <[SP+86]>
    UWPARAM43 TEXTEQU <[SP+88]>
    UWPARAM44 TEXTEQU <[SP+90]>
    UWPARAM45 TEXTEQU <[SP+92]>
    UWPARAM46 TEXTEQU <[SP+94]>
    UWPARAM47 TEXTEQU <[SP+96]>
    UWPARAM48 TEXTEQU <[SP+98]>
    UWPARAM49 TEXTEQU <[SP+100]>
    UWPARAM50 TEXTEQU <[SP+102]>
    UWPARAM51 TEXTEQU <[SP+104]>
    UWPARAM52 TEXTEQU <[SP+106]>
    UWPARAM53 TEXTEQU <[SP+108]>
    UWPARAM54 TEXTEQU <[SP+110]>
    UWPARAM55 TEXTEQU <[SP+112]>
    UWPARAM56 TEXTEQU <[SP+114]>
    UWPARAM57 TEXTEQU <[SP+116]>
    UWPARAM58 TEXTEQU <[SP+118]>
    UWPARAM59 TEXTEQU <[SP+120]>
    UWPARAM60 TEXTEQU <[SP+122]>
    UWPARAM61 TEXTEQU <[SP+124]>
    UWPARAM62 TEXTEQU <[SP+126]>
    UWPARAM63 TEXTEQU <[SP+128]>
    ;/* 8bits*/
    UBRET TEXTEQU <AL>
    UBRETURN TEXTEQU <AL>
    UBSIDX TEXTEQU <SIL>
    UBDIDX TEXTEQU <DIL>
    UBBPTR TEXTEQU <BPL>
    UBSPTR TEXTEQU <SPL>
    UBBASE TEXTEQU <BL>
    UBTHIS TEXTEQU <CL>
    UBPARAM0 TEXTEQU <CL>
    UBPARAM1 TEXTEQU <DL>
    UBPARAM2 TEXTEQU <R8B>
    UBPARAM3 TEXTEQU <R9B>
    UBPARAM4 TEXTEQU <[SPL+5]>
    UBPARAM5 TEXTEQU <[SPL+6]>
    UBPARAM6 TEXTEQU <[SPL+7]>
    UBPARAM7 TEXTEQU <[SPL+8]>
    UBPARAM8 TEXTEQU <[SPL+9]>
    UBPARAM9 TEXTEQU <[SPL+10]>
    UBPARAM10 TEXTEQU <[SPL+11]>
    UBPARAM11 TEXTEQU <[SPL+12]>
    UBPARAM12 TEXTEQU <[SPL+13]>
    UBPARAM13 TEXTEQU <[SPL+14]>
    UBPARAM14 TEXTEQU <[SPL+15]>
    UBPARAM15 TEXTEQU <[SPL+16]>
    UBPARAM16 TEXTEQU <[SPL+17]>
    UBPARAM17 TEXTEQU <[SPL+18]>
    UBPARAM18 TEXTEQU <[SPL+19]>
    UBPARAM19 TEXTEQU <[SPL+20]>
    UBPARAM20 TEXTEQU <[SPL+21]>
    UBPARAM21 TEXTEQU <[SPL+22]>
    UBPARAM22 TEXTEQU <[SPL+23]>
    UBPARAM23 TEXTEQU <[SPL+24]>
    UBPARAM24 TEXTEQU <[SPL+25]>
    UBPARAM25 TEXTEQU <[SPL+26]>
    UBPARAM26 TEXTEQU <[SPL+27]>
    UBPARAM27 TEXTEQU <[SPL+28]>
    UBPARAM28 TEXTEQU <[SPL+29]>
    UBPARAM29 TEXTEQU <[SPL+30]>
    UBPARAM30 TEXTEQU <[SPL+31]>
    UBPARAM31 TEXTEQU <[SPL+32]>
    UBPARAM32 TEXTEQU <[SPL+33]>
    UBPARAM33 TEXTEQU <[SPL+34]>
    UBPARAM34 TEXTEQU <[SPL+35]>
    UBPARAM35 TEXTEQU <[SPL+36]>
    UBPARAM36 TEXTEQU <[SPL+37]>
    UBPARAM37 TEXTEQU <[SPL+38]>
    UBPARAM38 TEXTEQU <[SPL+39]>
    UBPARAM39 TEXTEQU <[SPL+40]>
    UBPARAM40 TEXTEQU <[SPL+41]>
    UBPARAM41 TEXTEQU <[SPL+42]>
    UBPARAM42 TEXTEQU <[SPL+43]>
    UBPARAM43 TEXTEQU <[SPL+44]>
    UBPARAM44 TEXTEQU <[SPL+45]>
    UBPARAM45 TEXTEQU <[SPL+46]>
    UBPARAM46 TEXTEQU <[SPL+47]>
    UBPARAM47 TEXTEQU <[SPL+48]>
    UBPARAM48 TEXTEQU <[SPL+49]>
    UBPARAM49 TEXTEQU <[SPL+50]>
    UBPARAM50 TEXTEQU <[SPL+51]>
    UBPARAM51 TEXTEQU <[SPL+52]>
    UBPARAM52 TEXTEQU <[SPL+53]>
    UBPARAM53 TEXTEQU <[SPL+54]>
    UBPARAM54 TEXTEQU <[SPL+55]>
    UBPARAM55 TEXTEQU <[SPL+56]>
    UBPARAM56 TEXTEQU <[SPL+57]>
    UBPARAM57 TEXTEQU <[SPL+58]>
    UBPARAM58 TEXTEQU <[SPL+59]>
    UBPARAM59 TEXTEQU <[SPL+60]>
    UBPARAM60 TEXTEQU <[SPL+61]>
    UBPARAM61 TEXTEQU <[SPL+62]>
    UBPARAM62 TEXTEQU <[SPL+63]>
    UBPARAM63 TEXTEQU <[SPL+64]>
    ENDIF
    ;/*__WIN64__*/

    IFDEF __WIN32__
    ;/* Vectorcall or Fastcall*/
    ;/* 32bits*/
    RRET TEXTEQU <EAX>
    RRETURN TEXTEQU <EAX>
    RSIDX TEXTEQU <ESI>
    RDIDX TEXTEQU <EDI>
    RBPTR TEXTEQU <EBP>
    RSPTR TEXTEQU <ESP>
    RBASE TEXTEQU <EBX>
    RPARAM0 TEXTEQU <ECX>
    RPARAM1 TEXTEQU <EDX>
    RPARAM2 TEXTEQU <[ESP+12]>
    RPARAM3 TEXTEQU <[ESP+16]>
    RPARAM4 TEXTEQU <[ESP+20]>
    RPARAM5 TEXTEQU <[ESP+24]>
    RPARAM6 TEXTEQU <[ESP+28]>
    RPARAM7 TEXTEQU <[ESP+32]>
    RPARAM8 TEXTEQU <[ESP+36]>
    RPARAM9 TEXTEQU <[ESP+40]>
    RPARAM10 TEXTEQU <[ESP+44]>
    RPARAM11 TEXTEQU <[ESP+48]>
    RPARAM12 TEXTEQU <[ESP+52]>
    RPARAM13 TEXTEQU <[ESP+56]>
    RPARAM13 TEXTEQU <[ESP+60]>
    RPARAM14 TEXTEQU <[ESP+64]>
    RPARAM15 TEXTEQU <[ESP+68]>
    RPARAM16 TEXTEQU <[ESP+72]>
    RPARAM17 TEXTEQU <[ESP+76]>
    RPARAM19 TEXTEQU <[ESP+80]>
    RPARAM20 TEXTEQU <[ESP+84]>
    RPARAM21 TEXTEQU <[ESP+88]>
    RPARAM22 TEXTEQU <[ESP+92]>
    RPARAM23 TEXTEQU <[ESP+96]>
    RPARAM24 TEXTEQU <[ESP+100]>
    RPARAM25 TEXTEQU <[ESP+104]>
    RPARAM26 TEXTEQU <[ESP+108]>
    RPARAM27 TEXTEQU <[ESP+112]>
    RPARAM28 TEXTEQU <[ESP+116]>
    RPARAM29 TEXTEQU <[ESP+120]>
    RPARAM30 TEXTEQU <[ESP+124]>
    RPARAM31 TEXTEQU <[ESP+128]>
    RPARAM32 TEXTEQU <[ESP+132]>
    RPARAM33 TEXTEQU <[ESP+136]>
    RPARAM34 TEXTEQU <[ESP+140]>
    RPARAM35 TEXTEQU <[ESP+144]>
    RPARAM36 TEXTEQU <[ESP+148]>
    RPARAM37 TEXTEQU <[ESP+152]>
    RPARAM38 TEXTEQU <[ESP+156]>
    RPARAM39 TEXTEQU <[ESP+160]>
    RPARAM40 TEXTEQU <[ESP+164]>
    RPARAM41 TEXTEQU <[ESP+168]>
    RPARAM42 TEXTEQU <[ESP+172]>
    RPARAM43 TEXTEQU <[ESP+176]>
    RPARAM44 TEXTEQU <[ESP+180]>
    RPARAM45 TEXTEQU <[ESP+184]>
    RPARAM46 TEXTEQU <[ESP+188]>
    RPARAM47 TEXTEQU <[ESP+192]>
    RPARAM48 TEXTEQU <[ESP+196]>
    RPARAM49 TEXTEQU <[ESP+200]>
    RPARAM50 TEXTEQU <[ESP+204]>
    RPARAM51 TEXTEQU <[ESP+208]>
    RPARAM52 TEXTEQU <[ESP+212]>
    RPARAM53 TEXTEQU <[ESP+216]>
    RPARAM54 TEXTEQU <[ESP+220]>
    RPARAM55 TEXTEQU <[ESP+224]>
    RPARAM56 TEXTEQU <[ESP+228]>
    RPARAM57 TEXTEQU <[ESP+232]>
    RPARAM58 TEXTEQU <[ESP+236]>
    RPARAM59 TEXTEQU <[ESP+240]>
    RPARAM60 TEXTEQU <[ESP+244]>
    RPARAM61 TEXTEQU <[ESP+248]>
    RPARAM62 TEXTEQU <[ESP+252]>
    RPARAM63 TEXTEQU <[ESP+256]>
    ;/* 32bits*/
    DRET TEXTEQU <EAX>
    DRETURN TEXTEQU <EAX>
    DSIDX TEXTEQU <ESI>
    DDIDX TEXTEQU <EDI>
    DBPTR TEXTEQU <EBP>
    DSPTR TEXTEQU <ESP>
    DBASE TEXTEQU <EBX>
    DPARAM0 TEXTEQU <ECX>
    DPARAM1 TEXTEQU <EDX>
    DPARAM2 TEXTEQU <[ESP+12]>
    DPARAM3 TEXTEQU <[ESP+16]>
    DPARAM4 TEXTEQU <[ESP+20]>
    DPARAM5 TEXTEQU <[ESP+24]>
    DPARAM6 TEXTEQU <[ESP+28]>
    DPARAM7 TEXTEQU <[ESP+32]>
    DPARAM8 TEXTEQU <[ESP+36]>
    DPARAM9 TEXTEQU <[ESP+40]>
    DPARAM10 TEXTEQU <[ESP+44]>
    DPARAM11 TEXTEQU <[ESP+48]>
    DPARAM12 TEXTEQU <[ESP+52]>
    DPARAM13 TEXTEQU <[ESP+56]>
    DPARAM14 TEXTEQU <[ESP+60]>
    DPARAM15 TEXTEQU <[ESP+64]>
    DPARAM16 TEXTEQU <[ESP+68]>
    DPARAM17 TEXTEQU <[ESP+72]>
    DPARAM18 TEXTEQU <[ESP+76]>
    DPARAM19 TEXTEQU <[ESP+80]>
    DPARAM20 TEXTEQU <[ESP+84]>
    DPARAM21 TEXTEQU <[ESP+88]>
    DPARAM22 TEXTEQU <[ESP+92]>
    DPARAM23 TEXTEQU <[ESP+96]>
    DPARAM24 TEXTEQU <[ESP+100]>
    DPARAM25 TEXTEQU <[ESP+104]>
    DPARAM26 TEXTEQU <[ESP+108]>
    DPARAM27 TEXTEQU <[ESP+112]>
    DPARAM28 TEXTEQU <[ESP+116]>
    DPARAM29 TEXTEQU <[ESP+120]>
    DPARAM30 TEXTEQU <[ESP+124]>
    DPARAM31 TEXTEQU <[ESP+128]>
    DPARAM32 TEXTEQU <[ESP+132]>
    DPARAM33 TEXTEQU <[ESP+136]>
    DPARAM34 TEXTEQU <[ESP+140]>
    DPARAM35 TEXTEQU <[ESP+144]>
    DPARAM36 TEXTEQU <[ESP+148]>
    DPARAM37 TEXTEQU <[ESP+152]>
    DPARAM38 TEXTEQU <[ESP+156]>
    DPARAM39 TEXTEQU <[ESP+160]>
    DPARAM40 TEXTEQU <[ESP+164]>
    DPARAM41 TEXTEQU <[ESP+168]>
    DPARAM42 TEXTEQU <[ESP+172]>
    DPARAM43 TEXTEQU <[ESP+176]>
    DPARAM44 TEXTEQU <[ESP+180]>
    DPARAM45 TEXTEQU <[ESP+184]>
    DPARAM46 TEXTEQU <[ESP+188]>
    DPARAM47 TEXTEQU <[ESP+192]>
    DPARAM48 TEXTEQU <[ESP+196]>
    DPARAM49 TEXTEQU <[ESP+200]>
    DPARAM50 TEXTEQU <[ESP+204]>
    DPARAM51 TEXTEQU <[ESP+208]>
    DPARAM52 TEXTEQU <[ESP+212]>
    DPARAM53 TEXTEQU <[ESP+216]>
    DPARAM54 TEXTEQU <[ESP+220]>
    DPARAM55 TEXTEQU <[ESP+224]>
    DPARAM56 TEXTEQU <[ESP+228]>
    DPARAM57 TEXTEQU <[ESP+232]>
    DPARAM58 TEXTEQU <[ESP+236]>
    DPARAM59 TEXTEQU <[ESP+240]>
    DPARAM60 TEXTEQU <[ESP+244]>
    DPARAM61 TEXTEQU <[ESP+248]>
    DPARAM62 TEXTEQU <[ESP+252]>
    DPARAM63 TEXTEQU <[ESP+256]>
    ;/* 16bits*/
    WRET TEXTEQU <AX>
    WRETURN TEXTEQU <AX>
    WSIDX TEXTEQU <SI>
    WDIDX TEXTEQU <DI>
    WBPTR TEXTEQU <BP>
    WSPTR TEXTEQU <SP>
    WBASE TEXTEQU <BX>
    WPARAM0 TEXTEQU <CX>
    WPARAM1 TEXTEQU <DX>
    WPARAM2 TEXTEQU <[SP+6]>
    WPARAM3 TEXTEQU <[SP+8]>
    WPARAM4 TEXTEQU <[SP+10]>
    WPARAM5 TEXTEQU <[SP+12]>
    WPARAM6 TEXTEQU <[SP+14]>
    WPARAM7 TEXTEQU <[SP+16]>
    WPARAM8 TEXTEQU <[SP+18]>
    WPARAM9 TEXTEQU <[SP+20]>
    WPARAM10 TEXTEQU <[SP+22]>
    WPARAM11 TEXTEQU <[SP+24]>
    WPARAM12 TEXTEQU <[SP+26]>
    WPARAM13 TEXTEQU <[SP+28]>
    WPARAM14 TEXTEQU <[SP+30]>
    WPARAM15 TEXTEQU <[SP+32]>
    WPARAM16 TEXTEQU <[SP+34]>
    WPARAM17 TEXTEQU <[SP+36]>
    WPARAM18 TEXTEQU <[SP+38]>
    WPARAM19 TEXTEQU <[SP+40]>
    WPARAM20 TEXTEQU <[SP+42]>
    WPARAM21 TEXTEQU <[SP+44]>
    WPARAM22 TEXTEQU <[SP+46]>
    WPARAM23 TEXTEQU <[SP+48]>
    WPARAM24 TEXTEQU <[SP+50]>
    WPARAM25 TEXTEQU <[SP+52]>
    WPARAM26 TEXTEQU <[SP+54]>
    WPARAM27 TEXTEQU <[SP+56]>
    WPARAM28 TEXTEQU <[SP+58]>
    WPARAM29 TEXTEQU <[SP+60]>
    WPARAM30 TEXTEQU <[SP+62]>
    WPARAM31 TEXTEQU <[SP+64]>
    WPARAM32 TEXTEQU <[SP+66]>
    WPARAM33 TEXTEQU <[SP+68]>
    WPARAM34 TEXTEQU <[SP+70]>
    WPARAM35 TEXTEQU <[SP+72]>
    WPARAM36 TEXTEQU <[SP+74]>
    WPARAM37 TEXTEQU <[SP+76]>
    WPARAM38 TEXTEQU <[SP+78]>
    WPARAM39 TEXTEQU <[SP+80]>
    WPARAM40 TEXTEQU <[SP+82]>
    WPARAM41 TEXTEQU <[SP+84]>
    WPARAM42 TEXTEQU <[SP+86]>
    WPARAM43 TEXTEQU <[SP+88]>
    WPARAM44 TEXTEQU <[SP+90]>
    WPARAM45 TEXTEQU <[SP+92]>
    WPARAM46 TEXTEQU <[SP+94]>
    WPARAM47 TEXTEQU <[SP+96]>
    WPARAM48 TEXTEQU <[SP+98]>
    WPARAM49 TEXTEQU <[SP+100]>
    WPARAM50 TEXTEQU <[SP+102]>
    WPARAM51 TEXTEQU <[SP+104]>
    WPARAM52 TEXTEQU <[SP+106]>
    WPARAM53 TEXTEQU <[SP+108]>
    WPARAM54 TEXTEQU <[SP+110]>
    WPARAM55 TEXTEQU <[SP+112]>
    WPARAM56 TEXTEQU <[SP+114]>
    WPARAM57 TEXTEQU <[SP+116]>
    WPARAM58 TEXTEQU <[SP+118]>
    WPARAM59 TEXTEQU <[SP+120]>
    WPARAM60 TEXTEQU <[SP+122]>
    WPARAM61 TEXTEQU <[SP+124]>
    WPARAM62 TEXTEQU <[SP+126]>
    WPARAM63 TEXTEQU <[SP+128]>
    ;/* 8bits*/
    BRET TEXTEQU <AL>
    BRETURN TEXTEQU <AL>
    BSIDX TEXTEQU <SIL>
    BDIDX TEXTEQU <DIL>
    BBPTR TEXTEQU <BPL>
    BSPTR TEXTEQU <SPL>
    BBASE TEXTEQU <BL>
    BPARAM0 TEXTEQU <CL>
    BPARAM1 TEXTEQU <DL>
    BPARAM2 TEXTEQU <[SPL+3]>
    BPARAM3 TEXTEQU <[SPL+4]>
    BPARAM4 TEXTEQU <[SPL+5]>
    BPARAM5 TEXTEQU <[SPL+6]>
    BPARAM6 TEXTEQU <[SPL+7]>
    BPARAM7 TEXTEQU <[SPL+8]>
    BPARAM8 TEXTEQU <[SPL+9]>
    BPARAM9 TEXTEQU <[SPL+10]>
    BPARAM10 TEXTEQU <[SPL+11]>
    BPARAM11 TEXTEQU <[SPL+12]>
    BPARAM12 TEXTEQU <[SPL+13]>
    BPARAM13 TEXTEQU <[SPL+14]>
    BPARAM14 TEXTEQU <[SPL+15]>
    BPARAM15 TEXTEQU <[SPL+16]>
    BPARAM16 TEXTEQU <[SPL+17]>
    BPARAM17 TEXTEQU <[SPL+18]>
    BPARAM18 TEXTEQU <[SPL+19]>
    BPARAM19 TEXTEQU <[SPL+20]>
    BPARAM20 TEXTEQU <[SPL+21]>
    BPARAM21 TEXTEQU <[SPL+22]>
    BPARAM22 TEXTEQU <[SPL+23]>
    BPARAM23 TEXTEQU <[SPL+24]>
    BPARAM24 TEXTEQU <[SPL+25]>
    BPARAM25 TEXTEQU <[SPL+26]>
    BPARAM26 TEXTEQU <[SPL+27]>
    BPARAM27 TEXTEQU <[SPL+28]>
    BPARAM28 TEXTEQU <[SPL+29]>
    BPARAM29 TEXTEQU <[SPL+30]>
    BPARAM30 TEXTEQU <[SPL+31]>
    BPARAM31 TEXTEQU <[SPL+32]>
    BPARAM32 TEXTEQU <[SPL+33]>
    BPARAM33 TEXTEQU <[SPL+34]>
    BPARAM34 TEXTEQU <[SPL+35]>
    BPARAM35 TEXTEQU <[SPL+36]>
    BPARAM36 TEXTEQU <[SPL+37]>
    BPARAM37 TEXTEQU <[SPL+38]>
    BPARAM38 TEXTEQU <[SPL+39]>
    BPARAM39 TEXTEQU <[SPL+40]>
    BPARAM40 TEXTEQU <[SPL+41]>
    BPARAM41 TEXTEQU <[SPL+42]>
    BPARAM42 TEXTEQU <[SPL+43]>
    BPARAM43 TEXTEQU <[SPL+44]>
    BPARAM44 TEXTEQU <[SPL+45]>
    BPARAM45 TEXTEQU <[SPL+46]>
    BPARAM46 TEXTEQU <[SPL+47]>
    BPARAM47 TEXTEQU <[SPL+48]>
    BPARAM48 TEXTEQU <[SPL+49]>
    BPARAM49 TEXTEQU <[SPL+50]>
    BPARAM50 TEXTEQU <[SPL+51]>
    BPARAM51 TEXTEQU <[SPL+52]>
    BPARAM52 TEXTEQU <[SPL+53]>
    BPARAM53 TEXTEQU <[SPL+54]>
    BPARAM54 TEXTEQU <[SPL+55]>
    BPARAM55 TEXTEQU <[SPL+56]>
    BPARAM56 TEXTEQU <[SPL+57]>
    BPARAM57 TEXTEQU <[SPL+58]>
    BPARAM58 TEXTEQU <[SPL+59]>
    BPARAM59 TEXTEQU <[SPL+60]>
    BPARAM60 TEXTEQU <[SPL+61]>
    BPARAM61 TEXTEQU <[SPL+62]>
    BPARAM62 TEXTEQU <[SPL+63]>
    BPARAM63 TEXTEQU <[SPL+64]>

    ;/* Regcall*/
    ;/* 32bits*/
    RRRET TEXTEQU <EAX>
    RRRETURN TEXTEQU <EAX>
    RRSIDX TEXTEQU <ESI>
    RRDIDX TEXTEQU <EDI>
    RRBPTR TEXTEQU <EBP>
    RRSPTR TEXTEQU <ESP>
    RRBASE TEXTEQU <EBX>
    RRPARAM0 TEXTEQU <ECX>
    RRPARAM1 TEXTEQU <EDX>
    RRPARAM2 TEXTEQU <EDI>
    RRPARAM3 TEXTEQU <ESI>
    RRPARAM4 TEXTEQU <[ESP+20]>
    RRPARAM5 TEXTEQU <[ESP+24]>
    RRPARAM6 TEXTEQU <[ESP+28]>
    RRPARAM7 TEXTEQU <[ESP+32]>
    RRPARAM8 TEXTEQU <[ESP+36]>
    RRPARAM9 TEXTEQU <[ESP+40]>
    RRPARAM10 TEXTEQU <[ESP+44]>
    RRPARAM11 TEXTEQU <[ESP+48]>
    RRPARAM12 TEXTEQU <[ESP+52]>
    RRPARAM13 TEXTEQU <[ESP+56]>
    RRPARAM13 TEXTEQU <[ESP+60]>
    RRPARAM14 TEXTEQU <[ESP+64]>
    RRPARAM15 TEXTEQU <[ESP+68]>
    RRPARAM16 TEXTEQU <[ESP+72]>
    RRPARAM17 TEXTEQU <[ESP+76]>
    RRPARAM19 TEXTEQU <[ESP+80]>
    RRPARAM20 TEXTEQU <[ESP+84]>
    RRPARAM21 TEXTEQU <[ESP+88]>
    RRPARAM22 TEXTEQU <[ESP+92]>
    RRPARAM23 TEXTEQU <[ESP+96]>
    RRPARAM24 TEXTEQU <[ESP+100]>
    RRPARAM25 TEXTEQU <[ESP+104]>
    RRPARAM26 TEXTEQU <[ESP+108]>
    RRPARAM27 TEXTEQU <[ESP+112]>
    RRPARAM28 TEXTEQU <[ESP+116]>
    RRPARAM29 TEXTEQU <[ESP+120]>
    RRPARAM30 TEXTEQU <[ESP+124]>
    RRPARAM31 TEXTEQU <[ESP+128]>
    RRPARAM32 TEXTEQU <[ESP+132]>
    RRPARAM33 TEXTEQU <[ESP+136]>
    RRPARAM34 TEXTEQU <[ESP+140]>
    RRPARAM35 TEXTEQU <[ESP+144]>
    RRPARAM36 TEXTEQU <[ESP+148]>
    RRPARAM37 TEXTEQU <[ESP+152]>
    RRPARAM38 TEXTEQU <[ESP+156]>
    RRPARAM39 TEXTEQU <[ESP+160]>
    RRPARAM40 TEXTEQU <[ESP+164]>
    RRPARAM41 TEXTEQU <[ESP+168]>
    RRPARAM42 TEXTEQU <[ESP+172]>
    RRPARAM43 TEXTEQU <[ESP+176]>
    RRPARAM44 TEXTEQU <[ESP+180]>
    RRPARAM45 TEXTEQU <[ESP+184]>
    RRPARAM46 TEXTEQU <[ESP+188]>
    RRPARAM47 TEXTEQU <[ESP+192]>
    RRPARAM48 TEXTEQU <[ESP+196]>
    RRPARAM49 TEXTEQU <[ESP+200]>
    RRPARAM50 TEXTEQU <[ESP+204]>
    RRPARAM51 TEXTEQU <[ESP+208]>
    RRPARAM52 TEXTEQU <[ESP+212]>
    RRPARAM53 TEXTEQU <[ESP+216]>
    RRPARAM54 TEXTEQU <[ESP+220]>
    RRPARAM55 TEXTEQU <[ESP+224]>
    RRPARAM56 TEXTEQU <[ESP+228]>
    RRPARAM57 TEXTEQU <[ESP+232]>
    RRPARAM58 TEXTEQU <[ESP+236]>
    RRPARAM59 TEXTEQU <[ESP+240]>
    RRPARAM60 TEXTEQU <[ESP+244]>
    RRPARAM61 TEXTEQU <[ESP+248]>
    RRPARAM62 TEXTEQU <[ESP+252]>
    RRPARAM63 TEXTEQU <[ESP+256]>
    ;/* 32bits*/
    RDRET TEXTEQU <EAX>
    RDRETURN TEXTEQU <EAX>
    RDSIDX TEXTEQU <ESI>
    RDDIDX TEXTEQU <EDI>
    RDBPTR TEXTEQU <EBP>
    RDSPTR TEXTEQU <ESP>
    RDBASE TEXTEQU <EBX>
    RDPARAM0 TEXTEQU <ECX>
    RDPARAM1 TEXTEQU <EDX>
    RDPARAM2 TEXTEQU <EDI>
    RDPARAM3 TEXTEQU <ESI>
    RDPARAM4 TEXTEQU <[ESP+20]>
    RDPARAM5 TEXTEQU <[ESP+24]>
    RDPARAM6 TEXTEQU <[ESP+28]>
    RDPARAM7 TEXTEQU <[ESP+32]>
    RDPARAM8 TEXTEQU <[ESP+36]>
    RDPARAM9 TEXTEQU <[ESP+40]>
    RDPARAM10 TEXTEQU <[ESP+44]>
    RDPARAM11 TEXTEQU <[ESP+48]>
    RDPARAM12 TEXTEQU <[ESP+52]>
    RDPARAM13 TEXTEQU <[ESP+56]>
    RDPARAM14 TEXTEQU <[ESP+60]>
    RDPARAM15 TEXTEQU <[ESP+64]>
    RDPARAM16 TEXTEQU <[ESP+68]>
    RDPARAM17 TEXTEQU <[ESP+72]>
    RDPARAM18 TEXTEQU <[ESP+76]>
    RDPARAM19 TEXTEQU <[ESP+80]>
    RDPARAM20 TEXTEQU <[ESP+84]>
    RDPARAM21 TEXTEQU <[ESP+88]>
    RDPARAM22 TEXTEQU <[ESP+92]>
    RDPARAM23 TEXTEQU <[ESP+96]>
    RDPARAM24 TEXTEQU <[ESP+100]>
    RDPARAM25 TEXTEQU <[ESP+104]>
    RDPARAM26 TEXTEQU <[ESP+108]>
    RDPARAM27 TEXTEQU <[ESP+112]>
    RDPARAM28 TEXTEQU <[ESP+116]>
    RDPARAM29 TEXTEQU <[ESP+120]>
    RDPARAM30 TEXTEQU <[ESP+124]>
    RDPARAM31 TEXTEQU <[ESP+128]>
    RDPARAM32 TEXTEQU <[ESP+132]>
    RDPARAM33 TEXTEQU <[ESP+136]>
    RDPARAM34 TEXTEQU <[ESP+140]>
    RDPARAM35 TEXTEQU <[ESP+144]>
    RDPARAM36 TEXTEQU <[ESP+148]>
    RDPARAM37 TEXTEQU <[ESP+152]>
    RDPARAM38 TEXTEQU <[ESP+156]>
    RDPARAM39 TEXTEQU <[ESP+160]>
    RDPARAM40 TEXTEQU <[ESP+164]>
    RDPARAM41 TEXTEQU <[ESP+168]>
    RDPARAM42 TEXTEQU <[ESP+172]>
    RDPARAM43 TEXTEQU <[ESP+176]>
    RDPARAM44 TEXTEQU <[ESP+180]>
    RDPARAM45 TEXTEQU <[ESP+184]>
    RDPARAM46 TEXTEQU <[ESP+188]>
    RDPARAM47 TEXTEQU <[ESP+192]>
    RDPARAM48 TEXTEQU <[ESP+196]>
    RDPARAM49 TEXTEQU <[ESP+200]>
    RDPARAM50 TEXTEQU <[ESP+204]>
    RDPARAM51 TEXTEQU <[ESP+208]>
    RDPARAM52 TEXTEQU <[ESP+212]>
    RDPARAM53 TEXTEQU <[ESP+216]>
    RDPARAM54 TEXTEQU <[ESP+220]>
    RDPARAM55 TEXTEQU <[ESP+224]>
    RDPARAM56 TEXTEQU <[ESP+228]>
    RDPARAM57 TEXTEQU <[ESP+232]>
    RDPARAM58 TEXTEQU <[ESP+236]>
    RDPARAM59 TEXTEQU <[ESP+240]>
    RDPARAM60 TEXTEQU <[ESP+244]>
    RDPARAM61 TEXTEQU <[ESP+248]>
    RDPARAM62 TEXTEQU <[ESP+252]>
    RDPARAM63 TEXTEQU <[ESP+256]>
    ;/* 16bits*/
    RWRET TEXTEQU <AX>
    RWRETURN TEXTEQU <AX>
    RWSIDX TEXTEQU <SI>
    RWDIDX TEXTEQU <DI>
    RWBPTR TEXTEQU <BP>
    RWSPTR TEXTEQU <SP>
    RWBASE TEXTEQU <BX>
    RWPARAM0 TEXTEQU <CX>
    RWPARAM1 TEXTEQU <DX>
    RWPARAM2 TEXTEQU <DI>
    RWPARAM3 TEXTEQU <SI>
    RWPARAM4 TEXTEQU <[SP+10]>
    RWPARAM5 TEXTEQU <[SP+12]>
    RWPARAM6 TEXTEQU <[SP+14]>
    RWPARAM7 TEXTEQU <[SP+16]>
    RWPARAM8 TEXTEQU <[SP+18]>
    RWPARAM9 TEXTEQU <[SP+20]>
    RWPARAM10 TEXTEQU <[SP+22]>
    RWPARAM11 TEXTEQU <[SP+24]>
    RWPARAM12 TEXTEQU <[SP+26]>
    RWPARAM13 TEXTEQU <[SP+28]>
    RWPARAM14 TEXTEQU <[SP+30]>
    RWPARAM15 TEXTEQU <[SP+32]>
    RWPARAM16 TEXTEQU <[SP+34]>
    RWPARAM17 TEXTEQU <[SP+36]>
    RWPARAM18 TEXTEQU <[SP+38]>
    RWPARAM19 TEXTEQU <[SP+40]>
    RWPARAM20 TEXTEQU <[SP+42]>
    RWPARAM21 TEXTEQU <[SP+44]>
    RWPARAM22 TEXTEQU <[SP+46]>
    RWPARAM23 TEXTEQU <[SP+48]>
    RWPARAM24 TEXTEQU <[SP+50]>
    RWPARAM25 TEXTEQU <[SP+52]>
    RWPARAM26 TEXTEQU <[SP+54]>
    RWPARAM27 TEXTEQU <[SP+56]>
    RWPARAM28 TEXTEQU <[SP+58]>
    RWPARAM29 TEXTEQU <[SP+60]>
    RWPARAM30 TEXTEQU <[SP+62]>
    RWPARAM31 TEXTEQU <[SP+64]>
    RWPARAM32 TEXTEQU <[SP+66]>
    RWPARAM33 TEXTEQU <[SP+68]>
    RWPARAM34 TEXTEQU <[SP+70]>
    RWPARAM35 TEXTEQU <[SP+72]>
    RWPARAM36 TEXTEQU <[SP+74]>
    RWPARAM37 TEXTEQU <[SP+76]>
    RWPARAM38 TEXTEQU <[SP+78]>
    RWPARAM39 TEXTEQU <[SP+80]>
    RWPARAM40 TEXTEQU <[SP+82]>
    RWPARAM41 TEXTEQU <[SP+84]>
    RWPARAM42 TEXTEQU <[SP+86]>
    RWPARAM43 TEXTEQU <[SP+88]>
    RWPARAM44 TEXTEQU <[SP+90]>
    RWPARAM45 TEXTEQU <[SP+92]>
    RWPARAM46 TEXTEQU <[SP+94]>
    RWPARAM47 TEXTEQU <[SP+96]>
    RWPARAM48 TEXTEQU <[SP+98]>
    RWPARAM49 TEXTEQU <[SP+100]>
    RWPARAM50 TEXTEQU <[SP+102]>
    RWPARAM51 TEXTEQU <[SP+104]>
    RWPARAM52 TEXTEQU <[SP+106]>
    RWPARAM53 TEXTEQU <[SP+108]>
    RWPARAM54 TEXTEQU <[SP+110]>
    RWPARAM55 TEXTEQU <[SP+112]>
    RWPARAM56 TEXTEQU <[SP+114]>
    RWPARAM57 TEXTEQU <[SP+116]>
    RWPARAM58 TEXTEQU <[SP+118]>
    RWPARAM59 TEXTEQU <[SP+120]>
    RWPARAM60 TEXTEQU <[SP+122]>
    RWPARAM61 TEXTEQU <[SP+124]>
    RWPARAM62 TEXTEQU <[SP+126]>
    RWPARAM63 TEXTEQU <[SP+128]>
    ;/* 8bits*/
    RBRET TEXTEQU <AL>
    RBRETURN TEXTEQU <AL>
    RBSIDX TEXTEQU <SIL>
    RBDIDX TEXTEQU <DIL>
    RBBPTR TEXTEQU <BPL>
    RBSPTR TEXTEQU <SPL>
    RBBASE TEXTEQU <BL>
    RBPARAM0 TEXTEQU <CL>
    RBPARAM1 TEXTEQU <DL>
    RBPARAM2 TEXTEQU <DIL>
    RBPARAM3 TEXTEQU <SIL>
    RBPARAM4 TEXTEQU <[SPL+5]>
    RBPARAM5 TEXTEQU <[SPL+6]>
    RBPARAM6 TEXTEQU <[SPL+7]>
    RBPARAM7 TEXTEQU <[SPL+8]>
    RBPARAM8 TEXTEQU <[SPL+9]>
    RBPARAM9 TEXTEQU <[SPL+10]>
    RBPARAM10 TEXTEQU <[SPL+11]>
    RBPARAM11 TEXTEQU <[SPL+12]>
    RBPARAM12 TEXTEQU <[SPL+13]>
    RBPARAM13 TEXTEQU <[SPL+14]>
    RBPARAM14 TEXTEQU <[SPL+15]>
    RBPARAM15 TEXTEQU <[SPL+16]>
    RBPARAM16 TEXTEQU <[SPL+17]>
    RBPARAM17 TEXTEQU <[SPL+18]>
    RBPARAM18 TEXTEQU <[SPL+19]>
    RBPARAM19 TEXTEQU <[SPL+20]>
    RBPARAM20 TEXTEQU <[SPL+21]>
    RBPARAM21 TEXTEQU <[SPL+22]>
    RBPARAM22 TEXTEQU <[SPL+23]>
    RBPARAM23 TEXTEQU <[SPL+24]>
    RBPARAM24 TEXTEQU <[SPL+25]>
    RBPARAM25 TEXTEQU <[SPL+26]>
    RBPARAM26 TEXTEQU <[SPL+27]>
    RBPARAM27 TEXTEQU <[SPL+28]>
    RBPARAM28 TEXTEQU <[SPL+29]>
    RBPARAM29 TEXTEQU <[SPL+30]>
    RBPARAM30 TEXTEQU <[SPL+31]>
    RBPARAM31 TEXTEQU <[SPL+32]>
    RBPARAM32 TEXTEQU <[SPL+33]>
    RBPARAM33 TEXTEQU <[SPL+34]>
    RBPARAM34 TEXTEQU <[SPL+35]>
    RBPARAM35 TEXTEQU <[SPL+36]>
    RBPARAM36 TEXTEQU <[SPL+37]>
    RBPARAM37 TEXTEQU <[SPL+38]>
    RBPARAM38 TEXTEQU <[SPL+39]>
    RBPARAM39 TEXTEQU <[SPL+40]>
    RBPARAM40 TEXTEQU <[SPL+41]>
    RBPARAM41 TEXTEQU <[SPL+42]>
    RBPARAM42 TEXTEQU <[SPL+43]>
    RBPARAM43 TEXTEQU <[SPL+44]>
    RBPARAM44 TEXTEQU <[SPL+45]>
    RBPARAM45 TEXTEQU <[SPL+46]>
    RBPARAM46 TEXTEQU <[SPL+47]>
    RBPARAM47 TEXTEQU <[SPL+48]>
    RBPARAM48 TEXTEQU <[SPL+49]>
    RBPARAM49 TEXTEQU <[SPL+50]>
    RBPARAM50 TEXTEQU <[SPL+51]>
    RBPARAM51 TEXTEQU <[SPL+52]>
    RBPARAM52 TEXTEQU <[SPL+53]>
    RBPARAM53 TEXTEQU <[SPL+54]>
    RBPARAM54 TEXTEQU <[SPL+55]>
    RBPARAM55 TEXTEQU <[SPL+56]>
    RBPARAM56 TEXTEQU <[SPL+57]>
    RBPARAM57 TEXTEQU <[SPL+58]>
    RBPARAM58 TEXTEQU <[SPL+59]>
    RBPARAM59 TEXTEQU <[SPL+60]>
    RBPARAM60 TEXTEQU <[SPL+61]>
    RBPARAM61 TEXTEQU <[SPL+62]>
    RBPARAM62 TEXTEQU <[SPL+63]>
    RBPARAM63 TEXTEQU <[SPL+64]>

   ;/* Undefined call or cdecl*/
   ;/ 32bits*/
    URRET TEXTEQU <EAX>
    URRETURN TEXTEQU <EAX>
    URSIDX TEXTEQU <ESI>
    URDIDX TEXTEQU <EDI>
    URBPTR TEXTEQU <EBP>
    URSPTR TEXTEQU <ESP>
    URBASE TEXTEQU <EBX>
    URPARAM0 TEXTEQU <[ESP+4]>
    URPARAM1 TEXTEQU <[ESP+8]>
    URPARAM2 TEXTEQU <[ESP+12]>
    URPARAM3 TEXTEQU <[ESP+16]>
    URPARAM4 TEXTEQU <[ESP+20]>
    URPARAM5 TEXTEQU <[ESP+24]>
    URPARAM6 TEXTEQU <[ESP+28]>
    URPARAM7 TEXTEQU <[ESP+32]>
    URPARAM8 TEXTEQU <[ESP+36]>
    URPARAM9 TEXTEQU <[ESP+40]>
    URPARAM10 TEXTEQU <[ESP+44]>
    URPARAM11 TEXTEQU <[ESP+48]>
    URPARAM12 TEXTEQU <[ESP+52]>
    URPARAM13 TEXTEQU <[ESP+56]>
    URPARAM13 TEXTEQU <[ESP+60]>
    URPARAM14 TEXTEQU <[ESP+64]>
    URPARAM15 TEXTEQU <[ESP+68]>
    URPARAM16 TEXTEQU <[ESP+72]>
    URPARAM17 TEXTEQU <[ESP+76]>
    URPARAM19 TEXTEQU <[ESP+80]>
    URPARAM20 TEXTEQU <[ESP+84]>
    URPARAM21 TEXTEQU <[ESP+88]>
    URPARAM22 TEXTEQU <[ESP+92]>
    URPARAM23 TEXTEQU <[ESP+96]>
    URPARAM24 TEXTEQU <[ESP+100]>
    URPARAM25 TEXTEQU <[ESP+104]>
    URPARAM26 TEXTEQU <[ESP+108]>
    URPARAM27 TEXTEQU <[ESP+112]>
    URPARAM28 TEXTEQU <[ESP+116]>
    URPARAM29 TEXTEQU <[ESP+120]>
    URPARAM30 TEXTEQU <[ESP+124]>
    URPARAM31 TEXTEQU <[ESP+128]>
    URPARAM32 TEXTEQU <[ESP+132]>
    URPARAM33 TEXTEQU <[ESP+136]>
    URPARAM34 TEXTEQU <[ESP+140]>
    URPARAM35 TEXTEQU <[ESP+144]>
    URPARAM36 TEXTEQU <[ESP+148]>
    URPARAM37 TEXTEQU <[ESP+152]>
    URPARAM38 TEXTEQU <[ESP+156]>
    URPARAM39 TEXTEQU <[ESP+160]>
    URPARAM40 TEXTEQU <[ESP+164]>
    URPARAM41 TEXTEQU <[ESP+168]>
    URPARAM42 TEXTEQU <[ESP+172]>
    URPARAM43 TEXTEQU <[ESP+176]>
    URPARAM44 TEXTEQU <[ESP+180]>
    URPARAM45 TEXTEQU <[ESP+184]>
    URPARAM46 TEXTEQU <[ESP+188]>
    URPARAM47 TEXTEQU <[ESP+192]>
    URPARAM48 TEXTEQU <[ESP+196]>
    URPARAM49 TEXTEQU <[ESP+200]>
    URPARAM50 TEXTEQU <[ESP+204]>
    URPARAM51 TEXTEQU <[ESP+208]>
    URPARAM52 TEXTEQU <[ESP+212]>
    URPARAM53 TEXTEQU <[ESP+216]>
    URPARAM54 TEXTEQU <[ESP+220]>
    URPARAM55 TEXTEQU <[ESP+224]>
    URPARAM56 TEXTEQU <[ESP+228]>
    URPARAM57 TEXTEQU <[ESP+232]>
    URPARAM58 TEXTEQU <[ESP+236]>
    URPARAM59 TEXTEQU <[ESP+240]>
    URPARAM60 TEXTEQU <[ESP+244]>
    URPARAM61 TEXTEQU <[ESP+248]>
    URPARAM62 TEXTEQU <[ESP+252]>
    URPARAM63 TEXTEQU <[ESP+256]>
   ;/ 32bits*/
    UDRET TEXTEQU <EAX>
    UDRETURN TEXTEQU <EAX>
    UDSIDX TEXTEQU <ESI>
    UDDIDX TEXTEQU <EDI>
    UDBPTR TEXTEQU <EBP>
    UDSPTR TEXTEQU <ESP>
    UDBASE TEXTEQU <EBX>
    UDPARAM0 TEXTEQU <[ESP+4]>
    UDPARAM1 TEXTEQU <[ESP+8]>
    UDPARAM2 TEXTEQU <[ESP+12]>
    UDPARAM3 TEXTEQU <[ESP+16]>
    UDPARAM4 TEXTEQU <[ESP+20]>
    UDPARAM5 TEXTEQU <[ESP+24]>
    UDPARAM6 TEXTEQU <[ESP+28]>
    UDPARAM7 TEXTEQU <[ESP+32]>
    UDPARAM8 TEXTEQU <[ESP+36]>
    UDPARAM9 TEXTEQU <[ESP+40]>
    UDPARAM10 TEXTEQU <[ESP+44]>
    UDPARAM11 TEXTEQU <[ESP+48]>
    UDPARAM12 TEXTEQU <[ESP+52]>
    UDPARAM13 TEXTEQU <[ESP+56]>
    UDPARAM14 TEXTEQU <[ESP+60]>
    UDPARAM15 TEXTEQU <[ESP+64]>
    UDPARAM16 TEXTEQU <[ESP+68]>
    UDPARAM17 TEXTEQU <[ESP+72]>
    UDPARAM18 TEXTEQU <[ESP+76]>
    UDPARAM19 TEXTEQU <[ESP+80]>
    UDPARAM20 TEXTEQU <[ESP+84]>
    UDPARAM21 TEXTEQU <[ESP+88]>
    UDPARAM22 TEXTEQU <[ESP+92]>
    UDPARAM23 TEXTEQU <[ESP+96]>
    UDPARAM24 TEXTEQU <[ESP+100]>
    UDPARAM25 TEXTEQU <[ESP+104]>
    UDPARAM26 TEXTEQU <[ESP+108]>
    UDPARAM27 TEXTEQU <[ESP+112]>
    UDPARAM28 TEXTEQU <[ESP+116]>
    UDPARAM29 TEXTEQU <[ESP+120]>
    UDPARAM30 TEXTEQU <[ESP+124]>
    UDPARAM31 TEXTEQU <[ESP+128]>
    UDPARAM32 TEXTEQU <[ESP+132]>
    UDPARAM33 TEXTEQU <[ESP+136]>
    UDPARAM34 TEXTEQU <[ESP+140]>
    UDPARAM35 TEXTEQU <[ESP+144]>
    UDPARAM36 TEXTEQU <[ESP+148]>
    UDPARAM37 TEXTEQU <[ESP+152]>
    UDPARAM38 TEXTEQU <[ESP+156]>
    UDPARAM39 TEXTEQU <[ESP+160]>
    UDPARAM40 TEXTEQU <[ESP+164]>
    UDPARAM41 TEXTEQU <[ESP+168]>
    UDPARAM42 TEXTEQU <[ESP+172]>
    UDPARAM43 TEXTEQU <[ESP+176]>
    UDPARAM44 TEXTEQU <[ESP+180]>
    UDPARAM45 TEXTEQU <[ESP+184]>
    UDPARAM46 TEXTEQU <[ESP+188]>
    UDPARAM47 TEXTEQU <[ESP+192]>
    UDPARAM48 TEXTEQU <[ESP+196]>
    UDPARAM49 TEXTEQU <[ESP+200]>
    UDPARAM50 TEXTEQU <[ESP+204]>
    UDPARAM51 TEXTEQU <[ESP+208]>
    UDPARAM52 TEXTEQU <[ESP+212]>
    UDPARAM53 TEXTEQU <[ESP+216]>
    UDPARAM54 TEXTEQU <[ESP+220]>
    UDPARAM55 TEXTEQU <[ESP+224]>
    UDPARAM56 TEXTEQU <[ESP+228]>
    UDPARAM57 TEXTEQU <[ESP+232]>
    UDPARAM58 TEXTEQU <[ESP+236]>
    UDPARAM59 TEXTEQU <[ESP+240]>
    UDPARAM60 TEXTEQU <[ESP+244]>
    UDPARAM61 TEXTEQU <[ESP+248]>
    UDPARAM62 TEXTEQU <[ESP+252]>
    UDPARAM63 TEXTEQU <[ESP+256]>
   ;/ 16bits*/
    UWRET TEXTEQU <AX>
    UWRETURN TEXTEQU <AX>
    UWSIDX TEXTEQU <SI>
    UWDIDX TEXTEQU <DI>
    UWBPTR TEXTEQU <BP>
    UWSPTR TEXTEQU <SP>
    UWBASE TEXTEQU <BX>
    UWPARAM0 TEXTEQU <[SP+2]>
    UWPARAM1 TEXTEQU <[SP+4]>
    UWPARAM2 TEXTEQU <[SP+6]>
    UWPARAM3 TEXTEQU <[SP+8]>
    UWPARAM4 TEXTEQU <[SP+10]>
    UWPARAM5 TEXTEQU <[SP+12]>
    UWPARAM6 TEXTEQU <[SP+14]>
    UWPARAM7 TEXTEQU <[SP+16]>
    UWPARAM8 TEXTEQU <[SP+18]>
    UWPARAM9 TEXTEQU <[SP+20]>
    UWPARAM10 TEXTEQU <[SP+22]>
    UWPARAM11 TEXTEQU <[SP+24]>
    UWPARAM12 TEXTEQU <[SP+26]>
    UWPARAM13 TEXTEQU <[SP+28]>
    UWPARAM14 TEXTEQU <[SP+30]>
    UWPARAM15 TEXTEQU <[SP+32]>
    UWPARAM16 TEXTEQU <[SP+34]>
    UWPARAM17 TEXTEQU <[SP+36]>
    UWPARAM18 TEXTEQU <[SP+38]>
    UWPARAM19 TEXTEQU <[SP+40]>
    UWPARAM20 TEXTEQU <[SP+42]>
    UWPARAM21 TEXTEQU <[SP+44]>
    UWPARAM22 TEXTEQU <[SP+46]>
    UWPARAM23 TEXTEQU <[SP+48]>
    UWPARAM24 TEXTEQU <[SP+50]>
    UWPARAM25 TEXTEQU <[SP+52]>
    UWPARAM26 TEXTEQU <[SP+54]>
    UWPARAM27 TEXTEQU <[SP+56]>
    UWPARAM28 TEXTEQU <[SP+58]>
    UWPARAM29 TEXTEQU <[SP+60]>
    UWPARAM30 TEXTEQU <[SP+62]>
    UWPARAM31 TEXTEQU <[SP+64]>
    UWPARAM32 TEXTEQU <[SP+66]>
    UWPARAM33 TEXTEQU <[SP+68]>
    UWPARAM34 TEXTEQU <[SP+70]>
    UWPARAM35 TEXTEQU <[SP+72]>
    UWPARAM36 TEXTEQU <[SP+74]>
    UWPARAM37 TEXTEQU <[SP+76]>
    UWPARAM38 TEXTEQU <[SP+78]>
    UWPARAM39 TEXTEQU <[SP+80]>
    UWPARAM40 TEXTEQU <[SP+82]>
    UWPARAM41 TEXTEQU <[SP+84]>
    UWPARAM42 TEXTEQU <[SP+86]>
    UWPARAM43 TEXTEQU <[SP+88]>
    UWPARAM44 TEXTEQU <[SP+90]>
    UWPARAM45 TEXTEQU <[SP+92]>
    UWPARAM46 TEXTEQU <[SP+94]>
    UWPARAM47 TEXTEQU <[SP+96]>
    UWPARAM48 TEXTEQU <[SP+98]>
    UWPARAM49 TEXTEQU <[SP+100]>
    UWPARAM50 TEXTEQU <[SP+102]>
    UWPARAM51 TEXTEQU <[SP+104]>
    UWPARAM52 TEXTEQU <[SP+106]>
    UWPARAM53 TEXTEQU <[SP+108]>
    UWPARAM54 TEXTEQU <[SP+110]>
    UWPARAM55 TEXTEQU <[SP+112]>
    UWPARAM56 TEXTEQU <[SP+114]>
    UWPARAM57 TEXTEQU <[SP+116]>
    UWPARAM58 TEXTEQU <[SP+118]>
    UWPARAM59 TEXTEQU <[SP+120]>
    UWPARAM60 TEXTEQU <[SP+122]>
    UWPARAM61 TEXTEQU <[SP+124]>
    UWPARAM62 TEXTEQU <[SP+126]>
    UWPARAM63 TEXTEQU <[SP+128]>
   ;/ 8bits*/
    UBRET TEXTEQU <AL>
    UBRETURN TEXTEQU <AL>
    UBSIDX TEXTEQU <SIL>
    UBDIDX TEXTEQU <DIL>
    UBBPTR TEXTEQU <BPL>
    UBSPTR TEXTEQU <SPL>
    UBBASE TEXTEQU <BL>
    UBPARAM0 TEXTEQU <[SPL+1]>
    UBPARAM1 TEXTEQU <[SPL+2]>
    UBPARAM2 TEXTEQU <[SPL+3]>
    UBPARAM3 TEXTEQU <[SPL+4]>
    UBPARAM4 TEXTEQU <[SPL+5]>
    UBPARAM5 TEXTEQU <[SPL+6]>
    UBPARAM6 TEXTEQU <[SPL+7]>
    UBPARAM7 TEXTEQU <[SPL+8]>
    UBPARAM8 TEXTEQU <[SPL+9]>
    UBPARAM9 TEXTEQU <[SPL+10]>
    UBPARAM10 TEXTEQU <[SPL+11]>
    UBPARAM11 TEXTEQU <[SPL+12]>
    UBPARAM12 TEXTEQU <[SPL+13]>
    UBPARAM13 TEXTEQU <[SPL+14]>
    UBPARAM14 TEXTEQU <[SPL+15]>
    UBPARAM15 TEXTEQU <[SPL+16]>
    UBPARAM16 TEXTEQU <[SPL+17]>
    UBPARAM17 TEXTEQU <[SPL+18]>
    UBPARAM18 TEXTEQU <[SPL+19]>
    UBPARAM19 TEXTEQU <[SPL+20]>
    UBPARAM20 TEXTEQU <[SPL+21]>
    UBPARAM21 TEXTEQU <[SPL+22]>
    UBPARAM22 TEXTEQU <[SPL+23]>
    UBPARAM23 TEXTEQU <[SPL+24]>
    UBPARAM24 TEXTEQU <[SPL+25]>
    UBPARAM25 TEXTEQU <[SPL+26]>
    UBPARAM26 TEXTEQU <[SPL+27]>
    UBPARAM27 TEXTEQU <[SPL+28]>
    UBPARAM28 TEXTEQU <[SPL+29]>
    UBPARAM29 TEXTEQU <[SPL+30]>
    UBPARAM30 TEXTEQU <[SPL+31]>
    UBPARAM31 TEXTEQU <[SPL+32]>
    UBPARAM32 TEXTEQU <[SPL+33]>
    UBPARAM33 TEXTEQU <[SPL+34]>
    UBPARAM34 TEXTEQU <[SPL+35]>
    UBPARAM35 TEXTEQU <[SPL+36]>
    UBPARAM36 TEXTEQU <[SPL+37]>
    UBPARAM37 TEXTEQU <[SPL+38]>
    UBPARAM38 TEXTEQU <[SPL+39]>
    UBPARAM39 TEXTEQU <[SPL+40]>
    UBPARAM40 TEXTEQU <[SPL+41]>
    UBPARAM41 TEXTEQU <[SPL+42]>
    UBPARAM42 TEXTEQU <[SPL+43]>
    UBPARAM43 TEXTEQU <[SPL+44]>
    UBPARAM44 TEXTEQU <[SPL+45]>
    UBPARAM45 TEXTEQU <[SPL+46]>
    UBPARAM46 TEXTEQU <[SPL+47]>
    UBPARAM47 TEXTEQU <[SPL+48]>
    UBPARAM48 TEXTEQU <[SPL+49]>
    UBPARAM49 TEXTEQU <[SPL+50]>
    UBPARAM50 TEXTEQU <[SPL+51]>
    UBPARAM51 TEXTEQU <[SPL+52]>
    UBPARAM52 TEXTEQU <[SPL+53]>
    UBPARAM53 TEXTEQU <[SPL+54]>
    UBPARAM54 TEXTEQU <[SPL+55]>
    UBPARAM55 TEXTEQU <[SPL+56]>
    UBPARAM56 TEXTEQU <[SPL+57]>
    UBPARAM57 TEXTEQU <[SPL+58]>
    UBPARAM58 TEXTEQU <[SPL+59]>
    UBPARAM59 TEXTEQU <[SPL+60]>
    UBPARAM60 TEXTEQU <[SPL+61]>
    UBPARAM61 TEXTEQU <[SPL+62]>
    UBPARAM62 TEXTEQU <[SPL+63]>
    UBPARAM63 TEXTEQU <[SPL+64]>
    ENDIF
    ;/*__WIN32__*/

    IFDEF __UNIX64__
   ;/ norm reg bits*/
    RRET TEXTEQU <RAX>
    RRETURN TEXTEQU <RAX>
    RSIDX TEXTEQU <RSI>
    RDIDX TEXTEQU <RDI>
    RBPTR TEXTEQU <RBP>
    RSPTR TEXTEQU <RSP>
    RBASE TEXTEQU <RBX>
    RPARAM0 TEXTEQU <RDI>
    RPARAM1 TEXTEQU <RSI>
    RPARAM2 TEXTEQU <RDX>
    RPARAM3 TEXTEQU <RCX>
    RPARAM4 TEXTEQU <R8>
    RPARAM5 TEXTEQU <R9>
    RPARAM6 TEXTEQU <[RSP+56]>
    RPARAM7 TEXTEQU <[RSP+64]>
    RPARAM8 TEXTEQU <[RSP+72]>
    RPARAM9 TEXTEQU <[RSP+80]>
    RPARAM10 TEXTEQU <[RSP+88]>
    RPARAM11 TEXTEQU <[RSP+96]>
    RPARAM12 TEXTEQU <[RSP+104]>
    RPARAM13 TEXTEQU <[RSP+112]>
    RPARAM14 TEXTEQU <[RSP+120]>
    RPARAM15 TEXTEQU <[RSP+128]>
    RPARAM16 TEXTEQU <[RSP+136]>
    RPARAM17 TEXTEQU <[RSP+144]>
    RPARAM18 TEXTEQU <[RSP+152]>
    RPARAM19 TEXTEQU <[RSP+160]>
    RPARAM20 TEXTEQU <[RSP+168]>
    RPARAM21 TEXTEQU <[RSP+176]>
    RPARAM22 TEXTEQU <[RSP+184]>
    RPARAM23 TEXTEQU <[RSP+192]>
    RPARAM24 TEXTEQU <[RSP+200]>
    RPARAM25 TEXTEQU <[RSP+208]>
    RPARAM26 TEXTEQU <[RSP+216]>
    RPARAM27 TEXTEQU <[RSP+224]>
    RPARAM28 TEXTEQU <[RSP+232]>
    RPARAM29 TEXTEQU <[RSP+240]>
    RPARAM30 TEXTEQU <[RSP+248]>
    RPARAM31 TEXTEQU <[RSP+256]>
    RPARAM32 TEXTEQU <[RSP+264]>
    RPARAM33 TEXTEQU <[RSP+272]>
    RPARAM34 TEXTEQU <[RSP+280]>
    RPARAM35 TEXTEQU <[RSP+288]>
    RPARAM36 TEXTEQU <[RSP+296]>
    RPARAM37 TEXTEQU <[RSP+304]>
    RPARAM38 TEXTEQU <[RSP+312]>
    RPARAM39 TEXTEQU <[RSP+320]>
    RPARAM40 TEXTEQU <[RSP+328]>
    RPARAM41 TEXTEQU <[RSP+336]>
    RPARAM42 TEXTEQU <[RSP+344]>
    RPARAM43 TEXTEQU <[RSP+352]>
    RPARAM44 TEXTEQU <[RSP+360]>
    RPARAM45 TEXTEQU <[RSP+368]>
    RPARAM46 TEXTEQU <[RSP+376]>
    RPARAM47 TEXTEQU <[RSP+384]>
    RPARAM48 TEXTEQU <[RSP+392]>
    RPARAM49 TEXTEQU <[RSP+400]>
    RPARAM50 TEXTEQU <[RSP+408]>
    RPARAM51 TEXTEQU <[RSP+416]>
    RPARAM52 TEXTEQU <[RSP+424]>
    RPARAM53 TEXTEQU <[RSP+432]>
    RPARAM54 TEXTEQU <[RSP+440]>
    RPARAM55 TEXTEQU <[RSP+448]>
    RPARAM56 TEXTEQU <[RSP+456]>
    RPARAM57 TEXTEQU <[RSP+464]>
    RPARAM58 TEXTEQU <[RSP+472]>
    RPARAM59 TEXTEQU <[RSP+480]>
    RPARAM60 TEXTEQU <[RSP+488]>
    RPARAM61 TEXTEQU <[RSP+496]>
    RPARAM62 TEXTEQU <[RSP+504]>
    RPARAM63 TEXTEQU <[RSP+512]>
   ;/ 32bits*/
    DRET TEXTEQU <EAX>
    DRETURN TEXTEQU <EAX>
    DSIDX TEXTEQU <ESI>
    DDIDX TEXTEQU <EDI>
    DBPTR TEXTEQU <EBP>
    DSPTR TEXTEQU <ESP>
    DBASE TEXTEQU <EBX>
    DPARAM0 TEXTEQU <EDI>
    DPARAM1 TEXTEQU <ESI>
    DPARAM2 TEXTEQU <EDX>
    DPARAM3 TEXTEQU <ECX>
    DPARAM4 TEXTEQU <R8D>
    DPARAM5 TEXTEQU <R9D>
    DPARAM6 TEXTEQU <[ESP+28]>
    DPARAM7 TEXTEQU <[ESP+32]>
    DPARAM8 TEXTEQU <[ESP+36]>
    DPARAM9 TEXTEQU <[ESP+40]>
    DPARAM10 TEXTEQU <[ESP+44]>
    DPARAM11 TEXTEQU <[ESP+48]>
    DPARAM12 TEXTEQU <[ESP+52]>
    DPARAM13 TEXTEQU <[ESP+56]>
    DPARAM14 TEXTEQU <[ESP+60]>
    DPARAM15 TEXTEQU <[ESP+64]>
    DPARAM16 TEXTEQU <[ESP+68]>
    DPARAM17 TEXTEQU <[ESP+72]>
    DPARAM18 TEXTEQU <[ESP+76]>
    DPARAM19 TEXTEQU <[ESP+80]>
    DPARAM20 TEXTEQU <[ESP+84]>
    DPARAM21 TEXTEQU <[ESP+88]>
    DPARAM22 TEXTEQU <[ESP+92]>
    DPARAM23 TEXTEQU <[ESP+96]>
    DPARAM24 TEXTEQU <[ESP+100]>
    DPARAM25 TEXTEQU <[ESP+104]>
    DPARAM26 TEXTEQU <[ESP+108]>
    DPARAM27 TEXTEQU <[ESP+112]>
    DPARAM28 TEXTEQU <[ESP+116]>
    DPARAM29 TEXTEQU <[ESP+120]>
    DPARAM30 TEXTEQU <[ESP+124]>
    DPARAM31 TEXTEQU <[ESP+128]>
    DPARAM32 TEXTEQU <[ESP+132]>
    DPARAM33 TEXTEQU <[ESP+136]>
    DPARAM34 TEXTEQU <[ESP+140]>
    DPARAM35 TEXTEQU <[ESP+144]>
    DPARAM36 TEXTEQU <[ESP+148]>
    DPARAM37 TEXTEQU <[ESP+152]>
    DPARAM38 TEXTEQU <[ESP+156]>
    DPARAM39 TEXTEQU <[ESP+160]>
    DPARAM40 TEXTEQU <[ESP+164]>
    DPARAM41 TEXTEQU <[ESP+168]>
    DPARAM42 TEXTEQU <[ESP+172]>
    DPARAM43 TEXTEQU <[ESP+176]>
    DPARAM44 TEXTEQU <[ESP+180]>
    DPARAM45 TEXTEQU <[ESP+184]>
    DPARAM46 TEXTEQU <[ESP+188]>
    DPARAM47 TEXTEQU <[ESP+192]>
    DPARAM48 TEXTEQU <[ESP+196]>
    DPARAM49 TEXTEQU <[ESP+200]>
    DPARAM50 TEXTEQU <[ESP+204]>
    DPARAM51 TEXTEQU <[ESP+208]>
    DPARAM52 TEXTEQU <[ESP+212]>
    DPARAM53 TEXTEQU <[ESP+216]>
    DPARAM54 TEXTEQU <[ESP+220]>
    DPARAM55 TEXTEQU <[ESP+224]>
    DPARAM56 TEXTEQU <[ESP+228]>
    DPARAM57 TEXTEQU <[ESP+232]>
    DPARAM58 TEXTEQU <[ESP+236]>
    DPARAM59 TEXTEQU <[ESP+240]>
    DPARAM60 TEXTEQU <[ESP+244]>
    DPARAM61 TEXTEQU <[ESP+248]>
    DPARAM62 TEXTEQU <[ESP+252]>
    DPARAM63 TEXTEQU <[ESP+256]>
   ;/ 16bits*/
    WRET TEXTEQU <AX>
    WRETURN TEXTEQU <AX>
    WSIDX TEXTEQU <SI>
    WDIDX TEXTEQU <DI>
    WBPTR TEXTEQU <BP>
    WSPTR TEXTEQU <SP>
    WBASE TEXTEQU <BX>
    WPARAM0 TEXTEQU <DI>
    WPARAM1 TEXTEQU <SI>
    WPARAM2 TEXTEQU <DX>
    WPARAM3 TEXTEQU <CX>
    WPARAM4 TEXTEQU <R8W>
    WPARAM5 TEXTEQU <R9W>
    WPARAM6 TEXTEQU <[SP+14]>
    WPARAM7 TEXTEQU <[SP+16]>
    WPARAM8 TEXTEQU <[SP+18]>
    WPARAM9 TEXTEQU <[SP+20]>
    WPARAM10 TEXTEQU <[SP+22]>
    WPARAM11 TEXTEQU <[SP+24]>
    WPARAM12 TEXTEQU <[SP+26]>
    WPARAM13 TEXTEQU <[SP+28]>
    WPARAM14 TEXTEQU <[SP+30]>
    WPARAM15 TEXTEQU <[SP+32]>
    WPARAM16 TEXTEQU <[SP+34]>
    WPARAM17 TEXTEQU <[SP+36]>
    WPARAM18 TEXTEQU <[SP+38]>
    WPARAM19 TEXTEQU <[SP+40]>
    WPARAM20 TEXTEQU <[SP+42]>
    WPARAM21 TEXTEQU <[SP+44]>
    WPARAM22 TEXTEQU <[SP+46]>
    WPARAM23 TEXTEQU <[SP+48]>
    WPARAM24 TEXTEQU <[SP+50]>
    WPARAM25 TEXTEQU <[SP+52]>
    WPARAM26 TEXTEQU <[SP+54]>
    WPARAM27 TEXTEQU <[SP+56]>
    WPARAM28 TEXTEQU <[SP+58]>
    WPARAM29 TEXTEQU <[SP+60]>
    WPARAM30 TEXTEQU <[SP+62]>
    WPARAM31 TEXTEQU <[SP+64]>
    WPARAM32 TEXTEQU <[SP+66]>
    WPARAM33 TEXTEQU <[SP+68]>
    WPARAM34 TEXTEQU <[SP+70]>
    WPARAM35 TEXTEQU <[SP+72]>
    WPARAM36 TEXTEQU <[SP+74]>
    WPARAM37 TEXTEQU <[SP+76]>
    WPARAM38 TEXTEQU <[SP+78]>
    WPARAM39 TEXTEQU <[SP+80]>
    WPARAM40 TEXTEQU <[SP+82]>
    WPARAM41 TEXTEQU <[SP+84]>
    WPARAM42 TEXTEQU <[SP+86]>
    WPARAM43 TEXTEQU <[SP+88]>
    WPARAM44 TEXTEQU <[SP+90]>
    WPARAM45 TEXTEQU <[SP+92]>
    WPARAM46 TEXTEQU <[SP+94]>
    WPARAM47 TEXTEQU <[SP+96]>
    WPARAM48 TEXTEQU <[SP+98]>
    WPARAM49 TEXTEQU <[SP+100]>
    WPARAM50 TEXTEQU <[SP+102]>
    WPARAM51 TEXTEQU <[SP+104]>
    WPARAM52 TEXTEQU <[SP+106]>
    WPARAM53 TEXTEQU <[SP+108]>
    WPARAM54 TEXTEQU <[SP+110]>
    WPARAM55 TEXTEQU <[SP+112]>
    WPARAM56 TEXTEQU <[SP+114]>
    WPARAM57 TEXTEQU <[SP+116]>
    WPARAM58 TEXTEQU <[SP+118]>
    WPARAM59 TEXTEQU <[SP+120]>
    WPARAM60 TEXTEQU <[SP+122]>
    WPARAM61 TEXTEQU <[SP+124]>
    WPARAM62 TEXTEQU <[SP+126]>
    WPARAM63 TEXTEQU <[SP+128]>
   ;/ 8bits*/
    BRET TEXTEQU <AL>
    BRETURN TEXTEQU <AL>
    BSIDX TEXTEQU <SIL>
    BDIDX TEXTEQU <DIL>
    BBPTR TEXTEQU <BPL>
    BSPTR TEXTEQU <SPL>
    BBASE TEXTEQU <BL>
    BPARAM0 TEXTEQU <DIL>
    BPARAM1 TEXTEQU <SIL>
    BPARAM2 TEXTEQU <DL>
    BPARAM3 TEXTEQU <CL>
    BPARAM4 TEXTEQU <R8B>
    BPARAM5 TEXTEQU <R9B>
    BPARAM6 TEXTEQU <[SPL+7]>
    BPARAM7 TEXTEQU <[SPL+8]>
    BPARAM8 TEXTEQU <[SPL+9]>
    BPARAM9 TEXTEQU <[SPL+10]>
    BPARAM10 TEXTEQU <[SPL+11]>
    BPARAM11 TEXTEQU <[SPL+12]>
    BPARAM12 TEXTEQU <[SPL+13]>
    BPARAM13 TEXTEQU <[SPL+14]>
    BPARAM14 TEXTEQU <[SPL+15]>
    BPARAM15 TEXTEQU <[SPL+16]>
    BPARAM16 TEXTEQU <[SPL+17]>
    BPARAM17 TEXTEQU <[SPL+18]>
    BPARAM18 TEXTEQU <[SPL+19]>
    BPARAM19 TEXTEQU <[SPL+20]>
    BPARAM20 TEXTEQU <[SPL+21]>
    BPARAM21 TEXTEQU <[SPL+22]>
    BPARAM22 TEXTEQU <[SPL+23]>
    BPARAM23 TEXTEQU <[SPL+24]>
    BPARAM24 TEXTEQU <[SPL+25]>
    BPARAM25 TEXTEQU <[SPL+26]>
    BPARAM26 TEXTEQU <[SPL+27]>
    BPARAM27 TEXTEQU <[SPL+28]>
    BPARAM28 TEXTEQU <[SPL+29]>
    BPARAM29 TEXTEQU <[SPL+30]>
    BPARAM30 TEXTEQU <[SPL+31]>
    BPARAM31 TEXTEQU <[SPL+32]>
    BPARAM32 TEXTEQU <[SPL+33]>
    BPARAM33 TEXTEQU <[SPL+34]>
    BPARAM34 TEXTEQU <[SPL+35]>
    BPARAM35 TEXTEQU <[SPL+36]>
    BPARAM36 TEXTEQU <[SPL+37]>
    BPARAM37 TEXTEQU <[SPL+38]>
    BPARAM38 TEXTEQU <[SPL+39]>
    BPARAM39 TEXTEQU <[SPL+40]>
    BPARAM40 TEXTEQU <[SPL+41]>
    BPARAM41 TEXTEQU <[SPL+42]>
    BPARAM42 TEXTEQU <[SPL+43]>
    BPARAM43 TEXTEQU <[SPL+44]>
    BPARAM44 TEXTEQU <[SPL+45]>
    BPARAM45 TEXTEQU <[SPL+46]>
    BPARAM46 TEXTEQU <[SPL+47]>
    BPARAM47 TEXTEQU <[SPL+48]>
    BPARAM48 TEXTEQU <[SPL+49]>
    BPARAM49 TEXTEQU <[SPL+50]>
    BPARAM50 TEXTEQU <[SPL+51]>
    BPARAM51 TEXTEQU <[SPL+52]>
    BPARAM52 TEXTEQU <[SPL+53]>
    BPARAM53 TEXTEQU <[SPL+54]>
    BPARAM54 TEXTEQU <[SPL+55]>
    BPARAM55 TEXTEQU <[SPL+56]>
    BPARAM56 TEXTEQU <[SPL+57]>
    BPARAM57 TEXTEQU <[SPL+58]>
    BPARAM58 TEXTEQU <[SPL+59]>
    BPARAM59 TEXTEQU <[SPL+60]>
    BPARAM60 TEXTEQU <[SPL+61]>
    BPARAM61 TEXTEQU <[SPL+62]>
    BPARAM62 TEXTEQU <[SPL+63]>
    BPARAM63 TEXTEQU <[SPL+64]>

   ;/ norm reg bits regcall*/
    RRRET TEXTEQU <RAX>
    RRRETURN TEXTEQU <RAX>
    RRSIDX TEXTEQU <RSI>
    RRDIDX TEXTEQU <RDI>
    RRBPTR TEXTEQU <RBP>
    RRSPTR TEXTEQU <RSP>
    RRBASE TEXTEQU <RBX>
    RRPARAM0 TEXTEQU <RAX>
    RRPARAM1 TEXTEQU <RCX>
    RRPARAM2 TEXTEQU <RDX>
    RRPARAM3 TEXTEQU <RDI>
    RRPARAM4 TEXTEQU <RSI>
    RRPARAM5 TEXTEQU <R8>
    RRPARAM6 TEXTEQU <R9>
    RRPARAM7 TEXTEQU <R10>
    RRPARAM8 TEXTEQU <R11>
    RRPARAM9 TEXTEQU <R12>
    RRPARAM10 TEXTEQU <R14>
    RRPARAM11 TEXTEQU <R15>
    RRPARAM12 TEXTEQU <[RSP+104]>
    RRPARAM13 TEXTEQU <[RSP+112]>
    RRPARAM14 TEXTEQU <[RSP+120]>
    RRPARAM15 TEXTEQU <[RSP+128]>
    RRPARAM16 TEXTEQU <[RSP+136]>
    RRPARAM17 TEXTEQU <[RSP+144]>
    RRPARAM18 TEXTEQU <[RSP+152]>
    RRPARAM19 TEXTEQU <[RSP+160]>
    RRPARAM20 TEXTEQU <[RSP+168]>
    RRPARAM21 TEXTEQU <[RSP+176]>
    RRPARAM22 TEXTEQU <[RSP+184]>
    RRPARAM23 TEXTEQU <[RSP+192]>
    RRPARAM24 TEXTEQU <[RSP+200]>
    RRPARAM25 TEXTEQU <[RSP+208]>
    RRPARAM26 TEXTEQU <[RSP+216]>
    RRPARAM27 TEXTEQU <[RSP+224]>
    RRPARAM28 TEXTEQU <[RSP+232]>
    RRPARAM29 TEXTEQU <[RSP+240]>
    RRPARAM30 TEXTEQU <[RSP+248]>
    RRPARAM31 TEXTEQU <[RSP+256]>
    RRPARAM32 TEXTEQU <[RSP+264]>
    RRPARAM33 TEXTEQU <[RSP+272]>
    RRPARAM34 TEXTEQU <[RSP+280]>
    RRPARAM35 TEXTEQU <[RSP+288]>
    RRPARAM36 TEXTEQU <[RSP+296]>
    RRPARAM37 TEXTEQU <[RSP+304]>
    RRPARAM38 TEXTEQU <[RSP+312]>
    RRPARAM39 TEXTEQU <[RSP+320]>
    RRPARAM40 TEXTEQU <[RSP+328]>
    RRPARAM41 TEXTEQU <[RSP+336]>
    RRPARAM42 TEXTEQU <[RSP+344]>
    RRPARAM43 TEXTEQU <[RSP+352]>
    RRPARAM44 TEXTEQU <[RSP+360]>
    RRPARAM45 TEXTEQU <[RSP+368]>
    RRPARAM46 TEXTEQU <[RSP+376]>
    RRPARAM47 TEXTEQU <[RSP+384]>
    RRPARAM48 TEXTEQU <[RSP+392]>
    RRPARAM49 TEXTEQU <[RSP+400]>
    RRPARAM50 TEXTEQU <[RSP+408]>
    RRPARAM51 TEXTEQU <[RSP+416]>
    RRPARAM52 TEXTEQU <[RSP+424]>
    RRPARAM53 TEXTEQU <[RSP+432]>
    RRPARAM54 TEXTEQU <[RSP+440]>
    RRPARAM55 TEXTEQU <[RSP+448]>
    RRPARAM56 TEXTEQU <[RSP+456]>
    RRPARAM57 TEXTEQU <[RSP+464]>
    RRPARAM58 TEXTEQU <[RSP+472]>
    RRPARAM59 TEXTEQU <[RSP+480]>
    RRPARAM60 TEXTEQU <[RSP+488]>
    RRPARAM61 TEXTEQU <[RSP+496]>
    RRPARAM62 TEXTEQU <[RSP+504]>
    RRPARAM63 TEXTEQU <[RSP+512]>
   ;/ 32bits*/
    RDRET TEXTEQU <EAX>
    RDRETURN TEXTEQU <EAX>
    RDSIDX TEXTEQU <ESI>
    RDDIDX TEXTEQU <EDI>
    RDBPTR TEXTEQU <EBP>
    RDSPTR TEXTEQU <ESP>
    RDBASE TEXTEQU <EBX>
    RDPARAM0 TEXTEQU <EAX>
    RDPARAM1 TEXTEQU <ECX>
    RDPARAM2 TEXTEQU <EDX>
    RDPARAM3 TEXTEQU <EDI>
    RDPARAM4 TEXTEQU <ESI>
    RDPARAM5 TEXTEQU <R8D>
    RDPARAM6 TEXTEQU <R9D>
    RDPARAM7 TEXTEQU <R10D>
    RDPARAM8 TEXTEQU <R11D>
    RDPARAM9 TEXTEQU <R12D>
    RDPARAM10 TEXTEQU <R14D>
    RDPARAM11 TEXTEQU <R15D>
    RDPARAM12 TEXTEQU <[ESP+52]>
    RDPARAM13 TEXTEQU <[ESP+56]>
    RDPARAM14 TEXTEQU <[ESP+60]>
    RDPARAM15 TEXTEQU <[ESP+64]>
    RDPARAM16 TEXTEQU <[ESP+68]>
    RDPARAM17 TEXTEQU <[ESP+72]>
    RDPARAM18 TEXTEQU <[ESP+76]>
    RDPARAM19 TEXTEQU <[ESP+80]>
    RDPARAM20 TEXTEQU <[ESP+84]>
    RDPARAM21 TEXTEQU <[ESP+88]>
    RDPARAM22 TEXTEQU <[ESP+92]>
    RDPARAM23 TEXTEQU <[ESP+96]>
    RDPARAM24 TEXTEQU <[ESP+100]>
    RDPARAM25 TEXTEQU <[ESP+104]>
    RDPARAM26 TEXTEQU <[ESP+108]>
    RDPARAM27 TEXTEQU <[ESP+112]>
    RDPARAM28 TEXTEQU <[ESP+116]>
    RDPARAM29 TEXTEQU <[ESP+120]>
    RDPARAM30 TEXTEQU <[ESP+124]>
    RDPARAM31 TEXTEQU <[ESP+128]>
    RDPARAM32 TEXTEQU <[ESP+132]>
    RDPARAM33 TEXTEQU <[ESP+136]>
    RDPARAM34 TEXTEQU <[ESP+140]>
    RDPARAM35 TEXTEQU <[ESP+144]>
    RDPARAM36 TEXTEQU <[ESP+148]>
    RDPARAM37 TEXTEQU <[ESP+152]>
    RDPARAM38 TEXTEQU <[ESP+156]>
    RDPARAM39 TEXTEQU <[ESP+160]>
    RDPARAM40 TEXTEQU <[ESP+164]>
    RDPARAM41 TEXTEQU <[ESP+168]>
    RDPARAM42 TEXTEQU <[ESP+172]>
    RDPARAM43 TEXTEQU <[ESP+176]>
    RDPARAM44 TEXTEQU <[ESP+180]>
    RDPARAM45 TEXTEQU <[ESP+184]>
    RDPARAM46 TEXTEQU <[ESP+188]>
    RDPARAM47 TEXTEQU <[ESP+192]>
    RDPARAM48 TEXTEQU <[ESP+196]>
    RDPARAM49 TEXTEQU <[ESP+200]>
    RDPARAM50 TEXTEQU <[ESP+204]>
    RDPARAM51 TEXTEQU <[ESP+208]>
    RDPARAM52 TEXTEQU <[ESP+212]>
    RDPARAM53 TEXTEQU <[ESP+216]>
    RDPARAM54 TEXTEQU <[ESP+220]>
    RDPARAM55 TEXTEQU <[ESP+224]>
    RDPARAM56 TEXTEQU <[ESP+228]>
    RDPARAM57 TEXTEQU <[ESP+232]>
    RDPARAM58 TEXTEQU <[ESP+236]>
    RDPARAM59 TEXTEQU <[ESP+240]>
    RDPARAM60 TEXTEQU <[ESP+244]>
    RDPARAM61 TEXTEQU <[ESP+248]>
    RDPARAM62 TEXTEQU <[ESP+252]>
    RDPARAM63 TEXTEQU <[ESP+256]>
   ;/ 16bits*/
    RWRET TEXTEQU <AX>
    RWRETURN TEXTEQU <AX>
    RWSIDX TEXTEQU <SI>
    RWDIDX TEXTEQU <DI>
    RWBPTR TEXTEQU <BP>
    RWSPTR TEXTEQU <SP>
    RWBASE TEXTEQU <BX>
    RWPARAM0 TEXTEQU <AX>
    RWPARAM1 TEXTEQU <CX>
    RWPARAM2 TEXTEQU <DX>
    RWPARAM3 TEXTEQU <DI>
    RWPARAM4 TEXTEQU <SI>
    RWPARAM5 TEXTEQU <R8W>
    RWPARAM6 TEXTEQU <R9W>
    RWPARAM7 TEXTEQU <R10W>
    RWPARAM8 TEXTEQU <R11W>
    RWPARAM9 TEXTEQU <R12W>
    RWPARAM10 TEXTEQU <R14W>
    RWPARAM11 TEXTEQU <R15W>
    RWPARAM12 TEXTEQU <[SP+26]>
    RWPARAM13 TEXTEQU <[SP+28]>
    RWPARAM14 TEXTEQU <[SP+30]>
    RWPARAM15 TEXTEQU <[SP+32]>
    RWPARAM16 TEXTEQU <[SP+34]>
    RWPARAM17 TEXTEQU <[SP+36]>
    RWPARAM18 TEXTEQU <[SP+38]>
    RWPARAM19 TEXTEQU <[SP+40]>
    RWPARAM20 TEXTEQU <[SP+42]>
    RWPARAM21 TEXTEQU <[SP+44]>
    RWPARAM22 TEXTEQU <[SP+46]>
    RWPARAM23 TEXTEQU <[SP+48]>
    RWPARAM24 TEXTEQU <[SP+50]>
    RWPARAM25 TEXTEQU <[SP+52]>
    RWPARAM26 TEXTEQU <[SP+54]>
    RWPARAM27 TEXTEQU <[SP+56]>
    RWPARAM28 TEXTEQU <[SP+58]>
    RWPARAM29 TEXTEQU <[SP+60]>
    RWPARAM30 TEXTEQU <[SP+62]>
    RWPARAM31 TEXTEQU <[SP+64]>
    RWPARAM32 TEXTEQU <[SP+66]>
    RWPARAM33 TEXTEQU <[SP+68]>
    RWPARAM34 TEXTEQU <[SP+70]>
    RWPARAM35 TEXTEQU <[SP+72]>
    RWPARAM36 TEXTEQU <[SP+74]>
    RWPARAM37 TEXTEQU <[SP+76]>
    RWPARAM38 TEXTEQU <[SP+78]>
    RWPARAM39 TEXTEQU <[SP+80]>
    RWPARAM40 TEXTEQU <[SP+82]>
    RWPARAM41 TEXTEQU <[SP+84]>
    RWPARAM42 TEXTEQU <[SP+86]>
    RWPARAM43 TEXTEQU <[SP+88]>
    RWPARAM44 TEXTEQU <[SP+90]>
    RWPARAM45 TEXTEQU <[SP+92]>
    RWPARAM46 TEXTEQU <[SP+94]>
    RWPARAM47 TEXTEQU <[SP+96]>
    RWPARAM48 TEXTEQU <[SP+98]>
    RWPARAM49 TEXTEQU <[SP+100]>
    RWPARAM50 TEXTEQU <[SP+102]>
    RWPARAM51 TEXTEQU <[SP+104]>
    RWPARAM52 TEXTEQU <[SP+106]>
    RWPARAM53 TEXTEQU <[SP+108]>
    RWPARAM54 TEXTEQU <[SP+110]>
    RWPARAM55 TEXTEQU <[SP+112]>
    RWPARAM56 TEXTEQU <[SP+114]>
    RWPARAM57 TEXTEQU <[SP+116]>
    RWPARAM58 TEXTEQU <[SP+118]>
    RWPARAM59 TEXTEQU <[SP+120]>
    RWPARAM60 TEXTEQU <[SP+122]>
    RWPARAM61 TEXTEQU <[SP+124]>
    RWPARAM62 TEXTEQU <[SP+126]>
    RWPARAM63 TEXTEQU <[SP+128]>
   ;/ 8bits*/
    RBRET TEXTEQU <AL>
    RBRETURN TEXTEQU <AL>
    RBSIDX TEXTEQU <SIL>
    RBDIDX TEXTEQU <DIL>
    RBBPTR TEXTEQU <BPL>
    RBSPTR TEXTEQU <SPL>
    RBBASE TEXTEQU <BL>
    RBPARAM0 TEXTEQU <AL>
    RBPARAM1 TEXTEQU <CL>
    RBPARAM2 TEXTEQU <DL>
    RBPARAM3 TEXTEQU <DIL>
    RBPARAM4 TEXTEQU <SIL>
    RBPARAM5 TEXTEQU <R8B>
    RBPARAM6 TEXTEQU <R9B>
    RBPARAM7 TEXTEQU <R10B>
    RBPARAM8 TEXTEQU <R11B>
    RBPARAM9 TEXTEQU <R12B>
    RBPARAM10 TEXTEQU <R14B>
    RBPARAM11 TEXTEQU <R15B>
    RBPARAM12 TEXTEQU <[SPL+13]>
    RBPARAM13 TEXTEQU <[SPL+14]>
    RBPARAM14 TEXTEQU <[SPL+15]>
    RBPARAM15 TEXTEQU <[SPL+16]>
    RBPARAM16 TEXTEQU <[SPL+17]>
    RBPARAM17 TEXTEQU <[SPL+18]>
    RBPARAM18 TEXTEQU <[SPL+19]>
    RBPARAM19 TEXTEQU <[SPL+20]>
    RBPARAM20 TEXTEQU <[SPL+21]>
    RBPARAM21 TEXTEQU <[SPL+22]>
    RBPARAM22 TEXTEQU <[SPL+23]>
    RBPARAM23 TEXTEQU <[SPL+24]>
    RBPARAM24 TEXTEQU <[SPL+25]>
    RBPARAM25 TEXTEQU <[SPL+26]>
    RBPARAM26 TEXTEQU <[SPL+27]>
    RBPARAM27 TEXTEQU <[SPL+28]>
    RBPARAM28 TEXTEQU <[SPL+29]>
    RBPARAM29 TEXTEQU <[SPL+30]>
    RBPARAM30 TEXTEQU <[SPL+31]>
    RBPARAM31 TEXTEQU <[SPL+32]>
    RBPARAM32 TEXTEQU <[SPL+33]>
    RBPARAM33 TEXTEQU <[SPL+34]>
    RBPARAM34 TEXTEQU <[SPL+35]>
    RBPARAM35 TEXTEQU <[SPL+36]>
    RBPARAM36 TEXTEQU <[SPL+37]>
    RBPARAM37 TEXTEQU <[SPL+38]>
    RBPARAM38 TEXTEQU <[SPL+39]>
    RBPARAM39 TEXTEQU <[SPL+40]>
    RBPARAM40 TEXTEQU <[SPL+41]>
    RBPARAM41 TEXTEQU <[SPL+42]>
    RBPARAM42 TEXTEQU <[SPL+43]>
    RBPARAM43 TEXTEQU <[SPL+44]>
    RBPARAM44 TEXTEQU <[SPL+45]>
    RBPARAM45 TEXTEQU <[SPL+46]>
    RBPARAM46 TEXTEQU <[SPL+47]>
    RBPARAM47 TEXTEQU <[SPL+48]>
    RBPARAM48 TEXTEQU <[SPL+49]>
    RBPARAM49 TEXTEQU <[SPL+50]>
    RBPARAM50 TEXTEQU <[SPL+51]>
    RBPARAM51 TEXTEQU <[SPL+52]>
    RBPARAM52 TEXTEQU <[SPL+53]>
    RBPARAM53 TEXTEQU <[SPL+54]>
    RBPARAM54 TEXTEQU <[SPL+55]>
    RBPARAM55 TEXTEQU <[SPL+56]>
    RBPARAM56 TEXTEQU <[SPL+57]>
    RBPARAM57 TEXTEQU <[SPL+58]>
    RBPARAM58 TEXTEQU <[SPL+59]>
    RBPARAM59 TEXTEQU <[SPL+60]>
    RBPARAM60 TEXTEQU <[SPL+61]>
    RBPARAM61 TEXTEQU <[SPL+62]>
    RBPARAM62 TEXTEQU <[SPL+63]>
    RBPARAM63 TEXTEQU <[SPL+64]>
    
   ;/* Undefined call or cdecl*/
   ;/ norm reg bits*/
    URRET TEXTEQU <RAX>
    URRETURN TEXTEQU <RAX>
    URSIDX TEXTEQU <RSI>
    URDIDX TEXTEQU <RDI>
    URBPTR TEXTEQU <RBP>
    URSPTR TEXTEQU <RSP>
    URBASE TEXTEQU <RBX>
    URPARAM0 TEXTEQU <[RSP+8]>
    URPARAM1 TEXTEQU <[RSP+16]>
    URPARAM2 TEXTEQU <[RSP+24]>
    URPARAM3 TEXTEQU <[RSP+32]>
    URPARAM4 TEXTEQU <[RSP+40]>
    URPARAM5 TEXTEQU <[RSP+48]>
    URPARAM6 TEXTEQU <[RSP+56]>
    URPARAM7 TEXTEQU <[RSP+64]>
    URPARAM8 TEXTEQU <[RSP+72]>
    URPARAM9 TEXTEQU <[RSP+80]>
    URPARAM10 TEXTEQU <[RSP+88]>
    URPARAM11 TEXTEQU <[RSP+96]>
    URPARAM12 TEXTEQU <[RSP+104]>
    URPARAM13 TEXTEQU <[RSP+112]>
    URPARAM14 TEXTEQU <[RSP+120]>
    URPARAM15 TEXTEQU <[RSP+128]>
    URPARAM16 TEXTEQU <[RSP+136]>
    URPARAM17 TEXTEQU <[RSP+144]>
    URPARAM18 TEXTEQU <[RSP+152]>
    URPARAM19 TEXTEQU <[RSP+160]>
    URPARAM20 TEXTEQU <[RSP+168]>
    URPARAM21 TEXTEQU <[RSP+176]>
    URPARAM22 TEXTEQU <[RSP+184]>
    URPARAM23 TEXTEQU <[RSP+192]>
    URPARAM24 TEXTEQU <[RSP+200]>
    URPARAM25 TEXTEQU <[RSP+208]>
    URPARAM26 TEXTEQU <[RSP+216]>
    URPARAM27 TEXTEQU <[RSP+224]>
    URPARAM28 TEXTEQU <[RSP+232]>
    URPARAM29 TEXTEQU <[RSP+240]>
    URPARAM30 TEXTEQU <[RSP+248]>
    URPARAM31 TEXTEQU <[RSP+256]>
    URPARAM32 TEXTEQU <[RSP+264]>
    URPARAM33 TEXTEQU <[RSP+272]>
    URPARAM34 TEXTEQU <[RSP+280]>
    URPARAM35 TEXTEQU <[RSP+288]>
    URPARAM36 TEXTEQU <[RSP+296]>
    URPARAM37 TEXTEQU <[RSP+304]>
    URPARAM38 TEXTEQU <[RSP+312]>
    URPARAM39 TEXTEQU <[RSP+320]>
    URPARAM40 TEXTEQU <[RSP+328]>
    URPARAM41 TEXTEQU <[RSP+336]>
    URPARAM42 TEXTEQU <[RSP+344]>
    URPARAM43 TEXTEQU <[RSP+352]>
    URPARAM44 TEXTEQU <[RSP+360]>
    URPARAM45 TEXTEQU <[RSP+368]>
    URPARAM46 TEXTEQU <[RSP+376]>
    URPARAM47 TEXTEQU <[RSP+384]>
    URPARAM48 TEXTEQU <[RSP+392]>
    URPARAM49 TEXTEQU <[RSP+400]>
    URPARAM50 TEXTEQU <[RSP+408]>
    URPARAM51 TEXTEQU <[RSP+416]>
    URPARAM52 TEXTEQU <[RSP+424]>
    URPARAM53 TEXTEQU <[RSP+432]>
    URPARAM54 TEXTEQU <[RSP+440]>
    URPARAM55 TEXTEQU <[RSP+448]>
    URPARAM56 TEXTEQU <[RSP+456]>
    URPARAM57 TEXTEQU <[RSP+464]>
    URPARAM58 TEXTEQU <[RSP+472]>
    URPARAM59 TEXTEQU <[RSP+480]>
    URPARAM60 TEXTEQU <[RSP+488]>
    URPARAM61 TEXTEQU <[RSP+496]>
    URPARAM62 TEXTEQU <[RSP+504]>
    URPARAM63 TEXTEQU <[RSP+512]>
   ;/ 32bits*/
    UDRET TEXTEQU <EAX>
    UDRETURN TEXTEQU <EAX>
    UDSIDX TEXTEQU <ESI>
    UDDIDX TEXTEQU <EDI>
    UDBPTR TEXTEQU <EBP>
    UDSPTR TEXTEQU <ESP>
    UDBASE TEXTEQU <EBX>
    UDPARAM0 TEXTEQU <EDI>
    UDPARAM1 TEXTEQU <ESI>
    UDPARAM2 TEXTEQU <EDX>
    UDPARAM3 TEXTEQU <ECX>
    UDPARAM4 TEXTEQU <R8D>
    UDPARAM5 TEXTEQU <R9D>
    UDPARAM6 TEXTEQU <[ESP+28]>
    UDPARAM7 TEXTEQU <[ESP+32]>
    UDPARAM8 TEXTEQU <[ESP+36]>
    UDPARAM9 TEXTEQU <[ESP+40]>
    UDPARAM10 TEXTEQU <[ESP+44]>
    UDPARAM11 TEXTEQU <[ESP+48]>
    UDPARAM12 TEXTEQU <[ESP+52]>
    UDPARAM13 TEXTEQU <[ESP+56]>
    UDPARAM14 TEXTEQU <[ESP+60]>
    UDPARAM15 TEXTEQU <[ESP+64]>
    UDPARAM16 TEXTEQU <[ESP+68]>
    UDPARAM17 TEXTEQU <[ESP+72]>
    UDPARAM18 TEXTEQU <[ESP+76]>
    UDPARAM19 TEXTEQU <[ESP+80]>
    UDPARAM20 TEXTEQU <[ESP+84]>
    UDPARAM21 TEXTEQU <[ESP+88]>
    UDPARAM22 TEXTEQU <[ESP+92]>
    UDPARAM23 TEXTEQU <[ESP+96]>
    UDPARAM24 TEXTEQU <[ESP+100]>
    UDPARAM25 TEXTEQU <[ESP+104]>
    UDPARAM26 TEXTEQU <[ESP+108]>
    UDPARAM27 TEXTEQU <[ESP+112]>
    UDPARAM28 TEXTEQU <[ESP+116]>
    UDPARAM29 TEXTEQU <[ESP+120]>
    UDPARAM30 TEXTEQU <[ESP+124]>
    UDPARAM31 TEXTEQU <[ESP+128]>
    UDPARAM32 TEXTEQU <[ESP+132]>
    UDPARAM33 TEXTEQU <[ESP+136]>
    UDPARAM34 TEXTEQU <[ESP+140]>
    UDPARAM35 TEXTEQU <[ESP+144]>
    UDPARAM36 TEXTEQU <[ESP+148]>
    UDPARAM37 TEXTEQU <[ESP+152]>
    UDPARAM38 TEXTEQU <[ESP+156]>
    UDPARAM39 TEXTEQU <[ESP+160]>
    UDPARAM40 TEXTEQU <[ESP+164]>
    UDPARAM41 TEXTEQU <[ESP+168]>
    UDPARAM42 TEXTEQU <[ESP+172]>
    UDPARAM43 TEXTEQU <[ESP+176]>
    UDPARAM44 TEXTEQU <[ESP+180]>
    UDPARAM45 TEXTEQU <[ESP+184]>
    UDPARAM46 TEXTEQU <[ESP+188]>
    UDPARAM47 TEXTEQU <[ESP+192]>
    UDPARAM48 TEXTEQU <[ESP+196]>
    UDPARAM49 TEXTEQU <[ESP+200]>
    UDPARAM50 TEXTEQU <[ESP+204]>
    UDPARAM51 TEXTEQU <[ESP+208]>
    UDPARAM52 TEXTEQU <[ESP+212]>
    UDPARAM53 TEXTEQU <[ESP+216]>
    UDPARAM54 TEXTEQU <[ESP+220]>
    UDPARAM55 TEXTEQU <[ESP+224]>
    UDPARAM56 TEXTEQU <[ESP+228]>
    UDPARAM57 TEXTEQU <[ESP+232]>
    UDPARAM58 TEXTEQU <[ESP+236]>
    UDPARAM59 TEXTEQU <[ESP+240]>
    UDPARAM60 TEXTEQU <[ESP+244]>
    UDPARAM61 TEXTEQU <[ESP+248]>
    UDPARAM62 TEXTEQU <[ESP+252]>
    UDPARAM63 TEXTEQU <[ESP+256]>
   ;/ 16bits*/
    UWRET TEXTEQU <AX>
    UWRETURN TEXTEQU <AX>
    UWSIDX TEXTEQU <SI>
    UWDIDX TEXTEQU <DI>
    UWBPTR TEXTEQU <BP>
    UWSPTR TEXTEQU <SP>
    UWBASE TEXTEQU <BX>
    UWPARAM0 TEXTEQU <DI>
    UWPARAM1 TEXTEQU <SI>
    UWPARAM2 TEXTEQU <DX>
    UWPARAM3 TEXTEQU <CX>
    UWPARAM4 TEXTEQU <R8W>
    UWPARAM5 TEXTEQU <R9W>
    UWPARAM6 TEXTEQU <[SP+14]>
    UWPARAM7 TEXTEQU <[SP+16]>
    UWPARAM8 TEXTEQU <[SP+18]>
    UWPARAM9 TEXTEQU <[SP+20]>
    UWPARAM10 TEXTEQU <[SP+22]>
    UWPARAM11 TEXTEQU <[SP+24]>
    UWPARAM12 TEXTEQU <[SP+26]>
    UWPARAM13 TEXTEQU <[SP+28]>
    UWPARAM14 TEXTEQU <[SP+30]>
    UWPARAM15 TEXTEQU <[SP+32]>
    UWPARAM16 TEXTEQU <[SP+34]>
    UWPARAM17 TEXTEQU <[SP+36]>
    UWPARAM18 TEXTEQU <[SP+38]>
    UWPARAM19 TEXTEQU <[SP+40]>
    UWPARAM20 TEXTEQU <[SP+42]>
    UWPARAM21 TEXTEQU <[SP+44]>
    UWPARAM22 TEXTEQU <[SP+46]>
    UWPARAM23 TEXTEQU <[SP+48]>
    UWPARAM24 TEXTEQU <[SP+50]>
    UWPARAM25 TEXTEQU <[SP+52]>
    UWPARAM26 TEXTEQU <[SP+54]>
    UWPARAM27 TEXTEQU <[SP+56]>
    UWPARAM28 TEXTEQU <[SP+58]>
    UWPARAM29 TEXTEQU <[SP+60]>
    UWPARAM30 TEXTEQU <[SP+62]>
    UWPARAM31 TEXTEQU <[SP+64]>
    UWPARAM32 TEXTEQU <[SP+66]>
    UWPARAM33 TEXTEQU <[SP+68]>
    UWPARAM34 TEXTEQU <[SP+70]>
    UWPARAM35 TEXTEQU <[SP+72]>
    UWPARAM36 TEXTEQU <[SP+74]>
    UWPARAM37 TEXTEQU <[SP+76]>
    UWPARAM38 TEXTEQU <[SP+78]>
    UWPARAM39 TEXTEQU <[SP+80]>
    UWPARAM40 TEXTEQU <[SP+82]>
    UWPARAM41 TEXTEQU <[SP+84]>
    UWPARAM42 TEXTEQU <[SP+86]>
    UWPARAM43 TEXTEQU <[SP+88]>
    UWPARAM44 TEXTEQU <[SP+90]>
    UWPARAM45 TEXTEQU <[SP+92]>
    UWPARAM46 TEXTEQU <[SP+94]>
    UWPARAM47 TEXTEQU <[SP+96]>
    UWPARAM48 TEXTEQU <[SP+98]>
    UWPARAM49 TEXTEQU <[SP+100]>
    UWPARAM50 TEXTEQU <[SP+102]>
    UWPARAM51 TEXTEQU <[SP+104]>
    UWPARAM52 TEXTEQU <[SP+106]>
    UWPARAM53 TEXTEQU <[SP+108]>
    UWPARAM54 TEXTEQU <[SP+110]>
    UWPARAM55 TEXTEQU <[SP+112]>
    UWPARAM56 TEXTEQU <[SP+114]>
    UWPARAM57 TEXTEQU <[SP+116]>
    UWPARAM58 TEXTEQU <[SP+118]>
    UWPARAM59 TEXTEQU <[SP+120]>
    UWPARAM60 TEXTEQU <[SP+122]>
    UWPARAM61 TEXTEQU <[SP+124]>
    UWPARAM62 TEXTEQU <[SP+126]>
    UWPARAM63 TEXTEQU <[SP+128]>
   ;/ 8bits*/
    UBRET TEXTEQU <AL>
    UBRETURN TEXTEQU <AL>
    UBSIDX TEXTEQU <SIL>
    UBDIDX TEXTEQU <DIL>
    UBBPTR TEXTEQU <BPL>
    UBSPTR TEXTEQU <SPL>
    UBBASE TEXTEQU <BL>
    UBPARAM0 TEXTEQU <DIL>
    UBPARAM1 TEXTEQU <SIL>
    UBPARAM2 TEXTEQU <DL>
    UBPARAM3 TEXTEQU <CL>
    UBPARAM4 TEXTEQU <R8B>
    UBPARAM5 TEXTEQU <R9B>
    UBPARAM6 TEXTEQU <[SPL+7]>
    UBPARAM7 TEXTEQU <[SPL+8]>
    UBPARAM8 TEXTEQU <[SPL+9]>
    UBPARAM9 TEXTEQU <[SPL+10]>
    UBPARAM10 TEXTEQU <[SPL+11]>
    UBPARAM11 TEXTEQU <[SPL+12]>
    UBPARAM12 TEXTEQU <[SPL+13]>
    UBPARAM13 TEXTEQU <[SPL+14]>
    UBPARAM14 TEXTEQU <[SPL+15]>
    UBPARAM15 TEXTEQU <[SPL+16]>
    UBPARAM16 TEXTEQU <[SPL+17]>
    UBPARAM17 TEXTEQU <[SPL+18]>
    UBPARAM18 TEXTEQU <[SPL+19]>
    UBPARAM19 TEXTEQU <[SPL+20]>
    UBPARAM20 TEXTEQU <[SPL+21]>
    UBPARAM21 TEXTEQU <[SPL+22]>
    UBPARAM22 TEXTEQU <[SPL+23]>
    UBPARAM23 TEXTEQU <[SPL+24]>
    UBPARAM24 TEXTEQU <[SPL+25]>
    UBPARAM25 TEXTEQU <[SPL+26]>
    UBPARAM26 TEXTEQU <[SPL+27]>
    UBPARAM27 TEXTEQU <[SPL+28]>
    UBPARAM28 TEXTEQU <[SPL+29]>
    UBPARAM29 TEXTEQU <[SPL+30]>
    UBPARAM30 TEXTEQU <[SPL+31]>
    UBPARAM31 TEXTEQU <[SPL+32]>
    UBPARAM32 TEXTEQU <[SPL+33]>
    UBPARAM33 TEXTEQU <[SPL+34]>
    UBPARAM34 TEXTEQU <[SPL+35]>
    UBPARAM35 TEXTEQU <[SPL+36]>
    UBPARAM36 TEXTEQU <[SPL+37]>
    UBPARAM37 TEXTEQU <[SPL+38]>
    UBPARAM38 TEXTEQU <[SPL+39]>
    UBPARAM39 TEXTEQU <[SPL+40]>
    UBPARAM40 TEXTEQU <[SPL+41]>
    UBPARAM41 TEXTEQU <[SPL+42]>
    UBPARAM42 TEXTEQU <[SPL+43]>
    UBPARAM43 TEXTEQU <[SPL+44]>
    UBPARAM44 TEXTEQU <[SPL+45]>
    UBPARAM45 TEXTEQU <[SPL+46]>
    UBPARAM46 TEXTEQU <[SPL+47]>
    UBPARAM47 TEXTEQU <[SPL+48]>
    UBPARAM48 TEXTEQU <[SPL+49]>
    UBPARAM49 TEXTEQU <[SPL+50]>
    UBPARAM50 TEXTEQU <[SPL+51]>
    UBPARAM51 TEXTEQU <[SPL+52]>
    UBPARAM52 TEXTEQU <[SPL+53]>
    UBPARAM53 TEXTEQU <[SPL+54]>
    UBPARAM54 TEXTEQU <[SPL+55]>
    UBPARAM55 TEXTEQU <[SPL+56]>
    UBPARAM56 TEXTEQU <[SPL+57]>
    UBPARAM57 TEXTEQU <[SPL+58]>
    UBPARAM58 TEXTEQU <[SPL+59]>
    UBPARAM59 TEXTEQU <[SPL+60]>
    UBPARAM60 TEXTEQU <[SPL+61]>
    UBPARAM61 TEXTEQU <[SPL+62]>
    UBPARAM62 TEXTEQU <[SPL+63]>
    UBPARAM63 TEXTEQU <[SPL+64]>
    ENDIF
    ;/*__UNIX64__*/

    IFDEF __UNIX32__
   ;/** Intel386 */
   ;/** 32bits*/
    RRET TEXTEQU <EAX>
    RRETURN TEXTEQU <EAX>
    RSIDX TEXTEQU <ESI>
    RDIDX TEXTEQU <EDI>
    RBPTR TEXTEQU <EBP>
    RSPTR TEXTEQU <ESP>
    RBASE TEXTEQU <EBX>
    RPARAM0 TEXTEQU <ECX>
    RPARAM1 TEXTEQU <EDX>
    RPARAM2 TEXTEQU <[ESP+12]>
    RPARAM3 TEXTEQU <[ESP+16]>
    RPARAM4 TEXTEQU <[ESP+20]>
    RPARAM5 TEXTEQU <[ESP+24]>
    RPARAM6 TEXTEQU <[ESP+28]>
    RPARAM7 TEXTEQU <[ESP+32]>
    RPARAM8 TEXTEQU <[ESP+36]>
    RPARAM9 TEXTEQU <[ESP+40]>
    RPARAM10 TEXTEQU <[ESP+44]>
    RPARAM11 TEXTEQU <[ESP+48]>
    RPARAM12 TEXTEQU <[ESP+52]>
    RPARAM13 TEXTEQU <[ESP+56]>
    RPARAM13 TEXTEQU <[ESP+60]>
    RPARAM14 TEXTEQU <[ESP+64]>
    RPARAM15 TEXTEQU <[ESP+68]>
    RPARAM16 TEXTEQU <[ESP+72]>
    RPARAM17 TEXTEQU <[ESP+76]>
    RPARAM19 TEXTEQU <[ESP+80]>
    RPARAM20 TEXTEQU <[ESP+84]>
    RPARAM21 TEXTEQU <[ESP+88]>
    RPARAM22 TEXTEQU <[ESP+92]>
    RPARAM23 TEXTEQU <[ESP+96]>
    RPARAM24 TEXTEQU <[ESP+100]>
    RPARAM25 TEXTEQU <[ESP+104]>
    RPARAM26 TEXTEQU <[ESP+108]>
    RPARAM27 TEXTEQU <[ESP+112]>
    RPARAM28 TEXTEQU <[ESP+116]>
    RPARAM29 TEXTEQU <[ESP+120]>
    RPARAM30 TEXTEQU <[ESP+124]>
    RPARAM31 TEXTEQU <[ESP+128]>
    RPARAM32 TEXTEQU <[ESP+132]>
    RPARAM33 TEXTEQU <[ESP+136]>
    RPARAM34 TEXTEQU <[ESP+140]>
    RPARAM35 TEXTEQU <[ESP+144]>
    RPARAM36 TEXTEQU <[ESP+148]>
    RPARAM37 TEXTEQU <[ESP+152]>
    RPARAM38 TEXTEQU <[ESP+156]>
    RPARAM39 TEXTEQU <[ESP+160]>
    RPARAM40 TEXTEQU <[ESP+164]>
    RPARAM41 TEXTEQU <[ESP+168]>
    RPARAM42 TEXTEQU <[ESP+172]>
    RPARAM43 TEXTEQU <[ESP+176]>
    RPARAM44 TEXTEQU <[ESP+180]>
    RPARAM45 TEXTEQU <[ESP+184]>
    RPARAM46 TEXTEQU <[ESP+188]>
    RPARAM47 TEXTEQU <[ESP+192]>
    RPARAM48 TEXTEQU <[ESP+196]>
    RPARAM49 TEXTEQU <[ESP+200]>
    RPARAM50 TEXTEQU <[ESP+204]>
    RPARAM51 TEXTEQU <[ESP+208]>
    RPARAM52 TEXTEQU <[ESP+212]>
    RPARAM53 TEXTEQU <[ESP+216]>
    RPARAM54 TEXTEQU <[ESP+220]>
    RPARAM55 TEXTEQU <[ESP+224]>
    RPARAM56 TEXTEQU <[ESP+228]>
    RPARAM57 TEXTEQU <[ESP+232]>
    RPARAM58 TEXTEQU <[ESP+236]>
    RPARAM59 TEXTEQU <[ESP+240]>
    RPARAM60 TEXTEQU <[ESP+244]>
    RPARAM61 TEXTEQU <[ESP+248]>
    RPARAM62 TEXTEQU <[ESP+252]>
    RPARAM63 TEXTEQU <[ESP+256]>
   ;/** 32bits*/
    DRET TEXTEQU <EAX>
    DRETURN TEXTEQU <EAX>
    DSIDX TEXTEQU <ESI>
    DDIDX TEXTEQU <EDI>
    DBPTR TEXTEQU <EBP>
    DSPTR TEXTEQU <ESP>
    DBASE TEXTEQU <EBX>
    DPARAM0 TEXTEQU <ECX>
    DPARAM1 TEXTEQU <EDX>
    DPARAM2 TEXTEQU <[ESP+12]>
    DPARAM3 TEXTEQU <[ESP+16]>
    DPARAM4 TEXTEQU <[ESP+20]>
    DPARAM5 TEXTEQU <[ESP+24]>
    DPARAM6 TEXTEQU <[ESP+28]>
    DPARAM7 TEXTEQU <[ESP+32]>
    DPARAM8 TEXTEQU <[ESP+36]>
    DPARAM9 TEXTEQU <[ESP+40]>
    DPARAM10 TEXTEQU <[ESP+44]>
    DPARAM11 TEXTEQU <[ESP+48]>
    DPARAM12 TEXTEQU <[ESP+52]>
    DPARAM13 TEXTEQU <[ESP+56]>
    DPARAM14 TEXTEQU <[ESP+60]>
    DPARAM15 TEXTEQU <[ESP+64]>
    DPARAM16 TEXTEQU <[ESP+68]>
    DPARAM17 TEXTEQU <[ESP+72]>
    DPARAM18 TEXTEQU <[ESP+76]>
    DPARAM19 TEXTEQU <[ESP+80]>
    DPARAM20 TEXTEQU <[ESP+84]>
    DPARAM21 TEXTEQU <[ESP+88]>
    DPARAM22 TEXTEQU <[ESP+92]>
    DPARAM23 TEXTEQU <[ESP+96]>
    DPARAM24 TEXTEQU <[ESP+100]>
    DPARAM25 TEXTEQU <[ESP+104]>
    DPARAM26 TEXTEQU <[ESP+108]>
    DPARAM27 TEXTEQU <[ESP+112]>
    DPARAM28 TEXTEQU <[ESP+116]>
    DPARAM29 TEXTEQU <[ESP+120]>
    DPARAM30 TEXTEQU <[ESP+124]>
    DPARAM31 TEXTEQU <[ESP+128]>
    DPARAM32 TEXTEQU <[ESP+132]>
    DPARAM33 TEXTEQU <[ESP+136]>
    DPARAM34 TEXTEQU <[ESP+140]>
    DPARAM35 TEXTEQU <[ESP+144]>
    DPARAM36 TEXTEQU <[ESP+148]>
    DPARAM37 TEXTEQU <[ESP+152]>
    DPARAM38 TEXTEQU <[ESP+156]>
    DPARAM39 TEXTEQU <[ESP+160]>
    DPARAM40 TEXTEQU <[ESP+164]>
    DPARAM41 TEXTEQU <[ESP+168]>
    DPARAM42 TEXTEQU <[ESP+172]>
    DPARAM43 TEXTEQU <[ESP+176]>
    DPARAM44 TEXTEQU <[ESP+180]>
    DPARAM45 TEXTEQU <[ESP+184]>
    DPARAM46 TEXTEQU <[ESP+188]>
    DPARAM47 TEXTEQU <[ESP+192]>
    DPARAM48 TEXTEQU <[ESP+196]>
    DPARAM49 TEXTEQU <[ESP+200]>
    DPARAM50 TEXTEQU <[ESP+204]>
    DPARAM51 TEXTEQU <[ESP+208]>
    DPARAM52 TEXTEQU <[ESP+212]>
    DPARAM53 TEXTEQU <[ESP+216]>
    DPARAM54 TEXTEQU <[ESP+220]>
    DPARAM55 TEXTEQU <[ESP+224]>
    DPARAM56 TEXTEQU <[ESP+228]>
    DPARAM57 TEXTEQU <[ESP+232]>
    DPARAM58 TEXTEQU <[ESP+236]>
    DPARAM59 TEXTEQU <[ESP+240]>
    DPARAM60 TEXTEQU <[ESP+244]>
    DPARAM61 TEXTEQU <[ESP+248]>
    DPARAM62 TEXTEQU <[ESP+252]>
    DPARAM63 TEXTEQU <[ESP+256]>
   ;/** 16bits*/
    WRET TEXTEQU <AX>
    WRETURN TEXTEQU <AX>
    WSIDX TEXTEQU <SI>
    WDIDX TEXTEQU <DI>
    WBPTR TEXTEQU <BP>
    WSPTR TEXTEQU <SP>
    WBASE TEXTEQU <BX>
    WPARAM0 TEXTEQU <CX>
    WPARAM1 TEXTEQU <DX>
    WPARAM2 TEXTEQU <[SP+6]>
    WPARAM3 TEXTEQU <[SP+8]>
    WPARAM4 TEXTEQU <[SP+10]>
    WPARAM5 TEXTEQU <[SP+12]>
    WPARAM6 TEXTEQU <[SP+14]>
    WPARAM7 TEXTEQU <[SP+16]>
    WPARAM8 TEXTEQU <[SP+18]>
    WPARAM9 TEXTEQU <[SP+20]>
    WPARAM10 TEXTEQU <[SP+22]>
    WPARAM11 TEXTEQU <[SP+24]>
    WPARAM12 TEXTEQU <[SP+26]>
    WPARAM13 TEXTEQU <[SP+28]>
    WPARAM14 TEXTEQU <[SP+30]>
    WPARAM15 TEXTEQU <[SP+32]>
    WPARAM16 TEXTEQU <[SP+34]>
    WPARAM17 TEXTEQU <[SP+36]>
    WPARAM18 TEXTEQU <[SP+38]>
    WPARAM19 TEXTEQU <[SP+40]>
    WPARAM20 TEXTEQU <[SP+42]>
    WPARAM21 TEXTEQU <[SP+44]>
    WPARAM22 TEXTEQU <[SP+46]>
    WPARAM23 TEXTEQU <[SP+48]>
    WPARAM24 TEXTEQU <[SP+50]>
    WPARAM25 TEXTEQU <[SP+52]>
    WPARAM26 TEXTEQU <[SP+54]>
    WPARAM27 TEXTEQU <[SP+56]>
    WPARAM28 TEXTEQU <[SP+58]>
    WPARAM29 TEXTEQU <[SP+60]>
    WPARAM30 TEXTEQU <[SP+62]>
    WPARAM31 TEXTEQU <[SP+64]>
    WPARAM32 TEXTEQU <[SP+66]>
    WPARAM33 TEXTEQU <[SP+68]>
    WPARAM34 TEXTEQU <[SP+70]>
    WPARAM35 TEXTEQU <[SP+72]>
    WPARAM36 TEXTEQU <[SP+74]>
    WPARAM37 TEXTEQU <[SP+76]>
    WPARAM38 TEXTEQU <[SP+78]>
    WPARAM39 TEXTEQU <[SP+80]>
    WPARAM40 TEXTEQU <[SP+82]>
    WPARAM41 TEXTEQU <[SP+84]>
    WPARAM42 TEXTEQU <[SP+86]>
    WPARAM43 TEXTEQU <[SP+88]>
    WPARAM44 TEXTEQU <[SP+90]>
    WPARAM45 TEXTEQU <[SP+92]>
    WPARAM46 TEXTEQU <[SP+94]>
    WPARAM47 TEXTEQU <[SP+96]>
    WPARAM48 TEXTEQU <[SP+98]>
    WPARAM49 TEXTEQU <[SP+100]>
    WPARAM50 TEXTEQU <[SP+102]>
    WPARAM51 TEXTEQU <[SP+104]>
    WPARAM52 TEXTEQU <[SP+106]>
    WPARAM53 TEXTEQU <[SP+108]>
    WPARAM54 TEXTEQU <[SP+110]>
    WPARAM55 TEXTEQU <[SP+112]>
    WPARAM56 TEXTEQU <[SP+114]>
    WPARAM57 TEXTEQU <[SP+116]>
    WPARAM58 TEXTEQU <[SP+118]>
    WPARAM59 TEXTEQU <[SP+120]>
    WPARAM60 TEXTEQU <[SP+122]>
    WPARAM61 TEXTEQU <[SP+124]>
    WPARAM62 TEXTEQU <[SP+126]>
    WPARAM63 TEXTEQU <[SP+128]>
   ;/** 8bits*/
    BRET TEXTEQU <AL>
    BRETURN TEXTEQU <AL>
    BSIDX TEXTEQU <SIL>
    BDIDX TEXTEQU <DIL>
    BBPTR TEXTEQU <BPL>
    BSPTR TEXTEQU <SPL>
    BBASE TEXTEQU <BL>
    BPARAM0 TEXTEQU <CL>
    BPARAM1 TEXTEQU <DL>
    BPARAM2 TEXTEQU <[SPL+3]>
    BPARAM3 TEXTEQU <[SPL+4]>
    BPARAM4 TEXTEQU <[SPL+5]>
    BPARAM5 TEXTEQU <[SPL+6]>
    BPARAM6 TEXTEQU <[SPL+7]>
    BPARAM7 TEXTEQU <[SPL+8]>
    BPARAM8 TEXTEQU <[SPL+9]>
    BPARAM9 TEXTEQU <[SPL+10]>
    BPARAM10 TEXTEQU <[SPL+11]>
    BPARAM11 TEXTEQU <[SPL+12]>
    BPARAM12 TEXTEQU <[SPL+13]>
    BPARAM13 TEXTEQU <[SPL+14]>
    BPARAM14 TEXTEQU <[SPL+15]>
    BPARAM15 TEXTEQU <[SPL+16]>
    BPARAM16 TEXTEQU <[SPL+17]>
    BPARAM17 TEXTEQU <[SPL+18]>
    BPARAM18 TEXTEQU <[SPL+19]>
    BPARAM19 TEXTEQU <[SPL+20]>
    BPARAM20 TEXTEQU <[SPL+21]>
    BPARAM21 TEXTEQU <[SPL+22]>
    BPARAM22 TEXTEQU <[SPL+23]>
    BPARAM23 TEXTEQU <[SPL+24]>
    BPARAM24 TEXTEQU <[SPL+25]>
    BPARAM25 TEXTEQU <[SPL+26]>
    BPARAM26 TEXTEQU <[SPL+27]>
    BPARAM27 TEXTEQU <[SPL+28]>
    BPARAM28 TEXTEQU <[SPL+29]>
    BPARAM29 TEXTEQU <[SPL+30]>
    BPARAM30 TEXTEQU <[SPL+31]>
    BPARAM31 TEXTEQU <[SPL+32]>
    BPARAM32 TEXTEQU <[SPL+33]>
    BPARAM33 TEXTEQU <[SPL+34]>
    BPARAM34 TEXTEQU <[SPL+35]>
    BPARAM35 TEXTEQU <[SPL+36]>
    BPARAM36 TEXTEQU <[SPL+37]>
    BPARAM37 TEXTEQU <[SPL+38]>
    BPARAM38 TEXTEQU <[SPL+39]>
    BPARAM39 TEXTEQU <[SPL+40]>
    BPARAM40 TEXTEQU <[SPL+41]>
    BPARAM41 TEXTEQU <[SPL+42]>
    BPARAM42 TEXTEQU <[SPL+43]>
    BPARAM43 TEXTEQU <[SPL+44]>
    BPARAM44 TEXTEQU <[SPL+45]>
    BPARAM45 TEXTEQU <[SPL+46]>
    BPARAM46 TEXTEQU <[SPL+47]>
    BPARAM47 TEXTEQU <[SPL+48]>
    BPARAM48 TEXTEQU <[SPL+49]>
    BPARAM49 TEXTEQU <[SPL+50]>
    BPARAM50 TEXTEQU <[SPL+51]>
    BPARAM51 TEXTEQU <[SPL+52]>
    BPARAM52 TEXTEQU <[SPL+53]>
    BPARAM53 TEXTEQU <[SPL+54]>
    BPARAM54 TEXTEQU <[SPL+55]>
    BPARAM55 TEXTEQU <[SPL+56]>
    BPARAM56 TEXTEQU <[SPL+57]>
    BPARAM57 TEXTEQU <[SPL+58]>
    BPARAM58 TEXTEQU <[SPL+59]>
    BPARAM59 TEXTEQU <[SPL+60]>
    BPARAM60 TEXTEQU <[SPL+61]>
    BPARAM61 TEXTEQU <[SPL+62]>
    BPARAM62 TEXTEQU <[SPL+63]>
    BPARAM63 TEXTEQU <[SPL+64]>

   ;/ Regcall */
   ;/ 32bits*/
    RRRET TEXTEQU <EAX>
    RRRETURN TEXTEQU <EAX>
    RRSIDX TEXTEQU <ESI>
    RRDIDX TEXTEQU <EDI>
    RRBPTR TEXTEQU <EBP>
    RRSPTR TEXTEQU <ESP>
    RRBASE TEXTEQU <EBX>
    RRPARAM0 TEXTEQU <EAX>
    RRPARAM1 TEXTEQU <ECX>
    RRPARAM2 TEXTEQU <EDX>
    RRPARAM3 TEXTEQU <EDI>
    RRPARAM4 TEXTEQU <ESI>
    RRPARAM5 TEXTEQU <[ESP+24]>
    RRPARAM6 TEXTEQU <[ESP+28]>
    RRPARAM7 TEXTEQU <[ESP+32]>
    RRPARAM8 TEXTEQU <[ESP+36]>
    RRPARAM9 TEXTEQU <[ESP+40]>
    RRPARAM10 TEXTEQU <[ESP+44]>
    RRPARAM11 TEXTEQU <[ESP+48]>
    RRPARAM12 TEXTEQU <[ESP+52]>
    RRPARAM13 TEXTEQU <[ESP+56]>
    RRPARAM14 TEXTEQU <[ESP+60]>
    RRPARAM15 TEXTEQU <[ESP+64]>
    RRPARAM16 TEXTEQU <[ESP+68]>
    RRPARAM17 TEXTEQU <[ESP+72]>
    RRPARAM18 TEXTEQU <[ESP+76]>
    RRPARAM19 TEXTEQU <[ESP+80]>
    RRPARAM20 TEXTEQU <[ESP+84]>
    RRPARAM21 TEXTEQU <[ESP+88]>
    RRPARAM22 TEXTEQU <[ESP+92]>
    RRPARAM23 TEXTEQU <[ESP+96]>
    RRPARAM24 TEXTEQU <[ESP+100]>
    RRPARAM25 TEXTEQU <[ESP+104]>
    RRPARAM26 TEXTEQU <[ESP+108]>
    RRPARAM27 TEXTEQU <[ESP+112]>
    RRPARAM28 TEXTEQU <[ESP+116]>
    RRPARAM29 TEXTEQU <[ESP+120]>
    RRPARAM30 TEXTEQU <[ESP+124]>
    RRPARAM31 TEXTEQU <[ESP+128]>
    RRPARAM32 TEXTEQU <[ESP+132]>
    RRPARAM33 TEXTEQU <[ESP+136]>
    RRPARAM34 TEXTEQU <[ESP+140]>
    RRPARAM35 TEXTEQU <[ESP+144]>
    RRPARAM36 TEXTEQU <[ESP+148]>
    RRPARAM37 TEXTEQU <[ESP+152]>
    RRPARAM38 TEXTEQU <[ESP+156]>
    RRPARAM39 TEXTEQU <[ESP+160]>
    RRPARAM40 TEXTEQU <[ESP+164]>
    RRPARAM41 TEXTEQU <[ESP+168]>
    RRPARAM42 TEXTEQU <[ESP+172]>
    RRPARAM43 TEXTEQU <[ESP+176]>
    RRPARAM44 TEXTEQU <[ESP+180]>
    RRPARAM45 TEXTEQU <[ESP+184]>
    RRPARAM46 TEXTEQU <[ESP+188]>
    RRPARAM47 TEXTEQU <[ESP+192]>
    RRPARAM48 TEXTEQU <[ESP+196]>
    RRPARAM49 TEXTEQU <[ESP+200]>
    RRPARAM50 TEXTEQU <[ESP+204]>
    RRPARAM51 TEXTEQU <[ESP+208]>
    RRPARAM52 TEXTEQU <[ESP+212]>
    RRPARAM53 TEXTEQU <[ESP+216]>
    RRPARAM54 TEXTEQU <[ESP+220]>
    RRPARAM55 TEXTEQU <[ESP+224]>
    RRPARAM56 TEXTEQU <[ESP+228]>
    RRPARAM57 TEXTEQU <[ESP+232]>
    RRPARAM58 TEXTEQU <[ESP+236]>
    RRPARAM59 TEXTEQU <[ESP+240]>
    RRPARAM60 TEXTEQU <[ESP+244]>
    RRPARAM61 TEXTEQU <[ESP+248]>
    RRPARAM62 TEXTEQU <[ESP+252]>
    RRPARAM63 TEXTEQU <[ESP+256]>
   ;/ 32bits*/
    RDRET TEXTEQU <EAX>
    RDRETURN TEXTEQU <EAX>
    RDSIDX TEXTEQU <ESI>
    RDDIDX TEXTEQU <EDI>
    RDBPTR TEXTEQU <EBP>
    RDSPTR TEXTEQU <ESP>
    RDBASE TEXTEQU <EBX>
    RDPARAM0 TEXTEQU <EAX>
    RDPARAM1 TEXTEQU <ECX>
    RDPARAM2 TEXTEQU <EDX>
    RDPARAM3 TEXTEQU <EDI>
    RDPARAM4 TEXTEQU <ESI>
    RDPARAM5 TEXTEQU <[ESP+24]>
    RDPARAM6 TEXTEQU <[ESP+28]>
    RDPARAM7 TEXTEQU <[ESP+32]>
    RDPARAM8 TEXTEQU <[ESP+36]>
    RDPARAM9 TEXTEQU <[ESP+40]>
    RDPARAM10 TEXTEQU <[ESP+44]>
    RDPARAM11 TEXTEQU <[ESP+48]>
    RDPARAM12 TEXTEQU <[ESP+52]>
    RDPARAM13 TEXTEQU <[ESP+56]>
    RDPARAM14 TEXTEQU <[ESP+60]>
    RDPARAM15 TEXTEQU <[ESP+64]>
    RDPARAM16 TEXTEQU <[ESP+68]>
    RDPARAM17 TEXTEQU <[ESP+72]>
    RDPARAM18 TEXTEQU <[ESP+76]>
    RDPARAM19 TEXTEQU <[ESP+80]>
    RDPARAM20 TEXTEQU <[ESP+84]>
    RDPARAM21 TEXTEQU <[ESP+88]>
    RDPARAM22 TEXTEQU <[ESP+92]>
    RDPARAM23 TEXTEQU <[ESP+96]>
    RDPARAM24 TEXTEQU <[ESP+100]>
    RDPARAM25 TEXTEQU <[ESP+104]>
    RDPARAM26 TEXTEQU <[ESP+108]>
    RDPARAM27 TEXTEQU <[ESP+112]>
    RDPARAM28 TEXTEQU <[ESP+116]>
    RDPARAM29 TEXTEQU <[ESP+120]>
    RDPARAM30 TEXTEQU <[ESP+124]>
    RDPARAM31 TEXTEQU <[ESP+128]>
    RDPARAM32 TEXTEQU <[ESP+132]>
    RDPARAM33 TEXTEQU <[ESP+136]>
    RDPARAM34 TEXTEQU <[ESP+140]>
    RDPARAM35 TEXTEQU <[ESP+144]>
    RDPARAM36 TEXTEQU <[ESP+148]>
    RDPARAM37 TEXTEQU <[ESP+152]>
    RDPARAM38 TEXTEQU <[ESP+156]>
    RDPARAM39 TEXTEQU <[ESP+160]>
    RDPARAM40 TEXTEQU <[ESP+164]>
    RDPARAM41 TEXTEQU <[ESP+168]>
    RDPARAM42 TEXTEQU <[ESP+172]>
    RDPARAM43 TEXTEQU <[ESP+176]>
    RDPARAM44 TEXTEQU <[ESP+180]>
    RDPARAM45 TEXTEQU <[ESP+184]>
    RDPARAM46 TEXTEQU <[ESP+188]>
    RDPARAM47 TEXTEQU <[ESP+192]>
    RDPARAM48 TEXTEQU <[ESP+196]>
    RDPARAM49 TEXTEQU <[ESP+200]>
    RDPARAM50 TEXTEQU <[ESP+204]>
    RDPARAM51 TEXTEQU <[ESP+208]>
    RDPARAM52 TEXTEQU <[ESP+212]>
    RDPARAM53 TEXTEQU <[ESP+216]>
    RDPARAM54 TEXTEQU <[ESP+220]>
    RDPARAM55 TEXTEQU <[ESP+224]>
    RDPARAM56 TEXTEQU <[ESP+228]>
    RDPARAM57 TEXTEQU <[ESP+232]>
    RDPARAM58 TEXTEQU <[ESP+236]>
    RDPARAM59 TEXTEQU <[ESP+240]>
    RDPARAM60 TEXTEQU <[ESP+244]>
    RDPARAM61 TEXTEQU <[ESP+248]>
    RDPARAM62 TEXTEQU <[ESP+252]>
    RDPARAM63 TEXTEQU <[ESP+256]>
   ;/ 16bits*/
    RWRET TEXTEQU <AX>
    RWRETURN TEXTEQU <AX>
    RWSIDX TEXTEQU <SI>
    RWDIDX TEXTEQU <DI>
    RWBPTR TEXTEQU <BP>
    RWSPTR TEXTEQU <SP>
    RWBASE TEXTEQU <BX>
    RWPARAM0 TEXTEQU <AX>
    RWPARAM1 TEXTEQU <CX>
    RWPARAM2 TEXTEQU <DX>
    RWPARAM3 TEXTEQU <DI>
    RWPARAM4 TEXTEQU <SI>
    RWPARAM5 TEXTEQU <[SP+12]>
    RWPARAM6 TEXTEQU <[SP+14]>
    RWPARAM7 TEXTEQU <[SP+16]>
    RWPARAM8 TEXTEQU <[SP+18]>
    RWPARAM9 TEXTEQU <[SP+20]>
    RWPARAM10 TEXTEQU <[SP+22]>
    RWPARAM11 TEXTEQU <[SP+24]>
    RWPARAM12 TEXTEQU <[SP+26]>
    RWPARAM13 TEXTEQU <[SP+28]>
    RWPARAM14 TEXTEQU <[SP+30]>
    RWPARAM15 TEXTEQU <[SP+32]>
    RWPARAM16 TEXTEQU <[SP+34]>
    RWPARAM17 TEXTEQU <[SP+36]>
    RWPARAM18 TEXTEQU <[SP+38]>
    RWPARAM19 TEXTEQU <[SP+40]>
    RWPARAM20 TEXTEQU <[SP+42]>
    RWPARAM21 TEXTEQU <[SP+44]>
    RWPARAM22 TEXTEQU <[SP+46]>
    RWPARAM23 TEXTEQU <[SP+48]>
    RWPARAM24 TEXTEQU <[SP+50]>
    RWPARAM25 TEXTEQU <[SP+52]>
    RWPARAM26 TEXTEQU <[SP+54]>
    RWPARAM27 TEXTEQU <[SP+56]>
    RWPARAM28 TEXTEQU <[SP+58]>
    RWPARAM29 TEXTEQU <[SP+60]>
    RWPARAM30 TEXTEQU <[SP+62]>
    RWPARAM31 TEXTEQU <[SP+64]>
    RWPARAM32 TEXTEQU <[SP+66]>
    RWPARAM33 TEXTEQU <[SP+68]>
    RWPARAM34 TEXTEQU <[SP+70]>
    RWPARAM35 TEXTEQU <[SP+72]>
    RWPARAM36 TEXTEQU <[SP+74]>
    RWPARAM37 TEXTEQU <[SP+76]>
    RWPARAM38 TEXTEQU <[SP+78]>
    RWPARAM39 TEXTEQU <[SP+80]>
    RWPARAM40 TEXTEQU <[SP+82]>
    RWPARAM41 TEXTEQU <[SP+84]>
    RWPARAM42 TEXTEQU <[SP+86]>
    RWPARAM43 TEXTEQU <[SP+88]>
    RWPARAM44 TEXTEQU <[SP+90]>
    RWPARAM45 TEXTEQU <[SP+92]>
    RWPARAM46 TEXTEQU <[SP+94]>
    RWPARAM47 TEXTEQU <[SP+96]>
    RWPARAM48 TEXTEQU <[SP+98]>
    RWPARAM49 TEXTEQU <[SP+100]>
    RWPARAM50 TEXTEQU <[SP+102]>
    RWPARAM51 TEXTEQU <[SP+104]>
    RWPARAM52 TEXTEQU <[SP+106]>
    RWPARAM53 TEXTEQU <[SP+108]>
    RWPARAM54 TEXTEQU <[SP+110]>
    RWPARAM55 TEXTEQU <[SP+112]>
    RWPARAM56 TEXTEQU <[SP+114]>
    RWPARAM57 TEXTEQU <[SP+116]>
    RWPARAM58 TEXTEQU <[SP+118]>
    RWPARAM59 TEXTEQU <[SP+120]>
    RWPARAM60 TEXTEQU <[SP+122]>
    RWPARAM61 TEXTEQU <[SP+124]>
    RWPARAM62 TEXTEQU <[SP+126]>
    RWPARAM63 TEXTEQU <[SP+128]>
   ;/ 8bits*/
    RBRET TEXTEQU <AL>
    RBRETURN TEXTEQU <AL>
    RBSIDX TEXTEQU <SIL>
    RBDIDX TEXTEQU <DIL>
    RBBPTR TEXTEQU <BPL>
    RBSPTR TEXTEQU <SPL>
    RBBASE TEXTEQU <BL>
    RBPARAM0 TEXTEQU <AL>
    RBPARAM1 TEXTEQU <CL>
    RBPARAM2 TEXTEQU <DL>
    RBPARAM3 TEXTEQU <DIL>
    RBPARAM4 TEXTEQU <SIL>
    RBPARAM5 TEXTEQU <[SPL+6]>
    RBPARAM6 TEXTEQU <[SPL+7]>
    RBPARAM7 TEXTEQU <[SPL+8]>
    RBPARAM8 TEXTEQU <[SPL+9]>
    RBPARAM9 TEXTEQU <[SPL+10]>
    RBPARAM10 TEXTEQU <[SPL+11]>
    RBPARAM11 TEXTEQU <[SPL+12]>
    RBPARAM12 TEXTEQU <[SPL+13]>
    RBPARAM13 TEXTEQU <[SPL+14]>
    RBPARAM14 TEXTEQU <[SPL+15]>
    RBPARAM15 TEXTEQU <[SPL+16]>
    RBPARAM16 TEXTEQU <[SPL+17]>
    RBPARAM17 TEXTEQU <[SPL+18]>
    RBPARAM18 TEXTEQU <[SPL+19]>
    RBPARAM19 TEXTEQU <[SPL+20]>
    RBPARAM20 TEXTEQU <[SPL+21]>
    RBPARAM21 TEXTEQU <[SPL+22]>
    RBPARAM22 TEXTEQU <[SPL+23]>
    RBPARAM23 TEXTEQU <[SPL+24]>
    RBPARAM24 TEXTEQU <[SPL+25]>
    RBPARAM25 TEXTEQU <[SPL+26]>
    RBPARAM26 TEXTEQU <[SPL+27]>
    RBPARAM27 TEXTEQU <[SPL+28]>
    RBPARAM28 TEXTEQU <[SPL+29]>
    RBPARAM29 TEXTEQU <[SPL+30]>
    RBPARAM30 TEXTEQU <[SPL+31]>
    RBPARAM31 TEXTEQU <[SPL+32]>
    RBPARAM32 TEXTEQU <[SPL+33]>
    RBPARAM33 TEXTEQU <[SPL+34]>
    RBPARAM34 TEXTEQU <[SPL+35]>
    RBPARAM35 TEXTEQU <[SPL+36]>
    RBPARAM36 TEXTEQU <[SPL+37]>
    RBPARAM37 TEXTEQU <[SPL+38]>
    RBPARAM38 TEXTEQU <[SPL+39]>
    RBPARAM39 TEXTEQU <[SPL+40]>
    RBPARAM40 TEXTEQU <[SPL+41]>
    RBPARAM41 TEXTEQU <[SPL+42]>
    RBPARAM42 TEXTEQU <[SPL+43]>
    RBPARAM43 TEXTEQU <[SPL+44]>
    RBPARAM44 TEXTEQU <[SPL+45]>
    RBPARAM45 TEXTEQU <[SPL+46]>
    RBPARAM46 TEXTEQU <[SPL+47]>
    RBPARAM47 TEXTEQU <[SPL+48]>
    RBPARAM48 TEXTEQU <[SPL+49]>
    RBPARAM49 TEXTEQU <[SPL+50]>
    RBPARAM50 TEXTEQU <[SPL+51]>
    RBPARAM51 TEXTEQU <[SPL+52]>
    RBPARAM52 TEXTEQU <[SPL+53]>
    RBPARAM53 TEXTEQU <[SPL+54]>
    RBPARAM54 TEXTEQU <[SPL+55]>
    RBPARAM55 TEXTEQU <[SPL+56]>
    RBPARAM56 TEXTEQU <[SPL+57]>
    RBPARAM57 TEXTEQU <[SPL+58]>
    RBPARAM58 TEXTEQU <[SPL+59]>
    RBPARAM59 TEXTEQU <[SPL+60]>
    RBPARAM60 TEXTEQU <[SPL+61]>
    RBPARAM61 TEXTEQU <[SPL+62]>
    RBPARAM62 TEXTEQU <[SPL+63]>
    RBPARAM63 TEXTEQU <[SPL+64]>

   ;/ Undefined call cdecl*/
   ;/ Sysvcall Intel386*/
   ;/ 32bits*/
    URRET TEXTEQU <EAX>
    URRETURN TEXTEQU <EAX>
    URSIDX TEXTEQU <ESI>
    URDIDX TEXTEQU <EDI>
    URBPTR TEXTEQU <EBP>
    URSPTR TEXTEQU <ESP>
    URBASE TEXTEQU <EBX>
    URPARAM0 TEXTEQU <[ESP+4]>
    URPARAM1 TEXTEQU <[ESP+8]>
    URPARAM2 TEXTEQU <[ESP+12]>
    URPARAM3 TEXTEQU <[ESP+16]>
    URPARAM4 TEXTEQU <[ESP+20]>
    URPARAM5 TEXTEQU <[ESP+24]>
    URPARAM6 TEXTEQU <[ESP+28]>
    URPARAM7 TEXTEQU <[ESP+32]>
    URPARAM8 TEXTEQU <[ESP+36]>
    URPARAM9 TEXTEQU <[ESP+40]>
    URPARAM10 TEXTEQU <[ESP+44]>
    URPARAM11 TEXTEQU <[ESP+48]>
    URPARAM12 TEXTEQU <[ESP+52]>
    URPARAM13 TEXTEQU <[ESP+56]>
    URPARAM14 TEXTEQU <[ESP+60]>
    URPARAM15 TEXTEQU <[ESP+64]>
    URPARAM16 TEXTEQU <[ESP+68]>
    URPARAM17 TEXTEQU <[ESP+72]>
    URPARAM18 TEXTEQU <[ESP+76]>
    URPARAM19 TEXTEQU <[ESP+80]>
    URPARAM20 TEXTEQU <[ESP+84]>
    URPARAM21 TEXTEQU <[ESP+88]>
    URPARAM22 TEXTEQU <[ESP+92]>
    URPARAM23 TEXTEQU <[ESP+96]>
    URPARAM24 TEXTEQU <[ESP+100]>
    URPARAM25 TEXTEQU <[ESP+104]>
    URPARAM26 TEXTEQU <[ESP+108]>
    URPARAM27 TEXTEQU <[ESP+112]>
    URPARAM28 TEXTEQU <[ESP+116]>
    URPARAM29 TEXTEQU <[ESP+120]>
    URPARAM30 TEXTEQU <[ESP+124]>
    URPARAM31 TEXTEQU <[ESP+128]>
    URPARAM32 TEXTEQU <[ESP+132]>
    URPARAM33 TEXTEQU <[ESP+136]>
    URPARAM34 TEXTEQU <[ESP+140]>
    URPARAM35 TEXTEQU <[ESP+144]>
    URPARAM36 TEXTEQU <[ESP+148]>
    URPARAM37 TEXTEQU <[ESP+152]>
    URPARAM38 TEXTEQU <[ESP+156]>
    URPARAM39 TEXTEQU <[ESP+160]>
    URPARAM40 TEXTEQU <[ESP+164]>
    URPARAM41 TEXTEQU <[ESP+168]>
    URPARAM42 TEXTEQU <[ESP+172]>
    URPARAM43 TEXTEQU <[ESP+176]>
    URPARAM44 TEXTEQU <[ESP+180]>
    URPARAM45 TEXTEQU <[ESP+184]>
    URPARAM46 TEXTEQU <[ESP+188]>
    URPARAM47 TEXTEQU <[ESP+192]>
    URPARAM48 TEXTEQU <[ESP+196]>
    URPARAM49 TEXTEQU <[ESP+200]>
    URPARAM50 TEXTEQU <[ESP+204]>
    URPARAM51 TEXTEQU <[ESP+208]>
    URPARAM52 TEXTEQU <[ESP+212]>
    URPARAM53 TEXTEQU <[ESP+216]>
    URPARAM54 TEXTEQU <[ESP+220]>
    URPARAM55 TEXTEQU <[ESP+224]>
    URPARAM56 TEXTEQU <[ESP+228]>
    URPARAM57 TEXTEQU <[ESP+232]>
    URPARAM58 TEXTEQU <[ESP+236]>
    URPARAM59 TEXTEQU <[ESP+240]>
    URPARAM60 TEXTEQU <[ESP+244]>
    URPARAM61 TEXTEQU <[ESP+248]>
    URPARAM62 TEXTEQU <[ESP+252]>
    URPARAM63 TEXTEQU <[ESP+256]>
   ;/ 32bits*/
    UDRET TEXTEQU <EAX>
    UDRETURN TEXTEQU <EAX>
    UDSIDX TEXTEQU <ESI>
    UDDIDX TEXTEQU <EDI>
    UDBPTR TEXTEQU <EBP>
    UDSPTR TEXTEQU <ESP>
    UDBASE TEXTEQU <EBX>
    UDPARAM0 TEXTEQU <[ESP+4]>
    UDPARAM1 TEXTEQU <[ESP+8]>
    UDPARAM2 TEXTEQU <[ESP+12]>
    UDPARAM3 TEXTEQU <[ESP+16]>
    UDPARAM4 TEXTEQU <[ESP+20]>
    UDPARAM5 TEXTEQU <[ESP+24]>
    UDPARAM6 TEXTEQU <[ESP+28]>
    UDPARAM7 TEXTEQU <[ESP+32]>
    UDPARAM8 TEXTEQU <[ESP+36]>
    UDPARAM9 TEXTEQU <[ESP+40]>
    UDPARAM10 TEXTEQU <[ESP+44]>
    UDPARAM11 TEXTEQU <[ESP+48]>
    UDPARAM12 TEXTEQU <[ESP+52]>
    UDPARAM13 TEXTEQU <[ESP+56]>
    UDPARAM14 TEXTEQU <[ESP+60]>
    UDPARAM15 TEXTEQU <[ESP+64]>
    UDPARAM16 TEXTEQU <[ESP+68]>
    UDPARAM17 TEXTEQU <[ESP+72]>
    UDPARAM18 TEXTEQU <[ESP+76]>
    UDPARAM19 TEXTEQU <[ESP+80]>
    UDPARAM20 TEXTEQU <[ESP+84]>
    UDPARAM21 TEXTEQU <[ESP+88]>
    UDPARAM22 TEXTEQU <[ESP+92]>
    UDPARAM23 TEXTEQU <[ESP+96]>
    UDPARAM24 TEXTEQU <[ESP+100]>
    UDPARAM25 TEXTEQU <[ESP+104]>
    UDPARAM26 TEXTEQU <[ESP+108]>
    UDPARAM27 TEXTEQU <[ESP+112]>
    UDPARAM28 TEXTEQU <[ESP+116]>
    UDPARAM29 TEXTEQU <[ESP+120]>
    UDPARAM30 TEXTEQU <[ESP+124]>
    UDPARAM31 TEXTEQU <[ESP+128]>
    UDPARAM32 TEXTEQU <[ESP+132]>
    UDPARAM33 TEXTEQU <[ESP+136]>
    UDPARAM34 TEXTEQU <[ESP+140]>
    UDPARAM35 TEXTEQU <[ESP+144]>
    UDPARAM36 TEXTEQU <[ESP+148]>
    UDPARAM37 TEXTEQU <[ESP+152]>
    UDPARAM38 TEXTEQU <[ESP+156]>
    UDPARAM39 TEXTEQU <[ESP+160]>
    UDPARAM40 TEXTEQU <[ESP+164]>
    UDPARAM41 TEXTEQU <[ESP+168]>
    UDPARAM42 TEXTEQU <[ESP+172]>
    UDPARAM43 TEXTEQU <[ESP+176]>
    UDPARAM44 TEXTEQU <[ESP+180]>
    UDPARAM45 TEXTEQU <[ESP+184]>
    UDPARAM46 TEXTEQU <[ESP+188]>
    UDPARAM47 TEXTEQU <[ESP+192]>
    UDPARAM48 TEXTEQU <[ESP+196]>
    UDPARAM49 TEXTEQU <[ESP+200]>
    UDPARAM50 TEXTEQU <[ESP+204]>
    UDPARAM51 TEXTEQU <[ESP+208]>
    UDPARAM52 TEXTEQU <[ESP+212]>
    UDPARAM53 TEXTEQU <[ESP+216]>
    UDPARAM54 TEXTEQU <[ESP+220]>
    UDPARAM55 TEXTEQU <[ESP+224]>
    UDPARAM56 TEXTEQU <[ESP+228]>
    UDPARAM57 TEXTEQU <[ESP+232]>
    UDPARAM58 TEXTEQU <[ESP+236]>
    UDPARAM59 TEXTEQU <[ESP+240]>
    UDPARAM60 TEXTEQU <[ESP+244]>
    UDPARAM61 TEXTEQU <[ESP+248]>
    UDPARAM62 TEXTEQU <[ESP+252]>
    UDPARAM63 TEXTEQU <[ESP+256]>
   ;/ 16bits*/
    UWRET TEXTEQU <AX>
    UWRETURN TEXTEQU <AX>
    UWSIDX TEXTEQU <SI>
    UWDIDX TEXTEQU <DI>
    UWBPTR TEXTEQU <BP>
    UWSPTR TEXTEQU <SP>
    UWBASE TEXTEQU <BX>
    UWPARAM0 TEXTEQU <[SP+2]>
    UWPARAM1 TEXTEQU <[SP+4]>
    UWPARAM2 TEXTEQU <[SP+6]>
    UWPARAM3 TEXTEQU <[SP+8]>
    UWPARAM4 TEXTEQU <[SP+10]>
    UWPARAM5 TEXTEQU <[SP+12]>
    UWPARAM6 TEXTEQU <[SP+14]>
    UWPARAM7 TEXTEQU <[SP+16]>
    UWPARAM8 TEXTEQU <[SP+18]>
    UWPARAM9 TEXTEQU <[SP+20]>
    UWPARAM10 TEXTEQU <[SP+22]>
    UWPARAM11 TEXTEQU <[SP+24]>
    UWPARAM12 TEXTEQU <[SP+26]>
    UWPARAM13 TEXTEQU <[SP+28]>
    UWPARAM14 TEXTEQU <[SP+30]>
    UWPARAM15 TEXTEQU <[SP+32]>
    UWPARAM16 TEXTEQU <[SP+34]>
    UWPARAM17 TEXTEQU <[SP+36]>
    UWPARAM18 TEXTEQU <[SP+38]>
    UWPARAM19 TEXTEQU <[SP+40]>
    UWPARAM20 TEXTEQU <[SP+42]>
    UWPARAM21 TEXTEQU <[SP+44]>
    UWPARAM22 TEXTEQU <[SP+46]>
    UWPARAM23 TEXTEQU <[SP+48]>
    UWPARAM24 TEXTEQU <[SP+50]>
    UWPARAM25 TEXTEQU <[SP+52]>
    UWPARAM26 TEXTEQU <[SP+54]>
    UWPARAM27 TEXTEQU <[SP+56]>
    UWPARAM28 TEXTEQU <[SP+58]>
    UWPARAM29 TEXTEQU <[SP+60]>
    UWPARAM30 TEXTEQU <[SP+62]>
    UWPARAM31 TEXTEQU <[SP+64]>
    UWPARAM32 TEXTEQU <[SP+66]>
    UWPARAM33 TEXTEQU <[SP+68]>
    UWPARAM34 TEXTEQU <[SP+70]>
    UWPARAM35 TEXTEQU <[SP+72]>
    UWPARAM36 TEXTEQU <[SP+74]>
    UWPARAM37 TEXTEQU <[SP+76]>
    UWPARAM38 TEXTEQU <[SP+78]>
    UWPARAM39 TEXTEQU <[SP+80]>
    UWPARAM40 TEXTEQU <[SP+82]>
    UWPARAM41 TEXTEQU <[SP+84]>
    UWPARAM42 TEXTEQU <[SP+86]>
    UWPARAM43 TEXTEQU <[SP+88]>
    UWPARAM44 TEXTEQU <[SP+90]>
    UWPARAM45 TEXTEQU <[SP+92]>
    UWPARAM46 TEXTEQU <[SP+94]>
    UWPARAM47 TEXTEQU <[SP+96]>
    UWPARAM48 TEXTEQU <[SP+98]>
    UWPARAM49 TEXTEQU <[SP+100]>
    UWPARAM50 TEXTEQU <[SP+102]>
    UWPARAM51 TEXTEQU <[SP+104]>
    UWPARAM52 TEXTEQU <[SP+106]>
    UWPARAM53 TEXTEQU <[SP+108]>
    UWPARAM54 TEXTEQU <[SP+110]>
    UWPARAM55 TEXTEQU <[SP+112]>
    UWPARAM56 TEXTEQU <[SP+114]>
    UWPARAM57 TEXTEQU <[SP+116]>
    UWPARAM58 TEXTEQU <[SP+118]>
    UWPARAM59 TEXTEQU <[SP+120]>
    UWPARAM60 TEXTEQU <[SP+122]>
    UWPARAM61 TEXTEQU <[SP+124]>
    UWPARAM62 TEXTEQU <[SP+126]>
    UWPARAM63 TEXTEQU <[SP+128]>
   ;/ 8bits*/
    UBRET TEXTEQU <AL>
    UBRETURN TEXTEQU <AL>
    UBSIDX TEXTEQU <SIL>
    UBDIDX TEXTEQU <DIL>
    UBBPTR TEXTEQU <BPL>
    UBSPTR TEXTEQU <SPL>
    UBBASE TEXTEQU <BL>
    UBPARAM0 TEXTEQU <[SPL+1]>
    UBPARAM1 TEXTEQU <[SPL+2]>
    UBPARAM2 TEXTEQU <[SPL+3]>
    UBPARAM3 TEXTEQU <[SPL+4]>
    UBPARAM4 TEXTEQU <[SPL+5]>
    UBPARAM5 TEXTEQU <[SPL+6]>
    UBPARAM6 TEXTEQU <[SPL+7]>
    UBPARAM7 TEXTEQU <[SPL+8]>
    UBPARAM8 TEXTEQU <[SPL+9]>
    UBPARAM9 TEXTEQU <[SPL+10]>
    UBPARAM10 TEXTEQU <[SPL+11]>
    UBPARAM11 TEXTEQU <[SPL+12]>
    UBPARAM12 TEXTEQU <[SPL+13]>
    UBPARAM13 TEXTEQU <[SPL+14]>
    UBPARAM14 TEXTEQU <[SPL+15]>
    UBPARAM15 TEXTEQU <[SPL+16]>
    UBPARAM16 TEXTEQU <[SPL+17]>
    UBPARAM17 TEXTEQU <[SPL+18]>
    UBPARAM18 TEXTEQU <[SPL+19]>
    UBPARAM19 TEXTEQU <[SPL+20]>
    UBPARAM20 TEXTEQU <[SPL+21]>
    UBPARAM21 TEXTEQU <[SPL+22]>
    UBPARAM22 TEXTEQU <[SPL+23]>
    UBPARAM23 TEXTEQU <[SPL+24]>
    UBPARAM24 TEXTEQU <[SPL+25]>
    UBPARAM25 TEXTEQU <[SPL+26]>
    UBPARAM26 TEXTEQU <[SPL+27]>
    UBPARAM27 TEXTEQU <[SPL+28]>
    UBPARAM28 TEXTEQU <[SPL+29]>
    UBPARAM29 TEXTEQU <[SPL+30]>
    UBPARAM30 TEXTEQU <[SPL+31]>
    UBPARAM31 TEXTEQU <[SPL+32]>
    UBPARAM32 TEXTEQU <[SPL+33]>
    UBPARAM33 TEXTEQU <[SPL+34]>
    UBPARAM34 TEXTEQU <[SPL+35]>
    UBPARAM35 TEXTEQU <[SPL+36]>
    UBPARAM36 TEXTEQU <[SPL+37]>
    UBPARAM37 TEXTEQU <[SPL+38]>
    UBPARAM38 TEXTEQU <[SPL+39]>
    UBPARAM39 TEXTEQU <[SPL+40]>
    UBPARAM40 TEXTEQU <[SPL+41]>
    UBPARAM41 TEXTEQU <[SPL+42]>
    UBPARAM42 TEXTEQU <[SPL+43]>
    UBPARAM43 TEXTEQU <[SPL+44]>
    UBPARAM44 TEXTEQU <[SPL+45]>
    UBPARAM45 TEXTEQU <[SPL+46]>
    UBPARAM46 TEXTEQU <[SPL+47]>
    UBPARAM47 TEXTEQU <[SPL+48]>
    UBPARAM48 TEXTEQU <[SPL+49]>
    UBPARAM49 TEXTEQU <[SPL+50]>
    UBPARAM50 TEXTEQU <[SPL+51]>
    UBPARAM51 TEXTEQU <[SPL+52]>
    UBPARAM52 TEXTEQU <[SPL+53]>
    UBPARAM53 TEXTEQU <[SPL+54]>
    UBPARAM54 TEXTEQU <[SPL+55]>
    UBPARAM55 TEXTEQU <[SPL+56]>
    UBPARAM56 TEXTEQU <[SPL+57]>
    UBPARAM57 TEXTEQU <[SPL+58]>
    UBPARAM58 TEXTEQU <[SPL+59]>
    UBPARAM59 TEXTEQU <[SPL+60]>
    UBPARAM60 TEXTEQU <[SPL+61]>
    UBPARAM61 TEXTEQU <[SPL+62]>
    UBPARAM62 TEXTEQU <[SPL+63]>
    UBPARAM63 TEXTEQU <[SPL+64]>
    ENDIF ;/*__UNIX32__*/
    
    IFDEF UNDEFINED_PLATFORM
    .ERR <"No platform defined for parameters">
    ENDIF ;/*UNDEFINED_PLATFORM
    
    IFDEF CASEMAPNONE
   ;/* norm reg bits*/
    rret TEXTEQU <RRET>
    rreturn TEXTEQU <RRETURN>
    rsidx TEXTEQU <RSIDX>
    rdidx TEXTEQU <RDIDX>
    rbptr TEXTEQU <RBPTR>
    rsptr TEXTEQU <RSPTR>
    rbase TEXTEQU <RBASE>
    rparam0 TEXTEQU <RPARAM0>
    rparam1 TEXTEQU <RPARAM1>
    rparam2 TEXTEQU <RPARAM2>
    rparam3 TEXTEQU <RPARAM3>
    rparam4 TEXTEQU <RPARAM4>
    rparam5 TEXTEQU <RPARAM5>
    rparam6 TEXTEQU <RPARAM6>
    rparam7 TEXTEQU <RPARAM7>
    rparam8 TEXTEQU <RPARAM8>
    rparam9 TEXTEQU <RPARAM9>
    rparam10 TEXTEQU <RPARAM10>
    rparam11 TEXTEQU <RPARAM11>
    rparam12 TEXTEQU <RPARAM12>
    rparam13 TEXTEQU <RPARAM13>
    rparam14 TEXTEQU <RPARAM14>
    rparam15 TEXTEQU <RPARAM15>
    rparam16 TEXTEQU <RPARAM16>
    rparam17 TEXTEQU <RPARAM17>
    rparam18 TEXTEQU <RPARAM18>
    rparam19 TEXTEQU <RPARAM19>
    rparam20 TEXTEQU <RPARAM20>
    rparam21 TEXTEQU <RPARAM21>
    rparam22 TEXTEQU <RPARAM22>
    rparam23 TEXTEQU <RPARAM23>
    rparam24 TEXTEQU <RPARAM24>
    rparam25 TEXTEQU <RPARAM25>
    rparam26 TEXTEQU <RPARAM26>
    rparam27 TEXTEQU <RPARAM27>
    rparam28 TEXTEQU <RPARAM28>
    rparam29 TEXTEQU <RPARAM29>
    rparam30 TEXTEQU <RPARAM30>
    rparam31 TEXTEQU <RPARAM31>
    rparam32 TEXTEQU <RPARAM32>
    rparam33 TEXTEQU <RPARAM33>
    rparam34 TEXTEQU <RPARAM34>
    rparam35 TEXTEQU <RPARAM35>
    rparam36 TEXTEQU <RPARAM36>
    rparam37 TEXTEQU <RPARAM37>
    rparam38 TEXTEQU <RPARAM38>
    rparam39 TEXTEQU <RPARAM39>
    rparam40 TEXTEQU <RPARAM40>
    rparam41 TEXTEQU <RPARAM41>
    rparam42 TEXTEQU <RPARAM42>
    rparam43 TEXTEQU <RPARAM43>
    rparam44 TEXTEQU <RPARAM44>
    rparam45 TEXTEQU <RPARAM45>
    rparam46 TEXTEQU <RPARAM46>
    rparam47 TEXTEQU <RPARAM47>
    rparam48 TEXTEQU <RPARAM48>
    rparam49 TEXTEQU <RPARAM49>
    rparam50 TEXTEQU <RPARAM50>
    rparam51 TEXTEQU <RPARAM51>
    rparam52 TEXTEQU <RPARAM52>
    rparam53 TEXTEQU <RPARAM53>
    rparam54 TEXTEQU <RPARAM54>
    rparam55 TEXTEQU <RPARAM55>
    rparam56 TEXTEQU <RPARAM56>
    rparam57 TEXTEQU <RPARAM57>
    rparam58 TEXTEQU <RPARAM58>
    rparam59 TEXTEQU <RPARAM59>
    rparam60 TEXTEQU <RPARAM60>
    rparam61 TEXTEQU <RPARAM61>
    rparam62 TEXTEQU <RPARAM62>
    rparam63 TEXTEQU <RPARAM63>
   ;/* 32bits*/
    dret TEXTEQU <DRET>
    dreturn TEXTEQU <DRETURN>
    dsidx TEXTEQU <DSIDX>
    ddidx TEXTEQU <DDIDX>
    dbptr TEXTEQU <DBPTR>
    dsptr TEXTEQU <DSPTR>
    dbase TEXTEQU <DBASE>
    dparam0 TEXTEQU <DPARAM0>
    dparam1 TEXTEQU <DPARAM1>
    dparam2 TEXTEQU <DPARAM2>
    dparam3 TEXTEQU <DPARAM3>
    dparam4 TEXTEQU <DPARAM4>
    dparam5 TEXTEQU <DPARAM5>
    dparam6 TEXTEQU <DPARAM6>
    dparam7 TEXTEQU <DPARAM7>
    dparam8 TEXTEQU <DPARAM8>
    dparam9 TEXTEQU <DPARAM9>
    dparam10 TEXTEQU <DPARAM10>
    dparam11 TEXTEQU <DPARAM11>
    dparam12 TEXTEQU <DPARAM12>
    dparam13 TEXTEQU <DPARAM13>
    dparam14 TEXTEQU <DPARAM14>
    dparam15 TEXTEQU <DPARAM15>
    dparam16 TEXTEQU <DPARAM16>
    dparam17 TEXTEQU <DPARAM17>
    dparam18 TEXTEQU <DPARAM18>
    dparam19 TEXTEQU <DPARAM19>
    dparam20 TEXTEQU <DPARAM20>
    dparam21 TEXTEQU <DPARAM21>
    dparam22 TEXTEQU <DPARAM22>
    dparam23 TEXTEQU <DPARAM23>
    dparam24 TEXTEQU <DPARAM24>
    dparam25 TEXTEQU <DPARAM25>
    dparam26 TEXTEQU <DPARAM26>
    dparam27 TEXTEQU <DPARAM27>
    dparam28 TEXTEQU <DPARAM28>
    dparam29 TEXTEQU <DPARAM29>
    dparam30 TEXTEQU <DPARAM30>
    dparam31 TEXTEQU <DPARAM31>
    dparam32 TEXTEQU <DPARAM32>
    dparam33 TEXTEQU <DPARAM33>
    dparam34 TEXTEQU <DPARAM34>
    dparam35 TEXTEQU <DPARAM35>
    dparam36 TEXTEQU <DPARAM36>
    dparam37 TEXTEQU <DPARAM37>
    dparam38 TEXTEQU <DPARAM38>
    dparam39 TEXTEQU <DPARAM39>
    dparam40 TEXTEQU <DPARAM40>
    dparam41 TEXTEQU <DPARAM41>
    dparam42 TEXTEQU <DPARAM42>
    dparam43 TEXTEQU <DPARAM43>
    dparam44 TEXTEQU <DPARAM44>
    dparam45 TEXTEQU <DPARAM45>
    dparam46 TEXTEQU <DPARAM46>
    dparam47 TEXTEQU <DPARAM47>
    dparam48 TEXTEQU <DPARAM48>
    dparam49 TEXTEQU <DPARAM49>
    dparam50 TEXTEQU <DPARAM50>
    dparam51 TEXTEQU <DPARAM51>
    dparam52 TEXTEQU <DPARAM52>
    dparam53 TEXTEQU <DPARAM53>
    dparam54 TEXTEQU <DPARAM54>
    dparam55 TEXTEQU <DPARAM55>
    dparam56 TEXTEQU <DPARAM56>
    dparam57 TEXTEQU <DPARAM57>
    dparam58 TEXTEQU <DPARAM58>
    dparam59 TEXTEQU <DPARAM59>
    dparam60 TEXTEQU <DPARAM60>
    dparam61 TEXTEQU <DPARAM61>
    dparam62 TEXTEQU <DPARAM62>
    dparam63 TEXTEQU <DPARAM63>
   ;/* 16bits*/
    wret TEXTEQU <WRET>
    wreturn TEXTEQU <WRETURN>
    wsidx TEXTEQU <WSIDX>
    wdidx TEXTEQU <WDIDX>
    wbptr TEXTEQU <WBPTR>
    wsptr TEXTEQU <WSPTR>
    wbase TEXTEQU <WBASE>
    wparam0 TEXTEQU <WPARAM0>
    wparam1 TEXTEQU <WPARAM1>
    wparam2 TEXTEQU <WPARAM2>
    wparam3 TEXTEQU <WPARAM3>
    wparam4 TEXTEQU <WPARAM4>
    wparam5 TEXTEQU <WPARAM5>
    wparam6 TEXTEQU <WPARAM6>
    wparam7 TEXTEQU <WPARAM7>
    wparam8 TEXTEQU <WPARAM8>
    wparam9 TEXTEQU <WPARAM9>
    wparam10 TEXTEQU <WPARAM10>
    wparam11 TEXTEQU <WPARAM11>
    wparam12 TEXTEQU <WPARAM12>
    wparam13 TEXTEQU <WPARAM13>
    wparam14 TEXTEQU <WPARAM14>
    wparam15 TEXTEQU <WPARAM15>
    wparam16 TEXTEQU <WPARAM16>
    wparam17 TEXTEQU <WPARAM17>
    wparam18 TEXTEQU <WPARAM18>
    wparam19 TEXTEQU <WPARAM19>
    wparam20 TEXTEQU <WPARAM20>
    wparam21 TEXTEQU <WPARAM21>
    wparam22 TEXTEQU <WPARAM22>
    wparam23 TEXTEQU <WPARAM23>
    wparam24 TEXTEQU <WPARAM24>
    wparam25 TEXTEQU <WPARAM25>
    wparam26 TEXTEQU <WPARAM26>
    wparam27 TEXTEQU <WPARAM27>
    wparam28 TEXTEQU <WPARAM28>
    wparam29 TEXTEQU <WPARAM29>
    wparam30 TEXTEQU <WPARAM30>
    wparam31 TEXTEQU <WPARAM31>
    wparam32 TEXTEQU <WPARAM32>
    wparam33 TEXTEQU <WPARAM33>
    wparam34 TEXTEQU <WPARAM34>
    wparam35 TEXTEQU <WPARAM35>
    wparam36 TEXTEQU <WPARAM36>
    wparam37 TEXTEQU <WPARAM37>
    wparam38 TEXTEQU <WPARAM38>
    wparam39 TEXTEQU <WPARAM39>
    wparam40 TEXTEQU <WPARAM40>
    wparam41 TEXTEQU <WPARAM41>
    wparam42 TEXTEQU <WPARAM42>
    wparam43 TEXTEQU <WPARAM43>
    wparam44 TEXTEQU <WPARAM44>
    wparam45 TEXTEQU <WPARAM45>
    wparam46 TEXTEQU <WPARAM46>
    wparam47 TEXTEQU <WPARAM47>
    wparam48 TEXTEQU <WPARAM48>
    wparam49 TEXTEQU <WPARAM49>
    wparam50 TEXTEQU <WPARAM50>
    wparam51 TEXTEQU <WPARAM51>
    wparam52 TEXTEQU <WPARAM52>
    wparam53 TEXTEQU <WPARAM53>
    wparam54 TEXTEQU <WPARAM54>
    wparam55 TEXTEQU <WPARAM55>
    wparam56 TEXTEQU <WPARAM56>
    wparam57 TEXTEQU <WPARAM57>
    wparam58 TEXTEQU <WPARAM58>
    wparam59 TEXTEQU <WPARAM59>
    wparam60 TEXTEQU <WPARAM60>
    wparam61 TEXTEQU <WPARAM61>
    wparam62 TEXTEQU <WPARAM62>
    wparam63 TEXTEQU <WPARAM63>
   ;/* 8bits*/
    bret TEXTEQU <BRET>
    breturn TEXTEQU <BRETURN>
    bsidx TEXTEQU <BSIDX>
    bdidx TEXTEQU <BDIDX>
    bbptr TEXTEQU <BBPTR>
    bsptr TEXTEQU <BSPTR>
    bbase TEXTEQU <BBASE>
    bparam0 TEXTEQU <BPARAM0>
    bparam1 TEXTEQU <BPARAM1>
    bparam2 TEXTEQU <BPARAM2>
    bparam3 TEXTEQU <BPARAM3>
    bparam4 TEXTEQU <BPARAM4>
    bparam5 TEXTEQU <BPARAM5>
    bparam6 TEXTEQU <BPARAM6>
    bparam7 TEXTEQU <BPARAM7>
    bparam8 TEXTEQU <BPARAM8>
    bparam9 TEXTEQU <BPARAM9>
    bparam10 TEXTEQU <BPARAM10>
    bparam11 TEXTEQU <BPARAM11>
    bparam12 TEXTEQU <BPARAM12>
    bparam13 TEXTEQU <BPARAM13>
    bparam14 TEXTEQU <BPARAM14>
    bparam15 TEXTEQU <BPARAM15>
    bparam16 TEXTEQU <BPARAM16>
    bparam17 TEXTEQU <BPARAM17>
    bparam18 TEXTEQU <BPARAM18>
    bparam19 TEXTEQU <BPARAM19>
    bparam20 TEXTEQU <BPARAM20>
    bparam21 TEXTEQU <BPARAM21>
    bparam22 TEXTEQU <BPARAM22>
    bparam23 TEXTEQU <BPARAM23>
    bparam24 TEXTEQU <BPARAM24>
    bparam25 TEXTEQU <BPARAM25>
    bparam26 TEXTEQU <BPARAM26>
    bparam27 TEXTEQU <BPARAM27>
    bparam28 TEXTEQU <BPARAM28>
    bparam29 TEXTEQU <BPARAM29>
    bparam30 TEXTEQU <BPARAM30>
    bparam31 TEXTEQU <BPARAM31>
    bparam32 TEXTEQU <BPARAM32>
    bparam33 TEXTEQU <BPARAM33>
    bparam34 TEXTEQU <BPARAM34>
    bparam35 TEXTEQU <BPARAM35>
    bparam36 TEXTEQU <BPARAM36>
    bparam37 TEXTEQU <BPARAM37>
    bparam38 TEXTEQU <BPARAM38>
    bparam39 TEXTEQU <BPARAM39>
    bparam40 TEXTEQU <BPARAM40>
    bparam41 TEXTEQU <BPARAM41>
    bparam42 TEXTEQU <BPARAM42>
    bparam43 TEXTEQU <BPARAM43>
    bparam44 TEXTEQU <BPARAM44>
    bparam45 TEXTEQU <BPARAM45>
    bparam46 TEXTEQU <BPARAM46>
    bparam47 TEXTEQU <BPARAM47>
    bparam48 TEXTEQU <BPARAM48>
    bparam49 TEXTEQU <BPARAM49>
    bparam50 TEXTEQU <BPARAM50>
    bparam51 TEXTEQU <BPARAM51>
    bparam52 TEXTEQU <BPARAM52>
    bparam53 TEXTEQU <BPARAM53>
    bparam54 TEXTEQU <BPARAM54>
    bparam55 TEXTEQU <BPARAM55>
    bparam56 TEXTEQU <BPARAM56>
    bparam57 TEXTEQU <BPARAM57>
    bparam58 TEXTEQU <BPARAM58>
    bparam59 TEXTEQU <BPARAM59>
    bparam60 TEXTEQU <BPARAM60>
    bparam61 TEXTEQU <BPARAM61>
    bparam62 TEXTEQU <BPARAM62>
    bparam63 TEXTEQU <BPARAM63>

   ;/* Regcall*/
   ;/* norm reg bits*/
    rrret TEXTEQU <RRRET>
    rrreturn TEXTEQU <RRRETURN>
    rrsidx TEXTEQU <RRSIDX>
    rrdidx TEXTEQU <RRDIDX>
    rrbptr TEXTEQU <RRBPTR>
    rrsptr TEXTEQU <RRSPTR>
    rrbase TEXTEQU <RRBASE>
    rrparam0 TEXTEQU <RRPARAM0>
    rrparam1 TEXTEQU <RRPARAM1>
    rrparam2 TEXTEQU <RRPARAM2>
    rrparam3 TEXTEQU <RRPARAM3>
    rrparam4 TEXTEQU <RRPARAM4>
    rrparam5 TEXTEQU <RRPARAM5>
    rrparam6 TEXTEQU <RRPARAM6>
    rrparam7 TEXTEQU <RRPARAM7>
    rrparam8 TEXTEQU <RRPARAM8>
    rrparam9 TEXTEQU <RRPARAM9>
    rrparam10 TEXTEQU <RRPARAM10>
    rrparam11 TEXTEQU <RRPARAM11>
    rrparam12 TEXTEQU <RRPARAM12>
    rrparam13 TEXTEQU <RRPARAM13>
    rrparam14 TEXTEQU <RRPARAM14>
    rrparam15 TEXTEQU <RRPARAM15>
    rrparam16 TEXTEQU <RRPARAM16>
    rrparam17 TEXTEQU <RRPARAM17>
    rrparam18 TEXTEQU <RRPARAM18>
    rrparam19 TEXTEQU <RRPARAM19>
    rrparam20 TEXTEQU <RRPARAM20>
    rrparam21 TEXTEQU <RRPARAM21>
    rrparam22 TEXTEQU <RRPARAM22>
    rrparam23 TEXTEQU <RRPARAM23>
    rrparam24 TEXTEQU <RRPARAM24>
    rrparam25 TEXTEQU <RRPARAM25>
    rrparam26 TEXTEQU <RRPARAM26>
    rrparam27 TEXTEQU <RRPARAM27>
    rrparam28 TEXTEQU <RRPARAM28>
    rrparam29 TEXTEQU <RRPARAM29>
    rrparam30 TEXTEQU <RRPARAM30>
    rrparam31 TEXTEQU <RRPARAM31>
    rrparam32 TEXTEQU <RRPARAM32>
    rrparam33 TEXTEQU <RRPARAM33>
    rrparam34 TEXTEQU <RRPARAM34>
    rrparam35 TEXTEQU <RRPARAM35>
    rrparam36 TEXTEQU <RRPARAM36>
    rrparam37 TEXTEQU <RRPARAM37>
    rrparam38 TEXTEQU <RRPARAM38>
    rrparam39 TEXTEQU <RRPARAM39>
    rrparam40 TEXTEQU <RRPARAM40>
    rrparam41 TEXTEQU <RRPARAM41>
    rrparam42 TEXTEQU <RRPARAM42>
    rrparam43 TEXTEQU <RRPARAM43>
    rrparam44 TEXTEQU <RRPARAM44>
    rrparam45 TEXTEQU <RRPARAM45>
    rrparam46 TEXTEQU <RRPARAM46>
    rrparam47 TEXTEQU <RRPARAM47>
    rrparam48 TEXTEQU <RRPARAM48>
    rrparam49 TEXTEQU <RRPARAM49>
    rrparam50 TEXTEQU <RRPARAM50>
    rrparam51 TEXTEQU <RRPARAM51>
    rrparam52 TEXTEQU <RRPARAM52>
    rrparam53 TEXTEQU <RRPARAM53>
    rrparam54 TEXTEQU <RRPARAM54>
    rrparam55 TEXTEQU <RRPARAM55>
    rrparam56 TEXTEQU <RRPARAM56>
    rrparam57 TEXTEQU <RRPARAM57>
    rrparam58 TEXTEQU <RRPARAM58>
    rrparam59 TEXTEQU <RRPARAM59>
    rrparam60 TEXTEQU <RRPARAM60>
    rrparam61 TEXTEQU <RRPARAM61>
    rrparam62 TEXTEQU <RRPARAM62>
    rrparam63 TEXTEQU <RRPARAM63>
   ;/* 32bits*/
    rdret TEXTEQU <RDRET>
    rdreturn TEXTEQU <RDRETURN>
    rdsidx TEXTEQU <RDSIDX>
    rddidx TEXTEQU <RDDIDX>
    rdbptr TEXTEQU <RDBPTR>
    rdsptr TEXTEQU <RDSPTR>
    rdbase TEXTEQU <RDBASE>
    rdparam0 TEXTEQU <RDPARAM0>
    rdparam1 TEXTEQU <RDPARAM1>
    rdparam2 TEXTEQU <RDPARAM2>
    rdparam3 TEXTEQU <RDPARAM3>
    rdparam4 TEXTEQU <RDPARAM4>
    rdparam5 TEXTEQU <RDPARAM5>
    rdparam6 TEXTEQU <RDPARAM6>
    rdparam7 TEXTEQU <RDPARAM7>
    rdparam8 TEXTEQU <RDPARAM8>
    rdparam9 TEXTEQU <RDPARAM9>
    rdparam10 TEXTEQU <RDPARAM10>
    rdparam11 TEXTEQU <RDPARAM11>
    rdparam12 TEXTEQU <RDPARAM12>
    rdparam13 TEXTEQU <RDPARAM13>
    rdparam14 TEXTEQU <RDPARAM14>
    rdparam15 TEXTEQU <RDPARAM15>
    rdparam16 TEXTEQU <RDPARAM16>
    rdparam17 TEXTEQU <RDPARAM17>
    rdparam18 TEXTEQU <RDPARAM18>
    rdparam19 TEXTEQU <RDPARAM19>
    rdparam20 TEXTEQU <RDPARAM20>
    rdparam21 TEXTEQU <RDPARAM21>
    rdparam22 TEXTEQU <RDPARAM22>
    rdparam23 TEXTEQU <RDPARAM23>
    rdparam24 TEXTEQU <RDPARAM24>
    rdparam25 TEXTEQU <RDPARAM25>
    rdparam26 TEXTEQU <RDPARAM26>
    rdparam27 TEXTEQU <RDPARAM27>
    rdparam28 TEXTEQU <RDPARAM28>
    rdparam29 TEXTEQU <RDPARAM29>
    rdparam30 TEXTEQU <RDPARAM30>
    rdparam31 TEXTEQU <RDPARAM31>
    rdparam32 TEXTEQU <RDPARAM32>
    rdparam33 TEXTEQU <RDPARAM33>
    rdparam34 TEXTEQU <RDPARAM34>
    rdparam35 TEXTEQU <RDPARAM35>
    rdparam36 TEXTEQU <RDPARAM36>
    rdparam37 TEXTEQU <RDPARAM37>
    rdparam38 TEXTEQU <RDPARAM38>
    rdparam39 TEXTEQU <RDPARAM39>
    rdparam40 TEXTEQU <RDPARAM40>
    rdparam41 TEXTEQU <RDPARAM41>
    rdparam42 TEXTEQU <RDPARAM42>
    rdparam43 TEXTEQU <RDPARAM43>
    rdparam44 TEXTEQU <RDPARAM44>
    rdparam45 TEXTEQU <RDPARAM45>
    rdparam46 TEXTEQU <RDPARAM46>
    rdparam47 TEXTEQU <RDPARAM47>
    rdparam48 TEXTEQU <RDPARAM48>
    rdparam49 TEXTEQU <RDPARAM49>
    rdparam50 TEXTEQU <RDPARAM50>
    rdparam51 TEXTEQU <RDPARAM51>
    rdparam52 TEXTEQU <RDPARAM52>
    rdparam53 TEXTEQU <RDPARAM53>
    rdparam54 TEXTEQU <RDPARAM54>
    rdparam55 TEXTEQU <RDPARAM55>
    rdparam56 TEXTEQU <RDPARAM56>
    rdparam57 TEXTEQU <RDPARAM57>
    rdparam58 TEXTEQU <RDPARAM58>
    rdparam59 TEXTEQU <RDPARAM59>
    rdparam60 TEXTEQU <RDPARAM60>
    rdparam61 TEXTEQU <RDPARAM61>
    rdparam62 TEXTEQU <RDPARAM62>
    rdparam63 TEXTEQU <RDPARAM63>
   ;/* 16bits*/
    rwret TEXTEQU <RWRET>
    rwreturn TEXTEQU <RWRETURN>
    rwsidx TEXTEQU <RWSIDX>
    rwdidx TEXTEQU <RWDIDX>
    rwbptr TEXTEQU <RWBPTR>
    rwsptr TEXTEQU <RWSPTR>
    rwbase TEXTEQU <RWBASE>
    rwparam0 TEXTEQU <RWPARAM0>
    rwparam1 TEXTEQU <RWPARAM1>
    rwparam2 TEXTEQU <RWPARAM2>
    rwparam3 TEXTEQU <RWPARAM3>
    rwparam4 TEXTEQU <RWPARAM4>
    rwparam5 TEXTEQU <RWPARAM5>
    rwparam6 TEXTEQU <RWPARAM6>
    rwparam7 TEXTEQU <RWPARAM7>
    rwparam8 TEXTEQU <RWPARAM8>
    rwparam9 TEXTEQU <RWPARAM9>
    rwparam10 TEXTEQU <RWPARAM10>
    rwparam11 TEXTEQU <RWPARAM11>
    rwparam12 TEXTEQU <RWPARAM12>
    rwparam13 TEXTEQU <RWPARAM13>
    rwparam14 TEXTEQU <RWPARAM14>
    rwparam15 TEXTEQU <RWPARAM15>
    rwparam16 TEXTEQU <RWPARAM16>
    rwparam17 TEXTEQU <RWPARAM17>
    rwparam18 TEXTEQU <RWPARAM18>
    rwparam19 TEXTEQU <RWPARAM19>
    rwparam20 TEXTEQU <RWPARAM20>
    rwparam21 TEXTEQU <RWPARAM21>
    rwparam22 TEXTEQU <RWPARAM22>
    rwparam23 TEXTEQU <RWPARAM23>
    rwparam24 TEXTEQU <RWPARAM24>
    rwparam25 TEXTEQU <RWPARAM25>
    rwparam26 TEXTEQU <RWPARAM26>
    rwparam27 TEXTEQU <RWPARAM27>
    rwparam28 TEXTEQU <RWPARAM28>
    rwparam29 TEXTEQU <RWPARAM29>
    rwparam30 TEXTEQU <RWPARAM30>
    rwparam31 TEXTEQU <RWPARAM31>
    rwparam32 TEXTEQU <RWPARAM32>
    rwparam33 TEXTEQU <RWPARAM33>
    rwparam34 TEXTEQU <RWPARAM34>
    rwparam35 TEXTEQU <RWPARAM35>
    rwparam36 TEXTEQU <RWPARAM36>
    rwparam37 TEXTEQU <RWPARAM37>
    rwparam38 TEXTEQU <RWPARAM38>
    rwparam39 TEXTEQU <RWPARAM39>
    rwparam40 TEXTEQU <RWPARAM40>
    rwparam41 TEXTEQU <RWPARAM41>
    rwparam42 TEXTEQU <RWPARAM42>
    rwparam43 TEXTEQU <RWPARAM43>
    rwparam44 TEXTEQU <RWPARAM44>
    rwparam45 TEXTEQU <RWPARAM45>
    rwparam46 TEXTEQU <RWPARAM46>
    rwparam47 TEXTEQU <RWPARAM47>
    rwparam48 TEXTEQU <RWPARAM48>
    rwparam49 TEXTEQU <RWPARAM49>
    rwparam50 TEXTEQU <RWPARAM50>
    rwparam51 TEXTEQU <RWPARAM51>
    rwparam52 TEXTEQU <RWPARAM52>
    rwparam53 TEXTEQU <RWPARAM53>
    rwparam54 TEXTEQU <RWPARAM54>
    rwparam55 TEXTEQU <RWPARAM55>
    rwparam56 TEXTEQU <RWPARAM56>
    rwparam57 TEXTEQU <RWPARAM57>
    rwparam58 TEXTEQU <RWPARAM58>
    rwparam59 TEXTEQU <RWPARAM59>
    rwparam60 TEXTEQU <RWPARAM60>
    rwparam61 TEXTEQU <RWPARAM61>
    rwparam62 TEXTEQU <RWPARAM62>
    rwparam63 TEXTEQU <RWPARAM63>
   ;/* 8bits*/
    rbret TEXTEQU <RBRET>
    rbreturn TEXTEQU <RBRETURN>
    rbsidx TEXTEQU <RBSIDX>
    rbdidx TEXTEQU <RBDIDX>
    rbbptr TEXTEQU <RBBPTR>
    rbsptr TEXTEQU <RBSPTR>
    rbbase TEXTEQU <RBBASE>
    rbparam0 TEXTEQU <RBPARAM0>
    rbparam1 TEXTEQU <RBPARAM1>
    rbparam2 TEXTEQU <RBPARAM2>
    rbparam3 TEXTEQU <RBPARAM3>
    rbparam4 TEXTEQU <RBPARAM4>
    rbparam5 TEXTEQU <RBPARAM5>
    rbparam6 TEXTEQU <RBPARAM6>
    rbparam7 TEXTEQU <RBPARAM7>
    rbparam8 TEXTEQU <RBPARAM8>
    rbparam9 TEXTEQU <RBPARAM9>
    rbparam10 TEXTEQU <RBPARAM10>
    rbparam11 TEXTEQU <RBPARAM11>
    rbparam12 TEXTEQU <RBPARAM12>
    rbparam13 TEXTEQU <RBPARAM13>
    rbparam14 TEXTEQU <RBPARAM14>
    rbparam15 TEXTEQU <RBPARAM15>
    rbparam16 TEXTEQU <RBPARAM16>
    rbparam17 TEXTEQU <RBPARAM17>
    rbparam18 TEXTEQU <RBPARAM18>
    rbparam19 TEXTEQU <RBPARAM19>
    rbparam20 TEXTEQU <RBPARAM20>
    rbparam21 TEXTEQU <RBPARAM21>
    rbparam22 TEXTEQU <RBPARAM22>
    rbparam23 TEXTEQU <RBPARAM23>
    rbparam24 TEXTEQU <RBPARAM24>
    rbparam25 TEXTEQU <RBPARAM25>
    rbparam26 TEXTEQU <RBPARAM26>
    rbparam27 TEXTEQU <RBPARAM27>
    rbparam28 TEXTEQU <RBPARAM28>
    rbparam29 TEXTEQU <RBPARAM29>
    rbparam30 TEXTEQU <RBPARAM30>
    rbparam31 TEXTEQU <RBPARAM31>
    rbparam32 TEXTEQU <RBPARAM32>
    rbparam33 TEXTEQU <RBPARAM33>
    rbparam34 TEXTEQU <RBPARAM34>
    rbparam35 TEXTEQU <RBPARAM35>
    rbparam36 TEXTEQU <RBPARAM36>
    rbparam37 TEXTEQU <RBPARAM37>
    rbparam38 TEXTEQU <RBPARAM38>
    rbparam39 TEXTEQU <RBPARAM39>
    rbparam40 TEXTEQU <RBPARAM40>
    rbparam41 TEXTEQU <RBPARAM41>
    rbparam42 TEXTEQU <RBPARAM42>
    rbparam43 TEXTEQU <RBPARAM43>
    rbparam44 TEXTEQU <RBPARAM44>
    rbparam45 TEXTEQU <RBPARAM45>
    rbparam46 TEXTEQU <RBPARAM46>
    rbparam47 TEXTEQU <RBPARAM47>
    rbparam48 TEXTEQU <RBPARAM48>
    rbparam49 TEXTEQU <RBPARAM49>
    rbparam50 TEXTEQU <RBPARAM50>
    rbparam51 TEXTEQU <RBPARAM51>
    rbparam52 TEXTEQU <RBPARAM52>
    rbparam53 TEXTEQU <RBPARAM53>
    rbparam54 TEXTEQU <RBPARAM54>
    rbparam55 TEXTEQU <RBPARAM55>
    rbparam56 TEXTEQU <RBPARAM56>
    rbparam57 TEXTEQU <RBPARAM57>
    rbparam58 TEXTEQU <RBPARAM58>
    rbparam59 TEXTEQU <RBPARAM59>
    rbparam60 TEXTEQU <RBPARAM60>
    rbparam61 TEXTEQU <RBPARAM61>
    rbparam62 TEXTEQU <RBPARAM62>
    rbparam63 TEXTEQU <RBPARAM63>

   ;/* Undefined call cdecl*/
   ;/ Sysvcall Intel386*/
   ;/* norm reg bits*/
    urret TEXTEQU <URRET>
    urreturn TEXTEQU <URRETURN>
    ursidx TEXTEQU <URSIDX>
    urdidx TEXTEQU <URDIDX>
    urbptr TEXTEQU <URBPTR>
    ursptr TEXTEQU <URSPTR>
    urbase TEXTEQU <URBASE>
    urparam0 TEXTEQU <URPARAM0>
    urparam1 TEXTEQU <URPARAM1>
    urparam2 TEXTEQU <URPARAM2>
    urparam3 TEXTEQU <URPARAM3>
    urparam4 TEXTEQU <URPARAM4>
    urparam5 TEXTEQU <URPARAM5>
    urparam6 TEXTEQU <URPARAM6>
    urparam7 TEXTEQU <URPARAM7>
    urparam8 TEXTEQU <URPARAM8>
    urparam9 TEXTEQU <URPARAM9>
    urparam10 TEXTEQU <URPARAM10>
    urparam11 TEXTEQU <URPARAM11>
    urparam12 TEXTEQU <URPARAM12>
    urparam13 TEXTEQU <URPARAM13>
    urparam14 TEXTEQU <URPARAM14>
    urparam15 TEXTEQU <URPARAM15>
    urparam16 TEXTEQU <URPARAM16>
    urparam17 TEXTEQU <URPARAM17>
    urparam18 TEXTEQU <URPARAM18>
    urparam19 TEXTEQU <URPARAM19>
    urparam20 TEXTEQU <URPARAM20>
    urparam21 TEXTEQU <URPARAM21>
    urparam22 TEXTEQU <URPARAM22>
    urparam23 TEXTEQU <URPARAM23>
    urparam24 TEXTEQU <URPARAM24>
    urparam25 TEXTEQU <URPARAM25>
    urparam26 TEXTEQU <URPARAM26>
    urparam27 TEXTEQU <URPARAM27>
    urparam28 TEXTEQU <URPARAM28>
    urparam29 TEXTEQU <URPARAM29>
    urparam30 TEXTEQU <URPARAM30>
    urparam31 TEXTEQU <URPARAM31>
    urparam32 TEXTEQU <URPARAM32>
    urparam33 TEXTEQU <URPARAM33>
    urparam34 TEXTEQU <URPARAM34>
    urparam35 TEXTEQU <URPARAM35>
    urparam36 TEXTEQU <URPARAM36>
    urparam37 TEXTEQU <URPARAM37>
    urparam38 TEXTEQU <URPARAM38>
    urparam39 TEXTEQU <URPARAM39>
    urparam40 TEXTEQU <URPARAM40>
    urparam41 TEXTEQU <URPARAM41>
    urparam42 TEXTEQU <URPARAM42>
    urparam43 TEXTEQU <URPARAM43>
    urparam44 TEXTEQU <URPARAM44>
    urparam45 TEXTEQU <URPARAM45>
    urparam46 TEXTEQU <URPARAM46>
    urparam47 TEXTEQU <URPARAM47>
    urparam48 TEXTEQU <URPARAM48>
    urparam49 TEXTEQU <URPARAM49>
    urparam50 TEXTEQU <URPARAM50>
    urparam51 TEXTEQU <URPARAM51>
    urparam52 TEXTEQU <URPARAM52>
    urparam53 TEXTEQU <URPARAM53>
    urparam54 TEXTEQU <URPARAM54>
    urparam55 TEXTEQU <URPARAM55>
    urparam56 TEXTEQU <URPARAM56>
    urparam57 TEXTEQU <URPARAM57>
    urparam58 TEXTEQU <URPARAM58>
    urparam59 TEXTEQU <URPARAM59>
    urparam60 TEXTEQU <URPARAM60>
    urparam61 TEXTEQU <URPARAM61>
    urparam62 TEXTEQU <URPARAM62>
    urparam63 TEXTEQU <URPARAM63>
   ;/* 32bits*/
    udret TEXTEQU <UDRET>
    udreturn TEXTEQU <UDRETURN>
    udsidx TEXTEQU <UDSIDX>
    uddidx TEXTEQU <UDDIDX>
    udbptr TEXTEQU <UDBPTR>
    udsptr TEXTEQU <UDSPTR>
    udbase TEXTEQU <UDBASE>
    udparam0 TEXTEQU <UDPARAM0>
    udparam1 TEXTEQU <UDPARAM1>
    udparam2 TEXTEQU <UDPARAM2>
    udparam3 TEXTEQU <UDPARAM3>
    udparam4 TEXTEQU <UDPARAM4>
    udparam5 TEXTEQU <UDPARAM5>
    udparam6 TEXTEQU <UDPARAM6>
    udparam7 TEXTEQU <UDPARAM7>
    udparam8 TEXTEQU <UDPARAM8>
    udparam9 TEXTEQU <UDPARAM9>
    udparam10 TEXTEQU <UDPARAM10>
    udparam11 TEXTEQU <UDPARAM11>
    udparam12 TEXTEQU <UDPARAM12>
    udparam13 TEXTEQU <UDPARAM13>
    udparam14 TEXTEQU <UDPARAM14>
    udparam15 TEXTEQU <UDPARAM15>
    udparam16 TEXTEQU <UDPARAM16>
    udparam17 TEXTEQU <UDPARAM17>
    udparam18 TEXTEQU <UDPARAM18>
    udparam19 TEXTEQU <UDPARAM19>
    udparam20 TEXTEQU <UDPARAM20>
    udparam21 TEXTEQU <UDPARAM21>
    udparam22 TEXTEQU <UDPARAM22>
    udparam23 TEXTEQU <UDPARAM23>
    udparam24 TEXTEQU <UDPARAM24>
    udparam25 TEXTEQU <UDPARAM25>
    udparam26 TEXTEQU <UDPARAM26>
    udparam27 TEXTEQU <UDPARAM27>
    udparam28 TEXTEQU <UDPARAM28>
    udparam29 TEXTEQU <UDPARAM29>
    udparam30 TEXTEQU <UDPARAM30>
    udparam31 TEXTEQU <UDPARAM31>
    udparam32 TEXTEQU <UDPARAM32>
    udparam33 TEXTEQU <UDPARAM33>
    udparam34 TEXTEQU <UDPARAM34>
    udparam35 TEXTEQU <UDPARAM35>
    udparam36 TEXTEQU <UDPARAM36>
    udparam37 TEXTEQU <UDPARAM37>
    udparam38 TEXTEQU <UDPARAM38>
    udparam39 TEXTEQU <UDPARAM39>
    udparam40 TEXTEQU <UDPARAM40>
    udparam41 TEXTEQU <UDPARAM41>
    udparam42 TEXTEQU <UDPARAM42>
    udparam43 TEXTEQU <UDPARAM43>
    udparam44 TEXTEQU <UDPARAM44>
    udparam45 TEXTEQU <UDPARAM45>
    udparam46 TEXTEQU <UDPARAM46>
    udparam47 TEXTEQU <UDPARAM47>
    udparam48 TEXTEQU <UDPARAM48>
    udparam49 TEXTEQU <UDPARAM49>
    udparam50 TEXTEQU <UDPARAM50>
    udparam51 TEXTEQU <UDPARAM51>
    udparam52 TEXTEQU <UDPARAM52>
    udparam53 TEXTEQU <UDPARAM53>
    udparam54 TEXTEQU <UDPARAM54>
    udparam55 TEXTEQU <UDPARAM55>
    udparam56 TEXTEQU <UDPARAM56>
    udparam57 TEXTEQU <UDPARAM57>
    udparam58 TEXTEQU <UDPARAM58>
    udparam59 TEXTEQU <UDPARAM59>
    udparam60 TEXTEQU <UDPARAM60>
    udparam61 TEXTEQU <UDPARAM61>
    udparam62 TEXTEQU <UDPARAM62>
    udparam63 TEXTEQU <UDPARAM63>
   ;/* 16bits*/
    uwret TEXTEQU <UWRET>
    uwreturn TEXTEQU <UWRETURN>
    uwsidx TEXTEQU <UWSIDX>
    uwdidx TEXTEQU <UWDIDX>
    uwbptr TEXTEQU <UWBPTR>
    uwsptr TEXTEQU <UWSPTR>
    uwbase TEXTEQU <UWBASE>
    uwparam0 TEXTEQU <UWPARAM0>
    uwparam1 TEXTEQU <UWPARAM1>
    uwparam2 TEXTEQU <UWPARAM2>
    uwparam3 TEXTEQU <UWPARAM3>
    uwparam4 TEXTEQU <UWPARAM4>
    uwparam5 TEXTEQU <UWPARAM5>
    uwparam6 TEXTEQU <UWPARAM6>
    uwparam7 TEXTEQU <UWPARAM7>
    uwparam8 TEXTEQU <UWPARAM8>
    uwparam9 TEXTEQU <UWPARAM9>
    uwparam10 TEXTEQU <UWPARAM10>
    uwparam11 TEXTEQU <UWPARAM11>
    uwparam12 TEXTEQU <UWPARAM12>
    uwparam13 TEXTEQU <UWPARAM13>
    uwparam14 TEXTEQU <UWPARAM14>
    uwparam15 TEXTEQU <UWPARAM15>
    uwparam16 TEXTEQU <UWPARAM16>
    uwparam17 TEXTEQU <UWPARAM17>
    uwparam18 TEXTEQU <UWPARAM18>
    uwparam19 TEXTEQU <UWPARAM19>
    uwparam20 TEXTEQU <UWPARAM20>
    uwparam21 TEXTEQU <UWPARAM21>
    uwparam22 TEXTEQU <UWPARAM22>
    uwparam23 TEXTEQU <UWPARAM23>
    uwparam24 TEXTEQU <UWPARAM24>
    uwparam25 TEXTEQU <UWPARAM25>
    uwparam26 TEXTEQU <UWPARAM26>
    uwparam27 TEXTEQU <UWPARAM27>
    uwparam28 TEXTEQU <UWPARAM28>
    uwparam29 TEXTEQU <UWPARAM29>
    uwparam30 TEXTEQU <UWPARAM30>
    uwparam31 TEXTEQU <UWPARAM31>
    uwparam32 TEXTEQU <UWPARAM32>
    uwparam33 TEXTEQU <UWPARAM33>
    uwparam34 TEXTEQU <UWPARAM34>
    uwparam35 TEXTEQU <UWPARAM35>
    uwparam36 TEXTEQU <UWPARAM36>
    uwparam37 TEXTEQU <UWPARAM37>
    uwparam38 TEXTEQU <UWPARAM38>
    uwparam39 TEXTEQU <UWPARAM39>
    uwparam40 TEXTEQU <UWPARAM40>
    uwparam41 TEXTEQU <UWPARAM41>
    uwparam42 TEXTEQU <UWPARAM42>
    uwparam43 TEXTEQU <UWPARAM43>
    uwparam44 TEXTEQU <UWPARAM44>
    uwparam45 TEXTEQU <UWPARAM45>
    uwparam46 TEXTEQU <UWPARAM46>
    uwparam47 TEXTEQU <UWPARAM47>
    uwparam48 TEXTEQU <UWPARAM48>
    uwparam49 TEXTEQU <UWPARAM49>
    uwparam50 TEXTEQU <UWPARAM50>
    uwparam51 TEXTEQU <UWPARAM51>
    uwparam52 TEXTEQU <UWPARAM52>
    uwparam53 TEXTEQU <UWPARAM53>
    uwparam54 TEXTEQU <UWPARAM54>
    uwparam55 TEXTEQU <UWPARAM55>
    uwparam56 TEXTEQU <UWPARAM56>
    uwparam57 TEXTEQU <UWPARAM57>
    uwparam58 TEXTEQU <UWPARAM58>
    uwparam59 TEXTEQU <UWPARAM59>
    uwparam60 TEXTEQU <UWPARAM60>
    uwparam61 TEXTEQU <UWPARAM61>
    uwparam62 TEXTEQU <UWPARAM62>
    uwparam63 TEXTEQU <UWPARAM63>
   ;/* 8bits*/
    ubret TEXTEQU <UBRET>
    ubreturn TEXTEQU <UBRETURN>
    ubsidx TEXTEQU <UBSIDX>
    ubdidx TEXTEQU <UBDIDX>
    ubbptr TEXTEQU <UBBPTR>
    ubsptr TEXTEQU <UBSPTR>
    ubbase TEXTEQU <UBBASE>
    ubparam0 TEXTEQU <UBPARAM0>
    ubparam1 TEXTEQU <UBPARAM1>
    ubparam2 TEXTEQU <UBPARAM2>
    ubparam3 TEXTEQU <UBPARAM3>
    ubparam4 TEXTEQU <UBPARAM4>
    ubparam5 TEXTEQU <UBPARAM5>
    ubparam6 TEXTEQU <UBPARAM6>
    ubparam7 TEXTEQU <UBPARAM7>
    ubparam8 TEXTEQU <UBPARAM8>
    ubparam9 TEXTEQU <UBPARAM9>
    ubparam10 TEXTEQU <UBPARAM10>
    ubparam11 TEXTEQU <UBPARAM11>
    ubparam12 TEXTEQU <UBPARAM12>
    ubparam13 TEXTEQU <UBPARAM13>
    ubparam14 TEXTEQU <UBPARAM14>
    ubparam15 TEXTEQU <UBPARAM15>
    ubparam16 TEXTEQU <UBPARAM16>
    ubparam17 TEXTEQU <UBPARAM17>
    ubparam18 TEXTEQU <UBPARAM18>
    ubparam19 TEXTEQU <UBPARAM19>
    ubparam20 TEXTEQU <UBPARAM20>
    ubparam21 TEXTEQU <UBPARAM21>
    ubparam22 TEXTEQU <UBPARAM22>
    ubparam23 TEXTEQU <UBPARAM23>
    ubparam24 TEXTEQU <UBPARAM24>
    ubparam25 TEXTEQU <UBPARAM25>
    ubparam26 TEXTEQU <UBPARAM26>
    ubparam27 TEXTEQU <UBPARAM27>
    ubparam28 TEXTEQU <UBPARAM28>
    ubparam29 TEXTEQU <UBPARAM29>
    ubparam30 TEXTEQU <UBPARAM30>
    ubparam31 TEXTEQU <UBPARAM31>
    ubparam32 TEXTEQU <UBPARAM32>
    ubparam33 TEXTEQU <UBPARAM33>
    ubparam34 TEXTEQU <UBPARAM34>
    ubparam35 TEXTEQU <UBPARAM35>
    ubparam36 TEXTEQU <UBPARAM36>
    ubparam37 TEXTEQU <UBPARAM37>
    ubparam38 TEXTEQU <UBPARAM38>
    ubparam39 TEXTEQU <UBPARAM39>
    ubparam40 TEXTEQU <UBPARAM40>
    ubparam41 TEXTEQU <UBPARAM41>
    ubparam42 TEXTEQU <UBPARAM42>
    ubparam43 TEXTEQU <UBPARAM43>
    ubparam44 TEXTEQU <UBPARAM44>
    ubparam45 TEXTEQU <UBPARAM45>
    ubparam46 TEXTEQU <UBPARAM46>
    ubparam47 TEXTEQU <UBPARAM47>
    ubparam48 TEXTEQU <UBPARAM48>
    ubparam49 TEXTEQU <UBPARAM49>
    ubparam50 TEXTEQU <UBPARAM50>
    ubparam51 TEXTEQU <UBPARAM51>
    ubparam52 TEXTEQU <UBPARAM52>
    ubparam53 TEXTEQU <UBPARAM53>
    ubparam54 TEXTEQU <UBPARAM54>
    ubparam55 TEXTEQU <UBPARAM55>
    ubparam56 TEXTEQU <UBPARAM56>
    ubparam57 TEXTEQU <UBPARAM57>
    ubparam58 TEXTEQU <UBPARAM58>
    ubparam59 TEXTEQU <UBPARAM59>
    ubparam60 TEXTEQU <UBPARAM60>
    ubparam61 TEXTEQU <UBPARAM61>
    ubparam62 TEXTEQU <UBPARAM62>
    ubparam63 TEXTEQU <UBPARAM63>    
    ENDIF ;CASEMAPNONE

    ENDIF ;WITHMACROLIB

    ENDIF    ;PARAMS_INC
