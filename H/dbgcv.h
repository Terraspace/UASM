/****************************************************************************
*
*  This code is Public Domain. It's new for Uasm.
*
*  ========================================================================
*
* Description:  MS codeview debug info header. Values and structures
*               in this header are derived from document:
*               "Microsoft Symbol and Type Information"
*               Format Specifications for Windows Version 1.0
*               Tool Interface Standards (TIS)
*
*               CV 5 format is described in
*               "Visual C++ 5.0 Symbolic Debug Information Specification";
*               the doc is available in MSDN libraries ( 199?-2001 ).
*
*               CV 8 is not "officially" described.
*               It's an extended CV5 format - 'names' are no longer
*               prefixed by a 1-byte length, instead they are terminated
*               by a x'00 (asciiz).
*               Additionally, the $$SYMBOLS segment has now sub-sections
*               for filenames, files, linenumbers and symbols.
****************************************************************************/

#ifndef CVDBG_H
#define CVDBG_H 1

#define CV4_SIGNATURE 1
#define CV5_SIGNATURE 2
#define CV8_SIGNATURE 4 /* not yet supported */

#define CV_SIGNATURE CV4_SIGNATURE /* default is CV4 */

/* reserved primitive types (0x0000-0x0FFF) */

struct cv_primitive_type {
    uint_16 size:3, /* see CV_PDS_ below */
    reserved:1,     /* added to size in CV8? */
    type:4,         /* see CV_PDT_ below */
    mode:3,         /* see CV_PDM_ below */
    reserved2:1;
};

/* typeref type. for CV4, this is uint_16, for CV5/CV8, it's uint_32 */

#if CV_SIGNATURE==CV4_SIGNATURE
typedef uint_16 cv_typeref;
#else
typedef uint_32 cv_typeref;
#endif

/* bits 4-7 of predefined primitive types */
enum cv_predef_type_types {
    CV_PDT_SPECIAL           = 0x00, /* CV_PDS_SPECIAL_xxx  */
    CV_PDT_SIGNED_INTEGRAL   = 0x01, /* CV_PDS_INTEGRAL_xxx */
    CV_PDT_UNSIGNED_INTEGRAL = 0x02, /* CV_PDS_INTEGRAL_xxx */
    CV_PDT_BOOLEAN           = 0x03, /* CV_PDS_INTEGRAL_xxx */
    CV_PDT_REAL              = 0x04, /* CV_PDS_REAL_xxx     */
    CV_PDT_COMPLEX           = 0x05, /* CV_PDS_REAL_xxx     */
    CV_PDT_SPECIAL2          = 0x06, /* CV_PDS_SPECIAL2_xxx */
    CV_PDT_REAL_INT_VALUE    = 0x07  /* CV_PDS_REAL_INT_xxx */
    /* values 08-0F are reserved */
};

/* bits 0-2 of predefined primitive types */
enum cv_predef_type_sizes {
    CV_PDS_SPECIAL_NO_TYPE           = 0x00,
    CV_PDS_SPECIAL_ABSOLUTE          = 0x01,
    CV_PDS_SPECIAL_SEGMENT           = 0x02,
    CV_PDS_SPECIAL_VOID              = 0x03,
    CV_PDS_SPECIAL_BASIC_CURRENCY    = 0x04,
    CV_PDS_SPECIAL_BASIC_NEAR_STRING = 0x05,
    CV_PDS_SPECIAL_BASIC_FAR_STRING  = 0x06,
    CV_PDS_SPECIAL_UNTRANSLATED      = 0x07,
    CV_PDS_INTEGRAL_1BYTE            = 0x00,
    CV_PDS_INTEGRAL_2BYTE            = 0x01,
    CV_PDS_INTEGRAL_4BYTE            = 0x02,
    CV_PDS_INTEGRAL_8BYTE            = 0x03,
    /* values 4-7 reserved */
    CV_PDS_REAL_32BIT                = 0x00,
    CV_PDS_REAL_64BIT                = 0x01,
    CV_PDS_REAL_80BIT                = 0x02,
    CV_PDS_REAL_128BIT               = 0x03,
    CV_PDS_REAL_48BIT                = 0x04,
    /* values 5-7 reserved */
    CV_PDS_SPECIAL2_BIT              = 0x00,
    CV_PDS_SPECIAL2_PASCAL_CHAR      = 0x01,
    /* values 2-7 reserved? */
    CV_PDS_REAL_INT_CHAR             = 0x00,
    CV_PDS_REAL_INT_WCHAR            = 0x01,
    CV_PDS_REAL_INT_SINT16           = 0x02,
    CV_PDS_REAL_INT_UINT16           = 0x03,
    CV_PDS_REAL_INT_SINT32           = 0x04,
    CV_PDS_REAL_INT_UINT32           = 0x05,
    CV_PDS_REAL_INT_SINT64           = 0x06,
    CV_PDS_REAL_INT_UINT64           = 0x07,
};

