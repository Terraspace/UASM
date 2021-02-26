/* operand classes. Introduced with v2.06, when the operand types were removed
 * from the instruction table and replaced by a class index.
 * As a result, it's easier and won't bloat the instruction table if the
 * third operand is extended or a 4th operand ( for AVX ) is added.
 */
OpCls( NONE,     NONE,       NONE  )
OpCls( AX,       NONE,       NONE  ) /* FSTSW */
OpCls( I,        NONE,       NONE  )
OpCls( I16,      NONE,       NONE  )
OpCls( I32,      NONE,       NONE  )
OpCls( I48,      NONE,       NONE  )
OpCls( I8,       NONE,       NONE  )
OpCls( I8_U,     NONE,       NONE  )
OpCls( I_3,      NONE,       NONE  )
OpCls( M08,      NONE,       NONE  )
OpCls( M16,      NONE,       NONE  )
OpCls( M16_M32,  NONE,       NONE  )
#if AMD64_SUPPORT
OpCls( M16_M64,  NONE,       NONE  )
#endif
OpCls( M32,      NONE,       NONE  )
OpCls( M48,      NONE,       NONE  )
OpCls( M64,      NONE,       NONE  )
OpCls( M80,      NONE,       NONE  )
#if AMD64_SUPPORT
OpCls( M128,     NONE,       NONE  )
#endif
OpCls( MGT8,     NONE,       NONE  )
OpCls( MS,       NONE,       NONE  )
OpCls( M_ANY,    NONE,       NONE  )
OpCls( R,        NONE,       NONE  )
OpCls( R16_M16,  NONE,       NONE  )
OpCls( R16_R32,  NONE,       NONE  )
OpCls( R32,      NONE,       NONE  )
#if AMD64_SUPPORT
OpCls( R64,      NONE,       NONE  )
OpCls( R64_M64,  NONE,       NONE  )
OpCls( R16_R64,  NONE,       NONE  )
#endif
OpCls( R8_M08,   NONE,       NONE  )
OpCls( RGT16,    NONE,       NONE  )
OpCls( RGT8,     NONE,       NONE  )
OpCls( SR,       NONE,       NONE  )
OpCls( SR86,     NONE,       NONE  )
#if AMD64_SUPPORT
OpCls( SR386,    NONE,       NONE  )
#endif
OpCls( STI,      NONE,       NONE  )
OpCls( A,        DX_ONLY,    NONE  )
OpCls( A,        I,          NONE  )
OpCls( A,        I8_U,       NONE  )
OpCls( A,        MS,         NONE  )
OpCls( A,        RGT8,       NONE  )
OpCls( DX_ONLY,  A,          NONE  )
OpCls( DX_ONLY,  M08,        NONE  )
OpCls( DX_ONLY,  M16,        NONE  )
OpCls( DX_ONLY,  M32,        NONE  )
OpCls( DX_ONLY,  MS,         NONE  )
OpCls( I16,      I8_U,       NONE  )
OpCls( I8_U,     A,          NONE  )
OpCls( M08,      DX_ONLY,    NONE  )
OpCls( M08,      M08,        NONE  )
OpCls( M16,      DX_ONLY,    NONE  )
OpCls( M16,      M16,        NONE  )
OpCls( M32,      DX_ONLY,    NONE  )
OpCls( M32,      M32,        NONE  )
OpCls( M32,      XMM,        NONE  )
#if AMD64_SUPPORT
OpCls( M64,      M64,        NONE  )
#endif
OpCls( M64,      MMX,        NONE  )
OpCls( M64,      XMM,        NONE  )
OpCls( M128,     XMM,        NONE  )
#if AVXSUPP
OpCls( M256,     YMM,        NONE  )

#endif
OpCls( MGT16,    RGT16,      NONE  )
OpCls( MGT8,     I8,         NONE  )
OpCls( MGT8,     I8_U,       NONE  )
OpCls( MGT8,     RGT8,       NONE  )
OpCls( MMX,      I8_U,       NONE  )
OpCls( MMX,      MMX,        NONE  )
OpCls( MMX,      MMX_M64,    NONE  )
#if MASM_SSE_MEMX
OpCls( MMX,      MMX_M64_08, NONE  )
OpCls( MMX,      MMX_M64_16, NONE  )
OpCls( MMX,      MMX_M64_32, NONE  )
#endif

OpCls( MMX,      RMGT16,     NONE  )  /* MOVD, CVTSI2SD, CVTSI2SS */
OpCls( MMX,      XMM,        NONE  )
OpCls( MMX,      XMM_M64,    NONE  )
OpCls( MMX,      XMM_M128,   NONE  )
OpCls( MS,       A,          NONE  )
OpCls( MS,       DX_ONLY,    NONE  )
OpCls( MS,       I,          NONE  )
OpCls( MS,       MS,         NONE  )
OpCls( MS,       R,          NONE  )
OpCls( MS,       SR,         NONE  )
OpCls( R,        I,          NONE  )
OpCls( R,        MS,         NONE  )
OpCls( R,        R,          NONE  )
OpCls( R,        R_MS,       NONE  )
OpCls( R16_M16,  R16,        NONE  )
OpCls( R16_R32,  I,          NONE  )
#if AMD64_SUPPORT
OpCls( R64,      I,          NONE  )
OpCls( R64,      I64,        NONE  )
OpCls( R64,      R32_M32,    NONE  )
#endif

