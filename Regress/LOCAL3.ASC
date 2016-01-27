
;--- -Zg option
;--- indirect addressing of LOCAL variable with additional register
;--- with -Zg, jwasm is supposed to use the additional register as base (!)
;--- and hence has to emit a 36h (=SS:) prefix!

;--- masm does this in any case, jwasm will do only if model isn't flat.

    .386
    .model small

    .code

p1 proc

local buff[128]:byte

    xor esi,esi
    .while esi < sizeof buff
        mov al,buff[esi]
        inc esi
    .endw
    ret

p1 endp

    end
