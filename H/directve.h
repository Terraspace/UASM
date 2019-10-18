/****************************************************************************
*
* Description:  table of directives
*
****************************************************************************/

/* v1.96: items needn't be sorted anymore!
 * The items are stored in structures of type special_item.
 * If an item is inserted, moved or deleted, the project needs
 * a full rebuild.
 */

/* directives field usage:
 * value  = DF_  flags    SpecialTable.value  unsigned
 * bytval = DRT_ value    SpecialTable.bytval uint_8
 * flags  = RWF_ flags    ResWordTable.flags  uint_8
 * cpu    = cpu  flags    SpecialTable.cpu    uint_16
 * sflags = dep. on DRT_  SpecialTable.sflags unsigned
 */

/* cpu directives */

/* token      str         value     bytval  flags  cpu   sflags */
res(DOT_8086, .8086,        0,      DRT_CPU,  0,   P_86,  P_86   )
res(DOT_186,  .186,         0,      DRT_CPU,  0,   P_86,  P_186  )
res(DOT_286,  .286,         0,      DRT_CPU,  0,   P_86,  P_286  )
res(DOT_286C, .286c,        0,      DRT_CPU,  0,   P_86,  P_286  )
res(DOT_286P, .286p,        0,      DRT_CPU,  0,   P_86,  P_286p )
res(DOT_386,  .386,         0,      DRT_CPU,  0,   P_86,  P_386  )
res(DOT_386C, .386c,        0,      DRT_CPU,  0,   P_86,  P_386  )
res(DOT_386P, .386p,        0,      DRT_CPU,  0,   P_86,  P_386p )
res(DOT_486,  .486,         0,      DRT_CPU,  0,   P_86,  P_486  )
res(DOT_486P, .486p,        0,      DRT_CPU,  0,   P_86,  P_486p )
res(DOT_586,  .586,         0,      DRT_CPU,  0,   P_86,  P_586  )
res(DOT_586P, .586p,        0,      DRT_CPU,  0,   P_86,  P_586p )
res(DOT_686,  .686,         0,      DRT_CPU,  0,   P_86,  P_686  )
res(DOT_686P, .686p,        0,      DRT_CPU,  0,   P_86,  P_686p )
res(DOT_K3D,  .k3d,         0,      DRT_CPU,  0,   P_586, P_K3D|P_MMX )
res(DOT_MMX,  .mmx,         0,      DRT_CPU,  0,   P_586, P_MMX  )
res(DOT_XMM,  .xmm,         0,      DRT_CPU,  0,   P_686, P_MMX|P_SSEALL )
#if AMD64_SUPPORT
res(DOT_X64,  .x64,         0,      DRT_CPU,  0,   P_86,  P_64  )
res(DOT_X64P, .x64p,        0,      DRT_CPU,  0,   P_86,  P_64p )
res(DOT_AMD64, .amd64,      0,      DRT_CPU,  0,   P_86,  P_64 )
res(DOT_WIN64, .win64,      0,      DRT_CPU,  0,   P_86,  P_64 )
#endif

res(DOT_8087, .8087,        0,      DRT_CPU,  0,   P_86,  P_87   )
res(DOT_287,  .287,         0,      DRT_CPU,  0,   P_86,  P_287  )
res(DOT_387,  .387,         0,      DRT_CPU,  0,   P_86,  P_387  )
res(DOT_NO87, .no87,        0,      DRT_CPU,  0,   P_86,  P_NO87 )

/* listing directives */
/* .LFCOND is synonym for .LISTIF
 * .SFCOND is synonym for .NOLISTIF
 * .TFCOND toggles .LFCOND, .SFCOND
 */

