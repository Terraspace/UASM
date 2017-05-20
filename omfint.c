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
* Description:  OMF low-level output routines.
*
****************************************************************************/

#include <stddef.h>

#include "globals.h"
#include "omfint.h"
#include "omfspec.h"
#include "myassert.h"

#ifdef __I86__
#define FFQUAL __near
#else
#define FFQUAL
#endif

#pragma pack( push, 1 )
/* fields cmd, reclen and buffer must be consecutive */
struct outbuff {
    unsigned    in_buf;   /* number of bytes in buffer  */
    uint_8      cmd;      /* record cmd                 */
    uint_16     reclen;   /* record length              */
    uint_8      buffer[OBJ_BUFFER_SIZE];
};
#pragma pack( pop )

static void safeWrite( FILE *file, const uint_8 *buf, unsigned len )
/******************************************************************/
{
    if( fwrite( buf, 1, len, file ) != len )
        WriteError();
}

#if 0
/* this function was needed to reposition to the record's
 * length field for update. Now always the full record is
 * kept in the buffer until WEndRec().
 */
static void safeSeek( FILE *file, int_32 offset, int mode )
/*********************************************************/
{
    if( fseek( file, offset, mode ) != 0 )
        SeekError();
}
#endif

/* start a buffered OMF record output */

static void WBegRec( struct outbuff *out, uint_8 command )
/********************************************************/
{
    out->in_buf = 0;
    out->cmd = command;
}

/* WEndRec() finish a buffered record.
 * - calculate checksum
 * - store checksum behind buffer contents
 * - writes the contents of the buffer(cmd, length, contents, checksum)
 */

static void WEndRec( struct outbuff *out )
/****************************************/
{
    uint_8  checksum;
    uint_8  *p;
    uint_8  *end;

    /**/myassert( out && out->cmd );

    out->reclen = out->in_buf + 1; /* add 1 for checksum byte */
    checksum = out->cmd + ( out->reclen & 0xff ) + (( out->reclen ) >> 8);
    for( p = out->buffer, end = p + out->in_buf; p < end; ) {
        checksum += *p++;
    }
    checksum = - checksum;
    *p = checksum; /* store chksum in buffer */

    /* write buffer + 4 extra bytes (1 cmd, 2 length, 1 chksum) */
    safeWrite( CurrFile[OBJ], &out->cmd, out->in_buf + 4 );

#if 0 //def DEBUG_OUT
    p = &out->cmd;
    DebugMsg1(("WEndRec: %X %X %X %X\n", *p, *(p+1), *(p+2), *(p+3) ));
    //printf( "WEndRec: %X %X %X %X (ofs cmd=%u ofs reclen=%u)\n", *p, *(p+1), *(p+2), *(p+3), offsetof( struct outbuff, cmd ), offsetof( struct outbuff, reclen ) );
#endif

}

/* write a byte to the current record */

static void PutByte( struct outbuff *out, uint_8 value )
/******************************************************/
{
    out->buffer[ out->in_buf++ ] = value;
}

/* write an index - 1|2 byte(s) - to the current record */

static void PutIndex( struct outbuff *out, uint_16 index )
/********************************************************/
{
    if( index > 0x7f ) {
        PutByte( out, 0x80 | ( index >> 8 ) );
    }
    PutByte( out, index & 0xff );
}

/* write a word to the current record */

static void PutWord( struct outbuff *out, uint_16 value )
/*******************************************************/
{
    WriteU16( out->buffer + out->in_buf, value );
    out->in_buf += sizeof( uint_16 );
}

/* write a dword to the current record */

static void PutDword( struct outbuff *out, uint_32 value )
/********************************************************/
{
    WriteU32( out->buffer + out->in_buf, value );
    out->in_buf += sizeof( uint_32 );
}

/* write a byte sequence to the current record */

static void PutMem( struct outbuff *out, const uint_8 *buf, unsigned length )
/***************************************************************************/
{
    /* ensure that there is enough free space in the buffer,
     * and also 1 byte left for the chksum!
     */
    if( length <= OBJ_BUFFER_SIZE - 1 - out->in_buf ) {
        memcpy( &out->buffer[ out->in_buf ], buf, length );
        out->in_buf += length;
    } else {
        /* this "shouldn't happen". */
        DebugMsg(("PutMem: buffer overflow error [length=%u, free=%u]\n", length, OBJ_BUFFER_SIZE - 1 - out->in_buf ));
        Fatal( INTERNAL_ERROR, __FILE__, __LINE__ );
    }
}

