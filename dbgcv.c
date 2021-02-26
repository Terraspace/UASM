/***************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:  Generate CodeView symbolic debug info ( Version 4 format )
*
****************************************************************************/

#include <stddef.h>

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "segment.h"
#include "fixup.h"
#include "myassert.h"
#include "dbgcv.h"

#define EQUATESYMS 1 /* 1=generate info for EQUates ( -Zi3 ) */

#define SIZE_CV_SEGBUF ( MAX_LINE_LEN * 2 ) /* assumed size of codeview sections temp buffer */
#define GENPTRTYPE 0 /* generate a generic pointer type */
#define SetPrefixName( p, name, len ) *p++ = len; memcpy( p, name, len ); p += len

extern const char szCVCompiler[];

union cv_typeref_u {
    struct cv_primitive_type s;
    cv_typeref uvalue;
};


struct dbgcv {
    union {
        uint_8 *ps;
        struct cv_symrec_compile  *ps_cp;  /* S_COMPILE  */
        struct cv_symrec_register *ps_reg; /* S_REGISTER */
        struct cv_symrec_constant *ps_con; /* S_CONSTANT */
        struct cv_symrec_udt      *ps_udt; /* S_UDT      */
        struct cv_symrec_endblk   *ps_eb;  /* S_ENDBLK   */
        struct cv_symrec_objname  *ps_on;  /* S_OBJNAME  */
        struct cv_symrec_bprel16  *ps_br16;/* S_BPREL16  */
        struct cv_symrec_ldata16  *ps_d16; /* S_xDATA16  */
        struct cv_symrec_lproc16  *ps_p16; /* S_xPROC16  */
        struct cv_symrec_label16  *ps_l16; /* S_LABEL16  */
        struct cv_symrec_bprel32  *ps_br32;/* S_BPREL32  */
        struct cv_symrec_ldata32  *ps_d32; /* S_xDATA32  */
        struct cv_symrec_lproc32  *ps_p32; /* S_xPROC32  */
        struct cv_symrec_regrel32 *ps_rr32;/* S_REGREL32 */
        struct cv_symrec_label32  *ps_l32; /* S_LABEL32  */
    };
    struct dsym *symbols;
    union {
        uint_8 *pt;
        struct cv_typerec_array     *pt_ar;
        struct cv_typerec_pointer   *pt_ptr;
        struct cv_typerec_bitfield  *pt_bf;
        struct cv_typerec_union     *pt_un;
        struct cv_typerec_structure *pt_st;
        struct cv_typerec_procedure *pt_pr;
        struct cv_typerec_arglist   *pt_al;
        struct cv_typerec_fieldlist *pt_fl;
        struct cv_typerec_member    *pt_mbr;
    };
    struct dsym *types;
    void *param;
    unsigned level;  /* nesting level */
    cv_typeref currtype; /* current type ( starts with 0x1000 ) */
#if GENPTRTYPE
    uint_16 ptrtype[3]; /* generic 16-,32- and 64-bit pointer type */
#endif
};

struct leaf32 {
    uint_16 leaf;
    uint_32 value32;
};

static const union cv_typeref_u cv_idx_type = { CV_PDS_INTEGRAL_4BYTE, 0, CV_PDT_SIGNED_INTEGRAL, CV_PDM_DIRECT, 0 };
static const union cv_typeref_u cv_void     = { CV_PDS_SPECIAL_VOID,   0, CV_PDT_SPECIAL,         CV_PDM_DIRECT, 0 };
//static const union cv_typeref_u cv_pvoid    = { CV_PDS_SPECIAL_VOID,   0, CV_PDT_SPECIAL,         CV_PDM_DIRECT, 0 };
#if EQUATESYMS
static const union cv_typeref_u cv_abs_type = { CV_PDS_SPECIAL_ABSOLUTE,0,CV_PDT_SPECIAL,         CV_PDM_DIRECT, 0 };
#endif

/* translate symbol's mem_type to a codeview typeref */

static cv_typeref GetTyperef( struct asym *sym, uint_8 Ofssize )
/**************************************************************/
{
    union cv_typeref_u value = { CV_PDS_SPECIAL_NO_TYPE, 0, CV_PDT_SPECIAL, CV_PDM_DIRECT, 0 };

    if ( ( sym->mem_type & MT_SPECIAL ) == 0 ) {
        int size = SizeFromMemtype( sym->mem_type, Ofssize, sym->type );
        if ( sym->mem_type & MT_FLOAT ) {
            value.s.type = CV_PDT_REAL;
            switch ( size ) {
            case 4:  value.s.size = CV_PDS_REAL_32BIT; break;
            case 8:  value.s.size = CV_PDS_REAL_64BIT; break;
            case 10: value.s.size = CV_PDS_REAL_80BIT; break;
            }
        } else if ( size <= 8 ) {
            if ( sym->mem_type & MT_SIGNED )
                value.s.type = CV_PDT_SIGNED_INTEGRAL;
            else
                value.s.type = CV_PDT_UNSIGNED_INTEGRAL;
            switch ( size ) {
            case 1:  value.s.size = CV_PDS_INTEGRAL_1BYTE; break;
            case 2:  value.s.size = CV_PDS_INTEGRAL_2BYTE; break;
            case 4:  value.s.size = CV_PDS_INTEGRAL_4BYTE; break;
            case 8:  value.s.size = CV_PDS_INTEGRAL_8BYTE; break;
            case 6: /* v2.11: added ( FWORD ) */
                value.s.type = CV_PDT_SPECIAL;
                value.s.size = CV_PDS_SPECIAL_VOID;
                value.s.mode = CV_PDM_FAR32PTR;
                break;
            }
        } else { /* v2.11: branch added */
            /* problem: there's no integral size > 8 bytes.
             * Masm v8+ sets 79h (=?) for 16-byte and 3h (=void) for 32-byte.
             * jwasm sets uint64, which allows to view at least
             * the lower 8 bytes.
             */
            value.s.type = CV_PDT_REAL_INT_VALUE;
            value.s.size = CV_PDS_REAL_INT_UINT64;
        }
    } else {
        switch ( sym->mem_type ) {
        //case MT_ABS:  break;  /* v2.07: MT_ABS obsolete */
        case MT_PTR:
            /* v2.10 */
            value.s.size = CV_PDS_SPECIAL_VOID;
            value.s.type = CV_PDT_SPECIAL;
            switch ( sym->Ofssize ) {
            case USE16:
                value.s.mode = ( sym->isfar ? CV_PDM_FARPTR : CV_PDM_NEARPTR );
                break;
            case USE32:
                value.s.mode = ( sym->isfar ? CV_PDM_FAR32PTR : CV_PDM_NEAR32PTR );
                break;
#if AMD64_SUPPORT
            case USE64:
                value.s.mode = CV_PDM_NEAR64PTR;
                break;
#endif
            }
            break;
        case MT_BITS:
            if ( sym->cvtyperef )
                return( sym->cvtyperef );
            break;
        case MT_NEAR: value.s.mode = CV_PDM_NEARPTR; break;
        case MT_FAR:  value.s.mode = CV_PDM_FARPTR; break;
        case MT_TYPE:
            for ( sym = sym->type; sym->type; sym = sym->type );
            if ( sym->cvtyperef )
                return( sym->cvtyperef );
            DebugMsg(( "GetTypeRef, MT_TYPE: sym=%s state=%X memt=%X\n", sym->name, sym->state, sym->mem_type ));
            return( GetTyperef( sym, Ofssize ) );
            break;
        }
    }

    return( value.uvalue );
}

