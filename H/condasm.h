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
* Description:  prototypes for conditional assembly and errors
*
****************************************************************************/

#ifndef _CONDASM_H_
#define _CONDASM_H_

enum if_state {
    BLOCK_ACTIVE,    /* current cond is true */
    BLOCK_INACTIVE,  /* current IF cond is false, looking for elseif */
    BLOCK_DONE       /* done TRUE section of current if, just nuke
                        everything until we see an endif */
};

enum cond_class {
    CC_NULL,
    CC_NUMARG,
    CC_LITARG,
    CC_BLKARG,
    CC_SYMARG,
    CC_PASS1,
    CC_PASS2,
};

extern enum if_state CurrIfState;

extern void conditional_assembly_prepare( int );
extern int  GetIfNestLevel( void );
extern void SetIfNestLevel( int );
extern void CondCheckOpen( void );
extern void CondInit( void );

#endif
