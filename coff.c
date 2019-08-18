/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:  COFF output routines
*
****************************************************************************/

#include <ctype.h>
#include <time.h>

#include "globals.h"
#include "memalloc.h"
#include "mangle.h"
#include "parser.h"
#include "fixup.h"
#include "segment.h"
#include "extern.h"
#include "coff.h"
#include "coffspec.h"
#include "input.h"
#include "myassert.h"
#include "omfspec.h"
#include "linnum.h"

#if COFF_SUPPORT

#define HELPSYMS     0 /* use helper symbols for assembly time symbol refs */
#define MANGLE_BYTES 8 /* extra size required for name decoration */
/* v2.04: to make Uasm always add static (=private) procs to the symbol table
 * set STATIC_PROCS to 1. Normally those procs are only added if line
 * number/symbolic debugging information is generated.
 */
#define STATIC_PROCS 1 /* v2.10: changed to 1, because Masm 6-10 DOES add static procs */
#define COMPID       0 /* 1=add comp.id absolute symbol */
/* size of codeview temp segment buffer; prior to v2.12 it was 1024 - but this may be
 * insufficient if MAX_ID_LEN has been enlarged.
 */
#define SIZE_CV_SEGBUF ( MAX_LINE_LEN * 2 )

struct stringitem {
    struct stringitem *next;
    char string[1];
};

extern void cv_write_debug_tables( struct dsym *, struct dsym *, void * );

enum dbgseg_index {
    DBGS_SYMBOLS,
    DBGS_TYPES,
    DBGS_MAX
};

struct dbg_section {
    //const char *name;
    struct dsym *seg;
    struct qdesc q;
};

/* -Zi option section info */
static const char * const SymDebName[DBGS_MAX] = { ".debug$S", ".debug$T" };

/* v2.12: all coff global variables replaced by struct coffmod */
struct coffmod {
    struct dsym *directives;    /* .drectve section, contains linker directives */
    struct dsym *sxdata;        /* section for safe exception handler data */
    struct asym *lastproc;      /* used if -Zd is set */
    char        *dot_file_value;/* value of .file symbol (isn't written by Masm v8+) */
    uint_32     start_data;     /* file position of start section data */
    uint_32     size_data;      /* total of section contents (incl relocs + linnums) */
    uint_32     start_files;    /* symbol table index of first .file entry used by line number info */
    uint_32     sectionstart;   /* symbol table index of first section */
    struct dbg_section SymDeb[DBGS_MAX]; /* codeview debug sections */
    struct {
        struct stringitem *head;
        struct stringitem *tail;
        uint_32 size;
    } LongNames;
#ifdef DEBUG_OUT
    uint_32     start_symtab;   /* calculated start of symbol table when section table is written */
#endif
};

static const char szdrectve[] = { ".drectve" };

static const IMAGE_SYMBOL isFeat00 = {
    {"@feat.00"},
     1,
     IMAGE_SYM_ABSOLUTE,
     IMAGE_SYM_TYPE_NULL,
     IMAGE_SYM_CLASS_STATIC,
     0
};
#if COMPID
static const IMAGE_SYMBOL isCompId = {
    {"@comp.id"},
    //8803 + ( 0x2a << 16 ), /* value of Masm v6.15.8803 */
    //9466 + ( 0x40 << 16 ), /* value of Masm v7.00.9466 */
    50727 + ( 0x7d << 16 ), /* value of Masm v8.00.50727.104 */
    //30729 + ( 0x95 << 16 ), /* value of Masm v9.00.30729.01 */
    //30319 + ( 0x9e << 16 ), /* value of Masm v10.00.30319.01 */
    IMAGE_SYM_ABSOLUTE,
    IMAGE_SYM_TYPE_NULL,
    IMAGE_SYM_CLASS_STATIC,
    0 /* # of aux symbols */
};
#endif

/* alloc a string which will be stored in the COFF string table */

static uint_32 Coff_AllocString( struct coffmod *cm, const char *string, int len )
/********************************************************************************/
{
    struct stringitem *name;
    uint_32 oldsize = cm->LongNames.size;

    cm->LongNames.size += len + 1;
    name = LclAlloc( len + sizeof( struct stringitem ) );
    name->next = NULL;
    strcpy( name->string, string );
    if ( cm->LongNames.head ) {
        cm->LongNames.tail->next = name;
        cm->LongNames.tail = name;
    } else {
        cm->LongNames.head = cm->LongNames.tail = name;
    }
    return( oldsize );
}

/* return number of line number items */

static unsigned GetLinnumItems( struct qdesc *q )
/***********************************************/
{
    unsigned i;
    struct line_num_info *curr;

    for ( i = 0, curr = q->head; curr; i++, curr = curr->next );
    return( i );
}

/* write COFF section table */

