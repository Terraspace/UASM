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
* Description:  handles ASSUME
*
****************************************************************************/

#include <ctype.h>

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "segment.h"
#include "assume.h"
#include "types.h"
#include "label.h"
#include "lqueue.h"
#include "expreval.h"
#include "fastpass.h"
#include "tokenize.h"
#include "listing.h"

#if AMD64_SUPPORT
#define NUM_STDREGS 16
#else
#define NUM_STDREGS 8
#endif

/* prototypes */

/* todo: move static variables to ModuleInfo */

/* table SegAssume is for the segment registers;
 * for order see enum assume_segreg.
 */
struct assume_info SegAssumeTable[NUM_SEGREGS];

/* table StdAssume is for the standard registers;
 * order does match regno in special.h:
 * (R|E)AX=0, (R|E)CX=1, (R|E)DX=2, (R|E)BX=3
 * (R|E)SP=4, (R|E)BP=5, (R|E)SI=6, (R|E)DI=7
 * R8 .. R15.
 */
struct assume_info StdAssumeTable[NUM_STDREGS];

static struct asym *stdsym[NUM_STDREGS];

#if FASTPASS
static struct assume_info saved_SegAssumeTable[NUM_SEGREGS];
static struct assume_info saved_StdAssumeTable[NUM_STDREGS];
/* v2.05: saved type info content */
static struct stdassume_typeinfo saved_StdTypeInfo[NUM_STDREGS];
#endif

/* order to use for assume searches */
static const enum assume_segreg searchtab[] = {
    ASSUME_DS, ASSUME_SS, ASSUME_ES, ASSUME_FS, ASSUME_GS, ASSUME_CS
};

static const char szError[]   = { "ERROR" };
static const char szNothing[] = { "NOTHING" };
const char szDgroup[]  = { "DGROUP" };

void SetSegAssumeTable( void *savedstate )
/****************************************/
{
    DebugMsg(("SetSegAssumeTable\n" ));
    memcpy( &SegAssumeTable, savedstate, sizeof(SegAssumeTable) );
}
void GetSegAssumeTable( void *savedstate )
/****************************************/
{
    DebugMsg(("GetSegAssumeTable\n" ));
    memcpy( savedstate, &SegAssumeTable, sizeof(SegAssumeTable) );
}

/* unlike the segment register assumes, the
 * register assumes need more work to save/restore the
 * current status, because they have their own
 * type symbols, which may be reused.
 * this functions is also called by context.c, ContextDirective()!
 */

void SetStdAssumeTable( void *savedstate, struct stdassume_typeinfo *ti )
/***********************************************************************/
{
    int i;

    DebugMsg(("SetStdAssumeTable enter\n" ));
    memcpy( &StdAssumeTable, savedstate, sizeof(StdAssumeTable) );
    for ( i = 0; i < NUM_STDREGS; i++, ti++ ) {
        if ( StdAssumeTable[i].symbol ) {
            StdAssumeTable[i].symbol->type        = ti->type;
            StdAssumeTable[i].symbol->target_type = ti->target_type;
            StdAssumeTable[i].symbol->mem_type    = ti->mem_type;
            StdAssumeTable[i].symbol->ptr_memtype = ti->ptr_memtype;
            StdAssumeTable[i].symbol->is_ptr      = ti->is_ptr;
        }
    }
}

void GetStdAssumeTable( void *savedstate, struct stdassume_typeinfo *ti )
/***********************************************************************/
{
    int i;
    DebugMsg(("GetStdAssumeTable\n" ));
    memcpy( savedstate, &StdAssumeTable, sizeof(StdAssumeTable) );
    for ( i = 0; i < NUM_STDREGS; i++, ti++ ) {
        if ( StdAssumeTable[i].symbol ) {
            ti->type        = StdAssumeTable[i].symbol->type;
            ti->target_type = StdAssumeTable[i].symbol->target_type;
            ti->mem_type    = StdAssumeTable[i].symbol->mem_type;
            ti->ptr_memtype = StdAssumeTable[i].symbol->ptr_memtype;
            ti->is_ptr      = StdAssumeTable[i].symbol->is_ptr;
        }
    }
}

#if FASTPASS
void AssumeSaveState( void )
/**************************/
{
    GetSegAssumeTable( &saved_SegAssumeTable );
    GetStdAssumeTable( &saved_StdAssumeTable, saved_StdTypeInfo );
}
#endif

