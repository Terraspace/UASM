
    IFNDEF GRP
    GRP MACRO num:REQ, regsize:REQ
        LOCAL cnt, arg, tcnt, targ, cargsize, cargssise, targssise, cntp
        rptxt TEXTEQU <-1>
        IF num LT 0
            .ERR <num "That don't work. Please use a decimal number has argument for argument's passing from 0 to 16.">
            EXITM <rptxt>
        ENDIF
        IF num GE 16
            .ERR <num "!!!UNIMPLEMENTED!!! Please kindle hask in masm32 dot com sub-forum UASM <http://masm32.com/board/index.php?board=51.0> for aditional parameters implementation">
            EXITM <rptxt>
        ENDIF
        IF regsize LT BYTE_SIZE
            .ERR <regsize "That don't work. No data type is know with less than BYTE_SIZE." >
            EXITM <rptxt>
        ENDIF
        IF regsize EQ 3 OR regsize EQ 5 OR regsize EQ 6 OR regsize EQ 7
            .ERR <regsize "That don't work. Unknown data type exist with this size. Probably You want to use the PRP for pointer register parameters">
            EXITM <rptxt>
        ENDIF
        IF regsize GT SIZE_T_SIZE
            .ERR <regsize "That don't work. Please use good know data bytes sizes from BYTE_SIZE to DWORD_SIZE in 32bits from BYTE_SIZE TO QWORD_SIZE in 64bits.">
            EXITM <rptxt>
        ENDIF
        targssise = SIZE _currargs_
        cnt = -1
        FOR arg, <_currargs_>
            cnt = cnt + 1
            IF cnt EQ num
                cargsize = SIZE arg
                cargssise = cargssise + SIZE arg
                IF cargsize GT REG_SIZE
                    .ERR <cargsize "You are trying to use a general register instead of a PTR OR SIMD register. Please use the PRP for pointer register parameters or SRP for SIMD register parameters">
                    EXITM
                ENDIF
                IF regsize EQ BYTE_SIZE
                    cntp = cargssise - cargsize + BYTE_SIZE
                    IFDEF __WIN64__
                        IF @LangType EQ LANG_REGCALL
                            tcnt = -1
                            FOR targ,<AL,CL,DL,DIL,SIL,R8B,R9B,R11B,R12B,R14B,R15B,[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ELSE
                            tcnt = -1
                            FOR targ,<CL,DL,R8B,R9B,[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ENDIF ;;@LangType
                    ENDIF ;;__WIN64__
                    IFDEF __UNIX64__
                        IF @LangType EQ LANG_REGCALL
                            tcnt = -1
                            FOR targ,<AL,CL,DL,DIL,SIL,R8B,R9B,R10B,R11B,R12B,R14B,R15B,[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ELSE
                            tcnt = -1
                            FOR targ,<DIL,SIL,DL,CL,R8B,R9B,[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ENDIF ;;@LangType
                    ENDIF ;;__UNIX64__
                    IFDEF __WIN32__
                        IF @LangType EQ LANG_REGCALL
                            tcnt = -1
                            FOR targ,<CL,DL,DIL,SIL,[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ELSEIF @LangType EQ LANG_FASTSCALL OR @LangType EQ LANG_VECTORCALL
                            tcnt = -1
                            FOR targ,<CL,DL,[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ELSEIF @LangType EQ LANG_THISCALL
                            tcnt = -1
                            FOR targ,<CL,[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ELSE
                            tcnt = -1
                            FOR targ,<[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ENDIF ;;@LangType
                    ENDIF ;;__WIN32__
                    IFDEF __UNIX32__
                        IF @LangType EQ LANG_REGCALL
                            tcnt = -1
                            FOR targ,<AL,CL,DL,DIL,SIL,[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ELSE
                            tcnt = -1
                            FOR targ,<[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp],[SPL+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ENDIF ;;@LangType
                    ENDIF ;;__UNIX32__
                    EXITM
                ELSEIF regsize EQ WORD_SIZE
                    cntp = cargssise - cargsize + WORD_SIZE
                    IFDEF __WIN64__
                        IF @LangType EQ LANG_REGCALL
                            tcnt = -1
                            FOR targ,<AX,CX,DX,DI,SI,R8W,R9W,R11W,R12W,R14W,R15W,[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ELSE
                            tcnt = -1
                            FOR targ,<CX,DX,R8W,R9W,[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ENDIF ;;@LangType
                    ENDIF ;;__WIN64__
                    IFDEF __UNIX64__
                        IF @LangType EQ LANG_REGCALL
                            tcnt = -1
                            FOR targ,<AX,CX,DX,DI,SI,R8W,R9W,R10W,R11W,R12W,R14W,R15W,[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ELSE
                            tcnt = -1
                            FOR targ,<DI,SI,DX,CX,R8W,R9W,[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ENDIF ;;@LangType
                    ENDIF ;;__UNIX64__
                    IFDEF __WIN32__
                        IF @LangType EQ LANG_REGCALL
                            tcnt = -1
                            FOR targ,<CX,DX,DI,SI,[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ELSEIF @LangType EQ LANG_FASTSCALL OR @LangType EQ LANG_VECTORCALL
                            tcnt = -1
                            FOR targ,<CX,DX,[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ELSEIF @LangType EQ LANG_THISCALL
                            tcnt = -1
                            FOR targ,<CX,[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ELSE
                            tcnt = -1
                            FOR targ,<[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ENDIF ;;@LangType
                    ENDIF ;;__WIN32__
                    IFDEF __UNIX32__
                        IF @LangType EQ LANG_REGCALL
                            tcnt = -1
                            FOR targ,<AX,CX,DX,DI,SI,[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ELSE
                            tcnt = -1
                            FOR targ,<[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp],[SP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ENDIF ;;@LangType
                    ENDIF ;;__UNIX32__
                    EXITM
                ELSEIF regsize EQ DWORD_SIZE
                    cntp = cargssise - cargsize + DWORD_SIZE
                    IFDEF __WIN64__
                        IF @LangType EQ LANG_REGCALL
                            tcnt = -1
                            FOR targ,<EAX,ECX,EDX,EDI,ESI,R8D,R9D,R11D,R12D,R14D,R15D,[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ELSE
                            tcnt = -1
                            FOR targ,<ECX,EDX,R8D,R9D,[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ENDIF ;;@LangType
                    ENDIF ;;__WIN64__
                    IFDEF __UNIX64__
                        IF @LangType EQ LANG_REGCALL
                            tcnt = -1
                            FOR targ,<EAX,ECX,EDX,EDI,ESI,R8D,R9D,R10D,R11D,R12D,R14D,R15D,[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ELSE
                            tcnt = -1
                            FOR targ,<EDI,ESI,EDX,ECX,R8D,R9D,[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ENDIF ;;@LangType
                    ENDIF ;;__UNIX64__
                    IFDEF __WIN32__
                        IF @LangType EQ LANG_REGCALL
                            tcnt = -1
                            FOR targ,<ECX,EDX,EDI,ESI,[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ELSEIF @LangType EQ LANG_FASTSCALL OR @LangType EQ LANG_VECTORCALL
                            tcnt = -1
                            FOR targ,<ECX,EDX,[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ELSEIF @LangType EQ LANG_THISCALL
                            tcnt = -1
                            FOR targ,<ECX,[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ELSE
                            tcnt = -1
                            FOR targ,<[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ENDIF ;;@LangType
                    ENDIF ;;__WIN32__
                    IFDEF __UNIX32__
                        IF @LangType EQ LANG_REGCALL
                            tcnt = -1
                            FOR targ,<EAX,ECX,EDX,EDI,ESI,[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ELSE
                            tcnt = -1
                            FOR targ,<[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp],[ESP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ENDIF ;;@LangType
                    ENDIF ;;__UNIX32__
                    EXITM
                ELSEIF regsize EQ QWORD_SIZE
                    cntp = cargssise - cargsize + QWORD_SIZE
                    IFDEF __WIN64__
                        IF @LangType EQ LANG_REGCALL
                            tcnt = -1
                            FOR targ,<RAX,RCX,RDX,RDI,RSI,R8,R9,R11,R12,R14,R15,[RSP+cntp],[RSP+cntp],[RSP+cntp],[RSP+cntp],[RSP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ELSE
                            tcnt = -1
                            FOR targ,<RCX,RDX,R8,R9,[RSP+cntp],[RSP+cntp],[RSP+cntp],[RSP+cntp],[RSP+cntp],[RSP+cntp],[RSP+cntp],[RSP+cntp],[RSP+cntp],[RSP+cntp],[RSP+cntp],[RSP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ENDIF ;;@LangType
                    ENDIF ;;__WIN64__
                    IFDEF __UNIX64__
                        IF @LangType EQ LANG_REGCALL
                            tcnt = -1
                            FOR targ,<RAX,RCX,RDX,RDI,RSI,R8,R9,R10,R11,R12,R14,R15,[RSP+cntp],[RSP+cntp],[RSP+cntp],[RSP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ELSE
                            tcnt = -1
                            FOR targ,<RDI,RSI,RDX,RCX,R8,R9,[RSP+cntp],[RSP+cntp],[RSP+cntp],[RSP+cntp],[RSP+cntp],[RSP+cntp],[RSP+cntp],[RSP+cntp],[RSP+cntp],[RSP+cntp]>
                                tcnt = tcnt + 1
                                IF tcnt EQ cnt
                                    rptxt TEXTEQU <targ>
                                    EXITM
                                ENDIF
                            ENDM
                        ENDIF ;;@LangType
                    ENDIF ;;__UNIX64__
                    EXITM
                ENDIF ;; regsize EQ QWORD_SIZE
                EXITM
            ENDIF ;;cnt EQ num
        ENDM
        EXITM <rptxt>
    ENDM
    ENDIF ;GRP
    