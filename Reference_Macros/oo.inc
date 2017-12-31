
; Allocate an array of structs (using their actual size) or an array of object pointers (8bytes per pointer).
$ARRAY MACRO arrType:REQ,sizeArr:REQ

	cdef TEXTEQU <__&arrType&_def>				; If the type exists as a class/object then we allocate the array based on a pointer, otherwise normal structs allocate to their true size.
	% IFDEF cdef
		mov r8,8
	ELSE
		mov r8,sizeof(arrType)
	ENDIF
	imul r8,sizeArr
	invoke HeapAlloc,RV(GetProcessHeap),0,rax
	exitm<rax>

ENDM

; Delete an array previously allocated with $ARRAY.
$DELETEARRAY MACRO arrPtr:REQ

	;mov rax,arrPtr
	invoke HeapFree,RV(GetProcessHeap),0,arrPtr ;rax	

ENDM

curClass TEXTEQU <>				; During declaration of classes and methods we need to track which one we're currently in.
curMethod TEXTEQU <>
CSTATIC TEXTEQU <CMETHOD>		; Todo later: we can check that cstatic type method?

INTERFACE MACRO CName:REQ

	curClass TEXTEQU <CName>
	@CatStr(CName, < STRUCT >)
		__0 dq 0			; These are placeholders as no interface can actually be invoked/instantiated, so this is effectively a dummy vtable.
		__1 dq 0			; These first 4 entries relate to ctor, dtor, release and refCount.
		__2 dq 0			; Further interface methods are added with CVIRTUAL.
		__3 dq 0
	
ENDM

ENDINTERFACE MACRO
	
	curClass ENDS
	
ENDM

