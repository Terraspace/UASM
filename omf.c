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
* Description:  handle OMF output format.
*
****************************************************************************/

#include <limits.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "segment.h"
#include "mangle.h"
#include "extern.h"
#include "fixup.h"
#include "omf.h"
#include "omfint.h"
#include "omfspec.h"
#include "fastpass.h"
#include "myassert.h"
#include "tokenize.h" /* needed because of StringBufferEnd usage */
#include "input.h"
#include "linnum.h"

#define TRUNCATE 1
#define MULTIHDR 1     /* write muliple THEADR records (Masm compatible) */
#define WRITEIMPDEF 0  /* write IMPDEF coment records for OPTION DLLIMPORT */

#define MANGLE_BYTES 8 /* extra size required for name decoration */
#define MAX_ID_LEN_OMF 247
#define MAX_LNAME_SIZE 1024
#define MAX_EXT_LENGTH 1020 /* max length ( in chars ) of EXTDEF */
#define MAX_PUB_LENGTH 1024 /* max length of PUBDEF record */


#if TRUNCATE
#if defined(__UNIX__) || defined(__CYGWIN__) || defined(__DJGPP__)
#include <unistd.h>
#else
#include <io.h>
#endif
#endif

#if defined(__UNIX__) || defined(__CYGWIN__)
#define _stat stat
#endif

#define TruncRec(objr)       (void)( (objr)->length = (objr)->curoff )

enum {
    TIME_SEC_B  = 0,
    TIME_SEC_F  = 0x001f,
    TIME_MIN_B  = 5,
    TIME_MIN_F  = 0x07e0,
    TIME_HOUR_B = 11,
    TIME_HOUR_F = 0xf800
};

enum {
    DATE_DAY_B  = 0,
    DATE_DAY_F  = 0x001f,
    DATE_MON_B  = 5,
    DATE_MON_F  = 0x01e0,
    DATE_YEAR_B = 9,
    DATE_YEAR_F = 0xfe00
};

union DOS_DATETIME {
    struct {
        unsigned short time;
        unsigned short date;
    } dos;
    time_t timet;
};

extern void cv_write_debug_tables( struct dsym *, struct dsym *, void * );
extern void SortSegments( int );

extern struct qdesc LinnumQueue;    /* queue of line_num_info items */
extern const char szNull[];

/* LastCodeBufSize stores the size of the code buffer AFTER it has been written in omf_write_ledata().
 * This allows to get the content bytes for the listing.
 * This is a rather hackish "design" and is to be improved.
 */
int_32       LastCodeBufSize;

static uint_32    seg_pos;        /* file pos of SEGDEF record(s) */
static uint_32    public_pos;     /* file pos of PUBDEF record(s) */
static uint_32    end_of_header;  /* file pos of "end of header"  */

/* v2.12: moved from inside omf_write_lnames() */
static int startitem;
static int startext;

#if MULTIHDR
static unsigned ln_srcfile;      /* last file for which line numbers have been written */
#endif
static uint_8 ln_is32;           /* last mode for which line numbers have been written */
static uint_16 ln_size;          /* size of line number info */

/* CodeView symbolic debug info */
enum dbgseg_index {
    DBGS_SYMBOLS,
    DBGS_TYPES,
    DBGS_MAX
};

struct dbg_section {
    const char *name;
    const char *cname;
};

static const struct dbg_section SymDebParm[DBGS_MAX] = {
    { "$$SYMBOLS", "DEBSYM" },
    { "$$TYPES",   "DEBTYP" },
};

static struct dsym *SymDebSeg[DBGS_MAX];

static void omf_InitRec( struct omf_rec *obj, uint_8 command )
/************************************************************/
{
    obj->length = 0;
    obj->curoff = 0;
    obj->data = NULL;
    obj->command = command;
    obj->is_32 = 0;
    DebugMsg1(("omf_InitRec(%p, %X)\n", obj, command ));
    return;
}

static time_t timet2dostime( time_t x )
/*************************************/
{
    struct tm *    ltime;
    union DOS_DATETIME dt;

    ltime = localtime( &x );
    dt.dos.date = (( ltime->tm_year - 80 ) << DATE_YEAR_B )
             | (( ltime->tm_mon + 1 ) << DATE_MON_B )
             | (( ltime->tm_mday ) << DATE_DAY_B );
    dt.dos.time = (( ltime->tm_hour ) << TIME_HOUR_B )
             | (( ltime->tm_min ) << TIME_MIN_B )
             | (( ltime->tm_sec / 2 ) << TIME_SEC_B );
    return( dt.timet );
}

static void Put8( struct omf_rec *objr, uint_8 value )
/****************************************************/
{
/**/myassert( objr != NULL && objr->data != NULL );
    objr->data[ objr->curoff++ ] = value;
}

static void Put16( struct omf_rec *objr, uint_16 value )
/******************************************************/
{
/**/myassert( objr != NULL && objr->data != NULL );

    WriteU16( objr->data + objr->curoff, value );
    objr->curoff += sizeof( uint_16 );
}

static void Put32( struct omf_rec *objr, uint_32 value )
/******************************************************/
{
/**/myassert( objr != NULL && objr->data != NULL );

    WriteU32( objr->data + objr->curoff, value );
    objr->curoff += sizeof( uint_32 );
}

#if 0
static void PutEither( struct omf_rec *objr, uint_32 data )
/*********************************************************/
{
/**/myassert( objr != NULL && objr->data != NULL );
    if( objr->is_32 ) {
        WriteU32( objr->data + objr->curoff, data );
        objr->curoff += sizeof( uint_32 );
    } else {
        WriteU16( objr->data + objr->curoff, data );
        objr->curoff += sizeof( uint_16 );
    }
}
#endif

/* index in OMF is limited to 0-7FFFh
 * index values 0-7Fh are stored in 1 byte.
 * index values 80h-7FFFh are stored in 2 bytes, the high
 * order byte first ( with bit 7=1 ).
 */

static void PutIndex( struct omf_rec *objr, unsigned idx )
/********************************************************/
{
/**/myassert( objr != NULL && objr->data != NULL && idx <= 0x7FFF );
    if( idx > 0x7f ) {
        objr->data[objr->curoff++] = ( idx >> 8 ) | 0x80;
    }
    objr->data[objr->curoff++] = idx & 0xff;
}

static void PutData( struct omf_rec *objr, const uint_8 *data, size_t len )
/*************************************************************************/
{
    /**/myassert( objr != NULL && objr->data != NULL );
    memcpy( objr->data + objr->curoff, data, len );
    objr->curoff += len;
}

static void PutName( struct omf_rec *objr, const char *name, size_t len )
/***********************************************************************/
{
    /**/myassert( objr != NULL && objr->data != NULL );
#if MAX_ID_LEN > MAX_ID_LEN_OMF
    if ( len > MAX_ID_LEN_OMF ) {
        EmitWarn( 1, IDENTIFIER_TOO_LONG );
        len = MAX_ID_LEN_OMF;
    }
#endif
    objr->data[objr->curoff++] = len;
    PutData( objr, (uint_8 *)name, len );
}

static void AttachData( struct omf_rec *objr, uint_8 *data, size_t len )
/**********************************************************************/
{
/**/myassert( objr->data == NULL );
    objr->data = data;
    objr->length = len;
}

#if 0
static void AllocData( struct omf_rec *objr, size_t len )
/*******************************************************/
{
/**/myassert( objr->data == NULL );
    objr->data = LclAlloc( len );
    objr->length = len;
}
#endif

/* return a group's index */

unsigned omf_GetGrpIdx( struct asym *sym )
/****************************************/
{
    return( sym ? ((struct dsym *)sym)->e.grpinfo->grp_idx : 0 );
}

