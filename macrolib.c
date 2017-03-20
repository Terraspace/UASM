
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
	char *macDef = "@CSTR macro Text:VARARG";
	char *macCode[] = { "local szText", ".data", "szText db Text,0", ".code", "exitm <szText>", "endm", NULL };
	struct dsym *mac = CreateMacro("@CSTR");

	char *macDef2 = "@WSTR macro Text:VARARG";
	char *macCode2[] = { "local szText", ".data", "szText dw Text,0", ".code", "exitm <szText>", "endm", NULL };
	struct dsym *mac2 = CreateMacro("@WSTR");

	char *macDef1 = "@FP4 macro value:REQ";
	char *macCode1[] = { "local vname", ".data","align 4", "vname REAL4 value", ".code", "exitm <vname>", "endm", NULL };
	struct dsym *mac1 = CreateMacro("@FP4");

	char *macDef3 = "@FP8 macro value:REQ";
	char *macCode3[] = { "local vname", ".data","align 8", "vname REAL8 value", ".code", "exitm <vname>", "endm", NULL };
	struct dsym *mac3 = CreateMacro("@FP8");

	char *macDef4 = "@FP10 macro value:REQ";
	char *macCode4[] = { "local vname", ".data","align 8", "vname REAL10 value", ".code", "exitm <vname>", "endm", NULL };
	struct dsym *mac4 = CreateMacro("@FP10");

	/* ASCIIZ String Inline MACRO */
	ModuleInfo.token_count = Tokenize(macDef, 0, ModuleInfo.tokenarray, 0);
	StoreAutoMacro(mac, 2, ModuleInfo.tokenarray, TRUE, macCode);

	/* Unicode String Inline MACRO */
	ModuleInfo.token_count = Tokenize(macDef2, 0, ModuleInfo.tokenarray, 0);
	StoreAutoMacro(mac2, 2, ModuleInfo.tokenarray, TRUE, macCode2);
	
	/* FP4 and FP8 */
	ModuleInfo.token_count = Tokenize(macDef1, 0, ModuleInfo.tokenarray, 0);
	StoreAutoMacro(mac1, 2, ModuleInfo.tokenarray, TRUE, macCode1);
	//-----
	ModuleInfo.token_count = Tokenize(macDef3, 0, ModuleInfo.tokenarray, 0);
	StoreAutoMacro(mac3, 2, ModuleInfo.tokenarray, TRUE, macCode3);
	//-----
	ModuleInfo.token_count = Tokenize(macDef4, 0, ModuleInfo.tokenarray, 0);
	StoreAutoMacro(mac4, 2, ModuleInfo.tokenarray, TRUE, macCode4);

}