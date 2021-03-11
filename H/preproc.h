#pragma once

#ifndef _PREPROC_H_INCLUDED
#define _PREPROC_H_INCLUDED

/* v2.11: preprocessor functions moved from input.c to preproc.c */

#include "basedefs.h"

uasm_PACK_PUSH_STACK

extern int      PreprocessLine(char*, struct asm_tok[]);
extern ret_code WriteCodeLabel(char*, struct asm_tok[]);

uasm_PACK_POP

#endif