static ret_code coff_write_section_table( struct module_info *modinfo, struct coffmod *cm )
/*****************************************************************************************/
{
    struct dsym  *curr;
    struct fixup *fix;
    uint_32      fileoffset; /* calculated file offset for section data, relocs and linenumber info */
    unsigned     len;
    char         *secname;
    //struct omf_rec  *objr;
    //char        *p;
    //uint        size_relocs = 0;
    enum seg_type segtype;
    struct IMAGE_SECTION_HEADER ish;
    char buffer[MAX_ID_LEN+1];

    DebugMsg(("coff_write_section_table: enter, sections=%u\n", modinfo->g.num_segs ));

    fileoffset = sizeof( struct IMAGE_FILE_HEADER ) + modinfo->g.num_segs * sizeof( struct IMAGE_SECTION_HEADER );
    cm->start_data = fileoffset;
    for( curr = SymTables[TAB_SEG].head; curr; curr = curr->next ) {

        /* v2.04: can't happen */
        //if( curr->sym.state != SYM_SEG ) {
        //    EmitErr( SEGMENT_NOT_DEFINED, curr->sym.name );
        //    continue;
        //}
        segtype = SEGTYPE_UNDEF;
        /* v2.07: prefer ALIAS name if defined. */
        secname = ( curr->e.seginfo->aliasname ? curr->e.seginfo->aliasname : ConvertSectionName( &curr->sym, &segtype, buffer ) );
        len = strlen( secname );
        /* if section name is longer than 8 chars, a '/' is stored,
         followed by a number in ascii which is the offset for the string table
         */
        if ( len <= IMAGE_SIZEOF_SHORT_NAME )
            strncpy( ish.Name, secname, IMAGE_SIZEOF_SHORT_NAME );
        else
            sprintf( ish.Name, "/%u", Coff_AllocString( cm, secname, len ) );

        /* v2.04: what is the old line supposed to do? */
        //ish.Misc.PhysicalAddress = fileoffset - (size_relocs + sizeof(struct IMAGE_FILE_HEADER) + ModuleInfo->g.num_segs * sizeof(struct IMAGE_SECTION_HEADER));
        ish.Misc.PhysicalAddress = 0;
        ish.VirtualAddress = 0;
        ish.SizeOfRawData = curr->sym.max_offset;
        ish.PointerToRawData = ( ish.SizeOfRawData ? fileoffset : 0 );
        ish.PointerToRelocations = 0;
        ish.PointerToLinenumbers = 0;
        ish.NumberOfRelocations = 0;
        ish.NumberOfLinenumbers = 0;
        ish.Characteristics = 0;

        /* set field Characteristics; optionally reset PointerToRawData/SizeOfRawData */
        if ( curr->e.seginfo->info ) {
            /* v2.09: set "remove" flag for .drectve section, as it was done in v2.06 and earlier */
            if ( curr == cm->directives )
                ish.Characteristics = ( IMAGE_SCN_LNK_INFO | IMAGE_SCN_LNK_REMOVE );
            else
                ish.Characteristics = ( IMAGE_SCN_LNK_INFO | IMAGE_SCN_CNT_INITIALIZED_DATA );
        } else {
            if ( curr->e.seginfo->alignment != MAX_SEGALIGNMENT ) /* ABS not possible */
                ish.Characteristics |= (uint_32)(curr->e.seginfo->alignment + 1) << 20;
#if COMDATSUPP
            if ( curr->e.seginfo->comdat_selection )
                ish.Characteristics |= IMAGE_SCN_LNK_COMDAT;
#endif
            if ( curr->e.seginfo->segtype == SEGTYPE_CODE ) {
                ish.Characteristics |= IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ;
            } else if ( curr->e.seginfo->readonly ) {
                ish.Characteristics |= IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_READ;
            } else if ( curr->e.seginfo->clsym && strcmp( curr->e.seginfo->clsym->name, "CONST" ) == 0 ) {
                ish.Characteristics |= IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_READ;
            } else if ( curr->e.seginfo->segtype == SEGTYPE_BSS || segtype == SEGTYPE_BSS ) {
                /* v2.12: if segtype is bss, ensure that seginfo->segtype is also bss; else
                 * the segment might be written in coff_write_data().
                 */
                curr->e.seginfo->segtype = SEGTYPE_BSS;
                ish.Characteristics |= IMAGE_SCN_CNT_UNINITIALIZED_DATA | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE;
                /* ish.SizeOfRawData = 0; */
                ish.PointerToRawData = 0;
            } else if ( curr->e.seginfo->combine == COMB_STACK && curr->e.seginfo->bytes_written == 0 ) {
                ish.Characteristics |= IMAGE_SCN_CNT_UNINITIALIZED_DATA | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE;
                ish.SizeOfRawData = 0;
                ish.PointerToRawData = 0;
            } else
                ish.Characteristics |= IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE;
        }

        /* manual characteristics set? */
        if ( curr->e.seginfo->characteristics ) {
            ish.Characteristics &= 0x1FFFFFF; /* clear the IMAGE_SCN_MEM flags */
            ish.Characteristics |= (uint_32)(curr->e.seginfo->characteristics & 0xFE) << 24;
            /* the INFO bit (bit 0) needs special handling! */
            //if ( curr->e.seginfo->characteristics & 1 )
            //    ish.Characteristics |= IMAGE_SCN_LNK_INFO;
        }

        if ( ish.PointerToRawData )
            fileoffset += ish.SizeOfRawData;

        /* set fields PointerToRelocations/NumberOfRelocations; update 'fileoffset'.
         * v2.10: don't use the 16-bit NumberOfRelocations member to count relocs!
         * if the true number of relocs doesn't fit in 16-bits, set the appropriate
         * flag in the section header!
         */
        if ( curr->e.seginfo->FixupList.head ) {
            for ( fix = curr->e.seginfo->FixupList.head; fix ; fix = fix->nextrlc ) {
                //printf("segment %s, reloc.sym=%s\n", curr->sym.name, fix->sym ? fix->sym : "NULL" );
                if ( fix->sym == NULL ) {
#if AMD64_SUPPORT
                    if ( fix->type == FIX_RELOFF32 ) {
                        uint_32 *cp = (uint_32 *)( curr->e.seginfo->CodeBuffer + (fix->locofs - curr->e.seginfo->start_loc ));
                        uint_32 src = fix->locofs + fix->addbytes;
                        (*cp) -= src;
                    }
#endif
                    fix->type = FIX_VOID;
                    continue;
                }
                curr->e.seginfo->num_relocs++;
            }
            fileoffset = (fileoffset + 1) & ~1;
            ish.PointerToRelocations = fileoffset;
            /* v2.10: handle the "relocs overflow"-case */
            fileoffset += curr->e.seginfo->num_relocs * sizeof( IMAGE_RELOCATION );
            if ( curr->e.seginfo->num_relocs <= 0xffff ) {
                ish.NumberOfRelocations =  (uint_16)curr->e.seginfo->num_relocs;
            } else {
                DebugMsg(( "coff_write_section_table(%s): %" I32_SPEC "u fixups (more than 0xffff!)!\n", curr->sym.name, curr->e.seginfo->num_relocs ));
                ish.NumberOfRelocations =  0xffff;
                ish.Characteristics |= IMAGE_SCN_LNK_NRELOC_OVFL;
                /* add 1 relocation - the true number of relocations is stored in the first relocation item */
                fileoffset += sizeof( IMAGE_RELOCATION );
            }
            //printf( "segment %s has %u relocs\n", curr->sym.name, curr->e.seginfo->num_relocs );
        }

        /* set fields PointerToLinenumbers/NumberOfLinenumbers; update 'fileoffset' */

        if ( curr->e.seginfo->LinnumQueue ) {
            ish.PointerToLinenumbers = fileoffset;
            ish.NumberOfLinenumbers = GetLinnumItems( curr->e.seginfo->LinnumQueue );
            fileoffset += ish.NumberOfLinenumbers * sizeof( IMAGE_LINENUMBER );
        }

        DebugMsg(( "coff_write_section_table(%s): name=%.8s Fixups=%u, Linnums=%u\n", curr->sym.name, ish.Name, ish.NumberOfRelocations, ish.NumberOfLinenumbers ));
        if ( fwrite( &ish, 1, sizeof( ish ), CurrFile[OBJ] ) != sizeof( ish ) )
            WriteError();
    }
#ifdef DEBUG_OUT
    cm->start_symtab = fileoffset;
#endif
    DebugMsg(("coff_write_section_table: exit\n"));
    return( NOT_ERROR );
}


/*
 * get value for field 'type' ( IMAGE_SYM_TYPE_x ) in symbol table.
 * MS tools use only 0x0 or 0x20.
 */
static short CoffGetType( const struct asym *sym )
/************************************************/
{
    if ( sym->isproc )
        return( 0x20 );

#if 0
    switch (sym->mem_type) {
    case MT_BYTE:
    case MT_SBYTE:
        return( IMAGE_SYM_TYPE_BYTE );
    case MT_WORD:
    case MT_SWORD:
        return( IMAGE_SYM_TYPE_WORD );
    case MT_DWORD:
    case MT_SDWORD:
        return( IMAGE_SYM_TYPE_DWORD );
    }
#endif
    return( IMAGE_SYM_TYPE_NULL );
}

/*
 * get value for field 'class' ( IMAGE_SYM_CLASS_x ) in symbol table.
 */
static short CoffGetClass( const struct asym *sym )
/*************************************************/
{
    if ( sym->state == SYM_EXTERNAL )
        if ( sym->iscomm == FALSE && sym->altname )
            return( IMAGE_SYM_CLASS_WEAK_EXTERNAL );
        else
            return( IMAGE_SYM_CLASS_EXTERNAL );
    else if ( sym->ispublic == TRUE )
        return( IMAGE_SYM_CLASS_EXTERNAL );
#if HELPSYMS
    else if ( sym->variable == TRUE ) /* assembly time variable in fixup */
        return( IMAGE_SYM_CLASS_LABEL );
#endif
    /* v2.09: don't declare private procs as label */
    //else if ( sym->mem_type == MT_NEAR )/* added v2.0 */
    else if ( sym->mem_type == MT_NEAR && sym->isproc == FALSE )
        return( IMAGE_SYM_CLASS_LABEL );

    return( IMAGE_SYM_CLASS_STATIC );
}

/* calc number of entries in symbol table for a file entry */

static unsigned GetFileAuxEntries( uint_16 file, char * *fname )
/**************************************************************/
{
    const struct fname_item *curr;
    unsigned len;
    curr = GetFName( file );
    if ( fname )
        *fname = curr->fname;
    len = strlen( curr->fname );
    /**/myassert( len ); /* name length must be > 0 */
    return ( len / sizeof( IMAGE_AUX_SYMBOL ) + ( len % sizeof( IMAGE_AUX_SYMBOL ) ? 1 : 0 ) );
}

#if COMDATSUPP

/* v2.10: COMDAT CRC calculation ( suggestion by drizz, slightly modified ) */

static uint_32 CRC32Table[256]; /* table is initialized if needed */

static void InitCRC32( void )
/***************************/
{
    int i,j;
    uint_32 crc;
    for ( i = 0; i < 256; i++ ) {
        for ( j = 0, crc = i; j < 8; j++ ) {
            crc = ( crc >> 1 ) ^ (0xEDB88320 * ( crc & 1 ) );
        }
        CRC32Table[i] = crc;
    }
}

static uint_32 CRC32Comdat( uint_8 *lpBuffer, uint_32 dwBufLen, uint_32 dwCRC )
/*****************************************************************************/
{
    static bool init = FALSE;
    uint_8 byt;

    if ( !init ) {
        init = TRUE;
        InitCRC32();
    }
    if ( lpBuffer ) /* v2.11: lpBuffer may be NULL ( uninitialized data segs ) */
        for ( ; dwBufLen; dwBufLen-- ) {
            byt = *lpBuffer++;
            byt = byt ^ (uint_8)dwCRC;
            dwCRC = dwCRC >> 8;
            dwCRC = dwCRC ^ CRC32Table[byt];
        }
    return( dwCRC );
}
#endif

