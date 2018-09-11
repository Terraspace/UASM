/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:  Memory allocation routines.
*
****************************************************************************/

#if defined(__UNIX__) && defined(__GNUC__)
    #include <sys/mman.h>
#endif

#include "globals.h"
#include "memalloc.h"

/* what items are stored in the heap?
 * - symbols + symbol names ( asym, dsym; symbol.c )
 * - macro lines ( StoreMacro(); macro.c )
 * - file names ( CurrFName[]; assemble.c )
 * - temp items + buffers ( omf.c, bin.c, coff.c, elf.c )
 * - contexts ( reused; context.c )
 * - codeview debug info ( dbgcv.c )
 * - library names ( includelib; directiv.c )
 * - src lines for FASTPASS ( fastpass.c )
 * - fixups ( fixup.c )
 * - hll items (reused; .IF, .WHILE, .REPEAT; hll.c )
 * - one big input buffer ( src line buffer, tokenarray, string buffer; input.c )
 * - src filenames array ( AddFile(); input.c )
 * - line number info ( -Zd, -Zi; linnum.c )
 * - macro parameter array + default values ( macro.c )
 * - prologue, epilogue macro names ??? ( option.c )
 * - dll names ( OPTION DLLIMPORT; option.c )
 * - std queue items ( see queues in struct module_vars; globals.h, queue.c )
 * - renamed keyword queue ( reswords.c )
 * - safeseh queue ( safeseh.c )
 * - segment alias names ( segment.c )
 * - segment stack ( segment.c )
 * - segment buffers ( 1024 for omf, else may be HUGE ) ( segment.c )
 * - segment names for simplified segment directives (simsegm.c )
 * - strings of text macros ( string.c )
 * - struct/union/record member items + default values ( types.c )
 * - procedure prologue argument, debug info ( proc.c )
 */

#ifndef alloca
#define alloca(x)  __builtin_alloca(x)
#endif

#if FASTMEM

/* FASTMEM is a simple memory alloc approach which allocates chunks of 512 kB
 * and will release it only at MemFini().
 *
 * May be considered to create an additional "line heap" to store lines of
 * loop macros and generated code - since this is hierarchical, a simple
 * Mark/Release mechanism will do the memory management.
 * currently generated code lines are stored in the C heap, while
 * loop macro lines go to the "fastmem" heap.
 */

#define BLKSIZE 0x80000

#ifndef __UNIX__
  #if defined(__OS2__)
   #include <os2.h>
  #elif defined(__DJGPP__)
   #include <dpmi.h>
  #else
   #include "win32.h"
  #endif
#endif

struct linked_list {
    struct linked_list *next;
};
static struct linked_list *pBase; /* start list of 512 kB blocks; to be moved to ModuleInfo.g */
static uint_8 *pCurr; /* points into current block; to be moved to ModuleInfo.g */
static uint_32 currfree; /* free memory left in current block; to be moved to ModuleInfo.g */
#ifdef DEBUG_OUT
static int blocks;    /* number of blocks allocated so far; to be moved to ModuleInfo.g */
#endif

#if defined(__UNIX__) && defined(__WATCOMC__)

#define SYS_mmap                 90
#define SYS_munmap               91

uint_32 sys_call1( uint_32 func, uint_32 r_ebx );
#pragma aux sys_call1 =                         \
    "int    0x80"                               \
    parm [eax] [ebx]                            \
    value [eax];

uint_32 sys_call2( uint_32 func, uint_32 r_ebx, uint_32 r_ecx );
#pragma aux sys_call2 =                         \
    "int    0x80"                               \
    parm [eax] [ebx] [ecx]                      \
    value [eax];

struct mmap {
    uint_32 base;   /* linear base (or 0) */
    uint_32 size;   /* size in bytes */
    uint_32 access; /* 3 = PROT_READ | PROT_WRITE */
    uint_32 flags;  /* 0x22 = MAP_PRIVATE | MAP_ANON */
    uint_32 fd;     /* should be -1 */
    uint_32 offset; /* ignored */
};
static struct mmap mymmap = { 0, 0, 3, 0x22, -1, 0 };
#endif

/* Allow clang on Linux to build */
#ifndef MAP_ANON
	#define MAP_ANON 0x20
#endif

#ifndef __UNIX__
 #if defined(__OS2__)
  #define BLKALLOC( p, size ) DosAllocMem( (void**)&p, size, PAG_COMMIT|PAG_READ|PAG_WRITE )
  #define BLKFREE( p )        DosFreeMem( p )
 #elif defined(__NT__) || defined(_WIN64)
  #define BLKALLOC( p, size ) p = (uint_8 *)VirtualAlloc( NULL, size, MEM_COMMIT, PAGE_READWRITE )
  #define BLKFREE( p )        VirtualFree( p, 0, MEM_RELEASE )
 #else
  #define BLKALLOC( p, size ) p = malloc( size )
  #define BLKFREE( p )        free( p )
 #endif
