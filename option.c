/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:  Processing of OPTION directive.
*
****************************************************************************/

#include <ctype.h>

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "reswords.h"
#include "expreval.h"
#if STACKBASESUPP
#include "equate.h"
#endif

/* prototypes */
extern struct asym          *sym_Interface;

#ifdef __I86__
#define OPTQUAL __near
#else
#define OPTQUAL
#endif

#define OPTFUNC( name ) static ret_code OPTQUAL name( int *pi, struct asm_tok tokenarray[] )

/* OPTION directive helper functions */

/* OPTION DOTNAME */

OPTFUNC( SetDotName )
/*******************/
{
    ModuleInfo.dotname = TRUE;
    return( NOT_ERROR );
}

/* OPTION NODOTNAME */

OPTFUNC( SetNoDotName )
/*********************/
{
    ModuleInfo.dotname = FALSE;
    return( NOT_ERROR );
}

/* OPTION CASEMAP:NONE | NOTPUBLIC | ALL */

OPTFUNC( SetCaseMap )
/*******************/
{
    int i = *pi;
    if ( tokenarray[i].token == T_ID ) {
        if ( 0 == _stricmp( tokenarray[i].string_ptr, "NONE" ) ) {
            ModuleInfo.case_sensitive = TRUE;        /* -Cx */
            ModuleInfo.convert_uppercase = FALSE;
        } else if ( 0 == _stricmp( tokenarray[i].string_ptr, "NOTPUBLIC" ) ) {
            ModuleInfo.case_sensitive = FALSE;       /* -Cp */
            ModuleInfo.convert_uppercase = FALSE;
        } else if ( 0 == _stricmp( tokenarray[i].string_ptr, "ALL" ) ) {
            ModuleInfo.case_sensitive = FALSE;       /* -Cu */
            ModuleInfo.convert_uppercase = TRUE;
        } else {
            return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].tokpos ) );
        }
        DebugMsg1(("SetCaseMap(%s) ok\n", tokenarray[i].string_ptr ));
        i++;
        SymSetCmpFunc();
    } else {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].tokpos ) );
    }
    *pi = i;
    return( NOT_ERROR );
}

/* OPTION M510 */

OPTFUNC( SetM510 )
/****************/
{
    SetMasm510( TRUE );
    return( NOT_ERROR );
}

/* OPTION NOM510 */

OPTFUNC( SetNoM510 )
/******************/
{
    SetMasm510(FALSE);
    return( NOT_ERROR );
}

/* OPTION SCOPED */

OPTFUNC( SetScoped )
/******************/
{
    ModuleInfo.scoped = TRUE;
    return( NOT_ERROR );
}

/* OPTION NOSCOPED */

OPTFUNC( SetNoScoped )
/********************/
{
    ModuleInfo.scoped = FALSE;
    return( NOT_ERROR );
}

/* OPTION OLDSTRUCTS */

OPTFUNC( SetOldStructs )
/**********************/
{
    ModuleInfo.oldstructs = TRUE;
    return( NOT_ERROR );
}

/* OPTION NOOLDSTRUCTS */

OPTFUNC( SetNoOldStructs )
/************************/
{
    ModuleInfo.oldstructs = FALSE;
    return( NOT_ERROR );
}

/* OPTION EMULATOR */

OPTFUNC( SetEmulator )
/********************/
{
    ModuleInfo.emulator = TRUE;
    return( NOT_ERROR );
}

/* OPTION NOEMULATOR */

OPTFUNC( SetNoEmulator )
/**********************/
{
    ModuleInfo.emulator = FALSE;
    return( NOT_ERROR );
}

/* OPTION LJMP */

OPTFUNC( SetLJmp )
/****************/
{
    ModuleInfo.ljmp = TRUE;
    return( NOT_ERROR );
}

/* OPTION NOLJMP */

OPTFUNC( SetNoLJmp )
/******************/
{
    ModuleInfo.ljmp = FALSE;
    return( NOT_ERROR );
}

/* OPTION NOREADONLY */

OPTFUNC( SetNoReadonly )
/**********************/
{
    /* default, nothing to do */
    return( NOT_ERROR );
}

/* OPTION NOOLDMACROS */

OPTFUNC( SetNoOldmacros )
/***********************/
{
    /* default, nothing to do */
    return( NOT_ERROR );
}

