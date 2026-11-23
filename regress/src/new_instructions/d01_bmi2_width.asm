; D01: BMI2 W follows operand width, not the assembler build architecture.
; BEXTR is an adjacent-path control. Expected bytes independently checked with LLVM.
.x64
.model flat
.code
use32
bzhi eax, ecx, edx
bzhi edi, esi, ebx
bzhi eax, dword ptr [ebp], ecx
bzhi edx, dword ptr [ebx+esi*4+127], edi
bzhi edi, dword ptr [eax+ecx*2+128], esi
bzhi esi, dword ptr [ebx-128], ecx
bzhi ecx, dword ptr [ebx-129], edx
sarx eax, ecx, edx
sarx edi, esi, ebx
sarx eax, dword ptr [ebp], ecx
sarx edx, dword ptr [ebx+esi*4+127], edi
sarx edi, dword ptr [eax+ecx*2+128], esi
sarx esi, dword ptr [ebx-128], ecx
sarx ecx, dword ptr [ebx-129], edx
shlx eax, ecx, edx
shlx edi, esi, ebx
shlx eax, dword ptr [ebp], ecx
shlx edx, dword ptr [ebx+esi*4+127], edi
shlx edi, dword ptr [eax+ecx*2+128], esi
shlx esi, dword ptr [ebx-128], ecx
shlx ecx, dword ptr [ebx-129], edx
shrx eax, ecx, edx
shrx edi, esi, ebx
shrx eax, dword ptr [ebp], ecx
shrx edx, dword ptr [ebx+esi*4+127], edi
shrx edi, dword ptr [eax+ecx*2+128], esi
shrx esi, dword ptr [ebx-128], ecx
shrx ecx, dword ptr [ebx-129], edx
bextr eax, ecx, edx
bextr edi, esi, ebx
bextr eax, dword ptr [ebp], ecx
bextr edx, dword ptr [ebx+esi*4+127], edi
bextr edi, dword ptr [eax+ecx*2+128], esi
bextr esi, dword ptr [ebx-128], ecx
bextr ecx, dword ptr [ebx-129], edx
use64
bzhi eax, ecx, edx
bzhi edi, esi, ebx
bzhi eax, dword ptr [ebp], ecx
bzhi edx, dword ptr [ebx+esi*4+127], edi
bzhi edi, dword ptr [eax+ecx*2+128], esi
bzhi esi, dword ptr [ebx-128], ecx
bzhi ecx, dword ptr [ebx-129], edx
bzhi r9d, r10d, r11d
bzhi r15d, dword ptr [r13], r8d
bzhi r8d, dword ptr [r12+r14*8+128], r15d
bzhi rax, rcx, rdx
bzhi r9, r10, r11
bzhi r15, qword ptr [r13], r8
bzhi r8, qword ptr [r12+r14*8+127], r15
bzhi r11, qword ptr [rbp-129], r10
sarx eax, ecx, edx
sarx edi, esi, ebx
sarx eax, dword ptr [ebp], ecx
sarx edx, dword ptr [ebx+esi*4+127], edi
sarx edi, dword ptr [eax+ecx*2+128], esi
sarx esi, dword ptr [ebx-128], ecx
sarx ecx, dword ptr [ebx-129], edx
sarx r9d, r10d, r11d
sarx r15d, dword ptr [r13], r8d
sarx r8d, dword ptr [r12+r14*8+128], r15d
sarx rax, rcx, rdx
sarx r9, r10, r11
sarx r15, qword ptr [r13], r8
sarx r8, qword ptr [r12+r14*8+127], r15
sarx r11, qword ptr [rbp-129], r10
shlx eax, ecx, edx
shlx edi, esi, ebx
shlx eax, dword ptr [ebp], ecx
shlx edx, dword ptr [ebx+esi*4+127], edi
shlx edi, dword ptr [eax+ecx*2+128], esi
shlx esi, dword ptr [ebx-128], ecx
shlx ecx, dword ptr [ebx-129], edx
shlx r9d, r10d, r11d
shlx r15d, dword ptr [r13], r8d
shlx r8d, dword ptr [r12+r14*8+128], r15d
shlx rax, rcx, rdx
shlx r9, r10, r11
shlx r15, qword ptr [r13], r8
shlx r8, qword ptr [r12+r14*8+127], r15
shlx r11, qword ptr [rbp-129], r10
shrx eax, ecx, edx
shrx edi, esi, ebx
shrx eax, dword ptr [ebp], ecx
shrx edx, dword ptr [ebx+esi*4+127], edi
shrx edi, dword ptr [eax+ecx*2+128], esi
shrx esi, dword ptr [ebx-128], ecx
shrx ecx, dword ptr [ebx-129], edx
shrx r9d, r10d, r11d
shrx r15d, dword ptr [r13], r8d
shrx r8d, dword ptr [r12+r14*8+128], r15d
shrx rax, rcx, rdx
shrx r9, r10, r11
shrx r15, qword ptr [r13], r8
shrx r8, qword ptr [r12+r14*8+127], r15
shrx r11, qword ptr [rbp-129], r10
bextr eax, ecx, edx
bextr edi, esi, ebx
bextr eax, dword ptr [ebp], ecx
bextr edx, dword ptr [ebx+esi*4+127], edi
bextr edi, dword ptr [eax+ecx*2+128], esi
bextr esi, dword ptr [ebx-128], ecx
bextr ecx, dword ptr [ebx-129], edx
bextr r9d, r10d, r11d
bextr r15d, dword ptr [r13], r8d
bextr r8d, dword ptr [r12+r14*8+128], r15d
bextr rax, rcx, rdx
bextr r9, r10, r11
bextr r15, qword ptr [r13], r8
bextr r8, qword ptr [r12+r14*8+127], r15
bextr r11, qword ptr [rbp-129], r10
end
