option stackbase:rsp
option win64:15
option frame:auto
B proto (byte)
SB proto (sbyte)
W proto (word)
SW proto (sword)
D proto (dword)
SD proto (sdword)
Q proto (qword)
P proto (ptr)
F proto (real4)
G proto (real8)
Sink proto :byte,:sbyte,:word,:sword,:dword,:sdword,:qword,:ptr,:real4,:real8
.code
Caller proc frame
 Sink(B(),SB(),W(),SW(),D(),SD(),Q(),P(),F(),G())
 ret
Caller endp
end
