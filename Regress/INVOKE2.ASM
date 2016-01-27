
;--- invoke tests for 8086
;--- ( the 8086 has no PUSH <imm> instruction variant )

    .model small, stdcall

fn1     proto :byte, :word, :dword
fn2     proto :sbyte, :sword

protoFn typedef proto :WORD
LPFN    typedef ptr protoFn

S1  struct
    dw ?
p1  LPFN ?
S1  ends

    .DATA
        
pFN LPFN 0
v1  S1 <0, 0>
v2	SBYTE 0

    .CODE

    invoke fn1, 1, 2, 3
    invoke fn1, 1, 2, 12345h
    invoke fn1, 0, 0, 0
    invoke fn2, v2, -1
    invoke fn2, cl, dl
    invoke fn2, dh, bh
    invoke pFN, 1
    invoke pFN, offset fn1
    invoke v1.p1, 2
    ret

fn1 proc x1:byte, x2:word, x3:dword
    ret
fn1 endp
fn2 proc x1:sbyte, x2:sword
    ret
fn2 endp

    END