/* calc size of a codeview item in symbols segment */

static uint_16 GetCVStructLen( struct asym *sym, uint_8 Ofssize )
/***************************************************************/
{
    uint_16 len;
    switch ( sym->state ) {
    case SYM_TYPE:
        len = sizeof( struct cv_symrec_udt );
        break;
    default:
        if ( sym->isproc && Options.debug_ext >= CVEX_REDUCED ) {
            len = ( Ofssize == USE16 ? sizeof( struct cv_symrec_lproc16 ) : sizeof( struct cv_symrec_lproc32 ) );
        } else if ( sym->mem_type == MT_NEAR || sym->mem_type == MT_FAR ) {
            len = ( Ofssize == USE16 ? sizeof( struct cv_symrec_label16 ) : sizeof( struct cv_symrec_label32 ) );
#if EQUATESYMS
        } else if ( sym->isequate ) {
            len = sizeof( struct cv_symrec_constant ) + ( sym->value >= LF_NUMERIC ? 2 : 0 );
#endif
        } else {
            len = ( Ofssize == USE16 ? sizeof( struct cv_symrec_ldata16 ) : sizeof( struct cv_symrec_ldata32 ) );
        }
    }
    return( len );
}

/* flush the segment buffer for symbols and types.
 * For OMF, the buffer is written to disk. For COFF, it's
 * more complicated, because we cannot write now, but also
 * don't know yet the final size of the segment. So a linked
 * list of buffer items has to be created. The contents will
 * later be written inside coff_write_header().
 */
#define checkflush( seg, curr, size, param ) seg->e.seginfo->flushfunc( seg, curr, size, param )

static void PadBytes( uint_8 *curr, uint_8 *base )
/************************************************/
{
    static const char padtab[] = { LF_PAD1, LF_PAD2, LF_PAD3 };
    while( ( curr - base ) & 3 )
        *curr++ = padtab[3-((curr - base) & 3)];
}

/* write a bitfield to $$TYPES */

static void cv_write_bitfield( struct dbgcv *cv, struct dsym *type, struct asym *sym )
/************************************************************************************/
{
    cv->pt = checkflush( cv->types, cv->pt, sizeof( struct cv_typerec_bitfield ), cv->param );
    sym->cvtyperef = cv->currtype++;
    cv->pt_bf->tr.size = sizeof( struct cv_typerec_bitfield ) - sizeof(uint_16);
    cv->pt_bf->tr.leaf = LF_BITFIELD;
    cv->pt_bf->length = sym->total_size;
    cv->pt_bf->position = sym->offset;
    cv->pt_bf->type = GetTyperef( (struct asym *)type, USE16 );
    cv->pt += sizeof( struct cv_typerec_bitfield );
    return;
}

#ifdef DEBUG_OUT
#define GetPos(x,y) (x->e.seginfo->current_loc + (y - x->e.seginfo->CodeBuffer ))
#endif

static void cv_write_array_type( struct dbgcv *cv, struct asym *sym, uint_16 elemtype, uint_8 Ofssize )
/*****************************************************************************************************/
{
    uint_8      *tmp;
    int         typelen;
    int         size;

    typelen = ( sym->total_size >= LF_NUMERIC ? sizeof( uint_32 ) : 0 );
    size = ( sizeof( struct cv_typerec_array ) + 2 + typelen + 1 + 3 ) & ~3;
    cv->pt = checkflush( cv->types, cv->pt, size, cv->param );
    cv->pt_ar->tr.size = size - sizeof(uint_16);
    cv->pt_ar->tr.leaf = LF_ARRAY;
    cv->pt_ar->elemtype = ( elemtype ? elemtype : GetTyperef( sym, Ofssize ) );
    cv->pt_ar->idxtype = cv_idx_type.uvalue; /* ok? */
    tmp = cv->pt + sizeof( struct cv_typerec_array );
    if ( typelen ) {
        cv->pt_ar->length = LF_ULONG;
        *(uint_32 *)tmp = sym->total_size;
        tmp += sizeof( uint_32 );
    } else {
        cv->pt_ar->length = sym->total_size;
    }
    *tmp++ = NULLC; /* the array type name is empty */
    PadBytes( tmp, cv->types->e.seginfo->CodeBuffer );
    cv->pt += size;
    cv->currtype++;
    return;
}

/* create a pointer type for procedure params and locals.
 * the symbol's mem_type is MT_PTR.
 */

static cv_typeref cv_write_ptr_type( struct dbgcv *cv, struct asym *sym  )
/************************************************************************/
{
    int size = ( sizeof( struct cv_typerec_pointer ) + sizeof( uint_32 ) );

    /* for untyped pointers & for function pointers don't create a type, just
     * return a void ptr.
     */
    if ( ( sym->ptr_memtype == MT_EMPTY && sym->target_type == NULL ) || sym->ptr_memtype == MT_PROC )
        return( GetTyperef( sym, sym->Ofssize ) );

    cv->pt = checkflush( cv->types, cv->pt, size, cv->param );
    cv->pt_ptr->tr.size = size - sizeof(uint_16);
    cv->pt_ptr->tr.leaf = LF_POINTER;
    if ( sym->Ofssize == USE16 ) {
        cv->pt_ptr->attribute = ( sym->isfar ? CV_TYPE_PTRTYPE_FAR : CV_TYPE_PTRTYPE_NEAR );
    } else {
        cv->pt_ptr->attribute = ( sym->isfar ? CV_TYPE_PTRTYPE_FAR32 : CV_TYPE_PTRTYPE_NEAR32 );
    }
    /* if indirection is > 1, define an untyped pointer - to be improved */
    if ( sym->is_ptr > 1 ) {
        cv->pt_ptr->type = GetTyperef( sym, sym->Ofssize );
    } else if ( sym->target_type ) {
        /* the target's typeref must have been set here */
        if ( sym->target_type->cvtyperef )
            cv->pt_ptr->type = sym->target_type->cvtyperef;
        else
            cv->pt_ptr->type = GetTyperef( sym, sym->Ofssize );
    } else { /* pointer to simple type */
        enum memtype tmpmt = sym->mem_type; /* the target type is tmp. copied to mem_type */
        sym->mem_type = sym->ptr_memtype;   /* thus GetTyperef() can be used */
        cv->pt_ptr->type = GetTyperef( sym, sym->Ofssize );
        sym->mem_type = tmpmt;
    }
    *(uint_32 *)( cv->pt + sizeof( struct cv_typerec_pointer ) ) = 0; /* variant */
    DebugMsg(( "%u cv_write_ptr_type(%Xh, typeref=%X ): name=%s [memt=%X ptr_memt=%X target_type=%s] reftype=%X\n",
              cv->level, GetPos(cv->types, cv->pt), cv->currtype, sym->name, sym->mem_type, sym->ptr_memtype, sym->target_type ? sym->target_type->name : "NULL", cv->pt_ptr->type ));
    cv->pt += size;
    return( cv->currtype++ );
}

