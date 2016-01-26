/****************************************************************************
*
* Description:  PUSHCONTEXT/POPCONTEXT interface
*
****************************************************************************/

#ifndef _CONTEXT_H_
#define _CONTEXT_H_

/*---------------------------------------------------------------------------*/

extern void      ContextInit( int );
#if FASTMEM==0
extern void      ContextFini( void );
#endif

#endif
