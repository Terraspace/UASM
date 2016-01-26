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
* Description:  segment related prototypes & externals
*
****************************************************************************/


#ifndef _SEGMENT_H_
#define _SEGMENT_H_

#define GetSegm( x )     (struct dsym *)x->segment

extern void             SetSymSegOfs( struct asym * );
extern int              GetSymOfssize( const struct asym * );
/* Get current segment's offset */
extern uint_32          GetCurrOffset( void );
extern ret_code         SetCurrOffset( struct dsym *, uint_32, bool, bool );
extern struct asym      *CreateIntSegment( const char *, const char *, uint_8, uint_8, bool );
/* get symbol's segment index, from the symbol itself */
extern unsigned         GetSegIdx( const struct asym * );
extern void             SegmentInit( int );     /* init segments */
extern void             SegmentFini( void );    /* exit segments */
extern struct asym      *GetGroup( const struct asym * );
extern uint_32          GetCurrSegAlign( void );
extern ret_code         SetOfssize( void );
extern enum seg_type    TypeFromClassName( const struct dsym *, const struct asym * );
extern void             DefineFlatGroup( void );
extern ret_code         SegmentModuleExit( void );
extern void             DeleteGroup( struct dsym * );
//extern char             *GetLname( int );
//extern void             FreeLnameQueue( void );

/* simplified segment functions */

enum sim_seg {
    SIM_CODE = 0,
    SIM_STACK,
    SIM_DATA,
    SIM_DATA_UN,            /* .DATA? */
    SIM_FARDATA,
    SIM_FARDATA_UN,         /* .FARDATA? */
    SIM_CONST,
    SIM_LAST
};

extern char             *SimGetSegName( enum sim_seg );
extern const char       *GetCodeClass( void );
extern ret_code         ModelSimSegmInit( int type );
extern void             ModelSimSegmExit( void );
extern void             SetModelDefaultSegNames( void );

#endif
