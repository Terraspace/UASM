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
* Description:  Symbol name mangling routines.
*
****************************************************************************/

#include <ctype.h>

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "mangle.h"

#if MANGLERSUPP
#if !defined(__GNUC__) && !defined(__POCC__)
#define tolower(c) ((c >= 'A' && c <= 'Z') ? c | 0x20 : c )
#endif
#endif

typedef int (*mangle_func)( const struct asym *, char * );

static int ms32_decorate( const struct asym *sym, char *buffer );
#if OWFC_SUPPORT
static int ow_decorate( const struct asym *sym, char *buffer );
#endif
#if AMD64_SUPPORT
static int ms64_decorate( const struct asym *sym, char *buffer );
#endif

/* table of FASTCALL types.
 * order must match the one of enum fastcall_type
 * also see proc.c and invoke.c!
 */

static const mangle_func fcmanglers[] = {
    ms32_decorate, /* FCT_MSC */
#if OWFC_SUPPORT
    ow_decorate,   /* FCT_WATCOMC */
#endif
#if AMD64_SUPPORT
    ms64_decorate  /* FCT_WIN64 */
#endif
};

/* VoidMangler: no change to symbol name */

static int VoidMangler( const struct asym *sym, char *buffer )
/************************************************************/
{
    memcpy( buffer, sym->name, sym->name_size + 1 );
    return( sym->name_size );
}

/* UCaseMangler: convert symbol name to upper case */

static int UCaseMangler( const struct asym *sym, char *buffer )
/*************************************************************/
{
    memcpy( buffer, sym->name, sym->name_size + 1 );
    _strupr( buffer );
    return( sym->name_size );
}

/* UScoreMangler: add '_' prefix to symbol name */

static int UScoreMangler( const struct asym *sym, char *buffer )
/**************************************************************/
{
    buffer[0] = '_';
    memcpy( buffer+1, sym->name, sym->name_size + 1 );
    return( sym->name_size + 1 );
}

/* StdcallMangler: add '_' prefix and '@size' suffix to proc names */
/*                 add '_' prefix to other symbols */

static int StdcallMangler( const struct asym *sym, char *buffer )
/***************************************************************/
{
    const struct dsym *dir = (struct dsym *)sym;

    if( Options.stdcall_decoration == STDCALL_FULL && sym->isproc ) {
        return( sprintf( buffer, "_%s@%d", sym->name, dir->e.procinfo->parasize ) );
    } else {
        return( UScoreMangler( sym, buffer ) );
    }
}

/* MS FASTCALL 32bit */

static int ms32_decorate( const struct asym *sym, char *buffer )
/**************************************************************/
{
    return ( sprintf( buffer, "@%s@%u", sym->name, ((struct dsym *)sym)->e.procinfo->parasize ) );
}

#if OWFC_SUPPORT

/* flag values used by the OW fastcall name mangler ( changes ) */
enum changes {
    NORMAL           = 0,
    USCORE_FRONT     = 1,
    USCORE_BACK      = 2
};

/* FASTCALL OW style:
 *  add '_' suffix to proc names and labels
 *  add '_' prefix to other symbols
 */

static int ow_decorate( const struct asym *sym, char *buffer )
/************************************************************/
{
    char                *name;
    enum changes        changes = NORMAL;

    if( sym->isproc ) {
        changes |= USCORE_BACK;
    } else {
        switch( sym->mem_type ) {
        case MT_NEAR:
        case MT_FAR:
        case MT_EMPTY:
            changes |= USCORE_BACK;
            break;
        default:
            changes |= USCORE_FRONT;
        }
    }

    name = buffer;

    if( changes & USCORE_FRONT )
        *name++ = '_';
    memcpy( name, sym->name, sym->name_size + 1 );
    name += sym->name_size;
    if( changes & USCORE_BACK ) {
        *name++ = '_';
        *name = NULLC;
    }
    return( name - buffer );
}
#endif

#if AMD64_SUPPORT

/* MS FASTCALL 64bit */

static int ms64_decorate( const struct asym *sym, char *buffer )
/**************************************************************/
{
    memcpy( buffer, sym->name, sym->name_size + 1 );
    return( sym->name_size );
}
#endif

#if MANGLERSUPP
static char *CMangler( const struct asym *sym, char *buffer )
/***********************************************************/
{
    if( Options.naming_convention == NC_ADD_USCORES ) {
        return( UScoreMangler( sym, buffer ) );
    } else {
        return( VoidMangler( sym, buffer ) );
    }
}

static mangle_func GetMangler( const char *mangle_type )
/******************************************************/
{
    if( mangle_type != NULL && mangle_type[1] == NULLC ) {
        switch ( tolower( *mangle_type ) ) {
        case 'c':
            return( Options.xxx ? CMangler : ow_decorate );
        case 'n':
            return( VoidMangler );
        }
    }
    if ( mangle_type )
        EmitErr( UNKNOWN_MANGLER, mangle_type );

    return( NULL );
}
#endif

int Mangle( struct asym *sym, char *buffer )
/******************************************/
{
    mangle_func mangler;

    switch( sym->langtype ) {
    case LANG_C:
        /* leading underscore for C? */
        mangler = Options.no_cdecl_decoration ? VoidMangler : UScoreMangler;
        break;
    case LANG_SYSCALL:
        mangler = VoidMangler;
        break;
    case LANG_STDCALL:
        mangler = ( Options.stdcall_decoration == STDCALL_NONE ) ? VoidMangler : StdcallMangler;
        break;
    case LANG_PASCAL:
    case LANG_FORTRAN:
    case LANG_BASIC:
        mangler = UCaseMangler;
        break;
    case LANG_FASTCALL:          /* registers passing parameters */
        mangler = fcmanglers[ModuleInfo.fctype];
        break;
    default: /* LANG_NONE */
#if MANGLERSUPP
        mangler = sym->mangler;
        if( mangler == NULL )
            mangler = GetMangler( Options.default_name_mangler );
        if( mangler == NULL )
#endif
            mangler = VoidMangler;
        break;
    }
#if MANGLERSUPP
    sym->mangler = mangler;
#endif
    return( mangler( sym, buffer ) );
}

/* the "mangle_type" is an extension inherited from OW Wasm
 * accepted are "C" and "N". It's NULL if MANGLESUPP == 0 (standard)
 */
void SetMangler( struct asym *sym, int langtype, const char *mangle_type )
/************************************************************************/
{
#if MANGLERSUPP
    mangle_func mangler;
#endif

    if( langtype != LANG_NONE )
        sym->langtype = langtype;

#if MANGLERSUPP
    mangler = GetMangler( mangle_type );
    if( mangler == NULL ) {
        /* nothing to do */
    } else if( sym->mangler == NULL ) {
        sym->mangler = mangler;
    } else if( sym->mangler != mangler ) {
        EmitErr( CONFLICTING_MANGLER, sym->name );
    }
#endif
}
