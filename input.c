/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  processing file/macro input data.
*
****************************************************************************/

#include <ctype.h>
//#include <stdarg.h> /* v2.12: removed - was necessary for _splitpath()/_makepath() */

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "macro.h"
#include "input.h"
#include "lqueue.h"
#include "myassert.h"

#define DETECTCTRLZ 1 /* 1=Ctrl-Z in input stream will skip rest of the file */

/* FILESEQ: if 1, stores a linked list of source files, ordered
 * by usage. Masm stores such a list in the COFF symbol table
 * when -Zd/-Zi is set. It isn't necessary, however, and Uasm's
 * COFF code currently will ignore the list.
 */

#define FILESEQ 0

char   *commentbuffer;

struct asym *FileCur; /* @FileCur symbol, created in SymInit() */
struct asym *LineCur; /* @Line symbol, created in SymInit()    */

enum src_item_type {
    SIT_FILE,
    SIT_MACRO,
};

/* item on src stack ( contains currently open source files & macros ) */
struct src_item {
    struct src_item     *next;
    uint_8              type;       /* item type ( see enum src_item_type ) */
    uint_16             srcfile;    /* index of file in ModuleInfo.g.FNames */
    union {
        void            *content;   /* generic */
        FILE            *file;      /* if item is a file */
        struct macro_instance *mi;  /* if item is a macro */
    };
    uint_32             line_num;   /* current line # */
    /* v2.11 field macro moved to struct macro_instance */
    //struct asym         *macro;     /* the symbol if it is a macro */
};

/* v2.11: introduced a list of unused src_items */
static struct src_item *SrcFree;

#define src_stack  ModuleInfo.g.src_stack

#if FILESEQ
struct qdesc            FileSeq;
#endif

#ifdef DEBUG_OUT
struct asm_tok *end_tokenarray;
char           *end_stringbuf;
static int_32 cntflines;  /* count file lines ( read by fgets() ) */
static int_32 cntlines;   /* count lines read by GetTextLine() */
extern int_32 cnttok0;    /* count Tokenize() calls, index==0 */
extern int_32 cnttok1;    /* count Tokenize() calls, index!=0 */
extern int_32 cntppl0;    /* count preprocessed lines 1 */
extern int_32 cntppl1;    /* count preprocessed lines 2 */
extern int_32 cntppl2;    /* count lines NOT handled by preprocessor */
#endif

/* buffer for source lines
 * since the lines are sometimes concatenated
 * the buffer must be a multiple of MAX_LINE_LEN
 */
static char *srclinebuffer;

/* string buffer - token strings and other stuff are stored here.
 * must be a multiple of MAX_LINE_LEN since it is used for string expansion.
 */
char *token_stringbuf;  /* start token string buffer */

/* fixme: add '|| defined(__CYGWIN__)' ? */
#if defined(__UNIX__)

#define INC_PATH_DELIM      ':'
#define INC_PATH_DELIM_STR  ":"
#define DIR_SEPARATOR       '/'
#define filecmp strcmp
#define ISPC( x ) ( x == '/' )
#define ISABS( x ) ( *x == '/' )

#else

#define INC_PATH_DELIM      ';'
#define INC_PATH_DELIM_STR  ";"
#define DIR_SEPARATOR       '\\'
#define filecmp _stricmp
#define ISPC( x ) ( x == '/' || x == '\\' || x == ':' )
#define ISABS( x ) ( *x == '/' || *x == '\\' || ( *x &&  *(x+1) == ':' && ( *(x+2) == '/' || *(x+2) == '\\' ) ) )

#endif

#if 0 /* v2.11: obsolete, field fullname removed */
static char *GetFullPath( const char *name, char *buff, size_t max )
/******************************************************************/
{
    char        *p;

    p = _fullpath( buff, name, max );
    if( p == NULL )
        p = (char *)name;

#if defined(__UNIX__)
    if( (p[0] == '/' && p[1] == '/') && (name[0] != '/' || name[1] != '/') ) {
        /*
         * if the _fullpath result has a node number and
         * the user didn't specify one, strip the node number
         * off before returning
         */
        p += 2;
        while( *(p++) != '/' ) ;
    }
#endif
    return( p );
}
#endif

