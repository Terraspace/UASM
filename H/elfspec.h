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
* Description:  Executable and Linkable Format (ELF) definitions.
*
****************************************************************************/


#ifndef _ELFSPEC_H_INCLUDED_
#define _ELFSPEC_H_INCLUDED_

// the main header

#define EI_NIDENT       16

typedef struct {
    uint_8   e_ident[EI_NIDENT];     // +0 signature & ID info
    uint_16  e_type;                 // +16 file type (i.e. obj file, exe file)
    uint_16  e_machine;              // +18 required architecture
    uint_32  e_version;              // +20 version of the file
    uint_32  e_entry;                // +24 program entry point
    uint_32  e_phoff;                // +28 program header offset
    uint_32  e_shoff;                // +32 section header offset
    uint_32  e_flags;                // +36 processor specific flags
    uint_16  e_ehsize;               // +40 elf header size
    uint_16  e_phentsize;            // +42 program header entry size
    uint_16  e_phnum;                // +44 number of program header entries
    uint_16  e_shentsize;            // +46 section header entry size
    uint_16  e_shnum;                // +48 number of section header entries
    uint_16  e_shstrndx;             // +50 section name string table index.
} Elf32_Ehdr;

typedef struct {
    uint_8   e_ident[EI_NIDENT];     // +0 signature & ID info
    uint_16  e_type;                 // +16 file type (i.e. obj file, exe file)
    uint_16  e_machine;              // +18 required architecture
    uint_32  e_version;              // +20 version of the file
    uint_64  e_entry;                // +24 program entry point
    uint_64  e_phoff;                // +32 program header offset
    uint_64  e_shoff;                // +40 section header offset
    uint_32  e_flags;                // +48 processor specific flags
    uint_16  e_ehsize;               // +52 elf header size
    uint_16  e_phentsize;            // +54 program header entry size
    uint_16  e_phnum;                // +56 number of program header entries
    uint_16  e_shentsize;            // +58 section header entry size
    uint_16  e_shnum;                // +60 number of section header entries
    uint_16  e_shstrndx;             // +62 section name string table index.
} Elf64_Ehdr;

// e_ident field indicies

#define ELF_SIGNATURE   "\177ELF"
#define ELF_SIGNATURE_LEN 4
#define ELFMAG0         '\177'  // bytes of signature
#define ELFMAG1         'E'     // bytes of signature
#define ELFMAG2         'L'     // bytes of signature
#define ELFMAG3         'F'     // bytes of signature
#define EI_MAG0         0       // signature bytes
#define EI_MAG1         1       // signature bytes
#define EI_MAG2         2       // signature bytes
#define EI_MAG3         3       // signature bytes
#define EI_CLASS        4       // "file class", i.e. 32-bit vs. 64-bit
#define EI_DATA         5       // data encoding (big-endian vs. little-endian)
#define EI_VERSION      6       // header version #
#define EI_OSABI        7       // OS/ABI identification
#define EI_ABIVERSION   8       // ABI version
#define EI_PAD          9       // start of padding bytes

// contents of the EI_CLASS field index

#define ELFCLASSNONE    0       // invalid class
#define ELFCLASS32      1       // 32-bit objects
#define ELFCLASS64      2       // 64-bit objects

// contents of the EI_DATA field index

#define ELFDATANONE     0       // invalid data encoding
#define ELFDATA2LSB     1       // "little-endian"
#define ELFDATA2MSB     2       // "big-endian"

// the current elf version number (EI_VERSION)

#define EV_CURRENT      1


// contents of the EI_OSABI field index

