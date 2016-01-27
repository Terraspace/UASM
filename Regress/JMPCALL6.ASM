
    .286
    .model small

    .code

;--- it's a slighly incorrect coercion ("dword ptr" would be correct)
;--- but it "should" work!

    call near ptr [bp]
    call far  ptr [bp]	;must generate a far indirect call
    .386
    call near16 ptr [bp]
    call near32 ptr [bp]	;Masm generates code for far16 here!
    call far16  ptr [bp]
    call far32  ptr [bp]
    ret

    end