/* OPTION EXPR32 */

OPTFUNC( SetExpr32 )
/******************/
{
    /* default, nothing to do */
    return( NOT_ERROR );
}

OPTFUNC( SetNoSignExt )
/*********************/
{
    ModuleInfo.NoSignExtend = TRUE;
    return( NOT_ERROR );
}

static void SkipOption( int *pi, struct asm_tok tokenarray[] )
/************************************************************/
{
    while ( tokenarray[*pi].token != T_FINAL &&
           tokenarray[*pi].token != T_COMMA )
        (*pi)++;
}

/* OPTION NOKEYWORD: <keyword[,keyword,...]>
 */

OPTFUNC( SetNoKeyword )
/*********************/
{
    int i = *pi;
    //struct ReservedWord *resw;
    unsigned index;
    char *p;

    if( Parse_Pass != PASS_1 ) {
        SkipOption( pi, tokenarray );
        return( NOT_ERROR);
    }
    if ( tokenarray[i].token != T_STRING || tokenarray[i].string_delim != '<' ) {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].tokpos ) );
    }
    for ( p = tokenarray[i].string_ptr; *p; ) {
        while ( isspace( *p ) ) p++;
        if ( *p ) {
            char *p2 = p;
            unsigned char cnt;
            //struct instr_item *instruct;
            for ( ;*p; p++ ) {
                if ( isspace( *p ) || *p == ',' )
                    break;
            }
            cnt = p - p2;
            /* todo: if MAX_ID_LEN can be > 255, then check size,
             * since a reserved word's size must be <= 255
             */
            index = FindResWord( p2, cnt );
            if ( index != 0 )
                DisableKeyword( index );
            else {
                if ( IsKeywordDisabled( p2, cnt ) ) {
                    return( EmitError( RESERVED_WORD_EXPECTED ) );
                }
            }
        }
        while ( isspace(*p) ) p++;
        if (*p == ',') p++;
    }
    i++;
    *pi = i;
    return( NOT_ERROR );
}

/* OPTION LANGUAGE:{C|PASCAL|BASIC|FORTRAN|SYSCALL|STDCALL|FASTCALL} */

OPTFUNC( SetLanguage )
/********************/
{
    int i = *pi;
    //lang_type langtype;
    //int language = ERROR;

    if ( tokenarray[i].token == T_RES_ID ) {
        if ( GetLangType( &i, tokenarray, &ModuleInfo.langtype ) == NOT_ERROR ) {
            /* update @Interface assembly time variable */
            if ( ModuleInfo.model != MODEL_NONE && sym_Interface )
                sym_Interface->value = ModuleInfo.langtype;
            *pi = i;
            return( NOT_ERROR );
        }
    }
    return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].tokpos ) );
}

/* OPTION SETIF2
 * syntax: option setif2:TRUE|FALSE
 */

OPTFUNC( SetSetIF2 )
/******************/
{
    int i = *pi;

    if ( 0 == _stricmp( tokenarray[i].string_ptr, "TRUE" ) ) {
        ModuleInfo.setif2 = TRUE;
        i++;
    } else if ( 0 == _stricmp( tokenarray[i].string_ptr, "FALSE" ) ) {
        ModuleInfo.setif2 = FALSE;
        i++;
    }
    *pi = i;
    return( NOT_ERROR );
}

/* OPTION PROLOGUE:macroname
 the prologue macro must be a macro function with 6 params:
 name macro procname, flag, parmbytes, localbytes, <reglist>, userparms
 procname: name of procedure
 flag: bits 0-2: calling convention
 bit 3: undef
 bit 4: 1 if caller restores ESP
 bit 5: 1 if proc is far
 bit 6: 1 if proc is private
 bit 7: 1 if proc is export
 bit 8: for epilogue: 1 if IRET, 0 if RET
 parmbytes: no of bytes for all params
 localbytes: no of bytes for all locals
 reglist: list of registers to save/restore, separated by commas
 userparms: prologuearg specified in PROC
 */

