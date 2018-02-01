arginvoke MACRO argNo:REQ, invCnt:REQ, func:REQ, args:VARARG
	LOCAL dstSize, stackPos
	
	REGS15STORAGE
	
	IFB <args>
		invoke func
	ELSE
		IF invCnt EQ 2
			mov RRCX,rcx
			IF @Arch EQ 0
			movaps RXMM0,xmm0
			ELSE
			vmovaps RXMM0,xmm0
			ENDIF
		ELSEIF invCnt EQ 3
			mov RRCX,rcx
			mov RRDX,rdx
			IF @Arch EQ 0
			movaps RXMM0,xmm0
			movaps RXMM1,xmm1
			ELSE
			vmovaps RXMM0,xmm0
			vmovaps RXMM1,xmm1
			ENDIF
		ELSEIF invCnt EQ 4
			mov RRCX,rcx
			mov RRDX,rdx
			mov RR8,r8
			IF @Arch EQ 0
			movaps RXMM0,xmm0
			movaps RXMM1,xmm1
			movaps RXMM2,xmm2
			ELSE
			vmovaps RXMM0,xmm0
			vmovaps RXMM1,xmm1
			vmovaps RXMM2,xmm2
			ENDIF
		ELSEIF invCnt GE 5
			mov RRCX,rcx
			mov RRDX,rdx
			mov RR8,r8
			mov RR9,r9
			IF @Arch EQ 0
			movaps RXMM0,xmm0
			movaps RXMM1,xmm1
			movaps RXMM2,xmm2
			movaps RXMM3,xmm3
			ELSE
			vmovaps RXMM0,xmm0
			vmovaps RXMM1,xmm1
			vmovaps RXMM2,xmm2
			vmovaps RXMM3,xmm3
			ENDIF
		ENDIF
		invoke func, args
		IF invCnt EQ 2
			mov rcx,RRCX
			IF @Arch EQ 0
			movaps xmm0,RXMM0
			ELSE
			vmovaps xmm0,RXMM0
			ENDIF
		ELSEIF invCnt EQ 3
			mov rcx,RRCX
			mov rdx,RRDX
			IF @Arch EQ 0
			movaps xmm0,RXMM0
			movaps xmm1,RXMM1
			ELSE
			vmovaps xmm0,RXMM0
			vmovaps xmm1,RXMM1
			ENDIF
		ELSEIF invCnt EQ 4
			mov rcx,RRCX
			mov rdx,RRDX
			mov r8,RR8
			IF @Arch EQ 0
			movaps xmm0,RXMM0
			movaps xmm1,RXMM1
			movaps xmm2,RXMM2
			ELSE
			vmovaps xmm0,RXMM0
			vmovaps xmm1,RXMM1
			vmovaps xmm2,RXMM2
			ENDIF
		ELSEIF invCnt GE 5
			mov rcx,RRCX
			mov rdx,RRDX
			mov r8,RR8
			mov r9,RR9
			IF @Arch EQ 0
			movaps xmm0,RXMM0
			movaps xmm1,RXMM1
			movaps xmm2,RXMM2
			movaps xmm3,RXMM3
			ELSE
			vmovaps xmm0,RXMM0
			vmovaps xmm1,RXMM1
			vmovaps xmm2,RXMM2
			vmovaps xmm3,RXMM3
			ENDIF
		ENDIF	
	ENDIF

	IF @LastReturnType EQ 0
		dstSize = 1
	ELSEIF @LastReturnType EQ 0x40
		dstSize = 1
	ELSEIF @LastReturnType EQ 1
		dstSize = 2
	ELSEIF @LastReturnType EQ 0x41
		dstSize = 2
	ELSEIF @LastReturnType EQ 2
		dstSize = 4
	ELSEIF @LastReturnType EQ 0x42
		dstSize = 4
	ELSEIF @LastReturnType EQ 3
		dstSize = 8
	ELSEIF @LastReturnType EQ 0x43
		dstSize = 8
	ELSEIF @LastReturnType EQ 0xc3
		dstSize = 8
	ELSEIF @LastReturnType EQ 6
		dstSize = 16
	ELSEIF @LastReturnType EQ 7
		dstSize = 32
	ELSEIF @LastReturnType EQ 8
		dstSize = 64
	ELSEIF @LastReturnType EQ 0x22
		dstSize = 16
	ELSEIF @LastReturnType EQ 0x23
		dstSize = 16
	ELSE
		dstSize = 4
	ENDIF

	IF argNo EQ 1
		IF dstSize EQ 1
			mov cl,al
			EXITM<cl>
		ELSEIF dstSize EQ 2
			mov cx,ax
			EXITM<cx>
		ELSEIF dstSize EQ 4
			mov ecx,eax
			EXITM<ecx>
		ELSEIF dstSize EQ 8
			mov rcx,rax
			EXITM<rcx>
		ELSEIF dstSize EQ 16
			EXITM<xmm0>
		ELSEIF dstSize EQ 32
			EXITM<ymm0>
		ELSEIF dstSize EQ 64	
			EXITM<zmm0>
		ENDIF
	ELSEIF argNo EQ 2
		IF dstSize EQ 1
			mov dl,al
			EXITM<dl>
		ELSEIF dstSize EQ 2
			mov dx,ax
			EXITM<dx>
		ELSEIF dstSize EQ 4
			mov edx,eax
			EXITM<edx>
		ELSEIF dstSize EQ 8
			mov rdx,rax
			EXITM<rdx>
		ELSEIF dstSize EQ 16
			IF @Arch EQ 0
				movdqa xmm1,xmm0
			ELSE
				vmovdqa xmm1,xmm0
			ENDIF
			EXITM<xmm1>
		ELSEIF dstSize EQ 32
			vmovdqa ymm1,ymm0
			EXITM<ymm1>
		ELSEIF dstSize EQ 64	
			vmovdqa zmm1,zmm0
			EXITM<zmm1>
		ENDIF
	ELSEIF argNo EQ 3
		IF dstSize EQ 1
			mov r8b,al
			EXITM<r8b>
		ELSEIF dstSize EQ 2
			mov r8w,ax
			EXITM<r8w>
		ELSEIF dstSize EQ 4
			mov r8d,eax
			EXITM<r8d>
		ELSEIF dstSize EQ 8
			mov r8,rax
			EXITM<r8>
		ELSEIF dstSize EQ 16
			IF @Arch EQ 0
				movdqa xmm2,xmm0
			ELSE
				vmovdqa xmm2,xmm0
			ENDIF
			EXITM<xmm2>
		ELSEIF dstSize EQ 32
			vmovdqa ymm2,ymm0
			EXITM<ymm2>
		ELSEIF dstSize EQ 64	
			vmovdqa zmm2,zmm0
			EXITM<zmm2>
		ENDIF
	ELSEIF argNo EQ 4
		IF dstSize EQ 1
			mov r9b,al
			EXITM<r9b>
		ELSEIF dstSize EQ 2
			mov r9w,ax
			EXITM<r9w>
		ELSEIF dstSize EQ 4
			mov r9d,eax
			EXITM<r9d>
		ELSEIF dstSize EQ 8
			mov r9,rax
			EXITM<r9>
		ELSEIF dstSize EQ 16
			IF @Arch EQ 0
				movdqa xmm3,xmm0
			ELSE
				vmovdqa xmm3,xmm0
			ENDIF
			EXITM<xmm3>
		ELSEIF dstSize EQ 32
			vmovdqa ymm3,ymm0
			EXITM<ymm3>
		ELSEIF dstSize EQ 64	
			vmovdqa zmm3,zmm0
			EXITM<zmm3>
		ENDIF
	ELSE
		IF dstSize EQ 1
			mov [rsp+0x20+((argNo-5)*8)],al
		ELSEIF dstSize EQ 2
			mov [rsp+0x20+((argNo-5)*8)],ax
		ELSEIF dstSize EQ 4
			mov [rsp+0x20+((argNo-5)*8)],eax
		ELSEIF dstSize EQ 8
			mov [rsp+0x20+((argNo-5)*8)],rax
		ELSEIF (dstSize EQ 16) OR (dstSize EQ 32) OR (dstSize EQ 64)
			IF @Arch EQ 0
				movsd [rsp+0x20+((argNo-5)*8)],xmm0
			ELSE
				vmovsd [rsp+0x20+((argNo-5)*8)],xmm0
			ENDIF
		ENDIF
		EXITM<[rsp+0x20+((argNo-5)*8)]>
	ENDIF
