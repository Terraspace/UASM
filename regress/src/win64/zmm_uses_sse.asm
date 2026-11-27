; Mixed-width USES, low/high EVEX registers, both bases and WIN64 modes.
.x64
option evex:1
option arch:sse
option frame:auto
Sink proto
.code
option stackbase:rsp
option win64:1
Use_rsp_1_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rsp_1_0 endp
Use_rsp_1_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rsp_1_1 endp
option stackbase:rsp
option win64:2
Use_rsp_2_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rsp_2_0 endp
Use_rsp_2_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rsp_2_1 endp
option stackbase:rsp
option win64:3
Use_rsp_3_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rsp_3_0 endp
Use_rsp_3_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rsp_3_1 endp
option stackbase:rsp
option win64:4
Use_rsp_4_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rsp_4_0 endp
Use_rsp_4_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rsp_4_1 endp
option stackbase:rsp
option win64:5
Use_rsp_5_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rsp_5_0 endp
Use_rsp_5_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rsp_5_1 endp
option stackbase:rsp
option win64:6
Use_rsp_6_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rsp_6_0 endp
Use_rsp_6_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rsp_6_1 endp
option stackbase:rsp
option win64:7
Use_rsp_7_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rsp_7_0 endp
Use_rsp_7_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rsp_7_1 endp
option stackbase:rsp
option win64:8
Use_rsp_8_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rsp_8_0 endp
Use_rsp_8_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rsp_8_1 endp
option stackbase:rsp
option win64:9
Use_rsp_9_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rsp_9_0 endp
Use_rsp_9_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rsp_9_1 endp
option stackbase:rsp
option win64:10
Use_rsp_10_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rsp_10_0 endp
Use_rsp_10_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rsp_10_1 endp
option stackbase:rsp
option win64:11
Use_rsp_11_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rsp_11_0 endp
Use_rsp_11_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rsp_11_1 endp
option stackbase:rsp
option win64:12
Use_rsp_12_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rsp_12_0 endp
Use_rsp_12_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rsp_12_1 endp
option stackbase:rsp
option win64:13
Use_rsp_13_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rsp_13_0 endp
Use_rsp_13_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rsp_13_1 endp
option stackbase:rsp
option win64:14
Use_rsp_14_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rsp_14_0 endp
Use_rsp_14_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rsp_14_1 endp
option stackbase:rsp
option win64:15
Use_rsp_15_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rsp_15_0 endp
Use_rsp_15_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rsp_15_1 endp
option stackbase:rbp
option win64:1
Use_rbp_1_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rbp_1_0 endp
Use_rbp_1_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rbp_1_1 endp
option stackbase:rbp
option win64:2
Use_rbp_2_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rbp_2_0 endp
Use_rbp_2_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rbp_2_1 endp
option stackbase:rbp
option win64:3
Use_rbp_3_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rbp_3_0 endp
Use_rbp_3_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rbp_3_1 endp
option stackbase:rbp
option win64:4
Use_rbp_4_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rbp_4_0 endp
Use_rbp_4_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rbp_4_1 endp
option stackbase:rbp
option win64:5
Use_rbp_5_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rbp_5_0 endp
Use_rbp_5_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rbp_5_1 endp
option stackbase:rbp
option win64:6
Use_rbp_6_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rbp_6_0 endp
Use_rbp_6_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rbp_6_1 endp
option stackbase:rbp
option win64:7
Use_rbp_7_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rbp_7_0 endp
Use_rbp_7_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rbp_7_1 endp
option stackbase:rbp
option win64:8
Use_rbp_8_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rbp_8_0 endp
Use_rbp_8_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rbp_8_1 endp
option stackbase:rbp
option win64:9
Use_rbp_9_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rbp_9_0 endp
Use_rbp_9_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rbp_9_1 endp
option stackbase:rbp
option win64:10
Use_rbp_10_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rbp_10_0 endp
Use_rbp_10_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rbp_10_1 endp
option stackbase:rbp
option win64:11
Use_rbp_11_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rbp_11_0 endp
Use_rbp_11_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rbp_11_1 endp
option stackbase:rbp
option win64:12
Use_rbp_12_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rbp_12_0 endp
Use_rbp_12_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rbp_12_1 endp
option stackbase:rbp
option win64:13
Use_rbp_13_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rbp_13_0 endp
Use_rbp_13_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rbp_13_1 endp
option stackbase:rbp
option win64:14
Use_rbp_14_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rbp_14_0 endp
Use_rbp_14_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rbp_14_1 endp
option stackbase:rbp
option win64:15
Use_rbp_15_0 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
ret
Use_rbp_15_0 endp
Use_rbp_15_1 proc frame uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22
local value:qword
mov value,1
invoke Sink
ret
Use_rbp_15_1 endp
end
