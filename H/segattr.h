/* segment attributes. Included by segment.c only */
sitem( "READONLY",     0,              INIT_ATTR       )
sitem( "BYTE",         0,              INIT_ALIGN      )
sitem( "WORD",         1,              INIT_ALIGN      )
sitem( "DWORD",        2,              INIT_ALIGN      )
sitem( "PARA",         4,              INIT_ALIGN      )
sitem( "PAGE",         8,              INIT_ALIGN      )
#if PAGE4K
sitem( "PAGE4K",       12,             INIT_ALIGN      )
#endif
sitem( "ALIGN",        0,              INIT_ALIGN_PARAM )
sitem( "PRIVATE",      COMB_INVALID,   INIT_COMBINE    )
sitem( "PUBLIC",       COMB_ADDOFF,    INIT_COMBINE    )
sitem( "STACK",        COMB_STACK,     INIT_COMBINE    )
sitem( "COMMON",       COMB_COMMON,    INIT_COMBINE    )
sitem( "MEMORY",       COMB_ADDOFF,    INIT_COMBINE    )
sitem( "AT",           COMB_INVALID,   INIT_COMBINE_AT )
#if COMDATSUPP
sitem( "COMDAT",       COMB_INVALID,   INIT_COMBINE_COMDAT )
#endif
sitem( "USE16",        USE16,          INIT_OFSSIZE    )
sitem( "USE32",        USE32,          INIT_OFSSIZE    )
#if AMD64_SUPPORT
sitem( "USE64",        USE64,          INIT_OFSSIZE    )
#endif
sitem( "FLAT",         USE32,          INIT_OFSSIZE_FLAT )
#if COFF_SUPPORT || ELF_SUPPORT
sitem( "INFO",         0,                                    INIT_CHAR_INFO )
sitem( "DISCARD",      IMAGE_SCN_MEM_DISCARDABLE >> 24,      INIT_CHAR )
sitem( "NOCACHE",      IMAGE_SCN_MEM_NOT_CACHED  >> 24,      INIT_CHAR )
sitem( "NOPAGE",       IMAGE_SCN_MEM_NOT_PAGED   >> 24,      INIT_CHAR )
sitem( "SHARED",       IMAGE_SCN_MEM_SHARED      >> 24,      INIT_CHAR )
sitem( "EXECUTE",      IMAGE_SCN_MEM_EXECUTE     >> 24,      INIT_CHAR )
sitem( "READ",         IMAGE_SCN_MEM_READ        >> 24,      INIT_CHAR )
sitem( "WRITE",        IMAGE_SCN_MEM_WRITE       >> 24,      INIT_CHAR )
sitem( "ALIAS",        0,                                    INIT_ALIAS )
#endif