/*
 * write OMF comment records about data in code.
 */

void omf_OutSelect( bool is_data )
/********************************/
{
    struct omf_rec      obj;
    uint_32             currofs;
    int                 sel_idx;
    static uint_32      sel_start;  /* start offset of data items */
    unsigned char       buffer[12]; /* max is 11 ( see below ) */

    if( is_data ) {
        /* do nothing if it isn't the first data item or
         * if current segment isn't code
         */
        if( CurrSeg->e.seginfo->data_in_code ||
           ( CurrSeg->e.seginfo->segtype != SEGTYPE_CODE ) )
            return;
        sel_start = GetCurrOffset();
        CurrSeg->e.seginfo->data_in_code = TRUE;
        DebugMsg(("omf_OutSelect: data in code segment (%s), starting at %" I32_SPEC "X\n", CurrSeg->sym.name, sel_start ));
    } else if ( CurrSeg->e.seginfo->data_in_code ) { /* data items written? */
        
        CurrSeg->e.seginfo->data_in_code = FALSE;

        if( write_to_file == TRUE ) {
            omf_InitRec( &obj, CMD_COMENT );
            obj.d.coment.attr = CMT_TNP;
            obj.d.coment.cmt_class = CMT_DISASM_DIRECTIVE;

            sel_idx = GetSegIdx( &CurrSeg->sym );

            //AllocData( objr, 11 );  /* 11 = 1 + 2 + 4 + 4 */
            AttachData( &obj, buffer, 11 );  /* 11 = 1 + 2 + 4 + 4 */
            currofs = GetCurrOffset();
            DebugMsg(("omf_OutSelect: writing coment record about data in code: start=%" I32_SPEC "X curofs=%" I32_SPEC "X\n", sel_start, currofs ));
            if( ( sel_start > 0xffffUL ) || ( currofs > 0xffffUL ) ) {
                Put8( &obj, DDIR_SCAN_TABLE_32 );
                PutIndex( &obj, sel_idx );
                Put32( &obj, sel_start );
                Put32( &obj, currofs );
            } else {
                Put8( &obj, DDIR_SCAN_TABLE );
                PutIndex( &obj, sel_idx );
                Put16( &obj, sel_start );
                Put16( &obj, currofs );
            }
            TruncRec( &obj );
            omf_write_record( &obj );
        }
    }
}

/* write line number debug info.
 * since v2.11, it's ensured that the size of this info will be < 1024.
 * note the item structure:
 *   uint_16 line_number;
 *   union {
 *       uint_16 ofs16;
 *       uint_32 ofs32;
 *   };
 * v2.11: create 16- or 32-bit data variant here!
 */

static void omf_write_linnum( uint_8 is32 )
/*****************************************/
{
    unsigned             ofssize = ( is32 ? sizeof( uint_32) : sizeof( uint_16 ) );
    unsigned             size;
    uint_8               *data;
    struct line_num_info *node;
    struct line_num_info *next;
    struct omf_rec       obj;

    for( node = LinnumQueue.head, data = StringBufferEnd; node; node = next ) {
        next = node->next;
        *(uint_16 *)data = node->number;
        data += sizeof( uint_16 );
        *(uint_32 *)data = node->offset;
        data += ofssize;
        LclFree( node );
    }
    LinnumQueue.head = NULL;

    size = (char *)data - StringBufferEnd;
    if( size ) {
        omf_InitRec( &obj, CMD_LINNUM );
        obj.is_32 = is32;
        AttachData( &obj, StringBufferEnd, size );
        obj.d.linnum.base.grp_idx = omf_GetGrpIdx( GetGroup( &CurrSeg->sym ) ); /* fixme ? */
        obj.d.linnum.base.seg_idx = CurrSeg->e.seginfo->seg_idx;
        obj.d.linnum.base.frame = 0; /* field not used here */
        omf_write_record( &obj );
    }
    return;
}

static void omf_write_fixupp( struct dsym *seg, char is32 )
/*********************************************************/
{
    uint_8 *data;
    unsigned size;
    struct fixup *fix;
    enum fixup_types type = ( is32 ? FIX_GEN_MS386 : FIX_GEN_INTEL );
    struct omf_rec  obj;

    fix = seg->e.seginfo->FixupList.head;
    while ( fix ) {
        for( data = StringBufferEnd, size = 0; fix; fix = fix->nextrlc ) {
            switch( fix->type ) {
            case FIX_RELOFF32:
            case FIX_OFF32:
            case FIX_PTR32:
                if ( !is32 ) continue;
                break;
            default:
                if ( is32 ) continue;
                break;
            }
            if ( size > 1020 - FIX_GEN_MAX )
                break;
            data += OmfFixGenFix( fix, seg->e.seginfo->start_loc, data, type );
            size = (char *)data - StringBufferEnd;
        }
        if ( size ) {
            omf_InitRec( &obj, CMD_FIXUPP );
            obj.is_32 = is32;
            AttachData( &obj, StringBufferEnd, size );
            omf_write_record( &obj );
        }
    }
}

static uint_8 get_omfalign( uint_8 alignment );

/* write an LEDATA record, optionally write fixups */

static void omf_write_ledata( struct dsym *seg )
/**********************************************/
{
    struct omf_rec  obj;
    int_32          size;

    size = seg->e.seginfo->current_loc - seg->e.seginfo->start_loc;
    DebugMsg1(( "omf_write_ledata enter, buffer=%p start ofs=%" I32_SPEC "X, size=%" I32_SPEC "X\n",
              seg->e.seginfo->CodeBuffer, seg->e.seginfo->start_loc, size ));
    if( size > 0 && write_to_file == TRUE ) {
        LastCodeBufSize = size;
#if COMDATSUPP
        if ( seg->e.seginfo->comdat_selection ) {
            /* if the COMDAT symbol has been referenced in a FIXUPP,
             * a CEXTDEF has to be written.
             */
            if ( seg->sym.used ) {
                omf_InitRec( &obj, CMD_CEXTDEF );
                AttachData( &obj, StringBufferEnd, 2 * sizeof( uint_16 ) );
                PutIndex( &obj, seg->e.seginfo->comdat_idx ); /* Index */
                PutIndex( &obj, 0 ); /* Type */
                TruncRec( &obj );
                omf_write_record( &obj );
                if ( seg->e.seginfo->seg_idx == 0 )
                    seg->e.seginfo->seg_idx = startext++;
            }

            omf_InitRec( &obj, CMD_COMDAT );
            AttachData( &obj, seg->e.seginfo->CodeBuffer, size );
            if( seg->e.seginfo->start_loc > 0xffffUL )
                obj.is_32 = 1;
            obj.d.comdat.flags = 0;
            /* low 4-bits is allocation type */
            if ( seg->e.seginfo->segtype == SEGTYPE_CODE ) {
                obj.d.comdat.attributes = ( ModuleInfo.model == MODEL_FLAT ? COMDAT_CODE32 : COMDAT_FAR_CODE );
            } else {
                obj.d.comdat.attributes = ( ModuleInfo.model == MODEL_FLAT ? COMDAT_DATA32 : COMDAT_FAR_DATA );
            }
            obj.d.comdat.align = get_omfalign( seg->e.seginfo->alignment );
            obj.d.comdat.offset = seg->e.seginfo->start_loc;
            obj.d.comdat.type_idx = 0;
            obj.d.comdat.public_lname_idx = seg->e.seginfo->comdat_idx;
            /* todo: error if comdat_idx is 0 */
        } else {
#endif
            omf_InitRec( &obj, CMD_LEDATA );
            AttachData( &obj, seg->e.seginfo->CodeBuffer, size );
            obj.d.ledata.idx = seg->e.seginfo->seg_idx;
            obj.d.ledata.offset = seg->e.seginfo->start_loc;
            if( obj.d.ledata.offset > 0xffffUL )
                obj.is_32 = 1;
#if COMDATSUPP
        }
#endif
        omf_write_record( &obj );

        /* process Fixup, if any */
        if( seg->e.seginfo->FixupList.head != NULL ) {
#if FASTMEM==0
            struct fixup *fix;
            struct fixup *next;
#endif
            omf_write_fixupp( seg, 0 );
            omf_write_fixupp( seg, 1 );
#if FASTMEM==0
            for( fix = seg->e.seginfo->FixupList.head; fix; ) {
                next = fix->nextrlc;
                LclFree( fix );
                fix = next;
            }
#endif
            seg->e.seginfo->FixupList.head = seg->e.seginfo->FixupList.tail = NULL;
        }
    }
    seg->e.seginfo->start_loc = seg->e.seginfo->current_loc;
}

