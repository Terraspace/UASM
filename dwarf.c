/* ELF64 DWARF 4 writer. Debug addresses use ELF relocations, never file offsets.
 * Compilation units, lines, types, variables and parameter location lists. */
#include <ctype.h>
#include <time.h>
#ifdef __UNIX__
#include <unistd.h>
#define _getcwd getcwd
#define _MAX_PATH 260
#else
#include <direct.h>
#endif
#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "segment.h"
#include "input.h"
#include "fixup.h"
#include "dwarf.h"
#include "proc.h"
#include "expreval.h"
#if ELF_SUPPORT && AMD64_SUPPORT
struct dwrow { struct dwrow *next; struct dsym *seg; unsigned file; uint_32 line, offset; };
struct dwrel { struct dwrel *next; struct dsym *target; unsigned offset, width; bool pcrel; };
struct dwbuf { uint_8 *p; unsigned size, cap; struct dwrel *rel; struct dsym *seg; };
static struct dwrow *rows, **tail;
enum { DW_SECTIONS = 7 };
static struct dsym *sections[DW_SECTIONS];
struct dwframe { struct dwframe *next; struct dsym *proc; unsigned body; bool automatic; };
struct dwepi { struct dwepi *next; struct dsym *proc; unsigned first,last; };
static struct dwframe *frames;
static struct dwepi *epis, **epi_tail;
void dwarf_body(struct dsym *proc)
{
    struct dwframe *f;
    if(!write_to_file || Options.output_format!=OFORMAT_ELF || ModuleInfo.defOfssize!=USE64 || !Options.debug_symbols) return;
    f=MemAlloc(sizeof(*f));f->proc=proc;f->body=GetCurrOffset();
    f->automatic=ModuleInfo.prologuemode==PEM_DEFAULT && proc->sym.langtype==LANG_SYSVCALL;
    f->next=frames;frames=f;
}
void dwarf_epilogue(struct dsym *proc,unsigned first,unsigned last)
{
    struct dwepi *e;
    if(!write_to_file || Options.output_format!=OFORMAT_ELF || ModuleInfo.defOfssize!=USE64 || !Options.debug_symbols) return;
    e=MemAlloc(sizeof(*e));e->proc=proc;e->first=first;e->last=last;e->next=NULL;*epi_tail=e;epi_tail=&e->next;
}
static void clear_cfi(void);
static void clear_frames(void)
{
    clear_cfi();
    while(frames) {struct dwframe *f=frames->next;MemFree(frames);frames=f;}
    while(epis) {struct dwepi *e=epis->next;MemFree(epis);epis=e;}
    epi_tail=&epis;
}
void dwarf_init(void)
{
    struct dwrow *p;
    clear_frames();
    while (rows) { p = rows->next; MemFree(rows); rows = p; }
    tail = &rows;
    memset(sections, 0, sizeof(sections));
}
void dwarf_line(unsigned file, uint_32 line)
{
    struct dwrow *p;
    if (!write_to_file || !line || !CurrSeg || CurrSeg->e.seginfo->segtype != SEGTYPE_CODE) return;
    p = MemAlloc(sizeof(*p));
    p->next = NULL; p->seg = CurrSeg; p->file = file; p->line = line; p->offset = GetCurrOffset();
    *tail = p; tail = &p->next;
}
bool dwarf_section(const struct dsym *seg)
{
    unsigned i;
    for (i = 0; i < DW_SECTIONS; i++) if (sections[i] == seg) return TRUE;
    return FALSE;
}
bool dwarf_eh_frame(const struct dsym *seg)
{
    return sections[6] && sections[6] == seg;
}
static void bytes(struct dwbuf *b, const void *p, unsigned n)
{
    if (b->size + n > b->cap) {
        uint_8 *q;
        b->cap = (b->size + n) * 2 + 256;
        q = MemAlloc(b->cap);
        if (b->size) memcpy(q, b->p, b->size);
        if (b->p) MemFree(b->p);
        b->p = q;
    }
    memcpy(b->p + b->size, p, n); b->size += n;
}
static void num(struct dwbuf *b, uint_64 v, unsigned n)
{
    uint_8 p[8]; unsigned i;
    for (i = 0; i < n; i++) { p[i] = (uint_8)v; v >>= 8; }
    bytes(b, p, n);
}
static void uleb(struct dwbuf *b, unsigned v)
{
    do { unsigned c = v & 127; v >>= 7; num(b, c | (v ? 128 : 0), 1); } while (v);
}
static void sleb(struct dwbuf *b, int v)
{
    bool more;
    do { unsigned c = v & 127; v >>= 7; more = !((v == 0 && !(c & 64)) || (v == -1 && (c & 64))); num(b, c | (more ? 128 : 0), 1); } while (more);
}
static void str(struct dwbuf *b, const char *s) { bytes(b, s, (unsigned)strlen(s) + 1); }
static void patch32(struct dwbuf *b, unsigned at, unsigned v)
{
    unsigned i; for (i = 0; i < 4; i++, v >>= 8) b->p[at+i] = (uint_8)v;
}
static void address(struct dwbuf *b, struct dsym *seg, unsigned offset, unsigned width)
{
    struct dwrel *r = MemAlloc(sizeof(*r));
    r->pcrel = FALSE; r->target = seg; r->offset = b->size; r->width = width; r->next = b->rel; b->rel = r;
    num(b, offset, width);
}
static void publish(struct dwbuf *b)
{
    struct dwrel *r, *next;
    /* Linkers consume .eh_frame relocations while walking records in order. */
    if (dwarf_eh_frame(b->seg)) {
        r = b->rel; b->rel = NULL;
        while (r) {next = r->next; r->next = b->rel; b->rel = r; r = next;}
    }
    b->seg->e.seginfo->CodeBuffer = LclAlloc(b->size);
    memcpy(b->seg->e.seginfo->CodeBuffer, b->p, b->size);
    b->seg->sym.max_offset = b->size;
    b->seg->e.seginfo->bytes_written = b->size;
    for (r = b->rel; r; r = next) {
        struct fixup *f;
        b->seg->e.seginfo->current_loc = r->offset;
        f = CreateFixup(&r->target->sym, r->pcrel ? FIX_RELOFF32 : (r->width == 8 ? FIX_OFF64 : FIX_OFF32), OPTJ_NONE);
        f->locofs = r->offset; f->addbytes = 0;
        store_fixup(f, b->seg, (int_32 *)(b->seg->e.seginfo->CodeBuffer + r->offset));
        next = r->next; MemFree(r);
    }
    b->seg->e.seginfo->current_loc = b->size;
    MemFree(b->p);
}
/* Type graph references are CU-relative and patched after recursive types
 * have been emitted. Never reuse CodeView indices or ELF symbol indices. */
