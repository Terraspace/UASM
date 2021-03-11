/****************************************************************************
*
* Description:  msgtext.c interface
*
****************************************************************************/
#pragma once

#ifndef _MSGTEXT_H_
#define _MSGTEXT_H_

#include "basedefs.h"

uasm_PACK_PUSH_STACK

//extern const char *MsgGet( int, char * );
extern const char* MsgGetEx(int); /* doesn't need a buffer */

uasm_PACK_POP

#endif
