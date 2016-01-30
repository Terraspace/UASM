
;--- test case EXITM expansion

.386
.model flat

TM1	textequ <!Zero?>
TM2	textequ <!a>

Exist0 textequ <!Zero?>

Exist1 MACRO 
	EXITM <!Zero?>
ENDM

Exist2 MACRO 
	EXITM TM1
ENDM

Exst0 textequ <!a>

Exst1 MACRO 
	EXITM <!a>
ENDM

Exst2 MACRO 
	EXITM TM2
ENDM

.code

	.if Exist0
		nop
	.endif
	.if Exist1()
		nop
	.endif
	.if Exist2()
		nop
	.endif

ifidn Exst0,<!a>
		nop
endif
ifidn Exst1(),<!a>
		nop
endif
ifidn Exst2(),<!a>
		nop
endif
	ret
end
