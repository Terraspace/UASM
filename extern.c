/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:  Processing of directives
*               PUBLIC
*               EXT[E]RN
*               EXTERNDEF
*               PROTO
*               COMM
****************************************************************************/

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "segment.h"
#include "fastpass.h"
#include "listing.h"
#include "equate.h"
#include "fixup.h"
#include "mangle.h"
#include "label.h"
#include "input.h"
#include "expreval.h"
#include "types.h"
#include "condasm.h"
#include "proc.h"
#include "extern.h"

/* Masm accepts EXTERN for internal absolute symbols:
 * X EQU 0
 * EXTERN X:ABS
 *
 * However, the other way:
 * EXTERN X:ABS
 * X EQU 0
 *
 * is rejected! MASM_EXTCOND=1 will copy this behavior for Uasm.
 */
#define MASM_EXTCOND 1  /* 1 is Masm compatible */

static const char szCOMM[] = "COMM";

#if MANGLERSUPP

/* The "mangler" has been inherited from Wasm.
 * By default it's not active in Uasm (see MANGLERSUPP in globals.h)
 * It allows some fine tuning of the external's name in the object module,
 * but is relevant for mixing with OW code only.
 * Syntax:
 * EXTERN|EXTERNDEF [ [ mangle_type, ] lang_type ] name : type
 * PUBLIC [ [ mangle_type, ] lang_type ] name
 * COMM [ [ mangle_type, ] langtype] [NEAR|FAR] name: ...
 * mangle_type must be a 'string'.
 */
static char *Check4Mangler( int *i, struct asm_tok tokenarray[] )
/***************************************************************/
{
    char *mangle_type = NULL;
    if( tokenarray[*i].token == T_STRING ) {
        mangle_type = tokenarray[*i].string_ptr;
        (*i)++;
        if( tokenarray[*i].token != T_COMMA ) {
            EmitWarn( 2, EXPECTING_COMMA, tokenarray[*i].tokpos );
        } else {
            (*i)++;
        }
    }
    return( mangle_type );
}
#else
#define mangle_type NULL
#endif

/* create external.
 * sym must be NULL or of state SYM_UNDEFINED!
 */
static struct asym *CreateExternal( struct asym *sym, const char *name, char weak )
/*********************************************************************************/
{
    if ( sym == NULL )
        sym = SymCreate( name );
    else
        sym_remove_table( &SymTables[TAB_UNDEF], (struct dsym *)sym );

    if ( sym ) {
        sym->state = SYM_EXTERNAL;
        sym->seg_ofssize = ModuleInfo.Ofssize;
        sym->iscomm = FALSE;
        sym->weak = weak;
        sym_add_table( &SymTables[TAB_EXT], (struct dsym *)sym ); /* add EXTERNAL */
    }
    return( sym );
}

/* create communal.
 * sym must be NULL or of state SYM_UNDEFINED!
 */
static struct asym *CreateComm( struct asym *sym, const char *name )
/******************************************************************/
{
    if ( sym == NULL )
        sym = SymCreate( name );
    else
        sym_remove_table( &SymTables[TAB_UNDEF], (struct dsym *)sym );

    if ( sym ) {
        sym->state = SYM_EXTERNAL;
        sym->seg_ofssize = ModuleInfo.Ofssize;
        sym->iscomm = TRUE;
        sym->weak = FALSE;
        sym->isfar = FALSE;
        sym_add_table( &SymTables[TAB_EXT], (struct dsym *)sym ); /* add EXTERNAL */
    }
    return( sym );
}

/* create a prototype.
 * used by PROTO, EXTERNDEF and EXT[E]RN directives.
 */