/* write COFF symbol table
 * contents of the table
 * - @@feat.00 if .SAFESEH was set
 * - file (+ 1-n aux)
 * - 2 entries per section
 * - externals, communals and publics
 * - entries for relocations (internal)
 * - aliases (weak externals)
 */
static uint_32 coff_write_symbols( struct module_info *modinfo, struct coffmod *cm )
/**********************************************************************************/
{
    uint_32     cntSymbols = 0;
    struct dsym *curr;
    struct asym *sym;
    struct qnode *q;
    char        *p;
    unsigned    len;
    unsigned    i;
    IMAGE_SYMBOL is;
    IMAGE_AUX_SYMBOL ias;
    unsigned    lastfile = 0;
    char        buffer[MAX_ID_LEN + MANGLE_BYTES + 1];

    DebugMsg(("coff_write_symbols: enter\n"));

#if COMPID
    /* write "@comp.id" entry */
    if ( fwrite( &isCompId, 1, sizeof(IMAGE_SYMBOL), CurrFile[OBJ] ) != sizeof(IMAGE_SYMBOL) )
        WriteError();
    cntSymbols++;
#endif
    /* "@feat.00" entry (for SafeSEH) */
    if ( Options.safeseh ) {
        if ( fwrite( &isFeat00, 1, sizeof(IMAGE_SYMBOL), CurrFile[OBJ] ) != sizeof(IMAGE_SYMBOL) )
            WriteError();
        cntSymbols++;
    }

    /* .file item (optionally disabled by -zlf) */

    if ( Options.no_file_entry == FALSE ) {
        strncpy( is.N.ShortName, ".file", IMAGE_SIZEOF_SHORT_NAME );
        is.Value = ( Options.line_numbers ? cm->start_files : 0 );  /* index of next .file entry */
        is.SectionNumber = (uint_16)IMAGE_SYM_DEBUG;
        is.Type = IMAGE_SYM_TYPE_NULL;
        is.StorageClass = IMAGE_SYM_CLASS_FILE;

        p = cm->dot_file_value;
        i = strlen( p );
        is.NumberOfAuxSymbols = i / sizeof(IMAGE_AUX_SYMBOL) + (i % sizeof(IMAGE_AUX_SYMBOL) ? 1 : 0);
        if ( fwrite( &is, 1, sizeof(is), CurrFile[OBJ] ) != sizeof(is) )
            WriteError();

        for ( i = is.NumberOfAuxSymbols;i;i--, p += sizeof(IMAGE_AUX_SYMBOL) ) {
            strncpy( ias.File.Name, p, sizeof(IMAGE_AUX_SYMBOL) );
            if ( fwrite( &ias, 1, sizeof(ias), CurrFile[OBJ] ) != sizeof(ias) )
                WriteError();
        }
        cntSymbols += is.NumberOfAuxSymbols + 1;
    }

    /* next are section entries */

    for( i = 1, curr = SymTables[TAB_SEG].head; curr; curr = curr->next, i++ ) {
        /* v2.07: prefer ALIAS name if defined */
        p = ( curr->e.seginfo->aliasname ? curr->e.seginfo->aliasname : ConvertSectionName( &curr->sym, NULL, buffer ) );
        len = strlen( p );
        if ( len <= IMAGE_SIZEOF_SHORT_NAME )
            strncpy( is.N.ShortName, p, IMAGE_SIZEOF_SHORT_NAME );
        else {
            is.N.Name.Short = 0;
            is.N.Name.Long = Coff_AllocString( cm, p, len );
        }
        is.Value = 0;
        is.SectionNumber = i;
        is.Type = IMAGE_SYM_TYPE_NULL;
        is.StorageClass = IMAGE_SYM_CLASS_STATIC;
        is.NumberOfAuxSymbols = 0;
        if ( Options.no_section_aux_entry == FALSE )
            is.NumberOfAuxSymbols = 1;

        DebugMsg(("coff_write_symbols(%u, SECT): %s, type=%x, stgcls=%x\n", cntSymbols, curr->sym.name, is.Type, is.StorageClass ));

        if ( fwrite( &is, 1, sizeof(is), CurrFile[OBJ] ) != sizeof(is) )
            WriteError();
        cntSymbols++;

        /* write the auxiliary symbol record for sections.
         * may be suppressed with option -zls.
         */
        if ( Options.no_section_aux_entry == FALSE 
#if COMDATSUPP
            || curr->e.seginfo->comdat_selection
#endif
            ) {
            ias.Section.Length = curr->sym.max_offset;
            /* v2.10: check for overflow */
            //ias.Section.NumberOfRelocations = curr->e.seginfo->num_relocs;
            ias.Section.NumberOfRelocations = ( curr->e.seginfo->num_relocs > 0xffff ? 0xffff : (uint_16)curr->e.seginfo->num_relocs );
            if ( Options.line_numbers )
                ias.Section.NumberOfLinenumbers = curr->e.seginfo->num_linnums;
            else
                ias.Section.NumberOfLinenumbers = 0;
            /* CheckSum, Number and Selection are for COMDAT sections only */
#if COMDATSUPP
            if ( curr->e.seginfo->comdat_selection ) {
                ias.Section.CheckSum = CRC32Comdat( curr->e.seginfo->CodeBuffer, curr->sym.max_offset, 0 );
                ias.Section.Number = curr->e.seginfo->comdat_number;
                ias.Section.Selection = curr->e.seginfo->comdat_selection;
            } else {
#endif
                ias.Section.CheckSum = 0;
                ias.Section.Number = 0;
                ias.Section.Selection = 0;
#if COMDATSUPP
            };
#endif
            if ( fwrite( &ias, 1, sizeof(ias), CurrFile[OBJ] ) != sizeof(ias) )
                WriteError();
            DebugMsg(("coff_write_symbols(%u, SECT): %s, AUX, relocs=%u, linnums=%u\n", cntSymbols, curr->sym.name, ias.Section.NumberOfRelocations, ias.Section.NumberOfLinenumbers ));
            cntSymbols++;
        }
    }

    /* third are externals + communals ( + protos [since v2.01] ) */

    for( curr = SymTables[TAB_EXT].head ; curr != NULL ;curr = curr->next ) {
        /* skip "weak" (=unused) externdefs */
        if ( curr->sym.iscomm == FALSE && curr->sym.weak == TRUE ) {
            DebugMsg(("coff_write_symbols(EXT+COMM): %s skipped, used=%u, comm=%u, weak=%u\n", curr->sym.name, curr->sym.used, curr->sym.iscomm, curr->sym.weak ));
            continue;
        }
        len = Mangle( &curr->sym, buffer );

        is.Type = CoffGetType(&curr->sym);
        is.StorageClass = CoffGetClass(&curr->sym);

        DebugMsg(("coff_write_symbols(%u, EXT+COMM): %s, type=%x, stgcls=%x\n", cntSymbols, curr->sym.name, is.Type, is.StorageClass ));

        /* for COMMUNALs, store their size in the Value field */
        if (curr->sym.iscomm == TRUE)
            is.Value = curr->sym.total_size;
        else
            is.Value = curr->sym.offset; /* is always 0 */
        is.SectionNumber = IMAGE_SYM_UNDEFINED;
        is.NumberOfAuxSymbols = (( curr->sym.iscomm == FALSE && curr->sym.altname ) ? 1 : 0 );

        if ( len <= IMAGE_SIZEOF_SHORT_NAME )
            strncpy( is.N.ShortName, buffer, IMAGE_SIZEOF_SHORT_NAME );
        else {
            is.N.Name.Short = 0;
            is.N.Name.Long = Coff_AllocString( cm, buffer, len );
        }
        if ( fwrite( &is, 1, sizeof(is), CurrFile[OBJ] ) != sizeof(is) )
            WriteError();
        cntSymbols++;

        /* for weak externals, write the auxiliary record */
        if ( curr->sym.iscomm == FALSE && curr->sym.altname ) {
            memset( &ias, 0, sizeof(ias) );
            ias.Sym.TagIndex = curr->sym.altname->ext_idx;
            /* v2.10: weak externals defined via "extern sym (altsym) ..."
             * are to have characteristics IMAGE_WEAK_EXTERN_SEARCH_LIBRARY.
             */
            //ias.Sym.Misc.TotalSize = IMAGE_WEAK_EXTERN_SEARCH_ALIAS;
            ias.Sym.Misc.TotalSize = IMAGE_WEAK_EXTERN_SEARCH_LIBRARY;
            if ( fwrite( &ias, 1, sizeof(ias), CurrFile[OBJ] ) != sizeof(ias) )
                WriteError();
            cntSymbols++;
        }
    }

    /* publics and internal symbols. The internal symbols have
     * been written to the "public" queue inside coff_write_data().
     */
    for ( q = ModuleInfo.g.PubQueue.head; q; q = q->next ) {
        sym = q->sym;
        len = Mangle( sym, buffer );
#ifdef DEBUG_OUT
        if ( sym->state == SYM_INTERNAL && sym->isproc == TRUE && Options.line_numbers )
            DebugMsg(("coff_write_symbols(%u): %s, file=%u\n", cntSymbols, sym->name, sym->debuginfo->file ));
#endif
        if ( Options.line_numbers &&
            sym->isproc &&
            sym->debuginfo->file != lastfile ) {
            lastfile = sym->debuginfo->file;
            strncpy( is.N.ShortName, ".file", IMAGE_SIZEOF_SHORT_NAME );
            is.SectionNumber = (uint_16)IMAGE_SYM_DEBUG;
            is.Type = IMAGE_SYM_TYPE_NULL;
            is.StorageClass = IMAGE_SYM_CLASS_FILE;
            is.NumberOfAuxSymbols = GetFileAuxEntries( sym->debuginfo->file, &p );
            is.Value = sym->debuginfo->next_file;
            if ( fwrite( &is, 1, sizeof(is), CurrFile[OBJ] ) != sizeof(is) )
                WriteError();

            for ( i = is.NumberOfAuxSymbols; i; i--, p += sizeof(IMAGE_AUX_SYMBOL) ) {
                strncpy( ias.File.Name, p, sizeof(IMAGE_AUX_SYMBOL) );
                if ( fwrite( &ias, 1, sizeof(ias), CurrFile[OBJ] ) != sizeof(ias) )
                    WriteError();
            }
            cntSymbols += is.NumberOfAuxSymbols + 1;
        }
        is.Type = CoffGetType( sym );
        is.StorageClass = CoffGetClass( sym );
        is.Value = sym->offset;
#if 1 /* v2.07: changed - to make MT_ABS obsolete */
        if ( sym->state == SYM_INTERNAL ) {
            if ( sym->segment )
                is.SectionNumber = GetSegIdx( sym->segment );
            else
                is.SectionNumber = (uint_16)IMAGE_SYM_ABSOLUTE;
        } else
            is.SectionNumber = IMAGE_SYM_UNDEFINED;
#else
        if ( sym->state == SYM_EXTERNAL )
            is.SectionNumber = IMAGE_SYM_UNDEFINED;
        else if ( sym->mem_type == MT_ABS )
            is.SectionNumber = IMAGE_SYM_ABSOLUTE;
        else if ( sym->segment )
            is.SectionNumber = GetSegIdx( sym->segment );
        else
            is.SectionNumber = IMAGE_SYM_UNDEFINED;
#endif
        is.NumberOfAuxSymbols = 0;
        if ( Options.line_numbers && sym->isproc )
            is.NumberOfAuxSymbols++;

        if ( len <= IMAGE_SIZEOF_SHORT_NAME )
            strncpy( is.N.ShortName, buffer, IMAGE_SIZEOF_SHORT_NAME );
        else {
            is.N.Name.Short = 0;
            is.N.Name.Long = Coff_AllocString( cm, buffer, len );
        }

        DebugMsg(("coff_write_symbols(%u, PUB+INT): %s, ofs=%X, type=%X, stgcls=%X\n", cntSymbols, buffer, is.Value, is.Type, is.StorageClass ));

        if ( fwrite( &is, 1, sizeof(is), CurrFile[OBJ] ) != sizeof(is) )
            WriteError();
        cntSymbols++;
        if ( Options.line_numbers && sym->isproc ) {
            /* write:
             * 1.   the aux for the proc
             * 2+3. a .bf record with 1 aux
             * 4.   a .lf record with 0 aux
             * 5+6. a .ef record with 1 aux
             */
            ias.Sym.TagIndex = cntSymbols+1;
            ias.Sym.Misc.TotalSize = sym->total_size;
            ias.Sym.FcnAry.Function.PointerToLinenumber = sym->debuginfo->ln_fileofs;
            ias.Sym.FcnAry.Function.PointerToNextFunction = sym->debuginfo->next_proc;
            if ( fwrite( &ias, 1, sizeof(ias), CurrFile[OBJ] ) != sizeof(ias) )
                WriteError();

            strncpy( is.N.ShortName, ".bf", IMAGE_SIZEOF_SHORT_NAME );
            is.Type = IMAGE_SYM_TYPE_NULL;
            is.NumberOfAuxSymbols = 1;
            is.StorageClass = IMAGE_SYM_CLASS_FUNCTION;
            if ( fwrite( &is, 1, sizeof(is), CurrFile[OBJ] ) != sizeof(is) )
                WriteError();
            ias.Sym.TagIndex = 0;
            ias.Sym.Misc.LnSz.Linenumber = sym->debuginfo->start_line;
            if ( sym->debuginfo->next_proc )
                ias.Sym.FcnAry.Function.PointerToNextFunction = sym->debuginfo->next_proc + 2;
            else
                ias.Sym.FcnAry.Function.PointerToNextFunction = 0;
            if ( fwrite( &ias, 1, sizeof(ias), CurrFile[OBJ] ) != sizeof(ias) )
                WriteError();

            strncpy( is.N.ShortName, ".lf", IMAGE_SIZEOF_SHORT_NAME );
            is.Type = IMAGE_SYM_TYPE_NULL;
            is.NumberOfAuxSymbols = 0;
            is.StorageClass = IMAGE_SYM_CLASS_FUNCTION;
            is.Value = sym->debuginfo->line_numbers;
            if ( fwrite( &is, 1, sizeof(is), CurrFile[OBJ] ) != sizeof(is) )
                WriteError();

            strncpy( is.N.ShortName, ".ef", IMAGE_SIZEOF_SHORT_NAME );
            is.Type = IMAGE_SYM_TYPE_NULL;
            is.NumberOfAuxSymbols = 1;
            is.StorageClass = IMAGE_SYM_CLASS_FUNCTION;
            is.Value = sym->offset + sym->total_size;
            if ( fwrite( &is, 1, sizeof(is), CurrFile[OBJ] ) != sizeof(is) )
                WriteError();
            ias.Sym.TagIndex = 0;
            ias.Sym.Misc.LnSz.Linenumber = sym->debuginfo->end_line;
            if ( fwrite( &ias, 1, sizeof(ias), CurrFile[OBJ] ) != sizeof(ias) )
                WriteError();

            cntSymbols += 6;
        }
    }

    /* aliases. A weak external entry with 1 aux entry is created.
     */
    for( curr = SymTables[TAB_ALIAS].head ; curr != NULL ;curr = curr->next ) {
        struct asym * sym;

        len = Mangle( &curr->sym, buffer );

        if ( len <= IMAGE_SIZEOF_SHORT_NAME )
            strncpy( is.N.ShortName, buffer, IMAGE_SIZEOF_SHORT_NAME );
        else {
            is.N.Name.Short = 0;
            is.N.Name.Long = Coff_AllocString( cm, buffer, len );
        }

        is.Value = 0;
        is.SectionNumber = IMAGE_SYM_UNDEFINED;
        is.Type = IMAGE_SYM_TYPE_NULL;
        is.StorageClass = IMAGE_SYM_CLASS_WEAK_EXTERNAL;
        is.NumberOfAuxSymbols = 1;

        DebugMsg(("coff_write_symbols(%u, ALIAS): symbol %s, ofs=%X\n", cntSymbols, buffer, is.Value ));

        if ( fwrite( &is, 1, sizeof(is), CurrFile[OBJ] ) != sizeof(is) )
            WriteError();
        cntSymbols++;

        memset( &ias, 0, sizeof(ias) );

        /* v2.04b: adjusted to new field <substitute> */
        //sym = SymSearch( curr->sym.string_ptr );
        sym = curr->sym.substitute;
        if (sym)
            ias.Sym.TagIndex = sym->ext_idx;

        ias.Sym.Misc.TotalSize = IMAGE_WEAK_EXTERN_SEARCH_ALIAS;
        if ( fwrite( &ias, 1, sizeof(ias), CurrFile[OBJ] ) != sizeof(ias) )
            WriteError();
        cntSymbols++;

    }

    DebugMsg(("coff_write_symbols: exit cntSymbols=%u\n", cntSymbols ));
    return( cntSymbols );
}

