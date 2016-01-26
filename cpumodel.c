/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:  processes .MODEL and cpu directives
*
****************************************************************************/

#include <ctype.h>

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "segment.h"
#include "assume.h"
#include "equate.h"
#include "lqueue.h"
#include "tokenize.h"
#include "expreval.h"
#include "fastpass.h"
#include "listing.h"
#include "proc.h"
#include "macro.h"
#include "fixup.h"
#ifdef DEBUG_OUT
#include "reswords.h"
#endif
#include "myassert.h"
#if PE_SUPPORT
#include "bin.h"
#endif

#define DOT_XMMARG 0 /* 1=optional argument for .XMM directive */

extern const char szDgroup[];

/* prototypes */

/* the following flags assume the MODEL_xxx enumeration.
 * must be sorted like MODEL_xxx enum:
 * TINY=1, SMALL=2, COMPACT=3, MEDIUM=4, LARGE=5, HUGE=6, FLAT=7
 */
const char * const ModelToken[] = {
    "TINY", "SMALL", "COMPACT", "MEDIUM", "LARGE", "HUGE", "FLAT" };

#define INIT_LANG       0x1
#define INIT_STACK      0x2
#define INIT_OS         0x4

struct typeinfo {
    uint_8 value;  /* value assigned to the token */
    uint_8 init;   /* kind of token */
};

static const char * const ModelAttr[] = {
    "NEARSTACK", "FARSTACK", "OS_OS2", "OS_DOS" };

static const struct typeinfo ModelAttrValue[] = {
    { STACK_NEAR,     INIT_STACK      },
    { STACK_FAR,      INIT_STACK      },
    { OPSYS_DOS,      INIT_OS         },
    { OPSYS_OS2,      INIT_OS         },
};

static struct asym *sym_CodeSize  ; /* numeric. requires model */
static struct asym *sym_DataSize  ; /* numeric. requires model */
static struct asym *sym_Model     ; /* numeric. requires model */
struct asym *sym_Interface ; /* numeric. requires model */
struct asym *sym_Cpu       ; /* numeric. This is ALWAYS set */

#if AMD64_SUPPORT
#if COFF_SUPPORT
const struct format_options coff64_fmtopt = { NULL, COFF64_DISALLOWED, "PE32+" };
#endif
#if ELF_SUPPORT
const struct format_options elf64_fmtopt  = { NULL, ELF64_DISALLOWED,  "ELF64" };
#endif
#endif

/* find token in a string table */

static int FindToken( const char *token, const char * const *table, int size )
/****************************************************************************/
{
    int i;
    for( i = 0; i < size; i++, table++ ) {
        if( _stricmp( *table, token ) == 0 ) {
            return( i );
        }
    }
    return( -1 );  /* Not found */
}

static struct asym *AddPredefinedConstant( const char *name, int value )
/**********************************************************************/
{
    struct asym *sym = CreateVariable( name, value );
    if (sym)
        sym->predefined = TRUE;
    return(sym);
}

/* set default wordsize for segment definitions */

static ret_code SetDefaultOfssize( int size )
/*******************************************/
{
    /* outside any segments? */
    if( CurrSeg == NULL ) {
        ModuleInfo.defOfssize = size;
    }
    return( SetOfssize() );
}

/* set memory model, called by ModelDirective()
 * also set predefined symbols:
 * - @CodeSize  (numeric)
 * - @code      (text)
 * - @DataSize  (numeric)
 * - @data      (text)
 * - @stack     (text)
 * - @Model     (numeric)
 * - @Interface (numeric)
 * inactive:
 * - @fardata   (text)
 * - @fardata?  (text)
 * Win64 only:
 * - @ReservedStack (numeric)
 */
