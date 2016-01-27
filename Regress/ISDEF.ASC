
;--- test IFDEF
;--- must be tested with JWASMR
;--- because FASTPASS must not be active

_TEXT segment WORD public 'CODE'

E1	equ 0
E2	label near
E3	proc private
E3	endp
E4	segment
E4	ends
E5	group E4
externdef E6:byte
extern E7:byte
comm E8:byte
E9 proto
E10	textequ <abc>
E11 macro
	endm

@isdef macro sym, num
	db num
;	echo sym is defined
	endm

ifdef E1
	@isdef E1,1
endif
ifdef E2
	@isdef E2,2
endif
ifdef E3
	@isdef E3,3
endif
ifdef E4
	@isdef E4,4
endif
ifdef E5
	@isdef E5,5
endif
ifdef E6
	@isdef E6,6
endif
ifdef E7
	@isdef E7,7
endif
ifdef E8
	@isdef E8,8
endif
ifdef E9
	@isdef E9,9
endif
ifdef E10
	@isdef E10,10
endif
ifdef E11
	@isdef E11,11
endif

ifdef G1
	@isdef G1,1+128
endif
ifdef G2
	@isdef G2,2+128
endif
ifdef G3
	@isdef G3,3+128
endif
ifdef G4
	@isdef G4,4+128
endif
ifdef G5
	@isdef G5,5+128
endif
ifdef G6
	@isdef G6,6+128
endif
ifdef G7
	@isdef G7,7+128
endif
ifdef G8
	@isdef G8,8+128
endif
ifdef G9
	@isdef G9,9+128
endif
ifdef G10
	@isdef G10,10+128
endif
ifdef G11
	@isdef G11,11+128
endif

G1	equ 0
G2	label near
G3	proc private
G3	endp
G4	segment
G4	ends
G5	group G4
externdef G6:byte
extern G7:byte
comm G8:byte
G9 proto
G10	textequ <abc>
G11 macro
	endm

_TEXT ends

	END
