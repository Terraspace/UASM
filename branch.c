/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  parser's processing of branch instructions with immediate
*                operand (CALL, JMP, Jxx, LOOPxx, JxCXZ). Includes:
*               - "far call optimisation": a "call FAR ptr <proc>" is
*                 exchanged by a "push cs" + "call NEAR ptr <proc>".
*               - "short jump extension": a conditional jump with a
*                 destination not within the SHORT range is exchanged
*                 by "j<cond> $+3|5" and "jmp <dest>" if cpu is < 386
*                 (see OPTION LJMP | NOLJMP).
****************************************************************************/

#ifdef __GNUC__ 
#define _BITS_FLOATN_COMMON_H
#endif

#include <limits.h>
#include "globals.h"
#include "parser.h"
#include "fixup.h"
#include "expreval.h"
#include "fastpass.h"
#include "segment.h"
#include "input.h"
#include "assume.h"
#include "codegen.h"
#include "myassert.h"

#define NEEDLABEL 1 /* 1=better Masm compatibility */

#define IS_CONDJMP( inst )  ( ( inst >= T_JA ) && ( inst <= T_JZ ) )

/* opsize byte (0x66) to be generated? */
#define OPSIZE( s, x ) ( (  s != x ) ? TRUE : FALSE )

/* v2.03: OutputCodeByte no longer needed */
#define OutputCodeByte( x ) OutputByte( x )

extern ret_code segm_override( const struct expr *opndx, struct code_info *CodeInfo );
extern struct asym *SegOverride;

/* "short jump extension": extend a (conditional) jump.
 * example:
 * "jz label"
 * is converted to
 * "jnz SHORT $+x"  ( x = sizeof(next ins), may be 3|5|6|7|8 )
 * "jmp label"
 *
 * there is a problem if it's a short forward jump with a distance
 * of 7D-7F (16bit), because the additional "jmp label" will increase
 * the code size.
 */
static void jumpExtend( struct code_info *CodeInfo, int far_flag )
/****************************************************************/
{
    //uint_8 opcode;
    unsigned next_ins_size;

    if( Parse_Pass == PASS_2 )
        EmitWarn( 4, EXTENDING_JUMP );

    DebugMsg(("jumpExtend(far=%u), pass=%u, curr offset=%X, Ofssize=%u\n", far_flag, Parse_Pass + 1, GetCurrOffset(), CodeInfo->Ofssize ));
    if( far_flag ) {
        if ( CodeInfo->prefix.opsiz ) {
            /* it's 66 EA OOOO SSSS or 66 EA OOOOOOOO SSSS */
            next_ins_size = CodeInfo->Ofssize ? 6 : 8;
        } else {
            /* it's EA OOOOOOOO SSSS or EA OOOO SSSS */
            next_ins_size = CodeInfo->Ofssize ? 7 : 5;
        }
    } else {
        /* it's E9 OOOOOOOO or E9 OOOO */
        next_ins_size = CodeInfo->Ofssize ? 5 : 3;
    }

    /* it's ensured that the short jump version is first in InstrTable */
    //opcode = InstrTable[optable_idx[CodeInfo->token]].opcode;
    //OutputCodeByte( opcode ^ 1 );
    /* the negation is achieved by XOR 1 */
    OutputCodeByte( CodeInfo->pinstr->opcode ^ 1 );
    OutputCodeByte( next_ins_size );
    CodeInfo->token = T_JMP;
    CodeInfo->pinstr = &InstrTable[ IndexFromToken( T_JMP )];

    return;
}

/* "far call optimisation": a far call is done to a near label
 * optimize (call SSSS:OOOO -> PUSH CS, CALL OOOO)
 */
static void FarCallToNear( struct code_info *CodeInfo )
/*****************************************************/
{
    if( Parse_Pass == PASS_2 )
        EmitWarn( 4, CALL_FAR_TO_NEAR );

    OutputCodeByte( 0x0E ); /* 0x0E is "PUSH CS" opcode */
    CodeInfo->mem_type = MT_NEAR;

    return;
}

