
option flat:1
option evex:1

.code

	use64

	vfmadd132sd xmm1, xmm30, mmword ptr [r11]	
	{evex} vfmadd132sd xmm1, xmm30, mmword ptr [r11]
	
.data

align 32
myVector __m256f <1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0>