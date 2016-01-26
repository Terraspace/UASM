
/* PE definitions
 * see also: coffspec.h
 */

#ifndef PE_H
#define PE_H

struct IMAGE_DOS_HEADER {
    uint_16 e_magic;          // Magic number
    uint_16 e_cblp;           // Bytes on last page of file
    uint_16 e_cp;             // Pages in file
    uint_16 e_crlc;           // Relocations
    uint_16 e_cparhdr;        // Size of header in paragraphs
    uint_16 e_minalloc;       // Minimum extra paragraphs needed
    uint_16 e_maxalloc;       // Maximum extra paragraphs needed
    uint_16 e_ss;             // Initial (relative) SS value
    uint_16 e_sp;             // Initial SP value
    uint_16 e_csum;           // Checksum
    uint_16 e_ip;             // Initial IP value
    uint_16 e_cs;             // Initial (relative) CS value
    uint_16 e_lfarlc;         // File address of relocation table
    uint_16 e_ovno;           // Overlay number
    uint_16 e_res[4];         // Reserved words
    uint_16 e_oemid;          // OEM identifier (for e_oeminfo)
    uint_16 e_oeminfo;        // OEM information; e_oemid specific
    uint_16 e_res2[10];       // Reserved words
    uint_32 e_lfanew;         // File address of new exe header
};

#if PE_SUPPORT

struct IMAGE_DATA_DIRECTORY {
    uint_32 VirtualAddress;
    uint_32 Size;
};

#define IMAGE_DIRECTORY_ENTRY_EXPORT       0
#define IMAGE_DIRECTORY_ENTRY_IMPORT       1
#define IMAGE_DIRECTORY_ENTRY_RESOURCE     2
#define IMAGE_DIRECTORY_ENTRY_EXCEPTION    3
#define IMAGE_DIRECTORY_ENTRY_SECURITY     4
#define IMAGE_DIRECTORY_ENTRY_BASERELOC    5
#define IMAGE_DIRECTORY_ENTRY_DEBUG        6
#define IMAGE_DIRECTORY_ENTRY_ARCHITECTURE 7
#define IMAGE_DIRECTORY_ENTRY_GLOBALPTR    8
#define IMAGE_DIRECTORY_ENTRY_TLS          9
#define IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG  10
#define IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT 11
#define IMAGE_DIRECTORY_ENTRY_IAT          12

#define IMAGE_NT_OPTIONAL_HDR32_MAGIC      0x10b
#define IMAGE_NT_OPTIONAL_HDR64_MAGIC      0x20b

/* Subsystem values */
#define IMAGE_SUBSYSTEM_UNKNOWN              0   // Unknown subsystem.
#define IMAGE_SUBSYSTEM_NATIVE               1   // Image doesn't require a subsystem.
#define IMAGE_SUBSYSTEM_WINDOWS_GUI          2   // Image runs in the Windows GUI subsystem.
#define IMAGE_SUBSYSTEM_WINDOWS_CUI          3   // Image runs in the Windows character subsystem.
#define IMAGE_SUBSYSTEM_OS2_CUI              5   // image runs in the OS/2 character subsystem.
#define IMAGE_SUBSYSTEM_POSIX_CUI            7   // image runs in the Posix character subsystem.
#define IMAGE_SUBSYSTEM_NATIVE_WINDOWS       8   // image is a native Win9x driver.
#define IMAGE_SUBSYSTEM_WINDOWS_CE_GUI       9   // Image runs in the Windows CE subsystem.
#define IMAGE_SUBSYSTEM_EFI_APPLICATION      10  //
#define IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER  11
#define IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER   12  //
#define IMAGE_SUBSYSTEM_EFI_ROM              13
#define IMAGE_SUBSYSTEM_XBOX                 14

struct IMAGE_OPTIONAL_HEADER32 {

    uint_16 Magic;
    uint_8  MajorLinkerVersion;
    uint_8  MinorLinkerVersion;
    uint_32 SizeOfCode;
    uint_32 SizeOfInitializedData;
    uint_32 SizeOfUninitializedData;
    uint_32 AddressOfEntryPoint;
    uint_32 BaseOfCode;
    uint_32 BaseOfData;

    // NT additional fields.

