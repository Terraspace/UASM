
;--- some invoke tests
;--- the "expected" version must be created with JWasm,
;--- because Masm's <PUSH DWORD imm> is different!

    .286
    .MODEL small, stdcall
    option casemap:none
    .386

fn1     proto :byte, :word, :dword
fn2     proto :qword
fn3     proto :real10
fn4     proto :ptr qword

protoFn typedef proto :DWORD
LPFN    typedef ptr protoFn

S1  struct
    dd ?
p1  LPFN ?
S1  ends

    .DATA

pFN LPFN 0
s1  S1 <0, 0>

    .CODE

    invoke fn1, 1, 2, 3
    invoke pFN, 1
    invoke s1.p1, 2
    invoke fn2, [bx]
    invoke fn3, [ebx]
    invoke fn4, addr s1
    ret

; no epilogues since they may differ between Masm - JWasm
    option prologue:none
    option epilogue:none

fn1 proc x1:byte, x2:word, x3:dword
    ret
fn1 endp

fn2 proc x1:qword
    ret
fn2 endp

fn3 proc x1:real10
    ret
fn3 endp

fn4 proc x1:ptr qword
    ret
fn4 endp

    END