/* bits 8-10 of predefined primitive types */
enum cv_predef_type_modes {
    CV_PDM_DIRECT            = 0x00,
    CV_PDM_NEARPTR           = 0x01,
    CV_PDM_FARPTR            = 0x02,
    CV_PDM_HUGEPTR           = 0x03,
    CV_PDM_NEAR32PTR         = 0x04,
    CV_PDM_FAR32PTR          = 0x05,
    CV_PDM_NEAR64PTR         = 0x06
    /* value 7 reserved */
};

struct cv_attribute {
    uint_16 access:2, /* see CV_ATTR_ACC_ below */
    mprop:3,          /* see CV_ATTR_MPR_ below */
    pseudo:1,
    noinherit:1,
    noconstruct:1,
    reserved:8;
};

enum cv_attr_access {
    CV_ATTR_ACC_NOPROTECTION = 0,
    CV_ATTR_ACC_PRIVATE      = 1,
    CV_ATTR_ACC_PROTECTED    = 2,
    CV_ATTR_ACC_PUBLIC       = 3,
};

enum cv_attr_mprop {
    CV_ATTR_MPR_VANILLA      = 0,
    CV_ATTR_MPR_VIRTUAL      = 1,
    CV_ATTR_MPR_STATIC       = 2,
    CV_ATTR_MPR_FRIEND       = 3,
    CV_ATTR_MPR_INTRO_VIRTUAL = 4,
    CV_ATTR_MPR_PURE_VIRTUAL = 5,
    CV_ATTR_MPR_PURE_INTRO_VIRTUAL = 6,
};

enum cv4_leaf_indices {
    CV4_LF_MODIFIER  = 0x0001,
    CV4_LF_POINTER   = 0x0002,  /* emitted by Uasm */
    CV4_LF_ARRAY     = 0x0003,  /* emitted by Uasm */
    CV4_LF_CLASS     = 0x0004,
    CV4_LF_STRUCTURE = 0x0005,  /* emitted by Uasm */
    CV4_LF_UNION     = 0x0006,  /* emitted by Uasm */
    CV4_LF_ENUM      = 0x0007,
    CV4_LF_PROCEDURE = 0x0008,  /* not yet emitted by Uasm */
    //CV4_LF_MFUNCTION = 0x0009,
    //CV4_LF_VTSHAPE   = 0x000A,
    //CV4_LF_BARRAY    = 0x000D,

    CV4_LF_ARGLIST   = 0x0201,  /* not yet emitted by Uasm */
    CV4_LF_FIELDLIST = 0x0204,  /* emitted by Uasm */
    CV4_LF_BITFIELD  = 0x0206,  /* emitted by Uasm */

    CV4_LF_MEMBER    = 0x0406,  /* emitted by Uasm */
};

enum cv5_leaf_indices {
    CV5_LF_POINTER   = 0x1002,
    CV5_LF_ARRAY     = 0x1003,
    CV5_LF_CLASS     = 0x1004,
    CV5_LF_STRUCTURE = 0x1005,
    CV5_LF_UNION     = 0x1006,
    CV5_LF_ENUM      = 0x1007,
    CV5_LF_PROCEDURE = 0x1008,

