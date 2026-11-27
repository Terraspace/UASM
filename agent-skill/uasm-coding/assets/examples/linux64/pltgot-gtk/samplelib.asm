BUILD_LIBRARY equ 1
include api.inc
sample_adjust proto SYSTEMV value:real8
public sample_model,sample_events,sample_adjust
option elfvisibility:sample_adjust:hidden
.data
sample_model SampleState <0,0,0.0,0.0>
sample_events dq 0
adjust_factor real8 1.0
.code
sample_reset proc SYSTEMV state:ptr SampleState
 mov rax,state
 mov [rax].SampleState.count,0
 mov [rax].SampleState.padding,0
 pxor xmm0,xmm0
 movsd [rax].SampleState.total,xmm0
 movsd [rax].SampleState.last,xmm0
 mov GOT(sample_events,r11),0
 ret
sample_reset endp

sample_add proc SYSTEMV state:ptr SampleState, amount:real8
 LOCAL before:real8,after:real8
 ; Named parameters are homed, and remain available across this call.
 invoke sample_adjust,amount
 mov rax,state
 movsd xmm1,[rax].SampleState.total
 movsd before,xmm1
 addsd xmm1,xmm0
 movsd after,xmm1
 movsd [rax].SampleState.total,xmm1
 movsd [rax].SampleState.last,xmm0
 inc [rax].SampleState.count
 lock inc GOT(sample_events,r11)
 movsd xmm0,after ; DEBUG_STOP: inspect state, amount, before and after here
 ret
sample_add endp

; Register-backed parameter example for comparison in the debugger.
option sysvhome:0
sample_adjust proc SYSTEMV value:real8
 movsd xmm0,value ; DEBUG_REGISTER: value is in XMM0
 mulsd xmm0,adjust_factor
 ret
sample_adjust endp
end