#else
 #if defined(__WATCOMC__)
  #define BLKALLOC( p, size_ ) mymmap.size = size_; \
                              p = (uint_8 *)sys_call1( SYS_mmap, (uint_32)&mymmap )
  #define BLKFREE( p )        sys_call2( SYS_munmap, (uint_32)p, 0 )
 #else
  #define BLKALLOC( p, size ) p = (uint_8 *)mmap( 0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0 ); \
                              if ( p == MAP_FAILED ) p = NULL
  #define BLKFREE( p )        munmap( (void *)p, 0 )
 #endif
#endif

#endif /* FASTMEM */

#ifdef DEBUG_OUT
static uint_32 memcalls = 0;
static uint_32 memstart;
#endif

#ifdef TRMEM /* track memory allocation? */

#include "trmem.h"

extern _trmem_hdl   hTrmem;
#define malloc( x ) _trmem_alloc( x, _trmem_guess_who( &x ), hTrmem )
#define free( x )   _trmem_free( x, _trmem_guess_who( &x ), hTrmem )

#endif

void MemInit( void )
/******************/
{
#if FASTMEM
    pBase = NULL;
    currfree = 0;
    DebugCmd( blocks = 0 );
#endif
    DebugCmd( memstart = memcalls );
}

void MemFini( void )
/******************/
{

#if FASTMEM
#ifdef DEBUG_OUT
    if ( Options.quiet == FALSE )
        printf( "memory used: %u kB\n", (blocks * BLKSIZE - currfree) / 1024 );
#endif
    while ( pBase ) {
        struct linked_list *pNext = pBase->next;
        BLKFREE( pBase );
        pBase = pNext;
    }
#endif
#ifdef DEBUG_OUT
    if ( memcalls != memstart )
        printf("still allocated memory blocks : %u\n", memcalls - memstart );
#endif
}

void *LclAlloc( size_t size )
/***************************/
{
    void        *ptr;

#if FASTMEM
    size = (size + sizeof(void *)-1) & ~(sizeof(void *)-1);
    if ( currfree < size ) {
        DebugMsg(("LclAlloc: new block needed, req. size=%Xh > currfree=%Xh\n", size, currfree ));
        currfree = ( size <= ( BLKSIZE - sizeof( struct linked_list ) ) ? BLKSIZE - sizeof( struct linked_list ) : size );
        BLKALLOC( pCurr, currfree + sizeof( struct linked_list ) );
        if ( !pCurr ) {
            currfree = 0;
            Fatal( OUT_OF_MEMORY );
        }
        ((struct linked_list *)pCurr)->next = pBase;
        pBase = (struct linked_list *)pCurr;
        pCurr += sizeof( struct linked_list );
        DebugCmd( blocks++ );
    }
    ptr = pCurr;
    pCurr += size;
    currfree -= size;

#else /* ! FASTMEM */

    ptr = malloc( size );
#ifdef TRMEM
    DebugMsg1(("LclAlloc(0x%X)=%p cnt=%" I32_SPEC "u\n", size, ptr, ++memcalls ));
#endif
    if( ptr == NULL ) {
        Fatal( OUT_OF_MEMORY );
    }
#endif

#ifdef _DEBUG
	memset(ptr, 0, size);
#endif

    return( ptr );
}

#if FASTMEM==0
void LclFree( void *ptr )
/***********************/
{
    if( ptr != NULL ) {
#ifdef TRMEM
        DebugMsg1(("LclFree(0x%p) cnt=%" I32_SPEC "u\n", ptr, --memcalls ));
#endif
        free( ptr );
    }
}
#endif

void *MemAlloc( size_t size )
/***************************/
{
    void        *ptr;
    ptr = malloc( size );
    DebugMsg1(("MemAlloc(0x%X)=%p cnt=%" I32_SPEC "u\n", size, ptr, ++memcalls ));
    if( ptr == NULL ) {
        Fatal( OUT_OF_MEMORY );
    }
#ifdef _DEBUG
    memset( ptr, 0x0, size );
#endif
    return( ptr );
}

void MemFree( void *ptr )
/***********************/
{
    DebugMsg1(("MemFree(0x%p) cnt=%" I32_SPEC "u\n", ptr, --memcalls ));
    free( ptr );
    return;
}

#if 0
void *MemRealloc( void *ptr, size_t size )
/****************************************/
{
    void *new;

    new = realloc( ptr, size );
    if( new == NULL && size != 0 ) {
        Fatal( OUT_OF_MEMORY );
    }
    return( new );
}
#endif