/* v2.12: function added - _splitpath()/_makepath() removed */

const char *GetFNamePart( const char *fname )
/*******************************************/
{
    const char *rc;
    for ( rc = fname; *fname; fname++ )
        if ( ISPC( *fname ) )
            rc = fname + 1;
    return( rc );
}

/* fixme: if the dot is at pos 0 of filename, ignore it */

char *GetExtPart( const char *fname )
/***********************************/
{
    char *rc;
    for( rc = NULL; *fname; fname++ ) {
        if( *fname == '.' ) {
            rc = (char *)fname;
        } else if( ISPC( *fname ) ) {
            rc = NULL;
        }
    }
    return( rc ? rc : (char *)fname );
}

/* check if a file is in the array of known files.
 * if no, store the file at the array's end.
 * returns array index.
 * used for the main source and all INCLUDEd files.
 * the array is stored in the standard C heap!
 * the filenames are stored in the "local" heap.
 */
static unsigned AddFile( char const *fname )
/******************************************/
{
    unsigned    index;

    DebugMsg1(("AddFile(%s) enter, curr index=%u\n", fname, ModuleInfo.g.cnt_fnames ));
    for( index = 0; index < ModuleInfo.g.cnt_fnames; index++ ) {
        if( filecmp( fname, ModuleInfo.g.FNames[index] ) == 0 ) {
            return( index );
        }
    }

    if ( ( index % 64 ) == 0 ) {
        struct fname_item *newfn;
        newfn = (struct fname_item *)MemAlloc( ( index + 64 ) * sizeof( struct fname_item ) );
        if ( ModuleInfo.g.FNames ) {
            memcpy( newfn, ModuleInfo.g.FNames, index * sizeof( struct fname_item ) );
            MemFree( ModuleInfo.g.FNames );
        }
        ModuleInfo.g.FNames = newfn;
    }
    ModuleInfo.g.cnt_fnames++;

    ModuleInfo.g.FNames[index] = (char *)LclAlloc( strlen( fname ) + 1 );
    strcpy( ModuleInfo.g.FNames[index], fname );
    return( index );
}

const struct fname_item *GetFName( unsigned index )
/*************************************************/
{
    return( ModuleInfo.g.FNames+index );
}

/* free the file array.
 * this is done once for each module after the last pass.
 */

static void FreeFiles( void )
/***************************/
{
#if FASTMEM==0
    int i;

    /* remove the main src item from src stack */
    src_stack->next = SrcFree;
    SrcFree = src_stack;
#endif
    /* v2.03: set src_stack=NULL to ensure that GetCurrSrcPos()
     * won't find something when called from main().
     */
    src_stack = NULL;

#if FASTMEM==0
    /* free the "free src_items"-heap */
    while ( SrcFree ) {
        struct src_item *next;
        next = SrcFree->next;
        LclFree( SrcFree );
        SrcFree = next;
    };
    for ( i = 0; i < ModuleInfo.g.cnt_fnames; i++ ) {
        LclFree( ModuleInfo.g.FNames[i].fname );
        //LclFree( ModuleInfo.g.FNames[i].fullname );
    }
#endif
    if ( ModuleInfo.g.FNames ) {
        MemFree( ModuleInfo.g.FNames );
        ModuleInfo.g.FNames = NULL;
    }
    return;
}

/* clear input source stack (include files and open macros).
 * This is done after each pass.
 * Usually the stack is empty when the END directive occurs,
 * but it isn't required that the END directive is located in
 * the main source file. Also, an END directive might be
 * simulated if a "too many errors" condition occurs.
 */

void ClearSrcStack( void )
/************************/
{
    struct src_item   *nextfile;

    DeleteLineQueue();

    /* dont close the last item (which is the main src file) */
    for( ; src_stack->next ; src_stack = nextfile ) {
        nextfile = src_stack->next;
        if ( src_stack->type == SIT_FILE ) {
            fclose( src_stack->file );
        }
        //LclFree( src_stack );
        src_stack->next = SrcFree;
        SrcFree = src_stack;
    }
    return;
}