static void SetModel( void )
/**************************/
{
    int         value;
    const char  *textvalue;
    //struct asym     *sym;

    DebugMsg1(("SetModel() enter (model=%u)\n", ModuleInfo.model ));
    /* if model is set, it disables OT_SEGMENT of -Zm switch */
    if ( ModuleInfo.model == MODEL_FLAT ) {
        ModuleInfo.offsettype = OT_FLAT;
#if AMD64_SUPPORT
        SetDefaultOfssize( ((ModuleInfo.curr_cpu & P_CPU_MASK) >= P_64 ) ? USE64 : USE32 );
        /* v2.03: if cpu is x64 and language is fastcall,
         * set fastcall type to win64.
         * This is rather hackish, but currently there's no other possibility
         * to enable the win64 ABI from the source.
         */
        if ( ( ModuleInfo.curr_cpu & P_CPU_MASK ) == P_64 )
            if ( ModuleInfo.langtype == LANG_FASTCALL ) {
                if ( Options.output_format != OFORMAT_ELF ) {
                    DebugMsg(("SetModel: FASTCALL type set to WIN64\n"));
                    ModuleInfo.fctype = FCT_WIN64;
                }
            }
#else
        SetDefaultOfssize( USE32 );
#endif
        /* v2.11: define symbol FLAT - after default offset size has been set! */
        DefineFlatGroup();
    } else
        ModuleInfo.offsettype = OT_GROUP;

    ModelSimSegmInit( ModuleInfo.model ); /* create segments in first pass */
    ModelAssumeInit();

    if ( ModuleInfo.list )
        LstWriteSrcLine();

    RunLineQueue();

    if ( Parse_Pass != PASS_1 )
        return;

    /* Set @CodeSize */
    if ( SIZE_CODEPTR & ( 1 << ModuleInfo.model ) ) {
        value = 1;
        /* v2.06: SimpleType[] is obsolete */
        //SimpleType[ST_PROC].mem_type = MT_FAR;
    } else {
        value = 0;
        // SimpleType[ST_PROC].mem_type = MT_NEAR; /* this is default */
    }
    sym_CodeSize = AddPredefinedConstant( "@CodeSize", value );
    AddPredefinedText( "@code", SimGetSegName( SIM_CODE ) );

    /* Set @DataSize */
    switch( ModuleInfo.model ) {
    case MODEL_COMPACT:
    case MODEL_LARGE:
        value = 1;
        break;
    case MODEL_HUGE:
        value = 2;
        break;
    default:
        value = 0;
        break;
    }
    sym_DataSize = AddPredefinedConstant( "@DataSize", value );

    textvalue = ( ModuleInfo.model == MODEL_FLAT ? "FLAT" : szDgroup );
    AddPredefinedText( "@data", textvalue );

    if ( ModuleInfo.distance == STACK_FAR )
        textvalue = "STACK";
    AddPredefinedText( "@stack", textvalue );

#if 0
    AddPredefinedText( "@fardata", ( ModuleInfo.model == MODEL_FLAT ? "FLAT" : SimGetSegName( SIM_FARDATA ) ) );
    AddPredefinedText( "@fardata?", ( ModuleInfo.model == MODEL_FLAT ? "FLAT" : SimGetSegName( SIM_FARDATA_UN ) ) );
#endif

    /* Set @Model and @Interface */

    sym_Model     = AddPredefinedConstant( "@Model", ModuleInfo.model );
    sym_Interface = AddPredefinedConstant( "@Interface", ModuleInfo.langtype );

#if AMD64_SUPPORT
    if ( ModuleInfo.defOfssize == USE64 && ModuleInfo.fctype == FCT_WIN64 ) {
        sym_ReservedStack = AddPredefinedConstant( "@ReservedStack", 0 );
    }
#endif
#if PE_SUPPORT
    if ( ModuleInfo.sub_format == SFORMAT_PE )
        pe_create_PE_header();
#endif

#ifdef DEBUG_OUT
    if ( Options.dump_reswords )
        DumpResWords();
#endif

}

/* handle .model directive
 * syntax: .MODEL <FLAT|TINY|SMALL...> [,<C|PASCAL|STDCALL...>][,<NEARSTACK|FARSTACK>][,<OS_DOS|OS_OS2>]
 * sets fields
 * - ModuleInfo.model
 * - ModuleInfo.language
 * - ModuleInfo.distance
 * - ModuleInfo.ostype
 * if model is FLAT, defines FLAT pseudo-group
 * set default segment names for code and data
 */