/* structure for field enumeration callback function */
struct cv_counters {
    unsigned cnt;     /* number of fields */
    uint_32 size; /* size of field list */
    uint_32 ofs;  /* current start offset for member */
};

static void cv_write_type( struct dbgcv *cv, struct asym *sym );

/* type of field enumeration callback function */
typedef void (* cv_enum_func)( struct dsym *, struct asym *, struct dbgcv *, struct cv_counters * );

/* field enumeration callback, does:
 * - count number of members in a field list
 * - calculate the size LF_MEMBER records inside the field list
 * - create types ( array, structure ) if not defined yet
 */

static void cv_cntproc( struct dsym *type, struct asym *mbr, struct dbgcv *cv, struct cv_counters *cc )
/*****************************************************************************************************/
{
    int      numsize;
    uint_32  offset;

    cc->cnt++;
    offset = ( type->sym.typekind == TYPE_RECORD ? 0 : mbr->offset + cc->ofs );
    numsize = ( offset >= LF_NUMERIC ? sizeof( uint_32 ) : 0 );
    cc->size += ( sizeof( struct cv_typerec_member ) + numsize + mbr->name_size + 1 + 3 ) & ~3;

    /* field cv_typeref can only be queried from SYM_TYPE items! */

    if ( mbr->mem_type == MT_TYPE && mbr->type->cvtyperef == 0 ) {
        cv->level++;
        cv_write_type( cv, mbr->type );
        cv->level--;
    } else if ( mbr->mem_type == MT_BITS && mbr->cvtyperef == 0 ) {
        cv_write_bitfield( cv, type, mbr );
    }
    //DebugMsg(( "%u cv_cntproc(%Xh, %u): struct=%s MEMBER=%s [memt=%X type=%s]\n", cv->level, GetPos(cv->types, cv->pt), cc->cnt++, type->sym.name, mbr->name, mbr->mem_type, mbr->type ? mbr->type->name : "NULL" ));
    if ( mbr->isarray ) {
        /* temporarily (mis)use ext_idx1 member to store the type;
         * this field usually isn't used by struct fields */
        mbr->ext_idx1 = cv->currtype;
        cv_write_array_type( cv, mbr, 0, USE16 );
    }
}

/* field enumeration callback, does:
 * - create LF_MEMBER record
 */

static void cv_memberproc( struct dsym *type, struct asym *mbr, struct dbgcv *cv, struct cv_counters *cc )
/********************************************************************************************************/
{
    uint_32     offset;
    int         typelen;
    int         size;
    uint_8      *tmp;

    offset = ( type->sym.typekind == TYPE_RECORD ? 0 : mbr->offset + cc->ofs );
    typelen = ( offset >= LF_NUMERIC ? sizeof( uint_32 ) : 0 );
    size = ( sizeof( struct cv_typerec_member ) + typelen + 1 + mbr->name_size + 3 ) & ~3;
    cv->pt = checkflush( cv->types, cv->pt, size, cv->param );
    cv->pt_mbr->leaf = LF_MEMBER;
    if ( mbr->isarray ) {
        cv->pt_mbr->type = mbr->ext_idx1;
        mbr->ext_idx1 = 0; /* reset the temporarily used field */
    } else
        cv->pt_mbr->type = GetTyperef( mbr, USE16 );

    cv->pt_mbr->attribute.access = CV_ATTR_ACC_PUBLIC;
    cv->pt_mbr->attribute.mprop = CV_ATTR_MPR_VANILLA;
    cv->pt_mbr->attribute.pseudo = 0;
    cv->pt_mbr->attribute.noinherit = 0;
    cv->pt_mbr->attribute.noconstruct = 0;
    cv->pt_mbr->attribute.reserved = 0;
    tmp = cv->pt + sizeof( struct cv_typerec_member );
    if ( typelen == 0 ) {
        cv->pt_mbr->offset = offset;
    } else {
        cv->pt_mbr->offset = LF_ULONG;
        *(uint_32 *)tmp = offset;
        tmp += sizeof( uint_32 );
    }
    DebugMsg(( "%u cv_memberproc(%Xh, %u): struct=%s MEMBER=%s [memt=%X], typeref=%X\n", cv->level, GetPos(cv->types, cv->pt), cc->cnt++, type->sym.name, mbr->name, mbr->mem_type, cv->pt_mbr->type ));
    SetPrefixName( tmp, mbr->name, mbr->name_size );
    PadBytes( tmp, cv->types->e.seginfo->CodeBuffer );
    cv->pt += size;
    return;
}

/* field enumeration function.
 * The MS debug engine has problem with anonymous members (both members
 * and embedded structs).
 * If such a member is included, the containing struct can't be "opened".
 * The OW debugger and PellesC debugger have no such problems.
 * However, for Masm-compatibility, anonymous members are avoided and
 * anonymous struct members or embedded anonymous structs are "unfolded"
 * in this function.
 */
static void cv_enum_fields( struct dsym *sym, cv_enum_func enumfunc, struct dbgcv *cv, struct cv_counters *cc )
/*************************************************************************************************************/
{
    unsigned i;
    struct sfield  *curr;
    for ( curr = sym->e.structinfo->head, i = 0; curr; curr = curr->next ) {
        if ( curr->sym.name_size ) { /* has member a name? */
            enumfunc( sym, &curr->sym, cv, cc );
        } else if ( curr->sym.type ) { /* is member a type (struct, union, record)? */
            cc->ofs += curr->sym.offset;
            cv_enum_fields( (struct dsym *)curr->sym.type, enumfunc, cv, cc );
            cc->ofs -= curr->sym.offset;
        } else if ( sym->sym.typekind == TYPE_UNION ) {
            /* v2.11: include anonymous union members.
             * to make the MS debugger work with those members, they must have a name -
             * a temporary name is generated below which starts with "@@".
             */
            char *pold = curr->sym.name;
            char tmpname[8];
            curr->sym.name_size = sprintf( tmpname, "@@%u", ++i );
            curr->sym.name = tmpname;
            enumfunc( sym, &curr->sym, cv, cc );
            curr->sym.name = pold;
            curr->sym.name_size = 0;
        }
    }
    return;
}

/* write a LF_PROCEDURE & LF_ARGLIST type for procedures */