ENDM

_ARRAY MACRO arrType:REQ,sizeArr:REQ
cdef TEXTEQU <__&arrType&_def>
% IFDEF cdef
mov rax,8
ELSE
mov rax,sizeof(arrType)
ENDIF
imul rax,sizeArr
MEMALLOC(rax)
exitm<rax>
ENDM

_DELETEARRAY MACRO arrPtr:REQ
MEMFREE(arrPtr)
ENDM

OINTERFACE MACRO CName:REQ
% __&CName&_def EQU 1
% __&CName&_size = 16
curClass TEXTEQU <CName>
@CatStr(CName, <vtbl CSTRUCT >)
__0 dq 0
__1 dq 0
ENDM

ENDOINTERFACE MACRO
curClass ENDS
ptrDefS TEXTEQU <psr>
ptrDefS CATSTR ptrDefS, <&curClass&>, < TYPEDEF PTR >, <&curClass&>
% ptrDefS
ENDM

CVIRTUAL MACRO method:REQ, retType:REQ, protoDef:VARARG
LOCAL sz1, sz2
pDef CATSTR <TYPEDEF PROTO >,<&retType&>,< thisPtr:PTR>
IFNB <protoDef>
pDef CATSTR pDef, <, >, <&protoDef>
ENDIF
sz2 CATSTR <_>, curClass, <_&method>, <Pto>
% &sz2 &pDef
% sz1 typedef PTR &sz2
% method sz1 0
% __&curClass&_size = __&curClass&_size + 8
fnex TEXTEQU <_>
fnex CATSTR fnex, curClass, <_>, <&method&>, < PROTO >, <&retType&>, < thisPtr:psr>, curClass
IFNB <args>
fnex CATSTR fnex, <, >, <&args&>
ELSE
ENDIF
fnex
ENDM