ret_code ModelDirective( int i, struct asm_tok tokenarray[] )
/***********************************************************/
{
    enum model_type model;
    enum lang_type language;
    enum dist_type distance;
    enum os_type ostype;
    int index;
    uint_8 init;
    uint_8 initv;

    DebugMsg1(("ModelDirective enter\n"));
    /* v2.03: it may occur that "code" is defined BEFORE the MODEL
     * directive (i.e. DB directives in AT-segments). For FASTPASS,
     * this may have caused errors because contents of the ModuleInfo
     * structure was saved before the .MODEL directive.
     */
    //if( Parse_Pass != PASS_1 ) {
    if( Parse_Pass != PASS_1 && ModuleInfo.model != MODEL_NONE ) {
        /* just set the model with SetModel() if pass is != 1.
         * This won't set the language ( which can be modified by
         * OPTION LANGUAGE directive ), but the language in ModuleInfo
         * isn't needed anymore once pass one is done.
         */
        SetModel();
        return( NOT_ERROR );
    }

    i++;
    if ( tokenarray[i].token == T_FINAL ) {
        return( EmitError( EXPECTED_MEMORY_MODEL ) );
    }
    /* get the model argument */
    index = FindToken( tokenarray[i].string_ptr, ModelToken, sizeof( ModelToken )/sizeof( ModelToken[0] ) );
    if( index >= 0 ) {
        if( ModuleInfo.model != MODEL_NONE ) {
            //if ( Parse_Pass == PASS_1 ) /* not needed, this code runs in pass one only */
            EmitWarn( 2, MODEL_DECLARED_ALREADY );
        }
        model = index + 1; /* model is one-base ( 0 is MODEL_NONE ) */
        i++;
    } else {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
    }

    /* get the optional arguments: language, stack distance, os */
    init = 0;
    while ( i < ( Token_Count - 1 ) && tokenarray[i].token == T_COMMA ) {
        i++;
        if ( tokenarray[i].token != T_COMMA ) {
            if ( GetLangType( &i, tokenarray, &language ) == NOT_ERROR ) {
                initv = INIT_LANG;
            } else {
                index = FindToken( tokenarray[i].string_ptr, ModelAttr, sizeof( ModelAttr )/sizeof( ModelAttr[0] ) );
                if ( index < 0 )
                    break;
                initv = ModelAttrValue[index].init;
                switch ( initv ) {
                case INIT_STACK:
                    if ( model == MODEL_FLAT ) {
                        return( EmitError( INVALID_MODEL_PARAM_FOR_FLAT ) );
                    }
                    distance = ModelAttrValue[index].value;
                    break;
                case INIT_OS:
                    ostype = ModelAttrValue[index].value;
                    break;
                }
                i++;
            }
            /* attribute set already? */
            if ( initv & init ) {
                i--;
                break;
            }
            init |= initv;
        }
    }
    /* everything parsed successfully? */
    if ( tokenarray[i].token != T_FINAL ) {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].tokpos ) );
    }

    if ( model == MODEL_FLAT ) {
        if ( ( ModuleInfo.curr_cpu & P_CPU_MASK) < P_386 ) {
            return( EmitError( INSTRUCTION_OR_REGISTER_NOT_ACCEPTED_IN_CURRENT_CPU_MODE ) );
        }
#if AMD64_SUPPORT
        if ( ( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_64 ) /* cpu 64-bit? */
            switch ( Options.output_format ) {
            case OFORMAT_COFF: ModuleInfo.fmtopt = &coff64_fmtopt; break;
            case OFORMAT_ELF:  ModuleInfo.fmtopt = &elf64_fmtopt;  break;
            };
#endif
        /* v2.11: define FLAT symbol is to early here, because defOfssize isn't set yet */
        //DefineFlatGroup();
    }

    ModuleInfo.model = model;
    if ( init & INIT_LANG )
        ModuleInfo.langtype = language;
    if ( init & INIT_STACK )
        ModuleInfo.distance = distance;
    if ( init & INIT_OS )
        ModuleInfo.ostype = ostype;

    SetModelDefaultSegNames();
    SetModel();

    return( NOT_ERROR );
}

/* set CPU and FPU parameter in ModuleInfo.cpu + ModuleInfo.curr_cpu.
 * ModuleInfo.cpu is the value of Masm's @CPU symbol.
 * ModuleInfo.curr_cpu is the old OW Wasm value.
 * additional notes:
 * .[1|2|3|4|5|6]86 will reset .MMX, .K3D and .XMM,
 * OTOH, .MMX/.XMM won't automatically enable .586/.686 ( Masm does! )
*/