res(DOT_CREF,         .cref,          0,           DRT_LISTING, 0,  P_86, 0)
res(DOT_LFCOND,       .lfcond,        0,           DRT_LISTING, 0,  P_86, 0)
res(DOT_LIST,         .list,          0,           DRT_LISTING, 0,  P_86, 0)
res(DOT_LISTALL,      .listall,       0,           DRT_LISTING, 0,  P_86, 0)
res(DOT_LISTIF,       .listif,        0,           DRT_LISTING, 0,  P_86, 0)
res(DOT_NOCREF,       .nocref,        DF_NOEXPAND, DRT_LISTING, 0,  P_86, 0)
res(DOT_NOLIST,       .nolist,        0,           DRT_LISTING, 0,  P_86, 0)
res(DOT_NOLISTIF,     .nolistif,      0,           DRT_LISTING, 0,  P_86, 0)
res(DOT_SFCOND,       .sfcond,        0,           DRT_LISTING, 0,  P_86, 0)
res(DOT_TFCOND,       .tfcond,        0,           DRT_LISTING, 0,  P_86, 0)
res(DOT_XCREF,        .xcref,         DF_NOEXPAND, DRT_LISTING, 0,  P_86, 0)
res(DOT_XLIST,        .xlist,         0,           DRT_LISTING, 0,  P_86, 0)
res(PAGE,             page,           0,           DRT_LISTING, 0,  P_86, 0)
res(SUBTITLE,         subtitle,       0,           DRT_LISTING, 0,  P_86, 0)
res(SUBTTL,           subttl,         0,           DRT_LISTING, 0,  P_86, 0)
res(TITLE,            title,          0,           DRT_LISTING, 0,  P_86, 0)

/* list macro directives
 * .XALL is synonym for .LISTMACRO
 * .LALL is synonym for .LISTMACROALL
 * .SALL is synonym for .NOLISTMACRO
 */
res(DOT_LISTMACRO,    .listmacro,     0,           DRT_LISTMAC, 0,  P_86, LM_LISTMACRO)
res(DOT_LISTMACROALL, .listmacroall,  0,           DRT_LISTMAC, 0,  P_86, LM_LISTMACROALL)
res(DOT_NOLISTMACRO,  .nolistmacro,   0,           DRT_LISTMAC, 0,  P_86, LM_NOLISTMACRO)
res(DOT_XALL,         .xall,          0,           DRT_LISTMAC, 0,  P_86, LM_LISTMACRO)
res(DOT_LALL,         .lall,          0,           DRT_LISTMAC, 0,  P_86, LM_LISTMACROALL)
res(DOT_SALL,         .sall,          0,           DRT_LISTMAC, 0,  P_86, LM_NOLISTMACRO)


res(DOT_ALPHA,     .alpha,       0,          DRT_SEGORDER, 0,  P_86, SEGORDER_ALPHA )
res(DOT_DOSSEG,    .dosseg,      0,          DRT_SEGORDER, 0,  P_86, SEGORDER_DOSSEG)
res(DOT_SEQ,       .seq,         0,          DRT_SEGORDER, 0,  P_86, SEGORDER_SEQ   )
res(DOSSEG,        dosseg,       0,          DRT_SEGORDER, 0,  P_86, SEGORDER_DOSSEG)

/* simplified segment directives, numbers in sflags must match enum sim_seg (simseg.c) */
res(DOT_CODE,       .code,       DF_NOSTRUC|DF_PROC|DF_CGEN, DRT_SIMSEG, 0,  P_86, 0)
res(DOT_STACK,      .stack,      DF_NOSTRUC|DF_PROC|DF_CGEN, DRT_SIMSEG, 0,  P_86, 1)
res(DOT_DATA,       .data,       DF_NOSTRUC|DF_PROC|DF_CGEN, DRT_SIMSEG, 0,  P_86, 2)
res(DOT_DATA_UN,    .data?,      DF_NOSTRUC|DF_PROC|DF_CGEN, DRT_SIMSEG, 0,  P_86, 3)
res(DOT_FARDATA,    .fardata,    DF_NOSTRUC|DF_PROC|DF_CGEN, DRT_SIMSEG, 0,  P_86, 4)
res(DOT_FARDATA_UN, .fardata?,   DF_NOSTRUC|DF_PROC|DF_CGEN, DRT_SIMSEG, 0,  P_86, 5)
res(DOT_CONST,      .const,      DF_NOSTRUC|DF_PROC|DF_CGEN, DRT_SIMSEG, 0,  P_86, 6)

/* hll directives */

