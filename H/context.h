/****************************************************************************
*
* Description:  PUSHCONTEXT/POPCONTEXT interface
*
****************************************************************************/
#pragma once

#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include "basedefs.h"

uasm_PACK_PUSH_STACK

/*---------------------------------------------------------------------------*/

extern void      ContextInit(int);
#if FASTMEM==0
extern void      ContextFini(void);
#endif

uasm_PACK_POP

#endif