/*
 * flush current segment.
 * write_to_file is always TRUE here
 */

void omf_FlushCurrSeg( void )
/***************************/
{
    //unsigned i;
    //unsigned size;

    DebugMsg1(( "omf_FlushCurrSeg() enter, CurrSeg=%s, currsrc=%u\n", CurrSeg ? CurrSeg->sym.name : "NULL", get_curr_srcfile() ));

    omf_write_ledata( CurrSeg );
    /* add line numbers if debugging info is desired */
    //if( write_to_file && Options.line_numbers ) {
    if( Options.line_numbers ) {
        omf_write_linnum( ln_is32 );
        ln_size = 0;
    }
    //if ( Options.no_comment_data_in_code_records == FALSE )
    //    omf_OutSelect( FALSE );
    return;
}

/* Write a THEADR record.
 */
static void omf_write_theadr( const char *name )
/**********************************************/
{
    struct omf_rec obj;
    unsigned    len;
    //const struct fname_item *fn;

    DebugMsg1(("omf_write_theadr(%s) enter\n", name));

    omf_InitRec( &obj, CMD_THEADR );

    /* v2.08: use the name given at the cmdline, that's what Masm does.
     * Masm emits either a relative or a full path, depending on what
     * was given as filename!
     */
    len = strlen( name );
    AttachData( &obj, StringBufferEnd, len + 1 );
    PutName( &obj, name, len );
    omf_write_record( &obj );

    DebugMsg1(("omf_write_theadr() exit\n"));
}

/* v2.11: check if
 * - source file is changing
 * - offset magnitude is changing
 * - size of line number info exceeds 1024
 * if at least one of these conditions are met AND there are linnum items
 * in the queue, then flush the current LEDATA buffer.
 * If source file changed, write a THEADR record for the new source file.
 * ( Masm also emits THEADR records, but more frequently -
 * it doesn't care if linnum items are written or have been written. )
 *
 * This function is called by AddLinnumDataRef(), that is, whenever a linnum
 * info is about to be written.
 */

void omf_check_flush( const struct line_num_info *curr )
/******************************************************/
{
    uint_8 is_32;
    uint_16 size;
#if MULTIHDR
    if ( curr->srcfile != ln_srcfile ) {
        if ( LinnumQueue.head )
            omf_FlushCurrSeg();
        /* todo: for Borland, there's a COMENT ( CMT_SRCFILE ) that could be written
         * instead of THEADR.
         */
        omf_write_theadr( GetFName( curr->srcfile )->fname );
        ln_srcfile = curr->srcfile;
        return;
    }
#endif
    /* if there's a change in offset magnitude ( 16 -> 32 or 32 -> 16 ),
     * do flush ( Masm compatible ).
     */
    is_32 = ( curr->offset > 0xffff ? TRUE : FALSE );
    if ( ln_is32 != is_32 ) {
        if ( LinnumQueue.head )
            omf_FlushCurrSeg();
        ln_is32 = is_32;
        return;
    }
    /* line number item consists of 16-bit line# and 16- or 32-bit offset */
    size = sizeof( uint_16 ) + ( is_32 ? sizeof( uint_32 ) : sizeof( uint_16 ) );
    /* if the size of the linnum data exceeds 1016,
     * do flush ( Masm compatible ).
     */
    if ( ln_size + size > 1024 - 8 ) {
        if ( LinnumQueue.head )
            omf_FlushCurrSeg();
    }
    ln_size += size;
    return;
};

/*------------------------------------------------------*/

/* write end of pass 1 record. */

static void omf_end_of_pass1( void )
/**********************************/
{
    struct omf_rec obj;

    omf_InitRec( &obj, CMD_COMENT );
    obj.d.coment.attr = 0x00;
    obj.d.coment.cmt_class = CMT_MS_END_PASS_1;
    AttachData( &obj, (uint_8 *)"\x001", 1 );
    omf_write_record( &obj );
}

/* called when a new path is started
 * the OMF "path 2" records (LEDATA, FIXUP, LINNUM ) are written in all passes.
 */

void omf_set_filepos( void )
/**************************/
{
    DebugMsg1(( "omf_set_filepos: reset file pos to %X\n", end_of_header ));
#if MULTIHDR
#endif
    fseek( CurrFile[OBJ], end_of_header, SEEK_SET );
}

static void omf_write_dosseg( void )
/**********************************/
{
    struct omf_rec obj;

    omf_InitRec( &obj, CMD_COMENT );
    obj.d.coment.attr = CMT_TNP;
    obj.d.coment.cmt_class = CMT_DOSSEG;
    AttachData( &obj, (uint_8 *)"", 0 );
    omf_write_record( &obj );
}

static void omf_write_lib( void )
/*******************************/
{
    struct omf_rec      obj;
    struct qitem        *curr;
    struct qitem        *next;
    char                *name;

    DebugMsg1(("omf_write_lib() enter\n"));
    for( curr = ModuleInfo.g.LibQueue.head; curr; curr = next ) {
        next = curr->next;
        name = curr->value;
        omf_InitRec( &obj, CMD_COMENT );
        obj.d.coment.attr = CMT_TNP;
        obj.d.coment.cmt_class = CMT_DEFAULT_LIBRARY;
        AttachData( &obj, (uint_8 *)name, strlen( name ) );
        omf_write_record( &obj );
    }
    DebugMsg1(("omf_write_lib() exit\n"));
}

#if DLLIMPORT && WRITEIMPDEF /* writing import records in OMF not supported yet */

void omf_write_import( void )
/***************************/
{
    struct dsym    *imp;
    int            len;
    struct omf_rec obj;
    uint_8         *data;

    /* don't do anything if -Fd isn't set or if -Fd was given with a file name */
    if ( (!Options.write_impdef) || Options.names[OPTN_LNKDEF_FN] )
        return;
    for ( imp = SymTables[TAB_EXT].head; imp; imp = imp->next ) {
        if ( imp->sym.isproc && ( imp->sym.weak == FALSE || imp->sym.iat_used == TRUE ) ) {
            if ( imp->sym.dll && *imp->sym.dll->name ) {
                omf_InitRec( &obj, CMD_COMENT );
                obj.d.coment.attr = 0x00;
                obj.d.coment.cmt_class = CMT_OMF_EXT;

                /* structure of IMPDEF "comment":
                 * type          db CMT_EXT_IMPDEF (=01)
                 * ordinal_flag  db ?  ;0=import by name
                 * int_name_len  db ?
                 * int_name      db int_name_len dup (?)
                 * mod_name_len  db ?
                 * mod_name      db mod_name_len dup (?)
                 * union
                 *  entry_ident   dw ?   ;if by ordinal
                 *  struct               ;if by name
                 *   imp_name_len db ?   ;may be 0
                 *   imp_name     db imp_name_len dup (?)
                 *  ends
                 * ends
                 */

                data = StringBufferEnd;
                len = Mangle( &imp->sym, data+3 );
                AttachData( &obj, data, len + strlen( imp->sym.dll->name ) + 5 ); /* 2 bytes prefix, 2*len prefix, 1 for imp_name_len */

                Put8( &obj, CMT_EXT_IMPDEF );
                Put8( &obj, 0 ); /* import by name */
                Put8( &obj, len );
                obj.curoff += len;
                PutName( &obj, imp->sym.dll->name, strlen( imp->sym.dll->name ) );
                Put8( &obj, 0 );
                omf_write_record( &obj );
            }
        }
    }
}
#endif