#define ELFOSABI_NONE       0   // No extensions or unspecified
#define ELFOSABI_HPUX       1   // Hewlett-Packard HP-UX
#define ELFOSABI_NETBSD     2   // NetBSD
#define ELFOSABI_LINUX      3   // Linux
#define ELFOSABI_SOLARIS    6   // Sun Solaris
#define ELFOSABI_AIX        7   // IBM AIX
#define ELFOSABI_IRIX       8   // SGI IRIX
#define ELFOSABI_FREEBSD    9   // FreeBSD
#define ELFOSABI_TRU64      10  // Compaq TRU64 UNIX
#define ELFOSABI_MODESTO    11  // Novell Modesto
#define ELFOSABI_OPENBSD    12  // Open BSD
#define ELFOSABI_OPENVMS    13  // Open VMS
#define ELFOSABI_NSK        14  // Hewlett-Packard Non-Stop Kernel
#define ELFOSABI_AROS       15  // Amiga Research OS

// elf object file types

#define ET_NONE         0       // no file type
#define ET_REL          1       // relocatable file
#define ET_EXEC         2       // executable file
#define ET_DYN          3       // shared object file
#define ET_CORE         4       // core file
#define ET_LOPROC       0xff00  // processor specific file types
#define ET_HIPROC       0xffff

// elf machine types

#define EM_NONE         0       // No machine
#define EM_386          3       // Intel 80386
#define EM_IA_64        50      // Intel IA-64 processor architecture
#define EM_X86_64       62      // AMD x86-64 architecture

// version number info

#define EV_NONE         0
#define EV_CURRENT      1
#define EV_WPIBM        2       // version identifier for extended ELF

// flags (machine specific)
//EM_M32
#define EF_M32_MAU      0x1

// special section indicies

#define SHN_UNDEF       0
#define SHN_LORESERVE   0xff00
#define SHN_LOPROC      0xff00  // reserved for processor-specific semantics
#define SHN_HIPROC      0xff1f
#define SHN_ABS         0xfff1  // references to this section are absolute
#define SHN_COMMON      0xfff2  // references to this section are common.
#define SHN_HIRESERVE   0xffff

// section header

typedef struct {
    uint_32  sh_name;        // +0 name of the section
    uint_32  sh_type;        // +4 section type
    uint_32  sh_flags;       // +8
    uint_32  sh_addr;        // +12 starting address of section in image
    uint_32  sh_offset;      // +16 start of section in file
    uint_32  sh_size;        // +20 size of section (in file if type != SHT_NOBITS)
    uint_32  sh_link;        // +24 multipurpose field   (based on type)
    uint_32  sh_info;        // +28 another multipurpose field (based on type)
    uint_32  sh_addralign;   // +32 address alignment
    uint_32  sh_entsize;     // +36 entry size for sects with fixed sized entries
} Elf32_Shdr;

typedef struct {
    uint_32  sh_name;        // +0 name of the section
    uint_32  sh_type;        // +4 section type
    uint_64  sh_flags;       // +8
    uint_64  sh_addr;        // +16 starting address of section in image
    uint_64  sh_offset;      // +24 start of section in file
    uint_64  sh_size;        // +32 size of section (in file if type != SHT_NOBITS)
    uint_32  sh_link;        // +40 multipurpose field   (based on type)
    uint_32  sh_info;        // +44 another multipurpose field (based on type)
    uint_64  sh_addralign;   // +48 address alignment
    uint_64  sh_entsize;     // +56 entry size for sects with fixed sized entries
} Elf64_Shdr;

// section types

#define SHT_NULL        0               // inactive
#define SHT_PROGBITS    1               // meaning defined by program
#define SHT_SYMTAB      2               // symbol table
#define SHT_STRTAB      3               // string table
#define SHT_RELA        4               // reloc entries with explicit addends
#define SHT_HASH        5               // symbol hash table
#define SHT_DYNAMIC     6               // dynamic linking information
#define SHT_NOTE        7               // comment information
#define SHT_NOBITS      8               // like PROGBITS but no space in file.
#define SHT_REL         9               // as RELA but no explicit addends
#define SHT_SHLIB       10              // reserved but evil
#define SHT_DYNSYM      11              // dynamic link symbol table

