
	.model small

	public E1	;symbol will be skipped (weak external)
	public E2
	public E3	;symbol will be skipped (weak external)
	public E4	;error: symbol is undefined
	public E5
	public E6	;error: cannot define as public nor external
	public E7	;error: symbol redefinition
	public E8	;error: cannot define as public nor external

externdef E1:near
externdef E3:near
E6 struct
E6 ends
extern E7:near
COMM E8:byte

	.code
E2:
E5:

end