    CV5_LF_ARGLIST   = 0x1201,
    CV5_LF_FIELDLIST = 0x1203,
    CV5_LF_BITFIELD  = 0x1205,

    CV5_LF_MEMBER    = 0x1405,
};

enum cv8_leaf_indices {
    CV8_LF_ARRAY     = 0x1503,
    CV8_LF_STRUCTURE = 0x1505,
    CV8_LF_UNION     = 0x1506,
    CV8_LF_MEMBER    = 0x150D,
};

enum cv_leaf_indices {
    LF_MODIFIER  = 0x0001,
    LF_LABEL     = 0x000E,  /* emitted by Uasm */
#if CV_SIGNATURE==CV4_SIGNATURE
    LF_POINTER   = CV4_LF_POINTER,
    LF_ARRAY     = CV4_LF_ARRAY,
    LF_CLASS     = CV4_LF_CLASS,
    LF_STRUCTURE = CV4_LF_STRUCTURE,
    LF_UNION     = CV4_LF_UNION,
    LF_ENUM      = CV4_LF_ENUM,
    LF_PROCEDURE = CV4_LF_PROCEDURE,

    LF_ARGLIST   = CV4_LF_ARGLIST,
    LF_FIELDLIST = CV4_LF_FIELDLIST,
    LF_BITFIELD  = CV4_LF_BITFIELD,

    LF_MEMBER    = CV4_LF_MEMBER,
#else
    LF_POINTER   = CV5_LF_POINTER,
    LF_ARRAY     = CV5_LF_ARRAY,
    LF_CLASS     = CV5_LF_CLASS,
    LF_STRUCTURE = CV5_LF_STRUCTURE,
    LF_UNION     = CV5_LF_UNION,
    LF_ENUM      = CV5_LF_ENUM,
    LF_PROCEDURE = CV5_LF_PROCEDURE,

    LF_ARGLIST   = CV5_LF_ARGLIST,
    LF_FIELDLIST = CV5_LF_FIELDLIST,
    LF_BITFIELD  = CV5_LF_BITFIELD,

    LF_MEMBER    = CV5_LF_MEMBER,
#endif

    LF_NUMERIC   = 0x8000,
    LF_CHAR      = 0x8000,
    LF_SHORT     = 0x8001,
    LF_USHORT    = 0x8002,
    LF_LONG      = 0x8003,
    LF_ULONG     = 0x8004,

    LF_PAD0      = 0xF0,
    LF_PAD1      = 0xF1,
    LF_PAD2      = 0xF2,
    LF_PAD3      = 0xF3,
    LF_PAD4      = 0xF4,
    LF_PAD5      = 0xF5,
    LF_PAD6      = 0xF6,
    LF_PAD7      = 0xF7,
    LF_PAD8      = 0xF8,
    LF_PAD9      = 0xF9,
    LF_PAD10     = 0xFA,
    LF_PAD11     = 0xFB,
    LF_PAD12     = 0xFC,
    LF_PAD13     = 0xFD,
    LF_PAD14     = 0xFE,
    LF_PAD15     = 0xFF
};

struct cv_typerec {
    uint_16 size;
    uint_16 leaf;
};

/* values in attribute bits 0-4 */
enum cv_typerec_pointer_types {
    CV_TYPE_PTRTYPE_NEAR = 0,
    CV_TYPE_PTRTYPE_FAR  = 1,
    CV_TYPE_PTRTYPE_HUGE = 2,
    CV_TYPE_PTRTYPE_BASED1 = 3,
    CV_TYPE_PTRTYPE_BASED2 = 4,
    CV_TYPE_PTRTYPE_BASED3 = 5,
    CV_TYPE_PTRTYPE_BASED4 = 6,
    CV_TYPE_PTRTYPE_BASED5 = 7,
    CV_TYPE_PTRTYPE_BASED6 = 8,
    CV_TYPE_PTRTYPE_BASED7 = 9,
    CV_TYPE_PTRTYPE_NEAR32 = 10,
    CV_TYPE_PTRTYPE_FAR32  = 11,
};

#pragma pack(push, 1)