static int GetStartLabel( char *buffer, bool msg )
/************************************************/
{
    int size = 0;
    char temp[ MAX_ID_LEN + MANGLE_BYTES + 1 ];

    if ( ModuleInfo.g.start_label ) {
        Mangle( ModuleInfo.g.start_label, temp );
        if ( Options.entry_decorated )
            strcpy( buffer, temp );
        else {
            if ( ModuleInfo.g.start_label->langtype != LANG_C &&
                ModuleInfo.g.start_label->langtype != LANG_STDCALL &&
                ModuleInfo.g.start_label->langtype != LANG_SYSCALL ) {
                if ( *ModuleInfo.g.start_label->name != '_' ) {
                    if ( msg && ( ModuleInfo.fctype != FCT_WIN64 ) )
                        EmitWarn( 2, LEADING_UNDERSCORE_REQUIRED_FOR_START_LABEL, ModuleInfo.g.start_label->name );
                    strcpy( buffer, temp );
                } else {
                    strcpy( buffer, temp+1 );
                }
            } else
                strcpy( buffer, temp+1 );
        }
        size = strlen( buffer ) + 8; // 8 == size of " -entry:"
    }
    return( size );
}

/* callback to flush contents of codeview symbolic debug info sections */

static uint_8 *coff_flushfunc( struct dsym *seg, uint_8 *curr, unsigned size, void *pv )
/**************************************************************************************/
{
    unsigned currsize = curr - seg->e.seginfo->CodeBuffer;
    struct coffmod *cm;
    int i;
    uint_8 *p;

    if ( ( currsize + size ) > SIZE_CV_SEGBUF ) {
        if ( currsize ) {
            p = LclAlloc( currsize + sizeof( struct qditem ) );
            ((struct qditem *)p)->next = NULL;
            ((struct qditem *)p)->size = currsize;
            memcpy( p + sizeof( struct qditem ), seg->e.seginfo->CodeBuffer, currsize );
            cm = pv;
            i = ( seg == cm->SymDeb[DBGS_TYPES].seg ? DBGS_TYPES : DBGS_SYMBOLS );
            if ( cm->SymDeb[i].q.head == NULL )
                cm->SymDeb[i].q.head = cm->SymDeb[i].q.tail = p;
            else {
                ((struct qditem *)(cm->SymDeb[i].q.tail))->next = p;
                cm->SymDeb[i].q.tail = p;
            }
            seg->e.seginfo->current_loc = seg->e.seginfo->start_loc + currsize;
            seg->e.seginfo->start_loc = seg->e.seginfo->current_loc;
        }
        return( seg->e.seginfo->CodeBuffer );
    }
    return( curr );
}

