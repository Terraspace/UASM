
#if !(NOX86MACROLIB)
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
#include "symbols.h"
#include "x86macros.h"

extern void     AddLineQueue(const char *line);
extern void     AddLineQueueX(const char *fmt, ...);

void Addx86defs()
{
	struct asym* sym = 0;

	AddLineQueue("IF @Platform EQ 0");
	AddLineQueue("IFNDEF WIN32");
	AddLineQueue("DEFINE WIN32");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF _WIN32");
	AddLineQueue("DEFINE _WIN32");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __WIN32");
	AddLineQueue("DEFINE __WIN32");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __WIN32__");
	AddLineQueue("DEFINE __WIN32__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF _M_IX86");
	AddLineQueue("DEFINE _M_IX86");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __X86__");
	AddLineQueue("DEFINE __X86__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __X86");
	AddLineQueue("DEFINE __X86");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF WINDOWS");
	AddLineQueue("DEFINE WINDOWS");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF _WINDOWS");
	AddLineQueue("DEFINE _WINDOWS");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __WINDOWS");
	AddLineQueue("DEFINE __WINDOWS");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __WINDOWS__");
	AddLineQueue("DEFINE __WINDOWS__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __X32__");
	AddLineQueue("DEFINE __X32__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __X32");
	AddLineQueue("DEFINE __X32");
	AddLineQueue("ENDIF");
	AddLineQueue("IFDEF __KNC__");
	AddLineQueue(".ERR <KNC not available in windows>");
	AddLineQueue("ENDIF");
	AddLineQueue("IFDEF __MIC__");
	AddLineQueue(".ERR <MIC not available in windows>");
	AddLineQueue("ENDIF");
	AddLineQueue("ENDIF");

	AddLineQueue("IF @Platform EQ 1");
	AddLineQueue("IFNDEF WIN64");
	AddLineQueue("DEFINE WIN64");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF _WIN64");
	AddLineQueue("DEFINE _WIN64");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __WIN64");
	AddLineQueue("DEFINE __WIN64");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __WIN64__");
	AddLineQueue("DEFINE __WIN64__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF _M_AMD64");
	AddLineQueue("DEFINE _M_AMD64");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __X86_64__");
	AddLineQueue("DEFINE __X86_64__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __X86_64");
	AddLineQueue("DEFINE __X86_64");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF WINDOWS");
	AddLineQueue("DEFINE WINDOWS");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF _WINDOWS");
	AddLineQueue("DEFINE _WINDOWS");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __WINDOWS");
	AddLineQueue("DEFINE __WINDOWS");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __WINDOWS__");
	AddLineQueue("DEFINE __WINDOWS__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __X64__");
	AddLineQueue("DEFINE __X64__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __X64");
	AddLineQueue("DEFINE __X64");
	AddLineQueue("ENDIF");
	AddLineQueue("IFDEF __KNC__");
	AddLineQueue(".ERR <KNC not available in windows>");
	AddLineQueue("ENDIF");
	AddLineQueue("IFDEF __MIC__");
	AddLineQueue(".ERR <MIC not available in windows>");
	AddLineQueue("ENDIF");
	AddLineQueue("ENDIF");

	AddLineQueue("IF @Platform EQ 2");
	AddLineQueue("IFNDEF __I386__");
	AddLineQueue("DEFINE __I386__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __I386");
	AddLineQueue("DEFINE __I386");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __X86__");
	AddLineQueue("DEFINE __X86__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __X86");
	AddLineQueue("DEFINE __X86");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF UNIX32");
	AddLineQueue("DEFINE UNIX32");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __UNIX32__");
	AddLineQueue("DEFINE __UNIX32__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __UNIX32");
	AddLineQueue("DEFINE __UNIX32");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF UNIX");
	AddLineQueue("DEFINE UNIX");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __UNIX__");
	AddLineQueue("DEFINE __UNIX__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __UNIX");
	AddLineQueue("DEFINE __UNIX");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF LINUX32");
	AddLineQueue("DEFINE LINUX32");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __LINUX32__");
	AddLineQueue("DEFINE __LINUX32__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __LINUX32");
	AddLineQueue("DEFINE __LINUX32");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF LINUX");
	AddLineQueue("DEFINE LINUX");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __LINUX__");
	AddLineQueue("DEFINE __LINUX__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __LINUX");
	AddLineQueue("DEFINE __LINUX");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __X32__");
	AddLineQueue("DEFINE __X32__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __X32");
	AddLineQueue("DEFINE __X32");
	AddLineQueue("ENDIF");
	AddLineQueue("IFDEF __KNC__");
	AddLineQueue(".ERR <KNC not available in unix/linux 32-bits>");
	AddLineQueue("ENDIF");
	AddLineQueue("IFDEF __MIC__");
	AddLineQueue(".ERR <MIC not available in unix/linux 32-bits>");
	AddLineQueue("ENDIF");
	AddLineQueue("ENDIF");

	AddLineQueue("IF @Platform EQ 3");
	AddLineQueue("IFNDEF __X86_64__");
	AddLineQueue("DEFINE __X86_64__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __X86_64");
	AddLineQueue("DEFINE __X86_64");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF UNIX64");
	AddLineQueue("DEFINE UNIX64");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __UNIX64__");
	AddLineQueue("DEFINE __UNIX64__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __UNIX64");
	AddLineQueue("DEFINE __UNIX64");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF UNIX");
	AddLineQueue("DEFINE UNIX");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __UNIX__");
	AddLineQueue("DEFINE __UNIX__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __UNIX");
	AddLineQueue("DEFINE __UNIX");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF LINUX64");
	AddLineQueue("DEFINE LINUX64");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __LINUX64__");
	AddLineQueue("DEFINE __LINUX64__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __LINUX64");
	AddLineQueue("DEFINE __LINUX64");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF LINUX");
	AddLineQueue("DEFINE LINUX");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __LINUX__");
	AddLineQueue("DEFINE __LINUX__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __LINUX");
	AddLineQueue("DEFINE __LINUX");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __X64__");
	AddLineQueue("DEFINE __X64__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __X64");
	AddLineQueue("DEFINE __X64");
	AddLineQueue("ENDIF");
	AddLineQueue("ENDIF");

	AddLineQueue("IF @Platform EQ 4");
	AddLineQueue("IFNDEF __X86_64__");
	AddLineQueue("DEFINE __X86_64__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __X86_64");
	AddLineQueue("DEFINE __X86_64");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF UNIX64");
	AddLineQueue("DEFINE UNIX64");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __UNIX64__");
	AddLineQueue("DEFINE __UNIX64__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __UNIX64");
	AddLineQueue("DEFINE __UNIX64");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF UNIX");
	AddLineQueue("DEFINE UNIX");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __UNIX__");
	AddLineQueue("DEFINE __UNIX__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __UNIX");
	AddLineQueue("DEFINE __UNIX");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF MACH");
	AddLineQueue("DEFINE MACH");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __MACH");
	AddLineQueue("DEFINE __MACH");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __MACH__");
	AddLineQueue("DEFINE __MACH__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF APPLE");
	AddLineQueue("DEFINE APPLE");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __APPLE");
	AddLineQueue("DEFINE __APPLE");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __APPLE__");
	AddLineQueue("DEFINE __APPLE__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __X64__");
	AddLineQueue("DEFINE __X64__");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF __X64");
	AddLineQueue("DEFINE __X64");
	AddLineQueue("ENDIF");
	AddLineQueue("IFDEF __KNC__");
	AddLineQueue(".ERR <KNC not available in MAC OS>");
	AddLineQueue("ENDIF");
	AddLineQueue("IFDEF __MIC__");
	AddLineQueue(".ERR <MIC not available in MAC OS>");
	AddLineQueue("ENDIF");
	AddLineQueue("ENDIF");

	AddLineQueue("IFDEF __WIN64__");
	AddLineQueue("IFNDEF DEFINED_VECTORCALL");
	AddLineQueue("DEFINE DEFINED_VECTORCALL");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF CALLCONV");
	AddLineQueue("CALLCONV TEXTEQU <VECTORCALL>");
	AddLineQueue("ENDIF");
	AddLineQueue("CALLCONVOPT TEXTEQU <option language:VECTORCALL>");
	if (ModuleInfo.langtype == LANG_REGCALL)
	{
		/* 64bits*/
		AddLineQueue("RRET TEXTEQU <RAX>");
		AddLineQueue("RRETURN TEXTEQU <RAX>");
		AddLineQueue("RSIDX TEXTEQU <RSI>");
		AddLineQueue("RDIDX TEXTEQU <RDI>");
		AddLineQueue("RBPTR TEXTEQU <RBP>");
		AddLineQueue("RSPTR TEXTEQU <RSP>");
		AddLineQueue("RBASE TEXTEQU <RBX>");
		AddLineQueue("RPARAM0 TEXTEQU <RAX>");
		AddLineQueue("RPARAM1 TEXTEQU <RCX>");
		AddLineQueue("RPARAM2 TEXTEQU <RDX>");
		AddLineQueue("RPARAM3 TEXTEQU <RDI>");
		AddLineQueue("RPARAM4 TEXTEQU <RSI>");
		AddLineQueue("RPARAM5 TEXTEQU <R8>");
		AddLineQueue("RPARAM6 TEXTEQU <R9>");
		AddLineQueue("RPARAM7 TEXTEQU <R11>");
		AddLineQueue("RPARAM8 TEXTEQU <R12>");
		AddLineQueue("RPARAM9 TEXTEQU <R14>");
		AddLineQueue("RPARAM10 TEXTEQU <R15>");
		AddLineQueue("RPARAM11 TEXTEQU <[RSP+96]>");
		AddLineQueue("RPARAM12 TEXTEQU <[RSP+104]>");
		AddLineQueue("RPARAM13 TEXTEQU <[RSP+112]>");
		AddLineQueue("RPARAM14 TEXTEQU <[RSP+120]>");
		AddLineQueue("RPARAM15 TEXTEQU <[RSP+128]>");
		AddLineQueue("RPARAM16 TEXTEQU <[RSP+136]>");
		AddLineQueue("RPARAM17 TEXTEQU <[RSP+144]>");
		AddLineQueue("RPARAM18 TEXTEQU <[RSP+152]>");
		AddLineQueue("RPARAM19 TEXTEQU <[RSP+160]>");
		AddLineQueue("RPARAM20 TEXTEQU <[RSP+168]>");
		AddLineQueue("RPARAM21 TEXTEQU <[RSP+176]>");
		AddLineQueue("RPARAM22 TEXTEQU <[RSP+184]>");
		AddLineQueue("RPARAM23 TEXTEQU <[RSP+192]>");
		AddLineQueue("RPARAM24 TEXTEQU <[RSP+200]>");
		AddLineQueue("RPARAM25 TEXTEQU <[RSP+208]>");
		AddLineQueue("RPARAM26 TEXTEQU <[RSP+216]>");
		AddLineQueue("RPARAM27 TEXTEQU <[RSP+224]>");
		AddLineQueue("RPARAM28 TEXTEQU <[RSP+232]>");
		AddLineQueue("RPARAM29 TEXTEQU <[RSP+240]>");
		AddLineQueue("RPARAM30 TEXTEQU <[RSP+248]>");
		AddLineQueue("RPARAM31 TEXTEQU <[RSP+256]>");
		AddLineQueue("RPARAM32 TEXTEQU <[RSP+264]>");
		AddLineQueue("RPARAM33 TEXTEQU <[RSP+272]>");
		AddLineQueue("RPARAM34 TEXTEQU <[RSP+280]>");
		AddLineQueue("RPARAM35 TEXTEQU <[RSP+288]>");
		AddLineQueue("RPARAM36 TEXTEQU <[RSP+296]>");
		AddLineQueue("RPARAM37 TEXTEQU <[RSP+304]>");
		AddLineQueue("RPARAM38 TEXTEQU <[RSP+312]>");
		AddLineQueue("RPARAM39 TEXTEQU <[RSP+320]>");
		AddLineQueue("RPARAM40 TEXTEQU <[RSP+328]>");
		AddLineQueue("RPARAM41 TEXTEQU <[RSP+336]>");
		AddLineQueue("RPARAM42 TEXTEQU <[RSP+344]>");
		AddLineQueue("RPARAM43 TEXTEQU <[RSP+352]>");
		AddLineQueue("RPARAM44 TEXTEQU <[RSP+360]>");
		AddLineQueue("RPARAM45 TEXTEQU <[RSP+368]>");
		AddLineQueue("RPARAM46 TEXTEQU <[RSP+376]>");
		AddLineQueue("RPARAM47 TEXTEQU <[RSP+384]>");
		AddLineQueue("RPARAM48 TEXTEQU <[RSP+392]>");
		AddLineQueue("RPARAM49 TEXTEQU <[RSP+400]>");
		AddLineQueue("RPARAM50 TEXTEQU <[RSP+408]>");
		AddLineQueue("RPARAM51 TEXTEQU <[RSP+416]>");
		AddLineQueue("RPARAM52 TEXTEQU <[RSP+424]>");
		AddLineQueue("RPARAM53 TEXTEQU <[RSP+432]>");
		AddLineQueue("RPARAM54 TEXTEQU <[RSP+440]>");
		AddLineQueue("RPARAM55 TEXTEQU <[RSP+448]>");
		AddLineQueue("RPARAM56 TEXTEQU <[RSP+456]>");
		AddLineQueue("RPARAM57 TEXTEQU <[RSP+464]>");
		AddLineQueue("RPARAM58 TEXTEQU <[RSP+472]>");
		AddLineQueue("RPARAM59 TEXTEQU <[RSP+480]>");
		AddLineQueue("RPARAM60 TEXTEQU <[RSP+488]>");
		AddLineQueue("RPARAM61 TEXTEQU <[RSP+496]>");
		AddLineQueue("RPARAM62 TEXTEQU <[RSP+504]>");
		AddLineQueue("RPARAM63 TEXTEQU <[RSP+512]>");
		/* 32bits*/
		AddLineQueue("DRET TEXTEQU <EAX>");
		AddLineQueue("DRETURN TEXTEQU <EAX>");
		AddLineQueue("DSIDX TEXTEQU <ESI>");
		AddLineQueue("DDIDX TEXTEQU <EDI>");
		AddLineQueue("DBPTR TEXTEQU <EBP>");
		AddLineQueue("DSPTR TEXTEQU <ESP>");
		AddLineQueue("DBASE TEXTEQU <EBX>");
		AddLineQueue("DPARAM0 TEXTEQU <EAX>");
		AddLineQueue("DPARAM1 TEXTEQU <ECX>");
		AddLineQueue("DPARAM2 TEXTEQU <EDX>");
		AddLineQueue("DPARAM3 TEXTEQU <EDI>");
		AddLineQueue("DPARAM4 TEXTEQU <ESI>");
		AddLineQueue("DPARAM5 TEXTEQU <R8D>");
		AddLineQueue("DPARAM6 TEXTEQU <R9D>");
		AddLineQueue("DPARAM7 TEXTEQU <R11D>");
		AddLineQueue("DPARAM8 TEXTEQU <R12D>");
		AddLineQueue("DPARAM9 TEXTEQU <R14D>");
		AddLineQueue("DPARAM10 TEXTEQU <R15D>");
		AddLineQueue("DPARAM11 TEXTEQU <[ESP+48]>");
		AddLineQueue("DPARAM12 TEXTEQU <[ESP+52]>");
		AddLineQueue("DPARAM13 TEXTEQU <[ESP+56]>");
		AddLineQueue("DPARAM14 TEXTEQU <[ESP+60]>");
		AddLineQueue("DPARAM15 TEXTEQU <[ESP+64]>");
		AddLineQueue("DPARAM16 TEXTEQU <[ESP+68]>");
		AddLineQueue("DPARAM17 TEXTEQU <[ESP+72]>");
		AddLineQueue("DPARAM18 TEXTEQU <[ESP+76]>");
		AddLineQueue("DPARAM19 TEXTEQU <[ESP+80]>");
		AddLineQueue("DPARAM20 TEXTEQU <[ESP+84]>");
		AddLineQueue("DPARAM21 TEXTEQU <[ESP+88]>");
		AddLineQueue("DPARAM22 TEXTEQU <[ESP+92]>");
		AddLineQueue("DPARAM23 TEXTEQU <[ESP+96]>");
		AddLineQueue("DPARAM24 TEXTEQU <[ESP+100]>");
		AddLineQueue("DPARAM25 TEXTEQU <[ESP+104]>");
		AddLineQueue("DPARAM26 TEXTEQU <[ESP+108]>");
		AddLineQueue("DPARAM27 TEXTEQU <[ESP+112]>");
		AddLineQueue("DPARAM28 TEXTEQU <[ESP+116]>");
		AddLineQueue("DPARAM29 TEXTEQU <[ESP+120]>");
		AddLineQueue("DPARAM30 TEXTEQU <[ESP+124]>");
		AddLineQueue("DPARAM31 TEXTEQU <[ESP+128]>");
		AddLineQueue("DPARAM32 TEXTEQU <[ESP+132]>");
		AddLineQueue("DPARAM33 TEXTEQU <[ESP+136]>");
		AddLineQueue("DPARAM34 TEXTEQU <[ESP+140]>");
		AddLineQueue("DPARAM35 TEXTEQU <[ESP+144]>");
		AddLineQueue("DPARAM36 TEXTEQU <[ESP+148]>");
		AddLineQueue("DPARAM37 TEXTEQU <[ESP+152]>");
		AddLineQueue("DPARAM38 TEXTEQU <[ESP+156]>");
		AddLineQueue("DPARAM39 TEXTEQU <[ESP+160]>");
		AddLineQueue("DPARAM40 TEXTEQU <[ESP+164]>");
		AddLineQueue("DPARAM41 TEXTEQU <[ESP+168]>");
		AddLineQueue("DPARAM42 TEXTEQU <[ESP+172]>");
		AddLineQueue("DPARAM43 TEXTEQU <[ESP+176]>");
		AddLineQueue("DPARAM44 TEXTEQU <[ESP+180]>");
		AddLineQueue("DPARAM45 TEXTEQU <[ESP+184]>");
		AddLineQueue("DPARAM46 TEXTEQU <[ESP+188]>");
		AddLineQueue("DPARAM47 TEXTEQU <[ESP+192]>");
		AddLineQueue("DPARAM48 TEXTEQU <[ESP+196]>");
		AddLineQueue("DPARAM49 TEXTEQU <[ESP+200]>");
		AddLineQueue("DPARAM50 TEXTEQU <[ESP+204]>");
		AddLineQueue("DPARAM51 TEXTEQU <[ESP+208]>");
		AddLineQueue("DPARAM52 TEXTEQU <[ESP+212]>");
		AddLineQueue("DPARAM53 TEXTEQU <[ESP+216]>");
		AddLineQueue("DPARAM54 TEXTEQU <[ESP+220]>");
		AddLineQueue("DPARAM55 TEXTEQU <[ESP+224]>");
		AddLineQueue("DPARAM56 TEXTEQU <[ESP+228]>");
		AddLineQueue("DPARAM57 TEXTEQU <[ESP+232]>");
		AddLineQueue("DPARAM58 TEXTEQU <[ESP+236]>");
		AddLineQueue("DPARAM59 TEXTEQU <[ESP+240]>");
		AddLineQueue("DPARAM60 TEXTEQU <[ESP+244]>");
		AddLineQueue("DPARAM61 TEXTEQU <[ESP+248]>");
		AddLineQueue("DPARAM62 TEXTEQU <[ESP+252]>");
		AddLineQueue("DPARAM63 TEXTEQU <[ESP+256]>");
		/* 16bits*/
		AddLineQueue("WRET TEXTEQU <AX>");
		AddLineQueue("WRETURN TEXTEQU <AX>");
		AddLineQueue("WSIDX TEXTEQU <SI>");
		AddLineQueue("WDIDX TEXTEQU <DI>");
		AddLineQueue("WBPTR TEXTEQU <BP>");
		AddLineQueue("WSPTR TEXTEQU <SP>");
		AddLineQueue("WBASE TEXTEQU <BX>");
		AddLineQueue("WPARAM0 TEXTEQU <AX>");
		AddLineQueue("WPARAM1 TEXTEQU <CX>");
		AddLineQueue("WPARAM2 TEXTEQU <DX>");
		AddLineQueue("WPARAM3 TEXTEQU <DI>");
		AddLineQueue("WPARAM4 TEXTEQU <SI>");
		AddLineQueue("WPARAM5 TEXTEQU <R8W>");
		AddLineQueue("WPARAM6 TEXTEQU <R9W>");
		AddLineQueue("WPARAM7 TEXTEQU <R11W>");
		AddLineQueue("WPARAM8 TEXTEQU <R12W>");
		AddLineQueue("WPARAM9 TEXTEQU <R14W>");
		AddLineQueue("WPARAM10 TEXTEQU <R15W>");
		AddLineQueue("WPARAM11 TEXTEQU <[SP+24]>");
		AddLineQueue("WPARAM12 TEXTEQU <[SP+26]>");
		AddLineQueue("WPARAM13 TEXTEQU <[SP+28]>");
		AddLineQueue("WPARAM14 TEXTEQU <[SP+30]>");
		AddLineQueue("WPARAM15 TEXTEQU <[SP+32]>");
		AddLineQueue("WPARAM16 TEXTEQU <[SP+34]>");
		AddLineQueue("WPARAM17 TEXTEQU <[SP+36]>");
		AddLineQueue("WPARAM18 TEXTEQU <[SP+38]>");
		AddLineQueue("WPARAM19 TEXTEQU <[SP+40]>");
		AddLineQueue("WPARAM20 TEXTEQU <[SP+42]>");
		AddLineQueue("WPARAM21 TEXTEQU <[SP+44]>");
		AddLineQueue("WPARAM22 TEXTEQU <[SP+46]>");
		AddLineQueue("WPARAM23 TEXTEQU <[SP+48]>");
		AddLineQueue("WPARAM24 TEXTEQU <[SP+50]>");
		AddLineQueue("WPARAM25 TEXTEQU <[SP+52]>");
		AddLineQueue("WPARAM26 TEXTEQU <[SP+54]>");
		AddLineQueue("WPARAM27 TEXTEQU <[SP+56]>");
		AddLineQueue("WPARAM28 TEXTEQU <[SP+58]>");
		AddLineQueue("WPARAM29 TEXTEQU <[SP+60]>");
		AddLineQueue("WPARAM30 TEXTEQU <[SP+62]>");
		AddLineQueue("WPARAM31 TEXTEQU <[SP+64]>");
		AddLineQueue("WPARAM32 TEXTEQU <[SP+66]>");
		AddLineQueue("WPARAM33 TEXTEQU <[SP+68]>");
		AddLineQueue("WPARAM34 TEXTEQU <[SP+70]>");
		AddLineQueue("WPARAM35 TEXTEQU <[SP+72]>");
		AddLineQueue("WPARAM36 TEXTEQU <[SP+74]>");
		AddLineQueue("WPARAM37 TEXTEQU <[SP+76]>");
		AddLineQueue("WPARAM38 TEXTEQU <[SP+78]>");
		AddLineQueue("WPARAM39 TEXTEQU <[SP+80]>");
		AddLineQueue("WPARAM40 TEXTEQU <[SP+82]>");
		AddLineQueue("WPARAM41 TEXTEQU <[SP+84]>");
		AddLineQueue("WPARAM42 TEXTEQU <[SP+86]>");
		AddLineQueue("WPARAM43 TEXTEQU <[SP+88]>");
		AddLineQueue("WPARAM44 TEXTEQU <[SP+90]>");
		AddLineQueue("WPARAM45 TEXTEQU <[SP+92]>");
		AddLineQueue("WPARAM46 TEXTEQU <[SP+94]>");
		AddLineQueue("WPARAM47 TEXTEQU <[SP+96]>");
		AddLineQueue("WPARAM48 TEXTEQU <[SP+98]>");
		AddLineQueue("WPARAM49 TEXTEQU <[SP+100]>");
		AddLineQueue("WPARAM50 TEXTEQU <[SP+102]>");
		AddLineQueue("WPARAM51 TEXTEQU <[SP+104]>");
		AddLineQueue("WPARAM52 TEXTEQU <[SP+106]>");
		AddLineQueue("WPARAM53 TEXTEQU <[SP+108]>");
		AddLineQueue("WPARAM54 TEXTEQU <[SP+110]>");
		AddLineQueue("WPARAM55 TEXTEQU <[SP+112]>");
		AddLineQueue("WPARAM56 TEXTEQU <[SP+114]>");
		AddLineQueue("WPARAM57 TEXTEQU <[SP+116]>");
		AddLineQueue("WPARAM58 TEXTEQU <[SP+118]>");
		AddLineQueue("WPARAM59 TEXTEQU <[SP+120]>");
		AddLineQueue("WPARAM60 TEXTEQU <[SP+122]>");
		AddLineQueue("WPARAM61 TEXTEQU <[SP+124]>");
		AddLineQueue("WPARAM62 TEXTEQU <[SP+126]>");
		AddLineQueue("WPARAM63 TEXTEQU <[SP+128]>");
		/* 8bits*/
		AddLineQueue("BRET TEXTEQU <AL>");
		AddLineQueue("BRETURN TEXTEQU <AL>");
		AddLineQueue("BSIDX TEXTEQU <SIL>");
		AddLineQueue("BDIDX TEXTEQU <DIL>");
		AddLineQueue("BBPTR TEXTEQU <BPL>");
		AddLineQueue("BSPTR TEXTEQU <SPL>");
		AddLineQueue("BBASE TEXTEQU <BL>");
		AddLineQueue("BPARAM0 TEXTEQU <AL>");
		AddLineQueue("BPARAM1 TEXTEQU <CL>");
		AddLineQueue("BPARAM2 TEXTEQU <DL>");
		AddLineQueue("BPARAM3 TEXTEQU <DIL>");
		AddLineQueue("BPARAM4 TEXTEQU <SIL>");
		AddLineQueue("BPARAM5 TEXTEQU <R8L>");
		AddLineQueue("BPARAM6 TEXTEQU <R9L>");
		AddLineQueue("BPARAM7 TEXTEQU <R11L>");
		AddLineQueue("BPARAM8 TEXTEQU <R12L>");
		AddLineQueue("BPARAM9 TEXTEQU <R14L>");
		AddLineQueue("BPARAM10 TEXTEQU <R15L>");
		AddLineQueue("BPARAM11 TEXTEQU <[SPL+12]>");
		AddLineQueue("BPARAM12 TEXTEQU <[SPL+13]>");
		AddLineQueue("BPARAM13 TEXTEQU <[SPL+14]>");
		AddLineQueue("BPARAM14 TEXTEQU <[SPL+15]>");
		AddLineQueue("BPARAM15 TEXTEQU <[SPL+16]>");
		AddLineQueue("BPARAM16 TEXTEQU <[SPL+17]>");
		AddLineQueue("BPARAM17 TEXTEQU <[SPL+18]>");
		AddLineQueue("BPARAM18 TEXTEQU <[SPL+19]>");
		AddLineQueue("BPARAM19 TEXTEQU <[SPL+20]>");
		AddLineQueue("BPARAM20 TEXTEQU <[SPL+21]>");
		AddLineQueue("BPARAM21 TEXTEQU <[SPL+22]>");
		AddLineQueue("BPARAM22 TEXTEQU <[SPL+23]>");
		AddLineQueue("BPARAM23 TEXTEQU <[SPL+24]>");
		AddLineQueue("BPARAM24 TEXTEQU <[SPL+25]>");
		AddLineQueue("BPARAM25 TEXTEQU <[SPL+26]>");
		AddLineQueue("BPARAM26 TEXTEQU <[SPL+27]>");
		AddLineQueue("BPARAM27 TEXTEQU <[SPL+28]>");
		AddLineQueue("BPARAM28 TEXTEQU <[SPL+29]>");
		AddLineQueue("BPARAM29 TEXTEQU <[SPL+30]>");
		AddLineQueue("BPARAM30 TEXTEQU <[SPL+31]>");
		AddLineQueue("BPARAM31 TEXTEQU <[SPL+32]>");
		AddLineQueue("BPARAM32 TEXTEQU <[SPL+33]>");
		AddLineQueue("BPARAM33 TEXTEQU <[SPL+34]>");
		AddLineQueue("BPARAM34 TEXTEQU <[SPL+35]>");
		AddLineQueue("BPARAM35 TEXTEQU <[SPL+36]>");
		AddLineQueue("BPARAM36 TEXTEQU <[SPL+37]>");
		AddLineQueue("BPARAM37 TEXTEQU <[SPL+38]>");
		AddLineQueue("BPARAM38 TEXTEQU <[SPL+39]>");
		AddLineQueue("BPARAM39 TEXTEQU <[SPL+40]>");
		AddLineQueue("BPARAM40 TEXTEQU <[SPL+41]>");
		AddLineQueue("BPARAM41 TEXTEQU <[SPL+42]>");
		AddLineQueue("BPARAM42 TEXTEQU <[SPL+43]>");
		AddLineQueue("BPARAM43 TEXTEQU <[SPL+44]>");
		AddLineQueue("BPARAM44 TEXTEQU <[SPL+45]>");
		AddLineQueue("BPARAM45 TEXTEQU <[SPL+46]>");
		AddLineQueue("BPARAM46 TEXTEQU <[SPL+47]>");
		AddLineQueue("BPARAM47 TEXTEQU <[SPL+48]>");
		AddLineQueue("BPARAM48 TEXTEQU <[SPL+49]>");
		AddLineQueue("BPARAM49 TEXTEQU <[SPL+50]>");
		AddLineQueue("BPARAM50 TEXTEQU <[SPL+51]>");
		AddLineQueue("BPARAM51 TEXTEQU <[SPL+52]>");
		AddLineQueue("BPARAM52 TEXTEQU <[SPL+53]>");
		AddLineQueue("BPARAM53 TEXTEQU <[SPL+54]>");
		AddLineQueue("BPARAM54 TEXTEQU <[SPL+55]>");
		AddLineQueue("BPARAM55 TEXTEQU <[SPL+56]>");
		AddLineQueue("BPARAM56 TEXTEQU <[SPL+57]>");
		AddLineQueue("BPARAM57 TEXTEQU <[SPL+58]>");
		AddLineQueue("BPARAM58 TEXTEQU <[SPL+59]>");
		AddLineQueue("BPARAM59 TEXTEQU <[SPL+60]>");
		AddLineQueue("BPARAM60 TEXTEQU <[SPL+61]>");
		AddLineQueue("BPARAM61 TEXTEQU <[SPL+62]>");
		AddLineQueue("BPARAM62 TEXTEQU <[SPL+63]>");
		AddLineQueue("BPARAM63 TEXTEQU <[SPL+64]>");
	}
	else
	{
		/* 64bits*/
		AddLineQueue("RRET TEXTEQU <RAX>");
		AddLineQueue("RRETURN TEXTEQU <RAX>");
		AddLineQueue("RSIDX TEXTEQU <RSI>");
		AddLineQueue("RDIDX TEXTEQU <RDI>");
		AddLineQueue("RBPTR TEXTEQU <RBP>");
		AddLineQueue("RSPTR TEXTEQU <RSP>");
		AddLineQueue("RBASE TEXTEQU <RBX>");
		AddLineQueue("RPARAM0 TEXTEQU <RCX>");
		AddLineQueue("RPARAM1 TEXTEQU <RDX>");
		AddLineQueue("RPARAM2 TEXTEQU <R8>");
		AddLineQueue("RPARAM3 TEXTEQU <R9>");
		AddLineQueue("RPARAM4 TEXTEQU <[RSP+40]>");
		AddLineQueue("RPARAM5 TEXTEQU <[RSP+48]>");
		AddLineQueue("RPARAM6 TEXTEQU <[RSP+56]>");
		AddLineQueue("RPARAM7 TEXTEQU <[RSP+64]>");
		AddLineQueue("RPARAM8 TEXTEQU <[RSP+72]>");
		AddLineQueue("RPARAM9 TEXTEQU <[RSP+80]>");
		AddLineQueue("RPARAM10 TEXTEQU <[RSP+88]>");
		AddLineQueue("RPARAM11 TEXTEQU <[RSP+96]>");
		AddLineQueue("RPARAM12 TEXTEQU <[RSP+104]>");
		AddLineQueue("RPARAM13 TEXTEQU <[RSP+112]>");
		AddLineQueue("RPARAM14 TEXTEQU <[RSP+120]>");
		AddLineQueue("RPARAM15 TEXTEQU <[RSP+128]>");
		AddLineQueue("RPARAM16 TEXTEQU <[RSP+136]>");
		AddLineQueue("RPARAM17 TEXTEQU <[RSP+144]>");
		AddLineQueue("RPARAM18 TEXTEQU <[RSP+152]>");
		AddLineQueue("RPARAM19 TEXTEQU <[RSP+160]>");
		AddLineQueue("RPARAM20 TEXTEQU <[RSP+168]>");
		AddLineQueue("RPARAM21 TEXTEQU <[RSP+176]>");
		AddLineQueue("RPARAM22 TEXTEQU <[RSP+184]>");
		AddLineQueue("RPARAM23 TEXTEQU <[RSP+192]>");
		AddLineQueue("RPARAM24 TEXTEQU <[RSP+200]>");
		AddLineQueue("RPARAM25 TEXTEQU <[RSP+208]>");
		AddLineQueue("RPARAM26 TEXTEQU <[RSP+216]>");
		AddLineQueue("RPARAM27 TEXTEQU <[RSP+224]>");
		AddLineQueue("RPARAM28 TEXTEQU <[RSP+232]>");
		AddLineQueue("RPARAM29 TEXTEQU <[RSP+240]>");
		AddLineQueue("RPARAM30 TEXTEQU <[RSP+248]>");
		AddLineQueue("RPARAM31 TEXTEQU <[RSP+256]>");
		AddLineQueue("RPARAM32 TEXTEQU <[RSP+264]>");
		AddLineQueue("RPARAM33 TEXTEQU <[RSP+272]>");
		AddLineQueue("RPARAM34 TEXTEQU <[RSP+280]>");
		AddLineQueue("RPARAM35 TEXTEQU <[RSP+288]>");
		AddLineQueue("RPARAM36 TEXTEQU <[RSP+296]>");
		AddLineQueue("RPARAM37 TEXTEQU <[RSP+304]>");
		AddLineQueue("RPARAM38 TEXTEQU <[RSP+312]>");
		AddLineQueue("RPARAM39 TEXTEQU <[RSP+320]>");
		AddLineQueue("RPARAM40 TEXTEQU <[RSP+328]>");
		AddLineQueue("RPARAM41 TEXTEQU <[RSP+336]>");
		AddLineQueue("RPARAM42 TEXTEQU <[RSP+344]>");
		AddLineQueue("RPARAM43 TEXTEQU <[RSP+352]>");
		AddLineQueue("RPARAM44 TEXTEQU <[RSP+360]>");
		AddLineQueue("RPARAM45 TEXTEQU <[RSP+368]>");
		AddLineQueue("RPARAM46 TEXTEQU <[RSP+376]>");
		AddLineQueue("RPARAM47 TEXTEQU <[RSP+384]>");
		AddLineQueue("RPARAM48 TEXTEQU <[RSP+392]>");
		AddLineQueue("RPARAM49 TEXTEQU <[RSP+400]>");
		AddLineQueue("RPARAM50 TEXTEQU <[RSP+408]>");
		AddLineQueue("RPARAM51 TEXTEQU <[RSP+416]>");
		AddLineQueue("RPARAM52 TEXTEQU <[RSP+424]>");
		AddLineQueue("RPARAM53 TEXTEQU <[RSP+432]>");
		AddLineQueue("RPARAM54 TEXTEQU <[RSP+440]>");
		AddLineQueue("RPARAM55 TEXTEQU <[RSP+448]>");
		AddLineQueue("RPARAM56 TEXTEQU <[RSP+456]>");
		AddLineQueue("RPARAM57 TEXTEQU <[RSP+464]>");
		AddLineQueue("RPARAM58 TEXTEQU <[RSP+472]>");
		AddLineQueue("RPARAM59 TEXTEQU <[RSP+480]>");
		AddLineQueue("RPARAM60 TEXTEQU <[RSP+488]>");
		AddLineQueue("RPARAM61 TEXTEQU <[RSP+496]>");
		AddLineQueue("RPARAM62 TEXTEQU <[RSP+504]>");
		AddLineQueue("RPARAM63 TEXTEQU <[RSP+512]>");
		/* 32bits*/
		AddLineQueue("DRET TEXTEQU <EAX>");
		AddLineQueue("DRETURN TEXTEQU <EAX>");
		AddLineQueue("DSIDX TEXTEQU <ESI>");
		AddLineQueue("DDIDX TEXTEQU <EDI>");
		AddLineQueue("DBPTR TEXTEQU <EBP>");
		AddLineQueue("DSPTR TEXTEQU <ESP>");
		AddLineQueue("DBASE TEXTEQU <EBX>");
		AddLineQueue("DPARAM0 TEXTEQU <ECX>");
		AddLineQueue("DPARAM1 TEXTEQU <EDX>");
		AddLineQueue("DPARAM2 TEXTEQU <R8D>");
		AddLineQueue("DPARAM3 TEXTEQU <R9D>");
		AddLineQueue("DPARAM4 TEXTEQU <[ESP+20]>");
		AddLineQueue("DPARAM5 TEXTEQU <[ESP+24]>");
		AddLineQueue("DPARAM6 TEXTEQU <[ESP+28]>");
		AddLineQueue("DPARAM7 TEXTEQU <[ESP+32]>");
		AddLineQueue("DPARAM8 TEXTEQU <[ESP+36]>");
		AddLineQueue("DPARAM9 TEXTEQU <[ESP+40]>");
		AddLineQueue("DPARAM10 TEXTEQU <[ESP+44]>");
		AddLineQueue("DPARAM11 TEXTEQU <[ESP+48]>");
		AddLineQueue("DPARAM12 TEXTEQU <[ESP+52]>");
		AddLineQueue("DPARAM13 TEXTEQU <[ESP+56]>");
		AddLineQueue("DPARAM14 TEXTEQU <[ESP+60]>");
		AddLineQueue("DPARAM15 TEXTEQU <[ESP+64]>");
		AddLineQueue("DPARAM16 TEXTEQU <[ESP+68]>");
		AddLineQueue("DPARAM17 TEXTEQU <[ESP+72]>");
		AddLineQueue("DPARAM18 TEXTEQU <[ESP+76]>");
		AddLineQueue("DPARAM19 TEXTEQU <[ESP+80]>");
		AddLineQueue("DPARAM20 TEXTEQU <[ESP+84]>");
		AddLineQueue("DPARAM21 TEXTEQU <[ESP+88]>");
		AddLineQueue("DPARAM22 TEXTEQU <[ESP+92]>");
		AddLineQueue("DPARAM23 TEXTEQU <[ESP+96]>");
		AddLineQueue("DPARAM24 TEXTEQU <[ESP+100]>");
		AddLineQueue("DPARAM25 TEXTEQU <[ESP+104]>");
		AddLineQueue("DPARAM26 TEXTEQU <[ESP+108]>");
		AddLineQueue("DPARAM27 TEXTEQU <[ESP+112]>");
		AddLineQueue("DPARAM28 TEXTEQU <[ESP+116]>");
		AddLineQueue("DPARAM29 TEXTEQU <[ESP+120]>");
		AddLineQueue("DPARAM30 TEXTEQU <[ESP+124]>");
		AddLineQueue("DPARAM31 TEXTEQU <[ESP+128]>");
		AddLineQueue("DPARAM32 TEXTEQU <[ESP+132]>");
		AddLineQueue("DPARAM33 TEXTEQU <[ESP+136]>");
		AddLineQueue("DPARAM34 TEXTEQU <[ESP+140]>");
		AddLineQueue("DPARAM35 TEXTEQU <[ESP+144]>");
		AddLineQueue("DPARAM36 TEXTEQU <[ESP+148]>");
		AddLineQueue("DPARAM37 TEXTEQU <[ESP+152]>");
		AddLineQueue("DPARAM38 TEXTEQU <[ESP+156]>");
		AddLineQueue("DPARAM39 TEXTEQU <[ESP+160]>");
		AddLineQueue("DPARAM40 TEXTEQU <[ESP+164]>");
		AddLineQueue("DPARAM41 TEXTEQU <[ESP+168]>");
		AddLineQueue("DPARAM42 TEXTEQU <[ESP+172]>");
		AddLineQueue("DPARAM43 TEXTEQU <[ESP+176]>");
		AddLineQueue("DPARAM44 TEXTEQU <[ESP+180]>");
		AddLineQueue("DPARAM45 TEXTEQU <[ESP+184]>");
		AddLineQueue("DPARAM46 TEXTEQU <[ESP+188]>");
		AddLineQueue("DPARAM47 TEXTEQU <[ESP+192]>");
		AddLineQueue("DPARAM48 TEXTEQU <[ESP+196]>");
		AddLineQueue("DPARAM49 TEXTEQU <[ESP+200]>");
		AddLineQueue("DPARAM50 TEXTEQU <[ESP+204]>");
		AddLineQueue("DPARAM51 TEXTEQU <[ESP+208]>");
		AddLineQueue("DPARAM52 TEXTEQU <[ESP+212]>");
		AddLineQueue("DPARAM53 TEXTEQU <[ESP+216]>");
		AddLineQueue("DPARAM54 TEXTEQU <[ESP+220]>");
		AddLineQueue("DPARAM55 TEXTEQU <[ESP+224]>");
		AddLineQueue("DPARAM56 TEXTEQU <[ESP+228]>");
		AddLineQueue("DPARAM57 TEXTEQU <[ESP+232]>");
		AddLineQueue("DPARAM58 TEXTEQU <[ESP+236]>");
		AddLineQueue("DPARAM59 TEXTEQU <[ESP+240]>");
		AddLineQueue("DPARAM60 TEXTEQU <[ESP+244]>");
		AddLineQueue("DPARAM61 TEXTEQU <[ESP+248]>");
		AddLineQueue("DPARAM62 TEXTEQU <[ESP+252]>");
		AddLineQueue("DPARAM63 TEXTEQU <[ESP+256]>");
		/* 16bits*/
		AddLineQueue("WRET TEXTEQU <AX>");
		AddLineQueue("WRETURN TEXTEQU <AX>");
		AddLineQueue("WSIDX TEXTEQU <SI>");
		AddLineQueue("WDIDX TEXTEQU <DI>");
		AddLineQueue("WBPTR TEXTEQU <BP>");
		AddLineQueue("WSPTR TEXTEQU <SP>");
		AddLineQueue("WBASE TEXTEQU <BX>");
		AddLineQueue("WPARAM0 TEXTEQU <CX>");
		AddLineQueue("WPARAM1 TEXTEQU <DX>");
		AddLineQueue("WPARAM2 TEXTEQU <R8W>");
		AddLineQueue("WPARAM3 TEXTEQU <R9W>");
		AddLineQueue("WPARAM4 TEXTEQU <[SP+10]>");
		AddLineQueue("WPARAM5 TEXTEQU <[SP+12]>");
		AddLineQueue("WPARAM6 TEXTEQU <[SP+14]>");
		AddLineQueue("WPARAM7 TEXTEQU <[SP+16]>");
		AddLineQueue("WPARAM8 TEXTEQU <[SP+18]>");
		AddLineQueue("WPARAM9 TEXTEQU <[SP+20]>");
		AddLineQueue("WPARAM10 TEXTEQU <[SP+22]>");
		AddLineQueue("WPARAM11 TEXTEQU <[SP+24]>");
		AddLineQueue("WPARAM12 TEXTEQU <[SP+26]>");
		AddLineQueue("WPARAM13 TEXTEQU <[SP+28]>");
		AddLineQueue("WPARAM14 TEXTEQU <[SP+30]>");
		AddLineQueue("WPARAM15 TEXTEQU <[SP+32]>");
		AddLineQueue("WPARAM16 TEXTEQU <[SP+34]>");
		AddLineQueue("WPARAM17 TEXTEQU <[SP+36]>");
		AddLineQueue("WPARAM18 TEXTEQU <[SP+38]>");
		AddLineQueue("WPARAM19 TEXTEQU <[SP+40]>");
		AddLineQueue("WPARAM20 TEXTEQU <[SP+42]>");
		AddLineQueue("WPARAM21 TEXTEQU <[SP+44]>");
		AddLineQueue("WPARAM22 TEXTEQU <[SP+46]>");
		AddLineQueue("WPARAM23 TEXTEQU <[SP+48]>");
		AddLineQueue("WPARAM24 TEXTEQU <[SP+50]>");
		AddLineQueue("WPARAM25 TEXTEQU <[SP+52]>");
		AddLineQueue("WPARAM26 TEXTEQU <[SP+54]>");
		AddLineQueue("WPARAM27 TEXTEQU <[SP+56]>");
		AddLineQueue("WPARAM28 TEXTEQU <[SP+58]>");
		AddLineQueue("WPARAM29 TEXTEQU <[SP+60]>");
		AddLineQueue("WPARAM30 TEXTEQU <[SP+62]>");
		AddLineQueue("WPARAM31 TEXTEQU <[SP+64]>");
		AddLineQueue("WPARAM32 TEXTEQU <[SP+66]>");
		AddLineQueue("WPARAM33 TEXTEQU <[SP+68]>");
		AddLineQueue("WPARAM34 TEXTEQU <[SP+70]>");
		AddLineQueue("WPARAM35 TEXTEQU <[SP+72]>");
		AddLineQueue("WPARAM36 TEXTEQU <[SP+74]>");
		AddLineQueue("WPARAM37 TEXTEQU <[SP+76]>");
		AddLineQueue("WPARAM38 TEXTEQU <[SP+78]>");
		AddLineQueue("WPARAM39 TEXTEQU <[SP+80]>");
		AddLineQueue("WPARAM40 TEXTEQU <[SP+82]>");
		AddLineQueue("WPARAM41 TEXTEQU <[SP+84]>");
		AddLineQueue("WPARAM42 TEXTEQU <[SP+86]>");
		AddLineQueue("WPARAM43 TEXTEQU <[SP+88]>");
		AddLineQueue("WPARAM44 TEXTEQU <[SP+90]>");
		AddLineQueue("WPARAM45 TEXTEQU <[SP+92]>");
		AddLineQueue("WPARAM46 TEXTEQU <[SP+94]>");
		AddLineQueue("WPARAM47 TEXTEQU <[SP+96]>");
		AddLineQueue("WPARAM48 TEXTEQU <[SP+98]>");
		AddLineQueue("WPARAM49 TEXTEQU <[SP+100]>");
		AddLineQueue("WPARAM50 TEXTEQU <[SP+102]>");
		AddLineQueue("WPARAM51 TEXTEQU <[SP+104]>");
		AddLineQueue("WPARAM52 TEXTEQU <[SP+106]>");
		AddLineQueue("WPARAM53 TEXTEQU <[SP+108]>");
		AddLineQueue("WPARAM54 TEXTEQU <[SP+110]>");
		AddLineQueue("WPARAM55 TEXTEQU <[SP+112]>");
		AddLineQueue("WPARAM56 TEXTEQU <[SP+114]>");
		AddLineQueue("WPARAM57 TEXTEQU <[SP+116]>");
		AddLineQueue("WPARAM58 TEXTEQU <[SP+118]>");
		AddLineQueue("WPARAM59 TEXTEQU <[SP+120]>");
		AddLineQueue("WPARAM60 TEXTEQU <[SP+122]>");
		AddLineQueue("WPARAM61 TEXTEQU <[SP+124]>");
		AddLineQueue("WPARAM62 TEXTEQU <[SP+126]>");
		AddLineQueue("WPARAM63 TEXTEQU <[SP+128]>");
		/* 8bits*/
		AddLineQueue("BRET TEXTEQU <AL>");
		AddLineQueue("BRETURN TEXTEQU <AL>");
		AddLineQueue("BSIDX TEXTEQU <SIL>");
		AddLineQueue("BDIDX TEXTEQU <DIL>");
		AddLineQueue("BBPTR TEXTEQU <BPL>");
		AddLineQueue("BSPTR TEXTEQU <SPL>");
		AddLineQueue("BBASE TEXTEQU <BL>");
		AddLineQueue("BPARAM0 TEXTEQU <CL>");
		AddLineQueue("BPARAM1 TEXTEQU <DL>");
		AddLineQueue("BPARAM2 TEXTEQU <R8L>");
		AddLineQueue("BPARAM3 TEXTEQU <R9L>");
		AddLineQueue("BPARAM4 TEXTEQU <[SPL+5]>");
		AddLineQueue("BPARAM5 TEXTEQU <[SPL+6]>");
		AddLineQueue("BPARAM6 TEXTEQU <[SPL+7]>");
		AddLineQueue("BPARAM7 TEXTEQU <[SPL+8]>");
		AddLineQueue("BPARAM8 TEXTEQU <[SPL+9]>");
		AddLineQueue("BPARAM9 TEXTEQU <[SPL+10]>");
		AddLineQueue("BPARAM10 TEXTEQU <[SPL+11]>");
		AddLineQueue("BPARAM11 TEXTEQU <[SPL+12]>");
		AddLineQueue("BPARAM12 TEXTEQU <[SPL+13]>");
		AddLineQueue("BPARAM13 TEXTEQU <[SPL+14]>");
		AddLineQueue("BPARAM14 TEXTEQU <[SPL+15]>");
		AddLineQueue("BPARAM15 TEXTEQU <[SPL+16]>");
		AddLineQueue("BPARAM16 TEXTEQU <[SPL+17]>");
		AddLineQueue("BPARAM17 TEXTEQU <[SPL+18]>");
		AddLineQueue("BPARAM18 TEXTEQU <[SPL+19]>");
		AddLineQueue("BPARAM19 TEXTEQU <[SPL+20]>");
		AddLineQueue("BPARAM20 TEXTEQU <[SPL+21]>");
		AddLineQueue("BPARAM21 TEXTEQU <[SPL+22]>");
		AddLineQueue("BPARAM22 TEXTEQU <[SPL+23]>");
		AddLineQueue("BPARAM23 TEXTEQU <[SPL+24]>");
		AddLineQueue("BPARAM24 TEXTEQU <[SPL+25]>");
		AddLineQueue("BPARAM25 TEXTEQU <[SPL+26]>");
		AddLineQueue("BPARAM26 TEXTEQU <[SPL+27]>");
		AddLineQueue("BPARAM27 TEXTEQU <[SPL+28]>");
		AddLineQueue("BPARAM28 TEXTEQU <[SPL+29]>");
		AddLineQueue("BPARAM29 TEXTEQU <[SPL+30]>");
		AddLineQueue("BPARAM30 TEXTEQU <[SPL+31]>");
		AddLineQueue("BPARAM31 TEXTEQU <[SPL+32]>");
		AddLineQueue("BPARAM32 TEXTEQU <[SPL+33]>");
		AddLineQueue("BPARAM33 TEXTEQU <[SPL+34]>");
		AddLineQueue("BPARAM34 TEXTEQU <[SPL+35]>");
		AddLineQueue("BPARAM35 TEXTEQU <[SPL+36]>");
		AddLineQueue("BPARAM36 TEXTEQU <[SPL+37]>");
		AddLineQueue("BPARAM37 TEXTEQU <[SPL+38]>");
		AddLineQueue("BPARAM38 TEXTEQU <[SPL+39]>");
		AddLineQueue("BPARAM39 TEXTEQU <[SPL+40]>");
		AddLineQueue("BPARAM40 TEXTEQU <[SPL+41]>");
		AddLineQueue("BPARAM41 TEXTEQU <[SPL+42]>");
		AddLineQueue("BPARAM42 TEXTEQU <[SPL+43]>");
		AddLineQueue("BPARAM43 TEXTEQU <[SPL+44]>");
		AddLineQueue("BPARAM44 TEXTEQU <[SPL+45]>");
		AddLineQueue("BPARAM45 TEXTEQU <[SPL+46]>");
		AddLineQueue("BPARAM46 TEXTEQU <[SPL+47]>");
		AddLineQueue("BPARAM47 TEXTEQU <[SPL+48]>");
		AddLineQueue("BPARAM48 TEXTEQU <[SPL+49]>");
		AddLineQueue("BPARAM49 TEXTEQU <[SPL+50]>");
		AddLineQueue("BPARAM50 TEXTEQU <[SPL+51]>");
		AddLineQueue("BPARAM51 TEXTEQU <[SPL+52]>");
		AddLineQueue("BPARAM52 TEXTEQU <[SPL+53]>");
		AddLineQueue("BPARAM53 TEXTEQU <[SPL+54]>");
		AddLineQueue("BPARAM54 TEXTEQU <[SPL+55]>");
		AddLineQueue("BPARAM55 TEXTEQU <[SPL+56]>");
		AddLineQueue("BPARAM56 TEXTEQU <[SPL+57]>");
		AddLineQueue("BPARAM57 TEXTEQU <[SPL+58]>");
		AddLineQueue("BPARAM58 TEXTEQU <[SPL+59]>");
		AddLineQueue("BPARAM59 TEXTEQU <[SPL+60]>");
		AddLineQueue("BPARAM60 TEXTEQU <[SPL+61]>");
		AddLineQueue("BPARAM61 TEXTEQU <[SPL+62]>");
		AddLineQueue("BPARAM62 TEXTEQU <[SPL+63]>");
		AddLineQueue("BPARAM63 TEXTEQU <[SPL+64]>");
	}
	AddLineQueue("ENDIF"); /*__WIN64__*/

	AddLineQueue("IFDEF __WIN32__");
	AddLineQueue("IFDEF __WIN32_VECTORCALL__"); /*not available with uasm macrolib*/
	AddLineQueue("IFNDEF DEFINED_VECTORCALL");
	AddLineQueue("DEFINE DEFINED_VECTORCALL");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF CALLCONV");
	AddLineQueue("CALLCONV TEXTEQU <VECTORCALL>");
	AddLineQueue("ENDIF");
	AddLineQueue("CALLCONVOPT TEXTEQU <option language:VECTORCALL>");
	AddLineQueue("ELSE");
	AddLineQueue("IFNDEF CALLCONV");
	AddLineQueue("CALLCONV TEXTEQU <FASTCALL>");
	AddLineQueue("ENDIF");
	AddLineQueue("CALLCONVOPT TEXTEQU <option language:FASTCALL>");
	AddLineQueue("ENDIF");
	if (ModuleInfo.langtype == LANG_REGCALL)
	{
		/* 32bits*/
		AddLineQueue("RRET TEXTEQU <EAX>");
		AddLineQueue("RRETURN TEXTEQU <EAX>");
		AddLineQueue("RSIDX TEXTEQU <ESI>");
		AddLineQueue("RDIDX TEXTEQU <EDI>");
		AddLineQueue("RBPTR TEXTEQU <EBP>");
		AddLineQueue("RSPTR TEXTEQU <ESP>");
		AddLineQueue("RBASE TEXTEQU <EBX>");
		AddLineQueue("RPARAM0 TEXTEQU <ECX>");
		AddLineQueue("RPARAM1 TEXTEQU <EDX>");
		AddLineQueue("RPARAM2 TEXTEQU <EDI>");
		AddLineQueue("RPARAM3 TEXTEQU <ESI>");
		AddLineQueue("RPARAM4 TEXTEQU <[ESP+20]>");
		AddLineQueue("RPARAM5 TEXTEQU <[ESP+24]>");
		AddLineQueue("RPARAM6 TEXTEQU <[ESP+28]>");
		AddLineQueue("RPARAM7 TEXTEQU <[ESP+32]>");
		AddLineQueue("RPARAM8 TEXTEQU <[ESP+36]>");
		AddLineQueue("RPARAM9 TEXTEQU <[ESP+40]>");
		AddLineQueue("RPARAM10 TEXTEQU <[ESP+44]>");
		AddLineQueue("RPARAM11 TEXTEQU <[ESP+48]>");
		AddLineQueue("RPARAM12 TEXTEQU <[ESP+52]>");
		AddLineQueue("RPARAM13 TEXTEQU <[ESP+56]>");
		AddLineQueue("RPARAM13 TEXTEQU <[ESP+60]>");
		AddLineQueue("RPARAM14 TEXTEQU <[ESP+64]>");
		AddLineQueue("RPARAM15 TEXTEQU <[ESP+68]>");
		AddLineQueue("RPARAM16 TEXTEQU <[ESP+72]>");
		AddLineQueue("RPARAM17 TEXTEQU <[ESP+76]>");
		AddLineQueue("RPARAM19 TEXTEQU <[ESP+80]>");
		AddLineQueue("RPARAM20 TEXTEQU <[ESP+84]>");
		AddLineQueue("RPARAM21 TEXTEQU <[ESP+88]>");
		AddLineQueue("RPARAM22 TEXTEQU <[ESP+92]>");
		AddLineQueue("RPARAM23 TEXTEQU <[ESP+96]>");
		AddLineQueue("RPARAM24 TEXTEQU <[ESP+100]>");
		AddLineQueue("RPARAM25 TEXTEQU <[ESP+104]>");
		AddLineQueue("RPARAM26 TEXTEQU <[ESP+108]>");
		AddLineQueue("RPARAM27 TEXTEQU <[ESP+112]>");
		AddLineQueue("RPARAM28 TEXTEQU <[ESP+116]>");
		AddLineQueue("RPARAM29 TEXTEQU <[ESP+120]>");
		AddLineQueue("RPARAM30 TEXTEQU <[ESP+124]>");
		AddLineQueue("RPARAM31 TEXTEQU <[ESP+128]>");
		AddLineQueue("RPARAM32 TEXTEQU <[ESP+132]>");
		AddLineQueue("RPARAM33 TEXTEQU <[ESP+136]>");
		AddLineQueue("RPARAM34 TEXTEQU <[ESP+140]>");
		AddLineQueue("RPARAM35 TEXTEQU <[ESP+144]>");
		AddLineQueue("RPARAM36 TEXTEQU <[ESP+148]>");
		AddLineQueue("RPARAM37 TEXTEQU <[ESP+152]>");
		AddLineQueue("RPARAM38 TEXTEQU <[ESP+156]>");
		AddLineQueue("RPARAM39 TEXTEQU <[ESP+160]>");
		AddLineQueue("RPARAM40 TEXTEQU <[ESP+164]>");
		AddLineQueue("RPARAM41 TEXTEQU <[ESP+168]>");
		AddLineQueue("RPARAM42 TEXTEQU <[ESP+172]>");
		AddLineQueue("RPARAM43 TEXTEQU <[ESP+176]>");
		AddLineQueue("RPARAM44 TEXTEQU <[ESP+180]>");
		AddLineQueue("RPARAM45 TEXTEQU <[ESP+184]>");
		AddLineQueue("RPARAM46 TEXTEQU <[ESP+188]>");
		AddLineQueue("RPARAM47 TEXTEQU <[ESP+192]>");
		AddLineQueue("RPARAM48 TEXTEQU <[ESP+196]>");
		AddLineQueue("RPARAM49 TEXTEQU <[ESP+200]>");
		AddLineQueue("RPARAM50 TEXTEQU <[ESP+204]>");
		AddLineQueue("RPARAM51 TEXTEQU <[ESP+208]>");
		AddLineQueue("RPARAM52 TEXTEQU <[ESP+212]>");
		AddLineQueue("RPARAM53 TEXTEQU <[ESP+216]>");
		AddLineQueue("RPARAM54 TEXTEQU <[ESP+220]>");
		AddLineQueue("RPARAM55 TEXTEQU <[ESP+224]>");
		AddLineQueue("RPARAM56 TEXTEQU <[ESP+228]>");
		AddLineQueue("RPARAM57 TEXTEQU <[ESP+232]>");
		AddLineQueue("RPARAM58 TEXTEQU <[ESP+236]>");
		AddLineQueue("RPARAM59 TEXTEQU <[ESP+240]>");
		AddLineQueue("RPARAM60 TEXTEQU <[ESP+244]>");
		AddLineQueue("RPARAM61 TEXTEQU <[ESP+248]>");
		AddLineQueue("RPARAM62 TEXTEQU <[ESP+252]>");
		AddLineQueue("RPARAM63 TEXTEQU <[ESP+256]>");
		/* 32bits*/
		AddLineQueue("DRET TEXTEQU <EAX>");
		AddLineQueue("DRETURN TEXTEQU <EAX>");
		AddLineQueue("DSIDX TEXTEQU <ESI>");
		AddLineQueue("DDIDX TEXTEQU <EDI>");
		AddLineQueue("DBPTR TEXTEQU <EBP>");
		AddLineQueue("DSPTR TEXTEQU <ESP>");
		AddLineQueue("DBASE TEXTEQU <EBX>");
		AddLineQueue("DPARAM0 TEXTEQU <ECX>");
		AddLineQueue("DPARAM1 TEXTEQU <EDX>");
		AddLineQueue("DPARAM2 TEXTEQU <EDI>");
		AddLineQueue("DPARAM3 TEXTEQU <ESI>");
		AddLineQueue("DPARAM4 TEXTEQU <[ESP+20]>");
		AddLineQueue("DPARAM5 TEXTEQU <[ESP+24]>");
		AddLineQueue("DPARAM6 TEXTEQU <[ESP+28]>");
		AddLineQueue("DPARAM7 TEXTEQU <[ESP+32]>");
		AddLineQueue("DPARAM8 TEXTEQU <[ESP+36]>");
		AddLineQueue("DPARAM9 TEXTEQU <[ESP+40]>");
		AddLineQueue("DPARAM10 TEXTEQU <[ESP+44]>");
		AddLineQueue("DPARAM11 TEXTEQU <[ESP+48]>");
		AddLineQueue("DPARAM12 TEXTEQU <[ESP+52]>");
		AddLineQueue("DPARAM13 TEXTEQU <[ESP+56]>");
		AddLineQueue("DPARAM14 TEXTEQU <[ESP+60]>");
		AddLineQueue("DPARAM15 TEXTEQU <[ESP+64]>");
		AddLineQueue("DPARAM16 TEXTEQU <[ESP+68]>");
		AddLineQueue("DPARAM17 TEXTEQU <[ESP+72]>");
		AddLineQueue("DPARAM18 TEXTEQU <[ESP+76]>");
		AddLineQueue("DPARAM19 TEXTEQU <[ESP+80]>");
		AddLineQueue("DPARAM20 TEXTEQU <[ESP+84]>");
		AddLineQueue("DPARAM21 TEXTEQU <[ESP+88]>");
		AddLineQueue("DPARAM22 TEXTEQU <[ESP+92]>");
		AddLineQueue("DPARAM23 TEXTEQU <[ESP+96]>");
		AddLineQueue("DPARAM24 TEXTEQU <[ESP+100]>");
		AddLineQueue("DPARAM25 TEXTEQU <[ESP+104]>");
		AddLineQueue("DPARAM26 TEXTEQU <[ESP+108]>");
		AddLineQueue("DPARAM27 TEXTEQU <[ESP+112]>");
		AddLineQueue("DPARAM28 TEXTEQU <[ESP+116]>");
		AddLineQueue("DPARAM29 TEXTEQU <[ESP+120]>");
		AddLineQueue("DPARAM30 TEXTEQU <[ESP+124]>");
		AddLineQueue("DPARAM31 TEXTEQU <[ESP+128]>");
		AddLineQueue("DPARAM32 TEXTEQU <[ESP+132]>");
		AddLineQueue("DPARAM33 TEXTEQU <[ESP+136]>");
		AddLineQueue("DPARAM34 TEXTEQU <[ESP+140]>");
		AddLineQueue("DPARAM35 TEXTEQU <[ESP+144]>");
		AddLineQueue("DPARAM36 TEXTEQU <[ESP+148]>");
		AddLineQueue("DPARAM37 TEXTEQU <[ESP+152]>");
		AddLineQueue("DPARAM38 TEXTEQU <[ESP+156]>");
		AddLineQueue("DPARAM39 TEXTEQU <[ESP+160]>");
		AddLineQueue("DPARAM40 TEXTEQU <[ESP+164]>");
		AddLineQueue("DPARAM41 TEXTEQU <[ESP+168]>");
		AddLineQueue("DPARAM42 TEXTEQU <[ESP+172]>");
		AddLineQueue("DPARAM43 TEXTEQU <[ESP+176]>");
		AddLineQueue("DPARAM44 TEXTEQU <[ESP+180]>");
		AddLineQueue("DPARAM45 TEXTEQU <[ESP+184]>");
		AddLineQueue("DPARAM46 TEXTEQU <[ESP+188]>");
		AddLineQueue("DPARAM47 TEXTEQU <[ESP+192]>");
		AddLineQueue("DPARAM48 TEXTEQU <[ESP+196]>");
		AddLineQueue("DPARAM49 TEXTEQU <[ESP+200]>");
		AddLineQueue("DPARAM50 TEXTEQU <[ESP+204]>");
		AddLineQueue("DPARAM51 TEXTEQU <[ESP+208]>");
		AddLineQueue("DPARAM52 TEXTEQU <[ESP+212]>");
		AddLineQueue("DPARAM53 TEXTEQU <[ESP+216]>");
		AddLineQueue("DPARAM54 TEXTEQU <[ESP+220]>");
		AddLineQueue("DPARAM55 TEXTEQU <[ESP+224]>");
		AddLineQueue("DPARAM56 TEXTEQU <[ESP+228]>");
		AddLineQueue("DPARAM57 TEXTEQU <[ESP+232]>");
		AddLineQueue("DPARAM58 TEXTEQU <[ESP+236]>");
		AddLineQueue("DPARAM59 TEXTEQU <[ESP+240]>");
		AddLineQueue("DPARAM60 TEXTEQU <[ESP+244]>");
		AddLineQueue("DPARAM61 TEXTEQU <[ESP+248]>");
		AddLineQueue("DPARAM62 TEXTEQU <[ESP+252]>");
		AddLineQueue("DPARAM63 TEXTEQU <[ESP+256]>");
		/* 16bits*/
		AddLineQueue("WRET TEXTEQU <AX>");
		AddLineQueue("WRETURN TEXTEQU <AX>");
		AddLineQueue("WSIDX TEXTEQU <SI>");
		AddLineQueue("WDIDX TEXTEQU <DI>");
		AddLineQueue("WBPTR TEXTEQU <BP>");
		AddLineQueue("WSPTR TEXTEQU <SP>");
		AddLineQueue("WBASE TEXTEQU <BX>");
		AddLineQueue("WPARAM0 TEXTEQU <CX>");
		AddLineQueue("WPARAM1 TEXTEQU <DX>");
		AddLineQueue("WPARAM2 TEXTEQU <DI>");
		AddLineQueue("WPARAM3 TEXTEQU <SI>");
		AddLineQueue("WPARAM4 TEXTEQU <[SP+10]>");
		AddLineQueue("WPARAM5 TEXTEQU <[SP+12]>");
		AddLineQueue("WPARAM6 TEXTEQU <[SP+14]>");
		AddLineQueue("WPARAM7 TEXTEQU <[SP+16]>");
		AddLineQueue("WPARAM8 TEXTEQU <[SP+18]>");
		AddLineQueue("WPARAM9 TEXTEQU <[SP+20]>");
		AddLineQueue("WPARAM10 TEXTEQU <[SP+22]>");
		AddLineQueue("WPARAM11 TEXTEQU <[SP+24]>");
		AddLineQueue("WPARAM12 TEXTEQU <[SP+26]>");
		AddLineQueue("WPARAM13 TEXTEQU <[SP+28]>");
		AddLineQueue("WPARAM14 TEXTEQU <[SP+30]>");
		AddLineQueue("WPARAM15 TEXTEQU <[SP+32]>");
		AddLineQueue("WPARAM16 TEXTEQU <[SP+34]>");
		AddLineQueue("WPARAM17 TEXTEQU <[SP+36]>");
		AddLineQueue("WPARAM18 TEXTEQU <[SP+38]>");
		AddLineQueue("WPARAM19 TEXTEQU <[SP+40]>");
		AddLineQueue("WPARAM20 TEXTEQU <[SP+42]>");
		AddLineQueue("WPARAM21 TEXTEQU <[SP+44]>");
		AddLineQueue("WPARAM22 TEXTEQU <[SP+46]>");
		AddLineQueue("WPARAM23 TEXTEQU <[SP+48]>");
		AddLineQueue("WPARAM24 TEXTEQU <[SP+50]>");
		AddLineQueue("WPARAM25 TEXTEQU <[SP+52]>");
		AddLineQueue("WPARAM26 TEXTEQU <[SP+54]>");
		AddLineQueue("WPARAM27 TEXTEQU <[SP+56]>");
		AddLineQueue("WPARAM28 TEXTEQU <[SP+58]>");
		AddLineQueue("WPARAM29 TEXTEQU <[SP+60]>");
		AddLineQueue("WPARAM30 TEXTEQU <[SP+62]>");
		AddLineQueue("WPARAM31 TEXTEQU <[SP+64]>");
		AddLineQueue("WPARAM32 TEXTEQU <[SP+66]>");
		AddLineQueue("WPARAM33 TEXTEQU <[SP+68]>");
		AddLineQueue("WPARAM34 TEXTEQU <[SP+70]>");
		AddLineQueue("WPARAM35 TEXTEQU <[SP+72]>");
		AddLineQueue("WPARAM36 TEXTEQU <[SP+74]>");
		AddLineQueue("WPARAM37 TEXTEQU <[SP+76]>");
		AddLineQueue("WPARAM38 TEXTEQU <[SP+78]>");
		AddLineQueue("WPARAM39 TEXTEQU <[SP+80]>");
		AddLineQueue("WPARAM40 TEXTEQU <[SP+82]>");
		AddLineQueue("WPARAM41 TEXTEQU <[SP+84]>");
		AddLineQueue("WPARAM42 TEXTEQU <[SP+86]>");
		AddLineQueue("WPARAM43 TEXTEQU <[SP+88]>");
		AddLineQueue("WPARAM44 TEXTEQU <[SP+90]>");
		AddLineQueue("WPARAM45 TEXTEQU <[SP+92]>");
		AddLineQueue("WPARAM46 TEXTEQU <[SP+94]>");
		AddLineQueue("WPARAM47 TEXTEQU <[SP+96]>");
		AddLineQueue("WPARAM48 TEXTEQU <[SP+98]>");
		AddLineQueue("WPARAM49 TEXTEQU <[SP+100]>");
		AddLineQueue("WPARAM50 TEXTEQU <[SP+102]>");
		AddLineQueue("WPARAM51 TEXTEQU <[SP+104]>");
		AddLineQueue("WPARAM52 TEXTEQU <[SP+106]>");
		AddLineQueue("WPARAM53 TEXTEQU <[SP+108]>");
		AddLineQueue("WPARAM54 TEXTEQU <[SP+110]>");
		AddLineQueue("WPARAM55 TEXTEQU <[SP+112]>");
		AddLineQueue("WPARAM56 TEXTEQU <[SP+114]>");
		AddLineQueue("WPARAM57 TEXTEQU <[SP+116]>");
		AddLineQueue("WPARAM58 TEXTEQU <[SP+118]>");
		AddLineQueue("WPARAM59 TEXTEQU <[SP+120]>");
		AddLineQueue("WPARAM60 TEXTEQU <[SP+122]>");
		AddLineQueue("WPARAM61 TEXTEQU <[SP+124]>");
		AddLineQueue("WPARAM62 TEXTEQU <[SP+126]>");
		AddLineQueue("WPARAM63 TEXTEQU <[SP+128]>");
		/* 8bits*/
		AddLineQueue("BRET TEXTEQU <AL>");
		AddLineQueue("BRETURN TEXTEQU <AL>");
		AddLineQueue("BSIDX TEXTEQU <SIL>");
		AddLineQueue("BDIDX TEXTEQU <DIL>");
		AddLineQueue("BBPTR TEXTEQU <BPL>");
		AddLineQueue("BSPTR TEXTEQU <SPL>");
		AddLineQueue("BBASE TEXTEQU <BL>");
		AddLineQueue("BPARAM0 TEXTEQU <CL>");
		AddLineQueue("BPARAM1 TEXTEQU <DL>");
		AddLineQueue("BPARAM2 TEXTEQU <DIL>");
		AddLineQueue("BPARAM3 TEXTEQU <SIL>");
		AddLineQueue("BPARAM4 TEXTEQU <[SPL+5]>");
		AddLineQueue("BPARAM5 TEXTEQU <[SPL+6]>");
		AddLineQueue("BPARAM6 TEXTEQU <[SPL+7]>");
		AddLineQueue("BPARAM7 TEXTEQU <[SPL+8]>");
		AddLineQueue("BPARAM8 TEXTEQU <[SPL+9]>");
		AddLineQueue("BPARAM9 TEXTEQU <[SPL+10]>");
		AddLineQueue("BPARAM10 TEXTEQU <[SPL+11]>");
		AddLineQueue("BPARAM11 TEXTEQU <[SPL+12]>");
		AddLineQueue("BPARAM12 TEXTEQU <[SPL+13]>");
		AddLineQueue("BPARAM13 TEXTEQU <[SPL+14]>");
		AddLineQueue("BPARAM14 TEXTEQU <[SPL+15]>");
		AddLineQueue("BPARAM15 TEXTEQU <[SPL+16]>");
		AddLineQueue("BPARAM16 TEXTEQU <[SPL+17]>");
		AddLineQueue("BPARAM17 TEXTEQU <[SPL+18]>");
		AddLineQueue("BPARAM18 TEXTEQU <[SPL+19]>");
		AddLineQueue("BPARAM19 TEXTEQU <[SPL+20]>");
		AddLineQueue("BPARAM20 TEXTEQU <[SPL+21]>");
		AddLineQueue("BPARAM21 TEXTEQU <[SPL+22]>");
		AddLineQueue("BPARAM22 TEXTEQU <[SPL+23]>");
		AddLineQueue("BPARAM23 TEXTEQU <[SPL+24]>");
		AddLineQueue("BPARAM24 TEXTEQU <[SPL+25]>");
		AddLineQueue("BPARAM25 TEXTEQU <[SPL+26]>");
		AddLineQueue("BPARAM26 TEXTEQU <[SPL+27]>");
		AddLineQueue("BPARAM27 TEXTEQU <[SPL+28]>");
		AddLineQueue("BPARAM28 TEXTEQU <[SPL+29]>");
		AddLineQueue("BPARAM29 TEXTEQU <[SPL+30]>");
		AddLineQueue("BPARAM30 TEXTEQU <[SPL+31]>");
		AddLineQueue("BPARAM31 TEXTEQU <[SPL+32]>");
		AddLineQueue("BPARAM32 TEXTEQU <[SPL+33]>");
		AddLineQueue("BPARAM33 TEXTEQU <[SPL+34]>");
		AddLineQueue("BPARAM34 TEXTEQU <[SPL+35]>");
		AddLineQueue("BPARAM35 TEXTEQU <[SPL+36]>");
		AddLineQueue("BPARAM36 TEXTEQU <[SPL+37]>");
		AddLineQueue("BPARAM37 TEXTEQU <[SPL+38]>");
		AddLineQueue("BPARAM38 TEXTEQU <[SPL+39]>");
		AddLineQueue("BPARAM39 TEXTEQU <[SPL+40]>");
		AddLineQueue("BPARAM40 TEXTEQU <[SPL+41]>");
		AddLineQueue("BPARAM41 TEXTEQU <[SPL+42]>");
		AddLineQueue("BPARAM42 TEXTEQU <[SPL+43]>");
		AddLineQueue("BPARAM43 TEXTEQU <[SPL+44]>");
		AddLineQueue("BPARAM44 TEXTEQU <[SPL+45]>");
		AddLineQueue("BPARAM45 TEXTEQU <[SPL+46]>");
		AddLineQueue("BPARAM46 TEXTEQU <[SPL+47]>");
		AddLineQueue("BPARAM47 TEXTEQU <[SPL+48]>");
		AddLineQueue("BPARAM48 TEXTEQU <[SPL+49]>");
		AddLineQueue("BPARAM49 TEXTEQU <[SPL+50]>");
		AddLineQueue("BPARAM50 TEXTEQU <[SPL+51]>");
		AddLineQueue("BPARAM51 TEXTEQU <[SPL+52]>");
		AddLineQueue("BPARAM52 TEXTEQU <[SPL+53]>");
		AddLineQueue("BPARAM53 TEXTEQU <[SPL+54]>");
		AddLineQueue("BPARAM54 TEXTEQU <[SPL+55]>");
		AddLineQueue("BPARAM55 TEXTEQU <[SPL+56]>");
		AddLineQueue("BPARAM56 TEXTEQU <[SPL+57]>");
		AddLineQueue("BPARAM57 TEXTEQU <[SPL+58]>");
		AddLineQueue("BPARAM58 TEXTEQU <[SPL+59]>");
		AddLineQueue("BPARAM59 TEXTEQU <[SPL+60]>");
		AddLineQueue("BPARAM60 TEXTEQU <[SPL+61]>");
		AddLineQueue("BPARAM61 TEXTEQU <[SPL+62]>");
		AddLineQueue("BPARAM62 TEXTEQU <[SPL+63]>");
		AddLineQueue("BPARAM63 TEXTEQU <[SPL+64]>");
	}
	else
	{
		/* 32bits*/
		AddLineQueue("RRET TEXTEQU <EAX>");
		AddLineQueue("RRETURN TEXTEQU <EAX>");
		AddLineQueue("RSIDX TEXTEQU <ESI>");
		AddLineQueue("RDIDX TEXTEQU <EDI>");
		AddLineQueue("RBPTR TEXTEQU <EBP>");
		AddLineQueue("RSPTR TEXTEQU <ESP>");
		AddLineQueue("RBASE TEXTEQU <EBX>");
		AddLineQueue("RPARAM0 TEXTEQU <ECX>");
		AddLineQueue("RPARAM1 TEXTEQU <EDX>");
		AddLineQueue("RPARAM2 TEXTEQU <[ESP+12]>");
		AddLineQueue("RPARAM3 TEXTEQU <[ESP+16]>");
		AddLineQueue("RPARAM4 TEXTEQU <[ESP+20]>");
		AddLineQueue("RPARAM5 TEXTEQU <[ESP+24]>");
		AddLineQueue("RPARAM6 TEXTEQU <[ESP+28]>");
		AddLineQueue("RPARAM7 TEXTEQU <[ESP+32]>");
		AddLineQueue("RPARAM8 TEXTEQU <[ESP+36]>");
		AddLineQueue("RPARAM9 TEXTEQU <[ESP+40]>");
		AddLineQueue("RPARAM10 TEXTEQU <[ESP+44]>");
		AddLineQueue("RPARAM11 TEXTEQU <[ESP+48]>");
		AddLineQueue("RPARAM12 TEXTEQU <[ESP+52]>");
		AddLineQueue("RPARAM13 TEXTEQU <[ESP+56]>");
		AddLineQueue("RPARAM13 TEXTEQU <[ESP+60]>");
		AddLineQueue("RPARAM14 TEXTEQU <[ESP+64]>");
		AddLineQueue("RPARAM15 TEXTEQU <[ESP+68]>");
		AddLineQueue("RPARAM16 TEXTEQU <[ESP+72]>");
		AddLineQueue("RPARAM17 TEXTEQU <[ESP+76]>");
		AddLineQueue("RPARAM19 TEXTEQU <[ESP+80]>");
		AddLineQueue("RPARAM20 TEXTEQU <[ESP+84]>");
		AddLineQueue("RPARAM21 TEXTEQU <[ESP+88]>");
		AddLineQueue("RPARAM22 TEXTEQU <[ESP+92]>");
		AddLineQueue("RPARAM23 TEXTEQU <[ESP+96]>");
		AddLineQueue("RPARAM24 TEXTEQU <[ESP+100]>");
		AddLineQueue("RPARAM25 TEXTEQU <[ESP+104]>");
		AddLineQueue("RPARAM26 TEXTEQU <[ESP+108]>");
		AddLineQueue("RPARAM27 TEXTEQU <[ESP+112]>");
		AddLineQueue("RPARAM28 TEXTEQU <[ESP+116]>");
		AddLineQueue("RPARAM29 TEXTEQU <[ESP+120]>");
		AddLineQueue("RPARAM30 TEXTEQU <[ESP+124]>");
		AddLineQueue("RPARAM31 TEXTEQU <[ESP+128]>");
		AddLineQueue("RPARAM32 TEXTEQU <[ESP+132]>");
		AddLineQueue("RPARAM33 TEXTEQU <[ESP+136]>");
		AddLineQueue("RPARAM34 TEXTEQU <[ESP+140]>");
		AddLineQueue("RPARAM35 TEXTEQU <[ESP+144]>");
		AddLineQueue("RPARAM36 TEXTEQU <[ESP+148]>");
		AddLineQueue("RPARAM37 TEXTEQU <[ESP+152]>");
		AddLineQueue("RPARAM38 TEXTEQU <[ESP+156]>");
		AddLineQueue("RPARAM39 TEXTEQU <[ESP+160]>");
		AddLineQueue("RPARAM40 TEXTEQU <[ESP+164]>");
		AddLineQueue("RPARAM41 TEXTEQU <[ESP+168]>");
		AddLineQueue("RPARAM42 TEXTEQU <[ESP+172]>");
		AddLineQueue("RPARAM43 TEXTEQU <[ESP+176]>");
		AddLineQueue("RPARAM44 TEXTEQU <[ESP+180]>");
		AddLineQueue("RPARAM45 TEXTEQU <[ESP+184]>");
		AddLineQueue("RPARAM46 TEXTEQU <[ESP+188]>");
		AddLineQueue("RPARAM47 TEXTEQU <[ESP+192]>");
		AddLineQueue("RPARAM48 TEXTEQU <[ESP+196]>");
		AddLineQueue("RPARAM49 TEXTEQU <[ESP+200]>");
		AddLineQueue("RPARAM50 TEXTEQU <[ESP+204]>");
		AddLineQueue("RPARAM51 TEXTEQU <[ESP+208]>");
		AddLineQueue("RPARAM52 TEXTEQU <[ESP+212]>");
		AddLineQueue("RPARAM53 TEXTEQU <[ESP+216]>");
		AddLineQueue("RPARAM54 TEXTEQU <[ESP+220]>");
		AddLineQueue("RPARAM55 TEXTEQU <[ESP+224]>");
		AddLineQueue("RPARAM56 TEXTEQU <[ESP+228]>");
		AddLineQueue("RPARAM57 TEXTEQU <[ESP+232]>");
		AddLineQueue("RPARAM58 TEXTEQU <[ESP+236]>");
		AddLineQueue("RPARAM59 TEXTEQU <[ESP+240]>");
		AddLineQueue("RPARAM60 TEXTEQU <[ESP+244]>");
		AddLineQueue("RPARAM61 TEXTEQU <[ESP+248]>");
		AddLineQueue("RPARAM62 TEXTEQU <[ESP+252]>");
		AddLineQueue("RPARAM63 TEXTEQU <[ESP+256]>");
		/* 32bits*/
		AddLineQueue("DRET TEXTEQU <EAX>");
		AddLineQueue("DRETURN TEXTEQU <EAX>");
		AddLineQueue("DSIDX TEXTEQU <ESI>");
		AddLineQueue("DDIDX TEXTEQU <EDI>");
		AddLineQueue("DBPTR TEXTEQU <EBP>");
		AddLineQueue("DSPTR TEXTEQU <ESP>");
		AddLineQueue("DBASE TEXTEQU <EBX>");
		AddLineQueue("DPARAM0 TEXTEQU <ECX>");
		AddLineQueue("DPARAM1 TEXTEQU <EDX>");
		AddLineQueue("DPARAM2 TEXTEQU <[ESP+12]>");
		AddLineQueue("DPARAM3 TEXTEQU <[ESP+16]>");
		AddLineQueue("DPARAM4 TEXTEQU <[ESP+20]>");
		AddLineQueue("DPARAM5 TEXTEQU <[ESP+24]>");
		AddLineQueue("DPARAM6 TEXTEQU <[ESP+28]>");
		AddLineQueue("DPARAM7 TEXTEQU <[ESP+32]>");
		AddLineQueue("DPARAM8 TEXTEQU <[ESP+36]>");
		AddLineQueue("DPARAM9 TEXTEQU <[ESP+40]>");
		AddLineQueue("DPARAM10 TEXTEQU <[ESP+44]>");
		AddLineQueue("DPARAM11 TEXTEQU <[ESP+48]>");
		AddLineQueue("DPARAM12 TEXTEQU <[ESP+52]>");
		AddLineQueue("DPARAM13 TEXTEQU <[ESP+56]>");
		AddLineQueue("DPARAM14 TEXTEQU <[ESP+60]>");
		AddLineQueue("DPARAM15 TEXTEQU <[ESP+64]>");
		AddLineQueue("DPARAM16 TEXTEQU <[ESP+68]>");
		AddLineQueue("DPARAM17 TEXTEQU <[ESP+72]>");
		AddLineQueue("DPARAM18 TEXTEQU <[ESP+76]>");
		AddLineQueue("DPARAM19 TEXTEQU <[ESP+80]>");
		AddLineQueue("DPARAM20 TEXTEQU <[ESP+84]>");
		AddLineQueue("DPARAM21 TEXTEQU <[ESP+88]>");
		AddLineQueue("DPARAM22 TEXTEQU <[ESP+92]>");
		AddLineQueue("DPARAM23 TEXTEQU <[ESP+96]>");
		AddLineQueue("DPARAM24 TEXTEQU <[ESP+100]>");
		AddLineQueue("DPARAM25 TEXTEQU <[ESP+104]>");
		AddLineQueue("DPARAM26 TEXTEQU <[ESP+108]>");
		AddLineQueue("DPARAM27 TEXTEQU <[ESP+112]>");
		AddLineQueue("DPARAM28 TEXTEQU <[ESP+116]>");
		AddLineQueue("DPARAM29 TEXTEQU <[ESP+120]>");
		AddLineQueue("DPARAM30 TEXTEQU <[ESP+124]>");
		AddLineQueue("DPARAM31 TEXTEQU <[ESP+128]>");
		AddLineQueue("DPARAM32 TEXTEQU <[ESP+132]>");
		AddLineQueue("DPARAM33 TEXTEQU <[ESP+136]>");
		AddLineQueue("DPARAM34 TEXTEQU <[ESP+140]>");
		AddLineQueue("DPARAM35 TEXTEQU <[ESP+144]>");
		AddLineQueue("DPARAM36 TEXTEQU <[ESP+148]>");
		AddLineQueue("DPARAM37 TEXTEQU <[ESP+152]>");
		AddLineQueue("DPARAM38 TEXTEQU <[ESP+156]>");
		AddLineQueue("DPARAM39 TEXTEQU <[ESP+160]>");
		AddLineQueue("DPARAM40 TEXTEQU <[ESP+164]>");
		AddLineQueue("DPARAM41 TEXTEQU <[ESP+168]>");
		AddLineQueue("DPARAM42 TEXTEQU <[ESP+172]>");
		AddLineQueue("DPARAM43 TEXTEQU <[ESP+176]>");
		AddLineQueue("DPARAM44 TEXTEQU <[ESP+180]>");
		AddLineQueue("DPARAM45 TEXTEQU <[ESP+184]>");
		AddLineQueue("DPARAM46 TEXTEQU <[ESP+188]>");
		AddLineQueue("DPARAM47 TEXTEQU <[ESP+192]>");
		AddLineQueue("DPARAM48 TEXTEQU <[ESP+196]>");
		AddLineQueue("DPARAM49 TEXTEQU <[ESP+200]>");
		AddLineQueue("DPARAM50 TEXTEQU <[ESP+204]>");
		AddLineQueue("DPARAM51 TEXTEQU <[ESP+208]>");
		AddLineQueue("DPARAM52 TEXTEQU <[ESP+212]>");
		AddLineQueue("DPARAM53 TEXTEQU <[ESP+216]>");
		AddLineQueue("DPARAM54 TEXTEQU <[ESP+220]>");
		AddLineQueue("DPARAM55 TEXTEQU <[ESP+224]>");
		AddLineQueue("DPARAM56 TEXTEQU <[ESP+228]>");
		AddLineQueue("DPARAM57 TEXTEQU <[ESP+232]>");
		AddLineQueue("DPARAM58 TEXTEQU <[ESP+236]>");
		AddLineQueue("DPARAM59 TEXTEQU <[ESP+240]>");
		AddLineQueue("DPARAM60 TEXTEQU <[ESP+244]>");
		AddLineQueue("DPARAM61 TEXTEQU <[ESP+248]>");
		AddLineQueue("DPARAM62 TEXTEQU <[ESP+252]>");
		AddLineQueue("DPARAM63 TEXTEQU <[ESP+256]>");
		/* 16bits*/
		AddLineQueue("WRET TEXTEQU <AX>");
		AddLineQueue("WRETURN TEXTEQU <AX>");
		AddLineQueue("WSIDX TEXTEQU <SI>");
		AddLineQueue("WDIDX TEXTEQU <DI>");
		AddLineQueue("WBPTR TEXTEQU <BP>");
		AddLineQueue("WSPTR TEXTEQU <SP>");
		AddLineQueue("WBASE TEXTEQU <BX>");
		AddLineQueue("WPARAM0 TEXTEQU <CX>");
		AddLineQueue("WPARAM1 TEXTEQU <DX>");
		AddLineQueue("WPARAM2 TEXTEQU <[SP+6]>");
		AddLineQueue("WPARAM3 TEXTEQU <[SP+8]>");
		AddLineQueue("WPARAM4 TEXTEQU <[SP+10]>");
		AddLineQueue("WPARAM5 TEXTEQU <[SP+12]>");
		AddLineQueue("WPARAM6 TEXTEQU <[SP+14]>");
		AddLineQueue("WPARAM7 TEXTEQU <[SP+16]>");
		AddLineQueue("WPARAM8 TEXTEQU <[SP+18]>");
		AddLineQueue("WPARAM9 TEXTEQU <[SP+20]>");
		AddLineQueue("WPARAM10 TEXTEQU <[SP+22]>");
		AddLineQueue("WPARAM11 TEXTEQU <[SP+24]>");
		AddLineQueue("WPARAM12 TEXTEQU <[SP+26]>");
		AddLineQueue("WPARAM13 TEXTEQU <[SP+28]>");
		AddLineQueue("WPARAM14 TEXTEQU <[SP+30]>");
		AddLineQueue("WPARAM15 TEXTEQU <[SP+32]>");
		AddLineQueue("WPARAM16 TEXTEQU <[SP+34]>");
		AddLineQueue("WPARAM17 TEXTEQU <[SP+36]>");
		AddLineQueue("WPARAM18 TEXTEQU <[SP+38]>");
		AddLineQueue("WPARAM19 TEXTEQU <[SP+40]>");
		AddLineQueue("WPARAM20 TEXTEQU <[SP+42]>");
		AddLineQueue("WPARAM21 TEXTEQU <[SP+44]>");
		AddLineQueue("WPARAM22 TEXTEQU <[SP+46]>");
		AddLineQueue("WPARAM23 TEXTEQU <[SP+48]>");
		AddLineQueue("WPARAM24 TEXTEQU <[SP+50]>");
		AddLineQueue("WPARAM25 TEXTEQU <[SP+52]>");
		AddLineQueue("WPARAM26 TEXTEQU <[SP+54]>");
		AddLineQueue("WPARAM27 TEXTEQU <[SP+56]>");
		AddLineQueue("WPARAM28 TEXTEQU <[SP+58]>");
		AddLineQueue("WPARAM29 TEXTEQU <[SP+60]>");
		AddLineQueue("WPARAM30 TEXTEQU <[SP+62]>");
		AddLineQueue("WPARAM31 TEXTEQU <[SP+64]>");
		AddLineQueue("WPARAM32 TEXTEQU <[SP+66]>");
		AddLineQueue("WPARAM33 TEXTEQU <[SP+68]>");
		AddLineQueue("WPARAM34 TEXTEQU <[SP+70]>");
		AddLineQueue("WPARAM35 TEXTEQU <[SP+72]>");
		AddLineQueue("WPARAM36 TEXTEQU <[SP+74]>");
		AddLineQueue("WPARAM37 TEXTEQU <[SP+76]>");
		AddLineQueue("WPARAM38 TEXTEQU <[SP+78]>");
		AddLineQueue("WPARAM39 TEXTEQU <[SP+80]>");
		AddLineQueue("WPARAM40 TEXTEQU <[SP+82]>");
		AddLineQueue("WPARAM41 TEXTEQU <[SP+84]>");
		AddLineQueue("WPARAM42 TEXTEQU <[SP+86]>");
		AddLineQueue("WPARAM43 TEXTEQU <[SP+88]>");
		AddLineQueue("WPARAM44 TEXTEQU <[SP+90]>");
		AddLineQueue("WPARAM45 TEXTEQU <[SP+92]>");
		AddLineQueue("WPARAM46 TEXTEQU <[SP+94]>");
		AddLineQueue("WPARAM47 TEXTEQU <[SP+96]>");
		AddLineQueue("WPARAM48 TEXTEQU <[SP+98]>");
		AddLineQueue("WPARAM49 TEXTEQU <[SP+100]>");
		AddLineQueue("WPARAM50 TEXTEQU <[SP+102]>");
		AddLineQueue("WPARAM51 TEXTEQU <[SP+104]>");
		AddLineQueue("WPARAM52 TEXTEQU <[SP+106]>");
		AddLineQueue("WPARAM53 TEXTEQU <[SP+108]>");
		AddLineQueue("WPARAM54 TEXTEQU <[SP+110]>");
		AddLineQueue("WPARAM55 TEXTEQU <[SP+112]>");
		AddLineQueue("WPARAM56 TEXTEQU <[SP+114]>");
		AddLineQueue("WPARAM57 TEXTEQU <[SP+116]>");
		AddLineQueue("WPARAM58 TEXTEQU <[SP+118]>");
		AddLineQueue("WPARAM59 TEXTEQU <[SP+120]>");
		AddLineQueue("WPARAM60 TEXTEQU <[SP+122]>");
		AddLineQueue("WPARAM61 TEXTEQU <[SP+124]>");
		AddLineQueue("WPARAM62 TEXTEQU <[SP+126]>");
		AddLineQueue("WPARAM63 TEXTEQU <[SP+128]>");
		/* 8bits*/
		AddLineQueue("BRET TEXTEQU <AL>");
		AddLineQueue("BRETURN TEXTEQU <AL>");
		AddLineQueue("BSIDX TEXTEQU <SIL>");
		AddLineQueue("BDIDX TEXTEQU <DIL>");
		AddLineQueue("BBPTR TEXTEQU <BPL>");
		AddLineQueue("BSPTR TEXTEQU <SPL>");
		AddLineQueue("BBASE TEXTEQU <BL>");
		AddLineQueue("BPARAM0 TEXTEQU <CL>");
		AddLineQueue("BPARAM1 TEXTEQU <DL>");
		AddLineQueue("BPARAM2 TEXTEQU <[SPL+3]>");
		AddLineQueue("BPARAM3 TEXTEQU <[SPL+4]>");
		AddLineQueue("BPARAM4 TEXTEQU <[SPL+5]>");
		AddLineQueue("BPARAM5 TEXTEQU <[SPL+6]>");
		AddLineQueue("BPARAM6 TEXTEQU <[SPL+7]>");
		AddLineQueue("BPARAM7 TEXTEQU <[SPL+8]>");
		AddLineQueue("BPARAM8 TEXTEQU <[SPL+9]>");
		AddLineQueue("BPARAM9 TEXTEQU <[SPL+10]>");
		AddLineQueue("BPARAM10 TEXTEQU <[SPL+11]>");
		AddLineQueue("BPARAM11 TEXTEQU <[SPL+12]>");
		AddLineQueue("BPARAM12 TEXTEQU <[SPL+13]>");
		AddLineQueue("BPARAM13 TEXTEQU <[SPL+14]>");
		AddLineQueue("BPARAM14 TEXTEQU <[SPL+15]>");
		AddLineQueue("BPARAM15 TEXTEQU <[SPL+16]>");
		AddLineQueue("BPARAM16 TEXTEQU <[SPL+17]>");
		AddLineQueue("BPARAM17 TEXTEQU <[SPL+18]>");
		AddLineQueue("BPARAM18 TEXTEQU <[SPL+19]>");
		AddLineQueue("BPARAM19 TEXTEQU <[SPL+20]>");
		AddLineQueue("BPARAM20 TEXTEQU <[SPL+21]>");
		AddLineQueue("BPARAM21 TEXTEQU <[SPL+22]>");
		AddLineQueue("BPARAM22 TEXTEQU <[SPL+23]>");
		AddLineQueue("BPARAM23 TEXTEQU <[SPL+24]>");
		AddLineQueue("BPARAM24 TEXTEQU <[SPL+25]>");
		AddLineQueue("BPARAM25 TEXTEQU <[SPL+26]>");
		AddLineQueue("BPARAM26 TEXTEQU <[SPL+27]>");
		AddLineQueue("BPARAM27 TEXTEQU <[SPL+28]>");
		AddLineQueue("BPARAM28 TEXTEQU <[SPL+29]>");
		AddLineQueue("BPARAM29 TEXTEQU <[SPL+30]>");
		AddLineQueue("BPARAM30 TEXTEQU <[SPL+31]>");
		AddLineQueue("BPARAM31 TEXTEQU <[SPL+32]>");
		AddLineQueue("BPARAM32 TEXTEQU <[SPL+33]>");
		AddLineQueue("BPARAM33 TEXTEQU <[SPL+34]>");
		AddLineQueue("BPARAM34 TEXTEQU <[SPL+35]>");
		AddLineQueue("BPARAM35 TEXTEQU <[SPL+36]>");
		AddLineQueue("BPARAM36 TEXTEQU <[SPL+37]>");
		AddLineQueue("BPARAM37 TEXTEQU <[SPL+38]>");
		AddLineQueue("BPARAM38 TEXTEQU <[SPL+39]>");
		AddLineQueue("BPARAM39 TEXTEQU <[SPL+40]>");
		AddLineQueue("BPARAM40 TEXTEQU <[SPL+41]>");
		AddLineQueue("BPARAM41 TEXTEQU <[SPL+42]>");
		AddLineQueue("BPARAM42 TEXTEQU <[SPL+43]>");
		AddLineQueue("BPARAM43 TEXTEQU <[SPL+44]>");
		AddLineQueue("BPARAM44 TEXTEQU <[SPL+45]>");
		AddLineQueue("BPARAM45 TEXTEQU <[SPL+46]>");
		AddLineQueue("BPARAM46 TEXTEQU <[SPL+47]>");
		AddLineQueue("BPARAM47 TEXTEQU <[SPL+48]>");
		AddLineQueue("BPARAM48 TEXTEQU <[SPL+49]>");
		AddLineQueue("BPARAM49 TEXTEQU <[SPL+50]>");
		AddLineQueue("BPARAM50 TEXTEQU <[SPL+51]>");
		AddLineQueue("BPARAM51 TEXTEQU <[SPL+52]>");
		AddLineQueue("BPARAM52 TEXTEQU <[SPL+53]>");
		AddLineQueue("BPARAM53 TEXTEQU <[SPL+54]>");
		AddLineQueue("BPARAM54 TEXTEQU <[SPL+55]>");
		AddLineQueue("BPARAM55 TEXTEQU <[SPL+56]>");
		AddLineQueue("BPARAM56 TEXTEQU <[SPL+57]>");
		AddLineQueue("BPARAM57 TEXTEQU <[SPL+58]>");
		AddLineQueue("BPARAM58 TEXTEQU <[SPL+59]>");
		AddLineQueue("BPARAM59 TEXTEQU <[SPL+60]>");
		AddLineQueue("BPARAM60 TEXTEQU <[SPL+61]>");
		AddLineQueue("BPARAM61 TEXTEQU <[SPL+62]>");
		AddLineQueue("BPARAM62 TEXTEQU <[SPL+63]>");
		AddLineQueue("BPARAM63 TEXTEQU <[SPL+64]>");
	}
	AddLineQueue("ENDIF"); /*__WIN32__*/

	AddLineQueue("IFDEF __UNIX64__");
	AddLineQueue("IFNDEF DEFINED_SYSTEMV");
	AddLineQueue("DEFINE DEFINED_SYSTEMV");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF CALLCONV");
	AddLineQueue("CALLCONV TEXTEQU <SYSTEMV>");
	AddLineQueue("ENDIF");
	AddLineQueue("CALLCONVOPT TEXTEQU <option language:SYSTEMV>");
	if (ModuleInfo.langtype == LANG_REGCALL)
	{
		/* 64bits*/
		AddLineQueue("RRET TEXTEQU <RAX>");
		AddLineQueue("RRETURN TEXTEQU <RAX>");
		AddLineQueue("RSIDX TEXTEQU <RSI>");
		AddLineQueue("RDIDX TEXTEQU <RDI>");
		AddLineQueue("RBPTR TEXTEQU <RBP>");
		AddLineQueue("RSPTR TEXTEQU <RSP>");
		AddLineQueue("RBASE TEXTEQU <RBX>");
		AddLineQueue("RPARAM0 TEXTEQU <RAX>");
		AddLineQueue("RPARAM1 TEXTEQU <RCX>");
		AddLineQueue("RPARAM2 TEXTEQU <RDX>");
		AddLineQueue("RPARAM3 TEXTEQU <RDI>");
		AddLineQueue("RPARAM4 TEXTEQU <RSI>");
		AddLineQueue("RPARAM5 TEXTEQU <R8>");
		AddLineQueue("RPARAM6 TEXTEQU <R9>");
		AddLineQueue("RPARAM7 TEXTEQU <R10>");
		AddLineQueue("RPARAM8 TEXTEQU <R11>");
		AddLineQueue("RPARAM9 TEXTEQU <R12>");
		AddLineQueue("RPARAM10 TEXTEQU <R14>");
		AddLineQueue("RPARAM11 TEXTEQU <R15>");
		AddLineQueue("RPARAM12 TEXTEQU <[RSP+104]>");
		AddLineQueue("RPARAM13 TEXTEQU <[RSP+112]>");
		AddLineQueue("RPARAM14 TEXTEQU <[RSP+120]>");
		AddLineQueue("RPARAM15 TEXTEQU <[RSP+128]>");
		AddLineQueue("RPARAM16 TEXTEQU <[RSP+136]>");
		AddLineQueue("RPARAM17 TEXTEQU <[RSP+144]>");
		AddLineQueue("RPARAM18 TEXTEQU <[RSP+152]>");
		AddLineQueue("RPARAM19 TEXTEQU <[RSP+160]>");
		AddLineQueue("RPARAM20 TEXTEQU <[RSP+168]>");
		AddLineQueue("RPARAM21 TEXTEQU <[RSP+176]>");
		AddLineQueue("RPARAM22 TEXTEQU <[RSP+184]>");
		AddLineQueue("RPARAM23 TEXTEQU <[RSP+192]>");
		AddLineQueue("RPARAM24 TEXTEQU <[RSP+200]>");
		AddLineQueue("RPARAM25 TEXTEQU <[RSP+208]>");
		AddLineQueue("RPARAM26 TEXTEQU <[RSP+216]>");
		AddLineQueue("RPARAM27 TEXTEQU <[RSP+224]>");
		AddLineQueue("RPARAM28 TEXTEQU <[RSP+232]>");
		AddLineQueue("RPARAM29 TEXTEQU <[RSP+240]>");
		AddLineQueue("RPARAM30 TEXTEQU <[RSP+248]>");
		AddLineQueue("RPARAM31 TEXTEQU <[RSP+256]>");
		AddLineQueue("RPARAM32 TEXTEQU <[RSP+264]>");
		AddLineQueue("RPARAM33 TEXTEQU <[RSP+272]>");
		AddLineQueue("RPARAM34 TEXTEQU <[RSP+280]>");
		AddLineQueue("RPARAM35 TEXTEQU <[RSP+288]>");
		AddLineQueue("RPARAM36 TEXTEQU <[RSP+296]>");
		AddLineQueue("RPARAM37 TEXTEQU <[RSP+304]>");
		AddLineQueue("RPARAM38 TEXTEQU <[RSP+312]>");
		AddLineQueue("RPARAM39 TEXTEQU <[RSP+320]>");
		AddLineQueue("RPARAM40 TEXTEQU <[RSP+328]>");
		AddLineQueue("RPARAM41 TEXTEQU <[RSP+336]>");
		AddLineQueue("RPARAM42 TEXTEQU <[RSP+344]>");
		AddLineQueue("RPARAM43 TEXTEQU <[RSP+352]>");
		AddLineQueue("RPARAM44 TEXTEQU <[RSP+360]>");
		AddLineQueue("RPARAM45 TEXTEQU <[RSP+368]>");
		AddLineQueue("RPARAM46 TEXTEQU <[RSP+376]>");
		AddLineQueue("RPARAM47 TEXTEQU <[RSP+384]>");
		AddLineQueue("RPARAM48 TEXTEQU <[RSP+392]>");
		AddLineQueue("RPARAM49 TEXTEQU <[RSP+400]>");
		AddLineQueue("RPARAM50 TEXTEQU <[RSP+408]>");
		AddLineQueue("RPARAM51 TEXTEQU <[RSP+416]>");
		AddLineQueue("RPARAM52 TEXTEQU <[RSP+424]>");
		AddLineQueue("RPARAM53 TEXTEQU <[RSP+432]>");
		AddLineQueue("RPARAM54 TEXTEQU <[RSP+440]>");
		AddLineQueue("RPARAM55 TEXTEQU <[RSP+448]>");
		AddLineQueue("RPARAM56 TEXTEQU <[RSP+456]>");
		AddLineQueue("RPARAM57 TEXTEQU <[RSP+464]>");
		AddLineQueue("RPARAM58 TEXTEQU <[RSP+472]>");
		AddLineQueue("RPARAM59 TEXTEQU <[RSP+480]>");
		AddLineQueue("RPARAM60 TEXTEQU <[RSP+488]>");
		AddLineQueue("RPARAM61 TEXTEQU <[RSP+496]>");
		AddLineQueue("RPARAM62 TEXTEQU <[RSP+504]>");
		AddLineQueue("RPARAM63 TEXTEQU <[RSP+512]>");
		/* 32bits*/
		AddLineQueue("DRET TEXTEQU <EAX>");
		AddLineQueue("DRETURN TEXTEQU <EAX>");
		AddLineQueue("DSIDX TEXTEQU <ESI>");
		AddLineQueue("DDIDX TEXTEQU <EDI>");
		AddLineQueue("DBPTR TEXTEQU <EBP>");
		AddLineQueue("DSPTR TEXTEQU <ESP>");
		AddLineQueue("DBASE TEXTEQU <EBX>");
		AddLineQueue("DPARAM0 TEXTEQU <EAX>");
		AddLineQueue("DPARAM1 TEXTEQU <ECX>");
		AddLineQueue("DPARAM2 TEXTEQU <EDX>");
		AddLineQueue("DPARAM3 TEXTEQU <EDI>");
		AddLineQueue("DPARAM4 TEXTEQU <ESI>");
		AddLineQueue("DPARAM5 TEXTEQU <R8D>");
		AddLineQueue("DPARAM6 TEXTEQU <R9D>");
		AddLineQueue("DPARAM7 TEXTEQU <R10D>");
		AddLineQueue("DPARAM8 TEXTEQU <R11D>");
		AddLineQueue("DPARAM9 TEXTEQU <R12D>");
		AddLineQueue("DPARAM10 TEXTEQU <R14D>");
		AddLineQueue("DPARAM11 TEXTEQU <R15D>");
		AddLineQueue("DPARAM12 TEXTEQU <[ESP+52]>");
		AddLineQueue("DPARAM13 TEXTEQU <[ESP+56]>");
		AddLineQueue("DPARAM14 TEXTEQU <[ESP+60]>");
		AddLineQueue("DPARAM15 TEXTEQU <[ESP+64]>");
		AddLineQueue("DPARAM16 TEXTEQU <[ESP+68]>");
		AddLineQueue("DPARAM17 TEXTEQU <[ESP+72]>");
		AddLineQueue("DPARAM18 TEXTEQU <[ESP+76]>");
		AddLineQueue("DPARAM19 TEXTEQU <[ESP+80]>");
		AddLineQueue("DPARAM20 TEXTEQU <[ESP+84]>");
		AddLineQueue("DPARAM21 TEXTEQU <[ESP+88]>");
		AddLineQueue("DPARAM22 TEXTEQU <[ESP+92]>");
		AddLineQueue("DPARAM23 TEXTEQU <[ESP+96]>");
		AddLineQueue("DPARAM24 TEXTEQU <[ESP+100]>");
		AddLineQueue("DPARAM25 TEXTEQU <[ESP+104]>");
		AddLineQueue("DPARAM26 TEXTEQU <[ESP+108]>");
		AddLineQueue("DPARAM27 TEXTEQU <[ESP+112]>");
		AddLineQueue("DPARAM28 TEXTEQU <[ESP+116]>");
		AddLineQueue("DPARAM29 TEXTEQU <[ESP+120]>");
		AddLineQueue("DPARAM30 TEXTEQU <[ESP+124]>");
		AddLineQueue("DPARAM31 TEXTEQU <[ESP+128]>");
		AddLineQueue("DPARAM32 TEXTEQU <[ESP+132]>");
		AddLineQueue("DPARAM33 TEXTEQU <[ESP+136]>");
		AddLineQueue("DPARAM34 TEXTEQU <[ESP+140]>");
		AddLineQueue("DPARAM35 TEXTEQU <[ESP+144]>");
		AddLineQueue("DPARAM36 TEXTEQU <[ESP+148]>");
		AddLineQueue("DPARAM37 TEXTEQU <[ESP+152]>");
		AddLineQueue("DPARAM38 TEXTEQU <[ESP+156]>");
		AddLineQueue("DPARAM39 TEXTEQU <[ESP+160]>");
		AddLineQueue("DPARAM40 TEXTEQU <[ESP+164]>");
		AddLineQueue("DPARAM41 TEXTEQU <[ESP+168]>");
		AddLineQueue("DPARAM42 TEXTEQU <[ESP+172]>");
		AddLineQueue("DPARAM43 TEXTEQU <[ESP+176]>");
		AddLineQueue("DPARAM44 TEXTEQU <[ESP+180]>");
		AddLineQueue("DPARAM45 TEXTEQU <[ESP+184]>");
		AddLineQueue("DPARAM46 TEXTEQU <[ESP+188]>");
		AddLineQueue("DPARAM47 TEXTEQU <[ESP+192]>");
		AddLineQueue("DPARAM48 TEXTEQU <[ESP+196]>");
		AddLineQueue("DPARAM49 TEXTEQU <[ESP+200]>");
		AddLineQueue("DPARAM50 TEXTEQU <[ESP+204]>");
		AddLineQueue("DPARAM51 TEXTEQU <[ESP+208]>");
		AddLineQueue("DPARAM52 TEXTEQU <[ESP+212]>");
		AddLineQueue("DPARAM53 TEXTEQU <[ESP+216]>");
		AddLineQueue("DPARAM54 TEXTEQU <[ESP+220]>");
		AddLineQueue("DPARAM55 TEXTEQU <[ESP+224]>");
		AddLineQueue("DPARAM56 TEXTEQU <[ESP+228]>");
		AddLineQueue("DPARAM57 TEXTEQU <[ESP+232]>");
		AddLineQueue("DPARAM58 TEXTEQU <[ESP+236]>");
		AddLineQueue("DPARAM59 TEXTEQU <[ESP+240]>");
		AddLineQueue("DPARAM60 TEXTEQU <[ESP+244]>");
		AddLineQueue("DPARAM61 TEXTEQU <[ESP+248]>");
		AddLineQueue("DPARAM62 TEXTEQU <[ESP+252]>");
		AddLineQueue("DPARAM63 TEXTEQU <[ESP+256]>");
		/* 16bits*/
		AddLineQueue("WRET TEXTEQU <AX>");
		AddLineQueue("WRETURN TEXTEQU <AX>");
		AddLineQueue("WSIDX TEXTEQU <SI>");
		AddLineQueue("WDIDX TEXTEQU <DI>");
		AddLineQueue("WBPTR TEXTEQU <BP>");
		AddLineQueue("WSPTR TEXTEQU <SP>");
		AddLineQueue("WBASE TEXTEQU <BX>");
		AddLineQueue("WPARAM0 TEXTEQU <AX>");
		AddLineQueue("WPARAM1 TEXTEQU <CX>");
		AddLineQueue("WPARAM2 TEXTEQU <DX>");
		AddLineQueue("WPARAM3 TEXTEQU <DI>");
		AddLineQueue("WPARAM4 TEXTEQU <SI>");
		AddLineQueue("WPARAM5 TEXTEQU <R8W>");
		AddLineQueue("WPARAM6 TEXTEQU <R9W>");
		AddLineQueue("WPARAM7 TEXTEQU <R10W>");
		AddLineQueue("WPARAM8 TEXTEQU <R11W>");
		AddLineQueue("WPARAM9 TEXTEQU <R12W>");
		AddLineQueue("WPARAM10 TEXTEQU <R14W>");
		AddLineQueue("WPARAM11 TEXTEQU <R15W>");
		AddLineQueue("WPARAM12 TEXTEQU <[SP+26]>");
		AddLineQueue("WPARAM13 TEXTEQU <[SP+28]>");
		AddLineQueue("WPARAM14 TEXTEQU <[SP+30]>");
		AddLineQueue("WPARAM15 TEXTEQU <[SP+32]>");
		AddLineQueue("WPARAM16 TEXTEQU <[SP+34]>");
		AddLineQueue("WPARAM17 TEXTEQU <[SP+36]>");
		AddLineQueue("WPARAM18 TEXTEQU <[SP+38]>");
		AddLineQueue("WPARAM19 TEXTEQU <[SP+40]>");
		AddLineQueue("WPARAM20 TEXTEQU <[SP+42]>");
		AddLineQueue("WPARAM21 TEXTEQU <[SP+44]>");
		AddLineQueue("WPARAM22 TEXTEQU <[SP+46]>");
		AddLineQueue("WPARAM23 TEXTEQU <[SP+48]>");
		AddLineQueue("WPARAM24 TEXTEQU <[SP+50]>");
		AddLineQueue("WPARAM25 TEXTEQU <[SP+52]>");
		AddLineQueue("WPARAM26 TEXTEQU <[SP+54]>");
		AddLineQueue("WPARAM27 TEXTEQU <[SP+56]>");
		AddLineQueue("WPARAM28 TEXTEQU <[SP+58]>");
		AddLineQueue("WPARAM29 TEXTEQU <[SP+60]>");
		AddLineQueue("WPARAM30 TEXTEQU <[SP+62]>");
		AddLineQueue("WPARAM31 TEXTEQU <[SP+64]>");
		AddLineQueue("WPARAM32 TEXTEQU <[SP+66]>");
		AddLineQueue("WPARAM33 TEXTEQU <[SP+68]>");
		AddLineQueue("WPARAM34 TEXTEQU <[SP+70]>");
		AddLineQueue("WPARAM35 TEXTEQU <[SP+72]>");
		AddLineQueue("WPARAM36 TEXTEQU <[SP+74]>");
		AddLineQueue("WPARAM37 TEXTEQU <[SP+76]>");
		AddLineQueue("WPARAM38 TEXTEQU <[SP+78]>");
		AddLineQueue("WPARAM39 TEXTEQU <[SP+80]>");
		AddLineQueue("WPARAM40 TEXTEQU <[SP+82]>");
		AddLineQueue("WPARAM41 TEXTEQU <[SP+84]>");
		AddLineQueue("WPARAM42 TEXTEQU <[SP+86]>");
		AddLineQueue("WPARAM43 TEXTEQU <[SP+88]>");
		AddLineQueue("WPARAM44 TEXTEQU <[SP+90]>");
		AddLineQueue("WPARAM45 TEXTEQU <[SP+92]>");
		AddLineQueue("WPARAM46 TEXTEQU <[SP+94]>");
		AddLineQueue("WPARAM47 TEXTEQU <[SP+96]>");
		AddLineQueue("WPARAM48 TEXTEQU <[SP+98]>");
		AddLineQueue("WPARAM49 TEXTEQU <[SP+100]>");
		AddLineQueue("WPARAM50 TEXTEQU <[SP+102]>");
		AddLineQueue("WPARAM51 TEXTEQU <[SP+104]>");
		AddLineQueue("WPARAM52 TEXTEQU <[SP+106]>");
		AddLineQueue("WPARAM53 TEXTEQU <[SP+108]>");
		AddLineQueue("WPARAM54 TEXTEQU <[SP+110]>");
		AddLineQueue("WPARAM55 TEXTEQU <[SP+112]>");
		AddLineQueue("WPARAM56 TEXTEQU <[SP+114]>");
		AddLineQueue("WPARAM57 TEXTEQU <[SP+116]>");
		AddLineQueue("WPARAM58 TEXTEQU <[SP+118]>");
		AddLineQueue("WPARAM59 TEXTEQU <[SP+120]>");
		AddLineQueue("WPARAM60 TEXTEQU <[SP+122]>");
		AddLineQueue("WPARAM61 TEXTEQU <[SP+124]>");
		AddLineQueue("WPARAM62 TEXTEQU <[SP+126]>");
		AddLineQueue("WPARAM63 TEXTEQU <[SP+128]>");
		/* 8bits*/
		AddLineQueue("BRET TEXTEQU <AL>");
		AddLineQueue("BRETURN TEXTEQU <AL>");
		AddLineQueue("BSIDX TEXTEQU <SIL>");
		AddLineQueue("BDIDX TEXTEQU <DIL>");
		AddLineQueue("BBPTR TEXTEQU <BPL>");
		AddLineQueue("BSPTR TEXTEQU <SPL>");
		AddLineQueue("BBASE TEXTEQU <BL>");
		AddLineQueue("BPARAM0 TEXTEQU <AL>");
		AddLineQueue("BPARAM1 TEXTEQU <CL>");
		AddLineQueue("BPARAM2 TEXTEQU <DL>");
		AddLineQueue("BPARAM3 TEXTEQU <DIL>");
		AddLineQueue("BPARAM4 TEXTEQU <SIL>");
		AddLineQueue("BPARAM5 TEXTEQU <R8L>");
		AddLineQueue("BPARAM6 TEXTEQU <R9L>");
		AddLineQueue("BPARAM7 TEXTEQU <R10L>");
		AddLineQueue("BPARAM8 TEXTEQU <R11L>");
		AddLineQueue("BPARAM9 TEXTEQU <R12L>");
		AddLineQueue("BPARAM10 TEXTEQU <R14L>");
		AddLineQueue("BPARAM11 TEXTEQU <R15L>");
		AddLineQueue("BPARAM12 TEXTEQU <[SPL+13]>");
		AddLineQueue("BPARAM13 TEXTEQU <[SPL+14]>");
		AddLineQueue("BPARAM14 TEXTEQU <[SPL+15]>");
		AddLineQueue("BPARAM15 TEXTEQU <[SPL+16]>");
		AddLineQueue("BPARAM16 TEXTEQU <[SPL+17]>");
		AddLineQueue("BPARAM17 TEXTEQU <[SPL+18]>");
		AddLineQueue("BPARAM18 TEXTEQU <[SPL+19]>");
		AddLineQueue("BPARAM19 TEXTEQU <[SPL+20]>");
		AddLineQueue("BPARAM20 TEXTEQU <[SPL+21]>");
		AddLineQueue("BPARAM21 TEXTEQU <[SPL+22]>");
		AddLineQueue("BPARAM22 TEXTEQU <[SPL+23]>");
		AddLineQueue("BPARAM23 TEXTEQU <[SPL+24]>");
		AddLineQueue("BPARAM24 TEXTEQU <[SPL+25]>");
		AddLineQueue("BPARAM25 TEXTEQU <[SPL+26]>");
		AddLineQueue("BPARAM26 TEXTEQU <[SPL+27]>");
		AddLineQueue("BPARAM27 TEXTEQU <[SPL+28]>");
		AddLineQueue("BPARAM28 TEXTEQU <[SPL+29]>");
		AddLineQueue("BPARAM29 TEXTEQU <[SPL+30]>");
		AddLineQueue("BPARAM30 TEXTEQU <[SPL+31]>");
		AddLineQueue("BPARAM31 TEXTEQU <[SPL+32]>");
		AddLineQueue("BPARAM32 TEXTEQU <[SPL+33]>");
		AddLineQueue("BPARAM33 TEXTEQU <[SPL+34]>");
		AddLineQueue("BPARAM34 TEXTEQU <[SPL+35]>");
		AddLineQueue("BPARAM35 TEXTEQU <[SPL+36]>");
		AddLineQueue("BPARAM36 TEXTEQU <[SPL+37]>");
		AddLineQueue("BPARAM37 TEXTEQU <[SPL+38]>");
		AddLineQueue("BPARAM38 TEXTEQU <[SPL+39]>");
		AddLineQueue("BPARAM39 TEXTEQU <[SPL+40]>");
		AddLineQueue("BPARAM40 TEXTEQU <[SPL+41]>");
		AddLineQueue("BPARAM41 TEXTEQU <[SPL+42]>");
		AddLineQueue("BPARAM42 TEXTEQU <[SPL+43]>");
		AddLineQueue("BPARAM43 TEXTEQU <[SPL+44]>");
		AddLineQueue("BPARAM44 TEXTEQU <[SPL+45]>");
		AddLineQueue("BPARAM45 TEXTEQU <[SPL+46]>");
		AddLineQueue("BPARAM46 TEXTEQU <[SPL+47]>");
		AddLineQueue("BPARAM47 TEXTEQU <[SPL+48]>");
		AddLineQueue("BPARAM48 TEXTEQU <[SPL+49]>");
		AddLineQueue("BPARAM49 TEXTEQU <[SPL+50]>");
		AddLineQueue("BPARAM50 TEXTEQU <[SPL+51]>");
		AddLineQueue("BPARAM51 TEXTEQU <[SPL+52]>");
		AddLineQueue("BPARAM52 TEXTEQU <[SPL+53]>");
		AddLineQueue("BPARAM53 TEXTEQU <[SPL+54]>");
		AddLineQueue("BPARAM54 TEXTEQU <[SPL+55]>");
		AddLineQueue("BPARAM55 TEXTEQU <[SPL+56]>");
		AddLineQueue("BPARAM56 TEXTEQU <[SPL+57]>");
		AddLineQueue("BPARAM57 TEXTEQU <[SPL+58]>");
		AddLineQueue("BPARAM58 TEXTEQU <[SPL+59]>");
		AddLineQueue("BPARAM59 TEXTEQU <[SPL+60]>");
		AddLineQueue("BPARAM60 TEXTEQU <[SPL+61]>");
		AddLineQueue("BPARAM61 TEXTEQU <[SPL+62]>");
		AddLineQueue("BPARAM62 TEXTEQU <[SPL+63]>");
		AddLineQueue("BPARAM63 TEXTEQU <[SPL+64]>");
	}
	else
	{
		/* 64bits*/
		AddLineQueue("RRET TEXTEQU <RAX>");
		AddLineQueue("RRETURN TEXTEQU <RAX>");
		AddLineQueue("RSIDX TEXTEQU <RSI>");
		AddLineQueue("RDIDX TEXTEQU <RDI>");
		AddLineQueue("RBPTR TEXTEQU <RBP>");
		AddLineQueue("RSPTR TEXTEQU <RSP>");
		AddLineQueue("RBASE TEXTEQU <RBX>");
		AddLineQueue("RPARAM0 TEXTEQU <RDI>");
		AddLineQueue("RPARAM1 TEXTEQU <RSI>");
		AddLineQueue("RPARAM2 TEXTEQU <RDX>");
		AddLineQueue("RPARAM3 TEXTEQU <RCX>");
		AddLineQueue("RPARAM4 TEXTEQU <R8>");
		AddLineQueue("RPARAM5 TEXTEQU <R9>");
		AddLineQueue("RPARAM6 TEXTEQU <[RSP+56]>");
		AddLineQueue("RPARAM7 TEXTEQU <[RSP+64]>");
		AddLineQueue("RPARAM8 TEXTEQU <[RSP+72]>");
		AddLineQueue("RPARAM9 TEXTEQU <[RSP+80]>");
		AddLineQueue("RPARAM10 TEXTEQU <[RSP+88]>");
		AddLineQueue("RPARAM11 TEXTEQU <[RSP+96]>");
		AddLineQueue("RPARAM12 TEXTEQU <[RSP+104]>");
		AddLineQueue("RPARAM13 TEXTEQU <[RSP+112]>");
		AddLineQueue("RPARAM14 TEXTEQU <[RSP+120]>");
		AddLineQueue("RPARAM15 TEXTEQU <[RSP+128]>");
		AddLineQueue("RPARAM16 TEXTEQU <[RSP+136]>");
		AddLineQueue("RPARAM17 TEXTEQU <[RSP+144]>");
		AddLineQueue("RPARAM18 TEXTEQU <[RSP+152]>");
		AddLineQueue("RPARAM19 TEXTEQU <[RSP+160]>");
		AddLineQueue("RPARAM20 TEXTEQU <[RSP+168]>");
		AddLineQueue("RPARAM21 TEXTEQU <[RSP+176]>");
		AddLineQueue("RPARAM22 TEXTEQU <[RSP+184]>");
		AddLineQueue("RPARAM23 TEXTEQU <[RSP+192]>");
		AddLineQueue("RPARAM24 TEXTEQU <[RSP+200]>");
		AddLineQueue("RPARAM25 TEXTEQU <[RSP+208]>");
		AddLineQueue("RPARAM26 TEXTEQU <[RSP+216]>");
		AddLineQueue("RPARAM27 TEXTEQU <[RSP+224]>");
		AddLineQueue("RPARAM28 TEXTEQU <[RSP+232]>");
		AddLineQueue("RPARAM29 TEXTEQU <[RSP+240]>");
		AddLineQueue("RPARAM30 TEXTEQU <[RSP+248]>");
		AddLineQueue("RPARAM31 TEXTEQU <[RSP+256]>");
		AddLineQueue("RPARAM32 TEXTEQU <[RSP+264]>");
		AddLineQueue("RPARAM33 TEXTEQU <[RSP+272]>");
		AddLineQueue("RPARAM34 TEXTEQU <[RSP+280]>");
		AddLineQueue("RPARAM35 TEXTEQU <[RSP+288]>");
		AddLineQueue("RPARAM36 TEXTEQU <[RSP+296]>");
		AddLineQueue("RPARAM37 TEXTEQU <[RSP+304]>");
		AddLineQueue("RPARAM38 TEXTEQU <[RSP+312]>");
		AddLineQueue("RPARAM39 TEXTEQU <[RSP+320]>");
		AddLineQueue("RPARAM40 TEXTEQU <[RSP+328]>");
		AddLineQueue("RPARAM41 TEXTEQU <[RSP+336]>");
		AddLineQueue("RPARAM42 TEXTEQU <[RSP+344]>");
		AddLineQueue("RPARAM43 TEXTEQU <[RSP+352]>");
		AddLineQueue("RPARAM44 TEXTEQU <[RSP+360]>");
		AddLineQueue("RPARAM45 TEXTEQU <[RSP+368]>");
		AddLineQueue("RPARAM46 TEXTEQU <[RSP+376]>");
		AddLineQueue("RPARAM47 TEXTEQU <[RSP+384]>");
		AddLineQueue("RPARAM48 TEXTEQU <[RSP+392]>");
		AddLineQueue("RPARAM49 TEXTEQU <[RSP+400]>");
		AddLineQueue("RPARAM50 TEXTEQU <[RSP+408]>");
		AddLineQueue("RPARAM51 TEXTEQU <[RSP+416]>");
		AddLineQueue("RPARAM52 TEXTEQU <[RSP+424]>");
		AddLineQueue("RPARAM53 TEXTEQU <[RSP+432]>");
		AddLineQueue("RPARAM54 TEXTEQU <[RSP+440]>");
		AddLineQueue("RPARAM55 TEXTEQU <[RSP+448]>");
		AddLineQueue("RPARAM56 TEXTEQU <[RSP+456]>");
		AddLineQueue("RPARAM57 TEXTEQU <[RSP+464]>");
		AddLineQueue("RPARAM58 TEXTEQU <[RSP+472]>");
		AddLineQueue("RPARAM59 TEXTEQU <[RSP+480]>");
		AddLineQueue("RPARAM60 TEXTEQU <[RSP+488]>");
		AddLineQueue("RPARAM61 TEXTEQU <[RSP+496]>");
		AddLineQueue("RPARAM62 TEXTEQU <[RSP+504]>");
		AddLineQueue("RPARAM63 TEXTEQU <[RSP+512]>");
		/* 32bits*/
		AddLineQueue("DRET TEXTEQU <EAX>");
		AddLineQueue("DRETURN TEXTEQU <EAX>");
		AddLineQueue("DSIDX TEXTEQU <ESI>");
		AddLineQueue("DDIDX TEXTEQU <EDI>");
		AddLineQueue("DBPTR TEXTEQU <EBP>");
		AddLineQueue("DSPTR TEXTEQU <ESP>");
		AddLineQueue("DBASE TEXTEQU <EBX>");
		AddLineQueue("DPARAM0 TEXTEQU <EDI>");
		AddLineQueue("DPARAM1 TEXTEQU <ESI>");
		AddLineQueue("DPARAM2 TEXTEQU <EDX>");
		AddLineQueue("DPARAM3 TEXTEQU <ECX>");
		AddLineQueue("DPARAM4 TEXTEQU <R8D>");
		AddLineQueue("DPARAM5 TEXTEQU <R9D>");
		AddLineQueue("DPARAM6 TEXTEQU <[ESP+28]>");
		AddLineQueue("DPARAM7 TEXTEQU <[ESP+32]>");
		AddLineQueue("DPARAM8 TEXTEQU <[ESP+36]>");
		AddLineQueue("DPARAM9 TEXTEQU <[ESP+40]>");
		AddLineQueue("DPARAM10 TEXTEQU <[ESP+44]>");
		AddLineQueue("DPARAM11 TEXTEQU <[ESP+48]>");
		AddLineQueue("DPARAM12 TEXTEQU <[ESP+52]>");
		AddLineQueue("DPARAM13 TEXTEQU <[ESP+56]>");
		AddLineQueue("DPARAM14 TEXTEQU <[ESP+60]>");
		AddLineQueue("DPARAM15 TEXTEQU <[ESP+64]>");
		AddLineQueue("DPARAM16 TEXTEQU <[ESP+68]>");
		AddLineQueue("DPARAM17 TEXTEQU <[ESP+72]>");
		AddLineQueue("DPARAM18 TEXTEQU <[ESP+76]>");
		AddLineQueue("DPARAM19 TEXTEQU <[ESP+80]>");
		AddLineQueue("DPARAM20 TEXTEQU <[ESP+84]>");
		AddLineQueue("DPARAM21 TEXTEQU <[ESP+88]>");
		AddLineQueue("DPARAM22 TEXTEQU <[ESP+92]>");
		AddLineQueue("DPARAM23 TEXTEQU <[ESP+96]>");
		AddLineQueue("DPARAM24 TEXTEQU <[ESP+100]>");
		AddLineQueue("DPARAM25 TEXTEQU <[ESP+104]>");
		AddLineQueue("DPARAM26 TEXTEQU <[ESP+108]>");
		AddLineQueue("DPARAM27 TEXTEQU <[ESP+112]>");
		AddLineQueue("DPARAM28 TEXTEQU <[ESP+116]>");
		AddLineQueue("DPARAM29 TEXTEQU <[ESP+120]>");
		AddLineQueue("DPARAM30 TEXTEQU <[ESP+124]>");
		AddLineQueue("DPARAM31 TEXTEQU <[ESP+128]>");
		AddLineQueue("DPARAM32 TEXTEQU <[ESP+132]>");
		AddLineQueue("DPARAM33 TEXTEQU <[ESP+136]>");
		AddLineQueue("DPARAM34 TEXTEQU <[ESP+140]>");
		AddLineQueue("DPARAM35 TEXTEQU <[ESP+144]>");
		AddLineQueue("DPARAM36 TEXTEQU <[ESP+148]>");
		AddLineQueue("DPARAM37 TEXTEQU <[ESP+152]>");
		AddLineQueue("DPARAM38 TEXTEQU <[ESP+156]>");
		AddLineQueue("DPARAM39 TEXTEQU <[ESP+160]>");
		AddLineQueue("DPARAM40 TEXTEQU <[ESP+164]>");
		AddLineQueue("DPARAM41 TEXTEQU <[ESP+168]>");
		AddLineQueue("DPARAM42 TEXTEQU <[ESP+172]>");
		AddLineQueue("DPARAM43 TEXTEQU <[ESP+176]>");
		AddLineQueue("DPARAM44 TEXTEQU <[ESP+180]>");
		AddLineQueue("DPARAM45 TEXTEQU <[ESP+184]>");
		AddLineQueue("DPARAM46 TEXTEQU <[ESP+188]>");
		AddLineQueue("DPARAM47 TEXTEQU <[ESP+192]>");
		AddLineQueue("DPARAM48 TEXTEQU <[ESP+196]>");
		AddLineQueue("DPARAM49 TEXTEQU <[ESP+200]>");
		AddLineQueue("DPARAM50 TEXTEQU <[ESP+204]>");
		AddLineQueue("DPARAM51 TEXTEQU <[ESP+208]>");
		AddLineQueue("DPARAM52 TEXTEQU <[ESP+212]>");
		AddLineQueue("DPARAM53 TEXTEQU <[ESP+216]>");
		AddLineQueue("DPARAM54 TEXTEQU <[ESP+220]>");
		AddLineQueue("DPARAM55 TEXTEQU <[ESP+224]>");
		AddLineQueue("DPARAM56 TEXTEQU <[ESP+228]>");
		AddLineQueue("DPARAM57 TEXTEQU <[ESP+232]>");
		AddLineQueue("DPARAM58 TEXTEQU <[ESP+236]>");
		AddLineQueue("DPARAM59 TEXTEQU <[ESP+240]>");
		AddLineQueue("DPARAM60 TEXTEQU <[ESP+244]>");
		AddLineQueue("DPARAM61 TEXTEQU <[ESP+248]>");
		AddLineQueue("DPARAM62 TEXTEQU <[ESP+252]>");
		AddLineQueue("DPARAM63 TEXTEQU <[ESP+256]>");
		/* 16bits*/
		AddLineQueue("WRET TEXTEQU <AX>");
		AddLineQueue("WRETURN TEXTEQU <AX>");
		AddLineQueue("WSIDX TEXTEQU <SI>");
		AddLineQueue("WDIDX TEXTEQU <DI>");
		AddLineQueue("WBPTR TEXTEQU <BP>");
		AddLineQueue("WSPTR TEXTEQU <SP>");
		AddLineQueue("WBASE TEXTEQU <BX>");
		AddLineQueue("WPARAM0 TEXTEQU <DI>");
		AddLineQueue("WPARAM1 TEXTEQU <SI>");
		AddLineQueue("WPARAM2 TEXTEQU <DX>");
		AddLineQueue("WPARAM3 TEXTEQU <CX>");
		AddLineQueue("WPARAM4 TEXTEQU <R8W>");
		AddLineQueue("WPARAM5 TEXTEQU <R9W>");
		AddLineQueue("WPARAM6 TEXTEQU <[SP+14]>");
		AddLineQueue("WPARAM7 TEXTEQU <[SP+16]>");
		AddLineQueue("WPARAM8 TEXTEQU <[SP+18]>");
		AddLineQueue("WPARAM9 TEXTEQU <[SP+20]>");
		AddLineQueue("WPARAM10 TEXTEQU <[SP+22]>");
		AddLineQueue("WPARAM11 TEXTEQU <[SP+24]>");
		AddLineQueue("WPARAM12 TEXTEQU <[SP+26]>");
		AddLineQueue("WPARAM13 TEXTEQU <[SP+28]>");
		AddLineQueue("WPARAM14 TEXTEQU <[SP+30]>");
		AddLineQueue("WPARAM15 TEXTEQU <[SP+32]>");
		AddLineQueue("WPARAM16 TEXTEQU <[SP+34]>");
		AddLineQueue("WPARAM17 TEXTEQU <[SP+36]>");
		AddLineQueue("WPARAM18 TEXTEQU <[SP+38]>");
		AddLineQueue("WPARAM19 TEXTEQU <[SP+40]>");
		AddLineQueue("WPARAM20 TEXTEQU <[SP+42]>");
		AddLineQueue("WPARAM21 TEXTEQU <[SP+44]>");
		AddLineQueue("WPARAM22 TEXTEQU <[SP+46]>");
		AddLineQueue("WPARAM23 TEXTEQU <[SP+48]>");
		AddLineQueue("WPARAM24 TEXTEQU <[SP+50]>");
		AddLineQueue("WPARAM25 TEXTEQU <[SP+52]>");
		AddLineQueue("WPARAM26 TEXTEQU <[SP+54]>");
		AddLineQueue("WPARAM27 TEXTEQU <[SP+56]>");
		AddLineQueue("WPARAM28 TEXTEQU <[SP+58]>");
		AddLineQueue("WPARAM29 TEXTEQU <[SP+60]>");
		AddLineQueue("WPARAM30 TEXTEQU <[SP+62]>");
		AddLineQueue("WPARAM31 TEXTEQU <[SP+64]>");
		AddLineQueue("WPARAM32 TEXTEQU <[SP+66]>");
		AddLineQueue("WPARAM33 TEXTEQU <[SP+68]>");
		AddLineQueue("WPARAM34 TEXTEQU <[SP+70]>");
		AddLineQueue("WPARAM35 TEXTEQU <[SP+72]>");
		AddLineQueue("WPARAM36 TEXTEQU <[SP+74]>");
		AddLineQueue("WPARAM37 TEXTEQU <[SP+76]>");
		AddLineQueue("WPARAM38 TEXTEQU <[SP+78]>");
		AddLineQueue("WPARAM39 TEXTEQU <[SP+80]>");
		AddLineQueue("WPARAM40 TEXTEQU <[SP+82]>");
		AddLineQueue("WPARAM41 TEXTEQU <[SP+84]>");
		AddLineQueue("WPARAM42 TEXTEQU <[SP+86]>");
		AddLineQueue("WPARAM43 TEXTEQU <[SP+88]>");
		AddLineQueue("WPARAM44 TEXTEQU <[SP+90]>");
		AddLineQueue("WPARAM45 TEXTEQU <[SP+92]>");
		AddLineQueue("WPARAM46 TEXTEQU <[SP+94]>");
		AddLineQueue("WPARAM47 TEXTEQU <[SP+96]>");
		AddLineQueue("WPARAM48 TEXTEQU <[SP+98]>");
		AddLineQueue("WPARAM49 TEXTEQU <[SP+100]>");
		AddLineQueue("WPARAM50 TEXTEQU <[SP+102]>");
		AddLineQueue("WPARAM51 TEXTEQU <[SP+104]>");
		AddLineQueue("WPARAM52 TEXTEQU <[SP+106]>");
		AddLineQueue("WPARAM53 TEXTEQU <[SP+108]>");
		AddLineQueue("WPARAM54 TEXTEQU <[SP+110]>");
		AddLineQueue("WPARAM55 TEXTEQU <[SP+112]>");
		AddLineQueue("WPARAM56 TEXTEQU <[SP+114]>");
		AddLineQueue("WPARAM57 TEXTEQU <[SP+116]>");
		AddLineQueue("WPARAM58 TEXTEQU <[SP+118]>");
		AddLineQueue("WPARAM59 TEXTEQU <[SP+120]>");
		AddLineQueue("WPARAM60 TEXTEQU <[SP+122]>");
		AddLineQueue("WPARAM61 TEXTEQU <[SP+124]>");
		AddLineQueue("WPARAM62 TEXTEQU <[SP+126]>");
		AddLineQueue("WPARAM63 TEXTEQU <[SP+128]>");
		/* 8bits*/
		AddLineQueue("BRET TEXTEQU <AL>");
		AddLineQueue("BRETURN TEXTEQU <AL>");
		AddLineQueue("BSIDX TEXTEQU <SIL>");
		AddLineQueue("BDIDX TEXTEQU <DIL>");
		AddLineQueue("BBPTR TEXTEQU <BPL>");
		AddLineQueue("BSPTR TEXTEQU <SPL>");
		AddLineQueue("BBASE TEXTEQU <BL>");
		AddLineQueue("BPARAM0 TEXTEQU <DIL>");
		AddLineQueue("BPARAM1 TEXTEQU <SIL>");
		AddLineQueue("BPARAM2 TEXTEQU <DL>");
		AddLineQueue("BPARAM3 TEXTEQU <CL>");
		AddLineQueue("BPARAM4 TEXTEQU <R8L>");
		AddLineQueue("BPARAM5 TEXTEQU <R9L>");
		AddLineQueue("BPARAM6 TEXTEQU <[SPL+7]>");
		AddLineQueue("BPARAM7 TEXTEQU <[SPL+8]>");
		AddLineQueue("BPARAM8 TEXTEQU <[SPL+9]>");
		AddLineQueue("BPARAM9 TEXTEQU <[SPL+10]>");
		AddLineQueue("BPARAM10 TEXTEQU <[SPL+11]>");
		AddLineQueue("BPARAM11 TEXTEQU <[SPL+12]>");
		AddLineQueue("BPARAM12 TEXTEQU <[SPL+13]>");
		AddLineQueue("BPARAM13 TEXTEQU <[SPL+14]>");
		AddLineQueue("BPARAM14 TEXTEQU <[SPL+15]>");
		AddLineQueue("BPARAM15 TEXTEQU <[SPL+16]>");
		AddLineQueue("BPARAM16 TEXTEQU <[SPL+17]>");
		AddLineQueue("BPARAM17 TEXTEQU <[SPL+18]>");
		AddLineQueue("BPARAM18 TEXTEQU <[SPL+19]>");
		AddLineQueue("BPARAM19 TEXTEQU <[SPL+20]>");
		AddLineQueue("BPARAM20 TEXTEQU <[SPL+21]>");
		AddLineQueue("BPARAM21 TEXTEQU <[SPL+22]>");
		AddLineQueue("BPARAM22 TEXTEQU <[SPL+23]>");
		AddLineQueue("BPARAM23 TEXTEQU <[SPL+24]>");
		AddLineQueue("BPARAM24 TEXTEQU <[SPL+25]>");
		AddLineQueue("BPARAM25 TEXTEQU <[SPL+26]>");
		AddLineQueue("BPARAM26 TEXTEQU <[SPL+27]>");
		AddLineQueue("BPARAM27 TEXTEQU <[SPL+28]>");
		AddLineQueue("BPARAM28 TEXTEQU <[SPL+29]>");
		AddLineQueue("BPARAM29 TEXTEQU <[SPL+30]>");
		AddLineQueue("BPARAM30 TEXTEQU <[SPL+31]>");
		AddLineQueue("BPARAM31 TEXTEQU <[SPL+32]>");
		AddLineQueue("BPARAM32 TEXTEQU <[SPL+33]>");
		AddLineQueue("BPARAM33 TEXTEQU <[SPL+34]>");
		AddLineQueue("BPARAM34 TEXTEQU <[SPL+35]>");
		AddLineQueue("BPARAM35 TEXTEQU <[SPL+36]>");
		AddLineQueue("BPARAM36 TEXTEQU <[SPL+37]>");
		AddLineQueue("BPARAM37 TEXTEQU <[SPL+38]>");
		AddLineQueue("BPARAM38 TEXTEQU <[SPL+39]>");
		AddLineQueue("BPARAM39 TEXTEQU <[SPL+40]>");
		AddLineQueue("BPARAM40 TEXTEQU <[SPL+41]>");
		AddLineQueue("BPARAM41 TEXTEQU <[SPL+42]>");
		AddLineQueue("BPARAM42 TEXTEQU <[SPL+43]>");
		AddLineQueue("BPARAM43 TEXTEQU <[SPL+44]>");
		AddLineQueue("BPARAM44 TEXTEQU <[SPL+45]>");
		AddLineQueue("BPARAM45 TEXTEQU <[SPL+46]>");
		AddLineQueue("BPARAM46 TEXTEQU <[SPL+47]>");
		AddLineQueue("BPARAM47 TEXTEQU <[SPL+48]>");
		AddLineQueue("BPARAM48 TEXTEQU <[SPL+49]>");
		AddLineQueue("BPARAM49 TEXTEQU <[SPL+50]>");
		AddLineQueue("BPARAM50 TEXTEQU <[SPL+51]>");
		AddLineQueue("BPARAM51 TEXTEQU <[SPL+52]>");
		AddLineQueue("BPARAM52 TEXTEQU <[SPL+53]>");
		AddLineQueue("BPARAM53 TEXTEQU <[SPL+54]>");
		AddLineQueue("BPARAM54 TEXTEQU <[SPL+55]>");
		AddLineQueue("BPARAM55 TEXTEQU <[SPL+56]>");
		AddLineQueue("BPARAM56 TEXTEQU <[SPL+57]>");
		AddLineQueue("BPARAM57 TEXTEQU <[SPL+58]>");
		AddLineQueue("BPARAM58 TEXTEQU <[SPL+59]>");
		AddLineQueue("BPARAM59 TEXTEQU <[SPL+60]>");
		AddLineQueue("BPARAM60 TEXTEQU <[SPL+61]>");
		AddLineQueue("BPARAM61 TEXTEQU <[SPL+62]>");
		AddLineQueue("BPARAM62 TEXTEQU <[SPL+63]>");
		AddLineQueue("BPARAM63 TEXTEQU <[SPL+64]>");
	}
	AddLineQueue("ENDIF"); /*__UNIX64__*/

	AddLineQueue("IFNDEF __MACH__");
	AddLineQueue("IFDEF __UNIX32__");
	AddLineQueue("IFNDEF DEFINED_SYSTEMV");
	AddLineQueue("DEFINE DEFINED_SYSTEMV");
	AddLineQueue("ENDIF");
	AddLineQueue("IFNDEF CALLCONV");
	AddLineQueue("CALLCONV TEXTEQU <SYSTEMV>");
	AddLineQueue("ENDIF");
	AddLineQueue("CALLCONVOPT TEXTEQU <option language:SYSTEMV>");
	if (ModuleInfo.langtype == LANG_REGCALL)
	{
		/* 32bits*/
		AddLineQueue("RRET TEXTEQU <EAX>");
		AddLineQueue("RRETURN TEXTEQU <EAX>");
		AddLineQueue("RSIDX TEXTEQU <ESI>");
		AddLineQueue("RDIDX TEXTEQU <EDI>");
		AddLineQueue("RBPTR TEXTEQU <EBP>");
		AddLineQueue("RSPTR TEXTEQU <ESP>");
		AddLineQueue("RBASE TEXTEQU <EBX>");
		AddLineQueue("RPARAM0 TEXTEQU <EAX>");
		AddLineQueue("RPARAM1 TEXTEQU <ECX>");
		AddLineQueue("RPARAM2 TEXTEQU <EDX>");
		AddLineQueue("RPARAM3 TEXTEQU <EDI>");
		AddLineQueue("RPARAM4 TEXTEQU <ESI>");
		AddLineQueue("RPARAM5 TEXTEQU <[ESP+24]>");
		AddLineQueue("RPARAM6 TEXTEQU <[ESP+28]>");
		AddLineQueue("RPARAM7 TEXTEQU <[ESP+32]>");
		AddLineQueue("RPARAM8 TEXTEQU <[ESP+36]>");
		AddLineQueue("RPARAM9 TEXTEQU <[ESP+40]>");
		AddLineQueue("RPARAM10 TEXTEQU <[ESP+44]>");
		AddLineQueue("RPARAM11 TEXTEQU <[ESP+48]>");
		AddLineQueue("RPARAM12 TEXTEQU <[ESP+52]>");
		AddLineQueue("RPARAM13 TEXTEQU <[ESP+56]>");
		AddLineQueue("RPARAM14 TEXTEQU <[ESP+60]>");
		AddLineQueue("RPARAM15 TEXTEQU <[ESP+64]>");
		AddLineQueue("RPARAM16 TEXTEQU <[ESP+68]>");
		AddLineQueue("RPARAM17 TEXTEQU <[ESP+72]>");
		AddLineQueue("RPARAM18 TEXTEQU <[ESP+76]>");
		AddLineQueue("RPARAM19 TEXTEQU <[ESP+80]>");
		AddLineQueue("RPARAM20 TEXTEQU <[ESP+84]>");
		AddLineQueue("RPARAM21 TEXTEQU <[ESP+88]>");
		AddLineQueue("RPARAM22 TEXTEQU <[ESP+92]>");
		AddLineQueue("RPARAM23 TEXTEQU <[ESP+96]>");
		AddLineQueue("RPARAM24 TEXTEQU <[ESP+100]>");
		AddLineQueue("RPARAM25 TEXTEQU <[ESP+104]>");
		AddLineQueue("RPARAM26 TEXTEQU <[ESP+108]>");
		AddLineQueue("RPARAM27 TEXTEQU <[ESP+112]>");
		AddLineQueue("RPARAM28 TEXTEQU <[ESP+116]>");
		AddLineQueue("RPARAM29 TEXTEQU <[ESP+120]>");
		AddLineQueue("RPARAM30 TEXTEQU <[ESP+124]>");
		AddLineQueue("RPARAM31 TEXTEQU <[ESP+128]>");
		AddLineQueue("RPARAM32 TEXTEQU <[ESP+132]>");
		AddLineQueue("RPARAM33 TEXTEQU <[ESP+136]>");
		AddLineQueue("RPARAM34 TEXTEQU <[ESP+140]>");
		AddLineQueue("RPARAM35 TEXTEQU <[ESP+144]>");
		AddLineQueue("RPARAM36 TEXTEQU <[ESP+148]>");
		AddLineQueue("RPARAM37 TEXTEQU <[ESP+152]>");
		AddLineQueue("RPARAM38 TEXTEQU <[ESP+156]>");
		AddLineQueue("RPARAM39 TEXTEQU <[ESP+160]>");
		AddLineQueue("RPARAM40 TEXTEQU <[ESP+164]>");
		AddLineQueue("RPARAM41 TEXTEQU <[ESP+168]>");
		AddLineQueue("RPARAM42 TEXTEQU <[ESP+172]>");
		AddLineQueue("RPARAM43 TEXTEQU <[ESP+176]>");
		AddLineQueue("RPARAM44 TEXTEQU <[ESP+180]>");
		AddLineQueue("RPARAM45 TEXTEQU <[ESP+184]>");
		AddLineQueue("RPARAM46 TEXTEQU <[ESP+188]>");
		AddLineQueue("RPARAM47 TEXTEQU <[ESP+192]>");
		AddLineQueue("RPARAM48 TEXTEQU <[ESP+196]>");
		AddLineQueue("RPARAM49 TEXTEQU <[ESP+200]>");
		AddLineQueue("RPARAM50 TEXTEQU <[ESP+204]>");
		AddLineQueue("RPARAM51 TEXTEQU <[ESP+208]>");
		AddLineQueue("RPARAM52 TEXTEQU <[ESP+212]>");
		AddLineQueue("RPARAM53 TEXTEQU <[ESP+216]>");
		AddLineQueue("RPARAM54 TEXTEQU <[ESP+220]>");
		AddLineQueue("RPARAM55 TEXTEQU <[ESP+224]>");
		AddLineQueue("RPARAM56 TEXTEQU <[ESP+228]>");
		AddLineQueue("RPARAM57 TEXTEQU <[ESP+232]>");
		AddLineQueue("RPARAM58 TEXTEQU <[ESP+236]>");
		AddLineQueue("RPARAM59 TEXTEQU <[ESP+240]>");
		AddLineQueue("RPARAM60 TEXTEQU <[ESP+244]>");
		AddLineQueue("RPARAM61 TEXTEQU <[ESP+248]>");
		AddLineQueue("RPARAM62 TEXTEQU <[ESP+252]>");
		AddLineQueue("RPARAM63 TEXTEQU <[ESP+256]>");
		/* 32bits*/
		AddLineQueue("DRET TEXTEQU <EAX>");
		AddLineQueue("DRETURN TEXTEQU <EAX>");
		AddLineQueue("DSIDX TEXTEQU <ESI>");
		AddLineQueue("DDIDX TEXTEQU <EDI>");
		AddLineQueue("DBPTR TEXTEQU <EBP>");
		AddLineQueue("DSPTR TEXTEQU <ESP>");
		AddLineQueue("DBASE TEXTEQU <EBX>");
		AddLineQueue("DPARAM0 TEXTEQU <EAX>");
		AddLineQueue("DPARAM1 TEXTEQU <ECX>");
		AddLineQueue("DPARAM2 TEXTEQU <EDX>");
		AddLineQueue("DPARAM3 TEXTEQU <EDI>");
		AddLineQueue("DPARAM4 TEXTEQU <ESI>");
		AddLineQueue("DPARAM5 TEXTEQU <[ESP+24]>");
		AddLineQueue("DPARAM6 TEXTEQU <[ESP+28]>");
		AddLineQueue("DPARAM7 TEXTEQU <[ESP+32]>");
		AddLineQueue("DPARAM8 TEXTEQU <[ESP+36]>");
		AddLineQueue("DPARAM9 TEXTEQU <[ESP+40]>");
		AddLineQueue("DPARAM10 TEXTEQU <[ESP+44]>");
		AddLineQueue("DPARAM11 TEXTEQU <[ESP+48]>");
		AddLineQueue("DPARAM12 TEXTEQU <[ESP+52]>");
		AddLineQueue("DPARAM13 TEXTEQU <[ESP+56]>");
		AddLineQueue("DPARAM14 TEXTEQU <[ESP+60]>");
		AddLineQueue("DPARAM15 TEXTEQU <[ESP+64]>");
		AddLineQueue("DPARAM16 TEXTEQU <[ESP+68]>");
		AddLineQueue("DPARAM17 TEXTEQU <[ESP+72]>");
		AddLineQueue("DPARAM18 TEXTEQU <[ESP+76]>");
		AddLineQueue("DPARAM19 TEXTEQU <[ESP+80]>");
		AddLineQueue("DPARAM20 TEXTEQU <[ESP+84]>");
		AddLineQueue("DPARAM21 TEXTEQU <[ESP+88]>");
		AddLineQueue("DPARAM22 TEXTEQU <[ESP+92]>");
		AddLineQueue("DPARAM23 TEXTEQU <[ESP+96]>");
		AddLineQueue("DPARAM24 TEXTEQU <[ESP+100]>");
		AddLineQueue("DPARAM25 TEXTEQU <[ESP+104]>");
		AddLineQueue("DPARAM26 TEXTEQU <[ESP+108]>");
		AddLineQueue("DPARAM27 TEXTEQU <[ESP+112]>");
		AddLineQueue("DPARAM28 TEXTEQU <[ESP+116]>");
		AddLineQueue("DPARAM29 TEXTEQU <[ESP+120]>");
		AddLineQueue("DPARAM30 TEXTEQU <[ESP+124]>");
		AddLineQueue("DPARAM31 TEXTEQU <[ESP+128]>");
		AddLineQueue("DPARAM32 TEXTEQU <[ESP+132]>");
		AddLineQueue("DPARAM33 TEXTEQU <[ESP+136]>");
		AddLineQueue("DPARAM34 TEXTEQU <[ESP+140]>");
		AddLineQueue("DPARAM35 TEXTEQU <[ESP+144]>");
		AddLineQueue("DPARAM36 TEXTEQU <[ESP+148]>");
		AddLineQueue("DPARAM37 TEXTEQU <[ESP+152]>");
		AddLineQueue("DPARAM38 TEXTEQU <[ESP+156]>");
		AddLineQueue("DPARAM39 TEXTEQU <[ESP+160]>");
		AddLineQueue("DPARAM40 TEXTEQU <[ESP+164]>");
		AddLineQueue("DPARAM41 TEXTEQU <[ESP+168]>");
		AddLineQueue("DPARAM42 TEXTEQU <[ESP+172]>");
		AddLineQueue("DPARAM43 TEXTEQU <[ESP+176]>");
		AddLineQueue("DPARAM44 TEXTEQU <[ESP+180]>");
		AddLineQueue("DPARAM45 TEXTEQU <[ESP+184]>");
		AddLineQueue("DPARAM46 TEXTEQU <[ESP+188]>");
		AddLineQueue("DPARAM47 TEXTEQU <[ESP+192]>");
		AddLineQueue("DPARAM48 TEXTEQU <[ESP+196]>");
		AddLineQueue("DPARAM49 TEXTEQU <[ESP+200]>");
		AddLineQueue("DPARAM50 TEXTEQU <[ESP+204]>");
		AddLineQueue("DPARAM51 TEXTEQU <[ESP+208]>");
		AddLineQueue("DPARAM52 TEXTEQU <[ESP+212]>");
		AddLineQueue("DPARAM53 TEXTEQU <[ESP+216]>");
		AddLineQueue("DPARAM54 TEXTEQU <[ESP+220]>");
		AddLineQueue("DPARAM55 TEXTEQU <[ESP+224]>");
		AddLineQueue("DPARAM56 TEXTEQU <[ESP+228]>");
		AddLineQueue("DPARAM57 TEXTEQU <[ESP+232]>");
		AddLineQueue("DPARAM58 TEXTEQU <[ESP+236]>");
		AddLineQueue("DPARAM59 TEXTEQU <[ESP+240]>");
		AddLineQueue("DPARAM60 TEXTEQU <[ESP+244]>");
		AddLineQueue("DPARAM61 TEXTEQU <[ESP+248]>");
		AddLineQueue("DPARAM62 TEXTEQU <[ESP+252]>");
		AddLineQueue("DPARAM63 TEXTEQU <[ESP+256]>");
		/* 16bits*/
		AddLineQueue("WRET TEXTEQU <AX>");
		AddLineQueue("WRETURN TEXTEQU <AX>");
		AddLineQueue("WSIDX TEXTEQU <SI>");
		AddLineQueue("WDIDX TEXTEQU <DI>");
		AddLineQueue("WBPTR TEXTEQU <BP>");
		AddLineQueue("WSPTR TEXTEQU <SP>");
		AddLineQueue("WBASE TEXTEQU <BX>");
		AddLineQueue("WPARAM0 TEXTEQU <AX>");
		AddLineQueue("WPARAM1 TEXTEQU <CX>");
		AddLineQueue("WPARAM2 TEXTEQU <DX>");
		AddLineQueue("WPARAM3 TEXTEQU <DI>");
		AddLineQueue("WPARAM4 TEXTEQU <SI>");
		AddLineQueue("WPARAM5 TEXTEQU <[SP+12]>");
		AddLineQueue("WPARAM6 TEXTEQU <[SP+14]>");
		AddLineQueue("WPARAM7 TEXTEQU <[SP+16]>");
		AddLineQueue("WPARAM8 TEXTEQU <[SP+18]>");
		AddLineQueue("WPARAM9 TEXTEQU <[SP+20]>");
		AddLineQueue("WPARAM10 TEXTEQU <[SP+22]>");
		AddLineQueue("WPARAM11 TEXTEQU <[SP+24]>");
		AddLineQueue("WPARAM12 TEXTEQU <[SP+26]>");
		AddLineQueue("WPARAM13 TEXTEQU <[SP+28]>");
		AddLineQueue("WPARAM14 TEXTEQU <[SP+30]>");
		AddLineQueue("WPARAM15 TEXTEQU <[SP+32]>");
		AddLineQueue("WPARAM16 TEXTEQU <[SP+34]>");
		AddLineQueue("WPARAM17 TEXTEQU <[SP+36]>");
		AddLineQueue("WPARAM18 TEXTEQU <[SP+38]>");
		AddLineQueue("WPARAM19 TEXTEQU <[SP+40]>");
		AddLineQueue("WPARAM20 TEXTEQU <[SP+42]>");
		AddLineQueue("WPARAM21 TEXTEQU <[SP+44]>");
		AddLineQueue("WPARAM22 TEXTEQU <[SP+46]>");
		AddLineQueue("WPARAM23 TEXTEQU <[SP+48]>");
		AddLineQueue("WPARAM24 TEXTEQU <[SP+50]>");
		AddLineQueue("WPARAM25 TEXTEQU <[SP+52]>");
		AddLineQueue("WPARAM26 TEXTEQU <[SP+54]>");
		AddLineQueue("WPARAM27 TEXTEQU <[SP+56]>");
		AddLineQueue("WPARAM28 TEXTEQU <[SP+58]>");
		AddLineQueue("WPARAM29 TEXTEQU <[SP+60]>");
		AddLineQueue("WPARAM30 TEXTEQU <[SP+62]>");
		AddLineQueue("WPARAM31 TEXTEQU <[SP+64]>");
		AddLineQueue("WPARAM32 TEXTEQU <[SP+66]>");
		AddLineQueue("WPARAM33 TEXTEQU <[SP+68]>");
		AddLineQueue("WPARAM34 TEXTEQU <[SP+70]>");
		AddLineQueue("WPARAM35 TEXTEQU <[SP+72]>");
		AddLineQueue("WPARAM36 TEXTEQU <[SP+74]>");
		AddLineQueue("WPARAM37 TEXTEQU <[SP+76]>");
		AddLineQueue("WPARAM38 TEXTEQU <[SP+78]>");
		AddLineQueue("WPARAM39 TEXTEQU <[SP+80]>");
		AddLineQueue("WPARAM40 TEXTEQU <[SP+82]>");
		AddLineQueue("WPARAM41 TEXTEQU <[SP+84]>");
		AddLineQueue("WPARAM42 TEXTEQU <[SP+86]>");
		AddLineQueue("WPARAM43 TEXTEQU <[SP+88]>");
		AddLineQueue("WPARAM44 TEXTEQU <[SP+90]>");
		AddLineQueue("WPARAM45 TEXTEQU <[SP+92]>");
		AddLineQueue("WPARAM46 TEXTEQU <[SP+94]>");
		AddLineQueue("WPARAM47 TEXTEQU <[SP+96]>");
		AddLineQueue("WPARAM48 TEXTEQU <[SP+98]>");
		AddLineQueue("WPARAM49 TEXTEQU <[SP+100]>");
		AddLineQueue("WPARAM50 TEXTEQU <[SP+102]>");
		AddLineQueue("WPARAM51 TEXTEQU <[SP+104]>");
		AddLineQueue("WPARAM52 TEXTEQU <[SP+106]>");
		AddLineQueue("WPARAM53 TEXTEQU <[SP+108]>");
		AddLineQueue("WPARAM54 TEXTEQU <[SP+110]>");
		AddLineQueue("WPARAM55 TEXTEQU <[SP+112]>");
		AddLineQueue("WPARAM56 TEXTEQU <[SP+114]>");
		AddLineQueue("WPARAM57 TEXTEQU <[SP+116]>");
		AddLineQueue("WPARAM58 TEXTEQU <[SP+118]>");
		AddLineQueue("WPARAM59 TEXTEQU <[SP+120]>");
		AddLineQueue("WPARAM60 TEXTEQU <[SP+122]>");
		AddLineQueue("WPARAM61 TEXTEQU <[SP+124]>");
		AddLineQueue("WPARAM62 TEXTEQU <[SP+126]>");
		AddLineQueue("WPARAM63 TEXTEQU <[SP+128]>");
		/* 8bits*/
		AddLineQueue("BRET TEXTEQU <AL>");
		AddLineQueue("BRETURN TEXTEQU <AL>");
		AddLineQueue("BSIDX TEXTEQU <SIL>");
		AddLineQueue("BDIDX TEXTEQU <DIL>");
		AddLineQueue("BBPTR TEXTEQU <BPL>");
		AddLineQueue("BSPTR TEXTEQU <SPL>");
		AddLineQueue("BBASE TEXTEQU <BL>");
		AddLineQueue("BPARAM0 TEXTEQU <AL>");
		AddLineQueue("BPARAM1 TEXTEQU <CL>");
		AddLineQueue("BPARAM2 TEXTEQU <DL>");
		AddLineQueue("BPARAM3 TEXTEQU <DIL>");
		AddLineQueue("BPARAM4 TEXTEQU <SIL>");
		AddLineQueue("BPARAM5 TEXTEQU <[SPL+6]>");
		AddLineQueue("BPARAM6 TEXTEQU <[SPL+7]>");
		AddLineQueue("BPARAM7 TEXTEQU <[SPL+8]>");
		AddLineQueue("BPARAM8 TEXTEQU <[SPL+9]>");
		AddLineQueue("BPARAM9 TEXTEQU <[SPL+10]>");
		AddLineQueue("BPARAM10 TEXTEQU <[SPL+11]>");
		AddLineQueue("BPARAM11 TEXTEQU <[SPL+12]>");
		AddLineQueue("BPARAM12 TEXTEQU <[SPL+13]>");
		AddLineQueue("BPARAM13 TEXTEQU <[SPL+14]>");
		AddLineQueue("BPARAM14 TEXTEQU <[SPL+15]>");
		AddLineQueue("BPARAM15 TEXTEQU <[SPL+16]>");
		AddLineQueue("BPARAM16 TEXTEQU <[SPL+17]>");
		AddLineQueue("BPARAM17 TEXTEQU <[SPL+18]>");
		AddLineQueue("BPARAM18 TEXTEQU <[SPL+19]>");
		AddLineQueue("BPARAM19 TEXTEQU <[SPL+20]>");
		AddLineQueue("BPARAM20 TEXTEQU <[SPL+21]>");
		AddLineQueue("BPARAM21 TEXTEQU <[SPL+22]>");
		AddLineQueue("BPARAM22 TEXTEQU <[SPL+23]>");
		AddLineQueue("BPARAM23 TEXTEQU <[SPL+24]>");
		AddLineQueue("BPARAM24 TEXTEQU <[SPL+25]>");
		AddLineQueue("BPARAM25 TEXTEQU <[SPL+26]>");
		AddLineQueue("BPARAM26 TEXTEQU <[SPL+27]>");
		AddLineQueue("BPARAM27 TEXTEQU <[SPL+28]>");
		AddLineQueue("BPARAM28 TEXTEQU <[SPL+29]>");
		AddLineQueue("BPARAM29 TEXTEQU <[SPL+30]>");
		AddLineQueue("BPARAM30 TEXTEQU <[SPL+31]>");
		AddLineQueue("BPARAM31 TEXTEQU <[SPL+32]>");
		AddLineQueue("BPARAM32 TEXTEQU <[SPL+33]>");
		AddLineQueue("BPARAM33 TEXTEQU <[SPL+34]>");
		AddLineQueue("BPARAM34 TEXTEQU <[SPL+35]>");
		AddLineQueue("BPARAM35 TEXTEQU <[SPL+36]>");
		AddLineQueue("BPARAM36 TEXTEQU <[SPL+37]>");
		AddLineQueue("BPARAM37 TEXTEQU <[SPL+38]>");
		AddLineQueue("BPARAM38 TEXTEQU <[SPL+39]>");
		AddLineQueue("BPARAM39 TEXTEQU <[SPL+40]>");
		AddLineQueue("BPARAM40 TEXTEQU <[SPL+41]>");
		AddLineQueue("BPARAM41 TEXTEQU <[SPL+42]>");
		AddLineQueue("BPARAM42 TEXTEQU <[SPL+43]>");
		AddLineQueue("BPARAM43 TEXTEQU <[SPL+44]>");
		AddLineQueue("BPARAM44 TEXTEQU <[SPL+45]>");
		AddLineQueue("BPARAM45 TEXTEQU <[SPL+46]>");
		AddLineQueue("BPARAM46 TEXTEQU <[SPL+47]>");
		AddLineQueue("BPARAM47 TEXTEQU <[SPL+48]>");
		AddLineQueue("BPARAM48 TEXTEQU <[SPL+49]>");
		AddLineQueue("BPARAM49 TEXTEQU <[SPL+50]>");
		AddLineQueue("BPARAM50 TEXTEQU <[SPL+51]>");
		AddLineQueue("BPARAM51 TEXTEQU <[SPL+52]>");
		AddLineQueue("BPARAM52 TEXTEQU <[SPL+53]>");
		AddLineQueue("BPARAM53 TEXTEQU <[SPL+54]>");
		AddLineQueue("BPARAM54 TEXTEQU <[SPL+55]>");
		AddLineQueue("BPARAM55 TEXTEQU <[SPL+56]>");
		AddLineQueue("BPARAM56 TEXTEQU <[SPL+57]>");
		AddLineQueue("BPARAM57 TEXTEQU <[SPL+58]>");
		AddLineQueue("BPARAM58 TEXTEQU <[SPL+59]>");
		AddLineQueue("BPARAM59 TEXTEQU <[SPL+60]>");
		AddLineQueue("BPARAM60 TEXTEQU <[SPL+61]>");
		AddLineQueue("BPARAM61 TEXTEQU <[SPL+62]>");
		AddLineQueue("BPARAM62 TEXTEQU <[SPL+63]>");
		AddLineQueue("BPARAM63 TEXTEQU <[SPL+64]>");
	}
	else
	{
		/* 32bits*/
		AddLineQueue("RRET TEXTEQU <EAX>");
		AddLineQueue("RRETURN TEXTEQU <EAX>");
		AddLineQueue("RSIDX TEXTEQU <ESI>");
		AddLineQueue("RDIDX TEXTEQU <EDI>");
		AddLineQueue("RBPTR TEXTEQU <EBP>");
		AddLineQueue("RSPTR TEXTEQU <ESP>");
		AddLineQueue("RBASE TEXTEQU <EBX>");
		AddLineQueue("RPARAM0 TEXTEQU <ECX>");
		AddLineQueue("RPARAM1 TEXTEQU <EDX>");
		AddLineQueue("RPARAM2 TEXTEQU <[ESP+12]>");
		AddLineQueue("RPARAM3 TEXTEQU <[ESP+16]>");
		AddLineQueue("RPARAM4 TEXTEQU <[ESP+20]>");
		AddLineQueue("RPARAM5 TEXTEQU <[ESP+24]>");
		AddLineQueue("RPARAM6 TEXTEQU <[ESP+28]>");
		AddLineQueue("RPARAM7 TEXTEQU <[ESP+32]>");
		AddLineQueue("RPARAM8 TEXTEQU <[ESP+36]>");
		AddLineQueue("RPARAM9 TEXTEQU <[ESP+40]>");
		AddLineQueue("RPARAM10 TEXTEQU <[ESP+44]>");
		AddLineQueue("RPARAM11 TEXTEQU <[ESP+48]>");
		AddLineQueue("RPARAM12 TEXTEQU <[ESP+52]>");
		AddLineQueue("RPARAM13 TEXTEQU <[ESP+56]>");
		AddLineQueue("RPARAM14 TEXTEQU <[ESP+60]>");
		AddLineQueue("RPARAM15 TEXTEQU <[ESP+64]>");
		AddLineQueue("RPARAM16 TEXTEQU <[ESP+68]>");
		AddLineQueue("RPARAM17 TEXTEQU <[ESP+72]>");
		AddLineQueue("RPARAM18 TEXTEQU <[ESP+76]>");
		AddLineQueue("RPARAM19 TEXTEQU <[ESP+80]>");
		AddLineQueue("RPARAM20 TEXTEQU <[ESP+84]>");
		AddLineQueue("RPARAM21 TEXTEQU <[ESP+88]>");
		AddLineQueue("RPARAM22 TEXTEQU <[ESP+92]>");
		AddLineQueue("RPARAM23 TEXTEQU <[ESP+96]>");
		AddLineQueue("RPARAM24 TEXTEQU <[ESP+100]>");
		AddLineQueue("RPARAM25 TEXTEQU <[ESP+104]>");
		AddLineQueue("RPARAM26 TEXTEQU <[ESP+108]>");
		AddLineQueue("RPARAM27 TEXTEQU <[ESP+112]>");
		AddLineQueue("RPARAM28 TEXTEQU <[ESP+116]>");
		AddLineQueue("RPARAM29 TEXTEQU <[ESP+120]>");
		AddLineQueue("RPARAM30 TEXTEQU <[ESP+124]>");
		AddLineQueue("RPARAM31 TEXTEQU <[ESP+128]>");
		AddLineQueue("RPARAM32 TEXTEQU <[ESP+132]>");
		AddLineQueue("RPARAM33 TEXTEQU <[ESP+136]>");
		AddLineQueue("RPARAM34 TEXTEQU <[ESP+140]>");
		AddLineQueue("RPARAM35 TEXTEQU <[ESP+144]>");
		AddLineQueue("RPARAM36 TEXTEQU <[ESP+148]>");
		AddLineQueue("RPARAM37 TEXTEQU <[ESP+152]>");
		AddLineQueue("RPARAM38 TEXTEQU <[ESP+156]>");
		AddLineQueue("RPARAM39 TEXTEQU <[ESP+160]>");
		AddLineQueue("RPARAM40 TEXTEQU <[ESP+164]>");
		AddLineQueue("RPARAM41 TEXTEQU <[ESP+168]>");
		AddLineQueue("RPARAM42 TEXTEQU <[ESP+172]>");
		AddLineQueue("RPARAM43 TEXTEQU <[ESP+176]>");
		AddLineQueue("RPARAM44 TEXTEQU <[ESP+180]>");
		AddLineQueue("RPARAM45 TEXTEQU <[ESP+184]>");
		AddLineQueue("RPARAM46 TEXTEQU <[ESP+188]>");
		AddLineQueue("RPARAM47 TEXTEQU <[ESP+192]>");
		AddLineQueue("RPARAM48 TEXTEQU <[ESP+196]>");
		AddLineQueue("RPARAM49 TEXTEQU <[ESP+200]>");
		AddLineQueue("RPARAM50 TEXTEQU <[ESP+204]>");
		AddLineQueue("RPARAM51 TEXTEQU <[ESP+208]>");
		AddLineQueue("RPARAM52 TEXTEQU <[ESP+212]>");
		AddLineQueue("RPARAM53 TEXTEQU <[ESP+216]>");
		AddLineQueue("RPARAM54 TEXTEQU <[ESP+220]>");
		AddLineQueue("RPARAM55 TEXTEQU <[ESP+224]>");
		AddLineQueue("RPARAM56 TEXTEQU <[ESP+228]>");
		AddLineQueue("RPARAM57 TEXTEQU <[ESP+232]>");
		AddLineQueue("RPARAM58 TEXTEQU <[ESP+236]>");
		AddLineQueue("RPARAM59 TEXTEQU <[ESP+240]>");
		AddLineQueue("RPARAM60 TEXTEQU <[ESP+244]>");
		AddLineQueue("RPARAM61 TEXTEQU <[ESP+248]>");
		AddLineQueue("RPARAM62 TEXTEQU <[ESP+252]>");
		AddLineQueue("RPARAM63 TEXTEQU <[ESP+256]>");
		/* 32bits*/
		AddLineQueue("DRET TEXTEQU <EAX>");
		AddLineQueue("DRETURN TEXTEQU <EAX>");
		AddLineQueue("DSIDX TEXTEQU <ESI>");
		AddLineQueue("DDIDX TEXTEQU <EDI>");
		AddLineQueue("DBPTR TEXTEQU <EBP>");
		AddLineQueue("DSPTR TEXTEQU <ESP>");
		AddLineQueue("DBASE TEXTEQU <EBX>");
		AddLineQueue("DPARAM0 TEXTEQU <ECX>");
		AddLineQueue("DPARAM1 TEXTEQU <EDX>");
		AddLineQueue("DPARAM2 TEXTEQU <[ESP+12]>");
		AddLineQueue("DPARAM3 TEXTEQU <[ESP+16]>");
		AddLineQueue("DPARAM4 TEXTEQU <[ESP+20]>");
		AddLineQueue("DPARAM5 TEXTEQU <[ESP+24]>");
		AddLineQueue("DPARAM6 TEXTEQU <[ESP+28]>");
		AddLineQueue("DPARAM7 TEXTEQU <[ESP+32]>");
		AddLineQueue("DPARAM8 TEXTEQU <[ESP+36]>");
		AddLineQueue("DPARAM9 TEXTEQU <[ESP+40]>");
		AddLineQueue("DPARAM10 TEXTEQU <[ESP+44]>");
		AddLineQueue("DPARAM11 TEXTEQU <[ESP+48]>");
		AddLineQueue("DPARAM12 TEXTEQU <[ESP+52]>");
		AddLineQueue("DPARAM13 TEXTEQU <[ESP+56]>");
		AddLineQueue("DPARAM14 TEXTEQU <[ESP+60]>");
		AddLineQueue("DPARAM15 TEXTEQU <[ESP+64]>");
		AddLineQueue("DPARAM16 TEXTEQU <[ESP+68]>");
		AddLineQueue("DPARAM17 TEXTEQU <[ESP+72]>");
		AddLineQueue("DPARAM18 TEXTEQU <[ESP+76]>");
		AddLineQueue("DPARAM19 TEXTEQU <[ESP+80]>");
		AddLineQueue("DPARAM20 TEXTEQU <[ESP+84]>");
		AddLineQueue("DPARAM21 TEXTEQU <[ESP+88]>");
		AddLineQueue("DPARAM22 TEXTEQU <[ESP+92]>");
		AddLineQueue("DPARAM23 TEXTEQU <[ESP+96]>");
		AddLineQueue("DPARAM24 TEXTEQU <[ESP+100]>");
		AddLineQueue("DPARAM25 TEXTEQU <[ESP+104]>");
		AddLineQueue("DPARAM26 TEXTEQU <[ESP+108]>");
		AddLineQueue("DPARAM27 TEXTEQU <[ESP+112]>");
		AddLineQueue("DPARAM28 TEXTEQU <[ESP+116]>");
		AddLineQueue("DPARAM29 TEXTEQU <[ESP+120]>");
		AddLineQueue("DPARAM30 TEXTEQU <[ESP+124]>");
		AddLineQueue("DPARAM31 TEXTEQU <[ESP+128]>");
		AddLineQueue("DPARAM32 TEXTEQU <[ESP+132]>");
		AddLineQueue("DPARAM33 TEXTEQU <[ESP+136]>");
		AddLineQueue("DPARAM34 TEXTEQU <[ESP+140]>");
		AddLineQueue("DPARAM35 TEXTEQU <[ESP+144]>");
		AddLineQueue("DPARAM36 TEXTEQU <[ESP+148]>");
		AddLineQueue("DPARAM37 TEXTEQU <[ESP+152]>");
		AddLineQueue("DPARAM38 TEXTEQU <[ESP+156]>");
		AddLineQueue("DPARAM39 TEXTEQU <[ESP+160]>");
		AddLineQueue("DPARAM40 TEXTEQU <[ESP+164]>");
		AddLineQueue("DPARAM41 TEXTEQU <[ESP+168]>");
		AddLineQueue("DPARAM42 TEXTEQU <[ESP+172]>");
		AddLineQueue("DPARAM43 TEXTEQU <[ESP+176]>");
		AddLineQueue("DPARAM44 TEXTEQU <[ESP+180]>");
		AddLineQueue("DPARAM45 TEXTEQU <[ESP+184]>");
		AddLineQueue("DPARAM46 TEXTEQU <[ESP+188]>");
		AddLineQueue("DPARAM47 TEXTEQU <[ESP+192]>");
		AddLineQueue("DPARAM48 TEXTEQU <[ESP+196]>");
		AddLineQueue("DPARAM49 TEXTEQU <[ESP+200]>");
		AddLineQueue("DPARAM50 TEXTEQU <[ESP+204]>");
		AddLineQueue("DPARAM51 TEXTEQU <[ESP+208]>");
		AddLineQueue("DPARAM52 TEXTEQU <[ESP+212]>");
		AddLineQueue("DPARAM53 TEXTEQU <[ESP+216]>");
		AddLineQueue("DPARAM54 TEXTEQU <[ESP+220]>");
		AddLineQueue("DPARAM55 TEXTEQU <[ESP+224]>");
		AddLineQueue("DPARAM56 TEXTEQU <[ESP+228]>");
		AddLineQueue("DPARAM57 TEXTEQU <[ESP+232]>");
		AddLineQueue("DPARAM58 TEXTEQU <[ESP+236]>");
		AddLineQueue("DPARAM59 TEXTEQU <[ESP+240]>");
		AddLineQueue("DPARAM60 TEXTEQU <[ESP+244]>");
		AddLineQueue("DPARAM61 TEXTEQU <[ESP+248]>");
		AddLineQueue("DPARAM62 TEXTEQU <[ESP+252]>");
		AddLineQueue("DPARAM63 TEXTEQU <[ESP+256]>");
		/* 16bits*/
		AddLineQueue("WRET TEXTEQU <AX>");
		AddLineQueue("WRETURN TEXTEQU <AX>");
		AddLineQueue("WSIDX TEXTEQU <SI>");
		AddLineQueue("WDIDX TEXTEQU <DI>");
		AddLineQueue("WBPTR TEXTEQU <BP>");
		AddLineQueue("WSPTR TEXTEQU <SP>");
		AddLineQueue("WBASE TEXTEQU <BX>");
		AddLineQueue("WPARAM0 TEXTEQU <CX>");
		AddLineQueue("WPARAM1 TEXTEQU <DX>");
		AddLineQueue("WPARAM2 TEXTEQU <[SP+6]>");
		AddLineQueue("WPARAM3 TEXTEQU <[SP+8]>");
		AddLineQueue("WPARAM4 TEXTEQU <[SP+10]>");
		AddLineQueue("WPARAM5 TEXTEQU <[SP+12]>");
		AddLineQueue("WPARAM6 TEXTEQU <[SP+14]>");
		AddLineQueue("WPARAM7 TEXTEQU <[SP+16]>");
		AddLineQueue("WPARAM8 TEXTEQU <[SP+18]>");
		AddLineQueue("WPARAM9 TEXTEQU <[SP+20]>");
		AddLineQueue("WPARAM10 TEXTEQU <[SP+22]>");
		AddLineQueue("WPARAM11 TEXTEQU <[SP+24]>");
		AddLineQueue("WPARAM12 TEXTEQU <[SP+26]>");
		AddLineQueue("WPARAM13 TEXTEQU <[SP+28]>");
		AddLineQueue("WPARAM14 TEXTEQU <[SP+30]>");
		AddLineQueue("WPARAM15 TEXTEQU <[SP+32]>");
		AddLineQueue("WPARAM16 TEXTEQU <[SP+34]>");
		AddLineQueue("WPARAM17 TEXTEQU <[SP+36]>");
		AddLineQueue("WPARAM18 TEXTEQU <[SP+38]>");
		AddLineQueue("WPARAM19 TEXTEQU <[SP+40]>");
		AddLineQueue("WPARAM20 TEXTEQU <[SP+42]>");
		AddLineQueue("WPARAM21 TEXTEQU <[SP+44]>");
		AddLineQueue("WPARAM22 TEXTEQU <[SP+46]>");
		AddLineQueue("WPARAM23 TEXTEQU <[SP+48]>");
		AddLineQueue("WPARAM24 TEXTEQU <[SP+50]>");
		AddLineQueue("WPARAM25 TEXTEQU <[SP+52]>");
		AddLineQueue("WPARAM26 TEXTEQU <[SP+54]>");
		AddLineQueue("WPARAM27 TEXTEQU <[SP+56]>");
		AddLineQueue("WPARAM28 TEXTEQU <[SP+58]>");
		AddLineQueue("WPARAM29 TEXTEQU <[SP+60]>");
		AddLineQueue("WPARAM30 TEXTEQU <[SP+62]>");
		AddLineQueue("WPARAM31 TEXTEQU <[SP+64]>");
		AddLineQueue("WPARAM32 TEXTEQU <[SP+66]>");
		AddLineQueue("WPARAM33 TEXTEQU <[SP+68]>");
		AddLineQueue("WPARAM34 TEXTEQU <[SP+70]>");
		AddLineQueue("WPARAM35 TEXTEQU <[SP+72]>");
		AddLineQueue("WPARAM36 TEXTEQU <[SP+74]>");
		AddLineQueue("WPARAM37 TEXTEQU <[SP+76]>");
		AddLineQueue("WPARAM38 TEXTEQU <[SP+78]>");
		AddLineQueue("WPARAM39 TEXTEQU <[SP+80]>");
		AddLineQueue("WPARAM40 TEXTEQU <[SP+82]>");
		AddLineQueue("WPARAM41 TEXTEQU <[SP+84]>");
		AddLineQueue("WPARAM42 TEXTEQU <[SP+86]>");
		AddLineQueue("WPARAM43 TEXTEQU <[SP+88]>");
		AddLineQueue("WPARAM44 TEXTEQU <[SP+90]>");
		AddLineQueue("WPARAM45 TEXTEQU <[SP+92]>");
		AddLineQueue("WPARAM46 TEXTEQU <[SP+94]>");
		AddLineQueue("WPARAM47 TEXTEQU <[SP+96]>");
		AddLineQueue("WPARAM48 TEXTEQU <[SP+98]>");
		AddLineQueue("WPARAM49 TEXTEQU <[SP+100]>");
		AddLineQueue("WPARAM50 TEXTEQU <[SP+102]>");
		AddLineQueue("WPARAM51 TEXTEQU <[SP+104]>");
		AddLineQueue("WPARAM52 TEXTEQU <[SP+106]>");
		AddLineQueue("WPARAM53 TEXTEQU <[SP+108]>");
		AddLineQueue("WPARAM54 TEXTEQU <[SP+110]>");
		AddLineQueue("WPARAM55 TEXTEQU <[SP+112]>");
		AddLineQueue("WPARAM56 TEXTEQU <[SP+114]>");
		AddLineQueue("WPARAM57 TEXTEQU <[SP+116]>");
		AddLineQueue("WPARAM58 TEXTEQU <[SP+118]>");
		AddLineQueue("WPARAM59 TEXTEQU <[SP+120]>");
		AddLineQueue("WPARAM60 TEXTEQU <[SP+122]>");
		AddLineQueue("WPARAM61 TEXTEQU <[SP+124]>");
		AddLineQueue("WPARAM62 TEXTEQU <[SP+126]>");
		AddLineQueue("WPARAM63 TEXTEQU <[SP+128]>");
		/* 8bits*/
		AddLineQueue("BRET TEXTEQU <AL>");
		AddLineQueue("BRETURN TEXTEQU <AL>");
		AddLineQueue("BSIDX TEXTEQU <SIL>");
		AddLineQueue("BDIDX TEXTEQU <DIL>");
		AddLineQueue("BBPTR TEXTEQU <BPL>");
		AddLineQueue("BSPTR TEXTEQU <SPL>");
		AddLineQueue("BBASE TEXTEQU <BL>");
		AddLineQueue("BPARAM0 TEXTEQU <CL>");
		AddLineQueue("BPARAM1 TEXTEQU <DL>");
		AddLineQueue("BPARAM2 TEXTEQU <[SPL+3]>");
		AddLineQueue("BPARAM3 TEXTEQU <[SPL+4]>");
		AddLineQueue("BPARAM4 TEXTEQU <[SPL+5]>");
		AddLineQueue("BPARAM5 TEXTEQU <[SPL+6]>");
		AddLineQueue("BPARAM6 TEXTEQU <[SPL+7]>");
		AddLineQueue("BPARAM7 TEXTEQU <[SPL+8]>");
		AddLineQueue("BPARAM8 TEXTEQU <[SPL+9]>");
		AddLineQueue("BPARAM9 TEXTEQU <[SPL+10]>");
		AddLineQueue("BPARAM10 TEXTEQU <[SPL+11]>");
		AddLineQueue("BPARAM11 TEXTEQU <[SPL+12]>");
		AddLineQueue("BPARAM12 TEXTEQU <[SPL+13]>");
		AddLineQueue("BPARAM13 TEXTEQU <[SPL+14]>");
		AddLineQueue("BPARAM14 TEXTEQU <[SPL+15]>");
		AddLineQueue("BPARAM15 TEXTEQU <[SPL+16]>");
		AddLineQueue("BPARAM16 TEXTEQU <[SPL+17]>");
		AddLineQueue("BPARAM17 TEXTEQU <[SPL+18]>");
		AddLineQueue("BPARAM18 TEXTEQU <[SPL+19]>");
		AddLineQueue("BPARAM19 TEXTEQU <[SPL+20]>");
		AddLineQueue("BPARAM20 TEXTEQU <[SPL+21]>");
		AddLineQueue("BPARAM21 TEXTEQU <[SPL+22]>");
		AddLineQueue("BPARAM22 TEXTEQU <[SPL+23]>");
		AddLineQueue("BPARAM23 TEXTEQU <[SPL+24]>");
		AddLineQueue("BPARAM24 TEXTEQU <[SPL+25]>");
		AddLineQueue("BPARAM25 TEXTEQU <[SPL+26]>");
		AddLineQueue("BPARAM26 TEXTEQU <[SPL+27]>");
		AddLineQueue("BPARAM27 TEXTEQU <[SPL+28]>");
		AddLineQueue("BPARAM28 TEXTEQU <[SPL+29]>");
		AddLineQueue("BPARAM29 TEXTEQU <[SPL+30]>");
		AddLineQueue("BPARAM30 TEXTEQU <[SPL+31]>");
		AddLineQueue("BPARAM31 TEXTEQU <[SPL+32]>");
		AddLineQueue("BPARAM32 TEXTEQU <[SPL+33]>");
		AddLineQueue("BPARAM33 TEXTEQU <[SPL+34]>");
		AddLineQueue("BPARAM34 TEXTEQU <[SPL+35]>");
		AddLineQueue("BPARAM35 TEXTEQU <[SPL+36]>");
		AddLineQueue("BPARAM36 TEXTEQU <[SPL+37]>");
		AddLineQueue("BPARAM37 TEXTEQU <[SPL+38]>");
		AddLineQueue("BPARAM38 TEXTEQU <[SPL+39]>");
		AddLineQueue("BPARAM39 TEXTEQU <[SPL+40]>");
		AddLineQueue("BPARAM40 TEXTEQU <[SPL+41]>");
		AddLineQueue("BPARAM41 TEXTEQU <[SPL+42]>");
		AddLineQueue("BPARAM42 TEXTEQU <[SPL+43]>");
		AddLineQueue("BPARAM43 TEXTEQU <[SPL+44]>");
		AddLineQueue("BPARAM44 TEXTEQU <[SPL+45]>");
		AddLineQueue("BPARAM45 TEXTEQU <[SPL+46]>");
		AddLineQueue("BPARAM46 TEXTEQU <[SPL+47]>");
		AddLineQueue("BPARAM47 TEXTEQU <[SPL+48]>");
		AddLineQueue("BPARAM48 TEXTEQU <[SPL+49]>");
		AddLineQueue("BPARAM49 TEXTEQU <[SPL+50]>");
		AddLineQueue("BPARAM50 TEXTEQU <[SPL+51]>");
		AddLineQueue("BPARAM51 TEXTEQU <[SPL+52]>");
		AddLineQueue("BPARAM52 TEXTEQU <[SPL+53]>");
		AddLineQueue("BPARAM53 TEXTEQU <[SPL+54]>");
		AddLineQueue("BPARAM54 TEXTEQU <[SPL+55]>");
		AddLineQueue("BPARAM55 TEXTEQU <[SPL+56]>");
		AddLineQueue("BPARAM56 TEXTEQU <[SPL+57]>");
		AddLineQueue("BPARAM57 TEXTEQU <[SPL+58]>");
		AddLineQueue("BPARAM58 TEXTEQU <[SPL+59]>");
		AddLineQueue("BPARAM59 TEXTEQU <[SPL+60]>");
		AddLineQueue("BPARAM60 TEXTEQU <[SPL+61]>");
		AddLineQueue("BPARAM61 TEXTEQU <[SPL+62]>");
		AddLineQueue("BPARAM62 TEXTEQU <[SPL+63]>");
		AddLineQueue("BPARAM63 TEXTEQU <[SPL+64]>");
	}
	AddLineQueue("ENDIF"); /*__UNIX32__*/
	AddLineQueue("ENDIF"); /*__MACH__*/

	AddLineQueue("INT8 TEXTEQU <BYTE>");
	AddLineQueue("UINT8 TEXTEQU <BYTE>");
	AddLineQueue("SINT8 TEXTEQU <SBYTE>");
	AddLineQueue("INT8_T TEXTEQU <BYTE>");
	AddLineQueue("UINT8_T TEXTEQU <BYTE>");
	AddLineQueue("SINT8_T TEXTEQU <SBYTE>");
	AddLineQueue("INT16 TEXTEQU <WORD>");
	AddLineQueue("UINT16 TEXTEQU <WORD>");
	AddLineQueue("SINT16 TEXTEQU <SWORD>");
	AddLineQueue("INT16_T TEXTEQU <WORD>");
	AddLineQueue("UINT16_T TEXTEQU <WORD>");
	AddLineQueue("SINT16_T TEXTEQU <SWORD>");
	/*AddLineQueue("INT TEXTEQU <DWORD>"); cannot be used instruction type*/
	AddLineQueue("BOOL TEXTEQU <DWORD>");
	AddLineQueue("INT32 TEXTEQU <DWORD>");
	AddLineQueue("UINT32 TEXTEQU <DWORD>");
	AddLineQueue("SINT32 TEXTEQU <SDWORD>");
	AddLineQueue("INT32_T TEXTEQU <DWORD>");
	AddLineQueue("UINT32_T TEXTEQU <DWORD>");
	AddLineQueue("SINT32_T TEXTEQU <SDWORD>");
	AddLineQueue("INT64 TEXTEQU <QWORD>");
	AddLineQueue("UINT64 TEXTEQU <QWORD>");
	AddLineQueue("SINT64 TEXTEQU <SQWORD>");
	AddLineQueue("INT64_T TEXTEQU <QWORD>");
	AddLineQueue("UINT64_T TEXTEQU <QWORD>");
	AddLineQueue("SINT64_T TEXTEQU <SQWORD>");
	AddLineQueue("FLOAT TEXTEQU <REAL4>");
	AddLineQueue("DOUBLE TEXTEQU <REAL8>");

	AddLineQueue("BYTE_SIZE EQU 1");
	AddLineQueue("UBYTE_SIZE EQU 1");
	AddLineQueue("SBYTE_SIZE EQU 1");
	AddLineQueue("CHAR_SIZE EQU 1");
	AddLineQueue("UCHAR_SIZE EQU 1");
	AddLineQueue("SCHAR_SIZE EQU 1");
	AddLineQueue("INT8_SIZE EQU 1");
	AddLineQueue("I8_SIZE EQU 1");
	AddLineQueue("UINT8_SIZE EQU 1");
	AddLineQueue("UI8_SIZE EQU 1");
	AddLineQueue("SINT8_SIZE EQU 1");
	AddLineQueue("SI8_SIZE EQU 1");
	AddLineQueue("WORD_SIZE EQU 2");
	AddLineQueue("UWORD_SIZE EQU 2");
	AddLineQueue("SWORD_SIZE EQU 2");
	AddLineQueue("SHORT_SIZE EQU 2");
	AddLineQueue("USHORT_SIZE EQU 2");
	AddLineQueue("SSHORT_SIZE EQU 2");
	AddLineQueue("INT16_SIZE EQU 2");
	AddLineQueue("I16_SIZE EQU 2");
	AddLineQueue("UINT16_SIZE EQU 2");
	AddLineQueue("UI16_SIZE EQU 2");
	AddLineQueue("SINT16_SIZE EQU 2");
	AddLineQueue("SI16_SIZE EQU 2");
	AddLineQueue("DWORD_SIZE EQU 4");
	AddLineQueue("UDWORD_SIZE EQU 4");
	AddLineQueue("SDWORD_SIZE EQU 4");
	AddLineQueue("LONG_SIZE EQU 4");
	AddLineQueue("ULONG_SIZE EQU 4");
	AddLineQueue("SLONG_SIZE EQU 4");
	AddLineQueue("BOOL_SIZE EQU 4");
	AddLineQueue("INT_SIZE EQU 4");
	AddLineQueue("UINT_SIZE EQU 4");
	AddLineQueue("SINT_SIZE EQU 4");
	AddLineQueue("INT32_SIZE EQU 4");
	AddLineQueue("I32_SIZE EQU 4");
	AddLineQueue("UINT32_SIZE EQU 4");
	AddLineQueue("UI32_SIZE EQU 4");
	AddLineQueue("SINT32_SIZE EQU 4");
	AddLineQueue("SI32_SIZE EQU 4");
	AddLineQueue("QWORD_SIZE EQU 8");
	AddLineQueue("UQWORD_SIZE EQU 8");
	AddLineQueue("SQWORD_SIZE EQU 8");
	AddLineQueue("LONGLONG_SIZE EQU 8");
	AddLineQueue("ULONGLONG_SIZE EQU 8");
	AddLineQueue("SLONGLONG_SIZE EQU 8");
	AddLineQueue("INT64_SIZE EQU 8");
	AddLineQueue("I64_SIZE EQU 8");
	AddLineQueue("UINT64_SIZE EQU 8");
	AddLineQueue("UI64_SIZE EQU 8");
	AddLineQueue("SINT64_SIZE EQU 8");
	AddLineQueue("SI64_SIZE EQU 8");
	AddLineQueue("REAL4_SIZE EQU 4");
	AddLineQueue("FLOAT_SIZE EQU 4");
	AddLineQueue("FLT_SIZE EQU 4");
	AddLineQueue("REAL8_SIZE EQU 8");
	AddLineQueue("DOUBLE_SIZE EQU 8");
	AddLineQueue("DBL_SIZE EQU 8");

	AddLineQueue("BYTE_MAX EQU 0xff");
	AddLineQueue("UBYTE_MAX EQU 0xff");
	AddLineQueue("CHAR_MAX EQU BYTE_MAX");
	AddLineQueue("UCHAR_MAX EQU UBYTE_MAX");
	AddLineQueue("INT8_MAX EQU BYTE_MAX");
	AddLineQueue("I8_MAX EQU BYTE_MAX");
	AddLineQueue("UINT8_MAX EQU UBYTE_MAX");
	AddLineQueue("UI8_MAX EQU UBYTE_MAX");
	AddLineQueue("UBYTE_MIN EQU 0x0");
	AddLineQueue("UCHAR_MIN EQU UBYTE_MIN");
	AddLineQueue("UINT8_MIN EQU UBYTE_MIN");
	AddLineQueue("UI8_MIN EQU UBYTE_MIN");
	AddLineQueue("SBYTE_MAX EQU 0x7f");
	AddLineQueue("SCHAR_MAX EQU SBYTE_MAX");
	AddLineQueue("SINT8_MAX EQU SBYTE_MAX");
	AddLineQueue("SI8_MAX EQU SBYTE_MAX");
	AddLineQueue("BYTE_MIN EQU (-0x7f - 0x1)");
	AddLineQueue("SBYTE_MIN EQU (-0x7f - 0x1)");
	AddLineQueue("CHAR_MIN EQU BYTE_MIN");
	AddLineQueue("SCHAR_MIN EQU SBYTE_MIN");
	AddLineQueue("INT8_MIN EQU BYTE_MIN");
	AddLineQueue("I8_MIN EQU BYTE_MIN");
	AddLineQueue("SINT8_MIN EQU SBYTE_MIN");
	AddLineQueue("SI8_MIN EQU SBYTE_MIN");

	AddLineQueue("MAX_BYTE EQU 0xff");
	AddLineQueue("MAX_UBYTE EQU 0xff");
	AddLineQueue("MAX_CHAR EQU MAX_BYTE");
	AddLineQueue("MAX_UCHAR EQU MAX_UBYTE");
	AddLineQueue("MAX_INT8 EQU MAX_BYTE");
	AddLineQueue("MAX_I8 EQU MAX_BYTE");
	AddLineQueue("MAX_UINT8 EQU MAX_UBYTE");
	AddLineQueue("MAX_UI8 EQU MAX_UBYTE");
	AddLineQueue("MIN_UBYTE EQU 0x0");
	AddLineQueue("MIN_UCHAR EQU MIN_UBYTE");
	AddLineQueue("MIN_UINT8 EQU MIN_UBYTE");
	AddLineQueue("MIN_UI8 EQU MIN_UBYTE");
	AddLineQueue("MAX_SBYTE EQU 0x7f");
	AddLineQueue("MAX_SCHAR EQU MAX_SBYTE");
	AddLineQueue("MAX_SINT8 EQU MAX_SBYTE");
	AddLineQueue("MAX_SI8 EQU MAX_SBYTE");
	AddLineQueue("MIN_BYTE EQU (-0x7f - 0x1)");
	AddLineQueue("MIN_SBYTE EQU (-0x7f - 0x1)");
	AddLineQueue("MIN_CHAR EQU MIN_BYTE");
	AddLineQueue("MIN_SCHAR EQU MIN_SBYTE");
	AddLineQueue("MIN_INT8 EQU MIN_BYTE");
	AddLineQueue("MIN_I8 EQU MIN_BYTE");
	AddLineQueue("MIN_SINT8 EQU MIN_SBYTE");
	AddLineQueue("MIN_SI8 EQU MIN_SBYTE");

	AddLineQueue("WORD_MAX EQU 0xffff");
	AddLineQueue("UWORD_MAX EQU 0xffff");
	AddLineQueue("SHORT_MAX EQU WORD_MAX");
	AddLineQueue("USHORT_MAX EQU UWORD_MAX");
	AddLineQueue("INT16_MAX EQU WORD_MAX");
	AddLineQueue("I16_MAX EQU WORD_MAX");
	AddLineQueue("UINT16_MAX EQU UWORD_MAX");
	AddLineQueue("UI16_MAX EQU UWORD_MAX");
	AddLineQueue("UWORD_MIN EQU 0x0");
	AddLineQueue("USHORT_MIN EQU UWORD_MIN");
	AddLineQueue("UINT16_MIN EQU UWORD_MIN");
	AddLineQueue("UI16_MIN EQU UWORD_MIN");
	AddLineQueue("SWORD_MAX EQU 0x7fff");
	AddLineQueue("SSHORT_MAX EQU SWORD_MAX");
	AddLineQueue("SINT16_MAX EQU SWORD_MAX");
	AddLineQueue("SI16_MAX EQU SWORD_MAX");
	AddLineQueue("WORD_MIN EQU (-0x7fff - 0x1)");
	AddLineQueue("SWORD_MIN EQU (-0x7fff - 0x1)");
	AddLineQueue("SHORT_MIN EQU WORD_MIN");
	AddLineQueue("SSHORT_MIN EQU SWORD_MIN");
	AddLineQueue("INT16_MIN EQU WORD_MIN");
	AddLineQueue("I16_MIN EQU WORD_MIN");
	AddLineQueue("SINT16_MIN EQU SWORD_MIN");
	AddLineQueue("SI16_MIN EQU SWORD_MIN");

	AddLineQueue("MAX_WORD EQU 0xffff");
	AddLineQueue("MAX_UWORD EQU 0xffff");
	AddLineQueue("MAX_SHORT EQU MAX_WORD");
	AddLineQueue("MAX_USHORT EQU MAX_UWORD");
	AddLineQueue("MAX_INT16 EQU MAX_WORD");
	AddLineQueue("MAX_I16 EQU MAX_WORD");
	AddLineQueue("MAX_UINT16 EQU MAX_UWORD");
	AddLineQueue("MAX_UI16 EQU MAX_UWORD");
	AddLineQueue("MIN_UWORD EQU 0x0");
	AddLineQueue("MIN_USHORT EQU MIN_UWORD");
	AddLineQueue("MIN_UINT16 EQU MIN_UWORD");
	AddLineQueue("MIN_UI16 EQU MIN_UWORD");
	AddLineQueue("MAX_SWORD EQU 0x7fff");
	AddLineQueue("MAX_SSHORT EQU MAX_SWORD");
	AddLineQueue("MAX_SINT16 EQU MAX_SWORD");
	AddLineQueue("MAX_SI16 EQU MAX_SWORD");
	AddLineQueue("MIN_WORD EQU (-0x7fff - 0x1)");
	AddLineQueue("MIN_SWORD EQU (-0x7fff - 0x1)");
	AddLineQueue("MIN_SHORT EQU MIN_WORD");
	AddLineQueue("MIN_SSHORT EQU MIN_SWORD");
	AddLineQueue("MIN_INT16 EQU MIN_WORD");
	AddLineQueue("MIN_I16 EQU MIN_WORD");
	AddLineQueue("MIN_SINT16 EQU MIN_SWORD");
	AddLineQueue("MIN_SI16 EQU MIN_SWORD");

	AddLineQueue("BOOL_MAX EQU 0x1");
	AddLineQueue("BOOL_MIN EQU 0x0");

	AddLineQueue("MAX_BOOL EQU 0x1");
	AddLineQueue("MIN_BOOL EQU 0x0");

	AddLineQueue("DWORD_MAX EQU 0xffffffff");
	AddLineQueue("UDWORD_MAX EQU 0xffffffff");
	AddLineQueue("LONG_MAX EQU DWORD_MAX");
	AddLineQueue("ULONG_MAX EQU UDWORD_MAX");
	AddLineQueue("INT_MAX EQU DWORD_MAX");
	AddLineQueue("UINT_MAX EQU UDWORD_MAX");
	AddLineQueue("INT32_MAX EQU DWORD_MAX");
	AddLineQueue("I32_MAX EQU DWORD_MAX");
	AddLineQueue("UINT32_MAX EQU UDWORD_MAX");
	AddLineQueue("UI32_MAX EQU UDWORD_MAX");
	AddLineQueue("UDWORD_MIN EQU 0x0");
	AddLineQueue("ULONG_MIN EQU UDWORD_MIN");
	AddLineQueue("UINT_MIN EQU UDWORD_MIN");
	AddLineQueue("UINT32_MIN EQU UDWORD_MIN");
	AddLineQueue("UI32_MIN EQU UDWORD_MIN");
	AddLineQueue("SDWORD_MAX EQU 0x7fffffff");
	AddLineQueue("SLONG_MAX EQU SDWORD_MAX");
	AddLineQueue("SINT_MAX EQU SDWORD_MAX");
	AddLineQueue("SINT32_MAX EQU SDWORD_MAX");
	AddLineQueue("SI32_MAX EQU SDWORD_MAX");
	AddLineQueue("DWORD_MIN EQU (-0x7fffffff - 0x1)");
	AddLineQueue("SDWORD_MIN EQU (-0x7fffffff - 0x1)");
	AddLineQueue("LONG_MIN EQU DWORD_MIN");
	AddLineQueue("SLONG_MIN EQU SDWORD_MIN");
	AddLineQueue("INT_MIN EQU DWORD_MIN");
	AddLineQueue("SINT_MIN EQU SDWORD_MIN");
	AddLineQueue("INT32_MIN EQU DWORD_MIN");
	AddLineQueue("I32_MIN EQU DWORD_MIN");
	AddLineQueue("SINT32_MIN EQU SDWORD_MIN");
	AddLineQueue("SI32_MIN EQU SDWORD_MIN");

	AddLineQueue("MAX_DWORD EQU 0xffffffff");
	AddLineQueue("MAX_UDWORD EQU 0xffffffff");
	AddLineQueue("MAX_LONG EQU MAX_DWORD");
	AddLineQueue("MAX_ULONG EQU MAX_UDWORD");
	AddLineQueue("MAX_INT EQU MAX_DWORD");
	AddLineQueue("MAX_UINT EQU MAX_UDWORD");
	AddLineQueue("MAX_INT32 EQU MAX_DWORD");
	AddLineQueue("MAX_I32 EQU MAX_DWORD");
	AddLineQueue("MAX_UINT32 EQU MAX_UDWORD");
	AddLineQueue("MAX_UI32 EQU MAX_UDWORD");
	AddLineQueue("MIN_UDWORD EQU 0x0");
	AddLineQueue("MIN_ULONG EQU MIN_UDWORD");
	AddLineQueue("MIN_UINT EQU MIN_UDWORD");
	AddLineQueue("MIN_UINT32 EQU MIN_UDWORD");
	AddLineQueue("MIN_UI32 EQU MIN_UDWORD");
	AddLineQueue("MAX_SDWORD EQU 0x7fffffff");
	AddLineQueue("MAX_SLONG EQU MAX_SDWORD");
	AddLineQueue("MAX_SINT EQU MAX_SDWORD");
	AddLineQueue("MAX_SINT32 EQU MAX_SDWORD");
	AddLineQueue("MAX_SI32 EQU MAX_SDWORD");
	AddLineQueue("MIN_DWORD EQU (-0x7fffffff - 0x1)");
	AddLineQueue("MIN_SDWORD EQU (-0x7fffffff - 0x1)");
	AddLineQueue("MIN_LONG EQU MIN_DWORD");
	AddLineQueue("MIN_SLONG EQU MIN_SDWORD");
	AddLineQueue("MIN_INT EQU MIN_DWORD");
	AddLineQueue("MIN_SINT EQU MIN_SDWORD");
	AddLineQueue("MIN_INT32 EQU MIN_DWORD");
	AddLineQueue("MIN_I32 EQU MIN_DWORD");
	AddLineQueue("MIN_SINT32 EQU MIN_SDWORD");
	AddLineQueue("MIN_SI32 EQU MIN_SDWORD");

	AddLineQueue("QWORD_MAX EQU 0xffffffffffffffff");
	AddLineQueue("UQWORD_MAX EQU 0xffffffffffffffff");
	AddLineQueue("LONGLONG_MAX EQU QWORD_MAX");
	AddLineQueue("ULONGLONG_MAX EQU UQWORD_MAX");
	AddLineQueue("INT64_MAX EQU QWORD_MAX");
	AddLineQueue("I64_MAX EQU QWORD_MAX");
	AddLineQueue("UINT64_MAX EQU UQWORD_MAX");
	AddLineQueue("UI64_MAX EQU UQWORD_MAX");
	AddLineQueue("UQWORD_MIN EQU 0x0");
	AddLineQueue("ULONGLONG_MIN EQU UQWORD_MIN");
	AddLineQueue("UINT64_MIN EQU UQWORD_MIN");
	AddLineQueue("UI64_MIN EQU UQWORD_MIN");
	AddLineQueue("SQWORD_MAX EQU 0x7fffffffffffffff");
	AddLineQueue("SLONGLONG_MAX EQU SQWORD_MAX");
	AddLineQueue("SINT64_MAX EQU SQWORD_MAX");
	AddLineQueue("SI64_MAX EQU SQWORD_MAX");
	AddLineQueue("QWORD_MIN EQU (-0x7fffffffffffffff - 0x1)");
	AddLineQueue("SQWORD_MIN EQU (-0x7fffffffffffffff - 0x1)");
	AddLineQueue("LONGLONG_MIN EQU QWORD_MIN");
	AddLineQueue("SLONGLONG_MIN EQU SQWORD_MIN");
	AddLineQueue("INT64_MIN EQU QWORD_MIN");
	AddLineQueue("I64_MIN EQU QWORD_MIN");
	AddLineQueue("SINT64_MIN EQU SQWORD_MIN");
	AddLineQueue("SI64_MIN EQU SQWORD_MIN");

	AddLineQueue("MAX_QWORD EQU 0xffffffffffffffff");
	AddLineQueue("MAX_UQWORD EQU 0xffffffffffffffff");
	AddLineQueue("MAX_LONGLONG EQU MAX_QWORD");
	AddLineQueue("MAX_ULONGLONG EQU MAX_UQWORD");
	AddLineQueue("MAX_INT64 EQU MAX_QWORD");
	AddLineQueue("MAX_I64 EQU MAX_QWORD");
	AddLineQueue("MAX_UINT64 EQU MAX_UQWORD");
	AddLineQueue("MAX_UI64 EQU MAX_UQWORD");
	AddLineQueue("MIN_UQWORD EQU 0x0");
	AddLineQueue("MIN_ULONGLONG EQU MIN_UQWORD");
	AddLineQueue("MIN_UINT64 EQU MIN_UQWORD");
	AddLineQueue("MIN_UI64 EQU MIN_UQWORD");
	AddLineQueue("MAX_SQWORD EQU 0x7fffffffffffffff");
	AddLineQueue("MAX_SLONGLONG EQU MAX_SQWORD");
	AddLineQueue("MAX_SINT64 EQU MAX_SQWORD");
	AddLineQueue("MAX_SI64 EQU MAX_SQWORD");
	AddLineQueue("MIN_QWORD EQU (-0x7fffffffffffffff - 0x1)");
	AddLineQueue("MIN_SQWORD EQU (-0x7fffffffffffffff - 0x1)");
	AddLineQueue("MIN_LONGLONG EQU MIN_QWORD");
	AddLineQueue("MIN_SLONGLONG EQU MIN_SQWORD");
	AddLineQueue("MIN_INT64 EQU MIN_QWORD");
	AddLineQueue("MIN_I64 EQU MIN_QWORD");
	AddLineQueue("MIN_SINT64 EQU MIN_SQWORD");
	AddLineQueue("MIN_SI64 EQU MIN_SQWORD");

	AddLineQueue("BYTE_ERROR EQU 0xff");
	AddLineQueue("CHAR_ERROR EQU 0xff");
	AddLineQueue("INT8_ERROR EQU 0xff");
	AddLineQueue("I8_ERROR EQU 0xff");
	AddLineQueue("UBYTE_ERROR EQU 0xff");
	AddLineQueue("UCHAR_ERROR EQU 0xff");
	AddLineQueue("UINT8_ERROR EQU 0xff");
	AddLineQueue("UI8_ERROR EQU 0xff");
	AddLineQueue("SBYTE_ERROR EQU (-0x1)");
	AddLineQueue("SCHAR_ERROR EQU (-0x1)");
	AddLineQueue("SINT8_ERROR EQU (-0x1)");
	AddLineQueue("SI8_ERROR EQU (-0x1)");

	AddLineQueue("WORD_ERROR EQU 0xffff");
	AddLineQueue("SHORT_ERROR EQU 0xffff");
	AddLineQueue("INT16_ERROR EQU 0xffff");
	AddLineQueue("I16_ERROR EQU 0xffff");
	AddLineQueue("UWORD_ERROR EQU 0xffff");
	AddLineQueue("USHORT_ERROR EQU 0xffff");
	AddLineQueue("UINT18_ERROR EQU 0xffff");
	AddLineQueue("UI18_ERROR EQU 0xffff");
	AddLineQueue("SWORD_ERROR EQU (-0x1)");
	AddLineQueue("SSHORT_ERROR EQU (-0x1)");
	AddLineQueue("SINT16_ERROR EQU (-0x1)");
	AddLineQueue("SI16_ERROR EQU (-0x1)");

	AddLineQueue("DWORD_ERROR EQU 0xffffffff");
	AddLineQueue("LONG_ERROR EQU 0xffffffff");
	AddLineQueue("INT_ERROR EQU 0xffffffff");
	AddLineQueue("INT32_ERROR EQU 0xffffffff");
	AddLineQueue("I32_ERROR EQU 0xffffffff");
	AddLineQueue("UDWORD_ERROR EQU 0xffffffff");
	AddLineQueue("ULONG_ERROR EQU 0xffffffff");
	AddLineQueue("UINT_ERROR EQU 0xffffffff");
	AddLineQueue("UINT32_ERROR EQU 0xffffffff");
	AddLineQueue("UI32_ERROR EQU 0xffffffff");
	AddLineQueue("SDWORD_ERROR EQU (-0x1)");
	AddLineQueue("SLONG_ERROR EQU (-0x1)");
	AddLineQueue("SINT_ERROR EQU (-0x1)");
	AddLineQueue("SINT32_ERROR EQU (-0x1)");
	AddLineQueue("SI32_ERROR EQU (-0x1)");

	AddLineQueue("QWORD_ERROR EQU 0xffffffffffffffff");
	AddLineQueue("LONGLONG_ERROR EQU 0xffffffffffffffff");
	AddLineQueue("INT64_ERROR EQU 0xffffffffffffffff");
	AddLineQueue("I64_ERROR EQU 0xffffffffffffffff");
	AddLineQueue("UQWORD_ERROR EQU 0xffffffffffffffff");
	AddLineQueue("ULONGLONG_ERROR EQU 0xffffffffffffffff");
	AddLineQueue("UINT64_ERROR EQU 0xffffffffffffffff");
	AddLineQueue("UI64_ERROR EQU 0xffffffffffffffff");
	AddLineQueue("SQWORD_ERROR EQU (-0x1)");
	AddLineQueue("SLONGLONG_ERROR EQU (-0x1)");
	AddLineQueue("SINT64_ERROR EQU (-0x1)");
	AddLineQueue("SI64_ERROR EQU (-0x1)");

	AddLineQueue("FLOAT_ERROR EQU (-0x1)");
	AddLineQueue("FLT_ERROR EQU (-0x1)");
	AddLineQueue("DOUBLE_ERROR EQU (-0x1)");
	AddLineQueue("DBL_ERROR EQU (-0x1)");

	AddLineQueue("IFDEF __X64__");
	AddLineQueue("SIZE_T TEXTEQU <QWORD>");
	AddLineQueue("PTRDIFF_T TEXTEQU <QWORD>");
	AddLineQueue("INTPTR_T TEXTEQU <QWORD>");
	AddLineQueue("UINTPTR_T TEXTEQU <QWORD>");
	AddLineQueue("ISIZE_T TEXTEQU <DQ>");
	AddLineQueue("PSIZE_T TEXTEQU <PTR QWORD>");
	AddLineQueue("SIZE_TP TEXTEQU <QWORD PTR>");
	AddLineQueue("SIZE_T_SIZE EQU 8");
	AddLineQueue("PTRDIFF_T_SIZE EQU 8");
	AddLineQueue("INTPTR_T_SIZE EQU 8");
	AddLineQueue("UINTPTR_T_SIZE EQU 8");
	AddLineQueue("PTR_SIZE EQU 8");
	AddLineQueue("REG_SIZE EQU 8");
	AddLineQueue("SINTSIZE_T_MAX EQU SQWORD_MAX");
	AddLineQueue("SINTSIZE_T_MIN EQU SQWORD_MIN");
	AddLineQueue("UINTSIZE_T_MAX EQU UQWORD_MAX");
	AddLineQueue("UINTSIZE_T_MIN EQU UQWORD_MIN");
	AddLineQueue("INTSIZE_T_MAX EQU QWORD_MAX");
	AddLineQueue("INTSIZE_T_MIN EQU QWORD_MIN");
	AddLineQueue("SIZE_T_MAX EQU QWORD_MAX");
	AddLineQueue("SIZE_T_MIN EQU QWORD_MIN");
	AddLineQueue("PTRDIFF_T_MAX EQU QWORD_MAX");
	AddLineQueue("PTRDIFF_T_MIN EQU QWORD_MIN");
	AddLineQueue("INTPTR_T_MAX EQU QWORD_MAX");
	AddLineQueue("INTPTR_T_MIN EQU QWORD_MIN");
	AddLineQueue("UINTPTR_T_MAX EQU QWORD_MAX");
	AddLineQueue("UINTPTR_T_MIN EQU QWORD_MIN");
	AddLineQueue("SINTPTR_MAX EQU SQWORD_MAX");
	AddLineQueue("SINTPTR_MIN EQU SQWORD_MIN");
	AddLineQueue("UINTPTR_MAX EQU UQWORD_MAX");
	AddLineQueue("UINTPTR_MIN EQU UQWORD_MIN");
	AddLineQueue("INTPTR_MAX EQU QWORD_MAX");
	AddLineQueue("INTPTR_MIN EQU QWORD_MIN");
	AddLineQueue("MAX_SINTSIZE_T EQU MAX_SQWORD");
	AddLineQueue("MIN_SINTSIZE_T EQU MIN_SQWORD");
	AddLineQueue("MAX_UINTSIZE_T EQU MAX_UQWORD");
	AddLineQueue("MIN_UINTSIZE_T EQU MIN_UQWORD");
	AddLineQueue("MAX_INTSIZE_T EQU MAX_QWORD");
	AddLineQueue("MIN_INTSIZE_T EQU MIN_QWORD");
	AddLineQueue("MAX_SIZE_T EQU MAX_QWORD");
	AddLineQueue("MIN_SIZE_T EQU MIN_QWORD");
	AddLineQueue("MAX_PTRDIFF_T EQU MAX_QWORD");
	AddLineQueue("MIN_PTRDIFF_T EQU MIN_QWORD");
	AddLineQueue("MAX_INTPTR_T EQU MAX_QWORD");
	AddLineQueue("MIN_INTPTR_T EQU MIN_QWORD");
	AddLineQueue("MAX_UINTPTR_T EQU MAX_QWORD");
	AddLineQueue("MIN_UINTPTR_T EQU MIN_QWORD");
	AddLineQueue("MAX_SINTPTR EQU MAX_SQWORD");
	AddLineQueue("MIN_SINTPTR EQU MIN_SQWORD");
	AddLineQueue("MAX_UINTPTR EQU MAX_UQWORD");
	AddLineQueue("MIN_UINTPTR EQU MIN_UQWORD");
	AddLineQueue("MAX_INTPTR EQU MAX_QWORD");
	AddLineQueue("MIN_INTPTR EQU MIN_QWORD");
	AddLineQueue("SINTSIZE_T_ERROR EQU SQWORD_ERROR");
	AddLineQueue("UINTSIZE_T_ERROR EQU UQWORD_ERROR");
	AddLineQueue("INTSIZE_T_ERROR EQU QWORD_ERROR");
	AddLineQueue("SIZE_T_ERROR EQU QWORD_ERROR");
	AddLineQueue("PTRDIFF_T_ERROR EQU QWORD_ERROR");
	AddLineQueue("INTPTR_T_ERROR EQU QWORD_ERROR");
	AddLineQueue("UINTPTR_T_ERROR EQU QWORD_ERROR");
	AddLineQueue("SINTPTR_ERROR EQU SQWORD_ERROR");
	AddLineQueue("UINTPTR_ERROR EQU UQWORD_ERROR");
	AddLineQueue("INTPTR_ERROR EQU QWORD_ERROR");
	AddLineQueue("ENDIF"); /*__X64__*/

	AddLineQueue("IFDEF __X32__");
	AddLineQueue("SIZE_T TEXTEQU <DWORD>");
	AddLineQueue("PTRDIFF_T TEXTEQU <DWORD>");
	AddLineQueue("INTPTR_T TEXTEQU <DWORD>");
	AddLineQueue("UINTPTR_T TEXTEQU <DWORD>");
	AddLineQueue("ISIZE_T TEXTEQU <DD>");
	AddLineQueue("PSIZE_T TEXTEQU <PTR DWORD>");
	AddLineQueue("SIZE_TP TEXTEQU <DWORD PTR>");
	AddLineQueue("PTRDIFF_T_SIZE EQU 4");
	AddLineQueue("SIZE_T_SIZE EQU 4");
	AddLineQueue("INTPTR_T_SIZE EQU 4");
	AddLineQueue("UINTPTR_T_SIZE EQU 4");
	AddLineQueue("PTR_SIZE EQU 4");
	AddLineQueue("REG_SIZE EQU 4");
	AddLineQueue("SINTSIZE_T_MAX EQU SDWORD_MAX");
	AddLineQueue("SINTSIZE_T_MIN EQU SDWORD_MIN");
	AddLineQueue("UINTSIZE_T_MAX EQU UDWORD_MAX");
	AddLineQueue("UINTSIZE_T_MIN EQU UDWORD_MIN");
	AddLineQueue("INTSIZE_T_MAX EQU DWORD_MAX");
	AddLineQueue("INTSIZE_T_MIN EQU DWORD_MIN");
	AddLineQueue("SIZE_T_MAX EQU DWORD_MAX");
	AddLineQueue("SIZE_T_MIN EQU DWORD_MIN");
	AddLineQueue("PTRDIFF_T_MAX EQU DWORD_MAX");
	AddLineQueue("PTRDIFF_T_MIN EQU DWORD_MIN");
	AddLineQueue("INTPTR_T_MAX EQU DWORD_MAX");
	AddLineQueue("INTPTR_T_MIN EQU DWORD_MIN");
	AddLineQueue("UINTPTR_T_MAX EQU DWORD_MAX");
	AddLineQueue("UINTPTR_T_MIN EQU DWORD_MIN");
	AddLineQueue("SINTPTR_MAX EQU SDWORD_MAX");
	AddLineQueue("SINTPTR_MIN EQU SDWORD_MIN");
	AddLineQueue("UINTPTR_MAX EQU UDWORD_MAX");
	AddLineQueue("UINTPTR_MIN EQU UDWORD_MIN");
	AddLineQueue("INTPTR_MAX EQU DWORD_MAX");
	AddLineQueue("INTPTR_MIN EQU DWORD_MIN");
	AddLineQueue("MAX_SINTSIZE_T EQU MAX_SDWORD");
	AddLineQueue("MIN_SINTSIZE_T EQU MIN_SDWORD");
	AddLineQueue("MAX_UINTSIZE_T EQU MAX_UDWORD");
	AddLineQueue("MIN_UINTSIZE_T EQU MIN_UDWORD");
	AddLineQueue("MAX_INTSIZE_T EQU MAX_DWORD");
	AddLineQueue("MIN_INTSIZE_T EQU MIN_DWORD");
	AddLineQueue("MAX_SIZE_T EQU MAX_DWORD");
	AddLineQueue("MIN_SIZE_T EQU MIN_DWORD");
	AddLineQueue("MAX_PTRDIFF_T EQU MAX_DWORD");
	AddLineQueue("MIN_PTRDIFF_T EQU MIN_DWORD");
	AddLineQueue("MAX_INTPTR_T EQU MAX_DWORD");
	AddLineQueue("MIN_INTPTR_T EQU MIN_DWORD");
	AddLineQueue("MAX_UINTPTR_T EQU MAX_DWORD");
	AddLineQueue("MIN_UINTPTR_T EQU MIN_DWORD");
	AddLineQueue("MAX_SINTPTR EQU MAX_SDWORD");
	AddLineQueue("MIN_SINTPTR EQU MIN_SDWORD");
	AddLineQueue("MAX_UINTPTR EQU MAX_UDWORD");
	AddLineQueue("MIN_UINTPTR EQU MIN_UDWORD");
	AddLineQueue("MAX_INTPTR EQU MAX_DWORD");
	AddLineQueue("MIN_INTPTR EQU MIN_DWORD");
	AddLineQueue("SINTSIZE_T_ERROR EQU SDWORD_ERROR");
	AddLineQueue("UINTSIZE_T_ERROR EQU UDWORD_ERROR");
	AddLineQueue("INTSIZE_T_ERROR EQU DWORD_ERROR");
	AddLineQueue("SIZE_T_ERROR EQU DWORD_ERROR");
	AddLineQueue("PTRDIFF_T_ERROR EQU DWORD_ERROR");
	AddLineQueue("INTPTR_T_ERROR EQU DWORD_ERROR");
	AddLineQueue("UINTPTR_T_ERROR EQU DWORD_ERROR");
	AddLineQueue("SINTPTR_ERROR EQU SDWORD_ERROR");
	AddLineQueue("UINTPTR_ERROR EQU UDWORD_ERROR");
	AddLineQueue("INTPTR_ERROR EQU DWORD_ERROR");
	AddLineQueue("ENDIF"); /*__X32__*/

	/*bool*/
	AddLineQueue("FALSE EQU 0x0");
	AddLineQueue("TRUE EQU 0x1");

	/*byte*/
	AddLineQueue("M8_FALSE EQU 0x00");
	AddLineQueue("M8_TRUE EQU 0xff");
	AddLineQueue("BYTE_FALSE EQU 0x00");
	AddLineQueue("BYTE_TRUE EQU 0xff");
	AddLineQueue("CHAR_FALSE EQU 0x00");
	AddLineQueue("CHAR_TRUE EQU 0xff");
	AddLineQueue("INT8_FALSE EQU 0x00");
	AddLineQueue("INT8_TRUE EQU 0xff");
	AddLineQueue("I8_FALSE EQU 0x00");
	AddLineQueue("I8_TRUE EQU 0xff");
	AddLineQueue("I8_0 EQU 0x00");
	AddLineQueue("I8_1 EQU 0x01");
	AddLineQueue("I8_NEG0 EQU 0x80");
	AddLineQueue("I8_NEG1 EQU 0xff");
	/*word*/
	AddLineQueue("M16_FALSE EQU 0x0000");
	AddLineQueue("M16_TRUE EQU 0xffff");
	AddLineQueue("WORD_FALSE EQU 0x0000");
	AddLineQueue("WORD_TRUE EQU 0xffff");
	AddLineQueue("SHORT_FALSE EQU 0x0000");
	AddLineQueue("SHORT_TRUE EQU 0xffff");
	AddLineQueue("INT16_FALSE EQU 0x0000");
	AddLineQueue("INT16_TRUE EQU 0xffff");
	AddLineQueue("I16_FALSE EQU 0x0000");
	AddLineQueue("I16_TRUE EQU 0xffff");
	AddLineQueue("I16_0 EQU 0x0000");
	AddLineQueue("I16_1 EQU 0x0001");
	AddLineQueue("I16_NEG0 EQU 0x8000");
	AddLineQueue("I16_NEG1 EQU 0xffff");
	/*dword*/
	AddLineQueue("M32_FALSE EQU 0x00000000");
	AddLineQueue("M32_TRUE EQU 0xffffffff");
	AddLineQueue("DWORD_FALSE EQU 0x00000000");
	AddLineQueue("DWORD_TRUE EQU 0xffffffff");
	AddLineQueue("LONG_FALSE EQU 0x00000000");
	AddLineQueue("LONG_TRUE EQU 0xffffffff");
	AddLineQueue("INT_FALSE EQU 0x00000000");
	AddLineQueue("INT_TRUE EQU 0xffffffff");
	AddLineQueue("INT32_FALSE EQU 0x00000000");
	AddLineQueue("INT32_TRUE EQU 0xffffffff");
	AddLineQueue("I32_FALSE EQU 0x00000000");
	AddLineQueue("I32_TRUE EQU 0xffffffff");
	AddLineQueue("I32_0 EQU 0x00000000");
	AddLineQueue("I32_1 EQU 0x00000001");
	AddLineQueue("I32_NEG0 EQU 0x80000000");
	AddLineQueue("I32_meg1 EQU 0xffffffff");
	/*qword*/
	AddLineQueue("MM_SIZE EQU 8");
	AddLineQueue("M64_SIZE EQU 8");
	AddLineQueue("MM_FALSE EQU 0x0000000000000000");
	AddLineQueue("MM_TRUE EQU 0xffffffffffffffff");
	AddLineQueue("M64_FALSE EQU 0x0000000000000000");
	AddLineQueue("M64_TRUE EQU 0xffffffffffffffff");
	AddLineQueue("QWORD_FALSE EQU 0x0000000000000000");
	AddLineQueue("QWORD_TRUE EQU 0xffffffffffffffff");
	AddLineQueue("LONGLONG_FALSE EQU 0x0000000000000000");
	AddLineQueue("LONGLONG_TRUE EQU 0xffffffffffffffff");
	AddLineQueue("INT64_FALSE EQU 0x0000000000000000");
	AddLineQueue("INT64_TRUE EQU 0xffffffffffffffff");
	AddLineQueue("I64_FALSE EQU 0x0000000000000000");
	AddLineQueue("I64_TRUE EQU 0xffffffffffffffff");
	AddLineQueue("I64_0 EQU 0x0000000000000000");
	AddLineQueue("I64_1 EQU 0x0000000000000001");
	AddLineQueue("I64_NEG0 EQU 0x8000000000000000");
	AddLineQueue("I64_NEG1 EQU 0xffffffffffffffff");

	/*xmm type*/
	AddLineQueue("XMM_SIZE EQU 16");
	AddLineQueue("M128_SIZE EQU 16");

	/*ymm type*/
	AddLineQueue("YMM_SIZE EQU 32");
	AddLineQueue("M256_SIZE EQU 32");

	/*zmm type*/
	AddLineQueue("ZMM_SIZE EQU 64");
	AddLineQueue("M512_SIZE EQU 64");

	/*float mask*/
	AddLineQueue("FLT_1LSHL3_MSK EQU 0x00000008");
	AddLineQueue("FLT_1LSHL4_MSK EQU 0x00000010");
	AddLineQueue("FLT_1LSHL7_MSK EQU 0x00000080");
	AddLineQueue("FLT_1LSHL8_MSK EQU 0x00000100");
	AddLineQueue("FLT_1LSHL11_MSK EQU 0x00000800");
	AddLineQueue("FLT_1LSHL12_MSK EQU 0x00001000");
	AddLineQueue("FLT_1LSHL15_MSK EQU 0x00008000");
	AddLineQueue("FLT_1LSHL16_MSK EQU 0x00010000");
	AddLineQueue("FLT_1LSHL19_MSK EQU 0x00080000");
	AddLineQueue("FLT_1LSHL20_MSK EQU 0x00100000");
	AddLineQueue("FLT_1LSHL23_MSK EQU 0x00800000");
	AddLineQueue("FLT_1LSHL24_MSK EQU 0x01000000");
	AddLineQueue("FLT_1LSHL27_MSK EQU 0x08000000");
	AddLineQueue("FLT_1LSHL28_MSK EQU 0x10000000");
	AddLineQueue("FLT_1LSHL31_MSK EQU 0x80000000");

	AddLineQueue("FLT_NEG1LSHL3_MSK EQU 0xfffffff8");
	AddLineQueue("FLT_NEG1LSHL4_MSK EQU 0xfffffff0");
	AddLineQueue("FLT_NEG1LSHL7_MSK EQU 0xffffff80");
	AddLineQueue("FLT_NEG1LSHL8_MSK EQU 0xffffff00");
	AddLineQueue("FLT_NEG1LSHL11_MSK EQU 0xfffff800");
	AddLineQueue("FLT_NEG1LSHL12_MSK EQU 0xfffff000");
	AddLineQueue("FLT_NEG1LSHL15_MSK EQU 0xffff8000");
	AddLineQueue("FLT_NEG1LSHL16_MSK EQU 0xffff0000");
	AddLineQueue("FLT_NEG1LSHL19_MSK EQU 0xfff80000");
	AddLineQueue("FLT_NEG1LSHL20_MSK EQU 0xfff00000");
	AddLineQueue("FLT_NEG1LSHL23_MSK EQU 0xff800000");
	AddLineQueue("FLT_NEG1LSHL24_MSK EQU 0xff000000");
	AddLineQueue("FLT_NEG1LSHL27_MSK EQU 0xf8000000");
	AddLineQueue("FLT_NEG1LSHL28_MSK EQU 0xf0000000");
	AddLineQueue("FLT_NEG1LSHL31_MSK EQU 0x80000000");

	AddLineQueue("FLT_FALSE_MSK EQU 0x00000000");
	AddLineQueue("FLT_TRUE_MSK EQU 0xffffffff");
	AddLineQueue("FLT_ERROR_MSK EQU FLT_ERROR");

	AddLineQueue("FLT_MAGIC_MSK EQU 0x4b000000");
	AddLineQueue("FLT_SIGN_MSK EQU 0x80000000");
	AddLineQueue("FLT_INVSIGN_MSK EQU 0x7fffffff");

	AddLineQueue("FLT_INF_MSK EQU 0x7f800000");
	AddLineQueue("FLT_FIN_MSK EQU 0xff000000");
	AddLineQueue("FLT_INVINF_MSK EQU 0x807fffff");
	AddLineQueue("FLT_NEGINF_MSK EQU 0xff800000");
	AddLineQueue("FLT_NAN_MSK EQU 0x7fffffff");
	AddLineQueue("FLT_QNAN_MSK EQU 0x7fc00000");
	AddLineQueue("FLT_NEGQNAN_MSK EQU 0xffc00000");
	AddLineQueue("FLT_NANTEST_MSK EQU 0x007fffff");
	AddLineQueue("FLT_ABS_MSK EQU 0x7fffffff");
	AddLineQueue("FLT_MIN_MSK EQU 0x00800000");
	AddLineQueue("FLT_MAX_MSK EQU 0x7f7fffff");
	AddLineQueue("FLT_NOFRACTION_MSK EQU 0x00800000");
	AddLineQueue("FLT_MINDENORM_MSK EQU 0x00000001");
	AddLineQueue("FLT_DENORMLIMIT_MSK EQU 0x00800000");
	AddLineQueue("FLT_MINNORMAL_MSK EQU 0x00800000");
	AddLineQueue("FLT_MAXNORMAL_MSK EQU 0x7f7fffff");

	AddLineQueue("FLT_DECDIG_MSK EQU 0x00000009");
	AddLineQueue("FLT_DIG_MSK EQU 0x00000006");
	AddLineQueue("FLT_NEGDECDIG_MSK EQU 0xfffffff7");
	AddLineQueue("FLT_NEGDIG_MSK EQU 0xfffffffa");
	AddLineQueue("FLT_EPS_MSK EQU 0x34000000");
	AddLineQueue("FLT_EPSILON_MSK EQU 0x34000000");
	AddLineQueue("FLT_NORMEPS_MSK EQU 0x1e3ce508");
	AddLineQueue("FLT_GUARD_MSK EQU 0x00000000");
	AddLineQueue("FLT_MANTPOW2_MSK EQU 0x00800000");
	AddLineQueue("FLT_MAXMANTPOW2_MSK EQU 0x7f7fffff");
	AddLineQueue("FLT_MANTDIG_MSK EQU 0x00000018");
	AddLineQueue("FLT_MANT_MSK EQU 0x00000017");
	AddLineQueue("FLT_NEGMANTDIG_MSK EQU 0xffffffe8");
	AddLineQueue("FLT_NEGMANT_MSK EQU 0xffffffe9");
	AddLineQueue("FLT_MAXEXP_MSK EQU 0x00000080");
	AddLineQueue("FLT_EXPSIGN_MSK EQU 0x00000080");
	AddLineQueue("FLT_EXP_MSK EQU 0x0000007f");
	AddLineQueue("FLT_NEGMAXEXP_MSK EQU 0xffffff80");
	AddLineQueue("FLT_NEGEXPSIGN_MSK EQU 0xffffff80");
	AddLineQueue("FLT_NEGEXP_MSK EQU 0xffffff81");
	AddLineQueue("FLT_SUBNORMALEXP_MSK EQU 0xffffff82");
	AddLineQueue("FLT_MINEXP_MSK EQU 0xffffff83");
	AddLineQueue("FLT_MAXDECEXP_MSK EQU 0x00000026");
	AddLineQueue("FLT_NEGMAXDECEXP_MSK EQU 0xffffffda");
	AddLineQueue("FLT_MINDECEXP_MSK EQU 0xffffffd8");
	AddLineQueue("FLT_EXPFIELD_MSK EQU 0xff000000");
	AddLineQueue("FLT_MANTFIELD_MSK EQU 0x00ffffff");
	AddLineQueue("FLT_NORM_MSK EQU 0x00000000");
	AddLineQueue("FLT_RADIX_MSK EQU 0x00000002");
	AddLineQueue("FLT_ROUNDS_MSK EQU 0x00000001");
	AddLineQueue("FLT_SUBDEC_MSK EQU 0x0000000a");
	AddLineQueue("FLT_SQRTMAX_MSK EQU 0x5f7ffff0");
	AddLineQueue("FLT_SMALLNORMAL_MSK EQU 0x00800000");

	AddLineQueue("FLT_HALFMINUSEPS_MSK EQU 0x3efffffd");
	AddLineQueue("FLT_TRUEINT_MSK EQU 0x00000001");
	
	AddLineQueue("FLT_BYTE_MSK EQU 0x000000ff");
	AddLineQueue("FLT_BYTE_EVEN_MSK EQU 0x00ff00ff");
	AddLineQueue("FLT_BYTE_ODD_MSK EQU 0xff00ff00");
	AddLineQueue("FLT_4LOW_MSK EQU 0x0fffffff");
	AddLineQueue("FLT_4HIGH_MSK EQU 0xfffffff0");
	AddLineQueue("FLT_FLIP4_MSK EQU 0x00000008");
	AddLineQueue("FLT_8LOW_MSK EQU 0x00ffffff");
	AddLineQueue("FLT_8HIGH_MSK EQU 0xffffff00");
	AddLineQueue("FLT_FLIP8_MSK EQU 0x00000080");
	AddLineQueue("FLT_16LOW_MSK EQU 0x0000ffff");
	AddLineQueue("FLT_16HIGH_MSK EQU 0xffff0000");
	AddLineQueue("FLT_FLIP16_MSK EQU 0x00008000");
	AddLineQueue("FLT_24LOW_MSK EQU 0x000000ff");
	AddLineQueue("FLT_24HIGH_MSK EQU 0xff000000");
	AddLineQueue("FLT_FLIP24_MSK EQU 0x00800000");
	AddLineQueue("FLT_28LOW_MSK EQU 0x0000000f");
	AddLineQueue("FLT_28HIGH_MSK EQU 0xf0000000");
	AddLineQueue("FLT_FLIP28_MSK EQU 0x08000000");
	AddLineQueue("FLT_32LOW_MSK EQU 0x00000000");
	AddLineQueue("FLT_32HIGH_MSK EQU 0x00000000");
	AddLineQueue("FLT_FLIP32_MSK EQU 0x80000000");

	AddLineQueue("FLT_0_MSK EQU 0x00000000");
	AddLineQueue("FLT_0D5_MSK EQU 0x3f000000");
	AddLineQueue("FLT_1_MSK EQU 0x3f800000");
	AddLineQueue("FLT_1D5_MSK EQU 0x3fc00000");
	AddLineQueue("FLT_2_MSK EQU 0x40000000");
	AddLineQueue("FLT_2D5_MSK EQU 0x40200000");
	AddLineQueue("FLT_3_MSK EQU 0x40400000");
	AddLineQueue("FLT_4_MSK EQU 0x40800000");
	AddLineQueue("FLT_5_MSK EQU 0x40a00000");
	AddLineQueue("FLT_6_MSK EQU 0x40c00000");
	AddLineQueue("FLT_7_MSK EQU 0x40e00000");
	AddLineQueue("FLT_8_MSK EQU 0x41000000");
	AddLineQueue("FLT_9_MSK EQU 0x41100000");
	AddLineQueue("FLT_10_MSK EQU 0x41200000");
	AddLineQueue("FLT_20_MSK EQU 0x41a00000");
	AddLineQueue("FLT_23_MSK EQU 0x41b80000");
	AddLineQueue("FLT_23D5_MSK EQU 0x41bc0000");
	AddLineQueue("FLT_24_MSK EQU 0x41c00000");
	AddLineQueue("FLT_24D5_MSK EQU 0x41c40000");
	AddLineQueue("FLT_25_MSK EQU 0x41c80000");

	AddLineQueue("FLT_128_MSK EQU 0x43000000");

	AddLineQueue("FLT_253_MSK EQU 0x437d0000");

	AddLineQueue("FLT_NEG0_MSK EQU 0x80000000");
	AddLineQueue("FLT_NEG1_MSK EQU 0xbf800000");

	AddLineQueue("FLT_NEG150_MSK EQU 0xc3160000");
	
	AddLineQueue("FLT_A8_MSK EQU 0x00ff0000");
	AddLineQueue("FLT_R8_MSK EQU 0x0000ff00");
	AddLineQueue("FLT_G8_MSK EQU 0x000000ff");
	AddLineQueue("FLT_B8_MSK EQU 0xff000000");

	AddLineQueue("FLT_FLIPA8_MSK EQU FLT_0_MSK");
	AddLineQueue("FLT_FLIPR8_MSK EQU FLT_0_MSK");
	AddLineQueue("FLT_FLIPG8_MSK EQU FLT_0_MSK");
	AddLineQueue("FLT_FLIPB8_MSK EQU FLT_NEG0_MSK");

	AddLineQueue("FLT_A2_MSK EQU 0x000003ff");
	AddLineQueue("FLT_B10_MSK EQU 0x000ffc00");
	AddLineQueue("FLT_G10_MSK EQU 0x3ff00000");
	AddLineQueue("FLT_R10_MSK EQU 0xc0000000");

	AddLineQueue("FLT_FLIPA2_MSK EQU 0x00000200");
	AddLineQueue("FLT_FLIPB10_MSK EQU 0x00080000");
	AddLineQueue("FLT_FLIPG10_MSK EQU 0x20000000");
	AddLineQueue("FLT_FLIPR10_MSK EQU 0x80000000");

	AddLineQueue("FLT_BIN128_MSK EQU FLT_128_MSK");
	AddLineQueue("FLT_BINNEG150_MSK EQU FLT_NEG150_MSK");

	AddLineQueue("FLT_MAXRAND_MSK EQU 0x00007fff");

	AddLineQueue("FLT_MAXI8_MSK EQU 0x0000007f");
	AddLineQueue("FLT_MINI8_MSK EQU 0xffffff80");
	AddLineQueue("FLT_MAXU8_MSK EQU 0x000000ff");

	AddLineQueue("FLT_MAXI16_MSK EQU 0x00007fff");
	AddLineQueue("FLT_MINI16_MSK EQU 0xffff8000");
	AddLineQueue("FLT_MAXU16_MSK EQU 0x0000ffff");

	AddLineQueue("FLT_MAXI32_MSK EQU 0x7fffffff");
	AddLineQueue("FLT_MINI32_MSK EQU 0x80000000");
	AddLineQueue("FLT_MAXU32_MSK EQU 0xffffffff");

	AddLineQueue("FLT_MAXI8XU8_MSK EQU 0x00008000");
	AddLineQueue("FLT_MINI8XU8_MSK EQU 0xffff8000");
	AddLineQueue("FLT_MAXI8XU16_MSK EQU 0x00800000");
	AddLineQueue("FLT_MINI8XU16_MSK EQU 0xff800000");

	AddLineQueue("FLT_MAXI16XU16_MSK EQU 0x80000000");
	AddLineQueue("FLT_MINI16XU16_MSK EQU 0x80000000");

	AddLineQueue("FLT_FIXUNSIGNED_MSK EQU 0x80000000");
	AddLineQueue("FLT_FIXUNSIGNED32_MSK EQU 0x80000000");
	AddLineQueue("FLT_FIXMAXI32_MSK EQU 0x7fffff80");
	AddLineQueue("FLT_FIXMAXU32_MSK EQU 0xffffff00");

	/*float int*/
	AddLineQueue("FLT_1LSHL3_INT EQU 8");
	AddLineQueue("FLT_1LSHL4_INT EQU 16");
	AddLineQueue("FLT_1LSHL7_INT EQU 128");
	AddLineQueue("FLT_1LSHL8_INT EQU 256");
	AddLineQueue("FLT_1LSHL11_INT EQU 2048");
	AddLineQueue("FLT_1LSHL12_INT EQU 4096");
	AddLineQueue("FLT_1LSHL15_INT EQU 32768");
	AddLineQueue("FLT_1LSHL16_INT EQU 65536");
	AddLineQueue("FLT_1LSHL19_INT EQU 524288");
	AddLineQueue("FLT_1LSHL20_INT EQU 1048576");
	AddLineQueue("FLT_1LSHL23_INT EQU 8388608");
	AddLineQueue("FLT_1LSHL24_INT EQU 16777216");
	AddLineQueue("FLT_1LSHL27_INT EQU 134217728");
	AddLineQueue("FLT_1LSHL28_INT EQU 268435456");
	AddLineQueue("FLT_1LSHL31_INT EQU 2147483648");

	AddLineQueue("FLT_NEG1LSHL3_INT EQU (-8)");
	AddLineQueue("FLT_NEG1LSHL4_INT EQU (-16)");
	AddLineQueue("FLT_NEG1LSHL7_INT EQU (-128)");
	AddLineQueue("FLT_NEG1LSHL8_INT EQU (-256)");
	AddLineQueue("FLT_NEG1LSHL11_INT EQU (-2048)");
	AddLineQueue("FLT_NEG1LSHL12_INT EQU (-4096)");
	AddLineQueue("FLT_NEG1LSHL15_INT EQU (-32768)");
	AddLineQueue("FLT_NEG1LSHL16_INT EQU (-65536)");
	AddLineQueue("FLT_NEG1LSHL19_INT EQU (-524288)");
	AddLineQueue("FLT_NEG1LSHL20_INT EQU (-1048576)");
	AddLineQueue("FLT_NEG1LSHL23_INT EQU (-8388608)");
	AddLineQueue("FLT_NEG1LSHL24_INT EQU (-16777216)");
	AddLineQueue("FLT_NEG1LSHL27_INT EQU (-134217728)");
	AddLineQueue("FLT_NEG1LSHL28_INT EQU (-268435456)");
	AddLineQueue("FLT_NEG1LSHL31_INT EQU (-2147483648)");

	AddLineQueue("FLT_FALSE_INT EQU 0");
	AddLineQueue("FLT_TRUE_INT EQU (-1)");
	AddLineQueue("FLT_ERROR_INT EQU FLT_ERROR");

	AddLineQueue("FLT_MAGIC_INT EQU 1258291200");
	AddLineQueue("FLT_SIGN_INT EQU (-2147483648)");
	AddLineQueue("FLT_INVSIGN_INT EQU 2147483647");

	AddLineQueue("FLT_INF_INT EQU 2139095040");
	AddLineQueue("FLT_FIN_INT EQU (-16777216)");
	AddLineQueue("FLT_INVINF_INT EQU (-2139095041)");
	AddLineQueue("FLT_NEGINF_INT EQU (-8388608)");
	AddLineQueue("FLT_NAN_INT EQU 2147483647");
	AddLineQueue("FLT_QNAN_INT EQU 2143289344");
	AddLineQueue("FLT_NEGQNAN_INT EQU (-4194304)");
	AddLineQueue("FLT_NANTEST_INT EQU 8388607");
	AddLineQueue("FLT_ABS_INT EQU 2147483647");
	AddLineQueue("FLT_MIN_INT EQU 8388608");
	AddLineQueue("FLT_MAX_INT EQU 2139095039");
	AddLineQueue("FLT_NOFRACTION_INT EQU 8388608");
	AddLineQueue("FLT_MINDENORM_INT EQU 1");
	AddLineQueue("FLT_DENORMLIMIT_INT EQU 8388608");
	AddLineQueue("FLT_MINNORMAL_INT EQU 8388608");
	AddLineQueue("FLT_MAXNORMAL_INT EQU 2139095039");

	AddLineQueue("FLT_DECDIG_INT EQU 9");
	AddLineQueue("FLT_DIG_INT EQU 6");
	AddLineQueue("FLT_NEGDECDIG_INT EQU (-9)");
	AddLineQueue("FLT_NEGDIG_INT EQU (-6)");
	AddLineQueue("FLT_EPS_INT EQU 872415232");
	AddLineQueue("FLT_EPSILON_INT EQU 872415232");
	AddLineQueue("FLT_NORMEPS_INT EQU 507307272");
	AddLineQueue("FLT_GUARD_INT EQU 0");
	AddLineQueue("FLT_MANTPOW2_INT EQU 8388608");
	AddLineQueue("FLT_MAXMANTPOW2_INT EQU 2139095039");
	AddLineQueue("FLT_MANTDIG_INT EQU 24");
	AddLineQueue("FLT_MANT_INT EQU 23");
	AddLineQueue("FLT_NEGMANTDIG_INT EQU (-24)");
	AddLineQueue("FLT_NEGMANT_INT EQU (-23)");
	AddLineQueue("FLT_MAXEXP_INT EQU 128");
	AddLineQueue("FLT_EXPSIGN_INT EQU 128");
	AddLineQueue("FLT_EXP_INT EQU 127");
	AddLineQueue("FLT_NEGMAXEXP_INT EQU (-128)");
	AddLineQueue("FLT_NEGEXPSIGN_INT EQU (-128)");
	AddLineQueue("FLT_NEGEXP_INT EQU (-127)");
	AddLineQueue("FLT_SUBNORMALEXP_INT EQU (-126)");
	AddLineQueue("FLT_MINEXP_INT EQU (-125)");
	AddLineQueue("FLT_MAXDECEXP_INT EQU 38");
	AddLineQueue("FLT_NEGMAXDECEXP_INT EQU (-38)");
	AddLineQueue("FLT_MINDECEXP_INT EQU (-37)");
	AddLineQueue("FLT_EXPFIELD_INT EQU (-16777216)");
	AddLineQueue("FLT_MANTFIELD_INT EQU 16777215");
	AddLineQueue("FLT_NORM_INT EQU 0");
	AddLineQueue("FLT_RADIX_INT EQU 2");
	AddLineQueue("FLT_ROUNDS_INT EQU 1");
	AddLineQueue("FLT_SUBDEC_INT EQU 10");
	AddLineQueue("FLT_SQRTMAX_INT EQU 1602224112");
	AddLineQueue("FLT_SMALLNORMAL_INT EQU 8388608");

	AddLineQueue("FLT_HALFMINUSEPS_INT EQU 1056964605");
	AddLineQueue("FLT_TRUEINT_INT EQU 1");

	AddLineQueue("FLT_BYTE_INT EQU 255");
	AddLineQueue("FLT_BYTE_EVEN_INT EQU 16711935");
	AddLineQueue("FLT_BYTE_ODD_INT EQU (-16711936)");
	AddLineQueue("FLT_4LOW_INT EQU 268435455");
	AddLineQueue("FLT_4HIGH_INT EQU (-16)");
	AddLineQueue("FLT_FLIP4_INT EQU 8");
	AddLineQueue("FLT_8LOW_INT EQU 16777215");
	AddLineQueue("FLT_8HIGH_INT EQU (-256)");
	AddLineQueue("FLT_FLIP8_INT EQU 128");
	AddLineQueue("FLT_16LOW_INT EQU 65535");
	AddLineQueue("FLT_16HIGH_INT EQU (-65536)");
	AddLineQueue("FLT_FLIP16_INT EQU 32768");
	AddLineQueue("FLT_24LOW_INT EQU 255");
	AddLineQueue("FLT_24HIGH_INT EQU (-16777216)");
	AddLineQueue("FLT_FLIP24_INT EQU 8388608");
	AddLineQueue("FLT_28LOW_INT EQU 15");
	AddLineQueue("FLT_28HIGH_INT EQU (-268435456)");
	AddLineQueue("FLT_FLIP28_INT EQU 134217728");
	AddLineQueue("FLT_32LOW_INT EQU 0");
	AddLineQueue("FLT_32HIGH_INT EQU 0");
	AddLineQueue("FLT_FLIP32_INT EQU (-2147483648)");

	AddLineQueue("FLT_0_INT EQU 0x00000000");
	AddLineQueue("FLT_0D5_INT EQU 1056964608");
	AddLineQueue("FLT_1_INT EQU 1065353216");
	AddLineQueue("FLT_1D5_INT EQU 1069547520");
	AddLineQueue("FLT_2_INT EQU 1073741824");
	AddLineQueue("FLT_2D5_INT EQU 1075838976");
	AddLineQueue("FLT_3_INT EQU 1077936128");
	AddLineQueue("FLT_4_INT EQU 1082130432");
	AddLineQueue("FLT_5_INT EQU 1084227584");
	AddLineQueue("FLT_6_INT EQU 1086324736");
	AddLineQueue("FLT_7_INT EQU 1088421888");
	AddLineQueue("FLT_8_INT EQU 1090519040");
	AddLineQueue("FLT_9_INT EQU 1091567616");
	AddLineQueue("FLT_10_INT EQU 1092616192");
	AddLineQueue("FLT_20_INT EQU 1101004800");
	AddLineQueue("FLT_23_INT EQU 1102577664");
	AddLineQueue("FLT_23D5_INT EQU 1102839808");
	AddLineQueue("FLT_24_INT EQU 1103101952");
	AddLineQueue("FLT_24D5_INT EQU 1103364096");
	AddLineQueue("FLT_25_INT EQU 1103626240");

	AddLineQueue("FLT_128_INT EQU 1124073472");

	AddLineQueue("FLT_253_INT EQU 1132265472");

	AddLineQueue("FLT_NEG0_INT EQU (-2147483648)");
	AddLineQueue("FLT_NEG1_INT EQU (-1082130432)");

	AddLineQueue("FLT_NEG150_INT EQU (-1021968384)");

	AddLineQueue("FLT_A8_INT EQU 16711680");
	AddLineQueue("FLT_R8_INT EQU 65280");
	AddLineQueue("FLT_G8_INT EQU 255");
	AddLineQueue("FLT_B8_INT EQU (-16777216)");

	AddLineQueue("FLT_FLIPA8_INT EQU FLT_0_INT");
	AddLineQueue("FLT_FLIPR8_INT EQU FLT_0_INT");
	AddLineQueue("FLT_FLIPG8_INT EQU FLT_0_INT");
	AddLineQueue("FLT_FLIPB8_INT EQU FLT_NEG0_INT");

	AddLineQueue("FLT_A2_INT EQU 1023");
	AddLineQueue("FLT_B10_INT EQU 1047552");
	AddLineQueue("FLT_G10_INT EQU 1072693248");
	AddLineQueue("FLT_R10_INT EQU (-1073741824)");

	AddLineQueue("FLT_FLIPA2_INT EQU 512");
	AddLineQueue("FLT_FLIPB10_INT EQU 524288");
	AddLineQueue("FLT_FLIPG10_INT EQU 536870912");
	AddLineQueue("FLT_FLIPR10_INT EQU (-2147483648)");

	AddLineQueue("FLT_BIN128_INT EQU FLT_128_INT");
	AddLineQueue("FLT_BINNEG150_INT EQU FLT_NEG150_INT");

	AddLineQueue("FLT_MAXRAND_INT EQU 32767");

	AddLineQueue("FLT_MAXI8_INT EQU 127");
	AddLineQueue("FLT_MINI8_INT EQU (-128)");
	AddLineQueue("FLT_MAXU8_INT EQU 255");

	AddLineQueue("FLT_MAXI16_INT EQU 32767");
	AddLineQueue("FLT_MINI16_INT EQU (-32768)");
	AddLineQueue("FLT_MAXU16_INT EQU 65535");

	AddLineQueue("FLT_MAXI32_INT EQU 2147483647");
	AddLineQueue("FLT_MINI32_INT EQU (-2147483648)");
	AddLineQueue("FLT_MAXU32_INT EQU (-1)");

	AddLineQueue("FLT_MAXI8XU8_INT EQU 32768");
	AddLineQueue("FLT_MINI8XU8_INT EQU (-32768)");
	AddLineQueue("FLT_MAXI8XU16_INT EQU 8388608");
	AddLineQueue("FLT_MINI8XU16_INT EQU (-8388608)");

	AddLineQueue("FLT_MAXI16XU16_INT EQU (-2147483648)");
	AddLineQueue("FLT_MINI16XU16_INT EQU (-2147483648)");

	AddLineQueue("FLT_FIXUNSIGNED_INT EQU (-2147483648)");
	AddLineQueue("FLT_FIXUNSIGNED32_INT EQU (-2147483648)");
	AddLineQueue("FLT_FIXMAXI32_INT EQU 2147483520");
	AddLineQueue("FLT_FIXMAXU32_INT EQU (-256)");

	/*float*/
	AddLineQueue("FLT_1LSHL3 EQU 8.0");
	AddLineQueue("FLT_1LSHL4 EQU 16.0");
	AddLineQueue("FLT_1LSHL7 EQU 128.0");
	AddLineQueue("FLT_1LSHL8 EQU 256.0");
	AddLineQueue("FLT_1LSHL11 EQU 2048.0");
	AddLineQueue("FLT_1LSHL12 EQU 4096.0");
	AddLineQueue("FLT_1LSHL15 EQU 32768.0");
	AddLineQueue("FLT_1LSHL16 EQU 65536.0");
	AddLineQueue("FLT_1LSHL19 EQU 524288.0");
	AddLineQueue("FLT_1LSHL20 EQU 1048576.0");
	AddLineQueue("FLT_1LSHL23 EQU 8388608.0");
	AddLineQueue("FLT_1LSHL24 EQU 16777216.0");
	AddLineQueue("FLT_1LSHL27 EQU 134217728.0");
	AddLineQueue("FLT_1LSHL28 EQU 268435456.0");
	AddLineQueue("FLT_1LSHL31 EQU 2147483648.0");

	AddLineQueue("FLT_NEG1LSHL3 EQU (-8.0)");
	AddLineQueue("FLT_NEG1LSHL4 EQU (-16.0)");
	AddLineQueue("FLT_NEG1LSHL7 EQU (-128.0)");
	AddLineQueue("FLT_NEG1LSHL8 EQU (-256.0)");
	AddLineQueue("FLT_NEG1LSHL11 EQU (-2048.0)");
	AddLineQueue("FLT_NEG1LSHL12 EQU (-4096.0)");
	AddLineQueue("FLT_NEG1LSHL15 EQU (-32768.0)");
	AddLineQueue("FLT_NEG1LSHL16 EQU (-65536.0)");
	AddLineQueue("FLT_NEG1LSHL19 EQU (-524288.0)");
	AddLineQueue("FLT_NEG1LSHL20 EQU (-1048576.0)");
	AddLineQueue("FLT_NEG1LSHL23 EQU (-8388608.0)");
	AddLineQueue("FLT_NEG1LSHL24 EQU (-16777216.0)");
	AddLineQueue("FLT_NEG1LSHL27 EQU (-134217728.0)");
	AddLineQueue("FLT_NEG1LSHL28 EQU (-268435456.0)");
	AddLineQueue("FLT_NEG1LSHL31 EQU (-2147483648.0)");

	AddLineQueue("FLT_FALSE EQU FLT_FALSE_MSK");
	AddLineQueue("FLT_TRUE EQU FLT_TRUE_MSK");

	AddLineQueue("FLT_MAGIC EQU FLT_MAGIC_MSK");
	AddLineQueue("FLT_SIGN EQU FLT_SIGN_MSK");
	AddLineQueue("FLT_INVSIGN EQU FLT_INVSIGN_MSK");

	AddLineQueue("FLT_INF EQU FLT_INF_MSK");
	AddLineQueue("FLT_FIN EQU FLT_FIN_MSK");
	AddLineQueue("FLT_INVINF EQU FLT_INVINF_MSK");
	AddLineQueue("FLT_NEGINF EQU FLT_NEGINF_MSK");
	AddLineQueue("FLT_NAN EQU FLT_NAN_MSK");
	AddLineQueue("FLT_QNAN EQU FLT_QNAN_MSK");
	AddLineQueue("FLT_NEGQNAN EQU FLT_NEGQNAN_MSK");
	AddLineQueue("FLT_NANTEST EQU FLT_NANTEST_MSK");
	AddLineQueue("FLT_ABS EQU FLT_ABS_MSK");
	AddLineQueue("FLT_MIN EQU 1.175494351e-38");
	AddLineQueue("FLT_MAX EQU 3.402823457175904428664032e+38");
	AddLineQueue("FLT_NOFRACTION EQU 8388608.0");
	AddLineQueue("FLT_MINDENORM EQU 1.401298463344573974609375e-45");
	AddLineQueue("FLT_DENORMLIMIT EQU 1.175494351e-38");
	AddLineQueue("FLT_MINNORMAL EQU 1.175494351e-38");
	AddLineQueue("FLT_MAXNORMAL EQU 3.402823457175904428664032e+38");

	AddLineQueue("FLT_DECDIG EQU 9.0");
	AddLineQueue("FLT_DIG EQU 6.0");
	AddLineQueue("FLT_NEGDECDIG EQU (-9.0)");
	AddLineQueue("FLT_NEGDIG EQU (-6.0)");
	AddLineQueue("FLT_EPS EQU 1.192092896e-07");
	AddLineQueue("FLT_EPSILON EQU 1.192092896e-07");
	AddLineQueue("FLT_NORMEPS EQU 1e-20");
	AddLineQueue("FLT_GUARD EQU 0.0");
	AddLineQueue("FLT_MANTPOW2 EQU 1.175494351e-38");
	AddLineQueue("FLT_MAXMANTPOW2 EQU 3.402823457175904428664032e+38");
	AddLineQueue("FLT_MANTDIG EQU 24.0");
	AddLineQueue("FLT_MANT EQU 23.0");
	AddLineQueue("FLT_NEGMANTDIG EQU (-24.0)");
	AddLineQueue("FLT_NEGMANT EQU (-23.0)");
	AddLineQueue("FLT_MAXEXP EQU 128.0");
	AddLineQueue("FLT_EXPSIGN EQU 128.0");
	AddLineQueue("FLT_EXP EQU 127.0");
	AddLineQueue("FLT_NEGMAXEXP EQU (-128.0)");
	AddLineQueue("FLT_NEGEXPSIGN EQU (-128.0)");
	AddLineQueue("FLT_NEGEXP EQU (-127.0)");
	AddLineQueue("FLT_SUBNORMALEXP EQU (-126.0)");
	AddLineQueue("FLT_MINEXP EQU (-125.0)");
	AddLineQueue("FLT_MAXDECEXP EQU 38.0");
	AddLineQueue("FLT_NEGMAXDECEXP EQU (-38.0)");
	AddLineQueue("FLT_MINDECEXP EQU (-37.0)");
	AddLineQueue("FLT_EXPFIELD EQU (-16777216.0)");
	AddLineQueue("FLT_MANTFIELD EQU 16777215.0");
	AddLineQueue("FLT_NORM EQU 0.0");
	AddLineQueue("FLT_RADIX EQU 2.0");
	AddLineQueue("FLT_ROUNDS EQU 1.0");
	AddLineQueue("FLT_SUBDEC EQU 10.0");
	AddLineQueue("FLT_SQRTMAX EQU 1.8446726e+019");
	AddLineQueue("FLT_SMALLNORMAL EQU 1.175494351e-38");

	AddLineQueue("FLT_HALFMINUSEPS EQU 0.499999910593032825");
	AddLineQueue("FLT_TRUEINT EQU 1.0");

	AddLineQueue("FLT_BYTE EQU 255.0");
	AddLineQueue("FLT_BYTE_EVEN EQU 16711935.0");
	AddLineQueue("FLT_BYTE_ODD EQU (-16711936.0)");
	AddLineQueue("FLT_4LOW EQU 268435455.0");
	AddLineQueue("FLT_4HIGH EQU (-16.0)");
	AddLineQueue("FLT_FLIP4 EQU 8.0");
	AddLineQueue("FLT_8LOW EQU 16777215.0");
	AddLineQueue("FLT_8HIGH EQU (-256.0)");
	AddLineQueue("FLT_FLIP8 EQU 128.0");
	AddLineQueue("FLT_16LOW EQU 65535.0");
	AddLineQueue("FLT_16HIGH EQU (-65536.0)");
	AddLineQueue("FLT_FLIP16 EQU 32768.0");
	AddLineQueue("FLT_24LOW EQU 255.0");
	AddLineQueue("FLT_24HIGH EQU (-16777216.0)");
	AddLineQueue("FLT_FLIP24 EQU 8388608.0");
	AddLineQueue("FLT_28LOW EQU 15.0");
	AddLineQueue("FLT_28HIGH EQU (-268435456.0)");
	AddLineQueue("FLT_FLIP28 EQU 134217728.0");
	AddLineQueue("FLT_32LOW EQU 0.0");
	AddLineQueue("FLT_32HIGH EQU 0.0");
	AddLineQueue("FLT_FLIP32 EQU (-2147483648.0)");

	AddLineQueue("FLT_0 EQU 0.0");
	AddLineQueue("FLT_0D0001 EQU 0.0001");
	AddLineQueue("FLT_0D0002 EQU 0.0002");
	AddLineQueue("FLT_0D0003 EQU 0.0003");
	AddLineQueue("FLT_0D0004 EQU 0.0004");
	AddLineQueue("FLT_0D0005 EQU 0.0005");
	AddLineQueue("FLT_0D0006 EQU 0.0006");
	AddLineQueue("FLT_0D0007 EQU 0.0007");
	AddLineQueue("FLT_0D0008 EQU 0.0008");
	AddLineQueue("FLT_0D0009 EQU 0.0009");
	AddLineQueue("FLT_0D001 EQU 0.001");
	AddLineQueue("FLT_0D002 EQU 0.002");
	AddLineQueue("FLT_0D003 EQU 0.003");
	AddLineQueue("FLT_0D004 EQU 0.004");
	AddLineQueue("FLT_0D005 EQU 0.005");
	AddLineQueue("FLT_0D006 EQU 0.006");
	AddLineQueue("FLT_0D007 EQU 0.007");
	AddLineQueue("FLT_0D008 EQU 0.008");
	AddLineQueue("FLT_0D009 EQU 0.009");
	AddLineQueue("FLT_0D01 EQU 0.01");
	AddLineQueue("FLT_0D02 EQU 0.02");
	AddLineQueue("FLT_0D025 EQU 0.025");
	AddLineQueue("FLT_0D03 EQU 0.03");
	AddLineQueue("FLT_0D04 EQU 0.04");
	AddLineQueue("FLT_0D05 EQU 0.05");
	AddLineQueue("FLT_0D06 EQU 0.06");
	AddLineQueue("FLT_0D07 EQU 0.07");
	AddLineQueue("FLT_0D08 EQU 0.08");
	AddLineQueue("FLT_0D09 EQU 0.09");
	AddLineQueue("FLT_0D1 EQU 0.1");
	AddLineQueue("FLT_0D2 EQU 0.2");
	AddLineQueue("FLT_0D25 EQU 0.25");
	AddLineQueue("FLT_0D3 EQU 0.3");
	AddLineQueue("FLT_0D4 EQU 0.4");
	AddLineQueue("FLT_0D5 EQU 0.5");
	AddLineQueue("FLT_0D6 EQU 0.6");
	AddLineQueue("FLT_0D7 EQU 0.7");
	AddLineQueue("FLT_0D8 EQU 0.8");
	AddLineQueue("FLT_0D9 EQU 0.9");
	AddLineQueue("FLT_1 EQU 1.0");
	AddLineQueue("FLT_1D25 EQU 1.25");
	AddLineQueue("FLT_1D5 EQU 1.5");
	AddLineQueue("FLT_2 EQU 2.0");
	AddLineQueue("FLT_2D25 EQU 2.25");
	AddLineQueue("FLT_2D5 EQU 2.5");
	AddLineQueue("FLT_3 EQU 3.0");
	AddLineQueue("FLT_3D25 EQU 3.25");
	AddLineQueue("FLT_3D5 EQU 3.5");
	AddLineQueue("FLT_4 EQU 4.0");
	AddLineQueue("FLT_4D25 EQU 4.25");
	AddLineQueue("FLT_4D5 EQU 4.5");
	AddLineQueue("FLT_5 EQU 5.0");
	AddLineQueue("FLT_5D25 EQU 5.25");
	AddLineQueue("FLT_5D5 EQU 5.5");
	AddLineQueue("FLT_6 EQU 6.0");
	AddLineQueue("FLT_6D25 EQU 6.25");
	AddLineQueue("FLT_6D5 EQU 6.5");
	AddLineQueue("FLT_7 EQU 7.0");
	AddLineQueue("FLT_7D25 EQU 7.25");
	AddLineQueue("FLT_7D5 EQU 7.5");
	AddLineQueue("FLT_8 EQU 8.0");
	AddLineQueue("FLT_8D25 EQU 8.25");
	AddLineQueue("FLT_8D5 EQU 8.5");
	AddLineQueue("FLT_9 EQU 9.0");
	AddLineQueue("FLT_9D25 EQU 9.25");
	AddLineQueue("FLT_9D5 EQU 9.5");
	AddLineQueue("FLT_10 EQU 10.0");
	AddLineQueue("FLT_11 EQU 11.0");
	AddLineQueue("FLT_12 EQU 12.0");
	AddLineQueue("FLT_13 EQU 13.0");
	AddLineQueue("FLT_14 EQU 14.0");
	AddLineQueue("FLT_15 EQU 15.0");
	AddLineQueue("FLT_16 EQU 16.0");
	AddLineQueue("FLT_17 EQU 17.0");
	AddLineQueue("FLT_18 EQU 18.0");
	AddLineQueue("FLT_19 EQU 19.0");
	AddLineQueue("FLT_20 EQU 20.0");
	AddLineQueue("FLT_21 EQU 21.0");
	AddLineQueue("FLT_22 EQU 22.0");
	AddLineQueue("FLT_23 EQU 23.0");
	AddLineQueue("FLT_24 EQU 24.0");
	AddLineQueue("FLT_24D5 EQU 24.5");
	AddLineQueue("FLT_25 EQU 25.0");
	AddLineQueue("FLT_26 EQU 26.0");
	AddLineQueue("FLT_27 EQU 27.0");
	AddLineQueue("FLT_28 EQU 28.0");
	AddLineQueue("FLT_29 EQU 29.0");
	AddLineQueue("FLT_30 EQU 30.0");
	AddLineQueue("FLT_31 EQU 31.0");
	AddLineQueue("FLT_32 EQU 32.0");
	AddLineQueue("FLT_33 EQU 33.0");
	AddLineQueue("FLT_34 EQU 34.0");
	AddLineQueue("FLT_35 EQU 35.0");
	AddLineQueue("FLT_36 EQU 36.0");
	AddLineQueue("FLT_37 EQU 37.0");
	AddLineQueue("FLT_38 EQU 38.0");
	AddLineQueue("FLT_39 EQU 39.0");
	AddLineQueue("FLT_40 EQU 40.0");
	AddLineQueue("FLT_41 EQU 41.0");
	AddLineQueue("FLT_42 EQU 42.0");
	AddLineQueue("FLT_43 EQU 43.0");
	AddLineQueue("FLT_44 EQU 44.0");
	AddLineQueue("FLT_45 EQU 45.0");
	AddLineQueue("FLT_46 EQU 46.0");
	AddLineQueue("FLT_47 EQU 47.0");
	AddLineQueue("FLT_48 EQU 48.0");
	AddLineQueue("FLT_49 EQU 49.0");
	AddLineQueue("FLT_50 EQU 50.0");
	AddLineQueue("FLT_51 EQU 51.0");
	AddLineQueue("FLT_52 EQU 52.0");
	AddLineQueue("FLT_53 EQU 53.0");
	AddLineQueue("FLT_54 EQU 54.0");
	AddLineQueue("FLT_55 EQU 55.0");
	AddLineQueue("FLT_56 EQU 56.0");
	AddLineQueue("FLT_57 EQU 57.0");
	AddLineQueue("FLT_58 EQU 58.0");
	AddLineQueue("FLT_59 EQU 59.0");
	AddLineQueue("FLT_60 EQU 60.0");
	AddLineQueue("FLT_61 EQU 61.0");
	AddLineQueue("FLT_62 EQU 62.0");
	AddLineQueue("FLT_63 EQU 63.0");
	AddLineQueue("FLT_64 EQU 64.0");
	AddLineQueue("FLT_65 EQU 65.0");
	AddLineQueue("FLT_66 EQU 66.0");
	AddLineQueue("FLT_67 EQU 67.0");
	AddLineQueue("FLT_68 EQU 68.0");
	AddLineQueue("FLT_69 EQU 69.0");
	AddLineQueue("FLT_70 EQU 70.0");
	AddLineQueue("FLT_71 EQU 71.0");
	AddLineQueue("FLT_72 EQU 72.0");
	AddLineQueue("FLT_73 EQU 73.0");
	AddLineQueue("FLT_74 EQU 74.0");
	AddLineQueue("FLT_75 EQU 75.0");
	AddLineQueue("FLT_76 EQU 76.0");
	AddLineQueue("FLT_77 EQU 77.0");
	AddLineQueue("FLT_78 EQU 78.0");
	AddLineQueue("FLT_79 EQU 79.0");
	AddLineQueue("FLT_80 EQU 80.0");
	AddLineQueue("FLT_81 EQU 81.0");
	AddLineQueue("FLT_82 EQU 82.0");
	AddLineQueue("FLT_83 EQU 83.0");
	AddLineQueue("FLT_84 EQU 84.0");
	AddLineQueue("FLT_85 EQU 85.0");
	AddLineQueue("FLT_86 EQU 86.0");
	AddLineQueue("FLT_87 EQU 87.0");
	AddLineQueue("FLT_88 EQU 88.0");
	AddLineQueue("FLT_89 EQU 89.0");
	AddLineQueue("FLT_90 EQU 90.0");
	AddLineQueue("FLT_91 EQU 91.0");
	AddLineQueue("FLT_92 EQU 92.0");
	AddLineQueue("FLT_93 EQU 93.0");
	AddLineQueue("FLT_94 EQU 94.0");
	AddLineQueue("FLT_95 EQU 95.0");
	AddLineQueue("FLT_96 EQU 96.0");
	AddLineQueue("FLT_97 EQU 97.0");
	AddLineQueue("FLT_98 EQU 98.0");
	AddLineQueue("FLT_99 EQU 99.0");
	AddLineQueue("FLT_100 EQU 100.0");
	AddLineQueue("FLT_125 EQU 125.0");
	AddLineQueue("FLT_126 EQU 126.0");
	AddLineQueue("FLT_127 EQU 127.0");
	AddLineQueue("FLT_128 EQU 128.0");
	AddLineQueue("FLT_140 EQU 140.0");
	AddLineQueue("FLT_145 EQU 145.0");
	AddLineQueue("FLT_150 EQU 150.0");
	AddLineQueue("FLT_180 EQU 180.0");
	AddLineQueue("FLT_253 EQU 253.0");
	AddLineQueue("FLT_254 EQU 254.0");
	AddLineQueue("FLT_255 EQU 255.0");
	AddLineQueue("FLT_256 EQU 256.0");
	AddLineQueue("FLT_360 EQU 360.0");
	AddLineQueue("FLT_511 EQU 511.0");
	AddLineQueue("FLT_512 EQU 512.0");
	AddLineQueue("FLT_513 EQU 513.0");
	AddLineQueue("FLT_1023 EQU 1023.0");
	AddLineQueue("FLT_1024 EQU 1024.0");
	AddLineQueue("FLT_1025 EQU 1025.0");

	AddLineQueue("FLT_32767 EQU 32767.0");
	AddLineQueue("FLT_32768 EQU 32768.0");
	AddLineQueue("FLT_65535 EQU 65535.0");
	AddLineQueue("FLT_65536 EQU 65536.0");
	AddLineQueue("FLT_2147483647 EQU 2147483647.0");
	AddLineQueue("FLT_2147483648 EQU 2147483648.0");
	AddLineQueue("FLT_4294967295 EQU 4294967295.0");
	AddLineQueue("FLT_4294967296 EQU 4294967296.0");

	AddLineQueue("FLT_NEG0 EQU (-0.0)");
	AddLineQueue("FLT_NEG0D0001 EQU (-0.0001)");
	AddLineQueue("FLT_NEG0D0002 EQU (-0.0002)");
	AddLineQueue("FLT_NEG0D0003 EQU (-0.0003)");
	AddLineQueue("FLT_NEG0D0004 EQU (-0.0004)");
	AddLineQueue("FLT_NEG0D0005 EQU (-0.0005)");
	AddLineQueue("FLT_NEG0D0006 EQU (-0.0006)");
	AddLineQueue("FLT_NEG0D0007 EQU (-0.0007)");
	AddLineQueue("FLT_NEG0D0008 EQU (-0.0008)");
	AddLineQueue("FLT_NEG0D0009 EQU (-0.0009)");
	AddLineQueue("FLT_NEG0D001 EQU (-0.001)");
	AddLineQueue("FLT_NEG0D002 EQU (-0.002)");
	AddLineQueue("FLT_NEG0D003 EQU (-0.003)");
	AddLineQueue("FLT_NEG0D004 EQU (-0.004)");
	AddLineQueue("FLT_NEG0D005 EQU (-0.005)");
	AddLineQueue("FLT_NEG0D006 EQU (-0.006)");
	AddLineQueue("FLT_NEG0D007 EQU (-0.007)");
	AddLineQueue("FLT_NEG0D008 EQU (-0.008)");
	AddLineQueue("FLT_NEG0D009 EQU (-0.009)");
	AddLineQueue("FLT_NEG0D01 EQU (-0.01)");
	AddLineQueue("FLT_NEG0D02 EQU (-0.02)");
	AddLineQueue("FLT_NEG0D025 EQU (-0.025)");
	AddLineQueue("FLT_NEG0D03 EQU (-0.03)");
	AddLineQueue("FLT_NEG0D04 EQU (-0.04)");
	AddLineQueue("FLT_NEG0D05 EQU (-0.05)");
	AddLineQueue("FLT_NEG0D06 EQU (-0.06)");
	AddLineQueue("FLT_NEG0D07 EQU (-0.07)");
	AddLineQueue("FLT_NEG0D08 EQU (-0.08)");
	AddLineQueue("FLT_NEG0D09 EQU (-0.09)");
	AddLineQueue("FLT_NEG0D1 EQU (-0.1)");
	AddLineQueue("FLT_NEG0D2 EQU (-0.2)");
	AddLineQueue("FLT_NEG0D25 EQU (-0.25)");
	AddLineQueue("FLT_NEG0D3 EQU (-0.3)");
	AddLineQueue("FLT_NEG0D4 EQU (-0.4)");
	AddLineQueue("FLT_NEG0D5 EQU (-0.5)");
	AddLineQueue("FLT_NEG0D6 EQU (-0.6)");
	AddLineQueue("FLT_NEG0D7 EQU (-0.7)");
	AddLineQueue("FLT_NEG0D8 EQU (-0.8)");
	AddLineQueue("FLT_NEG0D9 EQU (-0.9)");
	AddLineQueue("FLT_NEG1 EQU (-1.0)");
	AddLineQueue("FLT_NEG1D25 EQU (-1.25)");
	AddLineQueue("FLT_NEG2 EQU (-2.0)");
	AddLineQueue("FLT_NEG2D25 EQU (-2.25)");
	AddLineQueue("FLT_NEG3 EQU (-3.0)");
	AddLineQueue("FLT_NEG3D25 EQU (-3.25)");
	AddLineQueue("FLT_NEG4 EQU (-4.0)");
	AddLineQueue("FLT_NEG4D25 EQU (-4.25)");
	AddLineQueue("FLT_NEG5 EQU (-5.0)");
	AddLineQueue("FLT_NEG5D25 EQU (-5.25)");
	AddLineQueue("FLT_NEG6 EQU (-6.0)");
	AddLineQueue("FLT_NEG6D25 EQU (-6.25)");
	AddLineQueue("FLT_NEG7 EQU (-7.0)");
	AddLineQueue("FLT_NEG7D25 EQU (-7.25)");
	AddLineQueue("FLT_NEG8 EQU (-8.0)");
	AddLineQueue("FLT_NEG8D25 EQU (-8.25)");
	AddLineQueue("FLT_NEG9 EQU (-9.0)");
	AddLineQueue("FLT_NEG9D25 EQU (-9.25)");
	AddLineQueue("FLT_NEG10 EQU (-10.0)");
	AddLineQueue("FLT_NEG11 EQU (-11.0)");
	AddLineQueue("FLT_NEG12 EQU (-12.0)");
	AddLineQueue("FLT_NEG13 EQU (-13.0)");
	AddLineQueue("FLT_NEG14 EQU (-14.0)");
	AddLineQueue("FLT_NEG15 EQU (-15.0)");
	AddLineQueue("FLT_NEG16 EQU (-16.0)");
	AddLineQueue("FLT_NEG17 EQU (-17.0)");
	AddLineQueue("FLT_NEG18 EQU (-18.0)");
	AddLineQueue("FLT_NEG19 EQU (-19.0)");
	AddLineQueue("FLT_NEG20 EQU (-20.0)");
	AddLineQueue("FLT_NEG21 EQU (-21.0)");
	AddLineQueue("FLT_NEG22 EQU (-22.0)");
	AddLineQueue("FLT_NEG23 EQU (-23.0)");
	AddLineQueue("FLT_NEG24 EQU (-24.0)");
	AddLineQueue("FLT_NEG24D5 EQU (-24.5)");
	AddLineQueue("FLT_NEG25 EQU (-25.0)");
	AddLineQueue("FLT_NEG26 EQU (-26.0)");
	AddLineQueue("FLT_NEG27 EQU (-27.0)");
	AddLineQueue("FLT_NEG28 EQU (-28.0)");
	AddLineQueue("FLT_NEG29 EQU (-29.0)");
	AddLineQueue("FLT_NEG30 EQU (-30.0)");
	AddLineQueue("FLT_NEG31 EQU (-31.0)");
	AddLineQueue("FLT_NEG32 EQU (-32.0)");
	AddLineQueue("FLT_NEG33 EQU (-33.0)");
	AddLineQueue("FLT_NEG34 EQU (-34.0)");
	AddLineQueue("FLT_NEG35 EQU (-35.0)");
	AddLineQueue("FLT_NEG36 EQU (-36.0)");
	AddLineQueue("FLT_NEG37 EQU (-37.0)");
	AddLineQueue("FLT_NEG38 EQU (-38.0)");
	AddLineQueue("FLT_NEG39 EQU (-39.0)");
	AddLineQueue("FLT_NEG40 EQU (-40.0)");
	AddLineQueue("FLT_NEG41 EQU (-41.0)");
	AddLineQueue("FLT_NEG42 EQU (-42.0)");
	AddLineQueue("FLT_NEG43 EQU (-43.0)");
	AddLineQueue("FLT_NEG44 EQU (-44.0)");
	AddLineQueue("FLT_NEG45 EQU (-45.0)");
	AddLineQueue("FLT_NEG46 EQU (-46.0)");
	AddLineQueue("FLT_NEG47 EQU (-47.0)");
	AddLineQueue("FLT_NEG48 EQU (-48.0)");
	AddLineQueue("FLT_NEG49 EQU (-49.0)");
	AddLineQueue("FLT_NEG50 EQU (-50.0)");
	AddLineQueue("FLT_NEG51 EQU (-51.0)");
	AddLineQueue("FLT_NEG52 EQU (-52.0)");
	AddLineQueue("FLT_NEG53 EQU (-53.0)");
	AddLineQueue("FLT_NEG54 EQU (-54.0)");
	AddLineQueue("FLT_NEG55 EQU (-55.0)");
	AddLineQueue("FLT_NEG56 EQU (-56.0)");
	AddLineQueue("FLT_NEG57 EQU (-57.0)");
	AddLineQueue("FLT_NEG58 EQU (-58.0)");
	AddLineQueue("FLT_NEG59 EQU (-59.0)");
	AddLineQueue("FLT_NEG60 EQU (-60.0)");
	AddLineQueue("FLT_NEG61 EQU (-61.0)");
	AddLineQueue("FLT_NEG62 EQU (-62.0)");
	AddLineQueue("FLT_NEG63 EQU (-63.0)");
	AddLineQueue("FLT_NEG64 EQU (-64.0)");
	AddLineQueue("FLT_NEG65 EQU (-65.0)");
	AddLineQueue("FLT_NEG66 EQU (-66.0)");
	AddLineQueue("FLT_NEG67 EQU (-67.0)");
	AddLineQueue("FLT_NEG68 EQU (-68.0)");
	AddLineQueue("FLT_NEG69 EQU (-69.0)");
	AddLineQueue("FLT_NEG70 EQU (-70.0)");
	AddLineQueue("FLT_NEG71 EQU (-71.0)");
	AddLineQueue("FLT_NEG72 EQU (-72.0)");
	AddLineQueue("FLT_NEG73 EQU (-73.0)");
	AddLineQueue("FLT_NEG74 EQU (-74.0)");
	AddLineQueue("FLT_NEG75 EQU (-75.0)");
	AddLineQueue("FLT_NEG76 EQU (-76.0)");
	AddLineQueue("FLT_NEG77 EQU (-77.0)");
	AddLineQueue("FLT_NEG78 EQU (-78.0)");
	AddLineQueue("FLT_NEG79 EQU (-79.0)");
	AddLineQueue("FLT_NEG80 EQU (-80.0)");
	AddLineQueue("FLT_NEG81 EQU (-81.0)");
	AddLineQueue("FLT_NEG82 EQU (-82.0)");
	AddLineQueue("FLT_NEG83 EQU (-83.0)");
	AddLineQueue("FLT_NEG84 EQU (-84.0)");
	AddLineQueue("FLT_NEG85 EQU (-85.0)");
	AddLineQueue("FLT_NEG86 EQU (-86.0)");
	AddLineQueue("FLT_NEG87 EQU (-87.0)");
	AddLineQueue("FLT_NEG88 EQU (-88.0)");
	AddLineQueue("FLT_NEG89 EQU (-89.0)");
	AddLineQueue("FLT_NEG90 EQU (-90.0)");
	AddLineQueue("FLT_NEG91 EQU (-91.0)");
	AddLineQueue("FLT_NEG92 EQU (-92.0)");
	AddLineQueue("FLT_NEG93 EQU (-93.0)");
	AddLineQueue("FLT_NEG94 EQU (-94.0)");
	AddLineQueue("FLT_NEG95 EQU (-95.0)");
	AddLineQueue("FLT_NEG96 EQU (-96.0)");
	AddLineQueue("FLT_NEG97 EQU (-97.0)");
	AddLineQueue("FLT_NEG98 EQU (-98.0)");
	AddLineQueue("FLT_NEG99 EQU (-99.0)");
	AddLineQueue("FLT_NEG100 EQU (-100.0)");
	AddLineQueue("FLT_NEG125 EQU (-125.0)");
	AddLineQueue("FLT_NEG126 EQU (-126.0)");
	AddLineQueue("FLT_NEG127 EQU (-127.0)");
	AddLineQueue("FLT_NEG128 EQU (-128.0)");
	AddLineQueue("FLT_NEG140 EQU (-140.0)");
	AddLineQueue("FLT_NEG145 EQU (-145.0)");
	AddLineQueue("FLT_NEG150 EQU (-150.0)");
	AddLineQueue("FLT_NEG180 EQU (-180.0)");
	AddLineQueue("FLT_NEG253 EQU (-253.0)");
	AddLineQueue("FLT_NEG254 EQU (-254.0)");
	AddLineQueue("FLT_NEG255 EQU (-255.0)");
	AddLineQueue("FLT_NEG256 EQU (-256.0)");
	AddLineQueue("FLT_NEG360 EQU (-360.0)");
	AddLineQueue("FLT_NEG511 EQU (-511.0)");
	AddLineQueue("FLT_NEG512 EQU (-512.0)");
	AddLineQueue("FLT_NEG513 EQU (-513.0)");
	AddLineQueue("FLT_NEG1023 EQU (-1023.0)");
	AddLineQueue("FLT_NEG1024 EQU (-1024.0)");
	AddLineQueue("FLT_NEG1025 EQU (-1025.0)");

	AddLineQueue("FLT_NEG32767 EQU (-32767.0)");
	AddLineQueue("FLT_NEG32768 EQU (-32768.0)");
	AddLineQueue("FLT_NEG65535 EQU (-65535.0)");
	AddLineQueue("FLT_NEG65536 EQU (-65536.0)");
	AddLineQueue("FLT_NEG2147483647 EQU (-2147483647.0)");
	AddLineQueue("FLT_NEG2147483648 EQU (-2147483648.0)");
	AddLineQueue("FLT_NEG4294967295 EQU (-4294967295.0)");
	AddLineQueue("FLT_NEG4294967296 EQU (-4294967296.0)");

	AddLineQueue("FLT_BIN128 EQU FLT_128_MSK");
	AddLineQueue("FLT_BINNEG150 EQU FLT_NEG150_MSK");

	AddLineQueue("FLT_MAXRAND EQU FLT_32767");

	AddLineQueue("FLT_MAXI8 EQU 127.0");
	AddLineQueue("FLT_MINI8 EQU (-128.0)");
	AddLineQueue("FLT_MAXU8 EQU 255.0");
	AddLineQueue("FLT_MINU8 EQU 0.0");

	AddLineQueue("FLT_MAXI16 EQU 32767.0");
	AddLineQueue("FLT_MINI16 EQU (-32768.0)");
	AddLineQueue("FLT_MAXU16 EQU 65535.0");
	AddLineQueue("FLT_MINU16 EQU 0.0");

	AddLineQueue("FLT_MAXI32 EQU 2147483647.0");
	AddLineQueue("FLT_MINI32 EQU (-2147483648.0)");
	AddLineQueue("FLT_MAXU32 EQU 4294967295.0");
	AddLineQueue("FLT_MINU32 EQU 0.0");

	AddLineQueue("FLT_MAXI8XU8 EQU 32768.0");
	AddLineQueue("FLT_MINI8XU8 EQU (-32768.0)");
	AddLineQueue("FLT_MAXI8XU16 EQU 8388608.0");
	AddLineQueue("FLT_MINI8XU16 EQU (-8388608.0)");

	AddLineQueue("FLT_MAXI16XU16 EQU 2147483648.0");
	AddLineQueue("FLT_MINI16XU16 EQU (-2147483648.0)");

	AddLineQueue("FLT_FIXUNSIGNED EQU 2147483648.0");
	AddLineQueue("FLT_FIXUNSIGNED32 EQU 2147483648.0");
	AddLineQueue("FLT_FIXMAXI32 EQU 2147483520.0");
	AddLineQueue("FLT_FIXMAXU32 EQU 4294967040.0");

	AddLineQueue("FLT_RCPI16 EQU 3.0518509475997192297128208258309e-5");
	AddLineQueue("FLT_RCPU16 EQU 0.0000152587890625");
	AddLineQueue("FLT_RCPI16XU16 EQU 4.656754985961485641041291543321e-10");

	AddLineQueue("FLT_FIXAA8 EQU FLT_0");
	AddLineQueue("FLT_FIXR8 EQU FLT_0");
	AddLineQueue("FLT_FIXG8 EQU FLT_0");
	AddLineQueue("FLT_FIXB8 EQU FLT_2147483648");

	AddLineQueue("FLT_NORMA8 EQU 5.983838848039216e-8");
	AddLineQueue("FLT_NORMR8 EQU 1.531862745098039e-5");
	AddLineQueue("FLT_NORMG8 EQU 0.003921568627451");
	AddLineQueue("FLT_NORMB8 EQU 2.337437050015319e-10");

	AddLineQueue("FLT_FIXAA2 EQU (-512.0)");
	AddLineQueue("FLT_FIXB10 EQU (-524288.0)");
	AddLineQueue("FLT_FIXG10 EQU (-536870912.0)");
	AddLineQueue("FLT_FIXR10 EQU FLT_2147483648");

	AddLineQueue("FLT_NORMA2 EQU 0.0019569471624266");
	AddLineQueue("FLT_NORMB10 EQU 1.911081213307241e-6");
	AddLineQueue("FLT_NORMG10 EQU 1.866290247370352e-9");
	AddLineQueue("FLT_NORMR10 EQU 3.104408582051595e-10");

	AddLineQueue("FLT_MG EQU 1024.0");
	AddLineQueue("FLT_NEGMG EQU (-1024.0)");
	AddLineQueue("FLT_HALFMG EQU 512.0");
	AddLineQueue("FLT_NEGHALFMG EQU (-512.0)");
	AddLineQueue("FLT_MGDIV4 EQU 256.0");
	AddLineQueue("FLT_NEGMGDIV4 EQU (-256.0)");
	AddLineQueue("FLT_HALFMGXMG EQU 524288.0");
	AddLineQueue("FLT_HALFMGXSQRMG EQU 536870912.0");
	AddLineQueue("FLT_HALFMGXCUBEMG EQU 549755813888.0");
	AddLineQueue("FLT_NEGHALFMGXMG EQU (-524288.0)");
	AddLineQueue("FLT_NEGHALFMGXSQRMG EQU (-536870912.0)");
	AddLineQueue("FLT_NEGHALFMGXCUBEMG EQU (-549755813888.0)");
	AddLineQueue("FLT_SQRMG EQU 1048576.0");
	AddLineQueue("FLT_CUBEMG EQU 1073741824.0");
	AddLineQueue("FLT_SQRTMG EQU 32.0");
	AddLineQueue("FLT_CBRTMG EQU 10.0793683991589853181");
	AddLineQueue("FLT_RCPMG EQU 0.0009765625");
	AddLineQueue("FLT_RCPSQRMG EQU 0.00000095367431640625");
	AddLineQueue("FLT_RCPCUBEMG EQU 0.00000000093132257462");
	AddLineQueue("FLT_RCPSQRTMG EQU 0.03125");
	AddLineQueue("FLT_RCPCBRTMG EQU 0.09921256574801246717");

	AddLineQueue("FLT_2MG EQU 2048.0");
	AddLineQueue("FLT_NEG2MG EQU (-2048.0)");
	AddLineQueue("FLT_SQR2MG EQU 4194304.0");
	AddLineQueue("FLT_CUBE2MG EQU 8589934592.0");
	AddLineQueue("FLT_SQRT2MG EQU 45.25483399593904156165403917471");
	AddLineQueue("FLT_CBRT2MG EQU 12.699208415745595798013645114178");
	AddLineQueue("FLT_4MG EQU 4096.0");
	AddLineQueue("FLT_NEG4MG EQU (-4096.0)");
	AddLineQueue("FLT_SQR4MG EQU 16777216.0");
	AddLineQueue("FLT_CUBE4MG EQU 68719476736.0");
	AddLineQueue("FLT_SQRT4MG EQU 64.0");
	AddLineQueue("FLT_CBRT4MG EQU 16.0");
	AddLineQueue("FLT_RCP2MG EQU 0.00048828125");
	AddLineQueue("FLT_RCP4MG EQU 0.000244140625");

	AddLineQueue("FLT_E EQU 2.71828182845904523536");
	AddLineQueue("FLT_EXP EQU 2.71828182845904523536");
	AddLineQueue("FLT_LOGE EQU 0.434294481903251827651");
	AddLineQueue("FLT_LOGEHIGH EQU 0.434294481903251827651");
	AddLineQueue("FLT_LOG2E EQU 1.44269504088896340736");
	AddLineQueue("FLT_LOG2EHIGH EQU 1.44269504088896340736");
	AddLineQueue("FLT_LOG10E EQU 0.434294481903251827651");
	AddLineQueue("FLT_RCPLOG2E EQU 0.693147180559945309417");
	AddLineQueue("FLT_RCPLOG10E EQU 2.30258509299404568402");
	AddLineQueue("FLT_LOG2T EQU 3.3219280948873622");
	AddLineQueue("FLT_LOG2 EQU 0.301029995663981195214");
	AddLineQueue("FLT_LOG2HIGH EQU 0.301029995663981195214");
	AddLineQueue("FLT_LN2 EQU 0.693147180559945309417");
	AddLineQueue("FLT_LN2HIGH EQU 0.693147180559945309417");
	AddLineQueue("FLT_1DIVLN2 EQU 1.44269504088896340736");
	AddLineQueue("FLT_2DIVLN2 EQU 2.88539008177792681472");
	AddLineQueue("FLT_LNT EQU 2.3025850929940459");
	AddLineQueue("FLT_LNTHIGH EQU 2.3025850929940459");
	AddLineQueue("FLT_LN10 EQU 2.302585092994045684018");
	AddLineQueue("FLT_SQRT2 EQU 1.414213562373095048802");
	AddLineQueue("FLT_RCPSQRT2 EQU 0.707106781186547524401");
	AddLineQueue("FLT_SQRT2DIV2 EQU 0.707106781186547524401");
	AddLineQueue("FLT_SQRT2DIV2HIGH EQU 0.707106781186547524401");
	AddLineQueue("FLT_SQRT2DIV2LOW EQU 1.210161749e-08");
	AddLineQueue("FLT_SQRTHALF EQU 0.707106781186547524401");
	AddLineQueue("FLT_SQRTHALFHIGH EQU 0.707106781186547524401");
	AddLineQueue("FLT_SQRTHALFLOW EQU 1.210161749e-08");
	AddLineQueue("FLT_POW2 EQU 7.389056098930650227230");
	AddLineQueue("FLT_RCPPOW2 EQU 0.135335283236612691893");
	AddLineQueue("FLT_CBRT2 EQU 1.259921049894873164767");
	AddLineQueue("FLT_RCPCBRT2 EQU 0.793700525984099737375");
	AddLineQueue("FLT_1DIV3 EQU 0.333333333333333333333");
	AddLineQueue("FLT_1DIV7 EQU 0.142857142857142857142");
	AddLineQueue("FLT_1DIV9 EQU 0.111111111111111111111");
	AddLineQueue("FLT_2DIV3 EQU 0.666666666666666666667");
	AddLineQueue("FLT_2DIV7 EQU 0.285714285714285714285");
	AddLineQueue("FLT_2DIV9 EQU 0.222222222222222222222");
	AddLineQueue("FLT_4DIV3 EQU 1.333333333333333333333");
	AddLineQueue("FLT_4DIV7 EQU 0.571428571428571428571");
	AddLineQueue("FLT_4DIV9 EQU 0.444444444444444444444");

	AddLineQueue("FLT_PI EQU 3.14159265358979323846");
	AddLineQueue("FLT_PIHIGH EQU 3.14159265358979323846");
	AddLineQueue("FLT_HALFPI EQU 1.57079632679489661923");
	AddLineQueue("FLT_2PI EQU 6.28318530717958647692");
	AddLineQueue("FLT_NEGPI EQU (-3.14159265358979323846)");
	AddLineQueue("FLT_NEGHALFPI EQU (-1.57079632679489661923)");
	AddLineQueue("FLT_NEG2PI EQU (-6.28318530717958647692)");
	AddLineQueue("FLT_RCPPI EQU 0.31830988618379067154");
	AddLineQueue("FLT_INVPI EQU 0.31830988618379067154");
	AddLineQueue("FLT_RCP2PI EQU 0.15915494309189533577");
	AddLineQueue("FLT_INV2PI EQU 0.15915494309189533577");
	AddLineQueue("FLT_PIDIV2 EQU 1.57079632679489661923");
	AddLineQueue("FLT_PIDIV2HIGH EQU 1.57079632679489661923");
	AddLineQueue("FLT_PIDIV4 EQU 0.78539816339744830962");
	AddLineQueue("FLT_PIDIV4HIGH EQU 0.78539816339744830962");
	AddLineQueue("FLT_PIX3DIV4 EQU 2.35619449019234492884");
	AddLineQueue("FLT_SQRTPI EQU 1.77245385090551602729");
	AddLineQueue("FLT_SQRT2PI EQU 2.50662827463100050242");
	AddLineQueue("FLT_SQRT2PIHIGH EQU 2.50662827463100050242");
	AddLineQueue("FLT_RCPSQRTPI EQU 0.56418958354775628695");
	AddLineQueue("FLT_RCPSQRT2PI EQU 0.39894228040143267794");
	AddLineQueue("FLT_SQRTPIDIV2 EQU 0.88622692545275801365");
	AddLineQueue("FLT_SQRTPIDIV2HIGH EQU 0.88622692545275801365");
	AddLineQueue("FLT_SQRT2PIDIV2 EQU 1.25331413731550025121");
	AddLineQueue("FLT_SQRT2PIDIV2HIGH EQU 1.25331413731550025121");
	AddLineQueue("FLT_2DIVPI EQU 0.63661977236758134308");
	AddLineQueue("FLT_2DIV2PI EQU 0.31830988618379067154");
	AddLineQueue("FLT_2DIVSQRTPI EQU 1.12837916709551257389");
	AddLineQueue("FLT_2DIVSQRT2PI EQU 0.79788456080286535588");
	AddLineQueue("FLT_SQRT2DIVPI EQU 0.45015815807855303477");
	AddLineQueue("FLT_LOGPI EQU 0.49714987269413385435");
	AddLineQueue("FLT_LOG2PI EQU 0.79817986835811504957");
	AddLineQueue("FLT_LNPI EQU 1.14472988584940017415");
	AddLineQueue("FLT_LN2PI EQU 1.83787706640934548356");
	AddLineQueue("FLT_POWPI EQU 23.1406926327792690057");
	AddLineQueue("FLT_RCPPOWPI EQU 0.04321391826377224977");
	AddLineQueue("FLT_POW2PI EQU 535.491655524764736503");
	AddLineQueue("FLT_RCPPOW2PI EQU 0.00186744273170798881");
	AddLineQueue("FLT_CBRTPI EQU 1.46459188756152326302");
	AddLineQueue("FLT_RCPCBRTPI EQU 0.68278406325529568148");
	AddLineQueue("FLT_CBRT2PI EQU 1.84527014864402841910");
	AddLineQueue("FLT_RCPCBRT2PI EQU 0.54192607013928900874");

	AddLineQueue("FLT_POW2TOM126 EQU 1.175494351e-38");
	AddLineQueue("FLT_POW2TO126 EQU 8.507059173e37");
	AddLineQueue("FLT_NORMHUGE EQU 3.402823466e38");
	AddLineQueue("FLT_POW2TO23 EQU 8388608.0");
	AddLineQueue("FLT_POW2TO24 EQU 16777216.0");
	AddLineQueue("FLT_MAXI32POW2TO23 EQU 2139095039.0");
	AddLineQueue("FLT_POW2TO31 EQU 2147483648.0");
	AddLineQueue("FLT_POW2TO32 EQU 4294967296.0");

	AddLineQueue("FLT_REMQUOBITS EQU 3");
	AddLineQueue("FLT_REMQUOMASK EQU (~((~0)<<FLT_REMQUOBITS))");

	AddLineQueue("FLT_TRIGPLOSS EQU 105615.0");

	AddLineQueue("FLT_DEGTORAD EQU 0.017453292519943295769");
	AddLineQueue("FLT_RADTODEG EQU 57.29577951308232087679");

	AddLineQueue("FLT_DEGTOGRAD EQU 1.111111111111111111111");
	AddLineQueue("FLT_GRADTODEG EQU 0.9");

	AddLineQueue("FLT_RADTOGRAD EQU 63.66197723675813430755");
	AddLineQueue("FLT_GRADTORAD EQU 0.015707963267948966192");

	AddLineQueue("FLT_SUNGRAVITY EQU 274.13");
	AddLineQueue("FLT_JUPITERGRAVITY EQU 25.95");
	AddLineQueue("FLT_NEPTUNEGRAVITY EQU 14.07");
	AddLineQueue("FLT_SATURNGRAVITY EQU 11.08");
	AddLineQueue("FLT_URANUSGRAVITY EQU 10.67");
	AddLineQueue("FLT_EARTHGRAVITY EQU 9.81");
	AddLineQueue("FLT_VENUSGRAVITY EQU 8.87");
	AddLineQueue("FLT_MARSGRAVITY EQU 3.77");
	AddLineQueue("FLT_MERCURYGRAVITY EQU 3.59");
	AddLineQueue("FLT_MOONGRAVITY EQU 1.62");
	AddLineQueue("FLT_PLUTOGRAVITY EQU 0.42");

	AddLineQueue("FLT_KMTOINCH EQU 39370.08");
	AddLineQueue("FLT_KMTOFEET EQU 3280.84");
	AddLineQueue("FLT_KMTOYARDS EQU 1093.613");
	AddLineQueue("FLT_KMTOMILES EQU 0.000621371");

	AddLineQueue("FLT_METOINCH EQU 39.37008");
	AddLineQueue("FLT_METOFEET EQU 3.28084");
	AddLineQueue("FLT_METOYARDS EQU 1.093613");
	AddLineQueue("FLT_METOMILES EQU 0.000621371");

	AddLineQueue("FLT_CMTOINCH EQU 0.3937008");
	AddLineQueue("FLT_CMTOFEET EQU 0.0328084");
	AddLineQueue("FLT_CMTOYARDS EQU 0.01093613");
	AddLineQueue("FLT_CMTOMILES EQU 0.00000621371");

	AddLineQueue("FLT_MILLTOINCH EQU 0.03937008");
	AddLineQueue("FLT_MILLTOFEET EQU 0.00328084");
	AddLineQueue("FLT_MILLTOYARDS EQU 0.001093613");
	AddLineQueue("FLT_MILLTOMILES EQU 0.000000621371");

	AddLineQueue("FLT_INCHTOMILL EQU 25.4");
	AddLineQueue("FLT_INCHTOCM EQU 2.54");
	AddLineQueue("FLT_INCHTOME EQU 0.0254");
	AddLineQueue("FLT_INCHTOKM EQU 0.0000254");
	AddLineQueue("FLT_INCHTOFEET EQU 0.083333");
	AddLineQueue("FLT_INCHTOYARDS EQU 0.027778");
	AddLineQueue("FLT_INCHTOMILES EQU 0.000016");

	AddLineQueue("FLT_FEETTOMILL EQU 304.8");
	AddLineQueue("FLT_FEETTOCM EQU 30.48");
	AddLineQueue("FLT_FEETTOME EQU 0.3048");
	AddLineQueue("FLT_FEETTOKM EQU 0.0003048");
	AddLineQueue("FLT_FEETTOINCH EQU 12.0");
	AddLineQueue("FLT_FEETTOYARDS EQU 0.333333");
	AddLineQueue("FLT_FEETTOMILES EQU 0.000189");

	AddLineQueue("FLT_YARDSTOMILL EQU 914.4");
	AddLineQueue("FLT_YARDSTOCM EQU 91.44");
	AddLineQueue("FLT_YARDSTOME EQU 0.9144");
	AddLineQueue("FLT_YARDSTOKM EQU 0.0009144");
	AddLineQueue("FLT_YARDSTOINCH EQU 36.0");
	AddLineQueue("FLT_YARDSTOFEET EQU 3.0");
	AddLineQueue("FLT_YARDSTOMILES EQU 0.000568");

	AddLineQueue("FLT_MILESTOMILL EQU 1609344.0");
	AddLineQueue("FLT_MILESTOCM EQU 160934.4");
	AddLineQueue("FLT_MILESTOME EQU 1609.344");
	AddLineQueue("FLT_MILESTOKM EQU 1.609344");
	AddLineQueue("FLT_MILESTOINCH EQU 63360.0");
	AddLineQueue("FLT_MILESTOFEET EQU 5280.0");
	AddLineQueue("FLT_MILESTOYARDS EQU 1760.0");

	AddLineQueue("FLT_KMPHTOMEPS EQU 0.27777777777778");
	AddLineQueue("FLT_KMPHTOKMPS EQU 0.00027777777777778");
	AddLineQueue("FLT_KMPHTOMEPM EQU 16.666666666667");
	AddLineQueue("FLT_KMPHTOMILESPH EQU 0.62137119223733");
	AddLineQueue("FLT_KMPHTOMILESPS EQU 0.00017260310895481");
	AddLineQueue("FLT_KMPHTOFOOTPS EQU 0.91134444444444");
	AddLineQueue("FLT_KMPHTOFOOTPM EQU 54.680666666667");

	AddLineQueue("FLT_KMPSTOMEPS EQU 1000.0");
	AddLineQueue("FLT_KMPSTOKMPH EQU 3600.0");
	AddLineQueue("FLT_KMPSTOMEPM EQU 60000.0");
	AddLineQueue("FLT_KMPSTOMILESPH EQU 2236.9362920544");
	AddLineQueue("FLT_KMPSTOMILESPS EQU 0.62137119223733");
	AddLineQueue("FLT_KMPSTOFOOTPS EQU 3280.84");
	AddLineQueue("FLT_KMPSTOFOOTPM EQU 196850.4");

	AddLineQueue("FLT_MEPSTOKMPH EQU 3.6");
	AddLineQueue("FLT_MEPSTOKMPS EQU 0.001");
	AddLineQueue("FLT_MEPSTOMEPM EQU 60.0");
	AddLineQueue("FLT_MEPSTOMILESPH EQU 2.2369362920544");
	AddLineQueue("FLT_MEPSTOMILESPS EQU 0.00062137119223733");
	AddLineQueue("FLT_MEPSTOFOOTPS EQU 3.28084");
	AddLineQueue("FLT_MEPSTOFOOTPM EQU 196.8504");

	AddLineQueue("FLT_MEPMTOKMPH EQU 0.06");
	AddLineQueue("FLT_MEPMTOKMPS EQU 1.6666666666667e-5");
	AddLineQueue("FLT_MEPMTOMEPS EQU 0.016666666666667");
	AddLineQueue("FLT_MEPMTOMILESPH EQU 0.03728227153424");
	AddLineQueue("FLT_MEPMTOMILESPS EQU 1.0356186537289e-5");
	AddLineQueue("FLT_MEPMTOFOOTPS EQU 0.054680666666667");
	AddLineQueue("FLT_MEPMTOFOOTPM EQU 3.28084");

	AddLineQueue("FLT_MILESPHTOKMPH EQU 1.609344");
	AddLineQueue("FLT_MILESPHTOKMPS EQU 0.00044704");
	AddLineQueue("FLT_MILESPHTOMEPS EQU 0.44704");
	AddLineQueue("FLT_MILESPHTOMEPM EQU 26.8224");
	AddLineQueue("FLT_MILESPHTOMILESPS EQU 0.00027777777777778");
	AddLineQueue("FLT_MILESPHTOFOOTPS EQU 1.4666667136");
	AddLineQueue("FLT_MILESPHTOFOOTPM EQU 88.000002816");

	AddLineQueue("FLT_MILESPSTOKMPH EQU 5793.6384");
	AddLineQueue("FLT_MILESPSTOKMPS EQU 1.609344");
	AddLineQueue("FLT_MILESPSTOMEPS EQU 1609.344");
	AddLineQueue("FLT_MILESPSTOMEPM EQU 96560.64");
	AddLineQueue("FLT_MILESPSTOMILESPM EQU 3600.0");
	AddLineQueue("FLT_MILESPSTOFOOTPS EQU 5280.00016896");
	AddLineQueue("FLT_MILESPSTOFOOTPM EQU 316800.0101376");

	AddLineQueue("FLT_FOOTPSTOKMPH EQU 1.097279964887");
	AddLineQueue("FLT_FOOTPSTOKMPS EQU 0.0003047999902464");
	AddLineQueue("FLT_FOOTPSTOMEPS EQU 0.3047999902464");
	AddLineQueue("FLT_FOOTPSTOMEPM EQU 18.287999414784");
	AddLineQueue("FLT_FOOTPSTOMILESPH EQU 0.68181816");
	AddLineQueue("FLT_FOOTPSTOMILESPS EQU 0.00018939393333333");
	AddLineQueue("FLT_FOOTPSTOFOOTPM EQU 60.0");

	AddLineQueue("FLT_FOOTPMTOKMPH EQU 0.018287999414784");
	AddLineQueue("FLT_FOOTPMTOKMPS EQU 5.07999983744e-6");
	AddLineQueue("FLT_FOOTPMTOMEPS EQU 0.00507999983744");
	AddLineQueue("FLT_FOOTPMTOMEPM EQU 0.3047999902464");
	AddLineQueue("FLT_FOOTPMTOMILESPH EQU 0.011363636");
	AddLineQueue("FLT_FOOTPMTOMILESPS EQU 3.1565655555556e-6");
	AddLineQueue("FLT_FOOTPMTOFOOTPS EQU 0.016666666666667");

	AddLineQueue("FLT_SOUNDSPEEDP50C EQU 360.35");
	AddLineQueue("FLT_SOUNDSPEEDP45C EQU 357.551");
	AddLineQueue("FLT_SOUNDSPEEDP40C EQU 354.73");
	AddLineQueue("FLT_SOUNDSPEEDP35C EQU 351.887");
	AddLineQueue("FLT_SOUNDSPEEDP30C EQU 349.02");
	AddLineQueue("FLT_SOUNDSPEEDP25C EQU 346.13");
	AddLineQueue("FLT_SOUNDSPEEDP20C EQU 343.216");
	AddLineQueue("FLT_SOUNDSPEEDP15C EQU 340.276");
	AddLineQueue("FLT_SOUNDSPEEDP10C EQU 337.311");
	AddLineQueue("FLT_SOUNDSPEEDP5C EQU 334.319");
	AddLineQueue("FLT_SOUNDSPEED0C EQU 331.301");
	AddLineQueue("FLT_SOUNDSPEEDN5C EQU 328.255");
	AddLineQueue("FLT_SOUNDSPEEDN10C EQU 325.18");
	AddLineQueue("FLT_SOUNDSPEEDN15C EQU 322.076");
	AddLineQueue("FLT_SOUNDSPEEDN20C EQU 318.942");
	AddLineQueue("FLT_SOUNDSPEEDN25C EQU 315.776");
	AddLineQueue("FLT_SOUNDSPEEDN30C EQU 312.579");
	AddLineQueue("FLT_SOUNDSPEEDN35C EQU 309.348");
	AddLineQueue("FLT_SOUNDSPEEDN40C EQU 306.083");
	AddLineQueue("FLT_SOUNDSPEEDN45C EQU 302.784");
	AddLineQueue("FLT_SOUNDSPEEDN50C EQU 299.447");

	AddLineQueue("FLT_SCHSCALE EQU FLT_1DIVLN2");
	AddLineQueue("FLT_THSCALE EQU FLT_2DIVLN2");

	AddLineQueue("FLT_EXPEST1 EQU (-6.93147182e-1)");
	AddLineQueue("FLT_EXPEST2 EQU (+2.40226462e-1)");
	AddLineQueue("FLT_EXPEST3 EQU (-5.55036440e-2)");
	AddLineQueue("FLT_EXPEST4 EQU (+9.61597636e-3)");
	AddLineQueue("FLT_EXPEST5 EQU (-1.32823968e-3)");
	AddLineQueue("FLT_EXPEST6 EQU (+1.47491097e-4)");
	AddLineQueue("FLT_EXPEST7 EQU (-1.08635004e-5)");
	AddLineQueue("FLT_LOGEST0 EQU (+1.442693)");
	AddLineQueue("FLT_LOGEST1 EQU (-0.721242)");
	AddLineQueue("FLT_LOGEST2 EQU (+0.479384)");
	AddLineQueue("FLT_LOGEST3 EQU (-0.350295)");
	AddLineQueue("FLT_LOGEST4 EQU (+0.248590)");
	AddLineQueue("FLT_LOGEST5 EQU (-0.145700)");
	AddLineQueue("FLT_LOGEST6 EQU (+0.057148)");
	AddLineQueue("FLT_LOGEST7 EQU (-0.010578)");
	
	/*double mask*/
	AddLineQueue("DBL_1LSHL3_MSK EQU 0x0000000000000008");
	AddLineQueue("DBL_1LSHL4_MSK EQU 0x0000000000000010");
	AddLineQueue("DBL_1LSHL7_MSK EQU 0x0000000000000080");
	AddLineQueue("DBL_1LSHL8_MSK EQU 0x0000000000000100");
	AddLineQueue("DBL_1LSHL11_MSK EQU 0x0000000000000800");
	AddLineQueue("DBL_1LSHL12_MSK EQU 0x0000000000001000");
	AddLineQueue("DBL_1LSHL15_MSK EQU 0x0000000000008000");
	AddLineQueue("DBL_1LSHL16_MSK EQU 0x0000000000010000");
	AddLineQueue("DBL_1LSHL19_MSK EQU 0x0000000000080000");
	AddLineQueue("DBL_1LSHL20_MSK EQU 0x0000000000100000");
	AddLineQueue("DBL_1LSHL23_MSK EQU 0x0000000000800000");
	AddLineQueue("DBL_1LSHL24_MSK EQU 0x0000000001000000");
	AddLineQueue("DBL_1LSHL27_MSK EQU 0x0000000008000000");
	AddLineQueue("DBL_1LSHL28_MSK EQU 0x0000000010000000");
	AddLineQueue("DBL_1LSHL31_MSK EQU 0x0000000080000000");
	AddLineQueue("DBL_1LSHL32_MSK EQU 0x0000000100000000");
	AddLineQueue("DBL_1LSHL35_MSK EQU 0x0000000800000000");
	AddLineQueue("DBL_1LSHL36_MSK EQU 0x0000001000000000");
	AddLineQueue("DBL_1LSHL39_MSK EQU 0x0000008000000000");
	AddLineQueue("DBL_1LSHL40_MSK EQU 0x0000010000000000");
	AddLineQueue("DBL_1LSHL43_MSK EQU 0x0000080000000000");
	AddLineQueue("DBL_1LSHL44_MSK EQU 0x0000100000000000");
	AddLineQueue("DBL_1LSHL47_MSK EQU 0x0000800000000000");
	AddLineQueue("DBL_1LSHL48_MSK EQU 0x0001000000000000");
	AddLineQueue("DBL_1LSHL51_MSK EQU 0x0008000000000000");
	AddLineQueue("DBL_1LSHL52_MSK EQU 0x0010000000000000");
	AddLineQueue("DBL_1LSHL55_MSK EQU 0x0080000000000000");
	AddLineQueue("DBL_1LSHL56_MSK EQU 0x0100000000000000");
	AddLineQueue("DBL_1LSHL59_MSK EQU 0x0800000000000000");
	AddLineQueue("DBL_1LSHL60_MSK EQU 0x1000000000000000");
	AddLineQueue("DBL_1LSHL63_MSK EQU 0x8000000000000000");

	AddLineQueue("DBL_NEG1LSHL3_MSK EQU 0xfffffffffffffff8");
	AddLineQueue("DBL_NEG1LSHL4_MSK EQU 0xfffffffffffffff0");
	AddLineQueue("DBL_NEG1LSHL7_MSK EQU 0xffffffffffffff80");
	AddLineQueue("DBL_NEG1LSHL8_MSK EQU 0xffffffffffffff00");
	AddLineQueue("DBL_NEG1LSHL11_MSK EQU 0xfffffffffffff800");
	AddLineQueue("DBL_NEG1LSHL12_MSK EQU 0xfffffffffffff000");
	AddLineQueue("DBL_NEG1LSHL15_MSK EQU 0xffffffffffff8000");
	AddLineQueue("DBL_NEG1LSHL16_MSK EQU 0xffffffffffff0000");
	AddLineQueue("DBL_NEG1LSHL19_MSK EQU 0xfffffffffff80000");
	AddLineQueue("DBL_NEG1LSHL20_MSK EQU 0xfffffffffff00000");
	AddLineQueue("DBL_NEG1LSHL23_MSK EQU 0xffffffffff800000");
	AddLineQueue("DBL_NEG1LSHL24_MSK EQU 0xffffffffff000000");
	AddLineQueue("DBL_NEG1LSHL27_MSK EQU 0xfffffffff8000000");
	AddLineQueue("DBL_NEG1LSHL28_MSK EQU 0xfffffffff0000000");
	AddLineQueue("DBL_NEG1LSHL31_MSK EQU 0xffffffff80000000");
	AddLineQueue("DBL_NEG1LSHL32_MSK EQU 0xffffffff00000000");
	AddLineQueue("DBL_NEG1LSHL35_MSK EQU 0xfffffff800000000");
	AddLineQueue("DBL_NEG1LSHL36_MSK EQU 0xfffffff000000000");
	AddLineQueue("DBL_NEG1LSHL39_MSK EQU 0xffffff8000000000");
	AddLineQueue("DBL_NEG1LSHL40_MSK EQU 0xffffff0000000000");
	AddLineQueue("DBL_NEG1LSHL43_MSK EQU 0xfffff80000000000");
	AddLineQueue("DBL_NEG1LSHL44_MSK EQU 0xfffff00000000000");
	AddLineQueue("DBL_NEG1LSHL47_MSK EQU 0xffff800000000000");
	AddLineQueue("DBL_NEG1LSHL48_MSK EQU 0xffff000000000000");
	AddLineQueue("DBL_NEG1LSHL51_MSK EQU 0xfff8000000000000");
	AddLineQueue("DBL_NEG1LSHL52_MSK EQU 0xfff0000000000000");
	AddLineQueue("DBL_NEG1LSHL55_MSK EQU 0xff80000000000000");
	AddLineQueue("DBL_NEG1LSHL56_MSK EQU 0xff00000000000000");
	AddLineQueue("DBL_NEG1LSHL59_MSK EQU 0xf800000000000000");
	AddLineQueue("DBL_NEG1LSHL60_MSK EQU 0xf000000000000000");
	AddLineQueue("DBL_NEG1LSHL63_MSK EQU 0x8000000000000000");

	AddLineQueue("DBL_FALSE_MSK EQU 0x0000000000000000");
	AddLineQueue("DBL_TRUE_MSK EQU 0xffffffffffffffff");
	AddLineQueue("DBL_ERROR_MSK EQU DBL_ERROR");

	AddLineQueue("DBL_MAGIC_MSK EQU 0x4330000000000000");
	AddLineQueue("DBL_SIGN_MSK EQU 0x8000000000000000");
	AddLineQueue("DBL_INVSIGN_MSK EQU 0x7fffffffffffffff");

	AddLineQueue("DBL_INF_MSK EQU 0x7ff0000000000000");
	AddLineQueue("DBL_FIN_MSK EQU 0xff00000000000000");
	AddLineQueue("DBL_INVINF_MSK EQU 0x800fffffffffffff");
	AddLineQueue("DBL_NEGINF_MSK EQU 0xfff0000000000000");
	AddLineQueue("DBL_NAN_MSK EQU 0x7fffffffffffffff");
	AddLineQueue("DBL_QNAN_MSK EQU 0x7ff8000000000000");
	AddLineQueue("DBL_NEGQNAN_MSK EQU 0xfff8000000000000");
	AddLineQueue("DBL_NANTEST_MSK EQU 0x000fffffffffffff");
	AddLineQueue("DBL_ABS_MSK EQU 0x7fffffffffffffff");
	AddLineQueue("DBL_MAX_MSK EQU 0x7fefffffffffffff");
	AddLineQueue("DBL_MIN_MSK EQU 0x0010000000000000");
	AddLineQueue("DBL_NOFRACTION_MSK EQU 0x0010000000000000");
	AddLineQueue("DBL_MINDENORM_MSK EQU 0x0000000000000001");
	AddLineQueue("DBL_DENORMLIMIT_MSK EQU 0x0010000000000000");
	AddLineQueue("DBL_MINNORMAL_MSK EQU 0x0010000000000000");
	AddLineQueue("DBL_MAXNORMAL_MSK EQU 0x7fefffffffffffff");

	AddLineQueue("DBL_DECDIG_MSK EQU 0x0000000000000011");
	AddLineQueue("DBL_DIG_MSK EQU 0x000000000000000f");
	AddLineQueue("DBL_NEGDECDIG_MSK EQU 0xffffffffffffffef");
	AddLineQueue("DBL_NEGDIG_MSK EQU 0xfffffffffffffff1");
	AddLineQueue("DBL_EPS_MSK EQU 0x3cb0000000000000");
	AddLineQueue("DBL_EPSILON_MSK EQU 0x3cb0000000000000");
	AddLineQueue("DBL_NORMEPS_MSK EQU 0x1a90991a9bfa58c8");
	AddLineQueue("DBL_GUARD_MSK EQU 0x0000000000000000");
	AddLineQueue("DBL_MANTPOW2_MSK EQU 0x0010000000000000");
	AddLineQueue("DBL_MAXMANTPOW2_MSK EQU 0x7fefffffffffffff");
	AddLineQueue("DBL_MANTDIG_MSK EQU 0x0000000000000035");
	AddLineQueue("DBL_MANT_MSK EQU 0x0000000000000034");
	AddLineQueue("DBL_NEGMANTDIG_MSK EQU 0xffffffffffffffcb");
	AddLineQueue("DBL_NEGMANT_MSK EQU 0xffffffffffffffcc");
	AddLineQueue("DBL_MAXEXP_MSK EQU 0x0000000000000400");
	AddLineQueue("DBL_EXPSIGN_MSK EQU 0x0000000000000400");
	AddLineQueue("DBL_EXP_MSK EQU 0x00000000000003ff");
	AddLineQueue("DBL_NEGMAXEXP_MSK EQU 0xfffffffffffffc00");
	AddLineQueue("DBL_NEGEXPSIGN_MSK EQU 0xfffffffffffffc00");
	AddLineQueue("DBL_NEGEXP_MSK EQU 0xfffffffffffffc01");
	AddLineQueue("DBL_SUBNORMALEXP_MSK EQU 0xfffffffffffffc02");
	AddLineQueue("DBL_MINEXP_MSK EQU 0xfffffffffffffc03");
	AddLineQueue("DBL_MAXDECEXP_MSK EQU 0x0000000000000134");
	AddLineQueue("DBL_NEGMAXDECEXP_MSK EQU 0xfffffffffffffecc");
	AddLineQueue("DBL_MINDECEXP_MSK EQU 0xfffffffffffffecd");
	AddLineQueue("DBL_EXPFIELD_MSK EQU 0xfff0000000000000");
	AddLineQueue("DBL_MANTFIELD_MSK EQU 0x000fffffffffffff");
	AddLineQueue("DBL_NORM_MSK EQU 0x0000000000000000");
	AddLineQueue("DBL_RADIX_MSK EQU 0x0000000000000002");
	AddLineQueue("DBL_ROUNDS_MSK EQU 0x0000000000000001");
	AddLineQueue("DBL_SUBDEC_MSK EQU 0x000000000000000a");
	AddLineQueue("DBL_SQRTMAX_MSK EQU 0x5f22087c1aeb65dc");
	AddLineQueue("DBL_SMALLNORM_MSK EQU 0x0010000000000000");

	AddLineQueue("DBL_HALFMINUSEPS_MSK EQU 0x3fdffffffffffffc");
	AddLineQueue("DBL_TRUEINT_MSK EQU 0x0000000000000001");

	AddLineQueue("DBL_BYTE_MSK EQU 0x00000000000000ff");
	AddLineQueue("DBL_BYTE_EVEN_MSK EQU 0x00ff00ff00ff00ff");
	AddLineQueue("DBL_BYTE_ODD_MSK EQU 0xff00ff00ff00ff00");
	AddLineQueue("DBL_4LOW_MSK EQU 0x0fffffffffffffff");
	AddLineQueue("DBL_4HIGH_MSK EQU 0xfffffffffffffff0");
	AddLineQueue("DBL_FLIP4_MSK EQU 0x0000000000000008");
	AddLineQueue("DBL_8LOW_MSK EQU 0x00ffffffffffffff");
	AddLineQueue("DBL_8HIGH_MSK EQU 0xffffffffffffff00");
	AddLineQueue("DBL_FLIP8_MSK EQU 0x0000000000000080");
	AddLineQueue("DBL_16LOW_MSK EQU 0x0000ffffffffffff");
	AddLineQueue("DBL_16HIGH_MSK EQU 0xffffffffffff0000");
	AddLineQueue("DBL_FLIP16_MSK EQU 0x0000000000008000");
	AddLineQueue("DBL_24LOW_MSK EQU 0x000000ffffffffff");
	AddLineQueue("DBL_24HIGH_MSK EQU 0xffffffffff000000");
	AddLineQueue("DBL_FLIP24_MSK EQU 0x0000000000800000");
	AddLineQueue("DBL_32LOW_MSK EQU 0x00000000ffffffff");
	AddLineQueue("DBL_32HIGH_MSK EQU 0xffffffff00000000");
	AddLineQueue("DBL_FLIP32_MSK EQU 0x0000000080000000");
	AddLineQueue("DBL_40LOW_MSK EQU 0x0000000000ffffff");
	AddLineQueue("DBL_40HIGH_MSK EQU 0xffffff0000000000");
	AddLineQueue("DBL_FLIP40_MSK EQU 0x0000008000000000");
	AddLineQueue("DBL_48LOW_MSK EQU 0x000000000000ffff");
	AddLineQueue("DBL_48HIGH_MSK EQU 0xffff000000000000");
	AddLineQueue("DBL_FLIP48_MSK EQU 0x0000800000000000");
	AddLineQueue("DBL_56LOW_MSK EQU 0x00000000000000ff");
	AddLineQueue("DBL_56HIGH_MSK EQU 0xff00000000000000");
	AddLineQueue("DBL_FLIP56_MSK EQU 0x0080000000000000");
	AddLineQueue("DBL_60LOW_MSK EQU 0x000000000000000f");
	AddLineQueue("DBL_60HIGH_MSK EQU 0xf000000000000000");
	AddLineQueue("DBL_FLIP60_MSK EQU 0x0800000000000000");
	AddLineQueue("DBL_64LOW_MSK EQU 0x0000000000000000");
	AddLineQueue("DBL_64HIGH_MSK EQU 0x0000000000000000");
	AddLineQueue("DBL_FLIP64_MSK EQU 0x8000000000000000");

	AddLineQueue("DBL_0_MSK EQU 0x0000000000000000");
	AddLineQueue("DBL_0D5_MSK EQU 0x3fe0000000000000");
	AddLineQueue("DBL_1_MSK EQU 0x3ff0000000000000");
	AddLineQueue("DBL_1D5_MSK EQU 0x3ff8000000000000");
	AddLineQueue("DBL_2_MSK EQU 0x4000000000000000");
	AddLineQueue("DBL_2D5_MSK EQU 0x4004000000000000");
	AddLineQueue("DBL_3_MSK EQU 0x4008000000000000");
	AddLineQueue("DBL_4_MSK EQU 0x4010000000000000");
	AddLineQueue("DBL_5_MSK EQU 0x4014000000000000");
	AddLineQueue("DBL_6_MSK EQU 0x4018000000000000");
	AddLineQueue("DBL_7_MSK EQU 0x401c000000000000");
	AddLineQueue("DBL_8_MSK EQU 0x4020000000000000");
	AddLineQueue("DBL_9_MSK EQU 0x4022000000000000");
	AddLineQueue("DBL_10_MSK EQU 0x4024000000000000");
	AddLineQueue("DBL_20_MSK EQU 0x4034000000000000");
	AddLineQueue("DBL_23_MSK EQU 0x4037000000000000");
	AddLineQueue("DBL_23D5_MSK EQU 0x4037800000000000");
	AddLineQueue("DBL_24_MSK EQU 0x4038000000000000");
	AddLineQueue("DBL_24D5_MSK EQU 0x4038800000000000");
	AddLineQueue("DBL_25_MSK EQU 0x4039000000000000");

	AddLineQueue("DBL_128_MSK EQU 0x4060000000000000");

	AddLineQueue("DBL_253_MSK EQU 0x406fa00000000000");

	AddLineQueue("DBL_NEG0_MSK EQU 0x8000000000000000");
	AddLineQueue("DBL_NEG1_MSK EQU 0xbff0000000000000");

	AddLineQueue("DBL_NEG150_MSK EQU 0xc062c00000000000");

	AddLineQueue("DBL_BIN128_MSK EQU DBL_128_MSK");
	AddLineQueue("DBL_BINNEG150_MSK EQU DBL_NEG150_MSK");

	AddLineQueue("DBL_MAXRAND_MSK EQU 0x0000000000007fff");

	AddLineQueue("DBL_MAXI8_MSK EQU 0x000000000000007f");
	AddLineQueue("DBL_MINI8_MSK EQU 0xffffffffffffff80");
	AddLineQueue("DBL_MAXU8_MSK EQU 0x00000000000000ff");

	AddLineQueue("DBL_MAXI16_MSK EQU 0x0000000000007fff");
	AddLineQueue("DBL_MINI16_MSK EQU 0xffffffffffff8000");
	AddLineQueue("DBL_MAXU16_MSK EQU 0x000000000000ffff");

	AddLineQueue("DBL_MAXI32_MSK EQU 0x000000007fffffff");
	AddLineQueue("DBL_MINI32_MSK EQU 0xffffffff80000000");
	AddLineQueue("DBL_MAXU32_MSK EQU 0x00000000ffffffff");

	AddLineQueue("DBL_MAXI64_MSK EQU 0x7fffffffffffffff");
	AddLineQueue("DBL_MINI64_MSK EQU 0x8000000000000000");
	AddLineQueue("DBL_MAXU64_MSK EQU 0xffffffffffffffff");

	AddLineQueue("DBL_MAXI8XU8_MSK EQU 0x0000000000008000");
	AddLineQueue("DBL_MINI8XU8_MSK EQU 0xffffffffffff8000");
	AddLineQueue("DBL_MAXI8XU16_MSK EQU 0x0000000000800000");
	AddLineQueue("DBL_MINI8XU16_MSK EQU 0xffffffffff800000");

	AddLineQueue("DBL_MAXI16XU16_MSK EQU 0x0000000080000000");
	AddLineQueue("DBL_MINI16XU16_MSK EQU 0xffffffff80000000");
	AddLineQueue("DBL_MAXI16XU32_MSK EQU 0x0000800000000000");
	AddLineQueue("DBL_MINI16XU32_MSK EQU 0xffff800000000000");

	AddLineQueue("DBL_MAXI32XU32_MSK EQU 0x8000000000000000");
	AddLineQueue("DBL_MINI32XU32_MSK EQU 0x8000000000000000");

	AddLineQueue("DBL_FIXUNSIGNED_MSK EQU 0x0000000080000000");
	AddLineQueue("DBL_FIXUNSIGNED32_MSK EQU 0x0000000080000000");
	AddLineQueue("DBL_FIXMAXI32_MSK EQU 0x000000007fffff80");
	AddLineQueue("DBL_FIXMAXU32_MSK EQU 0x00000000ffffff00");

	AddLineQueue("DBL_FIXUNSIGNED64_MSK EQU 0x8000000000000000");
	AddLineQueue("DBL_FIXMAXI64_MSK EQU 0x7ffffffffffff800");
	AddLineQueue("DBL_FIXMAXU64_MSK EQU 0xfffffffffffff000");

	/*double int*/
	AddLineQueue("DBL_1LSHL3_INT EQU 8");
	AddLineQueue("DBL_1LSHL4_INT EQU 16");
	AddLineQueue("DBL_1LSHL7_INT EQU 128");
	AddLineQueue("DBL_1LSHL8_INT EQU 256");
	AddLineQueue("DBL_1LSHL11_INT EQU 2048");
	AddLineQueue("DBL_1LSHL12_INT EQU 4096");
	AddLineQueue("DBL_1LSHL15_INT EQU 32768");
	AddLineQueue("DBL_1LSHL16_INT EQU 65536");
	AddLineQueue("DBL_1LSHL19_INT EQU 524288");
	AddLineQueue("DBL_1LSHL20_INT EQU 1048576");
	AddLineQueue("DBL_1LSHL23_INT EQU 8388608");
	AddLineQueue("DBL_1LSHL24_INT EQU 16777216");
	AddLineQueue("DBL_1LSHL27_INT EQU 134217728");
	AddLineQueue("DBL_1LSHL28_INT EQU 268435456");
	AddLineQueue("DBL_1LSHL31_INT EQU 2147483648");
	AddLineQueue("DBL_1LSHL32_INT EQU 4294967296");
	AddLineQueue("DBL_1LSHL35_INT EQU 34359738368");
	AddLineQueue("DBL_1LSHL36_INT EQU 68719476736");
	AddLineQueue("DBL_1LSHL39_INT EQU 549755813888");
	AddLineQueue("DBL_1LSHL40_INT EQU 1099511627776");
	AddLineQueue("DBL_1LSHL43_INT EQU 8796093022208");
	AddLineQueue("DBL_1LSHL44_INT EQU 17592186044416");
	AddLineQueue("DBL_1LSHL47_INT EQU 140737488355328");
	AddLineQueue("DBL_1LSHL48_INT EQU 281474976710656");
	AddLineQueue("DBL_1LSHL51_INT EQU 2251799813685248");
	AddLineQueue("DBL_1LSHL52_INT EQU 4503599627370496");
	AddLineQueue("DBL_1LSHL55_INT EQU 36028797018963968");
	AddLineQueue("DBL_1LSHL56_INT EQU 72057594037927936");
	AddLineQueue("DBL_1LSHL59_INT EQU 576460752303423488");
	AddLineQueue("DBL_1LSHL60_INT EQU 1152921504606846976");
	AddLineQueue("DBL_1LSHL63_INT EQU (-9223372036854775808)");

	AddLineQueue("DBL_NEG1LSHL3_INT EQU (-8)");
	AddLineQueue("DBL_NEG1LSHL4_INT EQU (-16)");
	AddLineQueue("DBL_NEG1LSHL7_INT EQU (-128)");
	AddLineQueue("DBL_NEG1LSHL8_INT EQU (-256)");
	AddLineQueue("DBL_NEG1LSHL11_INT EQU (-2048)");
	AddLineQueue("DBL_NEG1LSHL12_INT EQU (-4096)");
	AddLineQueue("DBL_NEG1LSHL15_INT EQU (-32768)");
	AddLineQueue("DBL_NEG1LSHL16_INT EQU (-65536)");
	AddLineQueue("DBL_NEG1LSHL19_INT EQU (-524288)");
	AddLineQueue("DBL_NEG1LSHL20_INT EQU (-1048576)");
	AddLineQueue("DBL_NEG1LSHL23_INT EQU (-8388608)");
	AddLineQueue("DBL_NEG1LSHL24_INT EQU (-16777216)");
	AddLineQueue("DBL_NEG1LSHL27_INT EQU (-134217728)");
	AddLineQueue("DBL_NEG1LSHL28_INT EQU (-268435456)");
	AddLineQueue("DBL_NEG1LSHL31_INT EQU (-2147483648)");
	AddLineQueue("DBL_NEG1LSHL32_INT EQU (-4294967296)");
	AddLineQueue("DBL_NEG1LSHL35_INT EQU (-34359738368)");
	AddLineQueue("DBL_NEG1LSHL36_INT EQU (-68719476736)");
	AddLineQueue("DBL_NEG1LSHL39_INT EQU (-549755813888)");
	AddLineQueue("DBL_NEG1LSHL40_INT EQU (-1099511627776)");
	AddLineQueue("DBL_NEG1LSHL43_INT EQU (-8796093022208)");
	AddLineQueue("DBL_NEG1LSHL44_INT EQU (-17592186044416)");
	AddLineQueue("DBL_NEG1LSHL47_INT EQU (-140737488355328)");
	AddLineQueue("DBL_NEG1LSHL48_INT EQU (-281474976710656)");
	AddLineQueue("DBL_NEG1LSHL51_INT EQU (-2251799813685248)");
	AddLineQueue("DBL_NEG1LSHL52_INT EQU (-4503599627370496)");
	AddLineQueue("DBL_NEG1LSHL55_INT EQU (-36028797018963968)");
	AddLineQueue("DBL_NEG1LSHL56_INT EQU (-72057594037927936)");
	AddLineQueue("DBL_NEG1LSHL59_INT EQU (-576460752303423488)");
	AddLineQueue("DBL_NEG1LSHL60_INT EQU (-1152921504606846976)");
	AddLineQueue("DBL_NEG1LSHL63_INT EQU (-9223372036854775808)");

	AddLineQueue("DBL_FALSE_INT EQU 0");
	AddLineQueue("DBL_TRUE_INT EQU (-1)");
	AddLineQueue("DBL_ERROR_INT EQU DBL_ERROR");

	AddLineQueue("DBL_MAGIC_INT EQU 4503599627370496");
	AddLineQueue("DBL_SIGN_INT EQU (-9223372036854775808)");
	AddLineQueue("DBL_INVSIGN_INT EQU 9223372036854775807");

	AddLineQueue("DBL_INF_INT EQU 9218868437227405312");
	AddLineQueue("DBL_FIN_INT EQU (-72057594037927936)");
	AddLineQueue("DBL_INVINF_INT EQU (-9218868437227405313)");
	AddLineQueue("DBL_NEGINF_INT EQU (-4503599627370496)");
	AddLineQueue("DBL_NAN_INT EQU 9223372036854775807");
	AddLineQueue("DBL_QNAN_INT EQU 9221120237041090560");
	AddLineQueue("DBL_NEGQNAN_INT EQU (-2251799813685248)");
	AddLineQueue("DBL_NANTEST_INT EQU 4503599627370495");
	AddLineQueue("DBL_ABS_INT EQU 9223372036854775807");
	AddLineQueue("DBL_MAX_INT EQU 9218868437227405311");
	AddLineQueue("DBL_MIN_INT EQU 4503599627370496");
	AddLineQueue("DBL_NOFRACTION_INT EQU 4503599627370496");
	AddLineQueue("DBL_MINDENORM_INT EQU 1");
	AddLineQueue("DBL_DENORMLIMIT_INT EQU 4503599627370496");
	AddLineQueue("DBL_MINNORMAL_INT EQU 4503599627370496");
	AddLineQueue("DBL_MAXNORMAL_INT EQU 9218868437227405311");

	AddLineQueue("DBL_DECDIG_INT EQU 17");
	AddLineQueue("DBL_DIG_INT EQU 15");
	AddLineQueue("DBL_NEGDECDIG_INT EQU (-17)");
	AddLineQueue("DBL_NEGDIG_INT EQU (-15)");
	AddLineQueue("DBL_EPS_INT EQU 4372995238176751616");
	AddLineQueue("DBL_EPSILON_INT EQU 4372995238176751616");
	AddLineQueue("DBL_NORMEPS_INT EQU 1914198181197535432");
	AddLineQueue("DBL_GUARD_INT EQU 0");
	AddLineQueue("DBL_MANTPOW2_INT EQU 4503599627370496");
	AddLineQueue("DBL_MAXMANTPOW2_INT EQU 9218868437227405311");
	AddLineQueue("DBL_MANTDIG_INT EQU 53");
	AddLineQueue("DBL_MANT_INT EQU 52");
	AddLineQueue("DBL_NEGMANTDIG_INT EQU (-53)");
	AddLineQueue("DBL_NEGMANT_INT EQU (-52)");
	AddLineQueue("DBL_MAXEXP_INT EQU 1024");
	AddLineQueue("DBL_EXPSIGN_INT EQU 1024");
	AddLineQueue("DBL_EXP_INT EQU 1023");
	AddLineQueue("DBL_NEGMAXEXP_INT EQU (-1024)");
	AddLineQueue("DBL_NEGEXPSIGN_INT EQU (-1024)");
	AddLineQueue("DBL_NEGEXP_INT EQU (-1023)");
	AddLineQueue("DBL_SUBNORMALEXP_INT EQU (-1022)");
	AddLineQueue("DBL_MINEXP_INT EQU (-1021)");
	AddLineQueue("DBL_MAXDECEXP_INT EQU 308");
	AddLineQueue("DBL_NEGMAXDECEXP_INT EQU (-308)");
	AddLineQueue("DBL_MINDECEXP_INT EQU (-307)");
	AddLineQueue("DBL_EXPFIELD_INT EQU (-4503599627370496)");
	AddLineQueue("DBL_MANTFIELD_INT EQU 4503599627370495");
	AddLineQueue("DBL_NORM_INT EQU 0");
	AddLineQueue("DBL_RADIX_INT EQU 2");
	AddLineQueue("DBL_ROUNDS_INT EQU 1");
	AddLineQueue("DBL_SUBDEC_INT EQU 10");
	AddLineQueue("DBL_SQRTMAX_INT EQU 6855050911931917788");
	AddLineQueue("DBL_SMALLNORM_INT EQU 4503599627370496");

	AddLineQueue("DBL_HALFMINUSEPS_INT EQU 4602678819172646908");
	AddLineQueue("DBL_TRUEINT_INT EQU 1");

	AddLineQueue("DBL_BYTE_INT EQU 255");
	AddLineQueue("DBL_BYTE_EVEN_INT EQU 71777214294589695");
	AddLineQueue("DBL_BYTE_ODD_INT EQU (-71777214294589696)");
	AddLineQueue("DBL_4LOW_INT EQU 1152921504606846975");
	AddLineQueue("DBL_4HIGH_INT EQU (-16)");
	AddLineQueue("DBL_FLIP4_INT EQU 8");
	AddLineQueue("DBL_8LOW_INT EQU 72057594037927935");
	AddLineQueue("DBL_8HIGH_INT EQU (-256)");
	AddLineQueue("DBL_FLIP8_INT EQU 128");
	AddLineQueue("DBL_16LOW_INT EQU 281474976710655");
	AddLineQueue("DBL_16HIGH_INT EQU (-65536)");
	AddLineQueue("DBL_FLIP16_INT EQU 32768");
	AddLineQueue("DBL_24LOW_INT EQU 1099511627775");
	AddLineQueue("DBL_24HIGH_INT EQU (-16777216)");
	AddLineQueue("DBL_FLIP24_INT EQU 8388608");
	AddLineQueue("DBL_32LOW_INT EQU 4294967295");
	AddLineQueue("DBL_32HIGH_INT EQU (-4294967296)");
	AddLineQueue("DBL_FLIP32_INT EQU 2147483648");
	AddLineQueue("DBL_40LOW_INT EQU 16777215");
	AddLineQueue("DBL_40HIGH_INT EQU (-1099511627776)");
	AddLineQueue("DBL_FLIP40_INT EQU 549755813888");
	AddLineQueue("DBL_48LOW_INT EQU 65535");
	AddLineQueue("DBL_48HIGH_INT EQU (-281474976710656)");
	AddLineQueue("DBL_FLIP48_INT EQU 140737488355328");
	AddLineQueue("DBL_56LOW_INT EQU 255");
	AddLineQueue("DBL_56HIGH_INT EQU (-72057594037927936)");
	AddLineQueue("DBL_FLIP56_INT EQU 36028797018963968");
	AddLineQueue("DBL_60LOW_INT EQU 15");
	AddLineQueue("DBL_60HIGH_INT EQU (-1152921504606846976)");
	AddLineQueue("DBL_FLIP60_INT EQU 576460752303423488");
	AddLineQueue("DBL_64LOW_INT EQU 0");
	AddLineQueue("DBL_64HIGH_INT EQU 0");
	AddLineQueue("DBL_FLIP64_INT EQU (-9223372036854775808)");

	AddLineQueue("DBL_0_INT EQU 0");
	AddLineQueue("DBL_OD5_INT EQU 4602678819172646912");
	AddLineQueue("DBL_1_INT EQU 4607182418800017408");
	AddLineQueue("DBL_1D5_INT EQU 4609434218613702656");
	AddLineQueue("DBL_2_INT EQU 4611686018427387904");
	AddLineQueue("DBL_2D5_INT EQU 4612811918334230528");
	AddLineQueue("DBL_3_INT EQU 4613937818241073152");
	AddLineQueue("DBL_4_INT EQU 4616189618054758400");
	AddLineQueue("DBL_5_INT EQU 4617315517961601024");
	AddLineQueue("DBL_6_INT EQU 4618441417868443648");
	AddLineQueue("DBL_7_INT EQU 4619567317775286272");
	AddLineQueue("DBL_8_INT EQU 4620693217682128896");
	AddLineQueue("DBL_9_INT EQU 4621256167635550208");
	AddLineQueue("DBL_10_INT EQU 4621819117588971520");
	AddLineQueue("DBL_20_INT EQU 4626322717216342016");
	AddLineQueue("DBL_23_INT EQU 4627167142146473984");
	AddLineQueue("DBL_23D5_INT EQU 4627307879634829312");
	AddLineQueue("DBL_24_INT EQU 4627448617123184640");
	AddLineQueue("DBL_24D5_INT EQU 4627589354611539968");
	AddLineQueue("DBL_25_INT EQU 4627730092099895296");

	AddLineQueue("DBL_128_INT EQU 4638707616191610880");

	AddLineQueue("DBL_253_INT EQU 4643105662702714880");

	AddLineQueue("DBL_NEG0_INT EQU (-9223372036854775808)");
	AddLineQueue("DBL_NEG1_INT EQU (-4616189618054758400)");

	AddLineQueue("DBL_NEG150_INT EQU (-4583890364477210624)");

	AddLineQueue("DBL_BIN128_INT EQU DBL_128_INT");
	AddLineQueue("DBL_BINNEG150_INT EQU DBL_NEG150_INT");

	AddLineQueue("DBL_MAXRAND_INT EQU 32767");

	AddLineQueue("DBL_MAXI8_INT EQU 127");
	AddLineQueue("DBL_MINI8_INT EQU (-128)");
	AddLineQueue("DBL_MAXU8_INT EQU 255");

	AddLineQueue("DBL_MAXI16_INT EQU 32767");
	AddLineQueue("DBL_MINI16_INT EQU (-32768)");
	AddLineQueue("DBL_MAXU16_INT EQU 65535");

	AddLineQueue("DBL_MAXI32_INT EQU 2147483647");
	AddLineQueue("DBL_MINI32_INT EQU (-2147483648)");
	AddLineQueue("DBL_MAXU32_INT EQU 4294967295");

	AddLineQueue("DBL_MAXI64_INT EQU 9223372036854775807");
	AddLineQueue("DBL_MINI64_INT EQU (-9223372036854775808)");
	AddLineQueue("DBL_MAXU64_INT EQU 18446744073709551615");

	AddLineQueue("DBL_MAXI8XU8_INT EQU 32768");
	AddLineQueue("DBL_MINI8XU8_INT EQU (-32768)");
	AddLineQueue("DBL_MAXI8XU16_INT EQU 8388608");
	AddLineQueue("DBL_MINI8XU16_INT EQU (-8388608)");

	AddLineQueue("DBL_MAXI16XU16_INT EQU 2147483648");
	AddLineQueue("DBL_MINI16XU16_INT EQU (-2147483648)");
	AddLineQueue("DBL_MAXI16XU32_INT EQU 140737488355328");
	AddLineQueue("DBL_MINI16XU32_INT EQU (-140737488355328)");

	AddLineQueue("DBL_MAXI32XU32_INT EQU (-9223372036854775808)");
	AddLineQueue("DBL_MINI32XU32_INT EQU (-9223372036854775808)");

	AddLineQueue("DBL_FIXUNSIGNED_INT EQU 2147483648");
	AddLineQueue("DBL_FIXUNSIGNED32_INT EQU 2147483648");
	AddLineQueue("DBL_FIXMAXI32_INT EQU 2147483520");
	AddLineQueue("DBL_FIXMAXU32_INT EQU 4294967040");

	AddLineQueue("DBL_FIXUNSIGNED64_INT EQU (-9223372036854775808)");
	AddLineQueue("DBL_FIXMAXI64_INT EQU 9223372036854773760");
	AddLineQueue("DBL_FIXMAXU64_INT EQU (-4096)");

	/*double*/
	AddLineQueue("DBL_1LSHL3 EQU 8.0");
	AddLineQueue("DBL_1LSHL4 EQU 16.0");
	AddLineQueue("DBL_1LSHL7 EQU 128.0");
	AddLineQueue("DBL_1LSHL8 EQU 256.0");
	AddLineQueue("DBL_1LSHL11 EQU 2048.0");
	AddLineQueue("DBL_1LSHL12 EQU 4096.0");
	AddLineQueue("DBL_1LSHL15 EQU 32768.0");
	AddLineQueue("DBL_1LSHL16 EQU 65536.0");
	AddLineQueue("DBL_1LSHL19 EQU 524288.0");
	AddLineQueue("DBL_1LSHL20 EQU 1048576.0");
	AddLineQueue("DBL_1LSHL23 EQU 8388608.0");
	AddLineQueue("DBL_1LSHL24 EQU 16777216.0");
	AddLineQueue("DBL_1LSHL27 EQU 134217728.0");
	AddLineQueue("DBL_1LSHL28 EQU 268435456.0");
	AddLineQueue("DBL_1LSHL31 EQU 2147483648.0");
	AddLineQueue("DBL_1LSHL32 EQU 4294967296.0");
	AddLineQueue("DBL_1LSHL35 EQU 34359738368.0");
	AddLineQueue("DBL_1LSHL36 EQU 68719476736.0");
	AddLineQueue("DBL_1LSHL39 EQU 549755813888.0");
	AddLineQueue("DBL_1LSHL40 EQU 1099511627776.0");
	AddLineQueue("DBL_1LSHL43 EQU 8796093022208.0");
	AddLineQueue("DBL_1LSHL44 EQU 17592186044416.0");
	AddLineQueue("DBL_1LSHL47 EQU 140737488355328.0");
	AddLineQueue("DBL_1LSHL48 EQU 281474976710656.0");
	AddLineQueue("DBL_1LSHL51 EQU 2251799813685248.0");
	AddLineQueue("DBL_1LSHL52 EQU 4503599627370496.0");
	AddLineQueue("DBL_1LSHL55 EQU 36028797018963968.0");
	AddLineQueue("DBL_1LSHL56 EQU 72057594037927936.0");
	AddLineQueue("DBL_1LSHL59 EQU 576460752303423488.0");
	AddLineQueue("DBL_1LSHL60 EQU 1152921504606846976.0");
	AddLineQueue("DBL_1LSHL63 EQU (-9223372036854775808.0)");

	AddLineQueue("DBL_NEG1LSHL3 EQU (-8.0)");
	AddLineQueue("DBL_NEG1LSHL4 EQU (-16.0)");
	AddLineQueue("DBL_NEG1LSHL7 EQU (-128.0)");
	AddLineQueue("DBL_NEG1LSHL8 EQU (-256.0)");
	AddLineQueue("DBL_NEG1LSHL11 EQU (-2048.0)");
	AddLineQueue("DBL_NEG1LSHL12 EQU (-4096.0)");
	AddLineQueue("DBL_NEG1LSHL15 EQU (-32768.0)");
	AddLineQueue("DBL_NEG1LSHL16 EQU (-65536.0)");
	AddLineQueue("DBL_NEG1LSHL19 EQU (-524288.0)");
	AddLineQueue("DBL_NEG1LSHL20 EQU (-1048576.0)");
	AddLineQueue("DBL_NEG1LSHL23 EQU (-8388608.0)");
	AddLineQueue("DBL_NEG1LSHL24 EQU (-16777216.0)");
	AddLineQueue("DBL_NEG1LSHL27 EQU (-134217728.0)");
	AddLineQueue("DBL_NEG1LSHL28 EQU (-268435456.0)");
	AddLineQueue("DBL_NEG1LSHL31 EQU (-2147483648.0)");
	AddLineQueue("DBL_NEG1LSHL32 EQU (-4294967296.0)");
	AddLineQueue("DBL_NEG1LSHL35 EQU (-34359738368.0)");
	AddLineQueue("DBL_NEG1LSHL36 EQU (-68719476736.0)");
	AddLineQueue("DBL_NEG1LSHL39 EQU (-549755813888.0)");
	AddLineQueue("DBL_NEG1LSHL40 EQU (-1099511627776.0)");
	AddLineQueue("DBL_NEG1LSHL43 EQU (-8796093022208.0)");
	AddLineQueue("DBL_NEG1LSHL44 EQU (-17592186044416.0)");
	AddLineQueue("DBL_NEG1LSHL47 EQU (-140737488355328.0)");
	AddLineQueue("DBL_NEG1LSHL48 EQU (-281474976710656.0)");
	AddLineQueue("DBL_NEG1LSHL51 EQU (-2251799813685248.0)");
	AddLineQueue("DBL_NEG1LSHL52 EQU (-4503599627370496.0)");
	AddLineQueue("DBL_NEG1LSHL55 EQU (-36028797018963968.0)");
	AddLineQueue("DBL_NEG1LSHL56 EQU (-72057594037927936.0)");
	AddLineQueue("DBL_NEG1LSHL59 EQU (-576460752303423488.0)");
	AddLineQueue("DBL_NEG1LSHL60 EQU (-1152921504606846976.0)");
	AddLineQueue("DBL_NEG1LSHL63 EQU (-9223372036854775808.0)");

	AddLineQueue("DBL_FALSE EQU DBL_FALSE_MSK");
	AddLineQueue("DBL_TRUE EQU DBL_TRUE_MSK");

	AddLineQueue("DBL_MAGIC EQU DBL_MAGIC_MSK");
	AddLineQueue("DBL_SIGN EQU DBL_SIGN_MSK");
	AddLineQueue("DBL_INVSIGN EQU DBL_INVSIGN_MSK");

	AddLineQueue("DBL_INF EQU DBL_INF_MSK");
	AddLineQueue("DBL_FIN EQU DBL_FIN_MSK");
	AddLineQueue("DBL_INVINF EQU DBL_INVINF_MSK");
	AddLineQueue("DBL_NEGINF EQU DBL_NEGINF_MSK");
	AddLineQueue("DBL_NAN EQU DBL_NAN_MSK");
	AddLineQueue("DBL_QNAN EQU DBL_QNAN_MSK");
	AddLineQueue("DBL_NEGQNAN EQU DBL_NEGQNAN_MSK");
	AddLineQueue("DBL_NANTEST EQU DBL_NANTEST_MSK");
	AddLineQueue("DBL_ABS EQU DBL_ABS_MSK");
	AddLineQueue("DBL_MIN EQU 2.2250738585072014e-308");
	AddLineQueue("DBL_MAX EQU 1.7976931348623158e+308");
	AddLineQueue("DBL_NOFRACTION EQU 4503599627370496.0");
	AddLineQueue("DBL_MINDENORM EQU 5e-324");
	AddLineQueue("DBL_DENORMLIMIT EQU 2.2250738585072014e-308");
	AddLineQueue("DBL_MINNORMAL EQU 2.2250738585072014e-308");
	AddLineQueue("DBL_MAXNORMAL EQU 1.7976931348623158e+308");

	AddLineQueue("DBL_DECDIG EQU 17.0");
	AddLineQueue("DBL_DIG EQU 15.0");
	AddLineQueue("DBL_NEGDECDIG EQU (-17.0)");
	AddLineQueue("DBL_NEGDIG EQU (-15.0)");
	AddLineQueue("DBL_EPS EQU 2.2204460492503131e-016");
	AddLineQueue("DBL_EPSILON EQU 2.2204460492503131e-016");
	AddLineQueue("DBL_NORMEPS EQU 1e-180");
	AddLineQueue("DBL_GUARD EQU 0.0");
	AddLineQueue("DBL_MANTPOW2 EQU 2.2250738585072014e-308");
	AddLineQueue("DBL_MAXMANTPOW2 EQU 1.7976931348623158e+308");
	AddLineQueue("DBL_MANTDIG EQU 53.0");
	AddLineQueue("DBL_MANT EQU 52.0");
	AddLineQueue("DBL_NEGMANTDIG EQU (-53.0)");
	AddLineQueue("DBL_NEGMANT EQU (-52.0)");
	AddLineQueue("DBL_MAXEXP EQU 1024.0");
	AddLineQueue("DBL_EXPSIGN EQU 1024.0");
	AddLineQueue("DBL_EXP EQU 1023.0");
	AddLineQueue("DBL_NEGMAXEXP EQU (-1024.0)");
	AddLineQueue("DBL_NEGEXPSIGN EQU (-1024.0)");
	AddLineQueue("DBL_NEGEXP EQU (-1023.0)");
	AddLineQueue("DBL_SUBNORMALEXP EQU (-1022.0)");
	AddLineQueue("DBL_MINEXP EQU (-1021.0)");
	AddLineQueue("DBL_MAXDECEXP EQU 308.0");
	AddLineQueue("DBL_NEGMAXDECEXP EQU (-308.0)");
	AddLineQueue("DBL_MINDECEXP EQU (-307.0)");
	AddLineQueue("DBL_EXPFIELD EQU (-4503599627370496.0)");
	AddLineQueue("DBL_MANTFIELD EQU 4503599627370495.0");
	AddLineQueue("DBL_NORM EQU 0.0");
	AddLineQueue("DBL_RADIX EQU 2.0");
	AddLineQueue("DBL_ROUNDS EQU 1.0");
	AddLineQueue("DBL_SUBDEC EQU 10.0");
	AddLineQueue("DBL_SQRTMAX EQU 1.8446726e+150");
	AddLineQueue("DBL_SMALLNORM EQU 2.2250738585072014e-308");

	AddLineQueue("DBL_HALFMINUSEPS EQU 0.49999999999999977795539507496869");
	AddLineQueue("DBL_TRUEINT EQU 1.0");

	AddLineQueue("DBL_BYTE EQU 255.0");
	AddLineQueue("DBL_BYTE_EVEN EQU 71777214294589695.0");
	AddLineQueue("DBL_BYTE_ODD EQU (-71777214294589696.0)");
	AddLineQueue("DBL_4LOW EQU 1152921504606846975.0");
	AddLineQueue("DBL_4HIGH EQU (-16.0)");
	AddLineQueue("DBL_FLIP4 EQU 8.0");
	AddLineQueue("DBL_8LOW EQU 72057594037927935.0");
	AddLineQueue("DBL_8HIGH EQU (-256.0)");
	AddLineQueue("DBL_FLIP8 EQU 128.0");
	AddLineQueue("DBL_16LOW EQU 281474976710655.0");
	AddLineQueue("DBL_16HIGH EQU (-65536.0)");
	AddLineQueue("DBL_FLIP16 EQU 32768.0");
	AddLineQueue("DBL_24LOW EQU 1099511627775.0");
	AddLineQueue("DBL_24HIGH EQU (-16777216.0)");
	AddLineQueue("DBL_FLIP24 EQU 8388608.0");
	AddLineQueue("DBL_32LOW EQU 4294967295.0");
	AddLineQueue("DBL_32HIGH EQU (-4294967296.0)");
	AddLineQueue("DBL_FLIP32 EQU 2147483648.0");
	AddLineQueue("DBL_40LOW EQU 16777215.0");
	AddLineQueue("DBL_40HIGH EQU (-1099511627776.0)");
	AddLineQueue("DBL_FLIP40 EQU 549755813888.0");
	AddLineQueue("DBL_48LOW EQU 65535.0");
	AddLineQueue("DBL_48HIGH EQU (-281474976710656.0)");
	AddLineQueue("DBL_FLIP48 EQU 140737488355328.0");
	AddLineQueue("DBL_56LOW EQU 255.0");
	AddLineQueue("DBL_56HIGH EQU (-72057594037927936.0)");
	AddLineQueue("DBL_FLIP56 EQU 36028797018963968.0");
	AddLineQueue("DBL_60LOW EQU 15.0");
	AddLineQueue("DBL_60HIGH EQU (-1152921504606846976.0)");
	AddLineQueue("DBL_FLIP60 EQU 576460752303423488.0");
	AddLineQueue("DBL_64LOW EQU 0.0");
	AddLineQueue("DBL_64HIGH EQU 0.0");
	AddLineQueue("DBL_FLIP64 EQU (-9223372036854775808.0)");
	
	AddLineQueue("DBL_0 EQU 0.0");
	AddLineQueue("DBL_0D0001 EQU 0.0001");
	AddLineQueue("DBL_0D0002 EQU 0.0002");
	AddLineQueue("DBL_0D0003 EQU 0.0003");
	AddLineQueue("DBL_0D0004 EQU 0.0004");
	AddLineQueue("DBL_0D0005 EQU 0.0005");
	AddLineQueue("DBL_0D0006 EQU 0.0006");
	AddLineQueue("DBL_0D0007 EQU 0.0007");
	AddLineQueue("DBL_0D0008 EQU 0.0008");
	AddLineQueue("DBL_0D0009 EQU 0.0009");
	AddLineQueue("DBL_0D001 EQU 0.001");
	AddLineQueue("DBL_0D002 EQU 0.002");
	AddLineQueue("DBL_0D003 EQU 0.003");
	AddLineQueue("DBL_0D004 EQU 0.004");
	AddLineQueue("DBL_0D005 EQU 0.005");
	AddLineQueue("DBL_0D006 EQU 0.006");
	AddLineQueue("DBL_0D007 EQU 0.007");
	AddLineQueue("DBL_0D008 EQU 0.008");
	AddLineQueue("DBL_0D009 EQU 0.009");
	AddLineQueue("DBL_0D01 EQU 0.01");
	AddLineQueue("DBL_0D02 EQU 0.02");
	AddLineQueue("DBL_0D025 EQU 0.025");
	AddLineQueue("DBL_0D03 EQU 0.03");
	AddLineQueue("DBL_0D04 EQU 0.04");
	AddLineQueue("DBL_0D05 EQU 0.05");
	AddLineQueue("DBL_0D06 EQU 0.06");
	AddLineQueue("DBL_0D07 EQU 0.07");
	AddLineQueue("DBL_0D08 EQU 0.08");
	AddLineQueue("DBL_0D09 EQU 0.09");
	AddLineQueue("DBL_0D1 EQU 0.1");
	AddLineQueue("DBL_0D2 EQU 0.2");
	AddLineQueue("DBL_0D25 EQU 0.25");
	AddLineQueue("DBL_0D3 EQU 0.3");
	AddLineQueue("DBL_0D4 EQU 0.4");
	AddLineQueue("DBL_0D5 EQU 0.5");
	AddLineQueue("DBL_0D6 EQU 0.6");
	AddLineQueue("DBL_0D7 EQU 0.7");
	AddLineQueue("DBL_0D8 EQU 0.8");
	AddLineQueue("DBL_0D9 EQU 0.9");
	AddLineQueue("DBL_1 EQU 1.0");
	AddLineQueue("DBL_1D25 EQU 1.25");
	AddLineQueue("DBL_1D5 EQU 1.5");
	AddLineQueue("DBL_2 EQU 2.0");
	AddLineQueue("DBL_2D25 EQU 2.25");
	AddLineQueue("DBL_2D5 EQU 2.5");
	AddLineQueue("DBL_3 EQU 3.0");
	AddLineQueue("DBL_3D25 EQU 3.25");
	AddLineQueue("DBL_3D5 EQU 3.5");
	AddLineQueue("DBL_4 EQU 4.0");
	AddLineQueue("DBL_4D25 EQU 4.25");
	AddLineQueue("DBL_4D5 EQU 4.5");
	AddLineQueue("DBL_5 EQU 5.0");
	AddLineQueue("DBL_5D25 EQU 5.25");
	AddLineQueue("DBL_5D5 EQU 5.5");
	AddLineQueue("DBL_6 EQU 6.0");
	AddLineQueue("DBL_6D25 EQU 6.25");
	AddLineQueue("DBL_6D5 EQU 6.5");
	AddLineQueue("DBL_7 EQU 7.0");
	AddLineQueue("DBL_7D25 EQU 7.25");
	AddLineQueue("DBL_7D5 EQU 7.5");
	AddLineQueue("DBL_8 EQU 8.0");
	AddLineQueue("DBL_8D25 EQU 8.25");
	AddLineQueue("DBL_8D5 EQU 8.5");
	AddLineQueue("DBL_9 EQU 9.0");
	AddLineQueue("DBL_9D25 EQU 9.25");
	AddLineQueue("DBL_9D5 EQU 9.5");
	AddLineQueue("DBL_10 EQU 10.0");
	AddLineQueue("DBL_11 EQU 11.0");
	AddLineQueue("DBL_12 EQU 12.0");
	AddLineQueue("DBL_13 EQU 13.0");
	AddLineQueue("DBL_14 EQU 14.0");
	AddLineQueue("DBL_15 EQU 15.0");
	AddLineQueue("DBL_16 EQU 16.0");
	AddLineQueue("DBL_17 EQU 17.0");
	AddLineQueue("DBL_18 EQU 18.0");
	AddLineQueue("DBL_19 EQU 19.0");
	AddLineQueue("DBL_20 EQU 20.0");
	AddLineQueue("DBL_21 EQU 21.0");
	AddLineQueue("DBL_22 EQU 22.0");
	AddLineQueue("DBL_23 EQU 23.0");
	AddLineQueue("DBL_24 EQU 24.0");
	AddLineQueue("DBL_24D5 EQU 24.5");
	AddLineQueue("DBL_25 EQU 25.0");
	AddLineQueue("DBL_26 EQU 26.0");
	AddLineQueue("DBL_27 EQU 27.0");
	AddLineQueue("DBL_28 EQU 28.0");
	AddLineQueue("DBL_29 EQU 29.0");
	AddLineQueue("DBL_30 EQU 30.0");
	AddLineQueue("DBL_31 EQU 31.0");
	AddLineQueue("DBL_32 EQU 32.0");
	AddLineQueue("DBL_33 EQU 33.0");
	AddLineQueue("DBL_34 EQU 34.0");
	AddLineQueue("DBL_35 EQU 35.0");
	AddLineQueue("DBL_36 EQU 36.0");
	AddLineQueue("DBL_37 EQU 37.0");
	AddLineQueue("DBL_38 EQU 38.0");
	AddLineQueue("DBL_39 EQU 39.0");
	AddLineQueue("DBL_40 EQU 40.0");
	AddLineQueue("DBL_41 EQU 41.0");
	AddLineQueue("DBL_42 EQU 42.0");
	AddLineQueue("DBL_43 EQU 43.0");
	AddLineQueue("DBL_44 EQU 44.0");
	AddLineQueue("DBL_45 EQU 45.0");
	AddLineQueue("DBL_46 EQU 46.0");
	AddLineQueue("DBL_47 EQU 47.0");
	AddLineQueue("DBL_48 EQU 48.0");
	AddLineQueue("DBL_49 EQU 49.0");
	AddLineQueue("DBL_50 EQU 50.0");
	AddLineQueue("DBL_51 EQU 51.0");
	AddLineQueue("DBL_52 EQU 52.0");
	AddLineQueue("DBL_53 EQU 53.0");
	AddLineQueue("DBL_54 EQU 54.0");
	AddLineQueue("DBL_55 EQU 55.0");
	AddLineQueue("DBL_56 EQU 56.0");
	AddLineQueue("DBL_57 EQU 57.0");
	AddLineQueue("DBL_58 EQU 58.0");
	AddLineQueue("DBL_59 EQU 59.0");
	AddLineQueue("DBL_60 EQU 60.0");
	AddLineQueue("DBL_61 EQU 61.0");
	AddLineQueue("DBL_62 EQU 62.0");
	AddLineQueue("DBL_63 EQU 63.0");
	AddLineQueue("DBL_64 EQU 64.0");
	AddLineQueue("DBL_65 EQU 65.0");
	AddLineQueue("DBL_66 EQU 66.0");
	AddLineQueue("DBL_67 EQU 67.0");
	AddLineQueue("DBL_68 EQU 68.0");
	AddLineQueue("DBL_69 EQU 69.0");
	AddLineQueue("DBL_70 EQU 70.0");
	AddLineQueue("DBL_71 EQU 71.0");
	AddLineQueue("DBL_72 EQU 72.0");
	AddLineQueue("DBL_73 EQU 73.0");
	AddLineQueue("DBL_74 EQU 74.0");
	AddLineQueue("DBL_75 EQU 75.0");
	AddLineQueue("DBL_76 EQU 76.0");
	AddLineQueue("DBL_77 EQU 77.0");
	AddLineQueue("DBL_78 EQU 78.0");
	AddLineQueue("DBL_79 EQU 79.0");
	AddLineQueue("DBL_80 EQU 80.0");
	AddLineQueue("DBL_81 EQU 81.0");
	AddLineQueue("DBL_82 EQU 82.0");
	AddLineQueue("DBL_83 EQU 83.0");
	AddLineQueue("DBL_84 EQU 84.0");
	AddLineQueue("DBL_85 EQU 85.0");
	AddLineQueue("DBL_86 EQU 86.0");
	AddLineQueue("DBL_87 EQU 87.0");
	AddLineQueue("DBL_88 EQU 88.0");
	AddLineQueue("DBL_89 EQU 89.0");
	AddLineQueue("DBL_90 EQU 90.0");
	AddLineQueue("DBL_91 EQU 91.0");
	AddLineQueue("DBL_92 EQU 92.0");
	AddLineQueue("DBL_93 EQU 93.0");
	AddLineQueue("DBL_94 EQU 94.0");
	AddLineQueue("DBL_95 EQU 95.0");
	AddLineQueue("DBL_96 EQU 96.0");
	AddLineQueue("DBL_97 EQU 97.0");
	AddLineQueue("DBL_98 EQU 98.0");
	AddLineQueue("DBL_99 EQU 99.0");
	AddLineQueue("DBL_100 EQU 100.0");
	AddLineQueue("DBL_125 EQU 125.0");
	AddLineQueue("DBL_126 EQU 126.0");
	AddLineQueue("DBL_127 EQU 127.0");
	AddLineQueue("DBL_128 EQU 128.0");
	AddLineQueue("DBL_140 EQU 140.0");
	AddLineQueue("DBL_145 EQU 145.0");
	AddLineQueue("DBL_150 EQU 150.0");
	AddLineQueue("DBL_180 EQU 180.0");
	AddLineQueue("DBL_253 EQU 253.0");
	AddLineQueue("DBL_254 EQU 254.0");
	AddLineQueue("DBL_255 EQU 255.0");
	AddLineQueue("DBL_256 EQU 256.0");
	AddLineQueue("DBL_360 EQU 360.0");
	AddLineQueue("DBL_511 EQU 511.0");
	AddLineQueue("DBL_512 EQU 512.0");
	AddLineQueue("DBL_513 EQU 513.0");
	AddLineQueue("DBL_1023 EQU 1023.0");
	AddLineQueue("DBL_1024 EQU 1024.0");
	AddLineQueue("DBL_1025 EQU 1025.0");

	AddLineQueue("DBL_32767 EQU 32767.0");
	AddLineQueue("DBL_32768 EQU 32768.0");
	AddLineQueue("DBL_65535 EQU 65535.0");
	AddLineQueue("DBL_65536 EQU 65536.0");
	AddLineQueue("DBL_2147483647 EQU 2147483647.0");
	AddLineQueue("DBL_2147483648 EQU 2147483648.0");
	AddLineQueue("DBL_4294967295 EQU 4294967295.0");
	AddLineQueue("DBL_4294967296 EQU 4294967296.0");

	AddLineQueue("DBL_NEG0 EQU (-0.0)");
	AddLineQueue("DBL_NEG0D0001 EQU (-0.0001)");
	AddLineQueue("DBL_NEG0D0002 EQU (-0.0002)");
	AddLineQueue("DBL_NEG0D0003 EQU (-0.0003)");
	AddLineQueue("DBL_NEG0D0004 EQU (-0.0004)");
	AddLineQueue("DBL_NEG0D0005 EQU (-0.0005)");
	AddLineQueue("DBL_NEG0D0006 EQU (-0.0006)");
	AddLineQueue("DBL_NEG0D0007 EQU (-0.0007)");
	AddLineQueue("DBL_NEG0D0008 EQU (-0.0008)");
	AddLineQueue("DBL_NEG0D0009 EQU (-0.0009)");
	AddLineQueue("DBL_NEG0D001 EQU (-0.001)");
	AddLineQueue("DBL_NEG0D002 EQU (-0.002)");
	AddLineQueue("DBL_NEG0D003 EQU (-0.003)");
	AddLineQueue("DBL_NEG0D004 EQU (-0.004)");
	AddLineQueue("DBL_NEG0D005 EQU (-0.005)");
	AddLineQueue("DBL_NEG0D006 EQU (-0.006)");
	AddLineQueue("DBL_NEG0D007 EQU (-0.007)");
	AddLineQueue("DBL_NEG0D008 EQU (-0.008)");
	AddLineQueue("DBL_NEG0D009 EQU (-0.009)");
	AddLineQueue("DBL_NEG0D01 EQU (-0.01)");
	AddLineQueue("DBL_NEG0D02 EQU (-0.02)");
	AddLineQueue("DBL_NEG0D025 EQU (-0.025)");
	AddLineQueue("DBL_NEG0D03 EQU (-0.03)");
	AddLineQueue("DBL_NEG0D04 EQU (-0.04)");
	AddLineQueue("DBL_NEG0D05 EQU (-0.05)");
	AddLineQueue("DBL_NEG0D06 EQU (-0.06)");
	AddLineQueue("DBL_NEG0D07 EQU (-0.07)");
	AddLineQueue("DBL_NEG0D08 EQU (-0.08)");
	AddLineQueue("DBL_NEG0D09 EQU (-0.09)");
	AddLineQueue("DBL_NEG0D1 EQU (-0.1)");
	AddLineQueue("DBL_NEG0D2 EQU (-0.2)");
	AddLineQueue("DBL_NEG0D25 EQU (-0.25)");
	AddLineQueue("DBL_NEG0D3 EQU (-0.3)");
	AddLineQueue("DBL_NEG0D4 EQU (-0.4)");
	AddLineQueue("DBL_NEG0D5 EQU (-0.5)");
	AddLineQueue("DBL_NEG0D6 EQU (-0.6)");
	AddLineQueue("DBL_NEG0D7 EQU (-0.7)");
	AddLineQueue("DBL_NEG0D8 EQU (-0.8)");
	AddLineQueue("DBL_NEG0D9 EQU (-0.9)");
	AddLineQueue("DBL_NEG1 EQU (-1.0)");
	AddLineQueue("DBL_NEG1D25 EQU (-1.25)");
	AddLineQueue("DBL_NEG1D5 EQU (-1.5)");
	AddLineQueue("DBL_NEG2 EQU (-2.0)");
	AddLineQueue("DBL_NEG2D25 EQU (-2.25)");
	AddLineQueue("DBL_NEG2D5 EQU (-2.5)");
	AddLineQueue("DBL_NEG3 EQU (-3.0)");
	AddLineQueue("DBL_NEG3D25 EQU (-3.25)");
	AddLineQueue("DBL_NEG3D5 EQU (-3.5)");
	AddLineQueue("DBL_NEG4 EQU (-4.0)");
	AddLineQueue("DBL_NEG4D25 EQU (-4.25)");
	AddLineQueue("DBL_NEG4D5 EQU (-4.5)");
	AddLineQueue("DBL_NEG5 EQU (-5.0)");
	AddLineQueue("DBL_NEG5D25 EQU (-5.25)");
	AddLineQueue("DBL_NEG5D5 EQU (-5.5)");
	AddLineQueue("DBL_NEG6 EQU (-6.0)");
	AddLineQueue("DBL_NEG6D25 EQU (-6.25)");
	AddLineQueue("DBL_NEG6D5 EQU (-6.5)");
	AddLineQueue("DBL_NEG7 EQU (-7.0)");
	AddLineQueue("DBL_NEG7D25 EQU (-7.25)");
	AddLineQueue("DBL_NEG7D5 EQU (-7.5)");
	AddLineQueue("DBL_NEG8 EQU (-8.0)");
	AddLineQueue("DBL_NEG8D25 EQU (-8.25)");
	AddLineQueue("DBL_NEG8D5 EQU (-8.5)");
	AddLineQueue("DBL_NEG9 EQU (-9.0)");
	AddLineQueue("DBL_NEG9D25 EQU (-9.25)");
	AddLineQueue("DBL_NEG9D5 EQU (-9.5)");
	AddLineQueue("DBL_NEG10 EQU (-10.0)");
	AddLineQueue("DBL_NEG11 EQU (-11.0)");
	AddLineQueue("DBL_NEG12 EQU (-12.0)");
	AddLineQueue("DBL_NEG13 EQU (-13.0)");
	AddLineQueue("DBL_NEG14 EQU (-14.0)");
	AddLineQueue("DBL_NEG15 EQU (-15.0)");
	AddLineQueue("DBL_NEG16 EQU (-16.0)");
	AddLineQueue("DBL_NEG17 EQU (-17.0)");
	AddLineQueue("DBL_NEG18 EQU (-18.0)");
	AddLineQueue("DBL_NEG19 EQU (-19.0)");
	AddLineQueue("DBL_NEG20 EQU (-20.0)");
	AddLineQueue("DBL_NEG21 EQU (-21.0)");
	AddLineQueue("DBL_NEG22 EQU (-22.0)");
	AddLineQueue("DBL_NEG23 EQU (-23.0)");
	AddLineQueue("DBL_NEG24 EQU (-24.0)");
	AddLineQueue("DBL_NEG24D5 EQU (-24.5)");
	AddLineQueue("DBL_NEG25 EQU (-25.0)");
	AddLineQueue("DBL_NEG26 EQU (-26.0)");
	AddLineQueue("DBL_NEG27 EQU (-27.0)");
	AddLineQueue("DBL_NEG28 EQU (-28.0)");
	AddLineQueue("DBL_NEG29 EQU (-29.0)");
	AddLineQueue("DBL_NEG30 EQU (-30.0)");
	AddLineQueue("DBL_NEG31 EQU (-31.0)");
	AddLineQueue("DBL_NEG32 EQU (-32.0)");
	AddLineQueue("DBL_NEG33 EQU (-33.0)");
	AddLineQueue("DBL_NEG34 EQU (-34.0)");
	AddLineQueue("DBL_NEG35 EQU (-35.0)");
	AddLineQueue("DBL_NEG36 EQU (-36.0)");
	AddLineQueue("DBL_NEG37 EQU (-37.0)");
	AddLineQueue("DBL_NEG38 EQU (-38.0)");
	AddLineQueue("DBL_NEG39 EQU (-39.0)");
	AddLineQueue("DBL_NEG40 EQU (-40.0)");
	AddLineQueue("DBL_NEG41 EQU (-41.0)");
	AddLineQueue("DBL_NEG42 EQU (-42.0)");
	AddLineQueue("DBL_NEG43 EQU (-43.0)");
	AddLineQueue("DBL_NEG44 EQU (-44.0)");
	AddLineQueue("DBL_NEG45 EQU (-45.0)");
	AddLineQueue("DBL_NEG46 EQU (-46.0)");
	AddLineQueue("DBL_NEG47 EQU (-47.0)");
	AddLineQueue("DBL_NEG48 EQU (-48.0)");
	AddLineQueue("DBL_NEG49 EQU (-49.0)");
	AddLineQueue("DBL_NEG50 EQU (-50.0)");
	AddLineQueue("DBL_NEG51 EQU (-51.0)");
	AddLineQueue("DBL_NEG52 EQU (-52.0)");
	AddLineQueue("DBL_NEG53 EQU (-53.0)");
	AddLineQueue("DBL_NEG54 EQU (-54.0)");
	AddLineQueue("DBL_NEG55 EQU (-55.0)");
	AddLineQueue("DBL_NEG56 EQU (-56.0)");
	AddLineQueue("DBL_NEG57 EQU (-57.0)");
	AddLineQueue("DBL_NEG58 EQU (-58.0)");
	AddLineQueue("DBL_NEG59 EQU (-59.0)");
	AddLineQueue("DBL_NEG60 EQU (-60.0)");
	AddLineQueue("DBL_NEG61 EQU (-61.0)");
	AddLineQueue("DBL_NEG62 EQU (-62.0)");
	AddLineQueue("DBL_NEG63 EQU (-63.0)");
	AddLineQueue("DBL_NEG64 EQU (-64.0)");
	AddLineQueue("DBL_NEG65 EQU (-65.0)");
	AddLineQueue("DBL_NEG66 EQU (-66.0)");
	AddLineQueue("DBL_NEG67 EQU (-67.0)");
	AddLineQueue("DBL_NEG68 EQU (-68.0)");
	AddLineQueue("DBL_NEG69 EQU (-69.0)");
	AddLineQueue("DBL_NEG70 EQU (-70.0)");
	AddLineQueue("DBL_NEG71 EQU (-71.0)");
	AddLineQueue("DBL_NEG72 EQU (-72.0)");
	AddLineQueue("DBL_NEG73 EQU (-73.0)");
	AddLineQueue("DBL_NEG74 EQU (-74.0)");
	AddLineQueue("DBL_NEG75 EQU (-75.0)");
	AddLineQueue("DBL_NEG76 EQU (-76.0)");
	AddLineQueue("DBL_NEG77 EQU (-77.0)");
	AddLineQueue("DBL_NEG78 EQU (-78.0)");
	AddLineQueue("DBL_NEG79 EQU (-79.0)");
	AddLineQueue("DBL_NEG80 EQU (-80.0)");
	AddLineQueue("DBL_NEG81 EQU (-81.0)");
	AddLineQueue("DBL_NEG82 EQU (-82.0)");
	AddLineQueue("DBL_NEG83 EQU (-83.0)");
	AddLineQueue("DBL_NEG84 EQU (-84.0)");
	AddLineQueue("DBL_NEG85 EQU (-85.0)");
	AddLineQueue("DBL_NEG86 EQU (-86.0)");
	AddLineQueue("DBL_NEG87 EQU (-87.0)");
	AddLineQueue("DBL_NEG88 EQU (-88.0)");
	AddLineQueue("DBL_NEG89 EQU (-89.0)");
	AddLineQueue("DBL_NEG90 EQU (-90.0)");
	AddLineQueue("DBL_NEG91 EQU (-91.0)");
	AddLineQueue("DBL_NEG92 EQU (-92.0)");
	AddLineQueue("DBL_NEG93 EQU (-93.0)");
	AddLineQueue("DBL_NEG94 EQU (-94.0)");
	AddLineQueue("DBL_NEG95 EQU (-95.0)");
	AddLineQueue("DBL_NEG96 EQU (-96.0)");
	AddLineQueue("DBL_NEG97 EQU (-97.0)");
	AddLineQueue("DBL_NEG98 EQU (-98.0)");
	AddLineQueue("DBL_NEG99 EQU (-99.0)");
	AddLineQueue("DBL_NEG100 EQU (-100.0)");
	AddLineQueue("DBL_NEG125 EQU (-125.0)");
	AddLineQueue("DBL_NEG126 EQU (-126.0)");
	AddLineQueue("DBL_NEG127 EQU (-127.0)");
	AddLineQueue("DBL_NEG128 EQU (-128.0)");
	AddLineQueue("DBL_NEG140 EQU (-140.0)");
	AddLineQueue("DBL_NEG145 EQU (-145.0)");
	AddLineQueue("DBL_NEG150 EQU (-150.0)");
	AddLineQueue("DBL_NEG180 EQU (-180.0)");
	AddLineQueue("DBL_NEG253 EQU (-253.0)");
	AddLineQueue("DBL_NEG254 EQU (-254.0)");
	AddLineQueue("DBL_NEG255 EQU (-255.0)");
	AddLineQueue("DBL_NEG256 EQU (-256.0)");
	AddLineQueue("DBL_NEG360 EQU (-360.0)");
	AddLineQueue("DBL_NEG511 EQU (-511.0)");
	AddLineQueue("DBL_NEG512 EQU (-512.0)");
	AddLineQueue("DBL_NEG513 EQU (-513.0)");
	AddLineQueue("DBL_NEG1023 EQU (-1023.0)");
	AddLineQueue("DBL_NEG1024 EQU (-1024.0)");
	AddLineQueue("DBL_NEG1025 EQU (-1025.0)");

	AddLineQueue("DBL_NEG32767 EQU (-32767.0)");
	AddLineQueue("DBL_NEG32768 EQU (-32768.0)");
	AddLineQueue("DBL_NEG65535 EQU (-65535.0)");
	AddLineQueue("DBL_NEG65536 EQU (-65536.0)");
	AddLineQueue("DBL_NEG2147483647 EQU (-2147483647.0)");
	AddLineQueue("DBL_NEG2147483648 EQU (-2147483648.0)");
	AddLineQueue("DBL_NEG4294967295 EQU (-4294967295.0)");
	AddLineQueue("DBL_NEG4294967296 EQU (-4294967296.0)");

	AddLineQueue("DBL_BIN128 EQU DBL_128_MSK");
	AddLineQueue("DBL_BINNEG150 EQU DBL_NEG150_MSK");

	AddLineQueue("DBL_MAXRAND EQU 32767.0");

	AddLineQueue("DBL_MAXI8 EQU 127.0");
	AddLineQueue("DBL_MINI8 EQU (-128.0)");
	AddLineQueue("DBL_MAXU8 EQU 255.0");

	AddLineQueue("DBL_MAXI16 EQU 32767.0");
	AddLineQueue("DBL_MINI16 EQU (-32768.0)");
	AddLineQueue("DBL_MAXU16 EQU 65535.0");

	AddLineQueue("DBL_MAXI32 EQU 2147483647.0");
	AddLineQueue("DBL_MINI32 EQU (-2147483648.0)");
	AddLineQueue("DBL_MAXU32 EQU 4294967295.0");

	AddLineQueue("DBL_MAXI64 EQU 9223372036854775807.0");
	AddLineQueue("DBL_MINI64 EQU (-9223372036854775808.0)");
	AddLineQueue("DBL_MAXU64 EQU 18446744073709551615.0");

	AddLineQueue("DBL_MAXI8XU8 EQU 32768.0");
	AddLineQueue("DBL_MINI8XU8 EQU (-32768.0)");
	AddLineQueue("DBL_MAXI8XU16 EQU 8388608.0");
	AddLineQueue("DBL_MINI8XU16 EQU (-8388608.0)");

	AddLineQueue("DBL_MAXI16XU16 EQU 2147483648.0");
	AddLineQueue("DBL_MINI16XU16 EQU (-2147483648.0)");
	AddLineQueue("DBL_MAXI16XU32 EQU 140737488355328.0");
	AddLineQueue("DBL_MINI16XU32 EQU (-140737488355328.0)");

	AddLineQueue("DBL_MAXI32XU32 EQU (-9223372036854775808.0)");
	AddLineQueue("DBL_MINI32XU32 EQU (-9223372036854775808.0)");

	AddLineQueue("DBL_FIXUNSIGNED EQU (-2147483648.0)");
	AddLineQueue("DBL_FIXUNSIGNED32	EQU (-2147483648.0)");
	AddLineQueue("DBL_FIXMAXI32 EQU 2147483520.0");
	AddLineQueue("DBL_FIXMAXU32 EQU (-256.0)");

	AddLineQueue("DBL_FIXUNSIGNED64	EQU (-9223372036854775808.0)");
	AddLineQueue("DBL_FIXMAXI64 EQU 9223372036854773760.0");
	AddLineQueue("DBL_FIXMAXU64 EQU (-4096.0)");

	AddLineQueue("DBL_RCPI16 EQU 3.0518509475997192297128208258309e-5");
	AddLineQueue("DBL_RCPU16 EQU 0.0000152587890625");
	AddLineQueue("DBL_RCPI16XU16 EQU 4.656754985961485641041291543321e-10");

	AddLineQueue("DBL_MG EQU 1024.0");
	AddLineQueue("DBL_NEGMG EQU (-1024.0)");
	AddLineQueue("DBL_HALFMG EQU 512.0");
	AddLineQueue("DBL_NEGHALFMG EQU (-512.0)");
	AddLineQueue("DBL_MGDIV4 EQU 256.0");
	AddLineQueue("DBL_NEGMGDIV4 EQU (-256.0)");
	AddLineQueue("DBL_HALFMGXMG EQU 524288.0");
	AddLineQueue("DBL_HALFMGXSQRMG EQU 536870912.0");
	AddLineQueue("DBL_HALFMGXCUBEMG EQU 549755813888.0");
	AddLineQueue("DBL_NEGHALFMGXMG EQU (-524288.0)");
	AddLineQueue("DBL_NEGHALFMGXSQRMG EQU (-536870912.0)");
	AddLineQueue("DBL_NEGHALFMGXCUBEMG EQU (-549755813888.0)");
	AddLineQueue("DBL_SQRMG EQU 1048576.0");
	AddLineQueue("DBL_CUBEMG EQU 1073741824.0");
	AddLineQueue("DBL_SQRTMG EQU 32.0");
	AddLineQueue("DBL_CBRTMG EQU 10.079368399158985318137684858226");
	AddLineQueue("DBL_RCPMG EQU 0.0009765625");
	AddLineQueue("DBL_RCPSQRMG EQU 0.00000095367431640625");
	AddLineQueue("DBL_RCPCUBEMG EQU 0.000000000931322574615478515625");
	AddLineQueue("DBL_RCPSQRTMG EQU 0.03125");
	AddLineQueue("DBL_RCPCBRTMG EQU 0.09921256574801246717198160245452");

	AddLineQueue("DBL_2MG EQU 2048.0");
	AddLineQueue("DBL_NEG2MG EQU (-2048.0)");
	AddLineQueue("DBL_SQR2MG EQU 4194304.0");
	AddLineQueue("DBL_CUBE2MG EQU 8589934592.0");
	AddLineQueue("DBL_SQRT2MG EQU 45.25483399593904156165403917471");
	AddLineQueue("DBL_CBRT2MG EQU 12.699208415745595798013645114178");
	AddLineQueue("DBL_4MG EQU 4096.0");
	AddLineQueue("DBL_NEG4MG EQU (-4096.0)");
	AddLineQueue("DBL_SQR4MG EQU 16777216.0");
	AddLineQueue("DBL_CUBE4MG EQU 68719476736.0");
	AddLineQueue("DBL_SQRT4MG EQU 64.0");
	AddLineQueue("DBL_CBRT4MG EQU 16.0");
	AddLineQueue("DBL_RCP2MG EQU 0.00048828125");
	AddLineQueue("DBL_RCP4MG EQU 0.000244140625");

	AddLineQueue("DBL_E EQU 2.71828182845904523536");
	AddLineQueue("DBL_EXP EQU 2.71828182845904523536");
	AddLineQueue("DBL_LOGE EQU 0.43429448190325182765108299019028");
	AddLineQueue("DBL_LOGEHIGH EQU 0.43429448190325182765108299019028");
	AddLineQueue("DBL_LOGELOW EQU 1.09831965021676510e-17");
	AddLineQueue("DBL_LOG2E EQU 1.44269504088896340736");
	AddLineQueue("DBL_LOG2EHIGH EQU 1.44269504088896340736");
	AddLineQueue("DBL_LOG2ELOW EQU 2.0355273740931033e-17");
	AddLineQueue("DBL_LOG10E EQU 0.43429448190325182765108299019028");
	AddLineQueue("DBL_RCPLOG2E EQU 0.69314718055994530941719593421853");
	AddLineQueue("DBL_RCPLOG10E EQU 2.3025850929940456840186749696447");
	AddLineQueue("DBL_LOG2T EQU 3.3219280948873622");
	AddLineQueue("DBL_LOG2 EQU 0.30102999566398119521373889472449");
	AddLineQueue("DBL_LOG2HIGH EQU 0.30102999566398119521373889472449");
	AddLineQueue("DBL_LOG2LOW EQU (-2.8037281277851704e-18)");
	AddLineQueue("DBL_LN2 EQU 0.69314718055994530941723212145818");
	AddLineQueue("DBL_LN2HIGH EQU 0.69314718055994530941723212145818");
	AddLineQueue("DBL_LN2LOW EQU 2.3190468138462996e-17");
	AddLineQueue("DBL_1DIVLN2 EQU 1.4426950408889634073599246810019");
	AddLineQueue("DBL_2DIVLN2 EQU 2.8853900817779268147198493620038");
	AddLineQueue("DBL_LNT EQU 2.3025850929940459");
	AddLineQueue("DBL_LNTHIGH EQU 2.3025850929940459e+0");
	AddLineQueue("DBL_LNTLOW EQU (-2.1707562233822494e-16)");
	AddLineQueue("DBL_LN10 EQU 2.302585092994045684018");
	AddLineQueue("DBL_SQRT2 EQU 1.414213562373095048801");
	AddLineQueue("DBL_RCPSQRT2 EQU 0.707106781186547524400");
	AddLineQueue("DBL_SQRT2DIV2 EQU 0.707106781186547524400");
	AddLineQueue("DBL_SQRT2DIV2HIGH EQU 0.707106781186547524400");
	AddLineQueue("DBL_SQRT2DIV2LOW EQU 1.210161749e-08");
	AddLineQueue("DBL_SQRTHALF EQU 0.707106781186547524401");
	AddLineQueue("DBL_SQRTHALFHIGH EQU 0.707106781186547524401");
	AddLineQueue("DBL_SQRTHALFLOW EQU (-4.8336466567264567e-17)");
	AddLineQueue("DBL_POW2 EQU 7.389056098930650227230");
	AddLineQueue("DBL_RCPOW2 EQU 0.135335283236612691893");
	AddLineQueue("DBL_CBRT2 EQU 1.259921049894873164767");
	AddLineQueue("DBL_RCPCBRT2 EQU 0.793700525984099737375");
	AddLineQueue("DBL_1DIV3 EQU 0.333333333333333333333");
	AddLineQueue("DBL_1DIV7 EQU 0.142857142857142857142");
	AddLineQueue("DBL_1DIV9 EQU 0.111111111111111111111");
	AddLineQueue("DBL_2DIV3 EQU 0.666666666666666666667");
	AddLineQueue("DBL_2DIV7 EQU 0.285714285714285714285");
	AddLineQueue("DBL_2DIV9 EQU 0.222222222222222222222");
	AddLineQueue("DBL_4DIV3 EQU 1.333333333333333333333");
	AddLineQueue("DBL_4DIV7 EQU 0.571428571428571428571");
	AddLineQueue("DBL_4DIV9 EQU 0.444444444444444444444");

	AddLineQueue("DBL_PI EQU 3.1415926535897932384626433832795");
	AddLineQueue("DBL_PIHIGH EQU 3.1415926535897932384626433832795");
	AddLineQueue("DBL_PILOW EQU 1.2246467991473532e-16");
	AddLineQueue("DBL_HALFPI EQU 1.5707963267948966192313216916398");
	AddLineQueue("DBL_2PI EQU 6.283185307179586476925286766559");
	AddLineQueue("DBL_NEGPI EQU (-3.1415926535897932384626433832795)");
	AddLineQueue("DBL_NEGHALFPI EQU (-1.5707963267948966192313216916398)");
	AddLineQueue("DBL_NEG2PI EQU (-6.283185307179586476925286766559)");
	AddLineQueue("DBL_RCPPI EQU 0.31830988618379067153776752674503");
	AddLineQueue("DBL_INVPI EQU 0.31830988618379067153776752674503");
	AddLineQueue("DBL_RCP2PI EQU 0.15915494309189533576888376337251");
	AddLineQueue("DBL_INV2PI EQU 0.15915494309189533576888376337251");
	AddLineQueue("DBL_PIDIV2 EQU 1.5707963267948966192313216916398");
	AddLineQueue("DBL_PIDIV2HIGH EQU 1.5707963267948966192313216916398");
	AddLineQueue("DBL_PIDIV2LOW EQU 6.1232339957367660e-17");
	AddLineQueue("DBL_PIDIV4 EQU 0.78539816339744830961566084581988");
	AddLineQueue("DBL_PIDIV4HIGH EQU 0.78539816339744830961566084581988");
	AddLineQueue("DBL_PIDIV4LOW EQU 3.0616169978683830e-17");
	AddLineQueue("DBL_PIx3DIV4 EQU 2.3561944901923449288469825374596");
	AddLineQueue("DBL_SQRTPI EQU 1.7724538509055160272981674833411");
	AddLineQueue("DBL_SQRT2PI EQU 2.506628274631000502415765284811");
	AddLineQueue("DBL_SQRT2PIHIGH EQU 2.506628274631000502415765284811");
	AddLineQueue("DBL_SQRT2PILOW EQU (-1.8328579980459167e-16)");
	AddLineQueue("DBL_RCPSQRTPI EQU 0.56418958354775628694807945156077");
	AddLineQueue("DBL_RCPSQRT2PI EQU 0.39894228040143267793994605993438");
	AddLineQueue("DBL_SQRTPIDIV2 EQU 0.88622692545275801364908374167057");
	AddLineQueue("DBL_SQRTPIDIV2HIGH EQU 0.88622692545275801364908374167057");
	AddLineQueue("DBL_SQRT2PIDIV2 EQU 1.2533141373155002512078826424055");
	AddLineQueue("DBL_SQRT2PIDIV2HIGH EQU 1.2533141373155002512078826424055");
	AddLineQueue("DBL_SQRT2PIDIV2LOW EQU (-9.1642899902295834e-17)");
	AddLineQueue("DBL_2DIVPI EQU 0.63661977236758134307553505349006");
	AddLineQueue("DBL_2DIV2PI EQU 0.31830988618379067153776752674503");
	AddLineQueue("DBL_2DIVSQRTPI EQU 1.1283791670955125738961589031216");
	AddLineQueue("DBL_2DIVSQRT2PI EQU 0.79788456080286535587989211986878");
	AddLineQueue("DBL_SQRT2DIVPI EQU 0.45015815807855303477759959550337");
	AddLineQueue("DBL_LOGPI EQU 0.4971498726941338543512682882909");
	AddLineQueue("DBL_LOG2PI EQU 0.4971498726941338543512682882909");
	AddLineQueue("DBL_LNPI EQU 1.1447298858494001741434273513531");
	AddLineQueue("DBL_LN2PI EQU 1.8378770664093454835606594728112");
	AddLineQueue("DBL_POWPI EQU 23.140692632779269005729086367949");
	AddLineQueue("DBL_RCPOWPI EQU 0.04321391826377224977441773717173");
	AddLineQueue("DBL_POW2PI EQU 535.49165552476473650304932958905");
	AddLineQueue("DBL_RCPOW2PI EQU 0.00186744273170798881443021293483");
	AddLineQueue("DBL_CBRTPI EQU 1.4645918875615232630201425272638");
	AddLineQueue("DBL_RCPCBRTPI EQU 0.68278406325529568146702083315816");
	AddLineQueue("DBL_CBRT2PI EQU 1.845270148644028419096803879589");
	AddLineQueue("DBL_RCPCBRT2PI EQU 0.54192607013928900874456136482964");

	AddLineQueue("DBL_LN2X1024 EQU 709.78271289338399684324569237317");
	AddLineQueue("DBL_LN2X1025 EQU 710.47586007394394215266292449463");
	AddLineQueue("DBL_LN2X1075 EQU 745.13321910194120762352453056754");
	AddLineQueue("DBL_LOG2X1024 EQU 308.25471555991674389886862819788");
	AddLineQueue("DBL_LOG2X1075 EQU 323.60724533877978485476931182883");

	AddLineQueue("DBL_POW2TOM126 EQU 1.175494351e-38");
	AddLineQueue("DBL_POW2TO126 EQU 8.507059173e37");
	AddLineQueue("DBL_NORMHUGE EQU 3.402823466e38");
	AddLineQueue("DBL_POW2TO23 EQU 8388608.0");
	AddLineQueue("DBL_POW2TO24 EQU 16777216.0");
	AddLineQueue("DBL_MAXI32POW2TO23 EQU 2139095039.0");
	AddLineQueue("DBL_POW2TO31 EQU 2147483648.0");
	AddLineQueue("DBL_POW2TO32 EQU 4294967296.0");
	AddLineQueue("DBL_POW2TO52 EQU 4503599627370496.0");
	AddLineQueue("DBL_POW2TO53 EQU 9007199254740992.0");
	AddLineQueue("DBL_POW2TO54 EQU 18014398509481984.0");
	AddLineQueue("DBL_POW2TOM54 EQU 5.5511151231257827e-17");
	AddLineQueue("DBL_POW2TO62 EQU 4611686018427387904.0");
	AddLineQueue("DBL_MAXI64POW2TO52 EQU 9218868437227405311.0");
	AddLineQueue("DBL_POW2TO63 EQU 9223372036854775808.0");
	AddLineQueue("DBL_POW2TO64 EQU 18446744073709551616.0");
	AddLineQueue("DBL_POW2TOM1022 EQU 2.22507385850720140e-308");
	AddLineQueue("DBL_TRIGPLOSS EQU 2147483648.0");

	AddLineQueue("DBL_DEGTORAD EQU 0.017453292519943295769");
	AddLineQueue("DBL_RADTODEG EQU 57.29577951308232087679");

	AddLineQueue("DBL_DEGTOGRAD EQU 1.111111111111111111111");
	AddLineQueue("DBL_GRADTODEG EQU 0.9");

	AddLineQueue("DBL_RADTOGRAD EQU 63.66197723675813430755");
	AddLineQueue("DBL_GRADTORAD EQU 0.015707963267948966192");

	// Gravity 

	AddLineQueue("DBL_SUNGRAVITY EQU 274.13");
	AddLineQueue("DBL_JUPIterGRAVITY EQU 25.95");
	AddLineQueue("DBL_NRPTUNEGRAVITY EQU 14.07");
	AddLineQueue("DBL_SATURNGRAVITY EQU 11.08");
	AddLineQueue("DBL_URANUSGRAVITY EQU 10.67");
	AddLineQueue("DBL_EARTHGRAVITY EQU 9.81");
	AddLineQueue("DBL_VENUSGRAVITY EQU 8.87");
	AddLineQueue("DBL_MARSGRAVITY EQU 3.77");
	AddLineQueue("DBL_MERCURYGRAVITY EQU 3.59");
	AddLineQueue("DBL_MOONGRAVITY EQU 1.62");
	AddLineQueue("DBL_PLUTOGRAVITY EQU 0.42");

	// Length conversion

	AddLineQueue("DBL_KMTOINCH EQU 39370.08");
	AddLineQueue("DBL_KMTOFEET EQU 3280.84");
	AddLineQueue("DBL_KMTOYARDS EQU 1093.613");
	AddLineQueue("DBL_KMTOMILES EQU 0.621371");

	AddLineQueue("DBL_METOINCH EQU 39.37008");
	AddLineQueue("DBL_METOFEET EQU 3.28084");
	AddLineQueue("DBL_METOYARDS EQU 1.093613");
	AddLineQueue("DBL_METOMILES EQU 0.000621371");

	AddLineQueue("DBL_CMTOINCH EQU 0.3937008");
	AddLineQueue("DBL_CMTOFEET EQU 0.0328084");
	AddLineQueue("DBL_CMTOYARDS EQU 0.01093613");
	AddLineQueue("DBL_CMTOMILES EQU 0.00000621371");

	AddLineQueue("DBL_MILLTOINCH EQU 0.03937008");
	AddLineQueue("DBL_MILLTOFEET EQU 0.00328084");
	AddLineQueue("DBL_MILLTOYARDS EQU 0.001093613");
	AddLineQueue("DBL_MILLTOMILES EQU 0.000000621371");

	AddLineQueue("DBL_INCHTOMILL EQU 25.4");
	AddLineQueue("DBL_INCHTOCM EQU 2.54");
	AddLineQueue("DBL_INCHTOME EQU 0.0254");
	AddLineQueue("DBL_INCHTOKM EQU 0.0000254");
	AddLineQueue("DBL_INCHTOFEET EQU 0.083333");
	AddLineQueue("DBL_INCHTOYARDS EQU 0.027778");
	AddLineQueue("DBL_INCHTOMILES EQU 0.000016");

	AddLineQueue("DBL_FEETTOMILL EQU 304.8");
	AddLineQueue("DBL_FEETTOCM EQU 30.48");
	AddLineQueue("DBL_FEETTOME EQU 0.3048");
	AddLineQueue("DBL_FEETTOKM EQU 0.0003048");
	AddLineQueue("DBL_FEETTOINCH EQU 12.0");
	AddLineQueue("DBL_FEETTOYARDS EQU 0.333333");
	AddLineQueue("DBL_FEETTOMILES EQU 0.000189");

	AddLineQueue("DBL_YARDSTOMILL EQU 914.4");
	AddLineQueue("DBL_YARDSTOCM EQU 91.44");
	AddLineQueue("DBL_YARDSTOME EQU 0.9144");
	AddLineQueue("DBL_YARDSTOKM EQU 0.0009144");
	AddLineQueue("DBL_YARDSTOINCH EQU 36.0");
	AddLineQueue("DBL_YARDSTOFEET EQU 3.0");
	AddLineQueue("DBL_YARDSTOMILES EQU 0.000568");

	AddLineQueue("DBL_MILESTOMILL EQU 1609344.0");
	AddLineQueue("DBL_MILESTOCM EQU 160934.4");
	AddLineQueue("DBL_MILESTOME EQU 1609.344");
	AddLineQueue("DBL_MILESTOKM EQU 1.609344");
	AddLineQueue("DBL_MILESTOINCH EQU 63360.0");
	AddLineQueue("DBL_MILESTOFEET EQU 5280.0");
	AddLineQueue("DBL_MILESTOYARDS EQU 1760.0");

	// Speed conversion

	AddLineQueue("DBL_KMPHTOMEPS EQU 0.27777777777778");
	AddLineQueue("DBL_KMPHTOKMPS EQU 0.00027777777777778");
	AddLineQueue("DBL_KMPHTOMEPM EQU 16.666666666667");
	AddLineQueue("DBL_KMPHTOMILESPH EQU 0.62137119223733");
	AddLineQueue("DBL_KMPHTOMILESPS EQU 0.00017260310895481");
	AddLineQueue("DBL_KMPHTOFOOTPS EQU 0.91134444444444");
	AddLineQueue("DBL_KMPHTOFOOTPM EQU 54.680666666667");

	AddLineQueue("DBL_KMPSTOMEPS EQU 1000.0");
	AddLineQueue("DBL_KMPSTOKMPH EQU 3600.0");
	AddLineQueue("DBL_KMPSTOMEPM EQU 60000.0");
	AddLineQueue("DBL_KMPSTOMILESPH EQU 2236.9362920544");
	AddLineQueue("DBL_KMPSTOMILESPS EQU 0.62137119223733");
	AddLineQueue("DBL_KMPSTOFOOTPS EQU 3280.84");
	AddLineQueue("DBL_KMPSTOFOOTPM EQU 196850.4");

	AddLineQueue("DBL_MEPSTOKMPH EQU 3.6");
	AddLineQueue("DBL_MEPSTOKMPS EQU 0.001");
	AddLineQueue("DBL_MEPSTOMEPM EQU 60.0");
	AddLineQueue("DBL_MEPSTOMILESPH EQU 2.2369362920544");
	AddLineQueue("DBL_MEPSTOMILESPS EQU 0.00062137119223733");
	AddLineQueue("DBL_MEPSTOFOOTPS EQU 3280.84");
	AddLineQueue("DBL_MEPSTOFOOTPM EQU 196850.4");

	AddLineQueue("DBL_MEPMTOKMPH EQU 0.06");
	AddLineQueue("DBL_MEPMTOKMPS EQU 1.6666666666667e-5");
	AddLineQueue("DBL_MEPMTOMEPS EQU 0.016666666666667");
	AddLineQueue("DBL_MEPMTOMILESPH EQU 0.03728227153424");
	AddLineQueue("DBL_MEPMTOMILESPS EQU 1.0356186537289e-5");
	AddLineQueue("DBL_MEPMTOFOOTPS EQU 0.054680666666667");
	AddLineQueue("DBL_MEPMTOFOOTPM EQU 3.28084");

	AddLineQueue("DBL_MILESPHTOKMPH EQU 1.609344");
	AddLineQueue("DBL_MILESPHTOKMPS EQU 0.00044704");
	AddLineQueue("DBL_MILESPHTOMEPS EQU 0.44704");
	AddLineQueue("DBL_MILESPHTOMEPM EQU 26.8224");
	AddLineQueue("DBL_MILESPHTOMILESPS EQU 0.00027777777777778");
	AddLineQueue("DBL_MILESPHTOFOOTPS EQU 1.4666667136");
	AddLineQueue("DBL_MILESPHTOFOOTPM EQU 88.000002816");

	AddLineQueue("DBL_MILESPSTOKMPH EQU 5793.6384");
	AddLineQueue("DBL_MILESPSTOKMPS EQU 1.609344");
	AddLineQueue("DBL_MILESPSTOMEPS EQU 1609.344");
	AddLineQueue("DBL_MILESPSTOMEPM EQU 96560.64");
	AddLineQueue("DBL_MILESPSTOMILESPH EQU 3600.0");
	AddLineQueue("DBL_MILESPSTOFOOTPS EQU 5280.00016896");
	AddLineQueue("DBL_MILESPSTOFOOTPM EQU 316800.0101376");

	AddLineQueue("DBL_FOOTPSTOKMPH EQU 1.097279964887");
	AddLineQueue("DBL_FOOTPSTOKMPS EQU 0.0003047999902464");
	AddLineQueue("DBL_FOOTPSTOMEPS EQU 0.3047999902464");
	AddLineQueue("DBL_FOOTPSTOMEPM EQU 18.287999414784");
	AddLineQueue("DBL_FOOTPSTOMILESPH EQU 0.68181816");
	AddLineQueue("DBL_FOOTPSTOMILESPS EQU 0.00018939393333333");
	AddLineQueue("DBL_FOOTPSTOFOOTPM EQU 60.0");

	AddLineQueue("DBL_FOOTPMTOKMPH EQU 0.018287999414784");
	AddLineQueue("DBL_FOOTPMTOKMPS EQU 5.07999983744e-6");
	AddLineQueue("DBL_FOOTPMTOMEPS EQU 0.00507999983744");
	AddLineQueue("DBL_FOOTPMTOMEPM EQU 0.3047999902464");
	AddLineQueue("DBL_FOOTPMTOMILESPH EQU 0.011363636");
	AddLineQueue("DBL_FOOTPMTOMILESPS EQU 3.1565655555556e-6");
	AddLineQueue("DBL_FOOTPMTOFOOTPS EQU 0.016666666666667");

	// Sound Speed on Air

	AddLineQueue("DBL_SOUNDSPEEDP50C EQU 360.35");
	AddLineQueue("DBL_SOUNDSPEEDP45C EQU 357.551");
	AddLineQueue("DBL_SOUNDSPEEDP40C EQU 354.73");
	AddLineQueue("DBL_SOUNDSPEEDP35C EQU 351.887");
	AddLineQueue("DBL_SOUNDSPEEDP30C EQU 349.02");
	AddLineQueue("DBL_SOUNDSPEEDP25C EQU 346.13");
	AddLineQueue("DBL_SOUNDSPEEDP20C EQU 343.216");
	AddLineQueue("DBL_SOUNDSPEEDP15C EQU 340.276");
	AddLineQueue("DBL_SOUNDSPEEDP10C EQU 337.311");
	AddLineQueue("DBL_SOUNDSPEEDP5C EQU 334.319");
	AddLineQueue("DBL_SOUNDSPEED0C EQU 331.301");
	AddLineQueue("DBL_SOUNDSPEEDN5C EQU 328.255");
	AddLineQueue("DBL_SOUNDSPEEDN10C EQU 325.18");
	AddLineQueue("DBL_SOUNDSPEEDN15C EQU 322.076");
	AddLineQueue("DBL_SOUNDSPEEDN20C EQU 318.942");
	AddLineQueue("DBL_SOUNDSPEEDN25C EQU 315.776");
	AddLineQueue("DBL_SOUNDSPEEDN30C EQU 312.579");
	AddLineQueue("DBL_SOUNDSPEEDN35C EQU 309.348");
	AddLineQueue("DBL_SOUNDSPEEDN40C EQU 306.083");
	AddLineQueue("DBL_SOUNDSPEEDN45C EQU 302.784");
	AddLineQueue("DBL_SOUNDSPEEDN50C EQU 299.447");

	AddLineQueue("DBL_SCHSCALE EQU DBL_1DIVLN2");
	AddLineQueue("DBL_THSCALE EQU DBL_2DIVLN2");

	AddLineQueue("DBL_EXPEST1 EQU (-6.93147182e-1)");
	AddLineQueue("DBL_EXPEST2 EQU (+2.40226462e-1)");
	AddLineQueue("DBL_EXPEST3 EQU (-5.55036440e-2)");
	AddLineQueue("DBL_EXPEST4 EQU (+9.61597636e-3)");
	AddLineQueue("DBL_EXPEST5 EQU (-1.32823968e-3)");
	AddLineQueue("DBL_EXPEST6 EQU (+1.47491097e-4)");
	AddLineQueue("DBL_EXPEST7 EQU (-1.08635004e-5)");
	AddLineQueue("DBL_LOGEST0 EQU (+1.442693)");
	AddLineQueue("DBL_LOGEST1 EQU (-0.721242)");
	AddLineQueue("DBL_LOGEST2 EQU (+0.479384)");
	AddLineQueue("DBL_LOGEST3 EQU (-0.350295)");
	AddLineQueue("DBL_LOGEST4 EQU (+0.248590)");
	AddLineQueue("DBL_LOGEST5 EQU (-0.145700)");
	AddLineQueue("DBL_LOGEST6 EQU (+0.057148)");
	AddLineQueue("DBL_LOGEST7 EQU (-0.010578)");

	/* EFLAGS %eax=00H, %ebx=00H */
	AddLineQueue("BIT_CPUID EQU 0x00200000");		/*1 << 21*/

	/* %eax=00H, %ecx %ebx */
	AddLineQueue("BIT_NTEL EQU 0x6c65746e");		/*'GenuineIntel'*/
	AddLineQueue("BIT_CAMD EQU 0x444d4163");		/*'AuthenticAMD'*/

	/* %eax=00H, %ebx */
	AddLineQueue("BIT_CENT EQU 0x746e6543");		/*'CentaurHauls'*/
	AddLineQueue("BIT_VIA EQU 0x20414956");			/*'VIA VIA VIA'*/
	AddLineQueue("BIT_CYRI EQU 0x69727943");		/*'CyrixInstead'*/
	AddLineQueue("BIT_NEXG EQU 0x4778654e");		/*'NexGenDriven'*/

	/* %eax=01H, %ecx */
	AddLineQueue("BIT_SSE3 EQU 0x00000001");		/*1 << 0*/
	AddLineQueue("BIT_PCLMULQDQ EQU 0x00000002");	/*1 << 1*/
	AddLineQueue("BIT_MONITOR EQU 0x00000008");		/*1 << 3*/
	AddLineQueue("BIT_SSSE3 EQU 0x00000200");		/*1 << 9*/
	AddLineQueue("BIT_FMA EQU 0x00001000");			/*1 << 12*/
	AddLineQueue("BIT_CMPXCHG16B EQU 0x00002000");	/*1 << 13*/
	AddLineQueue("BIT_SSE41 EQU 0x00080000");		/*1 << 19*/
	AddLineQueue("BIT_SSE42 EQU 0x00100000");		/*1 << 20*/
	AddLineQueue("BIT_MOVBE EQU 0x00400000");		/*1 << 22*/
	AddLineQueue("BIT_POPCNT EQU 0x00800000");		/*1 << 23*/
	AddLineQueue("BIT_AES EQU 0x02000000");			/*1 << 25*/
	AddLineQueue("BIT_XSAVE EQU 0x04000000");		/*1 << 26*/
	AddLineQueue("BIT_OSXSAVE EQU 0x08000000");		/*1 << 27*/
	AddLineQueue("BIT_AVX EQU 0x10000000");			/*1 << 28*/
	AddLineQueue("BIT_F16C EQU 0x20000000");		/*1 << 29*/
	AddLineQueue("BIT_RDRAND EQU 0x40000000");		/*1 << 30*/

	AddLineQueue("BIT_AVX_FMA EQU 0x18001000");		/*1 << 12 | 1 << 27 | 1 << 28*/
	AddLineQueue("BIT_OSXSAVE_AVX EQU 0x18000000");	/*1 << 27 | 1 << 28*/
	AddLineQueue("BIT_AVX_F16C EQU 0x38000000");	/*1 << 27 | 1 << 28 | 1 << 29*/

	AddLineQueue("BIT_SSE3_AES EQU 0x02000001");	/*1 << 0 | 1 << 25*/
	AddLineQueue("BIT_SSSE3_AES EQU 0x02000200");	/*1 << 9 | 1 << 25*/
	AddLineQueue("BIT_SSE41_AES EQU 0x02080000");	/*1 << 19 | 1 << 25*/
	AddLineQueue("BIT_SSE42_AES EQU 0x02100000");	/*1 << 20 | 1 << 25*/

	AddLineQueue("BIT_SSE3_PCLMULQDQ EQU 0x00000003");	/*1 << 1 | 1 << 1*/
	AddLineQueue("BIT_SSSE3_PCLMULQDQ EQU 0x00000202");	/*1 << 1 | 1 << 9*/
	AddLineQueue("BIT_SSE41_PCLMULQDQ EQU 0x00080002");	/*1 << 1 | 1 << 19*/
	AddLineQueue("BIT_SSE42_PCLMULQDQ EQU 0x00100002");	/*1 << 1 | 1 << 20*/

	/* %eax=01H, %edx */
	AddLineQueue("BIT_FPU EQU 0x00000001");				/*1 << 0*/
	AddLineQueue("BIT_TSC EQU 0x00000010");				/*1 << 4*/
	AddLineQueue("BIT_MSR EQU 0x00000020");				/*1 << 5*/
	AddLineQueue("BIT_CMPXCHG8B EQU 0x00000100");		/*1 << 8*/
	AddLineQueue("BIT_SEP EQU 0x00000800");				/*1 << 11*/
	AddLineQueue("BIT_CMOV EQU 0x00008000");			/*1 << 15*/
	AddLineQueue("BIT_CLFSH EQU 0x00080000");		/*1 << 19*/
	AddLineQueue("BIT_MMX EQU 0x00800000");			/*1 << 23*/
	AddLineQueue("BIT_FXSR EQU 0x01000000");		/*1 << 24*/
	AddLineQueue("BIT_SSE EQU 0x02000000");			/*1 << 25*/
	AddLineQueue("BIT_SSE2 EQU 0x04000000");		/*1 << 26*/

	/* %eax=07H, %ebx */
	AddLineQueue("BIT_FSGSBASE EQU 0x00000001");		/*1 << 0*/
	AddLineQueue("BIT_SGX EQU 0x00000004");				/*1 << 2*/
	AddLineQueue("BIT_BMI1 EQU 0x00000008");			/*1 << 3*/
	AddLineQueue("BIT_HLE EQU 0x00000010");				/*1 << 4*/
	AddLineQueue("BIT_AVX2 EQU 0x00000020");			/*1 << 5*/
	AddLineQueue("BIT_SMEP EQU 0x00000080");			/*1 << 7*/
	AddLineQueue("BIT_BMI2 EQU 0x00000100");			/*1 << 8*/
	AddLineQueue("BIT_ERMS EQU 0x00000200");			/*1 << 9*/
	AddLineQueue("BIT_INVPCID EQU 0x00000400");			/*1 << 10*/
	AddLineQueue("BIT_RTM EQU 0x00000800");				/*1 << 11*/
	AddLineQueue("BIT_MPX EQU 0x00004000");			/*1 << 14*/
	AddLineQueue("BIT_AVX512F EQU 0x00010000");		/*1 << 16*/
	AddLineQueue("BIT_AVX512DQ EQU 0x00020000");	/*1 << 17*/
	AddLineQueue("BIT_RDSEED EQU 0x00040000");		/*1 << 18*/
	AddLineQueue("BIT_ADX EQU 0x00080000");			/*1 << 19*/
	AddLineQueue("BIT_SMAP EQU 0x00100000");		/*1 << 20*/
	AddLineQueue("BIT_AVX512_IFMA EQU 0x00200000");	/*1 << 21*/
	AddLineQueue("BIT_CLFLUSHOPT EQU 0x00800000");	/*1 << 23*/
	AddLineQueue("BIT_CLWB EQU 0x01000000");		/*1 << 24*/
	AddLineQueue("BIT_AVX512PF EQU 0x04000000");	/*1 << 26*/
	AddLineQueue("BIT_AVX512ER EQU 0x08000000");	/*1 << 27*/
	AddLineQueue("BIT_AVX512CD EQU 0x10000000");	/*1 << 28*/
	AddLineQueue("BIT_SHA EQU 0x20000000");			/*1 << 29*/
	AddLineQueue("BIT_AVX512BW EQU 0x40000000");	/*1 << 30*/
	AddLineQueue("BIT_AVX512VL EQU 0x80000000");	/*1 << 31*/

	AddLineQueue("BIT_AVX512F_DQ EQU 0x00030000");		/*1 << 16 | 1 << 17*/
	AddLineQueue("BIT_AVX512F_DQ_VL EQU 0x80030000");	/*1 << 16 | 1 << 17 | 1 << 31*/
	AddLineQueue("BIT_AVX512F_IFMA EQU 0x00210000");	/*1 << 16 | 1 << 21*/
	AddLineQueue("BIT_AVX512F_IFMA_VL EQU 0x80210000");	/*1 << 16 | 1 << 21 | 1 << 31*/
	AddLineQueue("BIT_AVX512F_PF EQU 0x04010000");		/*1 << 16 | 1 << 26*/
	AddLineQueue("BIT_AVX512F_ER EQU 0x08010000");		/*1 << 16 | 1 << 27*/
	AddLineQueue("BIT_AVX512F_CD EQU 0x10010000");		/*1 << 16 | 1 << 28*/
	AddLineQueue("BIT_AVX512F_CD_VL EQU 0x90010000");	/*1 << 16 | 1 << 28 | 1 << 31*/
	AddLineQueue("BIT_AVX512F_BW EQU 0x40010000");		/*1 << 16 | 1 << 30*/
	AddLineQueue("BIT_AVX512F_BW_VL EQU 0xC0010000");	/*1 << 16 | 1 << 30 | 1 << 31*/
	AddLineQueue("BIT_AVX512F_VL EQU 0x80010000");		/*1 << 16 | 1 << 31*/

	/* %eax=07H, %ecx */
	AddLineQueue("BIT_PREFETCHWT1 EQU 0x00000001");		/*1 << 0*/
	AddLineQueue("BIT_AVX512_VBMI EQU 0x00000002");		/*1 << 1*/
	AddLineQueue("BIT_UMIP EQU 0x00000004");			/*1 << 2*/
	AddLineQueue("BIT_PKU EQU 0x00000008");				/*1 << 3*/
	AddLineQueue("BIT_OSPKE EQU 0x00000010");			/*1 << 4*/
	AddLineQueue("BIT_AVX512_VBMI2 EQU 0x00000040");	/*1 << 6*/
	AddLineQueue("BIT_GFNI EQU 0x00000100");			/*1 << 8*/
	AddLineQueue("BIT_VAES EQU 0x00000200");			/*1 << 9*/
	AddLineQueue("BIT_VPCLMULQDQ EQU 0x00000400");		/*1 << 10*/
	AddLineQueue("BIT_AVX512_VNNI EQU 0x00000800");		/*1 << 11*/
	AddLineQueue("BIT_AVX512_BITALG EQU 0x00001000");	/*1 << 12*/
	AddLineQueue("BIT_AVX512_VPOPCNTDQ EQU 0x00004000");/*1 << 14*/
	AddLineQueue("BIT_RDPID EQU 0x00400000");			/*1 << 22*/

	/* %eax=07H, %edx */
	AddLineQueue("BIT_AVX512_4VNNIW EQU 0x00000004");	/*1 << 2*/
	AddLineQueue("BIT_AVX512_4FMAPS EQU 0x00000008");	/*1 << 3*/

	/* %eax=80000001H, %ecx */
	AddLineQueue("BIT_LAHF EQU 0x00000001");			/*1 << 0*/
	AddLineQueue("BIT_LZCNT EQU 0x00000020");			/*1 << 5*/
	AddLineQueue("BIT_ABM EQU 0x00000020");				/*1 << 5*/
	AddLineQueue("BIT_SSE4A EQU 0x00000040");			/*1 << 6*/
	AddLineQueue("BIT_PREFETCHW EQU 0x00000100");		/*1 << 8*/
	AddLineQueue("BIT_XOP EQU 0x00000800");				/*1 << 11*/
	AddLineQueue("BIT_LWP EQU 0x00008000");				/*1 << 15*/
	AddLineQueue("BIT_FMA4 EQU 0x00010000");			/*1 << 16*/
	AddLineQueue("BIT_TBM EQU 0x00200000");				/*1 << 21*/
	AddLineQueue("BIT_MWAITX EQU 0x20000000");			/*1 << 29*/

	/* %eax=80000001H, %edx */
	AddLineQueue("BIT_SYSCALL EQU 0x00000800");			/*1 << 11*/
	AddLineQueue("BIT_MMXEXT EQU 0x00400000");			/*1 << 22*/
	AddLineQueue("BIT_RDTSCP EQU 0x08000000");			/*1 << 27*/
	AddLineQueue("BIT_3DNOWEXT EQU 0x40000000");		/*1 << 30*/
	AddLineQueue("BIT_3DNOW EQU 0x80000000");			/*1 << 31*/
	
/*
 * Compare predicates for scalar and packed compare intrinsic functions
 */
	/*No AVX*/
	AddLineQueue("CMPP_EQ EQU 0x0");
	AddLineQueue("CMPP_LT EQU 0x1");
	AddLineQueue("CMPP_LE EQU 0x2");
	AddLineQueue("CMPP_UNORD EQU 0x3");
	AddLineQueue("CMPP_NEQ EQU 0x4");
	AddLineQueue("CMPP_NLT EQU 0x5");
	AddLineQueue("CMPP_NLE EQU 0x6");
	AddLineQueue("CMPP_ORD EQU 0x7");

	/*With AVX*/
	AddLineQueue("CMP_EQ_OQ EQU 0x00");		/* Equal (ordered, nonsignaling)               */
	AddLineQueue("CMP_LT_OS EQU 0x01");		/* Less-than (ordered, signaling)              */
	AddLineQueue("CMP_LE_OS EQU 0x02");		/* Less-than-or-equal (ordered, signaling)     */
	AddLineQueue("CMP_UNORD_Q EQU 0x03");	/* Unordered (nonsignaling)                    */
	AddLineQueue("CMP_NEQ_UQ EQU 0x04");	/* Not-equal (unordered, nonsignaling)         */
	AddLineQueue("CMP_NLT_US EQU 0x05");	/* Not-less-than (unordered, signaling)        */
	AddLineQueue("CMP_NLE_US EQU 0x06");	/* Not-less-than-or-equal (unordered, signaling) */
	AddLineQueue("CMP_ORD_Q EQU 0x07");		/* Ordered (nonsignaling)                      */
	AddLineQueue("CMP_EQ_UQ EQU 0x08");		/* Equal (unordered, non-signaling)            */
	AddLineQueue("CMP_NGE_US EQU 0x09");	/* Not-greater-than-or-equal (unordered, signaling) */
	AddLineQueue("CMP_NGT_US EQU 0x0A");	/* Not-greater-than (unordered, signaling)     */
	AddLineQueue("CMP_FALSE_OQ EQU 0x0B");	/* False (ordered, nonsignaling)               */
	AddLineQueue("CMP_NEQ_OQ EQU 0x0C");	/* Not-equal (ordered, non-signaling)          */
	AddLineQueue("CMP_GE_OS EQU 0x0D");		/* Greater-than-or-equal (ordered, signaling)  */
	AddLineQueue("CMP_GT_OS EQU 0x0E");		/* Greater-than (ordered, signaling)           */
	AddLineQueue("CMP_TRUE_UQ EQU 0x0F");	/* True (unordered, non-signaling)             */
	AddLineQueue("CMP_EQ_OS EQU 0x10");		/* Equal (ordered, signaling)                  */
	AddLineQueue("CMP_LT_OQ EQU 0x11");		/* Less-than (ordered, nonsignaling)           */
	AddLineQueue("CMP_LE_OQ EQU 0x12");		/* Less-than-or-equal (ordered, nonsignaling)  */
	AddLineQueue("CMP_UNORD_S EQU 0x13");	/* Unordered (signaling)                       */
	AddLineQueue("CMP_NEQ_US EQU 0x14");	/* Not-equal (unordered, signaling)            */
	AddLineQueue("CMP_NLT_UQ EQU 0x15");	/* Not-less-than (unordered, nonsignaling)     */
	AddLineQueue("CMP_NLE_UQ EQU 0x16");	/* Not-less-than-or-equal (unordered, nonsignaling) */
	AddLineQueue("CMP_ORD_S EQU 0x17");		/* Ordered (signaling)                         */
	AddLineQueue("CMP_EQ_US EQU 0x18");		/* Equal (unordered, signaling)                */
	AddLineQueue("CMP_NGE_UQ EQU 0x19");	/* Not-greater-than-or-equal (unordered, nonsignaling) */
	AddLineQueue("CMP_NGT_UQ EQU 0x1A");	/* Not-greater-than (unordered, nonsignaling)  */
	AddLineQueue("CMP_FALSE_OS EQU 0x1B");	/* False (ordered, signaling)                  */
	AddLineQueue("CMP_NEQ_OS EQU 0x1C");	/* Not-equal (ordered, signaling)              */
	AddLineQueue("CMP_GE_OQ EQU 0x1D");		/* Greater-than-or-equal (ordered, nonsignaling) */
	AddLineQueue("CMP_GT_OQ EQU 0x1E");		/* Greater-than (ordered, nonsignaling)        */
	AddLineQueue("CMP_TRUE_US EQU 0x1F");	/* True (unordered, signaling)                 */

	/*AddLineQueue(" EQU ");*/

	RunLineQueue();
}

#define X86MACRO_COUNT64 58

/* MACRO names  */
char *x86macName64[] = {
	"ALIGNSIZE_T", 
	"ALIGNPTR", 
	"ALIGNMM", 
	"ALIGNXMM", 
	"ALIGNYMM", 
	"ALIGNZMM",
	"ALIGNFIELD",
	"ALIGNSIZE_TFIELD",
	"ALIGNPTRFIELD",
	"ALIGNMMFIELD",
	"ALIGNXMMFIELD", 
	"ALIGNYMMFIELD", 
	"ALIGNZMMFIELD", 
	"ALIGNPROC", 
	"ALIGNSIZE_TPROC", 
	"ALIGNPTRPROC", 
	"ALIGNMMPROC", 
	"ALIGNXMMPROC", 
	"ALIGNYMMPROC", 
	"ALIGNZMMPROC", 
	"ALIGNFIELDPROC", 
	"ALIGNSIZE_TFIELDPROC",
	"ALIGNPTRFIELDPROC",
	"ALIGNMMFIELDPROC",
	"ALIGNXMMFIELDPROC",
	"ALIGNYMMFIELDPROC",
	"ALIGNZMMFIELDPROC",
	"FUNCSTART",
	"FUNCEND",
	"SHUFFLE4",
	"SHUFFLER4",
	"SHUFFLE2",
	"SHUFFLER2",
	"V64CI",
	"V64CI64",
	"V32CI",
	"V32CI32",
	"V16CI",
	"V16CI16",
	"V8CI",
	"V8CI8",
	"V4CI",
	"V4CI4",
	"V2CI",
	"V2CI2",
	"VV64CI",
	"VV64CI64",
	"VV32CI",
	"VV32CI32",
	"VV16CI",
	"VV16CI16",
	"VV8CI",
	"VV8CI8",
	"VV4CI",
	"VV4CI4",
	"VV2CI",
	"VV2CI2",
	"V1CI"
};

/* MACRO definitions */
char *x86macDef64[] = {
	"ALIGNSIZE_T MACRO",
	"ALIGNPTR MACRO",
	"ALIGNMM MACRO",
	"ALIGNXMM MACRO",
	"ALIGNYMM MACRO",
	"ALIGNZMM MACRO",
	"ALIGNFIELD MACRO AlignSize",
	"ALIGNSIZE_TFIELD MACRO",
	"ALIGNPTRFIELD MACRO",
	"ALIGNMMFIELD MACRO",
	"ALIGNXMMFIELD MACRO",
	"ALIGNYMMFIELD MACRO",
	"ALIGNZMMFIELD MACRO",
	"ALIGNPROC MACRO AlignSize",
	"ALIGNSIZE_TPROC MACRO",
	"ALIGNPTRPROC MACRO",
	"ALIGNMMPROC MACRO",
	"ALIGNXMMPROC MACRO",
	"ALIGNYMMPROC MACRO",
	"ALIGNZMMPROC MACRO",
	"ALIGNFIELDPROC MACRO AlignSize",
	"ALIGNSIZE_TFIELDPROC MACRO",
	"ALIGNPTRFIELDPROC MACRO",
	"ALIGNMMFIELDPROC MACRO",
	"ALIGNXMMFIELDPROC MACRO",
	"ALIGNYMMFIELDPROC MACRO",
	"ALIGNZMMFIELDPROC MACRO",
	"FUNCSTART MACRO functionName:REQ, callconvType:REQ, retType:REQ, usesStr:REQ, args:VARARG",
	"FUNCEND MACRO",
	"SHUFFLE4 MACRO V3, V2, V1, V0",
	"SHUFFLER4 MACRO V0, V1, V2, V3",
	"SHUFFLE2 MACRO V1, V0",
	"SHUFFLER2 MACRO V0, V1",
	"V64CI MACRO functionName:REQ, vectorType:REQ, V1:REQ",
	"V64CI64 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ, V3:REQ, V4:REQ, V5:REQ, V6:REQ, V7:REQ, V8:REQ, V9:REQ, V10:REQ, V11:REQ, V12:REQ, V13:REQ, V14:REQ, V15:REQ, V16:REQ, V17:REQ, V18:REQ, V19:REQ, V20:REQ, V21:REQ, V22:REQ, V23:REQ, V24:REQ, V25:REQ, V26:REQ, V27:REQ, V28:REQ, V29:REQ, V30:REQ, V31:REQ, V32:REQ, V33:REQ, V34:REQ, V35:REQ, V36:REQ, V37:REQ, V38:REQ, V39:REQ, V40:REQ, V41:REQ, V42:REQ, V43:REQ, V44:REQ, V45:REQ, V46:REQ, V47:REQ, V48:REQ, V49:REQ, V50:REQ, V51:REQ, V52:REQ, V53:REQ, V54:REQ, V55:REQ, V56:REQ, V57:REQ, V58:REQ, V59:REQ, V60:REQ, V61:REQ, V62:REQ, V63:REQ, V64:REQ",
	"V32CI MACRO functionName:REQ, vectorType:REQ, V1:REQ",
	"V32CI32 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ, V3:REQ, V4:REQ, V5:REQ, V6:REQ, V7:REQ, V8:REQ, V9:REQ, V10:REQ, V11:REQ, V12:REQ, V13:REQ, V14:REQ, V15:REQ, V16:REQ, V17:REQ, V18:REQ, V19:REQ, V20:REQ, V21:REQ, V22:REQ, V23:REQ, V24:REQ, V25:REQ, V26:REQ, V27:REQ, V28:REQ, V29:REQ, V30:REQ, V31:REQ, V32:REQ",
	"V16CI MACRO functionName:REQ, vectorType:REQ, V1:REQ",
	"V16CI16 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ, V3:REQ, V4:REQ, V5:REQ, V6:REQ, V7:REQ, V8:REQ, V9:REQ, V10:REQ, V11:REQ, V12:REQ, V13:REQ, V14:REQ, V15:REQ, V16:REQ",
	"V8CI MACRO functionName:REQ, vectorType:REQ, V1:REQ",
	"V8CI8 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ, V3:REQ, V4:REQ, V5:REQ, V6:REQ, V7:REQ, V8:REQ",
	"V4CI MACRO functionName:REQ, vectorType:REQ, V1:REQ",
	"V4CI4 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ, V3:REQ, V4:REQ",
	"V2CI MACRO functionName:REQ, vectorType:REQ, V1:REQ",
	"V2CI2 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ",
	"VV64CI MACRO functionName:REQ, vectorType:REQ, V1:REQ",
	"VV64CI64 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ, V3:REQ, V4:REQ, V5:REQ, V6:REQ, V7:REQ, V8:REQ, V9:REQ, V10:REQ, V11:REQ, V12:REQ, V13:REQ, V14:REQ, V15:REQ, V16:REQ, V17:REQ, V18:REQ, V19:REQ, V20:REQ, V21:REQ, V22:REQ, V23:REQ, V24:REQ, V25:REQ, V26:REQ, V27:REQ, V28:REQ, V29:REQ, V30:REQ, V31:REQ, V32:REQ, V33:REQ, V34:REQ, V35:REQ, V36:REQ, V37:REQ, V38:REQ, V39:REQ, V40:REQ, V41:REQ, V42:REQ, V43:REQ, V44:REQ, V45:REQ, V46:REQ, V47:REQ, V48:REQ, V49:REQ, V50:REQ, V51:REQ, V52:REQ, V53:REQ, V54:REQ, V55:REQ, V56:REQ, V57:REQ, V58:REQ, V59:REQ, V60:REQ, V61:REQ, V62:REQ, V63:REQ, V64:REQ",
	"VV32CI MACRO functionName:REQ, vectorType:REQ, V1:REQ",
	"VV32CI32 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ, V3:REQ, V4:REQ, V5:REQ, V6:REQ, V7:REQ, V8:REQ, V9:REQ, V10:REQ, V11:REQ, V12:REQ, V13:REQ, V14:REQ, V15:REQ, V16:REQ, V17:REQ, V18:REQ, V19:REQ, V20:REQ, V21:REQ, V22:REQ, V23:REQ, V24:REQ, V25:REQ, V26:REQ, V27:REQ, V28:REQ, V29:REQ, V30:REQ, V31:REQ, V32:REQ",
	"VV16CI MACRO functionName:REQ, vectorType:REQ, V1:REQ",
	"VV16CI16 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ, V3:REQ, V4:REQ, V5:REQ, V6:REQ, V7:REQ, V8:REQ, V9:REQ, V10:REQ, V11:REQ, V12:REQ, V13:REQ, V14:REQ, V15:REQ, V16:REQ",
	"VV8CI MACRO functionName:REQ, vectorType:REQ, V1:REQ",
	"VV8CI8 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ, V3:REQ, V4:REQ, V5:REQ, V6:REQ, V7:REQ, V8:REQ",
	"VV4CI MACRO functionName:REQ, vectorType:REQ, V1:REQ",
	"VV4CI4 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ, V3:REQ, V4:REQ",
	"VV2CI MACRO functionName:REQ, vectorType:REQ, V1:REQ",
	"VV2CI2 MACRO functionName:REQ, vectorType:REQ, V1:REQ, V2:REQ",
	"V1CI MACRO functionName:REQ, vectorType:REQ, V1:REQ"
};

void x86CreateMacroLibCases(void)
{
	/* Create case alternative names for macrolib functions */
	if (ModuleInfo.case_sensitive && !ModuleInfo.convert_uppercase)
	{
		AddLineQueue("callconv TEXTEQU <CALLCONV>");
		AddLineQueue("callconvopt TEXTEQU <CALLCONVOPT>");

		AddLineQueue("alignsize_t EQU ALIGNSIZE_T");
		AddLineQueue("alignptr EQU ALIGNPTR");
		AddLineQueue("alignmm EQU ALIGNMM");
		AddLineQueue("alignxmm EQU ALIGNXMM");
		AddLineQueue("alignymm EQU ALIGNYMM");
		AddLineQueue("alignzmm EQU ALIGNZMM");
		AddLineQueue("alignfield EQU ALIGNFIELD");
		AddLineQueue("alignsize_tfield EQU ALIGNSIZE_TFIELD");
		AddLineQueue("alignptrfield EQU ALIGNPTRFIELD");
		AddLineQueue("alignmmfield EQU ALIGNMMFIELD");
		AddLineQueue("alignxmmfield EQU ALIGNXMMFIELD");
		AddLineQueue("alignymmfield EQU ALIGNYMMFIELD");
		AddLineQueue("alignzmmfield EQU ALIGNZMMFIELD");
		AddLineQueue("alignproc EQU ALIGNPROC");
		AddLineQueue("alignsize_tproc EQU ALIGNSIZE_TPROC");
		AddLineQueue("alignptrproc EQU ALIGNPTRPROC");
		AddLineQueue("alignmmproc EQU ALIGNMMPROC");
		AddLineQueue("alignxmmproc EQU ALIGNXMMPROC");
		AddLineQueue("alignymmproc EQU ALIGNYMMPROC");
		AddLineQueue("alignzmmproc EQU ALIGNZMMPROC");
		AddLineQueue("alignfieldproc EQU ALIGNFIELDPROC");
		AddLineQueue("alignsize_tfieldproc EQU ALIGNSIZE_TFIELDPROC");
		AddLineQueue("alignptrfieldproc EQU ALIGNPTRFIELDPROC");
		AddLineQueue("alignmmfieldproc EQU ALIGNMMFIELDPROC");
		AddLineQueue("alignxmmfieldproc EQU <ALIGNXMMFIELDPROC>");
		AddLineQueue("alignymmfieldproc EQU ALIGNYMMFIELDPROC");
		AddLineQueue("alignzmmfieldproc EQU ALIGNZMMFIELDPROC");
		AddLineQueue("funcstart EQU FUNCSTART");
		AddLineQueue("funcend EQU FUNCEND");

		AddLineQueue("shuffle4 EQU SHUFFLE4");
		AddLineQueue("shuffler4 EQU SHUFFLER4");
		AddLineQueue("shuffle2 EQU SHUFFLE2");
		AddLineQueue("shuffler2 EQU SHUFFLER2");

		AddLineQueue("v64ci EQU V64CI");
		AddLineQueue("v64ci64 EQU V64CI64");
		AddLineQueue("v32ci EQU V32CI");
		AddLineQueue("v32ci32 EQU V32CI32");
		AddLineQueue("v16ci EQU V16CI");
		AddLineQueue("v16ci16 EQU V16CI16");
		AddLineQueue("v8ci EQU V8CI");
		AddLineQueue("v8ci8 EQU V8CI8");
		AddLineQueue("v4ci EQU V4CI");
		AddLineQueue("v4ci4 EQU V4CI4");
		AddLineQueue("v2ci EQU V2CI");
		AddLineQueue("v2ci2 EQU V2CI2");
		AddLineQueue("vv64ci EQU VV64CI");
		AddLineQueue("vv64ci64 EQU VV64CI64");
		AddLineQueue("vv32ci EQU VV32CI");
		AddLineQueue("vv32ci32 EQU VV32CI32");
		AddLineQueue("vv16ci EQU VV16CI");
		AddLineQueue("vv16ci16 EQU VV16CI16");
		AddLineQueue("vv8ci EQU VV8CI");
		AddLineQueue("vv8ci8 EQU VV8CI8");
		AddLineQueue("vv4ci EQU VV4CI");
		AddLineQueue("vv4ci4 EQU VV4CI4");
		AddLineQueue("vv2ci EQU VV2CI");
		AddLineQueue("vv2ci2 EQU VV2CI2");

		/* 64bits*/
		AddLineQueue("rret TEXTEQU RRET");
		AddLineQueue("rreturn TEXTEQU RRETURN");
		AddLineQueue("rsidx TEXTEQU RSIDX");
		AddLineQueue("rdidx TEXTEQU RDIDX");
		AddLineQueue("rbptr TEXTEQU RBPTR");
		AddLineQueue("rsptr TEXTEQU RSPTR");
		AddLineQueue("rbase TEXTEQU RBASE");
		AddLineQueue("rparam0 TEXTEQU RPARAM0");
		AddLineQueue("rparam1 TEXTEQU RPARAM1");
		AddLineQueue("rparam2 TEXTEQU RPARAM2");
		AddLineQueue("rparam3 TEXTEQU RPARAM3");
		AddLineQueue("rparam4 TEXTEQU RPARAM4");
		AddLineQueue("rparam5 TEXTEQU RPARAM5");
		AddLineQueue("rparam6 TEXTEQU RPARAM6");
		AddLineQueue("rparam7 TEXTEQU RPARAM7");
		AddLineQueue("rparam8 TEXTEQU RPARAM8");
		AddLineQueue("rparam9 TEXTEQU RPARAM9");
		AddLineQueue("rparam10 TEXTEQU RPARAM10");
		AddLineQueue("rparam11 TEXTEQU RPARAM11");
		AddLineQueue("rparam12 TEXTEQU RPARAM12");
		AddLineQueue("rparam13 TEXTEQU RPARAM13");
		AddLineQueue("rparam14 TEXTEQU RPARAM14");
		AddLineQueue("rparam15 TEXTEQU RPARAM15");
		AddLineQueue("rparam16 TEXTEQU RPARAM16");
		AddLineQueue("rparam17 TEXTEQU RPARAM17");
		AddLineQueue("rparam18 TEXTEQU RPARAM18");
		AddLineQueue("rparam19 TEXTEQU RPARAM19");
		AddLineQueue("rparam20 TEXTEQU RPARAM20");
		AddLineQueue("rparam21 TEXTEQU RPARAM21");
		AddLineQueue("rparam22 TEXTEQU RPARAM22");
		AddLineQueue("rparam23 TEXTEQU RPARAM23");
		AddLineQueue("rparam24 TEXTEQU RPARAM24");
		AddLineQueue("rparam25 TEXTEQU RPARAM25");
		AddLineQueue("rparam26 TEXTEQU RPARAM26");
		AddLineQueue("rparam27 TEXTEQU RPARAM27");
		AddLineQueue("rparam28 TEXTEQU RPARAM28");
		AddLineQueue("rparam29 TEXTEQU RPARAM29");
		AddLineQueue("rparam30 TEXTEQU RPARAM30");
		AddLineQueue("rparam31 TEXTEQU RPARAM31");
		AddLineQueue("rparam32 TEXTEQU RPARAM32");
		AddLineQueue("rparam33 TEXTEQU RPARAM33");
		AddLineQueue("rparam34 TEXTEQU RPARAM34");
		AddLineQueue("rparam35 TEXTEQU RPARAM35");
		AddLineQueue("rparam36 TEXTEQU RPARAM36");
		AddLineQueue("rparam37 TEXTEQU RPARAM37");
		AddLineQueue("rparam38 TEXTEQU RPARAM38");
		AddLineQueue("rparam39 TEXTEQU RPARAM39");
		AddLineQueue("rparam40 TEXTEQU RPARAM40");
		AddLineQueue("rparam41 TEXTEQU RPARAM41");
		AddLineQueue("rparam42 TEXTEQU RPARAM42");
		AddLineQueue("rparam43 TEXTEQU RPARAM43");
		AddLineQueue("rparam44 TEXTEQU RPARAM44");
		AddLineQueue("rparam45 TEXTEQU RPARAM45");
		AddLineQueue("rparam46 TEXTEQU RPARAM46");
		AddLineQueue("rparam47 TEXTEQU RPARAM47");
		AddLineQueue("rparam48 TEXTEQU RPARAM48");
		AddLineQueue("rparam49 TEXTEQU RPARAM49");
		AddLineQueue("rparam50 TEXTEQU RPARAM50");
		AddLineQueue("rparam51 TEXTEQU RPARAM51");
		AddLineQueue("rparam52 TEXTEQU RPARAM52");
		AddLineQueue("rparam53 TEXTEQU RPARAM53");
		AddLineQueue("rparam54 TEXTEQU RPARAM54");
		AddLineQueue("rparam55 TEXTEQU RPARAM55");
		AddLineQueue("rparam56 TEXTEQU RPARAM56");
		AddLineQueue("rparam57 TEXTEQU RPARAM57");
		AddLineQueue("rparam58 TEXTEQU RPARAM58");
		AddLineQueue("rparam59 TEXTEQU RPARAM59");
		AddLineQueue("rparam60 TEXTEQU RPARAM60");
		AddLineQueue("rparam61 TEXTEQU RPARAM61");
		AddLineQueue("rparam62 TEXTEQU RPARAM62");
		AddLineQueue("rparam63 TEXTEQU RPARAM63");
		/* 32bits*/
		AddLineQueue("dret TEXTEQU DRET");
		AddLineQueue("dreturn TEXTEQU DRETURN");
		AddLineQueue("dsidx TEXTEQU DSIDX");
		AddLineQueue("ddidx TEXTEQU DDIDX");
		AddLineQueue("dbptr TEXTEQU DBPTR");
		AddLineQueue("dsptr TEXTEQU DSPTR");
		AddLineQueue("dbase TEXTEQU DBASE");
		AddLineQueue("dparam0 TEXTEQU DPARAM0");
		AddLineQueue("dparam1 TEXTEQU DPARAM1");
		AddLineQueue("dparam2 TEXTEQU DPARAM2");
		AddLineQueue("dparam3 TEXTEQU DPARAM3");
		AddLineQueue("dparam4 TEXTEQU DPARAM4");
		AddLineQueue("dparam5 TEXTEQU DPARAM5");
		AddLineQueue("dparam6 TEXTEQU DPARAM6");
		AddLineQueue("dparam7 TEXTEQU DPARAM7");
		AddLineQueue("dparam8 TEXTEQU DPARAM8");
		AddLineQueue("dparam9 TEXTEQU DPARAM9");
		AddLineQueue("dparam10 TEXTEQU DPARAM10");
		AddLineQueue("dparam11 TEXTEQU DPARAM11");
		AddLineQueue("dparam12 TEXTEQU DPARAM12");
		AddLineQueue("dparam13 TEXTEQU DPARAM13");
		AddLineQueue("dparam14 TEXTEQU DPARAM14");
		AddLineQueue("dparam15 TEXTEQU DPARAM15");
		AddLineQueue("dparam16 TEXTEQU DPARAM16");
		AddLineQueue("dparam17 TEXTEQU DPARAM17");
		AddLineQueue("dparam18 TEXTEQU DPARAM18");
		AddLineQueue("dparam19 TEXTEQU DPARAM19");
		AddLineQueue("dparam20 TEXTEQU DPARAM20");
		AddLineQueue("dparam21 TEXTEQU DPARAM21");
		AddLineQueue("dparam22 TEXTEQU DPARAM22");
		AddLineQueue("dparam23 TEXTEQU DPARAM23");
		AddLineQueue("dparam24 TEXTEQU DPARAM24");
		AddLineQueue("dparam25 TEXTEQU DPARAM25");
		AddLineQueue("dparam26 TEXTEQU DPARAM26");
		AddLineQueue("dparam27 TEXTEQU DPARAM27");
		AddLineQueue("dparam28 TEXTEQU DPARAM28");
		AddLineQueue("dparam29 TEXTEQU DPARAM29");
		AddLineQueue("dparam30 TEXTEQU DPARAM30");
		AddLineQueue("dparam31 TEXTEQU DPARAM31");
		AddLineQueue("dparam32 TEXTEQU DPARAM32");
		AddLineQueue("dparam33 TEXTEQU DPARAM33");
		AddLineQueue("dparam34 TEXTEQU DPARAM34");
		AddLineQueue("dparam35 TEXTEQU DPARAM35");
		AddLineQueue("dparam36 TEXTEQU DPARAM36");
		AddLineQueue("dparam37 TEXTEQU DPARAM37");
		AddLineQueue("dparam38 TEXTEQU DPARAM38");
		AddLineQueue("dparam39 TEXTEQU DPARAM39");
		AddLineQueue("dparam40 TEXTEQU DPARAM40");
		AddLineQueue("dparam41 TEXTEQU DPARAM41");
		AddLineQueue("dparam42 TEXTEQU DPARAM42");
		AddLineQueue("dparam43 TEXTEQU DPARAM43");
		AddLineQueue("dparam44 TEXTEQU DPARAM44");
		AddLineQueue("dparam45 TEXTEQU DPARAM45");
		AddLineQueue("dparam46 TEXTEQU DPARAM46");
		AddLineQueue("dparam47 TEXTEQU DPARAM47");
		AddLineQueue("dparam48 TEXTEQU DPARAM48");
		AddLineQueue("dparam49 TEXTEQU DPARAM49");
		AddLineQueue("dparam50 TEXTEQU DPARAM50");
		AddLineQueue("dparam51 TEXTEQU DPARAM51");
		AddLineQueue("dparam52 TEXTEQU DPARAM52");
		AddLineQueue("dparam53 TEXTEQU DPARAM53");
		AddLineQueue("dparam54 TEXTEQU DPARAM54");
		AddLineQueue("dparam55 TEXTEQU DPARAM55");
		AddLineQueue("dparam56 TEXTEQU DPARAM56");
		AddLineQueue("dparam57 TEXTEQU DPARAM57");
		AddLineQueue("dparam58 TEXTEQU DPARAM58");
		AddLineQueue("dparam59 TEXTEQU DPARAM59");
		AddLineQueue("dparam60 TEXTEQU DPARAM60");
		AddLineQueue("dparam61 TEXTEQU DPARAM61");
		AddLineQueue("dparam62 TEXTEQU DPARAM62");
		AddLineQueue("dparam63 TEXTEQU DPARAM63");
		/* 16bits*/
		AddLineQueue("wret TEXTEQU WRET");
		AddLineQueue("wreturn TEXTEQU WRETURN");
		AddLineQueue("wsidx TEXTEQU WSIDX");
		AddLineQueue("wdidx TEXTEQU WDIDX");
		AddLineQueue("wbptr TEXTEQU WBPTR");
		AddLineQueue("wsptr TEXTEQU WSPTR");
		AddLineQueue("wbase TEXTEQU WBASE");
		AddLineQueue("wparam0 TEXTEQU WPARAM0");
		AddLineQueue("wparam1 TEXTEQU WPARAM1");
		AddLineQueue("wparam2 TEXTEQU WPARAM2");
		AddLineQueue("wparam3 TEXTEQU WPARAM3");
		AddLineQueue("wparam4 TEXTEQU WPARAM4");
		AddLineQueue("wparam5 TEXTEQU WPARAM5");
		AddLineQueue("wparam6 TEXTEQU WPARAM6");
		AddLineQueue("wparam7 TEXTEQU WPARAM7");
		AddLineQueue("wparam8 TEXTEQU WPARAM8");
		AddLineQueue("wparam9 TEXTEQU WPARAM9");
		AddLineQueue("wparam10 TEXTEQU WPARAM10");
		AddLineQueue("wparam11 TEXTEQU WPARAM11");
		AddLineQueue("wparam12 TEXTEQU WPARAM12");
		AddLineQueue("wparam13 TEXTEQU WPARAM13");
		AddLineQueue("wparam14 TEXTEQU WPARAM14");
		AddLineQueue("wparam15 TEXTEQU WPARAM15");
		AddLineQueue("wparam16 TEXTEQU WPARAM16");
		AddLineQueue("wparam17 TEXTEQU WPARAM17");
		AddLineQueue("wparam18 TEXTEQU WPARAM18");
		AddLineQueue("wparam19 TEXTEQU WPARAM19");
		AddLineQueue("wparam20 TEXTEQU WPARAM20");
		AddLineQueue("wparam21 TEXTEQU WPARAM21");
		AddLineQueue("wparam22 TEXTEQU WPARAM22");
		AddLineQueue("wparam23 TEXTEQU WPARAM23");
		AddLineQueue("wparam24 TEXTEQU WPARAM24");
		AddLineQueue("wparam25 TEXTEQU WPARAM25");
		AddLineQueue("wparam26 TEXTEQU WPARAM26");
		AddLineQueue("wparam27 TEXTEQU WPARAM27");
		AddLineQueue("wparam28 TEXTEQU WPARAM28");
		AddLineQueue("wparam29 TEXTEQU WPARAM29");
		AddLineQueue("wparam30 TEXTEQU WPARAM30");
		AddLineQueue("wparam31 TEXTEQU WPARAM31");
		AddLineQueue("wparam32 TEXTEQU WPARAM32");
		AddLineQueue("wparam33 TEXTEQU WPARAM33");
		AddLineQueue("wparam34 TEXTEQU WPARAM34");
		AddLineQueue("wparam35 TEXTEQU WPARAM35");
		AddLineQueue("wparam36 TEXTEQU WPARAM36");
		AddLineQueue("wparam37 TEXTEQU WPARAM37");
		AddLineQueue("wparam38 TEXTEQU WPARAM38");
		AddLineQueue("wparam39 TEXTEQU WPARAM39");
		AddLineQueue("wparam40 TEXTEQU WPARAM40");
		AddLineQueue("wparam41 TEXTEQU WPARAM41");
		AddLineQueue("wparam42 TEXTEQU WPARAM42");
		AddLineQueue("wparam43 TEXTEQU WPARAM43");
		AddLineQueue("wparam44 TEXTEQU WPARAM44");
		AddLineQueue("wparam45 TEXTEQU WPARAM45");
		AddLineQueue("wparam46 TEXTEQU WPARAM46");
		AddLineQueue("wparam47 TEXTEQU WPARAM47");
		AddLineQueue("wparam48 TEXTEQU WPARAM48");
		AddLineQueue("wparam49 TEXTEQU WPARAM49");
		AddLineQueue("wparam50 TEXTEQU WPARAM50");
		AddLineQueue("wparam51 TEXTEQU WPARAM51");
		AddLineQueue("wparam52 TEXTEQU WPARAM52");
		AddLineQueue("wparam53 TEXTEQU WPARAM53");
		AddLineQueue("wparam54 TEXTEQU WPARAM54");
		AddLineQueue("wparam55 TEXTEQU WPARAM55");
		AddLineQueue("wparam56 TEXTEQU WPARAM56");
		AddLineQueue("wparam57 TEXTEQU WPARAM57");
		AddLineQueue("wparam58 TEXTEQU WPARAM58");
		AddLineQueue("wparam59 TEXTEQU WPARAM59");
		AddLineQueue("wparam60 TEXTEQU WPARAM60");
		AddLineQueue("wparam61 TEXTEQU WPARAM61");
		AddLineQueue("wparam62 TEXTEQU WPARAM62");
		AddLineQueue("wparam63 TEXTEQU WPARAM63");
		/* 8bits*/
		AddLineQueue("bret TEXTEQU BRET");
		AddLineQueue("breturn TEXTEQU BRETURN");
		AddLineQueue("bsidx TEXTEQU BSIDX");
		AddLineQueue("bdidx TEXTEQU BDIDX");
		AddLineQueue("bbptr TEXTEQU BBPTR");
		AddLineQueue("bsptr TEXTEQU BSPTR");
		AddLineQueue("bbase TEXTEQU BBASE");
		AddLineQueue("bparam0 TEXTEQU BPARAM0");
		AddLineQueue("bparam1 TEXTEQU BPARAM1");
		AddLineQueue("bparam2 TEXTEQU BPARAM2");
		AddLineQueue("bparam3 TEXTEQU BPARAM3");
		AddLineQueue("bparam4 TEXTEQU BPARAM4");
		AddLineQueue("bparam5 TEXTEQU BPARAM5");
		AddLineQueue("bparam6 TEXTEQU BPARAM6");
		AddLineQueue("bparam7 TEXTEQU BPARAM7");
		AddLineQueue("bparam8 TEXTEQU BPARAM8");
		AddLineQueue("bparam9 TEXTEQU BPARAM9");
		AddLineQueue("bparam10 TEXTEQU BPARAM10");
		AddLineQueue("bparam11 TEXTEQU BPARAM11");
		AddLineQueue("bparam12 TEXTEQU BPARAM12");
		AddLineQueue("bparam13 TEXTEQU BPARAM13");
		AddLineQueue("bparam14 TEXTEQU BPARAM14");
		AddLineQueue("bparam15 TEXTEQU BPARAM15");
		AddLineQueue("bparam16 TEXTEQU BPARAM16");
		AddLineQueue("bparam17 TEXTEQU BPARAM17");
		AddLineQueue("bparam18 TEXTEQU BPARAM18");
		AddLineQueue("bparam19 TEXTEQU BPARAM19");
		AddLineQueue("bparam20 TEXTEQU BPARAM20");
		AddLineQueue("bparam21 TEXTEQU BPARAM21");
		AddLineQueue("bparam22 TEXTEQU BPARAM22");
		AddLineQueue("bparam23 TEXTEQU BPARAM23");
		AddLineQueue("bparam24 TEXTEQU BPARAM24");
		AddLineQueue("bparam25 TEXTEQU BPARAM25");
		AddLineQueue("bparam26 TEXTEQU BPARAM26");
		AddLineQueue("bparam27 TEXTEQU BPARAM27");
		AddLineQueue("bparam28 TEXTEQU BPARAM28");
		AddLineQueue("bparam29 TEXTEQU BPARAM29");
		AddLineQueue("bparam30 TEXTEQU BPARAM30");
		AddLineQueue("bparam31 TEXTEQU BPARAM31");
		AddLineQueue("bparam32 TEXTEQU BPARAM32");
		AddLineQueue("bparam33 TEXTEQU BPARAM33");
		AddLineQueue("bparam34 TEXTEQU BPARAM34");
		AddLineQueue("bparam35 TEXTEQU BPARAM35");
		AddLineQueue("bparam36 TEXTEQU BPARAM36");
		AddLineQueue("bparam37 TEXTEQU BPARAM37");
		AddLineQueue("bparam38 TEXTEQU BPARAM38");
		AddLineQueue("bparam39 TEXTEQU BPARAM39");
		AddLineQueue("bparam40 TEXTEQU BPARAM40");
		AddLineQueue("bparam41 TEXTEQU BPARAM41");
		AddLineQueue("bparam42 TEXTEQU BPARAM42");
		AddLineQueue("bparam43 TEXTEQU BPARAM43");
		AddLineQueue("bparam44 TEXTEQU BPARAM44");
		AddLineQueue("bparam45 TEXTEQU BPARAM45");
		AddLineQueue("bparam46 TEXTEQU BPARAM46");
		AddLineQueue("bparam47 TEXTEQU BPARAM47");
		AddLineQueue("bparam48 TEXTEQU BPARAM48");
		AddLineQueue("bparam49 TEXTEQU BPARAM49");
		AddLineQueue("bparam50 TEXTEQU BPARAM50");
		AddLineQueue("bparam51 TEXTEQU BPARAM51");
		AddLineQueue("bparam52 TEXTEQU BPARAM52");
		AddLineQueue("bparam53 TEXTEQU BPARAM53");
		AddLineQueue("bparam54 TEXTEQU BPARAM54");
		AddLineQueue("bparam55 TEXTEQU BPARAM55");
		AddLineQueue("bparam56 TEXTEQU BPARAM56");
		AddLineQueue("bparam57 TEXTEQU BPARAM57");
		AddLineQueue("bparam58 TEXTEQU BPARAM58");
		AddLineQueue("bparam59 TEXTEQU BPARAM59");
		AddLineQueue("bparam60 TEXTEQU BPARAM60");
		AddLineQueue("bparam61 TEXTEQU BPARAM61");
		AddLineQueue("bparam62 TEXTEQU BPARAM62");
		AddLineQueue("bparam63 TEXTEQU BPARAM63");

		AddLineQueue("int8 TEXTEQU INT8");
		AddLineQueue("uint8 TEXTEQU UINT8");
		AddLineQueue("sint8 TEXTEQU SINT8");
		AddLineQueue("int8_t TEXTEQU INT8_T");
		AddLineQueue("uint8_t TEXTEQU UINT8_T");
		AddLineQueue("sint8_t TEXTEQU SINT8_T");
		AddLineQueue("int16 TEXTEQU INT16");
		AddLineQueue("uint16 TEXTEQU UINT16");
		AddLineQueue("sint16 TEXTEQU SINT16");
		AddLineQueue("int16_t TEXTEQU INT16_T");
		AddLineQueue("uint16_t TEXTEQU UINT16_T");
		AddLineQueue("sint16_t TEXTEQU SINT16_T");
		/*AddLineQueue("int TEXTEQU INT"); cannot be used instruction type*/
		AddLineQueue("bool TEXTEQU BOOL");
		AddLineQueue("int32 TEXTEQU INT32");
		AddLineQueue("uint32 TEXTEQU UINT32");
		AddLineQueue("sint32 TEXTEQU SINT32");
		AddLineQueue("int32_t TEXTEQU INT32_T");
		AddLineQueue("uint32_t TEXTEQU UINT32_T");
		AddLineQueue("sint32_t TEXTEQU SINT32_T");
		AddLineQueue("int64 TEXTEQU INT64");
		AddLineQueue("uint64 TEXTEQU UINT64");
		AddLineQueue("sint64 TEXTEQU SINT64");
		AddLineQueue("int64_t TEXTEQU INT64_T");
		AddLineQueue("uint64_t TEXTEQU UINT64_T");
		AddLineQueue("sint64_t TEXTEQU SINT64_T");
		AddLineQueue("float TEXTEQU <FLOAT>");
		AddLineQueue("double TEXTEQU <DOUBLE>");

		AddLineQueue("byte_size EQU BYTE_SIZE");
		AddLineQueue("ubyte_size EQU UBYTE_SIZE");
		AddLineQueue("sbyte_size EQU SBYTE_SIZE");
		AddLineQueue("char_size EQU CHAR_SIZE");
		AddLineQueue("uchar_size EQU UCHAR_SIZE");
		AddLineQueue("schar_size EQU SCHAR_SIZE");
		AddLineQueue("int8_size EQU INT8_SIZE");
		AddLineQueue("uint8_size EQU UINT8_SIZE");
		AddLineQueue("sint8_size EQU SINT8_SIZE");
		AddLineQueue("i8_size EQU I8_SIZE");
		AddLineQueue("ui8_size EQU UI8_SIZE");
		AddLineQueue("si8_size EQU SI8_SIZE");
		AddLineQueue("word_size EQU WORD_SIZE");
		AddLineQueue("uword_size EQU UWORD_SIZE");
		AddLineQueue("sword_size EQU SWORD_SIZE");
		AddLineQueue("short_size EQU SHORT_SIZE");
		AddLineQueue("ushort_size EQU USHORT_SIZE");
		AddLineQueue("sshort_size EQU SSHORT_SIZE");
		AddLineQueue("int16_size EQU INT16_SIZE");
		AddLineQueue("uint16_size EQU UINT16_SIZE");
		AddLineQueue("sint16_size EQU SINT16_SIZE");
		AddLineQueue("i16_size EQU I16_SIZE");
		AddLineQueue("ui16_size EQU U16_SIZE");
		AddLineQueue("si16_size EQU SI16_SIZE");
		AddLineQueue("dword_size EQU DWORD_SIZE");
		AddLineQueue("udword_size EQU UDWORD_SIZE");
		AddLineQueue("sdword_size EQU SDWORD_SIZE");
		AddLineQueue("long_size EQU LONG_SIZE");
		AddLineQueue("ulong_size EQU ULONG_SIZE");
		AddLineQueue("slong_size EQU SLONG_SIZE");
		AddLineQueue("bool_size EQU BOOL_SIZE");
		AddLineQueue("int_size EQU INT_SIZE");
		AddLineQueue("uint_size EQU UINT_SIZE");
		AddLineQueue("sint_size EQU SINT_SIZE");
		AddLineQueue("int32_size EQU INT32_SIZE");
		AddLineQueue("uint32_size EQU UINT32_SIZE");
		AddLineQueue("sint32_size EQU SINT32_SIZE");
		AddLineQueue("i32_size EQU I32_SIZE");
		AddLineQueue("ui32_size EQU UI32_SIZE");
		AddLineQueue("si32_size EQU SI32_SIZE");
		AddLineQueue("qword_size EQU QWORD_SIZE");
		AddLineQueue("uqword_size EQU UQWORD_SIZE");
		AddLineQueue("sqword_size EQU SQWORD_SIZE");
		AddLineQueue("longlong_size EQU LONGLONG_SIZE");
		AddLineQueue("ulonglong_size EQU ULONGLONG_SIZE");
		AddLineQueue("slonglong_size EQU SLONGLONG_SIZE");
		AddLineQueue("int64_size EQU INT64_SIZE");
		AddLineQueue("uint64_size EQU UINT64_SIZE");
		AddLineQueue("sint64_size EQU SINT64_SIZE");
		AddLineQueue("i64_size EQU I64_SIZE");
		AddLineQueue("ui64_size EQU UI64_SIZE");
		AddLineQueue("si64_size EQU SI64_SIZE");
		AddLineQueue("real4_size EQU REAL4_SIZE");
		AddLineQueue("float_size EQU FLOAT_SIZE");
		AddLineQueue("flt_size EQU FLT_SIZE");
		AddLineQueue("real8_size EQU REAL8_SIZE");
		AddLineQueue("double_size EQU DOUBLE_SIZE");
		AddLineQueue("dbl_size EQU DBL_SIZE");

		AddLineQueue("byte_max EQU BYTE_MAX");
		AddLineQueue("ubyte_max EQU UBYTE_MAX");
		AddLineQueue("char_max EQU CHAR_MAX");
		AddLineQueue("uchar_max EQU UCHAR_MAX");
		AddLineQueue("int8_max EQU INT8_MAX");
		AddLineQueue("uint8_max EQU UINT8_MAX");
		AddLineQueue("i8_max EQU I8_MAX");
		AddLineQueue("ui8_max EQU UI8_MAX");
		AddLineQueue("ubyte_min EQU UBYTE_MIN");
		AddLineQueue("uchar_min EQU UCHAR_MIN");
		AddLineQueue("uint8_min EQU UINT8_MIN");
		AddLineQueue("ui8_min EQU UI8_MIN");
		AddLineQueue("sbyte_max EQU SBYTE_MAX");
		AddLineQueue("schar_max EQU SCHAR_MAX");
		AddLineQueue("sint8_max EQU SINT8_MAX");
		AddLineQueue("si8_max EQU SI8_MAX");
		AddLineQueue("byte_min EQU BYTE_MIN");
		AddLineQueue("sbyte_min EQU SBYTE_MIN");
		AddLineQueue("char_min EQU CHAR_MIN");
		AddLineQueue("schar_min EQU SCHAR_MIN");
		AddLineQueue("int8_min EQU INT8_MIN");
		AddLineQueue("sint8_min EQU SINT8_MIN");
		AddLineQueue("i8_min EQU I8_MIN");
		AddLineQueue("si8_min EQU SI8_MIN");
		AddLineQueue("word_max EQU WORD_MAX");
		AddLineQueue("uword_max EQU UWORD_MAX");
		AddLineQueue("short_max EQU SHORT_MAX");
		AddLineQueue("ushort_max EQU USHORT_MAX");
		AddLineQueue("int16_max EQU INT16_MAX");
		AddLineQueue("uint16_max EQU UINT16_MAX");
		AddLineQueue("i16_max EQU I16_MAX");
		AddLineQueue("ui16_max EQU UI16_MAX");
		AddLineQueue("uword_min EQU UWORD_MIN");
		AddLineQueue("ushort_min EQU USHORT_MIN");
		AddLineQueue("uint16_min EQU UINT16_MIN");
		AddLineQueue("ui16_min EQU UI16_MIN");
		AddLineQueue("sword_max EQU SWORD_MAX");
		AddLineQueue("sshort_max EQU SSHORT_MAX");
		AddLineQueue("sint16_max EQU SINT16_MAX");
		AddLineQueue("si16_max EQU SI16_MAX");
		AddLineQueue("word_min EQU WORD_MIN");
		AddLineQueue("sword_min EQU SWORD_MIN");
		AddLineQueue("short_min EQU SHORT_MIN");
		AddLineQueue("sshort_min EQU SSHORT_MIN");
		AddLineQueue("int16_min EQU INT16_MIN");
		AddLineQueue("sint16_min EQU SINT16_MIN");
		AddLineQueue("i16_min EQU I16_MIN");
		AddLineQueue("si16_min EQU SI16_MIN");
		AddLineQueue("bool_max EQU BOOL_MAX");
		AddLineQueue("bool_min EQU BOOL_MIN");
		AddLineQueue("dword_max EQU DWORD_MAX");
		AddLineQueue("udword_max EQU UDWORD_MAX");
		AddLineQueue("long_max EQU LONG_MAX");
		AddLineQueue("ulong_max EQU ULONG_MAX");
		AddLineQueue("int_max EQU INT_MAX");
		AddLineQueue("uint_max EQU UINT_MAX");
		AddLineQueue("int32_max EQU INT32_MAX");
		AddLineQueue("uint32_max EQU UINT32_MAX");
		AddLineQueue("i32_max EQU I32_MAX");
		AddLineQueue("ui32_max EQU UI32_MAX");
		AddLineQueue("udword_min EQU UDWORD_MIN");
		AddLineQueue("ulong_min EQU ULONG_MIN");
		AddLineQueue("uint_min EQU UINT_MIN");
		AddLineQueue("uint32_min EQU UINT32_MIN");
		AddLineQueue("ui32_min EQU UI32_MIN");
		AddLineQueue("sdword_max EQU SDWORD_MAX");
		AddLineQueue("slong_max EQU SLONG_MAX");
		AddLineQueue("sint_max EQU SINT_MAX");
		AddLineQueue("sint32_max EQU SINT32_MAX");
		AddLineQueue("si32_max EQU SI32_MAX");
		AddLineQueue("dword_min EQU DWORD_MIN");
		AddLineQueue("sdword_min EQU SDWORD_MIN");
		AddLineQueue("long_min EQU LONG_MIN");
		AddLineQueue("slong_min EQU SLONG_MIN");
		AddLineQueue("int_min EQU INT_MIN");
		AddLineQueue("sint_min EQU SINT_MIN");
		AddLineQueue("int32_min EQU INT32_MIN");
		AddLineQueue("sint32_min EQU SINT32_MIN");
		AddLineQueue("i32_min EQU I32_MIN");
		AddLineQueue("si32_min EQU SI32_MIN");
		AddLineQueue("qword_max EQU QWORD_MAX");
		AddLineQueue("uqword_max EQU UQWORD_MAX");
		AddLineQueue("longlong_max EQU LONGLONG_MAX");
		AddLineQueue("ulonglong_max EQU ULONGLONG_MAX");
		AddLineQueue("int64_max EQU INT64_MAX");
		AddLineQueue("uint64_max EQU UINT64_MAX");
		AddLineQueue("i64_max EQU I64_MAX");
		AddLineQueue("ui64_max EQU UI64_MAX");
		AddLineQueue("uqword_min EQU UQWORD_MIN");
		AddLineQueue("ulonglong_min EQU ULONGLONG_MIN");
		AddLineQueue("uint64_min EQU UINT64_MIN");
		AddLineQueue("ui64_min EQU UI64_MIN");
		AddLineQueue("sqword_max EQU SQWORD_MAX");
		AddLineQueue("slonglong_max EQU SLONGLONG_MAX");
		AddLineQueue("sint64_max EQU SINT64_MAX");
		AddLineQueue("si64_max EQU SI64_MAX");
		AddLineQueue("qword_min EQU QWORD_MIN");
		AddLineQueue("sqword_min EQU SQWORD_MIN");
		AddLineQueue("longlong_min EQU LONGLONG_MIN");
		AddLineQueue("slonglong_min EQU SLONGLONG_MIN");
		AddLineQueue("int64_min EQU INT64_MIN");
		AddLineQueue("sint64_min EQU SINT64_MIN");
		AddLineQueue("i64_min EQU I64_MIN");
		AddLineQueue("si64_min EQU SI64_MIN");

		AddLineQueue("max_byte EQU MAX_BYTE");
		AddLineQueue("max_ubyte EQU MAX_UBYTE");
		AddLineQueue("max_char EQU MAX_CHAR");
		AddLineQueue("max_uchar EQU MAX_UCHAR");
		AddLineQueue("max_int8 EQU MAX_INT8");
		AddLineQueue("max_uint8 EQU MAX_UINT8");
		AddLineQueue("max_i8 EQU MAX_I8");
		AddLineQueue("max_ui8 EQU MAX_UI8");
		AddLineQueue("min_ubyte EQU MIN_UBYTE");
		AddLineQueue("min_uchar EQU MIN_UCHAR");
		AddLineQueue("min_uint8 EQU MIN_UINT8");
		AddLineQueue("min_ui8 EQU MIN_UI8");
		AddLineQueue("max_sbyte EQU MAX_SBYTE");
		AddLineQueue("max_schar EQU MAX_SCHAR");
		AddLineQueue("max_sint8 EQU MAX_SINT8");
		AddLineQueue("max_si8 EQU MAX_SI8");
		AddLineQueue("min_byte EQU MIN_BYTE");
		AddLineQueue("min_sbyte EQU MIN_SBYTE");
		AddLineQueue("min_char EQU MIN_CHAR");
		AddLineQueue("min_schar EQU MIN_SCHAR");
		AddLineQueue("min_int8 EQU MIN_INT8");
		AddLineQueue("min_sint8 EQU MIN_SINT8");
		AddLineQueue("min_i8 EQU MIN_I8");
		AddLineQueue("min_si8 EQU MIN_SI8");
		AddLineQueue("max_word EQU MAX_WORD");
		AddLineQueue("max_uword EQU MAX_UWORD");
		AddLineQueue("max_short EQU MAX_SHORT");
		AddLineQueue("max_ushort EQU MAX_USHORT");
		AddLineQueue("max_int16 EQU MAX_INT16");
		AddLineQueue("max_uint16 EQU MAX_UINT16");
		AddLineQueue("max_i16 EQU MAX_I16");
		AddLineQueue("max_ui16 EQU MAX_UI16");
		AddLineQueue("min_uword EQU MIN_UWORD");
		AddLineQueue("min_ushort EQU MIN_USHORT");
		AddLineQueue("min_uint16 EQU MIN_UINT16");
		AddLineQueue("min_ui16 EQU MIN_UI16");
		AddLineQueue("max_sword EQU MAX_SWORD");
		AddLineQueue("max_sshort EQU MAX_SSHORT");
		AddLineQueue("max_sint16 EQU MAX_SINT16");
		AddLineQueue("max_si16 EQU MAX_SI16");
		AddLineQueue("min_word EQU MIN_WORD");
		AddLineQueue("min_sword EQU MIN_SWORD");
		AddLineQueue("min_short EQU MIN_SHORT");
		AddLineQueue("min_sshort EQU MIN_SSHORT");
		AddLineQueue("min_int16 EQU MIN_INT16");
		AddLineQueue("min_sint16 EQU MIN_SINT16");
		AddLineQueue("min_i16 EQU MIN_I16");
		AddLineQueue("min_si16 EQU MIN_SI16");
		AddLineQueue("max_bool EQU MAX_BOOL");
		AddLineQueue("min_bool EQU MIN_BOOL");
		AddLineQueue("max_dword EQU MAX_DWORD");
		AddLineQueue("max_udword EQU MAX_UDWORD");
		AddLineQueue("max_long EQU MAX_LONG");
		AddLineQueue("max_ulong EQU MAX_ULONG");
		AddLineQueue("max_int EQU MAX_INT");
		AddLineQueue("max_uint EQU MAX_UINT");
		AddLineQueue("max_int32 EQU MAX_INT32");
		AddLineQueue("max_uint32 EQU MAX_UINT32");
		AddLineQueue("max_i32 EQU MAX_I32");
		AddLineQueue("max_ui32 EQU MAX_UI32");
		AddLineQueue("min_udword EQU MIN_UDWORD");
		AddLineQueue("min_ulong EQU MIN_ULONG");
		AddLineQueue("min_uint EQU MIN_UINT");
		AddLineQueue("min_uint32 EQU MIN_UINT32");
		AddLineQueue("min_ui32 EQU MIN_UI32");
		AddLineQueue("max_sdword EQU MAX_SDWORD");
		AddLineQueue("max_slong EQU MAX_SLONG");
		AddLineQueue("max_sint EQU MAX_SINT");
		AddLineQueue("max_sint32 EQU MAX_SINT32");
		AddLineQueue("max_si32 EQU MAX_SI32");
		AddLineQueue("min_dword EQU MIN_DWORD");
		AddLineQueue("min_sdword EQU MIN_SDWORD");
		AddLineQueue("min_long EQU MIN_LONG");
		AddLineQueue("min_slong EQU MIN_SLONG");
		AddLineQueue("min_int EQU MIN_INT");
		AddLineQueue("min_sint EQU MIN_SINT");
		AddLineQueue("min_int32 EQU MIN_INT32");
		AddLineQueue("min_sint32 EQU MIN_SINT32");
		AddLineQueue("min_i32 EQU MIN_I32");
		AddLineQueue("min_si32 EQU MIN_SI32");
		AddLineQueue("max_qword EQU MAX_QWORD");
		AddLineQueue("max_uqword EQU MAX_UQWORD");
		AddLineQueue("max_longlong EQU MAX_LONGLONG");
		AddLineQueue("max_ulonglong EQU MAX_ULONGLONG");
		AddLineQueue("max_int64 EQU MAX_INT64");
		AddLineQueue("max_uint64 EQU MAX_UINT64");
		AddLineQueue("max_i64 EQU MAX_I64");
		AddLineQueue("max_ui64 EQU MAX_UI64");
		AddLineQueue("min_uqword EQU MIN_UQWORD");
		AddLineQueue("min_ulonglong EQU MIN_ULONGLONG");
		AddLineQueue("min_uint64 EQU MIN_UINT64");
		AddLineQueue("min_ui64 EQU MIN_UI64");
		AddLineQueue("max_sqword EQU MAX_SQWORD");
		AddLineQueue("max_slonglong EQU MAX_SLONGLONG");
		AddLineQueue("max_sint64 EQU MAX_SINT64");
		AddLineQueue("max_si64 EQU MAX_SI64");
		AddLineQueue("min_qword EQU MIN_QWORD");
		AddLineQueue("min_sqword EQU MIN_SQWORD");
		AddLineQueue("min_longlong EQU MIN_LONGLONG");
		AddLineQueue("min_slonglong EQU MIN_SLONGLONG");
		AddLineQueue("min_int64 EQU MIN_INT64");
		AddLineQueue("min_sint64 EQU MIN_SINT64");
		AddLineQueue("min_i64 EQU MIN_I64");
		AddLineQueue("min_si64 EQU MIN_SI64");

		AddLineQueue("byte_error EQU BYTE_ERROR");
		AddLineQueue("char_error EQU CHAR_ERROR");
		AddLineQueue("int8_error EQU INT8_ERROR");
		AddLineQueue("i8_error EQU I8_ERROR");
		AddLineQueue("ubyte_error EQU UBYTE_ERROR");
		AddLineQueue("uchar_error EQU UCHAR_ERROR");
		AddLineQueue("uint8_error EQU UINT8_ERROR");
		AddLineQueue("ui8_error EQU UI8_ERROR");
		AddLineQueue("sbyte_error EQU SBYTE_ERROR");
		AddLineQueue("schar_error EQU SCHAR_ERROR");
		AddLineQueue("sint8_error EQU SINT8_ERROR");
		AddLineQueue("si8_error EQU SI8_ERROR");

		AddLineQueue("word_error EQU WORD_ERROR");
		AddLineQueue("short_error EQU SHORT_ERROR");
		AddLineQueue("int16_error EQU INT16_ERROR");
		AddLineQueue("i16_error EQU I16_ERROR");
		AddLineQueue("uword_error EQU UWORD_ERROR");
		AddLineQueue("ushort_error EQU USHORT_ERROR");
		AddLineQueue("uint16_error EQU UINT18_ERROR");
		AddLineQueue("ui16_error EQU UI18_ERROR");
		AddLineQueue("sword_error EQU SWORD_ERROR EQU");
		AddLineQueue("sshort_error EQU SSHORT_ERROR EQU");
		AddLineQueue("sint16_error EQU SINT16_ERROR EQU");
		AddLineQueue("si16_error EQU SI16_ERROR EQU");

		AddLineQueue("dword_error EQU DWORD_ERROR");
		AddLineQueue("long_error EQU LONG_ERROR");
		AddLineQueue("int_error EQU INT_ERROR");
		AddLineQueue("int32_error EQU INT32_ERROR");
		AddLineQueue("i32_error EQU I32_ERROR");
		AddLineQueue("udword_error EQU UDWORD_ERROR");
		AddLineQueue("ulong_error EQU ULONG_ERROR");
		AddLineQueue("uint_error EQU UINT_ERROR");
		AddLineQueue("uint32_error EQU UINT32_ERROR");
		AddLineQueue("ui32_error EQU UI32_ERROR");
		AddLineQueue("sdword_error EQU SDWORD_ERROR");
		AddLineQueue("slong_error EQU SLONG_ERROR");
		AddLineQueue("sint_error EQU SINT_ERROR");
		AddLineQueue("sint32_error EQU SINT32_ERROR");
		AddLineQueue("si32_error EQU SI32_ERROR");

		AddLineQueue("qword_error EQU QWORD_ERROR");
		AddLineQueue("longlong_error EQU LONGLONG_ERROR");
		AddLineQueue("int64_error EQU INT64_ERROR");
		AddLineQueue("i64_error EQU I64_ERROR");
		AddLineQueue("uqword_error EQU UQWORD_ERROR");
		AddLineQueue("ulonglong_error EQU ULONGLONG_ERROR");
		AddLineQueue("uint64_error EQU UINT64_ERROR");
		AddLineQueue("ui64_error EQU UI64_ERROR");
		AddLineQueue("sqword_error EQU SQWORD_ERROR");
		AddLineQueue("slonglong_error EQU SLONGLONG_ERROR");
		AddLineQueue("sint64_error EQU SINT64_ERROR");
		AddLineQueue("si64_error EQU SI64_ERROR");

		AddLineQueue("float_error EQU FLOAT_ERROR");
		AddLineQueue("flt_error EQU FLT_ERROR");
		AddLineQueue("double_error EQU DOUBLE_ERROR");
		AddLineQueue("dbl_error EQU DBL_ERROR");

		AddLineQueue("size_t TEXTEQU <SIZE_T>");
		AddLineQueue("ptrdiff_t TEXTEQU <PTRDIFF_T>");
		AddLineQueue("intptr_t TEXTEQU <INTPTR_T>");
		AddLineQueue("uintptr_t TEXTEQU <UINTPTR_T>");
		AddLineQueue("isize_t TEXTEQU <ISIZE_T>");
		AddLineQueue("psize_t TEXTEQU <PSIZE_T>");
		AddLineQueue("size_tp TEXTEQU <SIZE_TP>");
		AddLineQueue("size_t_size EQU SIZE_T_SIZE");
		AddLineQueue("ptrdiff_t_size EQU PTRDIFF_T_SIZE");
		AddLineQueue("intptr_t_size EQU INTPTR_T_SIZE");
		AddLineQueue("uintptr_t_size EQU UINTPTR_T_SIZE");
		AddLineQueue("ptr_size EQU PTR_SIZE");
		AddLineQueue("reg_size EQU REG_SIZE");
		AddLineQueue("sintsize_t_max EQU SINTSIZE_T_MAX");
		AddLineQueue("sintsize_t_min EQU SINTSIZE_T_MIN");
		AddLineQueue("uintsize_t_max EQU UINTSIZE_T_MAX");
		AddLineQueue("uintsize_t_min EQU UINTSIZE_T_MIN");
		AddLineQueue("intsize_t_max EQU INTSIZE_T_MAX");
		AddLineQueue("intsize_t_min EQU INTSIZE_T_MIN");
		AddLineQueue("size_t_max EQU SIZE_T_MAX");
		AddLineQueue("size_t_min EQU SIZE_T_MIN");
		AddLineQueue("ptrdiff_t_max EQU PTRDIFF_T_MAX");
		AddLineQueue("ptrdiff_t_min EQU PTRDIFF_T_MIN");
		AddLineQueue("intptr_t_max EQU INTPTR_T_MAX");
		AddLineQueue("intptr_t_min EQU INTPTR_T_MIN");
		AddLineQueue("uintptr_t_max EQU UINTPTR_T_MAX");
		AddLineQueue("uintptr_t_min EQU UINTPTR_T_MIN");
		AddLineQueue("sintptr_max EQU SINTPTR_MAX");
		AddLineQueue("sintptr_min EQU SINTPTR_MIN");
		AddLineQueue("uintptr_max EQU UINTPTR_MAX");
		AddLineQueue("uintptr_min EQU UINTPTR_MIN");
		AddLineQueue("intptr_max EQU INTPTR_MAX");
		AddLineQueue("intptr_min EQU INTPTR_MIN");
		AddLineQueue("max_sintsize_t EQU MAX_SINTSIZE_T");
		AddLineQueue("min_sintsize_t EQU MIN_SINTSIZE_T");
		AddLineQueue("max_uintsize_t EQU MAX_UINTSIZE_T");
		AddLineQueue("min_uintsize_t EQU MIN_UINTSIZE_T");
		AddLineQueue("max_intsize_t EQU MAX_INTSIZE_T");
		AddLineQueue("min_intsize_t EQU MIN_INTSIZE_T");
		AddLineQueue("max_size_t EQU MAX_SIZE_T");
		AddLineQueue("min_size_t EQU MIN_SIZE_T");
		AddLineQueue("max_ptrdiff_t EQU MAX_PTRDIFF_T");
		AddLineQueue("min_ptrdiff_t EQU MIN_PTRDIFF_T");
		AddLineQueue("max_intptr_t EQU MAX_INTPTR_T");
		AddLineQueue("min_intptr_t EQU MIN_INTPTR_T");
		AddLineQueue("max_uintptr_t EQU MAX_UINTPTR_T");
		AddLineQueue("min_uintptr_t EQU MIN_UINTPTR_T");
		AddLineQueue("max_sintptr EQU MAX_SINTPTR");
		AddLineQueue("min_sintptr EQU MIN_SINTPTR");
		AddLineQueue("max_uintptr EQU MAX_UINTPTR");
		AddLineQueue("min_uintptr EQU MIN_UINTPTR");
		AddLineQueue("max_intptr EQU MAX_INTPTR");
		AddLineQueue("min_intptr EQU MIN_INTPTR");
		AddLineQueue("sintsize_t_error EQU SINTSIZE_T_ERROR");
		AddLineQueue("uintsize_t_error EQU UINTSIZE_T_ERROR");
		AddLineQueue("intsize_t_error EQU INTSIZE_T_ERROR");
		AddLineQueue("size_t_error EQU SIZE_T_ERROR");
		AddLineQueue("ptrdiff_t_error EQU PTRDIFF_T_ERROR");
		AddLineQueue("intptr_t_error EQU INTPTR_T_ERROR");
		AddLineQueue("uintptr_t_error EQU UINTPTR_T_ERROR");
		AddLineQueue("sintptrt_error EQU SINTPTR_ERROR");
		AddLineQueue("uintptr_error EQU UINTPTR_ERROR");
		AddLineQueue("intptr_error EQU INTPTR_ERROR");

		AddLineQueue("false EQU FALSE");
		AddLineQueue("true EQU TRUE");

		AddLineQueue("m8_false EQU M8_FALSE");
		AddLineQueue("m8_true EQU M8_TRUE");
		AddLineQueue("byte_false EQU BYTE_FALSE");
		AddLineQueue("byte_true EQU BYTE_TRUE");
		AddLineQueue("char_false EQU CHAR_FALSE");
		AddLineQueue("char_true EQU CHAR_TRUE");
		AddLineQueue("int8_false EQU INT8_FALSE");
		AddLineQueue("int8_true EQU INT8_TRUE");
		AddLineQueue("i8_false EQU I8_FALSE");
		AddLineQueue("i8_true EQU I8_TRUE");
		AddLineQueue("i8_0 EQU I8_0");
		AddLineQueue("i8_1 EQU I8_1");
		AddLineQueue("i8_neg0 EQU I8_NEG0");
		AddLineQueue("i8_neg1 EQU I8_NEG1");

		AddLineQueue("m16_false EQU M16_FALSE");
		AddLineQueue("m16_true EQU M16_TRUE");
		AddLineQueue("word_false EQU WORD_FALSE");
		AddLineQueue("word_true EQU WORD_TRUE");
		AddLineQueue("short_false EQU SHORT_FALSE");
		AddLineQueue("short_true EQU SHORT_TRUE");
		AddLineQueue("int16_false EQU INT16_FALSE");
		AddLineQueue("int16_true EQU INT16_TRUE");
		AddLineQueue("i16_false EQU I16_FALSE");
		AddLineQueue("i16_true EQU I16_TRUE");
		AddLineQueue("i16_0 EQU I16_0");
		AddLineQueue("i16_1 EQU I16_1");
		AddLineQueue("i16_neg0 EQU I16_NEG0");
		AddLineQueue("i16_neg1 EQU I16_NEG1");

		AddLineQueue("m32_false EQU M32_FALSE");
		AddLineQueue("m32_true EQU M32_TRUE");
		AddLineQueue("dword_false EQU DWORD_FALSE");
		AddLineQueue("dword_true EQU DWORD_TRUE");
		AddLineQueue("long_false EQU LONG_FALSE");
		AddLineQueue("long_true EQU LONG_TRUE");
		AddLineQueue("int_false EQU INT_FALSE");
		AddLineQueue("int_true EQU INT_TRUE");
		AddLineQueue("int32_false EQU INT32_FALSE");
		AddLineQueue("int32_true EQU INT32_TRUE");
		AddLineQueue("i32_false EQU I32_FALSE");
		AddLineQueue("i32_true EQU I32_TRUE");
		AddLineQueue("i32_0 EQU I32_0");
		AddLineQueue("i32_1 EQU I32_1");
		AddLineQueue("i32_neg0 EQU I32_NEG0");
		AddLineQueue("i32_neg1 EQU I32_NEG1");

		AddLineQueue("mm_size EQU MM_SIZE");
		AddLineQueue("m64_size EQU M64_SIZE");
		AddLineQueue("mm_false EQU MM_FALSE");
		AddLineQueue("mm_true EQU MM_TRUE");
		AddLineQueue("m64_false EQU M64_FALSE");
		AddLineQueue("m64_true EQU M64_TRUE");
		AddLineQueue("qword_false EQU QWORD_FALSE");
		AddLineQueue("qword_true EQU QWORD_TRUE");
		AddLineQueue("longlong_false EQU LONGLONG_FALSE");
		AddLineQueue("longlong_true EQU LONGLONG_TRUE");
		AddLineQueue("int64_false EQU INT64_FALSE");
		AddLineQueue("int64_true EQU INT64_TRUE");
		AddLineQueue("i64_false EQU I64_FALSE");
		AddLineQueue("i64_true EQU I64_TRUE");
		AddLineQueue("i64_0 EQU I64_0");
		AddLineQueue("i64_1 EQU I64_1");
		AddLineQueue("i64_neg0 EQU I64_NEG0");
		AddLineQueue("i64_neg1 EQU I64_NEG1");

		AddLineQueue("xmm_size EQU XMM_SIZE");
		AddLineQueue("m128_size EQU M128_SIZE");
		AddLineQueue("ymm_size EQU YMM_SIZE");
		AddLineQueue("m256_size EQU M256_SIZE");
		AddLineQueue("zmm_size EQU ZMM_SIZE");
		AddLineQueue("m512_size EQU M512_SIZE");

		/*float mask*/
		AddLineQueue("flt_1lshl3_msk EQU FLT_1LSHL3_MSK");
		AddLineQueue("flt_1lshl4_msk EQU FLT_1LSHL4_MSK");
		AddLineQueue("flt_1lshl7_msk EQU FLT_1LSHL7_MSK");
		AddLineQueue("flt_1lshl8_msk EQU FLT_1LSHL8_MSK");
		AddLineQueue("flt_1lshl11_msk EQU FLT_1LSHL11_MSK");
		AddLineQueue("flt_1lshl12_msk EQU FLT_1LSHL12_MSK");
		AddLineQueue("flt_1lshl15_msk EQU FLT_1LSHL15_MSK");
		AddLineQueue("flt_1lshl16_msk EQU FLT_1LSHL16_MSK");
		AddLineQueue("flt_1lshl19_msk EQU FLT_1LSHL19_MSK");
		AddLineQueue("flt_1lshl20_msk EQU FLT_1LSHL20_MSK");
		AddLineQueue("flt_1lshl23_msk EQU FLT_1LSHL23_MSK");
		AddLineQueue("flt_1lshl24_msk EQU FLT_1LSHL24_MSK");
		AddLineQueue("flt_1lshl27_msk EQU FLT_1LSHL27_MSK");
		AddLineQueue("flt_1lshl28_msk EQU FLT_1LSHL28_MSK");
		AddLineQueue("flt_1lshl31_msk EQU FLT_1LSHL31_MSK");

		AddLineQueue("flt_neg1lshl3_msk EQU FLT_NEG1LSHL3_MSK");
		AddLineQueue("flt_neg1lshl4_msk EQU FLT_NEG1LSHL4_MSK");
		AddLineQueue("flt_neg1lshl7_msk EQU FLT_NEG1LSHL7_MSK");
		AddLineQueue("flt_neg1lshl8_msk EQU FLT_NEG1LSHL8_MSK");
		AddLineQueue("flt_neg1lshl11_msk EQU FLT_NEG1LSHL11_MSK");
		AddLineQueue("flt_neg1lshl12_msk EQU FLT_NEG1LSHL12_MSK");
		AddLineQueue("flt_neg1lshl15_msk EQU FLT_NEG1LSHL15_MSK");
		AddLineQueue("flt_neg1lshl16_msk EQU FLT_NEG1LSHL16_MSK");
		AddLineQueue("flt_neg1lshl19_msk EQU FLT_NEG1LSHL19_MSK");
		AddLineQueue("flt_neg1lshl20_msk EQU FLT_NEG1LSHL20_MSK");
		AddLineQueue("flt_neg1lshl23_msk EQU FLT_NEG1LSHL23_MSK");
		AddLineQueue("flt_neg1lshl24_msk EQU FLT_NEG1LSHL24_MSK");
		AddLineQueue("flt_neg1lshl27_msk EQU FLT_NEG1LSHL27_MSK");
		AddLineQueue("flt_neg1lshl28_msk EQU FLT_NEG1LSHL28_MSK");
		AddLineQueue("flt_neg1lshl31_msk EQU FLT_NEG1LSHL31_MSK");

		AddLineQueue("flt_false_msk EQU FLT_FALSE_MSK");
		AddLineQueue("flt_true_msk EQU FLT_TRUE_MSK");
		AddLineQueue("flt_error_msk EQU FLT_ERROR_MSK");

		AddLineQueue("flt_magic_msk EQU FLT_MAGIC_MSK");
		AddLineQueue("flt_sign_msk EQU FLT_SIGN_MSK");
		AddLineQueue("flt_invsign_msk EQU FLT_INVSIGN_MSK");

		AddLineQueue("flt_inf_msk EQU FLT_INF_MSK");
		AddLineQueue("flt_fin_msk EQU FLT_FIN_MSK");
		AddLineQueue("flt_invinf_msk EQU FLT_INVINF_MSK");
		AddLineQueue("flt_neginf_msk EQU FLT_NEGINF_MSK");
		AddLineQueue("flt_nan_msk EQU FLT_NAN_MSK");
		AddLineQueue("flt_qnan_msk EQU FLT_QNAN_MSK");
		AddLineQueue("flt_negqnan_msk EQU FLT_NEGQNAN_MSK");
		AddLineQueue("flt_nantest_msk EQU FLT_NANTEST_MSK");
		AddLineQueue("flt_abs_msk EQU FLT_ABS_MSK");
		AddLineQueue("flt_min_msk EQU FLT_MIN_MSK");
		AddLineQueue("flt_max_msk EQU FLT_MAX_MSK");
		AddLineQueue("flt_nofraction_msk EQU FLT_NOFRACTION_MSK");
		AddLineQueue("flt_mindenorm_msk EQU FLT_MINDENORM_MSK");
		AddLineQueue("flt_denormlimit_msk EQU FLT_DENORMLIMIT_MSK");
		AddLineQueue("flt_minnormal_msk EQU FLT_MINNORMAL_MSK");
		AddLineQueue("flt_maxnormal_msk EQU FLT_MAXNORMAL_MSK");

		AddLineQueue("flt_decdig_msk EQU FLT_DECDIG_MSK");
		AddLineQueue("flt_dig_msk EQU FLT_DIG_MSK");
		AddLineQueue("flt_negdecdig_msk EQU FLT_NEGDECDIG_MSK");
		AddLineQueue("flt_negdig_msk EQU FLT_NEGDIG_MSK");
		AddLineQueue("flt_eps_msk EQU FLT_EPS_MSK");
		AddLineQueue("flt_epsilon_msk EQU FLT_EPSILON_MSK");
		AddLineQueue("flt_normeps_msk EQU FLT_NORMEPS_MSK");
		AddLineQueue("flt_guard_msk EQU FLT_GUARD_MSK");
		AddLineQueue("flt_mantpow2_msk EQU FLT_MANTPOW2_MSK");
		AddLineQueue("flt_maxmantpow2_msk EQU FLT_MAXMANTPOW2_MSK");
		AddLineQueue("flt_mantdig_msk EQU FLT_MANTDIG_MSK");
		AddLineQueue("flt_mant_msk EQU FLT_MANT_MSK");
		AddLineQueue("flt_negmantdig_msk EQU FLT_NEGMANTDIG_MSK");
		AddLineQueue("flt_negmant_msk EQU FLT_NEGMANT_MSK");
		AddLineQueue("flt_maxexp_msk EQU FLT_MAXEXP_MSK");
		AddLineQueue("flt_expsign_msk EQU FLT_EXPSIGN_MSK");
		AddLineQueue("flt_exp_msk EQU FLT_EXP_MSK");
		AddLineQueue("flt_negmaxexp_msk EQU FLT_NEGMAXEXP_MSK");
		AddLineQueue("flt_negexpsign_msk EQU FLT_NEGEXPSIGN_MSK");
		AddLineQueue("flt_negexp_msk EQU FLT_NEGEXP_MSK");
		AddLineQueue("flt_subnormalexp_msk EQU FLT_SUBNORMALEXP_MSK");
		AddLineQueue("flt_minexp_msk EQU FLT_MINEXP_MSK");
		AddLineQueue("flt_maxdecexp_msk EQU FLT_MAXDECEXP_MSK");
		AddLineQueue("flt_negmaxdecexp_msk EQU FLT_NEGMAXDECEXP_MSK");
		AddLineQueue("flt_mindecexp_msk EQU FLT_MINDECEXP_MSK");
		AddLineQueue("flt_expfield_msk EQU FLT_EXPFIELD_MSK");
		AddLineQueue("flt_mantfield_msk EQU FLT_MANTFIELD_MSK");
		AddLineQueue("flt_norm_msk EQU FLT_NORM_MSK");
		AddLineQueue("flt_radix_msk EQU FLT_RADIX_MSK");
		AddLineQueue("flt_rounds_msk EQU FLT_ROUNDS_MSK");
		AddLineQueue("flt_subdec_msk EQU FLT_SUBDEC_MSK");
		AddLineQueue("flt_sqrtmax_msk EQU FLT_SQRTMAX_MSK");
		AddLineQueue("flt_smallnormal_msk EQU FLT_SMALLNORMAL_MSK");

		AddLineQueue("flt_halfminuseps_msk EQU FLT_HALFMINUSEPS_MSK");
		AddLineQueue("flt_trueint_msk EQU FLT_TRUEINT_MSK");

		AddLineQueue("flt_byte_msk EQU FLT_BYTE_MSK");
		AddLineQueue("flt_byte_even_msk EQU FLT_BYTE_EVEN_MSK");
		AddLineQueue("flt_byte_odd_msk EQU FLT_BYTE_ODD_MSK");
		AddLineQueue("flt_4low_msk EQU FLT_4LOW_MSK");
		AddLineQueue("flt_4high_msk EQU FLT_4HIGH_MSK");
		AddLineQueue("flt_flip4_msk EQU FLT_FLIP4_MSK");
		AddLineQueue("flt_8low_msk EQU FLT_8LOW_MSK");
		AddLineQueue("flt_8high_msk EQU FLT_8HIGH_MSK");
		AddLineQueue("flt_flip8_msk EQU FLT_FLIP8_MSK");
		AddLineQueue("flt_16low_msk EQU FLT_16LOW_MSK");
		AddLineQueue("flt_16high_msk EQU FLT_16HIGH_MSK");
		AddLineQueue("flt_flip16_msk EQU FLT_FLIP16_MSK");
		AddLineQueue("flt_24low_msk EQU FLT_24LOW_MSK");
		AddLineQueue("flt_24high_msk EQU FLT_24HIGH_MSK");
		AddLineQueue("flt_flip24_msk EQU FLT_FLIP24_MSK");
		AddLineQueue("flt_28low_msk EQU FLT_28LOW_MSK");
		AddLineQueue("flt_28high_msk EQU FLT_28HIGH_MSK");
		AddLineQueue("flt_flip28_msk EQU FLT_FLIP28_MSK");
		AddLineQueue("flt_32low_msk EQU FLT_32LOW_MSK");
		AddLineQueue("flt_32high_msk EQU FLT_32HIGH_MSK");
		AddLineQueue("flt_flip32_msk EQU FLT_FLIP32_MSK");

		AddLineQueue("flt_0_msk EQU FLT_0_MSK");
		AddLineQueue("flt_0d5_msk EQU FLT_0D5_MSK");
		AddLineQueue("flt_1_msk EQU FLT_1_MSK");
		AddLineQueue("flt_1d5_msk EQU FLT_1D5_MSK");
		AddLineQueue("flt_2_msk EQU FLT_2_MSK");
		AddLineQueue("flt_2d5_msk EQU FLT_2D5_MSK");
		AddLineQueue("flt_3_msk EQU FLT_3_MSK");
		AddLineQueue("flt_4_msk EQU FLT_4_MSK");
		AddLineQueue("flt_5_msk EQU FLT_5_MSK");
		AddLineQueue("flt_6_msk EQU FLT_6_MSK");
		AddLineQueue("flt_7_msk EQU FLT_7_MSK");
		AddLineQueue("flt_8_msk EQU FLT_8_MSK");
		AddLineQueue("flt_9_msk EQU FLT_9_MSK");
		AddLineQueue("flt_10_msk EQU FLT_10_MSK");
		AddLineQueue("flt_20_msk EQU FLT_20_MSK");
		AddLineQueue("flt_23_msk EQU FLT_23_MSK");
		AddLineQueue("flt_23d5_msk EQU FLT_23D5_MSK");
		AddLineQueue("flt_24_msk EQU FLT_24_MSK");
		AddLineQueue("flt_24d5_msk EQU FLT_24D5_MSK");
		AddLineQueue("flt_25_msk EQU FLT_25_MSK");

		AddLineQueue("flt_128_msk EQU FLT_128_MSK");

		AddLineQueue("flt_253_msk EQU FLT_253_MSK");

		AddLineQueue("flt_neg0_msk EQU FLT_NEG0_MSK");
		AddLineQueue("flt_neg1_msk EQU FLT_NEG1_MSK");

		AddLineQueue("flt_neg150_msk EQU FLT_NEG150_MSK");

		AddLineQueue("flt_a8_msk EQU FLT_A8_MSK");
		AddLineQueue("flt_r8_msk EQU FLT_R8_MSK");
		AddLineQueue("flt_g8_msk EQU FLT_G8_MSK");
		AddLineQueue("flt_b8_msk EQU FLT_B8_MSK");

		AddLineQueue("flt_flipa8_msk EQU FLT_FLIPA8_MSK");
		AddLineQueue("flt_flipr8_msk EQU FLT_FLIPR8_MSK");
		AddLineQueue("flt_flipg8_msk EQU FLT_FLIPG8_MSK");
		AddLineQueue("flt_flipb8_msk EQU FLT_FLIPB8_MSK");

		AddLineQueue("flt_a2_msk EQU FLT_A2_MSK");
		AddLineQueue("flt_b10_msk EQU FLT_B10_MSK");
		AddLineQueue("flt_g10_msk EQU FLT_G10_MSK");
		AddLineQueue("flt_r10_msk EQU FLT_R10_MSK");

		AddLineQueue("flt_flipa2_msk EQU FLT_FLIPA2_MSK");
		AddLineQueue("flt_flipb10_msk EQU FLT_FLIPB10_MSK");
		AddLineQueue("flt_flipg10_msk EQU FLT_FLIPG10_MSK");
		AddLineQueue("flt_flipr10_msk EQU FLT_FLIPR10_MSK");

		AddLineQueue("flt_bin128_msk EQU FLT_BIN128_MSK");
		AddLineQueue("flt_binneg150_msk EQU FLT_BINNEG150_MSK");

		AddLineQueue("flt_maxrand_msk EQU FLT_MAXRAND_MSK");

		AddLineQueue("flt_maxi8_msk EQU FLT_MAXI8_MSK");
		AddLineQueue("flt_mini8_msk EQU FLT_MINI8_MSK");
		AddLineQueue("flt_maxu8_msk EQU FLT_MAXU8_MSK");

		AddLineQueue("flt_maxi16_msk EQU FLT_MAXI16_MSK");
		AddLineQueue("flt_mini16_msk EQU FLT_MINI16_MSK");
		AddLineQueue("flt_maxu16_msk EQU FLT_MAXU16_MSK");

		AddLineQueue("flt_maxi32_msk EQU FLT_MAXI32_MSK");
		AddLineQueue("flt_mini32_msk EQU FLT_MINI32_MSK");
		AddLineQueue("flt_maxu32_msk EQU FLT_MAXU32_MSK");

		AddLineQueue("flt_maxi8xu8_msk EQU FLT_MAXI8XU8_MSK");
		AddLineQueue("flt_mini8xu8_msk EQU FLT_MINI8XU8_MSK");
		AddLineQueue("flt_maxi8xu16_msk EQU FLT_MAXI8XU16_MSK");
		AddLineQueue("flt_mini8xu16_msk EQU FLT_MINI8XU16_MSK");

		AddLineQueue("flt_maxi16xu16_msk EQU FLT_MAXI16XU16_MSK");
		AddLineQueue("flt_mini16xu16_msk EQU FLT_MINI16XU16_MSK");

		AddLineQueue("flt_fixunsigned_msk EQU FLT_FIXUNSIGNED_MSK");
		AddLineQueue("flt_fixunsigned32_msk EQU FLT_FIXUNSIGNED32_MSK");
		AddLineQueue("flt_fixmaxi32_msk EQU FLT_FIXMAXI32_MSK");
		AddLineQueue("flt_fixmaxu32_msk EQU FLT_FIXMAXU32_MSK");

		/*float int*/
		AddLineQueue("flt_1lshl3_int EQU FLT_1LSHL3_INT");
		AddLineQueue("flt_1lshl4_int EQU FLT_1LSHL4_INT");
		AddLineQueue("flt_1lshl7_int EQU FLT_1LSHL7_INT");
		AddLineQueue("flt_1lshl8_int EQU FLT_1LSHL8_INT");
		AddLineQueue("flt_1lshl11_int EQU FLT_1LSHL11_INT");
		AddLineQueue("flt_1lshl12_int EQU FLT_1LSHL12_INT");
		AddLineQueue("flt_1lshl15_int EQU FLT_1LSHL15_INT");
		AddLineQueue("flt_1lshl16_int EQU FLT_1LSHL16_INT");
		AddLineQueue("flt_1lshl19_int EQU FLT_1LSHL19_INT");
		AddLineQueue("flt_1lshl20_int EQU FLT_1LSHL20_INT");
		AddLineQueue("flt_1lshl23_int EQU FLT_1LSHL23_INT");
		AddLineQueue("flt_1lshl24_int EQU FLT_1LSHL24_INT");
		AddLineQueue("flt_1lshl27_int EQU FLT_1LSHL27_INT");
		AddLineQueue("flt_1lshl28_int EQU FLT_1LSHL28_INT");
		AddLineQueue("flt_1lshl31_int EQU FLT_1LSHL31_INT");

		AddLineQueue("flt_neg1lshl3_int EQU FLT_NEG1LSHL3_INT");
		AddLineQueue("flt_neg1lshl4_int EQU FLT_NEG1LSHL4_INT");
		AddLineQueue("flt_neg1lshl7_int EQU FLT_NEG1LSHL7_INT");
		AddLineQueue("flt_neg1lshl8_int EQU FLT_NEG1LSHL8_INT");
		AddLineQueue("flt_neg1lshl11_int EQU FLT_NEG1LSHL11_INT");
		AddLineQueue("flt_neg1lshl12_int EQU FLT_NEG1LSHL12_INT");
		AddLineQueue("flt_neg1lshl15_int EQU FLT_NEG1LSHL15_INT");
		AddLineQueue("flt_neg1lshl16_int EQU FLT_NEG1LSHL16_INT");
		AddLineQueue("flt_neg1lshl19_int EQU FLT_NEG1LSHL19_INT");
		AddLineQueue("flt_neg1lshl20_int EQU FLT_NEG1LSHL20_INT");
		AddLineQueue("flt_neg1lshl23_int EQU FLT_NEG1LSHL23_INT");
		AddLineQueue("flt_neg1lshl24_int EQU FLT_NEG1LSHL24_INT");
		AddLineQueue("flt_neg1lshl27_int EQU FLT_NEG1LSHL27_INT");
		AddLineQueue("flt_neg1lshl28_int EQU FLT_NEG1LSHL28_INT");
		AddLineQueue("flt_neg1lshl31_int EQU FLT_NEG1LSHL31_INT");

		AddLineQueue("flt_false_int EQU FLT_FALSE_INT");
		AddLineQueue("flt_true_int EQU FLT_TRUE_INT");
		AddLineQueue("flt_error_int EQU FLT_ERROR_INT");

		AddLineQueue("flt_magic_int EQU FLT_MAGIC_INT");
		AddLineQueue("flt_sign_int EQU FLT_SIGN_INT");
		AddLineQueue("flt_invsign_int EQU FLT_INVSIGN_INT");

		AddLineQueue("flt_inf_int EQU FLT_INF_INT");
		AddLineQueue("flt_fin_int EQU FLT_FIN_INT");
		AddLineQueue("flt_invinf_int EQU FLT_INVINF_INT");
		AddLineQueue("flt_neginf_int EQU FLT_NEGINF_INT");
		AddLineQueue("flt_nan_int EQU FLT_NAN_INT");
		AddLineQueue("flt_qnan_int EQU FLT_QNAN_INT");
		AddLineQueue("flt_negqnan_int EQU FLT_NEGQNAN_INT");
		AddLineQueue("flt_nantest_int EQU FLT_NANTEST_INT");
		AddLineQueue("flt_abs_int EQU FLT_ABS_INT");
		AddLineQueue("flt_min_int EQU FLT_MIN_INT");
		AddLineQueue("flt_max_int EQU FLT_MAX_INT");
		AddLineQueue("flt_nofraction_int EQU FLT_NOFRACTION_INT");
		AddLineQueue("flt_mindenorm_int EQU FLT_MINDENORM_INT");
		AddLineQueue("flt_denormlimit_int EQU FLT_DENORMLIMIT_INT");
		AddLineQueue("flt_minnormal_int EQU FLT_MINNORMAL_INT");
		AddLineQueue("flt_maxnormal_int EQU FLT_MAXNORMAL_INT");

		AddLineQueue("flt_decdig_int EQU FLT_DECDIG_INT");
		AddLineQueue("flt_dig_int EQU FLT_DIG_INT");
		AddLineQueue("flt_negdecdig_int EQU FLT_NEGDECDIG_INT");
		AddLineQueue("flt_negdig_int EQU FLT_NEGDIG_INT");
		AddLineQueue("flt_eps_int EQU FLT_EPS_INT");
		AddLineQueue("flt_epsilon_int EQU FLT_EPSILON_INT");
		AddLineQueue("flt_normeps_int EQU FLT_NORMEPS_INT");
		AddLineQueue("flt_guard_int EQU FLT_GUARD_INT");
		AddLineQueue("flt_mantpow2_int EQU FLT_MANTPOW2_INT");
		AddLineQueue("flt_maxmantpow2_int EQU FLT_MAXMANTPOW2_INT");
		AddLineQueue("flt_mantdig_int EQU FLT_MANTDIG_INT");
		AddLineQueue("flt_mant_int EQU FLT_MANT_INT");
		AddLineQueue("flt_negmantdig_int EQU FLT_NEGMANTDIG_INT");
		AddLineQueue("flt_negmant_int EQU FLT_NEGMANT_INT");
		AddLineQueue("flt_maxexp_int EQU FLT_MAXEXP_INT");
		AddLineQueue("flt_expsign_int EQU FLT_EXPSIGN_INT");
		AddLineQueue("flt_exp_int EQU FLT_EXP_INT");
		AddLineQueue("flt_negmaxexp_int EQU FLT_NEGMAXEXP_INT");
		AddLineQueue("flt_negexpsign_int EQU FLT_NEGEXPSIGN_INT");
		AddLineQueue("flt_negexp_int EQU FLT_NEGEXP_INT");
		AddLineQueue("flt_subnormalexp_int EQU FLT_SUBNORMALEXP_INT");
		AddLineQueue("flt_minexp_int EQU FLT_MINEXP_INT");
		AddLineQueue("flt_maxdecexp_int EQU FLT_MAXDECEXP_INT");
		AddLineQueue("flt_negmaxdecexp_int EQU FLT_NEGMAXDECEXP_INT");
		AddLineQueue("flt_mindecexp_int EQU FLT_MINDECEXP_INT");
		AddLineQueue("flt_expfield_int EQU FLT_EXPFIELD_INT");
		AddLineQueue("flt_mantfield_int EQU FLT_MANTFIELD_INT");
		AddLineQueue("flt_norm_int EQU FLT_NORM_INT");
		AddLineQueue("flt_radix_int EQU FLT_RADIX_INT");
		AddLineQueue("flt_rounds_int EQU FLT_ROUNDS_INT");
		AddLineQueue("flt_subdec_int EQU FLT_SUBDEC_INT");
		AddLineQueue("flt_sqrtmax_int EQU FLT_SQRTMAX_INT");
		AddLineQueue("flt_smallnormal_int EQU FLT_SMALLNORMAL_INT");

		AddLineQueue("flt_halfminuseps_int EQU FLT_HALFMINUSEPS_INT");
		AddLineQueue("flt_trueint_int EQU FLT_TRUEINT_INT");

		AddLineQueue("flt_byte_int EQU FLT_BYTE_INT");
		AddLineQueue("flt_byte_even_int EQU FLT_BYTE_EVEN_INT");
		AddLineQueue("flt_byte_odd_int EQU FLT_BYTE_ODD_INT");
		AddLineQueue("flt_4low_int EQU FLT_4LOW_INT");
		AddLineQueue("flt_4high_int EQU FLT_4HIGH_INT");
		AddLineQueue("flt_flip4_int EQU FLT_FLIP4_INT");
		AddLineQueue("flt_8low_int EQU FLT_8LOW_INT");
		AddLineQueue("flt_8high_int EQU FLT_8HIGH_INT");
		AddLineQueue("flt_flip8_int EQU FLT_FLIP8_INT");
		AddLineQueue("flt_16low_int EQU FLT_16LOW_INT");
		AddLineQueue("flt_16high_int EQU FLT_16HIGH_INT");
		AddLineQueue("flt_flip16_int EQU FLT_FLIP16_INT");
		AddLineQueue("flt_24low_int EQU FLT_24LOW_INT");
		AddLineQueue("flt_24high_int EQU FLT_24HIGH_INT");
		AddLineQueue("flt_flip24_int EQU FLT_FLIP24_INT");
		AddLineQueue("flt_28low_int EQU FLT_28LOW_INT");
		AddLineQueue("flt_28high_int EQU FLT_28HIGH_INT");
		AddLineQueue("flt_flip28_int EQU FLT_FLIP28_INT");
		AddLineQueue("flt_32low_int EQU FLT_32LOW_INT");
		AddLineQueue("flt_32high_int EQU FLT_32HIGH_INT");
		AddLineQueue("flt_flip32_int EQU FLT_FLIP32_INT");

		AddLineQueue("flt_0_int EQU FLT_0_INT");
		AddLineQueue("flt_0d5_int EQU FLT_0D5_INT");
		AddLineQueue("flt_1_int EQU FLT_1_INT");
		AddLineQueue("flt_1d5_int EQU FLT_1D5_INT");
		AddLineQueue("flt_2_int EQU FLT_2_INT");
		AddLineQueue("flt_2d5_int EQU FLT_2D5_INT");
		AddLineQueue("flt_3_int EQU FLT_3_INT");
		AddLineQueue("flt_4_int EQU FLT_4_INT");
		AddLineQueue("flt_5_int EQU FLT_5_INT");
		AddLineQueue("flt_6_int EQU FLT_6_INT");
		AddLineQueue("flt_7_int EQU FLT_7_INT");
		AddLineQueue("flt_8_int EQU FLT_8_INT");
		AddLineQueue("flt_9_int EQU FLT_9_INT");
		AddLineQueue("flt_10_int EQU FLT_10_INT");
		AddLineQueue("flt_20_int EQU FLT_20_INT");
		AddLineQueue("flt_23_int EQU FLT_23_INT");
		AddLineQueue("flt_23d5_int EQU FLT_23D5_INT");
		AddLineQueue("flt_24_int EQU FLT_24_INT");
		AddLineQueue("flt_24d5_int EQU FLT_24D5_INT");
		AddLineQueue("flt_25_int EQU FLT_25_INT");

		AddLineQueue("flt_128_int EQU FLT_128_INT");

		AddLineQueue("flt_253_int EQU FLT_253_INT");

		AddLineQueue("flt_neg0_int EQU FLT_NEG0_INT");
		AddLineQueue("flt_neg1_int EQU FLT_NEG1_INT");

		AddLineQueue("flt_neg150_int EQU FLT_NEG150_INT");

		AddLineQueue("flt_a8_int EQU FLT_A8_INT");
		AddLineQueue("flt_r8_int EQU FLT_R8_INT");
		AddLineQueue("flt_g8_int EQU FLT_G8_INT");
		AddLineQueue("flt_b8_int EQU FLT_B8_INT");

		AddLineQueue("flt_flipa8_int EQU FLT_FLIPA8_INT");
		AddLineQueue("flt_flipr8_int EQU FLT_FLIPR8_INT");
		AddLineQueue("flt_flipg8_int EQU FLT_FLIPG8_INT");
		AddLineQueue("flt_flipb8_int EQU FLT_FLIPB8_INT");

		AddLineQueue("flt_a2_int EQU FLT_A2_INT");
		AddLineQueue("flt_b10_int EQU FLT_B10_INT");
		AddLineQueue("flt_g10_int EQU FLT_G10_INT");
		AddLineQueue("flt_r10_int EQU FLT_R10_INT");

		AddLineQueue("flt_flipa2_int EQU FLT_FLIPA2_INT");
		AddLineQueue("flt_flipb10_int EQU FLT_FLIPB10_INT");
		AddLineQueue("flt_flipg10_int EQU FLT_FLIPG10_INT");
		AddLineQueue("flt_flipr10_int EQU FLT_FLIPR10_INT");

		AddLineQueue("flt_bin128_int EQU FLT_BIN128_INT");
		AddLineQueue("flt_binneg150_int EQU FLT_BINNEG150_INT");

		AddLineQueue("flt_maxrand_int EQU FLT_MAXRAND_INT");

		AddLineQueue("flt_maxi8_int EQU FLT_MAXI8_INT");
		AddLineQueue("flt_mini8_int EQU FLT_MINI8_INT");
		AddLineQueue("flt_maxu8_int EQU FLT_MAXU8_INT");

		AddLineQueue("flt_maxi16_int EQU FLT_MAXI16_INT");
		AddLineQueue("flt_mini16_int EQU FLT_MINI16_INT");
		AddLineQueue("flt_maxu16_int EQU FLT_MAXU16_INT");

		AddLineQueue("flt_maxi32_int EQU FLT_MAXI32_INT");
		AddLineQueue("flt_mini32_int EQU FLT_MINI32_INT");
		AddLineQueue("flt_maxu32_int EQU FLT_MAXU32_INT");

		AddLineQueue("flt_maxi8xu8_int EQU FLT_MAXI8XU8_INT");
		AddLineQueue("flt_mini8xu8_int EQU FLT_MINI8XU8_INT");
		AddLineQueue("flt_maxi8xu16_int EQU FLT_MAXI8XU16_INT");
		AddLineQueue("flt_mini8xu16_int EQU FLT_MINI8XU16_INT");

		AddLineQueue("flt_maxi16xu16_int EQU FLT_MAXI16XU16_INT");
		AddLineQueue("flt_mini16xu16_int EQU FLT_MINI16XU16_INT");

		AddLineQueue("flt_fixunsigned_int EQU FLT_FIXUNSIGNED_INT");
		AddLineQueue("flt_fixunsigned32_int EQU FLT_FIXUNSIGNED32_INT");
		AddLineQueue("flt_fixmaxi32_int EQU FLT_FIXMAXI32_INT");
		AddLineQueue("flt_fixmaxu32_int EQU FLT_FIXMAXU32_INT");

		/*float*/
		AddLineQueue("flt_1lshl3 EQU FLT_1LSHL3");
		AddLineQueue("flt_1lshl4 EQU FLT_1LSHL4");
		AddLineQueue("flt_1lshl7 EQU FLT_1LSHL7");
		AddLineQueue("flt_1lshl8 EQU FLT_1LSHL8");
		AddLineQueue("flt_1lshl11 EQU FLT_1LSHL11");
		AddLineQueue("flt_1lshl12 EQU FLT_1LSHL12");
		AddLineQueue("flt_1lshl15 EQU FLT_1LSHL15");
		AddLineQueue("flt_1lshl16 EQU FLT_1LSHL16");
		AddLineQueue("flt_1lshl19 EQU FLT_1LSHL10");
		AddLineQueue("flt_1lshl20 EQU FLT_1LSHL20");
		AddLineQueue("flt_1lshl23 EQU FLT_1LSHL23");
		AddLineQueue("flt_1lshl24 EQU FLT_1LSHL24");
		AddLineQueue("flt_1lshl27 EQU FLT_1LSHL27");
		AddLineQueue("flt_1lshl28 EQU FLT_1LSHL28");
		AddLineQueue("flt_1lshl31 EQU FLT_1LSHL31");

		AddLineQueue("flt_neg1lshl3 EQU FLT_NEG1LSHL3");
		AddLineQueue("flt_neg1lshl4 EQU FLT_NEG1LSHL4");
		AddLineQueue("flt_neg1lshl7 EQU FLT_NEG1LSHL7");
		AddLineQueue("flt_neg1lshl8 EQU FLT_NEG1LSHL8");
		AddLineQueue("flt_neg1lshl11 EQU FLT_NEG1LSHL11");
		AddLineQueue("flt_neg1lshl12 EQU FLT_NEG1LSHL12");
		AddLineQueue("flt_neg1lshl15 EQU FLT_NEG1LSHL15");
		AddLineQueue("flt_neg1lshl16 EQU FLT_NEG1LSHL16");
		AddLineQueue("flt_neg1lshl19 EQU FLT_NEG1LSHL10");
		AddLineQueue("flt_neg1lshl20 EQU FLT_NEG1LSHL20");
		AddLineQueue("flt_neg1lshl23 EQU FLT_NEG1LSHL23");
		AddLineQueue("flt_neg1lshl24 EQU FLT_NEG1LSHL24");
		AddLineQueue("flt_neg1lshl27 EQU FLT_NEG1LSHL27");
		AddLineQueue("flt_neg1lshl28 EQU FLT_NEG1LSHL28");
		AddLineQueue("flt_neg1lshl31 EQU FLT_NEG1LSHL31");

		AddLineQueue("flt_false EQU FLT_FALSE");
		AddLineQueue("flt_true EQU FLT_TRUE");

		AddLineQueue("flt_magic EQU FLT_MAGIC");
		AddLineQueue("flt_sign EQU FLT_SIGN");
		AddLineQueue("flt_invsign EQU FLT_INVSIGN");

		AddLineQueue("flt_inf EQU FLT_INF");
		AddLineQueue("flt_fin EQU FLT_FIN");
		AddLineQueue("flt_invinf EQU FLT_INVINF");
		AddLineQueue("flt_neginf EQU FLT_NEGINF");
		AddLineQueue("flt_nan EQU FLT_NAN");
		AddLineQueue("flt_qnan EQU FLT_QNAN");
		AddLineQueue("flt_negqnan EQU FLT_NEGQNAN");
		AddLineQueue("flt_nantest EQU FLT_NANTEST");
		AddLineQueue("flt_abs EQU FLT_ABS");
		AddLineQueue("flt_min EQU FLT_MIN");
		AddLineQueue("flt_max EQU FLT_MAX");
		AddLineQueue("flt_nofraction EQU FLT_NOFRACTION");
		AddLineQueue("flt_mindenorm EQU FLT_MINDENORM");
		AddLineQueue("flt_denormlimit EQU FLT_DENORMLIMIT");
		AddLineQueue("flt_minnormal EQU FLT_MINNORMAL");
		AddLineQueue("flt_maxnormal EQU FLT_MAXNORMAL");

		AddLineQueue("flt_decdig EQU FLT_DECDIG");
		AddLineQueue("flt_dig EQU FLT_DIG");
		AddLineQueue("flt_negdecdig EQU FLT_NEGDECDIG");
		AddLineQueue("flt_negdig EQU FLT_NEGDIG");
		AddLineQueue("flt_eps EQU FLT_EPS");
		AddLineQueue("flt_epsilon EQU FLT_EPSILON");
		AddLineQueue("flt_normeps EQU FLT_NORMEPS");
		AddLineQueue("flt_guard EQU FLT_GUARD");
		AddLineQueue("flt_mantpow2 EQU FLT_MANTPOW2");
		AddLineQueue("flt_maxmantpow2 EQU FLT_MAXMANTPOW2");
		AddLineQueue("flt_mantdig EQU FLT_MANTDIG");
		AddLineQueue("flt_mant EQU FLT_MANT");
		AddLineQueue("flt_negmantdig EQU FLT_NEGMANTDIG");
		AddLineQueue("flt_negmant EQU FLT_NEGMANT");
		AddLineQueue("flt_maxexp EQU FLT_MAXEXP");
		AddLineQueue("flt_expsign EQU FLT_EXPSIGN");
		AddLineQueue("flt_exp EQU FLT_EXP");
		AddLineQueue("flt_negmaxexp EQU FLT_NEGMAXEXP");
		AddLineQueue("flt_negexpsign EQU FLT_NEGEXPSIGN");
		AddLineQueue("flt_negexp EQU FLT_NEGEXP");
		AddLineQueue("flt_subnormalexp EQU FLT_SUBNORMALEXP");
		AddLineQueue("flt_minexp EQU FLT_MINEXP");
		AddLineQueue("flt_maxdecexp EQU FLT_MAXDECEXP");
		AddLineQueue("flt_negmaxdecexp EQU FLT_NEGMAXDECEXP");
		AddLineQueue("flt_mindecexp EQU FLT_MINDECEXP");
		AddLineQueue("flt_expfield EQU FLT_EXPFIELD");
		AddLineQueue("flt_mantfield EQU FLT_MANTFIELD");
		AddLineQueue("flt_norm EQU FLT_NORM");
		AddLineQueue("flt_radix EQU FLT_RADIX");
		AddLineQueue("flt_rounds EQU FLT_ROUNDS");
		AddLineQueue("flt_subdec EQU FLT_SUBDEC");
		AddLineQueue("flt_sqrtmax EQU FLT_SQRTMAX");
		AddLineQueue("flt_smallnormal EQU FLT_SMALLNORMAL");

		AddLineQueue("flt_halfminuseps EQU FLT_HALFMINUSEPS");
		AddLineQueue("flt_trueint EQU FLT_TRUEINT");

		AddLineQueue("flt_byte EQU FLT_BYTE");
		AddLineQueue("flt_byte_even EQU FLT_BYTE_EVEN");
		AddLineQueue("flt_byte_odd EQU FLT_BYTE_ODD");
		AddLineQueue("flt_4low EQU FLT_4LOW");
		AddLineQueue("flt_4high EQU FLT_4HIGH");
		AddLineQueue("flt_flip4 EQU FLT_FLIP4");
		AddLineQueue("flt_8low EQU FLT_8LOW");
		AddLineQueue("flt_8high EQU FLT_8HIGH");
		AddLineQueue("flt_flip8 EQU FLT_FLIP8");
		AddLineQueue("flt_16low EQU FLT_16LOW");
		AddLineQueue("flt_16high EQU FLT_16HIGH");
		AddLineQueue("flt_flip16 EQU FLT_FLIP16");
		AddLineQueue("flt_24low EQU FLT_24LOW");
		AddLineQueue("flt_24high EQU FLT_24HIGH");
		AddLineQueue("flt_flip24 EQU FLT_FLIP24");
		AddLineQueue("flt_28low EQU FLT_28LOW");
		AddLineQueue("flt_28high EQU FLT_28HIGH");
		AddLineQueue("flt_flip28 EQU FLT_FLIP28");
		AddLineQueue("flt_32low EQU FLT_32LOW");
		AddLineQueue("flt_32high EQU FLT_32HIGH");
		AddLineQueue("flt_flip32 EQU FLT_FLIP32");

		AddLineQueue("flt_0 EQU FLT_0");
		AddLineQueue("flt_0d0001 EQU FLT_0D0001");
		AddLineQueue("flt_0d0002 EQU FLT_0D0002");
		AddLineQueue("flt_0d0003 EQU FLT_0D0003");
		AddLineQueue("flt_0d0004 EQU FLT_0D0004");
		AddLineQueue("flt_0d0005 EQU FLT_0D0005");
		AddLineQueue("flt_0d0006 EQU FLT_0D0006");
		AddLineQueue("flt_0d0007 EQU FLT_0D0007");
		AddLineQueue("flt_0d0008 EQU FLT_0D0008");
		AddLineQueue("flt_0d0009 EQU FLT_0D0009");
		AddLineQueue("flt_0d001 EQU FLT_0D001");
		AddLineQueue("flt_0d002 EQU FLT_0D002");
		AddLineQueue("flt_0d003 EQU FLT_0D003");
		AddLineQueue("flt_0d004 EQU FLT_0D004");
		AddLineQueue("flt_0d005 EQU FLT_0D005");
		AddLineQueue("flt_0d006 EQU FLT_0D006");
		AddLineQueue("flt_0d007 EQU FLT_0D007");
		AddLineQueue("flt_0d008 EQU FLT_0D008");
		AddLineQueue("flt_0d009 EQU FLT_0D009");
		AddLineQueue("flt_0d01 EQU FLT_0D01");
		AddLineQueue("flt_0d02 EQU FLT_0D02");
		AddLineQueue("flt_0d025 EQU FLT_0D025");
		AddLineQueue("flt_0d03 EQU FLT_0D03");
		AddLineQueue("flt_0d04 EQU FLT_0D04");
		AddLineQueue("flt_0d05 EQU FLT_0D05");
		AddLineQueue("flt_0d06 EQU FLT_0D06");
		AddLineQueue("flt_0d07 EQU FLT_0D07");
		AddLineQueue("flt_0d08 EQU FLT_0D08");
		AddLineQueue("flt_0d09 EQU FLT_0D09");
		AddLineQueue("flt_0d1 EQU FLT_0D1");
		AddLineQueue("flt_0d2 EQU FLT_0D2");
		AddLineQueue("flt_0d25 EQU FLT_0D25");
		AddLineQueue("flt_0d3 EQU FLT_0D3");
		AddLineQueue("flt_0d4 EQU FLT_0D4");
		AddLineQueue("flt_0d5 EQU FLT_0D5");
		AddLineQueue("flt_0d6 EQU FLT_0D6");
		AddLineQueue("flt_0d7 EQU FLT_0D7");
		AddLineQueue("flt_0d8 EQU FLT_0D8");
		AddLineQueue("flt_0d9 EQU FLT_0D9");
		AddLineQueue("flt_1 EQU FLT_1");
		AddLineQueue("flt_1d25 EQU FLT_1D25");
		AddLineQueue("flt_1d5 EQU FLT_1D5");
		AddLineQueue("flt_2 EQU FLT_2");
		AddLineQueue("flt_2d25 EQU FLT_2D25");
		AddLineQueue("flt_2d5 EQU FLT_2D5");
		AddLineQueue("flt_3 EQU FLT_3");
		AddLineQueue("flt_3d25 EQU FLT_3D25");
		AddLineQueue("flt_3d5 EQU FLT_3D5");
		AddLineQueue("flt_4 EQU FLT_4");
		AddLineQueue("flt_4d25 EQU FLT_4D25");
		AddLineQueue("flt_4d5 EQU FLT_4D5");
		AddLineQueue("flt_5 EQU FLT_5");
		AddLineQueue("flt_5d25 EQU FLT_5D25");
		AddLineQueue("flt_5d5 EQU FLT_5D5");
		AddLineQueue("flt_6 EQU FLT_6");
		AddLineQueue("flt_6d25 EQU FLT_6D25");
		AddLineQueue("flt_6d5 EQU FLT_6D5");
		AddLineQueue("flt_7 EQU FLT_7");
		AddLineQueue("flt_7d25 EQU FLT_7D25");
		AddLineQueue("flt_7d5 EQU FLT_7D5");
		AddLineQueue("flt_8 EQU FLT_8");
		AddLineQueue("flt_8d25 EQU FLT_8D25");
		AddLineQueue("flt_8d5 EQU FLT_8D5");
		AddLineQueue("flt_9 EQU FLT_9");
		AddLineQueue("flt_9d25 EQU FLT_9D25");
		AddLineQueue("flt_9d5 EQU FLT_9D5");
		AddLineQueue("flt_10 EQU FLT_10");
		AddLineQueue("flt_11 EQU FLT_11");
		AddLineQueue("flt_12 EQU FLT_12");
		AddLineQueue("flt_13 EQU FLT_13");
		AddLineQueue("flt_14 EQU FLT_14");
		AddLineQueue("flt_15 EQU FLT_15");
		AddLineQueue("flt_16 EQU FLT_16");
		AddLineQueue("flt_17 EQU FLT_17");
		AddLineQueue("flt_18 EQU FLT_18");
		AddLineQueue("flt_19 EQU FLT_19");
		AddLineQueue("flt_20 EQU FLT_20");
		AddLineQueue("flt_21 EQU FLT_21");
		AddLineQueue("flt_22 EQU FLT_22");
		AddLineQueue("flt_23 EQU FLT_23");
		AddLineQueue("flt_24 EQU FLT_24");
		AddLineQueue("flt_24d5 EQU FLT_24D5");
		AddLineQueue("flt_25 EQU FLT_25");
		AddLineQueue("flt_26 EQU FLT_26");
		AddLineQueue("flt_27 EQU FLT_27");
		AddLineQueue("flt_28 EQU FLT_28");
		AddLineQueue("flt_29 EQU FLT_29");
		AddLineQueue("flt_30 EQU FLT_30");
		AddLineQueue("flt_31 EQU FLT_31");
		AddLineQueue("flt_32 EQU FLT_32");
		AddLineQueue("flt_33 EQU FLT_33");
		AddLineQueue("flt_34 EQU FLT_34");
		AddLineQueue("flt_35 EQU FLT_35");
		AddLineQueue("flt_36 EQU FLT_36");
		AddLineQueue("flt_37 EQU FLT_37");
		AddLineQueue("flt_38 EQU FLT_38");
		AddLineQueue("flt_39 EQU FLT_39");
		AddLineQueue("flt_40 EQU FLT_40");
		AddLineQueue("flt_41 EQU FLT_41");
		AddLineQueue("flt_42 EQU FLT_42");
		AddLineQueue("flt_43 EQU FLT_43");
		AddLineQueue("flt_44 EQU FLT_44");
		AddLineQueue("flt_45 EQU FLT_45");
		AddLineQueue("flt_46 EQU FLT_46");
		AddLineQueue("flt_47 EQU FLT_47");
		AddLineQueue("flt_48 EQU FLT_48");
		AddLineQueue("flt_49 EQU FLT_49");
		AddLineQueue("flt_50 EQU FLT_50");
		AddLineQueue("flt_51 EQU FLT_51");
		AddLineQueue("flt_52 EQU FLT_52");
		AddLineQueue("flt_53 EQU FLT_53");
		AddLineQueue("flt_54 EQU FLT_54");
		AddLineQueue("flt_55 EQU FLT_55");
		AddLineQueue("flt_56 EQU FLT_56");
		AddLineQueue("flt_57 EQU FLT_57");
		AddLineQueue("flt_58 EQU FLT_58");
		AddLineQueue("flt_59 EQU FLT_59");
		AddLineQueue("flt_60 EQU FLT_60");
		AddLineQueue("flt_61 EQU FLT_61");
		AddLineQueue("flt_62 EQU FLT_62");
		AddLineQueue("flt_63 EQU FLT_63");
		AddLineQueue("flt_64 EQU FLT_64");
		AddLineQueue("flt_65 EQU FLT_65");
		AddLineQueue("flt_66 EQU FLT_66");
		AddLineQueue("flt_67 EQU FLT_67");
		AddLineQueue("flt_68 EQU FLT_68");
		AddLineQueue("flt_69 EQU FLT_69");
		AddLineQueue("flt_70 EQU FLT_70");
		AddLineQueue("flt_71 EQU FLT_71");
		AddLineQueue("flt_72 EQU FLT_72");
		AddLineQueue("flt_73 EQU FLT_73");
		AddLineQueue("flt_74 EQU FLT_74");
		AddLineQueue("flt_75 EQU FLT_75");
		AddLineQueue("flt_76 EQU FLT_76");
		AddLineQueue("flt_77 EQU FLT_77");
		AddLineQueue("flt_78 EQU FLT_78");
		AddLineQueue("flt_79 EQU FLT_79");
		AddLineQueue("flt_80 EQU FLT_80");
		AddLineQueue("flt_81 EQU FLT_81");
		AddLineQueue("flt_82 EQU FLT_82");
		AddLineQueue("flt_83 EQU FLT_83");
		AddLineQueue("flt_84 EQU FLT_84");
		AddLineQueue("flt_85 EQU FLT_85");
		AddLineQueue("flt_86 EQU FLT_86");
		AddLineQueue("flt_87 EQU FLT_87");
		AddLineQueue("flt_88 EQU FLT_88");
		AddLineQueue("flt_89 EQU FLT_89");
		AddLineQueue("flt_90 EQU FLT_90");
		AddLineQueue("flt_91 EQU FLT_91");
		AddLineQueue("flt_92 EQU FLT_92");
		AddLineQueue("flt_93 EQU FLT_93");
		AddLineQueue("flt_94 EQU FLT_94");
		AddLineQueue("flt_95 EQU FLT_95");
		AddLineQueue("flt_96 EQU FLT_96");
		AddLineQueue("flt_97 EQU FLT_97");
		AddLineQueue("flt_98 EQU FLT_98");
		AddLineQueue("flt_99 EQU FLT_99");
		AddLineQueue("flt_100 EQU FLT_100");
		AddLineQueue("flt_125 EQU FLT_125");
		AddLineQueue("flt_126 EQU FLT_126");
		AddLineQueue("flt_127 EQU FLT_127");
		AddLineQueue("flt_128 EQU FLT_128");
		AddLineQueue("flt_140 EQU FLT_140");
		AddLineQueue("flt_145 EQU FLT_145");
		AddLineQueue("flt_150 EQU FLT_150");
		AddLineQueue("flt_180 EQU FLT_180");
		AddLineQueue("flt_253 EQU FLT_253");
		AddLineQueue("flt_254 EQU FLT_254");
		AddLineQueue("flt_255 EQU FLT_255");
		AddLineQueue("flt_256 EQU FLT_256");
		AddLineQueue("flt_360 EQU FLT_360");
		AddLineQueue("flt_511 EQU FLT_511");
		AddLineQueue("flt_512 EQU FLT_512");
		AddLineQueue("flt_513 EQU FLT_513");
		AddLineQueue("flt_1023 EQU FLT_1023");
		AddLineQueue("flt_1024 EQU FLT_1024");
		AddLineQueue("flt_1025 EQU FLT_1025");

		AddLineQueue("flt_32767 EQU FLT_32767");
		AddLineQueue("flt_32768 EQU FLT_32768");
		AddLineQueue("flt_65535 EQU FLT_65535");
		AddLineQueue("flt_65536 EQU FLT_65536");
		AddLineQueue("flt_2147483647 EQU FLT_2147483647");
		AddLineQueue("flt_2147483648 EQU FLT_2147483648");
		AddLineQueue("flt_4294967295 EQU FLT_4294967295");
		AddLineQueue("flt_4294967296 EQU FLT_4294967296");

		AddLineQueue("flt_neg0 EQU FLT_NEG0");
		AddLineQueue("flt_neg0d0001 EQU FLT_NEG0D0001");
		AddLineQueue("flt_neg0d0002 EQU FLT_NEG0D0002");
		AddLineQueue("flt_neg0d0003 EQU FLT_NEG0D0003");
		AddLineQueue("flt_neg0d0004 EQU FLT_NEG0D0004");
		AddLineQueue("flt_neg0d0005 EQU FLT_NEG0D0005");
		AddLineQueue("flt_neg0d0006 EQU FLT_NEG0D0006");
		AddLineQueue("flt_neg0d0007 EQU FLT_NEG0D0007");
		AddLineQueue("flt_neg0d0008 EQU FLT_NEG0D0008");
		AddLineQueue("flt_neg0d0009 EQU FLT_NEG0D0009");
		AddLineQueue("flt_neg0d001 EQU FLT_NEG0D001");
		AddLineQueue("flt_neg0d002 EQU FLT_NEG0D002");
		AddLineQueue("flt_neg0d003 EQU FLT_NEG0D003");
		AddLineQueue("flt_neg0d004 EQU FLT_NEG0D004");
		AddLineQueue("flt_neg0d005 EQU FLT_NEG0D005");
		AddLineQueue("flt_neg0d006 EQU FLT_NEG0D006");
		AddLineQueue("flt_neg0d007 EQU FLT_NEG0D007");
		AddLineQueue("flt_neg0d008 EQU FLT_NEG0D008");
		AddLineQueue("flt_neg0d009 EQU FLT_NEG0D009");
		AddLineQueue("flt_neg0d01 EQU FLT_NEG0D01");
		AddLineQueue("flt_neg0d02 EQU FLT_NEG0D02");
		AddLineQueue("flt_neg0d025 EQU FLT_NEG0D025");
		AddLineQueue("flt_neg0d03 EQU FLT_NEG0D03");
		AddLineQueue("flt_neg0d04 EQU FLT_NEG0D04");
		AddLineQueue("flt_neg0d05 EQU FLT_NEG0D05");
		AddLineQueue("flt_neg0d06 EQU FLT_NEG0D06");
		AddLineQueue("flt_neg0d07 EQU FLT_NEG0D07");
		AddLineQueue("flt_neg0d08 EQU FLT_NEG0D08");
		AddLineQueue("flt_neg0d09 EQU FLT_NEG0D09");
		AddLineQueue("flt_neg0d1 EQU FLT_NEG0D1");
		AddLineQueue("flt_neg0d2 EQU FLT_NEG0D2");
		AddLineQueue("flt_neg0d25 EQU FLT_NEG0D25");
		AddLineQueue("flt_neg0d3 EQU FLT_NEG0D3");
		AddLineQueue("flt_neg0d4 EQU FLT_NEG0D4");
		AddLineQueue("flt_neg0d5 EQU FLT_NEG0D5");
		AddLineQueue("flt_neg0d6 EQU FLT_NEG0D6");
		AddLineQueue("flt_neg0d7 EQU FLT_NEG0D7");
		AddLineQueue("flt_neg0d8 EQU FLT_NEG0D8");
		AddLineQueue("flt_neg0d9 EQU FLT_NEG0D9");
		AddLineQueue("flt_neg1 EQU FLT_NEG1");
		AddLineQueue("flt_neg1d25 EQU FLT_NEG1D25");
		AddLineQueue("flt_neg2 EQU FLT_NEG2");
		AddLineQueue("flt_neg2d25 EQU FLT_NEG2D25");
		AddLineQueue("flt_neg3 EQU FLT_NEG3");
		AddLineQueue("flt_neg3d25 EQU FLT_NEG3D25");
		AddLineQueue("flt_neg4 EQU FLT_NEG4");
		AddLineQueue("flt_neg4d25 EQU FLT_NEG4D25");
		AddLineQueue("flt_neg5 EQU FLT_NEG5");
		AddLineQueue("flt_neg5d25 EQU FLT_NEG5D25");
		AddLineQueue("flt_neg6 EQU FLT_NEG6");
		AddLineQueue("flt_neg6d25 EQU FLT_NEG6D25");
		AddLineQueue("flt_neg7 EQU FLT_NEG7");
		AddLineQueue("flt_neg7d25 EQU FLT_NEG7D25");
		AddLineQueue("flt_neg8 EQU FLT_NEG8");
		AddLineQueue("flt_neg8d25 EQU FLT_NEG8D25");
		AddLineQueue("flt_neg9 EQU FLT_NEG9");
		AddLineQueue("flt_neg9d25 EQU FLT_NEG9D25");
		AddLineQueue("flt_neg10 EQU FLT_NEG10");
		AddLineQueue("flt_neg11 EQU FLT_NEG11");
		AddLineQueue("flt_neg12 EQU FLT_NEG12");
		AddLineQueue("flt_neg13 EQU FLT_NEG13");
		AddLineQueue("flt_neg14 EQU FLT_NEG14");
		AddLineQueue("flt_neg15 EQU FLT_NEG15");
		AddLineQueue("flt_neg16 EQU FLT_NEG16");
		AddLineQueue("flt_neg17 EQU FLT_NEG17");
		AddLineQueue("flt_neg18 EQU FLT_NEG18");
		AddLineQueue("flt_neg19 EQU FLT_NEG19");
		AddLineQueue("flt_neg20 EQU FLT_NEG20");
		AddLineQueue("flt_neg21 EQU FLT_NEG21");
		AddLineQueue("flt_neg22 EQU FLT_NEG22");
		AddLineQueue("flt_neg23 EQU FLT_NEG23");
		AddLineQueue("flt_neg24 EQU FLT_NEG24");
		AddLineQueue("flt_neg24d5 EQU FLT_NEG24D5");
		AddLineQueue("flt_neg25 EQU FLT_NEG25");
		AddLineQueue("flt_neg26 EQU FLT_NEG26");
		AddLineQueue("flt_neg27 EQU FLT_NEG27");
		AddLineQueue("flt_neg28 EQU FLT_NEG28");
		AddLineQueue("flt_neg29 EQU FLT_NEG29");
		AddLineQueue("flt_neg30 EQU FLT_NEG30");
		AddLineQueue("flt_neg31 EQU FLT_NEG31");
		AddLineQueue("flt_neg32 EQU FLT_NEG32");
		AddLineQueue("flt_neg33 EQU FLT_NEG33");
		AddLineQueue("flt_neg34 EQU FLT_NEG34");
		AddLineQueue("flt_neg35 EQU FLT_NEG35");
		AddLineQueue("flt_neg36 EQU FLT_NEG36");
		AddLineQueue("flt_neg37 EQU FLT_NEG37");
		AddLineQueue("flt_neg38 EQU FLT_NEG38");
		AddLineQueue("flt_neg39 EQU FLT_NEG39");
		AddLineQueue("flt_neg40 EQU FLT_NEG40");
		AddLineQueue("flt_neg41 EQU FLT_NEG41");
		AddLineQueue("flt_neg42 EQU FLT_NEG42");
		AddLineQueue("flt_neg43 EQU FLT_NEG43");
		AddLineQueue("flt_neg44 EQU FLT_NEG44");
		AddLineQueue("flt_neg45 EQU FLT_NEG45");
		AddLineQueue("flt_neg46 EQU FLT_NEG46");
		AddLineQueue("flt_neg47 EQU FLT_NEG47");
		AddLineQueue("flt_neg48 EQU FLT_NEG48");
		AddLineQueue("flt_neg49 EQU FLT_NEG49");
		AddLineQueue("flt_neg50 EQU FLT_NEG50");
		AddLineQueue("flt_neg51 EQU FLT_NEG51");
		AddLineQueue("flt_neg52 EQU FLT_NEG52");
		AddLineQueue("flt_neg53 EQU FLT_NEG53");
		AddLineQueue("flt_neg54 EQU FLT_NEG54");
		AddLineQueue("flt_neg55 EQU FLT_NEG55");
		AddLineQueue("flt_neg56 EQU FLT_NEG56");
		AddLineQueue("flt_neg57 EQU FLT_NEG57");
		AddLineQueue("flt_neg58 EQU FLT_NEG58");
		AddLineQueue("flt_neg59 EQU FLT_NEG59");
		AddLineQueue("flt_neg60 EQU FLT_NEG60");
		AddLineQueue("flt_neg61 EQU FLT_NEG61");
		AddLineQueue("flt_neg62 EQU FLT_NEG62");
		AddLineQueue("flt_neg63 EQU FLT_NEG63");
		AddLineQueue("flt_neg64 EQU FLT_NEG64");
		AddLineQueue("flt_neg65 EQU FLT_NEG65");
		AddLineQueue("flt_neg66 EQU FLT_NEG66");
		AddLineQueue("flt_neg67 EQU FLT_NEG67");
		AddLineQueue("flt_neg68 EQU FLT_NEG68");
		AddLineQueue("flt_neg69 EQU FLT_NEG69");
		AddLineQueue("flt_neg70 EQU FLT_NEG70");
		AddLineQueue("flt_neg71 EQU FLT_NEG71");
		AddLineQueue("flt_neg72 EQU FLT_NEG72");
		AddLineQueue("flt_neg73 EQU FLT_NEG73");
		AddLineQueue("flt_neg74 EQU FLT_NEG74");
		AddLineQueue("flt_neg75 EQU FLT_NEG75");
		AddLineQueue("flt_neg76 EQU FLT_NEG76");
		AddLineQueue("flt_neg77 EQU FLT_NEG77");
		AddLineQueue("flt_neg78 EQU FLT_NEG78");
		AddLineQueue("flt_neg79 EQU FLT_NEG79");
		AddLineQueue("flt_neg80 EQU FLT_NEG80");
		AddLineQueue("flt_neg81 EQU FLT_NEG81");
		AddLineQueue("flt_neg82 EQU FLT_NEG82");
		AddLineQueue("flt_neg83 EQU FLT_NEG83");
		AddLineQueue("flt_neg84 EQU FLT_NEG84");
		AddLineQueue("flt_neg85 EQU FLT_NEG85");
		AddLineQueue("flt_neg86 EQU FLT_NEG86");
		AddLineQueue("flt_neg87 EQU FLT_NEG87");
		AddLineQueue("flt_neg88 EQU FLT_NEG88");
		AddLineQueue("flt_neg89 EQU FLT_NEG89");
		AddLineQueue("flt_neg90 EQU FLT_NEG90");
		AddLineQueue("flt_neg91 EQU FLT_NEG91");
		AddLineQueue("flt_neg92 EQU FLT_NEG92");
		AddLineQueue("flt_neg93 EQU FLT_NEG93");
		AddLineQueue("flt_neg94 EQU FLT_NEG94");
		AddLineQueue("flt_neg95 EQU FLT_NEG95");
		AddLineQueue("flt_neg96 EQU FLT_NEG96");
		AddLineQueue("flt_neg97 EQU FLT_NEG97");
		AddLineQueue("flt_neg98 EQU FLT_NEG98");
		AddLineQueue("flt_neg99 EQU FLT_NEG99");
		AddLineQueue("flt_neg100 EQU FLT_NEG100");
		AddLineQueue("flt_neg125 EQU FLT_NEG125");
		AddLineQueue("flt_neg126 EQU FLT_NEG126");
		AddLineQueue("flt_neg127 EQU FLT_NEG127");
		AddLineQueue("flt_neg128 EQU FLT_NEG128");
		AddLineQueue("flt_neg140 EQU FLT_NEG140");
		AddLineQueue("flt_neg145 EQU FLT_NEG145");
		AddLineQueue("flt_neg150 EQU FLT_NEG150");
		AddLineQueue("flt_neg180 EQU FLT_NEG180");
		AddLineQueue("flt_neg253 EQU FLT_NEG253");
		AddLineQueue("flt_neg254 EQU FLT_NEG254");
		AddLineQueue("flt_neg255 EQU FLT_NEG255");
		AddLineQueue("flt_neg256 EQU FLT_NEG256");
		AddLineQueue("flt_neg360 EQU FLT_NEG360");
		AddLineQueue("flt_neg511 EQU FLT_NEG511");
		AddLineQueue("flt_neg512 EQU FLT_NEG512");
		AddLineQueue("flt_neg513 EQU FLT_NEG513");
		AddLineQueue("flt_neg1023 EQU FLT_NEG1023");
		AddLineQueue("flt_neg1024 EQU FLT_NEG1024");
		AddLineQueue("flt_neg1025 EQU FLT_NEG1025");

		AddLineQueue("flt_neg32767 EQU FLT_NEG32767");
		AddLineQueue("flt_neg32768 EQU FLT_NEG32768");
		AddLineQueue("flt_neg65535 EQU FLT_NEG65535");
		AddLineQueue("flt_neg65536 EQU FLT_NEG65536");
		AddLineQueue("flt_neg2147483647 EQU FLT_NEG2147483647");
		AddLineQueue("flt_neg2147483648 EQU FLT_NEG2147483648");
		AddLineQueue("flt_neg4294967295 EQU FLT_NEG4294967295");
		AddLineQueue("flt_neg4294967296 EQU FLT_NEG4294967296");

		AddLineQueue("flt_bin128 EQU FLT_BIN128");
		AddLineQueue("flt_binneg150 EQU FLT_BINNEG150");

		AddLineQueue("flt_maxrand EQU FLT_MAXRAND");

		AddLineQueue("flt_maxi8 EQU FLT_MAXI8");
		AddLineQueue("flt_mini8 EQU FLT_MINI8");
		AddLineQueue("flt_maxu8 EQU FLT_MAXU8");
		AddLineQueue("flt_minu8 EQU FLT_MINU8");

		AddLineQueue("flt_maxi16 EQU FLT_MAXI16");
		AddLineQueue("flt_mini16 EQU FLT_MINI16");
		AddLineQueue("flt_maxu16 EQU FLT_MAXU16");
		AddLineQueue("flt_minu16 EQU FLT_MINU16");

		AddLineQueue("flt_maxi32 EQU FLT_MAXI32");
		AddLineQueue("flt_mini32 EQU FLT_MINI32");
		AddLineQueue("flt_maxu32 EQU FLT_MAXU32");
		AddLineQueue("flt_minu32 EQU FLT_MINU32");

		AddLineQueue("flt_maxi8xu8 EQU FLT_MAXI8XU8");
		AddLineQueue("flt_mini8xu8 EQU FLT_MINI8XU8");
		AddLineQueue("flt_maxi8xu16 EQU FLT_MAXI8XU16");
		AddLineQueue("flt_mini8xu16 EQU FLT_MINI8XU16");

		AddLineQueue("flt_maxi16xu16 EQU FLT_MAXI16XU16");
		AddLineQueue("flt_mini16xu16 EQU FLT_MINI16XU16");

		AddLineQueue("flt_fixunsigned EQU FLT_FIXUNSIGNED");
		AddLineQueue("flt_fixunsigned32 EQU FLT_FIXUNSIGNED32");
		AddLineQueue("flt_fixmaxi32 EQU FLT_FIXMAXI32");
		AddLineQueue("flt_fixmaxu32 EQU FLT_FIXMAXU32");

		AddLineQueue("flt_rcpi16 EQU FLT_RCPI16");
		AddLineQueue("flt_rcpu16 EQU FLT_RCPU16");
		AddLineQueue("flt_rcpi16xu16 EQU FLT_RCPI16XU16");

		AddLineQueue("flt_fixaa8 EQU FLT_FIXAA8");
		AddLineQueue("flt_fixr8 EQU FLT_FIXR8");
		AddLineQueue("flt_fixg8 EQU FLT_FIXG8");
		AddLineQueue("flt_fixb8 EQU FLT_FIXB8");

		AddLineQueue("flt_norma8 EQU FLT_NORMA8");
		AddLineQueue("flt_normr8 EQU FLT_NORMR8");
		AddLineQueue("flt_normg8 EQU FLT_NORMG8");
		AddLineQueue("flt_normb8 EQU FLT_NORMB8");

		AddLineQueue("flt_fixaa2 EQU FLT_FIXAA2");
		AddLineQueue("flt_fixb10 EQU FLT_FIXB10");
		AddLineQueue("flt_fixg10 EQU FLT_FIXG10");
		AddLineQueue("flt_fixr10 EQU FLT_FIXR10");

		AddLineQueue("flt_norma2 EQU FLT_NORMA2");
		AddLineQueue("flt_normb10 EQU FLT_NORMB10");
		AddLineQueue("flt_normg10 EQU FLT_NORMG10");
		AddLineQueue("flt_normr10 EQU FLT_NORMR10");

		AddLineQueue("flt_mg EQU FLT_MG");
		AddLineQueue("flt_negmg EQU FLT_NEGMG");
		AddLineQueue("flt_halfmg EQU FLT_HALFMG");
		AddLineQueue("flt_neghalfmg EQU FLT_NEGHALFMG");
		AddLineQueue("flt_mgdiv4 EQU FLT_MGDIV4");
		AddLineQueue("flt_negmgdiv4 EQU FLT_NEGMGDIV4");
		AddLineQueue("flt_halfmgxmg EQU FLT_HALFMGXMG");
		AddLineQueue("flt_halfmgxsqrmg EQU FLT_HALFMGXSQRMG");
		AddLineQueue("flt_halfmgxcubemg EQU FLT_HALFMGXCUBEMG");
		AddLineQueue("flt_neghalfmgxmg EQU FLT_NEGHALFMGXMG");
		AddLineQueue("flt_neghalfmgxsqrmg EQU FLT_NEGHALFMGXSQRMG");
		AddLineQueue("flt_neghalfmgxcubemg EQU FLT_NEGHALFMGXCUBEMG");
		AddLineQueue("flt_sqrmg EQU FLT_SQRMG");
		AddLineQueue("flt_cubemg EQU FLT_CUBEMG");
		AddLineQueue("flt_sqrtmg EQU FLT_SQRTMG");
		AddLineQueue("flt_cbrtmg EQU FLT_CBRTMG");
		AddLineQueue("flt_rcpmg EQU FLT_RCPMG");
		AddLineQueue("flt_rcpsqrmg EQU FLT_RCPSQRMG");
		AddLineQueue("flt_rcpcubemg EQU FLT_RCPCUBEMG");
		AddLineQueue("flt_rcpsqrtmg EQU FLT_RCPSQRTMG");
		AddLineQueue("flt_rcpcbrtmg EQU FLT_RCPCBRTMG");

		AddLineQueue("flt_2mg EQU FLT_2MG");
		AddLineQueue("flt_neg2mg EQU FLT_NEG2MG");
		AddLineQueue("flt_sqr2mg EQU FLT_SQR2MG");
		AddLineQueue("flt_cube2mg EQU FLT_CUBE2MG");
		AddLineQueue("flt_sqrt2mg EQU FLT_SQRT2MG");
		AddLineQueue("flt_cbrt2mg EQU FLT_CBRT2MG");
		AddLineQueue("flt_4mg EQU FLT_4MG");
		AddLineQueue("flt_neg4mg EQU FLT_NEG4MG");
		AddLineQueue("flt_sqr4mg EQU FLT_SQR4MG");
		AddLineQueue("flt_cube4mg EQU FLT_CUBE4MG");
		AddLineQueue("flt_sqrt4mg EQU FLT_SQRT4MG");
		AddLineQueue("flt_cbrt4mg EQU FLT_CBRT4MG");
		AddLineQueue("flt_rcp2mg EQU FLT_RCP2MG");
		AddLineQueue("flt_rcp4mg EQU FLT_RCP4MG");

		AddLineQueue("flt_e EQU FLT_E");
		AddLineQueue("flt_exp EQU FLT_EXP");
		AddLineQueue("flt_loge EQU FLT_LOGE");
		AddLineQueue("flt_logehigh EQU FLT_LOGEHIGH");
		AddLineQueue("flt_log2e EQU FLT_LOG2E");
		AddLineQueue("flt_log2ehigh EQU FLT_LOG2EHIGH");
		AddLineQueue("flt_log10e EQU FLT_LOG10E");
		AddLineQueue("flt_rcplog2e EQU FLT_RCPLOG2E");
		AddLineQueue("flt_rcplog10e EQU FLT_RCPLOG10E");
		AddLineQueue("flt_log2t EQU FLT_LOG2T");
		AddLineQueue("flt_log2 EQU FLT_LOG2");
		AddLineQueue("flt_log2high EQU FLT_LOG2HIGH");
		AddLineQueue("flt_ln2 EQU FLT_LN2");
		AddLineQueue("flt_ln2high EQU FLT_LN2HIGH");
		AddLineQueue("flt_1divln2 EQU FLT_1DIVLN2");
		AddLineQueue("flt_2divln2 EQU FLT_2DIVLN2");
		AddLineQueue("flt_lnt EQU FLT_LNT");
		AddLineQueue("flt_lnthigh EQU FLT_LNTHIGH");
		AddLineQueue("flt_ln10 EQU FLT_LN10");
		AddLineQueue("flt_sqrt2 EQU FLT_SQRT2");
		AddLineQueue("flt_rcpsqrt2 EQU FLT_RCPSQRT2");
		AddLineQueue("flt_sqrt2div2 EQU FLT_SQRT2DIV2");
		AddLineQueue("flt_sqrt2div2high EQU FLT_SQRT2DIV2HIGH");
		AddLineQueue("flt_sqrt2div2low EQU FLT_SQRT2DIV2LOW");
		AddLineQueue("flt_sqrthalf EQU FLT_SQRTHALF");
		AddLineQueue("flt_sqrthalfhigh EQU FLT_SQRTHALFHIGH");
		AddLineQueue("flt_sqrthalflow EQU FLT_SQRTHALFLOW");
		AddLineQueue("flt_pow2 EQU FLT_POW2");
		AddLineQueue("flt_rcppow2 EQU FLT_RCPPOW2");
		AddLineQueue("flt_cbrt2 EQU FLT_CBRT2");
		AddLineQueue("flt_rcpcbrt2 EQU FLT_RCPCBRT2");
		AddLineQueue("flt_1div3 EQU FLT_1DIV3");
		AddLineQueue("flt_1div7 EQU FLT_1DIV7");
		AddLineQueue("flt_1div9 EQU FLT_1DIV9");
		AddLineQueue("flt_2div3 EQU FLT_2DIV3");
		AddLineQueue("flt_2div7 EQU FLT_2DIV7");
		AddLineQueue("flt_2div9 EQU FLT_2DIV9");
		AddLineQueue("flt_4div3 EQU FLT_4DIV3");
		AddLineQueue("flt_4div7 EQU FLT_4DIV7");
		AddLineQueue("flt_4div9 EQU FLT_4DIV9");

		AddLineQueue("flt_pi EQU FLT_PI");
		AddLineQueue("flt_pihigh EQU FLT_PIHIGH");
		AddLineQueue("flt_halfpi EQU FLT_HALFPI");
		AddLineQueue("flt_2pi EQU FLT_2PI");
		AddLineQueue("flt_negpi EQU FLT_NEGPI");
		AddLineQueue("flt_neghalfpi EQU FLT_NEGHALFPI");
		AddLineQueue("flt_neg2pi EQU FLT_NEG2PI");
		AddLineQueue("flt_rcppi EQU FLT_RCPPI");
		AddLineQueue("flt_invpi EQU FLT_INVPI");
		AddLineQueue("flt_rcp2pi EQU FLT_RCP2PI");
		AddLineQueue("flt_inv2pi EQU FLT_INV2PI");
		AddLineQueue("flt_pidiv2 EQU FLT_PIDIV2");
		AddLineQueue("flt_pidiv2high EQU FLT_PIDIV2HIGH");
		AddLineQueue("flt_pidiv4 EQU FLT_PIDIV4");
		AddLineQueue("flt_pidiv4high EQU FLT_PIDIV4HIGH");
		AddLineQueue("flt_pix3div4 EQU FLT_PIX3DIV4");
		AddLineQueue("flt_sqrtpi EQU FLT_SQRTPI");
		AddLineQueue("flt_sqrt2pi EQU FLT_SQRT2PI");
		AddLineQueue("flt_sqrt2pihigh EQU FLT_SQRT2PIHIGH");
		AddLineQueue("flt_rcpsqrtpi EQU FLT_RCPSQRTPI");
		AddLineQueue("flt_rcpsqrt2pi EQU FLT_RCPSQRT2PI");
		AddLineQueue("flt_sqrtpidiv2 EQU FLT_SQRTPIDIV2");
		AddLineQueue("flt_sqrtpidiv2high EQU FLT_SQRTPIDIV2HIGH");
		AddLineQueue("flt_sqrt2pidiv2 EQU FLT_SQRT2PIDIV2");
		AddLineQueue("flt_sqrt2pidiv2high EQU FLT_SQRT2PIDIV2HIGH");
		AddLineQueue("flt_2divpi EQU FLT_2DIVPI");
		AddLineQueue("flt_2div2pi EQU FLT_2DIV2PI");
		AddLineQueue("flt_2divsqrtpi EQU FLT_2DIVSQRTPI");
		AddLineQueue("flt_2divsqrt2pi EQU FLT_2DIVSQRT2PI");
		AddLineQueue("flt_sqrt2divpi EQU FLT_SQRT2DIVPI");
		AddLineQueue("flt_logpi EQU FLT_LOGPI");
		AddLineQueue("flt_log2pi EQU FLT_LOG2PI");
		AddLineQueue("flt_lnpi EQU FLT_LNPI");
		AddLineQueue("flt_ln2pi EQU FLT_LN2PI");
		AddLineQueue("flt_powpi EQU FLT_POWPI");
		AddLineQueue("flt_rcppowpi EQU FLT_RCPPOWPI");
		AddLineQueue("flt_pow2pi EQU FLT_POW2PI");
		AddLineQueue("flt_rcppow2pi EQU FLT_RCPPOW2PI");
		AddLineQueue("flt_cbrtpi EQU FLT_CBRTPI");
		AddLineQueue("flt_rcpcbrtpi EQU FLT_RCPCBRTPI");
		AddLineQueue("flt_cbrt2pi EQU FLT_CBRT2PI");
		AddLineQueue("flt_rcpcbrt2pi EQU FLT_RCPCBRT2PI");

		AddLineQueue("flt_pow2tom126 EQU FLT_POW2TOM126");
		AddLineQueue("flt_pow2to126 EQU FLT_POW2TO126");
		AddLineQueue("flt_normhuge EQU FLT_NORMHUGE");
		AddLineQueue("flt_pow2to23 EQU FLT_POW2TO23");
		AddLineQueue("flt_pow2to24 EQU FLT_POW2TO24");
		AddLineQueue("flt_maxi32pow2to23 EQU FLT_MAXI32POW2TO23");
		AddLineQueue("flt_pow2to31 EQU FLT_POW2TO31");
		AddLineQueue("flt_pow2to32 EQU FLT_POW2TO32");

		AddLineQueue("flt_remquobits EQU FLT_REMQUOBITS");
		AddLineQueue("flt_remquomask EQU FLT_REMQUOMASK");

		AddLineQueue("flt_trigploss EQU FLT_TRIGPLOSS");

		AddLineQueue("flt_degtorad EQU FLT_DEGTORAD");
		AddLineQueue("flt_radtodeg EQU FLT_RADTODEG");

		AddLineQueue("flt_degtograd EQU FLT_DEGTOGRAD");
		AddLineQueue("flt_gradtodeg EQU FLT_GRADTODEG");

		AddLineQueue("flt_radtograd EQU FLT_RADTOGRAD");
		AddLineQueue("flt_gradtorad EQU FLT_GRADTORAD");

		AddLineQueue("flt_sungravity EQU FLT_SUNGRAVITY");
		AddLineQueue("flt_jupitergravity EQU FLT_JUPITERGRAVITY");
		AddLineQueue("flt_neptunegravity EQU FLT_NEPTUNEGRAVITY");
		AddLineQueue("flt_saturngravity EQU FLT_SATURNGRAVITY");
		AddLineQueue("flt_uranusgravity EQU FLT_URANUSGRAVITY");
		AddLineQueue("flt_earthgravity EQU FLT_EARTHGRAVITY");
		AddLineQueue("flt_venusgravity EQU FLT_VENUSGRAVITY");
		AddLineQueue("flt_marsgravity EQU FLT_MARSGRAVITY");
		AddLineQueue("flt_mercurygravity EQU FLT_MERCURYGRAVITY");
		AddLineQueue("flt_moongravity EQU FLT_MOONGRAVITY");
		AddLineQueue("flt_plutogravity EQU FLT_PLUTOGRAVITY");

		AddLineQueue("flt_kmtoinch EQU FLT_KMTOINCH");
		AddLineQueue("flt_kmtofeet EQU FLT_KMTOFEET");
		AddLineQueue("flt_kmtoyards EQU FLT_KMTOYARDS");
		AddLineQueue("flt_kmtomiles EQU FLT_KMTOMILES");

		AddLineQueue("flt_metoinch EQU FLT_METOINCH");
		AddLineQueue("flt_metofeet EQU FLT_METOFEET");
		AddLineQueue("flt_metoyards EQU FLT_METOYARDS");
		AddLineQueue("flt_metomiles EQU FLT_METOMILES");

		AddLineQueue("flt_cmtoinch EQU FLT_CMTOINCH");
		AddLineQueue("flt_cmtofeet EQU FLT_CMTOFEET");
		AddLineQueue("flt_cmtoyards EQU FLT_CMTOYARDS");
		AddLineQueue("flt_cmtomiles EQU FLT_CMTOMILES");

		AddLineQueue("flt_milltoinch EQU FLT_MILLTOINCH");
		AddLineQueue("flt_milltofeet EQU FLT_MILLTOFEET");
		AddLineQueue("flt_milltoyards EQU FLT_MILLTOYARDS");
		AddLineQueue("flt_milltomiles EQU FLT_MILLTOMILES");

		AddLineQueue("flt_inchtomill EQU FLT_INCHTOMILL");
		AddLineQueue("flt_inchtocm EQU FLT_INCHTOCM");
		AddLineQueue("flt_inchtome EQU FLT_INCHTOME");
		AddLineQueue("flt_inchtokm EQU FLT_INCHTOKM");
		AddLineQueue("flt_inchtofeet EQU FLT_INCHTOFEET");
		AddLineQueue("flt_inchtoyards EQU FLT_INCHTOYARDS");
		AddLineQueue("flt_inchtomiles EQU FLT_INCHTOMILES");

		AddLineQueue("flt_feettomill EQU FLT_FEETTOMILL");
		AddLineQueue("flt_feettocm EQU FLT_FEETTOCM");
		AddLineQueue("flt_feettome EQU FLT_FEETTOME");
		AddLineQueue("flt_feettokm EQU FLT_FEETTOKM");
		AddLineQueue("flt_feettoinch EQU FLT_FEETTOINCH");
		AddLineQueue("flt_feettoyards EQU FLT_FEETTOYARDS");
		AddLineQueue("flt_feettomiles EQU FLT_FEETTOMILES");

		AddLineQueue("flt_yardstomill EQU FLT_YARDSTOMILL");
		AddLineQueue("flt_yardstocm EQU FLT_YARDSTOCM");
		AddLineQueue("flt_yardstome EQU FLT_YARDSTOME");
		AddLineQueue("flt_yardstokm EQU FLT_YARDSTOKM");
		AddLineQueue("flt_yardstoinch EQU FLT_YARDSTOINCH");
		AddLineQueue("flt_yardstofeet EQU FLT_YARDSTOFEET");
		AddLineQueue("flt_yardstomiles EQU FLT_YARDSTOMILES");

		AddLineQueue("flt_milestomill EQU FLT_MILESTOMILL");
		AddLineQueue("flt_milestocm EQU FLT_MILESTOCM");
		AddLineQueue("flt_milestome EQU FLT_MILESTOME");
		AddLineQueue("flt_milestokm EQU FLT_MILESTOKM");
		AddLineQueue("flt_milestoinch EQU FLT_MILESTOINCH");
		AddLineQueue("flt_milestofeet EQU FLT_MILESTOFEET");
		AddLineQueue("flt_milestoyards EQU FLT_MILESTOYARDS");

		AddLineQueue("flt_kmphtomeps EQU FLT_KMPHTOMEPS");
		AddLineQueue("flt_kmphtokmps EQU FLT_KMPHTOKMPS");
		AddLineQueue("flt_kmphtomepm EQU FLT_KMPHTOMEPM");
		AddLineQueue("flt_kmphtomilesph EQU FLT_KMPHTOMILESPH");
		AddLineQueue("flt_kmphtomilesps EQU FLT_KMPHTOMILESPS");
		AddLineQueue("flt_kmphtofootps EQU FLT_KMPHTOFOOTPS");
		AddLineQueue("flt_kmphtofootpm EQU FLT_KMPHTOFOOTPM");

		AddLineQueue("flt_kmpstomeps EQU FLT_KMPSTOMEPS");
		AddLineQueue("flt_kmpstokmph EQU FLT_KMPSTOKMPH");
		AddLineQueue("flt_kmpstomepm EQU FLT_KMPSTOMEPM");
		AddLineQueue("flt_kmpstomilesph EQU FLT_KMPSTOMILESPH");
		AddLineQueue("flt_kmpstomilesps EQU FLT_KMPSTOMILESPS");
		AddLineQueue("flt_kmpstofootps EQU FLT_KMPSTOFOOTPS");
		AddLineQueue("flt_kmpstofootpm EQU FLT_KMPSTOFOOTPM");

		AddLineQueue("flt_mepstokmph EQU FLT_MEPSTOKMPH");
		AddLineQueue("flt_mepstokmps EQU FLT_MEPSTOKMPS");
		AddLineQueue("flt_mepstomepm EQU FLT_MEPSTOMEPM");
		AddLineQueue("flt_mepstomilesph EQU FLT_MEPSTOMILESPH");
		AddLineQueue("flt_mepstomilesps EQU FLT_MEPSTOMILESPS");
		AddLineQueue("flt_mepstofootps EQU FLT_MEPSTOFOOTPS");
		AddLineQueue("flt_mepstofootpm EQU FLT_MEPSTOFOOTPM");

		AddLineQueue("flt_mepmtokmph EQU FLT_MEPMTOKMPH");
		AddLineQueue("flt_mepmtokmps EQU FLT_MEPMTOKMPS");
		AddLineQueue("flt_mepmtomeps EQU FLT_MEPMTOMEPS");
		AddLineQueue("flt_mepmtomilesph EQU FLT_MEPMTOMILESPH");
		AddLineQueue("flt_mepmtomilesps EQU FLT_MEPMTOMILESPS");
		AddLineQueue("flt_mepmtofootps EQU FLT_MEPMTOFOOTPS");
		AddLineQueue("flt_mepmtofootpm EQU FLT_MEPMTOFOOTPM");

		AddLineQueue("flt_milesphtokmph EQU FLT_MILESPHTOKMPH");
		AddLineQueue("flt_milesphtokmps EQU FLT_MILESPHTOKMPS");
		AddLineQueue("flt_milesphtomeps EQU FLT_MILESPHTOMEPS");
		AddLineQueue("flt_milesphtomepm EQU FLT_MILESPHTOMEPM");
		AddLineQueue("flt_milesphtomilesps EQU FLT_MILESPHTOMILESPS");
		AddLineQueue("flt_milesphtofootps EQU FLT_MILESPHTOFOOTPS");
		AddLineQueue("flt_milesphtofootpm EQU FLT_MILESPHTOFOOTPM");

		AddLineQueue("flt_milespstokmph EQU FLT_MILESPSTOKMPH");
		AddLineQueue("flt_milespstokmps EQU FLT_MILESPSTOKMPS");
		AddLineQueue("flt_milespstomeps EQU FLT_MILESPSTOMEPS");
		AddLineQueue("flt_milespstomepm EQU FLT_MILESPSTOMEPM");
		AddLineQueue("flt_milespstomilespm EQU FLT_MILESPSTOMILESPM");
		AddLineQueue("flt_milespstofootps EQU FLT_MILESPSTOFOOTPS");
		AddLineQueue("flt_milespstofootpm EQU FLT_MILESPSTOFOOTPM");

		AddLineQueue("flt_footpstokmph EQU FLT_FOOTPSTOKMPH");
		AddLineQueue("flt_footpstokmps EQU FLT_FOOTPSTOKMPS");
		AddLineQueue("flt_footpstomeps EQU FLT_FOOTPSTOMEPS");
		AddLineQueue("flt_footpstomepm EQU FLT_FOOTPSTOMEPM");
		AddLineQueue("flt_footpstomilesph EQU FLT_FOOTPSTOMILESPH");
		AddLineQueue("flt_footpstomilesps EQU FLT_FOOTPSTOMILESPS");
		AddLineQueue("flt_footpstofootpm EQU FLT_FOOTPSTOFOOTPM");

		AddLineQueue("flt_footpmtokmph EQU FLT_FOOTPMTOKMPH");
		AddLineQueue("flt_footpmtokmps EQU FLT_FOOTPMTOKMPS");
		AddLineQueue("flt_footpmtomeps EQU FLT_FOOTPMTOMEPS");
		AddLineQueue("flt_footpmtomepm EQU FLT_FOOTPMTOMEPM");
		AddLineQueue("flt_footpmtomilesph EQU FLT_FOOTPMTOMILESPH");
		AddLineQueue("flt_footpmtomilesps EQU FLT_FOOTPMTOMILESPS");
		AddLineQueue("flt_footpmtofootps EQU FLT_FOOTPMTOFOOTPS");

		AddLineQueue("flt_soundspeedp50c EQU FLT_SOUNDSPEEDP50C");
		AddLineQueue("flt_soundspeedp45c EQU FLT_SOUNDSPEEDP45C");
		AddLineQueue("flt_soundspeedp40c EQU FLT_SOUNDSPEEDP40C");
		AddLineQueue("flt_soundspeedp35c EQU FLT_SOUNDSPEEDP35C");
		AddLineQueue("flt_soundspeedp30c EQU FLT_SOUNDSPEEDP30C");
		AddLineQueue("flt_soundspeedp25c EQU FLT_SOUNDSPEEDP25C");
		AddLineQueue("flt_soundspeedp20c EQU FLT_SOUNDSPEEDP20C");
		AddLineQueue("flt_soundspeedp15c EQU FLT_SOUNDSPEEDP15C");
		AddLineQueue("flt_soundspeedp10c EQU FLT_SOUNDSPEEDP10C");
		AddLineQueue("flt_soundspeedp5c EQU FLT_SOUNDSPEEDP5C");
		AddLineQueue("flt_soundspeed0c EQU FLT_SOUNDSPEED0C");
		AddLineQueue("flt_soundspeedn5c EQU FLT_SOUNDSPEEDN5C");
		AddLineQueue("flt_soundspeedn10c EQU FLT_SOUNDSPEEDN10C");
		AddLineQueue("flt_soundspeedn15c EQU FLT_SOUNDSPEEDN15C");
		AddLineQueue("flt_soundspeedn20c EQU FLT_SOUNDSPEEDN20C");
		AddLineQueue("flt_soundspeedn25c EQU FLT_SOUNDSPEEDN25C");
		AddLineQueue("flt_soundspeedn30c EQU FLT_SOUNDSPEEDN30C");
		AddLineQueue("flt_soundspeedn35c EQU FLT_SOUNDSPEEDN35C");
		AddLineQueue("flt_soundspeedn40c EQU FLT_SOUNDSPEEDN40C");
		AddLineQueue("flt_soundspeedn45c EQU FLT_SOUNDSPEEDN45C");
		AddLineQueue("flt_soundspeedn50c EQU FLT_SOUNDSPEEDN50C");

		AddLineQueue("flt_schscale EQU FLT_SCHSCALE");
		AddLineQueue("flt_thscale EQU FLT_THSCALE");

		AddLineQueue("flt_expest1 EQU FLT_EXPEST1");
		AddLineQueue("flt_expest2 EQU FLT_EXPEST2");
		AddLineQueue("flt_expest3 EQU FLT_EXPEST3");
		AddLineQueue("flt_expest4 EQU FLT_EXPEST4");
		AddLineQueue("flt_expest5 EQU FLT_EXPEST5");
		AddLineQueue("flt_expest6 EQU FLT_EXPEST6");
		AddLineQueue("flt_expest7 EQU FLT_EXPEST7");
		AddLineQueue("flt_logest0 EQU FLT_LOGEST0");
		AddLineQueue("flt_logest1 EQU FLT_LOGEST1");
		AddLineQueue("flt_logest2 EQU FLT_LOGEST2");
		AddLineQueue("flt_logest3 EQU FLT_LOGEST3");
		AddLineQueue("flt_logest4 EQU FLT_LOGEST4");
		AddLineQueue("flt_logest5 EQU FLT_LOGEST5");
		AddLineQueue("flt_logest6 EQU FLT_LOGEST6");
		AddLineQueue("flt_logest7 EQU FLT_LOGEST7");

		/*double mask*/
		AddLineQueue("dbl_1lshl3_msk EQU DBL_1LSHL3_MSK");
		AddLineQueue("dbl_1lshl4_msk EQU DBL_1LSHL4_MSK");
		AddLineQueue("dbl_1lshl7_msk EQU DBL_1LSHL7_MSK");
		AddLineQueue("dbl_1lshl8_msk EQU DBL_1LSHL8_MSK");
		AddLineQueue("dbl_1lshl11_msk EQU DBL_1LSHL11_MSK");
		AddLineQueue("dbl_1lshl12_msk EQU DBL_1LSHL12_MSK");
		AddLineQueue("dbl_1lshl15_msk EQU DBL_1LSHL15_MSK");
		AddLineQueue("dbl_1lshl16_msk EQU DBL_1LSHL16_MSK");
		AddLineQueue("dbl_1lshl19_msk EQU DBL_1LSHL19_MSK");
		AddLineQueue("dbl_1lshl20_msk EQU DBL_1LSHL20_MSK");
		AddLineQueue("dbl_1lshl23_msk EQU DBL_1LSHL23_MSK");
		AddLineQueue("dbl_1lshl24_msk EQU DBL_1LSHL24_MSK");
		AddLineQueue("dbl_1lshl27_msk EQU DBL_1LSHL27_MSK");
		AddLineQueue("dbl_1lshl28_msk EQU DBL_1LSHL28_MSK");
		AddLineQueue("dbl_1lshl31_msk EQU DBL_1LSHL31_MSK");
		AddLineQueue("dbl_1lshl32_msk EQU DBL_1LSHL32_MSK");
		AddLineQueue("dbl_1lshl35_msk EQU DBL_1LSHL35_MSK");
		AddLineQueue("dbl_1lshl36_msk EQU DBL_1LSHL36_MSK");
		AddLineQueue("dbl_1lshl39_msk EQU DBL_1LSHL39_MSK");
		AddLineQueue("dbl_1lshl40_msk EQU DBL_1LSHL40_MSK");
		AddLineQueue("dbl_1lshl43_msk EQU DBL_1LSHL43_MSK");
		AddLineQueue("dbl_1lshl44_msk EQU DBL_1LSHL44_MSK");
		AddLineQueue("dbl_1lshl47_msk EQU DBL_1LSHL47_MSK");
		AddLineQueue("dbl_1lshl48_msk EQU DBL_1LSHL48_MSK");
		AddLineQueue("dbl_1lshl51_msk EQU DBL_1LSHL51_MSK");
		AddLineQueue("dbl_1lshl52_msk EQU DBL_1LSHL52_MSK");
		AddLineQueue("dbl_1lshl55_msk EQU DBL_1LSHL55_MSK");
		AddLineQueue("dbl_1lshl56_msk EQU DBL_1LSHL56_MSK");
		AddLineQueue("dbl_1lshl59_msk EQU DBL_1LSHL59_MSK");
		AddLineQueue("dbl_1lshl60_msk EQU DBL_1LSHL60_MSK");
		AddLineQueue("dbl_1lshl63_msk EQU DBL_1LSHL63_MSK");

		AddLineQueue("dbl_neg1lshl3_msk EQU DBL_NEG1LSHL3_MSK");
		AddLineQueue("dbl_neg1lshl4_msk EQU DBL_NEG1LSHL4_MSK");
		AddLineQueue("dbl_neg1lshl7_msk EQU DBL_NEG1LSHL7_MSK");
		AddLineQueue("dbl_neg1lshl8_msk EQU DBL_NEG1LSHL8_MSK");
		AddLineQueue("dbl_neg1lshl11_msk EQU DBL_NEG1LSHL11_MSK");
		AddLineQueue("dbl_neg1lshl12_msk EQU DBL_NEG1LSHL12_MSK");
		AddLineQueue("dbl_neg1lshl15_msk EQU DBL_NEG1LSHL15_MSK");
		AddLineQueue("dbl_neg1lshl16_msk EQU DBL_NEG1LSHL16_MSK");
		AddLineQueue("dbl_neg1lshl19_msk EQU DBL_NEG1LSHL19_MSK");
		AddLineQueue("dbl_neg1lshl20_msk EQU DBL_NEG1LSHL20_MSK");
		AddLineQueue("dbl_neg1lshl23_msk EQU DBL_NEG1LSHL23_MSK");
		AddLineQueue("dbl_neg1lshl24_msk EQU DBL_NEG1LSHL24_MSK");
		AddLineQueue("dbl_neg1lshl27_msk EQU DBL_NEG1LSHL27_MSK");
		AddLineQueue("dbl_neg1lshl28_msk EQU DBL_NEG1LSHL28_MSK");
		AddLineQueue("dbl_neg1lshl31_msk EQU DBL_NEG1LSHL31_MSK");
		AddLineQueue("dbl_neg1lshl32_msk EQU DBL_NEG1LSHL32_MSK");
		AddLineQueue("dbl_neg1lshl35_msk EQU DBL_NEG1LSHL35_MSK");
		AddLineQueue("dbl_neg1lshl36_msk EQU DBL_NEG1LSHL36_MSK");
		AddLineQueue("dbl_neg1lshl39_msk EQU DBL_NEG1LSHL39_MSK");
		AddLineQueue("dbl_neg1lshl40_msk EQU DBL_NEG1LSHL40_MSK");
		AddLineQueue("dbl_neg1lshl43_msk EQU DBL_NEG1LSHL43_MSK");
		AddLineQueue("dbl_neg1lshl44_msk EQU DBL_NEG1LSHL44_MSK");
		AddLineQueue("dbl_neg1lshl47_msk EQU DBL_NEG1LSHL47_MSK");
		AddLineQueue("dbl_neg1lshl48_msk EQU DBL_NEG1LSHL48_MSK");
		AddLineQueue("dbl_neg1lshl51_msk EQU DBL_NEG1LSHL51_MSK");
		AddLineQueue("dbl_neg1lshl52_msk EQU DBL_NEG1LSHL52_MSK");
		AddLineQueue("dbl_neg1lshl55_msk EQU DBL_NEG1LSHL55_MSK");
		AddLineQueue("dbl_neg1lshl56_msk EQU DBL_NEG1LSHL56_MSK");
		AddLineQueue("dbl_neg1lshl59_msk EQU DBL_NEG1LSHL59_MSK");
		AddLineQueue("dbl_neg1lshl60_msk EQU DBL_NEG1LSHL60_MSK");
		AddLineQueue("dbl_neg1lshl63_msk EQU DBL_NEG1LSHL63_MSK");

		AddLineQueue("dbl_false_msk EQU DBL_FALSE_MSK");
		AddLineQueue("dbl_true_msk EQU DBL_TRUE_MSK");
		AddLineQueue("dbl_error_msk EQU DBL_ERROR_MSK");

		AddLineQueue("dbl_magic_msk EQU DBL_MAGIC_MSK");
		AddLineQueue("dbl_sign_msk EQU DBL_SIGN_MSK");
		AddLineQueue("dbl_invsign_msk EQU DBL_INVSIGN_MSK");

		AddLineQueue("dbl_inf_msk EQU DBL_INF_MSK");
		AddLineQueue("dbl_fin_msk EQU DBL_FIN_MSK");
		AddLineQueue("dbl_invinf_msk EQU DBL_INVINF_MSK");
		AddLineQueue("dbl_neginf_msk EQU DBL_NEGINF_MSK");
		AddLineQueue("dbl_nan_msk EQU DBL_NAN_MSK");
		AddLineQueue("dbl_qnan_msk EQU DBL_QNAN_MSK");
		AddLineQueue("dbl_negqnan_msk EQU DBL_NEGQNAN_MSK");
		AddLineQueue("dbl_nantest_msk EQU DBL_NANTEST_MSK");
		AddLineQueue("dbl_abs_msk EQU DBL_ABS_MSK");
		AddLineQueue("dbl_min_msk EQU DBL_MIN_MSK");
		AddLineQueue("dbl_max_msk EQU DBL_MAX_MSK");
		AddLineQueue("dbl_nofraction_msk EQU DBL_NOFRACTION_MSK");
		AddLineQueue("dbl_mindenorm_msk EQU DBL_MINDENORM_MSK");
		AddLineQueue("dbl_denormlimit_msk EQU DBL_DENORMLIMIT_MSK");
		AddLineQueue("dbl_minnormal_msk EQU DBL_MINNORMAL_MSK");
		AddLineQueue("dbl_maxnormal_msk EQU DBL_MAXNORMAL_MSK");

		AddLineQueue("dbl_decdig_msk EQU DBL_DECDIG_MSK");
		AddLineQueue("dbl_dig_msk EQU DBL_DIG_MSK");
		AddLineQueue("dbl_negdecdig_msk EQU DBL_NEGDECDIG_MSK");
		AddLineQueue("dbl_negdig_msk EQU DBL_NEGDIG_MSK");
		AddLineQueue("dbl_eps_msk EQU DBL_EPS_MSK");
		AddLineQueue("dbl_epsilon_msk EQU DBL_EPSILON_MSK");
		AddLineQueue("dbl_normeps_msk EQU DBL_NORMEPS_MSK");
		AddLineQueue("dbl_guard_msk EQU DBL_GUARD_MSK");
		AddLineQueue("dbl_mantpow2_msk EQU DBL_MANTPOW2_MSK");
		AddLineQueue("dbl_maxmantpow2_msk EQU DBL_MAXMANTPOW2_MSK");
		AddLineQueue("dbl_mantdig_msk EQU DBL_MANTDIG_MSK");
		AddLineQueue("dbl_mant_msk EQU DBL_MANT_MSK");
		AddLineQueue("dbl_negmantdig_msk EQU DBL_NEGMANTDIG_MSK");
		AddLineQueue("dbl_negmant_msk EQU DBL_NEGMANT_MSK");
		AddLineQueue("dbl_maxexp_msk EQU DBL_MAXEXP_MSK");
		AddLineQueue("dbl_expsign_msk EQU DBL_EXPSIGN_MSK");
		AddLineQueue("dbl_exp_msk EQU DBL_EXP_MSK");
		AddLineQueue("dbl_negmaxexp_msk EQU DBL_NEGMAXEXP_MSK");
		AddLineQueue("dbl_negexpsign_msk EQU DBL_NEGEXPSIGN_MSK");
		AddLineQueue("dbl_negexp_msk EQU DBL_NEGEXP_MSK");
		AddLineQueue("dbl_subnormalexp_msk EQU DBL_SUBNORMALEXP_MSK");
		AddLineQueue("dbl_minexp_msk EQU DBL_MINEXP_MSK");
		AddLineQueue("dbl_maxdecexp_msk EQU DBL_MAXDECEXP_MSK");
		AddLineQueue("dbl_negmaxdecexp_msk EQU DBL_NEGMAXDECEXP_MSK");
		AddLineQueue("dbl_mindecexp_msk EQU DBL_MINDECEXP_MSK");
		AddLineQueue("dbl_expfield_msk EQU DBL_EXPFIELD_MSK");
		AddLineQueue("dbl_mantfield_msk EQU DBL_MANTFIELD_MSK");
		AddLineQueue("dbl_norm_msk EQU DBL_NORM_MSK");
		AddLineQueue("dbl_radix_msk EQU DBL_RADIX_MSK");
		AddLineQueue("dbl_rounds_msk EQU DBL_ROUNDS_MSK");
		AddLineQueue("dbl_subdec_msk EQU DBL_SUBDEC_MSK");
		AddLineQueue("dbl_sqrtmax_msk EQU DBL_SQRTMAX_MSK");
		AddLineQueue("dbl_smallnormal_msk EQU DBL_SMALLNORMAL_MSK");

		AddLineQueue("dbl_halfminuseps_msk EQU DBL_HALFMINUSEPS_MSK");
		AddLineQueue("dbl_trueint_msk EQU DBL_TRUEINT_MSK");

		AddLineQueue("dbl_byte_msk EQU DBL_BYTE_MSK");
		AddLineQueue("DBL_byte_even_msk EQU DBL_BYTE_EVEN_MSK");
		AddLineQueue("DBL_byte_odd_msk EQU DBL_BYTE_ODD_MSK");
		AddLineQueue("dbl_4low_msk EQU DBL_4LOW_MSK");
		AddLineQueue("dbl_4high_msk EQU DBL_4HIGH_MSK");
		AddLineQueue("dbl_flip4_msk EQU DBL_FLIP4_MSK");
		AddLineQueue("dbl_8low_msk EQU DBL_8LOW_MSK");
		AddLineQueue("dbl_8high_msk EQU DBL_8HIGH_MSK");
		AddLineQueue("dbl_flip8_msk EQU DBL_FLIP8_MSK");
		AddLineQueue("dbl_16low_msk EQU DBL_16LOW_MSK");
		AddLineQueue("dbl_16high_msk EQU DBL_16HIGH_MSK");
		AddLineQueue("dbl_flip16_msk EQU DBL_FLIP16_MSK");
		AddLineQueue("dbl_24low_msk EQU DBL_24LOW_MSK");
		AddLineQueue("dbl_24high_msk EQU DBL_24HIGH_MSK");
		AddLineQueue("dbl_flip24_msk EQU DBL_FLIP24_MSK");
		AddLineQueue("dbl_28low_msk EQU DBL_28LOW_MSK");
		AddLineQueue("dbl_28high_msk EQU DBL_28HIGH_MSK");
		AddLineQueue("dbl_flip28_msk EQU DBL_FLIP28_MSK");
		AddLineQueue("dbl_32low_msk EQU DBL_32LOW_MSK");
		AddLineQueue("dbl_32high_msk EQU DBL_32HIGH_MSK");
		AddLineQueue("dbl_flip32_msk EQU DBL_FLIP32_MSK");
		AddLineQueue("dbl_40low_msk EQU DBL_40LOW_MSK");
		AddLineQueue("dbl_40high_msk EQU DBL_40HIGH_MSK");
		AddLineQueue("dbl_flip40_msk EQU DBL_FLIP40_MSK");
		AddLineQueue("dbl_48low_msk EQU DBL_48LOW_MSK");
		AddLineQueue("dbl_48high_msk EQU DBL_48HIGH_MSK");
		AddLineQueue("dbl_flip48_msk EQU DBL_FLIP48_MSK");
		AddLineQueue("dbl_56low_msk EQU DBL_56LOW_MSK");
		AddLineQueue("dbl_56high_msk EQU DBL_56HIGH_MSK");
		AddLineQueue("dbl_flip56_msk EQU DBL_FLIP56_MSK");
		AddLineQueue("dbl_60low_msk EQU DBL_60LOW_MSK");
		AddLineQueue("dbl_60high_msk EQU DBL_60HIGH_MSK");
		AddLineQueue("dbl_flip60_msk EQU DBL_FLIP60_MSK");
		AddLineQueue("dbl_64low_msk EQU DBL_64LOW_MSK");
		AddLineQueue("dbl_64high_msk EQU DBL_64HIGH_MSK");
		AddLineQueue("dbl_flip64_msk EQU DBL_FLIP64_MSK");

		AddLineQueue("dbl_0_msk EQU DBL_0_MSK");
		AddLineQueue("dbl_0d5_msk EQU DBL_0D5_MSK");
		AddLineQueue("dbl_1_msk EQU DBL_1_MSK");
		AddLineQueue("dbl_1d5_msk EQU DBL_1D5_MSK");
		AddLineQueue("dbl_2_msk EQU DBL_2_MSK");
		AddLineQueue("dbl_2d5_msk EQU DBL_2D5_MSK");
		AddLineQueue("dbl_3_msk EQU DBL_3_MSK");
		AddLineQueue("dbl_4_msk EQU DBL_4_MSK");
		AddLineQueue("dbl_5_msk EQU DBL_5_MSK");
		AddLineQueue("dbl_6_msk EQU DBL_6_MSK");
		AddLineQueue("dbl_7_msk EQU DBL_7_MSK");
		AddLineQueue("dbl_8_msk EQU DBL_8_MSK");
		AddLineQueue("dbl_9_msk EQU DBL_9_MSK");
		AddLineQueue("dbl_10_msk EQU DBL_10_MSK");
		AddLineQueue("dbl_20_msk EQU DBL_20_MSK");
		AddLineQueue("dbl_23_msk EQU DBL_23_MSK");
		AddLineQueue("dbl_23d5_msk EQU DBL_23D5_MSK");
		AddLineQueue("dbl_24_msk EQU DBL_24_MSK");
		AddLineQueue("dbl_24d5_msk EQU DBL_24D5_MSK");
		AddLineQueue("dbl_25_msk EQU DBL_25_MSK");

		AddLineQueue("dbl_128_msk EQU DBL_128_MSK");

		AddLineQueue("dbl_253_msk EQU DBL_253_MSK");

		AddLineQueue("dbl_neg0_msk EQU DBL_NEG0_MSK");
		AddLineQueue("dbl_neg1_msk EQU DBL_NEG1_MSK");

		AddLineQueue("dbl_neg150_msk EQU DBL_NEG150_MSK");

		AddLineQueue("dbl_bin128_msk EQU DBL_BIN128_MSK");
		AddLineQueue("dbl_binneg150_msk EQU DBL_BINNEG150_MSK");

		AddLineQueue("dbl_maxrand_msk EQU DBL_MAXRAND_MSK");

		AddLineQueue("dbl_maxi8_msk EQU DBL_MAXI8_MSK");
		AddLineQueue("dbl_mini8_msk EQU DBL_MINI8_MSK");
		AddLineQueue("dbl_maxu8_msk EQU DBL_MAXU8_MSK");

		AddLineQueue("dbl_maxi16_msk EQU DBL_MAXI16_MSK");
		AddLineQueue("dbl_mini16_msk EQU DBL_MINI16_MSK");
		AddLineQueue("dbl_maxu16_msk EQU DBL_MAXU16_MSK");

		AddLineQueue("dbl_maxi32_msk EQU DBL_MAXI32_MSK");
		AddLineQueue("dbl_mini32_msk EQU DBL_MINI32_MSK");
		AddLineQueue("dbl_maxu32_msk EQU DBL_MAXU32_MSK");

		AddLineQueue("dbl_maxi64_msk EQU DBL_MAXI64_MSK");
		AddLineQueue("dbl_mini64_msk EQU DBL_MINI64_MSK");
		AddLineQueue("dbl_maxu64_msk EQU DBL_MAXU64_MSK");

		AddLineQueue("dbl_maxi8xu8_msk EQU DBL_MAXI8XU8_MSK");
		AddLineQueue("dbl_mini8xu8_msk EQU DBL_MINI8XU8_MSK");
		AddLineQueue("dbl_maxi8xu16_msk EQU DBL_MAXI8XU16_MSK");
		AddLineQueue("dbl_mini8xu16_msk EQU DBL_MINI8XU16_MSK");

		AddLineQueue("dbl_maxi16xu16_msk EQU DBL_MAXI16XU16_MSK");
		AddLineQueue("dbl_mini16xu16_msk EQU DBL_MINI16XU16_MSK");
		AddLineQueue("dbl_maxi16xu32_msk EQU DBL_MAXI16XU32_MSK");
		AddLineQueue("dbl_mini16xu32_msk EQU DBL_MINI16XU32_MSK");

		AddLineQueue("dbl_maxi32xu32_msk EQU DBL_MAXI32XU32_MSK");
		AddLineQueue("dbl_mini32xu32_msk EQU DBL_MINI32XU32_MSK");

		AddLineQueue("dbl_fixunsigned_msk EQU DBL_FIXUNSIGNED_MSK");
		AddLineQueue("dbl_fixunsigned32_msk EQU DBL_FIXUNSIGNED32_MSK");
		AddLineQueue("dbl_fixmaxi32_msk EQU DBL_FIXMAXI32_MSK");
		AddLineQueue("dbl_fixmaxu32_msk EQU DBL_FIXMAXU32_MSK");

		AddLineQueue("dbl_fixunsigned64_msk EQU DBL_FIXUNSIGNED64_MSK");
		AddLineQueue("dbl_fixmaxi64_msk EQU DBL_FIXMAXI64_MSK");
		AddLineQueue("dbl_fixmaxu64_msk EQU DBL_FIXMAXU64_MSK");

		/*double int*/
		AddLineQueue("dbl_1lshl3_int EQU DBL_1LSHL3_INT");
		AddLineQueue("dbl_1lshl4_int EQU DBL_1LSHL4_INT");
		AddLineQueue("dbl_1lshl7_int EQU DBL_1LSHL7_INT");
		AddLineQueue("dbl_1lshl8_int EQU DBL_1LSHL8_INT");
		AddLineQueue("dbl_1lshl11_int EQU DBL_1LSHL11_INT");
		AddLineQueue("dbl_1lshl12_int EQU DBL_1LSHL12_INT");
		AddLineQueue("dbl_1lshl15_int EQU DBL_1LSHL15_INT");
		AddLineQueue("dbl_1lshl16_int EQU DBL_1LSHL16_INT");
		AddLineQueue("dbl_1lshl19_int EQU DBL_1LSHL19_INT");
		AddLineQueue("dbl_1lshl20_int EQU DBL_1LSHL20_INT");
		AddLineQueue("dbl_1lshl23_int EQU DBL_1LSHL23_INT");
		AddLineQueue("dbl_1lshl24_int EQU DBL_1LSHL24_INT");
		AddLineQueue("dbl_1lshl27_int EQU DBL_1LSHL27_INT");
		AddLineQueue("dbl_1lshl28_int EQU DBL_1LSHL28_INT");
		AddLineQueue("dbl_1lshl31_int EQU DBL_1LSHL31_INT");
		AddLineQueue("dbl_1lshl32_int EQU DBL_1LSHL32_INT");
		AddLineQueue("dbl_1lshl35_int EQU DBL_1LSHL35_INT");
		AddLineQueue("dbl_1lshl36_int EQU DBL_1LSHL36_INT");
		AddLineQueue("dbl_1lshl39_int EQU DBL_1LSHL39_INT");
		AddLineQueue("dbl_1lshl40_int EQU DBL_1LSHL40_INT");
		AddLineQueue("dbl_1lshl43_int EQU DBL_1LSHL43_INT");
		AddLineQueue("dbl_1lshl44_int EQU DBL_1LSHL44_INT");
		AddLineQueue("dbl_1lshl47_int EQU DBL_1LSHL47_INT");
		AddLineQueue("dbl_1lshl48_int EQU DBL_1LSHL48_INT");
		AddLineQueue("dbl_1lshl51_int EQU DBL_1LSHL51_INT");
		AddLineQueue("dbl_1lshl52_int EQU DBL_1LSHL52_INT");
		AddLineQueue("dbl_1lshl55_int EQU DBL_1LSHL55_INT");
		AddLineQueue("dbl_1lshl56_int EQU DBL_1LSHL56_INT");
		AddLineQueue("dbl_1lshl59_int EQU DBL_1LSHL59_INT");
		AddLineQueue("dbl_1lshl60_int EQU DBL_1LSHL60_INT");
		AddLineQueue("dbl_1lshl63_int EQU DBL_1LSHL63_INT");

		AddLineQueue("dbl_neg1lshl3_int EQU DBL_NEG1LSHL3_INT");
		AddLineQueue("dbl_neg1lshl4_int EQU DBL_NEG1LSHL4_INT");
		AddLineQueue("dbl_neg1lshl7_int EQU DBL_NEG1LSHL7_INT");
		AddLineQueue("dbl_neg1lshl8_int EQU DBL_NEG1LSHL8_INT");
		AddLineQueue("dbl_neg1lshl11_int EQU DBL_NEG1LSHL11_INT");
		AddLineQueue("dbl_neg1lshl12_int EQU DBL_NEG1LSHL12_INT");
		AddLineQueue("dbl_neg1lshl15_int EQU DBL_NEG1LSHL15_INT");
		AddLineQueue("dbl_neg1lshl16_int EQU DBL_NEG1LSHL16_INT");
		AddLineQueue("dbl_neg1lshl19_int EQU DBL_NEG1LSHL19_INT");
		AddLineQueue("dbl_neg1lshl20_int EQU DBL_NEG1LSHL20_INT");
		AddLineQueue("dbl_neg1lshl23_int EQU DBL_NEG1LSHL23_INT");
		AddLineQueue("dbl_neg1lshl24_int EQU DBL_NEG1LSHL24_INT");
		AddLineQueue("dbl_neg1lshl27_int EQU DBL_NEG1LSHL27_INT");
		AddLineQueue("dbl_neg1lshl28_int EQU DBL_NEG1LSHL28_INT");
		AddLineQueue("dbl_neg1lshl31_int EQU DBL_NEG1LSHL31_INT");
		AddLineQueue("dbl_neg1lshl32_int EQU DBL_NEG1LSHL32_INT");
		AddLineQueue("dbl_neg1lshl35_int EQU DBL_NEG1LSHL35_INT");
		AddLineQueue("dbl_neg1lshl36_int EQU DBL_NEG1LSHL36_INT");
		AddLineQueue("dbl_neg1lshl39_int EQU DBL_NEG1LSHL39_INT");
		AddLineQueue("dbl_neg1lshl40_int EQU DBL_NEG1LSHL40_INT");
		AddLineQueue("dbl_neg1lshl43_int EQU DBL_NEG1LSHL43_INT");
		AddLineQueue("dbl_neg1lshl44_int EQU DBL_NEG1LSHL44_INT");
		AddLineQueue("dbl_neg1lshl47_int EQU DBL_NEG1LSHL47_INT");
		AddLineQueue("dbl_neg1lshl48_int EQU DBL_NEG1LSHL48_INT");
		AddLineQueue("dbl_neg1lshl51_int EQU DBL_NEG1LSHL51_INT");
		AddLineQueue("dbl_neg1lshl52_int EQU DBL_NEG1LSHL52_INT");
		AddLineQueue("dbl_neg1lshl55_int EQU DBL_NEG1LSHL55_INT");
		AddLineQueue("dbl_neg1lshl56_int EQU DBL_NEG1LSHL56_INT");
		AddLineQueue("dbl_neg1lshl59_int EQU DBL_NEG1LSHL59_INT");
		AddLineQueue("dbl_neg1lshl60_int EQU DBL_NEG1LSHL60_INT");
		AddLineQueue("dbl_neg1lshl63_int EQU DBL_NEG1LSHL63_INT");

		AddLineQueue("dbl_false_int EQU DBL_FALSE_INT");
		AddLineQueue("dbl_true_int EQU DBL_TRUE_INT");
		AddLineQueue("dbl_error_int EQU DBL_ERROR_INT");

		AddLineQueue("dbl_magic_int EQU DBL_MAGIC_INT");
		AddLineQueue("dbl_sign_int EQU DBL_SIGN_INT");
		AddLineQueue("dbl_invsign_int EQU DBL_INVSIGN_INT");

		AddLineQueue("dbl_inf_int EQU DBL_INF_INT");
		AddLineQueue("dbl_fin_int EQU DBL_FIN_INT");
		AddLineQueue("dbl_invinf_int EQU DBL_INVINF_INT");
		AddLineQueue("dbl_neginf_int EQU DBL_NEGINF_INT");
		AddLineQueue("dbl_nan_int EQU DBL_NAN_INT");
		AddLineQueue("dbl_qnan_int EQU DBL_QNAN_INT");
		AddLineQueue("dbl_negqnan_int EQU DBL_NEGQNAN_INT");
		AddLineQueue("dbl_nantest_int EQU DBL_NANTEST_INT");
		AddLineQueue("dbl_abs_int EQU DBL_ABS_INT");
		AddLineQueue("dbl_min_int EQU DBL_MIN_INT");
		AddLineQueue("dbl_max_int EQU DBL_MAX_INT");
		AddLineQueue("dbl_nofraction_int EQU DBL_NOFRACTION_INT");
		AddLineQueue("dbl_mindenorm_int EQU DBL_MINDENORM_INT");
		AddLineQueue("dbl_denormlimit_int EQU DBL_DENORMLIMIT_INT");
		AddLineQueue("dbl_minnormal_int EQU DBL_MINNORMAL_INT");
		AddLineQueue("dbl_maxnormal_int EQU DBL_MAXNORMAL_INT");

		AddLineQueue("dbl_decdig_int EQU DBL_DECDIG_INT");
		AddLineQueue("dbl_dig_int EQU DBL_DIG_INT");
		AddLineQueue("dbl_negdecdig_int EQU DBL_NEGDECDIG_INT");
		AddLineQueue("dbl_negdig_int EQU DBL_NEGDIG_INT");
		AddLineQueue("dbl_eps_int EQU DBL_EPS_INT");
		AddLineQueue("dbl_epsilon_int EQU DBL_EPSILON_INT");
		AddLineQueue("dbl_normeps_int EQU DBL_NORMEPS_INT");
		AddLineQueue("dbl_guard_int EQU DBL_GUARD_INT");
		AddLineQueue("dbl_mantpow2_int EQU DBL_MANTPOW2_INT");
		AddLineQueue("dbl_maxmantpow2_int EQU DBL_MAXMANTPOW2_INT");
		AddLineQueue("dbl_mantdig_int EQU DBL_MANTDIG_INT");
		AddLineQueue("dbl_mant_int EQU DBL_MANT_INT");
		AddLineQueue("dbl_negmantdig_int EQU DBL_NEGMANTDIG_INT");
		AddLineQueue("dbl_negmant_int EQU DBL_NEGMANT_INT");
		AddLineQueue("dbl_maxexp_int EQU DBL_MAXEXP_INT");
		AddLineQueue("dbl_expsign_int EQU DBL_EXPSIGN_INT");
		AddLineQueue("dbl_exp_int EQU DBL_EXP_INT");
		AddLineQueue("dbl_negmaxexp_int EQU DBL_NEGMAXEXP_INT");
		AddLineQueue("dbl_negexpsign_int EQU DBL_NEGEXPSIGN_INT");
		AddLineQueue("dbl_negexp_int EQU DBL_NEGEXP_INT");
		AddLineQueue("dbl_subnormalexp_int EQU DBL_SUBNORMALEXP_INT");
		AddLineQueue("dbl_minexp_int EQU DBL_MINEXP_INT");
		AddLineQueue("dbl_maxdecexp_int EQU DBL_MAXDECEXP_INT");
		AddLineQueue("dbl_negmaxdecexp_int EQU DBL_NEGMAXDECEXP_INT");
		AddLineQueue("dbl_mindecexp_int EQU DBL_MINDECEXP_INT");
		AddLineQueue("dbl_expfield_int EQU DBL_EXPFIELD_INT");
		AddLineQueue("dbl_mantfield_int EQU DBL_MANTFIELD_INT");
		AddLineQueue("dbl_norm_int EQU DBL_NORM_INT");
		AddLineQueue("dbl_radix_int EQU DBL_RADIX_INT");
		AddLineQueue("dbl_rounds_int EQU DBL_ROUNDS_INT");
		AddLineQueue("dbl_subdec_int EQU DBL_SUBDEC_INT");
		AddLineQueue("dbl_sqrtmax_int EQU DBL_SQRTMAX_INT");
		AddLineQueue("dbl_smallnormal_int EQU DBL_SMALLNORMAL_INT");

		AddLineQueue("dbl_halfminuseps_int EQU DBL_HALFMINUSEPS_INT");
		AddLineQueue("dbl_trueint_int EQU DBL_TRUEINT_INT");

		AddLineQueue("dbl_byte_int EQU DBL_BYTE_INT");
		AddLineQueue("DBL_byte_even_int EQU DBL_BYTE_EVEN_INT");
		AddLineQueue("DBL_byte_odd_int EQU DBL_BYTE_ODD_INT");
		AddLineQueue("dbl_4low_int EQU DBL_4LOW_INT");
		AddLineQueue("dbl_4high_int EQU DBL_4HIGH_INT");
		AddLineQueue("dbl_flip4_int EQU DBL_FLIP4_INT");
		AddLineQueue("dbl_8low_int EQU DBL_8LOW_INT");
		AddLineQueue("dbl_8high_int EQU DBL_8HIGH_INT");
		AddLineQueue("dbl_flip8_int EQU DBL_FLIP8_INT");
		AddLineQueue("dbl_16low_int EQU DBL_16LOW_INT");
		AddLineQueue("dbl_16high_int EQU DBL_16HIGH_INT");
		AddLineQueue("dbl_flip16_int EQU DBL_FLIP16_INT");
		AddLineQueue("dbl_24low_int EQU DBL_24LOW_INT");
		AddLineQueue("dbl_24high_int EQU DBL_24HIGH_INT");
		AddLineQueue("dbl_flip24_int EQU DBL_FLIP24_INT");
		AddLineQueue("dbl_28low_int EQU DBL_28LOW_INT");
		AddLineQueue("dbl_28high_int EQU DBL_28HIGH_INT");
		AddLineQueue("dbl_flip28_int EQU DBL_FLIP28_INT");
		AddLineQueue("dbl_32low_int EQU DBL_32LOW_INT");
		AddLineQueue("dbl_32high_int EQU DBL_32HIGH_INT");
		AddLineQueue("dbl_flip32_int EQU DBL_FLIP32_INT");
		AddLineQueue("dbl_40low_int EQU DBL_40LOW_INT");
		AddLineQueue("dbl_40high_int EQU DBL_40HIGH_INT");
		AddLineQueue("dbl_flip40_int EQU DBL_FLIP40_INT");
		AddLineQueue("dbl_48low_int EQU DBL_48LOW_INT");
		AddLineQueue("dbl_48high_int EQU DBL_48HIGH_INT");
		AddLineQueue("dbl_flip48_int EQU DBL_FLIP48_INT");
		AddLineQueue("dbl_56low_int EQU DBL_56LOW_INT");
		AddLineQueue("dbl_56high_int EQU DBL_56HIGH_INT");
		AddLineQueue("dbl_flip56_int EQU DBL_FLIP56_INT");
		AddLineQueue("dbl_60low_int EQU DBL_60LOW_INT");
		AddLineQueue("dbl_60high_int EQU DBL_60HIGH_INT");
		AddLineQueue("dbl_flip60_int EQU DBL_FLIP60_INT");
		AddLineQueue("dbl_64low_int EQU DBL_64LOW_INT");
		AddLineQueue("dbl_64high_int EQU DBL_64HIGH_INT");
		AddLineQueue("dbl_flip64_int EQU DBL_FLIP64_INT");

		AddLineQueue("dbl_0_int EQU DBL_0_INT");
		AddLineQueue("dbl_0d5_int EQU DBL_0D5_INT");
		AddLineQueue("dbl_1_int EQU DBL_1_INT");
		AddLineQueue("dbl_1d5_int EQU DBL_1D5_INT");
		AddLineQueue("dbl_2_int EQU DBL_2_INT");
		AddLineQueue("dbl_2d5_int EQU DBL_2D5_INT");
		AddLineQueue("dbl_3_int EQU DBL_3_INT");
		AddLineQueue("dbl_4_int EQU DBL_4_INT");
		AddLineQueue("dbl_5_int EQU DBL_5_INT");
		AddLineQueue("dbl_6_int EQU DBL_6_INT");
		AddLineQueue("dbl_7_int EQU DBL_7_INT");
		AddLineQueue("dbl_8_int EQU DBL_8_INT");
		AddLineQueue("dbl_9_int EQU DBL_9_INT");
		AddLineQueue("dbl_10_int EQU DBL_10_INT");
		AddLineQueue("dbl_20_int EQU DBL_20_INT");
		AddLineQueue("dbl_23_int EQU DBL_23_INT");
		AddLineQueue("dbl_23d5_int EQU DBL_23D5_INT");
		AddLineQueue("dbl_24_int EQU DBL_24_INT");
		AddLineQueue("dbl_24d5_int EQU DBL_24D5_INT");
		AddLineQueue("dbl_25_int EQU DBL_25_INT");

		AddLineQueue("dbl_128_int EQU DBL_128_INT");

		AddLineQueue("dbl_253_int EQU DBL_253_INT");

		AddLineQueue("dbl_neg0_int EQU DBL_NEG0_INT");
		AddLineQueue("dbl_neg1_int EQU DBL_NEG1_INT");

		AddLineQueue("dbl_neg150_int EQU DBL_NEG150_INT");

		AddLineQueue("dbl_bin128_int EQU DBL_BIN128_INT");
		AddLineQueue("dbl_binneg150_int EQU DBL_BINNEG150_INT");

		AddLineQueue("dbl_maxrand_int EQU DBL_MAXRAND_INT");

		AddLineQueue("dbl_maxi8_int EQU DBL_MAXI8_INT");
		AddLineQueue("dbl_mini8_int EQU DBL_MINI8_INT");
		AddLineQueue("dbl_maxu8_int EQU DBL_MAXU8_INT");

		AddLineQueue("dbl_maxi16_int EQU DBL_MAXI16_INT");
		AddLineQueue("dbl_mini16_int EQU DBL_MINI16_INT");
		AddLineQueue("dbl_maxu16_int EQU DBL_MAXU16_INT");

		AddLineQueue("dbl_maxi32_int EQU DBL_MAXI32_INT");
		AddLineQueue("dbl_mini32_int EQU DBL_MINI32_INT");
		AddLineQueue("dbl_maxu32_int EQU DBL_MAXU32_INT");

		AddLineQueue("dbl_maxi64_int EQU DBL_MAXI64_INT");
		AddLineQueue("dbl_mini64_int EQU DBL_MINI64_INT");
		AddLineQueue("dbl_maxu64_int EQU DBL_MAXU64_INT");

		AddLineQueue("dbl_maxi8xu8_int EQU DBL_MAXI8XU8_INT");
		AddLineQueue("dbl_mini8xu8_int EQU DBL_MINI8XU8_INT");
		AddLineQueue("dbl_maxi8xu16_int EQU DBL_MAXI8XU16_INT");
		AddLineQueue("dbl_mini8xu16_int EQU DBL_MINI8XU16_INT");

		AddLineQueue("dbl_maxi16xu16_int EQU DBL_MAXI16XU16_INT");
		AddLineQueue("dbl_mini16xu16_int EQU DBL_MINI16XU16_INT");
		AddLineQueue("dbl_maxi16xu32_int EQU DBL_MAXI16XU32_INT");
		AddLineQueue("dbl_mini16xu32_int EQU DBL_MINI16XU32_INT");

		AddLineQueue("dbl_maxi32xu32_int EQU DBL_MAXI32XU32_INT");
		AddLineQueue("dbl_mini32xu32_int EQU DBL_MINI32XU32_INT");

		AddLineQueue("dbl_fixunsigned_int EQU DBL_FIXUNSIGNED_INT");
		AddLineQueue("dbl_fixunsigned32_int EQU DBL_FIXUNSIGNED32_INT");
		AddLineQueue("dbl_fixmaxi32_int EQU DBL_FIXMAXI32_INT");
		AddLineQueue("dbl_fixmaxu32_int EQU DBL_FIXMAXU32_INT");

		AddLineQueue("dbl_fixunsigned64_int EQU DBL_FIXUNSIGNED64_INT");
		AddLineQueue("dbl_fixmaxi64_int EQU DBL_FIXMAXI64_INT");
		AddLineQueue("dbl_fixmaxu64_int EQU DBL_FIXMAXU64_INT");

		/*double*/
		AddLineQueue("dbl_1lshl3 EQU DBL_1LSHL3");
		AddLineQueue("dbl_1lshl4 EQU DBL_1LSHL4");
		AddLineQueue("dbl_1lshl7 EQU DBL_1LSHL7");
		AddLineQueue("dbl_1lshl8 EQU DBL_1LSHL8");
		AddLineQueue("dbl_1lshl11 EQU DBL_1LSHL11");
		AddLineQueue("dbl_1lshl12 EQU DBL_1LSHL12");
		AddLineQueue("dbl_1lshl15 EQU DBL_1LSHL15");
		AddLineQueue("dbl_1lshl16 EQU DBL_1LSHL16");
		AddLineQueue("dbl_1lshl19 EQU DBL_1LSHL19");
		AddLineQueue("dbl_1lshl20 EQU DBL_1LSHL20");
		AddLineQueue("dbl_1lshl23 EQU DBL_1LSHL23");
		AddLineQueue("dbl_1lshl24 EQU DBL_1LSHL24");
		AddLineQueue("dbl_1lshl27 EQU DBL_1LSHL27");
		AddLineQueue("dbl_1lshl28 EQU DBL_1LSHL28");
		AddLineQueue("dbl_1lshl31 EQU DBL_1LSHL31");
		AddLineQueue("dbl_1lshl32 EQU DBL_1LSHL32");
		AddLineQueue("dbl_1lshl35 EQU DBL_1LSHL35");
		AddLineQueue("dbl_1lshl36 EQU DBL_1LSHL36");
		AddLineQueue("dbl_1lshl39 EQU DBL_1LSHL39");
		AddLineQueue("dbl_1lshl40 EQU DBL_1LSHL40");
		AddLineQueue("dbl_1lshl43 EQU DBL_1LSHL43");
		AddLineQueue("dbl_1lshl44 EQU DBL_1LSHL44");
		AddLineQueue("dbl_1lshl47 EQU DBL_1LSHL47");
		AddLineQueue("dbl_1lshl48 EQU DBL_1LSHL48");
		AddLineQueue("dbl_1lshl51 EQU DBL_1LSHL51");
		AddLineQueue("dbl_1lshl52 EQU DBL_1LSHL52");
		AddLineQueue("dbl_1lshl55 EQU DBL_1LSHL55");
		AddLineQueue("dbl_1lshl56 EQU DBL_1LSHL56");
		AddLineQueue("dbl_1lshl59 EQU DBL_1LSHL59");
		AddLineQueue("dbl_1lshl60 EQU DBL_1LSHL60");
		AddLineQueue("dbl_1lshl63 EQU DBL_1LSHL63");

		AddLineQueue("dbl_neg1lshl3 EQU DBL_NEG1LSHL3");
		AddLineQueue("dbl_neg1lshl4 EQU DBL_NEG1LSHL4");
		AddLineQueue("dbl_neg1lshl7 EQU DBL_NEG1LSHL7");
		AddLineQueue("dbl_neg1lshl8 EQU DBL_NEG1LSHL8");
		AddLineQueue("dbl_neg1lshl11 EQU DBL_NEG1LSHL11");
		AddLineQueue("dbl_neg1lshl12 EQU DBL_NEG1LSHL12");
		AddLineQueue("dbl_neg1lshl15 EQU DBL_NEG1LSHL15");
		AddLineQueue("dbl_neg1lshl16 EQU DBL_NEG1LSHL16");
		AddLineQueue("dbl_neg1lshl19 EQU DBL_NEG1LSHL19");
		AddLineQueue("dbl_neg1lshl20 EQU DBL_NEG1LSHL20");
		AddLineQueue("dbl_neg1lshl23 EQU DBL_NEG1LSHL23");
		AddLineQueue("dbl_neg1lshl24 EQU DBL_NEG1LSHL24");
		AddLineQueue("dbl_neg1lshl27 EQU DBL_NEG1LSHL27");
		AddLineQueue("dbl_neg1lshl28 EQU DBL_NEG1LSHL28");
		AddLineQueue("dbl_neg1lshl31 EQU DBL_NEG1LSHL31");
		AddLineQueue("dbl_neg1lshl32 EQU DBL_NEG1LSHL32");
		AddLineQueue("dbl_neg1lshl35 EQU DBL_NEG1LSHL35");
		AddLineQueue("dbl_neg1lshl36 EQU DBL_NEG1LSHL36");
		AddLineQueue("dbl_neg1lshl39 EQU DBL_NEG1LSHL39");
		AddLineQueue("dbl_neg1lshl40 EQU DBL_NEG1LSHL40");
		AddLineQueue("dbl_neg1lshl43 EQU DBL_NEG1LSHL43");
		AddLineQueue("dbl_neg1lshl44 EQU DBL_NEG1LSHL44");
		AddLineQueue("dbl_neg1lshl47 EQU DBL_NEG1LSHL47");
		AddLineQueue("dbl_neg1lshl48 EQU DBL_NEG1LSHL48");
		AddLineQueue("dbl_neg1lshl51 EQU DBL_NEG1LSHL51");
		AddLineQueue("dbl_neg1lshl52 EQU DBL_NEG1LSHL52");
		AddLineQueue("dbl_neg1lshl55 EQU DBL_NEG1LSHL55");
		AddLineQueue("dbl_neg1lshl56 EQU DBL_NEG1LSHL56");
		AddLineQueue("dbl_neg1lshl59 EQU DBL_NEG1LSHL59");
		AddLineQueue("dbl_neg1lshl60 EQU DBL_NEG1LSHL60");
		AddLineQueue("dbl_neg1lshl63 EQU DBL_NEG1LSHL63");

		AddLineQueue("dbl_false EQU DBL_FALSE");
		AddLineQueue("dbl_true EQU DBL_TRUE");

		AddLineQueue("dbl_magic EQU DBL_MAGIC");
		AddLineQueue("dbl_sign EQU DBL_SIGN");
		AddLineQueue("dbl_invsign EQU DBL_INVSIGN");

		AddLineQueue("dbl_inf EQU DBL_INF");
		AddLineQueue("dbl_fin EQU DBL_FIN");
		AddLineQueue("dbl_invinf EQU DBL_INVINF");
		AddLineQueue("dbl_neginf EQU DBL_NEGINF");
		AddLineQueue("dbl_nan EQU DBL_NAN");
		AddLineQueue("dbl_qnan EQU DBL_QNAN");
		AddLineQueue("dbl_negqnan EQU DBL_NEGQNAN");
		AddLineQueue("dbl_nantest EQU DBL_NANTEST");
		AddLineQueue("dbl_abs EQU DBL_ABS");
		AddLineQueue("dbl_min EQU DBL_MIN");
		AddLineQueue("dbl_max EQU DBL_MAX");
		AddLineQueue("dbl_nofraction EQU DBL_NOFRACTION");
		AddLineQueue("dbl_mindenorm EQU DBL_MINDENORM");
		AddLineQueue("dbl_denormlimit EQU DBL_DENORMLIMIT");
		AddLineQueue("dbl_minnormal EQU DBL_MINNORMAL");
		AddLineQueue("dbl_maxnormal EQU DBL_MAXNORMAL");

		AddLineQueue("dbl_decdig EQU DBL_DECDIG");
		AddLineQueue("dbl_dig EQU DBL_DIG");
		AddLineQueue("dbl_negdecdig EQU DBL_NEGDECDIG");
		AddLineQueue("dbl_negdig EQU DBL_NEGDIG");
		AddLineQueue("dbl_eps EQU DBL_EPS");
		AddLineQueue("dbl_epsilon EQU DBL_EPSILON");
		AddLineQueue("dbl_normeps EQU DBL_NORMEPS");
		AddLineQueue("dbl_guard EQU DBL_GUARD");
		AddLineQueue("dbl_mantpow2 EQU DBL_MANTPOW2");
		AddLineQueue("dbl_maxmantpow2 EQU DBL_MAXMANTPOW2");
		AddLineQueue("dbl_mantdig EQU DBL_MANTDIG");
		AddLineQueue("dbl_mant EQU DBL_MANT");
		AddLineQueue("dbl_negmantdig EQU DBL_NEGMANTDIG");
		AddLineQueue("dbl_negmant EQU DBL_NEGMANT");
		AddLineQueue("dbl_maxexp EQU DBL_MAXEXP");
		AddLineQueue("dbl_expsign EQU DBL_EXPSIGN");
		AddLineQueue("dbl_exp EQU DBL_EXP");
		AddLineQueue("dbl_negmaxexp EQU DBL_NEGMAXEXP");
		AddLineQueue("dbl_negexpsign EQU DBL_NEGEXPSIGN");
		AddLineQueue("dbl_negexp EQU DBL_NEGEXP");
		AddLineQueue("dbl_subnormalexp EQU DBL_SUBNORMALEXP");
		AddLineQueue("dbl_minexp EQU DBL_MINEXP");
		AddLineQueue("dbl_maxdecexp EQU DBL_MAXDECEXP");
		AddLineQueue("dbl_negmaxdecexp EQU DBL_NEGMAXDECEXP");
		AddLineQueue("dbl_mindecexp EQU DBL_MINDECEXP");
		AddLineQueue("dbl_expfield EQU DBL_EXPFIELD");
		AddLineQueue("dbl_mantfield EQU DBL_MANTFIELD");
		AddLineQueue("dbl_norm EQU DBL_NORM");
		AddLineQueue("dbl_radix EQU DBL_RADIX");
		AddLineQueue("dbl_rounds EQU DBL_ROUNDS");
		AddLineQueue("dbl_subdec EQU DBL_SUBDEC");
		AddLineQueue("dbl_sqrtmax EQU DBL_SQRTMAX");
		AddLineQueue("dbl_smallnormal EQU DBL_SMALLNORMAL");

		AddLineQueue("dbl_halfminuseps EQU DBL_HALFMINUSEPS");
		AddLineQueue("dbl_trueint EQU DBL_TRUEINT");

		AddLineQueue("dbl_byte EQU DBL_BYTE");
		AddLineQueue("DBL_byte_even EQU DBL_BYTE_EVEN");
		AddLineQueue("DBL_byte_odd EQU DBL_BYTE_ODD");
		AddLineQueue("dbl_4low EQU DBL_4LOW");
		AddLineQueue("dbl_4high EQU DBL_4HIGH");
		AddLineQueue("dbl_flip4 EQU DBL_FLIP4");
		AddLineQueue("dbl_8low EQU DBL_8LOW");
		AddLineQueue("dbl_8high EQU DBL_8HIGH");
		AddLineQueue("dbl_flip8 EQU DBL_FLIP8");
		AddLineQueue("dbl_16low EQU DBL_16LOW");
		AddLineQueue("dbl_16high EQU DBL_16HIGH");
		AddLineQueue("dbl_flip16 EQU DBL_FLIP16");
		AddLineQueue("dbl_24low EQU DBL_24LOW");
		AddLineQueue("dbl_24high EQU DBL_24HIGH");
		AddLineQueue("dbl_flip24 EQU DBL_FLIP24");
		AddLineQueue("dbl_28low EQU DBL_28LOW");
		AddLineQueue("dbl_28high EQU DBL_28HIGH");
		AddLineQueue("dbl_flip28 EQU DBL_FLIP28");
		AddLineQueue("dbl_32low EQU DBL_32LOW");
		AddLineQueue("dbl_32high EQU DBL_32HIGH");
		AddLineQueue("dbl_flip32 EQU DBL_FLIP32");
		AddLineQueue("dbl_40low EQU DBL_40LOW");
		AddLineQueue("dbl_40high EQU DBL_40HIGH");
		AddLineQueue("dbl_flip40 EQU DBL_FLIP40");
		AddLineQueue("dbl_48low EQU DBL_48LOW");
		AddLineQueue("dbl_48high EQU DBL_48HIGH");
		AddLineQueue("dbl_flip48 EQU DBL_FLIP48");
		AddLineQueue("dbl_56low EQU DBL_56LOW");
		AddLineQueue("dbl_56high EQU DBL_56HIGH");
		AddLineQueue("dbl_flip56 EQU DBL_FLIP56");
		AddLineQueue("dbl_60low EQU DBL_60LOW");
		AddLineQueue("dbl_60high EQU DBL_60HIGH");
		AddLineQueue("dbl_flip60 EQU DBL_FLIP60");
		AddLineQueue("dbl_64low EQU DBL_64LOW");
		AddLineQueue("dbl_64high EQU DBL_64HIGH");
		AddLineQueue("dbl_flip64 EQU DBL_FLIP64");

		AddLineQueue("dbl_0 EQU DBL_0");
		AddLineQueue("dbl_0d0001 EQU DBL_0D0001");
		AddLineQueue("dbl_0d0002 EQU DBL_0D0002");
		AddLineQueue("dbl_0d0003 EQU DBL_0D0003");
		AddLineQueue("dbl_0d0004 EQU DBL_0D0004");
		AddLineQueue("dbl_0d0005 EQU DBL_0D0005");
		AddLineQueue("dbl_0d0006 EQU DBL_0D0006");
		AddLineQueue("dbl_0d0007 EQU DBL_0D0007");
		AddLineQueue("dbl_0d0008 EQU DBL_0D0008");
		AddLineQueue("dbl_0d0009 EQU DBL_0D0009");
		AddLineQueue("dbl_0d001 EQU DBL_0D001");
		AddLineQueue("dbl_0d002 EQU DBL_0D002");
		AddLineQueue("dbl_0d003 EQU DBL_0D003");
		AddLineQueue("dbl_0d004 EQU DBL_0D004");
		AddLineQueue("dbl_0d005 EQU DBL_0D005");
		AddLineQueue("dbl_0d006 EQU DBL_0D006");
		AddLineQueue("dbl_0d007 EQU DBL_0D007");
		AddLineQueue("dbl_0d008 EQU DBL_0D008");
		AddLineQueue("dbl_0d009 EQU DBL_0D009");
		AddLineQueue("dbl_0d01 EQU DBL_0D01");
		AddLineQueue("dbl_0d02 EQU DBL_0D02");
		AddLineQueue("dbl_0d025 EQU DBL_0D025");
		AddLineQueue("dbl_0d03 EQU DBL_0D03");
		AddLineQueue("dbl_0d04 EQU DBL_0D04");
		AddLineQueue("dbl_0d05 EQU DBL_0D05");
		AddLineQueue("dbl_0d06 EQU DBL_0D06");
		AddLineQueue("dbl_0d07 EQU DBL_0D07");
		AddLineQueue("dbl_0d08 EQU DBL_0D08");
		AddLineQueue("dbl_0d09 EQU DBL_0D09");
		AddLineQueue("dbl_0d1 EQU DBL_0D1");
		AddLineQueue("dbl_0d2 EQU DBL_0D2");
		AddLineQueue("dbl_0d25 EQU DBL_0D25");
		AddLineQueue("dbl_0d3 EQU DBL_0D3");
		AddLineQueue("dbl_0d4 EQU DBL_0D4");
		AddLineQueue("dbl_0d5 EQU DBL_0D5");
		AddLineQueue("dbl_0d6 EQU DBL_0D6");
		AddLineQueue("dbl_0d7 EQU DBL_0D7");
		AddLineQueue("dbl_0d8 EQU DBL_0D8");
		AddLineQueue("dbl_0d9 EQU DBL_0D9");
		AddLineQueue("dbl_1 EQU DBL_1");
		AddLineQueue("dbl_1d25 EQU DBL_1D25");
		AddLineQueue("dbl_1d5 EQU DBL_1D5");
		AddLineQueue("dbl_2 EQU DBL_2");
		AddLineQueue("dbl_2d25 EQU DBL_2D25");
		AddLineQueue("dbl_2d5 EQU DBL_2D5");
		AddLineQueue("dbl_3 EQU DBL_3");
		AddLineQueue("dbl_3d25 EQU DBL_3D25");
		AddLineQueue("dbl_3d5 EQU DBL_3D5");
		AddLineQueue("dbl_4 EQU DBL_4");
		AddLineQueue("dbl_4d25 EQU DBL_4D25");
		AddLineQueue("dbl_4d5 EQU DBL_4D5");
		AddLineQueue("dbl_5 EQU DBL_5");
		AddLineQueue("dbl_5d25 EQU DBL_5D25");
		AddLineQueue("dbl_5d5 EQU DBL_5D5");
		AddLineQueue("dbl_6 EQU DBL_6");
		AddLineQueue("dbl_6d25 EQU DBL_6D25");
		AddLineQueue("dbl_6d5 EQU DBL_6D5");
		AddLineQueue("dbl_7 EQU DBL_7");
		AddLineQueue("dbl_7d25 EQU DBL_7D25");
		AddLineQueue("dbl_7d5 EQU DBL_7D5");
		AddLineQueue("dbl_8 EQU DBL_8");
		AddLineQueue("dbl_8d25 EQU DBL_8D25");
		AddLineQueue("dbl_8d5 EQU DBL_8D5");
		AddLineQueue("dbl_9 EQU DBL_9");
		AddLineQueue("dbl_9d25 EQU DBL_9D25");
		AddLineQueue("dbl_9d5 EQU DBL_9D5");
		AddLineQueue("dbl_10 EQU DBL_10");
		AddLineQueue("dbl_11 EQU DBL_11");
		AddLineQueue("dbl_12 EQU DBL_12");
		AddLineQueue("dbl_13 EQU DBL_13");
		AddLineQueue("dbl_14 EQU DBL_14");
		AddLineQueue("dbl_15 EQU DBL_15");
		AddLineQueue("dbl_16 EQU DBL_16");
		AddLineQueue("dbl_17 EQU DBL_17");
		AddLineQueue("dbl_18 EQU DBL_18");
		AddLineQueue("dbl_19 EQU DBL_19");
		AddLineQueue("dbl_20 EQU DBL_20");
		AddLineQueue("dbl_21 EQU DBL_21");
		AddLineQueue("dbl_22 EQU DBL_22");
		AddLineQueue("dbl_23 EQU DBL_23");
		AddLineQueue("dbl_24 EQU DBL_24");
		AddLineQueue("dbl_24d5 EQU DBL_24D5");
		AddLineQueue("dbl_25 EQU DBL_25");
		AddLineQueue("dbl_26 EQU DBL_26");
		AddLineQueue("dbl_27 EQU DBL_27");
		AddLineQueue("dbl_28 EQU DBL_28");
		AddLineQueue("dbl_29 EQU DBL_29");
		AddLineQueue("dbl_30 EQU DBL_30");
		AddLineQueue("dbl_31 EQU DBL_31");
		AddLineQueue("dbl_32 EQU DBL_32");
		AddLineQueue("dbl_33 EQU DBL_33");
		AddLineQueue("dbl_34 EQU DBL_34");
		AddLineQueue("dbl_35 EQU DBL_35");
		AddLineQueue("dbl_36 EQU DBL_36");
		AddLineQueue("dbl_37 EQU DBL_37");
		AddLineQueue("dbl_38 EQU DBL_38");
		AddLineQueue("dbl_39 EQU DBL_39");
		AddLineQueue("dbl_40 EQU DBL_40");
		AddLineQueue("dbl_41 EQU DBL_41");
		AddLineQueue("dbl_42 EQU DBL_42");
		AddLineQueue("dbl_43 EQU DBL_43");
		AddLineQueue("dbl_44 EQU DBL_44");
		AddLineQueue("dbl_45 EQU DBL_45");
		AddLineQueue("dbl_46 EQU DBL_46");
		AddLineQueue("dbl_47 EQU DBL_47");
		AddLineQueue("dbl_48 EQU DBL_48");
		AddLineQueue("dbl_49 EQU DBL_49");
		AddLineQueue("dbl_50 EQU DBL_50");
		AddLineQueue("dbl_51 EQU DBL_51");
		AddLineQueue("dbl_52 EQU DBL_52");
		AddLineQueue("dbl_53 EQU DBL_53");
		AddLineQueue("dbl_54 EQU DBL_54");
		AddLineQueue("dbl_55 EQU DBL_55");
		AddLineQueue("dbl_56 EQU DBL_56");
		AddLineQueue("dbl_57 EQU DBL_57");
		AddLineQueue("dbl_58 EQU DBL_58");
		AddLineQueue("dbl_59 EQU DBL_59");
		AddLineQueue("dbl_60 EQU DBL_60");
		AddLineQueue("dbl_61 EQU DBL_61");
		AddLineQueue("dbl_62 EQU DBL_62");
		AddLineQueue("dbl_63 EQU DBL_63");
		AddLineQueue("dbl_64 EQU DBL_64");
		AddLineQueue("dbl_65 EQU DBL_65");
		AddLineQueue("dbl_66 EQU DBL_66");
		AddLineQueue("dbl_67 EQU DBL_67");
		AddLineQueue("dbl_68 EQU DBL_68");
		AddLineQueue("dbl_69 EQU DBL_69");
		AddLineQueue("dbl_70 EQU DBL_70");
		AddLineQueue("dbl_71 EQU DBL_71");
		AddLineQueue("dbl_72 EQU DBL_72");
		AddLineQueue("dbl_73 EQU DBL_73");
		AddLineQueue("dbl_74 EQU DBL_74");
		AddLineQueue("dbl_75 EQU DBL_75");
		AddLineQueue("dbl_76 EQU DBL_76");
		AddLineQueue("dbl_77 EQU DBL_77");
		AddLineQueue("dbl_78 EQU DBL_78");
		AddLineQueue("dbl_79 EQU DBL_79");
		AddLineQueue("dbl_80 EQU DBL_80");
		AddLineQueue("dbl_81 EQU DBL_81");
		AddLineQueue("dbl_82 EQU DBL_82");
		AddLineQueue("dbl_83 EQU DBL_83");
		AddLineQueue("dbl_84 EQU DBL_84");
		AddLineQueue("dbl_85 EQU DBL_85");
		AddLineQueue("dbl_86 EQU DBL_86");
		AddLineQueue("dbl_87 EQU DBL_87");
		AddLineQueue("dbl_88 EQU DBL_88");
		AddLineQueue("dbl_89 EQU DBL_89");
		AddLineQueue("dbl_90 EQU DBL_90");
		AddLineQueue("dbl_91 EQU DBL_91");
		AddLineQueue("dbl_92 EQU DBL_92");
		AddLineQueue("dbl_93 EQU DBL_93");
		AddLineQueue("dbl_94 EQU DBL_94");
		AddLineQueue("dbl_95 EQU DBL_95");
		AddLineQueue("dbl_96 EQU DBL_96");
		AddLineQueue("dbl_97 EQU DBL_97");
		AddLineQueue("dbl_98 EQU DBL_98");
		AddLineQueue("dbl_99 EQU DBL_99");
		AddLineQueue("dbl_100 EQU DBL_100");
		AddLineQueue("dbl_125 EQU DBL_125");
		AddLineQueue("dbl_126 EQU DBL_126");
		AddLineQueue("dbl_127 EQU DBL_127");
		AddLineQueue("dbl_128 EQU DBL_128");
		AddLineQueue("dbl_140 EQU DBL_140");
		AddLineQueue("dbl_145 EQU DBL_145");
		AddLineQueue("dbl_150 EQU DBL_150");
		AddLineQueue("dbl_180 EQU DBL_180");
		AddLineQueue("dbl_253 EQU DBL_253");
		AddLineQueue("dbl_254 EQU DBL_254");
		AddLineQueue("dbl_255 EQU DBL_255");
		AddLineQueue("dbl_256 EQU DBL_256");
		AddLineQueue("dbl_360 EQU DBL_360");
		AddLineQueue("dbl_511 EQU DBL_511");
		AddLineQueue("dbl_512 EQU DBL_512");
		AddLineQueue("dbl_513 EQU DBL_513");
		AddLineQueue("dbl_1023 EQU DBL_1023");
		AddLineQueue("dbl_1024 EQU DBL_1024");
		AddLineQueue("dbl_1025 EQU DBL_1025");

		AddLineQueue("dbl_32767 EQU DBL_32767");
		AddLineQueue("dbl_32768 EQU DBL_32768");
		AddLineQueue("dbl_65535 EQU DBL_65535");
		AddLineQueue("dbl_65536 EQU DBL_65536");
		AddLineQueue("dbl_2147483647 EQU DBL_2147483647");
		AddLineQueue("dbl_2147483648 EQU DBL_2147483648");
		AddLineQueue("dbl_4294967295 EQU DBL_4294967295");
		AddLineQueue("dbl_4294967296 EQU DBL_4294967296");

		AddLineQueue("dbl_neg0 EQU DBL_NEG0");
		AddLineQueue("dbl_neg0d0001 EQU DBL_NEG0D0001");
		AddLineQueue("dbl_neg0d0002 EQU DBL_NEG0D0002");
		AddLineQueue("dbl_neg0d0003 EQU DBL_NEG0D0003");
		AddLineQueue("dbl_neg0d0004 EQU DBL_NEG0D0004");
		AddLineQueue("dbl_neg0d0005 EQU DBL_NEG0D0005");
		AddLineQueue("dbl_neg0d0006 EQU DBL_NEG0D0006");
		AddLineQueue("dbl_neg0d0007 EQU DBL_NEG0D0007");
		AddLineQueue("dbl_neg0d0008 EQU DBL_NEG0D0008");
		AddLineQueue("dbl_neg0d0009 EQU DBL_NEG0D0009");
		AddLineQueue("dbl_neg0d001 EQU DBL_NEG0D001");
		AddLineQueue("dbl_neg0d002 EQU DBL_NEG0D002");
		AddLineQueue("dbl_neg0d003 EQU DBL_NEG0D003");
		AddLineQueue("dbl_neg0d004 EQU DBL_NEG0D004");
		AddLineQueue("dbl_neg0d005 EQU DBL_NEG0D005");
		AddLineQueue("dbl_neg0d006 EQU DBL_NEG0D006");
		AddLineQueue("dbl_neg0d007 EQU DBL_NEG0D007");
		AddLineQueue("dbl_neg0d008 EQU DBL_NEG0D008");
		AddLineQueue("dbl_neg0d009 EQU DBL_NEG0D009");
		AddLineQueue("dbl_neg0d01 EQU DBL_NEG0D01");
		AddLineQueue("dbl_neg0d02 EQU DBL_NEG0D02");
		AddLineQueue("dbl_neg0d025 EQU DBL_NEG0D025");
		AddLineQueue("dbl_neg0d03 EQU DBL_NEG0D03");
		AddLineQueue("dbl_neg0d04 EQU DBL_NEG0D04");
		AddLineQueue("dbl_neg0d05 EQU DBL_NEG0D05");
		AddLineQueue("dbl_neg0d06 EQU DBL_NEG0D06");
		AddLineQueue("dbl_neg0d07 EQU DBL_NEG0D07");
		AddLineQueue("dbl_neg0d08 EQU DBL_NEG0D08");
		AddLineQueue("dbl_neg0d09 EQU DBL_NEG0D09");
		AddLineQueue("dbl_neg0d1 EQU DBL_NEG0D1");
		AddLineQueue("dbl_neg0d2 EQU DBL_NEG0D2");
		AddLineQueue("dbl_neg0d25 EQU DBL_NEG0D25");
		AddLineQueue("dbl_neg0d3 EQU DBL_NEG0D3");
		AddLineQueue("dbl_neg0d4 EQU DBL_NEG0D4");
		AddLineQueue("dbl_neg0d5 EQU DBL_NEG0D5");
		AddLineQueue("dbl_neg0d6 EQU DBL_NEG0D6");
		AddLineQueue("dbl_neg0d7 EQU DBL_NEG0D7");
		AddLineQueue("dbl_neg0d8 EQU DBL_NEG0D8");
		AddLineQueue("dbl_neg0d9 EQU DBL_NEG0D9");
		AddLineQueue("dbl_neg1 EQU DBL_NEG1");
		AddLineQueue("dbl_neg1d25 EQU DBL_NEG1D25");
		AddLineQueue("dbl_neg2 EQU DBL_NEG2");
		AddLineQueue("dbl_neg2d25 EQU DBL_NEG2D25");
		AddLineQueue("dbl_neg3 EQU DBL_NEG3");
		AddLineQueue("dbl_neg3d25 EQU DBL_NEG3D25");
		AddLineQueue("dbl_neg4 EQU DBL_NEG4");
		AddLineQueue("dbl_neg4d25 EQU DBL_NEG4D25");
		AddLineQueue("dbl_neg5 EQU DBL_NEG5");
		AddLineQueue("dbl_neg5d25 EQU DBL_NEG5D25");
		AddLineQueue("dbl_neg6 EQU DBL_NEG6");
		AddLineQueue("dbl_neg6d25 EQU DBL_NEG6D25");
		AddLineQueue("dbl_neg7 EQU DBL_NEG7");
		AddLineQueue("dbl_neg7d25 EQU DBL_NEG7D25");
		AddLineQueue("dbl_neg8 EQU DBL_NEG8");
		AddLineQueue("dbl_neg8d25 EQU DBL_NEG8D25");
		AddLineQueue("dbl_neg9 EQU DBL_NEG9");
		AddLineQueue("dbl_neg9d25 EQU DBL_NEG9D25");
		AddLineQueue("dbl_neg10 EQU DBL_NEG10");
		AddLineQueue("dbl_neg11 EQU DBL_NEG11");
		AddLineQueue("dbl_neg12 EQU DBL_NEG12");
		AddLineQueue("dbl_neg13 EQU DBL_NEG13");
		AddLineQueue("dbl_neg14 EQU DBL_NEG14");
		AddLineQueue("dbl_neg15 EQU DBL_NEG15");
		AddLineQueue("dbl_neg16 EQU DBL_NEG16");
		AddLineQueue("dbl_neg17 EQU DBL_NEG17");
		AddLineQueue("dbl_neg18 EQU DBL_NEG18");
		AddLineQueue("dbl_neg19 EQU DBL_NEG19");
		AddLineQueue("dbl_neg20 EQU DBL_NEG20");
		AddLineQueue("dbl_neg21 EQU DBL_NEG21");
		AddLineQueue("dbl_neg22 EQU DBL_NEG22");
		AddLineQueue("dbl_neg23 EQU DBL_NEG23");
		AddLineQueue("dbl_neg24 EQU DBL_NEG24");
		AddLineQueue("dbl_neg24d5 EQU DBL_NEG24D5");
		AddLineQueue("dbl_neg25 EQU DBL_NEG25");
		AddLineQueue("dbl_neg26 EQU DBL_NEG26");
		AddLineQueue("dbl_neg27 EQU DBL_NEG27");
		AddLineQueue("dbl_neg28 EQU DBL_NEG28");
		AddLineQueue("dbl_neg29 EQU DBL_NEG29");
		AddLineQueue("dbl_neg30 EQU DBL_NEG30");
		AddLineQueue("dbl_neg31 EQU DBL_NEG31");
		AddLineQueue("dbl_neg32 EQU DBL_NEG32");
		AddLineQueue("dbl_neg33 EQU DBL_NEG33");
		AddLineQueue("dbl_neg34 EQU DBL_NEG34");
		AddLineQueue("dbl_neg35 EQU DBL_NEG35");
		AddLineQueue("dbl_neg36 EQU DBL_NEG36");
		AddLineQueue("dbl_neg37 EQU DBL_NEG37");
		AddLineQueue("dbl_neg38 EQU DBL_NEG38");
		AddLineQueue("dbl_neg39 EQU DBL_NEG39");
		AddLineQueue("dbl_neg40 EQU DBL_NEG40");
		AddLineQueue("dbl_neg41 EQU DBL_NEG41");
		AddLineQueue("dbl_neg42 EQU DBL_NEG42");
		AddLineQueue("dbl_neg43 EQU DBL_NEG43");
		AddLineQueue("dbl_neg44 EQU DBL_NEG44");
		AddLineQueue("dbl_neg45 EQU DBL_NEG45");
		AddLineQueue("dbl_neg46 EQU DBL_NEG46");
		AddLineQueue("dbl_neg47 EQU DBL_NEG47");
		AddLineQueue("dbl_neg48 EQU DBL_NEG48");
		AddLineQueue("dbl_neg49 EQU DBL_NEG49");
		AddLineQueue("dbl_neg50 EQU DBL_NEG50");
		AddLineQueue("dbl_neg51 EQU DBL_NEG51");
		AddLineQueue("dbl_neg52 EQU DBL_NEG52");
		AddLineQueue("dbl_neg53 EQU DBL_NEG53");
		AddLineQueue("dbl_neg54 EQU DBL_NEG54");
		AddLineQueue("dbl_neg55 EQU DBL_NEG55");
		AddLineQueue("dbl_neg56 EQU DBL_NEG56");
		AddLineQueue("dbl_neg57 EQU DBL_NEG57");
		AddLineQueue("dbl_neg58 EQU DBL_NEG58");
		AddLineQueue("dbl_neg59 EQU DBL_NEG59");
		AddLineQueue("dbl_neg60 EQU DBL_NEG60");
		AddLineQueue("dbl_neg61 EQU DBL_NEG61");
		AddLineQueue("dbl_neg62 EQU DBL_NEG62");
		AddLineQueue("dbl_neg63 EQU DBL_NEG63");
		AddLineQueue("dbl_neg64 EQU DBL_NEG64");
		AddLineQueue("dbl_neg65 EQU DBL_NEG65");
		AddLineQueue("dbl_neg66 EQU DBL_NEG66");
		AddLineQueue("dbl_neg67 EQU DBL_NEG67");
		AddLineQueue("dbl_neg68 EQU DBL_NEG68");
		AddLineQueue("dbl_neg69 EQU DBL_NEG69");
		AddLineQueue("dbl_neg70 EQU DBL_NEG70");
		AddLineQueue("dbl_neg71 EQU DBL_NEG71");
		AddLineQueue("dbl_neg72 EQU DBL_NEG72");
		AddLineQueue("dbl_neg73 EQU DBL_NEG73");
		AddLineQueue("dbl_neg74 EQU DBL_NEG74");
		AddLineQueue("dbl_neg75 EQU DBL_NEG75");
		AddLineQueue("dbl_neg76 EQU DBL_NEG76");
		AddLineQueue("dbl_neg77 EQU DBL_NEG77");
		AddLineQueue("dbl_neg78 EQU DBL_NEG78");
		AddLineQueue("dbl_neg79 EQU DBL_NEG79");
		AddLineQueue("dbl_neg80 EQU DBL_NEG80");
		AddLineQueue("dbl_neg81 EQU DBL_NEG81");
		AddLineQueue("dbl_neg82 EQU DBL_NEG82");
		AddLineQueue("dbl_neg83 EQU DBL_NEG83");
		AddLineQueue("dbl_neg84 EQU DBL_NEG84");
		AddLineQueue("dbl_neg85 EQU DBL_NEG85");
		AddLineQueue("dbl_neg86 EQU DBL_NEG86");
		AddLineQueue("dbl_neg87 EQU DBL_NEG87");
		AddLineQueue("dbl_neg88 EQU DBL_NEG88");
		AddLineQueue("dbl_neg89 EQU DBL_NEG89");
		AddLineQueue("dbl_neg90 EQU DBL_NEG90");
		AddLineQueue("dbl_neg91 EQU DBL_NEG91");
		AddLineQueue("dbl_neg92 EQU DBL_NEG92");
		AddLineQueue("dbl_neg93 EQU DBL_NEG93");
		AddLineQueue("dbl_neg94 EQU DBL_NEG94");
		AddLineQueue("dbl_neg95 EQU DBL_NEG95");
		AddLineQueue("dbl_neg96 EQU DBL_NEG96");
		AddLineQueue("dbl_neg97 EQU DBL_NEG97");
		AddLineQueue("dbl_neg98 EQU DBL_NEG98");
		AddLineQueue("dbl_neg99 EQU DBL_NEG99");
		AddLineQueue("dbl_neg100 EQU DBL_NEG100");
		AddLineQueue("dbl_neg125 EQU DBL_NEG125");
		AddLineQueue("dbl_neg126 EQU DBL_NEG126");
		AddLineQueue("dbl_neg127 EQU DBL_NEG127");
		AddLineQueue("dbl_neg128 EQU DBL_NEG128");
		AddLineQueue("dbl_neg140 EQU DBL_NEG140");
		AddLineQueue("dbl_neg145 EQU DBL_NEG145");
		AddLineQueue("dbl_neg150 EQU DBL_NEG150");
		AddLineQueue("dbl_neg180 EQU DBL_NEG180");
		AddLineQueue("dbl_neg253 EQU DBL_NEG253");
		AddLineQueue("dbl_neg254 EQU DBL_NEG254");
		AddLineQueue("dbl_neg255 EQU DBL_NEG255");
		AddLineQueue("dbl_neg256 EQU DBL_NEG256");
		AddLineQueue("dbl_neg360 EQU DBL_NEG360");
		AddLineQueue("dbl_neg511 EQU DBL_NEG511");
		AddLineQueue("dbl_neg512 EQU DBL_NEG512");
		AddLineQueue("dbl_neg513 EQU DBL_NEG513");
		AddLineQueue("dbl_neg1023 EQU DBL_NEG1023");
		AddLineQueue("dbl_neg1024 EQU DBL_NEG1024");
		AddLineQueue("dbl_neg1025 EQU DBL_NEG1025");

		AddLineQueue("dbl_neg32767 EQU DBL_NEG32767");
		AddLineQueue("dbl_neg32768 EQU DBL_NEG32768");
		AddLineQueue("dbl_neg65535 EQU DBL_NEG65535");
		AddLineQueue("dbl_neg65536 EQU DBL_NEG65536");
		AddLineQueue("dbl_neg2147483647 EQU DBL_NEG2147483647");
		AddLineQueue("dbl_neg2147483648 EQU DBL_NEG2147483648");
		AddLineQueue("dbl_neg4294967295 EQU DBL_NEG4294967295");
		AddLineQueue("dbl_neg4294967296 EQU DBL_NEG4294967296");

		AddLineQueue("dbl_bin128 EQU DBL_BIN128");
		AddLineQueue("dbl_binneg150 EQU DBL_BINNEG150");

		AddLineQueue("dbl_maxrand EQU DBL_MAXRAND");

		AddLineQueue("dbl_maxi8 EQU DBL_MAXI8");
		AddLineQueue("dbl_mini8 EQU DBL_MINI8");
		AddLineQueue("dbl_maxu8 EQU DBL_MAXU8");

		AddLineQueue("dbl_maxi16 EQU DBL_MAXI16");
		AddLineQueue("dbl_mini16 EQU DBL_MINI16");
		AddLineQueue("dbl_maxu16 EQU DBL_MAXU16");

		AddLineQueue("dbl_maxi32 EQU DBL_MAXI32");
		AddLineQueue("dbl_mini32 EQU DBL_MINI32");
		AddLineQueue("dbl_maxu32 EQU DBL_MAXU32");

		AddLineQueue("dbl_maxi64 EQU DBL_MAXI64");
		AddLineQueue("dbl_mini64 EQU DBL_MINI64");
		AddLineQueue("dbl_maxu64 EQU DBL_MAXU64");

		AddLineQueue("dbl_maxi8xu8 EQU DBL_MAXI8XU8");
		AddLineQueue("dbl_mini8xu8 EQU DBL_MINI8XU8");
		AddLineQueue("dbl_maxi8xu16 EQU DBL_MAXI8XU16");
		AddLineQueue("dbl_mini8xu16 EQU DBL_MINI8XU16");

		AddLineQueue("dbl_maxi16xu16 EQU DBL_MAXI16XU16");
		AddLineQueue("dbl_mini16xu16 EQU DBL_MINI16XU16");
		AddLineQueue("dbl_maxi16xu32 EQU DBL_MAXI16XU32");
		AddLineQueue("dbl_mini16xu32 EQU DBL_MINI16XU32");

		AddLineQueue("dbl_maxi32xu32 EQU DBL_MAXI32XU32");
		AddLineQueue("dbl_mini32xu32 EQU DBL_MINI32XU32");

		AddLineQueue("dbl_fixunsigned EQU DBL_FIXUNSIGNED");
		AddLineQueue("dbl_fixunsigned32 EQU DBL_FIXUNSIGNED32");
		AddLineQueue("dbl_fixmaxi32 EQU DBL_FIXMAXI32");
		AddLineQueue("dbl_fixmaxu32 EQU DBL_FIXMAXU32");

		AddLineQueue("dbl_fixunsigned64 EQU DBL_FIXUNSIGNED64");
		AddLineQueue("dbl_fixmaxi64 EQU DBL_FIXMAXI64");
		AddLineQueue("dbl_fixmaxu64 EQU DBL_FIXMAXU64");

		AddLineQueue("dbl_rcpi16 EQU DBL_RCPI16");
		AddLineQueue("dbl_rcpu16 EQU DBL_RCPU16");
		AddLineQueue("dbl_rcpi16xu16 EQU DBL_RCPI16XU16");

		AddLineQueue("dbl_mg EQU DBL_MG");
		AddLineQueue("dbl_negmg EQU DBL_NEGMG");
		AddLineQueue("dbl_halfmg EQU DBL_HALFMG");
		AddLineQueue("dbl_neghalfmg EQU DBL_NEGHALFMG");
		AddLineQueue("dbl_mgdiv4 EQU DBL_MGDIV4");
		AddLineQueue("dbl_negmgdiv4 EQU DBL_NEGMGDIV4");
		AddLineQueue("dbl_halfmgxmg EQU DBL_HALFMGXMG");
		AddLineQueue("dbl_halfmgxsqrmg EQU DBL_HALFMGXSQRMG");
		AddLineQueue("dbl_halfmgxcubemg EQU DBL_HALFMGXCUBEMG");
		AddLineQueue("dbl_neghalfmgxmg EQU DBL_NEGHALFMGXMG");
		AddLineQueue("dbl_neghalfmgxsqrmg EQU DBL_NEGHALFMGXSQRMG");
		AddLineQueue("dbl_neghalfmgxcubemg EQU DBL_NEGHALFMGXCUBEMG");
		AddLineQueue("dbl_sqrmg EQU DBL_SQRMG");
		AddLineQueue("dbl_cubemg EQU DBL_CUBEMG");
		AddLineQueue("dbl_sqrtmg EQU DBL_SQRTMG");
		AddLineQueue("dbl_cbrtmg EQU DBL_CBRTMG");
		AddLineQueue("dbl_rcpmg EQU DBL_RCPMG");
		AddLineQueue("dbl_rcpsqrmg EQU DBL_RCPSQRMG");
		AddLineQueue("dbl_rcpcubemg EQU DBL_RCPCUBEMG");
		AddLineQueue("dbl_rcpsqrtmg EQU DBL_RCPSQRTMG");
		AddLineQueue("dbl_rcpcbrtmg EQU DBL_RCPCBRTMG");

		AddLineQueue("dbl_2mg EQU DBL_2MG");
		AddLineQueue("dbl_neg2mg EQU DBL_NEG2MG");
		AddLineQueue("dbl_sqr2mg EQU DBL_SQR2MG");
		AddLineQueue("dbl_cube2mg EQU DBL_CUBE2MG");
		AddLineQueue("dbl_sqrt2mg EQU DBL_SQRT2MG");
		AddLineQueue("dbl_cbrt2mg EQU DBL_CBRT2MG");
		AddLineQueue("dbl_4mg EQU DBL_4MG");
		AddLineQueue("dbl_neg4mg EQU DBL_NEG4MG");
		AddLineQueue("dbl_sqr4mg EQU DBL_SQR4MG");
		AddLineQueue("dbl_cube4mg EQU DBL_CUBE4MG");
		AddLineQueue("dbl_sqrt4mg EQU DBL_SQRT4MG");
		AddLineQueue("dbl_cbrt4mg EQU DBL_CBRT4MG");
		AddLineQueue("dbl_rcp2mg EQU DBL_RCP2MG");
		AddLineQueue("dbl_rcp4mg EQU DBL_RCP4MG");

		AddLineQueue("dbl_e EQU DBL_E");
		AddLineQueue("dbl_exp EQU DBL_EXP");
		AddLineQueue("dbl_loge EQU DBL_LOGE");
		AddLineQueue("dbl_logehigh EQU DBL_LOGEHIGH");
		AddLineQueue("dbl_logelow EQU DBL_LOGELOW");
		AddLineQueue("dbl_log2e EQU DBL_LOG2E");
		AddLineQueue("dbl_log2ehigh EQU DBL_LOG2EHIGH");
		AddLineQueue("dbl_log2elow EQU DBL_LOG2ELOW");
		AddLineQueue("dbl_log10e EQU DBL_LOG10E");
		AddLineQueue("dbl_rcplog2e EQU DBL_RCPLOG2E");
		AddLineQueue("dbl_rcplog10e EQU DBL_RCPLOG10E");
		AddLineQueue("dbl_log2t EQU DBL_LOG2T");
		AddLineQueue("dbl_log2 EQU DBL_LOG2");
		AddLineQueue("dbl_log2high EQU DBL_LOG2HIGH");
		AddLineQueue("dbl_log2low EQU DBL_LOG2LOW");
		AddLineQueue("dbl_ln2 EQU DBL_LN2");
		AddLineQueue("dbl_ln2high EQU DBL_LN2HIGH");
		AddLineQueue("dbl_ln2low EQU DBL_LN2LOW");
		AddLineQueue("dbl_1divln2 EQU DBL_1DIVLN2");
		AddLineQueue("dbl_2divln2 EQU DBL_2DIVLN2");
		AddLineQueue("dbl_lnt EQU DBL_LNT");
		AddLineQueue("dbl_lnthigh EQU DBL_LNTHIGH");
		AddLineQueue("dbl_lntlow EQU DBL_LNTLOW");
		AddLineQueue("dbl_ln10 EQU DBL_LN10");
		AddLineQueue("dbl_sqrt2 EQU DBL_SQRT2");
		AddLineQueue("dbl_rcpsqrt2 EQU DBL_RCPSQRT2");
		AddLineQueue("dbl_sqrt2div2 EQU DBL_SQRT2DIV2");
		AddLineQueue("dbl_sqrt2div2high EQU DBL_SQRT2DIV2HIGH");
		AddLineQueue("dbl_sqrt2div2low EQU DBL_SQRT2DIV2LOW");
		AddLineQueue("dbl_sqrthalf EQU DBL_SQRTHALF");
		AddLineQueue("dbl_sqrthalfhigh EQU DBL_SQRTHALFHIGH");
		AddLineQueue("dbl_sqrthalflow EQU DBL_SQRTHALFLOW");
		AddLineQueue("dbl_pow2 EQU DBL_POW2");
		AddLineQueue("dbl_rcppow2 EQU DBL_RCPPOW2");
		AddLineQueue("dbl_cbrt2 EQU DBL_CBRT2");
		AddLineQueue("dbl_rcpcbrt2 EQU DBL_RCPCBRT2");
		AddLineQueue("dbl_1div3 EQU DBL_1DIV3");
		AddLineQueue("dbl_1div7 EQU DBL_1DIV7");
		AddLineQueue("dbl_1div9 EQU DBL_1DIV9");
		AddLineQueue("dbl_2div3 EQU DBL_2DIV3");
		AddLineQueue("dbl_2div7 EQU DBL_2DIV7");
		AddLineQueue("dbl_2div9 EQU DBL_2DIV9");
		AddLineQueue("dbl_4div3 EQU DBL_4DIV3");
		AddLineQueue("dbl_4div7 EQU DBL_4DIV7");
		AddLineQueue("dbl_4div9 EQU DBL_4DIV9");

		AddLineQueue("dbl_pi EQU DBL_PI");
		AddLineQueue("dbl_pihigh EQU DBL_PIHIGH");
		AddLineQueue("dbl_pilow EQU DBL_PILOW");
		AddLineQueue("dbl_halfpi EQU DBL_HALFPI");
		AddLineQueue("dbl_2pi EQU DBL_2PI");
		AddLineQueue("dbl_negpi EQU DBL_NEGPI");
		AddLineQueue("dbl_neghalfpi EQU DBL_NEGHALFPI");
		AddLineQueue("dbl_neg2pi EQU DBL_NEG2PI");
		AddLineQueue("dbl_rcppi EQU DBL_RCPPI");
		AddLineQueue("dbl_invpi EQU DBL_INVPI");
		AddLineQueue("dbl_rcp2pi EQU DBL_RCP2PI");
		AddLineQueue("dbl_inv2pi EQU DBL_INV2PI");
		AddLineQueue("dbl_pidiv2 EQU DBL_PIDIV2");
		AddLineQueue("dbl_pidiv2high EQU DBL_PIDIV2HIGH");
		AddLineQueue("dbl_pidiv2low EQU DBL_PIDIV2LOW");
		AddLineQueue("dbl_pidiv4 EQU DBL_PIDIV4");
		AddLineQueue("dbl_pidiv4high EQU DBL_PIDIV4HIGH");
		AddLineQueue("dbl_pidiv4low EQU DBL_PIDIV4LOW");
		AddLineQueue("dbl_pix3div4 EQU DBL_PIX3DIV4");
		AddLineQueue("dbl_sqrtpi EQU DBL_SQRTPI");
		AddLineQueue("dbl_sqrt2pi EQU DBL_SQRT2PI");
		AddLineQueue("dbl_sqrt2pihigh EQU DBL_SQRT2PIHIGH");
		AddLineQueue("dbl_sqrt2pilow EQU DBL_SQRT2PILOW");
		AddLineQueue("dbl_rcpsqrtpi EQU DBL_RCPSQRTPI");
		AddLineQueue("dbl_rcpsqrt2pi EQU DBL_RCPSQRT2PI");
		AddLineQueue("dbl_sqrtpidiv2 EQU DBL_SQRTPIDIV2");
		AddLineQueue("dbl_sqrtpidiv2high EQU DBL_SQRTPIDIV2HIGH");
		AddLineQueue("dbl_sqrt2pidiv2 EQU DBL_SQRT2PIDIV2");
		AddLineQueue("dbl_sqrt2pidiv2high EQU DBL_SQRT2PIDIV2HIGH");
		AddLineQueue("dbl_sqrt2pidiv2low EQU DBL_SQRT2PIDIV2LOW");
		AddLineQueue("dbl_2divpi EQU DBL_2DIVPI");
		AddLineQueue("dbl_2div2pi EQU DBL_2DIV2PI");
		AddLineQueue("dbl_2divsqrtpi EQU DBL_2DIVSQRTPI");
		AddLineQueue("dbl_2divsqrt2pi EQU DBL_2DIVSQRT2PI");
		AddLineQueue("dbl_sqrt2divpi EQU DBL_SQRT2DIVPI");
		AddLineQueue("dbl_logpi EQU DBL_LOGPI");
		AddLineQueue("dbl_log2pi EQU DBL_LOG2PI");
		AddLineQueue("dbl_lnpi EQU DBL_LNPI");
		AddLineQueue("dbl_ln2pi EQU DBL_LN2PI");
		AddLineQueue("dbl_powpi EQU DBL_POWPI");
		AddLineQueue("dbl_rcppowpi EQU DBL_RCPPOWPI");
		AddLineQueue("dbl_pow2pi EQU DBL_POW2PI");
		AddLineQueue("dbl_rcppow2pi EQU DBL_RCPPOW2PI");
		AddLineQueue("dbl_cbrtpi EQU DBL_CBRTPI");
		AddLineQueue("dbl_rcpcbrtpi EQU DBL_RCPCBRTPI");
		AddLineQueue("dbl_cbrt2pi EQU DBL_CBRT2PI");
		AddLineQueue("dbl_rcpcbrt2pi EQU DBL_RCPCBRT2PI");

		AddLineQueue("dbl_ln2x1024 EQU DBL_LN2X1024");
		AddLineQueue("dbl_ln2x1025 EQU DBL_LN2X1025");
		AddLineQueue("dbl_ln2x1075 EQU DBL_LN2X1075");
		AddLineQueue("dbl_log2x1024 EQU DBL_LOG2X1024");
		AddLineQueue("dbl_log2x1075 EQU DBL_LOG2X1075");

		AddLineQueue("dbl_pow2tom126 EQU DBL_POW2TOM126");
		AddLineQueue("dbl_pow2to126 EQU DBL_POW2TO126");
		AddLineQueue("dbl_normhuge EQU DBL_NORMHUGE");
		AddLineQueue("dbl_pow2to23 EQU DBL_POW2TO23");
		AddLineQueue("dbl_pow2to24 EQU DBL_POW2TO24");
		AddLineQueue("dbl_maxi32pow2to23 EQU DBL_MAXI32POW2TO23");
		AddLineQueue("dbl_pow2to31 EQU DBL_POW2TO31");
		AddLineQueue("dbl_pow2to32 EQU DBL_POW2TO32");
		AddLineQueue("dbl_pow2to52 EQU DBL_POW2TO52");
		AddLineQueue("dbl_pow2to53 EQU DBL_POW2TO53");
		AddLineQueue("dbl_pow2to54 EQU DBL_POW2TO54");
		AddLineQueue("dbl_pow2tom54 EQU DBL_POW2TOM54");
		AddLineQueue("dbl_pow2to62 EQU DBL_POW2TO62");
		AddLineQueue("dbl_maxi64pow2to52 EQU DBL_MAXI64POW2TO52");
		AddLineQueue("dbl_pow2to63 EQU DBL_POW2TO63");
		AddLineQueue("dbl_pow2to64 EQU DBL_POW2TO64");
		AddLineQueue("dbl_pow2tom1022 EQU DBL_POW2TOM1022");
		AddLineQueue("dbl_trigploss EQU DBL_TRIGPLOSS");

		AddLineQueue("dbl_degtorad EQU DBL_DEGTORAD");
		AddLineQueue("dbl_radtodeg EQU DBL_RADTODEG");

		AddLineQueue("dbl_degtograd EQU DBL_DEGTOGRAD");
		AddLineQueue("dbl_gradtodeg EQU DBL_GRADTODEG");

		AddLineQueue("dbl_radtograd EQU DBL_RADTOGRAD");
		AddLineQueue("dbl_gradtorad EQU DBL_GRADTORAD");

		AddLineQueue("dbl_sungravity EQU DBL_SUNGRAVITY");
		AddLineQueue("dbl_jupitergravity EQU DBL_JUPITERGRAVITY");
		AddLineQueue("dbl_neptunegravity EQU DBL_NEPTUNEGRAVITY");
		AddLineQueue("dbl_saturngravity EQU DBL_SATURNGRAVITY");
		AddLineQueue("dbl_uranusgravity EQU DBL_URANUSGRAVITY");
		AddLineQueue("dbl_earthgravity EQU DBL_EARTHGRAVITY");
		AddLineQueue("dbl_venusgravity EQU DBL_VENUSGRAVITY");
		AddLineQueue("dbl_marsgravity EQU DBL_MARSGRAVITY");
		AddLineQueue("dbl_mercurygravity EQU DBL_MERCURYGRAVITY");
		AddLineQueue("dbl_moongravity EQU DBL_MOONGRAVITY");
		AddLineQueue("dbl_plutogravity EQU DBL_PLUTOGRAVITY");

		AddLineQueue("dbl_kmtoinch EQU DBL_KMTOINCH");
		AddLineQueue("dbl_kmtofeet EQU DBL_KMTOFEET");
		AddLineQueue("dbl_kmtoyards EQU DBL_KMTOYARDS");
		AddLineQueue("dbl_kmtomiles EQU DBL_KMTOMILES");

		AddLineQueue("dbl_metoinch EQU DBL_METOINCH");
		AddLineQueue("dbl_metofeet EQU DBL_METOFEET");
		AddLineQueue("dbl_metoyards EQU DBL_METOYARDS");
		AddLineQueue("dbl_metomiles EQU DBL_METOMILES");

		AddLineQueue("dbl_cmtoinch EQU DBL_CMTOINCH");
		AddLineQueue("dbl_cmtofeet EQU DBL_CMTOFEET");
		AddLineQueue("dbl_cmtoyards EQU DBL_CMTOYARDS");
		AddLineQueue("dbl_cmtomiles EQU DBL_CMTOMILES");

		AddLineQueue("dbl_milltoinch EQU DBL_MILLTOINCH");
		AddLineQueue("dbl_milltofeet EQU DBL_MILLTOFEET");
		AddLineQueue("dbl_milltoyards EQU DBL_MILLTOYARDS");
		AddLineQueue("dbl_milltomiles EQU DBL_MILLTOMILES");

		AddLineQueue("dbl_inchtomill EQU DBL_INCHTOMILL");
		AddLineQueue("dbl_inchtocm EQU DBL_INCHTOCM");
		AddLineQueue("dbl_inchtome EQU DBL_INCHTOME");
		AddLineQueue("dbl_inchtokm EQU DBL_INCHTOKM");
		AddLineQueue("dbl_inchtofeet EQU DBL_INCHTOFEET");
		AddLineQueue("dbl_inchtoyards EQU DBL_INCHTOYARDS");
		AddLineQueue("dbl_inchtomiles EQU DBL_INCHTOMILES");

		AddLineQueue("dbl_feettomill EQU DBL_FEETTOMILL");
		AddLineQueue("dbl_feettocm EQU DBL_FEETTOCM");
		AddLineQueue("dbl_feettome EQU DBL_FEETTOME");
		AddLineQueue("dbl_feettokm EQU DBL_FEETTOKM");
		AddLineQueue("dbl_feettoinch EQU DBL_FEETTOINCH");
		AddLineQueue("dbl_feettoyards EQU DBL_FEETTOYARDS");
		AddLineQueue("dbl_feettomiles EQU DBL_FEETTOMILES");

		AddLineQueue("dbl_yardstomill EQU DBL_YARDSTOMILL");
		AddLineQueue("dbl_yardstocm EQU DBL_YARDSTOCM");
		AddLineQueue("dbl_yardstome EQU DBL_YARDSTOME");
		AddLineQueue("dbl_yardstokm EQU DBL_YARDSTOKM");
		AddLineQueue("dbl_yardstoinch EQU DBL_YARDSTOINCH");
		AddLineQueue("dbl_yardstofeet EQU DBL_YARDSTOFEET");
		AddLineQueue("dbl_yardstomiles EQU DBL_YARDSTOMILES");

		AddLineQueue("dbl_milestomill EQU DBL_MILESTOMILL");
		AddLineQueue("dbl_milestocm EQU DBL_MILESTOCM");
		AddLineQueue("dbl_milestome EQU DBL_MILESTOME");
		AddLineQueue("dbl_milestokm EQU DBL_MILESTOKM");
		AddLineQueue("dbl_milestoinch EQU DBL_MILESTOINCH");
		AddLineQueue("dbl_milestofeet EQU DBL_MILESTOFEET");
		AddLineQueue("dbl_milestoyards EQU DBL_MILESTOYARDS");

		AddLineQueue("dbl_kmphtomeps EQU DBL_KMPHTOMEPS");
		AddLineQueue("dbl_kmphtokmps EQU DBL_KMPHTOKMPS");
		AddLineQueue("dbl_kmphtomepm EQU DBL_KMPHTOMEPM");
		AddLineQueue("dbl_kmphtomilesph EQU DBL_KMPHTOMILESPH");
		AddLineQueue("dbl_kmphtomilesps EQU DBL_KMPHTOMILESPS");
		AddLineQueue("dbl_kmphtofootps EQU DBL_KMPHTOFOOTPS");
		AddLineQueue("dbl_kmphtofootpm EQU DBL_KMPHTOFOOTPM");

		AddLineQueue("dbl_kmpstomeps EQU DBL_KMPSTOMEPS");
		AddLineQueue("dbl_kmpstokmph EQU DBL_KMPSTOKMPH");
		AddLineQueue("dbl_kmpstomepm EQU DBL_KMPSTOMEPM");
		AddLineQueue("dbl_kmpstomilesph EQU DBL_KMPSTOMILESPH");
		AddLineQueue("dbl_kmpstomilesps EQU DBL_KMPSTOMILESPS");
		AddLineQueue("dbl_kmpstofootps EQU DBL_KMPSTOFOOTPS");
		AddLineQueue("dbl_kmpstofootpm EQU DBL_KMPSTOFOOTPM");

		AddLineQueue("dbl_mepstokmph EQU DBL_MEPSTOKMPH");
		AddLineQueue("dbl_mepstokmps EQU DBL_MEPSTOKMPS");
		AddLineQueue("dbl_mepstomepm EQU DBL_MEPSTOMEPM");
		AddLineQueue("dbl_mepstomilesph EQU DBL_MEPSTOMILESPH");
		AddLineQueue("dbl_mepstomilesps EQU DBL_MEPSTOMILESPS");
		AddLineQueue("dbl_mepstofootps EQU DBL_MEPSTOFOOTPS");
		AddLineQueue("dbl_mepstofootpm EQU DBL_MEPSTOFOOTPM");

		AddLineQueue("dbl_mepmtokmph EQU DBL_MEPMTOKMPH");
		AddLineQueue("dbl_mepmtokmps EQU DBL_MEPMTOKMPS");
		AddLineQueue("dbl_mepmtomeps EQU DBL_MEPMTOMEPS");
		AddLineQueue("dbl_mepmtomilesph EQU DBL_MEPMTOMILESPH");
		AddLineQueue("dbl_mepmtomilesps EQU DBL_MEPMTOMILESPS");
		AddLineQueue("dbl_mepmtofootps EQU DBL_MEPMTOFOOTPS");
		AddLineQueue("dbl_mepmtofootpm EQU DBL_MEPMTOFOOTPM");

		AddLineQueue("dbl_milesphtokmph EQU DBL_MILESPHTOKMPH");
		AddLineQueue("dbl_milesphtokmps EQU DBL_MILESPHTOKMPS");
		AddLineQueue("dbl_milesphtomeps EQU DBL_MILESPHTOMEPS");
		AddLineQueue("dbl_milesphtomepm EQU DBL_MILESPHTOMEPM");
		AddLineQueue("dbl_milesphtomilesps EQU DBL_MILESPHTOMILESPS");
		AddLineQueue("dbl_milesphtofootps EQU DBL_MILESPHTOFOOTPS");
		AddLineQueue("dbl_milesphtofootpm EQU DBL_MILESPHTOFOOTPM");

		AddLineQueue("dbl_milespstokmph EQU DBL_MILESPSTOKMPH");
		AddLineQueue("dbl_milespstokmps EQU DBL_MILESPSTOKMPS");
		AddLineQueue("dbl_milespstomeps EQU DBL_MILESPSTOMEPS");
		AddLineQueue("dbl_milespstomepm EQU DBL_MILESPSTOMEPM");
		AddLineQueue("dbl_milespstomilespm EQU DBL_MILESPSTOMILESPM");
		AddLineQueue("dbl_milespstofootps EQU DBL_MILESPSTOFOOTPS");
		AddLineQueue("dbl_milespstofootpm EQU DBL_MILESPSTOFOOTPM");

		AddLineQueue("dbl_footpstokmph EQU DBL_FOOTPSTOKMPH");
		AddLineQueue("dbl_footpstokmps EQU DBL_FOOTPSTOKMPS");
		AddLineQueue("dbl_footpstomeps EQU DBL_FOOTPSTOMEPS");
		AddLineQueue("dbl_footpstomepm EQU DBL_FOOTPSTOMEPM");
		AddLineQueue("dbl_footpstomilesph EQU DBL_FOOTPSTOMILESPH");
		AddLineQueue("dbl_footpstomilesps EQU DBL_FOOTPSTOMILESPS");
		AddLineQueue("dbl_footpstofootpm EQU DBL_FOOTPSTOFOOTPM");

		AddLineQueue("dbl_footpmtokmph EQU DBL_FOOTPMTOKMPH");
		AddLineQueue("dbl_footpmtokmps EQU DBL_FOOTPMTOKMPS");
		AddLineQueue("dbl_footpmtomeps EQU DBL_FOOTPMTOMEPS");
		AddLineQueue("dbl_footpmtomepm EQU DBL_FOOTPMTOMEPM");
		AddLineQueue("dbl_footpmtomilesph EQU DBL_FOOTPMTOMILESPH");
		AddLineQueue("dbl_footpmtomilesps EQU DBL_FOOTPMTOMILESPS");
		AddLineQueue("dbl_footpmtofootps EQU DBL_FOOTPMTOFOOTPS");

		AddLineQueue("dbl_soundspeedp50c EQU DBL_SOUNDSPEEDP50C");
		AddLineQueue("dbl_soundspeedp45c EQU DBL_SOUNDSPEEDP45C");
		AddLineQueue("dbl_soundspeedp40c EQU DBL_SOUNDSPEEDP40C");
		AddLineQueue("dbl_soundspeedp35c EQU DBL_SOUNDSPEEDP35C");
		AddLineQueue("dbl_soundspeedp30c EQU DBL_SOUNDSPEEDP30C");
		AddLineQueue("dbl_soundspeedp25c EQU DBL_SOUNDSPEEDP25C");
		AddLineQueue("dbl_soundspeedp20c EQU DBL_SOUNDSPEEDP20C");
		AddLineQueue("dbl_soundspeedp15c EQU DBL_SOUNDSPEEDP15C");
		AddLineQueue("dbl_soundspeedp10c EQU DBL_SOUNDSPEEDP10C");
		AddLineQueue("dbl_soundspeedp5c EQU DBL_SOUNDSPEEDP5C");
		AddLineQueue("dbl_soundspeed0c EQU DBL_SOUNDSPEED0C");
		AddLineQueue("dbl_soundspeedn5c EQU DBL_SOUNDSPEEDN5C");
		AddLineQueue("dbl_soundspeedn10c EQU DBL_SOUNDSPEEDN10C");
		AddLineQueue("dbl_soundspeedn15c EQU DBL_SOUNDSPEEDN15C");
		AddLineQueue("dbl_soundspeedn20c EQU DBL_SOUNDSPEEDN20C");
		AddLineQueue("dbl_soundspeedn25c EQU DBL_SOUNDSPEEDN25C");
		AddLineQueue("dbl_soundspeedn30c EQU DBL_SOUNDSPEEDN30C");
		AddLineQueue("dbl_soundspeedn35c EQU DBL_SOUNDSPEEDN35C");
		AddLineQueue("dbl_soundspeedn40c EQU DBL_SOUNDSPEEDN40C");
		AddLineQueue("dbl_soundspeedn45c EQU DBL_SOUNDSPEEDN45C");
		AddLineQueue("dbl_soundspeedn50c EQU DBL_SOUNDSPEEDN50C");

		AddLineQueue("dbl_schscale EQU DBL_SCHSCALE");
		AddLineQueue("dbl_thscale EQU DBL_THSCALE");

		AddLineQueue("dbl_expest1 EQU DBL_EXPEST1");
		AddLineQueue("dbl_expest2 EQU DBL_EXPEST2");
		AddLineQueue("dbl_expest3 EQU DBL_EXPEST3");
		AddLineQueue("dbl_expest4 EQU DBL_EXPEST4");
		AddLineQueue("dbl_expest5 EQU DBL_EXPEST5");
		AddLineQueue("dbl_expest6 EQU DBL_EXPEST6");
		AddLineQueue("dbl_expest7 EQU DBL_EXPEST7");
		AddLineQueue("dbl_logest0 EQU DBL_LOGEST0");
		AddLineQueue("dbl_logest1 EQU DBL_LOGEST1");
		AddLineQueue("dbl_logest2 EQU DBL_LOGEST2");
		AddLineQueue("dbl_logest3 EQU DBL_LOGEST3");
		AddLineQueue("dbl_logest4 EQU DBL_LOGEST4");
		AddLineQueue("dbl_logest5 EQU DBL_LOGEST5");
		AddLineQueue("dbl_logest6 EQU DBL_LOGEST6");
		AddLineQueue("dbl_logest7 EQU DBL_LOGEST7");

		/* EFLAGS %eax=00H, %ebx=00H */
		AddLineQueue("bit_cpuid EQU BIT_CPUID");		/*1 << 21*/

		/* %eax=00H, %ecx %ebx */
		AddLineQueue("bit_ntel EQU BIT_NTEL");			/*'GenuineIntel'*/
		AddLineQueue("bit_camd EQU BIT_CAMD");			/*'AuthenticAMD'*/

		/* %eax=00H, %ebx */
		AddLineQueue("bit_cent EQU BIT_CENT");			/*'CentaurHauls'*/
		AddLineQueue("bit_via EQU BIT_VIA");			/*'VIA VIA VIA'*/
		AddLineQueue("bit_cyri EQU BIT_CYRI");			/*'CyrixInstead'*/
		AddLineQueue("bit_nexg EQU BIT_NEXG");			/*'NexGenDriven'*/

		/* %eax=01H, %ecx */
		AddLineQueue("bit_sse3 EQU BIT_SSE3");			/*1 << 0*/
		AddLineQueue("bit_pclmulqdq EQU BIT_PCLMULQDQ");/*1 << 1*/
		AddLineQueue("bit_monitor EQU BIT_MONITOR");	/*1 << 3*/
		AddLineQueue("bit_ssse3 EQU BIT_SSSE3");		/*1 << 9*/
		AddLineQueue("bit_fma EQU BIT_FMA");			/*1 << 12*/
		AddLineQueue("bit_cmpxchg16b EQU BIT_CMPXCHG16B");/*1 << 13*/
		AddLineQueue("bit_sse41 EQU BIT_SSE41");		/*1 << 19*/
		AddLineQueue("bit_sse42 EQU BIT_SSE42");		/*1 << 20*/
		AddLineQueue("bit_movbe EQU BIT_MOVBE");		/*1 << 22*/
		AddLineQueue("bit_popcnt EQU BIT_POPCNT");		/*1 << 23*/
		AddLineQueue("bit_aes EQU BIT_AES");			/*1 << 25*/
		AddLineQueue("bit_xsave EQU BIT_XSAVE");		/*1 << 26*/
		AddLineQueue("bit_osxsave EQU BIT_OSXSAVE");	/*1 << 27*/
		AddLineQueue("bit_avx EQU BIT_AVX");			/*1 << 28*/
		AddLineQueue("bit_f16c EQU BIT_F16C");			/*1 << 29*/
		AddLineQueue("bit_rdrand EQU BIT_RDRAND");		/*1 << 30*/

		AddLineQueue("bit_avx_fma EQU BIT_AVX_FMA");	/*1 << 12 | 1 << 27 | 1 << 28*/
		AddLineQueue("bit_osxsave_avx EQU BIT_OSXSAVE_AVX");	/*1 << 27 | 1 << 28*/
		AddLineQueue("bit_avx_f16c EQU BIT_AVX_F16C");	/*1 << 27 | 1 << 28 | 1 << 29*/

		AddLineQueue("bit_sse3_aes EQU BIT_SSE3_AES");	/*1 << 0 | 1 << 25*/
		AddLineQueue("bit_ssse3_aes EQU BIT_SSSE3_AES");	/*1 << 9 | 1 << 25*/
		AddLineQueue("bit_sse41_aes EQU BIT_SSE41_AES");	/*1 << 19 | 1 << 25*/
		AddLineQueue("bit_sse42_aes EQU BIT_SSE42_AES");	/*1 << 20 | 1 << 25*/

		AddLineQueue("bit_sse3_pclmulqdq EQU BIT_SSE3_PCLMULQDQ");		/*1 << 1 | 1 << 1*/
		AddLineQueue("bit_ssse3_pclmulqdq EQU BIT_SSSE3_PCLMULQDQ");	/*1 << 1 | 1 << 9*/
		AddLineQueue("bit_sse41_pclmulqdq EQU BIT_SSE41_PCLMULQDQ");	/*1 << 1 | 1 << 19*/
		AddLineQueue("bit_sse42_pclmulqdq EQU BIT_SSE42_PCLMULQDQ");	/*1 << 1 | 1 << 20*/

		/* %eax=01H, %edx */
		AddLineQueue("bit_fpu EQU BIT_FPU");				/*1 << 0*/
		AddLineQueue("bit_tsc EQU BIT_TSC");				/*1 << 4*/
		AddLineQueue("bit_msr EQU BIT_MSR");				/*1 << 5*/
		AddLineQueue("bit_cmpxchg8b EQU BIT_CMPXCHG8B");	/*1 << 8*/
		AddLineQueue("bit_sep EQU BIT_SEP");				/*1 << 11*/
		AddLineQueue("bit_cmov EQU BIT_CMOV");			/*1 << 15*/
		AddLineQueue("bit_clfsh EQU BIT_CLFSH");		/*1 << 19*/
		AddLineQueue("bit_mmx EQU BIT_MMX");			/*1 << 23*/
		AddLineQueue("bit_fxsr EQU BIT_FXSR");			/*1 << 24*/
		AddLineQueue("bit_sse EQU BIT_SSE");			/*1 << 25*/
		AddLineQueue("bit_sse2 EQU BIT_SSE2");			/*1 << 26*/

		/* %eax=07H, %ebx */
		AddLineQueue("bit_fsgsbase EQU BIT_FSGSBASE");	/*1 << 0*/
		AddLineQueue("bit_sgx EQU BIT_SGX");			/*1 << 2*/
		AddLineQueue("bit_bmi1 EQU BIT_BMI1");			/*1 << 3*/
		AddLineQueue("bit_hle EQU BIT_HLE");			/*1 << 4*/
		AddLineQueue("bit_avx2 EQU BIT_AVX2");			/*1 << 5*/
		AddLineQueue("bit_smep EQU BIT_SMEP");			/*1 << 7*/
		AddLineQueue("bit_bmi2 EQU BIT_BMI2");			/*1 << 8*/
		AddLineQueue("bit_erms EQU BIT_ERMS");			/*1 << 9*/
		AddLineQueue("bit_invpcid EQU BIT_INVPCID");	/*1 << 10*/
		AddLineQueue("bit_rtm EQU BIT_RTM");			/*1 << 11*/
		AddLineQueue("bit_mpx EQU BIT_MPX");			/*1 << 14*/
		AddLineQueue("bit_avx512f EQU BIT_AVX512F");	/*1 << 16*/
		AddLineQueue("bit_avx512DQ EQU BIT_AVX512DQ");	/*1 << 17*/
		AddLineQueue("bit_rdseed EQU BIT_RDSEED");		/*1 << 18*/
		AddLineQueue("bit_adx EQU BIT_ADX");			/*1 << 19*/
		AddLineQueue("bit_smap EQU BIT_SMAP");			/*1 << 20*/
		AddLineQueue("bit_avx512_Ifma EQU BIT_AVX512_IFMA");/*1 << 21*/
		AddLineQueue("bit_clflushopt EQU BIT_CLFLUSHOPT");	/*1 << 23*/
		AddLineQueue("bit_clwb EQU BIT_CLWB");				/*1 << 24*/
		AddLineQueue("bit_avx512pf EQU BIT_AVX512PF");		/*1 << 26*/
		AddLineQueue("bit_avx512er EQU BIT_AVX512ER");		/*1 << 27*/
		AddLineQueue("bit_avx512cd EQU BIT_AVX512CD");		/*1 << 28*/
		AddLineQueue("bit_sha EQU BIT_SHA");				/*1 << 29*/
		AddLineQueue("bit_avx512bw EQU BIT_AVX512BW");		/*1 << 30*/
		AddLineQueue("bit_avx512vl EQU BIT_AVX512VL");		/*1 << 31*/

		AddLineQueue("bit_avx512f_dq EQU BIT_AVX512F_DQ");			/*1 << 16 | 1 << 17*/
		AddLineQueue("bit_avx512f_dq_vl EQU BIT_AVX512F_DQ_VL");	/*1 << 16 | 1 << 17 | 1 << 31*/
		AddLineQueue("bit_avx512f_ifma EQU BIT_AVX512F_IFMA");		/*1 << 16 | 1 << 21*/
		AddLineQueue("bit_avx512f_ifma_vl EQU BIT_AVX512F_IFMA_VL");/*1 << 16 | 1 << 21 | 1 << 31*/
		AddLineQueue("bit_avx512f_pf EQU BIT_AVX512F_PF");			/*1 << 16 | 1 << 26*/
		AddLineQueue("bit_avx512f_er EQU BIT_AVX512F_ER");			/*1 << 16 | 1 << 27*/
		AddLineQueue("bit_avx512f_cd EQU BIT_AVX512F_CD");			/*1 << 16 | 1 << 28*/
		AddLineQueue("bit_avx512f_cd_vl EQU BIT_AVX512F_CD_VL");	/*1 << 16 | 1 << 28 | 1 << 31*/
		AddLineQueue("bit_avx512f_bw EQU BIT_AVX512F_BW");			/*1 << 16 | 1 << 30*/
		AddLineQueue("bit_avx512f_bw_vl EQU BIT_AVX512F_BW_VL");	/*1 << 16 | 1 << 30 | 1 << 31*/
		AddLineQueue("bit_avx512f_vl EQU BIT_AVX512F_VL");			/*1 << 16 | 1 << 31*/

		/* %eax=07H, %ecx */
		AddLineQueue("bit_prefetchwt1 EQU BIT_PREFETCHWT1");	/*1 << 0*/
		AddLineQueue("bit_avx512_vbmi EQU BIT_AVX512_VBMI");	/*1 << 1*/
		AddLineQueue("bit_unip EQU BIT_UMIP");					/*1 << 2*/
		AddLineQueue("bit_pku EQU BIT_PKU");					/*1 << 3*/
		AddLineQueue("bit_ospke EQU BIT_OSPKE");				/*1 << 4*/
		AddLineQueue("bit_avx512_vbmi2 EQU BIT_AVX512_VBMI2");	/*1 << 6*/
		AddLineQueue("bit_gfni EQU BIT_GFNI");					/*1 << 8*/
		AddLineQueue("bit_vaes EQU BIT_VAES");					/*1 << 9*/
		AddLineQueue("bit_vpclmulqdq EQU BIT_VPCLMULQDQ");		/*1 << 10*/
		AddLineQueue("bit_avx512_vnni EQU BIT_AVX512_VNNI");		/*1 << 11*/
		AddLineQueue("bit_avx512_bitalg EQU BIT_AVX512_BITALG");	/*1 << 12*/
		AddLineQueue("bit_avx512_vpopcntdq EQU BIT_AVX512_VPOPCNTDQ");/*1 << 14*/
		AddLineQueue("bit_rdpid EQU BIT_RDPID");					/*1 << 22*/

		/* %eax=07H, %edx */
		AddLineQueue("bit_avx512_4vnniw EQU BIT_AVX512_4VNNIW");	/*1 << 2*/
		AddLineQueue("bit_avx512_4fmaps EQU BIT_AVX512_4FMAPS");	/*1 << 3*/

		/* %eax=80000001H, %ecx */
		AddLineQueue("bit_lahf EQU BIT_LAHF");				/*1 << 0*/
		AddLineQueue("bit_lzcnt EQU BIT_LZCNT");			/*1 << 5*/
		AddLineQueue("bit_abm EQU BIT_ABM");				/*1 << 5*/
		AddLineQueue("bit_sse4a EQU BIT_SSE4A");			/*1 << 6*/
		AddLineQueue("bit_prefetchw EQU BIT_PREFETCHW");	/*1 << 8*/
		AddLineQueue("bit_xop EQU BIT_XOP");				/*1 << 11*/
		AddLineQueue("bit_lwp EQU BIT_LWP");				/*1 << 15*/
		AddLineQueue("bit_fma4 EQU BIT_FMA4");				/*1 << 16*/
		AddLineQueue("bit_tbm EQU BIT_TBM");				/*1 << 21*/
		AddLineQueue("bit_mwaitx EQU BIT_MWAITX");			/*1 << 29*/

		/* %eax=80000001H, %edx */
		AddLineQueue("bit_syscall EQU BIT_SYSCALL");		/*1 << 11*/
		AddLineQueue("bit_mmxext EQU BIT_MMXEXT");			/*1 << 22*/
		AddLineQueue("bit_rdtscp EQU BIT_RDTSCP");			/*1 << 27*/
		AddLineQueue("bit_3dnowext EQU BIT_3DNOWEXT");		/*1 << 30*/
		AddLineQueue("bit_3dnow EQU BIT_3DNOW");			/*1 << 31*/
	
		/*
		 * Compare predicates for scalar and packed compare intrinsic functions
		 */
		/*No AVX*/
		AddLineQueue("cmpp_eq EQU CMPP_EQ");
		AddLineQueue("cmpp_lt EQU CMPP_LT");
		AddLineQueue("cmpp_le EQU CMPP_LE");
		AddLineQueue("cmpp_unord EQU CMPP_UNORD");
		AddLineQueue("cmpp_neq EQU CMPP_NEQ");
		AddLineQueue("cmpp_nlt EQU CMPP_NLT");
		AddLineQueue("cmpp_nle EQU CMPP_NLE");
		AddLineQueue("cmpp_ord EQU CMPP_ORD");

		/*With AVX*/
		AddLineQueue("cmp_eq_oq EQU CMP_EQ_OQ");		/* Equal (ordered, nonsignaling)               */
		AddLineQueue("cmp_lt_os EQU CMP_LT_OS");		/* Less-than (ordered, signaling)              */
		AddLineQueue("cmp_le_os EQU CMP_LE_OS");		/* Less-than-or-equal (ordered, signaling)     */
		AddLineQueue("cmp_unord_q EQU CMP_UNORD_Q");	/* Unordered (nonsignaling)                    */
		AddLineQueue("cmp_neq_uq EQU CMP_NEQ_UQ");		/* Not-equal (unordered, nonsignaling)         */
		AddLineQueue("cmp_nlt_us EQU CMP_NLT_US");		/* Not-less-than (unordered, signaling)        */
		AddLineQueue("cmp_nle_us EQU CMP_NLE_US");		/* Not-less-than-or-equal (unordered, signaling) */
		AddLineQueue("cmp_ord_q EQU CMP_ORD_Q");		/* Ordered (nonsignaling)                      */
		AddLineQueue("cmp_eq_uq EQU CMP_EQ_UQ");		/* Equal (unordered, non-signaling)            */
		AddLineQueue("cmp_nge_us EQU CMP_NGE_US");		/* Not-greater-than-or-equal (unordered, signaling) */
		AddLineQueue("cmp_ngt_us EQU CMP_NGT_US");		/* Not-greater-than (unordered, signaling)     */
		AddLineQueue("cmp_false_oq EQU CMP_FALSE_OQ");	/* False (ordered, nonsignaling)               */
		AddLineQueue("cmp_neq_oq EQU CMP_NEQ_OQ");		/* Not-equal (ordered, non-signaling)          */
		AddLineQueue("cmp_ge_os EQU CMP_GE_OS");		/* Greater-than-or-equal (ordered, signaling)  */
		AddLineQueue("cmp_gt_os EQU CMP_GT_OS");		/* Greater-than (ordered, signaling)           */
		AddLineQueue("cmp_true_uq EQU CMP_TRUE_UQ");	/* True (unordered, non-signaling)             */
		AddLineQueue("cmp_eq_os EQU CMP_EQ_OS");		/* Equal (ordered, signaling)                  */
		AddLineQueue("cmp_lt_oq EQU CMP_LT_OQ");		/* Less-than (ordered, nonsignaling)           */
		AddLineQueue("cmp_le_oq EQU CMP_LE_OQ");		/* Less-than-or-equal (ordered, nonsignaling)  */
		AddLineQueue("cmp_unord_s EQU CMP_UNORD_S");	/* Unordered (signaling)                       */
		AddLineQueue("cmp_neq_us EQU CMP_NEQ_US");		/* Not-equal (unordered, signaling)            */
		AddLineQueue("cmp_nlt_uq EQU CMP_NLT_UQ");		/* Not-less-than (unordered, nonsignaling)     */
		AddLineQueue("cmp_nle_uq EQU CMP_NLE_UQ");		/* Not-less-than-or-equal (unordered, nonsignaling) */
		AddLineQueue("cmp_ord_s EQU CMP_ORD_S");		/* Ordered (signaling)                         */
		AddLineQueue("cmp_eq_us EQU CMP_EQ_US");		/* Equal (unordered, signaling)                */
		AddLineQueue("cmp_nge_uq EQU CMP_NGE_UQ");		/* Not-greater-than-or-equal (unordered, nonsignaling) */
		AddLineQueue("cmp_ngt_uq EQU CMP_NGT_UQ");		/* Not-greater-than (unordered, nonsignaling)  */
		AddLineQueue("cmp_false_os EQU CMP_FALSE_OS");	/* False (ordered, signaling)                  */
		AddLineQueue("cmp_neq_os EQU CMP_NEQ_OS");		/* Not-equal (ordered, signaling)              */
		AddLineQueue("cmp_ge_oq EQU CMP_GE_OQ");		/* Greater-than-or-equal (ordered, nonsignaling) */
		AddLineQueue("cmp_gt_oq EQU CMP_GT_OQ");		/* Greater-than (ordered, nonsignaling)        */
		AddLineQueue("cmp_true_us EQU CMP_TRUE_US");	/* True (unordered, signaling)                 */

		/*AddLineQueue(" EQU ");
		AddLineQueue(" EQU ");
		AddLineQueue(" EQU ");
		AddLineQueue(" EQU ");
		AddLineQueue(" EQU ");
		AddLineQueue(" EQU ");
		AddLineQueue(" EQU ");
		AddLineQueue(" EQU ");
		AddLineQueue(" EQU ");
		AddLineQueue(" EQU ");
		AddLineQueue(" EQU ");
		AddLineQueue(" EQU ");*/

	}
}

/*
Create the built-in 64bit macro library
This is called once initially as the macros always exist
*/
void Initx86AutoMacros64(void)
{
	struct dsym *mac;
	uint_32 i = 0;
	uint_32 j = 0;
	uint_32 start_pos = 0;
	char  *srcLines[512]; // NB: 512 is the max number of lines of macro code per macro.

	   //						 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22  23  24 25 26 27 28  29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58  59 60 61  62   63   64
	uint_32 x86macroLen[] =		{9, 9, 4, 4, 4, 4, 4, 9, 9, 4, 4, 4, 4, 4, 9, 9, 4, 4, 4, 4, 7, 13, 13, 7, 7, 7, 7, 10, 5, 2, 2, 2, 2, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, /*10, 6, 6, 106, 137, 7*/}; // Count of individual lines of macro-body code.
	char *x86macCode[] = {
	/*1 ALIGNSIZE_T*/			"size_talignment TEXTEQU <>","IFDEF __X64__","size_talignment CATSTR size_talignment, <ALIGN 8>","ENDIF","IFDEF __X32__","size_talignment CATSTR size_talignment, <ALIGN 4>","ENDIF","size_talignment","ENDM",NULL,
	/*2 ALIGNPTR*/				"ptr_talignment TEXTEQU <>","IFDEF __X64__","ptr_talignment CATSTR ptr_talignment, <ALIGN 8>","ENDIF","IFDEF __X32__","ptr_talignment CATSTR ptr_talignment, <ALIGN 4>","ENDIF","ptr_talignment","ENDM",NULL,
	/*3 ALIGNMM*/				"mmalignment TEXTEQU <>","mmalignment CATSTR mmalignment, <ALIGN 8>","mmalignment","ENDM",NULL,
	/*4 ALIGNXMM*/				"xmmalignment TEXTEQU <>","xmmalignment CATSTR xmmalignment, <ALIGN 16>","xmmalignment","ENDM",NULL,
	/*5 ALIGNYMM*/				"ymmalignment TEXTEQU <>","ymmalignment CATSTR ymmalignment, <ALIGN 32>","ymmalignment","ENDM",NULL,
	/*6 ALIGNZMM*/				"zmmalignment TEXTEQU <>","zmmalignment CATSTR zmmalignment, <ALIGN 64>","zmmalignment","ENDM",NULL,
	/*7 ALIGNFIELD*/			"field_option_alignment TEXTEQU <>","field_option_alignment CATSTR field_option_alignment, <option fieldalign:AlignSize>","field_option_alignment","ENDM",NULL,
	/*8 ALIGNSIZE_TFIELD*/		"size_tfield_option_alignment TEXTEQU <>","IFDEF __X64__","size_tfield_option_alignment CATSTR size_tfield_option_alignment, <option fieldalign:8>","ENDIF","IFDEF __X32__","size_tfield_option_alignment CATSTR size_tfield_option_alignment, <option fieldalign:4>","ENDIF","size_tfield_option_alignment","ENDM",NULL,
	/*9 ALIGNPTRFIELD*/			"ptr_field_option_alignment TEXTEQU <>","IFDEF __X64__","ptr_field_option_alignment CATSTR ptr_field_option_alignment, <option fieldalign:8>","ENDIF","IFDEF __X32__","ptr_field_option_alignment CATSTR ptr_field_option_alignment, <option fieldalign:4>","ENDIF","ptr_field_option_alignment","ENDM",NULL,
	/*10 ALIGNMMFIELD*/			"mm_field_option_alignment TEXTEQU <>","mm_field_option_alignment CATSTR mm_field_option_alignment, <option fieldalign:MM_SIZE>","mm_field_option_alignment","ENDM",NULL,
	/*11 ALIGNXMMFIELD*/		"xmm_field_option_alignment TEXTEQU <>","xmm_field_option_alignment CATSTR xmm_field_option_alignment, <option fieldalign:XMM_SIZE>","xmm_field_option_alignment","ENDM",NULL,
	/*12 ALIGNYMMFIELD*/		"ymm_field_option_alignment TEXTEQU <>","ymm_field_option_alignment CATSTR ymm_field_option_alignment, <option fieldalign:YMM_SIZE>","ymm_field_option_alignment","ENDM",NULL,
	/*13 ALIGNZMMFIELD*/		"zmm_field_option_alignment TEXTEQU <>","zmm_field_option_alignment CATSTR zmm_field_option_alignment, <option fieldalign:ZMM_SIZE>","zmm_field_option_alignment","ENDM",NULL,
	/*14 ALIGNPROC*/			"proc_option_alignment TEXTEQU <>","proc_option_alignment CATSTR proc_option_alignment, <option procalign:AlignSize>","proc_option_alignment","ENDM",NULL,
	/*15 ALIGNSIZE_TPROC*/		"size_tproc_option_alignment TEXTEQU <>","IFDEF __X64__","size_tproc_option_alignment CATSTR size_tproc_option_alignment, <option procalign:8>","ENDIF","IFDEF __X32__","size_tproc_option_alignment CATSTR size_tproc_option_alignment, <option procalign:4>","ENDIF","size_tproc_option_alignment","ENDM",NULL,
	/*16 ALIGNPTRPROC*/			"ptr_proc_option_alignment TEXTEQU <>","IFDEF __X64__","ptr_proc_option_alignment CATSTR ptr_proc_option_alignment, <option procalign:8>","ENDIF","IFDEF __X32__","ptr_proc_option_alignment CATSTR ptr_proc_option_alignment, <option procalign:4>","ENDIF","ptr_proc_option_alignment","ENDM",NULL,
	/*17 ALIGNMMPROC*/			"mm_proc_option_alignment TEXTEQU <>","mm_proc_option_alignment CATSTR mm_proc_option_alignment, <option procalign:MM_SIZE>","mm_proc_option_alignment","ENDM",NULL,
	/*18 ALIGNXMMPROC*/			"xmm_proc_option_alignment TEXTEQU <>","xmm_proc_option_alignment CATSTR xmm_proc_option_alignment, <option procalign:XMM_SIZE>","xmm_proc_option_alignment","ENDM",NULL,
	/*19 ALIGNYMMPROC*/			"ymm_proc_option_alignment TEXTEQU <>","ymm_proc_option_alignment CATSTR ymm_proc_option_alignment, <option procalign:YMM_SIZE>","ymm_proc_option_alignment","ENDM",NULL,
	/*20 ALIGNZMMPROC*/			"zmm_proc_option_alignment TEXTEQU <>","zmm_proc_option_alignment CATSTR zmm_proc_option_alignment, <option procalign:ZMM_SIZE>","zmm_proc_option_alignment","ENDM",NULL,
	/*21 ALIGNFIELDPROC*/		"pfield_option_alignment TEXTEQU <>","fproc_option_alignment TEXTEQU <>","pfield_option_alignment CATSTR pfield_option_alignment, <option fieldalign:AlignSize>","fproc_option_alignment CATSTR fproc_option_alignment, <option procalign:AlignSize>","pfield_option_alignment","fproc_option_alignment","ENDM",NULL,
	/*22 ALIGNSIZE_TFIELDPROC*/	"size_tpfield_option_alignment TEXTEQU <>","size_tfproc_option_alignment TEXTEQU <>","IFDEF __X64__","size_tpfield_option_alignment CATSTR size_tpfield_option_alignment, <option fieldalign:8>","size_tfproc_option_alignment CATSTR size_tfproc_option_alignment, <option procalign:8>","ENDIF","IFDEF __X32__","size_tpfield_option_alignment CATSTR size_tpfield_option_alignment, <option fieldalign:4>","size_tfproc_option_alignment CATSTR size_tfproc_option_alignment, <option procalign:4>","ENDIF","size_tpfield_option_alignment","size_tfproc_option_alignment","ENDM",NULL,
	/*23 ALIGNPTRFIELDPROC*/	"ptr_pfield_option_alignment TEXTEQU <>","ptr_fproc_option_alignment TEXTEQU <>","IFDEF __X64__","ptr_pfield_option_alignment CATSTR ptr_pfield_option_alignment, <option fieldalign:8>","ptr_fproc_option_alignment CATSTR ptr_fproc_option_alignment, <option procalign:8>","ENDIF","IFDEF __X32__","ptr_pfield_option_alignment CATSTR ptr_pfield_option_alignment, <option fieldalign:4>","ptr_fproc_option_alignment CATSTR ptr_fproc_option_alignment, <option procalign:4>","ENDIF","ptr_pfield_option_alignment","ptr_fproc_option_alignment","ENDM",NULL,
	/*24 ALIGNMMFIELDPROC*/		"mm_pfield_option_alignment TEXTEQU <>","mm_fproc_option_alignment TEXTEQU <>","mm_pfield_option_alignment CATSTR mm_pfield_option_alignment, <option fieldalign:MM_SIZE>","mm_fproc_option_alignment CATSTR mm_fproc_option_alignment, <option procalign:MM_SIZE>","mm_pfield_option_alignment","mm_fproc_option_alignment","ENDM",NULL,
	/*25 ALIGNXMMFIELDPROC*/	"xmm_pfield_option_alignment TEXTEQU <>","xmm_fproc_option_alignment TEXTEQU <>","xmm_pfield_option_alignment CATSTR xmm_pfield_option_alignment, <option fieldalign:XMM_SIZE>","xmm_fproc_option_alignment CATSTR xmm_fproc_option_alignment, <option procalign:XMM_SIZE>","xmm_pfield_option_alignment","xmm_fproc_option_alignment","ENDM",NULL,
	/*26 ALIGNYMMFIELDPROC*/	"ymm_pfield_option_alignment TEXTEQU <>","ymm_fproc_option_alignment TEXTEQU <>","ymm_pfield_option_alignment CATSTR ymm_pfield_option_alignment, <option fieldalign:YMM_SIZE>","ymm_fproc_option_alignment CATSTR ymm_fproc_option_alignment, <option procalign:YMM_SIZE>","ymm_pfield_option_alignment","ymm_fproc_option_alignment","ENDM",NULL,
	/*27 ALIGNZMMFIELDPROC*/	"zmm_pfield_option_alignment TEXTEQU <>","zmm_fproc_option_alignment TEXTEQU <>","zmm_pfield_option_alignment CATSTR zmm_pfield_option_alignment, <option fieldalign:ZMM_SIZE>","zmm_fproc_option_alignment CATSTR zmm_fproc_option_alignment, <option procalign:ZMM_SIZE>","zmm_pfield_option_alignment","zmm_fproc_option_alignment","ENDM",NULL,
	/*28 FUNCSTART*/			"_curfunctionName_ TEXTEQU <functionName>","fnexproto TEXTEQU <>","fnexproto CATSTR fnexproto, <&functionName&>","fnexproto CATSTR fnexproto, < PROTO >, <&callconvType&>, < >, <(&retType&)>, < >, <&args&>","fnexproc TEXTEQU <>","fnexproc CATSTR fnexproc, <&functionName&>","fnexproc CATSTR fnexproc, < PROC >, <&callconvType&>, < >, <(&retType&)>, < >, <FRAME>, < >, <&usesStr&>, < >, <&args&>","fnexproto","fnexproc","ENDM",NULL,
	/*29 FUNCEND*/				"fnexfuncend TEXTEQU <>","fnexfuncend CATSTR fnexfuncend, _curfunctionName_","fnexfuncend CATSTR fnexfuncend, < ENDP>","fnexfuncend","ENDM",NULL,
	/*30 SHUFFLE4*/				"EXITM %((V3 shl 6) or (V2 shl 4) or (V1 shl 2) or (V0))","ENDM",NULL,
	/*31 SHUFFLER4*/			"EXITM %((V0) or (V1 shl 2) or (V2 shl 4) or (V3 shl 6))","ENDM",NULL,
	/*32 SHUFFLE2*/				"EXITM %((V1 shl 1) or (V0))","ENDM",NULL,
	/*33 SHUFFLER2*/			"EXITM %((V0) or (V1 shl 1))","ENDM",NULL,
	/*34 V64CI*/				"mm64fnex TEXTEQU <>","mm64fnex CATSTR mm64fnex, <&functionName&>","public mm64fnex","mm64fnex CATSTR mm64fnex, < vectorType>,  < { V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1 } >","mm64fnex","ENDM",NULL,
	/*35 V64CI64*/				"mm64fnex64 TEXTEQU <>","mm64fnex64 CATSTR mm64fnex64, <&functionName&>","public mm64fnex64","mm64fnex64 CATSTR mm64fnex64, < vectorType>, < { V1, V2, V3, V4, V5, V6, V7, V8, V9, V10, V11, V12, V13, V14, V15, V16, V17, V18, V19, V20, V21, V22, V23, V24, V25, V26, V27, V28, V29, V30, V31, V32, V33, V34, V35, V36, V37, V38, V39, V40, V41, V42, V43, V44, V45, V46, V47, V48, V49, V50, V51, V52, V53, V54, V55, V56, V57, V58, V59, V60, V61, V62, V63, V64 } >","mm64fnex64","ENDM",NULL,
	/*36 V32CI*/				"mm32fnex TEXTEQU <>","mm32fnex CATSTR mm32fnex, <&functionName&>","public mm32fnex","mm32fnex CATSTR mm32fnex, < vectorType>,  < { V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1 } >","mm32fnex","ENDM",NULL,
	/*37 V32CI32*/				"mm32fnex32 TEXTEQU <>","mm32fnex32 CATSTR mm32fnex32, <&functionName&>","public mm32fnex32","mm32fnex32 CATSTR mm32fnex32, < vectorType>, < { V1, V2, V3, V4, V5, V6, V7, V8, V9, V10, V11, V12, V13, V14, V15, V16, V17, V18, V19, V20, V21, V22, V23, V24, V25, V26, V27, V28, V29, V30, V31, V32 } >","mm32fnex32","ENDM",NULL,
	/*38 V16CI*/				"mm16fnex TEXTEQU <>","mm16fnex CATSTR mm16fnex, <&functionName&>","public mm16fnex","mm16fnex CATSTR mm16fnex, < vectorType>,  < { V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1 } >","mm16fnex","ENDM",NULL,
	/*39 V16CI16*/				"mm16fnex16 TEXTEQU <>","mm16fnex16 CATSTR mm16fnex16, <&functionName&>","public mm16fnex16","mm16fnex16 CATSTR mm16fnex16, < vectorType>, < { V1, V2, V3, V4, V5, V6, V7, V8, V9, V10, V11, V12, V13, V14, V15, V16 } >","mm16fnex16","ENDM",NULL,
	/*40 V8CI*/					"mm8fnex TEXTEQU <>","mm8fnex CATSTR mm8fnex, <&functionName&>","public mm8fnex","mm8fnex CATSTR mm8fnex, < vectorType>,  < { V1, V1, V1, V1, V1, V1, V1, V1 } >","mm8fnex","ENDM",NULL,
	/*41 V8CI8*/				"mm8fnex8 TEXTEQU <>","mm8fnex8 CATSTR mm8fnex8, <&functionName&>","public mm8fnex8","mm8fnex8 CATSTR mm8fnex8, < vectorType>, < { V1, V2, V3, V4, V5, V6, V7, V8 } >","mm8fnex8","ENDM",NULL,
	/*42 V4CI*/					"mm4fnex TEXTEQU <>","mm4fnex CATSTR mm4fnex, <&functionName&>","public mm4fnex","mm4fnex CATSTR mm4fnex, < vectorType>,  < { V1, V1, V1, V1 } >","mm4fnex","ENDM",NULL,
	/*43 V4CI4*/				"mm4fnex4 TEXTEQU <>","mm4fnex4 CATSTR mm4fnex4, <&functionName&>","public mm4fnex4","mm4fnex4 CATSTR mm4fnex4, < vectorType>, < { V1, V2, V3, V4 } >","mm4fnex4","ENDM",NULL,
	/*44 V2CI*/					"mm2fnex TEXTEQU <>","mm2fnex CATSTR mm2fnex, <&functionName&>","public mm2fnex","mm2fnex CATSTR mm2fnex, < vectorType>,  < { V1, V1 } >","mm2fnex","ENDM",NULL,
	/*45 V2CI2*/				"mm2fnex2 TEXTEQU <>","mm2fnex2 CATSTR mm2fnex2, <&functionName&>","public mm2fnex2","mm2fnex2 CATSTR mm2fnex2, < vectorType>, < { V1, V2 } >","mm2fnex2","ENDM",NULL,
	/*46 VV64CI*/				"vmm64fnex TEXTEQU <>","vmm64fnex CATSTR vmm64fnex, <&functionName&>","public vmm64fnex","vmm64fnex CATSTR vmm64fnex, < vectorType>,  < { <V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1> } >","vmm64fnex","ENDM",NULL,
	/*47 VV64CI64*/				"vmm64fnex64 TEXTEQU <>","vmm64fnex64 CATSTR vmm64fnex64, <&functionName&>","public vmm64fnex64","vmm64fnex64 CATSTR vmm64fnex64, < vectorType>, < { <V1, V2, V3, V4, V5, V6, V7, V8, V9, V10, V11, V12, V13, V14, V15, V16, V17, V18, V19, V20, V21, V22, V23, V24, V25, V26, V27, V28, V29, V30, V31, V32, V33, V34, V35, V36, V37, V38, V39, V40, V41, V42, V43, V44, V45, V46, V47, V48, V49, V50, V51, V52, V53, V54, V55, V56, V57, V58, V59, V60, V61, V62, V63, V64> } >","vmm64fnex64","ENDM",NULL,
	/*48 VV32CI*/				"vmm32fnex TEXTEQU <>","vmm32fnex CATSTR vmm32fnex, <&functionName&>","public vmm32fnex","vmm32fnex CATSTR vmm32fnex, < vectorType>,  < { <V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1> } >","vmm32fnex","ENDM",NULL,
	/*49 VV32CI32*/				"mm32fnex32 TEXTEQU <>","mm32fnex32 CATSTR mm32fnex32, <&functionName&>","public mm32fnex32","mm32fnex32 CATSTR mm32fnex32, < vectorType>, < { <V1, V2, V3, V4, V5, V6, V7, V8, V9, V10, V11, V12, V13, V14, V15, V16, V17, V18, V19, V20, V21, V22, V23, V24, V25, V26, V27, V28, V29, V30, V31, V32> } >","mm32fnex32","ENDM",NULL,
	/*50 VV16CI*/				"vmm16fnex TEXTEQU <>","vmm16fnex CATSTR vmm16fnex, <&functionName&>","public vmm16fnex","vmm16fnex CATSTR vmm16fnex, < vectorType>,  < { <V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1, V1> } >","vmm16fnex","ENDM",NULL,
	/*51 VV16CI16*/				"mm16fnex16 TEXTEQU <>","mm16fnex16 CATSTR mm16fnex16, <&functionName&>","public mm16fnex16","mm16fnex16 CATSTR mm16fnex16, < vectorType>, < { <V1, V2, V3, V4, V5, V6, V7, V8, V9, V10, V11, V12, V13, V14, V15, V16> } >","mm16fnex16","ENDM",NULL,
	/*52 VV8CI*/				"vmm8fnex TEXTEQU <>","vmm8fnex CATSTR vmm8fnex, <&functionName&>","public vmm8fnex","vmm8fnex CATSTR vmm8fnex, < vectorType>,  < { <V1, V1, V1, V1, V1, V1, V1, V1> } >","vmm8fnex","ENDM",NULL,
	/*53 VV8CI8*/				"mm8fnex8 TEXTEQU <>","mm8fnex8 CATSTR mm8fnex8, <&functionName&>","public mm8fnex8","mm8fnex8 CATSTR mm8fnex8, < vectorType>, < { <V1, V2, V3, V4, V5, V6, V7, V8> } >","mm8fnex8","ENDM",NULL,
	/*54 VV4CI*/				"vmm4fnex TEXTEQU <>","vmm4fnex CATSTR vmm4fnex, <&functionName&>","public vmm4fnex","vmm4fnex CATSTR vmm4fnex, < vectorType>,  < { <V1, V1, V1, V1> } >","vmm4fnex","ENDM",NULL,
	/*55 VV4CI4*/				"vmm4fnex4 TEXTEQU <>","vmm4fnex4 CATSTR vmm4fnex4, <&functionName&>","public vmm4fnex4","vmm4fnex4 CATSTR vmm4fnex4, < vectorType>, < { <V1, V2, V3, V4> } >","vmm4fnex4","ENDM",NULL,
	/*56 VV2CI*/				"vmm2fnex TEXTEQU <>","vmm2fnex CATSTR vmm2fnex, <&functionName&>","public vmm2fnex","vmm2fnex CATSTR vmm2fnex, < vectorType>,  < { <V1, V1> } >","vmm2fnex","ENDM",NULL,
	/*57 VV2CI2*/				"vmm2fnex2 TEXTEQU <>","vmm2fnex2 CATSTR vmm2fnex2, <&functionName&>","public vmm2fnex2","vmm2fnex2 CATSTR vmm2fnex2, < vectorType>, < { <V1, V2> } >","vmm2fnex2","ENDM",NULL,
	/*58 V1CI*/					"mm1fnex TEXTEQU <>","mm1fnex CATSTR mm1fnex, <&functionName&>","public mm1fnex","mm1fnex CATSTR mm1fnex, < vectorType>,  < V1 >","mm1fnex","ENDM",NULL/*,*/
	/* */			/*"","","","","","","","",NULL,*/
	};

	/* Compile Macros */
	for (i = 0; i < X86MACRO_COUNT64; i++)
	{
		for (j = 0; j < x86macroLen[i]; j++)
		{
			srcLines[j] = (char *)malloc(MAX_LINE_LEN);
			if (srcLines[j])
				strcpy(srcLines[j], x86macCode[(start_pos + j)]);
		}
		mac = CreateMacro(x86macName64[i]);
		ModuleInfo.token_count = Tokenize(x86macDef64[i], 0, ModuleInfo.tokenarray, 0);
		StoreAutoMacro(mac, 2, ModuleInfo.tokenarray, TRUE, srcLines, 0, x86macroLen[i]);
		start_pos += x86macroLen[i] + 1;
	}
}
#endif