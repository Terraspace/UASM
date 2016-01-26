/* DRT_ values ( directive types ) */
/* items CONDDIR ... INCLUDE must be first, INCLUDE the last of them.
 * DATADIR must be the first non-preprocessor directive!
 */
res( CONDDIR,   CondAsmDirective ) /* conditional assembly directive (IF, ELSE, ...) */
res( LOOPDIR,   LoopDirective )    /* loop directive (FOR, REPEAT, WHILE, ...) */
res( PURGE,     PurgeDirective )   /* PURGE directive */
res( INCLUDE,   IncludeDirective ) /* INCLUDE directive */
res( MACRO,     MacroDir )         /* MACRO directive */
res( CATSTR,    CatStrDir )        /* TEXTEQU + CATSTR directives */
res( SUBSTR,    SubStrDir )        /* SUBSTR directive */
res( MACINT,    StubDir )          /* "internal macro" directives EXITM, ENDM, GOTO */
/* non-preprocessor directives */
res( DATADIR,   StubDir )          /* "data" directives DB, DW, DD, ... */
res( END,       EndDirective )
res( ERRDIR,    ErrorDirective )   /* v2.05: no longer preprocessor directives */
res( CPU,       CpuDirective )
res( LISTING,   ListingDirective )
res( LISTMAC,   ListMacroDirective )
res( SEGORDER,  SegOrderDirective )
res( SIMSEG,    SimplifiedSegDir )
res( HLLSTART,  HllStartDir )
res( HLLEXIT,   HllExitDir )
res( HLLEND,    HllEndDir )
res( STARTEXIT, StartupExitDirective )
res( MODEL,     ModelDirective )
res( RADIX,     RadixDirective )
#if COFF_SUPPORT
res( SAFESEH,   SafeSEHDirective )
#endif
res( INSTR,     InStrDir )
res( SIZESTR,   SizeStrDir )
#if AMD64_SUPPORT
res( EXCFRAME,  ExcFrameDirective )
#endif
res( STRUCT,    StructDirective )
res( TYPEDEF,   TypedefDirective )
res( RECORD,    RecordDirective )
res( COMM,      CommDirective )
res( EXTERN,    ExternDirective )
res( EXTERNDEF, ExterndefDirective )
res( PROTO,     ProtoDirective )
res( PUBLIC,    PublicDirective )
res( PROC,      ProcDir )
res( ENDP,      EndpDir )
res( LOCAL,     LocalDir )
res( INVOKE,    InvokeDirective )
res( ORG,       OrgDirective )
res( ALIGN,     AlignDirective )
res( SEGMENT,   SegmentDir )
res( ENDS,      EndsDir )
res( GROUP,     GrpDir )
res( ASSUME,    AssumeDirective )
res( LABEL,     LabelDirective )
res( ALIAS,     AliasDirective )
res( ECHO,      EchoDirective )
res( EQU,       EquDirective )
res( EQUALSGN,  EqualSgnDirective ) /* '=' directive */
#if INCBINSUPP
res( INCBIN,    IncBinDirective )
#endif
res( INCLIB,    IncludeLibDirective )
res( NAME,      NameDirective )
res( OPTION,    OptionDirective )
res( CONTEXT,   ContextDirective )
