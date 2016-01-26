/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:  ELF output routines
*
****************************************************************************/

#include <ctype.h>
#include <time.h>

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "mangle.h"
#include "fixup.h"
#include "segment.h"
#include "extern.h"
#include "elf.h"
#include "elfspec.h"
#include "myassert.h"

#if ELF_SUPPORT

/* v2.03: create weak externals for ALIAS symbols.
 * Since the syntax of the ALIAS directive requires
 * 2 names and, OTOH, the ELF implementation of weak 
 * externals has no "default resolution", the usefullness
 * of this option is questionable. Additionally, there's
 * the "EXTERN <name> (<altname>)" syntax, which also allows
 * to define a weak external.
 */
#define ELFALIAS 0

/* start label is always public for COFF/ELF, no need to add it */
#define ADDSTARTLABEL 0

/* there's no STT_IMPORT type for ELF, it's OW specific */
#define OWELFIMPORT 0

/* use GNU extensions for LD ( 16bit and 8bit relocations ) */
#define GNURELOCS 1

#define MANGLE_BYTES 8 /* extra size required for name decoration */

#define IsWeak( x ) ( x.iscomm == FALSE && x.altname )

/* section attributes for ELF
 *         execute write  alloc  type
 *---------------------------------------
 * CODE      x              x    progbits
 * CONST                    x    progbits
 * DATA              x      x    progbits
 * BSS               x      x    nobits
 * STACK             x      x    progbits
 * others            x      x    progbits
 *
 * todo: translate section bits:
 * - INFO    -> SHT_NOTE  (added in v2.07)
 * - DISCARD ->
 * - SHARED  ->
 * - EXECUTE -> SHF_EXECINSTR
 * - READ    ->
 * - WRITE   -> SHF_WRITE
 */

/* v2.12: global variables replaced by struct elfmod */
//static uint_32 symindex;       /* entries in symbol table */
//static uint_32 start_globals;  /* start index globals in symbol table */
//static char *srcname;          /* name of source module (name + extension) */
//static bool extused;

struct localname {
    void *next;
    struct asym *sym;
};

enum internal_sections {
    SHSTRTAB_IDX,
    SYMTAB_IDX,
    STRTAB_IDX,
    NUM_INTSEGS
};

struct intsegparm {
    const char *name;
    unsigned type;
};

/* constant parameters of internal sections; order must match enum internal_sections */
static const struct intsegparm internal_segparms[] = {
    { ".shstrtab", SHT_STRTAB },
    { ".symtab",   SHT_SYMTAB },
    { ".strtab",   SHT_STRTAB },
};

struct intseg {
    uint_32 size;
    uint_32 fileoffset;
    void *data;
};

//static struct intseg internal_segs[NUM_INTSEGS];

/* v2.12: all global variables replaced by struct elfmod */
struct elfmod {
    uint_32 symindex;       /* entries in symbol table */
    uint_32 start_globals;  /* start index globals in symbol table */
    char *srcname;          /* name of source module (name + extension) */
#if GNURELOCS
    bool extused;           /* gnu extensions used */
#endif
    struct intseg internal_segs[NUM_INTSEGS];
    union {
        Elf32_Ehdr ehdr32;
#if AMD64_SUPPORT
        Elf64_Ehdr ehdr64;
#endif
    };
};

/* struct to help convert section names in COFF, ELF, PE */
struct conv_section {
    uint_8 len;
    uint_8 flags; /* see below */
    const char *src;
    const char *dst;
};
enum cvs_flags {
    CSF_GRPCHK = 1
};

static const struct conv_section cst[] = {
    { 5, CSF_GRPCHK, "_TEXT", ".text"  },
    { 5, CSF_GRPCHK, "_DATA", ".data"  },
    { 5, CSF_GRPCHK, "CONST", ".rodata" }, /* v2.05: .rdata -> .rodata */
    { 4, 0,          "_BSS",  ".bss"   }
};


/* translate section names:
 * see cst[] above for details.
 */
static char *ElfConvertSectionName( const struct asym *sym, char *buffer )
/************************************************************************/
{
    int i;

    for ( i = 0; i < sizeof( cst ) / sizeof( cst[0] ); i++ ) {
        if ( memcmp( sym->name, cst[i].src, cst[i].len ) == 0 ) {
            if ( sym->name[cst[i].len] == NULLC )
                return( (char *)cst[i].dst );
            else if ( ( cst[i].flags & CSF_GRPCHK )  && sym->name[cst[i].len] == '$' ) {
                strcpy( buffer, cst[i].dst );
                strcat( buffer, sym->name+cst[i].len );
                return( buffer );
            }
        }
    }
    return( sym->name );
}

/* get number of sections that have relocations */

static int get_num_reloc_sections( void )
/***************************************/
{
    struct dsym    *curr;
    int num = 0;

    for( curr = SymTables[TAB_SEG].head; curr; curr = curr->next ) {
        if ( curr->e.seginfo->FixupList.head )
            num++;
    }
    return( num );
}

/* fill entries in ELF32 symbol table */

