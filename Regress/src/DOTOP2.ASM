
;--- dot operator without OPTION OLDSTRUCTS

	.386
	.model flat

	.code

S1 struct
f1	dd ?
S1 ends

v1 S1 <>

	mov eax, [eax].S1.f1
	mov eax, [eax+ecx].S1.f1
	mov eax, [eax+ecx*2].S1.f1
	mov eax, [eax+v1].f1
	mov eax, [eax+offset v1].S1.f1  ;type info is lost
	mov eax, v1[eax].f1
	mov eax, [v1][eax].f1
	mov eax, [eax][v1].f1
	mov eax, [eax][ecx][v1].f1
	mov eax, [eax][v1.f1]
	mov eax, [eax+ecx][v1.f1]
	mov eax, [eax+ecx][v1.S1.f1]
	mov eax, [eax][ecx][v1.S1.f1]
	mov eax, [eax][v1.S1.f1][ecx*2]
	mov eax, [v1.S1.f1][eax][ecx*2]
	mov eax, [v1][eax][ecx].S1.f1
	mov eax, [offset v1][eax][ecx].S1.f1
	mov eax, [S1.f1][eax]
	mov eax, [S1.f1][eax][ecx]
	mov eax, [S1.f1][v1]  ;S1 is needed here
	mov eax, v1.f1[ebx]
	mov eax, v1.f1[ebx*2]

S2 struct
	dw ?
f1	dd ?
S2 ends

v2 S2 <>

	mov eax, [eax].S2.f1
	mov eax, [eax+ecx].S2.f1
	mov eax, [eax+ecx*2].S2.f1
	mov eax, [eax+v2].f1
	mov eax, [eax+offset v2].S2.f1  ;type info is lost
	mov eax, v2[eax].f1
	mov eax, [v2][eax].f1
	mov eax, [eax][v2].f1
	mov eax, [eax][ecx][v2].f1
	mov eax, [eax][v2.f1]
	mov eax, [eax+ecx][v2.f1]
	mov eax, [eax+ecx][v2.S2.f1]
	mov eax, [eax][ecx][v2.S2.f1]
	mov eax, [eax][v2.S2.f1][ecx*2]
	mov eax, [v2.S2.f1][eax][ecx*2]
	mov eax, [v2][eax][ecx].S2.f1
	mov eax, [offset v2][eax][ecx].S2.f1
	mov eax, [S2.f1][eax]
	mov eax, [S2.f1][eax][ecx]
	mov eax, [eax].S2.f1[ecx*4]
;	mov eax, [S2.f1][v2]  ;this is rejected by both Masm and JWasm
	mov eax, v2.f1[ebx]
	mov eax, v2.f1[ebx*2]

	END
