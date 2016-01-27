
;--- if an EXTERN is referenced as altname in another EXTERN, two
;--- OMF EXTDEF records must be created for it.
;--- This was an issue in v2.09-2.10 ( although minor since accepted by OMF linkers )
;--- Also, there might have occured a loop inside the assembler
;--- if the altname was a global defined inside the module.
;--- Fixed in v2.11.

externdef c w1:near
extern c a1 (w1) :near	;case 1: altname is an undefined global

extern c w2:near
extern c a2 (w2) :near	;case 2: altname is an extern

externdef c w3:near
extern c a3 (w3) :near	;case 2: altname is a defined global

_TEXT segment public 'CODE'
	public w3
w3:
	ret
_TEXT ends

end