/* get/set value of predefined symbol @Line */

void UpdateLineNumber( struct asym *sym, void *p )
/************************************************/
{
    struct src_item *curr;
    for ( curr = src_stack; curr ; curr = curr->next )
        if ( curr->type == SIT_FILE ) {
            sym->value = curr->line_num;
            break;
        }
    return;
}

uint_32 GetLineNumber( void )
/***************************/
{
    UpdateLineNumber( LineCur, NULL );
    return( LineCur->uvalue );
}

#ifdef DEBUG_OUT

extern unsigned GetLqLine( void );

char *GetTopLine( char *buffer )
/******************************/
{
    *buffer = NULLC;
    if ( ModuleInfo.GeneratedCode )
        sprintf( buffer, "(%u)", GetLqLine() );
    else if( src_stack->type == SIT_MACRO )
        sprintf( buffer, "[%s.%" I32_SPEC "u]", src_stack->mi->macro->name, src_stack->line_num );
    return( buffer );
}

char *GetTopSrcName( void )
/*************************/
{
    if ( src_stack->type == SIT_MACRO )
        return( src_stack->mi->macro->name );
    return( GetFName( src_stack->srcfile )->fname );
}

#endif

/* read one line from current source file.
 * returns NULL if EOF has been detected and no char stored in buffer
 * v2.08: 00 in the stream no longer causes an exit. Hence if the
 * char occurs in the comment part, everything is ok.
 */
static char *my_fgets( char *buffer, int max, FILE *fp )
/******************************************************/
{
    char        *ptr = buffer;
    char        *last = buffer + max;
    int         c;

    c = getc( fp );
    while( ptr < last ) {
        switch ( c ) {
        case '\r':
            break; /* don't store CR */
        case '\n':
            /* fall through */
        //case '\0': /* v2.08: */
#ifdef DEBUG_OUT
            if ( Parse_Pass == PASS_1 )
                cntflines++;
#endif
            *ptr = NULLC;
            return( buffer );
#if DETECTCTRLZ
        case 0x1a:
            /* since source files are opened in binary mode, ctrl-z
             * handling must be done here.
             */
            /* no break */
#endif
        case EOF:
            *ptr = NULLC;
            return( ptr > buffer ? buffer : NULL );
        default:
            *ptr++ = c;
        }
        c = getc( fp );
    }
    EmitErr( LINE_TOO_LONG );
    *(ptr-1) = NULLC;
    return( buffer );
}

#if FILESEQ
void AddFileSeq( unsigned file )
/******************************/
{
    struct file_seq *node;
    node = LclAlloc( sizeof( struct file_seq ) );
    node->next = NULL;
    node->file = file;
    if ( FileSeq.head == NULL )
        FileSeq.head = FileSeq.tail = node;
    else {
        ((struct file_seq *)FileSeq.tail)->next = node;
        FileSeq.tail = node;
    }
}
#endif

/* push a new item onto the source stack.
 * type: SIT_FILE or SIT_MACRO
 */
 struct src_item *PushSrcItem( char type, void *pv )
/********************************************************/
{
    struct src_item   *curr;

    if ( SrcFree ) {
        curr = SrcFree;
        SrcFree = curr->next;
    } else
        curr = LclAlloc( sizeof( struct src_item ) );
    curr->next = src_stack;
    src_stack = curr;
    curr->type = type;
    curr->content = pv;
    curr->line_num = 0;
    return( curr );
}

/* push a macro onto the source stack. */

void PushMacro( struct macro_instance *mi )
/*****************************************/
{
    DebugMsg1(( "PushMacro(%s)\n", mi->macro->name ));
    PushSrcItem( SIT_MACRO, mi );
    return;
}

#if FASTMEM==0
bool MacroInUse( struct dsym *macro )
/***********************************/
{
    struct src_item *curr;

    for ( curr = src_stack; curr ; curr = curr->next )
        if ( curr->type == SIT_MACRO && curr->mi->macro == &macro->sym )
            return( TRUE );

    return( FALSE );
}
#endif

