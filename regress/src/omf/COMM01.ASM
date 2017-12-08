
;--- communal variables test for OMF

	.286
	.model small

	.stack
	.data

comm v1:127
comm v2:128
comm v3:129
comm vx1:WORD:127
comm vx2:WORD:128
comm vx3:WORD:129

comm far f1:127
comm far f2:128
comm far f3:129
comm far fx1:127:2
comm far fx2:128:3
comm far fx3:129:4
comm far fy1:4:200

	.code

_start:
	mov al,[v1]
	mov al,[v2]
	ret

	END _start
