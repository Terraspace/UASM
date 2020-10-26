/****************************************************************************
*
* Description:  prototypes of cmdline.c
*
****************************************************************************/
#pragma once

#ifdef __SW_BD
#define EXPQUAL __stdcall
#else
#define EXPQUAL
#endif

extern char* EXPQUAL ParseCmdline(const char** cmdline, int*);
extern void EXPQUAL CmdlineFini(void);
