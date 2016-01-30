
;--- BT, BTC, BTR, BTS

	.386
	.model flat

	.data

vq	dq 0
vd	dd 0
vw	dw 0
vb	db 0

	.code

	bt ax, 1
	bt vw, 2
	bt ax, cx
	bt vw, cx
	bt eax,3
	bt vd, 4
	bt eax,ecx
	bt vd, ecx

	btc ax, 1
	btc vw, 2
	btc ax, cx
	btc vw, cx
	btc eax,3
	btc vd, 4
	btc eax,ecx
	btc vd, ecx

	btr ax, 1
	btr vw, 2
	btr ax, cx
	btr vw, cx
	btr eax,3
	btr vd, 4
	btr eax,ecx
	btr vd, ecx

	bts ax, 1
	bts vw, 2
	bts ax, cx
	bts vw, cx
	bts eax,3
	bts vd, 4
	bts eax,ecx
	bts vd, ecx

;--- LOCK for BT is invalid, 
;--- for BTC, BTR and BTS LOCK is ok for memory operands only
;--- However, Masm will always accept LOCK for BT, BTC, BTR and BTS

;	lock bt ax,1
;	lock bt eax,1
;	lock bt vw,1
;	lock bt vd,1

;	lock btc ax,1
;	lock btc eax,1
	lock btc vw,1
	lock btc vd,1

;	lock btr ax,1
;	lock btr eax,1
	lock btr vw,1
	lock btr vd,1

;	lock bts ax,1
;	lock bts eax,1
	lock bts vw,1
	lock bts vd,1

if 0	;accepted by JWasm v2.05 and below
	bt  vb,1
	btc vb,1
	btr vb,1
	bts vb,1
endif

end
