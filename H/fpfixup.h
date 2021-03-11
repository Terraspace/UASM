#pragma once

#ifndef _FPFIXUP_H_INCLUDED
#define _FPFIXUP_H_INCLUDED

#include "basedefs.h"

uasm_PACK_PUSH_STACK

extern void AddFloatingPointEmulationFixup(struct code_info*);

uasm_PACK_POP

#endif
