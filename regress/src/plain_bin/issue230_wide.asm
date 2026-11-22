.x64
.model flat
PAIR RECORD f1:16,f2:16,f3:16,f4:16
.code
mov rax,PAIR <1234h,5678h,9abch,0def0h>+1
mov rbx,(PAIR <1,2,3,4>)
mov eax,HIGH32 PAIR <1234h,5678h,9abch,0def0h>
end
