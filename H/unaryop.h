/* table of unary operators, used in expreval.c */
res( LOW,       low_op     )
res( HIGH,      high_op    )
res( LOWWORD,   lowword_op )
res( HIGHWORD,  highword_op)
#if LOHI32
res( LOW32,     low32_op   )
res( HIGH32,    high32_op  )
#endif
res( OFFSET,    offset_op  )
res( LROFFSET,  offset_op  )
#if IMAGERELSUPP
res( IMAGEREL,  offset_op  )
#endif
#if SECTIONRELSUPP
res( SECTIONREL, offset_op )
#endif
res( SEG,       seg_op     )
res( OPATTR,    opattr_op  )
res( DOT_TYPE,  opattr_op  )
res( SIZE,      sizlen_op  )
res( SIZEOF,    sizlen_op  )
res( LENGTH,    sizlen_op  )
res( LENGTHOF,  sizlen_op  )
res( SHORT,     short_op   )
res( THIS,      this_op    )
res( TYPE,      type_op    )
res( MASK,      wimask_op  )
res( WIDTH,     wimask_op  )
