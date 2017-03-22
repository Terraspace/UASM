
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

#define MACRO_COUNT 10

/* MACRO names */
char *macName[] = {
	"@CSTR", "@WSTR", "FP4", "FP8", "FP10", "LOADSS", "LOADSD", "LOADPS", "MEMALIGN", "RV"
};

/* MACRO definitions */
char *macDef[] = {
	"@CSTR macro Text:VARARG",
	"@WSTR macro Text:VARARG",
	"FP4 macro value:REQ",
	"FP8 macro value:REQ",
	"FP10 macro value:REQ",
	"LOADSS MACRO reg, val",
	"LOADSD MACRO reg, val",
	"LOADPS MACRO reg, val",
	"MEMALIGN MACRO reg, number",
	"RV MACRO FuncName:REQ, args:VARARG"
};

/* 
Create the built-in macro library 
This is called once initially as the macros always exist
*/
void InitAutoMacros(void)
{
	struct dsym *mac;
	uint_32 i = 0;
	uint_32 j = 0;
	uint_32 k = 0;
	uint_32 start_pos = 0;
	char  *macCodePtr[MACRO_COUNT];

	uint_32 macroLen[] = { 6, 6, 7, 7, 7, 8, 8, 10, 3, 7 };
	char *macCode[] = {
		"local szText", ".data", "szText db Text,0", ".code", "exitm <szText>", "endm", NULL,
		"local szText", ".data", "szText dw Text,0", ".code", "exitm <szText>", "endm", NULL,
		"local vname", ".data", "align 4", "vname REAL4 value", ".code", "exitm <vname>", "endm", NULL,
		"local vname", ".data", "align 8", "vname REAL8 value", ".code", "exitm <vname>", "endm", NULL,
		"local vname", ".data", "align 8", "vname REAL10 value", ".code", "exitm <vname>", "endm", NULL,
		"IF @Arch EQ 0", "mov eax, val", "movd reg, eax", "ELSE", "mov eax, val", "vmovd reg, eax", "ENDIF", "ENDM", NULL,
		"IF @Arch EQ 0", "mov rax, val", "movq reg, rax", "ELSE", "mov rax, val", "vmovq reg, rax", "ENDIF", "ENDM", NULL,
		"IF @Arch EQ 0", "mov eax, val", "movd reg, eax", "pshufd reg, 0", "ELSE", "mov eax, val", "vmovd reg, eax", "vpshufd reg, 0", "ENDIF", "ENDM", NULL,
		"add reg, number - 1", "and reg, -number", "ENDM", NULL,
		"arg equ <invoke FuncName>", "FOR var, <args>", "arg CATSTR arg, <, expand_prefix(reparg(var))>", "ENDM", "arg", "EXITM <rax>", "ENDM", NULL
	};

	/* Compile Macros */
	for (i = 0; i < MACRO_COUNT; i++)
	{
		mac = CreateMacro(macName[i]);
		ModuleInfo.token_count = Tokenize(macDef[i], 0, ModuleInfo.tokenarray, 0);
		StoreAutoMacro(mac, 2, ModuleInfo.tokenarray, TRUE, macCode, start_pos, macroLen[i]);
		start_pos += macroLen[i] + 1;
	}
}
