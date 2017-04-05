
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

#define MACRO_COUNT 42

/* MACRO names */
char *macName[] = {
	"@CSTR", "@WSTR", "FP4", "FP8", "FP10", "LOADSS", "LOADSD", "LOADPS", "MEMALIGN", "RV", "REPARG", "EXPAND_PREFIX", "$ARRAY", "$DELETEARRAY", "INTERFACE", "ENDINTERFACE", "CVIRTUAL", "CLASS", "ENDCLASS", "CMETHOD", "METHOD", "STATICMETHOD", "ENDMETHOD", "$DECLARE", "$STATICREF", "$ACQUIRE", "$RELEASE", "$NEW", "$RBXNEW", "$ITEM", "$ITEMR", "$INVOKE", "$I", "$STATIC", "$DELETE", "$VINVOKE", "$V", "$VD", "$VW", "$VB", "$VF", "CSTATIC"
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
	"RV MACRO FuncName:REQ, args:VARARG",
	"REPARG MACRO arg",
	"EXPAND_PREFIX MACRO txtitm",
	"$ARRAY MACRO arrType:REQ,sizeArr:REQ",
	"$DELETEARRAY MACRO arrPtr:REQ",
	"INTERFACE MACRO CName : REQ",
	"ENDINTERFACE MACRO",
	"CVIRTUAL MACRO method : REQ, protoDef : VARARG",
	"CLASS MACRO CName : REQ",
	"ENDCLASS MACRO",
	"CMETHOD MACRO method : REQ",
	"METHOD MACRO className : REQ, method : REQ, args : VARARG",
	"STATICMETHOD MACRO className : REQ, method : REQ, args : VARARG",
	"ENDMETHOD MACRO",
	"$DECLARE MACRO varName : REQ, typeName : VARARG",
	"$STATICREF MACRO reg : REQ",
	"$ACQUIRE MACRO objPtr",
	"$RELEASE MACRO objPtr",
	"$NEW MACRO className : REQ, ctorArgs : VARARG",
	"$RBXNEW MACRO className : REQ, ctorArgs : VARARG",
	"$ITEM MACRO objPtr : REQ, idx : REQ",
	"$ITEMR MACRO objPtr : REQ, idx : REQ",
	"$INVOKE MACRO className : REQ, method : REQ, objPtr : REQ, args : VARARG",
	"$I MACRO className : REQ, method : REQ, objPtr : REQ, args : VARARG",
	"$STATIC MACRO className : REQ, method : REQ, args : VARARG",
	"$DELETE MACRO objPtr : REQ",
	"$VINVOKE MACRO pInterface : REQ, Interface : REQ, Function : REQ, args : VARARG",
	"$V MACRO pInterface : REQ, Interface : REQ, Function : REQ, args : VARARG",
	"$VD MACRO pInterface : REQ, Interface : REQ, Function : REQ, args : VARARG",
	"$VW MACRO pInterface : REQ, Interface : REQ, Function : REQ, args : VARARG",
	"$VB MACRO pInterface : REQ, Interface : REQ, Function : REQ, args : VARARG",
	"$VF MACRO pInterface : REQ, Interface : REQ, Function : REQ, args : VARARG",
	"CSTATIC MACRO method : REQ"
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

	uint_32 macroLen[] = { 6, 6, 7, 7, 7, 8, 8, 10, 3, 7, 11, 19, 10, 2, 7, 2, 10, 11, 19, 5, 35, 35, 8, 5, 2, 3, 3, 27, 28, 2, 2, 11, 8, 8, 5, 22, 23, 23, 23, 23, 23, 5 }; // Count of individual lines of macro-body code.
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
		"arg equ <invoke FuncName>", "FOR var, <args>", "arg CATSTR arg, <, EXPAND_PREFIX(REPARG(var))>", "ENDM", "arg", "EXITM <rax>", "ENDM", NULL,
		"LOCAL nustr", "quot SUBSTR <arg>, 1, 1", "IFIDN quot, <\">", ".data", "nustr db arg, 0", ".code", "EXITM <ADDR nustr>", "ELSE", "EXITM <ADDR arg>", "ENDIF", "ENDM", NULL,
		"LOCAL prefix1, wrd, nu, varname", "prefix1 SUBSTR <txtitm>, 1, 1", "IFIDN prefix1, <&>", "nu SUBSTR <txtitm>, 2", "wrd CATSTR <ADDR >, nu", "EXITM <wrd>", "ENDIF", "IFIDN prefix1, <*>", "nu SUBSTR <txtitm>, 2", ".data ?", "varname dq ?", ".code", "mov rax, nu", "mov rax,[rax]", "mov varname, rax", "EXITM <varname>", "ENDIF", "EXITM <txtitm>", "ENDM", NULL,
		"cdef TEXTEQU <__&arrType&_def>", "% IFDEF cdef", "mov r8,8", "ELSE", "mov r8,sizeof(arrType)", "ENDIF", "imul r8,sizeArr", "invoke HeapAlloc,RV(GetProcessHeap),0,r8", "exitm<rax>", "ENDM", NULL,
		"invoke HeapFree,RV(GetProcessHeap),0,arrPtr", "ENDM", NULL,
		"curClass TEXTEQU <CName>", "@CatStr(CName, < STRUCT >)", "__0 dq 0", "__1 dq 0", "__2 dq 0", "__3 dq 0", "ENDM", NULL,
		"curClass ENDS", "ENDM", NULL,
		"LOCAL sz1, sz2", "pDef TEXTEQU <TYPEDEF PROTO thisPtr : QWORD>", "IFNB <protoDef>", "pDef CATSTR pDef, <, >, <&protoDef>", "ENDIF", "sz2 CATSTR <_>, curClass, <_&method>, <Pto>; _curClass_methodPto", "% &sz2 &pDef", "% sz1 typedef PTR &sz2", "% method sz1 0", "ENDM", NULL,
		"% __&CName&_def EQU 1", "curClass TEXTEQU <CName>", "@CatStr(CName, < STRUCT >)", "ctorS TEXTEQU <ctor dq offset _&CName&_Init>", "dtorS TEXTEQU <dtor dq offset _&CName&_Destroy>", "relS TEXTEQU <release dq offset _&CName&_Release>", "ctorS", "dtorS", "relS", "_refCount dq 0", "ENDM", NULL,
		"curClass ENDS", ".code", "align 16", "rproc TEXTEQU <_&curClass&_Release PROC FRAME thisPtr : QWORD>", "% rproc", "assume rcx : ptr curClass", "dec[rcx]._refCount", "assume rcx : nothing", "ret", "rproce TEXTEQU <_&curClass&_Release ENDP>", "% rproce", ".data", "align 16", "% _stat&curClass& curClass <>", "ptrDefS TEXTEQU <psr>", "ptrDefS CATSTR ptrDefS, <&curClass&>, < TYPEDEF PTR >, <&curClass&>", "% ptrDefS", ".code", "ENDM", NULL,
		"LOCAL sz1, sz2", "sz2 CATSTR <_>, curClass, <_&method>, <Pto>", "% sz1 typedef PTR &sz2", "% method sz1 offset _&curClass&_&method&", "ENDM", NULL,
		"curClass TEXTEQU <className>", "curMethod TEXTEQU <method>", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex, < PROTO thisPtr : psr>, <&className&>", "IFNB <args>", "fnex CATSTR fnex, <, >, <&args&>", "ELSE", "ENDIF", "fnex", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex, <Pto TYPEDEF PROTO thisPtr : psr>, <&className&>", "IFNB <args>", "fnex CATSTR fnex, <, >, <&args&>", "ELSE", "ENDIF", "fnex", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex, < PROC FRAME USES rsi rdi rbx r10 r13 thisPtr : psr>, <&className&>", "IFNB <args>", "fnex CATSTR fnex, <, >, <&args&>", "ELSE", "ENDIF", "assume rcx : ptr curClass", "align 16", "fnex", "ENDM", NULL,
		"curClass TEXTEQU <className>", "curMethod TEXTEQU <method>", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex, < PROTO>", "IFNB <args>", "fnex CATSTR fnex, < >, <&args&>", "ELSE", "ENDIF", "fnex", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex, <Pto TYPEDEF PROTO>", "IFNB <args>", "fnex CATSTR fnex, < >, <&args&>", "ELSE", "ENDIF", "fnex", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex CATSTR fnex, < PROC FRAME USES rsi rdi rbx r10>", "IFNB <args>", "fnex CATSTR fnex, < >, <&args&>", "ELSE", "ENDIF", "assume rcx : ptr curClass", "align 16", "fnex", "ENDM", NULL,
		"assume rcx : nothing", "fnex TEXTEQU <_>", "fnex CATSTR fnex, curClass", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, curMethod", "fnex CATSTR fnex, < ENDP>", "fnex", "ENDM", NULL,
		"ldef TEXTEQU <LOCAL &varName&>", "ldef CATSTR ldef, < : >", "ldef CATSTR ldef, <typeName>", "% ldef", "ENDM", NULL,
		"% lea reg, _stat&curClass&", "ENDM", NULL,
		"mov rax, objPtr", "inc qword ptr[rax + 24]", "ENDM", NULL,
		"mov rax, objPtr", "dec qword ptr[rax + 24]", "ENDM", NULL,
		"mov rax, sizeof(className) + 16", "invoke HeapAlloc, RV(GetProcessHeap), 0, rax", "MEMALIGN rax, 16", ".if (rax != 0)", "mov rdi, rax", "lea rsi, _stat&className", "movdqa xmm0, [rsi]", "movdqa xmm1, [rsi + 16]", "movdqa[rdi], xmm0", "movdqa[rdi + 16], xmm1", "add rsi, 32", "add rdi, 32", "mov rcx, sizeof(className) - 32", "rep movsb", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <Init>", "IFNB <ctorArgs>", "fnex2 TEXTEQU <invoke fnex, rax, ctorArgs>", "ELSE", "fnex2 TEXTEQU <invoke fnex, rax>", "ENDIF", "fnex2", ".endif", "exitm<rax>", "ENDM", NULL,
		"mov rax, sizeof(className) + 16", "invoke HeapAlloc, RV(GetProcessHeap), 0, rax", "MEMALIGN rax, 16", ".if (rax != 0)", "mov rdi, rax", "lea rsi, _stat&className", "movdqa xmm0, [rsi]", "movdqa xmm1, [rsi + 16]", "movdqa[rdi], xmm0", "movdqa[rdi + 16], xmm1", "add rsi, 32", "add rdi, 32", "mov rcx, sizeof(className) - 32", "rep movsb", "fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <Init>", "IFNB <ctorArgs>", "fnex2 TEXTEQU <invoke fnex, rax, ctorArgs>", "ELSE", "fnex2 TEXTEQU <invoke fnex, rax>", "ENDIF", "fnex2", "mov rbx, rax", ".endif", "exitm<rbx>", "ENDM", NULL,
		"exitm<[$V(objPtr, Iterator, Items, idx)]>", "ENDM", NULL,
		"exitm<$V(objPtr, Iterator, Items, idx)>", "ENDM", NULL,
		"fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "IFNB <args>", "fnex2 TEXTEQU <invoke fnex, &objPtr&, &args&>", "ELSE", "fnex2 TEXTEQU <invoke fnex, &objPtr&>", "ENDIF", "fnex2", "ENDM", NULL,
		"fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex2 TEXTEQU <invoke fnex, &objPtr&, &args&>", "fnex2", "exitm<rax>", "ENDM", NULL,
		"fnex TEXTEQU <_>", "fnex CATSTR fnex, <&className&>", "fnex CATSTR fnex, <_>", "fnex CATSTR fnex, <&method&>", "fnex2 TEXTEQU <invoke fnex, &args&>", "fnex2", "exitm<rax>", "ENDM", NULL,
		"mov rax, objPtr", "mov rcx, rax", "call qword ptr[rax + 8]", "invoke HeapFree, RV(GetProcessHeap), 0, rax", "ENDM", NULL,
		"InterfacePtr TEXTEQU <_>", "InterfacePtr CATSTR InterfacePtr, <&Interface>, <_>, <&Function>, <Pto>", "IF(OPATTR(pInterface)) AND 00010000b", "IFNB <args>", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface", "ENDIF", "ELSE", "mov r15, pInterface", "IFNB <args>", "FOR arg, <args>", "IFIDNI <&arg>, <r15>", ".ERR <r15 is not allowed as a Method parameter with indirect object label>", "ENDIF", "ENDM", "invoke(InterfacePtr PTR[r15].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[r15].&Interface.&Function), pInterface", "ENDIF", "ENDIF", "ENDM", NULL,
		"InterfacePtr TEXTEQU <_>", "InterfacePtr CATSTR InterfacePtr, <&Interface>, <_>, <&Function>, <Pto>", "IF(OPATTR(pInterface)) AND 00010000b", "IFNB <args>", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface", "ENDIF", "ELSE", "mov r15, pInterface", "IFNB <args>", "FOR arg, <args>", "IFIDNI <&arg>, <r15>", ".ERR <r15 is not allowed as a Method parameter with indirect object label>", "ENDIF", "ENDM", "invoke(InterfacePtr PTR[r15].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[r15].&Interface.&Function), pInterface", "ENDIF", "ENDIF", "exitm<rax>", "ENDM", NULL,
		"InterfacePtr TEXTEQU <_>", "InterfacePtr CATSTR InterfacePtr, <&Interface>, <_>, <&Function>, <Pto>", "IF(OPATTR(pInterface)) AND 00010000b", "IFNB <args>", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface", "ENDIF", "ELSE", "mov rax, pInterface", "IFNB <args>", "FOR arg, <args>", "IFIDNI <&arg>, <rax>", ".ERR <rax is not allowed as a Method parameter with indirect object label>", "ENDIF", "ENDM", "invoke(InterfacePtr PTR[rax].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[rax].&Interface.&Function), pInterface", "ENDIF", "ENDIF", "exitm<eax>", "ENDM", NULL,
		"InterfacePtr TEXTEQU <_>", "InterfacePtr CATSTR InterfacePtr, <&Interface>, <_>, <&Function>, <Pto>", "IF(OPATTR(pInterface)) AND 00010000b", "IFNB <args>", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface", "ENDIF", "ELSE", "mov rax, pInterface", "IFNB <args>", "FOR arg, <args>", "IFIDNI <&arg>, <rax>", ".ERR <rax is not allowed as a Method parameter with indirect object label>", "ENDIF", "ENDM", "invoke(InterfacePtr PTR[rax].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[rax].&Interface.&Function), pInterface", "ENDIF", "ENDIF", "exitm<ax>", "ENDM", NULL,
		"InterfacePtr TEXTEQU <_>", "InterfacePtr CATSTR InterfacePtr, <&Interface>, <_>, <&Function>, <Pto>", "IF(OPATTR(pInterface)) AND 00010000b", "IFNB <args>", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface", "ENDIF", "ELSE", "mov rax, pInterface", "IFNB <args>", "FOR arg, <args>", "IFIDNI <&arg>, <rax>", ".ERR <rax is not allowed as a Method parameter with indirect object label>", "ENDIF", "ENDM", "invoke(InterfacePtr PTR[rax].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[rax].&Interface.&Function), pInterface", "ENDIF", "ENDIF", "exitm<al>", "ENDM", NULL,
		"InterfacePtr TEXTEQU <_>", "InterfacePtr CATSTR InterfacePtr, <&Interface>, <_>, <&Function>, <Pto>", "IF(OPATTR(pInterface)) AND 00010000b", "IFNB <args>", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface", "ENDIF", "ELSE", "mov rax, pInterface", "IFNB <args>", "FOR arg, <args>", "IFIDNI <&arg>, <rax>", ".ERR <rax is not allowed as a Method parameter with indirect object label>", "ENDIF", "ENDM", "invoke(InterfacePtr PTR[rax].&Interface.&Function), pInterface, &args", "ELSE", "invoke(InterfacePtr PTR[rax].&Interface.&Function), pInterface", "ENDIF", "ENDIF", "exitm<xmm0>", "ENDM", NULL,
		"LOCAL sz1, sz2", "sz2 CATSTR <_>, curClass, <_&method>, <Pto>", "% sz1 typedef PTR &sz2", "% method sz1 offset _&curClass&_&method&", "ENDM", NULL
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