unsigned get_curr_srcfile( void )
/*******************************/
{
    struct src_item *curr;
    for ( curr = src_stack; curr ; curr = curr->next )
        if ( curr->type == SIT_FILE )
            return( curr->srcfile );
    return( ModuleInfo.srcfile );
}

#if FASTPASS
void set_curr_srcfile( unsigned file, uint_32 line_num )
/******************************************************/
{
    if ( file != 0xFFF ) /* 0xFFF is the special value for macro lines */
        src_stack->srcfile = file;
    src_stack->line_num = line_num;
    return;
}
#endif

void SetLineNumber( unsigned line )
/*********************************/
{
    src_stack->line_num = line;
    return;
}

/* for error listing, render the current source file and line */
/* this function is also called if pass is > 1,
 * which is a problem for FASTPASS because the file stack is empty.
 */
int GetCurrSrcPos( char *buffer )
/*******************************/
{
    struct src_item *curr;

    for( curr = src_stack; curr; curr = curr->next ) {
        if ( curr->type == SIT_FILE ) {
            return( sprintf( buffer, ModuleInfo.EndDirFound == FALSE ? "%s(%" I32_SPEC "u) : " : "%s : ", GetFName( curr->srcfile )->fname , curr->line_num ) );
        }
    }
    *buffer = NULLC;
    return( 0 );
}

/* for error listing, render the source nesting structure.
 * the structure consists of include files and macros.
 */

void print_source_nesting_structure( void )
/*****************************************/
{
    struct src_item *curr;
    unsigned        tab = 1;

    /* in main source file? */
    if ( src_stack == NULL || src_stack->next == NULL )
        return;

    for( curr = src_stack; curr->next ; curr = curr->next ) {
        if( curr->type == SIT_FILE ) {
            PrintNote( NOTE_INCLUDED_BY, tab, "", GetFName( curr->srcfile )->fname, curr->line_num );
            tab++;
        } else {
            //char fname[_MAX_FNAME+_MAX_EXT];
            if (*(curr->mi->macro->name) == NULLC ) {
                PrintNote( NOTE_ITERATION_MACRO_CALLED_FROM, tab, "", "MacroLoop", curr->line_num, curr->mi->macro->value + 1 );
            } else {
                PrintNote( NOTE_MACRO_CALLED_FROM, tab, "", curr->mi->macro->name, curr->line_num, GetFNamePart( GetFName(((struct dsym *)curr->mi->macro)->e.macroinfo->srcfile)->fname ) ) ;
            }
            tab++;
        }
    }
    PrintNote( NOTE_MAIN_LINE_CODE, tab, "", GetFName( curr->srcfile )->fname, curr->line_num );
}

/* Scan the include path for a file!
 * variable ModuleInfo.g.IncludePath also contains directories set with -I cmdline option.
 */
static FILE *open_file_in_include_path( const char *name, char fullpath[] )
/*************************************************************************/
{
    char            *curr;
    char            *next;
    int             i;
    int             namelen;
    FILE            *file = NULL;

    while( isspace( *name ) )
        name++;

    curr = ModuleInfo.g.IncludePath;
    namelen = strlen( name );

    DebugMsg(("open_file_in_include_path(%s) enter\n", name ));
    for ( ; curr; curr = next ) {
        next = strchr( curr, INC_PATH_DELIM );
        if ( next ) {
            i = next - curr;
            next++; /* skip path delimiter char (; or :) */
        } else {
            i = strlen( curr );
        }

        /* v2.06: ignore
         * - "empty" entries in PATH
         * - entries which would cause a buffer overflow
         */
        if ( i == 0 || ( ( i + namelen ) >= FILENAME_MAX ) )
            continue;

        memcpy( fullpath, curr, i );
        if( fullpath[i-1] != '/'
#if !defined(__UNIX__)
           && fullpath[i-1] != '\\' && fullpath[i-1] != ':'
#endif
        ) {
            fullpath[i] = DIR_SEPARATOR;
            i++;
        }
        strcpy( fullpath+i, name );

        DebugMsg(("open_file_in_include_path: >%s<\n", fullpath ));
        file = fopen( fullpath, "rb" );
        if( file ) {
            break;
        }
    }
    DebugMsg(("open_file_in_include_path()=%p\n", file ));
    return( file );
}

