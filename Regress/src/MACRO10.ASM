
	.386
	.model flat, stdcall

m2 macro text
	db "&text",0
	endm

	.data

	db "abc \; def",0
	m2 <abc \!; def>
	m2 <abc ; def>
	m2 <'abc ; def'>
	m2 <""abc ; def"">
	m2 <'abc > def'>
	m2 <'abc < def'>
	m2 <abc !> def>
	m2 <abc !< def>
;	m2 <abc < def> 	;should fail

	end
