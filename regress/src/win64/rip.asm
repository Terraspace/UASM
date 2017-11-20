
    .code

label_0: nop
label_1: nop

    mov rax,[rip+(switch_table-label_rip)]

label_rip:

    jmp qword ptr [rip]

switch_table:
    dq label_0
    dq label_1

    end
