
#ifndef _LQUEUE_H_INCLUDED
#define _LQUEUE_H_INCLUDED

/* v2.11: line queue functions moved from input.c to lqueue.c */

extern void     DeleteLineQueue( void );
extern void     AddLineQueue( const char *line );
extern void     AddLineQueueX( const char *fmt, ... );
extern void     RunLineQueue( void );
extern void     BuildCodeLine(char *buffer, const char *fmt, ...);
//v2.11: replaced by macro
//extern bool   is_linequeue_populated( void );
#define is_linequeue_populated() ModuleInfo.g.line_queue.head

#endif