struct cv_typerec_pointer { /* LF_POINTER v2.10: added */
    struct cv_typerec tr;
    uint_16 attribute;
    union {
        struct cv_primitive_type pptype; /* predefined primitive type */
        cv_typeref type;
    };
    /* variant field ( size? ) */
};

struct cv_typerec_array { /* LF_ARRAY v2.10: added */
    struct cv_typerec tr;
    cv_typeref elemtype;
    cv_typeref idxtype;
    uint_16 length;  /* numeric leaf */
    // length-prefixed name
};

struct cv_typerec_structure { /* LF_STRUCTURE */
    struct cv_typerec tr;
    uint_16 count;
#if CV_SIGNATURE==CV4_SIGNATURE
    cv_typeref field;
    uint_16 property; /* see below */
    cv_typeref dList; /* type of derivation list */
    cv_typeref vshape;/* type of virtual function table shape descriptor */
#else
    uint_16 property; /* see below */
    cv_typeref field;
    cv_typeref dList; /* type of derivation list */
    cv_typeref vshape;/* type of virtual function table shape descriptor */
#endif
    uint_16 length;   /* numeric leaf, size of structure */
    // length-prefixed name
};

/* property flags. some bits are for classes only */

enum cv_typerec_structure_property {
    CVTSP_PACKED   = 0x001,  /* is packed */
    CVTSP_CTOR     = 0x002,  /* has constructors or destructors */
    CVTSP_OVEROPS  = 0x004,
    CVTSP_ISNESTED = 0x008,  /* is nested class/structure */
    CVTSP_CNESTED  = 0x010,  /* contains nested classes/structures */
    CVTSP_OPASSIGN = 0x020,  /* has overloaded assignment */
    CVTSP_OPCAST   = 0x040,  /* has casting methods */
    CVTSP_FWDREF   = 0x080,  /* is a forward ref */
    CVTSP_SCOPED   = 0x100,  /* scoped definition */
};

struct cv_typerec_union { /* LF_UNION */
    struct cv_typerec tr;
    uint_16 count;
#if CV_SIGNATURE==CV4_SIGNATURE
    cv_typeref field;
    uint_16 property;
#else
    uint_16 property;
    cv_typeref field;
#endif
    uint_16 length;    /* numeric leaf */
    // length-prefixed name
};

struct cv_typerec_procedure { /* LF_PROCEDURE */
    struct cv_typerec tr;
    cv_typeref rvtype; /* type of return value */
    uint_8 call;       /* call convention ( C, Pascal, Fastcall, Stdcall, Syscall, Thiscall ) */
    uint_8 rsvd;
    uint_16 numparams; /* number of parameters */
    cv_typeref arglist;
};

struct cv_typerec_label { /* LF_LABEL */
    struct cv_typerec tr;
    uint_16 mode;  /* see below, CV_TYPE_LABEL_ */
};

/* label flags (values for mode) */
enum cv_typerec_label_values {
    CV_TYPE_LABEL_NEAR      = 0x00,
    CV_TYPE_LABEL_FAR       = 0x04
};

struct cv_typerec_arglist { /* LF_ARGLIST */
    struct cv_typerec tr;
    uint_16 argcount;
    //uint_16 indices[];
};

struct cv_typerec_fieldlist { /* LF_FIELDLIST */
    struct cv_typerec tr;
};

struct cv_typerec_bitfield { /* LF_BITFIELD */
    struct cv_typerec tr;
#if CV_SIGNATURE==CV4_SIGNATURE
    uint_8 length;
    uint_8 position;
    cv_typeref type;
#else
    cv_typeref type;
    uint_8 length;
    uint_8 position;
#endif
};

struct cv_typerec_member {  /* LF_MEMBER */
    uint_16 leaf;
#if CV_SIGNATURE==CV4_SIGNATURE
    cv_typeref type;
    struct cv_attribute attribute;
#else
    struct cv_attribute attribute;
    cv_typeref type;
#endif
    uint_16 offset; /* numeric leaf */
    // length-prefixed name
};

enum cv4_symbol_types {
    CV4_S_REGISTER = 0x0002,
    CV4_S_CONSTANT = 0x0003,
    CV4_S_UDT      = 0x0004,