static uint_32 set_symtab32( struct elfmod *em, uint_32 entries, struct localname *localshead )
/*********************************************************************************************/
{
    uint_32   strsize = 1;
    uint_32   len;
    uint_8    stt;
    struct dsym   *curr;
    struct asym   *sym;
    struct localname *localscurr;
    struct qnode  *q;
    Elf32_Sym *p32;
    char      buffer[MAX_ID_LEN + MANGLE_BYTES + 1];

    em->internal_segs[SYMTAB_IDX].size = entries * sizeof( Elf32_Sym );
    em->internal_segs[SYMTAB_IDX].data = LclAlloc( em->internal_segs[SYMTAB_IDX].size );
    memset( em->internal_segs[SYMTAB_IDX].data, 0, em->internal_segs[SYMTAB_IDX].size );

    p32 = (Elf32_Sym *)em->internal_segs[SYMTAB_IDX].data;

    p32++; /* skip NULL entry */

    /* 1. make file entry */
    p32->st_name = strsize;  /* symbol's name in string table */
    strsize += strlen( em->srcname ) + 1;
    p32->st_value = 0;
    p32->st_size = 0;
    p32->st_info = ELF32_ST_INFO( STB_LOCAL, STT_FILE ); /* symbol's type and binding info */
    p32->st_shndx = SHN_ABS; /* section index */
    p32++;

    /* 2. make section entries */
    for( curr = SymTables[TAB_SEG].head; curr; curr = curr->next ) {
        //p32->st_name = ?;  /* name isn't set */
        p32->st_info = ELF32_ST_INFO( STB_LOCAL, STT_SECTION );
        p32->st_shndx = GetSegIdx( curr->sym.segment );
        p32++;
    }

    /* 3. locals */

    for ( localscurr = localshead ; localscurr ; localscurr = localscurr->next ) {
        len = Mangle( localscurr->sym, buffer );
        p32->st_name = strsize;
        curr = (struct dsym *)localscurr->sym->segment;
        if ( curr && curr->e.seginfo->segtype != SEGTYPE_CODE )
            stt = STT_OBJECT;
        else
            stt = STT_FUNC;
        p32->st_info = ELF32_ST_INFO( STB_LOCAL, stt );
        p32->st_value = localscurr->sym->offset;
#if 1 /* v2.07: changed - to make MT_ABS obsolete */
        if ( curr )
            p32->st_shndx = GetSegIdx( &curr->sym );
        else
            p32->st_shndx = SHN_ABS;
#else
        if ( localscurr->sym->mem_type == MT_ABS )
            p32->st_shndx = SHN_ABS;
        else
            p32->st_shndx = GetSegIdx( &curr->sym );
#endif
        strsize += len + 1;
        DebugMsg(("set_symtab32, LOCAL: symbol %s, value=%X\n", buffer, p32->st_value));
        p32++;
    }

    /* 4. externals + communals (+ protos [since v2.01]) */

    for( curr = SymTables[TAB_EXT].head ; curr != NULL ;curr = curr->next ) {
        /* skip "weak" (=unused) externdefs */
        if ( curr->sym.iscomm == FALSE && curr->sym.weak == TRUE )
            continue;
        len = Mangle( &curr->sym, buffer );

        p32->st_name = strsize;

        /* for COMMUNALs, store their size in the Value field */
        if ( curr->sym.iscomm == TRUE ) {
            p32->st_info = ELF32_ST_INFO( STB_GLOBAL, STT_COMMON );
            p32->st_value = curr->sym.total_size;
            p32->st_shndx = SHN_COMMON;
        } else {
#if OWELFIMPORT
            p32->st_info = ( IsWeak( curr->sym ) ? ELF32_ST_INFO( STB_WEAK, STT_IMPORT ) : ELF32_ST_INFO( STB_GLOBAL, STT_IMPORT ) );
#else
            /* todo: set STT_FUNC for prototypes/code labels??? */
            p32->st_info = ( IsWeak( curr->sym ) ? ELF32_ST_INFO( STB_WEAK, STT_NOTYPE ) : ELF32_ST_INFO( STB_GLOBAL, STT_NOTYPE ) );
#endif
            p32->st_value = curr->sym.offset; /* is always 0 */
            p32->st_shndx = SHN_UNDEF;
        }

        strsize += len + 1;
        DebugMsg(("set_symtab32, EXTERNAL: symbol %s, info=%X, shndx=%X, value=%X\n", buffer, p32->st_info, p32->st_shndx, p32->st_value));
        p32++;
    }

#if ELFALIAS
    /* 5. aliases */
    for( curr = SymTables[TAB_ALIAS].head ; curr != NULL ;curr = curr->next ) {
        len = Mangle( &curr->sym, buffer );

        p32->st_name = strsize;

#if OWELFIMPORT
        p32->st_info = ELF32_ST_INFO( STB_WEAK, STT_IMPORT );
#else
        p32->st_info = ELF32_ST_INFO( STB_WEAK, STT_NOTYPE );
#endif
        p32->st_value = 0; /* is always 0 */
        p32->st_shndx = SHN_UNDEF;

        strsize += len + 1;
        DebugMsg(("set_symtab32, ALIAS: symbol %s, value=%X\n", buffer, p32->st_value));
        p32++;
    }
#endif

    /* 6. PUBLIC entries */
    for ( q = ModuleInfo.g.PubQueue.head; q; q = q->next ) {
        sym = q->sym;
        len = Mangle( sym, buffer );

        curr = (struct dsym *)sym->segment;
        if ( curr && curr->e.seginfo->segtype != SEGTYPE_CODE )
            stt = STT_OBJECT;
        else
            stt = STT_FUNC;

        p32->st_name = strsize;
        p32->st_info = ELF32_ST_INFO( STB_GLOBAL, stt );
        p32->st_value = sym->offset;
#if 1 /* v2.07: changed - to make MT_ABS obsolete */
        if ( sym->state == SYM_INTERNAL )
            if ( curr )
                p32->st_shndx = GetSegIdx( &curr->sym );
            else
                p32->st_shndx = SHN_ABS;
        else
            p32->st_shndx = SHN_UNDEF;
#else
        if ( sym->mem_type == MT_ABS )
            p32->st_shndx = SHN_ABS;
        else if ( curr )
            p32->st_shndx = GetSegIdx( &curr->sym );
        else
            p32->st_shndx = SHN_UNDEF;
#endif
        strsize += len + 1;

        DebugMsg(("set_symtab32, PUBLIC+LOCAL: symbol %s, value=%X\n", buffer, p32->st_value));

        p32++;
    }
#if ADDSTARTLABEL
    if ( ModuleInfo.g.start_label ) {
        len = Mangle( ModuleInfo.g.start_label, buffer );
        p32->st_name = strsize;
        p32->st_info = ELF32_ST_INFO( STB_ENTRY, STT_FUNC );
        p32->st_value = ModuleInfo.g.start_label->offset;
        p32->st_shndx = GetSegIdx( ModuleInfo.g.start_label->segment );
        strsize += len + 1;
        DebugMsg(("set_symtab32, ENTRY: symbol %s, value=%X\n", buffer, p32->st_value));
        p32++;
    }
#endif
    return( strsize );
}

#if AMD64_SUPPORT

/* fill entries in ELF64 symbol table:
 typedef struct {
    uint_32  st_name;        //  +0 symbol name index into string table
    uint_8   st_info;        //  +4 symbol's type and binding attribs.
    uint_8   st_other;       //  +5 no meaning yet.
    uint_16  st_shndx;       //  +6 section index
    uint_64  st_value;       //  +8 symbol "value"
    uint_64  st_size;        // +16 symbol size
} Elf64_Sym;
 */

