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
* Description:  Processing of segment and group related directives:
*               - SEGMENT, ENDS, GROUP
****************************************************************************/

#include <ctype.h>

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "reswords.h"
#include "segment.h"
#include "expreval.h"
#include "omf.h"
#include "omfspec.h"
#include "fastpass.h"
#include "coffspec.h"
#include "assume.h"
#include "listing.h"
#include "msgtext.h"
#include "types.h"
#include "fixup.h"

#include "myassert.h"

extern ret_code    EndstructDirective( int, struct asm_tok tokenarray[] );

//struct asym  symPC = { NULL,"$", 0 };  /* the '$' symbol */
struct asym  *symCurSeg;     /* @CurSeg symbol */

#define INIT_ATTR         0x01 /* READONLY attribute */
#define INIT_ALIGN        0x02 /* BYTE, WORD, PARA, DWORD, ... */
#define INIT_ALIGN_PARAM  (0x80 | INIT_ALIGN) /* ALIGN(x) */
#define INIT_COMBINE      0x04 /* PRIVATE, PUBLIC, STACK, COMMON */
#define INIT_COMBINE_AT   (0x80 | INIT_COMBINE) /* AT */
#if COMDATSUPP
#define INIT_COMBINE_COMDAT (0xC0 | INIT_COMBINE) /* COMDAT */
#endif
#define INIT_OFSSIZE      0x08 /* USE16, USE32, ... */
#define INIT_OFSSIZE_FLAT (0x80 | INIT_OFSSIZE) /* FLAT */
#define INIT_ALIAS        0x10 /* ALIAS(x) */
#define INIT_CHAR         0x20 /* DISCARD, SHARED, EXECUTE, ... */
#define INIT_CHAR_INFO    (0x80 | INIT_CHAR) /* INFO */

#define INIT_EXCL_MASK    0x1F  /* exclusive bits */

struct typeinfo {
    uint_8    value;      /* value assigned to the token */
    uint_8    init;       /* kind of token */
};

static const char * const SegAttrToken[] = {
#define sitem( text, value, init ) text,
#include "segattr.h"
#undef sitem
};
static const struct typeinfo SegAttrValue[] = {
#define sitem( text, value, init ) { value, init },
#include "segattr.h"
#undef sitem
};

static unsigned         grpdefidx;      /* Number of group definitions   */
static struct dsym      *SegStack[MAX_SEG_NESTING]; /* stack of open segments */
static int              stkindex;       /* current top of stack */

#if FASTPASS
/* saved state */
static struct dsym      *saved_CurrSeg;
static struct dsym      **saved_SegStack;
static int              saved_stkindex;
#endif

/* generic byte buffer, used for OMF LEDATA records only */
static uint_8           codebuf[ 1024 ];
static uint_32          buffer_size; /* total size of code buffer */

/* min cpu for USE16, USE32 and USE64 */
static const uint_16 min_cpu[] = { P_86, P_386,
#if AMD64_SUPPORT
P_64
#endif
};

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

/* set value of $ symbol */
void UpdateCurPC( struct asym *sym, void *p )
/*******************************************/
{
    if( CurrStruct ) {
        sym->mem_type = MT_EMPTY;
        sym->segment = NULL; 
        sym->offset = CurrStruct->sym.offset + (CurrStruct->next ? CurrStruct->next->sym.offset : 0);
    } else if ( CurrSeg ) { 
        sym->mem_type = MT_NEAR;
        sym->segment = (struct asym *)CurrSeg;
        sym->offset = GetCurrOffset();
    } else
        EmitErr( MUST_BE_IN_SEGMENT_BLOCK );
}

#if 0
/* value of text macros can't be set by internal function call yet! */
void SetCurSeg( struct asym *sym )
/********************************/
{
    symCurSeg->string_ptr = CurrSeg ? CurrSeg->sym.name : "";
    DebugMsg1(("SetCurSeg: curr value=>%s<\n", symCurSeg->string_ptr ));
}
#endif

#if 0 /* v2.09: obsolete */
/* find a class name.
 * those names aren't in the symbol table!
 */
char *GetLname( int idx )
/***********************/
{
    struct qnode    *node;
    struct asym     *sym;

    for( node = ModuleInfo.g.LnameQueue.head; node != NULL; node = node->next ) {
        sym = node->sym;
        if( sym->state == SYM_CLASS_LNAME && sym->class_lname_idx == idx ) {
            return( sym->name );
        }
    }
    return( "" );
}
#endif

static void AddLnameItem( struct asym *sym )
/******************************************/
{
    QAddItem( &ModuleInfo.g.LnameQueue, sym );
    return;

}

/* what's inserted into the LNAMES queue:
 * SYM_SEG: segment names
 * SYM_GRP: group names
 * SYM_CLASS_LNAME : class names
*/

static void FreeLnameQueue( void )
/********************************/
{
    struct qnode *curr;
    struct qnode *next;

    DebugMsg(("FreeLnameQueue enter\n" ));
    for( curr = ModuleInfo.g.LnameQueue.head; curr; curr = next ) {
        next = curr->next;
        /* the class name symbols are not part of the
         * symbol table and hence must be freed now.
         */
        if( curr->sym->state == SYM_CLASS_LNAME ) {
            SymFree( curr->sym );
        }
        LclFree( curr );
    }
    DebugMsg(("FreeLnameQueue exit\n" ));
}

/* set CS assume entry whenever current segment is changed.
 * Also updates values of text macro @CurSeg.
 */
void UpdateCurrSegVars( void )
/***********************************/
{
    struct assume_info *info;

    DebugMsg1(("UpdateCurrSegVars(%s)\n", CurrSeg ? CurrSeg->sym.name : "NULL" ));
    info = &(SegAssumeTable[ ASSUME_CS ]);
    if( CurrSeg == NULL ) {
        info->symbol = NULL;
        info->is_flat = FALSE;
        info->error = TRUE;
        symCurSeg->string_ptr = "";
    } else {
        info->is_flat = FALSE;
        info->error = FALSE;
        /* fixme: OPTION OFFSET:SEGMENT? */
        if( CurrSeg->e.seginfo->group != NULL ) {
            info->symbol = CurrSeg->e.seginfo->group;
            if ( info->symbol == &ModuleInfo.flat_grp->sym )
                info->is_flat = TRUE;
        } else {
            info->symbol = &CurrSeg->sym;
        }
        symCurSeg->string_ptr = CurrSeg->sym.name;
    }
    return;
}

