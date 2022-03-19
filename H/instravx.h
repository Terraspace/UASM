/****************************************************************************
*
* Description:  AVX instructions with VEX prefix
*
****************************************************************************/

#if AVXSUPP
/*   tok                         cpu */
/* format: xmm|ymm, xmm|ymm|mem */
//     token,     string,         cpu,  flgs ) T_V ## token ,
avxins (ADDPD,    vaddpd,        P_AVX, VX_LL|VX_L ) /* L, s */
avxins (ADDSD,    vaddsd,        P_AVX, VX_LL )    /* -, s */
avxins (DIVPD,    vdivpd,        P_AVX, VX_LL|VX_L ) /* L, s */
avxins (DIVSD,    vdivsd,        P_AVX, VX_LL )    /* -, s */
avxins (MAXPD,    vmaxpd,        P_AVX, VX_LL|VX_L ) /* L, s */
avxins (MAXSD,    vmaxsd,        P_AVX, VX_LL )    /* -, s */
avxins (MINPD,    vminpd,        P_AVX, VX_LL|VX_L ) /* L, s */
avxins (MINSD,    vminsd,        P_AVX, VX_LL )    /* -, s */
avxins (MULPD,    vmulpd,        P_AVX, VX_LL|VX_L ) /* L, s */
avxins (MULSD,    vmulsd,        P_AVX, VX_LL )    /* -, s */
avxins (SQRTPD,   vsqrtpd,       P_AVX, VX_LL|VX_L|VX_NND ) /* L, ns */
avxins (SQRTSD,   vsqrtsd,       P_AVX, VX_LL|VX_LL )    /* -, s */
avxins (SUBPD,    vsubpd,        P_AVX, VX_LL|VX_L ) /* L, s */
avxins (SUBSD,    vsubsd,        P_AVX, VX_LL )    /* -, s */
avxins (ADDPS,    vaddps,        P_AVX, VX_LL|VX_L ) /* L, s */
avxins (ADDSS,    vaddss,        P_AVX, VX_LL )    /* -, s */
avxins (DIVPS,    vdivps,        P_AVX, VX_LL|VX_L ) /* L, s */
avxins (DIVSS,    vdivss,        P_AVX, VX_LL )    /* -, s */
avxins (MAXPS,    vmaxps,        P_AVX, VX_LL|VX_L ) /* L, s */
avxins (MAXSS,    vmaxss,        P_AVX, VX_LL|VX_LL )    /* -, s */
avxins (MINPS,    vminps,        P_AVX, VX_LL|VX_L ) /* L, s */
avxins (MINSS,    vminss,        P_AVX, VX_LL )    /* -, s */
avxins (MULPS,    vmulps,        P_AVX, VX_LL|VX_L ) /* L, s */
avxins (MULSS,    vmulss,        P_AVX, VX_LL|VX_LL )    /* -, s */
avxins (SQRTPS,   vsqrtps,       P_AVX, VX_LL|VX_L|VX_NND ) /* L, ns */
avxins (SQRTSS,   vsqrtss,       P_AVX, VX_LL )    /* -, s */
avxins (SUBPS,    vsubps,        P_AVX, VX_LL|VX_L ) /* L, s */
avxins (SUBSS,    vsubss,        P_AVX, VX_LL )    /* -, s */
avxins (CMPPD,    vcmppd,        P_AVX, VX_LL|VX_L|VX_HALF ) /* L, s */
avxins (CMPSD,    vcmpsd,        P_AVX, VX_LL|VX_HALF )    /* -, s */
avxins (CMPPS,    vcmpps,        P_AVX, VX_LL|VX_L|VX_HALF ) /* L, s */
avxins (CMPSS,    vcmpss,        P_AVX, VX_LL |VX_HALF)    /* -, s */

/* added by habran                                      */
avxins (CMPEQPD,      vcmpeqpd,        P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPLTPD,      vcmpltpd,        P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPLEPD,      vcmplepd,        P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPUNORDPD,   vcmpunordpd,     P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNEQPD,     vcmpneqpd,       P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNLTPD,     vcmpnltpd,       P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNLEPD,     vcmpnlepd,       P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPORDPD,     vcmpordpd,       P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPEQ_UQPD,   vcmpeq_uqpd,     P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNGEPD,     vcmpngepd,       P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNGTPD,     vcmpngtpd,       P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPFALSEPD,   vcmpfalsepd,     P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNEQ_OQPD,  vcmpneq_oqpd,    P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPGEPD,      vcmpgepd,        P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPGTPD,      vcmpgtpd,        P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPTRUEPD,    vcmptruepd,      P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPEQ_OSPD,   vcmpeq_ospd,     P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPLT_OQPD,   vcmplt_oqpd,     P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPLE_OQPD,   vcmple_oqpd,     P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPUNORD_SPD, vcmpunord_spd,   P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNEQ_USPD,  vcmpneq_uspd,    P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNLT_UQPD,  vcmpnlt_uqpd,    P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNLE_UQPD,  vcmpnle_uqpd,    P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPORD_SPD,   vcmpord_spd,     P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPEQ_USPD,   vcmpeq_uspd,     P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNGE_UQPD,  vcmpnge_uqpd,    P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNGT_UQPD,  vcmpngt_uqpd,    P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPFALSE_OSPD,vcmpfalse_ospd,  P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNEQ_OSPD,  vcmpneq_ospd,    P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPGE_OQPD,   vcmpge_oqpd,     P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPGT_OQPD,   vcmpgt_oqpd,     P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPTRUE_USPD, vcmptrue_uspd,   P_AVX, VX_LL|VX_L ) /* L, s */

