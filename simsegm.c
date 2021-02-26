/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:  Processing simplified segment directives:
*               - .CODE, .DATA, .DATA?, .CONST, .STACK, .FARDATA, .FARDATA?
****************************************************************************/

#include <ctype.h>

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "segment.h"
#include "lqueue.h"
#include "expreval.h"
#include "fastpass.h"
#include "listing.h"
#include "msgtext.h"
#include "tokenize.h"
#include "proc.h"
#include "cpumodel.h"
#include "equate.h"
#include "myassert.h"

#define DEFAULT_STACK_SIZE      1024

extern const char szDgroup[];

static char *SegmNames[ SIM_LAST ];

static const char * const SegmNamesDef[ SIM_LAST ] = {
    "_TEXT", "STACK", "_DATA", "_BSS", "FAR_DATA", "FAR_BSS", "CONST"
};
static const char * const SegmClass[ SIM_LAST ] = {
    "CODE", "STACK", "DATA", "BSS", "FAR_DATA", "FAR_BSS", "CONST"
};
static const char * const SegmCombine[ SIM_LAST ] = {
    "PUBLIC", "STACK", "PUBLIC", "PUBLIC", "PRIVATE", "PRIVATE", "PUBLIC"
};

char *SimGetSegName( enum sim_seg segno )
/***************************************/
{
	char* segn;
	segn = SegmNames[segno];
	if (segn == NULL && ModuleInfo.flat == TRUE)
		segn = "_flat";
    return( segn );
}

const char *GetCodeClass( void )
/******************************/
{
    /* option -nc set? */
    if ( Options.names[OPTN_CODE_CLASS] )
        return( Options.names[OPTN_CODE_CLASS] );

    return( SegmClass[SIM_CODE] );
}

/* emit DGROUP GROUP instruction */

static void AddToDgroup( enum sim_seg segm, const char *name )
/************************************************************/
{
    /* no DGROUP for FLAT or COFF/ELF */
    if( ModuleInfo.model == MODEL_FLAT
       || Options.output_format == OFORMAT_COFF
       || Options.output_format == OFORMAT_ELF)
        return;

    if( name == NULL )
        name = SegmNames[segm];

    AddLineQueueX( "%s %r %s", szDgroup, T_GROUP, name );
}

/* generate code to close the current segment */

static void close_currseg( void )
/*******************************/
{
    if ( CurrSeg ) {
        DebugMsg1(("close_currseg: current seg=%s\n", CurrSeg->sym.name));
        AddLineQueueX( "%s %r", CurrSeg->sym.name, T_ENDS );
    }
}

/* translate a simplified segment directive to
 * a standard segment directive line
 */

static void SetSimSeg( enum sim_seg segm, const char *name )
/**********************************************************/
{
    char *pAlign = "WORD";
    char *pAlignSt = "PARA";
    char *pUse = "";
	char align[16];
    struct asym *sym;
    const char *pFmt;
    const char *pClass;

	/* v2.34 /Sp[n] Set segment alignment */
	if (Options.seg_align != 4) 
	{
		sprintf(align, "ALIGN(%d)", (1 << Options.seg_align));
		pAlignSt = align;
	}

    if ( ModuleInfo.defOfssize > USE16 ) {
        if ( ModuleInfo.model == MODEL_FLAT )
            pUse = "FLAT";
        else
            pUse = "USE32";

		if (Options.seg_align != 4)
			pAlign = align;
		else if ((ModuleInfo.curr_cpu & P_CPU_MASK) <= P_386)
			pAlign = "DWORD";
		else
			pAlign = "PARA";
		pAlignSt = pAlign;
    }

    if ( segm == SIM_CODE )
        pClass = GetCodeClass();
    else
        pClass = SegmClass[segm];

    if ( segm == SIM_STACK || segm == SIM_FARDATA || segm == SIM_FARDATA_UN )
        pAlign = pAlignSt;

    pFmt = "%s %r %s %s %s '%s'";
    if ( name == NULL ) {
        name = SegmNames[segm];
		if (name == NULL && ModuleInfo.flat) name = "_flat";
		
		/* UASM 2.49 Prevent empty object with no options from crashing the assembler */
		if (name == NULL) name = "_TEXT";

        if ( ModuleInfo.simseg_init & ( 1 << segm ) )
            pFmt = "%s %r";
        else {
            ModuleInfo.simseg_init |= ( 1 << segm );
            /* v2.05: if segment exists already, use the current attribs.
             * This allows a better mix of full and simplified segment
             * directives. Masm behaves differently: the attributes
             * of the simplified segment directives have highest priority.
             */
            if ( Parse_Pass == PASS_1 ) {
				sym = SymSearch( name );
                if ( sym && sym->state == SYM_SEG && sym->isdefined == TRUE )
                    ModuleInfo.simseg_defd |= ( 1 << segm );
            }
            if ( ModuleInfo.simseg_defd & ( 1 << segm ) )
                pFmt = "%s %r";
        }
    } else {
        sym = SymSearch( name );
        /* v2.04: testing for state SYM_SEG isn't enough. The segment
         * might have been "defined" by a GROUP directive. Additional
         * check for segment's lname index is needed.
         * v2.12: check 'isdefined' member instead of 'lname_idx'
         */
        if ( sym && sym->state == SYM_SEG && sym->isdefined == TRUE )
            pFmt = "%s %r";
    }

	if (ModuleInfo.flat)
	{
		pUse = "USE64";
		pFmt = "%s %r %s %s %s '%s'";
		AddLineQueueX(pFmt, "_flat", T_SEGMENT, "BYTE", "USE16", "PUBLIC", "CODE");
		AddLineQueueX("assume cs:_flat, ds:_flat, es:_flat, ss:_flat, fs:_flat, gs:_flat");
		if (Parse_Pass == PASS_1)
		{
			sym_CodeSize = CreateVariable("@CodeSize", 0);
			sym_CodeSize->predefined = TRUE;
			sym_DataSize = CreateVariable("@DataSize", 0);
			sym_DataSize->predefined = TRUE;
			sym_ReservedStack = CreateVariable("@ReservedStack", 0);
			sym_ReservedStack->predefined = TRUE;
		}
		FStoreLine(0);
	}
	else
	{
		AddLineQueueX(pFmt, name, T_SEGMENT, pAlign, pUse, SegmCombine[segm], pClass);
	}
	
    return;
}