void push_seg( struct dsym *seg )
/**************************************/
/* Push a segment into the current segment stack */
{
    if ( stkindex >= MAX_SEG_NESTING ) {
        EmitError( NESTING_LEVEL_TOO_DEEP );
        return;
    }
    SegStack[stkindex] = CurrSeg;
    stkindex++;
    CurrSeg = seg;
    UpdateCurrSegVars();
    return;
}

void pop_seg( void )
/*************************/
/* Pop a segment out of the current segment stack */
{
    //seg = popitem( &CurrSeg ); /* changed in v1.96 */
    /* it's already checked that CurrSeg is != NULL, so
     * stkindex must be > 0, but anyway ...
     */
    if ( stkindex ) {
        stkindex--;
        CurrSeg = SegStack[stkindex];
        UpdateCurrSegVars();
    }
    return;
}

uint_32 GetCurrOffset( void )
/***************************/
{
    return( CurrSeg ? CurrSeg->e.seginfo->current_loc : 0 );
}

#if 0
struct dsym *GetCurrSeg( void )
/*****************************/
{
    return( CurrSeg );
}
#endif

#if 0
int GetCurrClass( void )
/***********************/
{
    if( CurrSeg == NULL )
        return( 0 );
    return( CurrSeg->e.seginfo->segrec->d.segdef.class_name_idx );
}
#endif

uint_32 GetCurrSegAlign( void )
/*****************************/
{
    if( CurrSeg == NULL )
        return( 0 );
    if ( CurrSeg->e.seginfo->alignment == MAX_SEGALIGNMENT ) /* ABS? */
        return( 0x40 ); /* assume PARA alignment for AT segments */
    return( 1 << CurrSeg->e.seginfo->alignment );
}

static struct dsym *CreateGroup( const char *name )
/*************************************************/
{
    struct dsym    *grp;

    grp = (struct dsym *)SymSearch( name );

    if( grp == NULL || grp->sym.state == SYM_UNDEFINED ) {
        if ( grp == NULL )
            grp = (struct dsym *)SymCreate( name );
        else
            sym_remove_table( &SymTables[TAB_UNDEF], grp );

        grp->sym.state = SYM_GRP;
        grp->e.grpinfo = LclAlloc( sizeof( struct grp_info ) );
        grp->e.grpinfo->seglist = NULL;
        grp->e.grpinfo->numseg = 0;
        sym_add_table( &SymTables[TAB_GRP], grp );

        grp->sym.list = TRUE;
        grp->e.grpinfo->grp_idx = ++grpdefidx;
        AddLnameItem( &grp->sym );
    } else if( grp->sym.state != SYM_GRP ) {
        EmitErr( SYMBOL_REDEFINITION, name );
        return( NULL );
    }
    grp->sym.isdefined = TRUE;
    return( grp );
}

static struct dsym *CreateSegment( struct dsym *seg, const char *name, bool add_global )
/**************************************************************************************/
{
    if ( seg == NULL )
        seg = ( add_global ? (struct dsym *)SymCreate( name ) : (struct dsym *)SymAlloc( name ) );
    else if ( seg->sym.state == SYM_UNDEFINED )
        sym_remove_table( &SymTables[TAB_UNDEF], seg );

    if ( seg ) {
        seg->sym.state = SYM_SEG;
        seg->e.seginfo = LclAlloc( sizeof( struct seg_info ) );
        memset( seg->e.seginfo, 0, sizeof( struct seg_info ) );
        seg->e.seginfo->Ofssize = ModuleInfo.defOfssize;
        seg->e.seginfo->alignment = 4; /* this is PARA (2^4) */
        seg->e.seginfo->combine = COMB_INVALID;
        /* null class name, in case none is mentioned */
        seg->next = NULL;
        /* don't use sym_add_table(). Thus the "prev" member
         * becomes free for another use.
         */
        if ( SymTables[TAB_SEG].head == NULL )
            SymTables[TAB_SEG].head = SymTables[TAB_SEG].tail = seg;
        else {
            SymTables[TAB_SEG].tail->next = seg;
            SymTables[TAB_SEG].tail = seg;
        }
    }
    return( seg );
}

void DeleteGroup( struct dsym *dir )
/**********************************/
{
#if FASTMEM==0 || defined(DEBUG_OUT)
    struct seg_item    *curr;
    struct seg_item    *next;

    for( curr = dir->e.grpinfo->seglist; curr; curr = next ) {
        next = curr->next;
        DebugMsg(("DeleteGroup(%s): free seg_item=%p\n", dir->sym.name, curr ));
        LclFree( curr );
    }
#endif
    DebugMsg(("DeleteGroup(%s): extension %p will be freed\n", dir->sym.name, dir->e.grpinfo ));
    LclFree( dir->e.grpinfo );
    return;
}

