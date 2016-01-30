
;--- ifdef test of groups, typedefs, records, structs
;--- it must also work if a full second pass is done,
;--- but this can't be forced currently in the release version

	.386

_TEXT segment dword public 'CODE'

ifdef S1
	inc eax
endif
ifdef T1
	inc ebx
endif
ifdef G1
	inc ecx
endif
ifdef R1
	inc edx
endif

G1 group _TEXT
T1 typedef ptr
R1 record rf1:1
S1 struct
f1  db ?
f2  dw ?
S1 ends

ifdef S1
	inc eax
endif
ifdef T1
	inc ebx
endif
ifdef G1
	inc ecx
endif
ifdef R1
	inc edx
endif

_TEXT ends

	end
