
	.x64
	.model flat
.data

align 32
floatvar1 REAL4 2.0
floatvar2 REAL4 1.0

doublevar1 REAL8 2.0
doublevar2 REAL8 1.0

.code
	mov rax,real8 ptr 123.3
	
	LOADSS xmm0, 1.0
	LOADSS xmm1, 2.0
	LOADSS xmm3, 1.0

	lea rdx,floatvar1
	mov rbx,4

	.if(xmm0 < FP4(1.5))
		xor eax,eax
	.endif
	.if(xmm0 > FP4(2))
		xor eax,eax
	.endif
		
	.if(xmm0 < floatvar1)
		xor eax,eax
	.endif
	.if(xmm0 == floatvar2)
		xor eax,eax
	.endif
	
	.if(xmm0 < [rdx])
		xor eax,eax
	.endif
	.if(xmm0 == [rdx+rbx])
		xor eax,eax	
	.endif
			
	.if(xmm0 < xmm1)
		xor eax,eax	
	.endif
	.if(xmm0 > xmm1)
		xor eax,eax	
	.endif
	.if(xmm0 <= xmm1)
		xor eax,eax	
	.endif
	.if(xmm0 == xmm3)
		xor eax,eax	
	.endif

	.if(real4 ptr xmm0 < xmm1)
		xor eax,eax	
	.endif
	.if(xmm0 < real4 ptr xmm1)
		xor eax,eax	
	.endif
	.if(asfloat(xmm0) < xmm1)
		xor eax,eax	
	.endif
		
	LOADSD xmm0, 1.0
	LOADSD xmm1, 2.0
	LOADSD xmm3, 1.0
	
	.if(xmm0 < doublevar1)
		xor eax,eax
	.endif
	.if(xmm0 == doublevar2)
		xor eax,eax
	.endif
	.if(real8 ptr xmm0 < FP8(1.5))
		xor eax,eax	
	.endif
	.if(xmm0 < real8 ptr FP8(1.5))
		xor eax,eax	
	.endif	
	.if(real8 ptr xmm0 < xmm1)
		xor eax,eax	
	.endif	
	.if(real8 ptr xmm0 > real8 ptr xmm1)
		xor eax,eax	
	.endif
	.if(real8 ptr xmm0 <= xmm1)
		xor eax,eax	
	.endif
	.if(xmm0 == real8 ptr xmm3)
		xor eax,eax	
	.endif
	.if(xmm0 == asdouble(xmm3))
		xor eax,eax
	.elseif(xmm0 > asdouble(xmm2))
		xor eax,eax	
	.endif
	
	LOADSS xmm0,1.0
	LOADSS xmm1,2.0
	.while(xmm0 < xmm1)
		vaddss xmm0,xmm0,FP4(0.1)
	.endw

end