/* handle GROUP directive */
ret_code GrpDir( int i, struct asm_tok tokenarray[] )
/***************************************************/
{
    char        *name;
    struct dsym *grp;
    struct dsym *seg;

    /* GROUP directive must be at pos 1, needs a name at pos 0 */
    if( i != 1 ) {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
    }
    /* GROUP isn't valid for COFF/ELF/BIN-PE */
#if COFF_SUPPORT || ELF_SUPPORT || PE_SUPPORT
    if ( Options.output_format == OFORMAT_COFF
#if ELF_SUPPORT
        || Options.output_format == OFORMAT_ELF
#endif
#if PE_SUPPORT
        || ( Options.output_format == OFORMAT_BIN && ModuleInfo.sub_format == SFORMAT_PE )
#endif
       ) {
        return( EmitErr( NOT_SUPPORTED_WITH_CURR_FORMAT, _strupr( tokenarray[i].string_ptr ) ) );
    }
#endif
    grp = CreateGroup( tokenarray[0].string_ptr );
    if( grp == NULL )
        return( ERROR );

    i++; /* go past GROUP */

    do {

        /* get segment name */
        if ( tokenarray[i].token != T_ID ) {
            return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
        }
        name = tokenarray[i].string_ptr;
        i++;

        seg = (struct dsym *)SymSearch( name );
        if ( Parse_Pass == PASS_1 ) {
            if( seg == NULL || seg->sym.state == SYM_UNDEFINED ) {
                seg = CreateSegment( seg, name, TRUE );
                /* inherit the offset magnitude from the group */
                if ( grp->e.grpinfo->seglist )
                    seg->e.seginfo->Ofssize = grp->sym.Ofssize;
            } else if( seg->sym.state != SYM_SEG ) {
                return( EmitErr( SEGMENT_EXPECTED, name ) );
            } else if( seg->e.seginfo->group != NULL &&
                      /* v2.09: allow segments in FLAT magic group be moved to a "real" group */
                      seg->e.seginfo->group != &ModuleInfo.flat_grp->sym &&
                      seg->e.seginfo->group != &grp->sym ) {
                /* segment is in another group */
                DebugMsg(("GrpDir: segment >%s< is in group >%s< already\n", name, seg->e.seginfo->group->name));
                return( EmitErr( SEGMENT_IN_ANOTHER_GROUP, name ) );
            }
            /* the first segment will define the group's word size */
            if( grp->e.grpinfo->seglist == NULL ) {
                grp->sym.Ofssize = seg->e.seginfo->Ofssize;
            } else if ( grp->sym.Ofssize != seg->e.seginfo->Ofssize ) {
                return( EmitErr( GROUP_SEGMENT_SIZE_CONFLICT, grp->sym.name, seg->sym.name ) );
            }
        } else {
            /* v2.04: don't check the "defined" flag in passes > 1. It's for IFDEF only! */
            //if( seg == NULL || seg->sym.state != SYM_SEG || seg->sym.defined == FALSE ) {
            /* v2.07: check the "segment" field instead of "defined" flag! */
            //if( seg == NULL || seg->sym.state != SYM_SEG ) {
            if( seg == NULL || seg->sym.state != SYM_SEG || seg->sym.segment == NULL ) {
                return( EmitErr( SEGMENT_NOT_DEFINED, name ) );
            }
        }

        /* insert segment in group if it's not there already */
        if ( seg->e.seginfo->group == NULL ) {
            struct seg_item    *si;

            /* set the segment's grp */
            seg->e.seginfo->group = &grp->sym;

            si = LclAlloc( sizeof( struct seg_item ) );
            si->seg = seg;
            si->next = NULL;
            grp->e.grpinfo->numseg++;

            /* insert the segment at the end of linked list */
            if( grp->e.grpinfo->seglist == NULL ) {
                grp->e.grpinfo->seglist = si;
            } else {
                struct seg_item *curr;
                curr = grp->e.grpinfo->seglist;
                while( curr->next != NULL ) {
                    curr = curr->next;
                }
                curr->next = si;
            }
        }

        if ( i < Token_Count ) {
            if ( tokenarray[i].token != T_COMMA || tokenarray[i+1].token == T_FINAL ) {
                return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].tokpos ) );
            }
            i++;
        }

    } while ( i < Token_Count );

    return( NOT_ERROR );
}

/* get/set value of predefined symbol @WordSize */
void UpdateWordSize( struct asym *sym, void *p )
/**********************************************/
{
    sym->value = CurrWordSize;
    return;
}

/* called by SEGMENT and ENDS directives */
ret_code SetOfssize( void )
/*************************/
{
    if( CurrSeg == NULL ) {
        ModuleInfo.Ofssize = ModuleInfo.defOfssize;
    } else {
        ModuleInfo.Ofssize = CurrSeg->e.seginfo->Ofssize;
        if( (uint_8)ModuleInfo.curr_cpu < min_cpu[ModuleInfo.Ofssize] ) {
            DebugMsg(("SetOfssize, error: CurrSeg=%s, ModuleInfo.Ofssize=%u, curr_cpu=%X, defOfssize=%u\n",
                      CurrSeg->sym.name, ModuleInfo.Ofssize, ModuleInfo.curr_cpu, ModuleInfo.defOfssize ));
            return( EmitErr( INCOMPATIBLE_CPU_MODE_FOR_XXBIT_SEGMENT, 16 << ModuleInfo.Ofssize ) );
        }
    }
    DebugMsg1(("SetOfssize: ModuleInfo.Ofssize=%u\n", ModuleInfo.Ofssize ));

    CurrWordSize = (2 << ModuleInfo.Ofssize);

#if AMD64_SUPPORT
    Set64Bit( ModuleInfo.Ofssize == USE64 );
#endif

    return( NOT_ERROR );
}

/* close segment */
static ret_code CloseSeg( const char *name )
/******************************************/
{
    if( CurrSeg == NULL || ( SymCmpFunc( CurrSeg->sym.name, name, CurrSeg->sym.name_size ) != 0 ) ) {
        DebugMsg(("CloseSeg(%s): nesting error, CurrSeg=%s\n", name, CurrSeg ? CurrSeg->sym.name : "(null)" ));
        return( EmitErr( BLOCK_NESTING_ERROR, name ) );
    }

    DebugMsg1(("CloseSeg(%s): current ofs=%" I32_SPEC "X\n", name, CurrSeg->e.seginfo->current_loc));

    if ( write_to_file && ( Options.output_format == OFORMAT_OMF ) ) {
        omf_FlushCurrSeg();
        if ( Options.no_comment_data_in_code_records == FALSE )
            omf_OutSelect( FALSE );
    }

    pop_seg();

    return( NOT_ERROR );
}

void DefineFlatGroup( void )
/**************************/
{
    if( ModuleInfo.flat_grp == NULL ) {
        /* can't fail because <FLAT> is a reserved word */
        ModuleInfo.flat_grp = CreateGroup( "FLAT" );
        ModuleInfo.flat_grp->sym.Ofssize = ModuleInfo.defOfssize;
        DebugMsg1(("DefineFlatGroup(): Ofssize=%u\n", ModuleInfo.flat_grp->sym.Ofssize ));
    }
    ModuleInfo.flat_grp->sym.isdefined = TRUE; /* v2.09 */
}

unsigned GetSegIdx( const struct asym *sym )
/******************************************/
/* get idx to sym's segment */
{
    if( sym )
        return( ((struct dsym *)sym)->e.seginfo->seg_idx );
    return( 0 );
}

struct asym *GetGroup( const struct asym *sym )
/*********************************************/
/* get a symbol's group */
{
    struct dsym  *curr;

    curr = GetSegm( sym );
    if( curr != NULL )
        return( curr->e.seginfo->group );
    return( NULL );
}