static void EndSimSeg( enum sim_seg segm )
/****************************************/
{
    AddLineQueueX( "%s %r", SegmNames[segm], T_ENDS );
    return;
}

ret_code SimplifiedSegDir( int i, struct asm_tok tokenarray[] )
/*************************************************************/
/*
 Handles simplified segment directives:
 .CODE, .STACK, .DATA, .DATA?, .FARDATA, .FARDATA?, .CONST
 */
{
    const char  *name = NULL;
    char        init;
    int         type;
    struct expr opndx;

    DebugMsg1(("SimplifiedSegDir(%s) enter\n", tokenarray[i].string_ptr ));

    if( ModuleInfo.model == MODEL_NONE ) {

		RewindToWin64();
        return( ERROR );
    }
	
	LstWrite(LSTTYPE_DIRECTIVE, 0, NULL);

    type = GetSflagsSp( tokenarray[i].tokval );
    i++; /* get past the directive token */

	/* UASM 2.50, Force .data to be same segment as .code for OPTION FLAT */
	/*if (ModuleInfo.flat == TRUE && type == SIM_DATA)
	{
		type = SIM_CODE;
	}*/

    if( type == SIM_STACK ) {
        if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR )
            return( ERROR );
        if( opndx.kind == EXPR_EMPTY )
            opndx.value = DEFAULT_STACK_SIZE;
        else if( opndx.kind != EXPR_CONST ) {
            EmitError( CONSTANT_EXPECTED );
            return( ERROR );
        }
    } else {
        /* Masm accepts a name argument for .CODE and .FARDATA[?] only.
         * Uasm also accepts this for .DATA[?] and .CONST unless
         * option -Zne is set.
         */
        if( tokenarray[i].token == T_ID &&
           ( type == SIM_CODE || type == SIM_FARDATA || type == SIM_FARDATA_UN
            || ( Options.strict_masm_compat == FALSE &&
                ( type == SIM_DATA || type == SIM_DATA_UN || type == SIM_CONST )))) {
            name = tokenarray[i].string_ptr;
            i++;
        }
    }
    if ( tokenarray[i].token != T_FINAL ) {
        EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr );
        return( ERROR );
    }

	if (type != SIM_STACK)
	{
		/* UASM 2.50 Don't close .CODE if trying to switch to .data for OPTION FLAT */
		//if (ModuleInfo.flat != TRUE ||
			//(ModuleInfo.flat == TRUE && type != SIM_DATA))
		//{
			close_currseg();  /* emit a "xxx ENDS" line to close current seg */
		//}
	}

    if ( name == NULL )
        init = ( ModuleInfo.simseg_init & ( 1 << type ) );

    switch( type ) {
    case SIM_CODE: /* .code */
        
		SetSimSeg( SIM_CODE, name );

        if( ModuleInfo.model == MODEL_TINY ) {
            /* v2.05: add the named code segment to DGROUP */
            if ( name )
                AddToDgroup( SIM_CODE, name );
            name = szDgroup;
        } else if( ModuleInfo.model == MODEL_FLAT ) {
            name = "FLAT";
        } else {
            if( name == NULL )
                name = SegmNames[SIM_CODE];
        }
        AddLineQueueX( "%r %r:%s", T_ASSUME, T_CS, name );
        break;
    case SIM_STACK: /* .stack */
        /* if code is generated which does "emit" bytes,
         * the original source line has to be saved.
         * v2.05: must not be done after LstWrite() has been called!
         * Also, there are no longer bytes "emitted".
         */
        SetSimSeg( SIM_STACK, NULL );
        AddLineQueueX( "ORG 0%xh", opndx.value );
        EndSimSeg( SIM_STACK );
        /* add stack to dgroup for some segmented models */
        if ( !init )
            if ( ModuleInfo.distance != STACK_FAR )
                AddToDgroup( SIM_STACK, NULL );
        break;
    case SIM_DATA:    /* .data  */
		/* UASM 2.50 in flat mode, .data does nothing */
		//if (ModuleInfo.flat != TRUE)
		//{
			SetSimSeg(type, name);
			AddLineQueueX("%r %r:ERROR", T_ASSUME, T_CS);
			if (name || (!init))
				AddToDgroup(type, name);
		//}
		break;
    case SIM_DATA_UN: /* .data? */

		/* UASM 2.49 Warn about BSS data in BIN, as the space won't be allocated */
		if (Options.output_format == OFORMAT_BIN && Options.sub_format != SFORMAT_PE && ModuleInfo.flat)
		{
			EmitWarn(2, UNINIT_DATA_IN_BIN);
		}

    case SIM_CONST:   /* .const */
        SetSimSeg( type, name );
        AddLineQueueX( "%r %r:ERROR", T_ASSUME, T_CS );
        if ( name || (!init) )
            AddToDgroup( type, name );
        break;
    case SIM_FARDATA:     /* .fardata  */
    case SIM_FARDATA_UN:  /* .fardata? */
        SetSimSeg( type, name );
        AddLineQueueX( "%r %r:ERROR", T_ASSUME, T_CS );
        break;
    default: /* shouldn't happen */
        /**/myassert( 0 );
        break;
    }

    RunLineQueue();

    return( NOT_ERROR );
}

