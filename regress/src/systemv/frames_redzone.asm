; System V regression: frames_redzone
; run_tests returns zero when its ABI assertions pass.
option casemap:none

option redzone:no
option redzone:no
.code
frame_0_0_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_0_0_0_0_child endp
frame_0_0_0_0_run_tests proc SYSTEMV
xor eax,eax
ret
frame_0_0_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_0_0_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_0_0_0_1_child endp
frame_0_0_0_1_run_tests proc SYSTEMV
invoke frame_0_0_0_1_child
xor eax,eax
ret
frame_0_0_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_0_0_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_0_0_1_0_child endp
frame_0_0_1_0_run_tests proc SYSTEMV
xor eax,eax
ret
frame_0_0_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_0_0_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_0_0_1_1_child endp
frame_0_0_1_1_run_tests proc SYSTEMV
invoke frame_0_0_1_1_child
xor eax,eax
ret
frame_0_0_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_0_1_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_0_1_0_0_child endp
frame_0_1_0_0_run_tests proc SYSTEMV uses rbx
xor eax,eax
ret
frame_0_1_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_0_1_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_0_1_0_1_child endp
frame_0_1_0_1_run_tests proc SYSTEMV uses rbx
invoke frame_0_1_0_1_child
xor eax,eax
ret
frame_0_1_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_0_1_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_0_1_1_0_child endp
frame_0_1_1_0_run_tests proc SYSTEMV uses rbx
xor eax,eax
ret
frame_0_1_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_0_1_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_0_1_1_1_child endp
frame_0_1_1_1_run_tests proc SYSTEMV uses rbx
invoke frame_0_1_1_1_child
xor eax,eax
ret
frame_0_1_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_0_2_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_0_2_0_0_child endp
frame_0_2_0_0_run_tests proc SYSTEMV uses rbx r12
xor eax,eax
ret
frame_0_2_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_0_2_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_0_2_0_1_child endp
frame_0_2_0_1_run_tests proc SYSTEMV uses rbx r12
invoke frame_0_2_0_1_child
xor eax,eax
ret
frame_0_2_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_0_2_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_0_2_1_0_child endp
frame_0_2_1_0_run_tests proc SYSTEMV uses rbx r12
xor eax,eax
ret
frame_0_2_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_0_2_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_0_2_1_1_child endp
frame_0_2_1_1_run_tests proc SYSTEMV uses rbx r12
invoke frame_0_2_1_1_child
xor eax,eax
ret
frame_0_2_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_0_3_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_0_3_0_0_child endp
frame_0_3_0_0_run_tests proc SYSTEMV uses rbx r12 r13
xor eax,eax
ret
frame_0_3_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_0_3_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_0_3_0_1_child endp
frame_0_3_0_1_run_tests proc SYSTEMV uses rbx r12 r13
invoke frame_0_3_0_1_child
xor eax,eax
ret
frame_0_3_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_0_3_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_0_3_1_0_child endp
frame_0_3_1_0_run_tests proc SYSTEMV uses rbx r12 r13
xor eax,eax
ret
frame_0_3_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_0_3_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_0_3_1_1_child endp
frame_0_3_1_1_run_tests proc SYSTEMV uses rbx r12 r13
invoke frame_0_3_1_1_child
xor eax,eax
ret
frame_0_3_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_120_0_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_120_0_0_0_child endp
frame_120_0_0_0_run_tests proc SYSTEMV
local v[120]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_120_0_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_120_0_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_120_0_0_1_child endp
frame_120_0_0_1_run_tests proc SYSTEMV
local v[120]:byte
mov byte ptr v,42
invoke frame_120_0_0_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_120_0_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_120_0_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_120_0_1_0_child endp
frame_120_0_1_0_run_tests proc SYSTEMV
local v[120]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_120_0_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_120_0_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_120_0_1_1_child endp
frame_120_0_1_1_run_tests proc SYSTEMV
local v[120]:byte
mov byte ptr v,42
invoke frame_120_0_1_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_120_0_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_120_1_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_120_1_0_0_child endp
frame_120_1_0_0_run_tests proc SYSTEMV uses rbx
local v[120]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_120_1_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_120_1_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_120_1_0_1_child endp
frame_120_1_0_1_run_tests proc SYSTEMV uses rbx
local v[120]:byte
mov byte ptr v,42
invoke frame_120_1_0_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_120_1_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_120_1_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_120_1_1_0_child endp
frame_120_1_1_0_run_tests proc SYSTEMV uses rbx
local v[120]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_120_1_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_120_1_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_120_1_1_1_child endp
frame_120_1_1_1_run_tests proc SYSTEMV uses rbx
local v[120]:byte
mov byte ptr v,42
invoke frame_120_1_1_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_120_1_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_120_2_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_120_2_0_0_child endp
frame_120_2_0_0_run_tests proc SYSTEMV uses rbx r12
local v[120]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_120_2_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_120_2_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_120_2_0_1_child endp
frame_120_2_0_1_run_tests proc SYSTEMV uses rbx r12
local v[120]:byte
mov byte ptr v,42
invoke frame_120_2_0_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_120_2_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_120_2_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_120_2_1_0_child endp
frame_120_2_1_0_run_tests proc SYSTEMV uses rbx r12
local v[120]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_120_2_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_120_2_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_120_2_1_1_child endp
frame_120_2_1_1_run_tests proc SYSTEMV uses rbx r12
local v[120]:byte
mov byte ptr v,42
invoke frame_120_2_1_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_120_2_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_120_3_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_120_3_0_0_child endp
frame_120_3_0_0_run_tests proc SYSTEMV uses rbx r12 r13
local v[120]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_120_3_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_120_3_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_120_3_0_1_child endp
frame_120_3_0_1_run_tests proc SYSTEMV uses rbx r12 r13
local v[120]:byte
mov byte ptr v,42
invoke frame_120_3_0_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_120_3_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_120_3_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_120_3_1_0_child endp
frame_120_3_1_0_run_tests proc SYSTEMV uses rbx r12 r13
local v[120]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_120_3_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_120_3_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_120_3_1_1_child endp
frame_120_3_1_1_run_tests proc SYSTEMV uses rbx r12 r13
local v[120]:byte
mov byte ptr v,42
invoke frame_120_3_1_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_120_3_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_128_0_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_128_0_0_0_child endp
frame_128_0_0_0_run_tests proc SYSTEMV
local v[128]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_128_0_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_128_0_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_128_0_0_1_child endp
frame_128_0_0_1_run_tests proc SYSTEMV
local v[128]:byte
mov byte ptr v,42
invoke frame_128_0_0_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_128_0_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_128_0_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_128_0_1_0_child endp
frame_128_0_1_0_run_tests proc SYSTEMV
local v[128]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_128_0_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_128_0_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_128_0_1_1_child endp
frame_128_0_1_1_run_tests proc SYSTEMV
local v[128]:byte
mov byte ptr v,42
invoke frame_128_0_1_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_128_0_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_128_1_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_128_1_0_0_child endp
frame_128_1_0_0_run_tests proc SYSTEMV uses rbx
local v[128]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_128_1_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_128_1_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_128_1_0_1_child endp
frame_128_1_0_1_run_tests proc SYSTEMV uses rbx
local v[128]:byte
mov byte ptr v,42
invoke frame_128_1_0_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_128_1_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_128_1_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_128_1_1_0_child endp
frame_128_1_1_0_run_tests proc SYSTEMV uses rbx
local v[128]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_128_1_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_128_1_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_128_1_1_1_child endp
frame_128_1_1_1_run_tests proc SYSTEMV uses rbx
local v[128]:byte
mov byte ptr v,42
invoke frame_128_1_1_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_128_1_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_128_2_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_128_2_0_0_child endp
frame_128_2_0_0_run_tests proc SYSTEMV uses rbx r12
local v[128]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_128_2_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_128_2_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_128_2_0_1_child endp
frame_128_2_0_1_run_tests proc SYSTEMV uses rbx r12
local v[128]:byte
mov byte ptr v,42
invoke frame_128_2_0_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_128_2_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_128_2_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_128_2_1_0_child endp
frame_128_2_1_0_run_tests proc SYSTEMV uses rbx r12
local v[128]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_128_2_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_128_2_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_128_2_1_1_child endp
frame_128_2_1_1_run_tests proc SYSTEMV uses rbx r12
local v[128]:byte
mov byte ptr v,42
invoke frame_128_2_1_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_128_2_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_128_3_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_128_3_0_0_child endp
frame_128_3_0_0_run_tests proc SYSTEMV uses rbx r12 r13
local v[128]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_128_3_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_128_3_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_128_3_0_1_child endp
frame_128_3_0_1_run_tests proc SYSTEMV uses rbx r12 r13
local v[128]:byte
mov byte ptr v,42
invoke frame_128_3_0_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_128_3_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_128_3_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_128_3_1_0_child endp
frame_128_3_1_0_run_tests proc SYSTEMV uses rbx r12 r13
local v[128]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_128_3_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_128_3_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_128_3_1_1_child endp
frame_128_3_1_1_run_tests proc SYSTEMV uses rbx r12 r13
local v[128]:byte
mov byte ptr v,42
invoke frame_128_3_1_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_128_3_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_136_0_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_136_0_0_0_child endp
frame_136_0_0_0_run_tests proc SYSTEMV
local v[136]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_136_0_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_136_0_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_136_0_0_1_child endp
frame_136_0_0_1_run_tests proc SYSTEMV
local v[136]:byte
mov byte ptr v,42
invoke frame_136_0_0_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_136_0_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_136_0_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_136_0_1_0_child endp
frame_136_0_1_0_run_tests proc SYSTEMV
local v[136]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_136_0_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_136_0_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_136_0_1_1_child endp
frame_136_0_1_1_run_tests proc SYSTEMV
local v[136]:byte
mov byte ptr v,42
invoke frame_136_0_1_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_136_0_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_136_1_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_136_1_0_0_child endp
frame_136_1_0_0_run_tests proc SYSTEMV uses rbx
local v[136]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_136_1_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_136_1_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_136_1_0_1_child endp
frame_136_1_0_1_run_tests proc SYSTEMV uses rbx
local v[136]:byte
mov byte ptr v,42
invoke frame_136_1_0_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_136_1_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_136_1_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_136_1_1_0_child endp
frame_136_1_1_0_run_tests proc SYSTEMV uses rbx
local v[136]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_136_1_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_136_1_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_136_1_1_1_child endp
frame_136_1_1_1_run_tests proc SYSTEMV uses rbx
local v[136]:byte
mov byte ptr v,42
invoke frame_136_1_1_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_136_1_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_136_2_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_136_2_0_0_child endp
frame_136_2_0_0_run_tests proc SYSTEMV uses rbx r12
local v[136]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_136_2_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_136_2_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_136_2_0_1_child endp
frame_136_2_0_1_run_tests proc SYSTEMV uses rbx r12
local v[136]:byte
mov byte ptr v,42
invoke frame_136_2_0_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_136_2_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_136_2_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_136_2_1_0_child endp
frame_136_2_1_0_run_tests proc SYSTEMV uses rbx r12
local v[136]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_136_2_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_136_2_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_136_2_1_1_child endp
frame_136_2_1_1_run_tests proc SYSTEMV uses rbx r12
local v[136]:byte
mov byte ptr v,42
invoke frame_136_2_1_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_136_2_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_136_3_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_136_3_0_0_child endp
frame_136_3_0_0_run_tests proc SYSTEMV uses rbx r12 r13
local v[136]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_136_3_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_136_3_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_136_3_0_1_child endp
frame_136_3_0_1_run_tests proc SYSTEMV uses rbx r12 r13
local v[136]:byte
mov byte ptr v,42
invoke frame_136_3_0_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_136_3_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_136_3_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_136_3_1_0_child endp
frame_136_3_1_0_run_tests proc SYSTEMV uses rbx r12 r13
local v[136]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_136_3_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_136_3_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_136_3_1_1_child endp
frame_136_3_1_1_run_tests proc SYSTEMV uses rbx r12 r13
local v[136]:byte
mov byte ptr v,42
invoke frame_136_3_1_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_136_3_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_16_0_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_16_0_0_0_child endp
frame_16_0_0_0_run_tests proc SYSTEMV
local v[16]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_16_0_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_16_0_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_16_0_0_1_child endp
frame_16_0_0_1_run_tests proc SYSTEMV
local v[16]:byte
mov byte ptr v,42
invoke frame_16_0_0_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_16_0_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_16_0_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_16_0_1_0_child endp
frame_16_0_1_0_run_tests proc SYSTEMV
local v[16]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_16_0_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_16_0_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_16_0_1_1_child endp
frame_16_0_1_1_run_tests proc SYSTEMV
local v[16]:byte
mov byte ptr v,42
invoke frame_16_0_1_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_16_0_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_16_1_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_16_1_0_0_child endp
frame_16_1_0_0_run_tests proc SYSTEMV uses rbx
local v[16]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_16_1_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_16_1_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_16_1_0_1_child endp
frame_16_1_0_1_run_tests proc SYSTEMV uses rbx
local v[16]:byte
mov byte ptr v,42
invoke frame_16_1_0_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_16_1_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_16_1_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_16_1_1_0_child endp
frame_16_1_1_0_run_tests proc SYSTEMV uses rbx
local v[16]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_16_1_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_16_1_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_16_1_1_1_child endp
frame_16_1_1_1_run_tests proc SYSTEMV uses rbx
local v[16]:byte
mov byte ptr v,42
invoke frame_16_1_1_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_16_1_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_16_2_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_16_2_0_0_child endp
frame_16_2_0_0_run_tests proc SYSTEMV uses rbx r12
local v[16]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_16_2_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_16_2_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_16_2_0_1_child endp
frame_16_2_0_1_run_tests proc SYSTEMV uses rbx r12
local v[16]:byte
mov byte ptr v,42
invoke frame_16_2_0_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_16_2_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_16_2_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_16_2_1_0_child endp
frame_16_2_1_0_run_tests proc SYSTEMV uses rbx r12
local v[16]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_16_2_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_16_2_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_16_2_1_1_child endp
frame_16_2_1_1_run_tests proc SYSTEMV uses rbx r12
local v[16]:byte
mov byte ptr v,42
invoke frame_16_2_1_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_16_2_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_16_3_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_16_3_0_0_child endp
frame_16_3_0_0_run_tests proc SYSTEMV uses rbx r12 r13
local v[16]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_16_3_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_16_3_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_16_3_0_1_child endp
frame_16_3_0_1_run_tests proc SYSTEMV uses rbx r12 r13
local v[16]:byte
mov byte ptr v,42
invoke frame_16_3_0_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_16_3_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_16_3_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_16_3_1_0_child endp
frame_16_3_1_0_run_tests proc SYSTEMV uses rbx r12 r13
local v[16]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_16_3_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_16_3_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_16_3_1_1_child endp
frame_16_3_1_1_run_tests proc SYSTEMV uses rbx r12 r13
local v[16]:byte
mov byte ptr v,42
invoke frame_16_3_1_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_16_3_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_8_0_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_8_0_0_0_child endp
frame_8_0_0_0_run_tests proc SYSTEMV
local v[8]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_8_0_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_8_0_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_8_0_0_1_child endp
frame_8_0_0_1_run_tests proc SYSTEMV
local v[8]:byte
mov byte ptr v,42
invoke frame_8_0_0_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_8_0_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_8_0_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_8_0_1_0_child endp
frame_8_0_1_0_run_tests proc SYSTEMV
local v[8]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_8_0_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_8_0_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_8_0_1_1_child endp
frame_8_0_1_1_run_tests proc SYSTEMV
local v[8]:byte
mov byte ptr v,42
invoke frame_8_0_1_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_8_0_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_8_1_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_8_1_0_0_child endp
frame_8_1_0_0_run_tests proc SYSTEMV uses rbx
local v[8]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_8_1_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_8_1_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_8_1_0_1_child endp
frame_8_1_0_1_run_tests proc SYSTEMV uses rbx
local v[8]:byte
mov byte ptr v,42
invoke frame_8_1_0_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_8_1_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_8_1_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_8_1_1_0_child endp
frame_8_1_1_0_run_tests proc SYSTEMV uses rbx
local v[8]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_8_1_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_8_1_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_8_1_1_1_child endp
frame_8_1_1_1_run_tests proc SYSTEMV uses rbx
local v[8]:byte
mov byte ptr v,42
invoke frame_8_1_1_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_8_1_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_8_2_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_8_2_0_0_child endp
frame_8_2_0_0_run_tests proc SYSTEMV uses rbx r12
local v[8]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_8_2_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_8_2_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_8_2_0_1_child endp
frame_8_2_0_1_run_tests proc SYSTEMV uses rbx r12
local v[8]:byte
mov byte ptr v,42
invoke frame_8_2_0_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_8_2_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_8_2_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_8_2_1_0_child endp
frame_8_2_1_0_run_tests proc SYSTEMV uses rbx r12
local v[8]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_8_2_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_8_2_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_8_2_1_1_child endp
frame_8_2_1_1_run_tests proc SYSTEMV uses rbx r12
local v[8]:byte
mov byte ptr v,42
invoke frame_8_2_1_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_8_2_1_1_run_tests endp

