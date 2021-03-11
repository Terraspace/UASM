/****************************************************************************
*
* Description:  prototypes of extern.c
*
****************************************************************************/
#pragma once

#ifndef _EXTERN_H_
#define _EXTERN_H_

/*---------------------------------------------------------------------------*/

#include "basedefs.h"

uasm_PACK_PUSH_STACK

extern struct asym* MakeExtern(const char* name, enum memtype type, struct asym* vartype, struct asym*, unsigned char);
extern void        AddPublicData(struct asym* sym);
extern void        FreePubQueue(void);

uasm_PACK_POP

#endif
