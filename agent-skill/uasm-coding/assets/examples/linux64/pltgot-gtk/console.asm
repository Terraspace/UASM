include api.inc
apply_value proto SYSTEMV amount:real8
.data
first_amount real8 1.25
second_amount real8 2.5
third_amount real8 -0.75
expected_total real8 3.0
success_text db "PASS: PIE + SO, PLT/GOT, count=3, total=3.00, events=3",0
failure_text db "FAIL: sample state mismatch",0
.code
apply_value proc SYSTEMV amount:real8
 LOCAL requested:real8
 movsd xmm0,amount
 movsd requested,xmm0
 invoke sample_add,ADDR sample_model,requested
 ret
apply_value endp

main proc SYSTEMV argc:dword,argv:ptr
 LOCAL observedCount:dword,observedTotal:real8,originalArgc:dword,originalArgv:ptr
 ; Referencing these by name explicitly homes them for debugger inspection.
 mov eax,argc
 mov originalArgc,eax
 mov rax,argv
 mov originalArgv,rax
 invoke sample_reset,ADDR sample_model
 invoke apply_value,first_amount
 invoke apply_value,second_amount
 invoke apply_value,third_amount
 mov eax,GOT(sample_model.count,r11)
 mov observedCount,eax
 cmp eax,3
 jne failed
 movsd xmm0,GOT(sample_model.total,r11)
 movsd observedTotal,xmm0
 ucomisd xmm0,expected_total
 jp failed
 jne failed
 mov rax,sample_events
 cmp rax,3
 jne failed
 invoke puts,ADDR success_text ; DEBUG_MAIN: completed state and locals
 xor eax,eax
 ret
failed:
 invoke puts,ADDR failure_text
 mov eax,1
 ret
main endp
end
