
    option flat:1
    option evex:1
    .code

	USE64
	vcvtdq2pd zmm30{k7},YMMWORD PTR [rdx+0xfe0]
	
	VCVTDQ2PD zmm1{k1}{z}, dword bcst myVector
	VCVTDQ2PD zmm1{k1}{z}, myVector{1to8}
	vcvtdq2pd zmm1{z}, myVector{1to8}
	vcvtdq2pd zmm1{k1}{z}, myVector{1to8}

	.data
myVector  dd 12
myVector2 dq 12

END
