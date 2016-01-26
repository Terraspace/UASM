/****************************************************************************
*
* Description:  prototypes of extern.c
*
****************************************************************************/

#ifndef _EXTERN_H_
#define _EXTERN_H_

/*---------------------------------------------------------------------------*/

//extern struct asym   *CreateExternal( struct asym *sym, const char *name, char weak );
extern struct asym   *MakeExtern( const char *name, enum memtype type, struct asym * vartype, struct asym *, unsigned char );
//extern struct asym   *CreateProto( int, const char * );

extern void        AddPublicData( struct asym *sym );
//extern struct asym *GetPublicSymbols( void ** ); /* v2.11: obsolete */
extern void        FreePubQueue( void );

#endif
