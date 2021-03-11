/****************************************************************************
*
* Description:  interface posndir.c - handles ORG, ALIGN, EVEN directives
*
****************************************************************************/
#pragma once

#ifndef _POSNDIR_H_
#define _POSNDIR_H_

#include "basedefs.h"

uasm_PACK_PUSH_STACK

extern void AlignCurrOffset(int);

uasm_PACK_POP

#endif
