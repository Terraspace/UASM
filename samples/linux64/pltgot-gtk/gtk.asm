include api.inc
include gtk4.inc

on_activate proto SYSTEMV app:ptr,userData:ptr
on_clicked proto SYSTEMV button:ptr,pLabel:ptr
refresh_display proto SYSTEMV pLabel:ptr
on_smoke proto SYSTEMV app:ptr

.data
app_id db "org.uasm.PltGotDemo",0
window_title db "UASM - Linux PIE / SO / DWARF",0
heading db '<span size="x-large" weight="bold">UASM Linux sample</span>',0
explanation db "GTK4 callbacks into assembly. State lives in libuasm_sample.so.",0
button_text db "Add 1.25",0
activate_signal db "activate",0
clicked_signal db "clicked",0
format_text db "Count: %u",10,"Total: %.2f",10,"Library events: %llu",0
smoke_name db "UASM_SAMPLE_SMOKE",0
smoke_ok db "PASS: GTK activation, two callbacks, SO state and clean exit",0
smoke_bad db "FAIL: GTK sample state mismatch",0
step_value real8 1.25
smoke_total real8 2.5
display_label dq 0
click_button dq 0
smoke_failure dd 0

.code

refresh_display proc SYSTEMV uses rbx pLabel:ptr
 LOCAL buffer[160]:byte,events:qword
 lea rbx,sample_model
 mov rax,sample_events
 mov events,rax
 invoke g_snprintf,ADDR buffer,160,ADDR format_text,[rbx].SampleState.count,[rbx].SampleState.total,events
 invoke gtk_label_set_text,pLabel,ADDR buffer
 ret
refresh_display endp

on_clicked proc SYSTEMV button:ptr,pLabel:ptr
 LOCAL clickedButton:ptr
 mov rax,button
 mov clickedButton,rax
 invoke sample_add,ADDR sample_model,step_value
 invoke refresh_display,pLabel
 ret
on_clicked endp

on_smoke proc SYSTEMV app:ptr
 invoke g_signal_emit_by_name,click_button,ADDR clicked_signal
 invoke g_signal_emit_by_name,click_button,ADDR clicked_signal
 mov eax,GOT(sample_model.count,r11)
 cmp eax,2
 jne bad
 movsd xmm0,GOT(sample_model.total,r11)
 ucomisd xmm0,smoke_total
 jp bad
 jne bad
 mov rax,sample_events
 cmp rax,2
 jne bad
 invoke puts,ADDR smoke_ok
 jmp finish
bad:
 mov smoke_failure,1
 invoke puts,ADDR smoke_bad
finish:
 invoke g_application_quit,app
 xor eax,eax
 ret
on_smoke endp

on_activate proc SYSTEMV app:ptr,userData:ptr
 LOCAL window:ptr,box:ptr,pLabel:ptr,button:ptr
 invoke gtk_application_window_new,app
 mov window,rax
 invoke gtk_window_set_title,window,ADDR window_title
 invoke gtk_window_set_default_size,window,520,280
 invoke gtk_box_new,1,16
 mov box,rax
 invoke gtk_widget_set_margin_top,box,24
 invoke gtk_widget_set_margin_bottom,box,24
 invoke gtk_widget_set_margin_start,box,24
 invoke gtk_widget_set_margin_end,box,24
 invoke gtk_window_set_child,window,box
 invoke gtk_label_new,NULLPTR
 mov pLabel,rax
 invoke gtk_label_set_markup,pLabel,ADDR heading
 invoke gtk_box_append,box,pLabel
 invoke gtk_label_new,ADDR explanation
 mov pLabel,rax
 invoke gtk_box_append,box,pLabel
 invoke gtk_label_new,NULLPTR
 mov display_label,rax
 invoke gtk_box_append,box,rax
 invoke refresh_display,display_label
 invoke gtk_button_new_with_label,ADDR button_text
 mov button,rax
 mov click_button,rax
 invoke g_signal_connect_data,button,ADDR clicked_signal,ADDR on_clicked,display_label,NULLPTR,0
 invoke gtk_box_append,box,button
 invoke gtk_window_present,window
 invoke getenv,ADDR smoke_name
 test rax,rax
 jz ready
 invoke g_timeout_add,300,ADDR on_smoke,app
ready:
 ret
on_activate endp

main proc SYSTEMV argc:dword,argv:ptr
 LOCAL app:ptr,status:dword
 invoke sample_reset,ADDR sample_model
 invoke gtk_application_new,ADDR app_id,0
 mov app,rax
 invoke g_signal_connect_data,app,ADDR activate_signal,ADDR on_activate,NULLPTR,NULLPTR,0
 invoke g_application_run,app,argc,argv
 mov status,eax
 invoke g_object_unref,app
 mov eax,smoke_failure
 test eax,eax
 jnz done
 mov eax,status
done:
 ret
main endp

end
