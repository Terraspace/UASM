; IntelliSense tour, not a runnable application.
include types.inc
.data
point Demo::Point <>
pointer Demo::PPoint 0
counter Demo::psrCounter 0
shell Demo::PShell 0
boot Demo::PBootServices 0
.code
Tour PROC namespace:PTR Demo::Point
    LOCAL localPoint:Demo::Point,localPtr:Demo::PPoint
    ASSUME rax:PTR Demo::Point
    ; Type a dot after point, pointer, localPoint, localPtr or [rax].
    ; Explicit forms: [rax].Demo::Point.  (Demo::Point PTR [rax]).
    ; Type counter->, shell-> or boot-> for method completion.
    ; Type Demo:: or Win32:: for namespace members.
    ; Type INVOKE Win32::WriteFile, or counter->Add( for signatures.
    mov eax,point.NameSpace
    mov eax,point.x


    ret
Tour ENDP
end