static uint_32 set_symtab64( struct elfmod *em, uint_32 entries, struct localname *localshead )
/*********************************************************************************************/
{
    uint_32   strsize = 1;
    uint_32   len;
    uint_8    stt;
    struct dsym   *curr;
    struct asym   *sym;
    struct localname *localscurr;
    struct qnode  *q;
    Elf64_Sym *p64;
    char      buffer[MAX_ID_LEN + MANGLE_BYTES + 1];

    em->internal_segs[SYMTAB_IDX].size = entries * sizeof( Elf64_Sym );
    em->internal_segs[SYMTAB_IDX].data = LclAlloc( em->internal_segs[SYMTAB_IDX].size );
    memset( em->internal_segs[SYMTAB_IDX].data, 0, em->internal_segs[SYMTAB_IDX].size );

    p64 = (Elf64_Sym *)em->internal_segs[SYMTAB_IDX].data;

    p64++; /* skip NULL entry */

    /* 1. make file entry */
    p64->st_name = strsize;  /* symbol's name in string table */
    strsize += strlen( em->srcname ) + 1;
    p64->st_value = 0;
    p64->st_size = 0;
    p64->st_info = ELF64_ST_INFO( STB_LOCAL, STT_FILE ); /* symbol's type and binding info */
    p64->st_shndx = SHN_ABS; /* section index */
    p64++;

    /* 2. make section entries */
    for( curr = SymTables[TAB_SEG].head; curr; curr = curr->next ) {
        //p64->st_name = ?;  /* name isn't set */
        p64->st_info = ELF64_ST_INFO( STB_LOCAL, STT_SECTION );
        p64->st_shndx = GetSegIdx( curr->sym.segment );
        p64++;
    }

    /* 3. locals */

    for ( localscurr = localshead ; localscurr ; localscurr = localscurr->next ) {
        len = Mangle( localscurr->sym, buffer );
        p64->st_name = strsize;
        curr = (struct dsym *)localscurr->sym->segment;
        if ( curr && curr->e.seginfo->segtype != SEGTYPE_CODE )
            stt = STT_OBJECT;
        else
            stt = STT_FUNC;
        p64->st_info = ELF64_ST_INFO( STB_LOCAL, stt );
        p64->st_value = localscurr->sym->offset;
#if 1 /* v2.07: changed - to make MT_ABS obsolete */
        if ( curr )
            p64->st_shndx = GetSegIdx( &curr->sym );
        else
            p64->st_shndx = SHN_ABS;
#else
        if ( localscurr->sym->mem_type == MT_ABS )
            p64->st_shndx = SHN_ABS;
        else
            p64->st_shndx = GetSegIdx( &curr->sym );
#endif
        strsize += len + 1;
        DebugMsg(("set_symtab64, LOCAL: symbol %s, value=%" I64_SPEC "X\n", buffer, p64->st_value));
        p64++;
    }

    /* 4. externals + communals ( + protos [since v2.01]) */

    for( curr = SymTables[TAB_EXT].head ; curr != NULL ;curr = curr->next ) {
        /* skip "weak" (=unused) externdefs */
        if ( curr->sym.iscomm == FALSE && curr->sym.weak == TRUE )
            continue;
        len = Mangle( &curr->sym, buffer );

        p64->st_name = strsize;

        /* for COMMUNALs, store their size in the Value field */
        if ( curr->sym.iscomm == TRUE ) {
            p64->st_info = ELF64_ST_INFO( STB_GLOBAL, STT_COMMON );
            p64->st_value = curr->sym.total_size;
            p64->st_shndx = SHN_COMMON;
        } else {
#if OWELFIMPORT
            p64->st_info = ( IsWeak( curr->sym ) ? ELF64_ST_INFO( STB_WEAK, STT_IMPORT ) : ELF64_ST_INFO( STB_GLOBAL, STT_IMPORT ) );
#else
            /* todo: set STT_FUNC for prototypes??? */
            p64->st_info = ( IsWeak( curr->sym ) ? ELF64_ST_INFO( STB_WEAK, STT_NOTYPE ) : ELF64_ST_INFO( STB_GLOBAL, STT_NOTYPE ) );
#endif
            p64->st_value = curr->sym.offset; /* is always 0 */
            p64->st_shndx = SHN_UNDEF;
        }

        strsize += len + 1;
        DebugMsg(("set_symtab64, EXTERNAL: symbol %s, info=%X, shndx=%X, value=%" I64_SPEC "X\n", buffer, p64->st_info, p64->st_shndx, p64->st_value));
        p64++;
    }

#if ELFALIAS
    /* 5. aliases */

    for( curr = SymTables[TAB_ALIAS].head ; curr != NULL ;curr = curr->next ) {
        len = Mangle( &curr->sym, buffer );

        p64->st_name = strsize;

#if OWELFIMPORT
        p64->st_info = ELF64_ST_INFO( STB_WEAK, STT_IMPORT );
#else
        p64->st_info = ELF64_ST_INFO( STB_WEAK, STT_NOTYPE );
#endif
        p64->st_value = 0; /* is always 0 */
        p64->st_shndx = SHN_UNDEF;

        strsize += len + 1;
        DebugMsg(("set_symtab64, ALIASES: symbol %s, value=%" I64_SPEC "X\n", buffer, p64->st_value));
        p64++;
    }
#endif

    /* 6. PUBLIC entries */
    for ( q = ModuleInfo.g.PubQueue.head; q; q = q->next ) {
        sym = q->sym;
        len = Mangle( sym, buffer );

        curr = (struct dsym *)sym->segment;
        if ( curr && curr->e.seginfo->segtype != SEGTYPE_CODE )
            stt = STT_OBJECT;
        else
            stt = STT_FUNC;

        p64->st_name = strsize;
        p64->st_info = ELF64_ST_INFO( STB_GLOBAL, stt );
        p64->st_value = sym->offset;
#if 1 /* v2.07: changed - to make MT_ABS obsolete */
        if ( sym->state == SYM_INTERNAL )
            if ( curr )
                p64->st_shndx = GetSegIdx( &curr->sym );
            else
                p64->st_shndx = SHN_ABS;
        else
            p64->st_shndx = SHN_UNDEF;
#else
        if ( sym->mem_type == MT_ABS )
            p64->st_shndx = SHN_ABS;
        else if ( curr )
            p64->st_shndx = GetSegIdx( &curr->sym );
        else
            p64->st_shndx = SHN_UNDEF;
#endif
        strsize += len + 1;

        DebugMsg(("set_symtab64, PUBLIC+LOCAL: symbol %s, info=%X, shndx=%X, value=%" I64_SPEC "X\n", buffer, p64->st_info, p64->st_shndx, p64->st_value));

        p64++;
    }
#if ADDSTARTLABEL
    if ( ModuleInfo.g.start_label ) {
        len = Mangle( ModuleInfo.g.start_label, buffer );
        p64->st_name = strsize;
        p64->st_info = ELF64_ST_INFO( STB_ENTRY, STT_FUNC );
        p64->st_value = ModuleInfo.g.start_label->offset;
        p64->st_shndx = GetSegIdx( ModuleInfo.g.start_label->segment );
        strsize += len + 1;
        DebugMsg(("set_symtab64, ENTRY: symbol %s, value=%" I64_SPEC "X\n", buffer, p64->st_value));
        p64++;
    }
#endif
    return( strsize );
}
#endif

/* calculate size of .symtab + .strtab section.
 * set content of these sections.
 */
static void set_symtab_values( struct elfmod *em )
/************************************************/
{
    uint_32 strsize;
    uint_32 entries;
    struct dsym *curr;
    //struct asym *sym;
    struct qnode *q;
    char *p2;
    struct {
        struct localname *head;
        struct localname *tail;
    } locals = { NULL, NULL };
    struct localname *localscurr;

    /* symbol table. there is
     - 1 NULL entry,
     - 1 entry for the module/file,
     - 1 entry for each section and
     - n entries for local symbols
     - m entries for global symbols
     */

    /* symbol table starts with 1 NULL entry + 1 file entry */
    em->symindex = 1 + 1;

    for( curr = SymTables[TAB_SEG].head; curr; curr = curr->next )
        curr->sym.ext_idx = em->symindex++;

    /* add local symbols to symbol table */

    for( curr = SymTables[TAB_SEG].head; curr; curr = curr->next ) {
        if ( curr->e.seginfo->num_relocs ) {
            struct fixup *fix = curr->e.seginfo->FixupList.head;
            for ( ; fix; fix = fix->nextrlc ) {
                /* if it's not EXTERNAL/PUBLIC, add symbol. */
                /* however, if it's an assembly time variable */
                /* use a raw section reference */
                if ( fix->sym->variable ) {
                    fix->sym = fix->segment_var;
                } else if ( ( fix->sym->state == SYM_INTERNAL ) &&
                    fix->sym->included == FALSE &&
                    fix->sym->ispublic == FALSE ) {
                    fix->sym->included = TRUE;
                    localscurr = LclAlloc( sizeof( struct localname ) );
                    localscurr->next = NULL;
                    localscurr->sym = fix->sym;
                    if (locals.tail) {
                        locals.tail->next = localscurr;
                        locals.tail = localscurr;
                    } else {
                        locals.head = locals.tail = localscurr;
                    }
                    fix->sym->ext_idx = em->symindex++;
                }
            }
        }
    }
    DebugMsg(("set_symtab_values: index after sections: %u\n", em->symindex));
    em->start_globals = em->symindex;

    /* count EXTERNs and used EXTERNDEFs (and PROTOs [since v2.01]) */
    for( curr = SymTables[TAB_EXT].head ; curr != NULL ;curr = curr->next ) {
        if ( curr->sym.iscomm == FALSE && curr->sym.weak == TRUE )
            continue;
        curr->sym.ext_idx = em->symindex++;
    }
    DebugMsg(("set_symtab_values: index after EXTERNALs: %u\n", em->symindex));

#if ELFALIAS
    /* count aliases */
    for( curr = SymTables[TAB_ALIAS].head ; curr != NULL ;curr = curr->next ) {
        curr->sym.idx = em->symindex++;
    }
    DebugMsg(("set_symtab_values: index after ALIASES: %u\n", em->symindex));
#endif

    /* count publics */
    for ( q = ModuleInfo.g.PubQueue.head; q; q = q->next ) {
        q->sym->ext_idx = em->symindex++;
    }
    DebugMsg(("set_symtab_values: index after PUBLICs: %u\n", em->symindex));

    /* size of symbol table is defined */
    entries = em->symindex;

#if ADDSTARTLABEL
    if ( ModuleInfo.g.start_label )
        entries++;
#endif

#if AMD64_SUPPORT
    if ( ModuleInfo.defOfssize == USE64 )
        strsize = set_symtab64( em, entries, locals.head );
    else
#endif
        strsize = set_symtab32( em, entries, locals.head );

    /* generate the string table */
    DebugMsg(("set_symtab_values: creating string table, size=%X\n", strsize));

    em->internal_segs[STRTAB_IDX].size = strsize;
    em->internal_segs[STRTAB_IDX].data = LclAlloc( strsize );
    memset( em->internal_segs[STRTAB_IDX].data, 0, strsize );
    p2 = em->internal_segs[STRTAB_IDX].data;
    *p2++ = NULLC;

    strcpy( p2, em->srcname );
    p2 += strlen( p2 ) + 1;

    for ( localscurr = locals.head ; localscurr ; localscurr = localscurr->next ) {
        p2 += Mangle( localscurr->sym, p2 ) + 1;
    }

    for( curr = SymTables[TAB_EXT].head ; curr != NULL ;curr = curr->next ) {
        if ( curr->sym.iscomm == FALSE && curr->sym.weak == TRUE )
            continue;
        p2 += Mangle( &curr->sym, p2 ) + 1;
    }

#if ELFALIAS
    for( curr = SymTables[TAB_ALIAS].head ; curr != NULL ;curr = curr->next ) {
        p2 += Mangle( &curr->sym, p2 ) + 1;
    }
#endif

    for ( q = ModuleInfo.g.PubQueue.head; q; q = q->next ) {
        p2 += Mangle( q->sym, p2 ) + 1;
    }
#if ADDSTARTLABEL
    if ( ModuleInfo.g.start_label ) {
        Mangle( ModuleInfo.g.start_label, p2 );
    }
#endif
    DebugMsg(("set_symtab_values: exit, symindex=%u\n", em->symindex ));
    return;
}