static struct asym *CreateProto( int i, struct asm_tok tokenarray[], const char *name, enum lang_type langtype )
/**************************************************************************************************************/
{
    struct asym      *sym;
    struct dsym      *dir;

    DebugMsg1(("CreateProto( i=%u, name=%s, lang=%u )\n", i, name ? name : "NULL", langtype ));
    sym = SymSearch( name );

    /* the symbol must be either NULL or state
     * - SYM_UNDEFINED
     * - SYM_EXTERNAL + isproc == FALSE ( previous EXTERNDEF )
     * - SYM_EXTERNAL + isproc == TRUE ( previous PROTO )
     * - SYM_INTERNAL + isproc == TRUE ( previous PROC )
     */
    if( sym == NULL ||
       sym->state == SYM_UNDEFINED ||
       ( sym->state == SYM_EXTERNAL && sym->weak == TRUE && sym->isproc == FALSE )) {
        if ( NULL == ( sym = CreateProc( sym, name, SYM_EXTERNAL ) ) )
            return( NULL ); /* name was probably invalid */
    } else if ( sym->isproc == FALSE ) {
        EmitErr( SYMBOL_REDEFINITION, sym->name );
        return( NULL );
    }
    dir = (struct dsym *)sym;

    /* a PROTO typedef may be used */
    if ( tokenarray[i].token == T_ID ) {
        struct asym * sym2;
        sym2 = SymSearch( tokenarray[i].string_ptr );
        if ( sym2 && sym2->state == SYM_TYPE && sym2->mem_type == MT_PROC ) {
            i++;
            if ( tokenarray[i].token != T_FINAL ) {
                EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr );
                return( NULL );
            }
            CopyPrototype( dir, (struct dsym *)sym2->target_type );
            return( sym );
        }
    }

	/* sym->isproc is set inside ParseProc() */
    if ( Parse_Pass == PASS_1 ) {
        if ( ParseProc( dir, i, tokenarray, FALSE, langtype ) == ERROR )
            return( NULL );
#if DLLIMPORT
        sym->dll = ModuleInfo.CurrDll;
#endif
    } else {
        sym->isdefined = TRUE;
    }
    return( sym );
}

/* externdef [ attr ] symbol:type [, symbol:type,...] */