int GetSymOfssize( const struct asym *sym )
/*****************************************/
/* get sym's offset size (64=2, 32=1, 16=0) */
{
    struct dsym   *curr;

    curr = GetSegm( sym );
    if( curr == NULL ) {
        if( sym->state == SYM_EXTERNAL )
            return( sym->seg_ofssize );
        if( sym->state == SYM_STACK || sym->state == SYM_GRP )
            return( sym->Ofssize );
        if( sym->state == SYM_SEG  )
            return( ((struct dsym *)sym)->e.seginfo->Ofssize );
        if ( sym->mem_type == MT_EMPTY )
            return( USE16 );
    } else {
        return( curr->e.seginfo->Ofssize );
    }
    return( ModuleInfo.Ofssize );
}

void SetSymSegOfs( struct asym *sym )
/***********************************/
{
    sym->segment = &CurrSeg->sym;
    sym->offset = GetCurrOffset();
}

/* get segment type from alignment, combine type or class name */
enum seg_type TypeFromClassName( const struct dsym *seg, const struct asym *clname )
/**********************************************************************************/
{
    int     slen;
    char    uname[MAX_ID_LEN+1];

    if ( seg->e.seginfo->alignment == MAX_SEGALIGNMENT )
        return( SEGTYPE_ABS );

    if ( seg->e.seginfo->combine == COMB_STACK )
        return( SEGTYPE_STACK );

    if( clname == NULL )
        return( SEGTYPE_UNDEF );

    if( _stricmp( clname->name, GetCodeClass() ) == 0 )
        return( SEGTYPE_CODE );

    slen = clname->name_size;
    memcpy( uname, clname->name, clname->name_size + 1 );
    _strupr( uname );
    switch( slen ) {
    default:
    case 5:
        if( memcmp( uname, "CONST", 6 ) == 0 )
            return( SEGTYPE_DATA );
        if( memcmp( uname, "DBTYP", 6 ) == 0 )
            return( SEGTYPE_DATA );
        if( memcmp( uname, "DBSYM", 6 ) == 0 )
            return( SEGTYPE_DATA );
    case 4:
        if( memcmp( uname + slen - 4, "CODE", 4 ) == 0 )
            return( SEGTYPE_CODE );
        if( memcmp( uname + slen - 4, "DATA", 4 ) == 0 )
            return( SEGTYPE_DATA );
    case 3:
        if( memcmp( uname + slen - 3, "BSS", 3 ) == 0 )
            return( SEGTYPE_BSS );
    case 2:
    case 1:
    case 0:
        return( SEGTYPE_UNDEF );
    }
}

/* search a class item by name.
 * the classes aren't stored in the symbol table!
 */
static struct asym *FindClass( const char *name, int len )
/********************************************************/
{
    struct qnode    *node;

    for( node = ModuleInfo.g.LnameQueue.head; node; node = node->next ) {
        struct asym *sym = node->sym;
        if( sym->state == SYM_CLASS_LNAME && ( SymCmpFunc( sym->name, name, len ) == 0 ) )
            return( sym );
    }
    return( NULL );
}

/* add a class name to the lname queue
 * if it doesn't exist yet.
 */
static struct asym *CreateClassLname( const char *name )
/******************************************************/
{
    struct asym *sym;
    int len = strlen( name );

    /* max lname is 255 - this is an OMF restriction */
    if( len > MAX_LNAME ) {
        EmitError( CLASS_NAME_TOO_LONG );
        return( NULL );
    }

    if ( !( sym = FindClass( name, len ) ) ) {
        /* the classes aren't inserted into the symbol table but they are in a queue */
        sym = SymAlloc( name );
        sym->state = SYM_CLASS_LNAME;
        /* sym->class_lname_idx = */ AddLnameItem( sym ); /* index needed by OMF only */
    }

    return( sym );
}

/* set the segment's class. report an error if the class has been set
 * already and the new value differs. */

static ret_code SetSegmentClass( struct dsym *seg, const char *name )
/*******************************************************************/
{
    struct asym *clsym;

    clsym = CreateClassLname( name );
    if( clsym == NULL ) {
        return( ERROR );
    }
#if 0 /* v2.09: Masm allows a segment's class name to change */
    if ( seg->e.seginfo->clsym == NULL )
        seg->e.seginfo->clsym = clsym;
    else if ( seg->e.seginfo->clsym != clsym ) {
        return( EmitErr( SEGDEF_CHANGED, seg->sym.name, MsgGetEx( TXT_CLASS ) ) );
    }
#else
    seg->e.seginfo->clsym = clsym;
#endif
    return( NOT_ERROR );
}

/* CreateIntSegment(), used for internally defined segments:
 * codeview debugging segments, COFF .drectve, COFF .sxdata
 */
struct asym *CreateIntSegment( const char *name, const char *classname, uint_8 alignment, uint_8 Ofssize, bool add_global )
/*************************************************************************************************************************/
{
    struct dsym *seg;
    if ( add_global ) {
        seg = (struct dsym *)SymSearch( name );
        if ( seg == NULL || seg->sym.state == SYM_UNDEFINED )
            seg = CreateSegment( seg, name, add_global );
        else if ( seg->sym.state != SYM_SEG ) {
            EmitErr( SYMBOL_REDEFINITION, name );
            return( NULL );
        }
    } else
        seg = CreateSegment( NULL, name, FALSE );
    if ( seg ) {
        if( seg->sym.isdefined == FALSE ) {
            seg->e.seginfo->seg_idx = ++ModuleInfo.g.num_segs;
            AddLnameItem( &seg->sym );
            seg->sym.isdefined = TRUE; 
        }
        seg->e.seginfo->internal = TRUE; /* segment has private buffer */
        seg->sym.segment = &seg->sym;
        seg->e.seginfo->alignment = alignment;
        seg->e.seginfo->Ofssize = Ofssize;
        SetSegmentClass( seg, classname );
        return( &seg->sym );
    }
    return( NULL );
}

/* ENDS directive */
ret_code EndsDir( int i, struct asm_tok tokenarray[] )
/****************************************************/
{
    if( CurrStruct != NULL ) {
        return( EndstructDirective( i, tokenarray ) );
    }
    /* a label must precede ENDS */
    if( i != 1 ) {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
    }
    if ( Parse_Pass != PASS_1 ) {
        if ( ModuleInfo.list )
            LstWrite( LSTTYPE_LABEL, 0, NULL );
    }
    if ( CloseSeg( tokenarray[0].string_ptr ) == ERROR )
        return( ERROR );
    i++;
    if ( tokenarray[i].token != T_FINAL ) {
        EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr );
    }
    return( SetOfssize() );
}