OpCls( R8,       I,          NONE  )
OpCls( RGT16,    MMX,        NONE  )
OpCls( RGT16,    R8_M08,     NONE  )
OpCls( RGT16,    RGT8_MS,    NONE  )
OpCls( RGT16,    RSPEC,      NONE  )
OpCls( RGT16,    XMM,        NONE  )
#if AVXSUPP
OpCls( RGT16,    YMM,        NONE  ) /* v2.11 */
#endif
OpCls( RGT16,    XMM_M32,    NONE  )
OpCls( RGT16,    XMM_M64,    NONE  )
#if VMXSUPP
OpCls( R32,      R32_M32,    NONE  )
OpCls( R32_M32,  R32,        NONE  )
OpCls( RGT16,    M128,       NONE  )
#if AMD64_SUPPORT
OpCls( R64,      R64_M64,    NONE  )
OpCls( R64_M64,  R64,        NONE  )
#endif
#endif
#if SVMSUPP
OpCls( A,        NONE,       NONE  )  /* VMRUN rAX */
OpCls( A,        R32,        NONE  )  /* INVLPGA rAX, ECX */
#endif
OpCls( RGT8,     A,          NONE  )
OpCls( RGT8,     I,          NONE  )
OpCls( RGT8,     I8,         NONE  )
OpCls( RGT8,     I8_U,       NONE  )
OpCls( RGT8,     MFPTR,      NONE  )
OpCls( RGT8,     MS,         NONE  )
OpCls( RGT8,     RGT8,       NONE  )
OpCls( RGT8,     RGT8_MS,    NONE  )
OpCls( RGT8,     R_MS,       NONE  )
OpCls( RGT8,     SR,         NONE  )
#if INTELMOVQ
OpCls( R32_M32,  MMX,        NONE  )
OpCls( R32_M32,  XMM,        NONE  )
OpCls( R64_M64,  MMX,        NONE  )
OpCls( R64_M64,  XMM,        NONE  )
#else
OpCls( RMGT16,   MMX,        NONE  )
OpCls( RMGT16,   XMM,        NONE  )
#endif
OpCls( RSPEC,    RGT16,      NONE  )
OpCls( R_MS,     CL_ONLY,    NONE  )
OpCls( R_MS,     I,          NONE  )
OpCls( R_MS,     I8_U,       NONE  )
OpCls( R_MS,     I_1,        NONE  )
OpCls( SR,       MS,         NONE  )
OpCls( SR,       RGT8,       NONE  )
OpCls( ST,       STI,        NONE  )
OpCls( STI,      ST,         NONE  )
OpCls( XMM,      I8_U,       NONE  )