option redzone:no
option redzone:no
.code
frame_8_3_0_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_8_3_0_0_child endp
frame_8_3_0_0_run_tests proc SYSTEMV uses rbx r12 r13
local v[8]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_8_3_0_0_run_tests endp

option redzone:no
option redzone:no
.code
frame_8_3_0_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_8_3_0_1_child endp
frame_8_3_0_1_run_tests proc SYSTEMV uses rbx r12 r13
local v[8]:byte
mov byte ptr v,42
invoke frame_8_3_0_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_8_3_0_1_run_tests endp

option redzone:no
option redzone:yes
.code
frame_8_3_1_0_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_8_3_1_0_child endp
frame_8_3_1_0_run_tests proc SYSTEMV uses rbx r12 r13
local v[8]:byte
mov byte ptr v,42
movzx eax,byte ptr v
sub eax,42
ret
frame_8_3_1_0_run_tests endp

option redzone:no
option redzone:yes
.code
frame_8_3_1_1_child proc SYSTEMV
movaps xmm15,[rsp+8]
ret
frame_8_3_1_1_child endp
frame_8_3_1_1_run_tests proc SYSTEMV uses rbx r12 r13
local v[8]:byte
mov byte ptr v,42
invoke frame_8_3_1_1_child
movzx eax,byte ptr v
sub eax,42
ret
frame_8_3_1_1_run_tests endp