/*--------------------------------------------------------*/

/* For 16-bit records which are the same under Intel and MS OMFs */

static int FFQUAL writeMisc( struct outbuff *out, const struct omf_rec *objr )
/****************************************************************************/
{
    /**/myassert( objr->data != NULL );

    WBegRec( out, objr->command );
    PutMem( out, objr->data, objr->length );
    WEndRec( out );
    return( 0 );
}

/* For 32-bit records which are the same under Intel and MS OMFs */

static int FFQUAL writeMisc32( struct outbuff *out, const struct omf_rec *objr )
/******************************************************************************/
{
    /**/myassert( objr->data != NULL );

    WBegRec( out, objr->command | objr->is_32 );
    PutMem( out, objr->data, objr->length );
    WEndRec( out );
    return( 0 );
}

static int FFQUAL writeComent( struct outbuff *out, const struct omf_rec *objr )
/******************************************************************************/
{
    /**/myassert( objr->data != NULL );

    WBegRec( out, CMD_COMENT );
    PutByte( out, objr->d.coment.attr );
    PutByte( out, objr->d.coment.cmt_class );
    PutMem( out, objr->data, objr->length );
    WEndRec( out );
    return( 0 );
}

static int FFQUAL writeSegdef( struct outbuff *out, const struct omf_rec *objr )
/******************************************************************************/
{
    int         is32;
    uint_8      acbp;
    uint_8      align;

    /**/myassert( objr->command == CMD_SEGDEF );

    //is32 = objr->d.segdef.use_32;
    is32 = objr->is_32;
    WBegRec( out, CMD_SEGDEF + is32 );

    /* ACBP: bits=AAACCCBP
     * AAA=alignment
     * CCC=combination
     * B=big
     * P=32bit
     */
    acbp = ( objr->d.segdef.combine << 2 ) | objr->d.segdef.use_32;
    align = objr->d.segdef.align;
#if 1
    acbp |= align << 5;
#else
    switch( align ) {
    case SEGDEF_ALIGN_ABS:      acbp |= ALIGN_ABS << 5;     break;
    case SEGDEF_ALIGN_BYTE:     acbp |= ALIGN_BYTE << 5;    break;
    case SEGDEF_ALIGN_WORD:     acbp |= ALIGN_WORD << 5;    break;
    case SEGDEF_ALIGN_PARA:     acbp |= ALIGN_PARA << 5;    break;
    case SEGDEF_ALIGN_PAGE:     acbp |= ALIGN_PAGE << 5;    break;
    case SEGDEF_ALIGN_DWORD:    acbp |= ALIGN_DWORD << 5;   break;
#if PAGE4K
    case SEGDEF_ALIGN_4KPAGE:   acbp |= ALIGN_4KPAGE << 5;  break;
#endif
    default: /**/myassert( 0 );
    }
#endif
    /* set BIG bit. should also be done for 32-bit segments
     * if their size is exactly 4 GB. Currently Uasm won't
     * support segments with size 4 GB.
     */
    if( is32 == 0 && objr->d.segdef.seg_length == 0x10000 ) {
        acbp |= 0x02;
    }

    /* the segdef record is small (16bit: size 6 - 9 ):
     * - byte acbp
     * - word (32bit:dword) length
     * - index seg name
     * - index class name
     * - index ovl name
     * ABS segdefs are 3 bytes longer
    */

    PutByte( out, acbp );
    if( align == SEGDEF_ALIGN_ABS ) {
        /* absolut segment has frame=word and offset=byte
         * it isn't fixupp physical reference
         * and doesn't depend on segment size (16/32bit)
         */
        PutWord( out, objr->d.segdef.abs.frame );
        PutByte( out, objr->d.segdef.abs.offset );
    }
    if( is32 ) {
        PutDword( out, objr->d.segdef.seg_length );
    } else {
        PutWord( out, objr->d.segdef.seg_length );
    }

    PutIndex( out, objr->d.segdef.seg_lname_idx );
    PutIndex( out, objr->d.segdef.class_lname_idx );
    PutIndex( out, objr->d.segdef.ovl_lname_idx );
    //if( objr->d.segdef.access_valid ) {
    //    EmitError( ACCESS_CLASSES_NOT_SUPPORTED );
    //}
    WEndRec( out );
    return( 0 );
}

