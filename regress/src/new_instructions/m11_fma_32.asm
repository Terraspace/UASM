; AVX-512 FP16: register/memory widths, masks, tuples and legal rounding/SAE.
.686p
.xmm
.model flat
option evex:1
.code
vfmadd132ph xmm1, xmm2, xmm3
vfmadd132ph xmm1{k3}{z}, xmm2, xmm3
vfmadd132ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vfmadd132ph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vfmadd132ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vfmadd132ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vfmadd132ph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vfmadd132ph ymm1, ymm2, ymm3
vfmadd132ph ymm1{k3}{z}, ymm2, ymm3
vfmadd132ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vfmadd132ph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vfmadd132ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vfmadd132ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vfmadd132ph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vfmadd132ph zmm1, zmm2, zmm3
vfmadd132ph zmm1{k3}{z}, zmm2, zmm3
vfmadd132ph zmm1{k3}, zmm2, zmm3, {rn-sae}
vfmadd132ph zmm1{k3}, zmm2, zmm3, {rd-sae}
vfmadd132ph zmm1{k3}, zmm2, zmm3, {ru-sae}
vfmadd132ph zmm1{k3}, zmm2, zmm3, {rz-sae}
vfmadd132ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vfmadd132ph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vfmadd132ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vfmadd132ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vfmadd132ph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vfmadd132sh xmm1, xmm2, xmm3
vfmadd132sh xmm1{k3}{z}, xmm2, xmm3
vfmadd132sh xmm1{k3}, xmm2, xmm3, {rn-sae}
vfmadd132sh xmm1{k3}, xmm2, xmm3, {rd-sae}
vfmadd132sh xmm1{k3}, xmm2, xmm3, {ru-sae}
vfmadd132sh xmm1{k3}, xmm2, xmm3, {rz-sae}
vfmadd132sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vfmadd132sh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vfmadd132sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vfmadd132sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vfmadd213ph xmm1, xmm2, xmm3
vfmadd213ph xmm1{k3}{z}, xmm2, xmm3
vfmadd213ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vfmadd213ph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vfmadd213ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vfmadd213ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vfmadd213ph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vfmadd213ph ymm1, ymm2, ymm3
vfmadd213ph ymm1{k3}{z}, ymm2, ymm3
vfmadd213ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vfmadd213ph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vfmadd213ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vfmadd213ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vfmadd213ph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vfmadd213ph zmm1, zmm2, zmm3
vfmadd213ph zmm1{k3}{z}, zmm2, zmm3
vfmadd213ph zmm1{k3}, zmm2, zmm3, {rn-sae}
vfmadd213ph zmm1{k3}, zmm2, zmm3, {rd-sae}
vfmadd213ph zmm1{k3}, zmm2, zmm3, {ru-sae}
vfmadd213ph zmm1{k3}, zmm2, zmm3, {rz-sae}
vfmadd213ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vfmadd213ph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vfmadd213ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vfmadd213ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vfmadd213ph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vfmadd213sh xmm1, xmm2, xmm3
vfmadd213sh xmm1{k3}{z}, xmm2, xmm3
vfmadd213sh xmm1{k3}, xmm2, xmm3, {rn-sae}
vfmadd213sh xmm1{k3}, xmm2, xmm3, {rd-sae}
vfmadd213sh xmm1{k3}, xmm2, xmm3, {ru-sae}
vfmadd213sh xmm1{k3}, xmm2, xmm3, {rz-sae}
vfmadd213sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vfmadd213sh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vfmadd213sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vfmadd213sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vfmadd231ph xmm1, xmm2, xmm3
vfmadd231ph xmm1{k3}{z}, xmm2, xmm3
vfmadd231ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vfmadd231ph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vfmadd231ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vfmadd231ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vfmadd231ph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vfmadd231ph ymm1, ymm2, ymm3
vfmadd231ph ymm1{k3}{z}, ymm2, ymm3
vfmadd231ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vfmadd231ph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vfmadd231ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vfmadd231ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vfmadd231ph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vfmadd231ph zmm1, zmm2, zmm3
vfmadd231ph zmm1{k3}{z}, zmm2, zmm3
vfmadd231ph zmm1{k3}, zmm2, zmm3, {rn-sae}
vfmadd231ph zmm1{k3}, zmm2, zmm3, {rd-sae}
vfmadd231ph zmm1{k3}, zmm2, zmm3, {ru-sae}
vfmadd231ph zmm1{k3}, zmm2, zmm3, {rz-sae}
vfmadd231ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vfmadd231ph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vfmadd231ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vfmadd231ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vfmadd231ph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vfmadd231sh xmm1, xmm2, xmm3
vfmadd231sh xmm1{k3}{z}, xmm2, xmm3
vfmadd231sh xmm1{k3}, xmm2, xmm3, {rn-sae}
vfmadd231sh xmm1{k3}, xmm2, xmm3, {rd-sae}
vfmadd231sh xmm1{k3}, xmm2, xmm3, {ru-sae}
vfmadd231sh xmm1{k3}, xmm2, xmm3, {rz-sae}
vfmadd231sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vfmadd231sh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vfmadd231sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vfmadd231sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vfmaddsub132ph xmm1, xmm2, xmm3
vfmaddsub132ph xmm1{k3}{z}, xmm2, xmm3
vfmaddsub132ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vfmaddsub132ph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vfmaddsub132ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vfmaddsub132ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vfmaddsub132ph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vfmaddsub132ph ymm1, ymm2, ymm3
vfmaddsub132ph ymm1{k3}{z}, ymm2, ymm3
vfmaddsub132ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vfmaddsub132ph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vfmaddsub132ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vfmaddsub132ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vfmaddsub132ph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vfmaddsub132ph zmm1, zmm2, zmm3
vfmaddsub132ph zmm1{k3}{z}, zmm2, zmm3
vfmaddsub132ph zmm1{k3}, zmm2, zmm3, {rn-sae}
vfmaddsub132ph zmm1{k3}, zmm2, zmm3, {rd-sae}
vfmaddsub132ph zmm1{k3}, zmm2, zmm3, {ru-sae}
vfmaddsub132ph zmm1{k3}, zmm2, zmm3, {rz-sae}
vfmaddsub132ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vfmaddsub132ph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vfmaddsub132ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vfmaddsub132ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vfmaddsub132ph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vfmaddsub213ph xmm1, xmm2, xmm3
vfmaddsub213ph xmm1{k3}{z}, xmm2, xmm3
vfmaddsub213ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vfmaddsub213ph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vfmaddsub213ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vfmaddsub213ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vfmaddsub213ph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vfmaddsub213ph ymm1, ymm2, ymm3
vfmaddsub213ph ymm1{k3}{z}, ymm2, ymm3
vfmaddsub213ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vfmaddsub213ph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vfmaddsub213ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vfmaddsub213ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vfmaddsub213ph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vfmaddsub213ph zmm1, zmm2, zmm3
vfmaddsub213ph zmm1{k3}{z}, zmm2, zmm3
vfmaddsub213ph zmm1{k3}, zmm2, zmm3, {rn-sae}
vfmaddsub213ph zmm1{k3}, zmm2, zmm3, {rd-sae}
vfmaddsub213ph zmm1{k3}, zmm2, zmm3, {ru-sae}
vfmaddsub213ph zmm1{k3}, zmm2, zmm3, {rz-sae}
vfmaddsub213ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vfmaddsub213ph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vfmaddsub213ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vfmaddsub213ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vfmaddsub213ph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vfmaddsub231ph xmm1, xmm2, xmm3
vfmaddsub231ph xmm1{k3}{z}, xmm2, xmm3
vfmaddsub231ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vfmaddsub231ph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vfmaddsub231ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vfmaddsub231ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vfmaddsub231ph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vfmaddsub231ph ymm1, ymm2, ymm3
vfmaddsub231ph ymm1{k3}{z}, ymm2, ymm3
vfmaddsub231ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vfmaddsub231ph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vfmaddsub231ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vfmaddsub231ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vfmaddsub231ph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vfmaddsub231ph zmm1, zmm2, zmm3
vfmaddsub231ph zmm1{k3}{z}, zmm2, zmm3
vfmaddsub231ph zmm1{k3}, zmm2, zmm3, {rn-sae}
vfmaddsub231ph zmm1{k3}, zmm2, zmm3, {rd-sae}
vfmaddsub231ph zmm1{k3}, zmm2, zmm3, {ru-sae}
vfmaddsub231ph zmm1{k3}, zmm2, zmm3, {rz-sae}
vfmaddsub231ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vfmaddsub231ph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vfmaddsub231ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vfmaddsub231ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vfmaddsub231ph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vfmsub132ph xmm1, xmm2, xmm3
vfmsub132ph xmm1{k3}{z}, xmm2, xmm3
vfmsub132ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vfmsub132ph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vfmsub132ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vfmsub132ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vfmsub132ph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vfmsub132ph ymm1, ymm2, ymm3
vfmsub132ph ymm1{k3}{z}, ymm2, ymm3
vfmsub132ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vfmsub132ph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vfmsub132ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vfmsub132ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vfmsub132ph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vfmsub132ph zmm1, zmm2, zmm3
vfmsub132ph zmm1{k3}{z}, zmm2, zmm3
vfmsub132ph zmm1{k3}, zmm2, zmm3, {rn-sae}
vfmsub132ph zmm1{k3}, zmm2, zmm3, {rd-sae}
vfmsub132ph zmm1{k3}, zmm2, zmm3, {ru-sae}
vfmsub132ph zmm1{k3}, zmm2, zmm3, {rz-sae}
vfmsub132ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vfmsub132ph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vfmsub132ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vfmsub132ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vfmsub132ph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vfmsub132sh xmm1, xmm2, xmm3
vfmsub132sh xmm1{k3}{z}, xmm2, xmm3
vfmsub132sh xmm1{k3}, xmm2, xmm3, {rn-sae}
vfmsub132sh xmm1{k3}, xmm2, xmm3, {rd-sae}
vfmsub132sh xmm1{k3}, xmm2, xmm3, {ru-sae}
vfmsub132sh xmm1{k3}, xmm2, xmm3, {rz-sae}
vfmsub132sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vfmsub132sh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vfmsub132sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vfmsub132sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vfmsub213ph xmm1, xmm2, xmm3
vfmsub213ph xmm1{k3}{z}, xmm2, xmm3
vfmsub213ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vfmsub213ph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vfmsub213ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vfmsub213ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vfmsub213ph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vfmsub213ph ymm1, ymm2, ymm3
vfmsub213ph ymm1{k3}{z}, ymm2, ymm3
vfmsub213ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vfmsub213ph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vfmsub213ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vfmsub213ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vfmsub213ph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vfmsub213ph zmm1, zmm2, zmm3
vfmsub213ph zmm1{k3}{z}, zmm2, zmm3
vfmsub213ph zmm1{k3}, zmm2, zmm3, {rn-sae}
vfmsub213ph zmm1{k3}, zmm2, zmm3, {rd-sae}
vfmsub213ph zmm1{k3}, zmm2, zmm3, {ru-sae}
vfmsub213ph zmm1{k3}, zmm2, zmm3, {rz-sae}
vfmsub213ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vfmsub213ph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vfmsub213ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vfmsub213ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vfmsub213ph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vfmsub213sh xmm1, xmm2, xmm3
vfmsub213sh xmm1{k3}{z}, xmm2, xmm3
vfmsub213sh xmm1{k3}, xmm2, xmm3, {rn-sae}
vfmsub213sh xmm1{k3}, xmm2, xmm3, {rd-sae}
vfmsub213sh xmm1{k3}, xmm2, xmm3, {ru-sae}
vfmsub213sh xmm1{k3}, xmm2, xmm3, {rz-sae}
vfmsub213sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vfmsub213sh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vfmsub213sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vfmsub213sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vfmsub231ph xmm1, xmm2, xmm3
vfmsub231ph xmm1{k3}{z}, xmm2, xmm3
vfmsub231ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vfmsub231ph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vfmsub231ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vfmsub231ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vfmsub231ph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vfmsub231ph ymm1, ymm2, ymm3
vfmsub231ph ymm1{k3}{z}, ymm2, ymm3
vfmsub231ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vfmsub231ph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vfmsub231ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vfmsub231ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vfmsub231ph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vfmsub231ph zmm1, zmm2, zmm3
vfmsub231ph zmm1{k3}{z}, zmm2, zmm3
vfmsub231ph zmm1{k3}, zmm2, zmm3, {rn-sae}
vfmsub231ph zmm1{k3}, zmm2, zmm3, {rd-sae}
vfmsub231ph zmm1{k3}, zmm2, zmm3, {ru-sae}
vfmsub231ph zmm1{k3}, zmm2, zmm3, {rz-sae}
vfmsub231ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vfmsub231ph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vfmsub231ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vfmsub231ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vfmsub231ph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vfmsub231sh xmm1, xmm2, xmm3
vfmsub231sh xmm1{k3}{z}, xmm2, xmm3
vfmsub231sh xmm1{k3}, xmm2, xmm3, {rn-sae}
vfmsub231sh xmm1{k3}, xmm2, xmm3, {rd-sae}
vfmsub231sh xmm1{k3}, xmm2, xmm3, {ru-sae}
vfmsub231sh xmm1{k3}, xmm2, xmm3, {rz-sae}
vfmsub231sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vfmsub231sh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vfmsub231sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vfmsub231sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vfmsubadd132ph xmm1, xmm2, xmm3
vfmsubadd132ph xmm1{k3}{z}, xmm2, xmm3
vfmsubadd132ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vfmsubadd132ph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vfmsubadd132ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vfmsubadd132ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vfmsubadd132ph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vfmsubadd132ph ymm1, ymm2, ymm3
vfmsubadd132ph ymm1{k3}{z}, ymm2, ymm3
vfmsubadd132ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vfmsubadd132ph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vfmsubadd132ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vfmsubadd132ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vfmsubadd132ph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vfmsubadd132ph zmm1, zmm2, zmm3
vfmsubadd132ph zmm1{k3}{z}, zmm2, zmm3
vfmsubadd132ph zmm1{k3}, zmm2, zmm3, {rn-sae}
vfmsubadd132ph zmm1{k3}, zmm2, zmm3, {rd-sae}
vfmsubadd132ph zmm1{k3}, zmm2, zmm3, {ru-sae}
vfmsubadd132ph zmm1{k3}, zmm2, zmm3, {rz-sae}
vfmsubadd132ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vfmsubadd132ph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vfmsubadd132ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vfmsubadd132ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vfmsubadd132ph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vfmsubadd213ph xmm1, xmm2, xmm3
vfmsubadd213ph xmm1{k3}{z}, xmm2, xmm3
vfmsubadd213ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vfmsubadd213ph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vfmsubadd213ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vfmsubadd213ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vfmsubadd213ph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vfmsubadd213ph ymm1, ymm2, ymm3
vfmsubadd213ph ymm1{k3}{z}, ymm2, ymm3
vfmsubadd213ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vfmsubadd213ph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vfmsubadd213ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vfmsubadd213ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vfmsubadd213ph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vfmsubadd213ph zmm1, zmm2, zmm3
vfmsubadd213ph zmm1{k3}{z}, zmm2, zmm3
vfmsubadd213ph zmm1{k3}, zmm2, zmm3, {rn-sae}
vfmsubadd213ph zmm1{k3}, zmm2, zmm3, {rd-sae}
vfmsubadd213ph zmm1{k3}, zmm2, zmm3, {ru-sae}
vfmsubadd213ph zmm1{k3}, zmm2, zmm3, {rz-sae}
vfmsubadd213ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vfmsubadd213ph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vfmsubadd213ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vfmsubadd213ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vfmsubadd213ph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vfmsubadd231ph xmm1, xmm2, xmm3
vfmsubadd231ph xmm1{k3}{z}, xmm2, xmm3
vfmsubadd231ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vfmsubadd231ph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vfmsubadd231ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vfmsubadd231ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vfmsubadd231ph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vfmsubadd231ph ymm1, ymm2, ymm3
vfmsubadd231ph ymm1{k3}{z}, ymm2, ymm3
vfmsubadd231ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vfmsubadd231ph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vfmsubadd231ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vfmsubadd231ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vfmsubadd231ph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vfmsubadd231ph zmm1, zmm2, zmm3
vfmsubadd231ph zmm1{k3}{z}, zmm2, zmm3
vfmsubadd231ph zmm1{k3}, zmm2, zmm3, {rn-sae}
vfmsubadd231ph zmm1{k3}, zmm2, zmm3, {rd-sae}
vfmsubadd231ph zmm1{k3}, zmm2, zmm3, {ru-sae}
vfmsubadd231ph zmm1{k3}, zmm2, zmm3, {rz-sae}
vfmsubadd231ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vfmsubadd231ph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vfmsubadd231ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vfmsubadd231ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vfmsubadd231ph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vfnmadd132ph xmm1, xmm2, xmm3
vfnmadd132ph xmm1{k3}{z}, xmm2, xmm3
vfnmadd132ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vfnmadd132ph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vfnmadd132ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vfnmadd132ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vfnmadd132ph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vfnmadd132ph ymm1, ymm2, ymm3
vfnmadd132ph ymm1{k3}{z}, ymm2, ymm3
vfnmadd132ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vfnmadd132ph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vfnmadd132ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vfnmadd132ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vfnmadd132ph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vfnmadd132ph zmm1, zmm2, zmm3
vfnmadd132ph zmm1{k3}{z}, zmm2, zmm3
vfnmadd132ph zmm1{k3}, zmm2, zmm3, {rn-sae}
vfnmadd132ph zmm1{k3}, zmm2, zmm3, {rd-sae}
vfnmadd132ph zmm1{k3}, zmm2, zmm3, {ru-sae}
vfnmadd132ph zmm1{k3}, zmm2, zmm3, {rz-sae}
vfnmadd132ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vfnmadd132ph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vfnmadd132ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vfnmadd132ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vfnmadd132ph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vfnmadd132sh xmm1, xmm2, xmm3
vfnmadd132sh xmm1{k3}{z}, xmm2, xmm3
vfnmadd132sh xmm1{k3}, xmm2, xmm3, {rn-sae}
vfnmadd132sh xmm1{k3}, xmm2, xmm3, {rd-sae}
vfnmadd132sh xmm1{k3}, xmm2, xmm3, {ru-sae}
vfnmadd132sh xmm1{k3}, xmm2, xmm3, {rz-sae}
vfnmadd132sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vfnmadd132sh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vfnmadd132sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vfnmadd132sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vfnmadd213ph xmm1, xmm2, xmm3
vfnmadd213ph xmm1{k3}{z}, xmm2, xmm3
vfnmadd213ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vfnmadd213ph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vfnmadd213ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vfnmadd213ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vfnmadd213ph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vfnmadd213ph ymm1, ymm2, ymm3
vfnmadd213ph ymm1{k3}{z}, ymm2, ymm3
vfnmadd213ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vfnmadd213ph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vfnmadd213ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vfnmadd213ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vfnmadd213ph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vfnmadd213ph zmm1, zmm2, zmm3
vfnmadd213ph zmm1{k3}{z}, zmm2, zmm3
vfnmadd213ph zmm1{k3}, zmm2, zmm3, {rn-sae}
vfnmadd213ph zmm1{k3}, zmm2, zmm3, {rd-sae}
vfnmadd213ph zmm1{k3}, zmm2, zmm3, {ru-sae}
vfnmadd213ph zmm1{k3}, zmm2, zmm3, {rz-sae}
vfnmadd213ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vfnmadd213ph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vfnmadd213ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vfnmadd213ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vfnmadd213ph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vfnmadd213sh xmm1, xmm2, xmm3
vfnmadd213sh xmm1{k3}{z}, xmm2, xmm3
vfnmadd213sh xmm1{k3}, xmm2, xmm3, {rn-sae}
vfnmadd213sh xmm1{k3}, xmm2, xmm3, {rd-sae}
vfnmadd213sh xmm1{k3}, xmm2, xmm3, {ru-sae}
vfnmadd213sh xmm1{k3}, xmm2, xmm3, {rz-sae}
vfnmadd213sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vfnmadd213sh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vfnmadd213sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vfnmadd213sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vfnmadd231ph xmm1, xmm2, xmm3
vfnmadd231ph xmm1{k3}{z}, xmm2, xmm3
vfnmadd231ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vfnmadd231ph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vfnmadd231ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vfnmadd231ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vfnmadd231ph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vfnmadd231ph ymm1, ymm2, ymm3
vfnmadd231ph ymm1{k3}{z}, ymm2, ymm3
vfnmadd231ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vfnmadd231ph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vfnmadd231ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vfnmadd231ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vfnmadd231ph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vfnmadd231ph zmm1, zmm2, zmm3
vfnmadd231ph zmm1{k3}{z}, zmm2, zmm3
vfnmadd231ph zmm1{k3}, zmm2, zmm3, {rn-sae}
vfnmadd231ph zmm1{k3}, zmm2, zmm3, {rd-sae}
vfnmadd231ph zmm1{k3}, zmm2, zmm3, {ru-sae}
vfnmadd231ph zmm1{k3}, zmm2, zmm3, {rz-sae}
vfnmadd231ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vfnmadd231ph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vfnmadd231ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vfnmadd231ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vfnmadd231ph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vfnmadd231sh xmm1, xmm2, xmm3
vfnmadd231sh xmm1{k3}{z}, xmm2, xmm3
vfnmadd231sh xmm1{k3}, xmm2, xmm3, {rn-sae}
vfnmadd231sh xmm1{k3}, xmm2, xmm3, {rd-sae}
vfnmadd231sh xmm1{k3}, xmm2, xmm3, {ru-sae}
vfnmadd231sh xmm1{k3}, xmm2, xmm3, {rz-sae}
vfnmadd231sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vfnmadd231sh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vfnmadd231sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vfnmadd231sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vfnmsub132ph xmm1, xmm2, xmm3
vfnmsub132ph xmm1{k3}{z}, xmm2, xmm3
vfnmsub132ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vfnmsub132ph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vfnmsub132ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vfnmsub132ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vfnmsub132ph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vfnmsub132ph ymm1, ymm2, ymm3
vfnmsub132ph ymm1{k3}{z}, ymm2, ymm3
vfnmsub132ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vfnmsub132ph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vfnmsub132ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vfnmsub132ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vfnmsub132ph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vfnmsub132ph zmm1, zmm2, zmm3
vfnmsub132ph zmm1{k3}{z}, zmm2, zmm3
vfnmsub132ph zmm1{k3}, zmm2, zmm3, {rn-sae}
vfnmsub132ph zmm1{k3}, zmm2, zmm3, {rd-sae}
vfnmsub132ph zmm1{k3}, zmm2, zmm3, {ru-sae}
vfnmsub132ph zmm1{k3}, zmm2, zmm3, {rz-sae}
vfnmsub132ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vfnmsub132ph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vfnmsub132ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vfnmsub132ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vfnmsub132ph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vfnmsub132sh xmm1, xmm2, xmm3
vfnmsub132sh xmm1{k3}{z}, xmm2, xmm3
vfnmsub132sh xmm1{k3}, xmm2, xmm3, {rn-sae}
vfnmsub132sh xmm1{k3}, xmm2, xmm3, {rd-sae}
vfnmsub132sh xmm1{k3}, xmm2, xmm3, {ru-sae}
vfnmsub132sh xmm1{k3}, xmm2, xmm3, {rz-sae}
vfnmsub132sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vfnmsub132sh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vfnmsub132sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vfnmsub132sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vfnmsub213ph xmm1, xmm2, xmm3
vfnmsub213ph xmm1{k3}{z}, xmm2, xmm3
vfnmsub213ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vfnmsub213ph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vfnmsub213ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vfnmsub213ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vfnmsub213ph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vfnmsub213ph ymm1, ymm2, ymm3
vfnmsub213ph ymm1{k3}{z}, ymm2, ymm3
vfnmsub213ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vfnmsub213ph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vfnmsub213ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vfnmsub213ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vfnmsub213ph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vfnmsub213ph zmm1, zmm2, zmm3
vfnmsub213ph zmm1{k3}{z}, zmm2, zmm3
vfnmsub213ph zmm1{k3}, zmm2, zmm3, {rn-sae}
vfnmsub213ph zmm1{k3}, zmm2, zmm3, {rd-sae}
vfnmsub213ph zmm1{k3}, zmm2, zmm3, {ru-sae}
vfnmsub213ph zmm1{k3}, zmm2, zmm3, {rz-sae}
vfnmsub213ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vfnmsub213ph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vfnmsub213ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vfnmsub213ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vfnmsub213ph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vfnmsub213sh xmm1, xmm2, xmm3
vfnmsub213sh xmm1{k3}{z}, xmm2, xmm3
vfnmsub213sh xmm1{k3}, xmm2, xmm3, {rn-sae}
vfnmsub213sh xmm1{k3}, xmm2, xmm3, {rd-sae}
vfnmsub213sh xmm1{k3}, xmm2, xmm3, {ru-sae}
vfnmsub213sh xmm1{k3}, xmm2, xmm3, {rz-sae}
vfnmsub213sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vfnmsub213sh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vfnmsub213sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vfnmsub213sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vfnmsub231ph xmm1, xmm2, xmm3
vfnmsub231ph xmm1{k3}{z}, xmm2, xmm3
vfnmsub231ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vfnmsub231ph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vfnmsub231ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vfnmsub231ph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vfnmsub231ph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vfnmsub231ph ymm1, ymm2, ymm3
vfnmsub231ph ymm1{k3}{z}, ymm2, ymm3
vfnmsub231ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vfnmsub231ph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vfnmsub231ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vfnmsub231ph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vfnmsub231ph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vfnmsub231ph zmm1, zmm2, zmm3
vfnmsub231ph zmm1{k3}{z}, zmm2, zmm3
vfnmsub231ph zmm1{k3}, zmm2, zmm3, {rn-sae}
vfnmsub231ph zmm1{k3}, zmm2, zmm3, {rd-sae}
vfnmsub231ph zmm1{k3}, zmm2, zmm3, {ru-sae}
vfnmsub231ph zmm1{k3}, zmm2, zmm3, {rz-sae}
vfnmsub231ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vfnmsub231ph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vfnmsub231ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vfnmsub231ph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vfnmsub231ph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vfnmsub231sh xmm1, xmm2, xmm3
vfnmsub231sh xmm1{k3}{z}, xmm2, xmm3
vfnmsub231sh xmm1{k3}, xmm2, xmm3, {rn-sae}
vfnmsub231sh xmm1{k3}, xmm2, xmm3, {rd-sae}
vfnmsub231sh xmm1{k3}, xmm2, xmm3, {ru-sae}
vfnmsub231sh xmm1{k3}, xmm2, xmm3, {rz-sae}
vfnmsub231sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vfnmsub231sh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vfnmsub231sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vfnmsub231sh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
end
