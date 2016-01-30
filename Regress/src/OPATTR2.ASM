
;--- test .TYPE

	.386

@what macro xx
	dw .TYPE xx
;TX textequ %(TYPE xx)
;%	echo -xx- has type TX
        endm

T1 typedef WORD
PP typedef near ptr
LP typedef far ptr
S1 struct
f1	PP ?
f2	LP ?
S1 ends
TE1 textequ <a>
E1 equ 1

_TEXT segment use32 'CODE'

v1 S1 <>

CGROUP group _TEXT

code_near label near
code_far  label far
data_db label byte
data_dd label dword

p1 proc c a1:dword
local lcl_dd:dword
local lcl_near:near

	@what code_near
	@what code_far
	@what data_db
	@what data_dd
	@what al
	@what ah
	@what ax
	@what eax
	@what <>
	@what <abc>
	@what TE1
	@what E1
	@what [ebx]
	@what [ebx+code_near]
	@what [ebx].S1.f1
	@what [ebx+v1].f1
	@what p1
	@what a1
	@what lcl_dd
	@what lcl_near
	@what WORD
	@what T1
	@what S1
	@what S1.f1
	@what v1
	@what v1.f1
	@what <offset code_near>
	@what <offset code_far>
	@what <offset data_db>
	@what FLAT
	@what _TEXT
	@what CGROUP
	@what <BYTE ptr code_near>

p1 endp

_TEXT ends

	end
