
;--- this didn't work prior to v2.08,
;--- if a '%' is first character, JWasm did expand everything
;--- within a quoted string, it didn't need a '&'.

	.386
	.model flat, stdcall

m1 macro text
	db text
	endm
m2 macro text
%   db text
	endm

	.data

TM1	equ <abc>

	db "TM1"
	db "&TM1"
	m1 "TM1"
	m1 "&TM1"
	m2 "TM1"
	m2 "&TM1"	;expands

%	db "TM1"
%	db "&TM1"	;expands
%	m1 "TM1"
%	m1 "&TM1"	;expands
%	m2 "TM1"
%	m2 "&TM1"	;expands

MF1	macro
	exitm <def>
	endm

	db "MF1()"
	db "&MF1()"
	m1 "MF1()"
	m1 "&MF1()"
	m2 "MF1()"
	m2 "&MF1()"	;expands

%	db "MF1()"
%	db "&MF1()"	;expands
%	m1 "MF1()"
%	m1 "&MF1()"	;expands
%	m2 "MF1()"
%	m2 "&MF1()"	;expands

	end
