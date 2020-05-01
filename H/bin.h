/****************************************************************************
*
* Description:  header for BIN output format
*
****************************************************************************/


#ifndef _BIN_H_INCLUDED_
#define _BIN_H_INCLUDED_

extern void     bin_init( struct module_info * );

#if PE_SUPPORT
extern void     pe_create_PE_header( void );
#endif

#endif // _BIN_H_INCLUDED_
