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
*  Description: declarations for assume.c
*
****************************************************************************/

#ifndef _ASSUME_H_
#define _ASSUME_H_

/* flags for error field, used for GPR's ASSUME:ERROR|NOTHING */
enum err_flags {
    RL_ERROR  = 0x01,
    RX_ERROR  = 0x02,
    ERX_ERROR = 0x04,
    RRX_ERROR = 0x08,
    RH_ERROR  = 0x10
};

struct assume_info {
    struct asym         *symbol;        /* segment, group or type that is to
                                           be associated with the register */
    unsigned char       error;          /* register assumed to ERROR */
    unsigned char       is_flat;        /* register assumed to FLAT  */
};

/* v2.05: introduced */
struct stdassume_typeinfo {
    struct asym         *type;
    struct asym         *target_type;
    enum memtype        mem_type;
    unsigned char       ptr_memtype;
    unsigned char       is_ptr;
};

/* segment assume table is sorted by seg reg number: ES,CS,SS,DS,FS,GS.
 * see enum assume_segreg in globals.h.
 */
extern struct assume_info SegAssumeTable[];

/* standard register assume table; contains 8/16 entries for the GPRs */
extern struct assume_info StdAssumeTable[];

#define NUM_SEGREGS 6

extern void AssumeInit( int );     /* init assume tables */

extern enum assume_segreg search_assume( const struct asym *sym, enum assume_segreg def, bool search_grps );
extern enum assume_segreg GetAssume( const struct asym *, const struct asym *, enum assume_segreg, struct asym * * );

extern struct asym      *GetOverrideAssume( enum assume_segreg );
extern struct asym      *GetStdAssume( int );
extern struct asym      *GetStdAssumeEx( int );

extern void             ModelAssumeInit( void );
extern void             SetSegAssumeTable( void * );
extern void             GetSegAssumeTable( void * );
extern void             SetStdAssumeTable( void *, struct stdassume_typeinfo * );
extern void             GetStdAssumeTable( void *, struct stdassume_typeinfo * );

#endif
