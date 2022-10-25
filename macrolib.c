
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

#define MACRO_COUNT64 69
#define MACRO_COUNT32 36

/* MACRO names  */
char *macName64[] = {
  "NOTMASK128", "GETMASK128", "REGS15STORAGE", "MOV64", "MOV128", "MOVXMMR128","SLXMMR","SHIFTLEFT128","SRXMMR","SHIFTRIGHT128","MEMALLOC", "MEMFREE", "CSTR", "WSTR", "FP4", "FP8", "FP10", "LOADSS", "LOADSD", "LOADPS", "ALIGNADDR", "RV", "REPARG", "EXPAND_PREFIX", "_ARRAY", "_DELETEARRAY", "OINTERFACE", "ENDOINTERFACE", "CVIRTUAL", "CLASS", "ENDCLASS", "CMETHOD", "METHOD", "STATICMETHOD", "VECMETHOD", "STATICVECMETHOD", "ENDMETHOD", "_DECLARE", "_STATICREF", "_NEW", "_RBXNEW", "_ITEM", "_ITEMR", "_INVOKE", "_I", "_STATIC", "_DELETE", "_VINVOKE", "_V", "CSTATIC", "LOADMSS", "LOADMSD", "UINVOKE", "ASFLOAT", "ASDOUBLE", "R4P", "R8P", "arginvoke", "COMINTERFACE", "ENDCOMINTERFACE", "ENDMETHODS", "_DEREF", "_DEREFI", "_SINVOKE", "RAWINTERFACE", "ENDRAWINTERFACE", "_DEREFR", "_DEREFRR","STDFUNC"
};
char *macName32[] = {
 "NOTMASK128", "GETMASK128", "MOV64", "MOV128", "MOVXMMR128","SLXMMR","SHIFTLEFT128","SRXMMR","SHIFTRIGHT128","MEMALLOC","MEMFREE","CSTR","WSTR","FP4","FP8","FP10","LOADSS","LOADPS","ALIGNADDR", "RV", "REPARG", "EXPAND_PREFIX", "LOADMSS", "LOADMSD", "UINVOKE", "ASFLOAT", "ASDOUBLE", "R4P", "R8P", "arginvoke", "COMINTERFACE", "ENDCOMINTERFACE", "_VINVOKE", "_V", "CVIRTUAL", "ENDMETHODS"
};

/* MACRO definitions */
char *macDef64[] = {
	"NOTMASK128 MACRO reg:REQ, field:REQ",
	"GETMASK128 MACRO reg:REQ, field:REQ",
	"REGS15STORAGE MACRO",
	"MOV64 MACRO dst:REQ, imm:REQ",
	"MOV128 MACRO dst:REQ, immLo:REQ,immHi:REQ",
	"MOVXMMR128 MACRO dst:REQ, immLo:REQ,immHi:REQ", 
	"SLXMMR MACRO xmm128:REQ,cnt:REQ",  
    "SHIFTLEFT128 MACRO mmr:REQ,cnt:REQ",  
	"SRXMMR MACRO xmm128:REQ,cnt:REQ",
	"SHIFTRIGHT128 MACRO mmr:REQ,cnt:REQ",
	"MEMALLOC macro aSize:REQ",
	"MEMFREE macro memPtr:REQ",
	"CSTR macro Text:VARARG",
	"WSTR macro Text:VARARG",
	"FP4 macro value:REQ",
	"FP8 macro value:REQ",
	"FP10 macro value:REQ",
	"LOADSS MACRO reg, val",
	"LOADSD MACRO reg, val",
	"LOADPS MACRO reg, val",
	"ALIGNADDR MACRO reg, number",
	"RV MACRO FuncName:REQ, args:VARARG",
	"REPARG MACRO arg",
	"EXPAND_PREFIX MACRO txtitm",
	"_ARRAY MACRO arrType:REQ,sizeArr:REQ",
	"_DELETEARRAY MACRO arrPtr:REQ",
	"OINTERFACE MACRO CName : REQ",
	"ENDOINTERFACE MACRO",
	"CVIRTUAL MACRO method:REQ, retType:REQ, protoDef:VARARG",
	"CLASS MACRO CName : REQ",
	"ENDCLASS MACRO",
	"CMETHOD MACRO method : REQ",
	"METHOD MACRO className:REQ, method:REQ, retType:=<dword>, usesStr:=<USES rbx rsi rdi>, args:VARARG",
	"STATICMETHOD MACRO className:REQ, method:REQ, retType:=<dword>, usesStr:=<USES rbx rsi rdi>, args:VARARG",
	"VECMETHOD MACRO className:REQ, method:REQ, retType:=<dword>, usesStr:=<USES rbx rsi rdi>, args:VARARG",
	"STATICVECMETHOD MACRO className:REQ, method:REQ, retType:=<dword>, usesStr:=<USES rbx rsi rdi>, args:VARARG",
	"ENDMETHOD MACRO",
	"_DECLARE MACRO varName : REQ, typeName : VARARG",
	"_STATICREF MACRO reg:REQ, classType:REQ",
	"_NEW MACRO className : REQ, ctorArgs : VARARG",
	"_RBXNEW MACRO className : REQ, ctorArgs : VARARG",
	"_ITEM MACRO objPtr : REQ, idx : REQ",
	"_ITEMR MACRO objPtr : REQ, idx : REQ",
	"_INVOKE MACRO className : REQ, method : REQ, objPtr : REQ, args : VARARG",
	"_I MACRO className : REQ, method : REQ, objPtr : REQ, args : VARARG",
	"_STATIC MACRO className:REQ, method:REQ, args:VARARG",
	"_DELETE MACRO objPtr : REQ",
	"_VINVOKE MACRO pInterface : REQ, Interface : REQ, Function : REQ, args : VARARG",
	"_V MACRO pInterface : REQ, Interface : REQ, Function : REQ, args : VARARG",
	"CSTATIC MACRO method : REQ",
	"LOADMSS MACRO reg, value",
	"LOADMSD MACRO reg, value",
	"UINVOKE MACRO func:REQ, args:VARARG",
	"ASFLOAT MACRO reg:REQ",
	"ASDOUBLE MACRO reg:REQ",
	"R4P MACRO reg:REQ",
	"R8P MACRO reg:REQ",
	"arginvoke MACRO argNo:REQ, invCount:REQ, func:REQ, args:VARARG",
	"COMINTERFACE MACRO CName : REQ",
	"ENDCOMINTERFACE MACRO",
	"ENDMETHODS MACRO",
	"_DEREF MACRO itype:REQ, proc:REQ, argCount:REQ, argsAndRefs:VARARG",
	"_DEREFI MACRO itype:REQ, proc:REQ, argCount:REQ, argsAndRefs:VARARG",
	"_SINVOKE MACRO className:REQ, method:REQ, args:VARARG",
	"RAWINTERFACE MACRO CName:REQ",
	"ENDRAWINTERFACE MACRO",
	"_DEREFR MACRO dref:REQ, itype:REQ, proc:REQ, argCount:REQ, argsAndRefs:VARARG",
	"_DEREFRR MACRO dref:REQ, itype:REQ, proc:REQ, argCount:REQ, argsAndRefs:VARARG",
	"STDFUNC MACRO method:REQ, retType:REQ, protoDef:VARARG",
};
char *macDef32[] = {
	"NOTMASK128 MACRO reg:REQ, field:REQ",
	"GETMASK128 MACRO reg:REQ, field:REQ",
	"MOV64 MACRO dst:REQ, imm:REQ",
	"MOV128 MACRO dst:REQ, immLo:REQ,immHi:REQ",
	"MOVXMMR128 MACRO dst:REQ, immLo:REQ,immHi:REQ", 
	"SLXMMR MACRO xmm128:REQ,cnt:REQ",  
	"SHIFTLEFT128 MACRO mmr:REQ,cnt:REQ",  
	"SRXMMR MACRO xmm128:REQ,cnt:REQ",
	"SHIFTRIGHT128 MACRO mmr:REQ,cnt:REQ",
	"MEMALLOC macro aSize:REQ",
	"MEMFREE macro memPtr:REQ",
	"CSTR macro Text:VARARG",
	"WSTR macro Text:VARARG",
	"FP4 macro value:REQ",
	"FP8 macro value:REQ",
	"FP10 macro value:REQ",
	"LOADSS MACRO reg, val",
	"LOADPS MACRO reg, val",
	"ALIGNADDR MACRO reg, number",
	"RV MACRO FuncName:REQ, args:VARARG",
	"REPARG MACRO arg",
	"EXPAND_PREFIX MACRO txtitm",
	"LOADMSS MACRO reg, value",
	"LOADMSD MACRO reg, value",
	"UINVOKE MACRO func:REQ, args:VARARG",
	"ASFLOAT MACRO reg:REQ",
	"ASDOUBLE MACRO reg:REQ",
	"R4P MACRO reg:REQ",
	"R8P MACRO reg:REQ",
	"arginvoke MACRO argNo:REQ, invCount:REQ, func:REQ, args:VARARG",
	"COMINTERFACE MACRO CName : REQ",
	"ENDCOMINTERFACE MACRO",
	"_VINVOKE MACRO pInterface:REQ, Interface:REQ, Function:REQ, args:VARARG",
	"_V MACRO pInterface:REQ, Interface:REQ, Function:REQ, args:VARARG",
	"CVIRTUAL MACRO method:REQ, retType:REQ, protoDef:VARARG",
	"ENDMETHODS MACRO"
};

