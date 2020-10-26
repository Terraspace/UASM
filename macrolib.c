#include "globals.h"
#if (defined(BUILD_MACROLIB) && (BUILD_MACROLIB >= 1))
#include <ctype.h>
#include <time.h>
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
#include "symbols.h"
#include "macrolib.h"

extern void     AddLineQueue(const char* line);
extern void     AddLineQueueX(const char* fmt, ...);

void Adddefs()
{
    AddLineQueue("IFNDEF WITHMACROLIB");
    AddLineQueue(" WITHMACROLIB EQU 1");
    AddLineQueue("ENDIF");
    RunLineQueue();
    /* detect casemap */
    if (Options.case_sensitive && !Options.convert_uppercase)
    {
        AddLineQueue("IFNDEF CASEMAPNONE");
        AddLineQueue("CASEMAPNONE EQU 1");
        AddLineQueue("ENDIF");
    }
}

void CreateMacroLibCases(void)
{
    /* Create case alternative names for macrolib functions */
    if (ModuleInfo.case_sensitive && !ModuleInfo.convert_uppercase)
    {
        AddLineQueue("IFNDEF CASEMAPNONE");
        AddLineQueue("CASEMAPNONE EQU 1");
        AddLineQueue("ENDIF");
        AddLineQueue("IFDEF CASEMAPNONE");
        AddLineQueue("casemapnone EQU CASEMAPNONE");
        AddLineQueue("ENDIF");
        AddLineQueue("IFNDEF WITHMACROLIB");
        AddLineQueue("withmacrolib EQU WITHMACROLIB");
        AddLineQueue("ENDIF");
    }
}

#endif //BUILD_MACROLIB