static void omf_write_export( void )
/**********************************/
{
    uint_8      parmcnt;
    struct dsym *dir;
    struct dsym *parm;
    struct omf_rec obj;
    int         len;
    uint_8      *data;

#if DLLIMPORT && WRITEIMPDEF /* writing import records in OMF not supported yet */
    omf_write_import();
#endif

    for( dir = SymTables[TAB_PROC].head; dir != NULL; dir = dir->nextproc ) {
        if( dir->e.procinfo->isexport ) {

            omf_InitRec( &obj, CMD_COMENT );
            obj.d.coment.attr = 0x00;
            obj.d.coment.cmt_class = CMT_OMF_EXT;
            data = StringBufferEnd;

            /* structure of EXPDEF "comment":
             * type          db CMT_EXT_EXPDEF (=02)
             * exported_flag db ?
             * ex_name_len   db ?
             * exported_name db ex_name_len dup (?)
             * int_name_len  db 0     ;always 0
             * ;internal_name db int_name_len dup (?)
             * ;ordinal      dw ?     ;optional
             */
            if ( Options.no_export_decoration == FALSE )
                len = Mangle( &dir->sym, data+3 );
            else {
                strcpy( data+3, dir->sym.name );
                len = dir->sym.name_size;
            }
            /* v2.11: case mapping was missing */
            if ( ModuleInfo.convert_uppercase )
                _strupr( data+3 );
#if MAX_ID_LEN > 255
            if ( len > 255 )
                len = 255; /* restrict name to 255 chars */
#endif
            AttachData( &obj, data, len + 4 );
            Put8( &obj, CMT_EXT_EXPDEF );
            /* write the "Exported Flag" byte:
             * bits 0-4: parameter count
             * bit 5: no data (entry doesn't use initialized data )
             * bit 6: resident (name should be kept resident)
             * bit 7: ordinal ( if 1, 2 byte index must follow name)
             */
            for ( parm = dir->e.procinfo->paralist, parmcnt = 0; parm; parm = parm->nextparam, parmcnt++ );
            parmcnt &= 0x1F; /* ensure bits 5-7 are still 0 */
            Put8( &obj, parmcnt ); /* v2.01: changed from fix 0x00 */
            Put8( &obj, len );
            obj.curoff += len;
            Put8( &obj, 0 );
            omf_write_record( &obj );
        }
    }
}

/* write OMF GRPDEF records
 */

static void omf_write_grpdef( void )
/**********************************/
{
    struct dsym     *curr;
    struct dsym     *segminfo;
    struct seg_item *seg;
    struct omf_rec  grp;
    //char            writeseg;

    DebugMsg1(("omf_write_grpdef enter\n"));
    //line_num = LineNumber;

    /* size of group records may exceed 1024! */
    for( curr = SymTables[TAB_GRP].head; curr; curr = curr->next ) {

        omf_InitRec( &grp, CMD_GRPDEF );

        grp.d.grpdef.idx = curr->e.grpinfo->grp_idx;

        /* we might need:
         * - 1 or 2 bytes for the group name index
         * - 2 or 3 bytes for each segment in the group
         */
        AttachData( &grp, StringBufferEnd, 2 + 3 * curr->e.grpinfo->numseg );
        /* v2.01: the LName index of the group may be > 0xff */
        /* v2.03: use the group index directly */
        PutIndex( &grp, curr->e.grpinfo->lname_idx );

        for( seg = curr->e.grpinfo->seglist; seg; seg = seg->next ) {
            //writeseg = TRUE;
            segminfo = (struct dsym *)(seg->seg);
            Put8( &grp, GRP_SEGIDX );
            PutIndex( &grp, segminfo->e.seginfo->seg_idx );
            /* truncate the group record if it comes near output buffer limit! */
            if ( grp.curoff > OBJ_BUFFER_SIZE - 10 ) {
                EmitWarn( 2, GROUP_DEFINITION_TOO_LARGE, curr->sym.name );
                break;
            }
        }
        TruncRec( &grp );
        omf_write_record( &grp );
    }
    DebugMsg1(("omf_write_grpdef exit\n"));
}

static uint_8 get_omfalign( uint_8 alignment )
/********************************************/
{
    switch ( alignment ) {
    case  1:  return( SEGDEF_ALIGN_WORD );
    case  2:  return( SEGDEF_ALIGN_DWORD );
    case  4:  return( SEGDEF_ALIGN_PARA );
    case  8:  return( SEGDEF_ALIGN_PAGE );
#if PAGE4K /* PharLab peculiarity; this is invalid for MS OMF */
    case 12:
        if ( Parse_Pass == PASS_1 )
            EmitWarn( 2, NO_4KPAGE_ALIGNED_SEGMENTS_IN_MS386 );
        return( SEGDEF_ALIGN_4KPAGE );
#endif
    case MAX_SEGALIGNMENT: return( SEGDEF_ALIGN_ABS );
    }
    /* value 0 is byte alignment, anything elso is "unexpected" */
    /**/myassert( alignment == 0 );
    return( SEGDEF_ALIGN_BYTE );
}

/* write segment table.
 * This is done after pass 1.
 * There might exist entries of undefined segments in
 * the segment list!
 */

static void omf_write_segdef( void )
/**********************************/
{
    struct dsym    *curr;
    struct omf_rec obj;

    DebugMsg1(("omf_write_segdef enter\n"));

    for( curr = SymTables[TAB_SEG].head; curr; curr = curr->next ) {

#if COMDATSUPP
        if ( curr->e.seginfo->comdat_selection )
            continue;
#endif
        omf_InitRec( &obj, CMD_SEGDEF );
        if ( curr->e.seginfo->Ofssize > USE16 ) {
            obj.is_32 = ( ( curr->e.seginfo->force32 || ( curr->sym.max_offset >= 0x10000 ) ) ? 1 : 0 );
        } else {
            obj.is_32 = 0;
        }

        obj.d.segdef.idx             = curr->e.seginfo->seg_idx;
        obj.d.segdef.use_32          = ( curr->e.seginfo->Ofssize > USE16 ? 1 : 0 );
        obj.d.segdef.align           = get_omfalign( curr->e.seginfo->alignment );
        obj.d.segdef.combine         = curr->e.seginfo->combine;
        obj.d.segdef.abs.frame       = curr->e.seginfo->abs_frame;
        obj.d.segdef.abs.offset      = curr->e.seginfo->abs_offset;
        obj.d.segdef.seg_length      = curr->sym.max_offset;
        obj.d.segdef.seg_lname_idx   = curr->e.seginfo->lname_idx;
        obj.d.segdef.class_lname_idx = ( curr->e.seginfo->clsym ? curr->e.seginfo->clsym->class_lname_idx : 1 );
        obj.d.segdef.ovl_lname_idx   = 1;

        omf_write_record( &obj );
        DebugMsg1(("omf_write_segdef(%s): len=%" I32_SPEC "X use32=%u align=%u comb=%u seg_lname=%u class_lname=%u ovl_lname=%u\n",
                  curr->sym.name,
                  obj.d.segdef.seg_length,
                  obj.d.segdef.use_32,
                  obj.d.segdef.align,
                  obj.d.segdef.combine,
                  obj.d.segdef.seg_lname_idx,
                  obj.d.segdef.class_lname_idx,
                  obj.d.segdef.ovl_lname_idx
                 ));
        /* write a comment for the linker.
         * this is something not done by Masm, it has
         * been inherited from Wasm.
         */
        if( curr->e.seginfo->segtype == SEGTYPE_CODE && Options.no_opt_farcall == FALSE ) {
            uint_8 buffer[4];
            omf_InitRec( &obj, CMD_COMENT );
            obj.d.coment.attr = CMT_TNP;
            obj.d.coment.cmt_class = CMT_LINKER_DIRECTIVE;
            AttachData( &obj, buffer, 3 );
            Put8( &obj, LDIR_OPT_FAR_CALLS );
            PutIndex( &obj, curr->e.seginfo->seg_idx );
            /* v2.04: added. cut off the 3. byte if not needed */
            TruncRec( &obj );
            omf_write_record( &obj );
        }
    }
    DebugMsg1(("omf_write_segdef exit\n"));
}