ret_code ExterndefDirective( int i, struct asm_tok tokenarray[] )
/***************************************************************/
{
    char                *token;
#if MANGLERSUPP
    char                *mangle_type = NULL;
#endif
    struct asym         *sym;
    enum lang_type      langtype;
    char isnew;
    struct qualified_type ti;

    DebugMsg1(("ExterndefDirective(%u) enter\n", i));

    i++; /* skip EXTERNDEF token */
#if MANGLERSUPP
    mangle_type = Check4Mangler( &i, tokenarray );
#endif
    do {

        ti.Ofssize = ModuleInfo.Ofssize;

        /* get the symbol language type if present */
        langtype = ModuleInfo.langtype;
        GetLangType( &i, tokenarray, &langtype );

        /* get the symbol name */
        if( tokenarray[i].token != T_ID ) {
            return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
        }
        token = tokenarray[i++].string_ptr;

        /* go past the colon */
        if( tokenarray[i].token != T_COLON ) {
            return( EmitError( COLON_EXPECTED ) );
        }
        i++;
        sym = SymSearch( token );

        //typetoken = tokenarray[i].string_ptr;
        ti.mem_type = MT_EMPTY;
        ti.size = 0;
        ti.is_ptr = 0;
        ti.is_far = FALSE;
        ti.ptr_memtype = MT_EMPTY;
        ti.symtype = NULL;
        ti.Ofssize = ModuleInfo.Ofssize;

        if ( tokenarray[i].token == T_ID && ( 0 == _stricmp( tokenarray[i].string_ptr, "ABS" ) ) ) {
            /* v2.07: MT_ABS is obsolete */
            //ti.mem_type = MT_ABS;
            i++;
        } else if ( tokenarray[i].token == T_DIRECTIVE && tokenarray[i].tokval == T_PROTO ) {
            /* dont scan this line further!
             * CreateProto() will either define a SYM_EXTERNAL or fail
             * if there's a syntax error or symbol redefinition.
             */
            sym = CreateProto( i + 1, tokenarray, token, langtype );
#if 0 /* global queue is obsolete */
            if ( sym && sym->isglobal == FALSE ) {
                sym->isglobal = TRUE;
                QAddItem( &ModuleInfo.g.GlobalQueue, sym );
            }
#endif
            return( sym ? NOT_ERROR : ERROR );
        } else if ( tokenarray[i].token != T_FINAL && tokenarray[i].token != T_COMMA ) {
            if ( GetQualifiedType( &i, tokenarray, &ti ) == ERROR )
                return( ERROR );
        }

        isnew = FALSE;
        if ( sym == NULL || sym->state == SYM_UNDEFINED ) {
            sym = CreateExternal( sym, token, TRUE );
            isnew = TRUE;
        }

        /* new symbol? */

        if ( isnew ) {
            DebugMsg1(("ExterndefDirective(%s): memtype=%X set, ofssize=%X\n", token, ti.mem_type, ti.Ofssize ));

            /* v2.05: added to accept type prototypes */
            if ( ti.is_ptr == 0 && ti.symtype && ti.symtype->isproc ) {
                CreateProc( sym, NULL, SYM_EXTERNAL );
                CopyPrototype( (struct dsym *)sym, (struct dsym *)ti.symtype );
                ti.mem_type = ti.symtype->mem_type;
                ti.symtype = NULL;
            }
            switch ( ti.mem_type ) {
            //case MT_ABS:
            case MT_EMPTY:
                /* v2.04: hack no longer necessary */
                //if ( sym->weak == TRUE )
                //    sym->equate = TRUE; /* allow redefinition by EQU, = */
                break;
            case MT_FAR:
                /* v2.04: don't inherit current segment for FAR externals
                 * if -Zg is set.
                 */
                if ( Options.masm_compat_gencode )
                    break; 
                /* fall through */
            default:
                //SetSymSegOfs( sym );
                sym->segment = &CurrSeg->sym;
            }
            sym->Ofssize = ti.Ofssize;

            if ( ti.is_ptr == 0 && ti.Ofssize != ModuleInfo.Ofssize ) {
                sym->seg_ofssize = ti.Ofssize;
                if ( sym->segment && ((struct dsym *)sym->segment)->e.seginfo->Ofssize != sym->seg_ofssize )
                    sym->segment = NULL;
            }

            sym->mem_type = ti.mem_type;
            sym->is_ptr = ti.is_ptr;
            sym->isfar = ti.is_far;
            sym->ptr_memtype = ti.ptr_memtype;
            if ( ti.mem_type == MT_TYPE )
                sym->type = ti.symtype;
            else
                sym->target_type = ti.symtype;

            /* v2.04: only set language if there was no previous definition */
            SetMangler( sym, langtype, mangle_type );

        } else if ( Parse_Pass == PASS_1 ) {

            /* v2.05: added to accept type prototypes */
            if ( ti.is_ptr == 0 && ti.symtype && ti.symtype->isproc ) {
                ti.mem_type = ti.symtype->mem_type;
                ti.symtype = NULL;
            }
            /* ensure that the type of the symbol won't change */

            if ( sym->mem_type != ti.mem_type ) {
                /* if the symbol is already defined (as SYM_INTERNAL), Masm
                 won't display an error. The other way, first externdef and
                 then the definition, will make Masm complain, however */
                DebugMsg(("ExterndefDirective: type conflict for %s. mem_types old-new: %X-%X\n", sym->name, sym->mem_type, ti.mem_type));
                EmitWarn( 1, SYMBOL_TYPE_CONFLICT, sym->name );
            } else if ( sym->mem_type == MT_TYPE && sym->type != ti.symtype ) {
                struct asym *sym2 = sym;
                /* skip alias types and compare the base types */
                DebugMsg(("ExterndefDirective(%s): types differ: %X (%s) - %X (%s)\n", sym->name, sym->type, sym->type->name, ti.symtype, ti.symtype->name));
                while ( sym2->type )
                    sym2 = sym2->type;
                while ( ti.symtype->type )
                    ti.symtype = ti.symtype->type;
                if ( sym2 != ti.symtype ) {
                    DebugMsg(("ExterndefDirective(%s): type conflict old-new: %X (%s) - %X (%s)\n", sym->name, sym2, sym2->name, ti.symtype, ti.symtype->name));
                    EmitWarn( 1, SYMBOL_TYPE_CONFLICT, sym->name );
                }
            }

            /* v2.04: emit a - weak - warning if language differs.
             * Masm doesn't warn.
             */
            if ( langtype != LANG_NONE && sym->langtype != langtype )
                EmitWarn( 3, LANGUAGE_ATTRIBUTE_CONFLICT, sym->name );
        }
        sym->isdefined = TRUE;

#if 0
        /* write a global entry if none has been written yet */
        if ( sym->state == SYM_EXTERNAL && sym->weak == FALSE )
            ;/* skip EXTERNDEF if a real EXTERN/COMM was done */
        else if ( sym->isglobal == FALSE ) {
            sym->isglobal = TRUE;
            DebugMsg1(("ExterndefDirective(%s): writing a global entry\n", sym->name));
            QAddItem( &ModuleInfo.g.GlobalQueue, sym );
        }
#else
        if ( sym->state == SYM_INTERNAL && sym->ispublic == FALSE ) {
            sym->ispublic = TRUE;
            AddPublicData( sym );
        }
#endif

        if ( tokenarray[i].token != T_FINAL )
            if ( tokenarray[i].token == T_COMMA ) {
                if ( (i + 1) < Token_Count )
                    i++;
            } else {
                return( EmitErr( EXPECTING_COMMA, tokenarray[i].tokpos ) );
            }

    } while ( i < Token_Count );

    return( NOT_ERROR );
}

/* PROTO directive.
 * <name> PROTO <params> is semantically identical to:
 * EXTERNDEF <name>: PROTO <params>
 */