/* set content + size of .shstrtab section.
 * this section contains the names of all sections.
 * three groups of sections are handled:
 * - sections defined in the program
 * - ELF internal sections
 * - relocation sections
 * alloc .shstrtab
 */
static void set_shstrtab_values( struct elfmod *em )
/**************************************************/
{
    int         i;
    struct dsym *curr;
    char        *p;
    unsigned int size = 1; /* the first byte at offset 0 is the NULL section name */
    char buffer[MAX_ID_LEN+1];

    /* get size of section names defined in the program & relocation sections ) */
    for( curr = SymTables[TAB_SEG].head; curr; curr = curr->next ) {
        /* v2.07: ALIAS name defined? */
        p = ( curr->e.seginfo->aliasname ? curr->e.seginfo->aliasname : ElfConvertSectionName( &curr->sym, buffer ) );
        size += strlen( p ) + 1;
        if ( curr->e.seginfo->FixupList.head )
            size += strlen( p ) +
#if AMD64_SUPPORT
                (( ModuleInfo.defOfssize == USE64 ) ? sizeof(".rela") : sizeof(".rel"));
#else
                sizeof(".rel");
#endif
    }
    /* get internal section name sizes */
    for ( i = 0; i < NUM_INTSEGS; i++ ) {
        size += strlen( internal_segparms[i].name ) + 1;
    }

    em->internal_segs[SHSTRTAB_IDX].size = size;

    /* size is known, now alloc .shstrtab data buffer and fill it */

    em->internal_segs[SHSTRTAB_IDX].data = LclAlloc( size );
    p = (char *)em->internal_segs[SHSTRTAB_IDX].data;
    *p++ = NULLC; /* NULL section name */

    /* 1. names of program sections */
    for( curr = SymTables[TAB_SEG].head; curr; curr = curr->next ) {
        strcpy( p, curr->e.seginfo->aliasname ? curr->e.seginfo->aliasname : ElfConvertSectionName( &curr->sym, buffer ) );
        p += strlen( p ) + 1;
    }
    /* 2. names of internal sections */
    for ( i = 0; i < NUM_INTSEGS; i++ ) {
        strcpy( p, internal_segparms[i].name );
        p += strlen( p ) + 1;
    }
    /* 3. names of "relocation" sections */
    for( curr = SymTables[TAB_SEG].head; curr; curr = curr->next ) {
        if ( curr->e.seginfo->FixupList.head ) {
#if AMD64_SUPPORT
            strcpy( p, (( ModuleInfo.defOfssize == USE64 ) ? ".rela": ".rel") );
#else
            strcpy( p, ".rel" );
#endif
            p += strlen( p );
            strcpy( p, curr->e.seginfo->aliasname ? curr->e.seginfo->aliasname : ElfConvertSectionName( &curr->sym, buffer ) );
            p += strlen( p ) + 1;
        }
    }
    /**/myassert( size == p - (char *)em->internal_segs[SHSTRTAB_IDX].data );
    DebugMsg(("set_shstrtab_values: size=%X\n", size));
    return;
}

static unsigned int get_relocation_count( struct dsym *curr )
/***********************************************************/
{
    unsigned relocs;
    struct fixup *fix;

    for ( relocs = 0, fix = curr->e.seginfo->FixupList.head; fix ; fix = fix->nextrlc, relocs++ );

    return( relocs );
}

static unsigned int Get_Alignment( struct dsym *curr )
/****************************************************/
{
    if ( curr->e.seginfo->alignment == MAX_SEGALIGNMENT )
        return( 0 );
    return( 1 << curr->e.seginfo->alignment );
}

/* write ELF32 section table.
 * fileoffset: start of section data ( behind elf header and section table )
 * there are 3 groups of sections to handle:
 * - the sections defined in the module
 * - the internal ELF sections ( .shstrtab, .symtab, .strtab )
 * - the 'relocation' sections
 */