/* SEGMENT directive if pass is > 1 */
static ret_code SetCurrSeg( int i, struct asm_tok tokenarray[] )
/**************************************************************/
{
    struct asym *sym;

    sym = SymSearch( tokenarray[0].string_ptr );
    DebugMsg1(("SetCurrSeg(%s) sym=%p\n", tokenarray[0].string_ptr, sym));
    if ( sym == NULL || sym->state != SYM_SEG ) {
        return( EmitErr( SEGMENT_NOT_DEFINED, tokenarray[0].string_ptr ) );
    }

    sym->isdefined = TRUE;
    if ( CurrSeg && Options.output_format == OFORMAT_OMF ) {
        omf_FlushCurrSeg();
        if ( Options.no_comment_data_in_code_records == FALSE )
            omf_OutSelect( FALSE );
    }
    push_seg( (struct dsym *)sym );

    if ( ModuleInfo.list )
        LstWrite( LSTTYPE_LABEL, 0, NULL );

    return( SetOfssize() );
}

static void UnlinkSeg( struct dsym *dir )
/***************************************/
{
    struct dsym *curr;
    struct dsym *prev;
    for ( curr = SymTables[TAB_SEG].head, prev = NULL; curr; prev = curr, curr = curr->next )
        if ( curr == dir ) {
            /* if segment is first, set a new head */
            if ( prev == NULL )
                SymTables[TAB_SEG].head = curr->next;
            else
                prev->next = curr->next;

            /* if segment is last, set a new tail */
            if ( curr->next == NULL )
                SymTables[TAB_SEG].tail = prev;
            break;
        }
    return;
}

/* SEGMENT directive */
ret_code SegmentDir( int i, struct asm_tok tokenarray[] )
/*******************************************************/
{
    char                is_old = FALSE;
    char                *token;
    int                 typeidx;
    const struct typeinfo *type;          /* type of option */
    int                 temp;
    int                 temp2;
    unsigned            initstate = 0;  /* flags for attribute initialization */
    unsigned char       oldOfssize;
    char                oldalign;
    char                oldcombine;
    uint_8              newcharacteristics = 0;
    struct dsym         *dir;
    char                *name;
    struct asym         *sym;
    struct expr         opndx;

    if ( Parse_Pass != PASS_1 )
        return( SetCurrSeg( i, tokenarray ) );

    if( i != 1 ) {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
    }

    name = tokenarray[0].string_ptr;

    /* See if the segment is already defined */
    sym = SymSearch( name );
    if( sym == NULL || sym->state == SYM_UNDEFINED ) {

        /* segment is not defined (yet) */
        sym = (struct asym *)CreateSegment( (struct dsym *)sym, name, TRUE );
        sym->list = TRUE; /* always list segments */
        dir = (struct dsym *)sym;
        /* v2.12: seg_idx member now set AFTER parsing is done */
    } else if ( sym->state == SYM_SEG ) { /* segment already defined? */
        
        dir = (struct dsym *)sym;
        /* v2.12: check 'isdefined' instead of lname_idx */
        if( sym->isdefined == FALSE ) {
            /* segment was forward referenced (in a GROUP directive), but not really set up */
            /* the segment list is to be sorted.
             * So unlink the segment and add it at the end.
             */
            UnlinkSeg( dir );
            dir->next = NULL;
            if ( SymTables[TAB_SEG].head == NULL )
                SymTables[TAB_SEG].head = SymTables[TAB_SEG].tail = dir;
            else {
                SymTables[TAB_SEG].tail->next = dir;
                SymTables[TAB_SEG].tail = dir;
            }
        } else {
            is_old = TRUE;
            oldOfssize  = dir->e.seginfo->Ofssize;
            oldalign    = dir->e.seginfo->alignment;
            oldcombine  = dir->e.seginfo->combine;
        }

    } else {
        /* symbol is different kind, error */
        return( EmitErr( SYMBOL_REDEFINITION, name ) );
    }

    i++; /* go past SEGMENT */

    for( ; i < Token_Count; i++ ) {
        token = tokenarray[i].string_ptr;
        DebugMsg1(("SegmentDir(%s): i=%u, string=%s token=%X\n", name, i, token, tokenarray[i].token ));
        if( tokenarray[i].token == T_STRING ) {

            /* the class name - the only token which is of type STRING */
            /* string must be delimited by [double]quotes */
            if ( tokenarray[i].string_delim != '"' &&
                tokenarray[i].string_delim != '\'' ) {
                EmitErr( SYNTAX_ERROR_EX, token );
                continue;
            }
            /* remove the quote delimiters */
            token++;
            *(token+tokenarray[i].stringlen) = NULLC;

            SetSegmentClass( dir, token );

            DebugMsg1(("SegmentDir(%s): class found: %s\n", name, token ));
            continue;
        }

        /* check the rest of segment attributes.
         */
        typeidx = FindToken( token, SegAttrToken, sizeof( SegAttrToken )/sizeof( SegAttrToken[0] ) );
        if( typeidx < 0 ) {
            EmitErr( UNKNOWN_SEGMENT_ATTRIBUTE, token );
            continue;
        }
        type = &SegAttrValue[typeidx];

        /* initstate is used to check if any field is already
         * initialized
         */
        if( initstate & INIT_EXCL_MASK & type->init ) {
            EmitErr( SEGMENT_ATTRIBUTE_DEFINED_ALREADY, token );
            continue;
        } else {
            initstate |= type->init; /* mark it initialized */
        }

        switch ( type->init ) {
        case INIT_ATTR:
            dir->e.seginfo->readonly = TRUE;
            break;
        case INIT_ALIGN:
            DebugMsg1(("SegmentDir(%s): align attribute found\n", name ));
            dir->e.seginfo->alignment = type->value;
            break;
        case INIT_ALIGN_PARAM:
            DebugMsg1(("SegmentDir(%s): ALIGN() found\n", name ));
            if ( Options.output_format == OFORMAT_OMF ) {
                EmitErr( NOT_SUPPORTED_WITH_OMF_FORMAT, tokenarray[i].string_ptr );
                i = Token_Count; /* stop further parsing of this line */
                break;
            }
            i++;
            if ( tokenarray[i].token != T_OP_BRACKET ) {
                EmitErr( EXPECTED, "(" );
                break;
            }
            i++;
            if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR )
                break;
            if ( tokenarray[i].token != T_CL_BRACKET ) {
                EmitErr( EXPECTED, ")" );
                break;
            }
            if ( opndx.kind != EXPR_CONST ) {
                EmitError( CONSTANT_EXPECTED );
                break;
            }
            /*
             COFF allows alignment values
             1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192
             */
            for( temp = 1, temp2 = 0; temp < opndx.value && temp < 8192 ; temp <<= 1, temp2++ );
            if( temp != opndx.value ) {
                EmitErr( POWER_OF_2, opndx.value );
            }
            dir->e.seginfo->alignment = temp2;
            break;
        case INIT_COMBINE:
            DebugMsg1(("SegmentDir(%s): combine attribute found\n", name ));
            dir->e.seginfo->combine = type->value;
            break;
        case INIT_COMBINE_AT:
            DebugMsg1(("SegmentDir(%s): AT found\n", name ));
            dir->e.seginfo->combine = type->value;
            /* v2.05: always use MAX_SEGALIGNMENT */
            dir->e.seginfo->alignment = MAX_SEGALIGNMENT;
            i++;
            if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) != ERROR ) {
                if ( opndx.kind == EXPR_CONST ) {
                    dir->e.seginfo->abs_frame = opndx.value;
                    dir->e.seginfo->abs_offset = 0;
                } else {
                    EmitError( CONSTANT_EXPECTED );
                }
            }
            break;