CLASS MACRO CName:REQ
% __&CName&_def EQU 1
% __&CName&_size = 16
curClass TEXTEQU <CName>
@CatStr(CName, <vtbl CSTRUCT >)
ctorS TEXTEQU <ctor dq offset _&CName&_Init>
dtorS TEXTEQU <dtor dq offset _&CName&_Destroy>
ctorS
dtorS
ENDM

ENDCLASS MACRO
curClass ENDS
.data
align 16
% _stat&curClass&vtbl &curClass&vtbl <>
% _stat&curClass& curClass <>
ptrDefS TEXTEQU <psr>
ptrDefS CATSTR ptrDefS, <&curClass&>, < TYPEDEF PTR >, <&curClass&>
% ptrDefS
ptrDefS2 TEXTEQU <psr>
ptrDefS2 CATSTR ptrDefS2, <&curClass&vtbl>, < TYPEDEF PTR >, <&curClass&vtbl>
% ptrDefS2
.code
ENDM

ENDMETHODS MACRO
LOCAL evtbl
% evtbl CATSTR <&curClass&>,<vtbl>,< ENDS>
evtbl
@CatStr(curClass, < CSTRUCT >)
% pVtbl dq offset _stat&curClass&vtbl
ENDM

CMETHOD MACRO method:REQ
LOCAL sz1, sz2
sz2 CATSTR <_>, curClass, <_&method>, <Pto>
% sz1 typedef PTR &sz2
% method sz1 offset _&curClass&_&method&
% __&curClass&_size = __&curClass&_size + 8
ENDM

CSTATIC MACRO method:REQ
LOCAL sz1, sz2
sz2 CATSTR <_>, curClass, <_&method>, <Pto>
% sz1 typedef PTR &sz2
% method sz1 offset _&curClass&_&method&
% __&curClass&_size = __&curClass&_size + 8
ENDM

METHOD MACRO className:REQ, method:REQ, retType:=<dword>, usesStr:=<USES rbx rsi rdi>, args:VARARG
curClass TEXTEQU <className>
curMethod TEXTEQU <method>
fnex TEXTEQU <_>
fnex CATSTR fnex, <&className&>
fnex CATSTR fnex, <_>
fnex CATSTR fnex, <&method&>
fnex CATSTR fnex, < PROTO >, <&retType&> , < thisPtr:psr>, <&className&>
IFNB <args>
fnex CATSTR fnex, <, >, <&args&>
ELSE
ENDIF
fnex
fnex TEXTEQU <_>
fnex CATSTR fnex, <&className&>
fnex CATSTR fnex, <_>
fnex CATSTR fnex, <&method&>
fnex CATSTR fnex, <Pto TYPEDEF PROTO >,<&retType&>,< thisPtr:psr>, <&className&>
IFNB <args>
fnex CATSTR fnex, <, >, <&args&>
ELSE
ENDIF
fnex
fnex TEXTEQU <_>
fnex CATSTR fnex, <&className&>
fnex CATSTR fnex, <_>
fnex CATSTR fnex, <&method&>
fnex CATSTR fnex,< PROC >, <&retType&>, < >, <&usesStr&>, < thisPtr:psr>, <&className&>
IFNB <args>
fnex CATSTR fnex, <, >, <&args&>
ELSE
ENDIF
IF @Platform EQ 1
assume rcx:ptr curClass
ELSE
assume rdi:ptr curClass
ENDIF
align 16
fnex
ENDM

STATICMETHOD MACRO className:REQ, method:REQ, retType:=<dword>, usesStr:=<USES rbx rsi rdi>, args:VARARG
curClass TEXTEQU <className>
curMethod TEXTEQU <method>
fnex TEXTEQU <_>
fnex CATSTR fnex, <&className&>
fnex CATSTR fnex, <_>
fnex CATSTR fnex, <&method&>
fnex CATSTR fnex, < PROTO >, <&retType&>
IFNB <args>
fnex CATSTR fnex, < >, <&args&>
ELSE
ENDIF
fnex
fnex TEXTEQU <_>
fnex CATSTR fnex, <&className&>
fnex CATSTR fnex, <_>
fnex CATSTR fnex, <&method&>
fnex CATSTR fnex, <Pto TYPEDEF PROTO >,<&retType&>
IFNB <args>
fnex CATSTR fnex, < >, <&args&>
ELSE
ENDIF
fnex
fnex TEXTEQU <_>
fnex CATSTR fnex, <&className&>
fnex CATSTR fnex, <_>
fnex CATSTR fnex, <&method&>
fnex CATSTR fnex,< PROC >, <&retType&>, < >, <&usesStr&>
IFNB <args>
fnex CATSTR fnex, < >, <&args&>
ELSE
ENDIF
IF @Platform EQ 1
assume rcx:ptr curClass
ELSE
assume rdi:ptr curClass
ENDIF
align 16
fnex
ENDM