OpCls( XMM,      M64,        NONE  )
OpCls( XMM,      M128,       NONE  )
OpCls( XMM,      MMX,        NONE  )
OpCls( XMM,      MMX_M64,    NONE  )
OpCls( XMM,      RMGT16,     NONE  )
OpCls( XMM,      XMM,        NONE  )
OpCls( XMM,      XMM_M16,    NONE  )
OpCls( XMM,      XMM_M32,    NONE  )
OpCls( XMM,      XMM_M64,    NONE  )
OpCls( XMM,      XMM_M128,   NONE  )
#if MASM_SSE_MEMX
OpCls( XMM,      XMM_M128_08, NONE  )
OpCls( XMM,      XMM_M128_16, NONE  )
OpCls( XMM,      XMM_M128_32, NONE  )
OpCls( XMM,      XMM_M128_64, NONE  )
#endif
#if AVXSUPP
OpCls( XMM,      YMM_M256,   NONE  )
OpCls( YMM,      XMM_M32,    NONE  )  //AVX2,habran
OpCls( YMM,      M128,       NONE  )
OpCls( YMM,      XMM_M128,   NONE  )  //AVX2,habran
OpCls( YMM,      XMM_M64,    NONE  )  //AVX2,habran
OpCls(ZMM_M32, NONE,     NONE )
OpCls(ZMM_M64, NONE,     NONE )
OpCls(YMM_M32, NONE,     NONE )
//OpCls( ZMM,      XMM_M128,   NONE  )  //AVX2,habran
//OpCls( ZMM,      YMM_M256,   NONE  )  //AVX2,habran
OpCls( XMM_M128,I8_U,  NONE)
OpCls( YMM,      YMM_M256,   NONE  )
OpCls( XMM,      XMM_M32,    XMM )
OpCls( XMM,      XMM_M64,    XMM )
#endif
OpCls( M16,      XMM,        I8_U  )
OpCls( M32,      XMM,        I8_U  )
OpCls( MMX,      MMX_M64,    I8_U  )
OpCls( MMX,      R32_M16,    I8_U  ) /* PINSRW */
OpCls( R32_M32,  XMM,        I8_U  )
#if AMD64_SUPPORT
OpCls( R64_M64,  XMM,        I8_U  )
#endif
OpCls( RGT16,    MMX,        I8_U  )
OpCls( RGT16,    XMM,        I8_U  )
OpCls( RGT16_M08,XMM,        I8_U  )
OpCls( RGT8,     R_MS,       I     )
OpCls( RGT8,     R_MS,       I8_U  )
OpCls( RGT8_MGT8,RGT8,       CL    )
OpCls( RGT8_MGT8,RGT8,       I8_U  )
OpCls( XMM,      I8_U,       I8_U  )
OpCls( XMM,      R32_M16,    I8_U  ) /* PINSRW */
OpCls( XMM,      R32_M08,    I8_U  ) /* PINSRB */
OpCls( XMM,      R32_M32,    I8_U  ) /* PINSRD */
#if AMD64_SUPPORT
OpCls( XMM,      R64_M64,    I8_U  )
#endif
OpCls( XMM,      XMM,        I8_U  )
OpCls( XMM,      XMM_M32 ,   HID   )
OpCls( XMM,      XMM_M64 ,   HID   )
OpCls( XMM,      XMM_M128,   HID   )
OpCls( XMM,      XMM_M32 ,   I8_U  )
OpCls( XMM,      XMM_M64 ,   I8_U  )
OpCls( XMM,      XMM_M128,   I8_U  )
OpCls( XMM,      XMM_M128,   XMM0  )
#if AVXSUPP
OpCls( M128,  YMM,       I8_U )
OpCls( XMM,   XMM_M128,   XMM )
OpCls( XMM,    YMM,      I8_U )
OpCls( YMM,  YMM_M256,   I8_U )
OpCls(XMM_M128,    XMM,  NONE )
OpCls(XMM, XMM_M128_M32, NONE ) //VGETEXPPS
OpCls(XMM, XMM_M128_M64, NONE ) //VGETEXPPD
OpCls(XMM, XMM,      XMM_M128 )
OpCls( XMM,   R32_M32,   NONE )
OpCls( R32_M32,   XMM,   NONE )
OpCls( R64_M64,   XMM,   NONE )
OpCls( XMM_M_ANY, XMM,   NONE )
OpCls( R64,    XMM_M64,  NONE )
OpCls( R32,    XMM_M64,  NONE )
OpCls( K,      K,        K    )
OpCls( K,      K,        NONE )
OpCls( K,      K,        I8_U )
OpCls( M08,    K,        NONE )
OpCls( M16,    K,        NONE )
OpCls( M32,    K,        NONE )
OpCls( M64,    K,        NONE )
OpCls( R32,    K,        NONE )
OpCls( R64,    K,        NONE )
OpCls( K,      M08,      NONE )
OpCls( K,      M16,      NONE )
OpCls( K,      M32,      NONE )
OpCls( K,      M64,      NONE )
OpCls( K,      R32,      NONE )
OpCls( K,      R64,      NONE )
OpCls(ZMM,     XMM_M32,  NONE )
OpCls(ZMM,     XMM_M64,  NONE )
OpCls(XMM,     R8,       NONE )
OpCls(XMM,     XMM_M08,  NONE )
OpCls(XMM,     R16,      NONE )
OpCls(XMM,     R32,      NONE )
OpCls(XMM,     R64,      NONE )
OpCls(ZMM,     M128,     NONE )
OpCls(ZMM,     M256,     NONE )
OpCls( YMM,    ZMM,      I8_U )
OpCls( M256,   ZMM,      I8_U )
OpCls(XMM_M32, XMM,      NONE )
OpCls( R32,    XMM_M32,  NONE )
OpCls( R64,    XMM_M32,  NONE )
OpCls( XMM,    R64_M64,  NONE )
OpCls( XMM_M128,    YMM, I8_U )
OpCls( XMM,    ZMM,      I8_U )
OpCls( M128,   ZMM,      I8_U )
OpCls( R,      R_MS,     I8_U )
OpCls( R,      R,        R_MS )
OpCls( R,      R_MS,        R )
#endif
OpCls( BND,      MS,       NONE )
OpCls( BND,      R_MS,     NONE )
OpCls( BND,      BND_MS,   NONE )
OpCls( BND,      BND_M128, NONE )
OpCls( BND_MS,   BND,      NONE )
OpCls( BND_M128, BND,      NONE )
OpCls( MS,       BND,      NONE )
OpCls( R32,      R32,      NONE )
OpCls( R64,      R64,      NONE )
OpCls( R32,      M32,      NONE )
OpCls( R64,      M64,      NONE )
OpCls( R32,      M64,      NONE )
OpCls( RGT8,     MGT8,     NONE )

OpCls( R64_M64,  MMX,      NONE)
OpCls( MMX,      R64_M64,  NONE)
OpCls( R64,      MMX,      NONE)