OPTFUNC( SetPrologue )
/********************/
{
    int i = *pi;

    if ( tokenarray[i].token != T_ID ) {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].tokpos ) );
    }
    if ( ModuleInfo.proc_prologue ) {
        LclFree( ModuleInfo.proc_prologue );
        ModuleInfo.proc_prologue = NULL;
    }
    if ( 0 == _stricmp( tokenarray[i].string_ptr, "NONE" ) ) {
        ModuleInfo.prologuemode = PEM_NONE;
    } else if ( 0 == _stricmp( tokenarray[i].string_ptr, "PROLOGUEDEF" ) ) {
        ModuleInfo.prologuemode = PEM_DEFAULT;
    } else {
        ModuleInfo.prologuemode = PEM_MACRO;
        ModuleInfo.proc_prologue = LclAlloc( strlen( tokenarray[i].string_ptr ) + 1);
        strcpy( ModuleInfo.proc_prologue, tokenarray[i].string_ptr );
    }

    i++;
    *pi = i;
    return( NOT_ERROR );
}

/* OPTION EPILOGUE:macroname */
/*
 do NOT check the macros here!
 */

OPTFUNC( SetEpilogue )
/********************/
{
    int i = *pi;

    if ( tokenarray[i].token != T_ID ) {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].tokpos ) );
    }
    if ( ModuleInfo.proc_epilogue ) {
        LclFree( ModuleInfo.proc_epilogue );
        ModuleInfo.proc_epilogue = NULL;
    }

    if ( 0 == _stricmp( tokenarray[i].string_ptr, "NONE" ) ) {
        ModuleInfo.epiloguemode = PEM_NONE;
    } else if ( 0 == _stricmp( tokenarray[i].string_ptr, "EPILOGUEDEF" ) ) {
        ModuleInfo.epiloguemode = PEM_DEFAULT;
    } else {
        ModuleInfo.epiloguemode = PEM_MACRO;
        ModuleInfo.proc_epilogue = LclAlloc( strlen( tokenarray[i].string_ptr ) + 1);
        strcpy( ModuleInfo.proc_epilogue, tokenarray[i].string_ptr );
    }

    i++;
    *pi = i;
    return( NOT_ERROR );
}

/* OPTION OFFSET: GROUP | FLAT | SEGMENT
 * default is GROUP.
 * determines result of OFFSET operator fixups if .model isn't set.
 */
OPTFUNC( SetOffset )
/******************/
{
    int i = *pi;

    if ( 0 == _stricmp( tokenarray[i].string_ptr, "GROUP" ) ) {
        ModuleInfo.offsettype = OT_GROUP;
    } else if ( 0 == _stricmp( tokenarray[i].string_ptr, "FLAT" ) ) {
        ModuleInfo.offsettype = OT_FLAT;
    } else if ( 0 == _stricmp( tokenarray[i].string_ptr, "SEGMENT" ) ) {
        ModuleInfo.offsettype = OT_SEGMENT;
    } else {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
    }
    i++;
    *pi = i;
    return( NOT_ERROR );
}

/* OPTION PROC:PRIVATE | PUBLIC | EXPORT */

OPTFUNC( SetProc )
/****************/
{
    int i = *pi;

    switch ( tokenarray[i].token ) {
    case T_ID:
        if ( 0 == _stricmp( tokenarray[i].string_ptr, "PRIVATE" ) ) {
            ModuleInfo.procs_private = TRUE;
            ModuleInfo.procs_export = FALSE;
            i++;
        } else if ( 0 == _stricmp( tokenarray[i].string_ptr, "EXPORT" ) ) {
            ModuleInfo.procs_private = FALSE;
            ModuleInfo.procs_export = TRUE;
            i++;
        }
        break;
    case T_DIRECTIVE: /* word PUBLIC is a directive */
        if ( tokenarray[i].tokval == T_PUBLIC ) {
            ModuleInfo.procs_private = FALSE;
            ModuleInfo.procs_export = FALSE;
            i++;
        }
        break;
    }
    *pi = i;
    return( NOT_ERROR );
}

/* OPTION SEGMENT:USE16|USE32|FLAT
 * this option set the default offset size for segments and
 * externals defined outside of segments.
 */