#define SHT_LOOS        0x60000000      /* reserved for environment specific use */
#define SHT_OS          0x60000001      // info to identify target OS
#define SHT_IMPORTS     0x60000002      // info on refs to external symbols
#define SHT_EXPORTS     0x60000003      // info on symbols exported by ordinal
#define SHT_RES         0x60000004      // read-only resource data.
#define SHT_PROGFRAGS   0x60001001      // similar to SHT_PROGBITS
#define SHT_IDMDLL      0x60001002      // symbol name demangling information
#define SHT_DEFLIB      0x60001003      // default static libraries
#define SHT_HIOS        0x6fffffff

#define SHT_LOPROC      0x70000000      // processor specific
#define SHT_X86_64_UNWIND 0x70000001    // contains entries for stack unwinding
#define SHT_HIPROC      0x7fffffff
#define SHT_LOUSER      0x80000000      // user defined sections
#define SHT_HIUSER      0xffffffff

// Old section types.  Readers should handle these, writers must use the above

#define SHT_OS_O        12              // info to identify target OS
#define SHT_IMPORTS_O   13              // info on refs to external symbols
#define SHT_EXPORTS_O   14              // info on symbols exported by ordinal
#define SHT_RES_O       15              // read-only resource data.

/* sh_flags values */

#define SHF_WRITE       0x00000001      // 0 section writable during execution
#define SHF_ALLOC       0x00000002      // 1 section occupies space during exec.
#define SHF_EXECINSTR   0x00000004      // 2 section contains code.
#define SHF_MERGE       0x00000010      // 4 section can be merged
#define SHF_STRINGS     0x00000020      // 5 section contains asciiz strings
#define SHF_BEGIN       0x01000000      // 24 section to be placed at the beginning
                                        // of like-named sections by static link
#define SHF_END         0x02000000      // 25 same, end.
#define SHF_MASKPROC    0xf0000000      // processor specific flags

#define SHF_X86_64_LARGE 0x1000000      // section with more than 2GB - value may be wrong!!!
#define SHF_ALPHA_GPREL 0x10000000

/* symbol table entry */

typedef struct {
    uint_32  st_name;        // symbol name index into string table
    uint_32  st_value;       // symbol "value"
    uint_32  st_size;        // symbol size
    uint_8   st_info;        // symbol's type and binding attribs.
    uint_8   st_other;       // no meaning yet.
    uint_16  st_shndx;       // section index
} Elf32_Sym;

typedef struct {
    uint_32  st_name;        // symbol name index into string table
    uint_8   st_info;        // symbol's type and binding attribs.
    uint_8   st_other;       // no meaning yet.
    uint_16  st_shndx;       // section index
    uint_64  st_value;       // symbol "value"
    uint_64  st_size;        // symbol size
} Elf64_Sym;

// symbol info field contents

#define ELF32_ST_BIND(i)        ((i)>>4)        // get the "bind" subfield
#define ELF32_ST_TYPE(i)        ((i)&0xf)       // get the type subfield
#define ELF32_ST_INFO(b,t)      (((b)<<4)+((t)&0xf)) // make a new st_info

// the macros for 64bits are a guess only
#define ELF64_ST_BIND(i)        ((i)>>4)        // get the "bind" subfield
#define ELF64_ST_TYPE(i)        ((i)&0xf)       // get the type subfield
#define ELF64_ST_INFO(b,t)      (((b)<<4)+((t)&0xf)) // make a new st_info

// bind subfield contents

#define STB_LOCAL       0       // symbol has local binding
#define STB_GLOBAL      1       // symbol has global binding
#define STB_WEAK        2       // symbol has weak binding
#define STB_ENTRY       12      // symbol is entry-point for the load module
#define STB_LOPROC      13      // processor specific semantics
#define STB_HIPROC      15

// type subfield contents

