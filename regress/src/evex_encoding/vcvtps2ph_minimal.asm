; Minimal VCVTPS2PH EVEX.R regression: must encode zmm30, not zmm22.
; Expected bytes (also independently assembled with GNU as):
; 62 63 7D 48 1D 31 AB
.x64
option evex:1
_TEXT SEGMENT USE64
vcvtps2ph ymmword ptr [rcx],zmm30,0abh
_TEXT ENDS
END