/* calc the current number of entries in the symbol table
 * so we know the index if a new entry has to be added
 * called by coff_write_data()
 */
static uint_32 SetSymbolIndices( struct module_info *ModuleInfo, struct coffmod *cm )
/***********************************************************************************/
{
    struct qnode *q;
    struct dsym  *curr;
    struct asym  *sym;
    uint_32 index;
    uint_32 i;
    struct asym *lastfproc;
    unsigned lastfile = 0;

    index = 0;
    cm->lastproc = NULL;
    cm->start_files = 0;  /* v2.11: added */

#if COMPID
    index++;
#endif
    /* add absolute symbol @@feat.00 if -SAFESEH is set */
    if ( Options.safeseh )
        index++;

    /* count AUX entries for .file. Depends on sizeof filename */

    if ( Options.no_file_entry == FALSE ) {
        i = strlen( cm->dot_file_value );
        index += i / sizeof( IMAGE_AUX_SYMBOL ) + 1;
        if ( i % sizeof( IMAGE_AUX_SYMBOL ) )
            index++;
    }

    /* add entries for sections */

    cm->sectionstart = index;
    index += ModuleInfo->g.num_segs;
    if ( Options.no_section_aux_entry == FALSE )
        index += ModuleInfo->g.num_segs;

    /* count externals and protos */
    for( curr = SymTables[TAB_EXT].head ; curr != NULL ; curr = curr->next ) {
        if ( curr->sym.iscomm == FALSE && curr->sym.weak == TRUE )
            continue;
        curr->sym.ext_idx = index++;
        /* weak externals need an additional aux entry */
        if ( curr->sym.iscomm == FALSE && curr->sym.altname )
            index++;
    }

#if STATIC_PROCS
    /* v2.04: count private procedures (will become static symbols) */
    if ( Options.no_static_procs == FALSE )
        for( curr = SymTables[TAB_PROC].head ; curr != NULL ; curr = curr->nextproc )
            if ( curr->sym.state == SYM_INTERNAL && curr->sym.ispublic == FALSE && curr->sym.included == FALSE ) {
                curr->sym.included = TRUE;
                AddPublicData( &curr->sym );
            }
#endif
    /* count items in public queue */
    for ( q = ModuleInfo->g.PubQueue.head; q; q = q->next ) {
        sym = q->sym;
        /* if line numbers are on, co, add 6 entries for procs */
        if ( Options.line_numbers && sym->isproc ) {
            if (  sym->debuginfo->file != lastfile ) {
                if ( cm->start_files == 0 )
                    cm->start_files = index;
                else
                    lastfproc->debuginfo->next_file = index;
                lastfproc = sym;
                index += 1 + GetFileAuxEntries( sym->debuginfo->file, NULL );
                lastfile = sym->debuginfo->file;
            }
            sym->ext_idx = index++;
            index += 6;
        } else
            sym->ext_idx = index++;
    }
    return( index );
}

/* write fixups for a section. */