avxins (CMPEQPS,      vcmpeqps,        P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPLTPS,      vcmpltps,        P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPLEPS,      vcmpleps,        P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPUNORDPS,   vcmpunordps,     P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNEQPS,     vcmpneqps,       P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNLTPS,     vcmpnltps,       P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNLEPS,     vcmpnleps,       P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPORDPS,     vcmpordps,       P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPEQ_UQPS,   vcmpeq_uqps,     P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNGEPS,     vcmpngeps,       P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNGTPS,     vcmpngtps,       P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPFALSEPS,   vcmpfalseps,     P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNEQ_OQPS,  vcmpneq_oqps,    P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPGEPS,      vcmpgeps,        P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPGTPS,      vcmpgtps,        P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPTRUEPS,    vcmptrueps,      P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPEQ_OSPS,   vcmpeq_osps,     P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPLT_OQPS,   vcmplt_oqps,     P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPLE_OQPS,   vcmple_oqps,     P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPUNORD_SPS, vcmpunord_sps,   P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNEQ_USPS,  vcmpneq_usps,    P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNLT_UQPS,  vcmpnlt_uqps,    P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNLE_UQPS,  vcmpnle_uqps,    P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPORD_SPS,   vcmpord_sps,     P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPEQ_USPS,   vcmpeq_usps,     P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNGE_UQPS,  vcmpnge_uqps,    P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNGT_UQPS,  vcmpngt_uqps,    P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPFALSE_OSPS,vcmpfalse_osps,  P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPNEQ_OSPS,  vcmpneq_osps,    P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPGE_OQPS,   vcmpge_oqps,     P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPGT_OQPS,   vcmpgt_oqps,     P_AVX, VX_LL|VX_L ) /* L, s */
avxins (CMPTRUE_USPS, vcmptrue_usps,   P_AVX, VX_LL|VX_L ) /* L, s */

avxins (CMPEQSD,      vcmpeqsd,        P_AVX, VX_LL     ) /* -, s */
avxins (CMPLTSD,      vcmpltsd,        P_AVX, VX_LL     ) /* -, s */
avxins (CMPLESD,      vcmplesd,        P_AVX, VX_LL     ) /* -, s */
avxins (CMPUNORDSD,   vcmpunordsd,     P_AVX, VX_LL     ) /* -, s */
avxins (CMPNEQSD,     vcmpneqsd,       P_AVX, VX_LL     ) /* -, s */
avxins (CMPNLTSD,     vcmpnltsd,       P_AVX, VX_LL     ) /* -, s */
avxins (CMPNLESD,     vcmpnlesd,       P_AVX, VX_LL     ) /* -, s */
avxins (CMPORDSD,     vcmpordsd,       P_AVX, VX_LL     ) /* -, s */
avxins (CMPEQ_UQSD,   vcmpeq_uqsd,     P_AVX, VX_LL     ) /* -, s */
avxins (CMPNGESD,     vcmpngesd,       P_AVX, VX_LL     ) /* -, s */
avxins (CMPNGTSD,     vcmpngtsd,       P_AVX, VX_LL     ) /* -, s */
avxins (CMPFALSESD,   vcmpfalsesd,     P_AVX, VX_LL     ) /* -, s */
avxins (CMPNEQ_OQSD,  vcmpneq_oqsd,    P_AVX, VX_LL     ) /* -, s */
avxins (CMPGESD,      vcmpgesd,        P_AVX, VX_LL     ) /* -, s */
avxins (CMPGTSD,      vcmpgtsd,        P_AVX, VX_LL     ) /* -, s */
avxins (CMPTRUESD,    vcmptruesd,      P_AVX, VX_LL     ) /* -, s */
avxins (CMPEQ_OSSD,   vcmpeq_ossd,     P_AVX, VX_LL     ) /* -, s */
avxins (CMPLT_OQSD,   vcmplt_oqsd,     P_AVX, VX_LL     ) /* -, s */
avxins (CMPLE_OQSD,   vcmple_oqsd,     P_AVX, VX_LL     ) /* -, s */
avxins (CMPUNORD_SSD, vcmpunord_ssd,   P_AVX, VX_LL     ) /* -, s */
avxins (CMPNEQ_USSD,  vcmpneq_ussd,    P_AVX, VX_LL     ) /* -, s */
avxins (CMPNLT_UQSD,  vcmpnlt_uqsd,    P_AVX, VX_LL     ) /* -, s */
avxins (CMPNLE_UQSD,  vcmpnle_uqsd,    P_AVX, VX_LL     ) /* -, s */
avxins (CMPORD_SSD,   vcmpord_ssd,     P_AVX, VX_LL     ) /* -, s */
avxins (CMPEQ_USSD,   vcmpeq_ussd,     P_AVX, VX_LL     ) /* -, s */
avxins (CMPNGE_UQSD,  vcmpnge_uqsd,    P_AVX, VX_LL     ) /* -, s */
avxins (CMPNGT_UQSD,  vcmpngt_uqsd,    P_AVX, VX_LL     ) /* -, s */
avxins (CMPFALSE_OSSD,vcmpfalse_ossd,  P_AVX, VX_LL     ) /* -, s */
avxins (CMPNEQ_OSSD,  vcmpneq_ossd,    P_AVX, VX_LL     ) /* -, s */
avxins (CMPGE_OQSD,   vcmpge_oqsd,     P_AVX, VX_LL     ) /* -, s */
avxins (CMPGT_OQSD,   vcmpgt_oqsd,     P_AVX, VX_LL     ) /* -, s */
avxins (CMPTRUE_USSD, vcmptrue_ussd,   P_AVX, VX_LL     ) /* -, s */