#define STT_NOTYPE      0       // not specified
#define STT_OBJECT      1       // symbol is a data object
#define STT_FUNC        2       // symbol is a code symbol
#define STT_SECTION     3       // symbol associated with a section
#define STT_FILE        4       // symbol gives name of the source file.
#define STT_COMMON      5       // symbol is common
#define STT_IMPORT      11      // reference to a symbol in another module
#define STT_LOPROC      13      // processor specific semantics
#define STT_HIPROC      15

// relocation entries

typedef struct {
    uint_32  r_offset;       // place to apply reloc (from begin of section)
    uint_32  r_info;         // symbol idx, and type of reloc
} Elf32_Rel;

typedef struct {
    uint_32  r_offset;       // place to apply reloc (from begin of section)
    uint_32  r_info;         // symbol idx, and type of reloc
    int_32   r_addend;       // value used as a basis for the reloc.
} Elf32_Rela;

typedef struct {
    uint_64  r_offset;       // place to apply reloc (from begin of section)
    uint_64  r_info;         // symbol idx, and type of reloc
} Elf64_Rel;

typedef struct {
    uint_64  r_offset;       // place to apply reloc (from begin of section)
    uint_64  r_info;         // symbol idx, and type of reloc
    int_64   r_addend;       // value used as a basis for the reloc.
} Elf64_Rela;

// r_info field contents

#define ELF32_R_SYM(i)  ((i)>>8)                // gets the symbol index
#define ELF32_R_TYPE(i) ((uint_8)(i))           // gets the symbol type
#define ELF32_R_INFO(s,t) (((s)<<8)+(uint_8)(t))    // make a new r_info

#define ELF64_R_SYM(i)  ((i)>>32)               // gets the symbol index
#define ELF64_R_TYPE(i) ((i)&0xffffffffL)       // gets the symbol type
#define ELF64_R_INFO(s,t) ((((uint_64)s)<<32)+((t)&0xffffffffL)) // make a new r_info

// relocation types.
//386
enum elf32_relocations {
 R_386_NONE      =  0,
 R_386_32        =  1, /* direct,       S + A     */
 R_386_PC32      =  2, /* PC-relative,  S + A - P */
 R_386_GOT32     =  3, /* GOT entry,    G + A     */
 R_386_PLT32     =  4, /* PLT entry,    L + A - P */
 R_386_COPY      =  5,
 R_386_GLOB_DAT  =  6, /* create GOT entry, S */
 R_386_JMP_SLOT  =  7, /* create PLT entry, S */
 R_386_RELATIVE  =  8, /* rel. to program base, B + A */
 R_386_GOTOFF    =  9, /* offset to GOT, S + A - GOT */
 R_386_GOTPC     = 10, /* GOT + A - P */
 R_386_32PLT     = 11, /* L + A       */
/* GNU extensions for LD */
 R_386_16        = 20, /* 16-bit direct,      S + A     */
 R_386_PC16      = 21, /* 16-bit PC-relative, S + A - P */
 R_386_8         = 22, /* 8-bit direct,       S + A     */
 R_386_PC8       = 23  /* 8-bit PC-relative,  S + A - P */
};