    CV4_S_BPREL32  = 0x0200,
    CV4_S_LDATA32  = 0x0201,
    CV4_S_GDATA32  = 0x0202,
    //CV4_S_PUB32    = 0x0203,
    CV4_S_LPROC32  = 0x0204,
    CV4_S_GPROC32  = 0x0205,
    //CV4_S_BLOCK32  = 0x0207,
    CV4_S_REGREL32 = 0x020C,
    CV4_S_LTHREAD32 = 0x020D,
    CV4_S_GTHREAD32 = 0x020E,
};

/* CV5 symbol types.
 * the new types > 0x1000 have a 4 byte typeref.
 */

enum cv5_symbol_types {
    CV5_S_REGISTER = 0x1001,
    CV5_S_CONSTANT = 0x1002,
    CV5_S_UDT      = 0x1003,

    CV5_S_MANYREG  = 0x1005,
    CV5_S_BPREL32  = 0x1006,
    CV5_S_LDATA32  = 0x1007,
    CV5_S_GDATA32  = 0x1008,
    //CV5_S_PUB32    = 0x1009,
    CV5_S_LPROC32  = 0x100A,
    CV5_S_GPROC32  = 0x100B,
    CV5_S_REGREL32  = 0x100D,
    CV5_S_LTHREAD32 = 0x100E,
    CV5_S_GTHREAD32 = 0x100F,
    CV5_S_COMPILE  = 0x1013, /* not documented in VC50 Spec */
};

/* CV8 symbol types.
 * this types also have a 4-byte typeref AND the name is
 * in asciiz format, not 1-byte-length-prefixed.
 */
enum cv8_symbol_types {
    CV8_S_OBJNAME  = 0x1101,  /* object filename */
    CV8_S_BLOCK32  = 0x1103,
    CV8_S_LABEL32  = 0x1105,
    CV8_S_CONSTANT = 0x1107,
    CV8_S_UDT      = 0x1108,
    CV8_S_BPREL32  = 0x110B,
    CV8_S_LDATA32  = 0x110C,
    CV8_S_GDATA32  = 0x110D,
    CV8_S_LPROC32  = 0x110F,
    CV8_S_GPROC32  = 0x1110,
    CV8_S_REGREL32  = 0x1111,
    CV8_S_LTHREAD32 = 0x1112,
    CV8_S_GTHREAD32 = 0x1113,
};


enum cv_symbol_types {
    S_COMPILE  = 0x0001,
#if CV_SIGNATURE==CV4_SIGNATURE
    S_REGISTER = CV4_S_REGISTER,
    S_CONSTANT = CV4_S_CONSTANT,
    S_UDT      = CV4_S_UDT,
#else
    S_REGISTER = CV5_S_REGISTER,
    S_CONSTANT = CV5_S_CONSTANT,
    S_UDT      = CV5_S_UDT,
#endif
    //S_SSEARCH  = 0x0005, /* used by CVPACK */
    S_ENDBLK   = 0x0006,   /* end of PROC, BLOCK, THUNK, WITH */
    //S_SKIP     = 0x0007,
    //S_CVRES    = 0x0008, /* reserved for CodeView */
    S_OBJNAME  = 0x0009,   /* didn't change for CV5 ( CV8 is different ) */
    //S_ENDARG   = 0x000A, /* end of arguments, not needed */
    //S_RETURN   = 0x000D,

