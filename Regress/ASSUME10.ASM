
;--- assumed type is not to override type of variable.
;--- regression in v2.08-2.09.

	.386
	.model flat

CV_LTYPE_STRUCT STRUC
CV_LTYPE_GTYPE      DD ?
CV_LTYPE_NAMEOFF    DB ?
CV_LTYPE_FLAGS      DB ?
                    DW ?
CV_LTYPE_NEST_LEVEL DD ?
CV_LTYPE_CIRC_CNT   DD ?
CV_LTYPE_CIRC1      DD ?
CV_LTYPE_STRUCT ENDS

STD_PTR_S STRUC
    DD ?
    DD ?
    DD ?
    DD ?
STD_PTRS DD 4 DUP(?)
STD_PTR_S ENDS

	.code

array STD_PTR_S <>

	assume esi:ptr CV_LTYPE_STRUCT
	xor esi, esi
	mov esi, array[esi*4].STD_PTRS

	END