//X86_64
enum elf64_relocations {
 R_X86_64_NONE        =   0,
 R_X86_64_64          =   1,    /* S + A     */
 R_X86_64_PC32        =   2,    /* S + A - P */
 R_X86_64_GOT32       =   3,    /* G + A     */
 R_X86_64_PLT32       =   4,    /* L + A - P */
 R_X86_64_COPY        =   5,    /*           */
 R_X86_64_GLOB_DAT    =   6,    /* S         */
 R_X86_64_JUMP_SLOT   =   7,    /* S         */
 R_X86_64_RELATIVE    =   8,    /* B + A     */
 R_X86_64_GOTPCREL    =   9,    /* G + GOT + A - P */
 R_X86_64_32          =  10,    /* S + A     */
 R_X86_64_32S         =  11,    /* S + A     */
 R_X86_64_16          =  12,    /* S + A     */
 R_X86_64_PC16        =  13,    /* S + A - P */
 R_X86_64_8           =  14,    /* S + A     */
 R_X86_64_PC8         =  15,    /* S + A - P */
 R_X86_64_DPTMOD64    =  16,
 R_X86_64_DTPOFF64    =  17,
 R_X86_64_TPOFF64     =  18,
 R_X86_64_TLSGD       =  19,
 R_X86_64_TLSLD       =  20,
 R_X86_64_DTPOFF32    =  21,
 R_X86_64_GOTTPOFF    =  22,
 R_X86_64_TPOFF32     =  23,
 R_X86_64_PC64        =  24,    /* S + A - P   */
 R_X86_64_GOTOFF64    =  25,    /* S + A - GOT */
 R_X86_64_GOTPC32     =  26,    /* GOT + A - P */
 R_X86_64_SIZE32      =  32,
 R_X86_64_SIZE64      =  33
};

// program header

typedef struct {
    uint_32  p_type;         // type of segment
    uint_32  p_offset;       // offset of segment from beginnning of file
    uint_32  p_vaddr;        // segment virtual address
    uint_32  p_paddr;        // segment physical address
    uint_32  p_filesz;       // size of segment in file
    uint_32  p_memsz;        // size of segment in memory
    uint_32  p_flags;
    uint_32  p_align;        // segment align value (in mem & file)
} Elf32_Phdr;

// segment types

#define PT_NULL         0               // unused segment
#define PT_LOAD         1               // loadable segment
#define PT_DYNAMIC      2               // contains dynamic linking information
#define PT_INTERP       3               // reference to a program interpreter
#define PT_NOTE         4               // comments & auxiliary information
#define PT_SHLIB        5               // here be dragons
#define PT_PHDR         6               // address of prog. header in mem (for interp.)
#define PT_OS           0x60000001      // target os information
#define PT_RES          0x60000002      // read-only resource information
#define PT_LOPROC       0x70000000      // processor specific
#define PT_HIPROC       0x7fffffff

// Old segment types.  Readers should handle these, writers must use the above

#define PT_OS_O         7       // target os information
#define PT_RES_O        9       // read-only resource information

// note entry format

typedef struct {
    uint_32       n_namesz; // length of name
    uint_32       n_descsz; // length of descriptor
    uint_32       n_type;   // user defined "type" of the note
    //char        name[];   // variable length name
    //uint_32     desc[];   // descriptors go here
} Elf_Note;

// note types (used in core files)

#define NT_PRSTATUS     1       // process status
#define NT_FPREGSET     2       // floating point registers
#define NT_PRPSINFO     3       // process state info

// dynamic segment entry information.

typedef struct {
    int_32           d_tag;
    union {
        uint_32      d_val;
        uint_32      d_ptr;
    } d_un;
} Elf32_Dyn;

// dynamic array tags

#define DT_NULL         0
#define DT_NEEDED       1               // name of a needed library
#define DT_PLTRELSZ     2               // size of reloc entries for PLT
#define DT_PLTGOT       3               // address with PLT or GOT
#define DT_HASH         4               // symbol hash table address
#define DT_STRTAB       5               // string table address
#define DT_SYMTAB       6               // symbol table address
#define DT_RELA         7               // address of reloc table with addends
#define DT_RELASZ       8               // size of the DT_RELA table
#define DT_RELAENT      9               // size of a DT_RELA entry
#define DT_STRSZ        10              // size of the string table
#define DT_SYMENT       11              // size of a symbol table entry
#define DT_SONAME       14              // shared object name
#define DT_REL          17              // address of reloc table without addends
#define DT_RELSZ        18              // size of the DT_REL table
#define DT_RELENT       19              // size of a DT_REL entry
#define DT_PLTREL       20              // type of reloc entry for PLT
#define DT_DEBUG        21              // for debugging information
#define DT_JMPREL       23              // reloc entries only with PLT
#define DT_EXPORT       0x60000001      // address of export table
#define DT_EXPORTSZ     0x60000002      // size of export table
#define DT_EXPENT       0x60000003      // size of export table entry
#define DT_IMPORT       0x60000004      // address of import table
#define DT_IMPORTSZ     0x60000005      // size of import table
#define DT_IMPENT       0x60000006      // size of import table entry
#define DT_IT           0x60000007      // init and term types for a DLL.
#define DT_ITPRTY       0x60000008      // relative priority of init and term to other functions
#define DT_INITTERM     0x60000009      // address of init and term function
#define DT_PPC_GOT      0x70000001      // address of Global Offset Table
#define DT_PPC_GOTSZ    0x70000002      // size of Global Offset Table
#define DT_PPC_PLTSZ    0x70000003      // size of Procedure Linkage Table
#define DT_LOPROC       0x70000000      // range of processor-defined tags
#define DT_HIPROC       0x7FFFFFFF