/*
 * Write LEDATA or LIDATA record.
 * the overhead is:
 * - 1 byte cmd
 * - 2 byte len
 * - 1/2 bytes segment index
 * - 2/4 bytes starting offset
 * - 1 byte chksum
 * so the data size "should" not exceed 1024-10 = 1014
 *
 * For LIDATA, the structure is equal.
 * The structure of the data block differs, however:
 * - 2/4: repeat count
 * - 2: block count
 * - content
 */

static int FFQUAL writeLedata( struct outbuff *out, const struct omf_rec *objr )
/******************************************************************************/
{
    /**/myassert( objr->command == CMD_LEDATA || objr->command == CMD_LIDATA );

    WBegRec( out, objr->command + objr->is_32 );
    PutIndex( out, objr->d.ledata.idx );
    if( objr->is_32 ) {
        PutDword( out, objr->d.ledata.offset );
    } else {
        PutWord( out, objr->d.ledata.offset );
    }
    PutMem( out, objr->data, objr->length );
    WEndRec( out );
    return( 0 );
}

static int FFQUAL writeTheadr( struct outbuff *out, const struct omf_rec *objr )
/******************************************************************************/
{
    /**/myassert( objr->command == CMD_THEADR );

    return( writeMisc( out, objr ) );
}

static int FFQUAL writeModend( struct outbuff *out, const struct omf_rec *objr )
/******************************************************************************/
{
    int     is32;
    //uint_8  is_log;
    uint_8  mtype;

    /**/myassert( objr->command == CMD_MODEND );

    is32 = ( ( objr->is_32 && objr->d.modend.start_addrs ) ? TRUE : FALSE );
    WBegRec( out, CMD_MODEND + is32 );
    /* first byte is Module Type:
     * bit 7: 1=main program module
     * bit 6: 1=contains start address
     * bit 5: Segment bit ( according to OMF, this bit should be 1 )
     * bit 1-4: must be 0
     * bit 0: start address contains relocatable address ( according to OMF, this bit should be 1 )
     * Masm does set bit 0, but does not set bit 5!
     */
    mtype = objr->d.modend.main_module ? 0x80 : 0;
    if( objr->d.modend.start_addrs ) {
        //is_log = objr->d.modend.is_logical;
        //mtype |= 0x40 | is_log;
        mtype |= 0x41;
        PutByte( out, mtype );
        PutMem( out, objr->data, objr->length );
    } else
        PutByte( out, mtype );

    WEndRec( out );
    return( 0 );
}

/* write public base field of COMDAT, PUBDEF or LINNUM records */

static void PutBase( struct outbuff *out, const struct base_info *base )
/**********************************************************************/
{
    PutIndex( out, base->grp_idx );
    PutIndex( out, base->seg_idx );
    if( base->grp_idx == 0 && base->seg_idx == 0 ) {
        PutWord( out, base->frame );
    }
}

static int FFQUAL writePubdef( struct outbuff *out, const struct omf_rec *objr )
/******************************************************************************/
{
    /**/myassert( objr->command == CMD_PUBDEF || objr->command == CMD_LPUBDEF );

    WBegRec( out, objr->command + objr->is_32 );
    PutBase( out, &objr->d.pubdef.base );
    PutMem( out, objr->data, objr->length );
    WEndRec( out );
    return( 0 );
}

static int FFQUAL writeLinnum( struct outbuff *out, const struct omf_rec *objr )
/******************************************************************************/
{

    /**/myassert( objr->command == CMD_LINNUM );

    WBegRec( out, CMD_LINNUM + objr->is_32 );
    PutBase( out, &objr->d.linnum.base );
    PutMem( out, objr->data, objr->length );
    WEndRec( out );
    return( 0 );
}

#if COMDATSUPP

/* COMDATs are initialized communal data records.
 * This isn't used yet for OMF.
 */

static int FFQUAL writeComdat( struct outbuff *out, const struct omf_rec *objr )
/******************************************************************************/
{
    /**/myassert( objr->command == CMD_COMDAT );

    /* write CMD_COMDAT/CMD_COMD32 */
    WBegRec( out, objr->command + objr->is_32 );
    PutByte( out, objr->d.comdat.flags );
    PutByte( out, objr->d.comdat.attributes );
    PutByte( out, objr->d.comdat.align );
    if( objr->is_32 ) {
        PutDword( out, objr->d.comdat.offset );
    } else {
        PutWord( out, objr->d.comdat.offset );
    }
    PutIndex( out, objr->d.comdat.type_idx );
    if( ( objr->d.comdat.attributes & COMDAT_ALLOC_MASK ) == COMDAT_EXPLICIT ) {
        PutBase( out, &objr->d.comdat.base );
    }
    PutIndex( out, objr->d.comdat.public_lname_idx );
    /* record is already in ms omf format */
    PutMem( out, objr->data, objr->length );
    WEndRec( out );
    return( 0 );
}