static void coff_write_fixups( struct dsym *section, uint_32 *poffset, uint_32 *pindex )
/**************************************************************************************/
{
    uint_32 offset = *poffset;
    uint_32 index = *pindex;
    struct fixup *fix;
    IMAGE_RELOCATION ir;

    /* v2.10: handle the reloc-overflow-case */
    if ( section->e.seginfo->num_relocs > 0xffff ) {
        DebugMsg(("coff_write_fixups(%s): enter, num_relocs=%" I32_SPEC "u\n", section->sym.name, section->e.seginfo->num_relocs ));
        ir.VirtualAddress = section->e.seginfo->num_relocs + 1;
        ir.SymbolTableIndex = 0;
        ir.Type = IMAGE_REL_I386_ABSOLUTE; /* doesn't matter if 32- or 64-bit */
        if ( fwrite( &ir, 1, sizeof(ir), CurrFile[OBJ] ) != sizeof(ir) )
            WriteError();
        offset += sizeof( ir );
    }
    /* reset counter */
    section->e.seginfo->num_relocs = 0;

    for ( fix = section->e.seginfo->FixupList.head; fix ; fix = fix->nextrlc ) {
#if AMD64_SUPPORT
        if ( section->e.seginfo->Ofssize == USE64 ) {
            switch ( fix->type ) {
            case FIX_VOID:
                continue;
            case FIX_RELOFF32: /* 32bit offset */
                /* translated to IMAGE_REL_AMD64_REL32_[1|2|3|4|5] */
                ir.Type = IMAGE_REL_AMD64_REL32 + (fix->addbytes - 4);
                break;
            case FIX_OFF32: /* 32bit offset */
                ir.Type = IMAGE_REL_AMD64_ADDR32;
                break;
#if IMAGERELSUPP
            case FIX_OFF32_IMGREL:
                ir.Type = IMAGE_REL_AMD64_ADDR32NB;
                break;
#endif
#if SECTIONRELSUPP
            case FIX_OFF32_SECREL:
                ir.Type = IMAGE_REL_AMD64_SECREL;
                break;
#endif
            case FIX_OFF64: /* 64bit offset */
                ir.Type = IMAGE_REL_AMD64_ADDR64;
                break;
            case FIX_SEG: /* segment fixup */
                ir.Type = IMAGE_REL_AMD64_SECTION; /* ??? */
                break;
#if 0 /* not supported by COFF64! shouldn't reach this point */
            case FIX_RELOFF8:
            case FIX_RELOFF16:
            case FIX_OFF8:
            case FIX_OFF16:
            case FIX_HIBYTE:
            case FIX_PTR16: /* 16bit far pointer */
            case FIX_PTR32: /* 32bit far pointer */
#endif
            default:
                DebugMsg(("coff_write_fixups(%s, %Xh): reloc loc=%X type=%u idx=%u sym=%s\n",
                          section->sym.name, offset, fix->locofs, fix->type, fix->sym->ext_idx, fix->sym->name));
                EmitErr( UNKNOWN_FIXUP_TYPE, fix->type, section->sym.name, fix->locofs );
                continue; /* v2.03: skip this fixup */
                //break;
            }
        } else
#endif
            switch ( fix->type ) {
            case FIX_VOID:
                continue;
            case FIX_RELOFF16: /* 16bit offset */
                ir.Type = IMAGE_REL_I386_REL16;
                break;
            case FIX_OFF16: /* 16bit offset */
                ir.Type = IMAGE_REL_I386_DIR16;
                break;
            case FIX_RELOFF32: /* 32bit offset */
                ir.Type = IMAGE_REL_I386_REL32;
                break;
            case FIX_OFF32: /* 32bit offset */
                ir.Type = IMAGE_REL_I386_DIR32;
                break;
#if IMAGERELSUPP
            case FIX_OFF32_IMGREL:
                ir.Type = IMAGE_REL_I386_DIR32NB;
                break;
#endif
#if SECTIONRELSUPP
            case FIX_OFF32_SECREL:
                ir.Type = IMAGE_REL_I386_SECREL;
                break;
#endif
            case FIX_SEG: /* segment fixup */
                ir.Type = IMAGE_REL_I386_SECTION; /* ??? */
                break;
#if 0
            case FIX_OFF8:
            case FIX_RELOFF8:
            case FIX_HIBYTE:
            case FIX_PTR16: /* 16bit far pointer */
            case FIX_PTR32: /* 32bit far pointer */
#endif
            default:
                DebugMsg(("coff_write_fixups(%s, %Xh): reloc loc=%X type=%u idx=%u sym=%s\n",
                          section->sym.name, offset, fix->locofs, fix->type, fix->sym->ext_idx, fix->sym->name));
                EmitErr( UNKNOWN_FIXUP_TYPE, fix->type, section->sym.name, fix->locofs );
                continue; /* v2.03: skip this fixup */
                //break;
            }
        /* if it's not EXTERNAL/PUBLIC, add symbol */
        /* if it's an assembly time variable, create helper symbol */
        if ( fix->sym->variable == TRUE ) {
#if HELPSYMS
            struct asym *sym;
            char buffer[12];
            sprintf( buffer, "$$%06X", fix->offset );
            sym = SymAlloc( buffer );
            sym->state = fix->sym->state;
            sym->mem_type = fix->sym->mem_type;
            sym->offset = fix->offset;
            sym->segment = fix->segment;
            sym->variable = TRUE; /* storage class LABEL */
            fix->sym = sym;
            AddPublicData( fix->sym );
            fix->sym->idx = index++;
#else
            /* just use the segment entry. This approach requires
             * that the offset is stored inline at the reloc location
             * (patch in fixup.c)
             */
            fix->sym = fix->segment_var;
#endif
        } else if (( fix->sym->state == SYM_INTERNAL ) &&
                   fix->sym->included == FALSE &&
                   fix->sym->ispublic == FALSE ) {
            fix->sym->included = TRUE;
            AddPublicData( fix->sym );
            DebugMsg(("coff_write_fixups(%s, %Xh): %s added to symbol table, idx=%u\n",
                      section->sym.name, offset, fix->sym->name, index ));
            fix->sym->ext_idx = index++;
            if ( Options.line_numbers && fix->sym->isproc )
                index += 6;
        }
        ir.VirtualAddress = fix->locofs;
        ir.SymbolTableIndex = fix->sym->ext_idx;
        if ( fwrite( &ir, 1, sizeof(ir), CurrFile[OBJ] ) != sizeof(ir) )
            WriteError();
        DebugMsg(("coff_write_fixups(%s, %Xh): reloc loc=%X type=%u idx=%u sym=%s\n",
                  section->sym.name, offset, ir.VirtualAddress, ir.Type, ir.SymbolTableIndex, fix->sym->name));
        offset += sizeof( ir );
        section->e.seginfo->num_relocs++;
    } /* end for */
    DebugMsg(("coff_write_fixups(%s): exit, num_relocs=%" I32_SPEC "u\n", section->sym.name, section->e.seginfo->num_relocs ));
    *poffset = offset;
    *pindex = index;
}

/* write section data */