    S_BPREL16  = 0x0100,
    S_LDATA16  = 0x0101,
    S_GDATA16  = 0x0102,
    //S_PUB16    = 0x0103, /* emitted by linker */
    S_LPROC16  = 0x0104,
    S_GPROC16  = 0x0105,
    //S_BLOCK16  = 0x0107,
    S_LABEL16  = 0x0109,
    //S_REGREL16 = 0x010C,

#if CV_SIGNATURE==CV4_SIGNATURE
    S_BPREL32  = CV4_S_BPREL32,
    S_LDATA32  = CV4_S_LDATA32,
    S_GDATA32  = CV4_S_GDATA32,
    //S_PUB32    = CV4_S_PUB32,
    S_LPROC32  = CV4_S_LPROC32,
    S_GPROC32  = CV4_S_GPROC32,
    S_REGREL32  = CV4_S_REGREL32,
    S_LTHREAD32 = CV4_S_LTHREAD32,
    S_GTHREAD32 = CV4_S_GTHREAD32,
#else
    S_BPREL32  = CV5_S_BPREL32,
    S_LDATA32  = CV5_S_LDATA32,
    S_GDATA32  = CV5_S_GDATA32,
    //S_PUB32    = CV5_S_PUB32,
    S_LPROC32  = CV5_S_LPROC32,
    S_GPROC32  = CV5_S_GPROC32,
    S_REGREL32  = CV5_S_REGREL32,
    S_LTHREAD32 = CV5_S_LTHREAD32,
    S_GTHREAD32 = CV5_S_GTHREAD32,
#endif
    S_LABEL32  = 0x0209, /* didn't change for CV5 ( CV8 is different ) */
};

struct cv_symrec {
    uint_16 size;
    uint_16 type;
    //uint_8  data[];
};

struct cv_symrec_compile { /* S_COMPILE */
    struct cv_symrec sr;
    uint_8 machine;  /* see below enum cv_machines */
    uint_8 Language; /* see below enum cv_languages */
    union {
        uint_16 flags;
        struct {
            uint_8 PCodePresent:1,
             FloatPrecision:2,
             Floatpackage:2,
             AmbientData:3; /* see below enum cv_ambient_model */
            uint_8 AmbientCode:3, /* see below enum cv_ambient_model */
             Mode32:1,
             Reserved:4;
        };
    };
    // uint_8 version[];  /* length-prefixed string */
};

enum cv_machines {
    CV_MACH_8080    = 0,  /* ??? */
    CV_MACH_8086    = 1,  /* also 80186 */
    CV_MACH_80286   = 2,
    CV_MACH_80386   = 3,
    CV_MACH_80486   = 4,
    CV_MACH_PENTIUM = 5,
    CV_MACH_P2      = 6, /* also Pentium Pro */
    CV_MACH_P3      = 7,
    CV_MACH_AMD64   = 0xD0,
};

enum cv_languages {
    CV_LANG_C       = 0,
    CV_LANG_CPP     = 1,
    CV_LANG_FORTRAN = 2,
    CV_LANG_MASM    = 3,
    CV_LANG_PASCAL  = 4,
    CV_LANG_BASIC   = 5,
    CV_LANG_COBOL   = 6
};

enum cv_ambient_model {
    CV_AMB_NEAR = 0,
    CV_AMB_FAR  = 1,
    CV_AMB_HUGE = 2,
};

struct cv_symrec_register { /* S_REGISTER */
    struct cv_symrec sr;
    cv_typeref type;
    uint_16 registr; /* low byte is register 1, high byte is (opt) register 2 */
    // length-prefixed name
};

struct cv_symrec_constant { /* S_CONSTANT */
    struct cv_symrec sr;
    cv_typeref type;
    uint_16 value;    /* numeric leaf */
    // length-prefixed name
};

struct cv_symrec_udt { /* S_UDT */
    struct cv_symrec sr;
    cv_typeref type;
    // length-prefixed name
};

struct cv_symrec_endblk { /* S_ENDBLK */
    struct cv_symrec sr;
};

struct cv_symrec_objname { /* S_OBJNAME */
    struct cv_symrec sr;
    uint_32 Signature;
    // length-prefixed name
};

struct cv_symrec_bprel16 { /* S_BPREL16 */
    struct cv_symrec sr;
    int_16 offset;
    cv_typeref type;
    // length-prefixed name
};

struct cv_symrec_ldata16 { /* S_LDATA16, S_GDATA16 */
    struct cv_symrec sr;
    int_16 offset;
    uint_16 segment;
    cv_typeref type;
    // length-prefixed name
};