VECMETHOD MACRO className:REQ, method:REQ, retType:=<dword>, usesStr:=<USES rbx rsi rdi>, args:VARARG
curClass TEXTEQU <className>
curMethod TEXTEQU <method>
fnex TEXTEQU <_>
fnex CATSTR fnex, <&className&>
fnex CATSTR fnex, <_>
fnex CATSTR fnex, <&method&>
fnex CATSTR fnex, < PROTO VECTORCALL >, <&retType&> , < thisPtr:psr>, <&className&>
IFNB <args>
fnex CATSTR fnex, <, >, <&args&>
ELSE
ENDIF
fnex
fnex TEXTEQU <_>
fnex CATSTR fnex, <&className&>
fnex CATSTR fnex, <_>
fnex CATSTR fnex, <&method&>
fnex CATSTR fnex, <Pto TYPEDEF PROTO VECTORCALL >,<&retType&>,< thisPtr:psr>, <&className&>
IFNB <args>
fnex CATSTR fnex, <, >, <&args&>
ELSE
ENDIF
fnex
fnex TEXTEQU <_>
fnex CATSTR fnex, <&className&>
fnex CATSTR fnex, <_>
fnex CATSTR fnex, <&method&>
fnex CATSTR fnex,< PROC VECTORCALL >, <&retType&>, < >, <&usesStr&>, < thisPtr:psr>, <&className&>
IFNB <args>
fnex CATSTR fnex, <, >, <&args&>
ELSE
ENDIF
IF @Platform EQ 1
assume rcx:ptr curClass
ELSE
assume rdi:ptr curClass
ENDIF
align 16
fnex
ENDM

STATICVECMETHOD MACRO className:REQ, method:REQ, retType:=<dword>, usesStr:=<USES rbx rsi rdi>, args:VARARG
curClass TEXTEQU <className>
curMethod TEXTEQU <method>
fnex TEXTEQU <_>
fnex CATSTR fnex, <&className&>
fnex CATSTR fnex, <_>
fnex CATSTR fnex, <&method&>
fnex CATSTR fnex, < PROTO VECTORCALL >, <&retType&>
IFNB <args>
fnex CATSTR fnex, < >, <&args&>
ELSE
ENDIF
fnex
fnex TEXTEQU <_>
fnex CATSTR fnex, <&className&>
fnex CATSTR fnex, <_>
fnex CATSTR fnex, <&method&>
fnex CATSTR fnex, <Pto TYPEDEF PROTO VECTORCALL >,<&retType&>
IFNB <args>
fnex CATSTR fnex, < >, <&args&>
ELSE
ENDIF
fnex
fnex TEXTEQU <_>
fnex CATSTR fnex, <&className&>
fnex CATSTR fnex, <_>
fnex CATSTR fnex, <&method&>
fnex CATSTR fnex,< PROC VECTORCALL >, <&retType&>, < >, <&usesStr&>
IFNB <args>
fnex CATSTR fnex, < >, <&args&>
ELSE
ENDIF
IF @Platform EQ 1
assume rcx:ptr curClass
ELSE
assume rdi:ptr curClass
ENDIF
align 16
fnex
ENDM

ENDMETHOD MACRO
IF @Platform EQ 1
assume rcx:nothing
ELSE
assume rdi:nothing
ENDIF
fnex TEXTEQU <_>
fnex CATSTR fnex, curClass
fnex CATSTR fnex, <_>
fnex CATSTR fnex, curMethod
fnex CATSTR fnex, < ENDP>
fnex
ENDM

_DECLARE MACRO varName:REQ, typeName:VARARG
ldef TEXTEQU <LOCAL &varName&>
ldef CATSTR ldef, < : >
ldef CATSTR ldef, <typeName>
% ldef
ENDM

_STATICREF MACRO reg:REQ
% lea reg,_stat&curClass&
ENDM

_NEW MACRO className:REQ, ctorArgs:VARARG
% mov r8, sizeof(className)
MEMALLOC(r8)
.if (rax != 0)
mov rdi,rax
% lea rsi,_stat&className
% mov rcx, sizeof(className)
rep movsb
fnex TEXTEQU <_>
fnex CATSTR fnex, <&className&>
fnex CATSTR fnex, <_>
fnex CATSTR fnex, <Init>
IFNB <ctorArgs>
fnex2 TEXTEQU <invoke fnex, rax, ctorArgs>
ELSE
fnex2 TEXTEQU <invoke fnex, rax>
ENDIF
fnex2
.endif
exitm<rax>
ENDM

