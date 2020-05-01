
/* interface to OMF format output functions */

#ifndef _OMF_H_INCLUDED_
#define _OMF_H_INCLUDED_

/* max size of LEDATA data is 1024 - (1+2+1/2+2/4+1) = 1014 */

#define MAX_LEDATA_THRESHOLD    (1024 - 10)

struct line_num_info;

extern void      omf_init( struct module_info * );

extern void      omf_set_filepos( void );
//void      omf_write_ledata( struct dsym * );
extern void      omf_OutSelect( bool );
extern void      omf_FlushCurrSeg( void );
extern void      omf_check_flush( const struct line_num_info * );

#endif // _OMF_H_INCLUDED_

