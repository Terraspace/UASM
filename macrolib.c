
#include <ctype.h>
#include <time.h>
#include "globals.h"
#include "memalloc.h"
#include "input.h"
#include "parser.h"
#include "reswords.h"
#include "tokenize.h"
#include "condasm.h"
#include "segment.h"
#include "assume.h"
#include "proc.h"
#include "expreval.h"
#include "hll.h"
#include "context.h"
#include "types.h"
#include "label.h"
#include "macro.h"
#include "extern.h"
#include "fixup.h"
#include "omf.h"
#include "fastpass.h"
#include "listing.h"
#include "msgtext.h"
#include "myassert.h"
#include "linnum.h"
#include "cpumodel.h"
#include "lqueue.h"

#include "orgfixup.h"

#include "macrolib.h"

/* Compile a library of built-in macros */
void CompileMacros( void )
{
	
	/* ASCIIZ String Inline MACRO */
	char *macDef = "_C macro Text:VARARG";
	char *macCode[] = { "local szText", ".data", "szText db Text,0", ".code", "exitm <szText>", "endm", NULL };
	struct dsym *mac = CreateMacro("_C");
	Tokenize(macDef, 0, ModuleInfo.tokenarray, 0);
	ModuleInfo.token_count = 5;
	StoreAutoMacro(mac, 2, ModuleInfo.tokenarray, TRUE, macCode);


}