static void cv_write_type_procedure( struct dbgcv *cv, struct asym *sym, int cnt )
/********************************************************************************/
{
    int         size;
    cv_typeref  *ptr;
    struct dsym *param;

    size = sizeof( struct cv_typerec_procedure );
    cv->pt = checkflush( cv->types, cv->pt, size, cv->param );
    cv->pt_pr->tr.size = size - sizeof(uint_16);
    cv->pt_pr->tr.leaf = LF_PROCEDURE;
    cv->pt_pr->rvtype = cv_void.uvalue;
    cv->pt_pr->call = 0;
    cv->pt_pr->rsvd = 0;
    cv->pt_pr->numparams = cnt;
    cv->pt_pr->arglist = ++cv->currtype;
    cv->pt += size;
    size = sizeof( struct cv_typerec_arglist ) + cnt * sizeof( cv_typeref );
    cv->pt = checkflush( cv->types, cv->pt, size, cv->param );
    cv->pt_al->tr.size = size - sizeof(uint_16);
    cv->pt_al->tr.leaf = LF_ARGLIST;
    cv->pt_al->argcount = cnt;
    ptr = (cv_typeref *)(cv->pt + sizeof( struct cv_typerec_arglist ) );
    /* fixme: order might be wrong ( is "push" order ) */
    for ( param = ((struct dsym *)sym)->e.procinfo->paralist; param; param = param->nextparam ) {
        *ptr++ = param->sym.ext_idx1;
    }
    cv->pt += size;
    cv->currtype++;
    return;
}
/* write a type. Items are dword-aligned,
 *    cv: debug state
 *   sym: type to dump
 */

static void cv_write_type( struct dbgcv *cv, struct asym *sym )
/*************************************************************/
{
    struct dsym *type = (struct dsym *)sym;
    uint_8      *tmp;
    int         namesize;
    int         typelen;
    int         size;
    uint_16     property;
    struct cv_counters count;

    /* v2.10: handle typedefs. when the types are enumerated,
     * typedefs are ignored.
     */
    if ( sym->typekind == TYPE_TYPEDEF ) {
        //if ( sym->is_ptr ) {
        if ( sym->mem_type == MT_PTR ) {
#if GENPTRTYPE
            /* for untyped void pointers use ONE generic definition */
            if ( !sym->isfar ) {
                if ( cv->ptrtype[sym->Ofssize] ) {
                    sym->cv_typeref = cv->ptrtype[sym->Ofssize];
                    return;
                }
                cv->ptrtype[sym->Ofssize] = cv->currtype;
            }
#endif
#if 1
            if ( sym->ptr_memtype != MT_PROC && sym->target_type && sym->target_type->cvtyperef == 0 ) {
                DebugMsg(( "%u cv_write_type(%Xh): TYPEDEF=%s target type=%s [kind=%u memt=%X] not defined yet\n",
                          cv->level, GetPos(cv->types, cv->pt), sym->name, sym->target_type->name, sym->target_type->typekind, sym->target_type->mem_type ));
                //cv->level++;
                //sym->cv_typeref = GetTyperef( sym, sym->Ofssize ); /* to avoid circular references! */
                if ( cv->level == 0 ) /* avoid circles */
                    cv_write_type( cv, sym->target_type );
                //cv->level--;
            }
            sym->cvtyperef = cv_write_ptr_type( cv, sym );
            DebugMsg(( "%u cv_write_type(%Xh): TYPEDEF=%s typeref=%X\n", cv->level, GetPos(cv->types, cv->pt), sym->name, sym->cvtyperef ));
#else
            sym->cv_typeref = cv->currtype++;
            size = ( sizeof( struct cv_typerec_pointer ) + sizeof( uint_32 ) );
            cv->pt = checkflush( cv->types, cv->pt, size );
            cv->pt_ptr->tr.size = size - sizeof(uint_16);
            cv->pt_ptr->tr.leaf = LF_POINTER;
            if ( sym->Ofssize == USE16 ) {
                cv->pt_ptr->attribute = ( sym->isfar ? CV_TYPE_POINTER_FAR : CV_TYPE_POINTER_NEAR );
            } else {
                cv->pt_ptr->attribute = ( sym->isfar ? CV_TYPE_POINTER_FAR32 : CV_TYPE_POINTER_NEAR32 );
            }
            cv->pt_ptr->pptype = cv_pvoid.s;
            *(uint_32 *)( cv->pt + sizeof( struct cv_typerec_pointer ) ) = 0; /* variant */
            DebugMsg(( "%u cv_write_type(%Xh, ref=%X): POINTER, attr=%X\n", cv->level, GetPos(cv->types, cv->pt), cv->currtype-1, cv->pt_ptr->attribute ));
            cv->pt += size;
#endif
        }
        return;
    } else if ( sym->typekind == TYPE_NONE ) {
        DebugMsg(( "cv_write_type: %s has typekind=TYPE_NONE, ignored!\n", sym->name ));
        return;
    }

    typelen = ( sym->total_size >= LF_NUMERIC ? sizeof( uint_32 ) : 0 );

    property = ( cv->level ? CVTSP_ISNESTED : 0 );

    /* Count the member fields. If a member's type is unknown, create it! */
    count.cnt = 0;
    count.size = 0;
    count.ofs = 0;
    cv_enum_fields( type, cv_cntproc, cv, &count );

    /* WinDbg wants embedded structs to have a name - else it won't allow to "open" it. */
    namesize = ( sym->name_size ? sym->name_size : 9 );  /* 9 is sizeof("__unnamed") */

    sym->cvtyperef = cv->currtype++;
    switch ( type->sym.typekind ) {
    case TYPE_UNION:
        DebugMsg(( "%u cv_write_type(%Xh, ref=%X): UNION=%s\n", cv->level, GetPos(cv->types, cv->pt), sym->cvtyperef, sym->name ));
        size = ( sizeof( struct cv_typerec_union ) + typelen + 1 + namesize + 3 ) & ~3;
        cv->pt = checkflush( cv->types, cv->pt, size, cv->param );
        cv->pt_un->tr.size = size - sizeof(uint_16);
        cv->pt_un->tr.leaf = LF_UNION;
        cv->pt_un->count = count.cnt;
        cv->pt_un->field = cv->currtype++;
        cv->pt_un->property = property;
        tmp = (uint_8 *)&cv->pt_un->length;
        break;
    case TYPE_RECORD:
        property |= CVTSP_PACKED; /* is "packed" */
        /* no break */
    case TYPE_STRUCT:
        DebugMsg(( "%u cv_write_type(%Xh, ref=%X): STRUCT=%s\n", cv->level, GetPos(cv->types, cv->pt), sym->cvtyperef, sym->name ));
        size = ( sizeof( struct cv_typerec_structure ) + typelen + 1 + namesize + 3 ) & ~3;
        cv->pt = checkflush( cv->types, cv->pt, size, cv->param );
        cv->pt_st->tr.size = size - sizeof(uint_16);
        cv->pt_st->tr.leaf = LF_STRUCTURE;
        cv->pt_st->count = count.cnt;
        cv->pt_st->field = cv->currtype++;
        cv->pt_st->property = property;
        cv->pt_st->dList = 0;
        cv->pt_st->vshape = 0;
        tmp = (uint_8 *)&cv->pt_st->length;
        break;
    }
    if ( typelen ) {
        ((struct leaf32 *)tmp)->leaf = LF_ULONG;
        ((struct leaf32 *)tmp)->value32 = sym->total_size;
        tmp += sizeof( struct leaf32 );
    } else {
        *(uint_16 *)tmp = sym->total_size;
        tmp += sizeof( uint_16 );
    }
    SetPrefixName( tmp, sym->name_size ? sym->name : "__unnamed", namesize );

    PadBytes( tmp, cv->types->e.seginfo->CodeBuffer );
    cv->pt += size;

    /* write the fieldlist record */
    cv->pt = checkflush( cv->types, cv->pt, sizeof( struct cv_typerec_fieldlist ), cv->param );
    size = sizeof( struct cv_typerec_fieldlist) + count.size;
    cv->pt_fl->tr.size = size - sizeof(uint_16);
    cv->pt_fl->tr.leaf = LF_FIELDLIST;
    DebugMsg(( "%u cv_write_type(%Xh, ref=%X): FIELDLIST, size=%u\n", cv->level, GetPos(cv->types, cv->pt), cv->currtype-1, size ));
    cv->pt += sizeof( struct cv_typerec_fieldlist );

    /* add the struct's members to the fieldlist. */
    count.ofs = 0;
#ifdef DEBUG_OUT
    count.cnt = 0;
#endif
    cv_enum_fields( type, cv_memberproc, cv, &count );
    return;
}

