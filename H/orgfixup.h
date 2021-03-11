#pragma once

#ifndef _ORGFIXUP_H_INCLUDED
#define _ORGFIXUP_H_INCLUDED

#include "basedefs.h"

uasm_PACK_PUSH_STACK

struct orgFixup
{
    int startPos;
    int orgValue;
    void* pNext;
};

extern void AddOrgFixup(int curPos, int orgValue);

extern void ResetOrgFixup();

extern bool InOrgRange(int position);

uasm_PACK_POP

#endif
