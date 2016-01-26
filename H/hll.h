/****************************************************************************
*
* Description:  hll constructs .IF, ...
*
****************************************************************************/


#ifndef _HLL_H_
#define _HLL_H_

extern void HllInit( int );    /* reset counter for hll labels */
#if FASTMEM==0
extern void HllFini( void );
#endif
extern void HllCheckOpen( void );

#endif