/* get register values for S_REGISTER */

static uint_16 cv_get_register( struct asym *sym )
/************************************************/
{
    uint_16 regno;
    uint_16 rc = 0;
    unsigned flags;
    int i;

    for ( i = 0; i < 2; i++ ) {
        if ( sym->regist[i] ) {
            flags = GetValueSp( sym->regist[i] );
            regno = 1 + GetRegNo( sym->regist[i] );
            if ( flags & OP_R16 )
                regno += 8;
            else if ( flags & OP_R32 )
                regno += 16;
            else if ( flags & OP_SR )
                regno += 24;
            rc |= regno << ( i * 8 );
        }
    }
    return( rc );
}

#if AMD64_SUPPORT

/*
 *  convert register number
 *        0  1  2  3  4  5  6  7
 * -----------------------------
 * from: ax cx dx bx sp bp si di
 *   to: ax bx cx dx si di bp sp
 */
static const uint_8 reg64[] = { 0, 2, 3, 1, 7, 6, 4, 5 };

static uint_16 cv_get_x64_regno( uint_16 regno )
/**********************************************/
{
    if ( regno >= T_RAX && regno <= T_RDI )
        return( reg64[ regno - T_RAX ] + CV_REG_AMD64_START64 );
    if ( regno >= T_R8 && regno <= T_R15 )
        return( regno - T_R8 + CV_REG_AMD64_START64 + 8 );
    /* it's a 32-bit register r8d-r15d */
    return( regno - T_R8D + CV_REG_AMD64_START32 );

}
#endif

/* write a symbol
 *    cv: debug state
 *   sym: symbol to write
 * the symbol has either state SYM_INTERNAL or SYM_TYPE.
 */

