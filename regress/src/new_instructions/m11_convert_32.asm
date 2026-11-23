; AVX-512 FP16: register/memory widths, masks, tuples and legal rounding/SAE.
.686p
.xmm
.model flat
option evex:1
.code
vcvtdq2ph xmm1, xmm2
vcvtdq2ph xmm1{k3}{z}, xmm2
vcvtdq2ph xmm1{k3}, xmmword ptr [ebx+esi*2+0]
vcvtdq2ph xmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vcvtdq2ph xmm1{k3}, xmmword ptr [ebx+esi*2+2048]
vcvtdq2ph xmm1{k3}, xmmword ptr [ebx+esi*2+1]
vcvtdq2ph xmm1{k3}, dword ptr [ebx+esi*2+508]{1to4}
vcvtdq2ph xmm1, ymm2
vcvtdq2ph xmm1{k3}{z}, ymm2
vcvtdq2ph xmm1{k3}, ymmword ptr [ebx+esi*2+0]
vcvtdq2ph xmm1{k3}{z}, ymmword ptr [ebx+esi*2+4064]
vcvtdq2ph xmm1{k3}, ymmword ptr [ebx+esi*2+4096]
vcvtdq2ph xmm1{k3}, ymmword ptr [ebx+esi*2+1]
vcvtdq2ph xmm1{k3}, dword ptr [ebx+esi*2+508]{1to8}
vcvtdq2ph ymm1, zmm2
vcvtdq2ph ymm1{k3}{z}, zmm2
vcvtdq2ph ymm1{k3}, zmm2, {rn-sae}
vcvtdq2ph ymm1{k3}, zmm2, {rd-sae}
vcvtdq2ph ymm1{k3}, zmm2, {ru-sae}
vcvtdq2ph ymm1{k3}, zmm2, {rz-sae}
vcvtdq2ph ymm1{k3}, zmmword ptr [ebx+esi*2+0]
vcvtdq2ph ymm1{k3}{z}, zmmword ptr [ebx+esi*2+8128]
vcvtdq2ph ymm1{k3}, zmmword ptr [ebx+esi*2+8192]
vcvtdq2ph ymm1{k3}, zmmword ptr [ebx+esi*2+1]
vcvtdq2ph ymm1{k3}, dword ptr [ebx+esi*2+508]{1to16}
vcvtpd2ph xmm1, xmm2
vcvtpd2ph xmm1{k3}{z}, xmm2
vcvtpd2ph xmm1{k3}, xmmword ptr [ebx+esi*2+0]
vcvtpd2ph xmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vcvtpd2ph xmm1{k3}, xmmword ptr [ebx+esi*2+2048]
vcvtpd2ph xmm1{k3}, xmmword ptr [ebx+esi*2+1]
vcvtpd2ph xmm1{k3}, qword ptr [ebx+esi*2+1016]{1to2}
vcvtpd2ph xmm1, ymm2
vcvtpd2ph xmm1{k3}{z}, ymm2
vcvtpd2ph xmm1{k3}, ymmword ptr [ebx+esi*2+0]
vcvtpd2ph xmm1{k3}{z}, ymmword ptr [ebx+esi*2+4064]
vcvtpd2ph xmm1{k3}, ymmword ptr [ebx+esi*2+4096]
vcvtpd2ph xmm1{k3}, ymmword ptr [ebx+esi*2+1]
vcvtpd2ph xmm1{k3}, qword ptr [ebx+esi*2+1016]{1to4}
vcvtpd2ph xmm1, zmm2
vcvtpd2ph xmm1{k3}{z}, zmm2
vcvtpd2ph xmm1{k3}, zmm2, {rn-sae}
vcvtpd2ph xmm1{k3}, zmm2, {rd-sae}
vcvtpd2ph xmm1{k3}, zmm2, {ru-sae}
vcvtpd2ph xmm1{k3}, zmm2, {rz-sae}
vcvtpd2ph xmm1{k3}, zmmword ptr [ebx+esi*2+0]
vcvtpd2ph xmm1{k3}{z}, zmmword ptr [ebx+esi*2+8128]
vcvtpd2ph xmm1{k3}, zmmword ptr [ebx+esi*2+8192]
vcvtpd2ph xmm1{k3}, zmmword ptr [ebx+esi*2+1]
vcvtpd2ph xmm1{k3}, qword ptr [ebx+esi*2+1016]{1to8}
vcvtph2dq xmm1, xmm2
vcvtph2dq xmm1{k3}{z}, xmm2
vcvtph2dq xmm1{k3}, qword ptr [ebx+esi*2+0]
vcvtph2dq xmm1{k3}{z}, qword ptr [ebx+esi*2+1016]
vcvtph2dq xmm1{k3}, qword ptr [ebx+esi*2+1024]
vcvtph2dq xmm1{k3}, qword ptr [ebx+esi*2+1]
vcvtph2dq xmm1{k3}, word ptr [ebx+esi*2+254]{1to4}
vcvtph2dq ymm1, xmm2
vcvtph2dq ymm1{k3}{z}, xmm2
vcvtph2dq ymm1{k3}, xmmword ptr [ebx+esi*2+0]
vcvtph2dq ymm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vcvtph2dq ymm1{k3}, xmmword ptr [ebx+esi*2+2048]
vcvtph2dq ymm1{k3}, xmmword ptr [ebx+esi*2+1]
vcvtph2dq ymm1{k3}, word ptr [ebx+esi*2+254]{1to8}
vcvtph2dq zmm1, ymm2
vcvtph2dq zmm1{k3}{z}, ymm2
vcvtph2dq zmm1{k3}, ymm2, {rn-sae}
vcvtph2dq zmm1{k3}, ymm2, {rd-sae}
vcvtph2dq zmm1{k3}, ymm2, {ru-sae}
vcvtph2dq zmm1{k3}, ymm2, {rz-sae}
vcvtph2dq zmm1{k3}, ymmword ptr [ebx+esi*2+0]
vcvtph2dq zmm1{k3}{z}, ymmword ptr [ebx+esi*2+4064]
vcvtph2dq zmm1{k3}, ymmword ptr [ebx+esi*2+4096]
vcvtph2dq zmm1{k3}, ymmword ptr [ebx+esi*2+1]
vcvtph2dq zmm1{k3}, word ptr [ebx+esi*2+254]{1to16}
vcvtph2pd xmm1, xmm2
vcvtph2pd xmm1{k3}{z}, xmm2
vcvtph2pd xmm1{k3}, dword ptr [ebx+esi*2+0]
vcvtph2pd xmm1{k3}{z}, dword ptr [ebx+esi*2+508]
vcvtph2pd xmm1{k3}, dword ptr [ebx+esi*2+512]
vcvtph2pd xmm1{k3}, dword ptr [ebx+esi*2+1]
vcvtph2pd xmm1{k3}, word ptr [ebx+esi*2+254]{1to2}
vcvtph2pd ymm1, xmm2
vcvtph2pd ymm1{k3}{z}, xmm2
vcvtph2pd ymm1{k3}, qword ptr [ebx+esi*2+0]
vcvtph2pd ymm1{k3}{z}, qword ptr [ebx+esi*2+1016]
vcvtph2pd ymm1{k3}, qword ptr [ebx+esi*2+1024]
vcvtph2pd ymm1{k3}, qword ptr [ebx+esi*2+1]
vcvtph2pd ymm1{k3}, word ptr [ebx+esi*2+254]{1to4}
vcvtph2pd zmm1, xmm2
vcvtph2pd zmm1{k3}{z}, xmm2
vcvtph2pd zmm1{k3}, xmm2, {sae}
vcvtph2pd zmm1{k3}, xmmword ptr [ebx+esi*2+0]
vcvtph2pd zmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vcvtph2pd zmm1{k3}, xmmword ptr [ebx+esi*2+2048]
vcvtph2pd zmm1{k3}, xmmword ptr [ebx+esi*2+1]
vcvtph2pd zmm1{k3}, word ptr [ebx+esi*2+254]{1to8}
vcvtph2psx xmm1, xmm2
vcvtph2psx xmm1{k3}{z}, xmm2
vcvtph2psx xmm1{k3}, qword ptr [ebx+esi*2+0]
vcvtph2psx xmm1{k3}{z}, qword ptr [ebx+esi*2+1016]
vcvtph2psx xmm1{k3}, qword ptr [ebx+esi*2+1024]
vcvtph2psx xmm1{k3}, qword ptr [ebx+esi*2+1]
vcvtph2psx xmm1{k3}, word ptr [ebx+esi*2+254]{1to4}
vcvtph2psx ymm1, xmm2
vcvtph2psx ymm1{k3}{z}, xmm2
vcvtph2psx ymm1{k3}, xmmword ptr [ebx+esi*2+0]
vcvtph2psx ymm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vcvtph2psx ymm1{k3}, xmmword ptr [ebx+esi*2+2048]
vcvtph2psx ymm1{k3}, xmmword ptr [ebx+esi*2+1]
vcvtph2psx ymm1{k3}, word ptr [ebx+esi*2+254]{1to8}
vcvtph2psx zmm1, ymm2
vcvtph2psx zmm1{k3}{z}, ymm2
vcvtph2psx zmm1{k3}, ymm2, {sae}
vcvtph2psx zmm1{k3}, ymmword ptr [ebx+esi*2+0]
vcvtph2psx zmm1{k3}{z}, ymmword ptr [ebx+esi*2+4064]
vcvtph2psx zmm1{k3}, ymmword ptr [ebx+esi*2+4096]
vcvtph2psx zmm1{k3}, ymmword ptr [ebx+esi*2+1]
vcvtph2psx zmm1{k3}, word ptr [ebx+esi*2+254]{1to16}
vcvtph2qq xmm1, xmm2
vcvtph2qq xmm1{k3}{z}, xmm2
vcvtph2qq xmm1{k3}, dword ptr [ebx+esi*2+0]
vcvtph2qq xmm1{k3}{z}, dword ptr [ebx+esi*2+508]
vcvtph2qq xmm1{k3}, dword ptr [ebx+esi*2+512]
vcvtph2qq xmm1{k3}, dword ptr [ebx+esi*2+1]
vcvtph2qq xmm1{k3}, word ptr [ebx+esi*2+254]{1to2}
vcvtph2qq ymm1, xmm2
vcvtph2qq ymm1{k3}{z}, xmm2
vcvtph2qq ymm1{k3}, qword ptr [ebx+esi*2+0]
vcvtph2qq ymm1{k3}{z}, qword ptr [ebx+esi*2+1016]
vcvtph2qq ymm1{k3}, qword ptr [ebx+esi*2+1024]
vcvtph2qq ymm1{k3}, qword ptr [ebx+esi*2+1]
vcvtph2qq ymm1{k3}, word ptr [ebx+esi*2+254]{1to4}
vcvtph2qq zmm1, xmm2
vcvtph2qq zmm1{k3}{z}, xmm2
vcvtph2qq zmm1{k3}, xmm2, {rn-sae}
vcvtph2qq zmm1{k3}, xmm2, {rd-sae}
vcvtph2qq zmm1{k3}, xmm2, {ru-sae}
vcvtph2qq zmm1{k3}, xmm2, {rz-sae}
vcvtph2qq zmm1{k3}, xmmword ptr [ebx+esi*2+0]
vcvtph2qq zmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vcvtph2qq zmm1{k3}, xmmword ptr [ebx+esi*2+2048]
vcvtph2qq zmm1{k3}, xmmword ptr [ebx+esi*2+1]
vcvtph2qq zmm1{k3}, word ptr [ebx+esi*2+254]{1to8}
vcvtph2udq xmm1, xmm2
vcvtph2udq xmm1{k3}{z}, xmm2
vcvtph2udq xmm1{k3}, qword ptr [ebx+esi*2+0]
vcvtph2udq xmm1{k3}{z}, qword ptr [ebx+esi*2+1016]
vcvtph2udq xmm1{k3}, qword ptr [ebx+esi*2+1024]
vcvtph2udq xmm1{k3}, qword ptr [ebx+esi*2+1]
vcvtph2udq xmm1{k3}, word ptr [ebx+esi*2+254]{1to4}
vcvtph2udq ymm1, xmm2
vcvtph2udq ymm1{k3}{z}, xmm2
vcvtph2udq ymm1{k3}, xmmword ptr [ebx+esi*2+0]
vcvtph2udq ymm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vcvtph2udq ymm1{k3}, xmmword ptr [ebx+esi*2+2048]
vcvtph2udq ymm1{k3}, xmmword ptr [ebx+esi*2+1]
vcvtph2udq ymm1{k3}, word ptr [ebx+esi*2+254]{1to8}
vcvtph2udq zmm1, ymm2
vcvtph2udq zmm1{k3}{z}, ymm2
vcvtph2udq zmm1{k3}, ymm2, {rn-sae}
vcvtph2udq zmm1{k3}, ymm2, {rd-sae}
vcvtph2udq zmm1{k3}, ymm2, {ru-sae}
vcvtph2udq zmm1{k3}, ymm2, {rz-sae}
vcvtph2udq zmm1{k3}, ymmword ptr [ebx+esi*2+0]
vcvtph2udq zmm1{k3}{z}, ymmword ptr [ebx+esi*2+4064]
vcvtph2udq zmm1{k3}, ymmword ptr [ebx+esi*2+4096]
vcvtph2udq zmm1{k3}, ymmword ptr [ebx+esi*2+1]
vcvtph2udq zmm1{k3}, word ptr [ebx+esi*2+254]{1to16}
vcvtph2uqq xmm1, xmm2
vcvtph2uqq xmm1{k3}{z}, xmm2
vcvtph2uqq xmm1{k3}, dword ptr [ebx+esi*2+0]
vcvtph2uqq xmm1{k3}{z}, dword ptr [ebx+esi*2+508]
vcvtph2uqq xmm1{k3}, dword ptr [ebx+esi*2+512]
vcvtph2uqq xmm1{k3}, dword ptr [ebx+esi*2+1]
vcvtph2uqq xmm1{k3}, word ptr [ebx+esi*2+254]{1to2}
vcvtph2uqq ymm1, xmm2
vcvtph2uqq ymm1{k3}{z}, xmm2
vcvtph2uqq ymm1{k3}, qword ptr [ebx+esi*2+0]
vcvtph2uqq ymm1{k3}{z}, qword ptr [ebx+esi*2+1016]
vcvtph2uqq ymm1{k3}, qword ptr [ebx+esi*2+1024]
vcvtph2uqq ymm1{k3}, qword ptr [ebx+esi*2+1]
vcvtph2uqq ymm1{k3}, word ptr [ebx+esi*2+254]{1to4}
vcvtph2uqq zmm1, xmm2
vcvtph2uqq zmm1{k3}{z}, xmm2
vcvtph2uqq zmm1{k3}, xmm2, {rn-sae}
vcvtph2uqq zmm1{k3}, xmm2, {rd-sae}
vcvtph2uqq zmm1{k3}, xmm2, {ru-sae}
vcvtph2uqq zmm1{k3}, xmm2, {rz-sae}
vcvtph2uqq zmm1{k3}, xmmword ptr [ebx+esi*2+0]
vcvtph2uqq zmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vcvtph2uqq zmm1{k3}, xmmword ptr [ebx+esi*2+2048]
vcvtph2uqq zmm1{k3}, xmmword ptr [ebx+esi*2+1]
vcvtph2uqq zmm1{k3}, word ptr [ebx+esi*2+254]{1to8}
vcvtph2uw xmm1, xmm2
vcvtph2uw xmm1{k3}{z}, xmm2
vcvtph2uw xmm1{k3}, xmmword ptr [ebx+esi*2+0]
vcvtph2uw xmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vcvtph2uw xmm1{k3}, xmmword ptr [ebx+esi*2+2048]
vcvtph2uw xmm1{k3}, xmmword ptr [ebx+esi*2+1]
vcvtph2uw xmm1{k3}, word ptr [ebx+esi*2+254]{1to8}
vcvtph2uw ymm1, ymm2
vcvtph2uw ymm1{k3}{z}, ymm2
vcvtph2uw ymm1{k3}, ymmword ptr [ebx+esi*2+0]
vcvtph2uw ymm1{k3}{z}, ymmword ptr [ebx+esi*2+4064]
vcvtph2uw ymm1{k3}, ymmword ptr [ebx+esi*2+4096]
vcvtph2uw ymm1{k3}, ymmword ptr [ebx+esi*2+1]
vcvtph2uw ymm1{k3}, word ptr [ebx+esi*2+254]{1to16}
vcvtph2uw zmm1, zmm2
vcvtph2uw zmm1{k3}{z}, zmm2
vcvtph2uw zmm1{k3}, zmm2, {rn-sae}
vcvtph2uw zmm1{k3}, zmm2, {rd-sae}
vcvtph2uw zmm1{k3}, zmm2, {ru-sae}
vcvtph2uw zmm1{k3}, zmm2, {rz-sae}
vcvtph2uw zmm1{k3}, zmmword ptr [ebx+esi*2+0]
vcvtph2uw zmm1{k3}{z}, zmmword ptr [ebx+esi*2+8128]
vcvtph2uw zmm1{k3}, zmmword ptr [ebx+esi*2+8192]
vcvtph2uw zmm1{k3}, zmmword ptr [ebx+esi*2+1]
vcvtph2uw zmm1{k3}, word ptr [ebx+esi*2+254]{1to32}
vcvtph2w xmm1, xmm2
vcvtph2w xmm1{k3}{z}, xmm2
vcvtph2w xmm1{k3}, xmmword ptr [ebx+esi*2+0]
vcvtph2w xmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vcvtph2w xmm1{k3}, xmmword ptr [ebx+esi*2+2048]
vcvtph2w xmm1{k3}, xmmword ptr [ebx+esi*2+1]
vcvtph2w xmm1{k3}, word ptr [ebx+esi*2+254]{1to8}
vcvtph2w ymm1, ymm2
vcvtph2w ymm1{k3}{z}, ymm2
vcvtph2w ymm1{k3}, ymmword ptr [ebx+esi*2+0]
vcvtph2w ymm1{k3}{z}, ymmword ptr [ebx+esi*2+4064]
vcvtph2w ymm1{k3}, ymmword ptr [ebx+esi*2+4096]
vcvtph2w ymm1{k3}, ymmword ptr [ebx+esi*2+1]
vcvtph2w ymm1{k3}, word ptr [ebx+esi*2+254]{1to16}
vcvtph2w zmm1, zmm2
vcvtph2w zmm1{k3}{z}, zmm2
vcvtph2w zmm1{k3}, zmm2, {rn-sae}
vcvtph2w zmm1{k3}, zmm2, {rd-sae}
vcvtph2w zmm1{k3}, zmm2, {ru-sae}
vcvtph2w zmm1{k3}, zmm2, {rz-sae}
vcvtph2w zmm1{k3}, zmmword ptr [ebx+esi*2+0]
vcvtph2w zmm1{k3}{z}, zmmword ptr [ebx+esi*2+8128]
vcvtph2w zmm1{k3}, zmmword ptr [ebx+esi*2+8192]
vcvtph2w zmm1{k3}, zmmword ptr [ebx+esi*2+1]
vcvtph2w zmm1{k3}, word ptr [ebx+esi*2+254]{1to32}
vcvtps2phx xmm1, xmm2
vcvtps2phx xmm1{k3}{z}, xmm2
vcvtps2phx xmm1{k3}, xmmword ptr [ebx+esi*2+0]
vcvtps2phx xmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vcvtps2phx xmm1{k3}, xmmword ptr [ebx+esi*2+2048]
vcvtps2phx xmm1{k3}, xmmword ptr [ebx+esi*2+1]
vcvtps2phx xmm1{k3}, dword ptr [ebx+esi*2+508]{1to4}
vcvtps2phx xmm1, ymm2
vcvtps2phx xmm1{k3}{z}, ymm2
vcvtps2phx xmm1{k3}, ymmword ptr [ebx+esi*2+0]
vcvtps2phx xmm1{k3}{z}, ymmword ptr [ebx+esi*2+4064]
vcvtps2phx xmm1{k3}, ymmword ptr [ebx+esi*2+4096]
vcvtps2phx xmm1{k3}, ymmword ptr [ebx+esi*2+1]
vcvtps2phx xmm1{k3}, dword ptr [ebx+esi*2+508]{1to8}
vcvtps2phx ymm1, zmm2
vcvtps2phx ymm1{k3}{z}, zmm2
vcvtps2phx ymm1{k3}, zmm2, {rn-sae}
vcvtps2phx ymm1{k3}, zmm2, {rd-sae}
vcvtps2phx ymm1{k3}, zmm2, {ru-sae}
vcvtps2phx ymm1{k3}, zmm2, {rz-sae}
vcvtps2phx ymm1{k3}, zmmword ptr [ebx+esi*2+0]
vcvtps2phx ymm1{k3}{z}, zmmword ptr [ebx+esi*2+8128]
vcvtps2phx ymm1{k3}, zmmword ptr [ebx+esi*2+8192]
vcvtps2phx ymm1{k3}, zmmword ptr [ebx+esi*2+1]
vcvtps2phx ymm1{k3}, dword ptr [ebx+esi*2+508]{1to16}
vcvtqq2ph xmm1, xmm2
vcvtqq2ph xmm1{k3}{z}, xmm2
vcvtqq2ph xmm1{k3}, xmmword ptr [ebx+esi*2+0]
vcvtqq2ph xmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vcvtqq2ph xmm1{k3}, xmmword ptr [ebx+esi*2+2048]
vcvtqq2ph xmm1{k3}, xmmword ptr [ebx+esi*2+1]
vcvtqq2ph xmm1{k3}, qword ptr [ebx+esi*2+1016]{1to2}
vcvtqq2ph xmm1, ymm2
vcvtqq2ph xmm1{k3}{z}, ymm2
vcvtqq2ph xmm1{k3}, ymmword ptr [ebx+esi*2+0]
vcvtqq2ph xmm1{k3}{z}, ymmword ptr [ebx+esi*2+4064]
vcvtqq2ph xmm1{k3}, ymmword ptr [ebx+esi*2+4096]
vcvtqq2ph xmm1{k3}, ymmword ptr [ebx+esi*2+1]
vcvtqq2ph xmm1{k3}, qword ptr [ebx+esi*2+1016]{1to4}
vcvtqq2ph xmm1, zmm2
vcvtqq2ph xmm1{k3}{z}, zmm2
vcvtqq2ph xmm1{k3}, zmm2, {rn-sae}
vcvtqq2ph xmm1{k3}, zmm2, {rd-sae}
vcvtqq2ph xmm1{k3}, zmm2, {ru-sae}
vcvtqq2ph xmm1{k3}, zmm2, {rz-sae}
vcvtqq2ph xmm1{k3}, zmmword ptr [ebx+esi*2+0]
vcvtqq2ph xmm1{k3}{z}, zmmword ptr [ebx+esi*2+8128]
vcvtqq2ph xmm1{k3}, zmmword ptr [ebx+esi*2+8192]
vcvtqq2ph xmm1{k3}, zmmword ptr [ebx+esi*2+1]
vcvtqq2ph xmm1{k3}, qword ptr [ebx+esi*2+1016]{1to8}
vcvtsd2sh xmm1, xmm2, xmm3
vcvtsd2sh xmm1{k3}{z}, xmm2, xmm3
vcvtsd2sh xmm1{k3}, xmm2, xmm3, {rn-sae}
vcvtsd2sh xmm1{k3}, xmm2, xmm3, {rd-sae}
vcvtsd2sh xmm1{k3}, xmm2, xmm3, {ru-sae}
vcvtsd2sh xmm1{k3}, xmm2, xmm3, {rz-sae}
vcvtsd2sh xmm1{k3}, xmm2, qword ptr [ebx+esi*2+0]
vcvtsd2sh xmm1{k3}{z}, xmm2, qword ptr [ebx+esi*2+1016]
vcvtsd2sh xmm1{k3}, xmm2, qword ptr [ebx+esi*2+1024]
vcvtsd2sh xmm1{k3}, xmm2, qword ptr [ebx+esi*2+1]
vcvtsh2sd xmm1, xmm2, xmm3
vcvtsh2sd xmm1{k3}{z}, xmm2, xmm3
vcvtsh2sd xmm1{k3}, xmm2, xmm3, {sae}
vcvtsh2sd xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vcvtsh2sd xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vcvtsh2sd xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vcvtsh2sd xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vcvtsh2si ecx, xmm2
vcvtsh2si ecx, xmm2
vcvtsh2si ecx, xmm2, {rn-sae}
vcvtsh2si ecx, xmm2, {rd-sae}
vcvtsh2si ecx, xmm2, {ru-sae}
vcvtsh2si ecx, xmm2, {rz-sae}
vcvtsh2si ecx, word ptr [ebx+esi*2+0]
vcvtsh2si ecx, word ptr [ebx+esi*2+254]
vcvtsh2si ecx, word ptr [ebx+esi*2+256]
vcvtsh2si ecx, word ptr [ebx+esi*2+1]
vcvtsh2ss xmm1, xmm2, xmm3
vcvtsh2ss xmm1{k3}{z}, xmm2, xmm3
vcvtsh2ss xmm1{k3}, xmm2, xmm3, {sae}
vcvtsh2ss xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vcvtsh2ss xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vcvtsh2ss xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vcvtsh2ss xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vcvtsh2usi ecx, xmm2
vcvtsh2usi ecx, xmm2
vcvtsh2usi ecx, xmm2, {rn-sae}
vcvtsh2usi ecx, xmm2, {rd-sae}
vcvtsh2usi ecx, xmm2, {ru-sae}
vcvtsh2usi ecx, xmm2, {rz-sae}
vcvtsh2usi ecx, word ptr [ebx+esi*2+0]
vcvtsh2usi ecx, word ptr [ebx+esi*2+254]
vcvtsh2usi ecx, word ptr [ebx+esi*2+256]
vcvtsh2usi ecx, word ptr [ebx+esi*2+1]
vcvtsi2sh xmm1, xmm2, ecx
vcvtsi2sh xmm1, xmm2, ecx
vcvtsi2sh xmm1, xmm2, ecx, {rn-sae}
vcvtsi2sh xmm1, xmm2, ecx, {rd-sae}
vcvtsi2sh xmm1, xmm2, ecx, {ru-sae}
vcvtsi2sh xmm1, xmm2, ecx, {rz-sae}
vcvtsi2sh xmm1, xmm2, dword ptr [ebx+esi*2+0]
vcvtsi2sh xmm1, xmm2, dword ptr [ebx+esi*2+508]
vcvtsi2sh xmm1, xmm2, dword ptr [ebx+esi*2+512]
vcvtsi2sh xmm1, xmm2, dword ptr [ebx+esi*2+1]
vcvtss2sh xmm1, xmm2, xmm3
vcvtss2sh xmm1{k3}{z}, xmm2, xmm3
vcvtss2sh xmm1{k3}, xmm2, xmm3, {rn-sae}
vcvtss2sh xmm1{k3}, xmm2, xmm3, {rd-sae}
vcvtss2sh xmm1{k3}, xmm2, xmm3, {ru-sae}
vcvtss2sh xmm1{k3}, xmm2, xmm3, {rz-sae}
vcvtss2sh xmm1{k3}, xmm2, dword ptr [ebx+esi*2+0]
vcvtss2sh xmm1{k3}{z}, xmm2, dword ptr [ebx+esi*2+508]
vcvtss2sh xmm1{k3}, xmm2, dword ptr [ebx+esi*2+512]
vcvtss2sh xmm1{k3}, xmm2, dword ptr [ebx+esi*2+1]
vcvttph2dq xmm1, xmm2
vcvttph2dq xmm1{k3}{z}, xmm2
vcvttph2dq xmm1{k3}, qword ptr [ebx+esi*2+0]
vcvttph2dq xmm1{k3}{z}, qword ptr [ebx+esi*2+1016]
vcvttph2dq xmm1{k3}, qword ptr [ebx+esi*2+1024]
vcvttph2dq xmm1{k3}, qword ptr [ebx+esi*2+1]
vcvttph2dq xmm1{k3}, word ptr [ebx+esi*2+254]{1to4}
vcvttph2dq ymm1, xmm2
vcvttph2dq ymm1{k3}{z}, xmm2
vcvttph2dq ymm1{k3}, xmmword ptr [ebx+esi*2+0]
vcvttph2dq ymm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vcvttph2dq ymm1{k3}, xmmword ptr [ebx+esi*2+2048]
vcvttph2dq ymm1{k3}, xmmword ptr [ebx+esi*2+1]
vcvttph2dq ymm1{k3}, word ptr [ebx+esi*2+254]{1to8}
vcvttph2dq zmm1, ymm2
vcvttph2dq zmm1{k3}{z}, ymm2
vcvttph2dq zmm1{k3}, ymm2, {sae}
vcvttph2dq zmm1{k3}, ymmword ptr [ebx+esi*2+0]
vcvttph2dq zmm1{k3}{z}, ymmword ptr [ebx+esi*2+4064]
vcvttph2dq zmm1{k3}, ymmword ptr [ebx+esi*2+4096]
vcvttph2dq zmm1{k3}, ymmword ptr [ebx+esi*2+1]
vcvttph2dq zmm1{k3}, word ptr [ebx+esi*2+254]{1to16}
vcvttph2qq xmm1, xmm2
vcvttph2qq xmm1{k3}{z}, xmm2
vcvttph2qq xmm1{k3}, dword ptr [ebx+esi*2+0]
vcvttph2qq xmm1{k3}{z}, dword ptr [ebx+esi*2+508]
vcvttph2qq xmm1{k3}, dword ptr [ebx+esi*2+512]
vcvttph2qq xmm1{k3}, dword ptr [ebx+esi*2+1]
vcvttph2qq xmm1{k3}, word ptr [ebx+esi*2+254]{1to2}
vcvttph2qq ymm1, xmm2
vcvttph2qq ymm1{k3}{z}, xmm2
vcvttph2qq ymm1{k3}, qword ptr [ebx+esi*2+0]
vcvttph2qq ymm1{k3}{z}, qword ptr [ebx+esi*2+1016]
vcvttph2qq ymm1{k3}, qword ptr [ebx+esi*2+1024]
vcvttph2qq ymm1{k3}, qword ptr [ebx+esi*2+1]
vcvttph2qq ymm1{k3}, word ptr [ebx+esi*2+254]{1to4}
vcvttph2qq zmm1, xmm2
vcvttph2qq zmm1{k3}{z}, xmm2
vcvttph2qq zmm1{k3}, xmm2, {sae}
vcvttph2qq zmm1{k3}, xmmword ptr [ebx+esi*2+0]
vcvttph2qq zmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vcvttph2qq zmm1{k3}, xmmword ptr [ebx+esi*2+2048]
vcvttph2qq zmm1{k3}, xmmword ptr [ebx+esi*2+1]
vcvttph2qq zmm1{k3}, word ptr [ebx+esi*2+254]{1to8}
vcvttph2udq xmm1, xmm2
vcvttph2udq xmm1{k3}{z}, xmm2
vcvttph2udq xmm1{k3}, qword ptr [ebx+esi*2+0]
vcvttph2udq xmm1{k3}{z}, qword ptr [ebx+esi*2+1016]
vcvttph2udq xmm1{k3}, qword ptr [ebx+esi*2+1024]
vcvttph2udq xmm1{k3}, qword ptr [ebx+esi*2+1]
vcvttph2udq xmm1{k3}, word ptr [ebx+esi*2+254]{1to4}
vcvttph2udq ymm1, xmm2
vcvttph2udq ymm1{k3}{z}, xmm2
vcvttph2udq ymm1{k3}, xmmword ptr [ebx+esi*2+0]
vcvttph2udq ymm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vcvttph2udq ymm1{k3}, xmmword ptr [ebx+esi*2+2048]
vcvttph2udq ymm1{k3}, xmmword ptr [ebx+esi*2+1]
vcvttph2udq ymm1{k3}, word ptr [ebx+esi*2+254]{1to8}
vcvttph2udq zmm1, ymm2
vcvttph2udq zmm1{k3}{z}, ymm2
vcvttph2udq zmm1{k3}, ymm2, {sae}
vcvttph2udq zmm1{k3}, ymmword ptr [ebx+esi*2+0]
vcvttph2udq zmm1{k3}{z}, ymmword ptr [ebx+esi*2+4064]
vcvttph2udq zmm1{k3}, ymmword ptr [ebx+esi*2+4096]
vcvttph2udq zmm1{k3}, ymmword ptr [ebx+esi*2+1]
vcvttph2udq zmm1{k3}, word ptr [ebx+esi*2+254]{1to16}
vcvttph2uqq xmm1, xmm2
vcvttph2uqq xmm1{k3}{z}, xmm2
vcvttph2uqq xmm1{k3}, dword ptr [ebx+esi*2+0]
vcvttph2uqq xmm1{k3}{z}, dword ptr [ebx+esi*2+508]
vcvttph2uqq xmm1{k3}, dword ptr [ebx+esi*2+512]
vcvttph2uqq xmm1{k3}, dword ptr [ebx+esi*2+1]
vcvttph2uqq xmm1{k3}, word ptr [ebx+esi*2+254]{1to2}
vcvttph2uqq ymm1, xmm2
vcvttph2uqq ymm1{k3}{z}, xmm2
vcvttph2uqq ymm1{k3}, qword ptr [ebx+esi*2+0]
vcvttph2uqq ymm1{k3}{z}, qword ptr [ebx+esi*2+1016]
vcvttph2uqq ymm1{k3}, qword ptr [ebx+esi*2+1024]
vcvttph2uqq ymm1{k3}, qword ptr [ebx+esi*2+1]
vcvttph2uqq ymm1{k3}, word ptr [ebx+esi*2+254]{1to4}
vcvttph2uqq zmm1, xmm2
vcvttph2uqq zmm1{k3}{z}, xmm2
vcvttph2uqq zmm1{k3}, xmm2, {sae}
vcvttph2uqq zmm1{k3}, xmmword ptr [ebx+esi*2+0]
vcvttph2uqq zmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vcvttph2uqq zmm1{k3}, xmmword ptr [ebx+esi*2+2048]
vcvttph2uqq zmm1{k3}, xmmword ptr [ebx+esi*2+1]
vcvttph2uqq zmm1{k3}, word ptr [ebx+esi*2+254]{1to8}
vcvttph2uw xmm1, xmm2
vcvttph2uw xmm1{k3}{z}, xmm2
vcvttph2uw xmm1{k3}, xmmword ptr [ebx+esi*2+0]
vcvttph2uw xmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vcvttph2uw xmm1{k3}, xmmword ptr [ebx+esi*2+2048]
vcvttph2uw xmm1{k3}, xmmword ptr [ebx+esi*2+1]
vcvttph2uw xmm1{k3}, word ptr [ebx+esi*2+254]{1to8}
vcvttph2uw ymm1, ymm2
vcvttph2uw ymm1{k3}{z}, ymm2
vcvttph2uw ymm1{k3}, ymmword ptr [ebx+esi*2+0]
vcvttph2uw ymm1{k3}{z}, ymmword ptr [ebx+esi*2+4064]
vcvttph2uw ymm1{k3}, ymmword ptr [ebx+esi*2+4096]
vcvttph2uw ymm1{k3}, ymmword ptr [ebx+esi*2+1]
vcvttph2uw ymm1{k3}, word ptr [ebx+esi*2+254]{1to16}
vcvttph2uw zmm1, zmm2
vcvttph2uw zmm1{k3}{z}, zmm2
vcvttph2uw zmm1{k3}, zmm2, {sae}
vcvttph2uw zmm1{k3}, zmmword ptr [ebx+esi*2+0]
vcvttph2uw zmm1{k3}{z}, zmmword ptr [ebx+esi*2+8128]
vcvttph2uw zmm1{k3}, zmmword ptr [ebx+esi*2+8192]
vcvttph2uw zmm1{k3}, zmmword ptr [ebx+esi*2+1]
vcvttph2uw zmm1{k3}, word ptr [ebx+esi*2+254]{1to32}
vcvttph2w xmm1, xmm2
vcvttph2w xmm1{k3}{z}, xmm2
vcvttph2w xmm1{k3}, xmmword ptr [ebx+esi*2+0]
vcvttph2w xmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vcvttph2w xmm1{k3}, xmmword ptr [ebx+esi*2+2048]
vcvttph2w xmm1{k3}, xmmword ptr [ebx+esi*2+1]
vcvttph2w xmm1{k3}, word ptr [ebx+esi*2+254]{1to8}
vcvttph2w ymm1, ymm2
vcvttph2w ymm1{k3}{z}, ymm2
vcvttph2w ymm1{k3}, ymmword ptr [ebx+esi*2+0]
vcvttph2w ymm1{k3}{z}, ymmword ptr [ebx+esi*2+4064]
vcvttph2w ymm1{k3}, ymmword ptr [ebx+esi*2+4096]
vcvttph2w ymm1{k3}, ymmword ptr [ebx+esi*2+1]
vcvttph2w ymm1{k3}, word ptr [ebx+esi*2+254]{1to16}
vcvttph2w zmm1, zmm2
vcvttph2w zmm1{k3}{z}, zmm2
vcvttph2w zmm1{k3}, zmm2, {sae}
vcvttph2w zmm1{k3}, zmmword ptr [ebx+esi*2+0]
vcvttph2w zmm1{k3}{z}, zmmword ptr [ebx+esi*2+8128]
vcvttph2w zmm1{k3}, zmmword ptr [ebx+esi*2+8192]
vcvttph2w zmm1{k3}, zmmword ptr [ebx+esi*2+1]
vcvttph2w zmm1{k3}, word ptr [ebx+esi*2+254]{1to32}
vcvttsh2si ecx, xmm2
vcvttsh2si ecx, xmm2
vcvttsh2si ecx, xmm2, {sae}
vcvttsh2si ecx, word ptr [ebx+esi*2+0]
vcvttsh2si ecx, word ptr [ebx+esi*2+254]
vcvttsh2si ecx, word ptr [ebx+esi*2+256]
vcvttsh2si ecx, word ptr [ebx+esi*2+1]
vcvttsh2usi ecx, xmm2
vcvttsh2usi ecx, xmm2
vcvttsh2usi ecx, xmm2, {sae}
vcvttsh2usi ecx, word ptr [ebx+esi*2+0]
vcvttsh2usi ecx, word ptr [ebx+esi*2+254]
vcvttsh2usi ecx, word ptr [ebx+esi*2+256]
vcvttsh2usi ecx, word ptr [ebx+esi*2+1]
vcvtudq2ph xmm1, xmm2
vcvtudq2ph xmm1{k3}{z}, xmm2
vcvtudq2ph xmm1{k3}, xmmword ptr [ebx+esi*2+0]
vcvtudq2ph xmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vcvtudq2ph xmm1{k3}, xmmword ptr [ebx+esi*2+2048]
vcvtudq2ph xmm1{k3}, xmmword ptr [ebx+esi*2+1]
vcvtudq2ph xmm1{k3}, dword ptr [ebx+esi*2+508]{1to4}
vcvtudq2ph xmm1, ymm2
vcvtudq2ph xmm1{k3}{z}, ymm2
vcvtudq2ph xmm1{k3}, ymmword ptr [ebx+esi*2+0]
vcvtudq2ph xmm1{k3}{z}, ymmword ptr [ebx+esi*2+4064]
vcvtudq2ph xmm1{k3}, ymmword ptr [ebx+esi*2+4096]
vcvtudq2ph xmm1{k3}, ymmword ptr [ebx+esi*2+1]
vcvtudq2ph xmm1{k3}, dword ptr [ebx+esi*2+508]{1to8}
vcvtudq2ph ymm1, zmm2
vcvtudq2ph ymm1{k3}{z}, zmm2
vcvtudq2ph ymm1{k3}, zmm2, {rn-sae}
vcvtudq2ph ymm1{k3}, zmm2, {rd-sae}
vcvtudq2ph ymm1{k3}, zmm2, {ru-sae}
vcvtudq2ph ymm1{k3}, zmm2, {rz-sae}
vcvtudq2ph ymm1{k3}, zmmword ptr [ebx+esi*2+0]
vcvtudq2ph ymm1{k3}{z}, zmmword ptr [ebx+esi*2+8128]
vcvtudq2ph ymm1{k3}, zmmword ptr [ebx+esi*2+8192]
vcvtudq2ph ymm1{k3}, zmmword ptr [ebx+esi*2+1]
vcvtudq2ph ymm1{k3}, dword ptr [ebx+esi*2+508]{1to16}
vcvtuqq2ph xmm1, xmm2
vcvtuqq2ph xmm1{k3}{z}, xmm2
vcvtuqq2ph xmm1{k3}, xmmword ptr [ebx+esi*2+0]
vcvtuqq2ph xmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vcvtuqq2ph xmm1{k3}, xmmword ptr [ebx+esi*2+2048]
vcvtuqq2ph xmm1{k3}, xmmword ptr [ebx+esi*2+1]
vcvtuqq2ph xmm1{k3}, qword ptr [ebx+esi*2+1016]{1to2}
vcvtuqq2ph xmm1, ymm2
vcvtuqq2ph xmm1{k3}{z}, ymm2
vcvtuqq2ph xmm1{k3}, ymmword ptr [ebx+esi*2+0]
vcvtuqq2ph xmm1{k3}{z}, ymmword ptr [ebx+esi*2+4064]
vcvtuqq2ph xmm1{k3}, ymmword ptr [ebx+esi*2+4096]
vcvtuqq2ph xmm1{k3}, ymmword ptr [ebx+esi*2+1]
vcvtuqq2ph xmm1{k3}, qword ptr [ebx+esi*2+1016]{1to4}
vcvtuqq2ph xmm1, zmm2
vcvtuqq2ph xmm1{k3}{z}, zmm2
vcvtuqq2ph xmm1{k3}, zmm2, {rn-sae}
vcvtuqq2ph xmm1{k3}, zmm2, {rd-sae}
vcvtuqq2ph xmm1{k3}, zmm2, {ru-sae}
vcvtuqq2ph xmm1{k3}, zmm2, {rz-sae}
vcvtuqq2ph xmm1{k3}, zmmword ptr [ebx+esi*2+0]
vcvtuqq2ph xmm1{k3}{z}, zmmword ptr [ebx+esi*2+8128]
vcvtuqq2ph xmm1{k3}, zmmword ptr [ebx+esi*2+8192]
vcvtuqq2ph xmm1{k3}, zmmword ptr [ebx+esi*2+1]
vcvtuqq2ph xmm1{k3}, qword ptr [ebx+esi*2+1016]{1to8}
vcvtusi2sh xmm1, xmm2, ecx
vcvtusi2sh xmm1, xmm2, ecx
vcvtusi2sh xmm1, xmm2, ecx, {rn-sae}
vcvtusi2sh xmm1, xmm2, ecx, {rd-sae}
vcvtusi2sh xmm1, xmm2, ecx, {ru-sae}
vcvtusi2sh xmm1, xmm2, ecx, {rz-sae}
vcvtusi2sh xmm1, xmm2, dword ptr [ebx+esi*2+0]
vcvtusi2sh xmm1, xmm2, dword ptr [ebx+esi*2+508]
vcvtusi2sh xmm1, xmm2, dword ptr [ebx+esi*2+512]
vcvtusi2sh xmm1, xmm2, dword ptr [ebx+esi*2+1]
vcvtuw2ph xmm1, xmm2
vcvtuw2ph xmm1{k3}{z}, xmm2
vcvtuw2ph xmm1{k3}, xmmword ptr [ebx+esi*2+0]
vcvtuw2ph xmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vcvtuw2ph xmm1{k3}, xmmword ptr [ebx+esi*2+2048]
vcvtuw2ph xmm1{k3}, xmmword ptr [ebx+esi*2+1]
vcvtuw2ph xmm1{k3}, word ptr [ebx+esi*2+254]{1to8}
vcvtuw2ph ymm1, ymm2
vcvtuw2ph ymm1{k3}{z}, ymm2
vcvtuw2ph ymm1{k3}, ymmword ptr [ebx+esi*2+0]
vcvtuw2ph ymm1{k3}{z}, ymmword ptr [ebx+esi*2+4064]
vcvtuw2ph ymm1{k3}, ymmword ptr [ebx+esi*2+4096]
vcvtuw2ph ymm1{k3}, ymmword ptr [ebx+esi*2+1]
vcvtuw2ph ymm1{k3}, word ptr [ebx+esi*2+254]{1to16}
vcvtuw2ph zmm1, zmm2
vcvtuw2ph zmm1{k3}{z}, zmm2
vcvtuw2ph zmm1{k3}, zmm2, {rn-sae}
vcvtuw2ph zmm1{k3}, zmm2, {rd-sae}
vcvtuw2ph zmm1{k3}, zmm2, {ru-sae}
vcvtuw2ph zmm1{k3}, zmm2, {rz-sae}
vcvtuw2ph zmm1{k3}, zmmword ptr [ebx+esi*2+0]
vcvtuw2ph zmm1{k3}{z}, zmmword ptr [ebx+esi*2+8128]
vcvtuw2ph zmm1{k3}, zmmword ptr [ebx+esi*2+8192]
vcvtuw2ph zmm1{k3}, zmmword ptr [ebx+esi*2+1]
vcvtuw2ph zmm1{k3}, word ptr [ebx+esi*2+254]{1to32}
vcvtw2ph xmm1, xmm2
vcvtw2ph xmm1{k3}{z}, xmm2
vcvtw2ph xmm1{k3}, xmmword ptr [ebx+esi*2+0]
vcvtw2ph xmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vcvtw2ph xmm1{k3}, xmmword ptr [ebx+esi*2+2048]
vcvtw2ph xmm1{k3}, xmmword ptr [ebx+esi*2+1]
vcvtw2ph xmm1{k3}, word ptr [ebx+esi*2+254]{1to8}
vcvtw2ph ymm1, ymm2
vcvtw2ph ymm1{k3}{z}, ymm2
vcvtw2ph ymm1{k3}, ymmword ptr [ebx+esi*2+0]
vcvtw2ph ymm1{k3}{z}, ymmword ptr [ebx+esi*2+4064]
vcvtw2ph ymm1{k3}, ymmword ptr [ebx+esi*2+4096]
vcvtw2ph ymm1{k3}, ymmword ptr [ebx+esi*2+1]
vcvtw2ph ymm1{k3}, word ptr [ebx+esi*2+254]{1to16}
vcvtw2ph zmm1, zmm2
vcvtw2ph zmm1{k3}{z}, zmm2
vcvtw2ph zmm1{k3}, zmm2, {rn-sae}
vcvtw2ph zmm1{k3}, zmm2, {rd-sae}
vcvtw2ph zmm1{k3}, zmm2, {ru-sae}
vcvtw2ph zmm1{k3}, zmm2, {rz-sae}
vcvtw2ph zmm1{k3}, zmmword ptr [ebx+esi*2+0]
vcvtw2ph zmm1{k3}{z}, zmmword ptr [ebx+esi*2+8128]
vcvtw2ph zmm1{k3}, zmmword ptr [ebx+esi*2+8192]
vcvtw2ph zmm1{k3}, zmmword ptr [ebx+esi*2+1]
vcvtw2ph zmm1{k3}, word ptr [ebx+esi*2+254]{1to32}
end