ret_code ProtoDirective( int i, struct asm_tok tokenarray[] )
/***********************************************************/
{
    if( Parse_Pass != PASS_1 ) {
        struct asym *sym;
        /* v2.04: set the "defined" flag */
        if ( ( sym = SymSearch( tokenarray[0].string_ptr ) ) && sym->isproc == TRUE )
            sym->isdefined = TRUE;
        return( NOT_ERROR );
    }
    if( i != 1 ) {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
    }

    return( CreateProto( 2, tokenarray, tokenarray[0].string_ptr, ModuleInfo.langtype ) ? NOT_ERROR : ERROR );
}

/* helper for EXTERN directive.
 * also used to create 16-bit floating-point fixups.
 * sym must be NULL or of state SYM_UNDEFINED!
 */

struct asym *MakeExtern( const char *name, enum memtype mem_type, struct asym *vartype, struct asym *sym, uint_8 Ofssize )
/************************************************************************************************************************/
{
    sym = CreateExternal( sym, name, FALSE );
    if ( sym == NULL )
        return( NULL );

    //if ( mem_type == MT_ABS )
    if ( mem_type == MT_EMPTY )
        ;
    else if ( Options.masm_compat_gencode == FALSE || mem_type != MT_FAR )
        sym->segment = &CurrSeg->sym;

    sym->isdefined = TRUE;
    sym->mem_type = mem_type;
    sym->seg_ofssize = Ofssize;
    sym->type = vartype;
    return( sym );
}

/* handle optional alternate names in EXTERN directive
 */

static ret_code HandleAltname( char *altname, struct asym *sym )
/**************************************************************/
{
    struct asym *symalt;

    if ( altname && sym->state == SYM_EXTERNAL ) {

        symalt = SymSearch( altname );

        /* altname symbol changed? */
        if ( sym->altname && sym->altname != symalt ) {
            return( EmitErr( SYMBOL_REDEFINITION, sym->name ) );
        }

        if ( Parse_Pass > PASS_1 ) {
            if ( symalt->state == SYM_UNDEFINED ) {
                EmitErr( SYMBOL_NOT_DEFINED, altname );
            } else if (symalt->state != SYM_INTERNAL && symalt->state != SYM_EXTERNAL ) {
                EmitErr( SYMBOL_TYPE_CONFLICT, altname );
            } else {
#if COFF_SUPPORT || ELF_SUPPORT
                if ( symalt->state == SYM_INTERNAL && symalt->ispublic == FALSE )
                    if ( Options.output_format == OFORMAT_COFF
#if ELF_SUPPORT
                        || Options.output_format == OFORMAT_ELF
#endif
                       ) {
                        EmitErr( MUST_BE_PUBLIC_OR_EXTERNAL, altname );
                    }
#endif
                if ( sym->mem_type != symalt->mem_type )
                    EmitErr( SYMBOL_TYPE_CONFLICT, altname );
            }
        } else {

            if ( symalt ) {
                DebugMsg(("HandleAltname: symbol '%s' found, state=%u\n", altname, symalt->state ));
                if ( symalt->state != SYM_INTERNAL &&
                    symalt->state != SYM_EXTERNAL &&
                    symalt->state != SYM_UNDEFINED ) {
                    return( EmitErr( SYMBOL_TYPE_CONFLICT, altname ) );
                }
            } else {
                symalt = SymCreate( altname );
                sym_add_table( &SymTables[TAB_UNDEF], (struct dsym *)symalt );
            }
            /* make sure the alt symbol becomes strong if it is an external
             * v2.11: don't do this for OMF ( maybe neither for COFF/ELF? )
             */
            if ( Options.output_format != OFORMAT_OMF )
                symalt->used = TRUE;
            /* symbol inserted in the "weak external" queue?
             * currently needed for OMF only.
             */
            if ( sym->altname == NULL ) {
                sym->altname = symalt;
#if 0 /* v2.11: removed. Member nextext wasn't free to use */
                DebugMsg1(("HandleAltname: symbol '%s' added to AltQueue\n", sym->name ));
                ((struct dsym *)sym)->nextext = NULL;
                if ( ModuleInfo.g.AltQueue.head == NULL )
                    ModuleInfo.g.AltQueue.head = ModuleInfo.g.AltQueue.tail = (struct dsym *)sym;
                else {
                    ((struct dsym *)ModuleInfo.g.AltQueue.tail)->nextext = (struct dsym *)sym;
                    ModuleInfo.g.AltQueue.tail = (struct dsym *)sym;
                }
#endif
            }
        }
    }
    return( NOT_ERROR );
}