/*
 * Set default values for .CODE and .DATA segment names.
 * Called by ModelDirective(), at Pass 1 only.
 */

void SetModelDefaultSegNames( void )
/**********************************/
{
    /* init segment names with default values */
    memcpy( SegmNames, SegmNamesDef, sizeof(SegmNames) );

    /* option -nt set? */
    if( Options.names[OPTN_TEXT_SEG] ) {
        SegmNames[SIM_CODE] = LclAlloc( strlen( Options.names[OPTN_TEXT_SEG] ) + 1 );
        strcpy( SegmNames[SIM_CODE], Options.names[OPTN_TEXT_SEG] );
    } else {
        if ( SIZE_CODEPTR & ( 1 << ModuleInfo.model ) ) {
            /* for some models, the code segment contains the module name */
            SegmNames[SIM_CODE] = LclAlloc( strlen( SegmNamesDef[SIM_CODE] ) + strlen( ModuleInfo.name ) + 1 );
            strcpy( SegmNames[SIM_CODE], ModuleInfo.name );
            strcat( SegmNames[SIM_CODE], SegmNamesDef[SIM_CODE] );
        }
    }

    /* option -nd set? */
    if ( Options.names[OPTN_DATA_SEG] ) {
        SegmNames[SIM_DATA] = LclAlloc( strlen( Options.names[OPTN_DATA_SEG] ) + 1 );
        strcpy( SegmNames[SIM_DATA], Options.names[OPTN_DATA_SEG] );
    }
    return;
}

/* Called by SetModel() [.MODEL directive].
 * Initializes simplified segment directives.
 * and the caller will run RunLineQueue() later.
 * Called for each pass.
 */
ret_code ModelSimSegmInit( int model )
/************************************/
{
    char buffer[20];

    ModuleInfo.simseg_init = 0; /* v2.09: reset init flags */
    /* v2.09: execute always, to make a proper listing if fastpass is off */

	/* create default code segment (_TEXT) */
    SetSimSeg( SIM_CODE, NULL );
    EndSimSeg( SIM_CODE );

    /* create default data segment (_DATA) */
    SetSimSeg( SIM_DATA, NULL ) ;
    EndSimSeg( SIM_DATA );

    /* create DGROUP for BIN/OMF if model isn't FLAT */
    if( model != MODEL_FLAT &&
        ( Options.output_format == OFORMAT_OMF
        || Options.output_format == OFORMAT_BIN)) {
        strcpy( buffer, "%s %r %s" );
        if( model == MODEL_TINY ) {
            strcat( buffer, ", %s" );
            AddLineQueueX( buffer, szDgroup, T_GROUP, SegmNames[SIM_CODE], SegmNames[SIM_DATA] );
        } else
            AddLineQueueX( buffer, szDgroup, T_GROUP, SegmNames[SIM_DATA] );
    }

    return( NOT_ERROR );
}

/* called when END has been found */
void ModelSimSegmExit( void )
/***************************/
{
    /* a model is set. Close current segment if one is open. */
    if ( CurrSeg ) {
        close_currseg();
        RunLineQueue();
    }
}