static ret_code coff_write_data( struct module_info *modinfo, struct coffmod *cm )
/********************************************************************************/
{
    struct dsym *section;
    uint_32 offset = 0; /* offset within section contents */
    int i;
    uint_32 index;

    DebugMsg(("coff_write_data(%s): enter\n", modinfo->name ));

    /* v2.11: removed. max_offset has been set already */
    //if ( directives )
    //    directives->sym.max_offset = size_drectve;

    /* calc the current index for the COFF symbol table */
    index = SetSymbolIndices( modinfo, cm );

    /* fill the SafeSEH array */
    if ( modinfo->g.SafeSEHQueue.head ) {
        struct qnode *sehp;
        struct qnode *sehp2;
        uint_32 *pdw;
        for( sehp = modinfo->g.SafeSEHQueue.head, pdw = (uint_32 *)cm->sxdata->e.seginfo->CodeBuffer; sehp ; sehp = sehp2 ) {
            sehp2 = sehp->next;
            DebugMsg(("coff_write_data: .sxdata value=%08Xh\n", ((struct asym *)sehp->elmt)->ext_idx));
            *pdw++ = ((struct asym *)sehp->elmt)->ext_idx;
            LclFree( sehp );
        }
    }

#if HELPSYMS==0
    for( i = 0, section = SymTables[TAB_SEG].head; section ; i++, section = section->next ) {
        section->sym.ext_idx = cm->sectionstart + i;
        if ( Options.no_section_aux_entry == FALSE )
            section->sym.ext_idx += i;
    }
#endif

    /* now scan the section's relocations. If a relocation refers to
     a symbol which is not public/external, it must be added to the
     symbol table. If the symbol is an assembly time variable, a helper
     symbol - name is $$<offset:6> is to be added.
     */

    for( section = SymTables[TAB_SEG].head; section ; section = section->next ) {
        uint_32 size;
        size = section->sym.max_offset;
#ifdef DEBUG_OUT
        if ( section->e.seginfo->CodeBuffer )
            DebugMsg(("coff_write_data(%s, %Xh): size=%X, written=%X, content=[%02X %02X ...]\n",
                      section->sym.name, offset, size - section->e.seginfo->start_loc, section->e.seginfo->bytes_written, *(section->e.seginfo->CodeBuffer), *(section->e.seginfo->CodeBuffer+1)));
        else
            DebugMsg(("coff_write_data(%s, %Xh): size=%X, buffer=NULL\n",
                      section->sym.name, offset, size - section->e.seginfo->start_loc ));
#endif

        /* don't write section data for bss and uninitialized stack segments */
        if ( section->e.seginfo->combine == COMB_STACK && section->e.seginfo->bytes_written == 0 )
            continue;
        if ( section->e.seginfo->segtype == SEGTYPE_BSS )
            continue;

        if ( size ) {
            offset += size;
            if ((offset & 1) && section->e.seginfo->FixupList.head ) {
                offset++;
                size++;
            }
            if ( section->e.seginfo->CodeBuffer == NULL ) {
                fseek( CurrFile[OBJ], size, SEEK_CUR );
            } else {
                /* if there was an ORG, the buffer content will
                 * start with the ORG address. The bytes from
                 * 0 - ORG must be written by moving the file pointer!
                 */
                if ( section->e.seginfo->start_loc ) {
                    fseek( CurrFile[OBJ], section->e.seginfo->start_loc, SEEK_CUR );
                    size -= section->e.seginfo->start_loc;
                }

                if ( fwrite( section->e.seginfo->CodeBuffer, 1, size, CurrFile[OBJ] ) != size )
                    WriteError();
            }

            coff_write_fixups( section, &offset, &index );
        } /* end if (size) */

        /* v2.07: the following block has beem moved outside of "if(size)" block,
         * because it may happen that a segment has size 0 and still debug info.
         * In any case it's important to initialize section->e.seginfo->num_linnums
         */
        /* write line number data. The peculiarity of COFF (compared to OMF) is
         * that line numbers are always relative to a function start.
         *
         * an item with line number 0 has a special meaning - it contains a reference
         * ( a symbol table index ) to the function whose line numbers are to follow.
         * this item is to be followed by an item with line number 32767, which then
         * tells the function's start offset ( undocumented! ).
         *
         */
        if( Options.line_numbers && section->e.seginfo->LinnumQueue ) {
            IMAGE_LINENUMBER il;
            struct line_num_info *lni;
            struct asym *last;
            uint_32 line_numbers = 0;
            last = NULL;
            lni = (struct line_num_info *)((struct qdesc *)section->e.seginfo->LinnumQueue)->head;
            DebugMsg(("coff_write_data(%s): writing linnum data\n", section->sym.name ));
            for( ; lni; lni = lni->next ) {
                DebugMsg(("coff_write_data(%s, %Xh): linnum, #=%u, %s=%X, sym=%s\n",
                          section->sym.name, offset, lni->number, lni->number ? "ofs" : "idx", lni->offset, lni->number ? "NULL" : lni->sym->name ));
                if ( lni->number == 0 ) {
                    last = lni->sym;
                    if ( cm->lastproc )
                        cm->lastproc->debuginfo->next_proc = lni->sym->ext_idx;
                    cm->lastproc = lni->sym;
                    lni->sym->debuginfo->next_proc = 0;
                    il.Linenumber = 0;
#ifdef DEBUG_OUT
                    /* if symbol table index is 0, then the proc wasn't added
                     * to the "publics" queue in AddLinnumDataRef().
                     */
                    if ( lni->sym->ext_idx == 0 ) {
                        DebugMsg(("coff_write_data(%s, %Xh): error, %s has symbol table index 0\n",
                                  section->sym.name, offset, lni->sym->name ));
                    }
#endif
                    il.Type.SymbolTableIndex = lni->sym->ext_idx;
                    lni->sym->debuginfo->start_line = lni->line_number;
                    //((struct dsym *)lni->sym)->e.procinfo->file = lni->file;
                    lni->sym->debuginfo->ln_fileofs = cm->start_data + offset;
                    DebugMsg(("coff_write_data(%s, %Xh): proc %s start_line=%u\n",
                              section->sym.name, offset, lni->sym->name, lni->sym->debuginfo->start_line ));
                } else {
                    /**/myassert( last != NULL );
                    il.Linenumber = lni->number - last->debuginfo->start_line;
                    /* if current line number - start line number is 0,
                     * generate a "32767" line number item.
                     */
                    if ( il.Linenumber == 0 )
                        il.Linenumber = 0x7FFF;
                    il.Type.VirtualAddress = lni->offset;
                }
                /* v2.11: last is always != NULL */
                //if ( last ) {
                    last->debuginfo->line_numbers++;
                    last->debuginfo->end_line = lni->number;
                //}
                if ( fwrite( &il, 1, sizeof(il), CurrFile[OBJ] ) != sizeof(il) )
                    WriteError();
                offset += sizeof(il);
                line_numbers++;
            } /* end for */
            section->e.seginfo->num_linnums = line_numbers;
        } /* end if (Options.line_numbers...) */
    } /* end for */

    cm->size_data = offset;

    DebugMsg(("coff_write_data: exit, size of sections=%Xh\n", cm->size_data ));

    return( NOT_ERROR );
}

/* check if a .drectve section has to be created.
 * if yes, create it and set its contents.
 */

static void coff_create_drectve( struct module_info *modinfo, struct coffmod *cm )
/********************************************************************************/
{
    struct dsym *exp;
#if DLLIMPORT
    struct dsym *imp = NULL;
#endif
    char buffer[MAX_ID_LEN + MANGLE_BYTES + 1];

    /* does a proc exist with the EXPORT attribute? */
    for( exp = SymTables[TAB_PROC].head; exp != NULL; exp = exp->nextproc ) {
        if( exp->e.procinfo->isexport )
            break;
    }
#if DLLIMPORT
    /* check if an impdef record is there */
    if ( Options.write_impdef && !Options.names[OPTN_LNKDEF_FN] )
        for ( imp = SymTables[TAB_EXT].head; imp; imp = imp->next )
            if ( imp->sym.isproc && ( imp->sym.weak == FALSE || imp->sym.iat_used == TRUE ) )
                if ( imp->sym.dll && *imp->sym.dll->name )
                    break;
#endif
    /* add a .drectve section if
     - a start_label is defined    and/or
     - a library is included       and/or
     - a proc is exported          and/or
     - impdefs are to be written (-Zd)
     */
    if ( modinfo->g.start_label != NULL ||
        modinfo->g.LibQueue.head != NULL ||
#if DLLIMPORT
        imp != NULL ||
#endif
        exp != NULL ) {
        if ( cm->directives = (struct dsym *)CreateIntSegment( szdrectve, "", MAX_SEGALIGNMENT, modinfo->Ofssize, FALSE ) ) {
            struct dsym *tmp;
            int size = 0;
            struct qitem *q;
            uint_8 *p;
            cm->directives->e.seginfo->info = TRUE;
            DebugMsg(("coff_create_drectve: %s section added\n", szdrectve));

            /* calc the size for this segment */
            /* 1. exports */
            for( tmp = exp; tmp ; tmp = tmp->nextproc ) {
                if( tmp->e.procinfo->isexport ) {
                    size += Mangle( &tmp->sym, buffer );
                    size += sizeof("-export:");
                    if ( Options.no_export_decoration == TRUE )
                        size += tmp->sym.name_size + 1;
                }
            }
            /* 2. defaultlibs */
            for( q = modinfo->g.LibQueue.head; q ; q = q->next ) {
                size += strlen( q->value ) + sizeof("-defaultlib:");
                /* if the name isn't enclosed in double quotes and contains
                 a space, add 2 bytes to enclose it */
                if ( *q->value != '"' && strchr( q->value, ' ') )
                    size += 2;
            }
            /* 3. start label */
            size += GetStartLabel( buffer, TRUE );
#if DLLIMPORT
            /* 4. impdefs */
            for( tmp = imp; tmp ; tmp = tmp->next ) {
                if ( tmp->sym.isproc && ( tmp->sym.weak == FALSE || tmp->sym.iat_used == TRUE ) &&
                    tmp->sym.dll && *tmp->sym.dll->name ) {
                    /* format is:
                     * "-import:<mangled_name>=<module_name>.<unmangled_name>" or
                     * "-import:<mangled_name>=<module_name>"
                     */
                    size += sizeof("-import:");
                    size += Mangle( &tmp->sym, buffer );
                    size += 1 + strlen( tmp->sym.dll->name );
                    size += 1 + tmp->sym.name_size;
                }
            }
#endif
            cm->directives->sym.max_offset = size;
            /* v2.09: allocate 1 byte more, because sprintf() is used, which
             * adds a NULLC.
             */
            //directives->e.seginfo->CodeBuffer = LclAlloc( size );
            cm->directives->e.seginfo->CodeBuffer = LclAlloc( size + 1 );
            p = cm->directives->e.seginfo->CodeBuffer;

            /* copy the data */

            /* 1. exports */
            for( tmp = exp; tmp ; tmp = tmp->nextproc ) {
                if( tmp->e.procinfo->isexport ) {
                    Mangle( &tmp->sym, buffer );
                    if ( Options.no_export_decoration == FALSE )
                        p += sprintf( (char *)p, "-export:%s ", buffer );
                    else
                        p += sprintf( (char *)p, "-export:%s=%s ", tmp->sym.name, buffer );
                }
            }
            /* 2. libraries */
            for( q = modinfo->g.LibQueue.head; q ; q = q->next ) {
                if ( *q->value != '"' && strchr( q->value, ' ' ) )
                    p += sprintf( (char *)p,"-defaultlib:\"%s\" ", (char *)q->value );
                else
                    p += sprintf( (char *)p,"-defaultlib:%s ", (char *)q->value );
            }
            /* 3. entry */
            if ( modinfo->g.start_label ) {
                GetStartLabel( buffer, FALSE );
                p += sprintf( (char *)p, "-entry:%s ", buffer );
            }
#if DLLIMPORT
            /* 4. impdefs */
            for( tmp = imp; tmp ; tmp = tmp->next ) {
                if ( tmp->sym.isproc && ( tmp->sym.weak == FALSE || tmp->sym.iat_used == TRUE ) &&
                    tmp->sym.dll && *tmp->sym.dll->name ) {
                    strcpy( p, "-import:" );
                    p += 8;
                    p += Mangle( &tmp->sym, p );
                    *p++ = '=';
                    strcpy( p, tmp->sym.dll->name );
                    p += strlen( p );
                    *p++ = '.';
                    memcpy( p, tmp->sym.name, tmp->sym.name_size );
                    p += tmp->sym.name_size;
                    *p++ = ' ';
                }
            }
#endif
            /**/myassert( size == p - cm->directives->e.seginfo->CodeBuffer );
            //size_drectve = p - directives->e.seginfo->CodeBuffer; /* v2.11:removed */
        }
    }
}