// Old dynamic tags.  Readers should handle these, writers must use the above

#define DT_INIT_O       12      // address of initialization function
#define DT_FINI_O       13      // address of finialization function
#define DT_RPATH_O      15      // library search path
#define DT_SYMBOLIC_O   16      // affects dyn. linker's sym. resolution
#define DT_TEXTREL_O    22      // signal we might mod. a non-writable segment
#define DT_IT_O         24      // init and term types for a DLL.
#define DT_EXPORT_O     25      // address of export table
#define DT_EXPORTSZ_O   26      // size of export table
#define DT_IMPORT_O     27      // address of import table
#define DT_IMPORTSZ_O   28      // size of import table
#define DT_GOT_O        29      // address of Global Offset Table
#define DT_GOTSZ_O      30      // size of Global Offset Table
#define DT_PLTSZ_O      32      // size of Procedure Linkage Table
#define DT_ITPRTY_O     33      // relative priority of init and term to other functions
#define DT_LOUSER_O     0x60000000      // range of user-definable tags. will not
#define DT_HIUSER_O     0x6FFFFFFF      // conflict with system-defined tags
                                        // Ha Ha Ha!

// description of DT_IT tag:
// Describe type for initalization and termination of DLL
// Required if DT_INIT and DT_FINI also specified

#define ELF_32_IT_INIT(it)      ((it) & 0x0f)
#define ELF_32_IT_TERM(it)      (((it) >> 4) & 0x0f)
#define ELF_32_IT_INFO(i,t)     (((i) & 0x0f)|(((t) & 0x0f) << 4))

#define IT_NONE         0       // no initialization or termination
#define IT_GLOBAL       1       // global init, term
#define IT_INSTANCE     2       // process init, term
#define IT_THREAD       3       // thread init, term

// DT_INITTERM function prototype

typedef unsigned long INITTERM ( unsigned long modhandle, unsigned long flag );

// elf segment flag bits

#define PF_X            0x1             // seg has execute permissions
#define PF_W            0x2             // seg has write permissions
#define PF_R            0x4             // seg has read permissions
#define PF_S            0x01000000      // segment is shared.
#define PF_MASKPROC     0xf0000000      // processor-specific flag mask

// operating system information

typedef struct {
    uint_32  os_type;
    uint_32  os_size;
} Elf32_Os;

#define EOS_NONE        0       // bad or unknown
#define EOS_PN          1       // IBM Microkernel personality neutral
#define EOS_SVR4        2       // UNIX System V Release 4
#define EOS_AIX         3       // IBM AIX
#define EOS_OS2         4       // IBM OS/2, 32 bit
#define EOS_NT          5       // Microsoft Windows NT, 32 bit
#define EOS_VMS         6       // DEC VMS/VAX
#define EOS_OS400       7       // IBM OS/400
#define EOS_NEXT        8       // NEXT
#define EOS_SYSTEM7     9       // Apple System 7

