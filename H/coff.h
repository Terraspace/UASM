
/* prototypes of functions defined in coff.c */

#ifndef _COFF_H_INCLUDED
#define _COFF_H_INCLUDED

enum dbgseg_index {
    DBGS_SYMBOLS,
    DBGS_TYPES,
    DBGS_MAX
};

struct qditem {
    uint_8 *next;
    unsigned size;
};

struct dbg_section {
    struct dsym* seg;
    struct qdesc q;
};

/* v2.12: all coff global variables replaced by struct coffmod */
struct coffmod {
    struct dsym* directives;    /* .drectve section, contains linker directives */
    struct dsym* sxdata;        /* section for safe exception handler data */
    struct asym* lastproc;      /* used if -Zd is set */
    char* dot_file_value;/* value of .file symbol (isn't written by Masm v8+) */
    uint_32     start_data;     /* file position of start section data */
    uint_32     size_data;      /* total of section contents (incl relocs + linnums) */
    uint_32     start_files;    /* symbol table index of first .file entry used by line number info */
    uint_32     sectionstart;   /* symbol table index of first section */
    struct dbg_section SymDeb[DBGS_MAX]; /* codeview debug sections */
    struct {
        struct stringitem* head;
        struct stringitem* tail;
        uint_32 size;
    } LongNames;
};

extern void coff_init( struct module_info * );

#endif
