/****************************************************************************
*
* Description:  listing interface.
*
****************************************************************************/


#ifndef _LISTING_H_INCLUDED
#define _LISTING_H_INCLUDED

enum lsttype {
 LSTTYPE_DATA,
 LSTTYPE_CODE,
 LSTTYPE_EQUATE,
 LSTTYPE_TMACRO,
 LSTTYPE_DIRECTIVE,
 LSTTYPE_MACRO,
 LSTTYPE_STRUCT,
 LSTTYPE_LABEL,
 LSTTYPE_MACROLINE,
};

extern void LstInit( void );
extern void LstWrite( enum lsttype, uint_32 ofs, void * sym );
extern void LstWriteSrcLine( void );
extern void LstWriteCRef( void );
extern void LstPrintf( const char *format, ... );
extern void LstNL( void );
#if FASTPASS
extern void LstSetPosition( void );
#endif

#endif