enum dwkind { DT_VOID, DT_BASE, DT_POINTER, DT_STRUCT, DT_UNION, DT_ALIAS, DT_ARRAY, DT_RECORD };
struct dwtype { struct dwtype *next, *target; struct asym *sym; enum dwkind kind; unsigned size, encoding, count, die; const char *name; };
struct dwref { struct dwref *next; struct dwtype *type; unsigned offset; };
static struct dwtype *types, **type_tail;
static struct dwref *refs;
static struct dwtype *type_sym(struct asym *, bool);
static struct dwtype *type_new(enum dwkind kind, struct asym *sym, struct dwtype *target, unsigned size, unsigned encoding, unsigned count, const char *name)
{
    struct dwtype *t;
    for (t=types;t;t=t->next)
        if(t->kind==kind && t->sym==sym && t->target==target && t->size==size && t->encoding==encoding && t->count==count) return t;
    t=MemAlloc(sizeof(*t)); memset(t,0,sizeof(*t)); t->kind=kind;t->sym=sym;t->target=target;t->size=size;t->encoding=encoding;t->count=count;t->name=name;
    *type_tail=t;type_tail=&t->next;return t;
}
static struct dwtype *type_mem(enum memtype mt, struct asym *target)
{
    unsigned size;
    if(mt==MT_TYPE && target) return type_sym(target,FALSE);
    if(mt==MT_EMPTY || (mt & MT_SPECIAL)) return type_new(DT_VOID,NULL,NULL,0,0,0,"void");
    size=SizeFromMemtype(mt,USE64,NULL);
    if(mt==MT_YMMWORD || mt==MT_ZMMWORD)
        return type_new(DT_ARRAY,NULL,type_mem(MT_BYTE,NULL),size,0,size,NULL);
    return type_new(DT_BASE,NULL,NULL,size,(mt & MT_FLOAT)?4:(mt & MT_SIGNED)?5:7,0,
        mt==MT_REAL4?"REAL4":mt==MT_REAL8?"REAL8":mt==MT_REAL10?"REAL10":
        mt==MT_BYTE?"BYTE":mt==MT_SBYTE?"SBYTE":mt==MT_WORD?"WORD":mt==MT_SWORD?"SWORD":
        mt==MT_DWORD?"DWORD":mt==MT_SDWORD?"SDWORD":mt==MT_QWORD?"QWORD":mt==MT_SQWORD?"SQWORD":
        mt==MT_OWORD?"OWORD":mt==MT_REAL2?"REAL2":mt==MT_REAL16?"REAL16":"integer");
}
static struct dwtype *type_sym(struct asym *s, bool array)
{
    struct dwtype *t; unsigned n;
    if(s->state==SYM_TYPE) {
        for(t=types;t;t=t->next) if(t->sym==s) return t;
        if(s->typekind==TYPE_STRUCT || s->typekind==TYPE_UNION || s->typekind==TYPE_RECORD)
            return type_new(s->typekind==TYPE_UNION?DT_UNION:s->typekind==TYPE_RECORD?DT_RECORD:DT_STRUCT,s,NULL,s->total_size,0,0,s->name);
        t=type_new(DT_ALIAS,s,NULL,0,0,0,s->name);
        /* Install the alias before following its target to terminate cycles. */
        if(s->mem_type==MT_PTR) {
            struct dwtype *target=s->target_type?type_sym(s->target_type,FALSE):type_mem(s->ptr_memtype,NULL);
            for(n=0;n<(s->is_ptr?s->is_ptr:1);n++) target=type_new(DT_POINTER,NULL,target,2<<s->Ofssize,0,0,NULL);
            t->target=target;
        } else t->target=type_mem(s->mem_type,s->type);
        return t;
    }
    if(s->mem_type==MT_PTR) {
        t=s->target_type?type_sym(s->target_type,FALSE):type_mem(s->ptr_memtype,NULL);
        for(n=0;n<(s->is_ptr?s->is_ptr:1);n++) t=type_new(DT_POINTER,NULL,t,2<<s->Ofssize,0,0,NULL);
    } else t=type_mem(s->mem_type,s->type);
    if(array && s->isarray) t=type_new(DT_ARRAY,NULL,t,s->total_size,0,s->total_length,NULL);
    return t;
}
static void typeref(struct dwbuf *b, struct dwtype *t)
{
    struct dwref *r=MemAlloc(sizeof(*r));r->type=t;r->offset=b->size;r->next=refs;refs=r;num(b,0,4);
}
static void write_types(struct dwbuf *b)
{
    struct dwtype *t,*next;struct dwref *r,*rn;struct sfield *f;
    for(t=types;t;t=t->next) {
        t->die=b->size;
        switch(t->kind) {
        case DT_VOID: uleb(b,3);str(b,"void");break;
        case DT_BASE: uleb(b,4);str(b,t->name);num(b,t->size,4);num(b,t->encoding,1);break;
        case DT_POINTER: uleb(b,5);typeref(b,t->target);num(b,t->size,1);break;
        case DT_ALIAS: uleb(b,6);str(b,t->name);typeref(b,t->target);break;
        case DT_ARRAY:
            uleb(b,7);typeref(b,t->target);num(b,t->size,4);
            uleb(b,8);num(b,0,4);num(b,t->count,4);num(b,0,1);break;
        default:
            uleb(b,t->kind==DT_UNION?10:9);str(b,t->name);num(b,t->size,4);
            for(f=((struct dsym *)t->sym)->e.structinfo->head;f;f=f->next) {
                if(t->kind==DT_RECORD) {
                    uleb(b,12);str(b,f->sym.name);typeref(b,type_mem(t->size>4?MT_QWORD:MT_DWORD,NULL));
                    num(b,f->sym.total_size,4);num(b,f->sym.offset,4);
                } else {
                    uleb(b,11);str(b,f->sym.name);typeref(b,type_sym(&f->sym,TRUE));num(b,f->sym.offset,4);
                }
            }
            num(b,0,1);break;
        }
    }
    for(r=refs;r;r=rn) { patch32(b,r->offset,r->type->die);rn=r->next;MemFree(r); } refs=NULL;
    for(t=types;t;t=next) { next=t->next;MemFree(t); } types=NULL;
}
static unsigned dwreg(unsigned token)
{
    static const unsigned gp[]={0,2,1,3,7,6,4,5,8,9,10,11,12,13,14,15};
    unsigned n=GetRegNo(token);
    if(GetValueSp(token)&(OP_XMM|OP_YMM|OP_ZMM)) return n<16?17+n:67+n-16;
    return n<16?gp[n]:~0U;
}

