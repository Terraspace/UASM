;--- some declarations from winnt.inc

IMAGE_DOS_HEADER	struct 
e_magic		WORD	?
e_cblp		WORD	?
e_cp		WORD	?
e_crlc		WORD	?
e_cparhdr	WORD	?
e_minalloc	WORD	?
e_maxalloc	WORD	?
e_ss		WORD	?
e_sp		WORD	?
e_csum		WORD	?
e_ip		WORD	?
e_cs		WORD	?
e_lfarlc	WORD	?
e_ovno		WORD	?
e_res		WORD 4 dup (?)
e_oemid		WORD	?
e_oeminfo	WORD	?
e_res2		WORD 10 dup (?)
e_lfanew	SDWORD	?
IMAGE_DOS_HEADER	ends

IMAGE_FILE_HEADER	struct 
Machine					WORD	?
NumberOfSections		WORD	?
TimeDateStamp			DWORD	?
PointerToSymbolTable	DWORD	?
NumberOfSymbols			DWORD	?
SizeOfOptionalHeader	WORD	?
Characteristics			WORD	?
IMAGE_FILE_HEADER	ends


IMAGE_FILE_MACHINE_AMD64              equ 8664h

IMAGE_FILE_RELOCS_STRIPPED	EQU	0001h
IMAGE_FILE_EXECUTABLE_IMAGE	EQU	0002h
IMAGE_FILE_LINE_NUMS_STRIPPED	EQU	0004h
IMAGE_FILE_LOCAL_SYMS_STRIPPED	EQU	0008h
IMAGE_FILE_AGGRESIVE_WS_TRIM	EQU	0010h
IMAGE_FILE_LARGE_ADDRESS_AWARE	EQU	0020h
IMAGE_FILE_BYTES_REVERSED_LO	EQU	0080h
IMAGE_FILE_32BIT_MACHINE	EQU	0100h
IMAGE_FILE_DEBUG_STRIPPED	EQU	0200h
IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP	EQU	0400h
IMAGE_FILE_NET_RUN_FROM_SWAP	EQU	0800h
IMAGE_FILE_SYSTEM	EQU	1000h
IMAGE_FILE_DLL	EQU	2000h
IMAGE_FILE_UP_SYSTEM_ONLY	EQU	4000h

IMAGE_DATA_DIRECTORY	struct 
VirtualAddress		DWORD	?
Size_				DWORD	?
IMAGE_DATA_DIRECTORY	ends

IMAGE_NUMBEROF_DIRECTORY_ENTRIES	EQU	16

IMAGE_OPTIONAL_HEADER64 STRUCT
    Magic                         WORD       ?
    MajorLinkerVersion            BYTE       ?
    MinorLinkerVersion            BYTE       ?
    SizeOfCode                    DWORD      ?
    SizeOfInitializedData         DWORD      ?
    SizeOfUninitializedData       DWORD      ?
    AddressOfEntryPoint           DWORD      ?
    BaseOfCode                    DWORD      ?
    ImageBase                     QWORD      ?
    SectionAlignment              DWORD      ?
    FileAlignment                 DWORD      ?
    MajorOperatingSystemVersion   WORD       ?
    MinorOperatingSystemVersion   WORD       ?
    MajorImageVersion             WORD       ?
    MinorImageVersion             WORD       ?
    MajorSubsystemVersion         WORD       ?
    MinorSubsystemVersion         WORD       ?
    Win32VersionValue             DWORD      ?
    SizeOfImage                   DWORD      ?
    SizeOfHeaders                 DWORD      ?
    CheckSum                      DWORD      ?
    Subsystem                     WORD       ?
    DllCharacteristics            WORD       ?
    SizeOfStackReserve            QWORD      ?
    SizeOfStackCommit             QWORD      ?
    SizeOfHeapReserve             QWORD      ?
    SizeOfHeapCommit              QWORD      ?
    LoaderFlags                   DWORD      ?
    NumberOfRvaAndSizes           DWORD      ?
    DataDirectory                 IMAGE_DATA_DIRECTORY IMAGE_NUMBEROF_DIRECTORY_ENTRIES dup(<>)
  IMAGE_OPTIONAL_HEADER64 ENDS

IMAGE_SUBSYSTEM_WINDOWS_CUI	EQU	3

IMAGE_SIZEOF_SHORT_NAME	EQU	8

IMAGE_SECTION_HEADER	struct 
Name_					BYTE IMAGE_SIZEOF_SHORT_NAME dup (?)
union Misc
PhysicalAddress			DWORD	?
VirtualSize				DWORD	?
ends
VirtualAddress			DWORD	?
SizeOfRawData			DWORD	?
PointerToRawData		DWORD	?
PointerToRelocations	DWORD	?
PointerToLinenumbers	DWORD	?
NumberOfRelocations		WORD	?
NumberOfLinenumbers		WORD	?
Characteristics			DWORD	?
IMAGE_SECTION_HEADER	ends

IMAGE_SCN_MEM_EXECUTE	EQU	20000000h
IMAGE_SCN_MEM_READ		EQU	40000000h
IMAGE_SCN_MEM_WRITE		EQU	80000000h

IMAGE_IMPORT_DESCRIPTOR	struct 
union
Characteristics	DWORD	?
OriginalFirstThunk	DWORD	?
ends
TimeDateStamp	DWORD	?
ForwarderChain	DWORD	?
Name_	DWORD	?
FirstThunk	DWORD	?
IMAGE_IMPORT_DESCRIPTOR	ends

