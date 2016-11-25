
#ifndef _ORGFIXUP_H_INCLUDED
#define _ORGFIXUP_H_INCLUDED

struct orgFixup
{
	int startPos;
	int orgValue;
	void *pNext;
};

extern void AddOrgFixup(int curPos, int orgValue);

extern void ResetOrgFixup();

extern bool InOrgRange(int position);

#endif