static void cv_write_symbol( struct dbgcv *cv, struct asym *sym )
/***************************************************************/
{
    int        len;
    unsigned   ofs;
    enum fixup_types rlctype;
    uint_8     Ofssize;
    struct fixup *fixup;
    struct dsym *proc;
    struct dsym *lcl;
    int        i;
    int        cnt[2];
    struct     dsym *locals[2];

    Ofssize = GetSymOfssize( sym );
    len = GetCVStructLen( sym, Ofssize );
    cv->ps = checkflush( cv->symbols, cv->ps, 1 + sym->name_size + len, cv->param );

    if ( sym->state == SYM_TYPE ) {
        /* Masm does only generate an UDT for typedefs
         * if the underlying type is "used" somewhere.
         * example:
         * LPSTR typedef ptr BYTE
         * will only generate an S_UDT for LPSTR if either
         * "LPSTR" or "ptr BYTE" is used in the source.
         */
        cv->ps_udt->sr.size = sizeof( struct cv_symrec_udt ) - sizeof(uint_16) + 1 + sym->name_size;
        cv->ps_udt->sr.type = S_UDT;
        /* v2.10: pointer typedefs will now have a cv_typeref */
        //if ( sym->typekind != TYPE_TYPEDEF ) {
        if ( sym->cvtyperef ) {
            cv->ps_udt->type = sym->cvtyperef;
        } else {
            cv->ps_udt->type = GetTyperef( sym, Ofssize );
        }

        /* Some typedefs won't get a valid type (<name> TYPEDEF PROTO ...).
         * In such cases just skip the type!
         */
        if ( cv->ps_udt->type == 0 )
            return;

        DebugMsg(( "cv_write_symbol(%X): TYPE=%s typeref=%Xh\n", GetPos(cv->symbols, cv->ps), sym->name, cv->ps_udt->type ));
        cv->ps += len;
        SetPrefixName( cv->ps, sym->name, sym->name_size );
        return;
    }

    /* rest is SYM_INTERNAL */
    /* there are 3 types of INTERNAL symbols:
     * - numeric constants ( equates, memtype MT_EMPTY )
     * - code labels, memtype == MT_NEAR | MT_FAR
     *   - procs
     *   - simple labels
     * - data labels, memtype != MT_NEAR | MT_FAR
     */

    if ( sym->isproc && Options.debug_ext >= CVEX_REDUCED ) { /* v2.10: no locals for -Zi0 */

        proc = (struct dsym *)sym;

        /* for PROCs, scan parameters and locals and create their types. */

        /* scan local symbols */
        locals[0] = proc->e.procinfo->paralist;
        locals[1] = proc->e.procinfo->locallist;
        for ( i = 0; i < 2; i++ ) {
            cnt[i] = 0;
            for ( lcl = locals[i]; lcl; lcl = lcl->nextparam ) {
                cv_typeref typeref;
                cnt[i]++;
                typeref = ( lcl->sym.mem_type == MT_PTR ? cv_write_ptr_type( cv, &lcl->sym ) : GetTyperef( &lcl->sym, Ofssize ) );
                if ( lcl->sym.isarray ) {
                    cv_write_array_type( cv, &lcl->sym, typeref, Ofssize );
                    typeref = cv->currtype - 1;
                }
                lcl->sym.ext_idx1 = typeref;
            }
        }

        DebugMsg(( "cv_write_symbol(%X): PROC=%s\n", GetPos(cv->symbols, cv->ps), sym->name ));
        if ( Ofssize == USE16 ) {
            cv->ps_p16->sr.size = sizeof( struct cv_symrec_lproc16 ) - sizeof(uint_16) + 1 + sym->name_size;
            cv->ps_p16->sr.type = (sym->ispublic ? S_GPROC16 : S_LPROC16);
            cv->ps_p16->pParent = 0;  /* filled by CVPACK */
            cv->ps_p16->pEnd = 0;     /* filled by CVPACK */
            cv->ps_p16->pNext = 0;    /* filled by CVPACK */
            cv->ps_p16->proc_length = sym->total_size;
            cv->ps_p16->debug_start = ((struct dsym *)sym)->e.procinfo->size_prolog;
            cv->ps_p16->debug_end = sym->total_size;
            cv->ps_p16->offset = 0;
            cv->ps_p16->segment = 0;
            cv->ps_p16->proctype = cv->currtype; /* typeref LF_PROCEDURE */
            cv->ps_p16->flags = ( sym->mem_type == MT_FAR ? CV_PROCF_FAR : 0 );
            rlctype = FIX_PTR16;
            ofs = offsetof( struct cv_symrec_lproc16, offset );
        } else {
            cv->ps_p32->sr.size = sizeof( struct cv_symrec_lproc32 ) - sizeof(uint_16) + 1 + sym->name_size;
            cv->ps_p32->sr.type = (sym->ispublic ? S_GPROC32 : S_LPROC32 );
            cv->ps_p32->pParent = 0; /* filled by CVPACK */
            cv->ps_p32->pEnd = 0;    /* filled by CVPACK */
            cv->ps_p32->pNext = 0;   /* filled by CVPACK */
            cv->ps_p32->proc_length = sym->total_size;
            cv->ps_p32->debug_start = ((struct dsym *)sym)->e.procinfo->size_prolog;
            cv->ps_p32->debug_end = sym->total_size;
            cv->ps_p32->offset = 0;
            cv->ps_p32->segment = 0;
            cv->ps_p32->proctype = cv->currtype; /* typeref LF_PROCEDURE */
#if STACKBASESUPP
            cv->ps_p32->flags = ( ( sym->mem_type == MT_FAR ? CV_PROCF_FAR : 0 ) | ( proc->e.procinfo->fpo ? CV_PROCF_FPO : 0 ) );
#else
            cv->ps_p32->flags = ( sym->mem_type == MT_FAR ? CV_PROCF_FAR : 0 );
#endif
            rlctype = FIX_PTR32;
            ofs = offsetof( struct cv_symrec_lproc32, offset );
        }
        cv_write_type_procedure( cv, sym, cnt[0] );

    } else if ( sym->mem_type == MT_NEAR || sym->mem_type == MT_FAR ) {

        if ( Ofssize == USE16 ) {
            cv->ps_l16->sr.size = sizeof( struct cv_symrec_label16 ) - sizeof(uint_16) + 1 + sym->name_size;
            cv->ps_l16->sr.type = S_LABEL16;
            cv->ps_l16->offset = 0;
            cv->ps_l16->segment = 0;
            cv->ps_l16->flags = ( sym->mem_type == MT_FAR ? CV_PROCF_FAR : 0 );
            rlctype = FIX_PTR16;
            ofs = offsetof( struct cv_symrec_label16, offset );
            DebugMsg(( "cv_write_symbol(%X): LABEL16=%s\n", GetPos(cv->symbols,cv->ps), sym->name ));
        } else {
            cv->ps_l32->sr.size = sizeof( struct cv_symrec_label32 ) - sizeof(uint_16) + 1 + sym->name_size;
            cv->ps_l32->sr.type = S_LABEL32;
            cv->ps_l32->offset = 0;
            cv->ps_l32->segment = 0;
            cv->ps_l32->flags = ( sym->mem_type == MT_FAR ? CV_PROCF_FAR : 0 );
            rlctype = FIX_PTR32;
            ofs = offsetof( struct cv_symrec_label32, offset );
            DebugMsg(( "cv_write_symbol(%X): LABEL32=%s\n", GetPos(cv->symbols,cv->ps), sym->name ));
        }
#if EQUATESYMS
    } else if ( sym->isequate ) {
        cv->ps_con->sr.size = len - sizeof(uint_16) + 1 + sym->name_size;
        cv->ps_con->sr.type = S_CONSTANT;
        cv->ps_con->type = cv_abs_type.uvalue;
        if ( sym->value >= LF_NUMERIC ) {
            uint_8 *tmp;
            cv->ps_con->value = LF_ULONG;
            tmp = (uint_8 *)&cv->ps_con->value;
            *(uint_32 *)tmp = sym->value;
        } else {
            cv->ps_con->value = sym->value;
        }
        cv->ps += len;
        SetPrefixName( cv->ps, sym->name, sym->name_size );
        return;
#endif
    } else {
        /* v2.10: set S_GDATA[16|32] if symbol is public */
        cv_typeref typeref;

        if ( sym->isarray ) {
            typeref = cv->currtype;
            cv_write_array_type( cv, sym, 0, Ofssize );
        } else
            typeref = GetTyperef( sym, Ofssize );

        if ( Ofssize == USE16 ) {
            cv->ps_d16->sr.size = sizeof( struct cv_symrec_ldata16 ) - sizeof(uint_16) + 1 + sym->name_size;
            cv->ps_d16->sr.type = (sym->ispublic ? S_GDATA16 : S_LDATA16 );
            cv->ps_d16->offset = 0;
            cv->ps_d16->segment = 0;
            cv->ps_d16->type = typeref;
            rlctype = FIX_PTR16;
            ofs = offsetof( struct cv_symrec_ldata16, offset );
            DebugMsg(( "cv_write_symbol(%X): INTERN16=%s typeref=%Xh\n", GetPos(cv->symbols,cv->ps), sym->name, cv->ps_d16->type ));
        } else {
            cv->ps_d32->sr.size = sizeof( struct cv_symrec_ldata32 ) - sizeof(uint_16) + 1 + sym->name_size;
#if CVOSUPP
            if ( ( ModuleInfo.cv_opt & CVO_STATICTLS ) && ((struct dsym *)sym->segment)->e.seginfo->clsym &&
                strcmp( ((struct dsym *)sym->segment)->e.seginfo->clsym->name, "TLS" ) == 0 )
                cv->ps_d32->sr.type = (sym->ispublic ? S_GTHREAD32 : S_LTHREAD32 );
            else
#endif
            cv->ps_d32->sr.type = (sym->ispublic ? S_GDATA32 : S_LDATA32 );
            cv->ps_d32->offset = 0;
            cv->ps_d32->segment = 0;
            cv->ps_d32->type = typeref;
            rlctype = FIX_PTR32;
            ofs = offsetof( struct cv_symrec_ldata32, offset );
            DebugMsg(( "cv_write_symbol(%X): INTERN32=%s typeref=%Xh\n", GetPos(cv->symbols,cv->ps), sym->name, cv->ps_d16->type ));
        }
    }
    cv->ps += ofs;
    cv->symbols->e.seginfo->current_loc = cv->symbols->e.seginfo->start_loc + ( cv->ps - cv->symbols->e.seginfo->CodeBuffer );
#if COFF_SUPPORT
    /* v2.10: also handle FIX_PTR16 for COFF */
    //if ( rlctype == FIX_PTR32 && Options.output_format == OFORMAT_COFF ) {
    if ( Options.output_format == OFORMAT_COFF ) {
        /* COFF has no "far" fixups. Instead Masm creates a
         * section-relative fixup + a section fixup.
         */
        fixup = CreateFixup( sym, FIX_OFF32_SECREL, OPTJ_NONE );
        fixup->locofs = cv->symbols->e.seginfo->current_loc;
        store_fixup( fixup, cv->symbols, (int_32 *)cv->ps );
        fixup = CreateFixup( sym, FIX_SEG, OPTJ_NONE );
        //fixup->locofs += sizeof( int_32 );
        fixup->locofs = cv->symbols->e.seginfo->current_loc + ( rlctype == FIX_PTR32 ? sizeof( int_32 ) : sizeof ( int_16 ) );
        store_fixup( fixup, cv->symbols, (int_32 *)cv->ps );
    } else {
#endif
        fixup = CreateFixup( sym, rlctype, OPTJ_NONE );
        fixup->locofs = cv->symbols->e.seginfo->current_loc;
        /* todo: for OMF, delay fixup store until checkflush has been called! */
        store_fixup( fixup, cv->symbols, (int_32 *)cv->ps );
#if COFF_SUPPORT
    }
#endif
    cv->ps += len - ofs;

    SetPrefixName( cv->ps, sym->name, sym->name_size );

    /* for PROCs, scan parameters and locals.
     * to mark the block's end, write an ENDBLK item.
     */
    if ( sym->isproc && Options.debug_ext >= CVEX_REDUCED ) { /* v2.10: no locals for -Zi0 */

        /* scan local symbols again */
        for ( i = 0; i < 2 ; i++ ) {
            for ( lcl = locals[i]; lcl; lcl = lcl->nextparam ) {

                /* FASTCALL register argument? */
                if ( lcl->sym.state == SYM_TMACRO ) {
                    len = sizeof( struct cv_symrec_register );
                    cv->ps = checkflush( cv->symbols, cv->ps, 1 + lcl->sym.name_size + len, cv->param );
                    cv->ps_reg->sr.size = sizeof( struct cv_symrec_register ) - sizeof(uint_16) + 1 + lcl->sym.name_size;
                    cv->ps_reg->sr.type = S_REGISTER;
                    cv->ps_reg->type = lcl->sym.ext_idx1;
                    cv->ps_reg->registr = cv_get_register( &lcl->sym );
                } else if ( Ofssize == USE16 ) {
                    len = sizeof( struct cv_symrec_bprel16 );
                    cv->ps = checkflush( cv->symbols, cv->ps, 1 + lcl->sym.name_size + len, cv->param );
                    cv->ps_br16->sr.size = sizeof( struct cv_symrec_bprel16 ) - sizeof(uint_16) + 1 + lcl->sym.name_size;
                    cv->ps_br16->sr.type = S_BPREL16;
                    cv->ps_br16->offset = lcl->sym.offset;
                    cv->ps_br16->type = lcl->sym.ext_idx1;
                    DebugMsg(( "cv_write_symbol(%X): proc=%s, S_BPREL16, var=%s [memt=%X typeref=%X]\n",
                              GetPos(cv->symbols,cv->ps), proc->sym.name, lcl->sym.name, lcl->sym.mem_type, cv->ps_br16->type ));
                } else {
#if STACKBASESUPP || AMD64_SUPPORT
                    /* v2.11: use S_REGREL if 64-bit or frame reg != [E|BP */
                    if (
#if AMD64_SUPPORT
                        Ofssize == USE64
#if STACKBASESUPP
                        || ( GetRegNo( proc->e.procinfo->basereg ) != 5 )
#endif
#else
                        GetRegNo( proc->e.procinfo->basereg ) != 5
#endif
                       ) {

                        len = sizeof( struct cv_symrec_regrel32 );
                        cv->ps = checkflush( cv->symbols, cv->ps, 1 + lcl->sym.name_size + len, cv->param );
                        cv->ps_rr32->sr.size = sizeof( struct cv_symrec_regrel32 ) - sizeof(uint_16) + 1 + lcl->sym.name_size;
                        cv->ps_rr32->sr.type = S_REGREL32;
                        cv->ps_rr32->offset = lcl->sym.offset ;
                        cv->ps_rr32->type = lcl->sym.ext_idx1;
#if AMD64_SUPPORT
                        //if W64F_HABRAN recalculate parameters positions
                        if (ModuleInfo.win64_flags & W64F_SMART){
                          if (lcl->sym.isparam){
                            int cnt = proc->e.procinfo->pushed_reg;
                            cnt = cnt * 8;
                            cnt += lcl->sym.offset + proc->e.procinfo->localsize + proc->e.procinfo->xmmsize; //pointing to RSP
                            if (proc->sym.langtype == LANG_VECTORCALL)
                            cnt += proc->e.procinfo->vsize;     //pointing abowe RSP to the shadow space off RCX RDX R8 R9
                            //else 
                              cnt -= 8;
                              if ((cnt & 7) != 0) cnt = (cnt + 7)&(-8);
                            cv->ps_rr32->offset = cnt;
                          }
                        }
                        /* x64 register numbers are different */
                        if ( SpecialTable[ proc->e.procinfo->basereg ].cpu == P_64 )
                            cv->ps_rr32->reg = cv_get_x64_regno( proc->e.procinfo->basereg );
                        else
#endif
                            cv->ps_rr32->reg = GetRegNo( proc->e.procinfo->basereg ) + CV_REG_START32;
                        DebugMsg(( "cv_write_symbol(%X): proc=%s, S_REGREL32, var=%s [memt=%X typeref=%X]\n",
                                  GetPos(cv->symbols,cv->ps), proc->sym.name, lcl->sym.name, lcl->sym.mem_type, cv->ps_rr32->type ));
                    } else {
#endif
                        len = sizeof( struct cv_symrec_bprel32 );
                        cv->ps = checkflush( cv->symbols, cv->ps, 1 + lcl->sym.name_size + len, cv->param );
                        cv->ps_br32->sr.size = sizeof( struct cv_symrec_bprel32 ) - sizeof(uint_16) + 1 + lcl->sym.name_size;
                        cv->ps_br32->sr.type = S_BPREL32;
                        cv->ps_br32->offset = lcl->sym.offset;
                        cv->ps_br32->type = lcl->sym.ext_idx1;
                        DebugMsg(( "cv_write_symbol(%X): proc=%s, S_BPREL32, var=%s [memt=%X typeref=%X]\n",
                                  GetPos(cv->symbols,cv->ps), proc->sym.name, lcl->sym.name, lcl->sym.mem_type, cv->ps_br32->type ));
#if STACKBASESUPP || AMD64_SUPPORT
                    }
#endif
                }
                lcl->sym.ext_idx1 = 0; /* to be safe, clear the temp. used field */
                cv->ps += len;
                SetPrefixName( cv->ps, lcl->sym.name, lcl->sym.name_size );
            }
        }

        cv->ps = checkflush( cv->symbols, cv->ps, sizeof( struct cv_symrec_endblk ), cv->param );
        cv->ps_eb->sr.size = sizeof( struct cv_symrec_endblk ) - sizeof(uint_16);
        cv->ps_eb->sr.type = S_ENDBLK;
        cv->ps += sizeof( struct cv_symrec_endblk );
    }
    return;
}