/* Capture final instruction boundaries, not assumed encoding lengths. CFA is
 * the caller's RSP before CALL. Only automatic System V procedures participate.
 * User-written custom frames have no inferred unwind contract. */
struct dwcfi_event { struct dwcfi_event *next; unsigned pc, op, reg; int value; };
struct dwcfi { struct dwcfi *next; struct dsym *proc; struct dwcfi_event *events, **tail;
    int depth, cfa_offset, saved_depth, saved_offset; unsigned cfa_reg, saved_reg; bool epilogue; };
static struct dwcfi *cfi_frames, *cfi_active;
static void cfi_event(unsigned op, unsigned reg, int value)
{
    struct dwcfi_event *e=MemAlloc(sizeof(*e));
    e->next=NULL;e->pc=GetCurrOffset();e->op=op;e->reg=reg;e->value=value;
    *cfi_active->tail=e;cfi_active->tail=&e->next;
}
static void clear_cfi(void)
{
    while(cfi_frames) {
        struct dwcfi *next=cfi_frames->next;
        struct dwcfi_event *e=cfi_frames->events;
        while(e) {struct dwcfi_event *n=e->next;MemFree(e);e=n;}
        MemFree(cfi_frames);cfi_frames=next;
    }
    cfi_active=NULL;
}
void dwarf_cfi_begin(struct dsym *proc)
{
    struct dwcfi *f;
    cfi_active=NULL;
    if(!write_to_file || Options.output_format!=OFORMAT_ELF || ModuleInfo.defOfssize!=USE64 ||
       !(Options.debug_symbols || Options.line_numbers) || proc->sym.langtype!=LANG_SYSVCALL ||
       ModuleInfo.prologuemode!=PEM_DEFAULT || ModuleInfo.epiloguemode!=PEM_DEFAULT) return;
    f=MemAlloc(sizeof(*f));memset(f,0,sizeof(*f));f->proc=proc;f->tail=&f->events;
    f->depth=f->cfa_offset=8;f->cfa_reg=7;f->next=cfi_frames;cfi_frames=f;cfi_active=f;
}
void dwarf_cfi_epilogue(bool begin)
{
    struct dwcfi *f=cfi_active;
    if(!f || f->proc!=CurrProc) return;
    if(begin) {
        f->saved_depth=f->depth;f->saved_offset=f->cfa_offset;f->saved_reg=f->cfa_reg;
        f->epilogue=TRUE;cfi_event(0x0a,0,0); /* remember_state */
    } else if(f->epilogue) {
        cfi_event(0x0b,0,0); /* restore state for subsequent source paths */
        f->depth=f->saved_depth;f->cfa_offset=f->saved_offset;f->cfa_reg=f->saved_reg;f->epilogue=FALSE;
    }
}
void dwarf_cfi_instruction(unsigned token, const struct expr *ops)
{
    struct dwcfi *f=cfi_active;
    unsigned a,b;
    int delta=0;
    if(!f || f->proc!=CurrProc || !write_to_file) return;
    a=ops[0].base_reg?ops[0].base_reg->tokval:0;
    b=ops[1].base_reg?ops[1].base_reg->tokval:0;
    if(token==T_PUSH) {
        f->depth+=8;
        if(f->cfa_reg==7) {f->cfa_offset=f->depth;cfi_event(0x0e,0,f->depth);}
        if(ops[0].kind==EXPR_REG && !CurrProc->e.procinfo->prologueDone) cfi_event(0x05,dwreg(a),f->depth/8); /* offset_extended */
    } else if(token==T_POP && ops[0].kind==EXPR_REG) {
        f->depth-=8;
        if(f->epilogue && f->cfa_reg==dwreg(a)) {f->cfa_reg=7;f->cfa_offset=f->depth;cfi_event(0x0c,7,f->depth);}
        else if(f->cfa_reg==7) {f->cfa_offset=f->depth;cfi_event(0x0e,0,f->depth);}
        if(f->epilogue) cfi_event(0x08,dwreg(a),0); /* restored register is now same_value */
    } else if(!CurrProc->e.procinfo->prologueDone && token==T_MOV && a==T_RBP && b==T_RSP && !ops[0].indirect && !ops[1].indirect) {
        f->cfa_reg=6;f->cfa_offset=f->depth;cfi_event(0x0c,6,f->depth);
    } else if(a==T_RSP && !ops[0].indirect) {
        if((token==T_SUB || token==T_ADD) && ops[1].kind==EXPR_CONST)
            delta=token==T_SUB?ops[1].value:-ops[1].value;
        else if(token==T_LEA && b==T_RSP && !ops[1].idx_reg) delta=-ops[1].value;
        f->depth+=delta;
        if(delta && f->cfa_reg==7) {f->cfa_offset=f->depth;cfi_event(0x0e,0,f->depth);}
    }
    /* USES vector saves describe the low 128 bits represented by the AMD64
     * DWARF XMM register. Full YMM/ZMM value reconstruction is not inferred. */
    if((token==T_MOVDQU || token==T_MOVDQA || token==T_VMOVDQU || token==T_VMOVDQU64) &&
       (!CurrProc->e.procinfo->prologueDone || f->epilogue)) {
        if(ops[0].indirect && a==T_RSP && b && (GetValueSp(b)&(OP_XMM|OP_YMM|OP_ZMM)))
            cfi_event(0x05,dwreg(b),(f->depth-ops[0].value)/8);
        else if(ops[1].indirect && b==T_RSP && a && (GetValueSp(a)&(OP_XMM|OP_YMM|OP_ZMM)))
            cfi_event(0x08,dwreg(a),0);
    }
}
static void write_cfi(struct dwbuf *b, bool eh)
{
    struct dwcfi *f;
    unsigned start;
    /* DWARF4 CIE, 8-byte addresses, code alignment 1, data alignment -8,
     * RIP return column 16, initial CFA RSP+8 and RIP at CFA-8. */
    num(b,0,4);num(b,eh ? 0 : 0xffffffff,4);
    if(eh) {num(b,1,1);str(b,"zR");}
    else {num(b,4,1);num(b,0,1);num(b,8,1);num(b,0,1);}
    uleb(b,1);sleb(b,-8);uleb(b,16);
    /* zR: FDE start addresses use DW_EH_PE_pcrel | DW_EH_PE_sdata4.
     * Section-relative code symbols avoid interposition and dynamic relocations. */
    if(eh) {uleb(b,1);num(b,0x1b,1);}
    num(b,0x0c,1);uleb(b,7);uleb(b,8);
    num(b,0x90,1);uleb(b,1);
    while(b->size%8) num(b,0,1);
    patch32(b,0,b->size-4);
    for(f=cfi_frames;f;f=f->next) {
        struct dwcfi_event *e;unsigned pc=f->proc->sym.offset;
        start=b->size;num(b,0,4);
        if(eh) num(b,start+4,4); /* backward distance from CIE pointer to CIE */
        else address(b,b->seg,0,4);
        address(b,(struct dsym *)f->proc->sym.segment,pc,eh ? 4 : 8);
        b->rel->pcrel=eh;
        num(b,f->proc->sym.total_size,eh ? 4 : 8);
        if(eh) uleb(b,0); /* empty FDE augmentation */
        for(e=f->events;e;e=e->next) {
            if(e->pc>pc) {num(b,4,1);num(b,e->pc-pc,4);pc=e->pc;} /* advance_loc4 */
            num(b,e->op,1);
            switch(e->op) {
            case 0x05:case 0x0c: uleb(b,e->reg);uleb(b,e->value);break;
            case 0x08: uleb(b,e->reg);break;
            case 0x0e: uleb(b,e->value);break;
            }
        }
        while(b->size%8) num(b,0,1);
        patch32(b,start,b->size-start-4);
    }
}