ret_code process_branch( struct code_info *CodeInfo, unsigned CurrOpnd, const struct expr *opndx )
/************************************************************************************************/
/*
 * called by idata_fixup(), idata_nofixup().
 * current instruction is CALL, JMP, Jxx, LOOPx, JCXZ or JECXZ
 * and operand is an immediate value.
 * determine the displacement of jmp;
 * possible return values are:
 * - NOT_ERROR,
 * - ERROR,
 */
{
    int_32              addr;
    enum fixup_types    fixup_type;
    enum fixup_options  fixup_option;
    enum sym_state      state;
    struct asym         *sym;
    enum memtype        mem_type;
    struct dsym         *symseg;
    unsigned            opidx = IndexFromToken( CodeInfo->token );

    /* v2.05: just 1 operand possible */
    if ( CurrOpnd != OPND1 ) {
        //EmitError( SYNTAX_ERROR ); /* v2.10: error msg changed */
        return( EmitError( INVALID_INSTRUCTION_OPERANDS ) );
    }
    if ( opndx->explicit && opndx->instr != T_SHORT )
        CodeInfo->mem_type = opndx->mem_type;
    /*
     * Masm checks overrides for branch instructions with immediate operand!
     * Of course, no segment prefix byte is emitted - would be pretty useless.
     * It might cause the call/jmp to become FAR, though.
     */
    if ( opndx->override != NULL ) {
        segm_override( opndx, NULL );
        DebugMsg(("process_branch(%" I32_SPEC "X): segment override %s\n", GetCurrOffset(), SegOverride ? SegOverride->name : "NULL" ));
        if ( SegOverride && opndx->sym && opndx->sym->segment ) {
            if ( SegOverride != opndx->sym->segment &&  SegOverride != ((struct dsym *)opndx->sym->segment)->e.seginfo->group ) {
                return( EmitErr( CANNOT_ACCESS_LABEL_THROUGH_SEGMENT_REGISTERS, opndx->sym ? opndx->sym->name : "" ) );
            }
            /* v2.05: switch to far jmp/call */
            if ( SegOverride != &CurrSeg->sym && SegOverride != CurrSeg->e.seginfo->group ) {
                DebugMsg(("process_branch(%" I32_SPEC "X): segment override %s caused FAR jmp/call\n", GetCurrOffset(), SegOverride->name ));
                //CodeInfo->isfar = TRUE;
                CodeInfo->mem_type = MT_FAR;
            }
        }
    }

    CodeInfo->opnd[OPND1].data32l = opndx->value;
    /* v2.06: make sure, that next bytes are cleared (for OP_I48)! */
    CodeInfo->opnd[OPND1].data32h = 0;
    sym = opndx->sym;
    if( sym == NULL ) { /* no symbolic label specified? */
        DebugMsg(("process_branch(%" I32_SPEC "X): sym=NULL, op.memtype=%Xh\n", GetCurrOffset(), opndx->mem_type ));

        /* Masm rejects: "jump dest must specify a label */
#if NEEDLABEL
        return( EmitError( JUMP_DESTINATION_MUST_SPECIFY_A_LABEL ) );
#else
        if( IS_JMPCALL( CodeInfo->token ) )
            CodeInfo->isfar = TRUE; /* ??? most likely nonsense! */

        if( CodeInfo->opnd[OPND1].data32l > USHRT_MAX )
            CodeInfo->opnd[OPND1].type = OP_I32;
        else
            CodeInfo->opnd_type[OPND1] = OP_I16;

        return( NOT_ERROR );
#endif
    }
    DebugMsg1(("process_branch(%" I32_SPEC "X, %s): opnd.explicit=%u/memtype=%X/Ofssize=%u CI.memtype=%X sym.state=%u/mem_type=%Xh/ofs=%" I32_SPEC "X/seg=%s\n",
              GetCurrOffset(), sym->name, opndx->explicit, opndx->mem_type, opndx->Ofssize, CodeInfo->mem_type,
              sym->state, sym->mem_type, sym->offset, sym->segment ? sym->segment->name : "NULL" ));

    state = sym->state;
    addr = GetCurrOffset(); /* for SYM_UNDEFINED, will force distance to SHORT */

    /* v2.02: if symbol is GLOBAL and it isn't clear yet were
     * it's located, then assume it is a forward reference (=SYM_UNDEFINED)!
     * This applies to PROTOs and EXTERNDEFs in Pass 1.
     */
    if ( ( state == SYM_EXTERNAL ) && sym->weak ) {
        DebugMsg1(("process_branch(%s): EXTERNDEF assumed forward reference (=SYM_UNDEFINED)\n", sym->name ));
        state = SYM_UNDEFINED;
    }

    /* v2.02: removed SYM_UNDEFINED. Don't check segment of such symbols! */
//    if ( state == SYM_UNDEFINED || state == SYM_INTERNAL || state == SYM_EXTERNAL ) {
    if ( state == SYM_INTERNAL || state == SYM_EXTERNAL ) {
        /* v2.04: if the symbol is internal, but wasn't met yet
         * in this pass and its offset is < $, don't use current offset
         */
        if ( state == SYM_INTERNAL &&
            sym->asmpass != ( Parse_Pass & 0xFF) &&
            sym->offset < addr )
            ;
        else
            addr = sym->offset; /* v2.02: init addr, so sym->offset isn't changed */
        symseg = GetSegm( sym );
        if( symseg == NULL || ( CurrSeg != symseg ) ) {
            /* if label has a different segment and jump/call is near or short,
             report an error */
            //if ( ModuleInfo.flatgrp_idx != 0 )
            /* v2.09: make sure there's no near jmp/call between 32- and 64-bit */
            //if ( ModuleInfo.flat_grp )
            if ( ModuleInfo.flat_grp
#if AMD64_SUPPORT
                && ( symseg == NULL || symseg->e.seginfo->Ofssize == ModuleInfo.Ofssize )
#endif
               ) {
            } else if ( symseg != NULL && CurrSeg != NULL ) {
                /* if the segments belong to the same group, it's ok */
                if ( symseg->e.seginfo->group != NULL &&
                    symseg->e.seginfo->group == CurrSeg->e.seginfo->group )
                    ;
                /* v2.05: added SegOverride condition */
                //else if ( opndx->mem_type == MT_NEAR ) {
                else if ( opndx->mem_type == MT_NEAR && SegOverride == NULL ) {
                    DebugMsg(("process_branch: error, opndx.mem_type is MT_NEAR\n" ));
                    return( EmitError( CANNOT_HAVE_IMPLICIT_FAR_JUMP_OR_CALL_TO_NEAR_LABEL ) );
                }
            }
            /* jumps to another segment are just like to another file */
            state = SYM_EXTERNAL;
        }
    } else if ( state != SYM_UNDEFINED ) {
        DebugMsg(("process_branch(%s): error, unexpected symbol state=%u\n", sym->name, sym->state ));
        return( EmitErr( JUMP_DESTINATION_MUST_SPECIFY_A_LABEL ) );
    }

    if ( state != SYM_EXTERNAL ) {
        /* v1.94: if a segment override is active,
         check if it's matching the assumed value of CS.
         If no, assume a FAR call.
         */
        if ( SegOverride != NULL && CodeInfo->mem_type == MT_EMPTY ) {
            if ( SegOverride != GetOverrideAssume( ASSUME_CS ) ) {
                CodeInfo->mem_type = MT_FAR;
            }
        }
        if(  ( CodeInfo->mem_type == MT_EMPTY ||
              CodeInfo->mem_type == MT_NEAR ) &&
           CodeInfo->isfar == FALSE ) {

            /* if the label is FAR - or there is a segment override
             * which equals assumed value of CS - and there is no type cast,
             * then do a "far call optimization".
             */
            if( CodeInfo->token == T_CALL &&
                CodeInfo->mem_type == MT_EMPTY &&
                ( sym->mem_type == MT_FAR || SegOverride ) ) {
                DebugMsg1(("process_branch: FAR call optimization applied!\n" ));
                FarCallToNear( CodeInfo ); /* switch mem_type to NEAR */
            }

            //addr = sym->offset; /* v2.02: this has been done above */
            DebugMsg(("process_branch: step1: addr=%Xh\n", addr ));
            addr -= ( GetCurrOffset() + 2 );  /* calculate the displacement */
            addr += CodeInfo->opnd[OPND1].data32l;
            /*  JCXZ, LOOPW, LOOPEW, LOOPZW, LOOPNEW, LOOPNZW,
               JECXZ, LOOPD, LOOPED, LOOPZD, LOOPNED, LOOPNZD? */
            if (( CodeInfo->Ofssize && InstrTable[opidx].byte1_info == F_16A ) ||
                ( CodeInfo->Ofssize != USE32 && InstrTable[opidx].byte1_info == F_32A ))
                addr--; /* 1 extra byte for ADRSIZ (0x67) */

			/* UASM v2.34 : When calculating the displace for a branch/call, if the bnd prefix was used we need to shift it out by a further byte */
			if (CodeInfo->prefix.ins == T_BND)
				addr--;

            /* v2.02: removed */
            //if( CodeInfo->token == T_CALL && CodeInfo->mem_type == MT_EMPTY ) {
            //    CodeInfo->mem_type = MT_NEAR;
            //}
            DebugMsg(("process_branch: CI.memtype=%Xh addr=%Xh\n", CodeInfo->mem_type, addr ));
            if( CodeInfo->mem_type != MT_NEAR && CodeInfo->token != T_CALL &&
                ( addr >= SCHAR_MIN && addr <= SCHAR_MAX ) ) {
                CodeInfo->opnd[OPND1].type = OP_I8;
            } else {
                if ( opndx->instr == T_SHORT || ( IS_XCX_BRANCH( CodeInfo->token ) ) ) {
                    /* v2.06: added */
                    if( CodeInfo->token == T_CALL ) {
                        return( EmitError( CANNOT_USE_SHORT_WITH_CALL ) );
                    }
                    /* v1.96: since Uasm's backpatch strategy is to move from
                     * "smallest" to "largest" distance, an "out of range"
                     * error can be detected at any time.
                     */
                    DebugMsg(("process_branch: jump out of range, mem_type=%Xh addr=%Xh\n", CodeInfo->mem_type, addr ));
                    /* v2.06: removed */
                    /* v2.03: added */
                    //if ( addr >= SCHAR_MIN && addr <= SCHAR_MAX ) {
                    //    return( EmitError( ONLY_SHORT_JUMP_DISTANCE_IS_ALLOWED ) );
                    //}
                    if ( addr < 0 ) {
                        addr -= SCHAR_MIN;
                        addr = 0 - addr;
                    } else
                        addr -= SCHAR_MAX;
                    return( EmitErr( CodeInfo->mem_type == MT_EMPTY ? JUMP_OUT_OF_RANGE : ONLY_SHORT_JUMP_DISTANCE_IS_ALLOWED, addr ) );
                }
                /* near destination */
                /* is there a type coercion? */
                if ( opndx->Ofssize != USE_EMPTY ) {
                    if ( opndx->Ofssize == USE16 ) {
                        CodeInfo->opnd[OPND1].type = OP_I16;
                        addr -= 1; /* 16 bit displacement */
                    } else {
                        CodeInfo->opnd[OPND1].type = OP_I32;
                        addr -= 3; /* 32 bit displacement */
                    }
                    CodeInfo->prefix.opsiz = OPSIZE( CodeInfo->Ofssize, opndx->Ofssize );
                    if ( CodeInfo->prefix.opsiz )
                        addr--;
                } else if( CodeInfo->Ofssize > USE16 ) {
                    CodeInfo->opnd[OPND1].type = OP_I32;
                    addr -= 3; /* 32 bit displacement */
                } else {
                    CodeInfo->opnd[OPND1].type = OP_I16;
                    addr -= 1; /* 16 bit displacement */
                }
                if( IS_CONDJMP( CodeInfo->token ) ) {
                    /* 1 extra byte for opcode ( 0F ) */
                    addr--;
                }
            }

            /* store the displacement */
            CodeInfo->opnd[OPND1].data32l = addr;
            DebugMsg1(("process_branch: displacement=%" I32_SPEC "X opnd_type=%" I32_SPEC "X\n", addr, CodeInfo->opnd[OPND1].type ));

            /* automatic (conditional) jump expansion.
             * for 386 and above this is not needed, since there exists
             * an extended version of Jcc
             */
            if( ( ModuleInfo.curr_cpu & P_CPU_MASK) < P_386 && IS_JCC( CodeInfo->token ) ) {
                /* look into jump extension */
                if( CodeInfo->opnd[OPND1].type != OP_I8 ) {
                    if( CodeInfo->mem_type == MT_EMPTY && ModuleInfo.ljmp == TRUE ) {
                        jumpExtend( CodeInfo, FALSE );
                        addr -= 1;
                        CodeInfo->opnd[OPND1].data32l = addr;
                        //return( SCRAP_INSTRUCTION );
                    //} else if( !PhaseError ) {
                    } else {
                        DebugMsg(("%u process_branch: CPU < 386 and Jcc distance != SHORT, mem_type=%X, curr_ofs=%X, addr=%d\n", Parse_Pass + 1, CodeInfo->mem_type, GetCurrOffset(), addr ));
                        /* v2.11: don't emit "out of range" if OP_I16 was forced by type coercion ( jmp near ptr xxx ) */
                        return( EmitErr( CodeInfo->mem_type == MT_EMPTY ? JUMP_OUT_OF_RANGE : JUMP_DISTANCE_NOT_POSSIBLE, addr ) );
                    }
                }
            }
            /* v2.02: in pass one, write "backpatch" fixup for forward
             * references.
             */
            /* the "if" below needs to be explaind.
             * Fixups will be written for forward references in pass one.
             * state is SYM_UNDEFINED then. The fixups will be scanned when
             * the label is met finally, still in pass one. See backptch.c
             * for details.
             */
            if ( state != SYM_UNDEFINED )
                return( NOT_ERROR ); /* exit, no fixup is written! */
        }
    }

    DebugMsg1(("process_branch: fixup needed\n" ));

    fixup_option = OPTJ_NONE;
    fixup_type = FIX_RELOFF8;

    mem_type = opndx->mem_type;

    /* v2.04: far call optimization possible if destination is in
     * another segment of the same group. However, a fixup must be written.
     * Masm does NOT optimize if destination is external!
     */
    if( CodeInfo->token == T_CALL &&
       CodeInfo->mem_type == MT_EMPTY &&
       ( sym->mem_type == MT_FAR || SegOverride ) ) {
        symseg = GetSegm( sym );
        if ( symseg == CurrSeg ||
            ( symseg != NULL && symseg->e.seginfo->group != NULL && symseg->e.seginfo->group == CurrSeg->e.seginfo->group ) ) {
            DebugMsg1(("process_branch: FAR call optimization applied!, seg=%X, CurrSeg=%X, grps=%X/%X\n", symseg, CurrSeg, symseg->e.seginfo->group, CurrSeg->e.seginfo->group ));
            FarCallToNear( CodeInfo ); /* switch mem_type to NEAR */
        }
    }
    /* forward ref, or external symbol */
    if( CodeInfo->mem_type == MT_EMPTY && mem_type != MT_EMPTY && opndx->instr != T_SHORT ) {
        /* MT_PROC is most likely obsolete ( used by TYPEDEF only ) */
        /* v2.09: removed */
        //if ( mem_type == MT_PROC )
        //    mem_type = ( ( SIZE_CODEPTR & ( 1 << ModuleInfo.model ) ) ? MT_FAR : MT_NEAR );
        switch( mem_type ) {
        case MT_FAR:
            if( IS_JMPCALL( CodeInfo->token ) ) {
                CodeInfo->isfar = TRUE;
            }
            /* v2.06: commented 2 lines to copy behavior of MT_NEAR */
            //CodeInfo->mem_type = mem_type;
            //break;
        case MT_NEAR:
            /* v2.04: 'if' added */
            if ( state != SYM_UNDEFINED )
                CodeInfo->mem_type = mem_type;
            break;
        default:
            DebugMsg(("process_branch: unexpected mem_type %Xh\n", mem_type ));
            /**/myassert( 0 );
            CodeInfo->mem_type = mem_type;
        }
    }

    /* handle far JMP + CALL? */
    if ( IS_JMPCALL( CodeInfo->token ) &&
        ( CodeInfo->isfar == TRUE || CodeInfo->mem_type == MT_FAR )) {
        CodeInfo->isfar = TRUE; /* flag isn't set if explicit is true */
        DebugMsg1(("process_branch: FAR call/jmp\n"));
        switch( CodeInfo->mem_type ) {
        case MT_NEAR:
            if( opndx->explicit || opndx->instr == T_SHORT ) {
                return( EmitError( CANNOT_USE_SHORT_OR_NEAR ) );
            }
            /* fall through */
        case MT_FAR:
        case MT_EMPTY:
            /* v1.95: explicit flag to be removed! */
            //if ( opndx->explicit && opndx->Ofssize != USE_EMPTY )
            if ( opndx->Ofssize != USE_EMPTY )
                CodeInfo->prefix.opsiz = OPSIZE( CodeInfo->Ofssize, opndx->Ofssize );
            else
                CodeInfo->prefix.opsiz = OPSIZE( CodeInfo->Ofssize, GetSymOfssize( sym ) );

            /* set fixup frame variables Frame + Frame_Datum */
            set_frame( sym );
            if( IS_OPER_32( CodeInfo ) ) {
                fixup_type = FIX_PTR32;
                CodeInfo->opnd[OPND1].type = OP_I48;
            } else {
                fixup_type = FIX_PTR16;
                CodeInfo->opnd[OPND1].type = OP_I32;
            }
            break;
#ifdef DEBUG_OUT
        default: /* cannot happen */
            DebugMsg(("process_branch: JMP/CALL far, unexpected mem_type=%X\n", CodeInfo->mem_type ));
            /**/myassert( 0 );
            //return( EmitError( INVALID_OPERAND_SIZE ) );
#endif
        }
        CodeInfo->opnd[OPND1].InsFixup = CreateFixup( sym, fixup_type, fixup_option );
        return( NOT_ERROR );
    }  /* end if FAR JMP/CALL */

    switch( CodeInfo->token ) {
    case T_CALL:
        if( opndx->instr == T_SHORT ) {
            return( EmitError( CANNOT_USE_SHORT_WITH_CALL ) );
        }
        if( CodeInfo->mem_type == MT_EMPTY ) {
            fixup_option = OPTJ_CALL;
            if( CodeInfo->Ofssize > USE16 ) {
                fixup_type = FIX_RELOFF32;
                CodeInfo->opnd[OPND1].type = OP_I32;
            } else {
                fixup_type = FIX_RELOFF16;
                CodeInfo->opnd[OPND1].type = OP_I16;
            }
            break;
        }
        /* fall through */
    case T_JMP:
        DebugMsg1(("process_branch: JMP/CALL, CodeInfo->memtype=%X\n", CodeInfo->mem_type ));
        switch( CodeInfo->mem_type ) {
        case MT_EMPTY:
            /* forward reference
             * default distance is short, we will expand later if needed
             */
            CodeInfo->opnd[OPND1].type = OP_I8;
            fixup_type = FIX_RELOFF8;
            fixup_option = (opndx->instr == T_SHORT) ? OPTJ_EXPLICIT : OPTJ_NONE;
            break;
        case MT_NEAR:
            fixup_option = OPTJ_EXPLICIT;
#if 1 /* v2.11: added, see call5.aso */
            if( opndx->Ofssize != USE_EMPTY ) {
                if ( opndx->Ofssize == USE16 ) {
                    fixup_type = FIX_RELOFF16;
                    CodeInfo->opnd[OPND1].type = OP_I16;
                } else {
                    fixup_type = FIX_RELOFF32;
                    CodeInfo->opnd[OPND1].type = OP_I32;
                }
                CodeInfo->prefix.opsiz = OPSIZE( CodeInfo->Ofssize, opndx->Ofssize );
            } else
#endif
            if( CodeInfo->Ofssize > USE16 ) {
                fixup_type = FIX_RELOFF32;
                CodeInfo->opnd[OPND1].type = OP_I32;
            } else {
                fixup_type = FIX_RELOFF16;
                CodeInfo->opnd[OPND1].type = OP_I16;
            }
            set_frame( sym );/* added v1.95 (after change in fixup.c */
            break;
#ifdef DEBUG_OUT
        default:
            DebugMsg(("process_branch: JMP/CALL, unexpected mem_type=%X\n", CodeInfo->mem_type ));
            /**/myassert( 0 );
            //return( EmitError( INVALID_OPERAND_SIZE ) );
#endif
        }
        /* deactivated because there's no override involved here */
        // check_assume( sym, EMPTY );
        break;
    default: /* JxCXZ, LOOPxx, Jxx */
        /* JxCXZ and LOOPxx always require SHORT label */
        if ( IS_XCX_BRANCH( CodeInfo->token ) ) {
            if( CodeInfo->mem_type != MT_EMPTY && opndx->instr != T_SHORT ) {
                return( EmitError( ONLY_SHORT_JUMP_DISTANCE_IS_ALLOWED ) );
            }
            CodeInfo->opnd[OPND1].type = OP_I8;
            fixup_option = OPTJ_EXPLICIT;
            fixup_type = FIX_RELOFF8;
            break;
        }
        /* just Jxx remaining */

        if( ( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_386 ) {

            switch( CodeInfo->mem_type ) {
            case MT_EMPTY:
                /* forward reference */
                fixup_option = ( opndx->instr == T_SHORT ) ? OPTJ_EXPLICIT : OPTJ_JXX;
                fixup_type = FIX_RELOFF8;
                CodeInfo->opnd[OPND1].type = OP_I8;
                break;
            case MT_NEAR:
                fixup_option = OPTJ_EXPLICIT;
                /* v1.95: explicit flag to be removed! */
                //if ( opndx->explicit && opndx->Ofssize != USE_EMPTY ) {
                if ( opndx->Ofssize != USE_EMPTY ) {
                    CodeInfo->prefix.opsiz = OPSIZE( CodeInfo->Ofssize, opndx->Ofssize );
                    CodeInfo->opnd[OPND1].type = (opndx->Ofssize >= USE32) ? OP_I32 : OP_I16;
                } else if( CodeInfo->Ofssize > USE16 ) {
                    fixup_type = FIX_RELOFF32;
                    CodeInfo->opnd[OPND1].type = OP_I32;
                } else {
                    fixup_type = FIX_RELOFF16;
                    CodeInfo->opnd[OPND1].type = OP_I16;
                }
                break;
            case MT_FAR:
                if ( ModuleInfo.ljmp ) { /* OPTION LJMP set? */
                    /* v1.95: explicit flag to be removed! */
                    //if ( opndx->explicit && opndx->Ofssize != USE_EMPTY )
                    if ( opndx->Ofssize != USE_EMPTY )
                        CodeInfo->prefix.opsiz = OPSIZE( CodeInfo->Ofssize, opndx->Ofssize );
                    else
                        CodeInfo->prefix.opsiz = OPSIZE( CodeInfo->Ofssize, GetSymOfssize( sym ));
                    /* destination is FAR (externdef <dest>:far */
                    DebugMsg(("process_branch: JMP/CALL, FAR memtype, jump extension\n" ));
                    jumpExtend( CodeInfo, TRUE );
                    CodeInfo->isfar = TRUE;
                    if( IS_OPER_32( CodeInfo ) ) {
                        fixup_type = FIX_PTR32;
                        CodeInfo->opnd[OPND1].type = OP_I48;
                    } else {
                        fixup_type = FIX_PTR16;
                        CodeInfo->opnd[OPND1].type = OP_I32;
                    }
                    break;
                }
                /* fall through */
            default: /* is another memtype possible at all? */
                return( EmitError( ONLY_SHORT_AND_NEAR_JUMP_DISTANCE_IS_ALLOWED ) );
            }
        } else {
            /* the only mode in 8086, 80186, 80286 is
             * Jxx SHORT
             * Masm allows "Jxx near" if LJMP is on (default) */
            switch( CodeInfo->mem_type ) {
            case MT_EMPTY:
                if ( opndx->instr == T_SHORT )
                    fixup_option = OPTJ_EXPLICIT;
                else
                    fixup_option = OPTJ_EXTEND;
                fixup_type = FIX_RELOFF8;
                CodeInfo->opnd[OPND1].type = OP_I8;
                break;
            case MT_NEAR: /* allow Jxx NEAR if LJMP on */
            case MT_FAR:
                if ( ModuleInfo.ljmp ) {
                    if ( CodeInfo->mem_type == MT_FAR ) {
                        jumpExtend( CodeInfo, TRUE );
                        fixup_type = FIX_PTR16;
                        CodeInfo->isfar = TRUE;
                        CodeInfo->opnd[OPND1].type = OP_I32;
                    } else {
                        jumpExtend( CodeInfo, FALSE );
                        fixup_type = FIX_RELOFF16;
                        CodeInfo->opnd[OPND1].type = OP_I16;
                    }
                    break;
                }
                /* fall through */
            default:
                return( EmitError( ONLY_SHORT_JUMP_DISTANCE_IS_ALLOWED ) );
            }
        }
    } /* end switch (CodeInfo->token) */
    CodeInfo->opnd[OPND1].InsFixup = CreateFixup( sym, fixup_type, fixup_option );
    return( NOT_ERROR );
}