/* the lnames are stored in a queue. read
 * the items one by one and take care that
 * the record size doesn't exceed 1024 bytes.
 */

static void omf_write_lnames( void )
/**********************************/
{
    int         size;
    int         items;
    unsigned char *p;
    //void        *pv = NULL;
    struct qnode *curr;
    struct asym *sym;
    struct omf_rec obj;
    unsigned char buffer[MAX_LNAME_SIZE];

    DebugMsg1(("omf_write_lnames() enter\n"));
    p = buffer;
    *p++ = NULLC; /* start with the NULL entry */
    items = 1;
    startitem = 1;

    for ( curr = ModuleInfo.g.LnameQueue.head; ; curr = curr->next ) {
        //sym = GetLnameData( &pv );
        sym = ( curr ? (struct asym *)(curr->elmt) : NULL );
        size = p - buffer;
        /* v2.04: changed extra bytes from 1 to 4 (CMD, RECLEN, CHKSUM) */
        //if ( sym == NULL || ( ( size + sym->name_size + 1 ) > MAX_LNAME_SIZE )) {
        if ( sym == NULL || ( ( size + sym->name_size + 4 ) > MAX_LNAME_SIZE )) {
            if( size ) {
                omf_InitRec( &obj, CMD_LNAMES );
                /* first_idx and num_names are NOT
                 * written to the LNAMES record!
                 * In fact, they aren't used at all.
                 */
                obj.d.lnames.first_idx = startitem;
                obj.d.lnames.num_names = items;
                AttachData( &obj, buffer, size );
                omf_write_record( &obj );
                startitem = items;
            }
            if ( sym == NULL )
                break;
            p = buffer;
        }
        *p++ = (char)sym->name_size;
        /* copy 1 byte more - the NULLC - for _strupr() */
        memcpy( p, sym->name, sym->name_size + 1 );
        /* lnames are converted for casemaps ALL and NOTPUBLIC */
        if ( ModuleInfo.case_sensitive == FALSE )
            _strupr( p );
        DebugMsg1(("omf_write_lnames: %u=%s\n", items, p ));
        p += sym->name_size; /* overwrite the null char */
        items++;
        /* v2.12: lname_idx fields now set in OMF only */
        switch ( sym->state ) {
        case SYM_SEG: ((struct dsym *)sym)->e.seginfo->lname_idx = items; break;
        case SYM_GRP: ((struct dsym *)sym)->e.grpinfo->lname_idx = items; break;
        default:      sym->class_lname_idx = items;                       break;
        }
    };

    DebugMsg1(("omf_write_lnames() exit, items=%u\n", items ));
}

struct readext {
    struct dsym *p;
    uint_16 index;
    uint_8 method;
};

/* read items for EXTDEF records.
 * there are 2 sources:
 * - the AltQueue of weak externals
 * - the TAB_EXT queue of externals
 * v2.09: index (ext_idx1, ext_idx2 ) is now set inside this function.
 */

static struct asym *GetExt( struct readext *r )
/*********************************************/
{
    struct asym *sym;
    if ( r->method == 0 ) {
        for ( ; r->p; ) {
            sym = (struct asym *)r->p;
            r->p = r->p->next;
            if ( sym->iscomm == TRUE )
                continue;
            if ( sym->altname && sym->altname->included == FALSE ) {
                /**/ myassert( r->index ); /* overflow occured? */
                sym->altname->ext_idx2 = r->index++;
                sym->altname->included = TRUE;
                return( sym->altname );
            }
        }
        r->method++;
        r->p = SymTables[TAB_EXT].head;
    }
    for ( ; r->p; ) {
        sym = (struct asym *)r->p;
        r->p = r->p->next;
        if ( sym->iscomm == TRUE || sym->weak == TRUE )
            continue;
        /**/ myassert( r->index ); /* overflow occured? */
        sym->ext_idx1 = r->index++;
        //r->p->sym.included = TRUE;
        return( sym );
    }
    return( NULL );
}

/* write EXTDEF records.
 * this is done once, after pass 1.
 * v2.09: external index is now set here.
 */

static uint_16 omf_write_extdef( void )
/*************************************/
{
    struct omf_rec obj;
    struct asym *sym;
    struct dsym *symext;
    unsigned    rec_size;
    unsigned    len;
    struct readext r;
    char        data[MAX_EXT_LENGTH];
    unsigned char buffer[MAX_ID_LEN + MANGLE_BYTES + 1];

    DebugMsg1(("omf_write_extdef enter\n"));

    r.p = SymTables[TAB_EXT].head;
    r.index = 1;
    r.method = 0;
    obj.d.extdef.first_idx = 0;

    /* scan the EXTERN/EXTERNDEF items */

    sym = GetExt( &r );
    while ( sym ) {
        for ( rec_size = 0, obj.d.extdef.num_names = 0; sym; sym = GetExt( &r ) ) {
            //DebugMsg(("omf_write_extdef: %s, weak=%u, used=%u\n", curr->sym.name, curr->sym.weak, curr->sym.used ));
            DebugMsg1(("omf_write_extdef: %s\n", sym->name));
            len = Mangle( sym, buffer );
#if MAX_ID_LEN > 255
            if ( len > 255 )
                len = 255; /* length is 1 byte only */
#endif
            if ( ModuleInfo.convert_uppercase )
                _strupr( buffer );

            if( rec_size + len + 2 >= MAX_EXT_LENGTH ) {
                break;
            }
            obj.d.extdef.num_names++;

            data[rec_size++] = (char)len;
            memcpy( data + rec_size, buffer, len );
            rec_size += len;
            data[rec_size++] = 0;      /* for the type index */
        }
        if ( rec_size ) {
            DebugMsg1(("omf_write_extdef: write record, names=%u, size=%u, MAX=%u\n", obj.d.extdef.num_names, rec_size, MAX_EXT_LENGTH ));
            omf_InitRec( &obj, CMD_EXTDEF );
            AttachData( &obj, (uint_8 *)data, rec_size );
            omf_write_record( &obj );
            obj.d.extdef.first_idx += obj.d.extdef.num_names;
        }
    }

    /* v2.04: write WKEXT coment records.
     * those items are defined via "EXTERN (altname)" syntax.
     * After the records have been written, the indices in
     * altname are no longer needed.
     */

    for ( symext = SymTables[TAB_EXT].head; symext; symext = symext->next ) {
        if ( symext->sym.iscomm == FALSE && symext->sym.altname ) {
            omf_InitRec( &obj, CMD_COMENT );
            obj.d.coment.attr = CMT_TNP;
            obj.d.coment.cmt_class = CMT_WKEXT;
            AttachData( &obj, buffer, 4 );
            PutIndex( &obj, symext->sym.ext_idx1 );
            PutIndex( &obj, symext->sym.altname->ext_idx2 );
            TruncRec( &obj );
            omf_write_record( &obj );
        }
    }
    /* v2.05: reset the indices - this must be done only after ALL WKEXT
     * records have been written!
     */
    for ( symext = SymTables[TAB_EXT].head; symext; symext = symext->next ) {
            /* v2.09: don't touch the index if the alternate name is an external
             * - else an invalid object file will be created!
             */
        if ( symext->sym.iscomm == FALSE && symext->sym.altname && symext->sym.altname->state != SYM_EXTERNAL )
            symext->sym.altname->ext_idx = 0;
    }
    /* v2.09: write COMM items here. This allows to handle
     * the external index field entirely in omf.c
     * v2.11: removed again, since omf_write_extdef() is no
     * longer called externally.
     */
    //omf_write_comdef( r.index );

    DebugMsg1(("omf_write_extdef exit, index=%u\n", r.index ));
    return( r.index );
}

