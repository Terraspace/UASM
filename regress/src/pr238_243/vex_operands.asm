; PR #242: overlapping operand shifts, NDS and immediate NDD forms.
.x64
_TEXT SEGMENT USE64
vaddps xmm1,xmm2,xmm3
vaddps ymm9,ymm10,ymm11
vpslld xmm1,xmm2,3
vpsrld ymm9,ymm10,7
_TEXT ENDS
END