_RBXNEW MACRO className:REQ, ctorArgs:VARARG
% mov r8, sizeof(className)
MEMALLOC(r8)
.if (rax != 0)
mov rdi,rax
% lea rsi,_stat&className
% mov rcx, sizeof(className)
rep movsb
fnex TEXTEQU <_>
fnex CATSTR fnex, <&className&>
fnex CATSTR fnex, <_>
fnex CATSTR fnex, <Init>
IFNB <ctorArgs>
fnex2 TEXTEQU <invoke fnex, rax, ctorArgs>
ELSE
fnex2 TEXTEQU <invoke fnex, rax>
ENDIF
fnex2
mov rbx, rax
.endif
exitm<rbx>
ENDM

_ITEM MACRO objPtr:REQ, idx:REQ
exitm<[_V(objPtr, Iterator, Items, idx)]>
ENDM

_ITEMR MACRO objPtr:REQ, idx:REQ
exitm<_V(objPtr, Iterator, Items, idx)>
ENDM

_INVOKE MACRO className:REQ, method:REQ, objPtr:REQ, args:VARARG
fnex TEXTEQU <_>
fnex CATSTR fnex, <&className&>
fnex CATSTR fnex, <_>
fnex CATSTR fnex, <&method&>
IFNB <args>
fnex2 TEXTEQU <invoke fnex, &objPtr&, &args&>
ELSE
fnex2 TEXTEQU <invoke fnex, &objPtr&>
ENDIF
fnex2
ENDM

_I MACRO className:REQ, method:REQ, objPtr:REQ, args:VARARG
fnex TEXTEQU <_>
fnex CATSTR fnex, <&className&>
fnex CATSTR fnex, <_>
fnex CATSTR fnex, <&method&>
fnex2 TEXTEQU <invoke fnex, &objPtr&, &args&>
fnex2
IF @LastReturnType EQ 0
EXITM <al>
ELSEIF @LastReturnType EQ 0x40
EXITM <al>
ELSEIF @LastReturnType EQ 1
EXITM <ax>
ELSEIF @LastReturnType EQ 0x41
EXITM <ax>
ELSEIF @LastReturnType EQ 2
EXITM <eax>
ELSEIF @LastReturnType EQ 0x42
EXITM <eax>
ELSEIF @LastReturnType EQ 3
EXITM <rax>
ELSEIF @LastReturnType EQ 0x43
EXITM <rax>
ELSEIF @LastReturnType EQ 0xc3
EXITM <rax>
ELSEIF @LastReturnType EQ 6
EXITM <xmm0>
ELSEIF @LastReturnType EQ 7
EXITM <ymm0>
ELSEIF @LastReturnType EQ 8
EXITM <zmm0>
ELSEIF @LastReturnType EQ 0x22
EXITM <xmm0>
ELSEIF @LastReturnType EQ 0x23
EXITM <xmm0>
ELSE
EXITM <eax>
ENDIF
ENDM

_STATIC MACRO className : REQ, method : REQ, args : VARARG
fnex TEXTEQU <_>
fnex CATSTR fnex, <&className&>
fnex CATSTR fnex, <_>
fnex CATSTR fnex, <&method&>
fnex2 TEXTEQU <invoke fnex, &args&>
fnex2
IF @LastReturnType EQ 0
EXITM <al>
ELSEIF @LastReturnType EQ 0x40
EXITM <al>
ELSEIF @LastReturnType EQ 1
EXITM <ax>
ELSEIF @LastReturnType EQ 0x41
EXITM <ax>
ELSEIF @LastReturnType EQ 2
EXITM <eax>
ELSEIF @LastReturnType EQ 0x42
EXITM <eax>
ELSEIF @LastReturnType EQ 3
EXITM <rax>
ELSEIF @LastReturnType EQ 0x43
EXITM <rax>
ELSEIF @LastReturnType EQ 0xc3
EXITM <rax>
ELSEIF @LastReturnType EQ 6
EXITM <xmm0>
ELSEIF @LastReturnType EQ 7
EXITM <ymm0>
ELSEIF @LastReturnType EQ 8
EXITM <zmm0>
ELSEIF @LastReturnType EQ 0x22
EXITM <xmm0>
ELSEIF @LastReturnType EQ 0x23
EXITM <xmm0>
ELSE
EXITM <eax>
ENDIF
ENDM

_DELETE MACRO objPtr:REQ
IF @Platform EQ 1
mov rcx, objPtr
mov rax, [rcx]
call qword ptr[rax + 8]
ELSE
mov rdi, objPtr
mov rax, [rdi]
call qword ptr[rax + 8]
ENDIF
MEMFREE(objPtr)
ENDM