/* syntax: EXT[E]RN [lang_type] name (altname) :type [, ...] */

ret_code ExternDirective( int i, struct asm_tok tokenarray[] )
/************************************************************/
{
    char                *token;
#if MANGLERSUPP
    char                *mangle_type = NULL;
#endif
    char                *altname;
    struct asym         *sym;
    enum lang_type      langtype;
    struct qualified_type ti;

    DebugMsg1(("ExternDirective(%u) enter\n", i));
    i++; /* skip EXT[E]RN token */
#if MANGLERSUPP
    mangle_type = Check4Mangler( &i, tokenarray );
#endif
    do {

        altname = NULL;

        /* get the symbol language type if present */
        langtype = ModuleInfo.langtype;
        GetLangType( &i, tokenarray, &langtype );

        /* get the symbol name */
        if( tokenarray[i].token != T_ID ) {
            return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
        }
        token = tokenarray[i++].string_ptr;

        /* go past the optional alternative name (weak ext, default resolution) */
        if( tokenarray[i].token == T_OP_BRACKET ) {
            i++;
            if ( tokenarray[i].token != T_ID ) {
                return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
            }
            altname = tokenarray[i].string_ptr;
            i++;
            if( tokenarray[i].token != T_CL_BRACKET ) {
                return( EmitErr( EXPECTED, ")" ) );
            }
            i++;
        }

        /* go past the colon */
        if( tokenarray[i].token != T_COLON ) {
            return( EmitError( COLON_EXPECTED ) );
        }
        i++;
        sym = SymSearch( token );

        ti.mem_type = MT_EMPTY;
        ti.size = 0;
        ti.is_ptr = 0;
        ti.is_far = FALSE;
        ti.ptr_memtype = MT_EMPTY;
        ti.symtype = NULL;
        ti.Ofssize = ModuleInfo.Ofssize;

        if ( tokenarray[i].token == T_ID && ( 0 == _stricmp( tokenarray[i].string_ptr, "ABS" ) ) ) {
            //ti.mem_type = MT_ABS;
            i++;
        } else if ( tokenarray[i].token == T_DIRECTIVE && tokenarray[i].tokval == T_PROTO ) {
            /* dont scan this line further */
            /* CreateProto() will define a SYM_EXTERNAL */
            sym = CreateProto( i + 1, tokenarray, token, langtype );
            DebugMsg1(("ExternDirective(%s): CreateProto()=%X\n", token, sym));
            if ( sym == NULL )
                return( ERROR );
            if ( sym->state == SYM_EXTERNAL ) {
                sym->weak = FALSE;
                return( HandleAltname( altname, sym ) );
            } else {
                /* unlike EXTERNDEF, EXTERN doesn't allow a PROC for the same name */
                return( EmitErr( SYMBOL_REDEFINITION, sym->name ) );
            }
        } else if ( tokenarray[i].token != T_FINAL && tokenarray[i].token != T_COMMA ) {
            if ( GetQualifiedType( &i, tokenarray, &ti ) == ERROR )
                return( ERROR );
        }

        DebugMsg1(("ExternDirective(%s): mem_type=%Xh\n", token, ti.mem_type ));

        if( sym == NULL || sym->state == SYM_UNDEFINED ) {
            /* v2.04: emit the error at the PUBLIC directive */
            //if ( sym && sym->public == TRUE ) {
            //    EmitErr( CANNOT_DEFINE_AS_PUBLIC_OR_EXTERNAL, sym->name );
            //    return( ERROR );
            //}
            if(( sym = MakeExtern( token, ti.mem_type,
                                  ti.mem_type == MT_TYPE ? ti.symtype : NULL, sym,
                                  ti.is_ptr ? ModuleInfo.Ofssize : ti.Ofssize )) == NULL )
                return( ERROR );

            /* v2.05: added to accept type prototypes */
            if ( ti.is_ptr == 0 && ti.symtype && ti.symtype->isproc ) {
                CreateProc( sym, NULL, SYM_EXTERNAL );
                sym->weak = FALSE; /* v2.09: reset the weak bit that has been set inside CreateProc() */
                CopyPrototype( (struct dsym *)sym, (struct dsym *)ti.symtype );
                ti.mem_type = ti.symtype->mem_type;
                ti.symtype = NULL;
                DebugMsg1(("ExternDirective(%s): prototype copied, memtype=%X\n", token, ti.mem_type ));
            }

        } else {
#if MASM_EXTCOND
            /* allow internal AND external definitions for equates */
            //if ( sym->state == SYM_INTERNAL && sym->mem_type == MT_ABS )
            if ( sym->state == SYM_INTERNAL && sym->mem_type == MT_EMPTY )
                ;
            else
#endif
            if ( sym->state != SYM_EXTERNAL ) {
                DebugMsg(("ExternDirective: symbol %s redefinition, state=%u\n", token, sym->state ));
                return( EmitErr( SYMBOL_REDEFINITION, token ) );
            }
            /* v2.05: added to accept type prototypes */
            if ( ti.is_ptr == 0 && ti.symtype && ti.symtype->isproc ) {
                ti.mem_type = ti.symtype->mem_type;
                ti.symtype = NULL;
            }

            if( sym->mem_type != ti.mem_type ||
               sym->is_ptr != ti.is_ptr ||
               sym->isfar != ti.is_far ||
               ( sym->is_ptr && sym->ptr_memtype != ti.ptr_memtype ) ||
               ((sym->mem_type == MT_TYPE) ? sym->type : sym->target_type) != ti.symtype ||
               ( langtype != LANG_NONE && sym->langtype != LANG_NONE && sym->langtype != langtype )) {
                DebugMsg(("ExternDirective: memtype:%X-%X ptr=%X-%X far=%X-%X ptr_memtype=%X-%X lang=%u-%u\n",
                          sym->mem_type, ti.mem_type,
                          sym->is_ptr, ti.is_ptr,
                          sym->isfar, ti.is_far,
                          sym->ptr_memtype, ti.ptr_memtype,
                          sym->langtype, langtype
                         ));
                return( EmitErr( SYMBOL_TYPE_CONFLICT, token ) );
            }
        }

        sym->isdefined = TRUE;
        sym->Ofssize = ti.Ofssize;

        if ( ti.is_ptr == 0 && ti.Ofssize != ModuleInfo.Ofssize ) {
            sym->seg_ofssize = ti.Ofssize;
            if ( sym->segment && ((struct dsym *)sym->segment)->e.seginfo->Ofssize != sym->seg_ofssize )
                sym->segment = NULL;
        }

        sym->mem_type = ti.mem_type;
        sym->is_ptr = ti.is_ptr;
        sym->isfar = ti.is_far;
        sym->ptr_memtype = ti.ptr_memtype;
        if ( ti.mem_type == MT_TYPE )
            sym->type = ti.symtype;
        else
            sym->target_type = ti.symtype;

        HandleAltname( altname, sym );

        SetMangler( sym, langtype, mangle_type );

        if ( tokenarray[i].token != T_FINAL )
            if ( tokenarray[i].token == T_COMMA &&  ( (i + 1) < Token_Count ) ) {
                i++;
            } else {
                return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
            }
    }  while ( i < Token_Count );

    return( NOT_ERROR );
}

