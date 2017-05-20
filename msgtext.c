/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:  handle (error) message texts
*
****************************************************************************/

#include "globals.h"
#include "token.h"
#include "tokenize.h"
#include "msgtext.h"

#define USERESOURCES 0 /* 1=use Win string resources, won't work for Linux! */

#if USERESOURCES

/*
 If Win32 resource strings are to be used, the
 makefiles must contain a call of the resource compiler!
 Resource file is H/Uasm.rc.
 */

#include "win32.h"
typedef void *HRSRC;
typedef void *HGLOBAL;
WINBASEAPI HRSRC   WINAPI FindResource( void *, char *, uint_32 );
WINBASEAPI HGLOBAL WINAPI LoadResource( void *, HRSRC );
WINBASEAPI void *  WINAPI LockResource( HGLOBAL );
WINBASEAPI void    WINAPI WideCharToMultiByte( uint_32, uint_32, uint_16 *, uint_32, uint_16 *, uint_32, uint_32, uint_32 );

#else

#ifdef __I86__

#include <i86.h>
#define FPTR( x ) MK_FP( FP_SEG( TX_MSG_USAGE ), x )
#undef pick
#define pick( code, string )  const char __based( __segname("_CODE") ) TX_ ## code[] = string;
#include "msgdef.h"
#undef pick
#define pick( code, string ) TX_ ## code,
static const char __based ( __segname("_CODE") ) * const msgtexts[] = {
#include "msgdef.h"
};

#else

#define FPTR( x ) x
#undef pick
#define pick( code, string )  string,
static const char * const msgtexts[] = {
#include "msgdef.h"
};
#endif

#endif

/* the compiler string stored in CodeView symbolic debugging info */
#ifdef DEBUG_OUT
const char szCVCompiler[] = { "Microsoft (R) Macro Assembler Version 6.15.8803" };
//const char szCVCompiler[] = { "Microsoft (R) Macro Assembler Version 8.00.50727" };
#else
const char szCVCompiler[] = { "Uasm v" _UASM_VERSION_STR_ };
#endif

static const char *MsgGet( int msgid, char *buffer )
/**************************************************/
{
#if USERESOURCES
    HRSRC hRsrc;
    HGLOBAL hRes;
    WORD * pId;
    int i;

    hRsrc = FindResource( NULL, MAKEINTRESOURCE(1 + (msgid >> 4)), RT_STRING );
    if (hRsrc) {
        hRes = LoadResource( NULL, hRsrc );
        if (hRes) {
            pId = LockResource( hRes );
            for (i = msgid % 16;i;i--)
                pId += *pId + 1;
            i = *pId++;
            if ( buffer == NULL )
                buffer = StringBufferEnd;
            WideCharToMultiByte( CP_ACP, 0, pId, i, buffer, -1, 0, 0 );
            buffer[i] = NULLC;
            return( buffer );
        }
    }
#else
    if ( msgid < MSG_LAST ) {
        if ( buffer ) {
            strcpy( buffer, FPTR( msgtexts[msgid] ) );
            return( buffer );
        } else
            return( (char *) FPTR( msgtexts[msgid] ) );
    }
#endif
    DebugMsg(("MsgGet(%u): Msg not found!!!\n", msgid));
    if ( buffer == NULL )
        buffer = StringBufferEnd;
    sprintf( buffer, "Msg %u", msgid );
    return( buffer );
}

const char *MsgGetEx( int msgid )
/*******************************/
{
    return( MsgGet( msgid, NULL ) );
}