static int elf_write_section_table32( struct module_info *modinfo, struct elfmod *em, uint_32 fileoffset )
/********************************************************************************************************/
{
    int         i;
    struct dsym *curr;
    uint_8      *p;
    //uint_32     fileoffset;
    Elf32_Shdr  shdr32;

    DebugMsg(("elf_write_section_table32( fileofs=%X ): enter\n", fileoffset ));

    //fileoffset = sizeof(Elf64_Ehdr) + ehdr->e_shnum * ehdr->e_shentsize;
    fileoffset = (fileoffset + 0xF) & ~0xF;

    /* set contents and size of internal .shstrtab section */
    set_shstrtab_values( em );

    /* write the NULL entry */
    memset( &shdr32, 0, sizeof( shdr32) );
    if ( fwrite( &shdr32, 1, sizeof(shdr32), CurrFile[OBJ] ) != sizeof(shdr32) ) /* write the empty NULL entry */
        WriteError();

    /* use p to scan strings (=section names) of .shstrtab */
    p = (uint_8 *)em->internal_segs[SHSTRTAB_IDX].data;
    p++; /* skip 'name' of NULL entry */

    /* write the section headers defined in the module, */
    for( curr = SymTables[TAB_SEG].head; curr; curr = curr->next ) {

        memset( &shdr32, 0, sizeof(shdr32) );

        shdr32.sh_name = p - (uint_8 *)em->internal_segs[SHSTRTAB_IDX].data;
        p += strlen( (char *)p ) + 1;
        if ( curr->e.seginfo->info == TRUE ) { /* v2.07:added; v2.12: highest priority */
            shdr32.sh_type = SHT_NOTE;
            shdr32.sh_flags = 0;
        } else {
            shdr32.sh_type = ( curr->e.seginfo->segtype != SEGTYPE_BSS ? SHT_PROGBITS : SHT_NOBITS );
            if ( curr->e.seginfo->segtype == SEGTYPE_CODE ) {
                shdr32.sh_flags = SHF_EXECINSTR | SHF_ALLOC;
            } else if ( curr->e.seginfo->readonly == TRUE ) {
                shdr32.sh_flags = SHF_ALLOC;
            } else if ( curr->e.seginfo->clsym && strcmp( curr->e.seginfo->clsym->name, "CONST" ) == 0 ) {
                shdr32.sh_flags = SHF_ALLOC; /* v2.07: added */
            } else {
                shdr32.sh_flags = SHF_WRITE | SHF_ALLOC;
            }
        }
#if 0
        /* todo: translate values in field <characteristics> to
         * elf section flags.
         */
        if ( curr->e.seginfo->characteristics == ??? ) {
        }
#endif
        shdr32.sh_addr = 0;
        /* v2.12: the sh_offset field holds the file position, even for SHT_NOBITS */
        //if ( shdr32.sh_type != SHT_NOBITS ) {
            shdr32.sh_offset = fileoffset; /* start of section in file */
            curr->e.seginfo->fileoffset = fileoffset; /* save the offset in the segment */
        //}
        /* v2.07: set size for all sections, including .bss */
        shdr32.sh_size = curr->sym.max_offset;
        shdr32.sh_link = 0;
        shdr32.sh_info = 0;
        shdr32.sh_addralign = Get_Alignment( curr );
        shdr32.sh_entsize = 0;

        if ( fwrite( &shdr32, 1, sizeof(shdr32), CurrFile[OBJ] ) != sizeof(shdr32) )
            WriteError();
        curr->e.seginfo->num_relocs = get_relocation_count( curr );

        /* v2.12: don't adjust fileoffset for SHT_NOBITS sections.
         * it didn't cause fatal damage previously, but made the
         * object module unnecessary large.
         */
        if ( shdr32.sh_type != SHT_NOBITS ) {
            fileoffset += shdr32.sh_size;
            fileoffset = (fileoffset + 0xF) & ~0xF;
        }

        DebugMsg(("elf_write_section_table32(%s): ofs=%X size=%X numrelocs=%u\n", curr->sym.name, shdr32.sh_offset, shdr32.sh_size, curr->e.seginfo->num_relocs));
    }

    /* set size and contents of .symtab and .strtab sections */
    set_symtab_values( em );

    /* write headers of internal sections */
    for ( i = 0; i < NUM_INTSEGS; i++ ) {
        shdr32.sh_name = p - (uint_8 *)em->internal_segs[SHSTRTAB_IDX].data;
        p += strlen( (char *)p ) + 1;
        shdr32.sh_type = internal_segparms[i].type;
        shdr32.sh_flags = 0;
        shdr32.sh_offset = fileoffset; /* start of section in file */
        em->internal_segs[i].fileoffset = fileoffset;
        shdr32.sh_size = em->internal_segs[i].size;
        /* section .symtab is special */
        if ( i == SYMTAB_IDX ) {
            shdr32.sh_link = 1 + modinfo->g.num_segs + STRTAB_IDX;
            shdr32.sh_info = em->start_globals;
            shdr32.sh_addralign = 4;
            shdr32.sh_entsize = sizeof( Elf32_Sym );
        } else {
            shdr32.sh_link = 0;
            shdr32.sh_info = 0;
            shdr32.sh_addralign = 1;
            shdr32.sh_entsize = 0;
        }
        if ( fwrite( &shdr32, 1, sizeof( shdr32 ), CurrFile[OBJ] ) != sizeof( shdr32 ) )
            WriteError();

        fileoffset += shdr32.sh_size;
        fileoffset = (fileoffset + 0xF) & ~0xF;
        DebugMsg(("elf_write_section_table32(%s): ofs=%X size=%X\n", internal_segparms[i].name, shdr32.sh_offset, shdr32.sh_size));
    }

    /* write headers of reloc sections */
    for( curr = SymTables[TAB_SEG].head; curr; curr = curr->next ) {
        if ( curr->e.seginfo->FixupList.head == NULL )
            continue;

        memset( &shdr32, 0, sizeof( shdr32 ) );

        shdr32.sh_name = p - (uint_8 *)em->internal_segs[SHSTRTAB_IDX].data;
        p += strlen( (char *)p ) + 1;
        shdr32.sh_type = SHT_REL;
        shdr32.sh_flags = 0;
        shdr32.sh_addr = 0;
        shdr32.sh_offset = fileoffset; /* start of section in file */
        /* save the file offset in the slot reserved for ELF relocs */
        curr->e.seginfo->reloc_offset = fileoffset;
        /* size of section in file */
        shdr32.sh_size = curr->e.seginfo->num_relocs * sizeof( Elf32_Rel );
        shdr32.sh_link = 1 + modinfo->g.num_segs + SYMTAB_IDX;
        /* set info to the src section index */
        shdr32.sh_info = GetSegIdx( curr->sym.segment );
        shdr32.sh_addralign = 4;
        shdr32.sh_entsize = sizeof( Elf32_Rel );

        if ( fwrite( &shdr32, 1, sizeof( shdr32 ), CurrFile[OBJ] ) != sizeof( shdr32 ) )
            WriteError();

        fileoffset += shdr32.sh_size;
        fileoffset = (fileoffset + 0xF) & ~0xF;
        DebugMsg(("elf_write_section_table32(%s): relocs, ofs=%X size=%X\n", curr->sym.name, shdr32.sh_offset, shdr32.sh_size));

    }
    DebugMsg(("elf_write_section_table32: exit, final fileofs=%X\n", fileoffset ));
    return( NOT_ERROR );
}

#if AMD64_SUPPORT

/* write ELF64 section table. */