void AssumeInit( int pass ) /* pass may be -1 here! */
/*************************/
{
    int reg;

    for( reg = 0; reg < NUM_SEGREGS; reg++ ) {
        SegAssumeTable[reg].symbol = NULL;
        SegAssumeTable[reg].error = FALSE;
        SegAssumeTable[reg].is_flat = FALSE;
    }

    /* the GPR assumes are handled somewhat special by masm.
     * they aren't reset for each pass - instead they keep their value.
     */

    if ( pass <= PASS_1 ) { /* v2.10: just reset assumes in pass one */

        for( reg = 0; reg < NUM_STDREGS; reg++ ) {
            StdAssumeTable[reg].symbol = NULL;
            StdAssumeTable[reg].error = 0;
        }
        if ( pass == PASS_1 )
            memset( &stdsym, 0, sizeof( stdsym ) );
    }
#if FASTPASS
    if ( pass > PASS_1 && UseSavedState ) {
        SetSegAssumeTable( &saved_SegAssumeTable );
#if 0
        /* v2.10: this is a weird Masm feature:
         * if a GPR is assumed to be a pointer to a struct,
         * it isn't reset when a new pass starts.
         * see assume11.asm and assume12.asm
         */
        if ( pass == PASS_2 ) {
            struct assume_info *psaved = &saved_StdAssumeTable;
            struct stdassume_typeinfo *ptype = &saved_StdTypeInfo;
            for ( reg = 0; reg < NUM_STDREGS; reg++, psaved++, ptype++ )
                if ( psaved->symbol == NULL && StdAssumeTable[reg].symbol && StdAssumeTable[reg].symbol->target_type ) {
                    psaved->symbol = StdAssumeTable[reg].symbol;
                    ptype->type        = psaved->symbol->type;
                    ptype->target_type = psaved->symbol->target_type;
                    ptype->mem_type    = psaved->symbol->mem_type;
                    ptype->ptr_memtype = psaved->symbol->ptr_memtype;
                    ptype->is_ptr      = psaved->symbol->is_ptr;
                }
        }
#endif
        SetStdAssumeTable( &saved_StdAssumeTable, saved_StdTypeInfo );
    }
#endif
}

/* generate assume lines after .MODEL directive
 * model is in ModuleInfo.model, it can't be MODEL_NONE.
 */
void ModelAssumeInit( void )
/**************************/
{
    const char *pCS;
    const char *pFSassume = szError;
    const char *pGSassume = szError;
    const char *pFmt;

    /* Generates codes for assume */
    switch( ModuleInfo.model ) {
    case MODEL_FLAT:
#if AMD64_SUPPORT
        if ( ModuleInfo.fctype == FCT_WIN64 )
            pGSassume = szNothing;
#endif
        AddLineQueueX( "%r %r:%r,%r:%r,%r:%r,%r:%r,%r:%s,%r:%s",
                  T_ASSUME, T_CS, T_FLAT, T_DS, T_FLAT, T_SS, T_FLAT, T_ES, T_FLAT, T_FS, pFSassume, T_GS, pGSassume );
        break;
    case MODEL_TINY:
    case MODEL_SMALL:
    case MODEL_COMPACT:
    case MODEL_MEDIUM:
    case MODEL_LARGE:
    case MODEL_HUGE:
        /* v2.03: no DGROUP for COFF/ELF */
#if COFF_SUPPORT || ELF_SUPPORT
        if( Options.output_format == OFORMAT_COFF
#if ELF_SUPPORT
           || Options.output_format == OFORMAT_ELF
#endif
          )
            break;
#endif
        if ( ModuleInfo.model == MODEL_TINY )
            pCS = szDgroup;
        else
            pCS = SimGetSegName( SIM_CODE );

        if ( ModuleInfo.distance != STACK_FAR )
            pFmt = "%r %r:%s,%r:%s,%r:%s";
        else
            pFmt = "%r %r:%s,%r:%s";
        AddLineQueueX( pFmt, T_ASSUME, T_CS, pCS, T_DS, szDgroup, T_SS, szDgroup );
        break;
    }
}

/* used by INVOKE directive */

struct asym *GetStdAssume( int reg )
/**********************************/
{
    if ( StdAssumeTable[reg].symbol )
        if ( StdAssumeTable[reg].symbol->mem_type == MT_TYPE )
            return( StdAssumeTable[reg].symbol->type );
        else
            return( StdAssumeTable[reg].symbol->target_type );
    return ( NULL );
}

/* v2.05: new, used by
 * expression evaluator if a register is used for indirect addressing
 */

struct asym *GetStdAssumeEx( int reg )
/************************************/
{
    return( StdAssumeTable[reg].symbol );
}