#define THREE_BYTE_MAX ( (1UL << 24) - 1 )

static int get_size_of_comdef_number( uint_32 value )
/***************************************************/
{
    /* The spec allows up to 128 in a one byte size field, but lots
       of software has problems with that, so we'll restrict ourselves
       to 127.
    */
    if( value < 128 ) {
        return( 1 );    /* 1 byte value */
    } else if( value <= USHRT_MAX ) {
        return( 3 );    /* 1 byte flag + 2 byte value */
    } else if( value <= THREE_BYTE_MAX ) {
        return( 4 );    /* 1 byte flag + 3 byte value */
    } else { /* if( value <= ULONG_MAX ) */
        return( 5 );    /* 1 byte flag + 4 byte value */
    }
}

/* for COMDEF: write item size (or number of items) */

static unsigned put_comdef_number( uint_8 *buffer, uint_32 value )
/****************************************************************/
{
    unsigned i;
    unsigned symsize;

    symsize = get_size_of_comdef_number( value );
    switch( symsize ) {
    case 1:  *buffer = value; break;
    case 3:  *buffer++ = COMDEF_LEAF_2;  break; /* 0x81 */
    case 4:  *buffer++ = COMDEF_LEAF_3;  break; /* 0x84 */
    case 5:  *buffer++ = COMDEF_LEAF_4;  break; /* 0x88 */
    }

    for( i = 1; i < symsize; i++ ) {
        *buffer++ = value % ( UCHAR_MAX + 1 );
        value >>= 8;
    }
    return( symsize );
}

/* write OMF COMDEF records.
 * this is done once, after pass 1.
 * v2.09: external index is now set inside this function.
 * important: the size of the communal variables must be known.
 * If the size is the difference of two code labels, it might
 * change in subsequent passes. Both Masm and Uasm won't adjust
 * the size then!
 */

static uint_16 omf_write_comdef( uint_16 index )
/**********************************************/
{
    struct omf_rec obj;
    struct dsym    *curr;
    unsigned    num;
    unsigned    recsize;
    unsigned    numsize;
    unsigned    symsize;
    uint_32     varsize;
    unsigned    start = 0; /* record's start index (not used) */
    char        buffer[MAX_ID_LEN + MANGLE_BYTES + 1];
    char        data[MAX_EXT_LENGTH];
    char        number[16];

    DebugMsg1(("omf_write_comdef enter\n"));
    curr = SymTables[TAB_EXT].head;
    while ( curr ) {
        for( num = 0, recsize = 0; curr != NULL ; curr = curr->next ) {
            if ( curr->sym.iscomm == FALSE )
                continue;
            symsize = Mangle( &curr->sym, buffer );
#if MAX_ID_LEN > 255
            if ( symsize > 255 )
                symsize = 255; /* length is 1 byte only */
#endif
            /* v2.11: case mapping was missing */
            if ( ModuleInfo.convert_uppercase )
                _strupr( buffer );

            varsize = SizeFromMemtype( curr->sym.mem_type, ModuleInfo.Ofssize, curr->sym.type );

            /**/ myassert( index );
            curr->sym.ext_idx = index++; /* v2.09: set external index here */

            DebugMsg1(("omf_write_comdef: %s, size=%u, sym.total_size=%u, sym.total_length=%u, sym.isfar=%u\n",
                      curr->sym.name, varsize, curr->sym.total_size, curr->sym.total_length, curr->sym.isfar ));
            if ( varsize == 0 )
                varsize = curr->sym.total_size / curr->sym.total_length;

            numsize = 1;
            if ( curr->sym.isfar == TRUE ) {
                number[0] = COMDEF_FAR;  /* 0x61 */
                numsize += put_comdef_number( &number[1], curr->sym.total_length );
                numsize += put_comdef_number( &number[numsize], varsize );
                DebugMsg(("omf_write_comdef: numsize=%u, length=%u, varsize=%u\n",
                          numsize, curr->sym.total_length, varsize ));
            } else {
                number[0] = COMDEF_NEAR; /* 0x62 */
                numsize += put_comdef_number( &number[1], curr->sym.total_length * varsize );
                DebugMsg1(("omf_write_comdef: numsize=%u, value=%u\n",
                          numsize, curr->sym.total_length * varsize ));
            }
            /* make sure the record's size doesn't exceed 1024.
             * 2 = 1 (name len) + 1 (type index)
             */
            if ( ( recsize + symsize + numsize + 2 ) > MAX_EXT_LENGTH )
                break;

            /* copy name ( including size prefix ), type, number */
            data[recsize++] = (char)symsize;
            memcpy( data + recsize, buffer, symsize );
            recsize += symsize;
            data[recsize++] = 0;      /* for the type index */
            memcpy( data + recsize, number, numsize );
            recsize += numsize;

            num++;

        } /* end for */

        if( num > 0 ) {
            omf_InitRec( &obj, CMD_COMDEF );
            obj.d.comdef.first_idx = start; /* unused */
            AttachData( &obj, (uint_8 *)data, recsize );
            obj.d.comdef.num_names = num; /* unused */
            omf_write_record( &obj );
            start += num;
        }
    }
    DebugMsg1(("omf_write_comdef exit\n"));
    return( index );
}

static time_t GetFileTimeStamp( const char *filename )
/****************************************************/
{
    struct _stat statbuf;

    if( _stat( filename, &statbuf ) != 0 ) {
        DebugMsg(("GetFileTimeStamp(%s): _stat() did return 0\n", filename ));
        return( 0 );
    }
    return( statbuf.st_mtime );
}

/*
 * write COMENT dependency records (CMT_DEPENDENCY) for debugging
 * if line numbers are on; this is a Borland/OW thing.
 */