res(DOT_IF,         .if,         DF_CGEN|DF_CEXPR|DF_NOSTRUC|DF_STORE|DF_PROC, DRT_HLLSTART, 0, P_86, 0)
res(DOT_REPEAT,     .repeat,     DF_CGEN|DF_NOSTRUC|DF_STORE|DF_PROC,          DRT_HLLSTART, 0, P_86, 0)
res(DOT_WHILE,      .while,      DF_CGEN|DF_CEXPR|DF_NOSTRUC|DF_STORE|DF_PROC, DRT_HLLSTART, 0, P_86, 0)
res(DOT_FOR,        .for,        DF_CGEN|DF_CEXPR|DF_NOSTRUC|DF_STORE|DF_PROC, DRT_HLLSTART, 0, P_86, 0)
res(DOT_BREAK,      .break,      DF_CGEN,                                      DRT_HLLEXIT,  0, P_86, 0)
res(DOT_CONTINUE,   .continue,   DF_CGEN,                                      DRT_HLLEXIT,  0, P_86, 0)
res(DOT_ELSE,       .else,       DF_CGEN,                                      DRT_HLLEXIT,  0, P_86, 0)
res(DOT_ELSEIF,     .elseif,     DF_CGEN|DF_CEXPR,                             DRT_HLLEXIT,  0, P_86, 0)
res(DOT_ENDIF,      .endif,      DF_CGEN,                                      DRT_HLLEND,   0, P_86, 0)
res(DOT_ENDW,       .endw,       DF_CGEN,                                      DRT_HLLEND,   0, P_86, 0)
res(DOT_UNTIL,      .until,      DF_CGEN|DF_CEXPR,                             DRT_HLLEND,   0, P_86, 0)
res(DOT_UNTILCXZ,   .untilcxz,   DF_CGEN|DF_CEXPR,                             DRT_HLLEND,   0, P_86, 0)
res(DOT_ENDFOR,     .endfor,     DF_CGEN,				                       DRT_HLLEND,   0, P_86, 0)
res(DOT_ENDF,       .endf,       DF_CGEN,                                      DRT_HLLEND, 0, P_86, 0)
res(DOT_SWITCH,	    .switch,	 DF_CGEN|DF_CEXPR|DF_NOSTRUC|DF_STORE|DF_PROC, DRT_HLLSTART, 0, P_86, 0)
res(DOT_CASE,	    .case,	     DF_CGEN|DF_CEXPR,			                   DRT_HLLEXIT,  0, P_86, 0)
res(DOT_DEFAULT,    .default,	 DF_CGEN|DF_CEXPR,			                   DRT_HLLEXIT,  0, P_86, 0)
res(DOT_ENDSWITCH,  .endswitch,	 DF_CGEN,				                       DRT_HLLEND,   0, P_86, 0)
res(DOT_ENDSW,      .endsw,      DF_CGEN,                                      DRT_HLLEND,   0, P_86, 0)

res(DOT_EXIT,       .exit,       DF_CGEN|DF_STORE,  DRT_STARTEXIT,  0,   P_86, 0)
res(DOT_STARTUP,    .startup,    DF_CGEN|DF_STORE,  DRT_STARTEXIT,  0,   P_86, 0)

res(DOT_MODEL,      .model,      DF_CGEN,   DRT_MODEL,  0,   P_86, 0)
res(DOT_RADIX,      .radix,      0,         DRT_RADIX,  0,   P_86, 0)

/* directives invalid for IA32+ */

#if COFF_SUPPORT
res(DOT_SAFESEH,    .safeseh,    0,     DRT_SAFESEH,  RWF_IA32,   P_386, 0)
#endif

/* error directives */

res(DOT_ERR,     .err,         DF_STRPARM|DF_STORE,  DRT_ERRDIR,  0, P_86, 0)
res(DOT_ERR1,    .err1,        DF_STRPARM|DF_STORE,  DRT_ERRDIR,  0, P_86, CC_PASS1 )
res(DOT_ERR2,    .err2,        DF_STRPARM|DF_STORE,  DRT_ERRDIR,  0, P_86, CC_PASS2 )
res(DOT_ERRE,    .erre,        DF_STORE,             DRT_ERRDIR,  0, P_86, CC_NUMARG)
res(DOT_ERRNZ,   .errnz,       DF_STORE,             DRT_ERRDIR,  0, P_86, CC_NUMARG)
res(DOT_ERRDIF,  .errdif,      DF_STRPARM|DF_STORE,  DRT_ERRDIR,  0, P_86, CC_LITARG)
res(DOT_ERRDIFI, .errdifi,     DF_STRPARM|DF_STORE,  DRT_ERRDIR,  0, P_86, CC_LITARG)
res(DOT_ERRIDN,  .erridn,      DF_STRPARM|DF_STORE,  DRT_ERRDIR,  0, P_86, CC_LITARG)
res(DOT_ERRIDNI, .erridni,     DF_STRPARM|DF_STORE,  DRT_ERRDIR,  0, P_86, CC_LITARG)
res(DOT_ERRB,    .errb,        DF_STRPARM|DF_STORE,  DRT_ERRDIR,  0, P_86, CC_BLKARG)
res(DOT_ERRNB,   .errnb,       DF_STRPARM|DF_STORE,  DRT_ERRDIR,  0, P_86, CC_BLKARG)
res(DOT_ERRDEF,  .errdef,      DF_STRPARM|DF_STORE,  DRT_ERRDIR,  0, P_86, CC_SYMARG)
res(DOT_ERRNDEF, .errndef,     DF_STRPARM|DF_STORE,  DRT_ERRDIR,  0, P_86, CC_SYMARG)