ret_code AssumeDirective( int i, struct asm_tok tokenarray[] )
/************************************************************/
/* Handles ASSUME
 * syntax is :
 * - ASSUME
 * - ASSUME NOTHING
 * - ASSUME segregister : seglocation [, segregister : seglocation ]
 * - ASSUME dataregister : qualified type [, dataregister : qualified type ]
 * - ASSUME register : ERROR | NOTHING | FLAT
 */
{
    int             reg;
    int             j;
    int             size;
    uint_32         flags;
    struct assume_info *info;
    bool            segtable;
    struct qualified_type ti;

    DebugMsg1(( "AssumeDirective enter, pass=%u\n", Parse_Pass+1 ));

    for( i++; i < Token_Count; i++ ) {

        if( ( tokenarray[i].token == T_ID )
            && (0 == _stricmp( tokenarray[i].string_ptr, szNothing )) ) {
            AssumeInit( -1 );
            i++;
            break;
        }

        /*---- get the info ptr for the register ----*/

        info = NULL;
        if ( tokenarray[i].token == T_REG ) {
            reg = tokenarray[i].tokval;
            j = GetRegNo( reg );
            flags = GetValueSp( reg );
            if ( flags & OP_SR ) {
                info = &SegAssumeTable[j];
                segtable = TRUE;
            } else if ( flags & OP_R ) {
                info = &StdAssumeTable[j];
                segtable = FALSE;
            }
        }
        if ( info == NULL ) {
            return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
        }

        if( ( ModuleInfo.curr_cpu & P_CPU_MASK ) < GetCpuSp( reg ) ) {
            return( EmitError( INSTRUCTION_OR_REGISTER_NOT_ACCEPTED_IN_CURRENT_CPU_MODE ) );
        }

        i++; /* go past register */

        if( tokenarray[i].token != T_COLON ) {
            return( EmitError( COLON_EXPECTED ) );
        }
        i++;

        if( tokenarray[i].token == T_FINAL ) {
            return( EmitError( SYNTAX_ERROR ) );
        }

        /* check for ERROR and NOTHING */

        if( 0 == _stricmp( tokenarray[i].string_ptr, szError )) {
            if ( segtable ) {
                info->is_flat = FALSE;
                info->error = TRUE;
            } else
                info->error |= (( reg >= T_AH && reg <= T_BH ) ? RH_ERROR : ( flags & OP_R ));
            info->symbol = NULL;
            i++;
        } else if( 0 == _stricmp( tokenarray[i].string_ptr, szNothing )) {
            if ( segtable ) {
                info->is_flat = FALSE;
                info->error = FALSE;
            } else
                info->error &= ~(( reg >= T_AH && reg <= T_BH ) ? RH_ERROR : ( flags & OP_R ));
            info->symbol = NULL;
            i++;
        } else if ( segtable == FALSE ) {

            /* v2.05: changed to use new GetQualifiedType() function */
            ti.size = 0;
            ti.is_ptr = 0;
            ti.is_far = FALSE;
            ti.mem_type = MT_EMPTY;
            ti.ptr_memtype = MT_EMPTY;
            ti.symtype = NULL;
            ti.Ofssize = ModuleInfo.Ofssize;
            if ( GetQualifiedType( &i, tokenarray, &ti ) == ERROR )
                return( ERROR );

            /* v2.04: check size of argument! */
            size = OperandSize( flags, NULL );
            if ( ( ti.is_ptr == 0 && size != ti.size ) ||
                ( ti.is_ptr > 0 && size < CurrWordSize ) ) {
                return( EmitError( TYPE_IS_WRONG_SIZE_FOR_REGISTER ) );
            }
            info->error &= ~(( reg >= T_AH && reg <= T_BH ) ? RH_ERROR : ( flags & OP_R ));
            if ( stdsym[j] == NULL ) {
                stdsym[j] = CreateTypeSymbol( NULL, "", FALSE );
                stdsym[j]->typekind = TYPE_TYPEDEF;
            }

            stdsym[j]->total_size = ti.size;
            stdsym[j]->mem_type   = ti.mem_type;
            stdsym[j]->is_ptr     = ti.is_ptr;
            stdsym[j]->isfar      = ti.is_far;
            stdsym[j]->Ofssize    = ti.Ofssize;
            stdsym[j]->ptr_memtype = ti.ptr_memtype; /* added v2.05 rc13 */
            if ( ti.mem_type == MT_TYPE )
                stdsym[j]->type = ti.symtype;
            else
                stdsym[j]->target_type = ti.symtype;

            info->symbol = stdsym[j];

        } else { /* segment register */
            struct expr opnd;

            /* v2.08: read expression with standard evaluator */
            if( EvalOperand( &i, tokenarray, Token_Count, &opnd, 0 ) == ERROR )
                return( ERROR );
            switch ( opnd.kind ) {
            case EXPR_ADDR:
                if ( opnd.sym == NULL || opnd.indirect == TRUE || opnd.value ) {
                    return( EmitError( SEGMENT_GROUP_OR_SEGREG_EXPECTED ) );
                } else if ( opnd.sym->state == SYM_UNDEFINED ) {
                    /* ensure that directive is rerun in pass 2
                     * so an error msg can be emitted.
                     */
                    FStoreLine( 0 );
                    info->symbol = opnd.sym;
                } else if ( ( opnd.sym->state == SYM_SEG || opnd.sym->state == SYM_GRP ) && opnd.instr == EMPTY ) {
                    info->symbol = opnd.sym;
                } else if ( opnd.instr == T_SEG ) {
                    info->symbol = opnd.sym->segment;
                } else {
                    return( EmitError( SEGMENT_GROUP_OR_SEGREG_EXPECTED ) );
                }
                info->is_flat = ( info->symbol == &ModuleInfo.flat_grp->sym );
                break;
            case EXPR_REG:
                if ( GetValueSp( opnd.base_reg->tokval ) & OP_SR ) {
                    info->symbol = SegAssumeTable[ GetRegNo( opnd.base_reg->tokval ) ].symbol;
                    info->is_flat = SegAssumeTable[ GetRegNo( opnd.base_reg->tokval ) ].is_flat;
                    break;
                }
            default:
                return( EmitError( SEGMENT_GROUP_OR_SEGREG_EXPECTED ) );
            }
            info->error = FALSE;
        }

        /* comma expected */
        if( i < Token_Count && tokenarray[i].token != T_COMMA )
            break;
    }
    if ( i < Token_Count ) {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].tokpos ) );
    }
    return( NOT_ERROR );
}