void CreateMacroLibCases64(void)
{
	/* Create case alternative names for macrolib functions */
	if (ModuleInfo.case_sensitive && !ModuleInfo.convert_uppercase)
	{
		AddLineQueue("uinvoke EQU UINVOKE");
		AddLineQueue("Uinvoke EQU UINVOKE");
		AddLineQueue("asfloat EQU ASFLOAT");
		AddLineQueue("asdouble EQU ASDOUBLE");
		AddLineQueue("r4p EQU R4P");
		AddLineQueue("r8p EQU R8P");
		AddLineQueue("cstr EQU CSTR");
		AddLineQueue("CStr EQU CSTR");
		AddLineQueue("wstr EQU WSTR");
		AddLineQueue("WStr EQU WSTR");
		AddLineQueue("alignaddr EQU ALIGNADDR");
		AddLineQueue("define EQU DEFINE");
		AddLineQueue("Define EQU DEFINE");
		AddLineQueue("mov64 EQU MOV64");
		AddLineQueue("mov128 EQU MOV128");
		AddLineQueue("movxmmr128 EQU MOVXMMR128");
		AddLineQueue("slxmmr EQU SLXMMR");
		AddLineQueue("shiftleft128 EQU SHIFTLEFT128");
		AddLineQueue("srxmmr EQU SRXMMR");
		AddLineQueue("shiftright128 EQU SHIFTRIGHT128");
		AddLineQueue("notmask128 EQU NOTMASK128");
		AddLineQueue("getmask128 EQU GETMASK128");
	}
}

void CreateMacroLibCases32(void)
{
	/* Create case alternative names for macrolib functions */
	if (ModuleInfo.case_sensitive && !ModuleInfo.convert_uppercase)
	{
		AddLineQueue("uinvoke EQU UINVOKE");
		AddLineQueue("Uinvoke EQU UINVOKE");
		AddLineQueue("asfloat EQU ASFLOAT");
		AddLineQueue("asdouble EQU ASDOUBLE");
		AddLineQueue("r4p EQU R4P");
		AddLineQueue("r8p EQU R8P");
		AddLineQueue("cstr EQU CSTR");
		AddLineQueue("CStr EQU CSTR");
		AddLineQueue("wstr EQU WSTR");
		AddLineQueue("WStr EQU WSTR");
		AddLineQueue("alignaddr EQU ALIGNADDR");
		AddLineQueue("define EQU DEFINE");
		AddLineQueue("Define EQU DEFINE");
		AddLineQueue("mov64 EQU MOV64");
		AddLineQueue("mov128 EQU MOV128");
		AddLineQueue("movxmmr128 EQU MOVXMMR128");
		AddLineQueue("slxmmr EQU SLXMMR");
		AddLineQueue("shiftleft128 EQU SHIFTLEFT128");
		AddLineQueue("srxmmr EQU SRXMMR");
		AddLineQueue("shiftright128 EQU SHIFTRIGHT128");
		AddLineQueue("notmask128 EQU NOTMASK128");
		AddLineQueue("getmask128 EQU GETMASK128");
	}
}

