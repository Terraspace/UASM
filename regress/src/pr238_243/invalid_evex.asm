; PR #243: reject forced EVEX on legacy instructions.
.x64
option evex:1
_TEXT SEGMENT USE64
{evex} add eax,ebx
{evex} mov rax,rbx
_TEXT ENDS
END