#if COMDATSUPP
        case INIT_COMBINE_COMDAT:
            DebugMsg1(("SegmentDir(%s): COMDAT found\n", name ));
            /* v2.12: COMDAT supported by OMF */
            if ( Options.output_format != OFORMAT_COFF && Options.output_format != OFORMAT_OMF ) {
                EmitErr( NOT_SUPPORTED_WITH_CURR_FORMAT, tokenarray[i].string_ptr );
                i = Token_Count; /* stop further parsing of this line */
                break;
            }
            i++;
            if ( tokenarray[i].token != T_OP_BRACKET ) {
                EmitErr( EXPECTED, "(" );
                break;
            }
            i++;
            if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR )
                break;
            if ( opndx.kind != EXPR_CONST ) {
                EmitError( CONSTANT_EXPECTED );
                i = Token_Count; /* stop further parsing of this line */
                break;
            }
            if ( opndx.value < 1 || opndx.value > 6 ) {
                EmitErr( VALUE_NOT_WITHIN_ALLOWED_RANGE, "1-6" );
            } else {
                /* if value is IMAGE_COMDAT_SELECT_ASSOCIATIVE,
                 * get the associated segment name argument.
                 */
                if ( opndx.value == 5 ) {
                    struct asym *sym2;
                    if ( tokenarray[i].token != T_COMMA ) {
                        EmitErr( EXPECTING_COMMA, tokenarray[i].tokpos );
                        i = Token_Count; /* stop further parsing of this line */
                        break;
                    }
                    i++;
                    if ( tokenarray[i].token != T_ID ) {
                        EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr );
                        i = Token_Count; /* stop further parsing of this line */
                        break;
                    }
                    /* associated segment must be COMDAT, but not associative */
                    sym2 = SymSearch( tokenarray[i].string_ptr );
                    if ( sym2 == NULL ||
                        sym2->state != SYM_SEG ||
                        ((struct dsym *)sym2)->e.seginfo->comdat_selection == 0 ||
                        ((struct dsym *)sym2)->e.seginfo->comdat_selection == 5 )
                        EmitErr( INVALID_ASSOCIATED_SEGMENT, tokenarray[i].string_ptr );
                    else
                        dir->e.seginfo->comdat_number = ((struct dsym *)sym2)->e.seginfo->seg_idx;
                    i++;
                }
            }
            if ( tokenarray[i].token != T_CL_BRACKET ) {
                EmitErr( EXPECTED, ")" );
                break;
            }
            dir->e.seginfo->comdat_selection = opndx.value;
            dir->e.seginfo->combine = type->value;
            break;
#endif
        case INIT_OFSSIZE:
        case INIT_OFSSIZE_FLAT:
            if ( type->init == INIT_OFSSIZE_FLAT ) {
                DefineFlatGroup();
#if AMD64_SUPPORT
                /* v2.09: make sure ofssize is at least USE32 for FLAT */
                dir->e.seginfo->Ofssize = ( ModuleInfo.defOfssize > USE16 ? ModuleInfo.defOfssize : USE32 );
#else
                dir->e.seginfo->Ofssize = USE32;
#endif
                /* put the segment into the FLAT group.
                 * this is not quite Masm-compatible, because trying to put
                 * the segment into another group will cause an error.
                 */
                dir->e.seginfo->group = &ModuleInfo.flat_grp->sym;
            } else
                dir->e.seginfo->Ofssize = type->value;
            break;