static void stack_range(struct dwbuf *loc, struct dsym *proc, unsigned first, unsigned last, int offset)
{
    struct dwbuf expr;memset(&expr,0,sizeof(expr));
    if(first>=last) return;
    num(&expr,0x70+dwreg(proc->e.procinfo->basereg),1);sleb(&expr,offset);
    address(loc,(struct dsym *)proc->sym.segment,first,8);address(loc,(struct dsym *)proc->sym.segment,last,8);
    num(loc,expr.size,2);bytes(loc,expr.p,expr.size);MemFree(expr.p);
}
static void local_symbol(struct dwbuf *info, struct dwbuf *loc, struct dsym *proc, struct asym *s, bool param)
{
    bool reg=s->state==SYM_TMACRO || (s->sysv_home && !s->used);
    if(s->is_vararg) { uleb(info,19);return; }
    if(reg) {
        struct dwbuf expr;memset(&expr,0,sizeof(expr));
        num(&expr,0x90,1);uleb(&expr,dwreg(s->tokval));
        uleb(info,param?14:15);str(info,s->name);typeref(info,type_sym(s,TRUE));
        uleb(info,expr.size);bytes(info,expr.p,expr.size);MemFree(expr.p);
    } else {
        struct dwframe *frame;struct dwepi *e;unsigned first;
        uleb(info,param?16:17);str(info,s->name);typeref(info,type_sym(s,TRUE));address(info,loc->seg,loc->size,4);
        num(loc,~(uint_64)0,8);num(loc,0,8); /* explicit zero base for absolute relocated ranges */
        for(frame=frames;frame && frame->proc!=proc;frame=frame->next);
        if(param && s->sysv_home && frame && frame->automatic && frame->body>(unsigned)proc->sym.offset) {
            struct dwbuf expr;memset(&expr,0,sizeof(expr));num(&expr,0x90,1);uleb(&expr,dwreg(s->tokval));
            address(loc,(struct dsym *)proc->sym.segment,proc->sym.offset,8);address(loc,(struct dsym *)proc->sym.segment,frame->body,8);
            num(loc,expr.size,2);bytes(loc,expr.p,expr.size);MemFree(expr.p);
        }
        /* Without a known automatic frame, leave the location unavailable. */
        if(frame && frame->automatic && proc->e.procinfo->basereg==T_RBP) {
            first=frame->body;
            for(e=epis;e;e=e->next) if(e->proc==proc) {
                stack_range(loc,proc,first,e->first,s->offset);first=e->last;
            }
            stack_range(loc,proc,first,proc->sym.offset+proc->sym.total_size,s->offset);
        }
        num(loc,0,8);num(loc,0,8);
    }
}
static void global_symbols(struct dwbuf *info)
{
    struct asym *s=NULL;int i=0;
    while((s=SymEnum(s,&i))!=NULL) {
        if(s->state==SYM_TYPE && !s->predefined) {type_sym(s,FALSE);continue;}
        if(s->state!=SYM_INTERNAL || !s->isdefined || !s->segment || s->isproc || s->scoped || s->isequate || s->predefined ||
            s->mem_type==MT_NEAR || s->mem_type==MT_FAR || s->mem_type==MT_EMPTY) continue;
        uleb(info,13);str(info,s->name);typeref(info,type_sym(s,TRUE));num(info,s->ispublic,1);
        uleb(info,9);num(info,3,1);address(info,(struct dsym *)s->segment,s->offset,8);
    }
}