OPTFUNC( SetSegment )
/*******************/
{
    int i = *pi;

    if ( tokenarray[i].token == T_RES_ID && tokenarray[i].tokval == T_FLAT ) {
#if AMD64_SUPPORT
        if ( ( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_64 )
            ModuleInfo.defOfssize = USE64;
        else
#endif
            ModuleInfo.defOfssize = USE32;
    } else if ( tokenarray[i].token == T_ID && _stricmp( tokenarray[i].string_ptr, "USE16" ) == 0) {
        ModuleInfo.defOfssize = USE16;
    } else if ( tokenarray[i].token == T_ID && _stricmp( tokenarray[i].string_ptr, "USE32" ) == 0) {
        ModuleInfo.defOfssize = USE32;
#if AMD64_SUPPORT
    } else if ( tokenarray[i].token == T_ID && _stricmp( tokenarray[i].string_ptr, "USE64" ) == 0) {
        ModuleInfo.defOfssize = USE64;
#endif
    } else {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
    }
    i++;
    *pi = i;
    return( NOT_ERROR );
}

#if FIELDALIGN
/* OPTION FIELDALIGN:1|2|4|8|16|32 */

OPTFUNC( SetFieldAlign )
/**********************/
{
    int i = *pi;
    unsigned temp, temp2;
    struct expr opndx;

    if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) == ERROR )
        return( ERROR );
    if ( opndx.kind != EXPR_CONST ) {
        return( EmitError( CONSTANT_EXPECTED ) );
    }
    if( opndx.uvalue > MAX_STRUCT_ALIGN ) {
        return( EmitError( STRUCT_ALIGN_TOO_HIGH ) );
    }
    for( temp = 1, temp2 = 0; temp < opndx.uvalue ; temp <<= 1, temp2++ );
    if( temp != opndx.uvalue ) {
        return( EmitErr( POWER_OF_2, opndx.value ) );
    }
    ModuleInfo.fieldalign = temp2;
    *pi = i;
    return( NOT_ERROR );
}
#endif

#if PROCALIGN
/* OPTION PROCALIGN:1|2|4|8|16|32 */

OPTFUNC( SetProcAlign )
/*********************/
{
    int i = *pi;
    int temp, temp2;
    struct expr opndx;

    if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) == ERROR )
        return( ERROR );
    if ( opndx.kind != EXPR_CONST ) {
        return( EmitError( CONSTANT_EXPECTED ) );
    }
    if( opndx.value > MAX_STRUCT_ALIGN ) {
        EmitError( STRUCT_ALIGN_TOO_HIGH );
    }
    for( temp = 1, temp2 = 0; temp < opndx.value ; temp <<= 1, temp2++ );
    if( temp != opndx.value ) {
        return( EmitErr( POWER_OF_2, opndx.value ) );
    }
    ModuleInfo.procalign = temp2;
    *pi = i;
    return( NOT_ERROR );
}
#endif

#if MZ_SUPPORT
OPTFUNC( SetMZ )
/**************/
{
    int i = *pi;
    int j;
    uint_16 *parms;
    struct expr opndx;

    for ( j = 0, parms = (uint_16 *)&ModuleInfo.mz_data ; j < 4; j++ ) {
        int k;
        for ( k = i; tokenarray[k].token != T_FINAL; k++ )
            if ( tokenarray[k].token == T_COMMA ||
                tokenarray[k].token == T_COLON ||
                tokenarray[k].token == T_DBL_COLON )
                break;
        if ( EvalOperand( &i, tokenarray, k, &opndx, 0 ) == ERROR )
            return( ERROR );
        if ( opndx.kind == EXPR_EMPTY ) {
        } else if ( opndx.kind == EXPR_CONST ) {
            if ( opndx.value64 > 0xFFFF ) {
                return( EmitConstError( &opndx ) );
            }
            if ( ModuleInfo.sub_format == SFORMAT_MZ )
                *(parms + j) = opndx.value;
        } else {
            return( EmitError( CONSTANT_EXPECTED ) );
        }
        if ( tokenarray[i].token == T_COLON )
            i++;
        else if ( tokenarray[i].token == T_DBL_COLON ) {
            i++;
            j++;
        }
    }

    /* ensure data integrity of the params */
    if ( ModuleInfo.sub_format == SFORMAT_MZ ) {
        if ( ModuleInfo.mz_data.ofs_fixups < 0x1E )
            ModuleInfo.mz_data.ofs_fixups = 0x1E;

        for( j = 16; j < ModuleInfo.mz_data.alignment; j <<= 1 );
        if( j != ModuleInfo.mz_data.alignment )
            EmitError( INVALID_HEADER_ALIGNMENT );

        if ( ModuleInfo.mz_data.heapmax < ModuleInfo.mz_data.heapmin )
            ModuleInfo.mz_data.heapmax = ModuleInfo.mz_data.heapmin;
    }
    *pi = i;
    return( NOT_ERROR );
}
#endif