/* helper for COMM directive */

static struct asym *MakeComm( char *name, struct asym *sym, uint_32 size, uint_32 count, bool isfar )
/***************************************************************************************************/
{
    sym = CreateComm( sym, name );
    if( sym == NULL )
        return( NULL );

    sym->total_length = count;
    sym->isfar = isfar;

    /* v2.04: don't set segment if communal is far and -Zg is set */
    if ( Options.masm_compat_gencode == FALSE || isfar == FALSE )
        sym->segment = &CurrSeg->sym;

    MemtypeFromSize( size, &sym->mem_type );

    /* v2.04: warning added ( Masm emits an error ) */
    /* v2.05: code active for 16-bit only */
    if ( ModuleInfo.Ofssize == USE16 )
        if ( ( count * size ) > 0x10000UL )
            EmitWarn( 2, COMM_VAR_EXCEEDS_64K, sym->name );

    sym->total_size = count * size;

    return( sym );
}

/* define "communal" items
 * syntax:
 * COMM [langtype] [NEAR|FAR] label:type[:count] [, ... ]
 * the size & count values must NOT be forward references!
 */

ret_code CommDirective( int i, struct asm_tok tokenarray[] )
/**********************************************************/
{
    char            *token;
#if MANGLERSUPP
    char            *mangle_type = NULL;
#endif
    bool            isfar;
    //int             distance;
    int             tmp;
    uint_32         size;  /* v2.12: changed from 'int' to 'uint_32' */
    uint_32         count; /* v2.12: changed from 'int' to 'uint_32' */
    struct asym     *sym;
    struct expr     opndx;
    enum lang_type  langtype;

    DebugMsg1(("CommDirective(%u) enter\n", i));
    i++; /* skip COMM token */
    for( ; i < Token_Count; i++ ) {
#if MANGLERSUPP
        mangle_type = Check4Mangler( &i, tokenarray );
#endif
        /* get the symbol language type if present */
        langtype = ModuleInfo.langtype;
        GetLangType( &i, tokenarray, &langtype );

        /* get the -optional- distance ( near or far ) */
        isfar = FALSE;
        if ( tokenarray[i].token == T_STYPE )
            switch ( tokenarray[i].tokval ) {
            case T_FAR:
            case T_FAR16:
            case T_FAR32:
                if ( ModuleInfo.model == MODEL_FLAT ) {
                    EmitError( FAR_NOT_ALLOWED_IN_FLAT_MODEL_COMM_VARIABLES );
                } else
                    isfar = TRUE;
                /* no break */
            case T_NEAR:
            case T_NEAR16:
            case T_NEAR32:
                i++;
            }

        /* v2.08: ensure token is a valid id */
        if( tokenarray[i].token != T_ID ) {
            return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
        }
        /* get the symbol name */
        token = tokenarray[i++].string_ptr;

        /* go past the colon */
        if( tokenarray[i].token != T_COLON ) {
            return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
        }
        i++;
        /* the evaluator cannot handle a ':' so scan for one first */
        for ( tmp = i; tmp < Token_Count;tmp++ )
            if ( tokenarray[tmp].token == T_COLON )
                break;
        /* v2.10: expression evaluator isn't to accept forward references */
        //if ( EvalOperand( &i, tokenarray, tmp, &opndx, 0 ) == ERROR )
        if ( EvalOperand( &i, tokenarray, tmp, &opndx, EXPF_NOUNDEF ) == ERROR )
            return( ERROR );

        /* v2.03: a string constant is accepted by Masm */
        /* v2.11: don't accept NEAR or FAR */
        /* v2.12: check for too large value added */
        //if ( opndx.kind != EXPR_CONST || opndx.string != NULL ) {
        if ( opndx.kind != EXPR_CONST )
            EmitError( CONSTANT_EXPECTED );
        else if ( ( opndx.mem_type & MT_SPECIAL_MASK) == MT_ADDRESS )
            EmitErr( INVALID_TYPE_FOR_DATA_DECLARATION, token );
        else if ( opndx.hvalue != 0 && opndx.hvalue != -1 )
            EmitConstError( &opndx );
        else if ( opndx.uvalue == 0 )
            EmitError( POSITIVE_VALUE_EXPECTED );

        size = opndx.uvalue;

        count = 1;
        if( tokenarray[i].token == T_COLON ) {
            i++;
            /* get optional count argument */
            /* v2.10: expression evaluator isn't to accept forward references */
            //if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR )
            if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) == ERROR )
                return( ERROR );

            /* v2.03: a string constant is acceptable! */
            /* v2.12: check for too large value added */
            //if ( opndx.kind != EXPR_CONST || opndx.string != NULL ) {
            if ( opndx.kind != EXPR_CONST )
                EmitError( CONSTANT_EXPECTED );
            else if ( opndx.hvalue != 0 && opndx.hvalue != -1 )
                EmitConstError( &opndx );
            else if ( opndx.uvalue == 0 )
                EmitError( POSITIVE_VALUE_EXPECTED );

            count = opndx.uvalue;
        }

        sym = SymSearch( token );
        if( sym == NULL || sym->state == SYM_UNDEFINED ) {
            sym = MakeComm( token, sym, size, count, isfar );
            if ( sym == NULL )
                return( ERROR );
        } else if ( sym->state != SYM_EXTERNAL || sym->iscomm != TRUE ) {
            return( EmitErr( SYMBOL_REDEFINITION, sym->name ) );
        } else {
            tmp = sym->total_size / sym->total_length;
            if( count != sym->total_length || size != tmp ) {
                return( EmitErr( NON_BENIGN_XXX_REDEFINITION, szCOMM, sym->name ) );
            }
        }
        sym->isdefined = TRUE;
        SetMangler( sym, langtype, mangle_type );

        if ( tokenarray[i].token != T_FINAL && tokenarray[i].token != T_COMMA ) {
            return( EmitErr( EXPECTING_COMMA, tokenarray[i].tokpos ) );
        }
    }
    return( NOT_ERROR );
}

