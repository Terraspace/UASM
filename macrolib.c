
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

#define MACRO_COUNT 47

/* MACRO names */
char *macName[] = {
	"MEMALLOC", "MEMFREE", "CSTR", "WSTR", "FP4", "FP8", "FP10", "LOADSS", "LOADSD", "LOADPS", "MEMALIGN", "RV", "REPARG", "EXPAND_PREFIX", "_ARRAY", "_DELETEARRAY", "OINTERFACE", "ENDOINTERFACE", "CVIRTUAL", "CLASS", "ENDCLASS", "CMETHOD", "METHOD", "STATICMETHOD", "ENDMETHOD", "_DECLARE", "_STATICREF", "_ACQUIRE", "_RELEASE", "_NEW", "_RBXNEW", "_ITEM", "_ITEMR", "_INVOKE", "_I", "_STATIC", "_DELETE", "_VINVOKE", "_V", "_VD", "_VW", "_VB", "_VF", "CSTATIC", "LOADMSS", "LOADMSD", "UINVOKE"
};

/* MACRO definitions */
char *macDef[] = {
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
	"MEMALIGN MACRO reg, number",
	"RV MACRO FuncName:REQ, args:VARARG",
	"REPARG MACRO arg",
	"EXPAND_PREFIX MACRO txtitm",
	"_ARRAY MACRO arrType:REQ,sizeArr:REQ",
	"_DELETEARRAY MACRO arrPtr:REQ",
	"OINTERFACE MACRO CName : REQ",
	"ENDOINTERFACE MACRO",
	"CVIRTUAL MACRO method : REQ, protoDef : VARARG",
	"CLASS MACRO CName : REQ",
	"ENDCLASS MACRO",
	"CMETHOD MACRO method : REQ",
	"METHOD MACRO className:REQ, method:REQ, usesStr:=<USES rbx rsi rdi>, args:VARARG",
	"STATICMETHOD MACRO className:REQ, method:REQ, usesStr:=<USES rbx rsi rdi>, args:VARARG",
	"ENDMETHOD MACRO",
	"_DECLARE MACRO varName : REQ, typeName : VARARG",
	"_STATICREF MACRO reg : REQ",
	"_ACQUIRE MACRO objPtr",
	"_RELEASE MACRO objPtr",
	"_NEW MACRO className : REQ, ctorArgs : VARARG",
	"_RBXNEW MACRO className : REQ, ctorArgs : VARARG",
	"_ITEM MACRO objPtr : REQ, idx : REQ",
	"_ITEMR MACRO objPtr : REQ, idx : REQ",
	"_INVOKE MACRO className : REQ, method : REQ, objPtr : REQ, args : VARARG",
	"_I MACRO className : REQ, method : REQ, objPtr : REQ, args : VARARG",
	"_STATIC MACRO className : REQ, method : REQ, args : VARARG",
	"_DELETE MACRO objPtr : REQ",
	"_VINVOKE MACRO pInterface : REQ, Interface : REQ, Function : REQ, args : VARARG",
	"_V MACRO pInterface : REQ, Interface : REQ, Function : REQ, args : VARARG",
	"_VD MACRO pInterface : REQ, Interface : REQ, Function : REQ, args : VARARG",
	"_VW MACRO pInterface : REQ, Interface : REQ, Function : REQ, args : VARARG",
	"_VB MACRO pInterface : REQ, Interface : REQ, Function : REQ, args : VARARG",
	"_VF MACRO pInterface : REQ, Interface : REQ, Function : REQ, args : VARARG",
	"CSTATIC MACRO method : REQ",
    "LOADMSS MACRO reg, value",
    "LOADMSD MACRO reg, value",
	"UINVOKE MACRO func:REQ, args:VARARG"
};