// OS/2-specific information

typedef struct {
    unsigned char       os2_sessiontype;
    unsigned char       os2_sessionflags;
    unsigned char       os2_reserved[14];
} Elf32_OS2Info;

// os2_sessiontype values

#define OS2_SES_NONE    0       // no session type.  Only valid for DLL's
#define OS2_SES_FS      1       // Full Screen session.
#define OS2_SES_PM      2       // Presentation Manager session.
#define OS2_SES_VIO     3       // Windowed (character-mode) session

// import table entry

typedef struct {
    uint_32  imp_ordinal;
    uint_32  imp_name;
    uint_32  imp_info;
    uint_32  imp_reserved;
} Elf32_Import;

#define ELF32_IMP_TYPE(i)       ((i) >> 24)
#define ELF32_IMP_DLL(i)        ((i) & 0x00FFFFFF)
#define ELF32_IMP_INFO(t,d)     (((t)<<24) | ((d) & 0x00FFFFFF)))

#define IMP_IGNORED     0       // This import entry to be ignored
#define IMP_STR_IDX     1       // Value is string table index to load module
#define IMP_DT_IDX      2       // Value is ref to DT_NEEDED in Dynamic Segment

// export table entry

typedef struct {
    uint_32  exp_ordinal;
    uint_32  exp_symbol;
    uint_32  exp_name;
    uint_32  exp_reserved;
} Elf32_Export;

// Resource header

#define RH_NIDENT       16

typedef struct {
    unsigned char    rh_ident[RH_NIDENT];
    uint_32          rh_name;
    uint_32          rh_itnum;
    uint_32          rh_rhsize;
    uint_32          rh_size;
    uint_32          rh_strtab;
} Elf32_Rhdr;

// rh_ident field indices

#define ELFRESMAG0      '\002'  // bytes of signature
#define ELFRESMAG1      'R'     // bytes of signature
#define ELFRESMAG2      'E'     // bytes of signature
#define ELFRESMAG3      'S'     // bytes of signature
#define RH_MAG0         0       // signature bytes
#define RH_MAG1         1       // signature bytes
#define RH_MAG2         2       // signature bytes
#define RH_MAG3         3       // signature bytes
#define RH_CLASS        4       // class of resource collection
#define RH_DATA         5       // data encoding of resource collection
#define RH_VERSION      6       // version
#define RH_PAD          7       // start of padding bytes - set to 0

// contents of RH_CLASS field

#define RESCLASSNONE    0       // invalid class
#define RESCLASS32      2       // 32-bit architecture
#define RESCLASS64      3       // reserved for 64-bit architecture

// contents of RH_DATA field

#define RESDATANONE     0       // invalid data
#define RESDATA2LSB     1       // Little Endian data encoding
#define RESDATA2MSB     2       // Bit Endian data encoding

// contents of RH_VERSION field

#define RV_NONE         0       // invalid version
#define RV_CURRENT      1       // current version.  will change in future.

// resource item

#define RI_NIDENT       4

typedef struct {
    unsigned char       ri_ident[RI_NIDENT];
    uint_32          ri_type;
    uint_32          ri_typename;
    uint_32          ri_ordinal;
    uint_32          ri_ordname;
    uint_32          ri_data;
    uint_32          ri_flags;
    uint_32          ri_size;
    uint_32          ri_reserved;
} Elf32_Ritem;

// ri_ident field indices

#define RI_VERSION      0       // version
#define RI_PAD          1       // start of padding bytes - set to 0

// contents of RI_VERSION field

#define IV_NONE         0       // invalid version
#define IV_CURRENT      1       // current version.  will change in future

// demangle information structure

typedef struct {
    uint_32  idm_dllname;
    uint_32  idm_initparms;
} Elf32_Demangle;

// default library structure

typedef struct {
    uint_32  lib_name;
} Elf32_Library;

#endif // _ELFSPEC_H_INCLUDED_
