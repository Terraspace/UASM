
;--- test option dotname + macro arguments preceded by a dot.
;--- this was a problem in v2.00-v2.02.

    .386
    .model flat, stdcall
    option casemap :none
    option dotname

RECT struct
left dd ?
top  dd ?
right dd ?
bottom dd ?
RECT ends

GetXY macro Rect:req, Border1:req, Border2:req
    mov edx, Rect
    mov eax, [edx].RECT.Border2
    sub eax, [edx].RECT.Border1
endm

    .data

rc  RECT <>

    .code

    GetXY offset rc, left, right
    GetXY offset rc, top, bottom

    end