avxins (CMPEQSS,      vcmpeqss,        P_AVX, VX_LL     ) /* -, s */
avxins (CMPLTSS,      vcmpltss,        P_AVX, VX_LL     ) /* -, s */
avxins (CMPLESS,      vcmpless,        P_AVX, VX_LL     ) /* -, s */
avxins (CMPUNORDSS,   vcmpunordss,     P_AVX, VX_LL     ) /* -, s */
avxins (CMPNEQSS,     vcmpneqss,       P_AVX, VX_LL     ) /* -, s */
avxins (CMPNLTSS,     vcmpnltss,       P_AVX, VX_LL     ) /* -, s */
avxins (CMPNLESS,     vcmpnless,       P_AVX, VX_LL     ) /* -, s */
avxins (CMPORDSS,     vcmpordss,       P_AVX, VX_LL     ) /* -, s */
avxins (CMPEQ_UQSS,   vcmpeq_uqss,     P_AVX, VX_LL     ) /* -, s */
avxins (CMPNGESS,     vcmpngess,       P_AVX, VX_LL     ) /* -, s */
avxins (CMPNGTSS,     vcmpngtss,       P_AVX, VX_LL     ) /* -, s */
avxins (CMPFALSESS,   vcmpfalsess,     P_AVX, VX_LL     ) /* -, s */
avxins (CMPNEQ_OQSS,  vcmpneq_oqss,    P_AVX, VX_LL     ) /* -, s */
avxins (CMPGESS,      vcmpgess,        P_AVX, VX_LL     ) /* -, s */
avxins (CMPGTSS,      vcmpgtss,        P_AVX, VX_LL     ) /* -, s */
avxins (CMPTRUESS,    vcmptruess,      P_AVX, VX_LL     ) /* -, s */
avxins (CMPEQ_OSSS,   vcmpeq_osss,     P_AVX, VX_LL     ) /* -, s */
avxins (CMPLT_OQSS,   vcmplt_oqss,     P_AVX, VX_LL     ) /* -, s */
avxins (CMPLE_OQSS,   vcmple_oqss,     P_AVX, VX_LL     ) /* -, s */
avxins (CMPUNORD_SSS, vcmpunord_sss,   P_AVX, VX_LL     ) /* -, s */
avxins (CMPNEQ_USSS,  vcmpneq_usss,    P_AVX, VX_LL     ) /* -, s */
avxins (CMPNLT_UQSS,  vcmpnlt_uqss,    P_AVX, VX_LL     ) /* -, s */
avxins (CMPNLE_UQSS,  vcmpnle_uqss,    P_AVX, VX_LL     ) /* -, s */
avxins (CMPORD_SSS,   vcmpord_sss,     P_AVX, VX_LL     ) /* -, s */
avxins (CMPEQ_USSS,   vcmpeq_usss,     P_AVX, VX_LL     ) /* -, s */
avxins (CMPNGE_UQSS,  vcmpnge_uqss,    P_AVX, VX_LL     ) /* -, s */
avxins (CMPNGT_UQSS,  vcmpngt_uqss,    P_AVX, VX_LL     ) /* -, s */
avxins (CMPFALSE_OSSS,vcmpfalse_osss,  P_AVX, VX_LL     ) /* -, s */
avxins (CMPNEQ_OSSS,  vcmpneq_osss,    P_AVX, VX_LL     ) /* -, s */
avxins (CMPGE_OQSS,   vcmpge_oqss,     P_AVX, VX_LL     ) /* -, s */
avxins (CMPGT_OQSS,   vcmpgt_oqss,     P_AVX, VX_LL     ) /* -, s */
avxins (CMPTRUE_USSS, vcmptrue_usss,   P_AVX, VX_LL     ) /* -, s */
                                               