/* conditional assembly directives, handled by preprocessor */

/* token          str          value        bytval     flgs cpu  sflags */
res(COMMENT,      comment,     0,           DRT_CONDDIR, 0, P_86, 0)
res(IF,           if,          0,           DRT_CONDDIR, 0, P_86, CC_NUMARG)
res(IFE,          ife,         0,           DRT_CONDDIR, 0, P_86, CC_NUMARG)
res(IF1,          if1,         0,           DRT_CONDDIR, 0, P_86, CC_PASS1 )
res(IF2,          if2,         0,           DRT_CONDDIR, 0, P_86, CC_PASS2 )
res(IFDIF,        ifdif,       DF_STRPARM,  DRT_CONDDIR, 0, P_86, CC_LITARG)
res(IFDIFI,       ifdifi,      DF_STRPARM,  DRT_CONDDIR, 0, P_86, CC_LITARG)
res(IFIDN,        ifidn,       DF_STRPARM,  DRT_CONDDIR, 0, P_86, CC_LITARG)
res(IFIDNI,       ifidni,      DF_STRPARM,  DRT_CONDDIR, 0, P_86, CC_LITARG)
res(IFB,          ifb,         DF_STRPARM,  DRT_CONDDIR, 0, P_86, CC_BLKARG)
res(IFNB,         ifnb,        DF_STRPARM,  DRT_CONDDIR, 0, P_86, CC_BLKARG)
res(IFDEF,        ifdef,       DF_NOEXPAND, DRT_CONDDIR, 0, P_86, CC_SYMARG)
res(IFNDEF,       ifndef,      DF_NOEXPAND, DRT_CONDDIR, 0, P_86, CC_SYMARG)
res(ELSE,         else,        0,           DRT_CONDDIR, 0, P_86, 0)
res(ELSEIF,       elseif,      0,           DRT_CONDDIR, 0, P_86, CC_NUMARG)
res(ELSEIFE,      elseife,     0,           DRT_CONDDIR, 0, P_86, CC_NUMARG)
res(ELSEIF1,      elseif1,     0,           DRT_CONDDIR, 0, P_86, CC_PASS1 )
res(ELSEIF2,      elseif2,     0,           DRT_CONDDIR, 0, P_86, CC_PASS2 )
res(ELSEIFDIF,    elseifdif,   DF_STRPARM,  DRT_CONDDIR, 0, P_86, CC_LITARG)
res(ELSEIFDIFI,   elseifdifi,  DF_STRPARM,  DRT_CONDDIR, 0, P_86, CC_LITARG)
res(ELSEIFIDN,    elseifidn,   DF_STRPARM,  DRT_CONDDIR, 0, P_86, CC_LITARG)
res(ELSEIFIDNI,   elseifidni,  DF_STRPARM,  DRT_CONDDIR, 0, P_86, CC_LITARG)
res(ELSEIFB,      elseifb,     DF_STRPARM,  DRT_CONDDIR, 0, P_86, CC_BLKARG)
res(ELSEIFNB,     elseifnb,    DF_STRPARM,  DRT_CONDDIR, 0, P_86, CC_BLKARG)
res(ELSEIFDEF,    elseifdef,   DF_NOEXPAND, DRT_CONDDIR, 0, P_86, CC_SYMARG)
res(ELSEIFNDEF,   elseifndef,  DF_NOEXPAND, DRT_CONDDIR, 0, P_86, CC_SYMARG)
res(ENDIF,        endif,       0,           DRT_CONDDIR, 0, P_86, 0)

/* assembly time loop directives, handled by preprocessor */