/* 
Create the built-in 64bit macro library 
This is called once initially as the macros always exist
*/
void InitAutoMacros64(void)
{
	struct dsym *mac;
	uint_32 i = 0;
	uint_32 j = 0;
	uint_32 start_pos = 0;
	char  *srcLines[512]; // NB: 512 is the max number of lines of macro code per macro.  

	//                    1   2   3   4  5  6  7   8   9   10  11 12 13  14 15 16 17 18 19 20  21 22 23  24  25  26 27 28  29  30  31  32 33  34  35  36  37  38 39 40  41  42 43 44  45  46  47  48  49  50 51  52  53  54 55 56 57 58   59  60 61 62   63   64  65  66 67 68 69
	uint_32 macroLen[] = {17, 11, 29, 3, 3, 8, 37, 33, 37, 33, 7, 6, 10, 6, 7, 7, 7, 8, 8, 10, 3, 7, 11, 19, 10, 2, 10, 2, 18,  9, 14, 6, 39, 39, 39, 39, 12, 5, 2, 20, 21, 2, 2, 11, 38, 38, 11, 45, 91, 6, 10, 10, 37, 1, 1, 1, 1, 256, 10, 6, 6, 106, 137, 11, 7 , 2, 9, 4, 18 }; // Count of individual lines of macro-body code.
	char *macCode[] = {
/*1 NOTMASK128*/		"IFNDEF GMASK",".data","GMASK OWORD 0","ENDIF","IFNDEF NOTMASK",".data","NOTMASK OWORD -1","ENDIF",".code","IF @Arch EQ 1","movups reg, MASK field","pxor reg, NOTMASK","ELSE","vmovups reg, MASK field","vpxor reg, reg, NOTMASK","ENDIF","ENDM",NULL,
/*2 GETMASK128*/		"IFNDEF GMASK",".data","GMASK OWORD 0","ENDIF",".code","IF @Arch EQ 1","movups reg, MASK field","ELSE","vmovups reg, MASK field","ENDIF","ENDM",NULL,
/*3 REGS15STORAGE*/		"IFNDEF RRAX",".data?", " RRAX dq ?", " RRCX dq ?", " RRDX dq ?", " RRBX dq ?", " RRDI dq ?", " RRSI dq ?", " RRBP dq ?", " RRSP dq ?", " RR8  dq ?", " RR9  dq ?", " RR10 dq ?", " RR11 dq ?", " RR12 dq ?", " RR13 dq ?", " RR14 dq ?", " RR15 dq ?", " RXMM0 OWORD ?", " RXMM1 OWORD ?", " RXMM2 OWORD ?", " RXMM3 OWORD ?", " RXMM4 OWORD ?", " RXMM5 OWORD ?", " RXMM6 OWORD ?", " RXMM7 OWORD ?", "ENDIF", " .code", "ENDM", NULL,
/*4 MOV64*/				"mov dword ptr dst, LOW32(imm)", "mov dword ptr dst + 4, HIGH32(imm)", "ENDM", NULL,
/*5 MOV128*/			"MOV64 dst, immHi", "MOV64 dst + 8, immLo", "ENDM", NULL,
/*6 MOVXMMR128*/		"LOCAL savexmm",".data?","savexmm OWORD ?",".code","MOV64 savexmm, immHi","MOV64 savexmm + 8, immLo","vmovups dst,savexmm","ENDM", NULL,
/*7 SLXMMR*/			"LOCAL mmr","LOCAL saverax","LOCAL savercx","LOCAL saversi",".data?","saverax QWORD ?","savercx QWORD ?","saversi QWORD ?","mmr OWORD ?",".code","mov saverax,rax","mov savercx,rcx","mov saversi,rsi","mov ecx, cnt","and ecx,7fh","vmovups mmr, xmm128","lea  rsi,mmr",".if (cl >=  0x40)","mov rax, qword ptr[rsi+8]","mov qword ptr[rsi],rax","sub ecx, 64","shr qword ptr[rsi], cl ","xor eax,eax","mov qword ptr[rsi+8],rax",".else ","mov rax,qword ptr[rsi+8]","shr qword ptr[rsi],cl","shr qword ptr[rsi+8],cl","neg cl","shl rax, cl","or qword ptr[rsi],rax",".endif ","mov rax,saverax","mov rcx,savercx","mov rsi,saversi","vmovups xmm128,mmr ","ENDM", NULL,
/*8 SHIFTLEFT128*/		"LOCAL saverax","LOCAL savercx","LOCAL saversi",".data?","saverax QWORD ?","savercx QWORD ?","saversi QWORD ?",".code","mov saverax,rax","mov savercx,rcx","mov saversi,rsi","mov  rsi,mmr","mov ecx, cnt","and ecx,7fh",".if (cl >=  0x40)","mov rax, qword ptr[rsi+8]","mov qword ptr[rsi],rax","sub ecx, 64","shr qword ptr[rsi], cl ","xor eax,eax","mov qword ptr[rsi+8],rax",".else ","mov rax,qword ptr[rsi+8]","shr qword ptr[rsi],cl","shr qword ptr[rsi+8],cl","neg cl","shl rax, cl","or qword ptr[rsi],rax",".endif ","mov rax,saverax","mov rcx,savercx","mov rcx,saversi","ENDM", NULL,
/*9 SRXMMR*/			"LOCAL mmr","LOCAL saverax","LOCAL savercx","LOCAL saversi",".data?","saverax QWORD ?","savercx QWORD ?","saversi QWORD ?","mmr OWORD ?",".code","mov saverax,rax","mov savercx,rcx","mov saversi,rsi","mov ecx, cnt","and ecx,7fh","vmovups mmr, xmm128","lea  rsi,mmr",".if (cl >=  0x40)","mov rax, qword ptr[rsi]","mov qword ptr[rsi+8],rax","sub ecx, 64","shl qword ptr[rsi+8], cl","xor eax,eax","mov qword ptr[rsi],rax",".else ","mov rax,qword ptr[rsi]","shl qword ptr[rsi],cl","shl qword ptr[rsi+8],cl","neg cl","shr rax, cl","or qword ptr[rsi+8],rax",".endif ","mov rax,saverax","mov rcx,savercx","mov rsi,saversi","vmovups xmm128,mmr ","ENDM",NULL,
/*10 SHIFTRIGHT128*/	"LOCAL saverax","LOCAL savercx","LOCAL saversi",".data?","saverax QWORD ?","savercx QWORD ?","saversi QWORD ?",".code","mov saverax,rax","mov savercx,rcx","mov saversi,rsi","mov  rsi,mmr","mov ecx, cnt","and ecx,7fh",".if (cl >=  0x40)","mov rax, qword ptr[rsi]","mov qword ptr[rsi+8],rax","sub ecx, 64","shl qword ptr[rsi+8], cl ","xor eax,eax","mov qword ptr[rsi],rax",".else ","mov rax,qword ptr[rsi]","shl qword ptr[rsi],cl","shl qword ptr[rsi+8],cl","neg cl","shr rax, cl","or qword ptr[rsi+8],rax",".endif ","mov rax,saverax","mov rcx,savercx","mov rsi,saversi","ENDM",NULL,
/*11 MEMALLOC*/			"IF @Platform EQ 1", "INVOKE HeapAlloc,RV(GetProcessHeap),0,aSize", "ELSE", "INVOKE malloc,aSize", "ENDIF", "ALIGNADDR rax, 16", "endm", NULL,
/*12 MEMFREE*/			"IF @Platform EQ 1", "INVOKE HeapFree,RV(GetProcessHeap),0,memPtr", "ELSE", "INVOKE free,memPtr", "ENDIF", "endm", NULL,
/*13 CSTR*/				"local szText", ".data", "szText db Text,0", ".code", "IF @Platform EQ 1", "exitm <offset szText>", "ELSE", "exitm <addr szText>", "ENDIF", "endm", NULL,
/*14 WSTR*/				"local szText", ".data", "szText dw Text,0", ".code", "exitm <addr szText>", "endm", NULL,
/*15 FP4*/				"local vname", ".data", "align 4", "vname REAL4 value", ".code", "exitm <vname>", "endm", NULL,
/*16 FP8*/				"local vname", ".data", "align 8", "vname REAL8 value", ".code", "exitm <vname>", "endm", NULL,
/*17 FP10*/				"local vname", ".data", "align 8", "vname REAL10 value", ".code", "exitm <vname>", "endm", NULL,
/*18 LOADSS*/			"IF @Arch EQ 0", "mov eax, val", "movd reg, eax", "ELSE", "mov eax, val", "vmovd reg, eax", "ENDIF", "ENDM", NULL,
/*19 LOADSD*/			"IF @Arch EQ 0", "mov rax, real8 ptr val", "movq reg, rax", "ELSE", "mov rax, real8 ptr val", "vmovq reg, rax", "ENDIF", "ENDM", NULL,
/*20 LOADPS*/			"IF @Arch EQ 0", "mov eax, val", "movd reg, eax", "pshufd reg, reg, 0", "ELSE", "mov eax, val", "vmovd reg, eax", "vpshufd reg, reg, 0", "ENDIF", "ENDM", NULL,
/*21 ALIGNADDR*/		"add reg, number - 1", "and reg, -number", "ENDM", NULL,
/*22 RV*/				"arg equ <invoke FuncName>", "FOR var, <args>", "arg CATSTR arg, <, EXPAND_PREFIX(var)>", "ENDM", "arg", "EXITM <rax>", "ENDM", NULL,
/*23 REPARG*/			"LOCAL nustr", "quot SUBSTR <arg>, 1, 1", "IFIDN quot, <\">", ".data", "nustr db arg, 0", ".code", "EXITM <ADDR nustr>", "ELSE", "EXITM <ADDR arg>", "ENDIF", "ENDM", NULL,
/*24 EXPAND_PREFIX*/	"LOCAL prefix1, wrd, nu, varname", "prefix1 SUBSTR <txtitm>, 1, 1", "IFIDN prefix1, <&>", "nu SUBSTR <txtitm>, 2", "wrd CATSTR <ADDR >, nu", "EXITM <wrd>", "ENDIF", "IFIDN prefix1, <*>", "nu SUBSTR <txtitm>, 2", ".data ?", "varname dq ?", ".code", "mov rax, nu", "mov rax,[rax]", "mov varname, rax", "EXITM <varname>", "ENDIF", "EXITM <txtitm>", "ENDM", NULL,
/*25 _ARRAY*/			"cdef TEXTEQU <__&arrType&_def>", "% IFDEF cdef", "mov r8,8", "ELSE", "mov r8,sizeof(arrType)", "ENDIF", "imul r8,sizeArr", "MEMALLOC(r8)", "exitm<rax>", "ENDM", NULL,
/*26 _DELETEARRAY*/		"MEMFREE(arrPtr)", "ENDM", NULL,
/*27 OINTERFACE*/		"% __&CName&_def EQU 1","% __&CName&_size = 16","curClass TEXTEQU <CName>","@CatStr(CName, <vtbl CSTRUCT >)","__0 dq 0","__1 dq 0","ptrDefS TEXTEQU <psr>","ptrDefS CATSTR ptrDefS, <&curClass&>, < TYPEDEF PTR >, <&curClass&>","% ptrDefS","ENDM", NULL,
/*28 ENDOINTERFACE*/	"curClass ENDS", "ENDM", NULL,
/*29 CVIRTUAL*/			"LOCAL sz1, sz2","pDef CATSTR <TYPEDEF PROTO >,<(&retType&)>,< thisPtr:PTR>","IFNB <protoDef>","pDef CATSTR pDef, <, >, <&protoDef>","ENDIF","sz2 CATSTR <_>, curClass, <_&method>, <Pto>","% &sz2 &pDef","% sz1 typedef PTR &sz2","% method sz1 0","% __&curClass&_size = __&curClass&_size + 8", "fnex TEXTEQU <_>","fnex CATSTR fnex, curClass, <_>, <&method&>, < PROTO >, <(&retType&)>, < thisPtr:psr>, curClass","IFNB <&protoDef>","fnex CATSTR fnex, <, >, <&protoDef&>","ELSE","ENDIF","fnex", "ENDM", NULL,
/*30 CLASS*/			"% __&CName&_def = 1","% __&CName&_size = 16","curClass TEXTEQU <CName>", "@CatStr(CName, <vtbl CSTRUCT >)","ctorS TEXTEQU <ctor dq offset _&CName&_Init>","dtorS TEXTEQU <dtor dq offset _&CName&_Destroy>","ctorS","dtorS","ENDM", NULL,
/*31 ENDCLASS*/			"curClass ENDS",".data","align 16","% _stat&curClass&vtbl &curClass&vtbl <>","align 16","% _stat&curClass& curClass <>","ptrDefS TEXTEQU <psr>","ptrDefS CATSTR ptrDefS, <&curClass&>, < TYPEDEF PTR >, <&curClass&>","% ptrDefS","ptrDefS2 TEXTEQU <psr>","ptrDefS2 CATSTR ptrDefS2, <&curClass&vtbl>, < TYPEDEF PTR >, <&curClass&vtbl>","% ptrDefS2",".code","ENDM", NULL,
/*32 CMETHOD*/			"LOCAL sz1, sz2","sz2 CATSTR <_>, curClass, <_&method>, <Pto>","% sz1 typedef PTR &sz2","% method sz1 offset _&curClass&_&method&","% __&curClass&_size = __&curClass&_size + 8","ENDM", NULL,
/*33 METHOD*/			"curClass TEXTEQU <className>", "curMethod TEXTEQU <method>", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex, < PROTO >, <(&retType&)> , < thisPtr:psr>, <&className&>", "IFNB <args>", "fnex CATSTR fnex, <, >, <&args&>", "ELSE", "ENDIF", "fnex", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex, <Pto TYPEDEF PROTO >,<(&retType&)>,< thisPtr:psr>, <&className&>", "IFNB <args>", "fnex CATSTR fnex, <, >, <&args&>", "ELSE", "ENDIF", "fnex", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex,< PROC >, <(&retType&)>, < >, <&usesStr&>, < thisPtr:psr>, <&className&>", "IFNB <args>", "fnex CATSTR fnex, <, >, <&args&>", "ELSE", "ENDIF", "IF @Platform EQ 1", "assume rcx:ptr curClass", "ELSE","assume rdi:ptr curClass","ENDIF", "align 16", "fnex", "ENDM", NULL,
/*34 STATICMETHOD*/		"curClass TEXTEQU <className>", "curMethod TEXTEQU <method>", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex, < PROTO >, <(&retType&)>", "IFNB <args>", "fnex CATSTR fnex, < >, <&args&>", "ELSE", "ENDIF", "fnex", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex, <Pto TYPEDEF PROTO >,<(&retType&)>", "IFNB <args>", "fnex CATSTR fnex, < >, <&args&>", "ELSE", "ENDIF", "fnex", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex,< PROC >, <(&retType&)>, < >, <&usesStr&>", "IFNB <args>", "fnex CATSTR fnex, < >, <&args&>", "ELSE", "ENDIF", "IF @Platform EQ 1", "assume rcx:ptr curClass", "ELSE","assume rdi:ptr curClass","ENDIF", "align 16", "fnex", "ENDM", NULL,
/*35 VECMETHOD*/		"curClass TEXTEQU <className>", "curMethod TEXTEQU <method>", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex, < PROTO VECTORCALL >, <(&retType&)> , < thisPtr:psr>, <&className&>", "IFNB <args>", "fnex CATSTR fnex, <, >, <&args&>", "ELSE", "ENDIF", "fnex", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex, <Pto TYPEDEF PROTO VECTORCALL >,<(&retType&)>,< thisPtr:psr>, <&className&>", "IFNB <args>", "fnex CATSTR fnex, <, >, <&args&>", "ELSE", "ENDIF", "fnex", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex,< PROC VECTORCALL >, <(&retType&)>, < >, <&usesStr&>, < thisPtr:psr>, <&className&>", "IFNB <args>", "fnex CATSTR fnex, <, >, <&args&>", "ELSE", "ENDIF", "IF @Platform EQ 1", "assume rcx:ptr curClass", "ELSE","assume rdi:ptr curClass","ENDIF", "align 16", "fnex", "ENDM", NULL,
/*36 STATICVECMETHOD*/	"curClass TEXTEQU <className>", "curMethod TEXTEQU <method>", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex, < PROTO VECTORCALL >, <(&retType&)>", "IFNB <args>", "fnex CATSTR fnex, < >, <&args&>", "ELSE", "ENDIF", "fnex", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex, <Pto TYPEDEF PROTO VECTORCALL >,<(&retType&)>", "IFNB <args>", "fnex CATSTR fnex, < >, <&args&>", "ELSE", "ENDIF", "fnex", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex,< PROC VECTORCALL >, <(&retType&)>, < >, <&usesStr&>", "IFNB <args>", "fnex CATSTR fnex, < >, <&args&>", "ELSE", "ENDIF", "IF @Platform EQ 1", "assume rcx:ptr curClass", "ELSE","assume rdi:ptr curClass","ENDIF", "align 16", "fnex", "ENDM", NULL,
/*37 ENDMETHOD*/		"IF @Platform EQ 1", "assume rcx:nothing", "ELSE","assume rdi:nothing","ENDIF", "fnex TEXTEQU <_>", "fnex CATSTR fnex, curClass", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, curMethod", "fnex CATSTR fnex, < ENDP>", "fnex", "ENDM", NULL,
/*38 _DECLARE*/			"ldef TEXTEQU <LOCAL &varName&>", "ldef CATSTR ldef, < : >", "ldef CATSTR ldef, <typeName>", "% ldef", "ENDM", NULL,
/*39 _STATICREF*/		"% lea reg, _stat&classType&", "ENDM", NULL,
/*40 _NEW*/				"% mov r8, sizeof(className)","MEMALLOC(r8)",".if (rax != 0)","mov rdi,rax","% lea rsi,_stat&className","% mov rcx, sizeof(className)","rep movsb","fnex TEXTEQU <_>","fnex CATSTR fnex, <&className&>","fnex CATSTR fnex, <_>","fnex CATSTR fnex, <Init>","IFNB <ctorArgs>","fnex2 TEXTEQU <invoke fnex, rax, ctorArgs>","ELSE","fnex2 TEXTEQU <invoke fnex, rax>","ENDIF","fnex2",".endif","exitm<rax>","ENDM", NULL, 
/*41 _RBXNEW*/			"% mov r8, sizeof(className)","MEMALLOC(r8)",".if (rax != 0)","mov rdi,rax","% lea rsi,_stat&className","% mov rcx, sizeof(className)","rep movsb","fnex TEXTEQU <_>","fnex CATSTR fnex, <&className&>","fnex CATSTR fnex, <_>","fnex CATSTR fnex, <Init>","IFNB <ctorArgs>","fnex2 TEXTEQU <invoke fnex, rax, ctorArgs>","ELSE","fnex2 TEXTEQU <invoke fnex, rax>","ENDIF","fnex2","mov rbx, rax",".endif","exitm<rbx>","ENDM", NULL,
/*42 _ITEM*/			"exitm<[_V(objPtr, Iterator, Items, idx)]>", "ENDM", NULL,
/*43 _ITEMR*/			"exitm<_V(objPtr, Iterator, Items, idx)>", "ENDM", NULL,
/*44 _INVOKE*/			"fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "IFNB <args>", "fnex2 TEXTEQU <invoke fnex, &objPtr&, &args&>", "ELSE", "fnex2 TEXTEQU <invoke fnex, &objPtr&>", "ENDIF", "fnex2", "ENDM", NULL,
/*45 _I*/				"fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex2 TEXTEQU <invoke fnex, &objPtr&, &args&>", "fnex2", "IF @LastReturnType EQ 0", "EXITM <al>", "ELSEIF @LastReturnType EQ 0x40", "EXITM <al>", "ELSEIF @LastReturnType EQ 1", "EXITM <ax>", "ELSEIF @LastReturnType EQ 0x41", "EXITM <ax>", "ELSEIF @LastReturnType EQ 2", "EXITM <eax>", "ELSEIF @LastReturnType EQ 0x42", "EXITM <eax>", "ELSEIF @LastReturnType EQ 3", "EXITM <rax>", "ELSEIF @LastReturnType EQ 0x43", "EXITM <rax>", "ELSEIF @LastReturnType EQ 0xc3", "EXITM <rax>", "ELSEIF @LastReturnType EQ 6", "EXITM <xmm0>", "ELSEIF @LastReturnType EQ 7", "EXITM <ymm0>", "ELSEIF @LastReturnType EQ 8", "EXITM <zmm0>", "ELSEIF @LastReturnType EQ 0x22", "EXITM <xmm0>", "ELSEIF @LastReturnType EQ 0x23", "EXITM <xmm0>", "ELSE", "EXITM <eax>", "ENDIF", "ENDM", NULL,
/*46 _STATIC*/			"fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex2 TEXTEQU <invoke fnex, &args&>", "fnex2", "IF @LastReturnType EQ 0", "EXITM <al>", "ELSEIF @LastReturnType EQ 0x40", "EXITM <al>", "ELSEIF @LastReturnType EQ 1", "EXITM <ax>", "ELSEIF @LastReturnType EQ 0x41", "EXITM <ax>", "ELSEIF @LastReturnType EQ 2", "EXITM <eax>", "ELSEIF @LastReturnType EQ 0x42", "EXITM <eax>", "ELSEIF @LastReturnType EQ 3", "EXITM <rax>", "ELSEIF @LastReturnType EQ 0x43", "EXITM <rax>", "ELSEIF @LastReturnType EQ 0xc3", "EXITM <rax>", "ELSEIF @LastReturnType EQ 6", "EXITM <xmm0>", "ELSEIF @LastReturnType EQ 7", "EXITM <ymm0>", "ELSEIF @LastReturnType EQ 8", "EXITM <zmm0>", "ELSEIF @LastReturnType EQ 0x22", "EXITM <xmm0>", "ELSEIF @LastReturnType EQ 0x23", "EXITM <xmm0>", "ELSE", "EXITM <eax>", "ENDIF", "ENDM", NULL,
/*47 _DELETE*/			"IF @Platform EQ 1","mov rcx, objPtr","mov rax,[rcx]","call qword ptr[rax + 8]","ELSE","mov rdi, objPtr","mov rax,[rdi]","call qword ptr[rax + 8]","ENDIF","MEMFREE(objPtr)","ENDM",NULL,
/*48 _VINVOKE*/			"InterfacePtr TEXTEQU <_>","InterfacePtr CATSTR InterfacePtr, <&Interface>, <_>, <&Function>, <Pto>","IF(OPATTR(pInterface)) AND 00010000b","IFNB <args>","IF @Platform EQ 1","IFDIFI <&pInterface>,<rcx>","mov rcx,&pInterface","ENDIF","mov r15,[rcx]","invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rcx, &args","ELSE","mov rdi,&pInterface","mov r15,[rdi]","invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rdi, &args","ENDIF","ELSE","IF @Platform EQ 1","IFDIFI <&pInterface>,<rcx>","mov rcx,&pInterface","ENDIF","mov r15,[rcx]","invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rcx","ELSE","mov rdi,&pInterface","mov r15,[rdi]","invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rdi","ENDIF","ENDIF","ELSE","IFDIFI <&pInterface>,<rcx>","mov rcx,pInterface","ENDIF","mov r15,[rcx]","IFNB <args>","FOR arg, <args>","IFIDNI <&arg>, <rcx>",".ERR <rcx is not allowed as a Method parameter with indirect object label>","ENDIF","ENDM","invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rcx, &args","ELSE","invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rcx","ENDIF","ENDIF","ENDM",NULL,
/*49 _V*/				"InterfacePtr TEXTEQU <_>","InterfacePtr CATSTR InterfacePtr, <&Interface>, <_>, <&Function>, <Pto>","IF(OPATTR(pInterface)) AND 00010000b","IFNB <args>","IF @Platform EQ 1","IFDIFI <&pInterface>,<rcx>","mov rcx,&pInterface","ENDIF","mov r15,[rcx]","invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rcx, &args","ELSE","mov rdi,&pInterface","mov r15,[rdi]","invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rdi, &args","ENDIF","ELSE","IF @Platform EQ 1","IFDIFI <&pInterface>,<rcx>","mov rcx,&pInterface","ENDIF","mov r15,[rcx]","invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rcx","ELSE","mov rdi,&pInterface","mov r15,[rdi]","invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rdi","ENDIF","ENDIF","ELSE","IF @Platform EQ 1","IFDIFI <&pInterface>,<rcx>","mov rcx,pInterface","ENDIF","mov r15,[rcx]","IFNB <args>","FOR arg, <args>","IFIDNI <&arg>, <rcx>",".ERR <rcx is not allowed as a Method parameter with indirect object label>","ENDIF","ENDM","invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rcx, &args","ELSE","invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rcx","ENDIF","ELSE","mov rdi,pInterface","mov r15,[rdi]","IFNB <args>","FOR arg, <args>","IFIDNI <&arg>, <rdi>",".ERR <rdi is not allowed as a Method parameter with indirect object label>","ENDIF","ENDM","invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rdi, &args","ELSE","invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rdi","ENDIF","ENDIF","ENDIF","IF @LastReturnType EQ 0","EXITM <al>","ELSEIF @LastReturnType EQ 0x40","EXITM <al>","ELSEIF @LastReturnType EQ 1","EXITM <ax>","ELSEIF @LastReturnType EQ 0x41","EXITM <ax>","ELSEIF @LastReturnType EQ 2","EXITM <eax>","ELSEIF @LastReturnType EQ 0x42","EXITM <eax>","ELSEIF @LastReturnType EQ 3","EXITM <rax>","ELSEIF @LastReturnType EQ 0x43","EXITM <rax>","ELSEIF @LastReturnType EQ 0xc3","EXITM <rax>","ELSEIF @LastReturnType EQ 6","EXITM <xmm0>","ELSEIF @LastReturnType EQ 7","EXITM <ymm0>","ELSEIF @LastReturnType EQ 8","EXITM <zmm0>","ELSEIF @LastReturnType EQ 0x22","EXITM <xmm0>","ELSEIF @LastReturnType EQ 0x23","EXITM <xmm0>","ELSE","EXITM <eax>","ENDIF","ENDM",NULL,
/*50 CSTATIC*/			"LOCAL sz1, sz2","sz2 CATSTR <_>, curClass, <_&method>, <Pto>","% sz1 typedef PTR &sz2","% method sz1 offset _&curClass&_&method&","% __&curClass&_size = __&curClass&_size + 8","ENDM", NULL,
/*51 LOADMSS*/ 			".data", "align 4", "vname dd value", ".code", "IF @Arch EQ 0", "movss reg, vname", "ELSE", "vmovss reg, vname", "ENDIF", "ENDM", NULL,
/*52 LOADMSD*/			".data", "align 8", "bname dq value", ".code", "IF @Arch EQ 0", "movsd reg, bname", "ELSE", "vmovsd reg, bname", "ENDIF", "ENDM", NULL,
/*53 UINVOKE*/			"IFB <args>", "invoke func", "ELSE", "invoke func, args", "ENDIF", "IF @LastReturnType EQ 0", "EXITM <al>", "ELSEIF @LastReturnType EQ 0x40", "EXITM <al>", "ELSEIF @LastReturnType EQ 1", "EXITM <ax>", "ELSEIF @LastReturnType EQ 0x41", "EXITM <ax>", "ELSEIF @LastReturnType EQ 2", "EXITM <eax>", "ELSEIF @LastReturnType EQ 0x42", "EXITM <eax>", "ELSEIF @LastReturnType EQ 3", "EXITM <rax>", "ELSEIF @LastReturnType EQ 0x43", "EXITM <rax>", "ELSEIF @LastReturnType EQ 0xc3", "EXITM <rax>", "ELSEIF @LastReturnType EQ 6", "EXITM <xmm0>", "ELSEIF @LastReturnType EQ 7", "EXITM <ymm0>", "ELSEIF @LastReturnType EQ 8", "EXITM <zmm0>", "ELSEIF @LastReturnType EQ 0x22", "EXITM <xmm0>", "ELSEIF @LastReturnType EQ 0x23", "EXITM <xmm0>", "ELSE", "EXITM <eax>", "ENDIF", "ENDM", NULL,
/*54 ASFLOAT*/			"EXITM <REAL4 PTR reg> ", NULL,
/*55 ASDOUBLE*/			"EXITM <REAL8 PTR reg> ", NULL,
/*56 R4P*/				"EXITM <REAL4 PTR reg> ", NULL,
/*57 R8P*/				"EXITM <REAL8 PTR reg> ", NULL,
/*58 arginvoke*/		"LOCAL dstSize, stackPos","REGS15STORAGE","IFB <args>","invoke func","ELSE","IF invCount GE 2","IF argNo EQ 2","mov RRCX,rcx","IF @Arch EQ 0","movaps RXMM0,xmm0","ELSE","vmovaps RXMM0,xmm0","ENDIF","ELSEIF argNo EQ 3","mov RRCX,rcx","mov RRDX,rdx","IF @Arch EQ 0","movaps RXMM0,xmm0","movaps RXMM1,xmm1","ELSE","vmovaps RXMM0,xmm0","vmovaps RXMM1,xmm1","ENDIF","ELSEIF argNo EQ 4","mov RRCX,rcx","mov RRDX,rdx","mov RR8,r8","IF @Arch EQ 0","movaps RXMM0,xmm0","movaps RXMM1,xmm1","movaps RXMM2,xmm2","ELSE","vmovaps RXMM0,xmm0","vmovaps RXMM1,xmm1","vmovaps RXMM2,xmm2","ENDIF","ELSEIF argNo GE 5","mov RRCX,rcx","mov RRDX,rdx","mov RR8,r8","mov RR9,r9","IF @Arch EQ 0","movaps RXMM0,xmm0","movaps RXMM1,xmm1","movaps RXMM2,xmm2","movaps RXMM3,xmm3","ELSE","vmovaps RXMM0,xmm0","vmovaps RXMM1,xmm1","vmovaps RXMM2,xmm2","vmovaps RXMM3,xmm3","ENDIF","ENDIF","ENDIF","invoke func, args", "IF invCount GE 2","IF argNo EQ 2","mov rcx,RRCX","IF @Arch EQ 0","movaps xmm0,RXMM0","ELSE","vmovaps xmm0,RXMM0","ENDIF","ELSEIF argNo EQ 3","mov rcx,RRCX","mov rdx,RRDX","IF @Arch EQ 0","movaps xmm0,RXMM0","movaps xmm1,RXMM1","ELSE","vmovaps xmm0,RXMM0","vmovaps xmm1,RXMM1","ENDIF","ELSEIF argNo EQ 4","mov rcx,RRCX","mov rdx,RRDX","mov r8,RR8","IF @Arch EQ 0","movaps xmm0,RXMM0","movaps xmm1,RXMM1","movaps xmm2,RXMM2","ELSE","vmovaps xmm0,RXMM0","vmovaps xmm1,RXMM1","vmovaps xmm2,RXMM2","ENDIF","ELSEIF argNo GE 5","mov rcx,RRCX","mov rdx,RRDX","mov r8,RR8","mov r9,RR9","IF @Arch EQ 0","movaps xmm0,RXMM0","movaps xmm1,RXMM1","movaps xmm2,RXMM2","movaps xmm3,RXMM3","ELSE","vmovaps xmm0,RXMM0","vmovaps xmm1,RXMM1","vmovaps xmm2,RXMM2","vmovaps xmm3,RXMM3","ENDIF","ENDIF","ENDIF","ENDIF","IF @LastReturnType EQ 0","dstSize = 1","ELSEIF @LastReturnType EQ 0x40","dstSize = 1","ELSEIF @LastReturnType EQ 1","dstSize = 2","ELSEIF @LastReturnType EQ 0x41","dstSize = 2","ELSEIF @LastReturnType EQ 2","dstSize = 4","ELSEIF @LastReturnType EQ 0x42","dstSize = 4","ELSEIF @LastReturnType EQ 3","dstSize = 8","ELSEIF @LastReturnType EQ 0x43","dstSize = 8","ELSEIF @LastReturnType EQ 0xc3","dstSize = 8","ELSEIF @LastReturnType EQ 6","dstSize = 16","ELSEIF @LastReturnType EQ 7","dstSize = 32","ELSEIF @LastReturnType EQ 8","dstSize = 64","ELSEIF @LastReturnType EQ 0x22","dstSize = 16","ELSEIF @LastReturnType EQ 0x23","dstSize = 16","ELSE","dstSize = 4","ENDIF","IF argNo EQ 1","IF dstSize EQ 1","mov cl,al","EXITM<cl>","ELSEIF dstSize EQ 2","mov cx,ax","EXITM<cx>","ELSEIF dstSize EQ 4","mov ecx,eax","EXITM<ecx>","ELSEIF dstSize EQ 8","mov rcx,rax","EXITM<rcx>","ELSEIF dstSize EQ 16","EXITM<xmm0>","ELSEIF dstSize EQ 32","EXITM<ymm0>","ELSEIF dstSize EQ 64","EXITM<zmm0>","ENDIF","ELSEIF argNo EQ 2","IF dstSize EQ 1","mov dl,al","EXITM<dl>","ELSEIF dstSize EQ 2","mov dx,ax","EXITM<dx>","ELSEIF dstSize EQ 4","mov edx,eax","EXITM<edx>","ELSEIF dstSize EQ 8","mov rdx,rax","EXITM<rdx>","ELSEIF dstSize EQ 16","IF @Arch EQ 0","movdqa xmm1,xmm0","ELSE","vmovdqa xmm1,xmm0","ENDIF","EXITM<xmm1>","ELSEIF dstSize EQ 32","vmovdqa ymm1,ymm0","EXITM<ymm1>","ELSEIF dstSize EQ 64","vmovdqa zmm1,zmm0","EXITM<zmm1>","ENDIF","ELSEIF argNo EQ 3","IF dstSize EQ 1","mov r8b,al","EXITM<r8b>","ELSEIF dstSize EQ 2","mov r8w,ax","EXITM<r8w>","ELSEIF dstSize EQ 4","mov r8d,eax","EXITM<r8d>","ELSEIF dstSize EQ 8","mov r8,rax","EXITM<r8>","ELSEIF dstSize EQ 16","IF @Arch EQ 0","movdqa xmm2,xmm0","ELSE","vmovdqa xmm2,xmm0","ENDIF","EXITM<xmm2>","ELSEIF dstSize EQ 32","vmovdqa ymm2,ymm0","EXITM<ymm2>","ELSEIF dstSize EQ 64","vmovdqa zmm2,zmm0","EXITM<zmm2>","ENDIF","ELSEIF argNo EQ 4","IF dstSize EQ 1","mov r9b,al","EXITM<r9b>","ELSEIF dstSize EQ 2","mov r9w,ax","EXITM<r9w>","ELSEIF dstSize EQ 4","mov r9d,eax","EXITM<r9d>","ELSEIF dstSize EQ 8","mov r9,rax","EXITM<r9>","ELSEIF dstSize EQ 16","IF @Arch EQ 0","movdqa xmm3,xmm0","ELSE","vmovdqa xmm3,xmm0","ENDIF","EXITM<xmm3>","ELSEIF dstSize EQ 32","vmovdqa ymm3,ymm0","EXITM<ymm3>","ELSEIF dstSize EQ 64","vmovdqa zmm3,zmm0","EXITM<zmm3>","ENDIF","ELSE","IF dstSize EQ 1","mov[rsp + 0x20 + ((argNo - 5) * 8)],al","ELSEIF dstSize EQ 2","mov[rsp + 0x20 + ((argNo - 5) * 8)],ax","ELSEIF dstSize EQ 4","mov[rsp + 0x20 + ((argNo - 5) * 8)],eax","ELSEIF dstSize EQ 8","mov[rsp + 0x20 + ((argNo - 5) * 8)],rax","ELSEIF(dstSize EQ 16) OR(dstSize EQ 32) OR(dstSize EQ 64)","IF @Arch EQ 0","movsd[rsp + 0x20 + ((argNo - 5) * 8)],xmm0","ELSE","vmovsd[rsp + 0x20 + ((argNo - 5) * 8)],xmm0","ENDIF","ENDIF","EXITM<[rsp + 0x20 + ((argNo - 5) * 8)]>","ENDIF","ENDM",NULL,
/*59 COMINTERFACE*/		"curClass TEXTEQU <CName>", "% __&CName&_size = 24", "@CatStr(CName, <vtbl COMSTRUCT >)", "ptrDefS TEXTEQU <psr>", "ptrDefS CATSTR ptrDefS, <&curClass&>, < TYPEDEF PTR >, <&curClass&>","% ptrDefS", "CVIRTUAL QueryInterface, <QWORD>, :PTR", "CVIRTUAL AddRef, <DWORD>", "CVIRTUAL Release, <DWORD>", "ENDM", NULL,
/*60 ENDCOMINTERFACE*/	"ENDMETHODS", "curClass ENDS", ".data","% _stat&curClass&vtbl &curClass&vtbl <>","% _stat&curClass& curClass <>", "ENDM", NULL,
/*61:ENDMETHODS*/		"LOCAL evtbl","% evtbl CATSTR <&curClass&>,<vtbl>,< ENDS>","evtbl", "@CatStr(curClass, < CSTRUCT >)","% pVtbl dq offset _stat&curClass&vtbl","ENDM",NULL,
/*62:_DEREF*/		    "LOCAL i, ptrstr, typestr, argstr","argstr TEXTEQU < >","i = 0","FOR dref, <argsAndRefs>","IF i LT argCount+1","IF i GT 0", "argstr CATSTR argstr, <,>, <&dref&>","ENDIF", "ELSE","IF(i - argCount) MOD 2 EQ 1","ptrstr TEXTEQU <&dref&>","ELSE","typestr TEXTEQU <&dref&>","IF(i - argCount) EQ 2","% IF(OPATTR(ptrstr)) EQ 0x30","% mov rcx, &ptrstr&","ELSE","% mov rcx, @CatStr(<[>, <&ptrstr&>, <].>, <&typestr&>)","ENDIF","ELSE","% mov rcx, @CatStr(<[>, <&ptrstr&>, <].>, <&typestr&>)","ENDIF","ENDIF","ENDIF","i = i + 1","ENDM","% IF @SizeStr(<%&argstr&>) GT 3", "argstr SUBSTR argstr, 3", "ENDIF", "IF argCount EQ 0", "argstr TEXTEQU <>", "ENDIF", "IF argCount GT 0", "InterfacePtr TEXTEQU <_>","InterfacePtr CATSTR InterfacePtr, <&itype>, <_>, <&proc>, <Pto>","IF(OPATTR(rcx)) AND 00010000b","% IF argCount GT 0", "IF @Platform EQ 1","mov r15,[rcx]","% invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx, &argstr","ELSE","mov rdi,rcx","mov r15,[rdi]","% invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rdi, &argstr","ENDIF","ELSE","IF @Platform EQ 1","mov r15,[rcx]","% invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx","ELSE","mov rdi,rcx","mov r15,[rdi]","% invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rdi","ENDIF","ENDIF","ELSE","mov r15,[rcx]","IF argCount GT 0","FOR arg, <argstr>","IFIDNI <&arg>, <rcx>",".ERR <rcx is not allowed as a Method parameter with indirect object label>","ENDIF","ENDM","% invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx, &argstr","ELSE","invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx","ENDIF","ENDIF","ELSE","InterfacePtr TEXTEQU <_>","InterfacePtr CATSTR InterfacePtr, <&itype>, <_>, <&proc>, <Pto>","IF(OPATTR(rcx)) AND 00010000b","IF argCount GT 0","IF @Platform EQ 1","mov r15,[rcx]","% invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx, &argstr","ELSE","mov rdi,rcx","mov r15,[rdi]","% invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rdi, &argstr","ENDIF","ELSE","IF @Platform EQ 1","mov r15,[rcx]","invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx","ELSE","mov rdi,rcx","mov r15,[rdi]","invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rdi","ENDIF","ENDIF","ELSE","mov r15,[rcx]","IF argCount GT 0","FOR arg, <argstr>","IFIDNI <&arg>, <rcx>",".ERR <rcx is not allowed as a Method parameter with indirect object label>","ENDIF","ENDM","% invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx, &argstr","ELSE","invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx","ENDIF","ENDIF","ENDIF","ENDM",NULL,
/*63:_DEREFI*/          "LOCAL i, ptrstr, typestr, argstr","argstr TEXTEQU < >","i = 0","FOR dref, <argsAndRefs>","IF i LT argCount+1","IF i GT 0", "argstr CATSTR argstr, <,>, <&dref&>","ENDIF", "ELSE","IF(i - argCount) MOD 2 EQ 1","ptrstr TEXTEQU <&dref&>","ELSE","typestr TEXTEQU <&dref&>","IF(i - argCount) EQ 2","% IF(OPATTR(ptrstr)) EQ 0x30","% mov rcx, &ptrstr&","ELSE","% mov rcx, @CatStr(<[>, <&ptrstr&>, <].>, <&typestr&>)","ENDIF","ELSE","% mov rcx, @CatStr(<[>, <&ptrstr&>, <].>, <&typestr&>)","ENDIF","ENDIF","ENDIF","i = i + 1","ENDM","% IF @SizeStr(<%&argstr&>) GT 3", "argstr SUBSTR argstr, 3", "ENDIF", "IF argCount EQ 0", "argstr TEXTEQU <>", "ENDIF", "IF argCount GT 0", "InterfacePtr TEXTEQU <_>","InterfacePtr CATSTR InterfacePtr, <&itype>, <_>, <&proc>, <Pto>","IF(OPATTR(rcx)) AND 00010000b","% IF argCount GT 0", "IF @Platform EQ 1","mov r15,[rcx]","% invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx, &argstr","ELSE","mov rdi,rcx","mov r15,[rdi]","% invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rdi, &argstr","ENDIF","ELSE","IF @Platform EQ 1","mov r15,[rcx]","% invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx","ELSE","mov rdi,rcx","mov r15,[rdi]","% invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rdi","ENDIF","ENDIF","ELSE","mov r15,[rcx]","IF argCount GT 0","FOR arg, <argstr>","IFIDNI <&arg>, <rcx>",".ERR <rcx is not allowed as a Method parameter with indirect object label>","ENDIF","ENDM","% invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx, &argstr","ELSE","invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx","ENDIF","ENDIF","ELSE","InterfacePtr TEXTEQU <_>","InterfacePtr CATSTR InterfacePtr, <&itype>, <_>, <&proc>, <Pto>","IF(OPATTR(rcx)) AND 00010000b","IF argCount GT 0","IF @Platform EQ 1","mov r15,[rcx]","% invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx, &argstr","ELSE","mov rdi,rcx","mov r15,[rdi]","% invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rdi, &argstr","ENDIF","ELSE","IF @Platform EQ 1","mov r15,[rcx]","invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx","ELSE","mov rdi,rcx","mov r15,[rdi]","invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rdi","ENDIF","ENDIF","ELSE","mov r15,[rcx]","IF argCount GT 0","FOR arg, <argstr>","IFIDNI <&arg>, <rcx>",".ERR <rcx is not allowed as a Method parameter with indirect object label>","ENDIF","ENDM","% invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx, &argstr","ELSE","invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx","ENDIF","ENDIF","ENDIF","IF @LastReturnType EQ 0","EXITM <al>","ELSEIF @LastReturnType EQ 0x40","EXITM <al>","ELSEIF @LastReturnType EQ 1","EXITM <ax>","ELSEIF @LastReturnType EQ 0x41","EXITM <ax>","ELSEIF @LastReturnType EQ 2","EXITM <eax>","ELSEIF @LastReturnType EQ 0x42","EXITM <eax>","ELSEIF @LastReturnType EQ 3","EXITM <rax>","ELSEIF @LastReturnType EQ 0x43","EXITM <rax>","ELSEIF @LastReturnType EQ 0xc3","EXITM <rax>","ELSEIF @LastReturnType EQ 6","EXITM <xmm0>","ELSEIF @LastReturnType EQ 7","EXITM <ymm0>","ELSEIF @LastReturnType EQ 8","EXITM <zmm0>","ELSEIF @LastReturnType EQ 0x22","EXITM <xmm0>","ELSEIF @LastReturnType EQ 0x23","EXITM <xmm0>","ELSE","EXITM <eax>","ENDIF","ENDM",NULL,
/*64 _SINVOKE*/			"fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "IFNB <args>", "fnex2 TEXTEQU <invoke fnex, &args&>", "ELSE", "fnex2 TEXTEQU <invoke fnex>", "ENDIF", "fnex2", "ENDM", NULL,
/*65 RAWINTERFACE*/		"curClass TEXTEQU <CName>", "% __&CName&_size = 0", "@CatStr(CName, < RAWSTRUCT >)", "ptrDefS TEXTEQU <psr>", "ptrDefS CATSTR ptrDefS, <&curClass&>, < TYPEDEF PTR >, <&curClass&>","% ptrDefS", "ENDM", NULL,
/*66 ENDRAWINTERFACE*/	"curClass ENDS", "ENDM", NULL,
/*67 _DEREFR */			"LOCAL argstr", "argstr TEXTEQU <>", "IFNB <&argsAndRegs&>", "mov rax,dref","% invoke [rax].&itype.&proc, &argsAndRefs", "ELSE", "% invoke [rax].&itype.&proc", "ENDIF","ENDM", NULL,
/*68 _DEREFRR */		"LOCAL argstr", "argstr TEXTEQU <>", "% invoke &dref&.&itype.&proc, &argsAndRefs", "ENDM", NULL,
/*69 STDFUNC */			"LOCAL sz1, sz2","pDef CATSTR <TYPEDEF PROTO >,<(&retType&) >","IFNB <protoDef>","pDef CATSTR pDef, <, >, <&protoDef>","ENDIF","sz2 CATSTR <_>, curClass, <_&method>, <Pto>","% &sz2 &pDef","% sz1 typedef PTR &sz2","% method sz1 0","% __&curClass&_size = __&curClass&_size + 8", "fnex TEXTEQU <_>","fnex CATSTR fnex, curClass, <_>, <&method&>, < PROTO >, <(&retType&) >","IFNB <&protoDef>","fnex CATSTR fnex, <, >, <&protoDef&>","ELSE","ENDIF","fnex", "ENDM", NULL,
    };	

	/* Compile Macros */
	for (i = 0; i < MACRO_COUNT64; i++)
	{
		for (j = 0; j < macroLen[i]; j++)
		{
			srcLines[j] = (char *)malloc(MAX_LINE_LEN);
			if(srcLines[j])
				strcpy(srcLines[j], macCode[(start_pos + j)]);
		}
		mac = CreateMacro(macName64[i]);
		ModuleInfo.token_count = Tokenize(macDef64[i], 0, ModuleInfo.tokenarray, 0);
		StoreAutoMacro(mac, 2, ModuleInfo.tokenarray, TRUE, srcLines, 0, macroLen[i]);
		start_pos += macroLen[i] + 1;
	}
}