/* format: xmm|ymm, xmm|ymm|mem */
avxins (ANDPD,    vandpd,        P_AVX, VX_LL|VX_L )   /* L, s */
avxins (ANDNPD,   vandnpd,       P_AVX, VX_LL|VX_L )   /* L, s */
avxins (ORPD,     vorpd,         P_AVX, VX_LL|VX_L )   /* L, s */
avxins (COMISD,   vcomisd,       P_AVX, VX_LL|VX_NND ) /* -, ns */
avxins (XORPD,    vxorpd,        P_AVX, VX_LL|VX_L )   /* L, s */
avxins (ANDPS,    vandps,        P_AVX, VX_LL|VX_L )   /* L, s */
avxins (ANDNPS,   vandnps,       P_AVX, VX_LL|VX_L )   /* L, s */
avxins (ORPS,     vorps,         P_AVX, VX_LL|VX_L )   /* L, s */
avxins (COMISS,   vcomiss,       P_AVX, VX_LL|VX_NND ) /* -, ns */
avxins (XORPS,    vxorps,        P_AVX, VX_LL|VX_L )   /* L, s */
                                        
/* format: xmm|ymm, xmm|ymm|mem */     
avxins (CVTDQ2PD, vcvtdq2pd,     P_AVX, VX_LL|VX_L|VX_NND|VX_HALF ) /* L, ns, 64->128 */
avxins (CVTDQ2PS, vcvtdq2ps,     P_AVX, VX_LL|VX_L|VX_NND ) /* L, ns */     
//avxins (CVTPD2DQ, vcvtpd2dq,   P_AVX, VX_LL|VX_L|VX_NND ) /* L, ns */  
//avxins (CVTTPD2DQ,vcvttpd2dq,  P_AVX, VX_LL|VX_L|VX_NND ) /* L, ns */
//avxins (CVTPD2PS, vcvtpd2ps,   P_AVX, VX_LL|VX_L|VX_NND ) /* L, ns */
avxins (CVTPS2DQ, vcvtps2dq,     P_AVX, VX_LL|VX_L|VX_NND ) /* L, ns */
avxins (CVTTPS2DQ,vcvttps2dq,    P_AVX, VX_LL|VX_L|VX_NND ) /* L, ns */
avxins (CVTPS2PD, vcvtps2pd,     P_AVX, VX_LL|VX_L|VX_NND|VX_HALF ) /* L, ns, 64->128 */
avxins (CVTSD2SI, vcvtsd2si,     P_AVX, VX_LL|VX_NND )   /* -, ns, W */
avxins (CVTTSD2SI,vcvttsd2si,    P_AVX, VX_LL|VX_NND )   /* -, ns, W */
avxins (CVTSD2SS, vcvtsd2ss,     P_AVX, VX_LL )        /* -, s     */
//avxins (CVTSI2SD, vcvtsi2sd,   P_AVX, VX_LL )        /* -, s,  W */
avxins (CVTSI2SS, vcvtsi2ss,     P_AVX, VX_LL )        /* -, s,  W */
avxins (CVTSS2SD, vcvtss2sd,     P_AVX, VX_LL )        /* -, s     */
avxins (CVTSS2SI, vcvtss2si,     P_AVX, VX_LL|VX_NND )   /* -, ns, W */
avxins (CVTTSS2SI,vcvttss2si,    P_AVX, VX_LL|VX_NND )   /* -, ns, W */

