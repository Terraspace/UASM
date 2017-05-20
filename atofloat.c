/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:  string to float conversion
*
****************************************************************************/

#include <float.h>
#include <math.h>

#include "globals.h"
#include "tbyte.h"
#include "atofloat.h"

#define USESTRTOF 0 /* 0=use strtod() and convert "manually", 1=use strtof() */

extern void myatoi128( const char *, uint_64[], int, int );

/* it's ensured that 'out' points to a buffer with a size of at least 16 */

void atofloat( void *out, const char *inp, unsigned size, bool negative, uint_8 ftype )
/*************************************************************************************/
{
    //const char *inp;
    double  double_value;
    float   float_value;

    /* v2.04: accept and handle 'real number designator' */
    if ( ftype ) {
        uint_8 *p;
        uint_8 *end;
        /* convert hex string with float "designator" to float.
         * this is supposed to work with real4, real8 and real10.
         * v2.11: use myatoi128() for conversion ( this function
         *        always initializes and reads a 16-byte number ).
         *        then check that the number fits in the variable.
         */
        myatoi128( inp, (uint_64 *)out, 16, strlen( inp ) - 1 );
        for ( p = (uint_8 *)out + size, end = (uint_8 *)out + 16; p < end; p++ )
            if ( *p != NULLC ) {
                EmitErr( INVALID_DATA_INITIALIZER, inp );
                break;
            }
    } else {
        switch ( size ) {
        case 4:
#if USESTRTOF
            errno = 0;
            float_value = strtof( inp, NULL );
            if ( errno == ERANGE ) {
                DebugMsg(("atofloat(%s, 4): magnitude too large\n", inp ));
                EmitErr( MAGNITUDE_TOO_LARGE_FOR_SPECIFIED_SIZE );
            }
            if( negative )
                float_value *= -1;
#else
            double_value = strtod( inp, NULL );
            /* v2.06: check FLT_MAX added */
            /* v2.11: check FLT_MIN (min positive value) added */
            //if ( double_value > FLT_MAX )
            if ( double_value > FLT_MAX || ( double_value < FLT_MIN && double_value != 0 ) ) {
                DebugMsg(("atofloat(%s, 4): magnitude too large; FLT_MAX=%e FLT_MIN=%e\n", inp, FLT_MAX, FLT_MIN ));
                EmitErr( MAGNITUDE_TOO_LARGE_FOR_SPECIFIED_SIZE );
            }
            if( negative )
                double_value *= -1;
            float_value = double_value;
#endif
            *(float *)out = float_value;
            break;
        case 8:
            errno = 0; /* v2.11: init errno; errno is set on over- and under-flow */
            double_value = strtod( inp, NULL );
            /* v2.11: check added */
            if ( errno == ERANGE ) {
                DebugMsg(("atofloat(%s, 8): magnitude too large\n", inp ));
                EmitErr( MAGNITUDE_TOO_LARGE_FOR_SPECIFIED_SIZE );
            }
            if( negative )
                double_value *= -1;
            *(double *)out = double_value;
            break;
        case 10:
            strtotb( inp, (struct TB_LD *)out, negative );
            break;
        default:
            /* sizes != 4,8 or 10 aren't accepted.
             * Masm ignores silently, Uasm also unless -W4 is set.
             */
            if ( Parse_Pass == PASS_1 )
                EmitWarn( 4, FP_INITIALIZER_IGNORED );
            memset( (char *)out, 0, size );
        }
    }
    return;
}