/* the worker behind the INCLUDE directive. Also used
 * by INCBIN and the -Fi cmdline option.
 * the main source file is added in InputInit().
 * v2.12: _splitpath()/_makepath() removed
 */

FILE *SearchFile( const char *path, bool queue )
/**********************************************/
{
    FILE        *file = NULL;
    struct src_item *fl;
    const char  *fn;
    bool        isabs;
    char        fullpath[FILENAME_MAX];

    DebugMsg1(("SearchFile(%s) enter\n", path ));

    //_splitpath( path, drive, dir, fname, ext );
    //DebugMsg1(("SearchFile(): drive=%s, dir=%s, fname=%s, ext=%s\n", drive, dir, fname, ext ));
    fn = GetFNamePart( path );

    /* if no absolute path is given, then search in the directory
     * of the current source file first!
     * v2.11: various changes because field fullpath has been removed.
     */

    isabs = ISABS( path );
    //if ( dir[0] != '\\' && dir[0] != '/' ) {
    if ( !isabs ) {
        for ( fl = src_stack; fl ; fl = fl->next ) {
            if ( fl->type == SIT_FILE ) {
                const char  *fn2;
                char        *src;
                //_splitpath( GetFName( fl->srcfile )->fname, drive2, dir2, NULL, NULL );
                //DebugMsg1(("SearchFile(): curr src=%s, split into drive=%s, dir=%s\n", GetFName( fl->srcfile)->fname, drive2, dir2 ));
                src = GetFName( fl->srcfile )->fname;
                fn2 = GetFNamePart( src );
                if ( fn2 != src ) {
                    int i = fn2 - src;
                    /* v2.10: if there's a directory part, add it to the directory part of the current file.
                     * fixme: check that both parts won't exceed FILENAME_MAX!
                     * fixme: 'path' is relative, but it may contain a drive letter!
                     */
                    memcpy( fullpath, src, i );
                    strcpy( fullpath + i, path );
                    if ( file = fopen( fullpath, "rb" ) ) {
                        DebugMsg1(("SearchFile(): file found, fopen(%s)=%X\n", fullpath, file ));
                        path = fullpath;
						if(file) 
							setvbuf( file, NULL, _IOFBF, 4096*4 );
                    }
#ifdef DEBUG_OUT
                    else
                        DebugMsg1(("SearchFile(): fopen(%s) failed\n", fullpath ));
#endif
                }
                break;
            }
        }
    }
    if ( file == NULL ) {
        fullpath[0] = NULLC;
        file = fopen( path, "rb" );
		if(file)
			setvbuf(file, NULL, _IOFBF, 4096*4 );
        DebugMsg1(("SearchFile(): fopen(%s)=%X\n", path, file ));

        /* if the file isn't found yet and include paths have been set,
         * and NO absolute path is given, then search include dirs
         */
        if( file == NULL && ModuleInfo.g.IncludePath != NULL && !isabs ) {
            if ( file = open_file_in_include_path( path, fullpath ) ) {
                DebugMsg1(("SearchFile(): open_file_in_include_path(%s)=%X [%s]\n", path, file, fullpath ));
                path = fullpath;
            }
#ifdef DEBUG_OUT
            else
                DebugMsg1(("SearchFile(): open_file_in_include_path(%s)=NULL\n", path ));
#endif
        }
        if( file == NULL ) {
            EmitErr( CANNOT_OPEN_FILE, path, ErrnoStr() );
            return( NULL );
        }
    }
    /* is the file to be added to the file stack?
     * assembly files usually are, but binary files ( INCBIN ) aren't.
     */
    if ( queue ) {
        fl = PushSrcItem( SIT_FILE, file );
        fl->srcfile = AddFile( path );
        FileCur->string_ptr = GetFName( fl->srcfile )->fname;
#if FILESEQ
        if ( Options.line_numbers && Parse_Pass == PASS_1 )
            AddFileSeq( fl->srcfile );
#endif
    }
    return( file );
}