/* format: xmm|ymm, xmm|ymm|mem [, i8] */
avxins (ADDSUBPD, vaddsubpd,     P_AVX, VX_L )     /* L, s */
avxins (ADDSUBPS, vaddsubps,     P_AVX, VX_L )     /* L, s */
avxins (BLENDPD , vblendpd ,     P_AVX, VX_L )     /* L, s */
avxins (BLENDPS , vblendps ,     P_AVX, VX_L )     /* L, s */
avxins (DPPD    , vdppd    ,     P_AVX, 0 )        /* -, s */
avxins (DPPS    , vdpps    ,     P_AVX, VX_L )     /* L, s */
avxins (EXTRACTPS,vextractps,    P_AVX, VX_LL|VX_NND )   /* -, ns! */ /* format: reg|mem32, xmm|ymm, i8 */
avxins (HADDPD  , vhaddpd  ,     P_AVX, VX_L )     /* L, s */
avxins (HADDPS  , vhaddps  ,     P_AVX, VX_L )     /* L, s */
avxins (HSUBPD  , vhsubpd  ,     P_AVX, VX_L )     /* L, s */
avxins (HSUBPS  , vhsubps  ,     P_AVX, VX_L )     /* L, s */
avxins (INSERTPS, vinsertps,     P_AVX, VX_LL )        /* -, s */
avxins (LDDQU   , vlddqu   ,     P_AVX, VX_L|VX_NND ) /* L, ns */ /* format: xmm|ymm, mem */
avxins (LDMXCSR , vldmxcsr ,     P_AVX, 0 )        /* -, ns */ /* format: mem32 */
avxins (STMXCSR , vstmxcsr ,     P_AVX, 0 )        /* -, ns */ /* format: mem32 */

avxins (MASKMOVDQU,vmaskmovdqu,  P_AVX, VX_NND )   /* -, ns */
avxins (MOVAPD  , vmovapd  ,     P_AVX, VX_LL|VX_L|VX_NND ) /* L, ns */
avxins (MOVAPS  , vmovaps  ,     P_AVX, VX_LL|VX_L|VX_NND ) /* L, ns */
/* v2.13: now handled in instruct.h */
avxins (MOVD    , vmovd    ,     P_AVX, VX_LL|VX_NND )   /* -, ns */
avxins (MOVQ    , vmovq    ,     P_AVX, VX_LL|VX_NND )   /* -, ns */
avxins (MOVDQA  , vmovdqa  ,     P_AVX, VX_LL|VX_L|VX_NND ) /* L, ns */
avxins (MOVDQU  , vmovdqu  ,     P_AVX, VX_LL|VX_L|VX_NND ) /* L, ns */
avxins (MOVHLPS , vmovhlps ,     P_AVX, VX_LL )        /* -, s */
avxins (MOVLHPS , vmovlhps ,     P_AVX, VX_LL )        /* -, s */
avxins (MOVHPD  , vmovhpd  ,     P_AVX, VX_LL|VX_NMEM )  /* -, s/ns! */
avxins (MOVHPS  , vmovhps  ,     P_AVX, VX_LL|VX_NMEM )  /* -, s/ns! */
avxins (MOVLPD  , vmovlpd  ,     P_AVX, VX_LL|VX_NMEM )  /* -, s/ns! */
avxins (MOVLPS  , vmovlps  ,     P_AVX, VX_LL|VX_NMEM )  /* -, s/ns! */
avxins (MOVSD   , vmovsd   ,     P_AVX, VX_LL|VX_NMEM )  /* -, s/ns! */ /* special case, see parser.c */
avxins (MOVSS   , vmovss   ,     P_AVX, VX_LL|VX_NMEM )  /* -, s/ns! */ /* special case, see parser.c */
/* v2.11: now handled in instruct.h */
avxins (MOVMSKPD, vmovmskpd,     P_AVX, VX_L|VX_NND ) /* L, ns */
avxins (MOVMSKPS, vmovmskps,     P_AVX, VX_L|VX_NND ) /* L, ns */
/* v2.11: VX_L flag added */
//avxins (MOVNTDQ , vmovntdq ,     P_AVX, VX_NND )   /* -, ns */
//avxins (MOVNTPD , vmovntpd ,     P_AVX, VX_NND )   /* -, ns */
//avxins (MOVNTPS , vmovntps ,     P_AVX, VX_NND )   /* -, ns */
avxins (MOVNTDQ , vmovntdq ,     P_AVX, VX_LL|VX_L|VX_NND )   /* L, ns */
avxins (MOVNTDQA, vmovntdqa,     P_AVX, VX_LL|VX_L|VX_NND )   /* -, ns */
avxins (MOVNTPD , vmovntpd ,     P_AVX, VX_LL|VX_L|VX_NND )   /* L, ns */
avxins (MOVNTPS , vmovntps ,     P_AVX, VX_LL|VX_L|VX_NND )   /* L, ns */
avxins (MOVSHDUP, vmovshdup,     P_AVX, VX_LL|VX_L|VX_NND ) /* L, ns */
avxins (MOVSLDUP, vmovsldup,     P_AVX, VX_LL|VX_L|VX_NND ) /* L, ns */
avxins (MOVUPD  , vmovupd  ,     P_AVX, VX_LL|VX_L|VX_NND ) /* L, ns */
avxins (MOVUPS  , vmovups  ,     P_AVX, VX_LL|VX_L|VX_NND ) /* L, ns */
                                        
avxins (MPSADBW , vmpsadbw ,     P_AVX, VX_L )        /* -, s */