#if AMD64_SUPPORT
/* OPTION FRAME: AUTO | NOAUTO
 * default is NOAUTO
 */
OPTFUNC( SetFrame )
/*****************/
{
    int i = *pi;

    if ( 0 == _stricmp( tokenarray[i].string_ptr, "AUTO" ) ) {
        ModuleInfo.frame_auto = 1;
        i++;
    } else if ( 0 == _stricmp( tokenarray[i].string_ptr, "NOAUTO" ) ) {
        ModuleInfo.frame_auto = 0;
        i++;
    }
    *pi = i;
    return( NOT_ERROR );
}
#endif

#if ELF_SUPPORT
OPTFUNC( SetElf )
/***************/
{
    int i = *pi;
    struct expr opndx;

    if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR )
        return( ERROR );
    if ( opndx.kind == EXPR_CONST ) {
        if ( opndx.llvalue > 0xFF ) {
            return( EmitConstError( &opndx ) );
        }
        if ( Options.output_format == OFORMAT_ELF )
            ModuleInfo.elf_osabi = opndx.value;
    } else {
        return( EmitError( CONSTANT_EXPECTED ) );
    }
    *pi = i;
    return( NOT_ERROR );
}
#endif

#if RENAMEKEY

/* OPTION RENAMEKEYWORD: <keyword>,new_name */

OPTFUNC( SetRenameKey )
/*********************/
{
    int i = *pi;
    //struct ReservedWord *resw;
    unsigned index;
    char *oldname;

#if 0 /* v2.11: allow temporary renaming of keywords */
    /* do nothing if pass > 1 */
    if( Parse_Pass != PASS_1 ) {
        SkipOption( pi, tokenarray );
        return( NOT_ERROR );
    }
#endif
    if ( tokenarray[i].token != T_STRING || tokenarray[i].string_delim != '<' )  {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].tokpos ) );
    }
    oldname = tokenarray[i].string_ptr;
    i++;
    /* v2.06: syntax changed */
    //if ( tokenarray[i].token != T_COMMA ) {
    if ( tokenarray[i].token != T_DIRECTIVE || tokenarray[i].dirtype != DRT_EQUALSGN ) {
        //EmitError( EXPECTING_COMMA );
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].tokpos ) );
    }
    i++;
    if ( tokenarray[i].token != T_ID )  {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].tokpos ) );
    }

    /* todo: if MAX_ID_LEN can be > 255, then check size,
     * since a reserved word's size must be <= 255 */
    index = FindResWord( oldname, strlen( oldname ) );
    if ( index == 0 ) {
        return( EmitError( RESERVED_WORD_EXPECTED ) );
    }
    RenameKeyword( index, tokenarray[i].string_ptr, strlen( tokenarray[i].string_ptr ) );
    i++;
    *pi = i;
    return( NOT_ERROR );
}
#endif

#if AMD64_SUPPORT
OPTFUNC( SetWin64 )
/*****************/
{
    int i = *pi;
    struct expr opndx;

    /* if -win64 isn't set, skip the option */
    /* v2.09: skip option if Ofssize != USE64 */
    if ( ModuleInfo.defOfssize != USE64 ) {
        SkipOption( pi, tokenarray );
        return( NOT_ERROR);
    }

    if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR )
        return( ERROR );
    if ( opndx.kind == EXPR_CONST ) {
        if ( opndx.llvalue & ( ~W64F_ALL ) ) {
            return( EmitConstError( &opndx ) );
        }
        ModuleInfo.win64_flags = opndx.value;
    } else {
        return( EmitError( CONSTANT_EXPECTED ) );
    }
    *pi = i;
    return( NOT_ERROR );
}
#endif

#if DLLIMPORT