void InitAutoMacros32(void)
{
	struct dsym *mac;
	uint_32 i = 0;
	uint_32 j = 0;
	uint_32 start_pos = 0;
	char  *srcLines[128]; // NB: 128 is the max number of lines of macro code per macro.

	uint_32 macroLen[] = {17, 11, 3, 3, 8, 54, 46, 54, 46, 7, 6, 6, 6, 7, 7, 7, 8, 10, 3, 7, 11, 19, 10, 10, 37, 1, 1, 1, 1, 37, 6, 2, 23, 54, 10, 6 }; // Count of individual lines of macro-body code.
	char *macCode[] = {
		"IFNDEF GMASK",".data","GMASK OWORD 0","ENDIF","IFNDEF NOTMASK",".data","NOTMASK OWORD -1","ENDIF",".code","IF @Arch EQ 1","movups reg, MASK field","pxor reg, NOTMASK","ELSE","vmovups reg, MASK field","vpxor reg, reg, NOTMASK","ENDIF","ENDM",NULL,
		"IFNDEF GMASK",".data","GMASK OWORD 0","ENDIF",".code","IF @Arch EQ 1","movups reg, MASK field","ELSE","vmovups reg, MASK field","ENDIF","ENDM",NULL,
		"mov dword ptr dst, LOW32(imm)", "mov dword ptr dst + 4, HIGH32(imm)", "ENDM", NULL,
		"MOV64 dst, immHi", "MOV64 dst + 8, immLo", "ENDM", NULL,
		"LOCAL savexmm",".data?","savexmm OWORD ?",".code","MOV64 savexmm, immHi","MOV64 savexmm + 8, immLo","vmovups dst,savexmm","ENDM", NULL,
		"LOCAL mmr","LOCAL savedLo","LOCAL savedxmm1","LOCAL savedxmm0",".data?","savedLo  QWORD ?","mmr OWORD ?","savedxmm1 OWORD ?","savedxmm0 OWORD ?",".code","push eax","push ecx","push esi","movups savedxmm1,xmm1","movups savedxmm0,xmm0","movups mmr,xmm0","mov ecx,cnt","and ecx,7fh","lea eax,mmr","movq xmm0,[eax+8]",".if (ecx >=  0x40)","sub ecx,64","movd xmm1,ecx","psrlq xmm0,xmm1","movq [eax],xmm0","pxor xmm0,xmm0","movq [eax+8],xmm0",".else","movq savedLo,xmm0","movd xmm1,ecx","psrlq	xmm0, xmm1","movq [eax+8],xmm0","movq xmm0,[eax]","psrlq	xmm0, xmm1","movq [eax],xmm0","neg ecx","and ecx,7fh","sub ecx,64","movd xmm1,ecx","movq xmm0,savedLo","psllq xmm0,xmm1","movq xmm1,[eax]","por xmm0,xmm1","movq [eax],xmm0",".endif ","movups xmm0,mmr","movups xmm1,savedxmm1","IFDIFI <xmm0>,<xmm128>","movups xmm0,savedxmm0","ENDIF","pop esi","pop ecx","pop eax","ENDM",NULL,
		"LOCAL savedLo","LOCAL savedxmm1","LOCAL savedxmm0 ",".data?","savedLo QWORD ?","savedxmm1 OWORD ?","savedxmm0 OWORD ?",".code","push eax","push ecx","movups savedxmm1,xmm1","movups savedxmm0,xmm0","mov ecx,cnt","and ecx,7fh","mov eax,mmr","movq xmm0,[eax+8]",".if (ecx >=  0x40)","sub ecx,64","movd xmm1,ecx","psrlq xmm0,xmm1","movq [eax],xmm0","pxor xmm0,xmm0","movq [eax+8],xmm0",".else","movq savedLo,xmm0","movd xmm1,ecx","psrlq	xmm0, xmm1","movq [eax+8],xmm0","movq xmm0,[eax]","psrlq	xmm0, xmm1","movq [eax],xmm0","neg ecx","and ecx,7fh","sub ecx,64","movd xmm1,ecx","movq xmm0,savedLo","psllq xmm0,xmm1","movq xmm1,[eax]","por xmm0,xmm1","movq [eax],xmm0",".endif ","movups xmm1,savedxmm1","movups xmm0,savedxmm0","pop ecx","pop eax","ENDM",NULL,		
		"LOCAL mmr","LOCAL savedLo","LOCAL savedxmm1","LOCAL savedxmm0",".data?","savedLo  QWORD ?","mmr OWORD ?","savedxmm1 OWORD ?","savedxmm0 OWORD ?",".code","push eax","push ecx","push esi","movups savedxmm1,xmm1","movups savedxmm0,xmm0","movups mmr,xmm0","mov ecx,cnt","and ecx,7fh","lea eax,mmr","movq xmm0,[eax]",".if (ecx >=  0x40)","sub ecx,64","movd xmm1,ecx","psllq xmm0,xmm1","movq [eax+8],xmm0","pxor xmm0,xmm0","movq [eax],xmm0",".else","movq savedLo,xmm0","movd xmm1,ecx","psllq	xmm0, xmm1","movq [eax],xmm0","movq xmm0,[eax+8]","psllq	xmm0, xmm1","movq [eax+8],xmm0","neg ecx","and ecx,7fh","sub ecx,64","movd xmm1,ecx","movq xmm0,savedLo","psrlq xmm0,xmm1","movq xmm1,[eax+8]","por xmm0,xmm1","movq [eax+8],xmm0",".endif ","movups xmm0,mmr","movups xmm1,savedxmm1","IFDIFI <xmm0>,<xmm128>","movups xmm0,savedxmm0","ENDIF","pop esi","pop ecx","pop eax","ENDM",NULL,        
		"LOCAL savedHi","LOCAL savedxmm1","LOCAL savedxmm0 ",".data?","savedHi   QWORD ?","savedxmm1 OWORD ?","savedxmm0 OWORD ?",".code","push eax","push ecx","movups savedxmm1,xmm1","movups savedxmm0,xmm0","mov ecx,cnt","and ecx,7fh","mov eax,mmr","movq xmm0,[eax]",".if (ecx >=  0x40)","sub ecx,64","movd xmm1,ecx","psllq xmm0,xmm1","movq [eax+8],xmm0","pxor xmm0,xmm0","movq [eax],xmm0",".else","movq savedHi,xmm0","movd xmm1,ecx","psllq	xmm0, xmm1","movq [eax],xmm0","movq xmm0,[eax+8]","psllq	xmm0, xmm1","movq [eax+8],xmm0","neg ecx","and ecx,7fh","sub ecx,64","movd xmm1,ecx","movq xmm0,savedHi","psrlq xmm0,xmm1","movq xmm1,[eax+8]","por xmm0,xmm1","movq [eax+8],xmm0",".endif ","movups xmm1,savedxmm1","movups xmm0,savedxmm0","pop ecx","pop eax","ENDM",NULL,
		"IF @Platform EQ 1", "INVOKE HeapAlloc,RV(GetProcessHeap),0,aSize", "ELSE", "INVOKE malloc,aSize", "ENDIF", "ALIGNADDR eax, 16", "endm", NULL,
		"IF @Platform EQ 1", "INVOKE HeapFree,RV(GetProcessHeap),0,memPtr", "ELSE", "INVOKE free,memPtr", "ENDIF", "endm", NULL,
		"local szText", ".data", "szText db Text,0", ".code", "exitm <offset szText>", "endm", NULL,
		"local szText", ".data", "szText dw Text,0", ".code", "exitm <offset szText>", "endm", NULL,
		"local vname", ".data", "align 4", "vname REAL4 value", ".code", "exitm <vname>", "endm", NULL,
		"local vname", ".data", "align 8", "vname REAL8 value", ".code", "exitm <vname>", "endm", NULL,
		"local vname", ".data", "align 8", "vname REAL10 value", ".code", "exitm <vname>", "endm", NULL,
		"IF @Arch EQ 0", "mov eax, val", "movd reg, eax", "ELSE", "mov eax, val", "vmovd reg, eax", "ENDIF", "ENDM", NULL,
		"IF @Arch EQ 0", "mov eax, val", "movd reg, eax", "pshufd reg, 0", "ELSE", "mov eax, val", "vmovd reg, eax", "vpshufd reg, reg, 0", "ENDIF", "ENDM", NULL,
		"add reg, number - 1", "and reg, -number", "ENDM", NULL,
		"arg equ <invoke FuncName>", "FOR var, <args>", "arg CATSTR arg, <, EXPAND_PREFIX(REPARG(var))>", "ENDM", "arg", "EXITM <eax>", "ENDM", NULL,
		"LOCAL nustr", "quot SUBSTR <arg>, 1, 1", "IFIDN quot, <\">", ".data", "nustr db arg, 0", ".code", "EXITM <ADDR nustr>", "ELSE", "EXITM <ADDR arg>", "ENDIF", "ENDM", NULL,
		"LOCAL prefix1, wrd, nu, varname", "prefix1 SUBSTR <txtitm>, 1, 1", "IFIDN prefix1, <&>", "nu SUBSTR <txtitm>, 2", "wrd CATSTR <ADDR >, nu", "EXITM <wrd>", "ENDIF", "IFIDN prefix1, <*>", "nu SUBSTR <txtitm>, 2", ".data ?", "varname dq ?", ".code", "mov eax, nu", "mov eax,[eax]", "mov varname, eax", "EXITM <varname>", "ENDIF", "EXITM <txtitm>", "ENDM", NULL,
		".data", "align 4", "vname dd value", ".code", "IF @Arch EQ 0", "movss reg, vname", "ELSE", "vmovss reg, vname", "ENDIF", "ENDM", NULL,
		".data", "align 8", "bname dq value", ".code", "IF @Arch EQ 0", "movsd reg, bname", "ELSE", "vmovsd reg, bname", "ENDIF", "ENDM", NULL,
		"IFB <args>", "invoke func", "ELSE", "invoke func, args", "ENDIF", "IF @LastReturnType EQ 0", "EXITM <al>", "ELSEIF @LastReturnType EQ 0x40", "EXITM <al>", "ELSEIF @LastReturnType EQ 1", "EXITM <ax>", "ELSEIF @LastReturnType EQ 0x41", "EXITM <ax>", "ELSEIF @LastReturnType EQ 2", "EXITM <eax>", "ELSEIF @LastReturnType EQ 0x42", "EXITM <eax>", "ELSEIF @LastReturnType EQ 3", "EXITM <rax>", "ELSEIF @LastReturnType EQ 0x43", "EXITM <rax>", "ELSEIF @LastReturnType EQ 0xc3", "EXITM <rax>", "ELSEIF @LastReturnType EQ 6", "EXITM <xmm0>", "ELSEIF @LastReturnType EQ 7", "EXITM <ymm0>", "ELSEIF @LastReturnType EQ 8", "EXITM <zmm0>", "ELSEIF @LastReturnType EQ 0x22", "EXITM <xmm0>", "ELSEIF @LastReturnType EQ 0x23", "EXITM <xmm0>", "ELSE", "EXITM <eax>", "ENDIF", "ENDM", NULL,
		"EXITM <REAL4 PTR reg> ", NULL,
		"EXITM <REAL8 PTR reg> ", NULL,
		"EXITM <REAL4 PTR reg> ", NULL,
		"EXITM <REAL8 PTR reg> ", NULL,
		"arg equ <invoke func>", "FOR var, <args>", "arg CATSTR arg, <, var>", "ENDM", "arg", "IF @LastReturnType EQ 0","EXITM<al>","ELSEIF @LastReturnType EQ 0x40","EXITM<al>","ELSEIF @LastReturnType EQ 1","EXITM<ax>","ELSEIF @LastReturnType EQ 0x41","EXITM<ax>","ELSEIF @LastReturnType EQ 2","EXITM<eax>","ELSEIF @LastReturnType EQ 0x42","EXITM<eax>","ELSEIF @LastReturnType EQ 3","EXITM<rax>","ELSEIF @LastReturnType EQ 0x43","EXITM<rax>","ELSEIF @LastReturnType EQ 0xc3","EXITM<rax>","ELSEIF @LastReturnType EQ 6","EXITM<xmm0>","ELSEIF @LastReturnType EQ 7","EXITM<ymm0>","ELSEIF @LastReturnType EQ 8","EXITM<zmm0>","ELSEIF @LastReturnType EQ 0x22","EXITM<xmm0>","ELSEIF @LastReturnType EQ 0x23","EXITM<xmm0>","ELSE","EXITM<eax>","ENDIF","ENDM",NULL,
		"curClass TEXTEQU <CName>", "@CatStr(CName, < COMSTRUCT >)", "CVIRTUAL QueryInterface, <>, :PTR", "CVIRTUAL AddRef, <>", "CVIRTUAL Release, <>", "ENDM", NULL,
		"curClass ENDS", "ENDM", NULL,
		"InterfacePtr TEXTEQU <_>", "InterfacePtr CATSTR InterfacePtr, <&Interface>, <_>, <&Function>, <Pto>", "IF(OPATTR(pInterface)) AND 00010000b", "IFNB <args>", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface", "ENDIF", "ELSE", "mov eax, pInterface", "mov eax,[eax]", "IFNB <args>", "FOR arg, <args>", "IFIDNI <&arg>, <eax>", ".ERR <eax is not allowed as a Method parameter with indirect object label>", "ENDIF", "ENDM", "invoke(InterfacePtr PTR[eax].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[eax].&Interface.&Function), pInterface", "ENDIF", "ENDIF", "ENDM", NULL,
		"InterfacePtr TEXTEQU <_>", "InterfacePtr CATSTR InterfacePtr, <&Interface>, <_>, <&Function>, <Pto>", "IF(OPATTR(pInterface)) AND 00010000b", "IFNB <args>", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface", "ENDIF", "ELSE", "mov eax, pInterface", "mov eax,[eax]", "IFNB <args>", "FOR arg, <args>", "IFIDNI <&arg>, <eax>", ".ERR <eax is not allowed as a Method parameter with indirect object label>", "ENDIF", "ENDM", "invoke(InterfacePtr PTR[eax].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[eax].&Interface.&Function), pInterface", "ENDIF", "ENDIF", "IF @LastReturnType EQ 0", "EXITM <al>", "ELSEIF @LastReturnType EQ 0x40", "EXITM <al>", "ELSEIF @LastReturnType EQ 1", "EXITM <ax>", "ELSEIF @LastReturnType EQ 0x41", "EXITM <ax>", "ELSEIF @LastReturnType EQ 2", "EXITM <eax>", "ELSEIF @LastReturnType EQ 0x42", "EXITM <eax>", "ELSEIF @LastReturnType EQ 3", "EXITM <rax>", "ELSEIF @LastReturnType EQ 0x43", "EXITM <rax>", "ELSEIF @LastReturnType EQ 0xc3", "EXITM <rax>", "ELSEIF @LastReturnType EQ 6", "EXITM <xmm0>", "ELSEIF @LastReturnType EQ 7", "EXITM <ymm0>", "ELSEIF @LastReturnType EQ 8", "EXITM <zmm0>", "ELSEIF @LastReturnType EQ 0x22", "EXITM <xmm0>", "ELSEIF @LastReturnType EQ 0x23", "EXITM <xmm0>", "ELSE", "EXITM <eax>", "ENDIF", "ENDM", NULL,
		"LOCAL sz1, sz2", "pDef CATSTR <TYPEDEF PROTO >,<&retType&>,< thisPtr:PTR>", "IFNB <protoDef>", "pDef CATSTR pDef, <, >, <&protoDef>", "ENDIF", "sz2 CATSTR <_>, curClass, <_&method>, <Pto>; _curClass_methodPto", "% &sz2 &pDef", "% sz1 typedef PTR &sz2", "% method sz1 0", "ENDM", NULL,
		"LOCAL evtbl","% evtbl CATSTR <&curClass&>,<vtbl>,< ENDS>","evtbl","@CatStr(curClass, < CSTRUCT >)","% pVtbl dd offset _stat&curClass&vtbl","ENDM", NULL
	};

	/* Compile Macros */
	for (i = 0; i < MACRO_COUNT32; i++)
	{
		for (j = 0; j < macroLen[i]; j++)
		{
			srcLines[j] = (char *)malloc(MAX_LINE_LEN);
			strcpy(srcLines[j], macCode[(start_pos + j)]);
		}
		mac = CreateMacro(macName32[i]);
		ModuleInfo.token_count = Tokenize(macDef32[i], 0, ModuleInfo.tokenarray, 0);
		StoreAutoMacro(mac, 2, ModuleInfo.tokenarray, TRUE, srcLines, 0, macroLen[i]);
		start_pos += macroLen[i] + 1;
	}
}