static int elf_write_section_table64( struct module_info *modinfo, struct elfmod *em, uint_32 fileoffset )
/********************************************************************************************************/
{
    int         i;
    struct dsym *curr;
    uint_8      *p;
    //uint_32     fileoffset;
    Elf64_Shdr  shdr64;

    DebugMsg(("elf_write_section_table64( fileofs=%X ): enter\n", fileoffset ));

    //fileoffset = sizeof(Elf64_Ehdr) + ehdr->e_shnum * ehdr->e_shentsize;
    fileoffset = (fileoffset + 0xF) & ~0xF;

    /* set contents and size of internal .shstrtab section */
    set_shstrtab_values( em );

    /* write the NULL entry */
    memset( &shdr64, 0, sizeof( shdr64) );
    if ( fwrite( &shdr64, 1, sizeof(shdr64), CurrFile[OBJ] ) != sizeof(shdr64) ) /* write the empty NULL entry */
        WriteError();

    /* use p to scan strings (=section names) of .shstrtab */
    p = (uint_8 *)em->internal_segs[SHSTRTAB_IDX].data;
    p++; /* skip 'name' of NULL entry */

    /* write the section headers defined in the module */
    for( curr = SymTables[TAB_SEG].head; curr; curr = curr->next ) {

        memset( &shdr64, 0, sizeof(shdr64) );

        shdr64.sh_name = p - (uint_8 *)em->internal_segs[SHSTRTAB_IDX].data;
        p += strlen( (char *)p ) + 1;
        if ( curr->e.seginfo->info == TRUE ) { /* v2.07:added; v2.12: highest priority */
            shdr64.sh_type = SHT_NOTE;
            shdr64.sh_flags = 0;
        } else {
            shdr64.sh_type = ( curr->e.seginfo->segtype != SEGTYPE_BSS ? SHT_PROGBITS : SHT_NOBITS );
            if ( curr->e.seginfo->segtype == SEGTYPE_CODE ) {
                shdr64.sh_flags = SHF_EXECINSTR | SHF_ALLOC;
            } else if ( curr->e.seginfo->readonly == TRUE ) {
                shdr64.sh_flags = SHF_ALLOC;
            } else if ( curr->e.seginfo->clsym && strcmp( curr->e.seginfo->clsym->name, "CONST" ) == 0 ) {
                shdr64.sh_flags = SHF_ALLOC; /* v2.07: added */
            } else {
                shdr64.sh_flags = SHF_WRITE | SHF_ALLOC;
            }
        }
#if 0
        /* todo: translate values in field <characteristics> to
         * elf section flags.
         */
        if ( curr->e.seginfo->characteristics == ??? ) {
        }
#endif
        shdr64.sh_addr = 0;
        /* v2.12: the sh_offset field holds the file position, even for SHT_NOBITS */
        //if ( shdr64.sh_type != SHT_NOBITS ) {
            shdr64.sh_offset = fileoffset; /* start of section in file */
            curr->e.seginfo->fileoffset = fileoffset; /* save the offset in the segment */
        //}
        /* v2.07: set size for all sections, including .bss */
        shdr64.sh_size = curr->sym.max_offset;
        shdr64.sh_link = 0;
        shdr64.sh_info = 0;
        shdr64.sh_addralign = Get_Alignment( curr );
        shdr64.sh_entsize = 0;

        if ( fwrite( &shdr64, 1, sizeof(shdr64), CurrFile[OBJ] ) != sizeof(shdr64) )
            WriteError();
        curr->e.seginfo->num_relocs = get_relocation_count( curr );

        /* v2.12: don't adjust fileoffset for SHT_NOBITS sections */
        if ( shdr64.sh_type != SHT_NOBITS ) {
            fileoffset += shdr64.sh_size;
            fileoffset = (fileoffset + 0xF) & ~0xF;
        }

        DebugMsg(("elf_write_section_table64(%s): ofs=%" I64_SPEC "X size=%" I64_SPEC "X numrelocs=%u\n", curr->sym.name, shdr64.sh_offset, shdr64.sh_size, curr->e.seginfo->num_relocs));
    }

    /* set size and contents of .symtab and .strtab sections */
    set_symtab_values( em );

    /* write headers of internal sections */
    for ( i = 0; i < NUM_INTSEGS; i++ ) {

        shdr64.sh_name = p - (uint_8 *)em->internal_segs[SHSTRTAB_IDX].data;
        p += strlen( (char *)p ) + 1;
        shdr64.sh_type = internal_segparms[i].type;
        shdr64.sh_flags = 0;
        shdr64.sh_offset = fileoffset; /* start of section in file */
        em->internal_segs[i].fileoffset = fileoffset;
        shdr64.sh_size = em->internal_segs[i].size;
        /* section .symtab is special */
        if ( i == SYMTAB_IDX ) {
            shdr64.sh_link = 1 + modinfo->g.num_segs + STRTAB_IDX;
            shdr64.sh_info = em->start_globals;
            shdr64.sh_addralign = 4;
            shdr64.sh_entsize = sizeof( Elf64_Sym );
        } else {
            shdr64.sh_link = 0;
            shdr64.sh_info = 0;
            shdr64.sh_addralign = 1;
            shdr64.sh_entsize = 0;
        }
        if ( fwrite( &shdr64, 1, sizeof( shdr64 ), CurrFile[OBJ] ) != sizeof( shdr64 ) )
            WriteError();

        fileoffset += shdr64.sh_size;
        fileoffset = (fileoffset + 0xF) & ~0xF;
        DebugMsg(("elf_write_section_table64(%s): ofs=%" I64_SPEC "X size=%" I64_SPEC "X\n", internal_segparms[i].name, shdr64.sh_offset, shdr64.sh_size));
    }

    /* write headers of reloc sections */
    for( curr = SymTables[TAB_SEG].head; curr; curr = curr->next ) {
        if ( curr->e.seginfo->FixupList.head == NULL )
            continue;

        memset( &shdr64, 0, sizeof(shdr64) );

        shdr64.sh_name = p - (uint_8 *)em->internal_segs[SHSTRTAB_IDX].data;
        p += strlen( (char *)p ) + 1;
        shdr64.sh_type = SHT_RELA; /* v2.05: changed REL to RELA */
        shdr64.sh_flags = 0;
        shdr64.sh_addr = 0;
        shdr64.sh_offset = fileoffset; /* start of section in file */
        /* save the file offset in the slot reserved for ELF relocs */
        curr->e.seginfo->reloc_offset = fileoffset;
        /* size of section in file */
        shdr64.sh_size = curr->e.seginfo->num_relocs * sizeof( Elf64_Rela );
        shdr64.sh_link = 1 + modinfo->g.num_segs + SYMTAB_IDX;
        /* set info to the src section index */
        shdr64.sh_info = GetSegIdx( curr->sym.segment );
        shdr64.sh_addralign = 4;
        shdr64.sh_entsize = sizeof( Elf64_Rela );

        if ( fwrite( &shdr64, 1, sizeof( shdr64 ), CurrFile[OBJ] ) != sizeof( shdr64 ) )
            WriteError();

        fileoffset += shdr64.sh_size;
        fileoffset = (fileoffset + 0xF) & ~0xF;
        DebugMsg(("elf_write_section_table64(%s): relocs, ofs=%" I64_SPEC "X size=%" I64_SPEC "X\n", curr->sym.name, shdr64.sh_offset, shdr64.sh_size));
    }
    DebugMsg(("elf_write_section_table64: exit, final fileofs=%X\n", fileoffset ));
    return( NOT_ERROR );
}
#endif

/* write 1 section's relocations (32-bit) */

static void write_relocs32( struct elfmod *em, struct dsym *curr )
/****************************************************************/
{
    uint_8 elftype;
    struct fixup *fixup;
    Elf32_Rel reloc32;

    DebugMsg(("write_relocs32: enter\n"));
    for ( fixup = curr->e.seginfo->FixupList.head; fixup; fixup = fixup->nextrlc ) {
        reloc32.r_offset = fixup->locofs;
        switch ( fixup->type ) {
        case FIX_OFF32:         elftype = R_386_32;             break;
        case FIX_RELOFF32:      elftype = R_386_PC32;           break;
        //case FIX_???:         elftype = R_386_GOT32;          break;
        //case FIX_???:         elftype = R_386_PLT32;          break;
        //case FIX_???:         elftype = R_386_COPY;           break;
        //case FIX_???:         elftype = R_386_GLOB_DAT;       break;
        //case FIX_???:         elftype = R_386_JMP_SLOT;       break;
        case FIX_OFF32_IMGREL:  elftype = R_386_RELATIVE;       break;
        //case FIX_???:         elftype = R_386_GOTOFF;         break;
        //case FIX_???:         elftype = R_386_GOTPC;          break;
#if GNURELOCS
        case FIX_OFF16:    em->extused = TRUE; elftype = R_386_16;   break;
        case FIX_RELOFF16: em->extused = TRUE; elftype = R_386_PC16; break;
        case FIX_OFF8:     em->extused = TRUE; elftype = R_386_8;    break;
        case FIX_RELOFF8:  em->extused = TRUE; elftype = R_386_PC8;  break;
#endif
        default:
            DebugMsg(("write_relocs32(): unhandled reloc loc=%X type=%u idx=%u sym=%s\n",
                      fixup->locofs, fixup->type, fixup->sym->ext_idx, fixup->sym->name));
            elftype = R_386_NONE;
            if ( fixup->type < FIX_LAST ) {
                EmitErr( INVALID_FIXUP_TYPE, ModuleInfo.fmtopt->formatname, fixup->type, curr->sym.name, fixup->locofs );
            } else
                EmitErr( UNKNOWN_FIXUP_TYPE, fixup->type, curr->sym.name, fixup->locofs );
        }
        /* the low 8 bits of info are type */
        /* the high 24 bits are symbol table index */
        reloc32.r_info = ELF32_R_INFO( fixup->sym->ext_idx, elftype );
        if ( fwrite( &reloc32, 1, sizeof(reloc32), CurrFile[OBJ] ) != sizeof(reloc32) )
            WriteError();
    }
    DebugMsg(("write_relocs32: exit\n"));
    return;
}