static ret_code omf_write_autodep( void )
/***************************************/
{
    struct omf_rec  obj;
    struct fname_item *curr;
    char            *p = StringBufferEnd;
    unsigned int    len;
    unsigned        idx;

    DebugMsg(("omf_write_autodep() enter\n"));
    for( idx = 0, curr = ModuleInfo.g.FNames; idx < ModuleInfo.g.cnt_fnames; idx++, curr++ ) {
        omf_InitRec( &obj, CMD_COMENT );
        obj.d.coment.attr = CMT_TNP;
        obj.d.coment.cmt_class = CMT_DEPENDENCY; /* 0xE9 */

        len = strlen( curr->fname );
#if MAX_STRING_LEN > 255
        if ( len > 255 )
            len = 255; /* length is 1 byte only */
#endif
        /* v2.11: field mtime removed, timestamp read when needed */
        //*((time_t *)p) = timet2dostime( curr->mtime );
        *((time_t *)p) = timet2dostime( GetFileTimeStamp( curr->fname ) );
        *(p + 4) = (unsigned char)len;
        memcpy( p + 5, curr->fname, len );
        AttachData( &obj, (uint_8 *)p, len + 5 );
        DebugMsg(("omf_write_autodep(): write record: file=%s, time=%X\n", curr->fname, *((time_t *)p) ));
        omf_write_record( &obj );
    }
    /* one NULL dependency record must be on the end */
    omf_InitRec( &obj, CMD_COMENT );
    obj.d.coment.attr = CMT_TNP;
    obj.d.coment.cmt_class = CMT_DEPENDENCY;
    AttachData( &obj, (uint_8 *)"", 0 );
    omf_write_record( &obj );
    DebugMsg(("omf_write_autodep() exit\n"));
    return( NOT_ERROR );
}

static void omf_write_alias( void )
/*********************************/
{
    struct omf_rec      obj;
    char                *p;
    uint_8              len1;
    uint_8              len2;
    //bool                first = TRUE;
    struct dsym         *curr;
    char                tmp[MAX_ID_LEN + MANGLE_BYTES + 1];
    unsigned char       buff[2*MAX_ID_LEN_OMF + 2];

    for( curr = SymTables[TAB_ALIAS].head; curr; curr = curr->next ) {

        /* output an alias record for this alias */
        /* v2.10: use the decorated names */
        //len1 = curr->sym.name_size;
        len1 = Mangle( &curr->sym, tmp );
#if MAX_ID_LEN > MAX_ID_LEN_OMF
        if ( len1 > MAX_ID_LEN_OMF )
            len1 = MAX_ID_LEN_OMF;
#endif
        p = buff;
        *p++ = len1;
        memcpy( p, tmp, len1 );
        p += len1;

        //len2 = curr->sym.substitute->name_size;
        len2 = Mangle( curr->sym.substitute, tmp );
#if MAX_ID_LEN > MAX_ID_LEN_OMF
        if ( len2 > MAX_ID_LEN_OMF )
            len2 = MAX_ID_LEN_OMF;
#endif
        *p++ = len2;
        memcpy( p, tmp, len2 );

        omf_InitRec( &obj, CMD_ALIAS );
        AttachData( &obj, buff, len1 + len2 + 2 );
        omf_write_record( &obj );
        //first = FALSE;
    }
}

/* the PUBDEF record consists of:
 * - base_info ( segment, group, frame ), max size is 4
 * - items
 *   - 1 byte name len
 *   - name[]
 *   - offset ( 2/4 bytes )
 *   - type ( index field, here always 0 )
 */
static ret_code omf_write_pubdef( void )
/**************************************/
{
    struct qnode        *q;

    DebugMsg1(("omf_write_pub enter\n"));

    /* v2.07: struct pubdef_data has been modified to match
     * the data to be written to the object module more closely.
     * This fixed a possible overrun if too many publics were written.
     * v2.11: now the data matches exactly the OMF PUBDEF record
     * and is just attached.
     */

    q = ModuleInfo.g.PubQueue.head;
    while ( q ) {
        struct asym     *curr_seg;
        uint_8          *data;
        unsigned        size;
        uint_8          curr32;
        uint_8          is32;

        for ( size = 0, data = StringBufferEnd; q; q = q->next ) {
            unsigned    recsize;
            unsigned    len;
            struct asym *sym;
            sym = q->sym;
#if COMDATSUPP
            /* COMDAT symbol? Then write an LNAME record */
            if ( sym->segment && ((struct dsym *)sym->segment)->e.seginfo->comdat_selection ) {
                struct dsym *seg = (struct dsym *)sym->segment;
                if ( seg->e.seginfo->comdat_idx == 0 ) {
                    struct omf_rec obj;
                    seg->e.seginfo->comdat_idx = ++startitem;
                    seg->sym.used = sym->used;
                    omf_InitRec( &obj, CMD_LNAMES );
                    len = Mangle( sym, StringBufferEnd + 1 );
                    *StringBufferEnd = len;
                    if ( ModuleInfo.case_sensitive == FALSE )
                        _strupr( StringBufferEnd + 1 );
                    AttachData( &obj, StringBufferEnd, len + 1 );
                    omf_write_record( &obj );
                } else if ( Parse_Pass == PASS_1 ) {
                    /* ??? */
                }
                continue;
            }
#endif
            /* for constants, Masm checks if the value will fit in a 16-bit field,
             * either signed ( -32768 ... 32767 ) or unsigned ( 0 ... 65635 ).
             * As a result, the following code:
             * E1 equ 32768
             * E2 equ -32768
             * PUBLIC E1, E2
             * will store both equates with value 8000h in the 16-bit PUBDEF record!!!
             * Uasm behaves differently, resulting in negative values to be stored as 32-bit.
             */
#if 1
            is32 = ( sym->offset > 0xffffUL ? 1 : 0 );
#else
            is32 = ( sym->offset > 0xffff || sym->offset < -32768 ? 1 : 0 ); /* this is what Masm does */
#endif
            /* check if public fits in current record yet.
             * 4 bytes omf record overhead, 4 for base info, 1+1+4/2 for name_size, type & offset
             */
            recsize = size + sym->name_size + MANGLE_BYTES + 4+4+1+1+( is32 ? 4 : 2 );
            /* exit loop if segment or offset magnitude changes, or record becomes too big */
            if( size && ( sym->segment != curr_seg || is32 != curr32 || recsize > MAX_PUB_LENGTH ) )
                break;
            len = Mangle( sym, data + 1 );
#if MAX_ID_LEN > MAX_ID_LEN_OMF
            if ( len > 255 )
                len = 255; /* length is 1 byte only */
#endif
            if ( ModuleInfo.convert_uppercase )
                _strupr( data + 1 );
            curr_seg = sym->segment;
            curr32 = is32;

            *data = len;
            data += len + 1;
            if ( curr32 ) {
                *(uint_32 *)data = sym->offset;
                data += sizeof( uint_32 );
            } else {
                *(uint_16 *)data = sym->offset;
                data += sizeof( uint_16 );
            }
            *data++ = 0; /* type field */
            size = (char *)data - StringBufferEnd;
        }
        if ( size ) {
            struct omf_rec      obj;
            omf_InitRec( &obj, CMD_PUBDEF );
            AttachData( &obj, StringBufferEnd, size );
            obj.is_32 = curr32;
            if( curr_seg == NULL ) { /* absolute symbol, no segment */
                obj.d.pubdef.base.grp_idx = 0;
                obj.d.pubdef.base.seg_idx = 0;
            } else {
                obj.d.pubdef.base.seg_idx = GetSegIdx( curr_seg );
                obj.d.pubdef.base.grp_idx = omf_GetGrpIdx( GetGroup( curr_seg ) );
            }
            obj.d.pubdef.base.frame = 0;
            omf_write_record( &obj );
        }
    }

    DebugMsg1(("omf_write_pub exit\n"));
    return( NOT_ERROR );
}