/* get the next source line from file or macro.
 * v2.11: line queues are no longer read here,
 * this is now done in RunLineQueue().
 * Also, if EOF/EOM is reached, the function will
 * now return NULL in any case.
 */

char *GetTextLine( char *buffer )
/*******************************/
{
    struct src_item *curr = src_stack;

    if ( curr->type == SIT_FILE ) {

        if( my_fgets( buffer, MAX_LINE_LEN, curr->file ) ) {
            curr->line_num++;
#ifdef DEBUG_OUT
            if ( Parse_Pass == PASS_1 ) cntlines++;
#endif
            return( buffer );
        }
 
        /* don't close and remove main source file */
        if ( curr->next ) {
            fclose( curr->file );
            src_stack = curr->next;
            curr->next = SrcFree;
            SrcFree = curr;
        }
        /* update value of @FileCur variable */
        for( curr = src_stack; curr->type != SIT_FILE; curr = curr->next );
        FileCur->string_ptr = GetFName( curr->srcfile)->fname;
#if FILESEQ
        if ( Options.line_numbers && Parse_Pass == PASS_1 )
            AddFileSeq( curr->srcfile );
#endif

    } else {

        curr->mi->currline = ( curr->mi->currline ? curr->mi->currline->next : curr->mi->startline );
        if ( curr->mi->currline ) {
            /* if line contains placeholders, replace them by current values */
            if ( curr->mi->currline->ph_count ) {
                fill_placeholders( buffer,
                                  curr->mi->currline->line,
                                  curr->mi->parmcnt,
                                  curr->mi->localstart, curr->mi->parm_array );
            } else {
                strcpy( buffer, curr->mi->currline->line );
            }
            curr->line_num++;
#ifdef DEBUG_OUT
            if ( Parse_Pass == PASS_1 ) cntlines++;
#endif
            return( buffer );
        }
        src_stack = curr->next;
        curr->next = SrcFree;
        SrcFree = curr;
    }

    return( NULL ); /* end of file or macro reached */
}

/* add a string to the include path.
 * called for -I cmdline options.
 * the include path is rebuilt for each assembled module.
 * it is stored in the standard C heap.
 */
void AddStringToIncludePath( const char *string )
/***********************************************/
{
    char *tmp;
    int len;

    DebugMsg(("AddStringToIncludePath(%s) enter\n", string ));
    while( isspace( *string ) )
        string++;
    len = strlen( string );
    if ( len == 0 )
        return;
    if( ModuleInfo.g.IncludePath == NULL ) {
        ModuleInfo.g.IncludePath = MemAlloc( len + 1 );
        strcpy( ModuleInfo.g.IncludePath, string );
    } else {
        tmp = ModuleInfo.g.IncludePath;
        ModuleInfo.g.IncludePath = MemAlloc( strlen( tmp ) + sizeof( INC_PATH_DELIM_STR ) +
                                len + 1 );
        strcpy( ModuleInfo.g.IncludePath, tmp );
        strcat( ModuleInfo.g.IncludePath, INC_PATH_DELIM_STR );
        strcat( ModuleInfo.g.IncludePath, string );
        MemFree( tmp );
    }
}

#if 0
/* function to get value of @FileCur.
 * won't work, because text macros don't use asym.sfunc_ptr
 */
static void GetFileCur( struct asym *sym )
/****************************************/
{
    struct src_item *curr;

    for( curr = src_stack; curr && curr->type != SIT_FILE; curr = curr->next );
    sym->string_ptr = GetFName( curr->srcfile )->name;
    DebugMsg1(("GetFileCur: curr value=%s\n", sym->string_ptr ));
}
#endif

/* input buffers
 * 1. src line stack ( default I86: 2*600  = 1200 )
 * 2. tokenarray     ( default I86: 150*12 = 1800 )
 * 3. string buffer  ( default I86: 2*600  = 1200 )
 */

