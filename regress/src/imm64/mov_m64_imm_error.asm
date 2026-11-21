; MOV m64 requires an immediate representable by sign-extension of imm32.
.x64
_TEXT SEGMENT USE64
mov qword ptr [rax],1122334455667788h
mov qword ptr [rax],-100000000h
mov qword ptr [rax],100000000h
_TEXT ENDS
END
