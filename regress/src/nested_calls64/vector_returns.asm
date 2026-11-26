option evex:1
option stackbase:rsp
option win64:15
option frame:auto
X proto vectorcall (xmmword)
Y proto vectorcall (ymmword)
Z proto vectorcall (zmmword)
SinkX proto vectorcall :xmmword,:xmmword
SinkY proto vectorcall :ymmword,:ymmword
SinkZ proto vectorcall :zmmword,:zmmword
.code
Caller proc frame
 option arch:sse
 SinkX(X(),X())
 option arch:avx
 SinkX(X(),X())
 SinkY(Y(),Y())
 SinkZ(Z(),Z())
 ret
Caller endp
end
