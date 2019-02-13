
option flat:1

.code

	use64

	vbroadcastsd ymm2, [r11+8]
	vbroadcastsd ymm12, dword ptr myVector
	
.data

align 32
myVector __m256f <1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0>