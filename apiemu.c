/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
*  Description: API emulations:
*               gcc:     strupr()
*               OW:      CharUpperA()
*
****************************************************************************/

#if defined(__UNIX__)

/* v2.12: _splitpath()/_makepath() removed */

char *strupr( char *str )
/***********************/
{
    char    *p;
    unsigned char   c;

    p = str;
    while( (c = *p) ) {
        c -= 'a';
        if( c <= 'z' - 'a' ) {
            c += 'A';
            *p = c;
        }
        ++p;
    }
    return( str );
}

#endif

/* emulations for Open Watcom */

#if defined(__WATCOMC__) && !defined(__UNIX__)
#ifdef __FLAT__
#ifndef DEBUG_OUT /* OW v1.8 WDW has a problem with locally defined imports */

union cu {
    int c;
    char *p;
};

/* this is an emulation of the Win32 function which is called
 * by the OW runtime. It's the only USER32 function used.
 * By defining it here the binary will just need KERNEL32 to load.
 */
char * _stdcall CharUpperA( char *lpsz )
/**************************************/
{
    union cu p;
    p.p = lpsz;

    if ( p.c < 0x10000 )
        if ( p.c >= 'a' )
            return( (char *)p.c - 0x20 );
        else
            return( (char *)p.c );
    else
        for ( ; *p.p; p.p++ )
            if ( *p.p >= 'a' )
                *p.p = *p.p - 0x20;
    return( lpsz );
}
#endif
#endif
#endif