_VINVOKE MACRO pInterface:REQ, Interface:REQ, Function:REQ, args:VARARG
InterfacePtr TEXTEQU <_>
InterfacePtr CATSTR InterfacePtr, <&Interface>, <_>, <&Function>, <Pto>
IF(OPATTR(pInterface)) AND 00010000b
IFNB <args>
IF @Platform EQ 1
mov rcx,&pInterface
mov r15,[rcx]
invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rcx, &args
ELSE
mov rdi,&pInterface
mov r15,[rdi]
invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rdi, &args
ENDIF
ELSE
IF @Platform EQ 1
mov rcx,&pInterface
mov r15,[rcx]
invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rcx
ELSE
mov rdi,&pInterface
mov r15,[rdi]
invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rdi
ENDIF
ENDIF
ELSE
mov rcx,pInterface
mov r15,[rcx]
IFNB <args>
FOR arg, <args>
IFIDNI <&arg>, <rcx>
.ERR <rcx is not allowed as a Method parameter with indirect object label>
ENDIF
ENDM
invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rcx, &args
ELSE
invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rcx
ENDIF
ENDIF
ENDM

_V MACRO pInterface:REQ, Interface:REQ, Function:REQ, args:VARARG
InterfacePtr TEXTEQU <_>
InterfacePtr CATSTR InterfacePtr, <&Interface>, <_>, <&Function>, <Pto>
IF(OPATTR(pInterface)) AND 00010000b
IFNB <args>
IF @Platform EQ 1
mov rcx,&pInterface
mov r15,[rcx]
invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rcx, &args
ELSE
mov rdi,&pInterface
mov r15,[rdi]
invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rdi, &args
ENDIF
ELSE
IF @Platform EQ 1
mov rcx,&pInterface
mov r15,[rcx]
invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rcx
ELSE
mov rdi,&pInterface
mov r15,[rdi]
invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rdi
 ENDIF
ENDIF
ELSE
IF @Platform EQ 1
mov rcx,pInterface
mov r15,[rcx]
IFNB <args>
FOR arg, <args>
IFIDNI <&arg>, <rcx>
.ERR <rcx is not allowed as a Method parameter with indirect object label>
ENDIF
ENDM
invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rcx, &args
ELSE
invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rcx
ENDIF
ELSE
mov rdi,pInterface
mov r15,[rdi]
IFNB <args>
FOR arg, <args>
IFIDNI <&arg>, <rdi>
.ERR <rdi is not allowed as a Method parameter with indirect object label>
ENDIF
ENDM
invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rdi, &args
ELSE
invoke(InterfacePtr PTR[r15].&Interface&vtbl.&Function), rdi
ENDIF    
ENDIF
ENDIF
IF @LastReturnType EQ 0
EXITM <al>
ELSEIF @LastReturnType EQ 0x40
EXITM <al>
ELSEIF @LastReturnType EQ 1
EXITM <ax>
ELSEIF @LastReturnType EQ 0x41
EXITM <ax>
ELSEIF @LastReturnType EQ 2
EXITM <eax>
ELSEIF @LastReturnType EQ 0x42
EXITM <eax>
ELSEIF @LastReturnType EQ 3
EXITM <rax>
ELSEIF @LastReturnType EQ 0x43
EXITM <rax>
ELSEIF @LastReturnType EQ 0xc3
EXITM <rax>
ELSEIF @LastReturnType EQ 6
EXITM <xmm0>
ELSEIF @LastReturnType EQ 7
EXITM <ymm0>
ELSEIF @LastReturnType EQ 8
EXITM <zmm0>
ELSEIF @LastReturnType EQ 0x22
EXITM <xmm0>
ELSEIF @LastReturnType EQ 0x23
EXITM <xmm0>
ELSE
EXITM <eax>
ENDIF
ENDM

;delete release, acquire, _vd, _vb, _vw, _vf

COMINTERFACE MACRO CName:REQ
curClass TEXTEQU <CName>
@CatStr(CName, <vtbl COMSTRUCT >)
CVIRTUAL QueryInterface, <>, :PTR
CVIRTUAL AddRef, <>
CVIRTUAL Release, <>
ENDM

ENDCOMINTERFACE MACRO
ENDMETHODS
curClass ENDS
ENDM

_VCOMINVOKE MACRO pInterface:REQ, Interface:REQ, Function:REQ, args:VARARG
InterfacePtr TEXTEQU <_>
InterfacePtr CATSTR InterfacePtr, <&Interface>, <_>, <&Function>, <Pto>
IF(OPATTR(pInterface)) AND 00010000b
IFNB <args>
invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface, &args
ELSE
invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface
ENDIF
ELSE
mov rcx, pInterface
mov r15,[rcx]
IFNB <args>
FOR arg, <args>
IFIDNI <&arg>, <rcx>
.ERR <rcx is not allowed as a Method parameter with indirect object label>
ENDIF
ENDM
invoke(InterfacePtr PTR[r15].&Interface.&Function), rcx, &args
ELSE
invoke(InterfacePtr PTR[r15].&Interface.&Function), rcx
ENDIF
ENDIF
ENDM