static struct dll_desc *IncludeDll( const char *name )
/****************************************************/
{
    struct dll_desc **q;
    struct dll_desc *node;

    /* allow a zero-sized name! */
    if ( *name == NULLC )
        return( NULL );

    for ( q = &ModuleInfo.g.DllQueue; *q ; q = &(*q)->next ) {
        if ( _stricmp( (*q)->name, name ) == 0 )
            return( *q );
    }
    node = LclAlloc( sizeof( struct dll_desc ) + strlen( name ) );
    node->next = NULL;
    node->cnt = 0;
    strcpy( node->name, name );
    *q = node;

#if AMD64_SUPPORT
    ModuleInfo.g.imp_prefix = ( ( ModuleInfo.defOfssize == USE64 ) ? "__imp_" : "_imp_" );
#else
    ModuleInfo.g.imp_prefix = "_imp_";
#endif

    return( node );
}

OPTFUNC( SetDllImport )
/*********************/
{
    int i = *pi;

    /* used for COFF only */
    //if ( Options.output_format != OFORMAT_COFF ) {
    //    SkipOption( pi, tokenarray );
    //    return( NOT_ERROR);
    //}

    if ( tokenarray[i].token == T_ID &&
        ( _stricmp( tokenarray[i].string_ptr, "NONE" ) == 0 ) ) {
        ModuleInfo.CurrDll = NULL;
        i++;
    } else if ( tokenarray[i].token == T_STRING && tokenarray[i].string_delim == '<' ) {
        if ( Parse_Pass == PASS_1 )
            ModuleInfo.CurrDll = IncludeDll( tokenarray[i].string_ptr );
        i++;
    }
    *pi = i;
    return( NOT_ERROR );
}
#endif

#if CVOSUPP
OPTFUNC( SetCodeView )
/********************/
{
    int i = *pi;
    struct expr opnd;

    if ( EvalOperand( &i, tokenarray, Token_Count, &opnd, 0 ) == ERROR )
        return( ERROR );
    if ( opnd.kind == EXPR_CONST ) {
        ModuleInfo.cv_opt = opnd.value;
    } else {
        return( EmitError( CONSTANT_EXPECTED ) );
    }
    *pi = i;
    return( NOT_ERROR );
}
#endif

#if STACKBASESUPP

extern void UpdateStackBase( struct asym *, void * );
extern void UpdateProcStatus( struct asym *, void * );

OPTFUNC( SetStackBase )
/*********************/
{
    int i = *pi;

    if ( tokenarray[i].token != T_REG ) {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
    }
    if ( !( GetSflagsSp( tokenarray[i].tokval ) & SFR_IREG ) ) {
        return( EmitError( MUST_BE_INDEX_OR_BASE_REGISTER ) );
    }
    ModuleInfo.basereg[ModuleInfo.Ofssize] = tokenarray[i].tokval;
    if ( !ModuleInfo.g.StackBase ) {
        ModuleInfo.g.StackBase = CreateVariable( "@StackBase", 0 );
        ModuleInfo.g.StackBase->predefined = TRUE;
        ModuleInfo.g.StackBase->sfunc_ptr = UpdateStackBase;
        ModuleInfo.g.ProcStatus = CreateVariable( "@ProcStatus", 0 );
        ModuleInfo.g.ProcStatus->predefined = TRUE;
        ModuleInfo.g.ProcStatus->sfunc_ptr = UpdateProcStatus;
    }
    i++;
    *pi = i;
    return( NOT_ERROR );
}
#endif

OPTFUNC( Unsupported )
/********************/
{
    return( EmitErr( NOT_SUPPORTED, tokenarray[(*pi)-2].tokpos ) );
}

struct asm_option {
    const char *name;
    ret_code OPTQUAL (*func)(int *, struct asm_tok[] );
};

/* the table must be here after the option helper functions
 * to avoid having to define prototypes.
 * the options without arguments must come first!
 */
