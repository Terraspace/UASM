; AVX-512 FP16: register/memory widths, masks, tuples and legal rounding/SAE.
.x64
.model flat
option evex:1
.code
vcvtdq2ph xmm1, xmm2
vcvtdq2ph xmm31{k3}{z}, xmm16
vcvtdq2ph xmm31{k3}, xmmword ptr [r13]
vcvtdq2ph xmm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vcvtdq2ph xmm31{k3}, xmmword ptr [r12+r14*2+2048]
vcvtdq2ph xmm31{k3}, xmmword ptr [r12+r14*2+1]
vcvtdq2ph xmm31{k3}, dword ptr [r12+r14*2+508]{1to4}
vcvtdq2ph xmm1, ymm2
vcvtdq2ph xmm31{k3}{z}, ymm16
vcvtdq2ph xmm31{k3}, ymmword ptr [r13]
vcvtdq2ph xmm31{k3}{z}, ymmword ptr [r12+r14*2+4064]
vcvtdq2ph xmm31{k3}, ymmword ptr [r12+r14*2+4096]
vcvtdq2ph xmm31{k3}, ymmword ptr [r12+r14*2+1]
vcvtdq2ph xmm31{k3}, dword ptr [r12+r14*2+508]{1to8}
vcvtdq2ph ymm1, zmm2
vcvtdq2ph ymm31{k3}{z}, zmm16
vcvtdq2ph ymm31{k3}, zmm16, {rn-sae}
vcvtdq2ph ymm31{k3}, zmm16, {rd-sae}
vcvtdq2ph ymm31{k3}, zmm16, {ru-sae}
vcvtdq2ph ymm31{k3}, zmm16, {rz-sae}
vcvtdq2ph ymm31{k3}, zmmword ptr [r13]
vcvtdq2ph ymm31{k3}{z}, zmmword ptr [r12+r14*2+8128]
vcvtdq2ph ymm31{k3}, zmmword ptr [r12+r14*2+8192]
vcvtdq2ph ymm31{k3}, zmmword ptr [r12+r14*2+1]
vcvtdq2ph ymm31{k3}, dword ptr [r12+r14*2+508]{1to16}
vcvtpd2ph xmm1, xmm2
vcvtpd2ph xmm31{k3}{z}, xmm16
vcvtpd2ph xmm31{k3}, xmmword ptr [r13]
vcvtpd2ph xmm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vcvtpd2ph xmm31{k3}, xmmword ptr [r12+r14*2+2048]
vcvtpd2ph xmm31{k3}, xmmword ptr [r12+r14*2+1]
vcvtpd2ph xmm31{k3}, qword ptr [r12+r14*2+1016]{1to2}
vcvtpd2ph xmm1, ymm2
vcvtpd2ph xmm31{k3}{z}, ymm16
vcvtpd2ph xmm31{k3}, ymmword ptr [r13]
vcvtpd2ph xmm31{k3}{z}, ymmword ptr [r12+r14*2+4064]
vcvtpd2ph xmm31{k3}, ymmword ptr [r12+r14*2+4096]
vcvtpd2ph xmm31{k3}, ymmword ptr [r12+r14*2+1]
vcvtpd2ph xmm31{k3}, qword ptr [r12+r14*2+1016]{1to4}
vcvtpd2ph xmm1, zmm2
vcvtpd2ph xmm31{k3}{z}, zmm16
vcvtpd2ph xmm31{k3}, zmm16, {rn-sae}
vcvtpd2ph xmm31{k3}, zmm16, {rd-sae}
vcvtpd2ph xmm31{k3}, zmm16, {ru-sae}
vcvtpd2ph xmm31{k3}, zmm16, {rz-sae}
vcvtpd2ph xmm31{k3}, zmmword ptr [r13]
vcvtpd2ph xmm31{k3}{z}, zmmword ptr [r12+r14*2+8128]
vcvtpd2ph xmm31{k3}, zmmword ptr [r12+r14*2+8192]
vcvtpd2ph xmm31{k3}, zmmword ptr [r12+r14*2+1]
vcvtpd2ph xmm31{k3}, qword ptr [r12+r14*2+1016]{1to8}
vcvtph2dq xmm1, xmm2
vcvtph2dq xmm31{k3}{z}, xmm16
vcvtph2dq xmm31{k3}, qword ptr [r13]
vcvtph2dq xmm31{k3}{z}, qword ptr [r12+r14*2+1016]
vcvtph2dq xmm31{k3}, qword ptr [r12+r14*2+1024]
vcvtph2dq xmm31{k3}, qword ptr [r12+r14*2+1]
vcvtph2dq xmm31{k3}, word ptr [r12+r14*2+254]{1to4}
vcvtph2dq ymm1, xmm2
vcvtph2dq ymm31{k3}{z}, xmm16
vcvtph2dq ymm31{k3}, xmmword ptr [r13]
vcvtph2dq ymm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vcvtph2dq ymm31{k3}, xmmword ptr [r12+r14*2+2048]
vcvtph2dq ymm31{k3}, xmmword ptr [r12+r14*2+1]
vcvtph2dq ymm31{k3}, word ptr [r12+r14*2+254]{1to8}
vcvtph2dq zmm1, ymm2
vcvtph2dq zmm31{k3}{z}, ymm16
vcvtph2dq zmm31{k3}, ymm16, {rn-sae}
vcvtph2dq zmm31{k3}, ymm16, {rd-sae}
vcvtph2dq zmm31{k3}, ymm16, {ru-sae}
vcvtph2dq zmm31{k3}, ymm16, {rz-sae}
vcvtph2dq zmm31{k3}, ymmword ptr [r13]
vcvtph2dq zmm31{k3}{z}, ymmword ptr [r12+r14*2+4064]
vcvtph2dq zmm31{k3}, ymmword ptr [r12+r14*2+4096]
vcvtph2dq zmm31{k3}, ymmword ptr [r12+r14*2+1]
vcvtph2dq zmm31{k3}, word ptr [r12+r14*2+254]{1to16}
vcvtph2pd xmm1, xmm2
vcvtph2pd xmm31{k3}{z}, xmm16
vcvtph2pd xmm31{k3}, dword ptr [r13]
vcvtph2pd xmm31{k3}{z}, dword ptr [r12+r14*2+508]
vcvtph2pd xmm31{k3}, dword ptr [r12+r14*2+512]
vcvtph2pd xmm31{k3}, dword ptr [r12+r14*2+1]
vcvtph2pd xmm31{k3}, word ptr [r12+r14*2+254]{1to2}
vcvtph2pd ymm1, xmm2
vcvtph2pd ymm31{k3}{z}, xmm16
vcvtph2pd ymm31{k3}, qword ptr [r13]
vcvtph2pd ymm31{k3}{z}, qword ptr [r12+r14*2+1016]
vcvtph2pd ymm31{k3}, qword ptr [r12+r14*2+1024]
vcvtph2pd ymm31{k3}, qword ptr [r12+r14*2+1]
vcvtph2pd ymm31{k3}, word ptr [r12+r14*2+254]{1to4}
vcvtph2pd zmm1, xmm2
vcvtph2pd zmm31{k3}{z}, xmm16
vcvtph2pd zmm31{k3}, xmm16, {sae}
vcvtph2pd zmm31{k3}, xmmword ptr [r13]
vcvtph2pd zmm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vcvtph2pd zmm31{k3}, xmmword ptr [r12+r14*2+2048]
vcvtph2pd zmm31{k3}, xmmword ptr [r12+r14*2+1]
vcvtph2pd zmm31{k3}, word ptr [r12+r14*2+254]{1to8}
vcvtph2psx xmm1, xmm2
vcvtph2psx xmm31{k3}{z}, xmm16
vcvtph2psx xmm31{k3}, qword ptr [r13]
vcvtph2psx xmm31{k3}{z}, qword ptr [r12+r14*2+1016]
vcvtph2psx xmm31{k3}, qword ptr [r12+r14*2+1024]
vcvtph2psx xmm31{k3}, qword ptr [r12+r14*2+1]
vcvtph2psx xmm31{k3}, word ptr [r12+r14*2+254]{1to4}
vcvtph2psx ymm1, xmm2
vcvtph2psx ymm31{k3}{z}, xmm16
vcvtph2psx ymm31{k3}, xmmword ptr [r13]
vcvtph2psx ymm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vcvtph2psx ymm31{k3}, xmmword ptr [r12+r14*2+2048]
vcvtph2psx ymm31{k3}, xmmword ptr [r12+r14*2+1]
vcvtph2psx ymm31{k3}, word ptr [r12+r14*2+254]{1to8}
vcvtph2psx zmm1, ymm2
vcvtph2psx zmm31{k3}{z}, ymm16
vcvtph2psx zmm31{k3}, ymm16, {sae}
vcvtph2psx zmm31{k3}, ymmword ptr [r13]
vcvtph2psx zmm31{k3}{z}, ymmword ptr [r12+r14*2+4064]
vcvtph2psx zmm31{k3}, ymmword ptr [r12+r14*2+4096]
vcvtph2psx zmm31{k3}, ymmword ptr [r12+r14*2+1]
vcvtph2psx zmm31{k3}, word ptr [r12+r14*2+254]{1to16}
vcvtph2qq xmm1, xmm2
vcvtph2qq xmm31{k3}{z}, xmm16
vcvtph2qq xmm31{k3}, dword ptr [r13]
vcvtph2qq xmm31{k3}{z}, dword ptr [r12+r14*2+508]
vcvtph2qq xmm31{k3}, dword ptr [r12+r14*2+512]
vcvtph2qq xmm31{k3}, dword ptr [r12+r14*2+1]
vcvtph2qq xmm31{k3}, word ptr [r12+r14*2+254]{1to2}
vcvtph2qq ymm1, xmm2
vcvtph2qq ymm31{k3}{z}, xmm16
vcvtph2qq ymm31{k3}, qword ptr [r13]
vcvtph2qq ymm31{k3}{z}, qword ptr [r12+r14*2+1016]
vcvtph2qq ymm31{k3}, qword ptr [r12+r14*2+1024]
vcvtph2qq ymm31{k3}, qword ptr [r12+r14*2+1]
vcvtph2qq ymm31{k3}, word ptr [r12+r14*2+254]{1to4}
vcvtph2qq zmm1, xmm2
vcvtph2qq zmm31{k3}{z}, xmm16
vcvtph2qq zmm31{k3}, xmm16, {rn-sae}
vcvtph2qq zmm31{k3}, xmm16, {rd-sae}
vcvtph2qq zmm31{k3}, xmm16, {ru-sae}
vcvtph2qq zmm31{k3}, xmm16, {rz-sae}
vcvtph2qq zmm31{k3}, xmmword ptr [r13]
vcvtph2qq zmm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vcvtph2qq zmm31{k3}, xmmword ptr [r12+r14*2+2048]
vcvtph2qq zmm31{k3}, xmmword ptr [r12+r14*2+1]
vcvtph2qq zmm31{k3}, word ptr [r12+r14*2+254]{1to8}
vcvtph2udq xmm1, xmm2
vcvtph2udq xmm31{k3}{z}, xmm16
vcvtph2udq xmm31{k3}, qword ptr [r13]
vcvtph2udq xmm31{k3}{z}, qword ptr [r12+r14*2+1016]
vcvtph2udq xmm31{k3}, qword ptr [r12+r14*2+1024]
vcvtph2udq xmm31{k3}, qword ptr [r12+r14*2+1]
vcvtph2udq xmm31{k3}, word ptr [r12+r14*2+254]{1to4}
vcvtph2udq ymm1, xmm2
vcvtph2udq ymm31{k3}{z}, xmm16
vcvtph2udq ymm31{k3}, xmmword ptr [r13]
vcvtph2udq ymm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vcvtph2udq ymm31{k3}, xmmword ptr [r12+r14*2+2048]
vcvtph2udq ymm31{k3}, xmmword ptr [r12+r14*2+1]
vcvtph2udq ymm31{k3}, word ptr [r12+r14*2+254]{1to8}
vcvtph2udq zmm1, ymm2
vcvtph2udq zmm31{k3}{z}, ymm16
vcvtph2udq zmm31{k3}, ymm16, {rn-sae}
vcvtph2udq zmm31{k3}, ymm16, {rd-sae}
vcvtph2udq zmm31{k3}, ymm16, {ru-sae}
vcvtph2udq zmm31{k3}, ymm16, {rz-sae}
vcvtph2udq zmm31{k3}, ymmword ptr [r13]
vcvtph2udq zmm31{k3}{z}, ymmword ptr [r12+r14*2+4064]
vcvtph2udq zmm31{k3}, ymmword ptr [r12+r14*2+4096]
vcvtph2udq zmm31{k3}, ymmword ptr [r12+r14*2+1]
vcvtph2udq zmm31{k3}, word ptr [r12+r14*2+254]{1to16}
vcvtph2uqq xmm1, xmm2
vcvtph2uqq xmm31{k3}{z}, xmm16
vcvtph2uqq xmm31{k3}, dword ptr [r13]
vcvtph2uqq xmm31{k3}{z}, dword ptr [r12+r14*2+508]
vcvtph2uqq xmm31{k3}, dword ptr [r12+r14*2+512]
vcvtph2uqq xmm31{k3}, dword ptr [r12+r14*2+1]
vcvtph2uqq xmm31{k3}, word ptr [r12+r14*2+254]{1to2}
vcvtph2uqq ymm1, xmm2
vcvtph2uqq ymm31{k3}{z}, xmm16
vcvtph2uqq ymm31{k3}, qword ptr [r13]
vcvtph2uqq ymm31{k3}{z}, qword ptr [r12+r14*2+1016]
vcvtph2uqq ymm31{k3}, qword ptr [r12+r14*2+1024]
vcvtph2uqq ymm31{k3}, qword ptr [r12+r14*2+1]
vcvtph2uqq ymm31{k3}, word ptr [r12+r14*2+254]{1to4}
vcvtph2uqq zmm1, xmm2
vcvtph2uqq zmm31{k3}{z}, xmm16
vcvtph2uqq zmm31{k3}, xmm16, {rn-sae}
vcvtph2uqq zmm31{k3}, xmm16, {rd-sae}
vcvtph2uqq zmm31{k3}, xmm16, {ru-sae}
vcvtph2uqq zmm31{k3}, xmm16, {rz-sae}
vcvtph2uqq zmm31{k3}, xmmword ptr [r13]
vcvtph2uqq zmm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vcvtph2uqq zmm31{k3}, xmmword ptr [r12+r14*2+2048]
vcvtph2uqq zmm31{k3}, xmmword ptr [r12+r14*2+1]
vcvtph2uqq zmm31{k3}, word ptr [r12+r14*2+254]{1to8}
vcvtph2uw xmm1, xmm2
vcvtph2uw xmm31{k3}{z}, xmm16
vcvtph2uw xmm31{k3}, xmmword ptr [r13]
vcvtph2uw xmm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vcvtph2uw xmm31{k3}, xmmword ptr [r12+r14*2+2048]
vcvtph2uw xmm31{k3}, xmmword ptr [r12+r14*2+1]
vcvtph2uw xmm31{k3}, word ptr [r12+r14*2+254]{1to8}
vcvtph2uw ymm1, ymm2
vcvtph2uw ymm31{k3}{z}, ymm16
vcvtph2uw ymm31{k3}, ymmword ptr [r13]
vcvtph2uw ymm31{k3}{z}, ymmword ptr [r12+r14*2+4064]
vcvtph2uw ymm31{k3}, ymmword ptr [r12+r14*2+4096]
vcvtph2uw ymm31{k3}, ymmword ptr [r12+r14*2+1]
vcvtph2uw ymm31{k3}, word ptr [r12+r14*2+254]{1to16}
vcvtph2uw zmm1, zmm2
vcvtph2uw zmm31{k3}{z}, zmm16
vcvtph2uw zmm31{k3}, zmm16, {rn-sae}
vcvtph2uw zmm31{k3}, zmm16, {rd-sae}
vcvtph2uw zmm31{k3}, zmm16, {ru-sae}
vcvtph2uw zmm31{k3}, zmm16, {rz-sae}
vcvtph2uw zmm31{k3}, zmmword ptr [r13]
vcvtph2uw zmm31{k3}{z}, zmmword ptr [r12+r14*2+8128]
vcvtph2uw zmm31{k3}, zmmword ptr [r12+r14*2+8192]
vcvtph2uw zmm31{k3}, zmmword ptr [r12+r14*2+1]
vcvtph2uw zmm31{k3}, word ptr [r12+r14*2+254]{1to32}
vcvtph2w xmm1, xmm2
vcvtph2w xmm31{k3}{z}, xmm16
vcvtph2w xmm31{k3}, xmmword ptr [r13]
vcvtph2w xmm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vcvtph2w xmm31{k3}, xmmword ptr [r12+r14*2+2048]
vcvtph2w xmm31{k3}, xmmword ptr [r12+r14*2+1]
vcvtph2w xmm31{k3}, word ptr [r12+r14*2+254]{1to8}
vcvtph2w ymm1, ymm2
vcvtph2w ymm31{k3}{z}, ymm16
vcvtph2w ymm31{k3}, ymmword ptr [r13]
vcvtph2w ymm31{k3}{z}, ymmword ptr [r12+r14*2+4064]
vcvtph2w ymm31{k3}, ymmword ptr [r12+r14*2+4096]
vcvtph2w ymm31{k3}, ymmword ptr [r12+r14*2+1]
vcvtph2w ymm31{k3}, word ptr [r12+r14*2+254]{1to16}
vcvtph2w zmm1, zmm2
vcvtph2w zmm31{k3}{z}, zmm16
vcvtph2w zmm31{k3}, zmm16, {rn-sae}
vcvtph2w zmm31{k3}, zmm16, {rd-sae}
vcvtph2w zmm31{k3}, zmm16, {ru-sae}
vcvtph2w zmm31{k3}, zmm16, {rz-sae}
vcvtph2w zmm31{k3}, zmmword ptr [r13]
vcvtph2w zmm31{k3}{z}, zmmword ptr [r12+r14*2+8128]
vcvtph2w zmm31{k3}, zmmword ptr [r12+r14*2+8192]
vcvtph2w zmm31{k3}, zmmword ptr [r12+r14*2+1]
vcvtph2w zmm31{k3}, word ptr [r12+r14*2+254]{1to32}
vcvtps2phx xmm1, xmm2
vcvtps2phx xmm31{k3}{z}, xmm16
vcvtps2phx xmm31{k3}, xmmword ptr [r13]
vcvtps2phx xmm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vcvtps2phx xmm31{k3}, xmmword ptr [r12+r14*2+2048]
vcvtps2phx xmm31{k3}, xmmword ptr [r12+r14*2+1]
vcvtps2phx xmm31{k3}, dword ptr [r12+r14*2+508]{1to4}
vcvtps2phx xmm1, ymm2
vcvtps2phx xmm31{k3}{z}, ymm16
vcvtps2phx xmm31{k3}, ymmword ptr [r13]
vcvtps2phx xmm31{k3}{z}, ymmword ptr [r12+r14*2+4064]
vcvtps2phx xmm31{k3}, ymmword ptr [r12+r14*2+4096]
vcvtps2phx xmm31{k3}, ymmword ptr [r12+r14*2+1]
vcvtps2phx xmm31{k3}, dword ptr [r12+r14*2+508]{1to8}
vcvtps2phx ymm1, zmm2
vcvtps2phx ymm31{k3}{z}, zmm16
vcvtps2phx ymm31{k3}, zmm16, {rn-sae}
vcvtps2phx ymm31{k3}, zmm16, {rd-sae}
vcvtps2phx ymm31{k3}, zmm16, {ru-sae}
vcvtps2phx ymm31{k3}, zmm16, {rz-sae}
vcvtps2phx ymm31{k3}, zmmword ptr [r13]
vcvtps2phx ymm31{k3}{z}, zmmword ptr [r12+r14*2+8128]
vcvtps2phx ymm31{k3}, zmmword ptr [r12+r14*2+8192]
vcvtps2phx ymm31{k3}, zmmword ptr [r12+r14*2+1]
vcvtps2phx ymm31{k3}, dword ptr [r12+r14*2+508]{1to16}
vcvtqq2ph xmm1, xmm2
vcvtqq2ph xmm31{k3}{z}, xmm16
vcvtqq2ph xmm31{k3}, xmmword ptr [r13]
vcvtqq2ph xmm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vcvtqq2ph xmm31{k3}, xmmword ptr [r12+r14*2+2048]
vcvtqq2ph xmm31{k3}, xmmword ptr [r12+r14*2+1]
vcvtqq2ph xmm31{k3}, qword ptr [r12+r14*2+1016]{1to2}
vcvtqq2ph xmm1, ymm2
vcvtqq2ph xmm31{k3}{z}, ymm16
vcvtqq2ph xmm31{k3}, ymmword ptr [r13]
vcvtqq2ph xmm31{k3}{z}, ymmword ptr [r12+r14*2+4064]
vcvtqq2ph xmm31{k3}, ymmword ptr [r12+r14*2+4096]
vcvtqq2ph xmm31{k3}, ymmword ptr [r12+r14*2+1]
vcvtqq2ph xmm31{k3}, qword ptr [r12+r14*2+1016]{1to4}
vcvtqq2ph xmm1, zmm2
vcvtqq2ph xmm31{k3}{z}, zmm16
vcvtqq2ph xmm31{k3}, zmm16, {rn-sae}
vcvtqq2ph xmm31{k3}, zmm16, {rd-sae}
vcvtqq2ph xmm31{k3}, zmm16, {ru-sae}
vcvtqq2ph xmm31{k3}, zmm16, {rz-sae}
vcvtqq2ph xmm31{k3}, zmmword ptr [r13]
vcvtqq2ph xmm31{k3}{z}, zmmword ptr [r12+r14*2+8128]
vcvtqq2ph xmm31{k3}, zmmword ptr [r12+r14*2+8192]
vcvtqq2ph xmm31{k3}, zmmword ptr [r12+r14*2+1]
vcvtqq2ph xmm31{k3}, qword ptr [r12+r14*2+1016]{1to8}
vcvtsd2sh xmm1, xmm2, xmm3
vcvtsd2sh xmm31{k3}{z}, xmm16, xmm30
vcvtsd2sh xmm31{k3}, xmm16, xmm30, {rn-sae}
vcvtsd2sh xmm31{k3}, xmm16, xmm30, {rd-sae}
vcvtsd2sh xmm31{k3}, xmm16, xmm30, {ru-sae}
vcvtsd2sh xmm31{k3}, xmm16, xmm30, {rz-sae}
vcvtsd2sh xmm31{k3}, xmm16, qword ptr [r13]
vcvtsd2sh xmm31{k3}{z}, xmm16, qword ptr [r12+r14*2+1016]
vcvtsd2sh xmm31{k3}, xmm16, qword ptr [r12+r14*2+1024]
vcvtsd2sh xmm31{k3}, xmm16, qword ptr [r12+r14*2+1]
vcvtsh2sd xmm1, xmm2, xmm3
vcvtsh2sd xmm31{k3}{z}, xmm16, xmm30
vcvtsh2sd xmm31{k3}, xmm16, xmm30, {sae}
vcvtsh2sd xmm31{k3}, xmm16, word ptr [r13]
vcvtsh2sd xmm31{k3}{z}, xmm16, word ptr [r12+r14*2+254]
vcvtsh2sd xmm31{k3}, xmm16, word ptr [r12+r14*2+256]
vcvtsh2sd xmm31{k3}, xmm16, word ptr [r12+r14*2+1]
vcvtsh2si ecx, xmm2
vcvtsh2si r9d, xmm16
vcvtsh2si r9d, xmm16, {rn-sae}
vcvtsh2si r9d, xmm16, {rd-sae}
vcvtsh2si r9d, xmm16, {ru-sae}
vcvtsh2si r9d, xmm16, {rz-sae}
vcvtsh2si r9d, word ptr [r13]
vcvtsh2si r9d, word ptr [r12+r14*2+254]
vcvtsh2si r9d, word ptr [r12+r14*2+256]
vcvtsh2si r9d, word ptr [r12+r14*2+1]
vcvtsh2si rcx, xmm2
vcvtsh2si r9, xmm16
vcvtsh2si r9, xmm16, {rn-sae}
vcvtsh2si r9, xmm16, {rd-sae}
vcvtsh2si r9, xmm16, {ru-sae}
vcvtsh2si r9, xmm16, {rz-sae}
vcvtsh2si r9, word ptr [r13]
vcvtsh2si r9, word ptr [r12+r14*2+254]
vcvtsh2si r9, word ptr [r12+r14*2+256]
vcvtsh2si r9, word ptr [r12+r14*2+1]
vcvtsh2ss xmm1, xmm2, xmm3
vcvtsh2ss xmm31{k3}{z}, xmm16, xmm30
vcvtsh2ss xmm31{k3}, xmm16, xmm30, {sae}
vcvtsh2ss xmm31{k3}, xmm16, word ptr [r13]
vcvtsh2ss xmm31{k3}{z}, xmm16, word ptr [r12+r14*2+254]
vcvtsh2ss xmm31{k3}, xmm16, word ptr [r12+r14*2+256]
vcvtsh2ss xmm31{k3}, xmm16, word ptr [r12+r14*2+1]
vcvtsh2usi ecx, xmm2
vcvtsh2usi r9d, xmm16
vcvtsh2usi r9d, xmm16, {rn-sae}
vcvtsh2usi r9d, xmm16, {rd-sae}
vcvtsh2usi r9d, xmm16, {ru-sae}
vcvtsh2usi r9d, xmm16, {rz-sae}
vcvtsh2usi r9d, word ptr [r13]
vcvtsh2usi r9d, word ptr [r12+r14*2+254]
vcvtsh2usi r9d, word ptr [r12+r14*2+256]
vcvtsh2usi r9d, word ptr [r12+r14*2+1]
vcvtsh2usi rcx, xmm2
vcvtsh2usi r9, xmm16
vcvtsh2usi r9, xmm16, {rn-sae}
vcvtsh2usi r9, xmm16, {rd-sae}
vcvtsh2usi r9, xmm16, {ru-sae}
vcvtsh2usi r9, xmm16, {rz-sae}
vcvtsh2usi r9, word ptr [r13]
vcvtsh2usi r9, word ptr [r12+r14*2+254]
vcvtsh2usi r9, word ptr [r12+r14*2+256]
vcvtsh2usi r9, word ptr [r12+r14*2+1]
vcvtsi2sh xmm1, xmm2, ecx
vcvtsi2sh xmm31, xmm16, r9d
vcvtsi2sh xmm31, xmm16, r9d, {rn-sae}
vcvtsi2sh xmm31, xmm16, r9d, {rd-sae}
vcvtsi2sh xmm31, xmm16, r9d, {ru-sae}
vcvtsi2sh xmm31, xmm16, r9d, {rz-sae}
vcvtsi2sh xmm31, xmm16, dword ptr [r13]
vcvtsi2sh xmm31, xmm16, dword ptr [r12+r14*2+508]
vcvtsi2sh xmm31, xmm16, dword ptr [r12+r14*2+512]
vcvtsi2sh xmm31, xmm16, dword ptr [r12+r14*2+1]
vcvtsi2sh xmm1, xmm2, rcx
vcvtsi2sh xmm31, xmm16, r9
vcvtsi2sh xmm31, xmm16, r9, {rn-sae}
vcvtsi2sh xmm31, xmm16, r9, {rd-sae}
vcvtsi2sh xmm31, xmm16, r9, {ru-sae}
vcvtsi2sh xmm31, xmm16, r9, {rz-sae}
vcvtsi2sh xmm31, xmm16, qword ptr [r13]
vcvtsi2sh xmm31, xmm16, qword ptr [r12+r14*2+1016]
vcvtsi2sh xmm31, xmm16, qword ptr [r12+r14*2+1024]
vcvtsi2sh xmm31, xmm16, qword ptr [r12+r14*2+1]
vcvtss2sh xmm1, xmm2, xmm3
vcvtss2sh xmm31{k3}{z}, xmm16, xmm30
vcvtss2sh xmm31{k3}, xmm16, xmm30, {rn-sae}
vcvtss2sh xmm31{k3}, xmm16, xmm30, {rd-sae}
vcvtss2sh xmm31{k3}, xmm16, xmm30, {ru-sae}
vcvtss2sh xmm31{k3}, xmm16, xmm30, {rz-sae}
vcvtss2sh xmm31{k3}, xmm16, dword ptr [r13]
vcvtss2sh xmm31{k3}{z}, xmm16, dword ptr [r12+r14*2+508]
vcvtss2sh xmm31{k3}, xmm16, dword ptr [r12+r14*2+512]
vcvtss2sh xmm31{k3}, xmm16, dword ptr [r12+r14*2+1]
vcvttph2dq xmm1, xmm2
vcvttph2dq xmm31{k3}{z}, xmm16
vcvttph2dq xmm31{k3}, qword ptr [r13]
vcvttph2dq xmm31{k3}{z}, qword ptr [r12+r14*2+1016]
vcvttph2dq xmm31{k3}, qword ptr [r12+r14*2+1024]
vcvttph2dq xmm31{k3}, qword ptr [r12+r14*2+1]
vcvttph2dq xmm31{k3}, word ptr [r12+r14*2+254]{1to4}
vcvttph2dq ymm1, xmm2
vcvttph2dq ymm31{k3}{z}, xmm16
vcvttph2dq ymm31{k3}, xmmword ptr [r13]
vcvttph2dq ymm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vcvttph2dq ymm31{k3}, xmmword ptr [r12+r14*2+2048]
vcvttph2dq ymm31{k3}, xmmword ptr [r12+r14*2+1]
vcvttph2dq ymm31{k3}, word ptr [r12+r14*2+254]{1to8}
vcvttph2dq zmm1, ymm2
vcvttph2dq zmm31{k3}{z}, ymm16
vcvttph2dq zmm31{k3}, ymm16, {sae}
vcvttph2dq zmm31{k3}, ymmword ptr [r13]
vcvttph2dq zmm31{k3}{z}, ymmword ptr [r12+r14*2+4064]
vcvttph2dq zmm31{k3}, ymmword ptr [r12+r14*2+4096]
vcvttph2dq zmm31{k3}, ymmword ptr [r12+r14*2+1]
vcvttph2dq zmm31{k3}, word ptr [r12+r14*2+254]{1to16}
vcvttph2qq xmm1, xmm2
vcvttph2qq xmm31{k3}{z}, xmm16
vcvttph2qq xmm31{k3}, dword ptr [r13]
vcvttph2qq xmm31{k3}{z}, dword ptr [r12+r14*2+508]
vcvttph2qq xmm31{k3}, dword ptr [r12+r14*2+512]
vcvttph2qq xmm31{k3}, dword ptr [r12+r14*2+1]
vcvttph2qq xmm31{k3}, word ptr [r12+r14*2+254]{1to2}
vcvttph2qq ymm1, xmm2
vcvttph2qq ymm31{k3}{z}, xmm16
vcvttph2qq ymm31{k3}, qword ptr [r13]
vcvttph2qq ymm31{k3}{z}, qword ptr [r12+r14*2+1016]
vcvttph2qq ymm31{k3}, qword ptr [r12+r14*2+1024]
vcvttph2qq ymm31{k3}, qword ptr [r12+r14*2+1]
vcvttph2qq ymm31{k3}, word ptr [r12+r14*2+254]{1to4}
vcvttph2qq zmm1, xmm2
vcvttph2qq zmm31{k3}{z}, xmm16
vcvttph2qq zmm31{k3}, xmm16, {sae}
vcvttph2qq zmm31{k3}, xmmword ptr [r13]
vcvttph2qq zmm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vcvttph2qq zmm31{k3}, xmmword ptr [r12+r14*2+2048]
vcvttph2qq zmm31{k3}, xmmword ptr [r12+r14*2+1]
vcvttph2qq zmm31{k3}, word ptr [r12+r14*2+254]{1to8}
vcvttph2udq xmm1, xmm2
vcvttph2udq xmm31{k3}{z}, xmm16
vcvttph2udq xmm31{k3}, qword ptr [r13]
vcvttph2udq xmm31{k3}{z}, qword ptr [r12+r14*2+1016]
vcvttph2udq xmm31{k3}, qword ptr [r12+r14*2+1024]
vcvttph2udq xmm31{k3}, qword ptr [r12+r14*2+1]
vcvttph2udq xmm31{k3}, word ptr [r12+r14*2+254]{1to4}
vcvttph2udq ymm1, xmm2
vcvttph2udq ymm31{k3}{z}, xmm16
vcvttph2udq ymm31{k3}, xmmword ptr [r13]
vcvttph2udq ymm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vcvttph2udq ymm31{k3}, xmmword ptr [r12+r14*2+2048]
vcvttph2udq ymm31{k3}, xmmword ptr [r12+r14*2+1]
vcvttph2udq ymm31{k3}, word ptr [r12+r14*2+254]{1to8}
vcvttph2udq zmm1, ymm2
vcvttph2udq zmm31{k3}{z}, ymm16
vcvttph2udq zmm31{k3}, ymm16, {sae}
vcvttph2udq zmm31{k3}, ymmword ptr [r13]
vcvttph2udq zmm31{k3}{z}, ymmword ptr [r12+r14*2+4064]
vcvttph2udq zmm31{k3}, ymmword ptr [r12+r14*2+4096]
vcvttph2udq zmm31{k3}, ymmword ptr [r12+r14*2+1]
vcvttph2udq zmm31{k3}, word ptr [r12+r14*2+254]{1to16}
vcvttph2uqq xmm1, xmm2
vcvttph2uqq xmm31{k3}{z}, xmm16
vcvttph2uqq xmm31{k3}, dword ptr [r13]
vcvttph2uqq xmm31{k3}{z}, dword ptr [r12+r14*2+508]
vcvttph2uqq xmm31{k3}, dword ptr [r12+r14*2+512]
vcvttph2uqq xmm31{k3}, dword ptr [r12+r14*2+1]
vcvttph2uqq xmm31{k3}, word ptr [r12+r14*2+254]{1to2}
vcvttph2uqq ymm1, xmm2
vcvttph2uqq ymm31{k3}{z}, xmm16
vcvttph2uqq ymm31{k3}, qword ptr [r13]
vcvttph2uqq ymm31{k3}{z}, qword ptr [r12+r14*2+1016]
vcvttph2uqq ymm31{k3}, qword ptr [r12+r14*2+1024]
vcvttph2uqq ymm31{k3}, qword ptr [r12+r14*2+1]
vcvttph2uqq ymm31{k3}, word ptr [r12+r14*2+254]{1to4}
vcvttph2uqq zmm1, xmm2
vcvttph2uqq zmm31{k3}{z}, xmm16
vcvttph2uqq zmm31{k3}, xmm16, {sae}
vcvttph2uqq zmm31{k3}, xmmword ptr [r13]
vcvttph2uqq zmm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vcvttph2uqq zmm31{k3}, xmmword ptr [r12+r14*2+2048]
vcvttph2uqq zmm31{k3}, xmmword ptr [r12+r14*2+1]
vcvttph2uqq zmm31{k3}, word ptr [r12+r14*2+254]{1to8}
vcvttph2uw xmm1, xmm2
vcvttph2uw xmm31{k3}{z}, xmm16
vcvttph2uw xmm31{k3}, xmmword ptr [r13]
vcvttph2uw xmm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vcvttph2uw xmm31{k3}, xmmword ptr [r12+r14*2+2048]
vcvttph2uw xmm31{k3}, xmmword ptr [r12+r14*2+1]
vcvttph2uw xmm31{k3}, word ptr [r12+r14*2+254]{1to8}
vcvttph2uw ymm1, ymm2
vcvttph2uw ymm31{k3}{z}, ymm16
vcvttph2uw ymm31{k3}, ymmword ptr [r13]
vcvttph2uw ymm31{k3}{z}, ymmword ptr [r12+r14*2+4064]
vcvttph2uw ymm31{k3}, ymmword ptr [r12+r14*2+4096]
vcvttph2uw ymm31{k3}, ymmword ptr [r12+r14*2+1]
vcvttph2uw ymm31{k3}, word ptr [r12+r14*2+254]{1to16}
vcvttph2uw zmm1, zmm2
vcvttph2uw zmm31{k3}{z}, zmm16
vcvttph2uw zmm31{k3}, zmm16, {sae}
vcvttph2uw zmm31{k3}, zmmword ptr [r13]
vcvttph2uw zmm31{k3}{z}, zmmword ptr [r12+r14*2+8128]
vcvttph2uw zmm31{k3}, zmmword ptr [r12+r14*2+8192]
vcvttph2uw zmm31{k3}, zmmword ptr [r12+r14*2+1]
vcvttph2uw zmm31{k3}, word ptr [r12+r14*2+254]{1to32}
vcvttph2w xmm1, xmm2
vcvttph2w xmm31{k3}{z}, xmm16
vcvttph2w xmm31{k3}, xmmword ptr [r13]
vcvttph2w xmm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vcvttph2w xmm31{k3}, xmmword ptr [r12+r14*2+2048]
vcvttph2w xmm31{k3}, xmmword ptr [r12+r14*2+1]
vcvttph2w xmm31{k3}, word ptr [r12+r14*2+254]{1to8}
vcvttph2w ymm1, ymm2
vcvttph2w ymm31{k3}{z}, ymm16
vcvttph2w ymm31{k3}, ymmword ptr [r13]
vcvttph2w ymm31{k3}{z}, ymmword ptr [r12+r14*2+4064]
vcvttph2w ymm31{k3}, ymmword ptr [r12+r14*2+4096]
vcvttph2w ymm31{k3}, ymmword ptr [r12+r14*2+1]
vcvttph2w ymm31{k3}, word ptr [r12+r14*2+254]{1to16}
vcvttph2w zmm1, zmm2
vcvttph2w zmm31{k3}{z}, zmm16
vcvttph2w zmm31{k3}, zmm16, {sae}
vcvttph2w zmm31{k3}, zmmword ptr [r13]
vcvttph2w zmm31{k3}{z}, zmmword ptr [r12+r14*2+8128]
vcvttph2w zmm31{k3}, zmmword ptr [r12+r14*2+8192]
vcvttph2w zmm31{k3}, zmmword ptr [r12+r14*2+1]
vcvttph2w zmm31{k3}, word ptr [r12+r14*2+254]{1to32}
vcvttsh2si ecx, xmm2
vcvttsh2si r9d, xmm16
vcvttsh2si r9d, xmm16, {sae}
vcvttsh2si r9d, word ptr [r13]
vcvttsh2si r9d, word ptr [r12+r14*2+254]
vcvttsh2si r9d, word ptr [r12+r14*2+256]
vcvttsh2si r9d, word ptr [r12+r14*2+1]
vcvttsh2si rcx, xmm2
vcvttsh2si r9, xmm16
vcvttsh2si r9, xmm16, {sae}
vcvttsh2si r9, word ptr [r13]
vcvttsh2si r9, word ptr [r12+r14*2+254]
vcvttsh2si r9, word ptr [r12+r14*2+256]
vcvttsh2si r9, word ptr [r12+r14*2+1]
vcvttsh2usi ecx, xmm2
vcvttsh2usi r9d, xmm16
vcvttsh2usi r9d, xmm16, {sae}
vcvttsh2usi r9d, word ptr [r13]
vcvttsh2usi r9d, word ptr [r12+r14*2+254]
vcvttsh2usi r9d, word ptr [r12+r14*2+256]
vcvttsh2usi r9d, word ptr [r12+r14*2+1]
vcvttsh2usi rcx, xmm2
vcvttsh2usi r9, xmm16
vcvttsh2usi r9, xmm16, {sae}
vcvttsh2usi r9, word ptr [r13]
vcvttsh2usi r9, word ptr [r12+r14*2+254]
vcvttsh2usi r9, word ptr [r12+r14*2+256]
vcvttsh2usi r9, word ptr [r12+r14*2+1]
vcvtudq2ph xmm1, xmm2
vcvtudq2ph xmm31{k3}{z}, xmm16
vcvtudq2ph xmm31{k3}, xmmword ptr [r13]
vcvtudq2ph xmm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vcvtudq2ph xmm31{k3}, xmmword ptr [r12+r14*2+2048]
vcvtudq2ph xmm31{k3}, xmmword ptr [r12+r14*2+1]
vcvtudq2ph xmm31{k3}, dword ptr [r12+r14*2+508]{1to4}
vcvtudq2ph xmm1, ymm2
vcvtudq2ph xmm31{k3}{z}, ymm16
vcvtudq2ph xmm31{k3}, ymmword ptr [r13]
vcvtudq2ph xmm31{k3}{z}, ymmword ptr [r12+r14*2+4064]
vcvtudq2ph xmm31{k3}, ymmword ptr [r12+r14*2+4096]
vcvtudq2ph xmm31{k3}, ymmword ptr [r12+r14*2+1]
vcvtudq2ph xmm31{k3}, dword ptr [r12+r14*2+508]{1to8}
vcvtudq2ph ymm1, zmm2
vcvtudq2ph ymm31{k3}{z}, zmm16
vcvtudq2ph ymm31{k3}, zmm16, {rn-sae}
vcvtudq2ph ymm31{k3}, zmm16, {rd-sae}
vcvtudq2ph ymm31{k3}, zmm16, {ru-sae}
vcvtudq2ph ymm31{k3}, zmm16, {rz-sae}
vcvtudq2ph ymm31{k3}, zmmword ptr [r13]
vcvtudq2ph ymm31{k3}{z}, zmmword ptr [r12+r14*2+8128]
vcvtudq2ph ymm31{k3}, zmmword ptr [r12+r14*2+8192]
vcvtudq2ph ymm31{k3}, zmmword ptr [r12+r14*2+1]
vcvtudq2ph ymm31{k3}, dword ptr [r12+r14*2+508]{1to16}
vcvtuqq2ph xmm1, xmm2
vcvtuqq2ph xmm31{k3}{z}, xmm16
vcvtuqq2ph xmm31{k3}, xmmword ptr [r13]
vcvtuqq2ph xmm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vcvtuqq2ph xmm31{k3}, xmmword ptr [r12+r14*2+2048]
vcvtuqq2ph xmm31{k3}, xmmword ptr [r12+r14*2+1]
vcvtuqq2ph xmm31{k3}, qword ptr [r12+r14*2+1016]{1to2}
vcvtuqq2ph xmm1, ymm2
vcvtuqq2ph xmm31{k3}{z}, ymm16
vcvtuqq2ph xmm31{k3}, ymmword ptr [r13]
vcvtuqq2ph xmm31{k3}{z}, ymmword ptr [r12+r14*2+4064]
vcvtuqq2ph xmm31{k3}, ymmword ptr [r12+r14*2+4096]
vcvtuqq2ph xmm31{k3}, ymmword ptr [r12+r14*2+1]
vcvtuqq2ph xmm31{k3}, qword ptr [r12+r14*2+1016]{1to4}
vcvtuqq2ph xmm1, zmm2
vcvtuqq2ph xmm31{k3}{z}, zmm16
vcvtuqq2ph xmm31{k3}, zmm16, {rn-sae}
vcvtuqq2ph xmm31{k3}, zmm16, {rd-sae}
vcvtuqq2ph xmm31{k3}, zmm16, {ru-sae}
vcvtuqq2ph xmm31{k3}, zmm16, {rz-sae}
vcvtuqq2ph xmm31{k3}, zmmword ptr [r13]
vcvtuqq2ph xmm31{k3}{z}, zmmword ptr [r12+r14*2+8128]
vcvtuqq2ph xmm31{k3}, zmmword ptr [r12+r14*2+8192]
vcvtuqq2ph xmm31{k3}, zmmword ptr [r12+r14*2+1]
vcvtuqq2ph xmm31{k3}, qword ptr [r12+r14*2+1016]{1to8}
vcvtusi2sh xmm1, xmm2, ecx
vcvtusi2sh xmm31, xmm16, r9d
vcvtusi2sh xmm31, xmm16, r9d, {rn-sae}
vcvtusi2sh xmm31, xmm16, r9d, {rd-sae}
vcvtusi2sh xmm31, xmm16, r9d, {ru-sae}
vcvtusi2sh xmm31, xmm16, r9d, {rz-sae}
vcvtusi2sh xmm31, xmm16, dword ptr [r13]
vcvtusi2sh xmm31, xmm16, dword ptr [r12+r14*2+508]
vcvtusi2sh xmm31, xmm16, dword ptr [r12+r14*2+512]
vcvtusi2sh xmm31, xmm16, dword ptr [r12+r14*2+1]
vcvtusi2sh xmm1, xmm2, rcx
vcvtusi2sh xmm31, xmm16, r9
vcvtusi2sh xmm31, xmm16, r9, {rn-sae}
vcvtusi2sh xmm31, xmm16, r9, {rd-sae}
vcvtusi2sh xmm31, xmm16, r9, {ru-sae}
vcvtusi2sh xmm31, xmm16, r9, {rz-sae}
vcvtusi2sh xmm31, xmm16, qword ptr [r13]
vcvtusi2sh xmm31, xmm16, qword ptr [r12+r14*2+1016]
vcvtusi2sh xmm31, xmm16, qword ptr [r12+r14*2+1024]
vcvtusi2sh xmm31, xmm16, qword ptr [r12+r14*2+1]
vcvtuw2ph xmm1, xmm2
vcvtuw2ph xmm31{k3}{z}, xmm16
vcvtuw2ph xmm31{k3}, xmmword ptr [r13]
vcvtuw2ph xmm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vcvtuw2ph xmm31{k3}, xmmword ptr [r12+r14*2+2048]
vcvtuw2ph xmm31{k3}, xmmword ptr [r12+r14*2+1]
vcvtuw2ph xmm31{k3}, word ptr [r12+r14*2+254]{1to8}
vcvtuw2ph ymm1, ymm2
vcvtuw2ph ymm31{k3}{z}, ymm16
vcvtuw2ph ymm31{k3}, ymmword ptr [r13]
vcvtuw2ph ymm31{k3}{z}, ymmword ptr [r12+r14*2+4064]
vcvtuw2ph ymm31{k3}, ymmword ptr [r12+r14*2+4096]
vcvtuw2ph ymm31{k3}, ymmword ptr [r12+r14*2+1]
vcvtuw2ph ymm31{k3}, word ptr [r12+r14*2+254]{1to16}
vcvtuw2ph zmm1, zmm2
vcvtuw2ph zmm31{k3}{z}, zmm16
vcvtuw2ph zmm31{k3}, zmm16, {rn-sae}
vcvtuw2ph zmm31{k3}, zmm16, {rd-sae}
vcvtuw2ph zmm31{k3}, zmm16, {ru-sae}
vcvtuw2ph zmm31{k3}, zmm16, {rz-sae}
vcvtuw2ph zmm31{k3}, zmmword ptr [r13]
vcvtuw2ph zmm31{k3}{z}, zmmword ptr [r12+r14*2+8128]
vcvtuw2ph zmm31{k3}, zmmword ptr [r12+r14*2+8192]
vcvtuw2ph zmm31{k3}, zmmword ptr [r12+r14*2+1]
vcvtuw2ph zmm31{k3}, word ptr [r12+r14*2+254]{1to32}
vcvtw2ph xmm1, xmm2
vcvtw2ph xmm31{k3}{z}, xmm16
vcvtw2ph xmm31{k3}, xmmword ptr [r13]
vcvtw2ph xmm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vcvtw2ph xmm31{k3}, xmmword ptr [r12+r14*2+2048]
vcvtw2ph xmm31{k3}, xmmword ptr [r12+r14*2+1]
vcvtw2ph xmm31{k3}, word ptr [r12+r14*2+254]{1to8}
vcvtw2ph ymm1, ymm2
vcvtw2ph ymm31{k3}{z}, ymm16
vcvtw2ph ymm31{k3}, ymmword ptr [r13]
vcvtw2ph ymm31{k3}{z}, ymmword ptr [r12+r14*2+4064]
vcvtw2ph ymm31{k3}, ymmword ptr [r12+r14*2+4096]
vcvtw2ph ymm31{k3}, ymmword ptr [r12+r14*2+1]
vcvtw2ph ymm31{k3}, word ptr [r12+r14*2+254]{1to16}
vcvtw2ph zmm1, zmm2
vcvtw2ph zmm31{k3}{z}, zmm16
vcvtw2ph zmm31{k3}, zmm16, {rn-sae}
vcvtw2ph zmm31{k3}, zmm16, {rd-sae}
vcvtw2ph zmm31{k3}, zmm16, {ru-sae}
vcvtw2ph zmm31{k3}, zmm16, {rz-sae}
vcvtw2ph zmm31{k3}, zmmword ptr [r13]
vcvtw2ph zmm31{k3}{z}, zmmword ptr [r12+r14*2+8128]
vcvtw2ph zmm31{k3}, zmmword ptr [r12+r14*2+8192]
vcvtw2ph zmm31{k3}, zmmword ptr [r12+r14*2+1]
vcvtw2ph zmm31{k3}, word ptr [r12+r14*2+254]{1to32}
end