/* LINSYM record types are only used in conjunction with COMDAT. */

static int FFQUAL writeLinsym( struct outbuff *out, const struct omf_rec *objr )
/******************************************************************************/
{

    /**/myassert( objr->command == CMD_LINSYM );

    WBegRec( out, CMD_LINSYM + objr->is_32 );
    PutByte( out, objr->d.linsym.flags );
    PutIndex( out, objr->d.linsym.public_lname_idx );
    PutMem( out, objr->data, objr->length );
    WEndRec( out );
    return( 0 );
}

#endif

static int FFQUAL writeUnexp( struct outbuff *out, const struct omf_rec *objr )
/*****************************************************************************/
{
    DebugMsg(("unexpected OMF record type 0x%02X\n", objr->command ));
    Fatal( INTERNAL_ERROR, __FILE__, __LINE__ );
    /* this is never reached, since Fatal() won't return */
    return( 0 );
}

typedef int FFQUAL (*pobj_filter)( struct outbuff *, const struct omf_rec * );

static const pobj_filter myFuncs[] = {
    writeUnexp,
    writeMisc,
    writeMisc32,
    writeSegdef,
    writeLedata,
    writeComent,
    writeTheadr,
    writeModend,
    writePubdef,
    writeLinnum,
#if COMDATSUPP
    writeComdat,
    writeLinsym
#endif
};

enum omffiltfuncs {
    OFF_UNEXP,
    OFF_MISC,
    OFF_MISC32,
    OFF_SEGDEF,
    OFF_LEDATA,
    OFF_COMENT,
    OFF_THEADR,
    OFF_MODEND,
    OFF_PUBDEF,
    OFF_LINNUM,
#if COMDATSUPP
    OFF_COMDAT,
    OFF_LINSYM
#endif
};

static const uint_8 func_index[] = {
    OFF_THEADR, 0,          0,          0,         /* 80 THEADR, LHEADR, PEDATA, PIDATA */
    OFF_COMENT, OFF_MODEND, OFF_MISC,   0,         /* 88 COMENT, MODEND, EXTDEF, TYPDEF */
    OFF_PUBDEF, 0,          OFF_LINNUM, OFF_MISC,  /* 90 PUBDEF, LOCSYM, LINNUM, LNAMES */
    OFF_SEGDEF, OFF_MISC,   OFF_MISC32, 0,         /* 98 SEGDEF, GRPDEF, FIXUP,  ???    */
    OFF_LEDATA, OFF_LEDATA, 0,          0,         /* A0 LEDATA, LIDATA, LIBHED, LIBNAM */
    0,          0,          0,          0,         /* A8 LIBLOC, LIBDIC, ???,    ???    */
    OFF_MISC,   OFF_MISC32, OFF_MISC,   OFF_PUBDEF,/* B0 COMDEF, BAKPAT, LEXTDEF,LPUBDEF*/
    OFF_MISC,   0,          OFF_MISC,   0,         /* B8 LCOMDEF,???,    CEXTDEF,???    */
#if COMDATSUPP
    0,          OFF_COMDAT, OFF_LINSYM, OFF_MISC,  /* C0 ???,    COMDAT, LINSYM, ALIAS  */
#else
    0,          0,          0,          OFF_MISC,  /* C0 ???,    COMDAT, LINSYM, ALIAS  */
#endif
    OFF_MISC32, OFF_MISC                           /* C8 NBKPAT, LLNAMES */
};

#define JUMP_INDEX(cmd)    ( ( ( cmd ) - CMD_MIN_CMD ) >> 1 )

/* call a function - bit 0 of command is always 0 */

void omf_write_record( const struct omf_rec *objr )
/*************************************************/
{
    struct outbuff out;

    /**/myassert( objr != NULL && objr->command >= CMD_MIN_CMD && objr->command <= CMD_MAX_CMD + 1 );
    DebugMsg1(("omf_write_record( cmd=%X data=%p length=%u )\n", objr->command, objr->data, objr->length ));
    myFuncs[ func_index[JUMP_INDEX(objr->command) ] ] ( &out, objr );
}