void AddPublicData( struct asym *sym )
/************************************/
{
    DebugMsg1(("AddPublicData(%s)\n", sym->name ));
    QAddItem( &ModuleInfo.g.PubQueue, sym );
}

#if 0 /* v2.11: obsolete - the queue is read directly when needed */

/* get (next) PUBLIC symbol */

struct asym *GetPublicSymbols( void * *vp )
/*****************************************/
{
    struct qnode * *curr = (struct qnode * *)vp;

    if ( *curr == NULL )
        *curr = ModuleInfo.g.PubQueue.head;
    else
        *curr = (*curr)->next;

    for ( ; *curr ; *curr = (*curr)->next ) {
        struct asym *sym = (struct asym *)(*curr)->elmt;
        if ( sym->state == SYM_INTERNAL )
            return ( sym );
        /* v2.09: also return undefined symbols. this may be
         * the case for assembly time variables. This will trigger a full second
         * pass, and the PUBLIC directive will emit an error then.
         */
        if ( sym->state == SYM_UNDEFINED ) {
            DebugMsg(("GetPublicSymbols: sym=%s has state SYM_UNDEFINED\n", sym->name ));
            return ( sym );
        }
        DebugMsg(("GetPublicSymbols: sym=%s skipped, state=%u\n", sym->name, sym->state ));
    }
    return( NULL );
}