_VCOM MACRO pInterface:REQ, Interface:REQ, Function:REQ, args:VARARG
InterfacePtr TEXTEQU <_>
InterfacePtr CATSTR InterfacePtr, <&Interface>, <_>, <&Function>, <Pto>
IF(OPATTR(pInterface)) AND 00010000b
IFNB <args>
invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface, &args
ELSE
invoke(InterfacePtr PTR[&pInterface].&Interface.&Function), pInterface
ENDIF
ELSE
mov rcx, pInterface
mov r15,[rcx]
IFNB <args>
FOR arg, <args>
IFIDNI <&arg>, <rcx>
.ERR <rcx is not allowed as a Method parameter with indirect object label>
ENDIF
ENDM
invoke(InterfacePtr PTR[r15].&Interface.&Function), rcx, &args
ELSE
invoke(InterfacePtr PTR[r15].&Interface.&Function), rcx
ENDIF
ENDIF
IF @LastReturnType EQ 0
EXITM <al>
ELSEIF @LastReturnType EQ 0x40
EXITM <al>
ELSEIF @LastReturnType EQ 1
EXITM <ax>
ELSEIF @LastReturnType EQ 0x41
EXITM <ax>
ELSEIF @LastReturnType EQ 2
EXITM <eax>
ELSEIF @LastReturnType EQ 0x42
EXITM <eax>
ELSEIF @LastReturnType EQ 3
EXITM <rax>
ELSEIF @LastReturnType EQ 0x43
EXITM <rax>
ELSEIF @LastReturnType EQ 0xc3
EXITM <rax>
ELSEIF @LastReturnType EQ 6
EXITM <xmm0>
ELSEIF @LastReturnType EQ 7
EXITM <ymm0>
ELSEIF @LastReturnType EQ 8
EXITM <zmm0>
ELSEIF @LastReturnType EQ 0x22
EXITM <xmm0>
ELSEIF @LastReturnType EQ 0x23
EXITM <xmm0>
ELSE
EXITM <eax>
ENDIF
ENDM


_DEREF MACRO itype:REQ, proc:REQ, argCount:REQ, argsAndRefs:VARARG
    LOCAL i, ptrstr, typestr, argstr
    argstr TEXTEQU < >
    i = 0
    FOR dref, <argsAndRefs>
        IF i LT argCount+1 
			IF i GT 0
				argstr CATSTR argstr, <,>, <&dref&>
			ENDIF
        ELSE
            IF (i-argCount) MOD 2 EQ 1
                ptrstr TEXTEQU <&dref&>
            ELSE
                typestr TEXTEQU <&dref&>
                IF (i-argCount) EQ 1
                    % IF(OPATTR(ptrstr)) EQ 0x30
                        % mov rcx, &ptrstr&
                    ELSE
                        % mov rcx, @CatStr(<[>, <&ptrstr&>, <].>, <&typestr&>)
                    ENDIF
                ELSE
                    % mov rcx, @CatStr(<[>, <&ptrstr&>, <].>, <&typestr&>)
                ENDIF
            ENDIF
        ENDIF
    i = i + 1
    ENDM

	% IF @SizeStr(<%&argstr&>) GT 3
		argstr SUBSTR argstr, 3
	ENDIF
	IF argCount EQ 0
	   argstr TEXTEQU <>
	ENDIF
	
    IF argCount GT 0
	    InterfacePtr TEXTEQU <_>
        InterfacePtr CATSTR InterfacePtr, <&itype>, <_>, <&proc>, <Pto>
        IF(OPATTR(rcx)) AND 00010000b
            IF argCount GT 0
                IF @Platform EQ 1
                    mov r15,[rcx]
                    % invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx, &argstr
                ELSE
                    mov rdi,rcx
                    mov r15,[rdi]
                    % invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rdi, &argstr
                ENDIF
            ELSE
                IF @Platform EQ 1
                    mov r15,[rcx]
                    % invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx
                ELSE
                    mov rdi,rcx
                    mov r15,[rdi]
                    % invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rdi
                ENDIF
            ENDIF
        ELSE
            mov r15,[rcx]
            IF argCount GT 0
                FOR arg, <argstr>
                    IFIDNI <&arg>, <rcx>
                        .ERR <rcx is not allowed as a Method parameter with indirect object label>
                    ENDIF
                ENDM
                % invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx, &argstr
            ELSE
                invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx
            ENDIF
        ENDIF
    ELSE
        InterfacePtr TEXTEQU <_>
        InterfacePtr CATSTR InterfacePtr, <&itype>, <_>, <&proc>, <Pto>
        IF(OPATTR(rcx)) AND 00010000b
            IF argCount GT 0
                IF @Platform EQ 1
                    mov r15,[rcx]
                    % invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx, &argstr
                ELSE
                    mov rdi,rcx
                    mov r15,[rdi]
                    % invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rdi, &argstr
                ENDIF
            ELSE
                IF @Platform EQ 1
                    mov r15,[rcx]
                    invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx
                ELSE
                    mov rdi,rcx
                    mov r15,[rdi]
                    invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rdi
                ENDIF
            ENDIF
        ELSE
            mov r15,[rcx]
            IF argCount GT 0
                FOR arg, <argstr>
                    IFIDNI <&arg>, <rcx>
                        .ERR <rcx is not allowed as a Method parameter with indirect object label>
                    ENDIF
                ENDM
                % invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx, &argstr
            ELSE
                invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx
            ENDIF
        ENDIF
    ENDIF