#if COFF_SUPPORT || ELF_SUPPORT || PE_SUPPORT
        case INIT_CHAR_INFO:
            dir->e.seginfo->info = TRUE; /* fixme: check that this flag isn't changed */
            break;
        case INIT_CHAR:
            DebugMsg1(("SegmentDir(%s): characteristics found\n", name ));
            /* characteristics are restricted to COFF/ELF/BIN-PE */
            if ( Options.output_format == OFORMAT_OMF
#if PE_SUPPORT
                || ( ModuleInfo.flat == FALSE && Options.output_format == OFORMAT_BIN && ModuleInfo.sub_format != SFORMAT_PE )
#endif
               ) {
                EmitErr( NOT_SUPPORTED_WITH_CURR_FORMAT, tokenarray[i].string_ptr );
            } else
                newcharacteristics |= type->value;
            break;
        case INIT_ALIAS:
            DebugMsg1(("SegmentDir(%s): ALIAS found, curr value=%s\n", name, dir->e.seginfo->aliasname ? dir->e.seginfo->aliasname : "NULL" ));
            /* alias() is restricted to COFF/ELF/BIN-PE */
            if ( Options.output_format == OFORMAT_OMF
                || ( Options.output_format == OFORMAT_BIN && ModuleInfo.sub_format != SFORMAT_PE )
               ) {
                EmitErr( NOT_SUPPORTED_WITH_CURR_FORMAT, tokenarray[i].string_ptr );
                i = Token_Count; /* stop further parsing of this line */
                break;
            }
            i++;
            if ( tokenarray[i].token != T_OP_BRACKET ) {
                EmitErr( EXPECTED, "(" );
                break;
            }
            i++;
            if ( tokenarray[i].token != T_STRING ||
                ( tokenarray[i].string_delim != '"' &&
                tokenarray[i].string_delim != '\'' ) ) {
                EmitErr( SYNTAX_ERROR_EX, token );
                i = Token_Count; /* stop further parsing of this line */
                break;
            }
            temp = i;
            i++;
            if ( tokenarray[i].token != T_CL_BRACKET ) {
                EmitErr( EXPECTED, ")" );
                break;
            }
            /* v2.10: if segment already exists, check that old and new aliasname are equal */
            if ( is_old ) {
                if ( dir->e.seginfo->aliasname == NULL ||
                    ( tokenarray[temp].stringlen != strlen( dir->e.seginfo->aliasname ) ) ||
                    memcmp( dir->e.seginfo->aliasname, tokenarray[temp].string_ptr + 1, tokenarray[temp].stringlen ) ) {
                    EmitErr( SEGDEF_CHANGED, dir->sym.name, MsgGetEx( TXT_ALIASNAME ) );
                    break;
                }
            } else {
                /* v2.10: " + 1" was missing in next line */
                dir->e.seginfo->aliasname = LclAlloc( tokenarray[temp].stringlen + 1 );
                memcpy( dir->e.seginfo->aliasname, tokenarray[temp].string_ptr+1, tokenarray[temp].stringlen );
                *(dir->e.seginfo->aliasname+tokenarray[temp].stringlen) = NULLC;
            }
            DebugMsg1(("SegmentDir(%s): ALIAS argument=>%s<\n", name, dir->e.seginfo->aliasname ));
            break;
#endif
#ifdef DEBUG_OUT
        default: /* shouldn't happen */
            /**/myassert( 0 );
            break;
#endif
        }
    } /* end for */

    /* make a guess about the segment's type */
    if( dir->e.seginfo->segtype != SEGTYPE_CODE ) {
        enum seg_type res;

        //token = GetLname( dir->e.seginfo->class_name_idx );
        res = TypeFromClassName( dir, dir->e.seginfo->clsym );
        if( res != SEGTYPE_UNDEF ) {
            dir->e.seginfo->segtype = res;
        }
#if 0 /* v2.03: removed */
        else {
            res = TypeFromSegmentName( name );
            dir->e.seginfo->segtype = res;
        }
#endif
    }

    if( is_old ) {
        int txt = 0;

        /* Check if new definition is different from previous one */

        // oldobj = dir->e.seginfo->segrec;
        if ( oldalign    != dir->e.seginfo->alignment && !ModuleInfo.flat ) // UASM 2.46 FLAT mode is allowed to change alignment
            txt = TXT_ALIGNMENT;
        else if ( oldcombine  != dir->e.seginfo->combine )
            txt = TXT_COMBINE;
        else if ( oldOfssize  != dir->e.seginfo->Ofssize && !ModuleInfo.flat ) //UASM 2.46 FLAT mode is allowed to change Ofssize
            txt = TXT_SEG_WORD_SIZE;
#if 0 /* v2.09: removed */
        else if(  oldreadonly != dir->e.seginfo->readonly )
            /* readonly is not a true segment attribute */
            txt = TXT_READONLY;
        else if ( oldclsym != dir->e.seginfo->clsym )
            /* segment class check is done in SetSegmentClass() */
            txt = TXT_CLASS;
#endif
        else if ( newcharacteristics && ( newcharacteristics != dir->e.seginfo->characteristics ) )
            txt = TXT_CHARACTERISTICS;

        if ( txt ) {
            EmitErr( SEGDEF_CHANGED, dir->sym.name, MsgGetEx( txt ) );
            //return( ERROR ); /* v2: display error, but continue */
        }

    } else {
        /* A new definition */

        //sym = &dir->sym;
        sym->isdefined = TRUE;
        sym->segment = sym;
        sym->offset = 0; /* remains 0 ( =segment's local start offset ) */
#if COMDATSUPP
        /* no segment index for COMDAT segments in OMF! */
        if ( dir->e.seginfo->comdat_selection && Options.output_format == OFORMAT_OMF )
            ;
        else {
#endif
            dir->e.seginfo->seg_idx = ++ModuleInfo.g.num_segs;
            /* dir->e.seginfo->lname_idx = */ AddLnameItem( sym );
#if COMDATSUPP
        }
#endif

    }
    if ( newcharacteristics )
        dir->e.seginfo->characteristics = newcharacteristics;

    push_seg( dir ); /* set CurrSeg */

    if ( ModuleInfo.list )
        LstWrite( LSTTYPE_LABEL, 0, NULL );

    return( SetOfssize() );
}

/* sort segments ( a simple bubble sort )
 * type = 0: sort by fileoffset (.DOSSEG )
 * type = 1: sort by name ( .ALPHA )
 * type = 2: sort by segment type+name ( PE format ). member lname_idx is misused here for "type"
 */
void SortSegments( int type )
/***************************/
{
    bool changed = TRUE;
    bool swap;
    struct dsym *curr;

    while ( changed == TRUE ) {
        struct dsym *prev = NULL;
        changed = FALSE;
        for( curr = SymTables[TAB_SEG].head; curr && curr->next ; prev = curr, curr = curr->next ) {
            swap = FALSE;
            switch (type ) {
            case 0:
                if ( curr->e.seginfo->fileoffset > curr->next->e.seginfo->fileoffset )
                    swap = TRUE;
                break;
            case 1:
                if ( strcmp( curr->sym.name, curr->next->sym.name ) > 0 )
                    swap = TRUE;
                break;
            case 2:
                if ( curr->e.seginfo->lname_idx > curr->next->e.seginfo->lname_idx ||
                    ( curr->e.seginfo->lname_idx == curr->next->e.seginfo->lname_idx &&
                    ( _stricmp( curr->sym.name, curr->next->sym.name ) > 0 ) ) )
                    swap = TRUE;
                break;
#ifdef DEBUG_OUT
            default: myassert( 0 );
#endif
            }
            if ( swap ) {
                struct dsym *tmp = curr->next;
                changed = TRUE;
                if ( prev == NULL ) {
                    SymTables[TAB_SEG].head = tmp;
                } else {
                    prev->next = tmp;
                }
                curr->next = tmp->next;
                tmp->next = curr;
            }
        }
    }
}

