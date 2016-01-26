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
* Description:  interface for queue.c.
*               This file is included by globals.h
*
****************************************************************************/


#ifndef QUEUE_H
#define QUEUE_H 1

struct qnode {
    void *next;
    union {
        const void  *elmt;
        struct asym *sym;
    };
};

struct qdesc {
    void *head;
    void *tail;
};

//extern void QInit( struct qdesc * );
extern void QEnqueue( struct qdesc *, void * );
extern void QAddItem( struct qdesc *, const void * );
//extern void *QDequeue( struct qdesc * );
//extern void QJoinQueue( struct qdesc *dest, struct qdesc *src );

#endif