#if AMD64_SUPPORT

/* write 1 section's relocations (64-bit) */

static void write_relocs64( struct dsym *curr )
/*********************************************/
{
    uint_8 elftype;
    struct fixup *fixup;
    Elf64_Rela reloc64; /* v2.05: changed to Rela */

    DebugMsg(("write_relocs64: enter\n"));
    for ( fixup = curr->e.seginfo->FixupList.head; fixup; fixup = fixup->nextrlc ) {
        unsigned symidx = fixup->sym->ext_idx;
        reloc64.r_offset = fixup->locofs;
        /* v2.07: addend wasn't handled correctly.
         * Also note the type cast for fixup.offset -
         * r_addend has type int_64, while fixup.offset has type uint_32!
         */
        //reloc64.r_addend = fixup->offset;
        /* the following line depends on what's done in store_fixup().
         * if the inline addend is set to 0 there, the fixup->offset
         * must be used in the calculation ( it's 32-bit only!!! ).
         */
        //reloc64.r_addend = (int_32)fixup->offset - fixup->addbytes;
        /*
         * if the inline addend is not touched in store_fixup(),
         * we just have to use the addbytes field.
         */
        reloc64.r_addend = - fixup->addbytes;
        DebugMsg(("write_relocs64(): reloc loc=%X type=%u idx=%u sym=%s ofs=%X addbyt=%u\n",
                  fixup->locofs, fixup->type, fixup->sym->ext_idx, fixup->sym->name, fixup->offset, fixup->addbytes ));
        switch ( fixup->type ) {
        case FIX_RELOFF32:
#if 0  /* v2.07: activate if the section's index is to be used as symtab ref */
            if ( fixup->sym->segment != &curr->sym ) {
                //printf("PC-relative fixup to another section: %s\n", fixup->sym->name );
                reloc64.r_addend += fixup->sym->offset;
                symidx = fixup->sym->segment->ext_idx;
            }
#endif
            elftype = R_X86_64_PC32;
            break;
        case FIX_OFF64:        elftype = R_X86_64_64;          break;
        //case FIX_???:        elftype = R_X86_64_GOT32;       break;
        //case FIX_???:        elftype = R_X86_64_PLT32;       break;
        //case FIX_???:        elftype = R_X86_64_COPY;        break;
        //case FIX_???:        elftype = R_X86_64_GLOB_DAT;    break;
        //case FIX_???:        elftype = R_X86_64_JMP_SLOT;    break;
        case FIX_OFF32_IMGREL: elftype = R_X86_64_RELATIVE;    break;
        //case FIX_???:        elftype = R_X86_64_GOTPCREL;    break;
        case FIX_OFF32:        elftype = R_X86_64_32;          break;
        //case FIX_???:        elftype = R_X86_64_32S;         break;
        case FIX_OFF16:        elftype = R_X86_64_16;          break;
        case FIX_RELOFF16:     elftype = R_X86_64_PC16;        break;
        case FIX_OFF8:         elftype = R_X86_64_8;           break;
        case FIX_RELOFF8:      elftype = R_X86_64_PC8;         break;
        //case FIX_???:        elftype = R_X86_64_DPTMOD64;    break;
        //case FIX_???:        elftype = R_X86_64_DPTOFF64;    break;
        //case FIX_???:        elftype = R_X86_64_TPOFF64;     break;
        //case FIX_???:        elftype = R_X86_64_TLSGD;       break;
        //case FIX_???:        elftype = R_X86_64_TLSLD;       break;
        //case FIX_???:        elftype = R_X86_64_DPTOFF32;    break;
        //case FIX_???:        elftype = R_X86_64_GOTTPOFF;    break;
        //case FIX_???:        elftype = R_X86_64_TPOFF32;     break;
        //case FIX_???:        elftype = R_X86_64_PC64;        break;
        //case FIX_???:        elftype = R_X86_64_GOTOFF64;    break;
        //case FIX_???:        elftype = R_X86_64_GOTPC32;     break;
        //case FIX_???:        elftype = R_X86_64_SIZE32;      break;
        //case FIX_???:        elftype = R_X86_64_SIZE64;      break;
        default:
            DebugMsg(("write_relocs64(): unhandled reloc loc=%X type=%u idx=%u sym=%s\n",
                      fixup->locofs, fixup->type, fixup->sym->ext_idx, fixup->sym->name));
            elftype = R_X86_64_NONE;
            if ( fixup->type < FIX_LAST ) {
                EmitErr( INVALID_FIXUP_TYPE, ModuleInfo.fmtopt->formatname, fixup->type, curr->sym.name, fixup->locofs );
            } else
                EmitErr( UNKNOWN_FIXUP_TYPE, fixup->type, curr->sym.name, fixup->locofs );
        }
        /* the low 8 bits of info are type */
        /* the high 24 bits are symbol table index */
        reloc64.r_info = ELF64_R_INFO( symidx, elftype );
        if ( fwrite( &reloc64, 1, sizeof( reloc64 ), CurrFile[OBJ] ) != sizeof(reloc64) )
            WriteError();
    }
    DebugMsg(("write_relocs64: exit\n"));
    return;
}
#endif

/* write section contents and fixups */

static ret_code elf_write_data( struct module_info *modinfo, struct elfmod *em )
/******************************************************************************/
{
    struct dsym *curr;
    //int seg_index;
    //uint_32 offset = 0;
    uint_32     size;
    int         i;

    DebugMsg(("elf_write_data: enter\n"));

    for( curr = SymTables[TAB_SEG].head; curr; curr = curr->next ) {
        size = curr->sym.max_offset - curr->e.seginfo->start_loc;
        DebugMsg(("elf_write_data(%s): program data at ofs=%X, size=%X\n", curr->sym.name, curr->e.seginfo->fileoffset, size ));
        if ( curr->e.seginfo->segtype != SEGTYPE_BSS && size != 0 ) {
            fseek( CurrFile[OBJ], curr->e.seginfo->fileoffset + curr->e.seginfo->start_loc, SEEK_SET );
            /**/myassert( curr->e.seginfo->CodeBuffer );
            if ( fwrite( curr->e.seginfo->CodeBuffer, 1, size, CurrFile[OBJ] ) != size )
                WriteError();
        }
    }

    /* write internal sections */
    for ( i = 0; i < NUM_INTSEGS; i++ ) {
        if ( em->internal_segs[i].data ) {
            DebugMsg(("elf_write_data(%s): internal at ofs=%X, size=%X\n", internal_segparms[i].name, em->internal_segs[i].fileoffset, em->internal_segs[i].size));
            fseek( CurrFile[OBJ], em->internal_segs[i].fileoffset, SEEK_SET );
            if ( fwrite( em->internal_segs[i].data, 1, em->internal_segs[i].size, CurrFile[OBJ] ) != em->internal_segs[i].size )
                WriteError();
        }
    }

    /* write reloc sections content */
    for( curr = SymTables[TAB_SEG].head; curr; curr = curr->next ) {
        if ( curr->e.seginfo->num_relocs ) {
            DebugMsg(("elf_write_data(%s): relocs at ofs=%X, size=%X\n", curr->sym.name, curr->e.seginfo->reloc_offset, curr->e.seginfo->num_relocs * sizeof(Elf32_Rel)));
            fseek( CurrFile[OBJ], curr->e.seginfo->reloc_offset, SEEK_SET );
#if AMD64_SUPPORT
            if ( modinfo->defOfssize == USE64 )
                write_relocs64( curr );
            else
#endif
                write_relocs32( em, curr );
        }
    }
#if GNURELOCS
    if ( em->extused ) {
        EmitWarn( 2, ELF_GNU_EXTENSIONS_USED );
    }
#endif

    DebugMsg(("elf_write_data: exit\n"));

    return( NOT_ERROR );
}

