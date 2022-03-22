;
; REP SCAS/CMPS in 64bit
;
    .x64
    .model flat
    .code
	
	rep scasb
	rep scasw
	rep scasd
	rep scasq

	repe scasb
	repe scasw
	repe scasd
	repe scasq

	repne scasb
	repne scasw
	repne scasd
	repne scasq	
	
	repz scasb
	repz scasw
	repz scasd
	repz scasq
	
	repnz scasb
	repnz scasw
	repnz scasd
	repnz scasq	
	
	rep scas byte ptr [rsi]
	rep scas word ptr [rdi]
	rep scas dword ptr [rax]
	rep scas qword ptr [rbx]

	rep cmpsb
	rep cmpsw
	rep cmpsd
	rep cmpsq

	repe cmpsb
	repe cmpsw
	repe cmpsd
	repe cmpsq

	repne cmpsb
	repne cmpsw
	repne cmpsd
	repne cmpsq	
	
	repz cmpsb
	repz cmpsw
	repz cmpsd
	repz cmpsq
	
	repnz cmpsb
	repnz cmpsw
	repnz cmpsd
	repnz cmpsq	
	
	rep cmps byte ptr [rax], byte ptr [rdi]
	rep cmps word ptr [rdi], byte ptr [rax]
	rep cmps dword ptr [rsi], byte ptr [rdi]
	rep cmps qword ptr [rcx], byte ptr [rdi]
    end