option redzone:no
option redzone:yes
.code
redzone_call_child proc SYSTEMV
mov qword ptr [rsp-8],0
mov qword ptr [rsp-16],0
ret
redzone_call_child endp
redzone_call_run_tests proc SYSTEMV
local v:qword
mov v,42
call redzone_call_child
mov rax,v
sub rax,42
ret
redzone_call_run_tests endp

option redzone:no
option redzone:yes
.code
redzone_invoke_child proc SYSTEMV
mov qword ptr [rsp-8],0
mov qword ptr [rsp-16],0
ret
redzone_invoke_child endp
redzone_invoke_run_tests proc SYSTEMV
local v:qword
mov v,42
invoke redzone_invoke_child
mov rax,v
sub rax,42
ret
redzone_invoke_run_tests endp

option redzone:no
.code
run_tests proc SYSTEMV uses r12
xor r12d,r12d
invoke frame_0_0_0_0_run_tests
or r12,rax
invoke frame_0_0_0_1_run_tests
or r12,rax
invoke frame_0_0_1_0_run_tests
or r12,rax
invoke frame_0_0_1_1_run_tests
or r12,rax
invoke frame_0_1_0_0_run_tests
or r12,rax
invoke frame_0_1_0_1_run_tests
or r12,rax
invoke frame_0_1_1_0_run_tests
or r12,rax
invoke frame_0_1_1_1_run_tests
or r12,rax
invoke frame_0_2_0_0_run_tests
or r12,rax
invoke frame_0_2_0_1_run_tests
or r12,rax
invoke frame_0_2_1_0_run_tests
or r12,rax
invoke frame_0_2_1_1_run_tests
or r12,rax
invoke frame_0_3_0_0_run_tests
or r12,rax
invoke frame_0_3_0_1_run_tests
or r12,rax
invoke frame_0_3_1_0_run_tests
or r12,rax
invoke frame_0_3_1_1_run_tests
or r12,rax
invoke frame_120_0_0_0_run_tests
or r12,rax
invoke frame_120_0_0_1_run_tests
or r12,rax
invoke frame_120_0_1_0_run_tests
or r12,rax
invoke frame_120_0_1_1_run_tests
or r12,rax
invoke frame_120_1_0_0_run_tests
or r12,rax
invoke frame_120_1_0_1_run_tests
or r12,rax
invoke frame_120_1_1_0_run_tests
or r12,rax
invoke frame_120_1_1_1_run_tests
or r12,rax
invoke frame_120_2_0_0_run_tests
or r12,rax
invoke frame_120_2_0_1_run_tests
or r12,rax
invoke frame_120_2_1_0_run_tests
or r12,rax
invoke frame_120_2_1_1_run_tests
or r12,rax
invoke frame_120_3_0_0_run_tests
or r12,rax
invoke frame_120_3_0_1_run_tests
or r12,rax
invoke frame_120_3_1_0_run_tests
or r12,rax
invoke frame_120_3_1_1_run_tests
or r12,rax
invoke frame_128_0_0_0_run_tests
or r12,rax
invoke frame_128_0_0_1_run_tests
or r12,rax
invoke frame_128_0_1_0_run_tests
or r12,rax
invoke frame_128_0_1_1_run_tests
or r12,rax
invoke frame_128_1_0_0_run_tests
or r12,rax
invoke frame_128_1_0_1_run_tests
or r12,rax
invoke frame_128_1_1_0_run_tests
or r12,rax
invoke frame_128_1_1_1_run_tests
or r12,rax
invoke frame_128_2_0_0_run_tests
or r12,rax
invoke frame_128_2_0_1_run_tests
or r12,rax
invoke frame_128_2_1_0_run_tests
or r12,rax
invoke frame_128_2_1_1_run_tests
or r12,rax
invoke frame_128_3_0_0_run_tests
or r12,rax
invoke frame_128_3_0_1_run_tests
or r12,rax
invoke frame_128_3_1_0_run_tests
or r12,rax
invoke frame_128_3_1_1_run_tests
or r12,rax
invoke frame_136_0_0_0_run_tests
or r12,rax
invoke frame_136_0_0_1_run_tests
or r12,rax
invoke frame_136_0_1_0_run_tests
or r12,rax
invoke frame_136_0_1_1_run_tests
or r12,rax
invoke frame_136_1_0_0_run_tests
or r12,rax
invoke frame_136_1_0_1_run_tests
or r12,rax
invoke frame_136_1_1_0_run_tests
or r12,rax
invoke frame_136_1_1_1_run_tests
or r12,rax
invoke frame_136_2_0_0_run_tests
or r12,rax
invoke frame_136_2_0_1_run_tests
or r12,rax
invoke frame_136_2_1_0_run_tests
or r12,rax
invoke frame_136_2_1_1_run_tests
or r12,rax
invoke frame_136_3_0_0_run_tests
or r12,rax
invoke frame_136_3_0_1_run_tests
or r12,rax
invoke frame_136_3_1_0_run_tests
or r12,rax
invoke frame_136_3_1_1_run_tests
or r12,rax
invoke frame_16_0_0_0_run_tests
or r12,rax
invoke frame_16_0_0_1_run_tests
or r12,rax
invoke frame_16_0_1_0_run_tests
or r12,rax
invoke frame_16_0_1_1_run_tests
or r12,rax
invoke frame_16_1_0_0_run_tests
or r12,rax
invoke frame_16_1_0_1_run_tests
or r12,rax
invoke frame_16_1_1_0_run_tests
or r12,rax
invoke frame_16_1_1_1_run_tests
or r12,rax
invoke frame_16_2_0_0_run_tests
or r12,rax
invoke frame_16_2_0_1_run_tests
or r12,rax
invoke frame_16_2_1_0_run_tests
or r12,rax
invoke frame_16_2_1_1_run_tests
or r12,rax
invoke frame_16_3_0_0_run_tests
or r12,rax
invoke frame_16_3_0_1_run_tests
or r12,rax
invoke frame_16_3_1_0_run_tests
or r12,rax
invoke frame_16_3_1_1_run_tests
or r12,rax
invoke frame_8_0_0_0_run_tests
or r12,rax
invoke frame_8_0_0_1_run_tests
or r12,rax
invoke frame_8_0_1_0_run_tests
or r12,rax
invoke frame_8_0_1_1_run_tests
or r12,rax
invoke frame_8_1_0_0_run_tests
or r12,rax
invoke frame_8_1_0_1_run_tests
or r12,rax
invoke frame_8_1_1_0_run_tests
or r12,rax
invoke frame_8_1_1_1_run_tests
or r12,rax
invoke frame_8_2_0_0_run_tests
or r12,rax
invoke frame_8_2_0_1_run_tests
or r12,rax
invoke frame_8_2_1_0_run_tests
or r12,rax
invoke frame_8_2_1_1_run_tests
or r12,rax
invoke frame_8_3_0_0_run_tests
or r12,rax
invoke frame_8_3_0_1_run_tests
or r12,rax
invoke frame_8_3_1_0_run_tests
or r12,rax
invoke frame_8_3_1_1_run_tests
or r12,rax
invoke redzone_call_run_tests
or r12,rax
invoke redzone_invoke_run_tests
or r12,rax
mov rax,r12
ret
run_tests endp
end
