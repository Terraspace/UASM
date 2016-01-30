
; ASMC v2.14 - JWASM 2.12 (signed) HIGHWORD -- QWORD


	.486
	.model flat
	.code

	mov	eax,HIGHWORD 80000000h

	end

Generated code:

	MOV	EAX,00008000h

EXPREVAL.C: highword_op()
{
    TokenAssign( opnd1, opnd2 );
    if ( opnd2->kind == EXPR_ADDR && opnd2->instr != T_SEG ) {
	opnd1->instr = T_HIGHWORD;
	opnd1->mem_type = MT_EMPTY;
    }
    opnd1->value = (opnd1->value >> 16) & 0xFFFF; /* ASMC v2.14 */
    return( NOT_ERROR );
}