static const struct asm_option optiontab[] = {
    { "DOTNAME",      SetDotName     },
    { "NODOTNAME",    SetNoDotName   },
    { "M510",         SetM510        },
    { "NOM510",       SetNoM510      },
    { "SCOPED",       SetScoped      },
    { "NOSCOPED",     SetNoScoped    },
    { "OLDSTRUCTS",   SetOldStructs  },
    { "NOOLDSTRUCTS", SetNoOldStructs},
    { "EMULATOR",     SetEmulator    },
    { "NOEMULATOR",   SetNoEmulator  },
    { "LJMP",         SetLJmp        },
    { "NOLJMP",       SetNoLJmp      },
    { "READONLY",     Unsupported    },
    { "NOREADONLY",   SetNoReadonly  },
    { "OLDMACROS",    Unsupported    },
    { "NOOLDMACROS",  SetNoOldmacros },
    { "EXPR16",       Unsupported    },
    { "EXPR32",       SetExpr32      },
    { "NOSIGNEXTEND", SetNoSignExt   },
#define NOARGOPTS 19 /* number of options without arguments */
    { "CASEMAP",      SetCaseMap     }, /* CASEMAP:NONE|..   */
    { "PROC",         SetProc        }, /* PROC:PRIVATE|..   */
    { "PROLOGUE",     SetPrologue    }, /* PROLOGUE: <name>  */
    { "EPILOGUE",     SetEpilogue    }, /* EPILOGUE: <name>  */
    { "LANGUAGE",     SetLanguage    }, /* LANGUAGE: <name>  */
    { "NOKEYWORD",    SetNoKeyword   }, /* NOKEYWORD: <id>   */
    { "SETIF2",       SetSetIF2      }, /* SETIF2: <value>   */
    { "OFFSET",       SetOffset      }, /* OFFSET: GROUP|..  */
    { "SEGMENT",      SetSegment     }, /* SEGMENT: USE16|.. */
#define MASMOPTS 28 /* number of options compatible with Masm */
#if FIELDALIGN
    { "FIELDALIGN",   SetFieldAlign  }, /* FIELDALIGN: <value> */
#endif
#if PROCALIGN
    { "PROCALIGN",    SetProcAlign   }, /* PROCALIGN: <value> */
#endif
#if MZ_SUPPORT
    { "MZ",           SetMZ          }, /* MZ: <value>:<value>.. */
#endif
#if AMD64_SUPPORT
    { "FRAME",        SetFrame       }, /* FRAME: AUTO|.. */
#endif
#if ELF_SUPPORT
    { "ELF",          SetElf         }, /* ELF: <value> */
#endif
#if RENAMEKEY
    { "RENAMEKEYWORD",SetRenameKey   }, /* RENAMEKEYWORD: <id>=<> */
#endif
#if AMD64_SUPPORT
    { "WIN64",        SetWin64       }, /* WIN64: <value> */
#endif
#if DLLIMPORT
    { "DLLIMPORT",    SetDllImport   }, /* DLLIMPORT: <NONE|library> */
#endif
#if CVOSUPP
    { "CODEVIEW",     SetCodeView    }, /* CODEVIEW: <value> */
#endif
#if STACKBASESUPP
    { "STACKBASE",    SetStackBase   }, /* STACKBASE: <reg> */
#endif
};

#define TABITEMS sizeof( optiontab) / sizeof( optiontab[0] )

/* handle OPTION directive
 * syntax:
 * OPTION option[:value][,option[:value,...]]
 */
ret_code OptionDirective( int i, struct asm_tok tokenarray[] )
/************************************************************/
{
    int idx = -1;

    DebugMsg1(( "OPTION directive enter, option=%s\n", tokenarray[i+1].string_ptr ));

    i++; /* skip OPTION directive */
    while ( tokenarray[i].token != T_FINAL ) {
        _strupr( tokenarray[i].string_ptr );
        for ( idx = 0; idx < TABITEMS; idx++ ) {
            if ( 0 == strcmp( tokenarray[i].string_ptr, optiontab[idx].name ) )
                break;
        }
        if ( idx >= TABITEMS )
            break;
        i++;
        /* v2.06: check for colon separator here */
        if ( idx >= NOARGOPTS ) {
            if ( tokenarray[i].token != T_COLON ) {
                return( EmitError( COLON_EXPECTED ) );
            }
            i++;
            /* there must be something after the colon */
            if ( tokenarray[i].token == T_FINAL ) {
                i -= 2; /* position back to option identifier */
                break;
            }
            /* reject option if -Zne is set */
            if ( idx >= MASMOPTS && Options.strict_masm_compat ) {
                i -= 2;
                break;
            }
        }
        if ( optiontab[idx].func( &i, tokenarray ) == ERROR )
            return( ERROR );
        if ( tokenarray[i].token != T_COMMA )
            break;
        i++;
    }
    if ( idx >= TABITEMS  || tokenarray[i].token != T_FINAL ) {
        DebugMsg(( "option syntax error: >%s<\n", tokenarray[i].tokpos ));
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].tokpos ) );
    }
    return( NOT_ERROR );
}