res(FOR,          for,         DF_NOEXPAND, DRT_LOOPDIR, 0, P_86, 0)
res(FORC,         forc,        DF_NOEXPAND, DRT_LOOPDIR, 0, P_86, 0)
res(IRP,          irp,         0,           DRT_LOOPDIR, 0, P_86, 0)
res(IRPC,         irpc,        0,           DRT_LOOPDIR, 0, P_86, 0)
res(REPEAT,       repeat,      0,           DRT_LOOPDIR, 0, P_86, 0)
res(REPT,         rept,        0,           DRT_LOOPDIR, 0, P_86, 0)
res(WHILE,        while,       0,           DRT_LOOPDIR, 0, P_86, 0)

/* other preprocessor directives */

res(MACRO,     macro,          DF_LABEL,              DRT_MACRO,   0, P_86, 0)
res(EXITM,     exitm,          DF_STRPARM,            DRT_MACINT,  0, P_86, 0)
res(ENDM,      endm,           0,                     DRT_MACINT,  0, P_86, 0)
res(GOTO,      goto,           0,                     DRT_MACINT,  0, P_86, 0)
res(PURGE,     purge,          0,                     DRT_PURGE,   0, P_86, 0)
res(UNDEF,     undef,          DF_NOEXPAND|DF_NOCONCAT, DRT_UNDEF, 0, P_86, 0)
res(DEFINE,    define,         DF_NOEXPAND|DF_NOCONCAT, DRT_DEFINE,0, P_86, 0)
res(INCLUDE,   include,        DF_NOEXPAND|DF_NOCONCAT,DRT_INCLUDE,0, P_86, 0)
res(TEXTEQU,   textequ,        DF_STRPARM | DF_LABEL, DRT_CATSTR,  0, P_86, 0)
res(CATSTR,    catstr,         DF_STRPARM | DF_LABEL, DRT_CATSTR,  0, P_86, 0)
res(SUBSTR,    substr,         DF_STRPARM | DF_LABEL, DRT_SUBSTR,  0, P_86, 0)

/* INSTR and SIZESTR aren't true preprocessor directives */
res(INSTR,     instr,          DF_STRPARM | DF_LABEL, DRT_INSTR,   0, P_86, 0)
res(SIZESTR,   sizestr,        DF_STRPARM | DF_LABEL, DRT_SIZESTR, 0, P_86, 0)

/* data definition directives */
res(DB,        db,             DF_LABEL,    DRT_DATADIR, 0, P_86, T_BYTE )
res(DW,        dw,             DF_LABEL,    DRT_DATADIR, 0, P_86, T_WORD )
res(DD,        dd,             DF_LABEL,    DRT_DATADIR, 0, P_86, T_DWORD)
res(DF,        df,             DF_LABEL,    DRT_DATADIR, 0, P_86, T_FWORD)
res(DQ,        dq,             DF_LABEL,    DRT_DATADIR, 0, P_86, T_QWORD)
res(DT,        dt,             DF_LABEL,    DRT_DATADIR, 0, P_86, T_TBYTE)
#if AMD64_SUPPORT 
res(DOT_ALLOCSTACK, .allocstack, 0,        DRT_EXCFRAME, RWF_X64,  P_64, 0)
res(DOT_ENDPROLOG,  .endprolog,  0,        DRT_EXCFRAME, RWF_X64,  P_64, 0)
res(DOT_PUSHFRAME,  .pushframe,  0,        DRT_EXCFRAME, RWF_X64,  P_64, 0)
res(DOT_PUSHREG,    .pushreg,    0,        DRT_EXCFRAME, RWF_X64,  P_64, 0)
res(DOT_SAVEREG,    .savereg,    0,        DRT_EXCFRAME, RWF_X64,  P_64, 0)
res(DOT_SAVEXMM128, .savexmm128, 0,        DRT_EXCFRAME, RWF_X64,  P_64, 0)
#if AVXSUPP
res(DOT_SAVEYMM256, .saveymm256, 0,        DRT_EXCFRAME, RWF_X64,  P_64, 0)
res(DOT_SAVEZMM512, .savezmm512, 0,        DRT_EXCFRAME, RWF_X64,  P_64, 0)
#endif
res(DOT_SETFRAME,   .setframe,   0,        DRT_EXCFRAME, RWF_X64,  P_64, 0)
#endif

