
#include <ctype.h>
#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "myassert.h"

#include "orgfixup.h"

struct orgFixup *pOrgTable = NULL;

void AddOrgFixup(int curPos, int orgValue)
{
	struct orgFixup *curPtr = pOrgTable;
	struct orgFixup *pFixup = (struct orgFixup*)malloc(sizeof(struct orgFixup));
	pFixup->startPos = curPos;
	pFixup->orgValue = orgValue;
	pFixup->pNext = NULL;
	if (!curPtr)
	{
		curPtr = pFixup;
		pOrgTable = pFixup;
	}
	else
	{
		while (curPtr->pNext != NULL)
			curPtr = curPtr->pNext;
		curPtr->pNext = pFixup;
	}
	return;
}

void ResetOrgFixup()
{
	struct orgFixup *curPtr = pOrgTable;
	struct orgFixup *nextPtr;

	if (!curPtr)
		return;

	nextPtr = curPtr->pNext;

	while (curPtr != NULL)
	{
		nextPtr = curPtr->pNext;
		free(curPtr);
		curPtr = nextPtr;
	}
	pOrgTable = NULL;
}

bool InOrgRange(int position)
{
	struct orgFixup *curPtr = pOrgTable;
	bool retval = FALSE;
	if (curPtr)
	{
		while (curPtr)
		{
			if (position >= curPtr->startPos && position < curPtr->orgValue)
			{
				retval = TRUE;
				break;
			}
			curPtr = curPtr->pNext;
		}
	}
	return(retval);
}