avxins (PABSB   , vpabsb   ,     P_AVX, VX_LL|VX_L|VX_NND )   /* -, ns */
avxins (PABSW   , vpabsw   ,     P_AVX, VX_LL|VX_L|VX_NND )   /* -, ns */
avxins (PABSD   , vpabsd   ,     P_AVX, VX_LL|VX_L|VX_NND )   /* -, ns */
avxins (PACKSSWB, vpacksswb,     P_AVX, VX_LL|VX_L )       /* -, s */
avxins (PACKSSDW, vpackssdw,     P_AVX, VX_LL|VX_L )       /* -, s */
avxins (PACKUSWB, vpackuswb,     P_AVX, VX_LL|VX_L )       /* -, s */
avxins (PACKUSDW, vpackusdw,     P_AVX, VX_LL|VX_L )       /* -, s */
avxins (PADDB   , vpaddb   ,     P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PADDW   , vpaddw   ,     P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PADDD   , vpaddd   ,     P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PADDQ   , vpaddq   ,     P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PADDSB  , vpaddsb  ,     P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PADDSW  , vpaddsw  ,     P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PADDUSB , vpaddusb ,     P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PADDUSW , vpaddusw ,     P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PALIGNR , vpalignr ,     P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PAND    , vpand    ,     P_AVX, VX_L )        /* -, s */
avxins (PANDN   , vpandn   ,     P_AVX, VX_L )        /* -, s */
avxins (PAVGB   , vpavgb   ,     P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PAVGW   , vpavgw   ,     P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PBLENDW , vpblendw ,     P_AVX, VX_L )        /* -, s */
avxins (PCMPESTRI,vpcmpestri,    P_AVX, VX_NND )      /* -, ns! */
avxins (PCMPESTRM,vpcmpestrm,    P_AVX, VX_NND )      /* -, ns! */
avxins (PCMPISTRI,vpcmpistri,    P_AVX, VX_NND )      /* -, ns! */
avxins (PCMPISTRM,vpcmpistrm,    P_AVX, VX_NND )      /* -, ns! */
avxins (PCMPEQB  ,vpcmpeqb  ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PCMPEQW  ,vpcmpeqw  ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PCMPEQD  ,vpcmpeqd  ,    P_AVX, VX_LL|VX_L|VX_HALF )        /* -, s */
avxins (PCMPEQQ  ,vpcmpeqq  ,    P_AVX, VX_LL|VX_L|VX_HALF )        /* -, s */
avxins (PCMPGTB  ,vpcmpgtb  ,    P_AVX, VX_LL|VX_L|VX_HALF)        /* -, s */
avxins (PCMPGTW  ,vpcmpgtw  ,    P_AVX, VX_LL|VX_L|VX_HALF)        /* -, s */
avxins (PCMPGTD  ,vpcmpgtd  ,    P_AVX, VX_LL|VX_L|VX_HALF )        /* -, s */
avxins (PCMPGTQ  ,vpcmpgtq  ,    P_AVX, VX_LL|VX_L|VX_HALF )        /* -, s */
avxins (PEXTRB   ,vpextrb   ,    P_AVX, VX_LL|VX_L|VX_NND )   /* -, ns! */
avxins (PEXTRW   ,vpextrw   ,    P_AVX, VX_LL|VX_L|VX_NND )   /* -, ns! */
avxins (PEXTRD   ,vpextrd   ,    P_AVX, VX_LL|VX_L|VX_NND )   /* -, ns! */
avxins (PINSRB   ,vpinsrb   ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PINSRW   ,vpinsrw   ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PINSRD   ,vpinsrd   ,    P_AVX, VX_LL|VX_L )        /* -, s */
#if AMD64_SUPPORT
avxins (PEXTRQ   ,vpextrq   ,    P_AVX, VX_LL|VX_L|VX_NND )   /* -, ns! */
avxins (PINSRQ   ,vpinsrq   ,    P_AVX, VX_LL )        /* -, s */
avxins (PCLMULQDQ,vpclmulqdq ,   P_AVX, VX_L )        /* -, s */
avxins (PCLMULLQLQDQ, vpclmullqlqdq,   P_AVX, VX_L )        /* -, s */
avxins (PCLMULHQLQDQ, vpclmulhqlqdq,   P_AVX, VX_L )        /* -, s */
avxins (PCLMULLQHQDQ, vpclmullqhqdq,   P_AVX, VX_L )        /* -, s */
avxins (PCLMULHQHQDQ, vpclmulhqhqdq,   P_AVX, VX_L )        /* -, s */
avxins (AESDECLAST,vaesdeclast , P_AVX, VX_L )        /* -, s */
avxins (AESDEC,vaesdec ,         P_AVX, VX_L )        /* -, s */
avxins (AESENC,vaesenc ,         P_AVX, VX_L )        /* -, s */
avxins (AESENCLAST,vaesenclast,  P_AVX, VX_L )        /* -, s */
avxins (AESIMC,  vaesimc,        P_AVX, VX_L|VX_NND )        /* -, s */
avxins (AESKEYGENASSIST,vaeskeygenassist, P_AVX, VX_NND )        /* -, s */