/* for a symbol, search segment register which holds segment
 * part of symbol's address in assume table.
 * - sym: segment of symbol for which to search segment register
 * - def: prefered default register (or ASSUME_NOTHING )
 * - search_grps: if TRUE, check groups as well
 *
 * for data items, Masm checks assumes in this order:
 *   DS, SS, ES, FS, GS, CS
 */

enum assume_segreg search_assume( const struct asym *sym,
                  enum assume_segreg def, bool search_grps )
/**********************************************************/
{
    struct asym *grp;

    if( sym == NULL )
        return( ASSUME_NOTHING );

    grp = GetGroup( sym );

    /* first check the default segment register */

    if( def != ASSUME_NOTHING ) {
        if( SegAssumeTable[def].symbol == sym )
            return( def );
        if( search_grps && grp ) {
            if( SegAssumeTable[def].is_flat && grp == &ModuleInfo.flat_grp->sym )
                return( def );
            if( SegAssumeTable[def].symbol == grp )
                return( def );
        }
    }

    /* now check all segment registers */

    for( def = 0; def < NUM_SEGREGS; def++ ) {
        if( SegAssumeTable[searchtab[def]].symbol == sym ) {
            return( searchtab[def] );
        }
    }

    /* now check the groups */
    if( search_grps && grp )
        for( def = 0; def < NUM_SEGREGS; def++ ) {
            if( SegAssumeTable[searchtab[def]].is_flat && grp == &ModuleInfo.flat_grp->sym )
                return( searchtab[def] );
            if( SegAssumeTable[searchtab[def]].symbol == grp ) {
                return( searchtab[def] );
            }
        }

    return( ASSUME_NOTHING );
}

/*
 called by the parser's seg_override() function if
 a segment register override has been detected.
 - override: segment register override (0,1,2,3,4,5)
*/

struct asym *GetOverrideAssume( enum assume_segreg override )
/***********************************************************/
{
    if( SegAssumeTable[override].is_flat ) {
        return( (struct asym *)ModuleInfo.flat_grp );
    }
    return( SegAssumeTable[override].symbol);

}

/*
 * GetAssume():
 * called by check_assume() in parser.c
 * in:
 * - override: SegOverride
 * - sym: symbol in current memory operand
 * - def: default segment assume value
 * to be fixed: check if symbols with state==SYM_STACK are handled correctly.
 */

enum assume_segreg GetAssume( const struct asym *override, const struct asym *sym, enum assume_segreg def, struct asym * *passume )
/*********************************************************************************************************************************/
{
    enum assume_segreg  reg;

    if( ( def != ASSUME_NOTHING ) && SegAssumeTable[def].is_flat ) {
        *passume = (struct asym *)ModuleInfo.flat_grp;
        return( def );
    }
    if( override != NULL ) {
        reg = search_assume( override, def, FALSE );
#if 1 /* v2.10: added */
    } else if ( sym->state == SYM_STACK ) {
        /* stack symbols don't have a segment part.
         * In case [R|E]BP is used as base, it doesn't matter.
         * However, if option -Zg is set, this isn't true.
         */
        reg = ASSUME_SS;
#endif
    } else {
        reg = search_assume( sym->segment, def, TRUE );
    }
    if( reg == ASSUME_NOTHING ) {
        if( sym && sym->state == SYM_EXTERNAL && sym->segment == NULL ) {
            reg = def;
        }
    }
    if( reg != ASSUME_NOTHING ) {
        *passume = SegAssumeTable[reg].symbol;
        return( reg );
    }
    *passume = NULL;
    return( ASSUME_NOTHING );
}

