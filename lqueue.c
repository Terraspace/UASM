/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:  handle the line queue.
*               this queue is used for "generated code".
*
****************************************************************************/

#include <stdarg.h>

#include "globals.h"
#include "memalloc.h"
#include "reswords.h"
#include "input.h"
#include "parser.h"
#include "preproc.h"
#include "myassert.h"

extern struct ReservedWord  ResWordTable[];

/* item of a line queue */
struct lq_line {
    struct lq_line *next;
#ifdef DEBUG_OUT
    char lineno;
#endif
    char line[1];
};

#define line_queue  ModuleInfo.g.line_queue

#ifdef DEBUG_OUT
static unsigned lqlines_written; /* lq lines written by AddLineQueue() */
static unsigned lqlines_read;    /* lq lines read by RunLineQueue() */
unsigned GetLqLine( void ) { return( lqlines_read ); }
#endif

/* free items of current line queue */

void DeleteLineQueue( void )
/**************************/
{
    struct qitem *curr;
    struct qitem *next;
    for( curr = line_queue.head; curr; curr = next ) {
        next = curr->next;
        MemFree( curr );
    }
    line_queue.head = NULL;
}


#if 0 /* v2.11: now a macro */
bool is_linequeue_populated( void )
/*********************************/
{
    return( line_queue.head != NULL );
}
#endif

/* Add a line to the current line queue. */

void AddLineQueue( const char *line )
/***********************************/
{
    unsigned i = strlen( line );
    struct lq_line   *new;

    /* v2.11: line queue has become static. */
    //if ( line_queue == NULL ) {
    //    line_queue = MemAlloc( sizeof( struct input_queue ) );
    //    line_queue->tail = NULL;
    //}
    new = MemAlloc( sizeof( struct lq_line ) + i );
    new->next = NULL;
    DebugCmd( new->lineno = lqlines_written );
    memcpy( new->line, line, i + 1 );

    if( line_queue.head == NULL ) {
        line_queue.head = new;
    } else {
        /* insert at the tail */
        ((struct qnode *)line_queue.tail)->next = new;
    }
    line_queue.tail = new;
    return;
}

/* Add a line to the current line queue, "printf" format. */

void AddLineQueueX( const char *fmt, ... )
/****************************************/
{
    va_list args;
    char *d;
    int i;
    int_32 l;
    int_64 q;
    const char *s;
    const char *p;
    char buffer[MAX_LINE_LEN];

    va_start( args, fmt );
    for ( s = fmt, d = buffer; *s; s++ ) {
        if ( *s == '%' ) {
            s++;
            switch ( *s ) {
            case 'r':
                i = va_arg( args, int );
                GetResWName( i , d );
                /* v2.06: the name is already copied */
                //memcpy( d, ResWordTable[i].name, ResWordTable[i].len );
                d += ResWordTable[i].len;
                break;
            case 's':
                p = va_arg( args, char * );
                i = strlen( p );
                memcpy( d, p, i );
                d += i;
                *d = NULLC;
                break;
#if AMD64_SUPPORT
            case 'q':
              q = va_arg(args, int_64);
              myqtoa(q, d, 10, q < 0, FALSE);
              d += strlen(d);
              /* v2.07: add a 't' suffix if radix is != 10 */
              if (ModuleInfo.radix != 10)
                *d++ = 't';
              break;
#endif
            case 'd':
            case 'u':
            case 'x':
#ifdef __I86__ /* v2.08: use long only if size(int) is 16-bit */
                l = va_arg( args, long );
#else
                l = va_arg( args, int );
#endif
                if ( *s == 'x' ) {
                    myltoa( l, d, 16, FALSE, FALSE );
                    d += strlen( d );
                } else {
                    myltoa( l, d, 10, l < 0, FALSE );
                    d += strlen( d );
                    /* v2.07: add a 't' suffix if radix is != 10 */
                    if ( ModuleInfo.radix != 10 )
                        *d++ = 't';
                }
                break;
            default:
                *d++ = *s;
            }
        } else
            *d++ = *s;
    }
    *d = NULLC;
    va_end( args );
    AddLineQueue( buffer );
    return;
}

void BuildCodeLine(char *buffer, const char *fmt, ...)
/****************************************/
{
	va_list args;
	char *d;
	int i;
	int_32 l;
	int_64 q;
	const char *s;
	const char *p;

	va_start(args, fmt);
	for (s = fmt, d = buffer; *s; s++) {
		if (*s == '%') {
			s++;
			switch (*s) {
			case 'r':
				i = va_arg(args, int);
				GetResWName(i, d);
				/* v2.06: the name is already copied */
				//memcpy( d, ResWordTable[i].name, ResWordTable[i].len );
				d += ResWordTable[i].len;
				break;
			case 's':
				p = va_arg(args, char *);
				i = strlen(p);
				memcpy(d, p, i);
				d += i;
				*d = NULLC;
				break;
#if AMD64_SUPPORT
			case 'q':
				q = va_arg(args, int_64);
				myqtoa(q, d, 10, q < 0, FALSE);
				d += strlen(d);
				/* v2.07: add a 't' suffix if radix is != 10 */
				if (ModuleInfo.radix != 10)
					*d++ = 't';
				break;
#endif
			case 'd':
			case 'u':
			case 'x':
#ifdef __I86__ /* v2.08: use long only if size(int) is 16-bit */
				l = va_arg(args, long);
#else
				l = va_arg(args, int);
#endif
				if (*s == 'x') {
					myltoa(l, d, 16, FALSE, FALSE);
					d += strlen(d);
				}
				else {
					myltoa(l, d, 10, l < 0, FALSE);
					d += strlen(d);
					/* v2.07: add a 't' suffix if radix is != 10 */
					if (ModuleInfo.radix != 10)
						*d++ = 't';
				}
				break;
			default:
				*d++ = *s;
			}
		}
		else
			*d++ = *s;
	}
	*d = NULLC;
	va_end(args);
	return;
}

/*
 * RunLineQueue() is called whenever generated code is to be assembled. It
 * - saves current input status
 * - processes the line queue
 * - restores input status
 */

void RunLineQueue( void )
/***********************/
{
    struct input_status oldstat;
    struct asm_tok *tokenarray;
    struct lq_line *currline = line_queue.head;

    /* v2.03: ensure the current source buffer is still aligned */
    tokenarray = PushInputStatus( &oldstat );
    ModuleInfo.GeneratedCode++;

    /* v2.11: line queues are no longer pushed onto the file stack.
     * Instead, the queue is processed directly here.
     */
    line_queue.head = NULL;
    DebugCmd( lqlines_written = 0 ); /* reset counter for AddLineQueue() */
    DebugCmd( lqlines_read = 0 ); /* reset counter for line-queue reads below */

    for ( ; currline; ) {
        struct lq_line *nextline = currline->next;
        strcpy( CurrSource, currline->line );
        DebugCmd ( lqlines_read++ );
        MemFree( currline );
        if ( PreprocessLine( CurrSource, tokenarray ) )
            ParseLine( tokenarray );
        currline = nextline;
    }

    ModuleInfo.GeneratedCode--;
    PopInputStatus( &oldstat );

    return;
}