/* "type" directives */
res(STRUC,       struc,       DF_LABEL,             DRT_STRUCT, 0,  P_86, 0)
res(STRUCT,      struct,      DF_LABEL,             DRT_STRUCT, 0,  P_86, 0)
res(CSTRUCT,     cstruct,     DF_LABEL,             DRT_CSTRUCT, 0,  P_86, 0)
res(COMSTRUCT,   comstruct,   DF_LABEL,             DRT_COMSTRUCT, 0, P_86, 0)
res(RAWSTRUCT,   rawstruct,   DF_LABEL,             DRT_RAWSTRUCT, 0, P_86, 0)
res(UNION,       union,       DF_LABEL,             DRT_STRUCT, 0,  P_86, 0)
res(TYPEDEF,     typedef,     DF_LABEL,             DRT_TYPEDEF,0,  P_86, 0)
res(RECORD,      record,      DF_LABEL,             DRT_RECORD, 0,  P_86, 0)

/* "global" directives */
res(COMM,        comm,        0,                    DRT_COMM,     0,  P_86, 0)
res(EXTERN,      extern,      0,                    DRT_EXTERN,   0,  P_86, 0)
res(EXTRN,       extrn,       0,                    DRT_EXTERN,   0,  P_86, 0)
res(EXTERNDEF,   externdef,   0,                    DRT_EXTERNDEF,0,  P_86, 0)
res(PUBLIC,      public,      0,                    DRT_PUBLIC,   0,  P_86, 0)

/* "proc" directives */
res(PROTO,       proto,       DF_LABEL,                            DRT_PROTO,  0,  P_86, 0)
res(PROC,        proc,        DF_CGEN|DF_LABEL|DF_NOSTRUC|DF_STORE,DRT_PROC,   0,  P_86, 0)
res(ENDP,        endp,        DF_LABEL|DF_NOSTRUC,                 DRT_ENDP,   0,  P_86, 0)
res(LOCAL,       local,       0,                                   DRT_LOCAL,  0,  P_86, 0)
res(LABEL,       label,       DF_LABEL|DF_NOSTRUC|DF_STORE,        DRT_LABEL,  0,  P_86, 0)
res(INVOKE,      invoke,      DF_CGEN|DF_NOSTRUC|DF_PROC|DF_STORE, DRT_INVOKE, 0,  P_86, 0)

/* other directives */

/* token         str        len  value                       bytval     flags cpu sflags */
res(ORG,         org,         0,                          DRT_ORG,     0,  P_86, 0)
res(ALIGN,       align,       0,                          DRT_ALIGN,   0,  P_86, 0)
res(EVEN,        even,        0,                          DRT_ALIGN,   0,  P_86, 0)

res(SEGMENT,     segment,     DF_LABEL|DF_NOSTRUC|DF_PROC,DRT_SEGMENT, 0,  P_86, 0)
/* v2.10: ENDS should not trigger prologue creation if it is to end a structure */
//res(ENDS,        ends,        DF_LABEL|DF_PROC,           DRT_ENDS,    0,  P_86, 0)
res(ENDS,        ends,        DF_LABEL,                   DRT_ENDS,    0,  P_86, 0)
res(GROUP,       group,       DF_LABEL,                   DRT_GROUP,   0,  P_86, 0)
res(ASSUME,      assume,      0,                          DRT_ASSUME,  0,  P_86, 0)

res(ALIAS,       alias,       0,                          DRT_ALIAS,   0,  P_86, 0)
res(ECHO,        echo,        DF_NOEXPAND|DF_NOCONCAT,    DRT_ECHO,    0,  P_86, 0)
res(END,         end,         DF_CGEN|DF_NOSTRUC|DF_STORE,DRT_END,     0,  P_86, 0)
res(EQU,         equ,         DF_STRPARM|DF_LABEL,        DRT_EQU,     0,  P_86, 0)
#if INCBINSUPP
res(INCBIN,      incbin,      DF_NOSTRUC|DF_PROC|DF_STORE,DRT_INCBIN,  0,  P_86, 0)
#endif
res(INCLUDELIB,  includelib,  DF_NOCONCAT,                DRT_INCLIB,  0,  P_86, 0)
res(NAME,        name,        0,                          DRT_NAME,    0,  P_86, 0)
res(OPTION,      option,      0,                          DRT_OPTION,  0,  P_86, 0)
res(POPCONTEXT,  popcontext,  0,                          DRT_CONTEXT, 0,  P_86, 0)
res(PUSHCONTEXT, pushcontext, 0,                          DRT_CONTEXT, 0,  P_86, 0)

