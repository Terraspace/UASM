
    option flat:1
    option evex:1
    .code

	USE64

	vmulps zmm1, zmm2, myVector{1to16} ;{1to16}
	vmulps ymm1, ymm2, myVector{1to8} ;{1to8}
	vmulps xmm1, xmm2, myVector{1to4} ;{1to4}
    vmulps zmm1, zmm2, dword bcst myVector ;{1to16}
	vmulps ymm1, ymm2, dword bcst myVector ;{1to8}
	vmulps xmm1, xmm2, dword bcst myVector ;{1to4}
	
    vmulpd zmm1, zmm2, myVector2{1to8} ;{1to8}
	vmulpd ymm1, ymm2, myVector2{1to4} ;{1to4}
	vmulpd xmm1, xmm2, myVector2{1to2} ;{1to2}
    vmulpd zmm1, zmm2, qword bcst myVector2 ;{1to8}
	vmulpd ymm1, ymm2, qword bcst myVector2 ;{1to4}
	vmulpd xmm1, xmm2, qword bcst myVector2 ;{1to2}

    vpcmpeqd k5,zmm30, [rdx+1fch]{1to16} ;{1to16}
	vpcmpeqd k5,ymm30, [rdx+1fch]{1to8} ;{1to8}
	vpcmpeqd k5,xmm30, [rdx+1fch]{1to4} ;{1to4}	
    vpcmpeqd k5,zmm30, dword bcst [rdx+1fch] ;{1to16}
	vpcmpeqd k5,ymm30, dword bcst [rdx+1fch] ;{1to8}
	vpcmpeqd k5,xmm30, dword bcst [rdx+1fch] ;{1to4}

	vpcmpeqq k5,zmm30, [rdx+1fch]{1to8} ;{1to8}
	vpcmpeqq k5,ymm30, [rdx+1fch]{1to4} ;{1to4}
	vpcmpeqq k5,xmm30, [rdx+1fch]{1to2} ;{1to2}
    vpcmpeqq k5,zmm30, qword bcst [rdx+1fch] ;{1to8}
	vpcmpeqq k5,ymm30, qword bcst [rdx+1fch] ;{1to4}
	vpcmpeqq k5,xmm30, qword bcst [rdx+1fch] ;{1to2}
	
	.data
myVector  dd 12
myVector2 dq 12

END
