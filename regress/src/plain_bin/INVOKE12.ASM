
;--- 16bit invoke test with local arguments
;--- for 8086, 80186|80286 and 80386
;--- no error expected

	.MODEL small, stdcall

	.CODE

prb proc a1:byte, a2:byte
prb endp
prw proc a1:word, a2:word
prw endp
prd proc a1:dword, a2:dword
prd endp
prf proc a1:fword, a2:fword
prf endp
prq proc a1:qword, a2:qword
prq endp

	.8086

callproc proc pb:byte, pw:word, pd:dword, pf:fword, pq:qword

local lb:byte
local lw:word
local ld:dword
local lf:fword
local lq:qword

	invoke prb, pb, lb
	invoke prw, pw, lw
	invoke prd, pd, ld
	invoke prf, pf, lf
	invoke prq, pq, lq

	.186

	invoke prb, pb, lb
	invoke prw, pw, lw
	invoke prd, pd, ld
	invoke prf, pf, lf
	invoke prq, pq, lq
	.386

	invoke prb, pb, lb
	invoke prw, pw, lw
	invoke prd, pd, ld
	invoke prf, pf, lf
	invoke prq, pq, lq

callproc endp

	.386

_TEXT32 segment use32 'CODE'

prbx proc a1:byte, a2:byte
prbx endp
prwx proc a1:word, a2:word
prwx endp
prdx proc a1:dword, a2:dword
prdx endp
prfx proc a1:fword, a2:fword
prfx endp
prqx proc a1:qword, a2:qword
prqx endp

callproc32 proc pb:byte, pw:word, pd:dword, pf:fword, pq:qword

local lb:byte
local lw:word
local ld:dword
local lf:fword
local lq:qword

	invoke prbx, pb, lb
	invoke prwx, pw, lw
	invoke prdx, pd, ld
	invoke prfx, pf, lf
	invoke prqx, pq, lq

callproc32 endp

_TEXT32 ends

	END


