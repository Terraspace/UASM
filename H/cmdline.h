/****************************************************************************
*
* Description:  prototypes of cmdline.c
*
****************************************************************************/
#pragma once

#ifndef _CMDLINE_H_INCLUDED_
#define _CMDLINE_H_INCLUDED_

#ifdef __SW_BD
#define EXPQUAL __stdcall
#else
#define EXPQUAL
#endif

#include "basedefs.h"

uasm_PACK_PUSH_STACK

extern char* EXPQUAL ParseCmdline(char** cmdline, int*);
extern void EXPQUAL CmdlineFini(void);

uasm_PACK_POP

#endif // _CMDLINE_H_INCLUDED_