CVIRTUAL MACRO method:REQ, protoDef:VARARG
	LOCAL sz1, sz2
    
    pDef TEXTEQU <TYPEDEF PROTO thisPtr:QWORD>
    
    IFNB <protoDef>
    	pDef CATSTR pDef,<,>,<&protoDef>
    ENDIF
    
    sz2 CATSTR <_>, curClass, <_&method>, <Pto>		;_curClass_methodPto
    
    % &sz2 &pDef
	% sz1 typedef PTR &sz2 
	% method sz1 0 ; set to 0 as its virtual and cannot be invoked directly on an interface. (This creates a vtable entry with 0 as it's value).
	
ENDM

CLASS MACRO CName:REQ
	% __&CName&_def EQU 1
	curClass TEXTEQU <CName>
	@CatStr(CName, < STRUCT >)
		ctorS TEXTEQU <ctor dq offset _&CName&_Init>
		dtorS TEXTEQU <dtor dq offset _&CName&_Destroy>
		relS TEXTEQU <release dq offset _&CName&_Release>
		ctorS
		dtorS
		relS
		_refCount dq 0
ENDM

ENDCLASS MACRO
	
	curClass ENDS	
	
	.code
	
	align 16
	rproc TEXTEQU <_&curClass&_Release PROC FRAME thisPtr:QWORD>
	% rproc
		assume rcx:ptr curClass
		dec [rcx]._refCount
		assume rcx:nothing
		ret	
	rproce TEXTEQU <_&curClass&_Release ENDP>
	% rproce
	
	.data
	
	align 16
	% _stat&curClass& curClass <>		; We create a static version of the class template STRUCT to allow for assembly/generation of labels, addresses and static values.
										; These can be copied to an instance via NEW. This also populates method pointers in vtbl and correct prototypes for function pointers.
	
	; We use this to create a PTR to Class type, so thisPtr can be properly typed as first argument to methods.
	ptrDefS TEXTEQU <psr>
	ptrDefS CATSTR ptrDefS,<&curClass&>,< TYPEDEF PTR >,<&curClass&>
	% ptrDefS
	
	.code
	; We assume methods will follow class definition.
	
ENDM

CMETHOD MACRO method:REQ
	LOCAL sz1, sz2
    
    sz2 CATSTR <_>, curClass, <_&method>, <Pto>
	% sz1 typedef PTR &sz2 
	% method sz1 offset _&curClass&_&method&		; By default the vtable entry points to the address of the actual method procedure.
	
ENDM

METHOD MACRO className:REQ, method:REQ, usesStr:REQ, args:VARARG
	
	curClass TEXTEQU <className>
	curMethod TEXTEQU <method>
	
	;Direct invocation proto.
	fnex TEXTEQU <_>
	fnex CATSTR fnex,<&className&>
	fnex CATSTR fnex,<_>
	fnex CATSTR fnex,<&method&>
	fnex CATSTR fnex,< PROTO thisPtr:psr>,<&className&>
	IFNB <args>
		fnex CATSTR fnex,<,>,<&args&>
	ELSE
	ENDIF
	fnex

	;vtbl invocation proto.
	fnex TEXTEQU <_>
	fnex CATSTR fnex,<&className&>
	fnex CATSTR fnex,<_>
	fnex CATSTR fnex,<&method&>
	fnex CATSTR fnex,<Pto TYPEDEF PROTO thisPtr:psr>,<&className&>
	IFNB <args>
		fnex CATSTR fnex,<,>,<&args&>
	ELSE
	ENDIF
	fnex
	
	;Method proc header.
	fnex TEXTEQU <_>
	fnex CATSTR fnex,<&className&>
	fnex CATSTR fnex,<_>
	fnex CATSTR fnex,<&method&>
	fnex CATSTR fnex,< PROC FRAME >,<&usesStr&>, < thisPtr:psr>,<&className&>
	IFNB <args>
		fnex CATSTR fnex,<,>,<&args&>
	ELSE
	ENDIF
	
	assume rcx:ptr curClass
	
	align 16
	fnex
	
ENDM

STATICMETHOD MACRO className:REQ, method:REQ, args:VARARG
	
	curClass TEXTEQU <className>
	curMethod TEXTEQU <method>
	
	;Direct invocation proto.
	fnex TEXTEQU <_>
	fnex CATSTR fnex,<&className&>
	fnex CATSTR fnex,<_>
	fnex CATSTR fnex,<&method&>
	fnex CATSTR fnex,< PROTO>
	IFNB <args>
		fnex CATSTR fnex,< >,<&args&>
	ELSE
	ENDIF
	fnex

	;vtbl invocation proto.
	fnex TEXTEQU <_>
	fnex CATSTR fnex,<&className&>
	fnex CATSTR fnex,<_>
	fnex CATSTR fnex,<&method&>
	fnex CATSTR fnex,<Pto TYPEDEF PROTO>
	IFNB <args>
		fnex CATSTR fnex,< >,<&args&>
	ELSE
	ENDIF
	fnex
	
	;Method proc header.
	fnex TEXTEQU <_>
	fnex CATSTR fnex,<&className&>
	fnex CATSTR fnex,<_>
	fnex CATSTR fnex,<&method&>
	fnex CATSTR fnex,< PROC FRAME USES rsi rdi rbx r10>
	IFNB <args>
		fnex CATSTR fnex,< >,<&args&>
	ELSE
	ENDIF
	
	assume rcx:ptr curClass
	
	align 16
	fnex
	
ENDM

ENDMETHOD MACRO
	
	assume rcx:nothing
	
	fnex TEXTEQU <_>
	fnex CATSTR fnex,curClass
	fnex CATSTR fnex,<_>
	fnex CATSTR fnex,curMethod
	fnex CATSTR fnex,< ENDP>
	fnex
	
ENDM

; Replacement for LOCAL directive when declaring an object pointer 
; -> This allows declaration of a generic type like List<String> with <> supported (macros remove these .. whereas normal LOCAL wont accept it)
$DECLARE MACRO varName:REQ, typeName:VARARG
	ldef TEXTEQU <LOCAL &varName&>
	ldef CATSTR ldef,<:>
	ldef CATSTR ldef,<typeName>
	% ldef
ENDM

; Used inside a static method code-body to acquire a reference to the static class (it's backing struct).
$STATICREF MACRO reg:REQ
	% lea reg,_stat&curClass&
ENDM

$ACQUIRE MACRO objPtr

	mov rax,objPtr
	inc qword ptr [rax+24]	; Increment instance' ref count.

ENDM

$RELEASE MACRO objPtr

	mov rax,objPtr
	dec qword ptr [rax+24]	; Decrement instance' ref count.
	
ENDM

$NEW MACRO className:REQ, ctorArgs:VARARG

	mov r15,sizeof(className)+16
	invoke HeapAlloc,RV(GetProcessHeap),0,r15
	MEMALIGN rax,16					; Ensure the object pointer is allocated to be 16byte aligned. This allows use of XMM types as properties/members etc.
	.if(rax != 0)

		mov rdi,rax
		lea rsi,_stat&className
		movdqa xmm0,[rsi]			; All objects are at least 32bytes.. dtor/ctor/release/refcount.
		movdqa xmm1,[rsi+16]
		movdqa [rdi],xmm0
		movdqa [rdi+16],xmm1
		add rsi,32
		add rdi,32
		mov rcx,sizeof(className)-32	; Transfer balance of objects statics.
		rep movsb
		
		fnex TEXTEQU <_>
		fnex CATSTR fnex,<&className&>
		fnex CATSTR fnex,<_>
		fnex CATSTR fnex,<Init>
		IFNB <ctorArgs>
			fnex2 TEXTEQU <invoke fnex,rax,ctorArgs>
		ELSE
			fnex2 TEXTEQU <invoke fnex,rax>
		ENDIF
		fnex2

	.endif
	exitm<rax>
			
ENDM

$RBXNEW MACRO className:REQ, ctorArgs:VARARG

	mov r15,sizeof(className)+16
	invoke HeapAlloc,RV(GetProcessHeap),0,r15

	MEMALIGN rax,16					; Ensure the object pointer is allocated to be 16byte aligned. This allows use of XMM types as properties/members etc.
	.if(rax != 0)
	
		mov rdi,rax
		lea rsi,_stat&className
		movdqa xmm0,[rsi]			; All objects are at least 32bytes.. dtor/ctor/release/refcount.
		movdqa xmm1,[rsi+16]
		movdqa [rdi],xmm0
		movdqa [rdi+16],xmm1
		add rsi,32
		add rdi,32
		mov rcx,sizeof(className)-32	; Transfer balance of objects statics.
		rep movsb
		
		fnex TEXTEQU <_>
		fnex CATSTR fnex,<&className&>
		fnex CATSTR fnex,<_>
		fnex CATSTR fnex,<Init>
		IFNB <ctorArgs>
			fnex2 TEXTEQU <invoke fnex,rax,ctorArgs>
		ELSE
			fnex2 TEXTEQU <invoke fnex,rax>
		ENDIF
		fnex2
		mov rbx,rax

	.endif
	exitm<rbx>
			
ENDM

 A number of classes need to implement an iterator of sorts. As we have no way to utilize they array [] operators so a class internally implements a method "Items" which performs
 a bounds checked return of the correct type (ptr,dword,word etc).
 However the system can lead to ugly looking code when used inline $v(objPtr,List,Items,0) instead of objPtr[0]. To clean this up we have 2 options, a piece of code that directly probes the internal
 array (this would be fast, but requires all objects to ensure their internal array type has the same name and item size would need to be accounted.. which isn't great.. 
 for Lists of any type it's itemsPtr) or we can just wrap the Items call with a sneaky macro? $_(objPtr,0) .. 
 To allow this to work without a type specified the Items method MUST BE THE FIRST so we can use the IteratorInterface type ptr.

$ITEM MACRO objPtr:REQ,idx:REQ
	exitm<[$v(objPtr,Iterator,Items,idx)]>
ENDM

$ITEMR MACRO objPtr:REQ,idx:REQ
	exitm<$v(objPtr,Iterator,Items,idx)>
ENDM

; Non Inline Direct Method Call.
$INVOKE MACRO className:REQ, method:REQ, objPtr:REQ, args:VARARG

	fnex TEXTEQU <_>
	fnex CATSTR fnex,<&className&>
	fnex CATSTR fnex,<_>
	fnex CATSTR fnex,<&method&>
	IFNB <args>
		fnex2 TEXTEQU <invoke fnex,&objPtr&,&args&>
	ELSE
		fnex2 TEXTEQU <invoke fnex,&objPtr&>
	ENDIF
	fnex2
	
ENDM

 Non Inline Vtable indirect method call.
$VINVOKE MACRO pInterface:REQ, Interface:REQ, Function:REQ, args:VARARG
   
   InterfacePtr TEXTEQU <_>
   InterfacePtr CATSTR InterfacePtr,<&Interface>,<_>,<&Function>,<Pto>
   
   IF (OPATTR (pInterface)) AND 00010000b
        IFNB <args>   
           invoke (InterfacePtr PTR [&pInterface].&Interface.&Function), pInterface, &args
        ELSE
           invoke (InterfacePtr PTR [&pInterface].&Interface.&Function), pInterface
        ENDIF 
    ELSE
        mov r15, pInterface
        IFNB <args>
           FOR arg, <args>
              IFIDNI <&arg>, <r15>
                .ERR <r15 is not allowed as a Method parameter with indirect object label>
              ENDIF
           ENDM
           invoke (InterfacePtr PTR [r15].&Interface.&Function), pInterface, &args
        ELSE
           invoke (InterfacePtr PTR [r15].&Interface.&Function), pInterface
        ENDIF 
    ENDIF
    
ENDM

$V MACRO pInterface:REQ, Interface:REQ, Function:REQ, args:VARARG

   InterfacePtr TEXTEQU <_>
   InterfacePtr CATSTR InterfacePtr,<&Interface>,<_>,<&Function>,<Pto>
   
   IF (OPATTR (pInterface)) AND 00010000b
        IFNB <args>   
           invoke (InterfacePtr PTR [&pInterface].&Interface.&Function), pInterface, &args
        ELSE
           invoke (InterfacePtr PTR [&pInterface].&Interface.&Function), pInterface
        ENDIF 
    ELSE
        mov r15, pInterface
        IFNB <args>
           FOR arg, <args>
              IFIDNI <&arg>, <r15>
                .ERR <r15 is not allowed as a Method parameter with indirect object label>
              ENDIF
           ENDM
           invoke (InterfacePtr PTR [r15].&Interface.&Function), pInterface, &args
        ELSE
           invoke (InterfacePtr PTR [r15].&Interface.&Function), pInterface
        ENDIF 
    ENDIF
  	
  	exitm<rax>
  	  
ENDM

$VD MACRO pInterface:REQ, Interface:REQ, Function:REQ, args:VARARG

   InterfacePtr TEXTEQU <_>
   InterfacePtr CATSTR InterfacePtr,<&Interface>,<_>,<&Function>,<Pto>
   
   IF (OPATTR (pInterface)) AND 00010000b
        IFNB <args>   
           invoke (InterfacePtr PTR [&pInterface].&Interface.&Function), pInterface, &args
        ELSE
           invoke (InterfacePtr PTR [&pInterface].&Interface.&Function), pInterface
        ENDIF 
    ELSE
        mov rax, pInterface
        IFNB <args>
           FOR arg, <args>
              IFIDNI <&arg>, <rax>
                .ERR <rax is not allowed as a Method parameter with indirect object label>
              ENDIF
           ENDM
           invoke (InterfacePtr PTR [rax].&Interface.&Function), pInterface, &args
        ELSE
           invoke (InterfacePtr PTR [rax].&Interface.&Function), pInterface
        ENDIF 
    ENDIF
  	
  	exitm<eax>
  	  
ENDM

$VW MACRO pInterface:REQ, Interface:REQ, Function:REQ, args:VARARG

   InterfacePtr TEXTEQU <_>
   InterfacePtr CATSTR InterfacePtr,<&Interface>,<_>,<&Function>,<Pto>
   
   IF (OPATTR (pInterface)) AND 00010000b
        IFNB <args>   
           invoke (InterfacePtr PTR [&pInterface].&Interface.&Function), pInterface, &args
        ELSE
           invoke (InterfacePtr PTR [&pInterface].&Interface.&Function), pInterface
        ENDIF 
    ELSE
        mov rax, pInterface
        IFNB <args>
           FOR arg, <args>
              IFIDNI <&arg>, <rax>
                .ERR <rax is not allowed as a Method parameter with indirect object label>
              ENDIF
           ENDM
           invoke (InterfacePtr PTR [rax].&Interface.&Function), pInterface, &args
        ELSE
           invoke (InterfacePtr PTR [rax].&Interface.&Function), pInterface
        ENDIF 
    ENDIF
  	
  	exitm<ax>
  	  
ENDM

$VB MACRO pInterface:REQ, Interface:REQ, Function:REQ, args:VARARG

   InterfacePtr TEXTEQU <_>
   InterfacePtr CATSTR InterfacePtr,<&Interface>,<_>,<&Function>,<Pto>
   
   IF (OPATTR (pInterface)) AND 00010000b
        IFNB <args>   
           invoke (InterfacePtr PTR [&pInterface].&Interface.&Function), pInterface, &args
        ELSE
           invoke (InterfacePtr PTR [&pInterface].&Interface.&Function), pInterface
        ENDIF 
    ELSE
        mov rax, pInterface
        IFNB <args>
           FOR arg, <args>
              IFIDNI <&arg>, <rax>
                .ERR <rax is not allowed as a Method parameter with indirect object label>
              ENDIF
           ENDM
           invoke (InterfacePtr PTR [rax].&Interface.&Function), pInterface, &args
        ELSE
           invoke (InterfacePtr PTR [rax].&Interface.&Function), pInterface
        ENDIF 
    ENDIF
  	
  	exitm<al>
  	  
ENDM

$VF MACRO pInterface:REQ, Interface:REQ, Function:REQ, args:VARARG

   InterfacePtr TEXTEQU <_>
   InterfacePtr CATSTR InterfacePtr,<&Interface>,<_>,<&Function>,<Pto>
   
   IF (OPATTR (pInterface)) AND 00010000b
        IFNB <args>   
           invoke (InterfacePtr PTR [&pInterface].&Interface.&Function), pInterface, &args
        ELSE
           invoke (InterfacePtr PTR [&pInterface].&Interface.&Function), pInterface
        ENDIF 
    ELSE
        mov rax, pInterface
        IFNB <args>
           FOR arg, <args>
              IFIDNI <&arg>, <rax>
                .ERR <rax is not allowed as a Method parameter with indirect object label>
              ENDIF
           ENDM
           invoke (InterfacePtr PTR [rax].&Interface.&Function), pInterface, &args
        ELSE
           invoke (InterfacePtr PTR [rax].&Interface.&Function), pInterface
        ENDIF 
    ENDIF
  	
  	exitm<xmm0>
  	  
ENDM

; Allow inline call of a direct method. MOV RAX,$I(String,Parse,CStr("test"))
$I MACRO className:REQ, method:REQ, objPtr:REQ, args:VARARG

	fnex TEXTEQU <_>
	fnex CATSTR fnex,<&className&>
	fnex CATSTR fnex,<_>
	fnex CATSTR fnex,<&method&>
	fnex2 TEXTEQU <invoke fnex,&objPtr&,&args&>
	fnex2
	exitm<rax>
	
ENDM

; Allow inline call of a static method.
$STATIC MACRO className:REQ, method:REQ, args:VARARG

	fnex TEXTEQU <_>
	fnex CATSTR fnex,<&className&>
	fnex CATSTR fnex,<_>
	fnex CATSTR fnex,<&method&>
	fnex2 TEXTEQU <invoke fnex,&args&>
	fnex2
	exitm<rax>
	
ENDM

; Delete an object.
$DELETE MACRO objPtr:REQ

	mov rax,objPtr
	call qword ptr [rax+8]						; Call destructor. 
	invoke HeapFree,RV(GetProcessHeap),0,objPtr	; Free memory.
	
ENDM