struct cv_symrec_lproc16 { /* S_LPROC16, S_GPROC16 */
    struct cv_symrec sr;
    uint_32 pParent;
    uint_32 pEnd;
    uint_32 pNext;
    uint_16 proc_length;
    uint_16 debug_start;
    uint_16 debug_end;
    uint_16 offset;
    uint_16 segment;
    cv_typeref proctype; /* typeref */
    uint_8 flags;     /* see enum cv_proc_flags */
    // length-prefixed name
};

enum cv_proc_flags {
    CV_PROCF_FPO       = 0x01,   /* no frame pointer */
    CV_PROCF_INTERRUPT = 0x02,   /* proc is interrrupt routine */
    CV_PROCF_FAR       = 0x04,   /* proc does FAR return */
    CV_PROCF_NEVER     = 0x08,   /* proc does not return */
};

struct cv_symrec_label16 { /* S_LABEL16 */
    struct cv_symrec sr;
    int_16 offset;
    uint_16 segment;
    uint_8 flags;     /* see enum cv_proc_flags */
    // length-prefixed name
};

struct cv_symrec_bprel32 { /* S_BPREL32 */
    struct cv_symrec sr;
    int_32 offset;
    cv_typeref type;
    // length-prefixed name
};

struct cv_symrec_ldata32 { /* S_LDATA32, S_GDATA32 */
    struct cv_symrec sr;
#if CV_SIGNATURE==CV4_SIGNATURE
    int_32 offset;
    uint_16 segment;
    cv_typeref type;
#else
    cv_typeref type;
    int_32 offset;
    uint_16 segment;
#endif
    // length-prefixed name
};

struct cv_symrec_lproc32 { /* S_LPROC32, S_GPROC32 */
    struct cv_symrec sr;
    uint_32 pParent;
    uint_32 pEnd;
    uint_32 pNext;
    uint_32 proc_length;
    uint_32 debug_start;
    uint_32 debug_end;
#if CV_SIGNATURE==CV4_SIGNATURE
    uint_32 offset;
    uint_16 segment;
    cv_typeref proctype; /* typeref */
#else
    cv_typeref proctype; /* typeref */
    uint_32 offset;
    uint_16 segment;
#endif
    uint_8 flags;     /* see enum cv_proc_flags */
    // length-prefixed name
};

enum cv_registers {
    CV_REG_START32 = 17,  /* 17-24 are 32-bit GPRs */
    CV_REG_ESP = CV_REG_START32+4,
    CV_REG_EBP = CV_REG_START32+5,
#if AMD64_SUPPORT
    CV_REG_AMD64_START32 = 360, /* 360-367 are 32-bit GPRs R8D-R15D - undocumented! */
    CV_REG_AMD64_START64 = 328, /* 328-343 are 64-bit GPRs - undocumented! */
    CV_REG_RSP = CV_REG_AMD64_START64+7,
    CV_REG_RBP = CV_REG_AMD64_START64+6,
#endif
};

struct cv_symrec_regrel32 { /* S_REGREL32 */
    struct cv_symrec sr;
    int_32 offset;
#if CV_SIGNATURE==CV4_SIGNATURE
    uint_16 reg;
    cv_typeref type;
#else
    cv_typeref type;
    uint_16 reg;
#endif
    // length-prefixed name
};

struct cv_symrec_label32 { /* S_LABEL32 */
    struct cv_symrec sr;
    int_32 offset;
    uint_16 segment;
    uint_8 flags;     /* see enum cv_proc_flags */
    // length-prefixed name
};

#if 0
/* CV8 declarations - not needed currently */
enum cv8_s_sections {
    CV8_SYMBOLS   = 0xF1,
    CV8_LINNUM    = 0xF2,
    CV8_FILENAMES = 0xF3,
    CV8_FILES     = 0xF4,
    CV8_SECTYP_F5 = 0xF5, /* unknown */
};

/* CV8 line numbers - not supported yet */
struct cv8_linenumber_item {
    uint_32 offset;
    uint_32 line;
};

struct cv8_linenumber_header {
    uint_32 section_start;
    uint_16 section_index;
    uint_32 section_length;
    uint_32 src_file;
    uint_32 num_items; /* number of cv8_linenumber_info items */
    uint_32 length;
};
#endif

#pragma pack(pop)

#endif