void dwarf_write(void)
{
    static const char *names[] = { ".debug_abbrev", ".debug_info", ".debug_line", ".debug_ranges", ".debug_loc", ".debug_frame", ".eh_frame" };
    /* Abbreviations: CU(name, producer, comp_dir, language, stmt_list, ranges);
     * subprogram(name, low_pc, high_pc length, external). */
    static const uint_8 abbrev[] = {1,0x11,1, 3,8, 0x25,8, 0x1b,8, 0x13,5, 0x10,0x17, 0x55,0x17, 0,0,
        2,0x2e,0, 3,8, 0x11,1, 0x12,6, 0x3f,0x0c, 0,0,
        3,0x3b,0, 3,8, 0,0,
        4,0x24,0, 3,8, 0x0b,6, 0x3e,0x0b, 0,0,
        5,0x0f,0, 0x49,0x13, 0x0b,0x0b, 0,0,
        6,0x16,0, 3,8, 0x49,0x13, 0,0,
        7,0x01,1, 0x49,0x13, 0x0b,6, 0,0,
        8,0x21,0, 0x22,6, 0x37,6, 0,0,
        9,0x13,1, 3,8, 0x0b,6, 0,0,
        10,0x17,1, 3,8, 0x0b,6, 0,0,
        11,0x0d,0, 3,8, 0x49,0x13, 0x38,6, 0,0,
        12,0x0d,0, 3,8, 0x49,0x13, 0x0d,6, 0x6b,6, 0,0,
        13,0x34,0, 3,8, 0x49,0x13, 0x3f,0x0c, 2,0x18, 0,0,
        14,0x05,0, 3,8, 0x49,0x13, 2,0x18, 0,0,
        15,0x34,0, 3,8, 0x49,0x13, 2,0x18, 0,0,
        16,0x05,0, 3,8, 0x49,0x13, 2,0x17, 0,0,
        17,0x34,0, 3,8, 0x49,0x13, 2,0x17, 0,0,
        18,0x2e,1, 3,8, 0x11,1, 0x12,6, 0x3f,0x0c, 0,0,
        19,0x18,0, 0,0, 0};
    struct dwbuf b[DW_SECTIONS]; struct dsym *seg, *proc; struct dwrow *row;
    unsigned i, header, program; char cwd[_MAX_PATH * 4];
    memset(b, 0, sizeof(b));
    types=NULL;type_tail=&types;refs=NULL;
    for (i = 0; i < DW_SECTIONS; i++) {
        if (SymSearch(names[i])) { EmitErr(SYMBOL_REDEFINITION, names[i]); return; }
    }
    for (i = 0; i < DW_SECTIONS; i++) {
        sections[i] = b[i].seg = (struct dsym *)CreateIntSegment(names[i], "", 0, USE64, TRUE);
        if (!sections[i]) return;
        sections[i]->e.seginfo->segtype = SEGTYPE_DATA;
        if (i == 6) sections[i]->e.seginfo->alignment = 3;
    }
    bytes(&b[0], abbrev, sizeof(abbrev));
    num(&b[2], 0, 4); num(&b[2], 4, 2); header = b[2].size; num(&b[2], 0, 4);
    num(&b[2], 1, 1); num(&b[2], 1, 1); num(&b[2], 1, 1); /* min insn, max ops, is_stmt */
    num(&b[2], (uint_8)-5, 1); num(&b[2], 14, 1); num(&b[2], 13, 1);
    { static const uint_8 lengths[] = {0,1,1,1,1,0,0,0,1,0,0,1}; bytes(&b[2], lengths, sizeof(lengths)); }
    num(&b[2], 0, 1); /* no include directories: file paths are relative to comp_dir */
    for (i = 0; i < ModuleInfo.g.cnt_fnames; i++) {
        str(&b[2], GetFName(i)->fname); uleb(&b[2], 0); uleb(&b[2], 0); uleb(&b[2], 0);
    }
    num(&b[2], 0, 1); program = b[2].size; patch32(&b[2], header, program - header - 4);
    for (seg = SymTables[TAB_SEG].head; seg; seg = seg->next) {
        unsigned lastfile = 1, lastoffset = 0; int lastline = 1; bool started = FALSE;
        if (seg->e.seginfo->segtype != SEGTYPE_CODE || !seg->sym.max_offset) continue;
        address(&b[3], seg, 0, 8); address(&b[3], seg, seg->sym.max_offset, 8);
        for (row = rows; row; row = row->next) if (row->seg == seg) {
            if (!started || row->offset < lastoffset) {
                if (started) { num(&b[2],0,1); uleb(&b[2],1); num(&b[2],1,1); }
                num(&b[2],0,1); uleb(&b[2],9); num(&b[2],2,1); address(&b[2],seg,row->offset,8);
                lastoffset=row->offset; lastline=1; lastfile=1; started=TRUE;
            }
            if (row->file + 1 != lastfile) { num(&b[2],4,1); uleb(&b[2],row->file+1); lastfile=row->file+1; }
            if ((int)row->line != lastline) { num(&b[2],3,1); sleb(&b[2],(int)row->line-lastline); lastline=row->line; }
            if (row->offset != lastoffset) { num(&b[2],2,1); uleb(&b[2],row->offset-lastoffset); lastoffset=row->offset; }
            num(&b[2],1,1);
        }
        if (started) { num(&b[2],2,1); uleb(&b[2],seg->sym.max_offset-lastoffset); num(&b[2],0,1); uleb(&b[2],1); num(&b[2],1,1); }
    }
    num(&b[3],0,8); num(&b[3],0,8);
    patch32(&b[2],0,b[2].size-4);
    num(&b[1],0,4); num(&b[1],4,2); address(&b[1],b[0].seg,0,4); num(&b[1],8,1);
    uleb(&b[1],1); str(&b[1],CurrFName[ASM]); str(&b[1],"UASM DWARF 4");
    if (!_getcwd(cwd,sizeof(cwd))) cwd[0]=0;
    str(&b[1],cwd); num(&b[1],0x8001,2); address(&b[1],b[2].seg,0,4); address(&b[1],b[3].seg,0,4);
    for (proc=SymTables[TAB_PROC].head; proc; proc=proc->nextproc) {
        if (!proc->sym.isdefined || !proc->sym.segment || !proc->sym.total_size) continue;
        uleb(&b[1],Options.debug_symbols && (proc->e.procinfo->paralist || proc->e.procinfo->locallist)?18:2); str(&b[1],proc->sym.name);
        address(&b[1],(struct dsym *)proc->sym.segment,proc->sym.offset,8);
        num(&b[1],proc->sym.total_size,4); num(&b[1],proc->sym.ispublic,1);
        if(Options.debug_symbols && (proc->e.procinfo->paralist || proc->e.procinfo->locallist)) {
            struct dsym *v;
            for(v=proc->e.procinfo->paralist;v;v=v->nextparam) local_symbol(&b[1],&b[4],proc,&v->sym,TRUE);
            for(v=proc->e.procinfo->locallist;v;v=v->nextlocal)
                if(!ProcIsCallTemp(proc,&v->sym)) local_symbol(&b[1],&b[4],proc,&v->sym,FALSE);
            num(&b[1],0,1);
        }
    }
    if(Options.debug_symbols) { global_symbols(&b[1]);write_types(&b[1]); }
    num(&b[1],0,1); patch32(&b[1],0,b[1].size-4);
    write_cfi(&b[5], FALSE);
    write_cfi(&b[6], TRUE);
    for (i=0;i<DW_SECTIONS;i++) publish(&b[i]);
    while (rows) { row = rows->next; MemFree(rows); rows = row; }
    tail = &rows;
    clear_frames();
}
#else
void dwarf_cfi_begin(struct dsym *proc) {}
void dwarf_cfi_instruction(unsigned token, const struct expr *ops) {}
void dwarf_cfi_epilogue(bool begin) {}
void dwarf_body(struct dsym *proc) {}
void dwarf_epilogue(struct dsym *proc,unsigned first,unsigned last) {}
void dwarf_init(void) {}
void dwarf_line(unsigned file, uint_32 line) {}
bool dwarf_section(const struct dsym *seg) { return FALSE; }
bool dwarf_eh_frame(const struct dsym *seg) { return FALSE; }
void dwarf_write(void) {}
#endif
