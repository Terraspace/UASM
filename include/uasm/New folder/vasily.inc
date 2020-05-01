; ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤

;   Original File - Vasily Sotnikov
;   vasil211@yandex.ru

; ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤

comment * Comparison run-time operators

     Operator      Meaning
 
     ==             Equal
     {}             Not equal
     }              Greater than
     }=             Greater than or equal to
     {              Less than
     {=             Less than or equal to
     &              Bit test (format: expression & bitnumber)
     ~              Logical NOT
     |              Bit test
     &&             Logical AND
     ||             Logical OR

     CARRY?         Carry bit set
     OVERFLOW?      Overflow bit set
     PARITY?        Parity bit set
     SIGN?          Sign bit set
     ZERO?          Zero bit set
     CARRY?|ZERO?    ìåíüíå èëè ðàâíî
     ~(CARRY?|ZERO?)    áîëüøå
     äëÿ ñðàâíåíèÿ ÷èñåë ñî çíàêîì
     ~ZERO?&(SIGN?==OVERFLOW?)    áîëüøå(greate than)
     SIGN?==OVERFLOW?        áîëüøå èëè ðàâíî(greate than or equal)
     SIGN?{}OVERFLOW?        ìåíüøå(less than)
     ZERO?|(SIGN?{}OVERFLOW?)        ìåíüøå èëè ðàâíî(less than or equal)
*
; ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤

    IMM_EXPR            equ 100b
    MEM_EXPR            equ 10b
    REG_EXPR            equ 10000b
    LABEL_EXPR          equ 1b
    VALID_REF           equ 100000b
    DIRECT_ADDR         equ 1000b
    VIMM_EXPR           equ (VALID_REF OR IMM_EXPR)
    TAB_CHAR            equ 9
    SPACE_CHAR          equ 20h
    CR_CHAR             equ 13
    LF_CHAR             equ 10
    COMMA_CHAR          equ 2Ch
    COLON_CHAR          equ 3Ah
    SEMICOLON_CHAR      equ 3Bh
    LEFT_PARENTHESES    equ 28h
    RIGHT_PARENTHESES   equ 29h
    EXCLAMATION_MARK    equ 21h
    LEFT_ANGLE          equ 3Ch
    RIGHT_ANGLE         equ 3Eh
    LEFT_SLASH          equ 5Ch    ;\
    RIGHT_SLASH         equ 2Fh    ;/
    NOT_A_REG64         equ 16
    NOT_A_REG32         equ 16
    NOT_A_REG16         equ 16
    NOT_A_REG8          equ 16
    NOT_A_REG           equ 16
    LOWER_MASK          equ 20202020h
    SHORT_LOW           equ 2020h
    LOW_CHAR            equ 20h
    LT_CHAR             equ 3Ch
    GT_CHAR             equ 3Eh

    TotalIfs = 0
    TotalRept = 0
    TotalWhile = 0
    UntilConds0 TEXTEQU <>
    UntilConds1 TEXTEQU <>
    UntilConds2 TEXTEQU <>
    UntilConds3 TEXTEQU <>
    UntilConds4 TEXTEQU <>
    UntilConds5 TEXTEQU <>
    UntilConds6 TEXTEQU <>
    UntilConds7 TEXTEQU <>
    UntilConds8 TEXTEQU <>
    UntilConds9 TEXTEQU <>
    UntilConds10 TEXTEQU <>
    UntilConds11 TEXTEQU <>
    UntilConds12 TEXTEQU <>
    UntilConds13 TEXTEQU <>
    UntilConds14 TEXTEQU <>
    UntilConds15 TEXTEQU <>
    UntilConds16 TEXTEQU <>
    UntilConds17 TEXTEQU <>
    UntilConds18 TEXTEQU <>
    UntilConds19 TEXTEQU <>
    LastUntilConds TEXTEQU <>

SaveUntilCondsLabel MACRO
    IFIDN UntilConds0,<>
      UntilConds0 CATSTR <locconds0_>,@CatStr(%TotalWhile)
      LastUntilConds TEXTEQU UntilConds0
    ELSEIFIDN UntilConds1,<> 
      UntilConds1 CATSTR <locconds1_>,@CatStr(%TotalWhile)
      LastUntilConds TEXTEQU UntilConds1
    ELSEIFIDN UntilConds2,<>
      UntilConds2 CATSTR <locconds2_>,@CatStr(%TotalWhile)
      LastUntilConds TEXTEQU UntilConds2
    ELSEIFIDN UntilConds3,<>
      UntilConds3 CATSTR <locconds3_>,@CatStr(%TotalWhile)
      LastUntilConds TEXTEQU UntilConds3
    ELSEIFIDN UntilConds4,<>
      UntilConds4 CATSTR <locconds4_>,@CatStr(%TotalWhile)
      LastUntilConds TEXTEQU UntilConds4
    ELSEIFIDN UntilConds5,<>
      UntilConds5 CATSTR <locconds5_>,@CatStr(%TotalWhile)
      LastUntilConds TEXTEQU UntilConds5
    ELSEIFIDN UntilConds6,<>
      UntilConds6 CATSTR <locconds6_>,@CatStr(%TotalWhile)
      LastUntilConds TEXTEQU UntilConds6
    ELSEIFIDN UntilConds7,<>
      UntilConds7 CATSTR <locconds7_>,@CatStr(%TotalWhile)
      LastUntilConds TEXTEQU UntilConds7
    ELSEIFIDN UntilConds8,<>
      UntilConds8 CATSTR <locconds8_>,@CatStr(%TotalWhile)
      LastUntilConds TEXTEQU UntilConds8
    ELSEIFIDN UntilConds9,<>
      UntilConds9 CATSTR <locconds9_>,@CatStr(%TotalWhile)
      LastUntilConds TEXTEQU UntilConds9
    ELSEIFIDN UntilConds10,<>
      UntilConds10 CATSTR <locconds10_>,@CatStr(%TotalWhile)
      LastUntilConds TEXTEQU UntilConds10
    ELSEIFIDN UntilConds11,<>
      UntilConds11 CATSTR <locconds11_>,@CatStr(%TotalWhile)
      LastUntilConds TEXTEQU UntilConds11
    ELSEIFIDN UntilConds12,<>
      UntilConds12 CATSTR <locconds12_>,@CatStr(%TotalWhile)
      LastUntilConds TEXTEQU UntilConds12
    ELSEIFIDN UntilConds13,<>
      UntilConds13 CATSTR <locconds13_>,@CatStr(%TotalWhile)
      LastUntilConds TEXTEQU UntilConds13
    ELSEIFIDN UntilConds14,<>
      UntilConds14 CATSTR <locconds14_>,@CatStr(%TotalWhile)
      LastUntilConds TEXTEQU UntilConds14
    ELSEIFIDN UntilConds15,<>
      UntilConds15 CATSTR <locconds15_>,@CatStr(%TotalWhile)
      LastUntilConds TEXTEQU UntilConds15
    ELSEIFIDN UntilConds16,<>
      UntilConds16 CATSTR <locconds16_>,@CatStr(%TotalWhile)
      LastUntilConds TEXTEQU UntilConds16
    ELSEIFIDN UntilConds17,<>
      UntilConds17 CATSTR <locconds17_>,@CatStr(%TotalWhile)
      LastUntilConds TEXTEQU UntilConds17
    ELSEIFIDN UntilConds18,<>
      UntilConds18 CATSTR <locconds18_>,@CatStr(%TotalWhile)
      LastUntilConds TEXTEQU UntilConds18
    ELSEIFIDN UntilConds19,<>
      UntilConds19 CATSTR <locconds19_>,@CatStr(%TotalWhile)
      LastUntilConds TEXTEQU UntilConds19
    ELSE
      .err <Nesting level too deep.>
    ENDIF
    TotalWhile = TotalWhile+1
ENDM

  GetUntilCondsLabel MACRO
    IFDIF UntilConds19,<>
      LastUntilConds TEXTEQU UntilConds19
    ELSEIFDIF UntilConds18,<>
      LastUntilConds TEXTEQU UntilConds18
    ELSEIFDIF UntilConds17,<>
      LastUntilConds TEXTEQU UntilConds17
    ELSEIFDIF UntilConds16,<>
      LastUntilConds TEXTEQU UntilConds16
    ELSEIFDIF UntilConds15,<>
      LastUntilConds TEXTEQU UntilConds15
    ELSEIFDIF UntilConds14,<>
      LastUntilConds TEXTEQU UntilConds14
    ELSEIFDIF UntilConds13,<>
      LastUntilConds TEXTEQU UntilConds13	
    ELSEIFDIF UntilConds12,<>
      LastUntilConds TEXTEQU UntilConds12
    ELSEIFDIF UntilConds11,<>
      LastUntilConds TEXTEQU UntilConds11	
    ELSEIFDIF UntilConds10,<>
      LastUntilConds TEXTEQU UntilConds10
    ELSEIFDIF UntilConds9,<>
      LastUntilConds TEXTEQU UntilConds9
    ELSEIFDIF UntilConds8,<>
      LastUntilConds TEXTEQU UntilConds8
    ELSEIFDIF UntilConds7,<>
      LastUntilConds TEXTEQU UntilConds7
    ELSEIFDIF UntilConds6,<>
      LastUntilConds TEXTEQU UntilConds6
    ELSEIFDIF UntilConds5,<>
      LastUntilConds TEXTEQU UntilConds5
    ELSEIFDIF UntilConds4,<>
      LastUntilConds TEXTEQU UntilConds4
    ELSEIFDIF UntilConds3,<>
      LastUntilConds TEXTEQU UntilConds3	
    ELSEIFDIF UntilConds2,<>
      LastUntilConds TEXTEQU UntilConds2
    ELSEIFDIF UntilConds1,<>
      LastUntilConds TEXTEQU UntilConds1	
    ELSEIFDIF UntilConds0,<>
      LastUntilConds TEXTEQU UntilConds0
    ELSE
      LastUntilConds TEXTEQU <>
    ENDIF		
  ENDM

    DelUntilCondsLabel MACRO
      IFDIF UntilConds19,<>
        UntilConds19 TEXTEQU <>
      ELSEIFDIF UntilConds18,<>
        UntilConds18 TEXTEQU <>
      ELSEIFDIF UntilConds17,<>
        UntilConds17 TEXTEQU <>
      ELSEIFDIF UntilConds16,<>
        UntilConds16 TEXTEQU <>
      ELSEIFDIF UntilConds15,<>
        UntilConds15 TEXTEQU <>
      ELSEIFDIF UntilConds14,<>
        UntilConds14 TEXTEQU <>
      ELSEIFDIF UntilConds13,<>
        UntilConds13 TEXTEQU <>	
      ELSEIFDIF UntilConds12,<>
        UntilConds12 TEXTEQU <>
      ELSEIFDIF UntilConds11,<>
        UntilConds11 TEXTEQU <>	
      ELSEIFDIF UntilConds10,<>
        UntilConds10 TEXTEQU <>
      ELSEIFDIF UntilConds9,<>
        UntilConds9 TEXTEQU <>
      ELSEIFDIF UntilConds8,<>
        UntilConds8 TEXTEQU <>
      ELSEIFDIF UntilConds7,<>
        UntilConds7 TEXTEQU <>
      ELSEIFDIF UntilConds6,<>
        UntilConds6 TEXTEQU <>
      ELSEIFDIF UntilConds5,<>
        UntilConds5 TEXTEQU <>
      ELSEIFDIF UntilConds4,<>
        UntilConds4 TEXTEQU <>
      ELSEIFDIF UntilConds3,<>
        UntilConds3 TEXTEQU <>	
      ELSEIFDIF UntilConds2,<>
        UntilConds2 TEXTEQU <>
      ELSEIFDIF UntilConds1,<>
        UntilConds1 TEXTEQU <>	
      ELSEIFDIF UntilConds0,<>
        UntilConds0 TEXTEQU <>
      ENDIF
    ENDM

    UntilLevel0 TEXTEQU <>
    UntilLevel1 TEXTEQU <>
    UntilLevel2 TEXTEQU <>
    UntilLevel3 TEXTEQU <>
    UntilLevel4 TEXTEQU <>
    UntilLevel5 TEXTEQU <>
    UntilLevel6 TEXTEQU <>
    UntilLevel7 TEXTEQU <>
    UntilLevel8 TEXTEQU <>
    UntilLevel9 TEXTEQU <>
    UntilLevel10 TEXTEQU <>
    UntilLevel11 TEXTEQU <>
    UntilLevel12 TEXTEQU <>
    UntilLevel13 TEXTEQU <>
    UntilLevel14 TEXTEQU <>
    UntilLevel15 TEXTEQU <>
    UntilLevel16 TEXTEQU <>
    UntilLevel17 TEXTEQU <>
    UntilLevel18 TEXTEQU <>
    UntilLevel19 TEXTEQU <>
    LastUntilLabel TEXTEQU <>

SaveUntilLabel MACRO
	IFIDN UntilLevel0,<>
		UntilLevel0 CATSTR <locuntil0_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel0
	ELSEIFIDN UntilLevel1,<> 
		UntilLevel1 CATSTR <locuntil1_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel1
	ELSEIFIDN UntilLevel2,<> 
		UntilLevel2 CATSTR <locuntil2_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel2
	ELSEIFIDN UntilLevel3,<> 
		UntilLevel3 CATSTR <locuntil3_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel3
	ELSEIFIDN UntilLevel4,<> 
		UntilLevel4 CATSTR <locuntil4_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel4
	ELSEIFIDN UntilLevel5,<> 
		UntilLevel5 CATSTR <locuntil5_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel5
	ELSEIFIDN UntilLevel6,<> 
		UntilLevel6 CATSTR <locuntil6_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel6
	ELSEIFIDN UntilLevel7,<> 
		UntilLevel7 CATSTR <locuntil7_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel7
	ELSEIFIDN UntilLevel8,<> 
		UntilLevel8 CATSTR <locuntil8_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel8
	ELSEIFIDN UntilLevel9,<> 
		UntilLevel9 CATSTR <locuntil9_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel9
	ELSEIFIDN UntilLevel10,<>
		UntilLevel10 CATSTR <locuntil10_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel10
	ELSEIFIDN UntilLevel11,<> 
		UntilLevel11 CATSTR <locuntil11_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel11
	ELSEIFIDN UntilLevel12,<> 
		UntilLevel12 CATSTR <locuntil12_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel12
	ELSEIFIDN UntilLevel13,<> 
		UntilLevel13 CATSTR <locuntil13_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel13
	ELSEIFIDN UntilLevel14,<> 
		UntilLevel14 CATSTR <locuntil14_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel14
	ELSEIFIDN UntilLevel15,<> 
		UntilLevel15 CATSTR <locuntil15_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel15
	ELSEIFIDN UntilLevel16,<> 
		UntilLevel16 CATSTR <locuntil16_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel16
	ELSEIFIDN UntilLevel17,<> 
		UntilLevel17 CATSTR <locuntil17_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel17
	ELSEIFIDN UntilLevel18,<> 
		UntilLevel18 CATSTR <locuntil18_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel18
	ELSEIFIDN UntilLevel19,<> 
		UntilLevel19 CATSTR <locuntil19_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel19
	ELSE
		.err <Nesting level too deep.>
	ENDIF
	TotalRept = TotalRept+1
ENDM

GetUntilLabel MACRO
	IFDIF UntilLevel19,<>
		LastUntilLabel TEXTEQU UntilLevel19
	ELSEIFDIF UntilLevel18,<>
		LastUntilLabel TEXTEQU UntilLevel18
	ELSEIFDIF UntilLevel17,<>
		LastUntilLabel TEXTEQU UntilLevel17
	ELSEIFDIF UntilLevel16,<>
		LastUntilLabel TEXTEQU UntilLevel16
	ELSEIFDIF UntilLevel15,<>
		LastUntilLabel TEXTEQU UntilLevel15
	ELSEIFDIF UntilLevel14,<>
		LastUntilLabel TEXTEQU UntilLevel14
	ELSEIFDIF UntilLevel13,<>
		LastUntilLabel TEXTEQU UntilLevel13	
	ELSEIFDIF UntilLevel12,<>
		LastUntilLabel TEXTEQU UntilLevel12
	ELSEIFDIF UntilLevel11,<>
		LastUntilLabel TEXTEQU UntilLevel11	
	ELSEIFDIF UntilLevel10,<>
		LastUntilLabel TEXTEQU UntilLevel10
	ELSEIFDIF UntilLevel9,<>
		LastUntilLabel TEXTEQU UntilLevel9
	ELSEIFDIF UntilLevel8,<>
		LastUntilLabel TEXTEQU UntilLevel8
	ELSEIFDIF UntilLevel7,<>
		LastUntilLabel TEXTEQU UntilLevel7
	ELSEIFDIF UntilLevel6,<>
		LastUntilLabel TEXTEQU UntilLevel6
	ELSEIFDIF UntilLevel5,<>
		LastUntilLabel TEXTEQU UntilLevel5
	ELSEIFDIF UntilLevel4,<>
		LastUntilLabel TEXTEQU UntilLevel4
	ELSEIFDIF UntilLevel3,<>
		LastUntilLabel TEXTEQU UntilLevel3	
	ELSEIFDIF UntilLevel2,<>
		LastUntilLabel TEXTEQU UntilLevel2
	ELSEIFDIF UntilLevel1,<>
		LastUntilLabel TEXTEQU UntilLevel1	
	ELSEIFDIF UntilLevel0,<>
		LastUntilLabel TEXTEQU UntilLevel0
	ELSE
		LastUntilLabel TEXTEQU <>
	ENDIF		
ENDM

DelUntilLabel MACRO
	IFDIF UntilLevel19,<>
		UntilLevel19 TEXTEQU <>
	ELSEIFDIF UntilLevel18,<>
		UntilLevel18 TEXTEQU <>
	ELSEIFDIF UntilLevel17,<>
		UntilLevel17 TEXTEQU <>
	ELSEIFDIF UntilLevel16,<>
		UntilLevel16 TEXTEQU <>
	ELSEIFDIF UntilLevel15,<>
		UntilLevel15 TEXTEQU <>
	ELSEIFDIF UntilLevel14,<>
		UntilLevel14 TEXTEQU <>
	ELSEIFDIF UntilLevel13,<>
		UntilLevel13 TEXTEQU <>	
	ELSEIFDIF UntilLevel12,<>
		UntilLevel12 TEXTEQU <>
	ELSEIFDIF UntilLevel11,<>
		UntilLevel11 TEXTEQU <>	
	ELSEIFDIF UntilLevel10,<>
		UntilLevel10 TEXTEQU <>
	ELSEIFDIF UntilLevel9,<>
		UntilLevel9 TEXTEQU <>
	ELSEIFDIF UntilLevel8,<>
		UntilLevel8 TEXTEQU <>
	ELSEIFDIF UntilLevel7,<>
		UntilLevel7 TEXTEQU <>
	ELSEIFDIF UntilLevel6,<>
		UntilLevel6 TEXTEQU <>
	ELSEIFDIF UntilLevel5,<>
		UntilLevel5 TEXTEQU <>
	ELSEIFDIF UntilLevel4,<>
		UntilLevel4 TEXTEQU <>
	ELSEIFDIF UntilLevel3,<>
		UntilLevel3 TEXTEQU <>	
	ELSEIFDIF UntilLevel2,<>
		UntilLevel2 TEXTEQU <>
	ELSEIFDIF UntilLevel1,<>
		UntilLevel1 TEXTEQU <>	
	ELSEIFDIF UntilLevel0,<>
		UntilLevel0 TEXTEQU <>
	ENDIF
ENDM

    TotalRept = 0
    UntilOut0 TEXTEQU <>
    UntilOut1 TEXTEQU <>
    UntilOut2 TEXTEQU <>
    UntilOut3 TEXTEQU <>
    UntilOut4 TEXTEQU <>
    UntilOut5 TEXTEQU <>
    UntilOut6 TEXTEQU <>
    UntilOut7 TEXTEQU <>
    UntilOut8 TEXTEQU <>
    UntilOut9 TEXTEQU <>
    UntilOut10 TEXTEQU <>
    UntilOut11 TEXTEQU <>
    UntilOut12 TEXTEQU <>
    UntilOut13 TEXTEQU <>
    UntilOut14 TEXTEQU <>
    UntilOut15 TEXTEQU <>
    UntilOut16 TEXTEQU <>
    UntilOut17 TEXTEQU <>
    UntilOut18 TEXTEQU <>
    UntilOut19 TEXTEQU <>
    LastUntilOutLabel TEXTEQU <>

SaveUntilOutLabel MACRO
	IFIDN UntilOut0,<>
		UntilOut0 CATSTR <locuntilout0_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut0
	ELSEIFIDN UntilOut1,<> 
		UntilOut1 CATSTR <locuntilout1_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut1
	ELSEIFIDN UntilOut2,<> 
		UntilOut2 CATSTR <locuntilout2_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut2
	ELSEIFIDN UntilOut3,<> 
		UntilOut3 CATSTR <locuntilout3_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut3
	ELSEIFIDN UntilOut4,<> 
		UntilOut4 CATSTR <locuntilout4_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut4
	ELSEIFIDN UntilOut5,<> 
		UntilOut5 CATSTR <locuntilout5_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut5
	ELSEIFIDN UntilOut6,<> 
		UntilOut6 CATSTR <locuntilout6_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut6
	ELSEIFIDN UntilOut7,<> 
		UntilOut7 CATSTR <locuntilout7_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut7
	ELSEIFIDN UntilOut8,<> 
		UntilOut8 CATSTR <locuntilout8_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut8
	ELSEIFIDN UntilOut9,<> 
		UntilOut9 CATSTR <locuntilout9_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut9
	ELSEIFIDN UntilOut10,<>
		UntilOut10 CATSTR <locuntilout10_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut10
	ELSEIFIDN UntilOut11,<> 
		UntilOut11 CATSTR <locuntilout11_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut11
	ELSEIFIDN UntilOut12,<> 
		UntilOut12 CATSTR <locuntilout12_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut12
	ELSEIFIDN UntilOut13,<> 
		UntilOut13 CATSTR <locuntilout13_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut13
	ELSEIFIDN UntilOut14,<> 
		UntilOut14 CATSTR <locuntilout14_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut14
	ELSEIFIDN UntilOut15,<> 
		UntilOut15 CATSTR <locuntilout15_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut15
	ELSEIFIDN UntilOut16,<> 
		UntilOut16 CATSTR <locuntilout16_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut16
	ELSEIFIDN UntilOut17,<> 
		UntilOut17 CATSTR <locuntilout17_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut17
	ELSEIFIDN UntilOut18,<> 
		UntilOut18 CATSTR <locuntilout18_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut18
	ELSEIFIDN UntilOut19,<> 
		UntilOut19 CATSTR <locuntilout19_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut19
	ELSE
		.err <Nesting level too deep.>
	ENDIF
ENDM

GetUntilOutLabel MACRO
	IFDIF UntilOut19,<>
		LastUntilOutLabel TEXTEQU UntilOut19
	ELSEIFDIF UntilOut18,<>
		LastUntilOutLabel TEXTEQU UntilOut18
	ELSEIFDIF UntilOut17,<>
		LastUntilOutLabel TEXTEQU UntilOut17
	ELSEIFDIF UntilOut16,<>
		LastUntilOutLabel TEXTEQU UntilOut16
	ELSEIFDIF UntilOut15,<>
		LastUntilOutLabel TEXTEQU UntilOut15
	ELSEIFDIF UntilOut14,<>
		LastUntilOutLabel TEXTEQU UntilOut14
	ELSEIFDIF UntilOut13,<>
		LastUntilOutLabel TEXTEQU UntilOut13	
	ELSEIFDIF UntilOut12,<>
		LastUntilOutLabel TEXTEQU UntilOut12
	ELSEIFDIF UntilOut11,<>
		LastUntilOutLabel TEXTEQU UntilOut11	
	ELSEIFDIF UntilOut10,<>
		LastUntilOutLabel TEXTEQU UntilOut10
	ELSEIFDIF UntilOut9,<>
		LastUntilOutLabel TEXTEQU UntilOut9
	ELSEIFDIF UntilOut8,<>
		LastUntilOutLabel TEXTEQU UntilOut8
	ELSEIFDIF UntilOut7,<>
		LastUntilOutLabel TEXTEQU UntilOut7
	ELSEIFDIF UntilOut6,<>
		LastUntilOutLabel TEXTEQU UntilOut6
	ELSEIFDIF UntilOut5,<>
		LastUntilOutLabel TEXTEQU UntilOut5
	ELSEIFDIF UntilOut4,<>
		LastUntilOutLabel TEXTEQU UntilOut4
	ELSEIFDIF UntilOut3,<>
		LastUntilOutLabel TEXTEQU UntilOut3	
	ELSEIFDIF UntilOut2,<>
		LastUntilOutLabel TEXTEQU UntilOut2
	ELSEIFDIF UntilOut1,<>
		LastUntilOutLabel TEXTEQU UntilOut1	
	ELSEIFDIF UntilOut0,<>
		LastUntilOutLabel TEXTEQU UntilOut0
	ELSE
		LastUntilOutLabel TEXTEQU <>
	ENDIF		
ENDM

DelUntilOutLabel MACRO
	IFDIF UntilOut19,<>
		UntilOut19 TEXTEQU <>
	ELSEIFDIF UntilOut18,<>
		UntilOut18 TEXTEQU <>
	ELSEIFDIF UntilOut17,<>
		UntilOut17 TEXTEQU <>
	ELSEIFDIF UntilOut16,<>
		UntilOut16 TEXTEQU <>
	ELSEIFDIF UntilOut15,<>
		UntilOut15 TEXTEQU <>
	ELSEIFDIF UntilOut14,<>
		UntilOut14 TEXTEQU <>
	ELSEIFDIF UntilOut13,<>
		UntilOut13 TEXTEQU <>	
	ELSEIFDIF UntilOut12,<>
		UntilOut12 TEXTEQU <>
	ELSEIFDIF UntilOut11,<>
		UntilOut11 TEXTEQU <>	
	ELSEIFDIF UntilOut10,<>
		UntilOut10 TEXTEQU <>
	ELSEIFDIF UntilOut9,<>
		UntilOut9 TEXTEQU <>
	ELSEIFDIF UntilOut8,<>
		UntilOut8 TEXTEQU <>
	ELSEIFDIF UntilOut7,<>
		UntilOut7 TEXTEQU <>
	ELSEIFDIF UntilOut6,<>
		UntilOut6 TEXTEQU <>
	ELSEIFDIF UntilOut5,<>
		UntilOut5 TEXTEQU <>
	ELSEIFDIF UntilOut4,<>
		UntilOut4 TEXTEQU <>
	ELSEIFDIF UntilOut3,<>
		UntilOut3 TEXTEQU <>	
	ELSEIFDIF UntilOut2,<>
		UntilOut2 TEXTEQU <>
	ELSEIFDIF UntilOut1,<>
		UntilOut1 TEXTEQU <>	
	ELSEIFDIF UntilOut0,<>
		UntilOut0 TEXTEQU <>
	ENDIF
ENDM

    OutLevel0 TEXTEQU <>
    OutLevel1 TEXTEQU <>
    OutLevel2 TEXTEQU <>
    OutLevel3 TEXTEQU <>
    OutLevel4 TEXTEQU <>
    OutLevel5 TEXTEQU <>
    OutLevel6 TEXTEQU <>
    OutLevel7 TEXTEQU <>
    OutLevel8 TEXTEQU <>
    OutLevel9 TEXTEQU <>
    OutLevel10 TEXTEQU <>
    OutLevel11 TEXTEQU <>
    OutLevel12 TEXTEQU <>
    OutLevel13 TEXTEQU <>
    OutLevel14 TEXTEQU <>
    OutLevel15 TEXTEQU <>
    OutLevel16 TEXTEQU <>
    OutLevel17 TEXTEQU <>
    OutLevel18 TEXTEQU <>
    OutLevel19 TEXTEQU <>
    LastOutLabel TEXTEQU <>

SaveOutLabel MACRO
	IFIDN OutLevel0,<>
		OutLevel0 CATSTR <locout0_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel1,<> 
		OutLevel1 CATSTR <locout1_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel2,<> 
		OutLevel2 CATSTR <locout2_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel3,<> 
		OutLevel3 CATSTR <locout3_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel4,<> 
		OutLevel4 CATSTR <locout4_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel5,<> 
		OutLevel5 CATSTR <locout5_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel6,<> 
		OutLevel6 CATSTR <locout6_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel7,<> 
		OutLevel7 CATSTR <locout7_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel8,<> 
		OutLevel8 CATSTR <locout8_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel9,<> 
		OutLevel9 CATSTR <locout9_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel10,<>
		OutLevel10 CATSTR <locout10_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel11,<> 
		OutLevel11 CATSTR <locout11_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel12,<> 
		OutLevel12 CATSTR <locout12_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel13,<> 
		OutLevel13 CATSTR <locout13_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel14,<> 
		OutLevel14 CATSTR <locout14_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel15,<> 
		OutLevel15 CATSTR <locout15_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel16,<> 
		OutLevel16 CATSTR <locout16_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel17,<> 
		OutLevel17 CATSTR <locout17_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel18,<> 
		OutLevel18 CATSTR <locout18_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel19,<> 
		OutLevel19 CATSTR <locout19_>,@CatStr(%TotalIfs)
	ELSE
		.err <Nesting level too deep.>
	ENDIF
ENDM

GetOutLabel MACRO
	IFDIF OutLevel19,<>
		LastOutLabel TEXTEQU OutLevel19
	ELSEIFDIF OutLevel18,<>
		LastOutLabel TEXTEQU OutLevel18
	ELSEIFDIF OutLevel17,<>
		LastOutLabel TEXTEQU OutLevel17
	ELSEIFDIF OutLevel16,<>
		LastOutLabel TEXTEQU OutLevel16
	ELSEIFDIF OutLevel15,<>
		LastOutLabel TEXTEQU OutLevel15
	ELSEIFDIF OutLevel14,<>
		LastOutLabel TEXTEQU OutLevel14
	ELSEIFDIF OutLevel13,<>
		LastOutLabel TEXTEQU OutLevel13	
	ELSEIFDIF OutLevel12,<>
		LastOutLabel TEXTEQU OutLevel12
	ELSEIFDIF OutLevel11,<>
		LastOutLabel TEXTEQU OutLevel11	
	ELSEIFDIF OutLevel10,<>
		LastOutLabel TEXTEQU OutLevel10
	ELSEIFDIF OutLevel9,<>
		LastOutLabel TEXTEQU OutLevel9
	ELSEIFDIF OutLevel8,<>
		LastOutLabel TEXTEQU OutLevel8
	ELSEIFDIF OutLevel7,<>
		LastOutLabel TEXTEQU OutLevel7
	ELSEIFDIF OutLevel6,<>
		LastOutLabel TEXTEQU OutLevel6
	ELSEIFDIF OutLevel5,<>
		LastOutLabel TEXTEQU OutLevel5
	ELSEIFDIF OutLevel4,<>
		LastOutLabel TEXTEQU OutLevel4
	ELSEIFDIF OutLevel3,<>
		LastOutLabel TEXTEQU OutLevel3	
	ELSEIFDIF OutLevel2,<>
		LastOutLabel TEXTEQU OutLevel2
	ELSEIFDIF OutLevel1,<>
		LastOutLabel TEXTEQU OutLevel1	
	ELSEIFDIF OutLevel0,<>
		LastOutLabel TEXTEQU OutLevel0
	ELSE
		LastOutLabel TEXTEQU <>
	ENDIF		
ENDM

DelOutLabel MACRO
	IFDIF OutLevel19,<>
		OutLevel19 TEXTEQU <>
	ELSEIFDIF OutLevel18,<>
		OutLevel18 TEXTEQU <>
	ELSEIFDIF OutLevel17,<>
		OutLevel17 TEXTEQU <>
	ELSEIFDIF OutLevel16,<>
		OutLevel16 TEXTEQU <>
	ELSEIFDIF OutLevel15,<>
		OutLevel15 TEXTEQU <>
	ELSEIFDIF OutLevel14,<>
		OutLevel14 TEXTEQU <>
	ELSEIFDIF OutLevel13,<>
		OutLevel13 TEXTEQU <>	
	ELSEIFDIF OutLevel12,<>
		OutLevel12 TEXTEQU <>
	ELSEIFDIF OutLevel11,<>
		OutLevel11 TEXTEQU <>	
	ELSEIFDIF OutLevel10,<>
		OutLevel10 TEXTEQU <>
	ELSEIFDIF OutLevel9,<>
		OutLevel9 TEXTEQU <>
	ELSEIFDIF OutLevel8,<>
		OutLevel8 TEXTEQU <>
	ELSEIFDIF OutLevel7,<>
		OutLevel7 TEXTEQU <>
	ELSEIFDIF OutLevel6,<>
		OutLevel6 TEXTEQU <>
	ELSEIFDIF OutLevel5,<>
		OutLevel5 TEXTEQU <>
	ELSEIFDIF OutLevel4,<>
		OutLevel4 TEXTEQU <>
	ELSEIFDIF OutLevel3,<>
		OutLevel3 TEXTEQU <>	
	ELSEIFDIF OutLevel2,<>
		OutLevel2 TEXTEQU <>
	ELSEIFDIF OutLevel1,<>
		OutLevel1 TEXTEQU <>	
	ELSEIFDIF OutLevel0,<>
		OutLevel0 TEXTEQU <>
	ENDIF
ENDM

    IfLevel0 TEXTEQU <>
    IfLevel1 TEXTEQU <>
    IfLevel2 TEXTEQU <>
    IfLevel3 TEXTEQU <>
    IfLevel4 TEXTEQU <>
    IfLevel5 TEXTEQU <>
    IfLevel6 TEXTEQU <>
    IfLevel7 TEXTEQU <>
    IfLevel8 TEXTEQU <>
    IfLevel9 TEXTEQU <>
    IfLevel10 TEXTEQU <>
    IfLevel11 TEXTEQU <>
    IfLevel12 TEXTEQU <>
    IfLevel13 TEXTEQU <>
    IfLevel14 TEXTEQU <>
    IfLevel15 TEXTEQU <>
    IfLevel16 TEXTEQU <>
    IfLevel17 TEXTEQU <>
    IfLevel18 TEXTEQU <>
    IfLevel19 TEXTEQU <>
    LastDefLabel TEXTEQU <>

SaveCurrentLabel MACRO
	IFIDN IfLevel0,<>
		IfLevel0 CATSTR <locif0_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel0
	ELSEIFIDN IfLevel1,<> 
		IfLevel1 CATSTR <locif1_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel1
	ELSEIFIDN IfLevel2,<> 
		IfLevel2 CATSTR <locif2_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel2
	ELSEIFIDN IfLevel3,<> 
		IfLevel3 CATSTR <locif3_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel3
	ELSEIFIDN IfLevel4,<> 
		IfLevel4 CATSTR <locif4_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel4
	ELSEIFIDN IfLevel5,<> 
		IfLevel5 CATSTR <locif5_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel5
	ELSEIFIDN IfLevel6,<> 
		IfLevel6 CATSTR <locif6_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel6
	ELSEIFIDN IfLevel7,<> 
		IfLevel7 CATSTR <locif7_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel7
	ELSEIFIDN IfLevel8,<> 
		IfLevel8 CATSTR <locif8_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel8
	ELSEIFIDN IfLevel9,<> 
		IfLevel9 CATSTR <locif9_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel9
	ELSEIFIDN IfLevel10,<>
		IfLevel10 CATSTR <locif10_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel10
	ELSEIFIDN IfLevel11,<> 
		IfLevel11 CATSTR <locif11_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel11
	ELSEIFIDN IfLevel12,<> 
		IfLevel12 CATSTR <locif12_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel12
	ELSEIFIDN IfLevel13,<> 
		IfLevel13 CATSTR <locif13_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel13
	ELSEIFIDN IfLevel14,<> 
		IfLevel14 CATSTR <locif14_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel14
	ELSEIFIDN IfLevel15,<> 
		IfLevel15 CATSTR <locif15_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel15
	ELSEIFIDN IfLevel16,<> 
		IfLevel16 CATSTR <locif16_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel16
	ELSEIFIDN IfLevel17,<> 
		IfLevel17 CATSTR <locif17_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel17
	ELSEIFIDN IfLevel18,<> 
		IfLevel18 CATSTR <locif18_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel18
	ELSEIFIDN IfLevel19,<> 
		IfLevel19 CATSTR <locif19_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel19
	ELSE
		.err <Nesting level too deep.>
	ENDIF
	TotalIfs = TotalIfs+1
ENDM

GetCurrentLabel MACRO
	IFDIF IfLevel19,<>
		LastDefLabel TEXTEQU IfLevel19
	ELSEIFDIF IfLevel18,<>
		LastDefLabel TEXTEQU IfLevel18
	ELSEIFDIF IfLevel17,<>
		LastDefLabel TEXTEQU IfLevel17
	ELSEIFDIF IfLevel16,<>
		LastDefLabel TEXTEQU IfLevel16
	ELSEIFDIF IfLevel15,<>
		LastDefLabel TEXTEQU IfLevel15
	ELSEIFDIF IfLevel14,<>
		LastDefLabel TEXTEQU IfLevel14
	ELSEIFDIF IfLevel13,<>
		LastDefLabel TEXTEQU IfLevel13	
	ELSEIFDIF IfLevel12,<>
		LastDefLabel TEXTEQU IfLevel12
	ELSEIFDIF IfLevel11,<>
		LastDefLabel TEXTEQU IfLevel11	
	ELSEIFDIF IfLevel10,<>
		LastDefLabel TEXTEQU IfLevel10
	ELSEIFDIF IfLevel9,<>
		LastDefLabel TEXTEQU IfLevel9
	ELSEIFDIF IfLevel8,<>
		LastDefLabel TEXTEQU IfLevel8
	ELSEIFDIF IfLevel7,<>
		LastDefLabel TEXTEQU IfLevel7
	ELSEIFDIF IfLevel6,<>
		LastDefLabel TEXTEQU IfLevel6
	ELSEIFDIF IfLevel5,<>
		LastDefLabel TEXTEQU IfLevel5
	ELSEIFDIF IfLevel4,<>
		LastDefLabel TEXTEQU IfLevel4
	ELSEIFDIF IfLevel3,<>
		LastDefLabel TEXTEQU IfLevel3	
	ELSEIFDIF IfLevel2,<>
		LastDefLabel TEXTEQU IfLevel2
	ELSEIFDIF IfLevel1,<>
		LastDefLabel TEXTEQU IfLevel1	
	ELSEIFDIF IfLevel0,<>
		LastDefLabel TEXTEQU IfLevel0
	ELSE
		LastDefLabel TEXTEQU <>
	ENDIF		
ENDM

DelCurrentLabel MACRO
	IFDIF IfLevel19,<>
		IfLevel19 TEXTEQU <>
	ELSEIFDIF IfLevel18,<>
		IfLevel18 TEXTEQU <>
	ELSEIFDIF IfLevel17,<>
		IfLevel17 TEXTEQU <>
	ELSEIFDIF IfLevel16,<>
		IfLevel16 TEXTEQU <>
	ELSEIFDIF IfLevel15,<>
		IfLevel15 TEXTEQU <>
	ELSEIFDIF IfLevel14,<>
		IfLevel14 TEXTEQU <>
	ELSEIFDIF IfLevel13,<>
		IfLevel13 TEXTEQU <>	
	ELSEIFDIF IfLevel12,<>
		IfLevel12 TEXTEQU <>
	ELSEIFDIF IfLevel11,<>
		IfLevel11 TEXTEQU <>	
	ELSEIFDIF IfLevel10,<>
		IfLevel10 TEXTEQU <>
	ELSEIFDIF IfLevel9,<>
		IfLevel9 TEXTEQU <>
	ELSEIFDIF IfLevel8,<>
		IfLevel8 TEXTEQU <>
	ELSEIFDIF IfLevel7,<>
		IfLevel7 TEXTEQU <>
	ELSEIFDIF IfLevel6,<>
		IfLevel6 TEXTEQU <>
	ELSEIFDIF IfLevel5,<>
		IfLevel5 TEXTEQU <>
	ELSEIFDIF IfLevel4,<>
		IfLevel4 TEXTEQU <>
	ELSEIFDIF IfLevel3,<>
		IfLevel3 TEXTEQU <>	
	ELSEIFDIF IfLevel2,<>
		IfLevel2 TEXTEQU <>
	ELSEIFDIF IfLevel1,<>
		IfLevel1 TEXTEQU <>	
	ELSEIFDIF IfLevel0,<>
		IfLevel0 TEXTEQU <>
	ENDIF
ENDM

.if MACRO args:VARARG
	SaveOutLabel
	SaveCurrentLabel
	J_POLY_COND LastDefLabel,FALSE,<args>
ENDM

.elseif MACRO args:VARARG
	GetOutLabel
	jmp LastOutLabel
	GetCurrentLabel
LastDefLabel:
	DelCurrentLabel
	SaveCurrentLabel
	J_POLY_COND LastDefLabel,FALSE,<args>	
ENDM

.nextif MACRO args:VARARG
	GetCurrentLabel
	J_POLY_COND LastDefLabel,TRUE,<args>
ENDM

.else MACRO
	GetOutLabel
	jmp LastOutLabel	
	GetCurrentLabel
LastDefLabel:
	DelCurrentLabel
	SaveCurrentLabel
ENDM

.endif MACRO
	GetCurrentLabel
LastDefLabel:
	DelCurrentLabel
	GetOutLabel
LastOutLabel:
	DelOutLabel
ENDM

;SaveUntilCondsLabel
;GetUntilCondsLabel
;DelUntilCondsLabel
while_cnt=0
.repeat MACRO
	while_cnt=while_cnt+1
	SaveUntilCondsLabel
	SaveUntilOutLabel
	SaveUntilLabel	
LastUntilLabel:
ENDM

j_test equ 1
.break MACRO args:VARARG
	GetUntilOutLabel
	IF @SizeStr(<args>) NE 0
		J_POLY_COND LastUntilOutLabel,TRUE,@SubStr(<args>,5,@SizeStr(<args>)-4)
		GOTO EndBreak		
	ELSE
		jmp LastUntilOutLabel
	ENDIF
:EndBreak
ENDM

.continue MACRO args:VARARG
	GetUntilCondsLabel
	IF @SizeStr(<args>) NE 0
		J_POLY_COND LastUntilConds,TRUE,@SubStr(<args>,5,@SizeStr(<args>)-4)		
	ELSE
		jmp LastUntilConds
	ENDIF
ENDM

.skip MACRO args:VARARG
	GetUntilLabel
	IF @SizeStr(<args>) NE 0
		J_POLY_COND LastUntilLabel,TRUE,@SubStr(<args>,5,@SizeStr(<args>)-4)		
	ELSE
		jmp LastUntilLabel
	ENDIF
ENDM

.until MACRO args:VARARG
	GetUntilCondsLabel
LastUntilConds:
	DelUntilCondsLabel
	GetUntilLabel
	IF @SizeStr(<args>) NE 0
		J_POLY_COND LastUntilLabel,FALSE,args
	ELSE
		jmp LastUntilLabel
	ENDIF
	DelUntilLabel
	GetUntilOutLabel
LastUntilOutLabel:
	DelUntilOutLabel
	while_cnt=while_cnt-1	
ENDM

.untilcxz MACRO
	GetUntilCondsLabel
LastUntilConds:
	DelUntilCondsLabel
	GetUntilLabel
	loop LastUntilLabel
	DelUntilLabel
	GetUntilOutLabel
LastUntilOutLabel:
	DelUntilOutLabel
	while_cnt=while_cnt-1
ENDM

.untilcxzd MACRO
	GetUntilCondsLabel
LastUntilConds:
	DelUntilCondsLabel
	GetUntilLabel
	loopd LastUntilLabel
	DelUntilLabel
	GetUntilOutLabel
LastUntilOutLabel:
	DelUntilOutLabel
	while_cnt=while_cnt-1
ENDM

.untilcxze MACRO
	GetUntilCondsLabel
LastUntilConds:
	DelUntilCondsLabel
	GetUntilLabel
	loope LastUntilLabel
	DelUntilLabel	
	GetUntilOutLabel
LastUntilOutLabel:
	DelUntilOutLabel
	while_cnt=while_cnt-1
ENDM

.untilcxzne MACRO
	GetUntilCondsLabel
LastUntilConds:
	DelUntilCondsLabel
	GetUntilLabel
	loopne LastUntilLabel
	DelUntilLabel
	GetUntilOutLabel
LastUntilOutLabel:
	DelUntilOutLabel
	while_cnt=while_cnt-1
ENDM

.untilcxzed MACRO
	GetUntilCondsLabel
LastUntilConds:
	DelUntilCondsLabel
	GetUntilLabel
	looped LastUntilLabel
	DelUntilLabel	
	GetUntilOutLabel
LastUntilOutLabel:
	DelUntilOutLabel
	while_cnt=while_cnt-1
ENDM

.untilcxzned MACRO
	GetUntilCondsLabel
LastUntilConds:
	DelUntilCondsLabel
	GetUntilLabel
	loopned LastUntilLabel
	DelUntilLabel
	GetUntilOutLabel
LastUntilOutLabel:
	DelUntilOutLabel
	while_cnt=while_cnt-1
ENDM

    WhileLevel0 TEXTEQU <>
    WhileLevel1 TEXTEQU <>
    WhileLevel2 TEXTEQU <>
    WhileLevel3 TEXTEQU <>
    WhileLevel4 TEXTEQU <>
    WhileLevel5 TEXTEQU <>
    WhileLevel6 TEXTEQU <>
    WhileLevel7 TEXTEQU <>
    WhileLevel8 TEXTEQU <>
    WhileLevel9 TEXTEQU <>
    WhileLevel10 TEXTEQU <>
    WhileLevel11 TEXTEQU <>
    WhileLevel12 TEXTEQU <>
    WhileLevel13 TEXTEQU <>
    WhileLevel14 TEXTEQU <>
    WhileLevel15 TEXTEQU <>
    WhileLevel16 TEXTEQU <>
    WhileLevel17 TEXTEQU <>
    WhileLevel18 TEXTEQU <>
    WhileLevel19 TEXTEQU <>
    wcond0l=0
    wcond1l=0
    wcond2l=0
    wcond3l=0
    wcond4l=0
    wcond5l=0
    wcond6l=0
    wcond7l=0
    wcond8l=0
    wcond9l=0
    wcond10l=0
    wcond11l=0
    wcond12l=0
    wcond13l=0
    wcond14l=0
    wcond15l=0
    wcond16l=0
    wcond17l=0
    wcond18l=0
    wcond19l=0

.while MACRO args:VARARG
	SaveUntilCondsLabel
	IFDIF <args>,<TRUE>
		jmp LastUntilConds
	ENDIF
	SaveUntilOutLabel
	SaveUntilLabel	
LastUntilLabel:
	while_cnt=while_cnt+1
	IF while_cnt EQ 1
		WhileLevel0 TEXTEQU <args>
		wcond0l SIZESTR <args>
	ELSEIF while_cnt EQ 2
		WhileLevel1 TEXTEQU <args>
		wcond1l SIZESTR <args>
	ELSEIF while_cnt EQ 3
		WhileLevel2 TEXTEQU <args>
		wcond2l SIZESTR <args>
	ELSEIF while_cnt EQ 4
		WhileLevel3 TEXTEQU <args>
		wcond3l SIZESTR <args>
	ELSEIF while_cnt EQ 5
		WhileLevel4 TEXTEQU <args>
		wcond4l SIZESTR <args>
	ELSEIF while_cnt EQ 6
		WhileLevel5 TEXTEQU <args>
		wcond5l SIZESTR <args>
	ELSEIF while_cnt EQ 7
		WhileLevel6 TEXTEQU <args>
		wcond6l SIZESTR <args>
	ELSEIF while_cnt EQ 8
		WhileLevel7 TEXTEQU <args>
		wcond7l SIZESTR <args>
	ELSEIF while_cnt EQ 9
		WhileLevel8 TEXTEQU <args>
		wcond8l SIZESTR <args>
	ELSEIF while_cnt EQ 10
		WhileLevel9 TEXTEQU <args>
		wcond9l SIZESTR <args>
	ELSEIF while_cnt EQ 11
		WhileLevel10 TEXTEQU <args>
		wcond10l SIZESTR <args>
	ELSEIF while_cnt EQ 12
		WhileLevel11 TEXTEQU <args>
		wcond11l SIZESTR <args>
	ELSEIF while_cnt EQ 13
		WhileLevel12 TEXTEQU <args>
		wcond12l SIZESTR <args>
	ELSEIF while_cnt EQ 14
		WhileLevel13 TEXTEQU <args>
		wcond13l SIZESTR <args>
	ELSEIF while_cnt EQ 15
		WhileLevel14 TEXTEQU <args>
		wcond14l SIZESTR <args>
	ELSEIF while_cnt EQ 16
		WhileLevel15 TEXTEQU <args>
		wcond15l SIZESTR <args>
	ELSEIF while_cnt EQ 17
		WhileLevel16 TEXTEQU <args>
		wcond16l SIZESTR <args>
	ELSEIF while_cnt EQ 18
		WhileLevel17 TEXTEQU <args>
		wcond17l SIZESTR <args>
	ELSEIF while_cnt EQ 19
		WhileLevel18 TEXTEQU <args>
		wcond18l SIZESTR <args>
	ELSEIF while_cnt EQ 20
		WhileLevel19 TEXTEQU <args>
		wcond19l SIZESTR <args>
	ELSE
		.err <Nesting level too deep.>
	ENDIF
ENDM

.endw MACRO
	GetUntilCondsLabel
LastUntilConds:
	DelUntilCondsLabel
	GetUntilLabel
	IF (while_cnt EQ 1) AND (wcond0l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel0
	ELSEIF (while_cnt EQ 2) AND (wcond1l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel1
	ELSEIF (while_cnt EQ 3) AND (wcond2l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel2
	ELSEIF (while_cnt EQ 4) AND (wcond3l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel3
	ELSEIF (while_cnt EQ 5) AND (wcond4l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel4
	ELSEIF (while_cnt EQ 6) AND (wcond5l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel5
	ELSEIF (while_cnt EQ 7) AND (wcond6l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel6
	ELSEIF (while_cnt EQ 8) AND (wcond7l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel7
	ELSEIF (while_cnt EQ 9) AND (wcond8l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel8
	ELSEIF (while_cnt EQ 10) AND (wcond9l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel9
	ELSEIF (while_cnt EQ 11) AND (wcond10l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel10
	ELSEIF (while_cnt EQ 12) AND (wcond11l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel11
	ELSEIF (while_cnt EQ 13) AND (wcond12l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel12
	ELSEIF (while_cnt EQ 14) AND (wcond13l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel13
	ELSEIF (while_cnt EQ 15) AND (wcond14l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel14
	ELSEIF (while_cnt EQ 16) AND (wcond15l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel15
	ELSEIF (while_cnt EQ 17) AND (wcond16l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel16
	ELSEIF (while_cnt EQ 18) AND (wcond17l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel17
	ELSEIF (while_cnt EQ 19) AND (wcond18l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel18
	ELSEIF (while_cnt EQ 20) AND (wcond19l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel19
	ENDIF
	DelUntilLabel
	GetUntilOutLabel
LastUntilOutLabel:
	DelUntilOutLabel
	while_cnt=while_cnt-1
ENDM

IS_ALNUM MACRO char
CharPosition INSTR 1,<0123456789abcdefghijklmnopqrstvuwxyzABCDEFGHIJKLMNOPQRSTVUWXYZ>,<char>
	exitm <@CatStr(%CharPosition)>
ENDM

IS_INT_REG MACRO val
RegPosition INSTR 1,< rsi al bl cl dl ah bh ch dh sil dil bpl spl r8b r9b r10b r11b r12b r13b r14b r15b eax ebx ecx edx esi edi ebp esp r14d r15d >,<val>
	IF RegPosition EQ 0
		RegPosition INSTR 1,< rax rbx rdx rcx rsi rdi rbp rsp r8w r9w r10w r11w r12w r13w r14w r15w r8d r9d r10d r11d r12d r13d r8 r9 r10 r11 r12 r13 r14 r15 >,<val>
	ENDIF
	exitm <@CatStr(%RegPosition)>
ENDM

constStringsNum=0
regIndex=0
ItemLen=0
AddrArg TEXTEQU <>
constStr TEXTEQU <>
itemSize=0
reg32v TEXTEQU <>

ToUpper MACRO String:VARARG
LOCAL UpperStr,LowNum
	UpperStr TEXTEQU <>
%	FORC char,<String>
		LowNum INSTR 1,<abcdefghijklmnopqrstuvwxyz>,<char>
		IF LowNum NE 0
			UpperStr CATSTR UpperStr,@SubStr(<ABCDEFGHIJKLMNOPQRSTUVWXYZ>,LowNum,1)
		ELSE
			UpperStr CATSTR UpperStr,<char>
		ENDIF
	ENDM
	EXITM <UpperStr>
ENDM

ToLower MACRO String:VARARG
LOCAL UpperStr,LowNum
	UpperStr TEXTEQU <>
%	FORC char,<String>
		LowNum INSTR 1,<ABCDEFGHIJKLMNOPQRSTUVWXYZ>,<char>
		IF LowNum NE 0
			UpperStr CATSTR UpperStr,@SubStr(<abcdefghijklmnopqrstuvwxyz>,LowNum,1)
		ELSE
			UpperStr CATSTR UpperStr,<char>
		ENDIF
	ENDM
	EXITM <UpperStr>
ENDM

; --------------------------------------------------------------------------------

FillStack = 1
rbpArg14	equ <[rbp-rbpFirstArgBias+8*14-8]>
rbpArg13	equ <[rbp-rbpFirstArgBias+8*13-8]>
rbpArg12	equ <[rbp-rbpFirstArgBias+8*12-8]>
rbpArg11	equ <[rbp-rbpFirstArgBias+8*11-8]>
rbpArg10	equ <[rbp-rbpFirstArgBias+8*10-8]>
rbpArg9		equ <[rbp-rbpFirstArgBias+8*9-8]>
rbpArg8		equ <[rbp-rbpFirstArgBias+8*8-8]>
rbpArg7		equ <[rbp-rbpFirstArgBias+8*7-8]>
rbpArg6		equ <[rbp-rbpFirstArgBias+8*6-8]>
rbpArg5		equ <[rbp-rbpFirstArgBias+8*5-8]>
rbpArg4		equ <[rbp-rbpFirstArgBias+8*4-8]>
rbpArg3		equ <[rbp-rbpFirstArgBias+8*3-8]>
rbpArg2		equ <[rbp-rbpFirstArgBias+8*2-8]>
rbpArg1		equ <[rbp-rbpFirstArgBias+8*1-8]>
rspBorder	= 0A8h
rspArg14	equ <[rsp+8*14-8]>
rspArg13	equ <[rsp+8*13-8]>
rspArg12	equ <[rsp+8*12-8]>
rspArg11	equ <[rsp+8*11-8]>
rspArg10	equ <[rsp+8*10-8]>
rspArg9		equ <[rsp+8*9-8]>
rspArg8		equ <[rsp+8*8-8]>
rspArg7		equ <[rsp+8*7-8]>
rspArg6		equ <[rsp+8*6-8]>
rspArg5		equ <[rsp+8*5-8]>
rspArg4		equ <[rsp+8*4-8]>
rspArg3		equ <[rsp+8*3-8]>
rspArg2		equ <[rsp+8*2-8]>
rspArg1		equ <[rsp+8*1-8]>

FREE_RAX equ (1 shl 0)
FREE_RBX equ (1 shl 1)
FREE_RCX equ (1 shl 2)
FREE_RDX equ (1 shl 3)
FREE_RSP equ (1 shl 4)
FREE_RBP equ (1 shl 5)
FREE_RDI equ (1 shl 6)
FREE_RSI equ (1 shl 7)
FREE_R8  equ (1 shl 8)
FREE_R9  equ (1 shl 9)
FREE_R10 equ (1 shl 10)
FREE_R11 equ (1 shl 11)
FREE_R12 equ (1 shl 12)
FREE_R13 equ (1 shl 13)
FREE_R14 equ (1 shl 14)
FREE_R15 equ (1 shl 15)
FreeRegs=(FREE_RAX or FREE_RCX or FREE_RDX or FREE_R8 or FREE_R9 or FREE_R10 or FREE_R11)

IN_ARG1_READY equ (1 shl 1)
IN_ARG2_READY equ (1 shl 2)
IN_ARG3_READY equ (1 shl 3)
IN_ARG4_READY equ (1 shl 4)
IN_ARG5_READY equ (1 shl 5)
IN_ARG6_READY equ (1 shl 6)
IN_ARG7_READY equ (1 shl 7)
IN_ARG8_READY equ (1 shl 8)
IN_ARG9_READY equ (1 shl 9)
IN_ARG10_READY equ (1 shl 10)
IN_ARG11_READY equ (1 shl 11)
IN_ARG12_READY equ (1 shl 12)
IN_ARG13_READY equ (1 shl 13)
IN_ARG14_READY equ (1 shl 14)

; ===========================
 
IsCharForNames MACRO char
CharPosition INSTR 1,<0123456789abcdefghijklmnopqrstvuwxyzABCDEFGHIJKLMNOPQRSTVUWXYZ_.?$@>,<char>
	EXITM<@CatStr(%CharPosition)>
ENDM

SelectValidSymbols MACRO CondString:VARARG
;;LOCAL SkipState,cnt_letter,curr_letter,c_char
	SkipState=0
	curr_letter=0
	ph_count=0
	cnt_letter SIZESTR <CondString>
	WHILE cnt_letter
		curr_letter=curr_letter+1
		c_char SUBSTR <CondString>,curr_letter,1
		IF SkipState EQ 0
			IF IsCharForNames(%c_char) EQ 0
				IFIDN c_char,<[>
					SkipState=1
				ELSEIFIDN c_char,<(>
					SkipState=2
					ph_count=1
				ELSEIFIDN c_char,<">
					SkipState=5
				ELSEIFIDN c_char,<'>
					SkipState=6
				ELSEIFDIF c_char,< >
					EXITM
				ENDIF
			ENDIF
		ELSEIF SkipState EQ 1
			IFIDN c_char,<]>
				SkipState=0
			ELSEIFIDN c_char,<">
				SkipState=7
			ELSEIFIDN c_char,<'>
				SkipState=8
			ENDIF
		ELSEIF SkipState EQ 2
			IFIDN c_char,<)>
				ph_count=ph_count-1
				IF ph_count EQ 0
					SkipState=0
				ENDIF
			ELSEIFIDN c_char,<(>
				ph_count=ph_count+1
			ELSEIFIDN c_char,<">
				SkipState=3
			ELSEIFIDN c_char,<'>
				SkipState=4
			ENDIF
		ELSEIF SkipState EQ 3
			IFIDN c_char,<">
				SkipState=2
			ENDIF
		ELSEIF SkipState EQ 4
			IFIDN c_char,<'>
				SkipState=2
			ENDIF
		ELSEIF SkipState EQ 5
			IFIDN c_char,<">
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 6
			IFIDN c_char,<'>
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 7
			IFIDN c_char,<">
				SkipState=1
			ENDIF
		ELSEIF SkipState EQ 8
			IFIDN c_char,<'>
				SkipState=1
			ENDIF
		ENDIF
		cnt_letter=cnt_letter-1
	ENDM
	IF cnt_letter EQ 0
		curr_letter=0
	ENDIF
	EXITM<@CatStr(%curr_letter)>
ENDM

sxb equ <sbyte ptr>
sxw equ <sword ptr>
sxd equ <sdword ptr>
sxq equ <sqword ptr>

j_one_bt_pow=0
j_one_bt_pow2=0
j_one_bt_pow3=0
j_one_bt_pow4=0
j_one_bt_uses=1

J_ONE_COND MACRO LabelName,IsTrueCondition,ConditionOne:VARARG
	cond_len SIZESTR <ConditionOne>
	fletter SUBSTR <ConditionOne>,1,1
	lletter SUBSTR <ConditionOne>,cond_len,1
	fchar=0
	schar=0
	lchar=0
	blchar=0
	IF cond_len GE 2
		IFIDN fletter,<(>
			fchar=1
		ELSEIFIDN fletter,<~>
			fchar=2
		ENDIF
		IFIDN @SubStr(<ConditionOne>,2,1),<(>
			schar=1
		ENDIF
		IFIDN lletter,<)>
			lchar=1
		ENDIF
		IFIDN lletter,<?>
			lchar=2
		ENDIF
		IFIDN @SubStr(<ConditionOne>,cond_len-1,1),<?>
			blchar=2
		ENDIF
	ENDIF
	IF fchar EQ 2
		IF (schar EQ 1) AND (lchar EQ 1)
			J_ONE_COND LabelName,(IsTrueCondition xor 1),@SubStr(<ConditionOne>,3,cond_len-3)
		ELSE
			J_ONE_COND LabelName,(IsTrueCondition xor 1),@SubStr(<ConditionOne>,2,cond_len-1)
		ENDIF
	ELSEIF (fchar EQ 1) AND (lchar EQ 1)	
		J_ONE_COND LabelName,IsTrueCondition,@SubStr(<ConditionOne>,2,cond_len-2)
	ELSE
		IF IsTrueCondition EQ FALSE
			NegateChar TEXTEQU <n>
			TrueChar TEXTEQU <>
		ELSE
			NegateChar TEXTEQU <>
			TrueChar TEXTEQU <n>
		ENDIF
		OperatorPos=SelectValidSymbols(ConditionOne)
		IF OperatorPos NE 0
			SingleRunTimeOperator SUBSTR <ConditionOne>,OperatorPos,1
		ELSE
			SingleRunTimeOperator TEXTEQU <>
		ENDIF
		CmpCmd TEXTEQU <>
		JCOND TEXTEQU <>
		IF OperatorPos EQ 0
			IF (OPATTR ConditionOne) EQ (IMM_EXPR OR VALID_REF)
				IF (ConditionOne NE 0)
					IF (IsTrueCondition NE 0)
						JCOND CATSTR <jmp >,<LabelName>
					ENDIF
				ELSEIF IsTrueCondition EQ 0
					JCOND CATSTR <jmp >,<LabelName>
				ENDIF
			ELSE
				IF lchar EQ 2
					IFIDN <ConditionOne>,<SIGN?>
						JCOND CATSTR <j>,NegateChar,<s >,<LabelName>
					ELSEIFIDN <ConditionOne>,<ZERO?>
						JCOND CATSTR <j>,NegateChar,<z >,<LabelName>
					ELSEIFIDN <ConditionOne>,<OVERFLOW?>
						JCOND CATSTR <j>,NegateChar,<o >,<LabelName>
					ELSEIFIDN <ConditionOne>,<PARITY?>
						JCOND CATSTR <j>,NegateChar,<p >,<LabelName>
					ELSEIFIDN <ConditionOne>,<CARRY?>
						JCOND CATSTR <j>,NegateChar,<c >,<LabelName>
					ENDIF
				ENDIF
				IFIDN JCOND,<>
					FirstArg TEXTEQU <ConditionOne>
					reg_ind=RegIndex(%FirstArg)
					reg_high_ind=RegHigh8Index(%FirstArg)
					is_jxcxz=0
					IF (reg_ind EQ 1) AND (IsTrueCondition EQ FALSE)
						IFDIF fletter,<c>
							is_jxcxz=1
						ENDIF
					ENDIF
					IF (is_jxcxz EQ 1)
						JCOND CATSTR <j>,FirstArg,<z >,<LabelName>
					ELSEIF (reg_ind EQ NOT_A_REG) AND (reg_high_ind EQ NOT_A_REG8)
						CmpCmd CATSTR <cmp >,FirstArg,<,0>
						JCOND CATSTR <j>,TrueChar,<z >,<LabelName>
					ELSE
						CmpCmd CATSTR <test >,FirstArg,<,>,FirstArg
						JCOND CATSTR <j>,TrueChar,<z >,<LabelName>
					ENDIF
				ENDIF
			ENDIF
		ELSE
			IF lchar EQ 2
				IFIDN <ConditionOne>,<SIGN?{}OVERFLOW?>
					JCOND CATSTR <j>,NegateChar,<l >,<LabelName>
				ELSEIFIDN <ConditionOne>,<SIGN?~=OVERFLOW?>
					JCOND CATSTR <j>,NegateChar,<l >,<LabelName>
				ELSEIFIDN <ConditionOne>,<SIGN?==OVERFLOW?>
					JCOND CATSTR <j>,NegateChar,<ge >,<LabelName>
				ELSEIFIDN <ConditionOne>,<CARRY?|ZERO?>
					JCOND CATSTR <j>,NegateChar,<be >,<LabelName>
				ENDIF
			ELSEIF (lchar EQ 1) AND (blchar EQ 2)
				IFIDN <ConditionOne>,<ZERO?|(SIGN?{}OVERFLOW?)>
					JCOND CATSTR <j>,NegateChar,<le >,<LabelName>
				ELSEIFIDN <ConditionOne>,<ZERO?|(SIGN?~=OVERFLOW?)>
					JCOND CATSTR <j>,NegateChar,<le >,<LabelName>
				ELSEIFIDN <ConditionOne>,<ZERO?&(SIGN?==OVERFLOW?)>
					JCOND CATSTR <j>,TrueChar,<g >,<LabelName>
				ENDIF
			ENDIF
			IFIDN JCOND,<>
				RunTimeOperator SUBSTR <ConditionOne>,OperatorPos,2
				FirstArg SUBSTR <ConditionOne>,1,OperatorPos-1
				is_signed_expr=0
				first_arg_length SIZESTR FirstArg
				IF first_arg_length GT 10
					IF first_arg_length GT 11
						first_arg_type_spec SUBSTR FirstArg,1,11
						first_arg_type_spec_len=11
					ELSE
						first_arg_type_spec SUBSTR FirstArg,1,10
						first_arg_type_spec_len=10
					ENDIF
					IFIDNI first_arg_type_spec,<sdword ptr >
						is_signed_expr=4
					ELSEIFIDNI first_arg_type_spec,<sqword ptr >
						is_signed_expr=8
					ELSE
						IF first_arg_type_spec_len EQ 11
							first_arg_type_spec SUBSTR first_arg_type_spec,1,10
						ENDIF
						IFIDNI first_arg_type_spec,<sbyte ptr >
							is_signed_expr=1
						ELSEIFIDNI first_arg_type_spec,<sword ptr >
							is_signed_expr=2
						ENDIF
					ENDIF
				ENDIF				
				IF cond_len GE (OperatorPos+2)
					SecondArg SUBSTR <ConditionOne>,OperatorPos+2,cond_len-OperatorPos-1
				ENDIF

				IFIDN RunTimeOperator,<==>		
					JCOND CATSTR <j>,NegateChar,<z >,<LabelName>

				ELSEIFIDN RunTimeOperator,<~=>		
					JCOND CATSTR <j>,TrueChar,<z >,<LabelName>

				ELSEIFIDN RunTimeOperator,<{}>
					JCOND CATSTR <j>,TrueChar,<z >,<LabelName>

				ELSEIFIDN RunTimeOperator,<}=>
					IF is_signed_expr
						JCOND CATSTR <j>,NegateChar,<ge >,<LabelName>
					ELSE
						JCOND CATSTR <j>,NegateChar,<ae >,<LabelName>
					ENDIF

				ELSEIFIDN RunTimeOperator,<{=>
					IF is_signed_expr
						JCOND CATSTR <j>,NegateChar,<le >,<LabelName>
					ELSE
						JCOND CATSTR <j>,NegateChar,<be >,<LabelName>
					ENDIF

				ELSEIFIDN RunTimeOperator,<={>
					IF is_signed_expr
						JCOND CATSTR <j>,NegateChar,<le >,<LabelName>
					ELSE
						JCOND CATSTR <j>,NegateChar,<be >,<LabelName>
					ENDIF

				ELSEIFIDN RunTimeOperator,<&&>
					IFIDN SecondArg,<SIGN?>
						reg_ind=RegIndex(%FirstArg)
						reg_high_ind=RegHigh8Index(%FirstArg)
						IF (reg_ind EQ NOT_A_REG) AND (reg_high_ind EQ NOT_A_REG8)
							CmpCmd TEXTEQU <cmp >,FirstArg,<,0>
						ELSE
							CmpCmd TEXTEQU <test >,FirstArg,<,>,FirstArg
						ENDIF
						JCOND CATSTR <j>,NegateChar,<s >,<LabelName>
					ELSE
						CmpCmd CATSTR <test >,FirstArg,<,>,SecondArg
						JCOND CATSTR <j>,TrueChar,<z >,<LabelName>
					ENDIF
				ENDIF
				IFIDN JCOND,<>
					SecondArg SUBSTR <ConditionOne>,OperatorPos+1,cond_len-OperatorPos
					IFIDN SingleRunTimeOperator,<}>
						IF is_signed_expr
							JCOND CATSTR <j>,NegateChar,<g >,<LabelName>
						ELSE
							JCOND CATSTR <j>,NegateChar,<a >,<LabelName>
						ENDIF
					ELSEIFIDN SingleRunTimeOperator,<{>
						IF is_signed_expr
							JCOND CATSTR <j>,NegateChar,<l >,<LabelName>
						ELSE
							JCOND CATSTR <j>,NegateChar,<b >,<LabelName>
						ENDIF
					ELSEIFIDN SingleRunTimeOperator,<|>
						CmpCmd CATSTR <or >,FirstArg,<,>,SecondArg
						JCOND CATSTR <j>,TrueChar,<z >,<LabelName>
					ELSEIFIDN SingleRunTimeOperator,<&>
						IFIDN SecondArg,<SIGN?>
							reg_ind=RegIndex(%FirstArg)
							reg_high_ind=RegHigh8Index(%FirstArg)
							IF (reg_ind EQ NOT_A_REG) AND (reg_high_ind EQ NOT_A_REG8)
								CmpCmd TEXTEQU <cmp >,FirstArg,<,0>
							ELSE
								CmpCmd TEXTEQU <test >,FirstArg,<,>,FirstArg
							ENDIF
							JCOND CATSTR <j>,NegateChar,<s >,<LabelName>
						ELSEIF ((OPATTR (SecondArg)) EQ VIMM_EXPR) AND (TYPE FirstArg GT 1) AND (j_one_bt_uses EQ 1)
							j_one_bt_pow=0
							j_one_bt_pow4=0
							IF (SecondArg) EQ 0
								j_one_bt_pow4=-1
							ENDIF
							j_one_bt_pow2=(SecondArg) AND 0FFFFFFFFh
							j_one_bt_pow3=(SecondArg) SHR 32
							IF j_one_bt_pow2 EQ 0
								j_one_bt_pow=32
								j_one_bt_pow2=j_one_bt_pow3
							ELSEIF j_one_bt_pow3 NE 0
								j_one_bt_pow4=-1
							ENDIF
							j_one_bt_pow3=j_one_bt_pow2 SHR 16
							j_one_bt_pow2=j_one_bt_pow2 AND 0FFFFh
							IF j_one_bt_pow2 EQ 0
								j_one_bt_pow=j_one_bt_pow+16
								j_one_bt_pow2=j_one_bt_pow3
							ELSEIF j_one_bt_pow3 NE 0
								j_one_bt_pow4=-1
							ENDIF
							j_one_bt_pow3=j_one_bt_pow2 SHR 8
							j_one_bt_pow2=j_one_bt_pow2 AND 0FFh
							IF j_one_bt_pow2 EQ 0
								j_one_bt_pow=j_one_bt_pow+8
								j_one_bt_pow2=j_one_bt_pow3
							ELSEIF j_one_bt_pow3 NE 0
								j_one_bt_pow4=-1
							ENDIF
							j_one_bt_pow3=j_one_bt_pow2 SHR 4
							j_one_bt_pow2=j_one_bt_pow2 AND 0Fh
							IF j_one_bt_pow2 EQ 0
								j_one_bt_pow=j_one_bt_pow+4
								j_one_bt_pow2=j_one_bt_pow3
							ELSEIF j_one_bt_pow3 NE 0
								j_one_bt_pow4=-1
							ENDIF
							j_one_bt_pow3=j_one_bt_pow2 SHR 2
							j_one_bt_pow2=j_one_bt_pow2 AND 11y
							IF j_one_bt_pow2 EQ 0
								j_one_bt_pow=j_one_bt_pow+2
								j_one_bt_pow2=j_one_bt_pow3
							ELSEIF j_one_bt_pow3 NE 0
								j_one_bt_pow4=-1
							ENDIF
							j_one_bt_pow3=j_one_bt_pow2 SHR 1
							j_one_bt_pow2=j_one_bt_pow2 AND 1y
							IF j_one_bt_pow2 EQ 0
								j_one_bt_pow=j_one_bt_pow+1
								j_one_bt_pow2=j_one_bt_pow3
							ELSEIF j_one_bt_pow3 NE 0
								j_one_bt_pow4=-1
							ENDIF
							IF j_one_bt_pow4 EQ 0
								j_one_bt_pow4=((TYPE FirstArg) EQ 2) AND (j_one_bt_pow EQ 15)
								j_one_bt_pow4=j_one_bt_pow4 OR (((TYPE FirstArg) EQ 4) AND (j_one_bt_pow EQ 31))
								j_one_bt_pow4=j_one_bt_pow4 OR (((TYPE FirstArg) EQ 8) AND (j_one_bt_pow EQ 63))
								IF j_one_bt_pow4 EQ 0
									CmpCmd CATSTR <bt >,FirstArg,<,>,@CatStr(%j_one_bt_pow)
									JCOND CATSTR <j>,NegateChar,<c >,<LabelName>
								ELSE
									reg_ind=RegIndex(%FirstArg)
									IF reg_ind EQ NOT_A_REG
										CmpCmd TEXTEQU <cmp >,FirstArg,<,0>
									ELSE
										CmpCmd TEXTEQU <test >,FirstArg,<,>,FirstArg
									ENDIF
									JCOND CATSTR <j>,NegateChar,<s >,<LabelName>
								ENDIF
							ELSE
								CmpCmd CATSTR <test >,FirstArg,<,>,SecondArg
								JCOND CATSTR <j>,TrueChar,<z >,<LabelName>
							ENDIF
						ELSE
							CmpCmd CATSTR <test >,FirstArg,<,>,SecondArg
							JCOND CATSTR <j>,TrueChar,<z >,<LabelName>
						ENDIF
					ELSE
						.err <Bad conditional operator.>
					ENDIF
				ENDIF
				IFDIF SecondArg,<>
					IFIDN CmpCmd,<>
						CmpCmd CATSTR <cmp >,FirstArg,<,>,SecondArg
					ENDIF
				ENDIF
			ENDIF
		ENDIF
		CmpCmd
		JCOND	
	ENDIF
ENDM
GetIfsPosition MACRO CondString:VARARG
;;LOCAL SkipState,cnt_letter,curr_letter,c_char,c_log_operator,total_conds,ph_count
	SkipState=0
	curr_letter=0
	cnt_letter SIZESTR <CondString>
	IF cnt_letter LT 6
		EXITM<0>
	ENDIF
	ph_count=0
	WHILE cnt_letter GT 5
		curr_letter=curr_letter+1
		c_char SUBSTR <CondString>,curr_letter,1
		IF SkipState EQ 0
			IFIDN c_char,<[>
				SkipState=1
			ELSEIFIDN c_char,<">
				SkipState=2
			ELSEIFIDN c_char,<'>
				SkipState=3
			ELSEIFIDN c_char,<(>
				SkipState=4
				ph_count=1
			ELSEIFIDN c_char,< >
				c_log_operator SUBSTR <CondString>,curr_letter,5
				IFIDN c_log_operator,< .if >
					EXITM
				ENDIF
			ENDIF
		ELSEIF SkipState EQ 1
			IFIDN c_char,<]>
				SkipState=0
			ELSEIFIDN c_char,<">
				SkipState=7
			ELSEIFIDN c_char,<'>
				SkipState=8
			ENDIF
		ELSEIF SkipState EQ 2
			IFIDN c_char,<">
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 3
			IFIDN c_char,<'>
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 4
			IFIDN c_char,<)>
				ph_count=ph_count-1
				IF ph_count EQ 0
					SkipState=0
				ENDIF
			ELSEIFIDN c_char,<(>
				ph_count=ph_count+1
			ELSEIFIDN c_char,<">
				SkipState=5
			ELSEIFIDN c_char,<'>
				SkipState=6
			ENDIF
		ELSEIF SkipState EQ 5
			IFIDN c_char,<">
				SkipState=4
			ENDIF
		ELSEIF SkipState EQ 6
			IFIDN c_char,<'>
				SkipState=4
			ENDIF
		ELSEIF SkipState EQ 7
			IFIDN c_char,<">
				SkipState=1
			ENDIF
		ELSEIF SkipState EQ 8
			IFIDN c_char,<'>
				SkipState=1
			ENDIF
		ENDIF
		cnt_letter=cnt_letter-1
	ENDM
	IF cnt_letter LE 5
		EXITM<0>
	ENDIF
	EXITM<@CatStr(%curr_letter)>
ENDM
SelectOrValidConds MACRO CondString:VARARG
;;LOCAL SkipState,cnt_letter,curr_letter,c_char,c_log_operator,total_conds,ph_count
	SkipState=0
	curr_letter=0
	cnt_letter SIZESTR <CondString>
	IF cnt_letter LT 6
		EXITM<0>
	ENDIF
	ph_count=0
	WHILE cnt_letter GT 4
		curr_letter=curr_letter+1
		c_char SUBSTR <CondString>,curr_letter,1
		IF SkipState EQ 0
			IFIDN c_char,<[>
				SkipState=1
			ELSEIFIDN c_char,<">
				SkipState=2
			ELSEIFIDN c_char,<'>
				SkipState=3
			ELSEIFIDN c_char,<(>
				SkipState=4
				ph_count=1
			ELSEIFIDN c_char,< >
				c_log_operator SUBSTR <CondString>,curr_letter,4
				IFIDN c_log_operator,< || >
					EXITM
				ENDIF
			ENDIF
		ELSEIF SkipState EQ 1
			IFIDN c_char,<]>
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 2
			IFIDN c_char,<">
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 3
			IFIDN c_char,<'>
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 4
			IFIDN c_char,<)>
				ph_count=ph_count-1
				IF ph_count EQ 0
					SkipState=0
				ENDIF
			ELSEIFIDN c_char,<(>
				ph_count=ph_count+1
			ELSEIFIDN c_char,<">
				SkipState=5
			ELSEIFIDN c_char,<'>
				SkipState=6
			ENDIF
		ELSEIF SkipState EQ 5
			IFIDN c_char,<">
				SkipState=4
			ENDIF
		ELSEIF SkipState EQ 6
			IFIDN c_char,<'>
				SkipState=4
			ENDIF
		ENDIF
		cnt_letter=cnt_letter-1
	ENDM
	IF cnt_letter LE 4
		EXITM<0>
	ENDIF
	EXITM<@CatStr(%curr_letter)>
ENDM
SelectValidCond MACRO CondString:VARARG
;;LOCAL SkipState,cnt_letter,curr_letter,c_char,c_log_operator,total_conds,ph_count
	SkipState=0
	curr_letter=0
	cnt_letter SIZESTR <CondString>
	IF cnt_letter LT 6
		EXITM<0>
	ENDIF
	ph_count=0
	WHILE cnt_letter GT 4
		curr_letter=curr_letter+1
		c_char SUBSTR <CondString>,curr_letter,1
		IF SkipState EQ 0
			IFIDN c_char,<[>
				SkipState=1
			ELSEIFIDN c_char,<">
				SkipState=2
			ELSEIFIDN c_char,<'>
				SkipState=3
			ELSEIFIDN c_char,<(>
				SkipState=4
				ph_count=1
			ELSEIFIDN c_char,< >
				c_log_operator SUBSTR <CondString>,curr_letter,4
				IFIDN c_log_operator,< || >
					EXITM
				ELSEIFIDN c_log_operator,< && >
					EXITM
				ENDIF
			ENDIF
		ELSEIF SkipState EQ 1
			IFIDN c_char,<]>
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 2
			IFIDN c_char,<">
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 3
			IFIDN c_char,<'>
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 4
			IFIDN c_char,<)>
				ph_count=ph_count-1
				IF ph_count EQ 0
					SkipState=0
				ENDIF
			ELSEIFIDN c_char,<(>
				ph_count=ph_count+1
			ELSEIFIDN c_char,<">
				SkipState=5
			ELSEIFIDN c_char,<'>
				SkipState=6
			ENDIF
		ELSEIF SkipState EQ 5
			IFIDN c_char,<">
				SkipState=4
			ENDIF
		ELSEIF SkipState EQ 6
			IFIDN c_char,<'>
				SkipState=4
			ENDIF
		ENDIF
		cnt_letter=cnt_letter-1
	ENDM
	IF cnt_letter LE 4
		EXITM<0>
	ENDIF
	EXITM<@CatStr(%curr_letter)>
ENDM
IsSingleCond MACRO CondString:VARARG
;;LOCAL SkipState,cnt_letter,curr_letter,c_char,c_log_operator
	SkipState=0
	curr_letter=0
	cnt_letter SIZESTR <CondString>
	IF cnt_letter LT 6
		EXITM<1>
	ENDIF
	WHILE cnt_letter GT 4
		curr_letter=curr_letter+1
		c_char SUBSTR <CondString>,curr_letter,1
		IF SkipState EQ 0
			IFIDN c_char,<[>
				SkipState=1
			ELSEIFIDN c_char,<">
				SkipState=2
			ELSEIFIDN c_char,<'>
				SkipState=3
			ELSEIFIDN c_char,< >
				c_log_operator SUBSTR <CondString>,curr_letter,4
				IFIDN c_log_operator,< || >
					EXITM
				ELSEIFIDN c_log_operator,< && >
					EXITM
				ENDIF
			ENDIF
		ELSEIF SkipState EQ 1
			IFIDN c_char,<]>
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 2
			IFIDN c_char,<">
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 3
			IFIDN c_char,<'>
				SkipState=0
			ENDIF
		ENDIF
		cnt_letter=cnt_letter-1
	ENDM
	IF cnt_letter GT 4
		EXITM<0>
	ENDIF
	EXITM<1>
ENDM
IntermedLabel=0
J_POLY_COND MACRO LabelName,TrueConditions,ConditionsString:VARARG
LOCAL BeginCond,EndCond,LogOperator,locLabel,SetLabel,IsTrueConditions,NegCond,EndLabel,LastConds
	BeginCond=1
	EndCond=1
	SetLabel=0
	NegCond=0
	LastConds=0
	IsTrueConditions=TrueConditions
	IF IsSingleCond(<ConditionsString>) NE 0
		J_ONE_COND LabelName,IsTrueConditions,ConditionsString
	ELSE
		EndLabel CATSTR <intermedloc_>,@CatStr(%IntermedLabel)
		IntermedLabel=IntermedLabel+1
		SetLabel=0
		LogOperator=0
	:NextCond
		IFIDN @SubStr(<ConditionsString>,BeginCond,2),<~(>
			IsTrueConditions=IsTrueConditions xor 1
			BeginCond=BeginCond+1
			NegCond=1
		ENDIF
		EndCond=SelectValidCond(@SubStr(<ConditionsString>,BeginCond,@SizeStr(<ConditionsString>)-BeginCond+1))
		IF EndCond EQ 0
			EndCond=@SizeStr(<ConditionsString>)+1
			LogOperator=0
		ELSE
			EndCond=EndCond+BeginCond-1
			LogOperator=EndCond
		ENDIF
		IFIDN @SubStr(<ConditionsString>,BeginCond,1),<(>
			BeginCond=BeginCond+1
			EndCond=EndCond-1
			IF NegCond EQ 1
				IF IsSingleCond(@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)) EQ 1
					IsTrueConditions=IsTrueConditions xor 1
					BeginCond=BeginCond-2
					EndCond=EndCond+1
					NegCond=0
				ENDIF
			ENDIF
		ENDIF
		IF LogOperator EQ 0
			J_POLY_COND LabelName,IsTrueConditions,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
			IF SetLabel NE 0
				locLabel:
			ENDIF
			EndLabel:
			GOTO EndConditions
		ENDIF
		IF SetLabel EQ 0
			IFIDN @SubStr(<ConditionsString>,LogOperator,4),< || >
				IF IsTrueConditions NE 0
					J_POLY_COND LabelName,1,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
					GOTO forward
				ELSE
					J_POLY_COND EndLabel,1,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
					GOTO forward
				ENDIF
			ELSE
				SetLabel=1
				locLabel CATSTR <intermedloc_>,@CatStr(%IntermedLabel)
				IntermedLabel=IntermedLabel+1
				RemnConds SUBSTR <ConditionsString>,LogOperator+4,@SizeStr(<ConditionsString>)-LogOperator-3
				LastConds=1
				IF (@SizeStr(RemnConds) NE 0) AND (SelectOrValidConds(RemnConds) NE 0)
					LastConds=0
				ENDIF
				IF IsTrueConditions EQ 0
					IF LastConds EQ 1
						IF NegCond EQ 1
							J_POLY_COND locLabel,1,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
						ELSE
							J_POLY_COND LabelName,0,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
						ENDIF
						GOTO forward
					ELSE
						J_POLY_COND locLabel,1,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
						GOTO forward
					ENDIF
				ELSE
					IF (LastConds EQ 1) AND (NegCond EQ 1)
						J_POLY_COND LabelName,1,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
						GOTO forward
					ENDIF
					J_POLY_COND locLabel,0,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
				ENDIF
			ENDIF
			GOTO forward
		ELSE
			IFIDN @SubStr(<ConditionsString>,LogOperator,4),< || >
				IF IsTrueConditions NE 0
					J_POLY_COND LabelName,1,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
				ELSE
					J_POLY_COND EndLabel,1,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
				ENDIF
				locLabel:
				SetLabel=0
			ELSEIF IsTrueConditions EQ 0
				IF LastConds EQ 1
					J_POLY_COND LabelName,0,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
					GOTO forward
				ELSE
					J_POLY_COND locLabel,1,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
					GOTO forward
				ENDIF
			ELSE
				J_POLY_COND locLabel,0,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
			ENDIF
		ENDIF
		:forward
		IF NegCond EQ 1
			IsTrueConditions=IsTrueConditions xor 1
			NegCond=0
		ENDIF		
		BeginCond=LogOperator+4
		IF IsSingleCond(@SubStr(<ConditionsString>,BeginCond,@SizeStr(<ConditionsString>)-BeginCond+1)) EQ 1
		%	J_POLY_COND LabelName,IsTrueConditions,@SubStr(<ConditionsString>,BeginCond,@SizeStr(<ConditionsString>)-BeginCond+1)
			IF SetLabel NE 0
				locLabel:
			ENDIF
			EndLabel:
			GOTO EndConditions
		ENDIF
		GOTO NextCond
	ENDIF
:EndConditions
ENDM

PreTestCond0 TEXTEQU <>
PreTestCond1 TEXTEQU <>
PreTestCond2 TEXTEQU <>
PreTestCond3 TEXTEQU <>
PreTestCond4 TEXTEQU <>
PreTestCond5 TEXTEQU <>
PreTestCond6 TEXTEQU <>
PreTestCond7 TEXTEQU <>
PreTestCond8 TEXTEQU <>
PreTestCond9 TEXTEQU <>
PreTestCond10 TEXTEQU <>
PreTestCond11 TEXTEQU <>
PreTestCond12 TEXTEQU <>
PreTestCond13 TEXTEQU <>
PreTestCond14 TEXTEQU <>
PreTestCond15 TEXTEQU <>
PreTestCond16 TEXTEQU <>
PreTestCond17 TEXTEQU <>
PreTestCond18 TEXTEQU <>
PreTestCond19 TEXTEQU <>

.for MACRO PreLoopAction,args,PreTestCondAction:VARARG
	v PreLoopAction
	SaveUntilCondsLabel
	IFDIF <args>,<TRUE>
		jmp LastUntilConds
	ENDIF
	SaveUntilOutLabel
	SaveUntilLabel	
LastUntilLabel:
	while_cnt=while_cnt+1
	IF while_cnt EQ 1
		WhileLevel0 TEXTEQU <args>
		PreTestCond0 TEXTEQU <PreTestCondAction>
		wcond0l SIZESTR <args>
	ELSEIF while_cnt EQ 2
		WhileLevel1 TEXTEQU <args>
		PreTestCond1 TEXTEQU <PreTestCondAction>
		wcond1l SIZESTR <args>
	ELSEIF while_cnt EQ 3
		WhileLevel2 TEXTEQU <args>
		PreTestCond2 TEXTEQU <PreTestCondAction>
		wcond2l SIZESTR <args>
	ELSEIF while_cnt EQ 4
		WhileLevel3 TEXTEQU <args>
		PreTestCond3 TEXTEQU <PreTestCondAction>
		wcond3l SIZESTR <args>
	ELSEIF while_cnt EQ 5
		WhileLevel4 TEXTEQU <args>
		PreTestCond4 TEXTEQU <PreTestCondAction>
		wcond4l SIZESTR <args>
	ELSEIF while_cnt EQ 6
		WhileLevel5 TEXTEQU <args>
		PreTestCond5 TEXTEQU <PreTestCondAction>
		wcond5l SIZESTR <args>
	ELSEIF while_cnt EQ 7
		WhileLevel6 TEXTEQU <args>
		PreTestCond6 TEXTEQU <PreTestCondAction>
		wcond6l SIZESTR <args>
	ELSEIF while_cnt EQ 8
		WhileLevel7 TEXTEQU <args>
		PreTestCond7 TEXTEQU <PreTestCondAction>
		wcond7l SIZESTR <args>
	ELSEIF while_cnt EQ 9
		WhileLevel8 TEXTEQU <args>
		PreTestCond8 TEXTEQU <PreTestCondAction>
		wcond8l SIZESTR <args>
	ELSEIF while_cnt EQ 10
		WhileLevel9 TEXTEQU <args>
		PreTestCond9 TEXTEQU <PreTestCondAction>
		wcond9l SIZESTR <args>
	ELSEIF while_cnt EQ 11
		WhileLevel10 TEXTEQU <args>
		PreTestCond10 TEXTEQU <PreTestCondAction>
		wcond10l SIZESTR <args>
	ELSEIF while_cnt EQ 12
		WhileLevel11 TEXTEQU <args>
		PreTestCond11 TEXTEQU <PreTestCondAction>
		wcond11l SIZESTR <args>
	ELSEIF while_cnt EQ 13
		WhileLevel12 TEXTEQU <args>
		PreTestCond12 TEXTEQU <PreTestCondAction>
		wcond12l SIZESTR <args>
	ELSEIF while_cnt EQ 14
		WhileLevel13 TEXTEQU <args>
		PreTestCond13 TEXTEQU <PreTestCondAction>
		wcond13l SIZESTR <args>
	ELSEIF while_cnt EQ 15
		WhileLevel14 TEXTEQU <args>
		PreTestCond14 TEXTEQU <PreTestCondAction>
		wcond14l SIZESTR <args>
	ELSEIF while_cnt EQ 16
		WhileLevel15 TEXTEQU <args>
		PreTestCond15 TEXTEQU <PreTestCondAction>
		wcond15l SIZESTR <args>
	ELSEIF while_cnt EQ 17
		WhileLevel16 TEXTEQU <args>
		PreTestCond16 TEXTEQU <PreTestCondAction>
		wcond16l SIZESTR <args>
	ELSEIF while_cnt EQ 18
		WhileLevel17 TEXTEQU <args>
		PreTestCond17 TEXTEQU <PreTestCondAction>
		wcond17l SIZESTR <args>
	ELSEIF while_cnt EQ 19
		WhileLevel18 TEXTEQU <args>
		PreTestCond18 TEXTEQU <PreTestCondAction>
		wcond18l SIZESTR <args>
	ELSEIF while_cnt EQ 20
		WhileLevel19 TEXTEQU <args>
		PreTestCond19 TEXTEQU <PreTestCondAction>
		wcond19l SIZESTR <args>
	ELSE
		.err <Nesting level too deep.>
	ENDIF
	EXITM<>
ENDM
.endf MACRO
	IF while_cnt EQ 1
	%	FOR parm,<PreTestCond0>
			v parm
		ENDM
	ELSEIF while_cnt EQ 2
	%	FOR parm,<PreTestCond1>
			v parm
		ENDM
	ELSEIF while_cnt EQ 3
	%	FOR parm,<PreTestCond2>
			v parm
		ENDM
	ELSEIF while_cnt EQ 4
	%	FOR parm,<PreTestCond3>
			v parm
		ENDM
	ELSEIF while_cnt EQ 5
	%	FOR parm,<PreTestCond4>
			v parm
		ENDM
	ELSEIF while_cnt EQ 6
	%	FOR parm,<PreTestCond5>
			v parm
		ENDM
	ELSEIF while_cnt EQ 7
	%	FOR parm,<PreTestCond6>
			v parm
		ENDM
	ELSEIF while_cnt EQ 8
	%	FOR parm,<PreTestCond7>
			v parm
		ENDM
	ELSEIF while_cnt EQ 9
	%	FOR parm,<PreTestCond8>
			v parm
		ENDM
	ELSEIF while_cnt EQ 10
	%	FOR parm,<PreTestCond9>
			v parm
		ENDM
	ELSEIF while_cnt EQ 11
	%	FOR parm,<PreTestCond10>
			v parm
		ENDM
	ELSEIF while_cnt EQ 12
	%	FOR parm,<PreTestCond11>
			v parm
		ENDM
	ELSEIF while_cnt EQ 13
	%	FOR parm,<PreTestCond12>
			v parm
		ENDM
	ELSEIF while_cnt EQ 14
	%	FOR parm,<PreTestCond13>
			v parm
		ENDM
	ELSEIF while_cnt EQ 15
	%	FOR parm,<PreTestCond14>
			v parm
		ENDM
	ELSEIF while_cnt EQ 16
	%	FOR parm,<PreTestCond15>
			v parm
		ENDM
	ELSEIF while_cnt EQ 17
	%	FOR parm,<PreTestCond16>
			v parm
		ENDM
	ELSEIF while_cnt EQ 18
	%	FOR parm,<PreTestCond17>
			v parm
		ENDM
	ELSEIF while_cnt EQ 19
	%	FOR parm,<PreTestCond18>
			v parm
		ENDM
	ELSEIF while_cnt EQ 20
	%	FOR parm,<PreTestCond19>
			v parm
		ENDM
	ENDIF	
	GetUntilCondsLabel
LastUntilConds:
	DelUntilCondsLabel
	GetUntilLabel
	IF (while_cnt EQ 1) AND (wcond0l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel0
	ELSEIF (while_cnt EQ 2) AND (wcond1l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel1
	ELSEIF (while_cnt EQ 3) AND (wcond2l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel2
	ELSEIF (while_cnt EQ 4) AND (wcond3l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel3
	ELSEIF (while_cnt EQ 5) AND (wcond4l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel4
	ELSEIF (while_cnt EQ 6) AND (wcond5l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel5
	ELSEIF (while_cnt EQ 7) AND (wcond6l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel6
	ELSEIF (while_cnt EQ 8) AND (wcond7l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel7
	ELSEIF (while_cnt EQ 9) AND (wcond8l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel8
	ELSEIF (while_cnt EQ 10) AND (wcond9l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel9
	ELSEIF (while_cnt EQ 11) AND (wcond10l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel10
	ELSEIF (while_cnt EQ 12) AND (wcond11l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel11
	ELSEIF (while_cnt EQ 13) AND (wcond12l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel12
	ELSEIF (while_cnt EQ 14) AND (wcond13l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel13
	ELSEIF (while_cnt EQ 15) AND (wcond14l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel14
	ELSEIF (while_cnt EQ 16) AND (wcond15l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel15
	ELSEIF (while_cnt EQ 17) AND (wcond16l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel16
	ELSEIF (while_cnt EQ 18) AND (wcond17l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel17
	ELSEIF (while_cnt EQ 19) AND (wcond18l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel18
	ELSEIF (while_cnt EQ 20) AND (wcond19l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel19
	ENDIF
	DelUntilLabel
	GetUntilOutLabel
LastUntilOutLabel:
	DelUntilOutLabel
	while_cnt=while_cnt-1
ENDM