
;*** problem: detecting endo of undelimited literals
;--- see @CatStr() below:

	.386
	.model flat, stdcall
	option casemap:none ; case sensitive
	option proc:private

CStr macro y:VARARG
local sym
CONST segment dword public 'CONST'
sym db y,0
CONST ends
	exitm <offset sym>
	endm

	.data

HANDLE TYPEDEF DWORD
LPSTR  TYPEDEF ptr BYTE
HKEY_CLASSES_ROOT equ 80000000h
NULL equ 0

REGSTRUCT struct
hRootKey		HANDLE ?
lpszSubKey		LPSTR  ?
lpszValueName   LPSTR  ?
lpszData		LPSTR  ?
REGSTRUCT ends

Version_AsmCtrl equ <1>

AsmCtrl_ProgidEntries label REGSTRUCT

;--- prior to v2.05, the second -!"- argument of the @CatStr macro
;--- did also contain the closing bracket(s), because the tokenizer
;--- did stop only if a white space, a comma or a semi-colon was detected.

	REGSTRUCT {HKEY_CLASSES_ROOT,CStr(".", @CatStr(!",%Version_AsmCtrl,!")),0,CStr("X")}
	REGSTRUCT {HKEY_CLASSES_ROOT,CStr(".", @CatStr(!",%Version_AsmCtrl,!"),"\X"),0,-1}
NUMREGSTRUCTENTRIES2 equ ($ - offset AsmCtrl_ProgidEntries) / sizeof REGSTRUCT

	end