#endif
avxins (PHADDW   ,vphaddw   ,    P_AVX, VX_L )        /* -, s */
avxins (PHADDD   ,vphaddd   ,    P_AVX, VX_L )        /* -, s */
avxins (PHADDSW  ,vphaddsw  ,    P_AVX, VX_L )        /* -, s */
avxins (PHMINPOSUW,vphminposuw,  P_AVX, VX_NND )      /* -, ns */
avxins (PHSUBW   ,vphsubw   ,    P_AVX, VX_L )        /* -, s */
avxins (PHSUBD   ,vphsubd   ,    P_AVX, VX_L )        /* -, s */
avxins (PHSUBSW  ,vphsubsw  ,    P_AVX, VX_L )        /* -, s */
avxins (PMADDWD  ,vpmaddwd  ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PMADDUBSW,vpmaddubsw,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PMAXSB   ,vpmaxsb   ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PMAXSW   ,vpmaxsw   ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PMAXSD   ,vpmaxsd   ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PMAXUB   ,vpmaxub   ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PMAXUW   ,vpmaxuw   ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PMAXUD   ,vpmaxud   ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PMINSB   ,vpminsb   ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PMINSW   ,vpminsw   ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PMINSD   ,vpminsd   ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PMINUB   ,vpminub   ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PMINUW   ,vpminuw   ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PMINUD   ,vpminud   ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PMOVMSKB ,vpmovmskb ,    P_AVX, VX_L|VX_NND|VX_HALF)   /* -, ns */
avxins (PMOVSXBW ,vpmovsxbw ,    P_AVX, VX_LL|VX_L|VX_NND|VX_HALF)   /* -, ns */
avxins (PMOVSXBD ,vpmovsxbd ,    P_AVX, VX_LL|VX_L|VX_NND|VX_HALF)   /* -, ns */
avxins (PMOVSXBQ ,vpmovsxbq ,    P_AVX, VX_LL|VX_L|VX_NND|VX_HALF)   /* -, ns */
avxins (PMOVSXWD ,vpmovsxwd ,    P_AVX, VX_LL|VX_L|VX_NND|VX_HALF)   /* -, ns */
avxins (PMOVSXWQ ,vpmovsxwq ,    P_AVX, VX_LL|VX_L|VX_NND|VX_HALF)   /* -, ns */
avxins (PMOVSXDQ ,vpmovsxdq ,    P_AVX, VX_LL|VX_L|VX_NND|VX_HALF)   /* -, ns */
avxins (PMOVZXBW ,vpmovzxbw ,    P_AVX, VX_LL|VX_L|VX_NND|VX_HALF)   /* -, ns */
avxins (PMOVZXBD ,vpmovzxbd ,    P_AVX, VX_LL|VX_L|VX_NND|VX_HALF)   /* -, ns */
avxins (PMOVZXBQ ,vpmovzxbq ,    P_AVX, VX_LL|VX_L|VX_NND|VX_HALF)   /* -, ns */
avxins (PMOVZXWD ,vpmovzxwd ,    P_AVX, VX_LL|VX_L|VX_NND|VX_HALF)   /* -, ns */
avxins (PMOVZXWQ ,vpmovzxwq ,    P_AVX, VX_LL|VX_L|VX_NND|VX_HALF)   /* -, ns */
avxins (PMOVZXDQ ,vpmovzxdq ,    P_AVX, VX_LL|VX_L|VX_NND|VX_HALF)   /* -, ns */
avxins (PMULHUW  ,vpmulhuw  ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PMULHRSW ,vpmulhrsw ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PMULHW   ,vpmulhw   ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PMULLW   ,vpmullw   ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PMULLD   ,vpmulld   ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PMULUDQ  ,vpmuludq  ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PMULDQ   ,vpmuldq   ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (POR      ,vpor      ,    P_AVX, VX_L )        /* -, s */
avxins (PSADBW   ,vpsadbw   ,    P_AVX, VX_LL|VX_L )       /* -, s */
avxins (PSHUFB   ,vpshufb   ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PSHUFD   ,vpshufd   ,    P_AVX, VX_LL|VX_NND )   /* -, ns! */
avxins (PSHUFHW  ,vpshufhw  ,    P_AVX, VX_LL|VX_NND )   /* -, ns! */
avxins (PSHUFLW  ,vpshuflw  ,    P_AVX, VX_LL|VX_NND )   /* -, ns! */
avxins (PSIGNB   ,vpsignb   ,    P_AVX, VX_L )        /* -, s */
avxins (PSIGNW   ,vpsignw   ,    P_AVX, VX_L )        /* -, s */
avxins (PSIGND   ,vpsignd   ,    P_AVX, VX_L )        /* -, s */
avxins(PSLLDQ, vpslldq, P_AVX, VX_LL | VX_L | VX_DST | VX_HALF)   /* -, d */
avxins(PSRLDQ, vpsrldq, P_AVX, VX_LL | VX_L | VX_DST | VX_HALF)   /* -, d */
avxins(PSLLW,  vpsllw,  P_AVX, VX_LL | VX_L | VX_DST | VX_HALF)   /* -, d/s */
avxins(PSLLD,  vpslld,  P_AVX, VX_LL | VX_L | VX_DST | VX_HALF)   /* -, d/s */
avxins(PSLLQ,  vpsllq,  P_AVX, VX_LL | VX_L | VX_DST | VX_HALF)   /* -, d/s */
avxins(PSRAW,  vpsraw,  P_AVX, VX_LL | VX_L | VX_DST | VX_HALF)   /* -, d/s */
avxins(PSRAD,  vpsrad,  P_AVX, VX_LL | VX_L | VX_DST | VX_HALF)   /* -, d/s */
/* PSRAQ moved here for easyer handling, Uasm 2.16 */
avxins(PSRAQ,  vpsraq,  P_AVX, VX_LL | VX_L | VX_DST | VX_HALF)   /* -, d/s */
avxins(PSRLW,  vpsrlw,  P_AVX, VX_LL | VX_L | VX_DST | VX_HALF)   /* -, d/s */
avxins(PSRLD,  vpsrld,  P_AVX, VX_LL | VX_L | VX_DST | VX_HALF)   /* -, d/s */
avxins(PSRLQ,  vpsrlq,  P_AVX, VX_LL | VX_L | VX_DST | VX_HALF)   /* -, d/s */
/* */
avxins (PTEST    ,vptest    ,    P_AVX, VX_LL|VX_L|VX_NND ) /* L, ns */
avxins (PSUBB    ,vpsubb    ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PSUBW    ,vpsubw    ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PSUBD    ,vpsubd    ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PSUBQ    ,vpsubq    ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PSUBSB   ,vpsubsb   ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PSUBSW   ,vpsubsw   ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PSUBUSB  ,vpsubusb  ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PSUBUSW  ,vpsubusw  ,    P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PUNPCKHBW ,vpunpckhbw,   P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PUNPCKHWD ,vpunpckhwd,   P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PUNPCKHDQ ,vpunpckhdq,   P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PUNPCKHQDQ,vpunpckhqdq,  P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PUNPCKLBW ,vpunpcklbw,   P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PUNPCKLWD ,vpunpcklwd,   P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PUNPCKLDQ ,vpunpckldq,   P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PUNPCKLQDQ,vpunpcklqdq,  P_AVX, VX_LL|VX_L )        /* -, s */
avxins (PXOR     ,vpxor     ,    P_AVX, VX_L )              /* -, s */

avxins (RCPPS    ,vrcpps    ,    P_AVX, VX_L|VX_NND ) /* L, ns */
avxins (RCPSS    ,vrcpss    ,    P_AVX, 0 )        /* -, s */
avxins (RSQRTPS  ,vrsqrtps  ,    P_AVX, VX_L|VX_NND ) /* L, ns */
avxins (RSQRTSS  ,vrsqrtss  ,    P_AVX, 0 )        /* -, s */
avxins (ROUNDPD  ,vroundpd  ,    P_AVX, VX_L|VX_NND ) /* L, ns! */
avxins (ROUNDPS  ,vroundps  ,    P_AVX, VX_L|VX_NND ) /* L, ns! */
avxins (ROUNDSD  ,vroundsd  ,    P_AVX, 0 )        /* -, s */
avxins (ROUNDSS  ,vroundss  ,    P_AVX, 0 )        /* -, s */
avxins (SHUFPD   ,vshufpd   ,    P_AVX, VX_LL|VX_L )     /* L, s */
avxins (SHUFPS   ,vshufps   ,    P_AVX, VX_LL|VX_L )     /* L, s */
avxins (UCOMISD  ,vucomisd  ,    P_AVX, VX_LL|VX_NND )   /* -, ns */
avxins (UCOMISS  ,vucomiss  ,    P_AVX, VX_LL|VX_NND )   /* -, ns */
avxins (UNPCKHPD ,vunpckhpd ,    P_AVX, VX_LL|VX_L )     /* L, s */
avxins (UNPCKHPS ,vunpckhps ,    P_AVX, VX_LL|VX_L )     /* L, s */
avxins (UNPCKLPD ,vunpcklpd ,    P_AVX, VX_LL|VX_L )     /* L, s */
avxins (UNPCKLPS ,vunpcklps ,    P_AVX, VX_LL|VX_L )     /* L, s */

#endif