ENDM

_DEREFI MACRO itype:REQ, proc:REQ,  argCount:REQ, argsAndRefs:VARARG
   LOCAL i, ptrstr, typestr, argstr
    argstr TEXTEQU < >
    i = 0
    FOR dref, <argsAndRefs>
        IF i LT argCount OR argCount EQ 0
			IF argCount GT 0
				argstr CATSTR argstr, <,>, <&dref&>
			ENDIF
        ELSE
            IF (i-argCount) MOD 2 EQ 0
                ptrstr TEXTEQU <&dref&>
            ELSE
                typestr TEXTEQU <&dref&>
                IF (i-argCount) EQ 1
                    % IF(OPATTR(ptrstr)) EQ 0x30
                        % mov rcx, &ptrstr&
                    ELSE
                        % mov rcx, @CatStr(<[>, <&ptrstr&>, <].>, <&typestr&>)
                    ENDIF
                ELSE
                    % mov rcx, @CatStr(<[>, <&ptrstr&>, <].>, <&typestr&>)
                ENDIF
            ENDIF
        ENDIF
    i = i + 1
    ENDM

	% IF @SizeStr(<%&argstr&>) GT 3
		argstr SUBSTR argstr, 3
	ENDIF
	
    IFNB <argstr>
        InterfacePtr TEXTEQU <_>
        InterfacePtr CATSTR InterfacePtr, <&itype>, <_>, <&proc>, <Pto>
        IF(OPATTR(rcx)) AND 00010000b
            IFNB <argstr>
                IF @Platform EQ 1
                    mov r15,[rcx]
                    % invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx, &argstr
                ELSE
                    mov rdi,rcx
                    mov r15,[rdi]
                    % invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rdi, &argstr
                ENDIF
            ELSE
                IF @Platform EQ 1
                    mov r15,[rcx]
                    % invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx
                ELSE
                    mov rdi,rcx
                    mov r15,[rdi]
                    % invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rdi
                ENDIF
            ENDIF
        ELSE
            mov r15,[rcx]
            IFNB <argstr>
                FOR arg, <argstr>
                    IFIDNI <&arg>, <rcx>
                        .ERR <rcx is not allowed as a Method parameter with indirect object label>
                    ENDIF
                ENDM
                % invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx, &argstr
            ELSE
                invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx
            ENDIF
        ENDIF
    ELSE
        InterfacePtr TEXTEQU <_>
        InterfacePtr CATSTR InterfacePtr, <&itype>, <_>, <&proc>, <Pto>
        IF(OPATTR(rcx)) AND 00010000b
            IFNB <argstr>
                IF @Platform EQ 1
                    mov r15,[rcx]
                    % invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx, &argstr
                ELSE
                    mov rdi,rcx
                    mov r15,[rdi]
                    % invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rdi, &argstr
                ENDIF
            ELSE
                IF @Platform EQ 1
                    mov r15,[rcx]
                    invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx
                ELSE
                    mov rdi,rcx
                    mov r15,[rdi]
                    invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rdi
                ENDIF
            ENDIF
        ELSE
            mov r15,[rcx]
            IFNB <argstr>
                FOR arg, <argstr>
                    IFIDNI <&arg>, <rcx>
                        .ERR <rcx is not allowed as a Method parameter with indirect object label>
                    ENDIF
                ENDM
                % invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx, &argstr
            ELSE
                invoke(InterfacePtr PTR[r15].&itype&vtbl.&proc), rcx
            ENDIF
        ENDIF
    ENDIF

    IF @LastReturnType EQ 0
        EXITM <al>
    ELSEIF @LastReturnType EQ 0x40
        EXITM <al>
    ELSEIF @LastReturnType EQ 1
        EXITM <ax>
    ELSEIF @LastReturnType EQ 0x41
        EXITM <ax>
    ELSEIF @LastReturnType EQ 2
        EXITM <eax>
    ELSEIF @LastReturnType EQ 0x42
        EXITM <eax>
    ELSEIF @LastReturnType EQ 3
        EXITM <rax>
    ELSEIF @LastReturnType EQ 0x43
        EXITM <rax>
    ELSEIF @LastReturnType EQ 0xc3
        EXITM <rax>
    ELSEIF @LastReturnType EQ 6
        EXITM <xmm0>
    ELSEIF @LastReturnType EQ 7
        EXITM <ymm0>
    ELSEIF @LastReturnType EQ 8
        EXITM <zmm0>
    ELSEIF @LastReturnType EQ 0x22
        EXITM <xmm0>
    ELSEIF @LastReturnType EQ 0x23
        EXITM <xmm0>
    ELSE
        EXITM <eax>
    ENDIF

ENDM