#ifdef __I86__
#define SIZE_SRCLINES     ( MAX_LINE_LEN * 2 )
#define SIZE_TOKENARRAY   ( sizeof( struct asm_tok ) * MAX_TOKEN )
#define SIZE_STRINGBUFFER ( MAX_LINE_LEN * 2 )
#else
#define SIZE_SRCLINES     ( MAX_LINE_LEN * ( MAX_MACRO_NESTING + 1 ) )
#define SIZE_TOKENARRAY   ( sizeof( struct asm_tok ) * MAX_TOKEN * MAX_MACRO_NESTING )
#define SIZE_STRINGBUFFER ( MAX_LINE_LEN * MAX_MACRO_NESTING )
#endif

/* PushInputStatus() is used whenever a macro or generated code is to be "executed".
 * after the macro/code has been assembled, PopInputStatus() is required to restore
 * the saved status.
 * the status information that is saved includes
 * - the source line ( including the comment )
 * - the token buffer
 * - the string buffer (used to store token strings)
 * - field Token_Count
 * - field line_flags
 */

struct asm_tok *PushInputStatus( struct input_status *oldstat )
/*************************************************************/
{
    oldstat->token_stringbuf = token_stringbuf;
    oldstat->token_count = Token_Count;
    oldstat->currsource = CurrSource;
    /* if there's a comment, attach it to current source */
    if ( ModuleInfo.CurrComment ) {
        int i = strlen( CurrSource );
        oldstat->CurrComment = CurrSource + i;
        strcpy( oldstat->CurrComment, ModuleInfo.CurrComment );
    } else
        oldstat->CurrComment = NULL;
    oldstat->line_flags = ModuleInfo.line_flags; /* v2.08 */
    token_stringbuf = StringBufferEnd;
    ModuleInfo.tokenarray += Token_Count + 1;
    CurrSource = GetAlignedPointer( CurrSource, strlen( CurrSource ) );
    return( ModuleInfo.tokenarray );
}

void PopInputStatus( struct input_status *newstat )
/*************************************************/
{
    StringBufferEnd = token_stringbuf;
    token_stringbuf = newstat->token_stringbuf;
    Token_Count = newstat->token_count;
    CurrSource = newstat->currsource;
    if ( newstat->CurrComment ) {
        ModuleInfo.CurrComment = commentbuffer;
        strcpy( ModuleInfo.CurrComment, newstat->CurrComment );
        *newstat->CurrComment = NULLC;
    } else
        ModuleInfo.CurrComment = NULL;
    ModuleInfo.tokenarray -= Token_Count + 1;
    ModuleInfo.line_flags = newstat->line_flags; /* v2.08 */
    return;
}

/* Initializer, called once for each module. */

void InputInit( void )
/********************/
{
    struct src_item *fl;

    SrcFree = NULL; /* v2.11 */
#if FILESEQ
    FileSeq.head = NULL;
#endif

    srclinebuffer = LclAlloc( SIZE_SRCLINES + SIZE_TOKENARRAY + SIZE_STRINGBUFFER );
    /* the comment buffer is at the end of the source line buffer */
    commentbuffer = srclinebuffer + SIZE_SRCLINES - MAX_LINE_LEN;
    /* behind the comment buffer is the token buffer */
    ModuleInfo.tokenarray = (struct asm_tok *)( srclinebuffer + SIZE_SRCLINES );
    token_stringbuf = srclinebuffer + SIZE_SRCLINES + SIZE_TOKENARRAY;
    fl = PushSrcItem( SIT_FILE, CurrFile[ASM] );
    fl->srcfile = ModuleInfo.srcfile = AddFile( CurrFName[ASM] );
    FileCur->string_ptr = GetFName( fl->srcfile )->fname;
}

/* init for each pass */

void InputPassInit( void )
/************************/
{
    src_stack->line_num = 0;
    CurrSource = srclinebuffer;
    *CurrSource = NULLC;
    StringBufferEnd = token_stringbuf;
    return;
}

/* release input buffers for a module */

void InputFini( void )
/********************/
{
    if ( ModuleInfo.g.IncludePath )
        MemFree( ModuleInfo.g.IncludePath );

    /* free items in ModuleInfo.g.FNames ( and FreeFile, if FASTMEM==0 ) */
    FreeFiles();
    ModuleInfo.tokenarray = NULL;
    LclFree( srclinebuffer );
}