/* write ELF module */

static ret_code elf_write_module( struct module_info *modinfo )
/*************************************************************/
{
    //struct dsym  *dir;
    struct elfmod em;

    DebugMsg(("elf_write_module: enter\n"));

    memset( &em, 0, sizeof( em ) );
    em.srcname = CurrFName[ASM];
#if 1
    /* the path part is stripped. todo: check if this is ok to do */
    em.srcname += strlen( em.srcname );
    while ( em.srcname > CurrFName[ASM] &&
           *(em.srcname-1) != '/' &&
           *(em.srcname-1) != '\\') em.srcname--;
#endif
    /* position at 0 ( probably unnecessary, since there were no writes yet ) */
    fseek( CurrFile[OBJ], 0, SEEK_SET );

    switch ( modinfo->defOfssize ) {
#if AMD64_SUPPORT
    case USE64:
        memcpy( &em.ehdr64.e_ident, ELF_SIGNATURE, ELF_SIGNATURE_LEN );
        em.ehdr64.e_ident[EI_CLASS] = ELFCLASS64;
        em.ehdr64.e_ident[EI_DATA] = ELFDATA2LSB;
        em.ehdr64.e_ident[EI_VERSION] = EV_CURRENT;
        em.ehdr64.e_ident[EI_OSABI] = modinfo->elf_osabi;
        /* v2.07: set abiversion to 0 */
        //ehdr64.e_ident[EI_ABIVERSION] = EV_CURRENT;
        em.ehdr64.e_ident[EI_ABIVERSION] = 0;
        em.ehdr64.e_type = ET_REL; /* file type */
        em.ehdr64.e_machine = EM_X86_64;
        em.ehdr64.e_version = EV_CURRENT;
        em.ehdr64.e_entry = 0; /* no entry for relocatable objects */
        em.ehdr64.e_phoff = 0; /* no progheaders for relocatable objects */
        em.ehdr64.e_shoff = sizeof( em.ehdr64 );
        em.ehdr64.e_flags = 0;
        em.ehdr64.e_ehsize = sizeof( em.ehdr64 );
        em.ehdr64.e_phentsize = 0; /* no progheaders for relocatable objects */
        em.ehdr64.e_phnum = 0;
        em.ehdr64.e_shentsize = sizeof( Elf64_Shdr );
        /* calculate # of sections. Add the following internal sections:
         - 1 NULL entry
         - 1 .shstrtab
         - 1 .symtab
         - 1 .strtab
         - n .rela<xxx> sections
         */
        em.ehdr64.e_shnum = 1 + modinfo->g.num_segs + 3 + get_num_reloc_sections();
        em.ehdr64.e_shstrndx = 1 + modinfo->g.num_segs + SHSTRTAB_IDX; /* set index of .shstrtab section */
        if ( fwrite( &em.ehdr64, 1, sizeof( em.ehdr64 ), CurrFile[OBJ] ) != sizeof( em.ehdr64 ) )
            WriteError();
        elf_write_section_table64( modinfo, &em,
                                  sizeof( Elf64_Ehdr ) + em.ehdr64.e_shnum * em.ehdr64.e_shentsize );
        break;
#endif
    default:
        memcpy( &em.ehdr32.e_ident, ELF_SIGNATURE, ELF_SIGNATURE_LEN );
        em.ehdr32.e_ident[EI_CLASS] = ELFCLASS32;
        em.ehdr32.e_ident[EI_DATA] = ELFDATA2LSB;
        em.ehdr32.e_ident[EI_VERSION] = EV_CURRENT;
        em.ehdr32.e_ident[EI_OSABI] = modinfo->elf_osabi;
        /* v2.07: set abiversion to 0 */
        //ehdr32.e_ident[EI_ABIVERSION] = EV_CURRENT;
        em.ehdr32.e_ident[EI_ABIVERSION] = 0;
        em.ehdr32.e_type = ET_REL; /* file type */
        em.ehdr32.e_machine = EM_386;
        em.ehdr32.e_version = EV_CURRENT;
        em.ehdr32.e_entry = 0; /* no entry for relocatable objects */
        em.ehdr32.e_phoff = 0; /* no progheaders for relocatable objects */
        em.ehdr32.e_shoff = sizeof( em.ehdr32 );
        em.ehdr32.e_flags = 0;
        em.ehdr32.e_ehsize = sizeof( em.ehdr32 );
        em.ehdr32.e_phentsize = 0; /* no progheaders for relocatable objects */
        em.ehdr32.e_phnum = 0;
        em.ehdr32.e_shentsize = sizeof( Elf32_Shdr );
        /* calculate # of sections. Add the following internal sections:
         - 1 NULL entry
         - 1 .shstrtab
         - 1 .symtab
         - 1 .strtab
         - n .rel<xxx> entries
         */
        em.ehdr32.e_shnum = 1 + modinfo->g.num_segs + 3 + get_num_reloc_sections();
        em.ehdr32.e_shstrndx = 1 + modinfo->g.num_segs + SHSTRTAB_IDX; /* set index of .shstrtab section */
        if ( fwrite( &em.ehdr32, 1, sizeof( em.ehdr32 ), CurrFile[OBJ] ) != sizeof( em.ehdr32 ) )
            WriteError();
        elf_write_section_table32( modinfo, &em,
                                  sizeof( Elf32_Ehdr ) + em.ehdr32.e_shnum * em.ehdr32.e_shentsize );
    };
    elf_write_data( modinfo, &em );
    DebugMsg(("elf_write_module: exit\n"));
    return( NOT_ERROR );
}

/* format-specific init.
 * called once per module.
 */

void elf_init( struct module_info *modinfo )
/******************************************/
{
    modinfo->elf_osabi = ELFOSABI_LINUX;
    modinfo->g.WriteModule = elf_write_module;
#if 0
    printf("size Elf_Ehdr: %2u - %2u\n", sizeof(Elf32_Ehdr), sizeof(Elf64_Ehdr));
    printf("size Elf_Shdr: %2u - %2u\n", sizeof(Elf32_Shdr), sizeof(Elf64_Shdr));
    printf("size Elf_Sym : %2u - %2u\n", sizeof(Elf32_Sym ), sizeof(Elf64_Sym ));
    printf("size Elf_Rel : %2u - %2u\n", sizeof(Elf32_Rel ), sizeof(Elf64_Rel ));
    printf("size Elf_Rela: %2u - %2u\n", sizeof(Elf32_Rela), sizeof(Elf64_Rela));
#endif
    return;
}

#endif