#endif

void FreePubQueue( void )
/***********************/
{
#if FASTMEM==0
    struct qnode *curr;
    struct qnode *next;
    for( curr = ModuleInfo.g.PubQueue.head; curr; curr = next ) {
        next = curr->next;
        LclFree( curr );
    }
#endif
    ModuleInfo.g.PubQueue.head = NULL;
}

/* syntax: PUBLIC [lang_type] name [, ...] */

ret_code PublicDirective( int i, struct asm_tok tokenarray[] )
/************************************************************/
{
#if MANGLERSUPP
    char                *mangle_type = NULL;
#endif
    char                *token;
    struct asym         *sym;
    //struct dsym       *dir;
    char                skipitem;
    enum lang_type      langtype;

    DebugMsg1(("PublicDirective(%u) enter\n", i));
    i++; /* skip PUBLIC directive */
#if MANGLERSUPP
    mangle_type = Check4Mangler( &i, tokenarray );
#endif
    do {

        /* read the optional language type */
        langtype = ModuleInfo.langtype;
        GetLangType( &i, tokenarray, &langtype );

        if ( tokenarray[i].token != T_ID ) {
            return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
        }
        /* get the symbol name */
        token = tokenarray[i++].string_ptr;

        DebugMsg1(("PublicDirective: sym=%s\n", token ));

        /* Add the public name */
        sym = SymSearch( token );
        if ( Parse_Pass == PASS_1 ) {
            if ( sym == NULL ) {
                if ( sym = SymCreate( token ) ) {
                    sym_add_table( &SymTables[TAB_UNDEF], (struct dsym *)sym );
                    DebugMsg1(("PublicDirective(%s): new symbol\n", sym->name ));
                } else
                    return( ERROR ); /* name was too long */
            }
            skipitem = FALSE;
        } else {
            if ( sym == NULL || sym->state == SYM_UNDEFINED ) {
                EmitErr( SYMBOL_NOT_DEFINED, token );
                //return( ERROR ); /* v2.04: dont exit */
            }
        }
        if ( sym ) {
            switch ( sym->state ) {
            case SYM_UNDEFINED:
                break;
            case SYM_INTERNAL:
                if ( sym->scoped == TRUE ) {
                    EmitErr( CANNOT_DECLARE_SCOPED_CODE_LABEL_AS_PUBLIC, sym->name );
                    skipitem = TRUE;
                    //return( ERROR );
                }
                break;
            case SYM_EXTERNAL:
                if ( sym->iscomm == TRUE ) {
                    EmitErr( CANNOT_DEFINE_AS_PUBLIC_OR_EXTERNAL, sym->name );
                    skipitem = TRUE;
                    //return( ERROR );
                } else if ( sym->weak == FALSE ) {
                    /* for EXTERNs, emit a different error msg */
                    EmitErr( SYMBOL_REDEFINITION, sym->name );
                    skipitem = TRUE;
                    //return( ERROR );
                }
                break;
            default:
                EmitErr( CANNOT_DEFINE_AS_PUBLIC_OR_EXTERNAL, sym->name );
                skipitem = TRUE;
                //return( ERROR );
            }
            if( Parse_Pass == PASS_1 && skipitem == FALSE ) {
                if ( sym->ispublic == FALSE ) {
                    sym->ispublic = TRUE;
                    AddPublicData( sym ); /* put it into the public table */
                }
                SetMangler( sym, langtype, mangle_type );
            }
        }

        if ( tokenarray[i].token != T_FINAL )
            if ( tokenarray[i].token == T_COMMA ) {
                if ( (i + 1) < Token_Count )
                    i++;
            } else {
                return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].tokpos ) );
            }

    } while ( i < Token_Count );

    return( NOT_ERROR );
}