ret_code SetCPU( enum cpu_info newcpu )
/*************************************/
{
    int temp;

    DebugMsg1(("SetCPU(%X) enter\n", newcpu ));
    if ( newcpu == P_86 || ( newcpu & P_CPU_MASK ) ) {
        /* reset CPU and EXT bits */
        ModuleInfo.curr_cpu &= ~( P_CPU_MASK | P_EXT_MASK | P_PM );

        /* set CPU bits */
        ModuleInfo.curr_cpu |= newcpu & ( P_CPU_MASK | P_PM );

        /* set default FPU bits if nothing is given and .NO87 not active */
        if ( (ModuleInfo.curr_cpu & P_FPU_MASK) != P_NO87 &&
            ( newcpu & P_FPU_MASK ) == 0 ) {
            ModuleInfo.curr_cpu &= ~P_FPU_MASK;
            if ( ( ModuleInfo.curr_cpu & P_CPU_MASK ) < P_286 )
                ModuleInfo.curr_cpu |= P_87;
            else if ( ( ModuleInfo.curr_cpu & P_CPU_MASK ) < P_386 )
                ModuleInfo.curr_cpu |= P_287;
            else
                ModuleInfo.curr_cpu |= P_387;
        }

    }
    if( newcpu & P_FPU_MASK ) {
        ModuleInfo.curr_cpu &= ~P_FPU_MASK;
        ModuleInfo.curr_cpu |= (newcpu & P_FPU_MASK);
    }
#if AMD64_SUPPORT
    /* enable MMX, K3D, SSEx for 64bit cpus */
    if ( ( newcpu & P_CPU_MASK ) == P_64 )
        ModuleInfo.curr_cpu |= P_EXT_ALL;
#endif
    if( newcpu & P_EXT_MASK ) {
        ModuleInfo.curr_cpu &= ~P_EXT_MASK;
        ModuleInfo.curr_cpu |= (newcpu & P_EXT_MASK);
    }

    /* set the Masm compatible @Cpu value */

    temp = ModuleInfo.curr_cpu & P_CPU_MASK;
    switch ( temp ) {
    case P_186: ModuleInfo.cpu = M_8086 | M_186; break;
    case P_286: ModuleInfo.cpu = M_8086 | M_186 | M_286; break;
    case P_386: ModuleInfo.cpu = M_8086 | M_186 | M_286 | M_386; break;
    case P_486: ModuleInfo.cpu = M_8086 | M_186 | M_286 | M_386 | M_486; break;
    case P_586: ModuleInfo.cpu = M_8086 | M_186 | M_286 | M_386 | M_486 | M_586; break;
    /* Masm's .686 directive doesn't set the Pentium flag! A bug? */
    //case P_686: ModuleInfo.cpu = M_8086 | M_186 | M_286 | M_386 | M_486 | M_586 | M_686; break;
#if AMD64_SUPPORT
    case P_64:
#endif
    case P_686: ModuleInfo.cpu = M_8086 | M_186 | M_286 | M_386 | M_486 | M_686; break;
    default: ModuleInfo.cpu = M_8086; break;
    }
    if ( ModuleInfo.curr_cpu & P_PM )
        ModuleInfo.cpu = ModuleInfo.cpu | M_PROT;

    temp = ModuleInfo.curr_cpu & P_FPU_MASK;
    switch (temp) {
    case P_87:  ModuleInfo.cpu = ModuleInfo.cpu | M_8087;     break;
    case P_287: ModuleInfo.cpu = ModuleInfo.cpu | M_8087 | M_287; break;
    case P_387: ModuleInfo.cpu = ModuleInfo.cpu | M_8087 | M_287 | M_387; break;
    }

    DebugMsg1(("SetCPU: ModuleInfo.curr_cpu=%X, @Cpu=%X\n", ModuleInfo.curr_cpu, ModuleInfo.cpu ));

    //MakeCPUConstant( newcpu );
    if ( ModuleInfo.model == MODEL_NONE )
#if AMD64_SUPPORT
        if ( ( ModuleInfo.curr_cpu & P_CPU_MASK) >= P_64 ) {
            SetDefaultOfssize( USE64 );
        } else
#endif
            SetDefaultOfssize( ((ModuleInfo.curr_cpu & P_CPU_MASK) >= P_386) ? USE32 : USE16 );

    /* Set @Cpu */
    /* differs from Codeinfo cpu setting */

    sym_Cpu = CreateVariable( "@Cpu", ModuleInfo.cpu );

    return( NOT_ERROR );
}

/* handles
 .8086,
 .[1|2|3|4|5|6]86[p],
 .8087,
 .[2|3]87,
 .NO87, .MMX, .K3D, .XMM directives.
*/
ret_code CpuDirective( int i, struct asm_tok tokenarray[] )
/*********************************************************/
{
    enum cpu_info newcpu;

    //newcpu = comp_opt( tokenarray[i].tokval );
    newcpu = GetSflagsSp( tokenarray[i].tokval );

#if DOT_XMMARG
    .if ( tokenarray[i].tokval == T_DOT_XMM && tokenarray[i+1].token != T_FINAL ) {
        struct expr opndx;
        i++;
        if ( EvalOperand( &i, Token_Count, &opndx, 0 ) == ERROR )
            return( ERROR );
        if ( opndx.kind != EXPR_CONST || opndx.value < 1 || opndx.value > 4 ) {
            return( EmitConstError( &opndx ) );
        }
        newcpy &= ~P_SSEALL; 
        switch ( opndx.value ) {
        case 4: newcpy |= P_SSE4;
        case 3: newcpy |= P_SSE3|P_SSSE3;
        case 2: newcpy |= P_SSE2;
        case 1: newcpy |= P_SSE1; break;
        }
    } else
#endif
    i++;

    if ( tokenarray[i].token != T_FINAL ) {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].tokpos ) );
    }

    return( SetCPU( newcpu ) );
}