/* option -Zi: write debug symbols and types
 * - symbols: segment $$SYMBOLS (OMF) or .debug$S (COFF)
 * - types:   segment $$TYPES (OMF) or .debug$T (COFF)
 * field Options.debug_symbols contains the format version
 * which is to be generated (CV4_, CV5_ or CV8_SIGNATURE)
 */

void cv_write_debug_tables( struct dsym *symbols, struct dsym *types, void *pv )
/******************************************************************************/
{
    struct asym *sym;
    int        i;
    int        len;
    char       *objname;
    struct dbgcv cv;

    DebugMsg(( "cv_write_debug_tables enter\n"));

    /**/myassert( types && symbols && types->sym.state == SYM_SEG &&  symbols->sym.state == SYM_SEG );

    cv.ps = symbols->e.seginfo->CodeBuffer;
    cv.symbols = symbols;
    cv.pt = types->e.seginfo->CodeBuffer;
    cv.types   = types;
    cv.currtype = 0x1000; /* user-defined types start at 0x1000 */
    cv.level   = 0;
    cv.param = pv;
#if GENPTRTYPE
    cv.ptrtype[0] = 0;
    cv.ptrtype[1] = 0;
    cv.ptrtype[2] = 0;
#endif
    /* init types */
    //memset( pt, 0, 1024 ); /* it's ensured to have at least size 1024 */
    *(uint_32 *)cv.pt = Options.debug_symbols; /* "signature" */
    cv.pt += sizeof( uint_32 );

    /* init symbols */
    //memset( ps, 0, 1024 ); /* it's ensured to has at least size 1024 */
    *(uint_32 *)cv.ps = Options.debug_symbols; /* "signature" */
    cv.ps += sizeof(uint_32);

    /* 1. symbol record: object name */
    objname = CurrFName[OBJ];
    for ( i = strlen( objname ); i; i-- )
        if ( *(objname+i-1) == '/' || *(objname+i-1) == '\\' )
            break;
    objname += i;
    len = strlen( objname );
    cv.ps_on->sr.size = sizeof( struct cv_symrec_objname ) - sizeof(uint_16) + 1 + len;
    cv.ps_on->sr.type = S_OBJNAME;
    cv.ps_on->Signature = 1;
    DebugMsg(( "cv_write_debug_tables: at %X objname=%s\n", GetPos(cv.symbols,cv.ps), objname ));
    cv.ps += sizeof( struct cv_symrec_objname );
    SetPrefixName( cv.ps, objname, len );

    /* 2. symbol record: compiler */
    len = strlen( szCVCompiler );
    cv.ps_cp->sr.size = sizeof( struct cv_symrec_compile ) - sizeof(uint_16) + 1 + len;
    cv.ps_cp->sr.type = S_COMPILE;
#if AMD64_SUPPORT
    /* v2.11: use a valid 64-bit value */
    cv.ps_cp->machine = ( ModuleInfo.defOfssize == USE64 ? CV_MACH_AMD64 : ( ModuleInfo.curr_cpu & P_CPU_MASK ) >> 4 );
#else
    cv.ps_cp->machine = ( ModuleInfo.curr_cpu & P_CPU_MASK ) >> 4;
#endif
    /* 0 isnt possible, 1 is 8086 and 80186 */
    if ( cv.ps_cp->machine == 0 )
        cv.ps_cp->machine = CV_MACH_8086;
    cv.ps_cp->Language = CV_LANG_MASM;
    cv.ps_cp->flags = 0;
    if ( ModuleInfo.model ) {
        if ( ModuleInfo.model == MODEL_HUGE )
            cv.ps_cp->AmbientData = CV_AMB_HUGE;
        else
            cv.ps_cp->AmbientData = ( SIZE_DATAPTR & ( 1 << ModuleInfo.model ) ? CV_AMB_FAR : CV_AMB_NEAR );
        cv.ps_cp->AmbientCode = ( SIZE_CODEPTR & ( 1 << ModuleInfo.model ) ? CV_AMB_FAR : CV_AMB_NEAR );
    }
    DebugMsg(( "cv_write_debug_tables: at %X compiler=%s\n", GetPos(cv.symbols,cv.ps), szCVCompiler ));
    cv.ps += sizeof( struct cv_symrec_compile );
    SetPrefixName( cv.ps, szCVCompiler, len );

    /* CurrSeg must be set for store_fixup(); v2.12: obsolete */
    //CurrSeg = symbols;

    /* scan symbol table for types */

    sym = NULL;
    while ( sym = SymEnum( sym, &i ) ) {
        if ( sym->state == SYM_TYPE && sym->typekind != TYPE_TYPEDEF && sym->cvtyperef == 0 ) {
            /**/myassert( cv.currtype >= 0x1000 ); /* check for overflow */
            cv_write_type( &cv, sym );
        }
    }

    /* scan symbol table for SYM_TYPE, SYM_INTERNAL */

    sym = NULL;
    while ( sym = SymEnum( sym, &i ) ) {
        switch ( sym->state ) {
        case SYM_TYPE: /* may create an S_UDT entry in the symbols table */
            if ( Options.debug_ext < CVEX_NORMAL ) /* v2.10: no UDTs for -Zi0 and -Zi1 */
                break;
        case SYM_INTERNAL:
            if (
#if EQUATESYMS
                /* emit constants if -Zi3 */
                ( Options.debug_ext < CVEX_MAX ? sym->isequate : sym->variable )
#else
                sym->isequate
#endif
                || sym->predefined ) { /* EQUates? */
                break;
            }
            /**/myassert( cv.currtype >= 0x1000 ); /* check for overflow */
            cv_write_symbol( &cv, sym );
            break;
        }
    }

    /* final flush for both types and symbols.
     * use 'fictional' size of MAX_LINE_LEN * 2!
     */
    checkflush( cv.types, cv.pt, SIZE_CV_SEGBUF, cv.param );
    checkflush( cv.symbols, cv.ps, SIZE_CV_SEGBUF, cv.param );
    types->sym.max_offset = types->e.seginfo->current_loc;
    types->e.seginfo->start_loc = 0; /* required for COFF */
    symbols->sym.max_offset = symbols->e.seginfo->current_loc;
    symbols->e.seginfo->start_loc = 0; /* required for COFF */

    //CurrSeg = NULL;
    //Modend = TRUE;

    DebugMsg(( "cv_write_debug_tables exit, max type=%Xh\n", cv.currtype - 1 ));
    return;
}