/* END directive has been found. */
ret_code SegmentModuleExit( void )
/********************************/
{
    if ( ModuleInfo.model != MODEL_NONE )
        ModelSimSegmExit();
    /* if there's still an open segment, it's an error */
    if ( CurrSeg ) {
        EmitErr( BLOCK_NESTING_ERROR, CurrSeg->sym.name );
        /* but close the still open segments anyway */
        while( CurrSeg && ( CloseSeg( CurrSeg->sym.name ) == NOT_ERROR ) );
    }

    return( NOT_ERROR );
}

/* this is called once per module after the last pass is finished */
void SegmentFini( void )
/**********************/
{
#if FASTMEM==0
    struct dsym    *curr;
#endif

    DebugMsg(("SegmentFini() enter\n"));
#if FASTMEM==0
    for( curr = SymTables[TAB_SEG].head; curr; curr = curr->next ) {
        struct fixup *fix;
        DebugMsg(("SegmentFini: segment %s\n", curr->sym.name ));
        for ( fix = curr->e.seginfo->FixupList.head; fix ; ) {
            struct fixup *next = fix->nextrlc;
            DebugMsg(("SegmentFini: free fixup [sym=%s, loc=%" I32_SPEC "X]\n", fix->sym ? fix->sym->name : "NULL", fix->location ));
            LclFree( fix );
            fix = next;
        }
    }
#endif

#if FASTPASS
    if ( saved_SegStack ) {
        LclFree( saved_SegStack );
    }
#endif
    FreeLnameQueue();
    DebugMsg(("SegmentFini() exit\n"));
}

/* init. called for each pass */
void SegmentInit( int pass )
/**************************/
{
    struct dsym *curr;
    uint_32     i;
#ifdef __I86__
    char __huge *p;
#else
    char        *p;
#endif

    DebugMsg(("SegmentInit(%u) enter\n", pass ));
    CurrSeg      = NULL;
    stkindex     = 0;

    if ( pass == PASS_1 ) {
        grpdefidx   = 0;
        buffer_size = 0;
#if FASTPASS
#if FASTMEM==0
        saved_SegStack = NULL;
#endif
#endif
    }

    /*
     * alloc a buffer for the contents
     */
    if ( ModuleInfo.pCodeBuff == NULL && Options.output_format != OFORMAT_OMF ) {
        for( curr = SymTables[TAB_SEG].head, buffer_size = 0; curr; curr = curr->next ) {
            if ( curr->e.seginfo->internal )
                continue;
            if ( curr->e.seginfo->bytes_written ) {
                i = curr->sym.max_offset - curr->e.seginfo->start_loc;
                /* the segment can grow in step 2-n due to forward references.
                 * for a quick solution just add 25% to the size if segment
                 * is a code segment. (v2.02: previously if was added only if
                 * code segment contained labels, but this isn't sufficient.)
                 */
                if ( curr->e.seginfo->segtype == SEGTYPE_CODE )
                    i = i + (i >> 2);
                DebugMsg(("SegmentInit(%u), %s: max_ofs=%" I32_SPEC "X, alloc_size=%" I32_SPEC "Xh\n", pass, curr->sym.name, curr->sym.max_offset, i ));
                buffer_size += i;
            }
        }
        if ( buffer_size ) {
            ModuleInfo.pCodeBuff = LclAlloc( buffer_size );
            DebugMsg(("SegmentInit(%u): total buffer size=%" I32_SPEC "X, start=%p\n", pass, buffer_size, ModuleInfo.pCodeBuff ));
        }
    }
    /* Reset length of all segments to zero.
     * set start of segment buffers.
     */
#if FASTMEM==0
    /* fastmem clears the memory blocks, but malloc() won't */
    if ( ModuleInfo.pCodeBuff )
        memset( ModuleInfo.pCodeBuff, 0, buffer_size );
#endif
    for( curr = SymTables[TAB_SEG].head, p = ModuleInfo.pCodeBuff; curr; curr = curr->next ) {
        curr->e.seginfo->current_loc = 0;
        if ( curr->e.seginfo->internal )
            continue;
        if ( curr->e.seginfo->bytes_written ) {
            if ( Options.output_format == OFORMAT_OMF ) {
                curr->e.seginfo->CodeBuffer = codebuf;
                DebugMsg(("SegmentInit(%u), %s: buffer=%p\n", pass, curr->sym.name, codebuf ));
            } else {
                curr->e.seginfo->CodeBuffer = p;
                i = curr->sym.max_offset - curr->e.seginfo->start_loc;
                DebugMsg(("SegmentInit(%u), %s: size=%" I32_SPEC "X buffer=%p\n", pass, curr->sym.name, i, p ));
                p += i;
            }
        }
        if( curr->e.seginfo->combine != COMB_STACK ) {
            curr->sym.max_offset = 0;
        }
        if ( Options.output_format == OFORMAT_OMF ) { /* v2.03: do this selectively */
            curr->e.seginfo->start_loc = 0;
            curr->e.seginfo->data_in_code = FALSE;
        }
        curr->e.seginfo->bytes_written = 0;

        curr->e.seginfo->FixupList.head = NULL;
        curr->e.seginfo->FixupList.tail = NULL;
    }

    ModuleInfo.Ofssize = USE16;

#if FASTPASS
    if ( pass != PASS_1 && UseSavedState == TRUE ) {
        CurrSeg = saved_CurrSeg;
        stkindex = saved_stkindex;
        if ( stkindex )
            memcpy( &SegStack, saved_SegStack, stkindex * sizeof(struct dsym *) );

        UpdateCurrSegVars();
    }
#endif
}
#if FASTPASS
void SegmentSaveState( void )
/***************************/
{
    saved_CurrSeg = CurrSeg;
    saved_stkindex = stkindex;
    if ( stkindex ) {
        saved_SegStack = LclAlloc( stkindex * sizeof(struct dsym *) );
        memcpy( saved_SegStack, &SegStack, stkindex * sizeof(struct dsym *) );
        DebugMsg(("SegmentSaveState: saved_segStack=%X\n", saved_SegStack ));
    }
}
#endif
