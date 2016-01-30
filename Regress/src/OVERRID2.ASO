
;--- regression in v2.07

	.386
	.MODEL SMALL

	.data
v1	db 0
	.code

;--- Masm emits no warning
	mov al,ds:[ebx + DGROUP:v1]             ;warning in v2.06, error in v2.07
	mov al,ds:[ebx*4 + DGROUP:v1]           ;no warning in v2.06, error in v2.07
	mov al,es:[ebx + DGROUP:v1]             ;warning in v2.06, error in v2.07
	mov al,es:[ebx*4 + DGROUP:v1]           ;no warning in v2.06, error in v2.07
	mov al,es:[ebx*4 + ds:v1]               ;error in v2.07+
	mov al,DGROUP:[ebx*4 + DGROUP:v1]       ;error in v2.07+

;--- offset operator is not accepted by Masm
;	mov al,ds:[ebx + offset DGROUP:v1]      ;warning in v2.06
;	mov al,ds:[ebx*4 + offset DGROUP:v1]    ;no warning in v2.06

	end