/* Write current object module in COFF format.
 * This function is called AFTER all assembly passes have been done.
 */

static ret_code coff_write_module( struct module_info *modinfo )
/**************************************************************/
{
    struct stringitem  *pName;
    struct coffmod cm;
    struct IMAGE_FILE_HEADER ifh;

    DebugMsg(("coff_write_module: enter, sections=%u\n", modinfo->g.num_segs ));

    memset( &cm, 0, sizeof( cm ) );
    //directives = NULL;
    //LongNames.head = NULL;
    cm.LongNames.size = sizeof( uint_32 );

    /* get value for .file symbol */
    cm.dot_file_value = CurrFName[ASM];
#if 0 /* v2.09: always add the name in CurrFName[ASM] */
    cm.dot_file_value += strlen( dot_file_value );
    while ( cm.dot_file_value > CurrFName[ASM] &&
           *(cm.dot_file_value-1) != '/' &&
           *(cm.dot_file_value-1) != '\\') cm.dot_file_value--;
#endif

    /* it might be necessary to add "internal" sections:
     * - .debug$S and .debug$T sections if -Zi was set
     * - .sxdata section if .SAFESEH was used
     * - .drectve section if start label, exports or includelibs are used
     */
	
    /* if -Zi is set, add .debug$S and .debug$T sections */
    if ( Options.debug_symbols ) {
        int i;
        for ( i = 0; i < DBGS_MAX; i++ ) {
            if ( NULL == ( cm.SymDeb[i].seg = (struct dsym *)CreateIntSegment( SymDebName[i], "", 0, USE32, TRUE ) ) )
                break;
            DebugMsg(("coff_write_module: %s section added\n", SymDebName[i] ));
            cm.SymDeb[i].seg->e.seginfo->characteristics = (IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_DISCARDABLE) >> 24;
            /* use the source line buffer as code buffer. It isn't needed anymore */
            cm.SymDeb[i].seg->e.seginfo->CodeBuffer = CurrSource + i * SIZE_CV_SEGBUF;
            cm.SymDeb[i].seg->e.seginfo->flushfunc = coff_flushfunc;
            cm.SymDeb[i].q.head = NULL;
        }
        if ( i == DBGS_MAX ) {
            cv_write_debug_tables( cm.SymDeb[DBGS_SYMBOLS].seg, cm.SymDeb[DBGS_TYPES].seg, &cm );
            /* the contents have been written in queues. now
             * copy all queue items in ONE buffer.
             */
            for ( i = 0; i < DBGS_MAX; i++ ) {
                uint_8 *src;
                uint_8 *dst;
                if ( cm.SymDeb[i].seg->sym.max_offset ) {
                    cm.SymDeb[i].seg->e.seginfo->CodeBuffer = LclAlloc( cm.SymDeb[i].seg->sym.max_offset );
                    dst = cm.SymDeb[i].seg->e.seginfo->CodeBuffer;
                    for ( src = cm.SymDeb[i].q.head; src; src = ((struct qditem *)src)->next ) {
                        memcpy( dst, src + sizeof( struct qditem ), ((struct qditem *)src)->size );
                        dst += ((struct qditem *)src)->size;
                        /* fixme: free the queue items if FASTMEM==0 */
                    }
                }
            }
        }
    }

    /* if safeSEH procs are defined, add a .sxdata section */
    if ( modinfo->g.SafeSEHQueue.head ) {
        struct qnode *sehp;
        unsigned cnt = 0;
        if ( cm.sxdata = (struct dsym *)CreateIntSegment( ".sxdata", "", MAX_SEGALIGNMENT, modinfo->Ofssize, FALSE ) ) {
            cm.sxdata->e.seginfo->info = TRUE;
            /* calc the size for this segment */
            for( sehp = modinfo->g.SafeSEHQueue.head; sehp ; sehp = sehp->next, cnt++ );
            cm.sxdata->sym.max_offset = cnt*4;
            cm.sxdata->e.seginfo->CodeBuffer = LclAlloc( cnt*4 );
            DebugMsg(("coff_write_module: .sxdata section added, size=%u\n", cnt*4));
        }
    }

    /* create .drectve section if necessary */
    coff_create_drectve( modinfo, &cm );

    /* v2.11: removed, max_offset has been set already */
    //if ( directives )
    //    directives->sym.max_offset = size_drectve;

#if AMD64_SUPPORT
    if ( modinfo->defOfssize == USE64 )
        ifh.Machine = IMAGE_FILE_MACHINE_AMD64;
    else
#endif
        ifh.Machine = IMAGE_FILE_MACHINE_I386;
    ifh.NumberOfSections = modinfo->g.num_segs;
#if 0 //def __UNIX__
    time((int_32 *)&ifh.TimeDateStamp);
#else
    time((time_t *)&ifh.TimeDateStamp);
#endif
    ifh.SizeOfOptionalHeader = 0;
    ifh.Characteristics = 0;

    /* position behind coff file header */
    fseek( CurrFile[OBJ], sizeof( ifh ), SEEK_SET );

    coff_write_section_table( modinfo, &cm );
    coff_write_data( modinfo, &cm );
    /* v2.12: check that calculated sizes are identical to those that have been written */
    /*myassert( cm.start_symtab == ( cm.start_data + cm.size_data ) );*/

    ifh.NumberOfSymbols = coff_write_symbols( modinfo, &cm );
    ifh.PointerToSymbolTable = ( ifh.NumberOfSymbols ? cm.start_data + cm.size_data : 0 );

    /* the string table is ALWAYS written, even if no strings are defined */
    DebugMsg(("coff_write_module: string_table size=%u\n", cm.LongNames.size ));
    if ( fwrite( &cm.LongNames.size, 1, sizeof( cm.LongNames.size ), CurrFile[OBJ] ) != sizeof( cm.LongNames.size ) )
        WriteError();
    for ( pName = cm.LongNames.head; pName; pName = pName->next ) {
        int i = strlen( pName->string ) + 1;
        if ( fwrite( pName->string, 1, i, CurrFile[OBJ] ) != i )
            WriteError();
    }
#if FASTMEM==0
    for ( ; cm.LongNames.head; ) {
        pName = cm.LongNames.head;
        cm.LongNames.head = cm.LongNames.head->next;
        LclFree( pName );
    }
#endif
    /* finally write the COFF file header */
    fseek( CurrFile[OBJ], 0, SEEK_SET);
    if ( fwrite( &ifh, 1, sizeof( ifh ), CurrFile[OBJ] ) != sizeof( ifh ) ) {
        DebugMsg(("coff_write_module: error writing file header\n"));
        WriteError();
    }

    DebugMsg(("coff_write_module: exit\n"));
    return( NOT_ERROR );
}

void coff_init( struct module_info *modinfo )
/*******************************************/
{
    modinfo->g.WriteModule = coff_write_module;
    return;
}
#endif