    uint_32 ImageBase;
    uint_32 SectionAlignment;
    uint_32 FileAlignment;
    uint_16 MajorOperatingSystemVersion;
    uint_16 MinorOperatingSystemVersion;
    uint_16 MajorImageVersion;
    uint_16 MinorImageVersion;
    uint_16 MajorSubsystemVersion;
    uint_16 MinorSubsystemVersion;
    uint_32 Win32VersionValue;
    uint_32 SizeOfImage;
    uint_32 SizeOfHeaders;
    uint_32 CheckSum;
    uint_16 Subsystem;
    uint_16 DllCharacteristics;
    uint_32 SizeOfStackReserve;
    uint_32 SizeOfStackCommit;
    uint_32 SizeOfHeapReserve;
    uint_32 SizeOfHeapCommit;
    uint_32 LoaderFlags;
    uint_32 NumberOfRvaAndSizes;
    struct IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
};

struct IMAGE_PE_HEADER32 {
    uint_32 Signature;
    struct IMAGE_FILE_HEADER FileHeader;
    struct IMAGE_OPTIONAL_HEADER32 OptionalHeader;
};

#if AMD64_SUPPORT

struct IMAGE_OPTIONAL_HEADER64 {
    uint_16 Magic;
    uint_8  MajorLinkerVersion;
    uint_8  MinorLinkerVersion;
    uint_32 SizeOfCode;
    uint_32 SizeOfInitializedData;
    uint_32 SizeOfUninitializedData;
    uint_32 AddressOfEntryPoint;
    uint_32 BaseOfCode;
    uint_64 ImageBase;
    uint_32 SectionAlignment;
    uint_32 FileAlignment;
    uint_16 MajorOperatingSystemVersion;
    uint_16 MinorOperatingSystemVersion;
    uint_16 MajorImageVersion;
    uint_16 MinorImageVersion;
    uint_16 MajorSubsystemVersion;
    uint_16 MinorSubsystemVersion;
    uint_32 Win32VersionValue;
    uint_32 SizeOfImage;
    uint_32 SizeOfHeaders;
    uint_32 CheckSum;
    uint_16 Subsystem;
    uint_16 DllCharacteristics;
    uint_64 SizeOfStackReserve;
    uint_64 SizeOfStackCommit;
    uint_64 SizeOfHeapReserve;
    uint_64 SizeOfHeapCommit;
    uint_32 LoaderFlags;
    uint_32 NumberOfRvaAndSizes;
    struct IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
};

struct IMAGE_PE_HEADER64 {
    uint_32 Signature;
    struct IMAGE_FILE_HEADER FileHeader;
    struct IMAGE_OPTIONAL_HEADER64 OptionalHeader;
};

#endif

/* base relocations */

struct IMAGE_BASE_RELOCATION {
    uint_32 VirtualAddress;
    uint_32 SizeOfBlock;
};

#define IMAGE_REL_BASED_ABSOLUTE   0 /* relocation is skipped */
#define IMAGE_REL_BASED_HIGH       1 /* high 16-bits of a 32-bit target */
#define IMAGE_REL_BASED_LOW        2 /* low 16-bits of a 32-bit target */
#define IMAGE_REL_BASED_HIGHLOW    3 /* 32-bit target */
#define IMAGE_REL_BASED_HIGHADJ    4 /* 32-bit target; first high 16-bits, then low 16-bits in next slot */
//#define IMAGE_REL_BASED_IA64_IMM64 9 /* ??? */
#define IMAGE_REL_BASED_DIR64      10 /* 64-bit target */

/* PE resource directory structure */

struct IMAGE_RESOURCE_DIRECTORY { /* size 16 */
    uint_32 Characteristics;
    uint_32 TimeDateStamp;
    uint_16 MajorVersion;
    uint_16 MinorVersion;
    uint_16 NumberOfNamedEntries;
    uint_16 NumberOfIdEntries;
};

struct IMAGE_RESOURCE_DIRECTORY_ENTRY { /* size 8 */
    union {
        struct {
            uint_32 NameOffset:31;
            uint_32 NameIsString:1; /* is 1 if id is a name */
        };
        uint_32 Name; /* ID is an offset to an IMAGE_RESOURCE_DIR_STRING_U struct */
        uint_16 Id;   /* ID is an integer (usually a resource type ) */
    };
    union {
        uint_32 OffsetToData;
        struct {
            uint_32 OffsetToDirectory:31;
            uint_32 DataIsDirectory:1;
        };
    };
};

struct IMAGE_RESOURCE_DIR_STRING_U {
    uint_16 Length;
    int_16  NameString[1];
};

struct IMAGE_RESOURCE_DATA_ENTRY {
    uint_32 OffsetToData;
    uint_32 Size;
    uint_32 CodePage;
    uint_32 Reserved;
};

#endif

#endif