static void omf_write_modend( struct fixup *fixup, uint_32 displ )
/****************************************************************/
{
    struct omf_rec  obj;
    uint_8 buffer[FIX_GEN_MODEND_MAX];

    DebugMsg(("omf_write_modend( fixup=%p, displ=%" I32_SPEC "X)\n", fixup, displ ));

    omf_InitRec( &obj, CMD_MODEND );

    if( fixup == NULL ) {
        obj.d.modend.main_module = FALSE;
        obj.d.modend.start_addrs = FALSE;
    } else {
        obj.d.modend.start_addrs = TRUE;
        obj.d.modend.main_module = TRUE;
        obj.is_32 = ( GetSymOfssize( fixup->sym ) > USE16 ? 1 : 0 ); /* USE16 or USE32 */
        AttachData( &obj, buffer, 0 );
        obj.length = OmfFixGenFixModend( fixup, buffer, displ, obj.is_32 ? FIX_GEN_MS386 : FIX_GEN_INTEL );
    }
    omf_write_record( &obj );
}

/* this callback function is called during codeview debug info generation */

static uint_8 *omf_cv_flushfunc( struct dsym *seg, uint_8 *curr, unsigned size, void *pv )
/****************************************************************************************/
{
    uint_8 *buffer = seg->e.seginfo->CodeBuffer;

    if ( ( curr - buffer ) && ( ( curr - buffer ) + size ) > ( 1024 - 8 ) ) {
        seg->e.seginfo->current_loc = seg->e.seginfo->start_loc + ( curr - buffer );
        omf_write_ledata( seg );
        return( buffer );
    }
    return( curr );
}

/*
 * If -Zi is set, a comment class
 * A1 record (MS extensions present) is written.
 *
 * Additionally, segments $$SYMBOLS, $$TYPES are added to the segment table
 */
static void omf_write_header_dbgcv( void )
/****************************************/
{
    int i;
    struct omf_rec obj;

    omf_InitRec( &obj, CMD_COMENT );
    obj.d.coment.attr = 0x00;
    obj.d.coment.cmt_class = CMT_MS_OMF; /* MS extensions present */
    AttachData( &obj, "\001CV", 3 );
    omf_write_record( &obj );
    for ( i = 0; i < DBGS_MAX; i++ ) {
        if ( SymDebSeg[i] = (struct dsym *)CreateIntSegment( SymDebParm[i].name, SymDebParm[i].cname, 0, USE32, TRUE ) ) {
            SymDebSeg[i]->e.seginfo->force32 = TRUE; /* without this a 32-bit segdef is emitted only if segsize > 64kB */
            SymDebSeg[i]->e.seginfo->flushfunc = omf_cv_flushfunc;
        }
    }
    return;
}

/* write contents of segments $$SYMBOLS and $$TYPES */

static void omf_write_debug_tables( void )
/****************************************/
{
    if ( SymDebSeg[DBGS_SYMBOLS] && SymDebSeg[DBGS_TYPES] ) {
        SymDebSeg[DBGS_SYMBOLS]->e.seginfo->CodeBuffer = CurrSource;
        SymDebSeg[DBGS_TYPES]->e.seginfo->CodeBuffer = CurrSource + 1024;
        cv_write_debug_tables( SymDebSeg[DBGS_SYMBOLS], SymDebSeg[DBGS_TYPES], NULL );
    }
}

/* write OMF module.
 * this is called after the last pass.
 * since the OMF records are written "on the fly",
 * the "normal" section contents are already written at this time.
 */

static ret_code omf_write_module( struct module_info *modinfo )
/*************************************************************/
{
#if TRUNCATE
    int fh;
    uint_32 size;
#endif
    /* -if Zi is set, write symbols and types */
    if ( Options.debug_symbols )
        omf_write_debug_tables();
    omf_write_modend( modinfo->g.start_fixup, modinfo->g.start_displ );
#if FASTMEM==0
    LclFree( modinfo->g.start_fixup );
#endif

#if TRUNCATE
    /* under some very rare conditions, the object
     * module might become shorter! Hence the file
     * must be truncated now. The problem is that there
     * is no stream function for this task.
     * the final solution will be to save the segment contents
     * in buffers and write the object module once everything
     * is done ( as it is done for the other formats already).
     * v2.03: most likely no longer necessary, since the file
     * won't become shorter anymore.
     */
    size = ftell( CurrFile[OBJ] );
#if defined(__UNIX__) || defined(__CYGWIN__) || defined(__DJGPP__)
    fh = fileno( CurrFile[OBJ] );
    if ( ftruncate( fh, size ) ); /* gcc warns if return value of ftruncate() is "ignored" */
#elif defined(__BORLANDC__)
    fh = _fileno( CurrFile[OBJ] );
    chsize( fh, size );
#else
    fh = _fileno( CurrFile[OBJ] );
    _chsize( fh, size );
#endif

#endif

    /* write SEGDEF records. Since these records contain the segment's length,
     * the records have to be written again after the final assembly pass.
     */
    fseek( CurrFile[OBJ] , seg_pos, SEEK_SET );
    omf_write_segdef();
    /* write PUBDEF records. Since the final value of offsets isn't known after
     * the first pass, this has to be called again after the final pass.
     */
    fseek( CurrFile[OBJ], public_pos, SEEK_SET);
    omf_write_pubdef();
    return( NOT_ERROR );
}

/* write OMF header info after pass 1 */

static ret_code omf_write_header_initial( struct module_info *modinfo )
/*********************************************************************/
{
    uint_16 ext_idx;

    if ( write_to_file == FALSE )
        return( NOT_ERROR );

    omf_write_theadr( CurrFName[ASM] ); /* write THEADR record, main src filename */
    /* v2.11: coment record "ms extensions present" now written here */
    if ( Options.debug_symbols ) /* -Zi option set? */
        omf_write_header_dbgcv();
    /* if( Options.no_dependencies == FALSE ) */
    if( Options.line_numbers )
        omf_write_autodep(); /* write dependency COMENT records ( known by Borland & OW ) */
    if( ModuleInfo.segorder == SEGORDER_DOSSEG )
        omf_write_dosseg(); /* write dosseg COMENT records */
    else if( ModuleInfo.segorder == SEGORDER_ALPHA )
        SortSegments( 1 );
    omf_write_lib(); /* write default lib COMENT records */
    omf_write_lnames(); /* write LNAMES records */

    /* write SEGDEF records. Since these records contain the segment's length,
     * the records have to be written again after the final assembly pass.
     * hence the start position of those records has to be saved.
     */
    seg_pos = ftell( CurrFile[OBJ] );
    omf_write_segdef();
    omf_write_grpdef(); /* write GRPDEF records */
    ext_idx = omf_write_extdef(); /* write EXTDEF records */
    startext = omf_write_comdef( ext_idx ); /* write COMDEF records */
    omf_write_alias(); /* write ALIAS records */

    /* write PUBDEF records. Since the final value of offsets isn't known after
     * the first pass, this has to be called again after the final pass.
     */
    public_pos = ftell( CurrFile[OBJ] );
    omf_write_pubdef();
    omf_write_export(); /* write export COMENT records */

    /* (optionally) write end-of-pass-one COMENT record
     * v2.10: don't write record if starting address is present.
     * the TIS OMF spec v1.1. warns that this
     * comment record is NOT to be present if
     * the MODEND record contains a starting address!
     */
    if ( !ModuleInfo.g.start_fixup )
        omf_end_of_pass1();
    end_of_header = ftell( CurrFile[OBJ] );
    return( NOT_ERROR );
}

/* init. called once per module */

void omf_init( struct module_info *modinfo )
/******************************************/
{
    DebugMsg(("omf_init enter\n"));
    modinfo->g.WriteModule = omf_write_module;
    modinfo->g.Pass1Checks = omf_write_header_initial;
    SymDebSeg[DBGS_SYMBOLS] = NULL;
    SymDebSeg[DBGS_TYPES] = NULL;
#if MULTIHDR
    ln_srcfile = modinfo->srcfile;
#endif
    ln_size = 0;
    return;
}