void CreateMacroLibCases(void)
{
	/* Create case alternative names for macrolib functions */
	if (ModuleInfo.case_sensitive && !ModuleInfo.convert_uppercase)
	{
		AddLineQueue("uinvoke EQU UINVOKE");
		AddLineQueue("Uinvoke EQU UINVOKE");
	}
}

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
	char  *srcLines[128]; // NB: 128 is the max number of lines of macro code per macro.

	uint_32 macroLen[] = { 7, 6, 6, 6, 7, 7, 7, 8, 8, 10, 3, 7, 11, 19, 10, 2, 7, 2, 10, 11, 19, 5, 39, 39, 12, 5, 2, 3, 3, 26, 27, 2, 2, 11, 8, 8, 9, 22, 23, 23, 23, 23, 23, 5, 10, 10, 35 }; // Count of individual lines of macro-body code.
	char *macCode[] = {
		"IF @Platform EQ 1", "INVOKE HeapAlloc,RV(GetProcessHeap),0,aSize", "ELSE", "INVOKE malloc,aSize", "ENDIF", "MEMALIGN rax, 16", "endm", NULL,
		"IF @Platform EQ 1", "INVOKE HeapFree,RV(GetProcessHeap),0,memPtr", "ELSE", "INVOKE free,memPtr", "ENDIF", "endm", NULL,
		"local szText", ".data", "szText db Text,0", ".code", "exitm <ADDR szText>", "endm", NULL,
		"local szText", ".data", "szText dw Text,0", ".code", "exitm <ADDR szText>", "endm", NULL,
		"local vname", ".data", "align 4", "vname REAL4 value", ".code", "exitm <vname>", "endm", NULL,
		"local vname", ".data", "align 8", "vname REAL8 value", ".code", "exitm <vname>", "endm", NULL,
		"local vname", ".data", "align 8", "vname REAL10 value", ".code", "exitm <vname>", "endm", NULL,
		"IF @Arch EQ 0", "mov eax, val", "movd reg, eax", "ELSE", "mov eax, val", "vmovd reg, eax", "ENDIF", "ENDM", NULL,
		"IF @Arch EQ 0", "mov rax, real8 ptr val", "movq reg, rax", "ELSE", "mov rax, real8 ptr val", "vmovq reg, rax", "ENDIF", "ENDM", NULL,
		"IF @Arch EQ 0", "mov eax, val", "movd reg, eax", "pshufd reg, 0", "ELSE", "mov eax, val", "vmovd reg, eax", "vpshufd reg, 0", "ENDIF", "ENDM", NULL,
		"add reg, number - 1", "and reg, -number", "ENDM", NULL,
		"arg equ <invoke FuncName>", "FOR var, <args>", "arg CATSTR arg, <, EXPAND_PREFIX(REPARG(var))>", "ENDM", "arg", "EXITM <rax>", "ENDM", NULL,
		"LOCAL nustr", "quot SUBSTR <arg>, 1, 1", "IFIDN quot, <\">", ".data", "nustr db arg, 0", ".code", "EXITM <ADDR nustr>", "ELSE", "EXITM <ADDR arg>", "ENDIF", "ENDM", NULL,
		"LOCAL prefix1, wrd, nu, varname", "prefix1 SUBSTR <txtitm>, 1, 1", "IFIDN prefix1, <&>", "nu SUBSTR <txtitm>, 2", "wrd CATSTR <ADDR >, nu", "EXITM <wrd>", "ENDIF", "IFIDN prefix1, <*>", "nu SUBSTR <txtitm>, 2", ".data ?", "varname dq ?", ".code", "mov rax, nu", "mov rax,[rax]", "mov varname, rax", "EXITM <varname>", "ENDIF", "EXITM <txtitm>", "ENDM", NULL,
		"cdef TEXTEQU <__&arrType&_def>", "% IFDEF cdef", "mov r8,8", "ELSE", "mov r8,sizeof(arrType)", "ENDIF", "imul r8,sizeArr", "MEMALLOC(r8)", "exitm<rax>", "ENDM", NULL,
		"MEMFREE(arrPtr)", "ENDM", NULL,
		"curClass TEXTEQU <CName>", "@CatStr(CName, < STRUCT >)", "__0 dq 0", "__1 dq 0", "__2 dq 0", "__3 dq 0", "ENDM", NULL,
		"curClass ENDS", "ENDM", NULL,
		"LOCAL sz1, sz2", "pDef TEXTEQU <TYPEDEF PROTO thisPtr : QWORD>", "IFNB <protoDef>", "pDef CATSTR pDef, <, >, <&protoDef>", "ENDIF", "sz2 CATSTR <_>, curClass, <_&method>, <Pto>; _curClass_methodPto", "% &sz2 &pDef", "% sz1 typedef PTR &sz2", "% method sz1 0", "ENDM", NULL,
		"% __&CName&_def EQU 1", "curClass TEXTEQU <CName>", "@CatStr(CName, < STRUCT >)", "ctorS TEXTEQU <ctor dq offset _&CName&_Init>", "dtorS TEXTEQU <dtor dq offset _&CName&_Destroy>", "relS TEXTEQU <release dq offset _&CName&_Release>", "ctorS", "dtorS", "relS", "_refCount dq 0", "ENDM", NULL,
		"curClass ENDS", ".code", "align 16", "rproc TEXTEQU <_&curClass&_Release PROC FRAME thisPtr : QWORD>", "% rproc", "assume rcx : ptr curClass", "dec[rcx]._refCount", "assume rcx : nothing", "ret", "rproce TEXTEQU <_&curClass&_Release ENDP>", "% rproce", ".data", "align 16", "% _stat&curClass& curClass <>", "ptrDefS TEXTEQU <psr>", "ptrDefS CATSTR ptrDefS, <&curClass&>, < TYPEDEF PTR >, <&curClass&>", "% ptrDefS", ".code", "ENDM", NULL,
		"LOCAL sz1, sz2", "sz2 CATSTR <_>, curClass, <_&method>, <Pto>", "% sz1 typedef PTR &sz2", "% method sz1 offset _&curClass&_&method&", "ENDM", NULL,
		"curClass TEXTEQU <className>", "curMethod TEXTEQU <method>", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex, < PROTO thisPtr : psr>, <&className&>", "IFNB <args>", "fnex CATSTR fnex, <, >, <&args&>", "ELSE", "ENDIF", "fnex", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex, <Pto TYPEDEF PROTO thisPtr : psr>, <&className&>", "IFNB <args>", "fnex CATSTR fnex, <, >, <&args&>", "ELSE", "ENDIF", "fnex", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex,< PROC >,<&usesStr&>, < thisPtr:psr>,<&className&>", "IFNB <args>", "fnex CATSTR fnex, <, >, <&args&>", "ELSE", "ENDIF", "IF @Platform EQ 1", "assume rcx:ptr curClass", "ELSE","assume rdi:ptr curClass","ENDIF", "align 16", "fnex", "ENDM", NULL,
		"curClass TEXTEQU <className>", "curMethod TEXTEQU <method>", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex, < PROTO>", "IFNB <args>", "fnex CATSTR fnex, < >, <&args&>", "ELSE", "ENDIF", "fnex", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex, <Pto TYPEDEF PROTO>", "IFNB <args>", "fnex CATSTR fnex, < >, <&args&>", "ELSE", "ENDIF", "fnex", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex,< PROC >, <&usesStr&>", "IFNB <args>", "fnex CATSTR fnex, < >, <&args&>", "ELSE", "ENDIF", "IF @Platform EQ 1", "assume rcx:ptr curClass", "ELSE","assume rdi:ptr curClass","ENDIF", "align 16", "fnex", "ENDM", NULL,
		"IF @Platform EQ 1", "assume rcx:nothing", "ELSE","assume rdi:nothing","ENDIF", "fnex TEXTEQU <_>", "fnex CATSTR fnex, curClass", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, curMethod", "fnex CATSTR fnex, < ENDP>", "fnex", "ENDM", NULL,
		"ldef TEXTEQU <LOCAL &varName&>", "ldef CATSTR ldef, < : >", "ldef CATSTR ldef, <typeName>", "% ldef", "ENDM", NULL,
		"% lea reg, _stat&curClass&", "ENDM", NULL,
		"mov rax, objPtr", "inc qword ptr[rax + 24]", "ENDM", NULL,
		"mov rax, objPtr", "dec qword ptr[rax + 24]", "ENDM", NULL,
		"mov r15, sizeof(className) + 16", "MEMALLOC(r15)", ".if (rax != 0)", "mov rdi, rax", "lea rsi, _stat&className", "movdqa xmm0, [rsi]", "movdqa xmm1, [rsi + 16]", "movdqa[rdi], xmm0", "movdqa[rdi + 16], xmm1", "add rsi, 32", "add rdi, 32", "mov rcx, sizeof(className) - 32", "rep movsb", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <Init>", "IFNB <ctorArgs>", "fnex2 TEXTEQU <invoke fnex, rax, ctorArgs>", "ELSE", "fnex2 TEXTEQU <invoke fnex, rax>", "ENDIF", "fnex2", ".endif", "exitm<rax>", "ENDM", NULL,
		"mov r15, sizeof(className) + 16", "MEMALLOC(r15)", ".if (rax != 0)", "mov rdi, rax", "lea rsi, _stat&className", "movdqa xmm0, [rsi]", "movdqa xmm1, [rsi + 16]", "movdqa[rdi], xmm0", "movdqa[rdi + 16], xmm1", "add rsi, 32", "add rdi, 32", "mov rcx, sizeof(className) - 32", "rep movsb", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <Init>", "IFNB <ctorArgs>", "fnex2 TEXTEQU <invoke fnex, rax, ctorArgs>", "ELSE", "fnex2 TEXTEQU <invoke fnex, rax>", "ENDIF", "fnex2", "mov rbx, rax", ".endif", "exitm<rbx>", "ENDM", NULL,
		"exitm<[$V(objPtr, Iterator, Items, idx)]>", "ENDM", NULL,
		"exitm<$V(objPtr, Iterator, Items, idx)>", "ENDM", NULL,
		"fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "IFNB <args>", "fnex2 TEXTEQU <invoke fnex, &objPtr&, &args&>", "ELSE", "fnex2 TEXTEQU <invoke fnex, &objPtr&>", "ENDIF", "fnex2", "ENDM", NULL,
		"fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex2 TEXTEQU <invoke fnex, &objPtr&, &args&>", "fnex2", "exitm<rax>", "ENDM", NULL,
		"fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex2 TEXTEQU <invoke fnex, &args&>", "fnex2", "exitm<rax>", "ENDM", NULL,
		"IF @Platform EQ 1", "mov rcx, objPtr", "call qword ptr[rcx + 8]", "ELSE", "mov rdi, objPtr", "call qword ptr[rdi + 8]", "ENDIF", "MEMFREE(objPtr)", "ENDM", NULL,
		"InterfacePtr TEXTEQU <_>", "InterfacePtr CATSTR InterfacePtr, <&Interface>, <_>, <&Function>, <Pto>", "IF(OPATTR(pInterface)) AND 00010000b", "IFNB <args>", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface", "ENDIF", "ELSE", "mov r15, pInterface", "IFNB <args>", "FOR arg, <args>", "IFIDNI <&arg>, <r15>", ".ERR <r15 is not allowed as a Method parameter with indirect object label>", "ENDIF", "ENDM", "invoke(InterfacePtr PTR[r15].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[r15].&Interface.&Function), pInterface", "ENDIF", "ENDIF", "ENDM", NULL,
		"InterfacePtr TEXTEQU <_>", "InterfacePtr CATSTR InterfacePtr, <&Interface>, <_>, <&Function>, <Pto>", "IF(OPATTR(pInterface)) AND 00010000b", "IFNB <args>", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface", "ENDIF", "ELSE", "mov r15, pInterface", "IFNB <args>", "FOR arg, <args>", "IFIDNI <&arg>, <r15>", ".ERR <r15 is not allowed as a Method parameter with indirect object label>", "ENDIF", "ENDM", "invoke(InterfacePtr PTR[r15].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[r15].&Interface.&Function), pInterface", "ENDIF", "ENDIF", "exitm<rax>", "ENDM", NULL,
		"InterfacePtr TEXTEQU <_>", "InterfacePtr CATSTR InterfacePtr, <&Interface>, <_>, <&Function>, <Pto>", "IF(OPATTR(pInterface)) AND 00010000b", "IFNB <args>", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface", "ENDIF", "ELSE", "mov rax, pInterface", "IFNB <args>", "FOR arg, <args>", "IFIDNI <&arg>, <rax>", ".ERR <rax is not allowed as a Method parameter with indirect object label>", "ENDIF", "ENDM", "invoke(InterfacePtr PTR[rax].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[rax].&Interface.&Function), pInterface", "ENDIF", "ENDIF", "exitm<eax>", "ENDM", NULL,
		"InterfacePtr TEXTEQU <_>", "InterfacePtr CATSTR InterfacePtr, <&Interface>, <_>, <&Function>, <Pto>", "IF(OPATTR(pInterface)) AND 00010000b", "IFNB <args>", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface", "ENDIF", "ELSE", "mov rax, pInterface", "IFNB <args>", "FOR arg, <args>", "IFIDNI <&arg>, <rax>", ".ERR <rax is not allowed as a Method parameter with indirect object label>", "ENDIF", "ENDM", "invoke(InterfacePtr PTR[rax].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[rax].&Interface.&Function), pInterface", "ENDIF", "ENDIF", "exitm<ax>", "ENDM", NULL,
		"InterfacePtr TEXTEQU <_>", "InterfacePtr CATSTR InterfacePtr, <&Interface>, <_>, <&Function>, <Pto>", "IF(OPATTR(pInterface)) AND 00010000b", "IFNB <args>", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface", "ENDIF", "ELSE", "mov rax, pInterface", "IFNB <args>", "FOR arg, <args>", "IFIDNI <&arg>, <rax>", ".ERR <rax is not allowed as a Method parameter with indirect object label>", "ENDIF", "ENDM", "invoke(InterfacePtr PTR[rax].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[rax].&Interface.&Function), pInterface", "ENDIF", "ENDIF", "exitm<al>", "ENDM", NULL,
		"InterfacePtr TEXTEQU <_>", "InterfacePtr CATSTR InterfacePtr, <&Interface>, <_>, <&Function>, <Pto>", "IF(OPATTR(pInterface)) AND 00010000b", "IFNB <args>", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface", "ENDIF", "ELSE", "mov rax, pInterface", "IFNB <args>", "FOR arg, <args>", "IFIDNI <&arg>, <rax>", ".ERR <rax is not allowed as a Method parameter with indirect object label>", "ENDIF", "ENDM", "invoke(InterfacePtr PTR[rax].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[rax].&Interface.&Function), pInterface", "ENDIF", "ENDIF", "exitm<xmm0>", "ENDM", NULL,
		"LOCAL sz1, sz2", "sz2 CATSTR <_>, curClass, <_&method>, <Pto>", "% sz1 typedef PTR &sz2", "% method sz1 offset _&curClass&_&method&", "ENDM", NULL,
 	    ".data", "align 4", "vname dd value", ".code", "IF @Arch EQ 0", "movss reg, vname", "ELSE", "vmovss reg, vname", "ENDIF", "ENDM", NULL,
        ".data", "align 8", "bname dq value", ".code", "IF @Arch EQ 0", "movsd reg, bname", "ELSE", "vmovsd reg, bname", "ENDIF", "ENDM", NULL,
		"IFB <args>", "invoke func", "ELSE", "invoke func, args", "ENDIF", "IF @LastReturnType EQ 0", "EXITM <al>", "ELSEIF @LastReturnType EQ 0x40", "EXITM <al>", "ELSEIF @LastReturnType EQ 1", "EXITM <ax>", "ELSEIF @LastReturnType EQ 0x41", "EXITM <ax>", "ELSEIF @LastReturnType EQ 2", "EXITM <eax>", "ELSEIF @LastReturnType EQ 0x42", "EXITM <eax>", "ELSEIF @LastReturnType EQ 3", "EXITM <rax>", "ELSEIF @LastReturnType EQ 0x43", "EXITM <rax>", "ELSEIF @LastReturnType EQ 0xc3", "EXITM <rax>", "ELSEIF @LastReturnType EQ 6", "EXITM <xmm0>", "ELSEIF @LastReturnType EQ 7", "EXITM <ymm0>", "ELSEIF @LastReturnType EQ 8", "EXITM <zmm0>", "ELSEIF @LastReturnType EQ 0x22", "EXITM <xmm0>", "ELSEIF @LastReturnType EQ 0x23", "EXITM <xmm0>", "ENDIF", "ENDM", NULL
    };	

	/* Compile Macros */
	for (i = 0; i < MACRO_COUNT; i++)
	{
		for (j = 0; j < macroLen[i]; j++)
		{
			srcLines[j] = (char *)malloc(MAX_LINE_LEN);
			strcpy(srcLines[j], macCode[(start_pos + j)]);
		}
		mac = CreateMacro(macName[i]);
		ModuleInfo.token_count = Tokenize(macDef[i], 0, ModuleInfo.tokenarray, 0);
		StoreAutoMacro(mac, 2, ModuleInfo.tokenarray, TRUE, srcLines, 0, macroLen[i]);
		start_pos += macroLen[i] + 1;
		for (j = 0; j < macroLen[i]; j++)
		{
			free(srcLines[j]);
		}
	}



}
