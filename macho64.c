
#include <ctype.h>
#include <time.h>

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "mangle.h"
#include "fixup.h"
#include "segment.h"
#include "extern.h"
#include "macho64.h"
#include "macho64spec.h"
#include "myassert.h"

#define MACHOABI_OSX64 1   // 64bit x86 OSX

#define ROUND_UP( i, r ) (((i)+((r)-1)) & ~((r)-1))

/* String table entry */
struct strentry
{
	char *pstr;
	struct strentry *next;
	struct asym *sym;
	int idx;
};

struct macho_section_entry
{
	struct section_64 section;
	struct section_64 *next;
	int size;
	int ofs;
	void *data;
};

struct macho_module 
{
	char *srcname;
	struct mach_header_64 header;
	struct segment_command_64 *pSegCmd;
	struct macho_section_entry *sections;
	struct symtab_command *pSymTblCmd;
	struct dysymtab_command *pdySymTblCmd;
	struct strentry *strings;
	int symCount;
	int dySymCount;
};

/* ========================================================================================== 
Calculate the number of sections required for the MACHO64 Obj file 
-> An object file only contains 1 segment with sections, 
-> our internal segments become sections.
========================================================================================== */
int macho_section_count()
{
	int cnt = 0;
	struct dsym *curr;
	for (curr = SymTables[TAB_SEG].head; curr; curr = curr->next)
	{
		cnt++;
	}
	return(cnt);
}

/* ==========================================================================================
Build a segment_command_64 structure.
========================================================================================== */
struct segment_command_64 * macho_build_seg_cmd( int fileofs )
{
	struct segment_command_64 *pCmd = NULL;
	pCmd = malloc(sizeof(struct segment_command_64));
	memset(pCmd,0,sizeof(struct segment_command_64));
	
	pCmd->cmd      = LC_SEGMENT_64;
	pCmd->cmdsize  = sizeof(struct segment_command_64) + (sizeof(struct section_64) * macho_section_count());
	pCmd->flags = 0;
	pCmd->initprot = VM_PROT_ALL;
	pCmd->maxprot  = VM_PROT_ALL;
	pCmd->nsects = macho_section_count();
	pCmd->vmaddr = 0;
	pCmd->fileoff = fileofs;

	/* These attributes need to be completed */
	pCmd->filesize = 0;
	pCmd->vmsize = 0;

	return(pCmd);
}

/* ==========================================================================================
Build a symtabl_command structure.
========================================================================================== */
struct symtab_command * macho_build_symtbl_cmd()
{
	struct symtab_command *pCmd = NULL;
	pCmd = malloc(sizeof(struct symtab_command));
	memset(pCmd, 0, sizeof(struct symtab_command));

	pCmd->cmd = LC_SYMTAB;
	pCmd->cmdsize = sizeof(struct symtab_command);
	pCmd->nsyms = SymGetCount();
	pCmd->symoff = 0;
	pCmd->stroff = 0;
	pCmd->strsize = 0;

	return(pCmd);
}

struct dysymtab_command * macho_build_dysymtbl_cmd()
{
	struct dysymtab_command *pCmd = NULL;
	pCmd = malloc(sizeof(struct dysymtab_command));
	memset(pCmd, 0, sizeof(struct dysymtab_command));

	pCmd->cmd = LC_DYSYMTAB;
	pCmd->cmdsize = sizeof(struct dysymtab_command);

	return(pCmd);
}

/* ==========================================================================================
Add an entry to the string table.
========================================================================================== */
static void macho_add_string(struct strentry *pstr, struct macho_module *mm)
{
	struct strentry *pCurrStr = mm->strings;
	int lastIdx = 1;
	if (pCurrStr == NULL)
	{
		pstr->idx = 1;
		mm->strings = pstr;
	}
	else
	{
		while (pCurrStr->next != NULL)
		{
			pCurrStr = pCurrStr->next;
			lastIdx = pCurrStr->idx;
		}
		pstr->idx = lastIdx + 1;
		pCurrStr->next = pstr;
	}
	return;
}

/* ==========================================================================================
Create linked list of symbol names (string table)
-> This can be later scanned to determine symbol index (1 based).
========================================================================================== */
int macho_build_string_tbl(struct symtab_command *pSymCmd, struct macho_module *mm)
{
	int tblSize = 0;
	int i = 0;
	struct asym *sym = NULL;
	struct strentry *pstr = NULL;

	while (sym = SymEnum(sym, &i))
	{
		if ( ((sym->state == SYM_EXTERNAL && sym->used) || sym->ispublic || sym->segment) 
			&& (sym->state != SYM_MACRO && sym->state != SYM_SEG && sym->state != SYM_TMACRO))
		{
			tblSize += strlen(sym->name) + 1;
			pstr = malloc(sizeof(struct strentry));
			memset(pstr, 0, sizeof(struct strentry));
			pstr->pstr = sym->name;
			pstr->sym = sym;
			macho_add_string(pstr, mm);
			mm->symCount++;
		}
	}
	return(tblSize);
}

/* ==========================================================================================
Build a macho_section_entry structure.
========================================================================================== */
struct section_64 * macho_build_section( const char *secName, const char *segName, uint32_t flags )
{
	struct macho_section_entry *pSec = NULL;
	pSec = malloc(sizeof(struct macho_section_entry));
	memset(pSec, 0, sizeof(struct macho_section_entry));

	strcpy(pSec->section.sectname, secName);
	strcpy(pSec->section.segname, segName);
	pSec->section.align = 4; // 2^4 = 16 byte alignment.
	pSec->section.flags = flags;

	/* addr, size, offset, reloff, nreloc still need to be completed */
	return(pSec);
}

/* ==========================================================================================
Add a macho_section_entry to our module linked list.
========================================================================================== */
static void macho_add_section(struct macho_section_entry *pSec, struct macho_module *mm)
{
	struct macho_section_entry *pCurrSec = mm->sections;
	if (pCurrSec == NULL)
		mm->sections = pSec;
	else
	{
		while (pCurrSec->next != NULL)
		{
			pCurrSec = pCurrSec->next;
		}
		pCurrSec->next = pSec;
	}
	mm->header.sizeofcmds += sizeof(struct section_64);
	return;
}

/* ==========================================================================================
Create all the macho obj file structures and calculate offsets.
========================================================================================== */
static void macho_build_structures( struct module_info *modinfo, struct macho_module mm )
{
	int cnt = 0;
	struct dsym *curr;
	struct macho_section_entry *currSec;
	struct strentry *currStr;
	int fileofs = sizeof(struct mach_header_64);
	uint64_t currAddr = 0; /* the first section starts in the 1 segment at vmaddr == 0 */
	struct segment_command_64 *pCmd = NULL;
	struct symtab_command *pSymCmd = NULL;
	struct dysymtab_command *pdySymCmd = NULL;
	int sectionDataSize = 0;
	int stringTableSize = 0;

	/* Setup the load segment command */
	pCmd = macho_build_seg_cmd( fileofs );
	mm.pSegCmd = pCmd;
	mm.header.ncmds++;
	mm.header.sizeofcmds += sizeof(struct segment_command_64);
	fileofs += sizeof(struct segment_command_64);

	/* For every internal segment, create a section */
	for (curr = SymTables[TAB_SEG].head; curr; curr = curr->next)
	{
		if (strcmp(curr->sym.name, "_TEXT") == 0)
		{
			currSec = macho_build_section("__text", "__TEXT", S_REGULAR);
			macho_add_section(currSec, &mm);
			currSec->data = curr->e.seginfo->CodeBuffer;
			currSec->size = curr->e.seginfo->bytes_written;
			currSec->section.size = currSec->size;
			currSec->section.addr = currAddr;
			currAddr += currSec->size;
			currAddr = ROUND_UP(currAddr, 16); /* Keep vmaddr aligned to 16bytes after each section */
			pCmd->filesize += currSec->size;
		}
		
		else if (strcmp(curr->sym.name, "_DATA") == 0)
		{
			currSec = macho_build_section("__data", "__DATA", S_REGULAR);
			macho_add_section(currSec, &mm);
			currSec->data = curr->e.seginfo->CodeBuffer;
			currSec->size = curr->e.seginfo->bytes_written;
			currSec->section.size = currSec->size;
			currSec->section.addr = currAddr;
			currAddr += currSec->size;
			currAddr = ROUND_UP(currAddr, 16);
			pCmd->filesize += currSec->size;
		}

		else if (strcmp(curr->sym.name, "CONST") == 0)
		{
			currSec = macho_build_section("_rdata", "__DATA", S_REGULAR);
			macho_add_section(currSec, &mm);
			currSec->data = curr->e.seginfo->CodeBuffer;
			currSec->size = curr->e.seginfo->bytes_written;
			currSec->section.size = currSec->size;
			currSec->section.addr = currAddr;
			currAddr += currSec->size;
			currAddr = ROUND_UP(currAddr, 16);
			pCmd->filesize += currSec->size;
		}

		else if (strcmp(curr->sym.name, "_BSS") == 0)
		{
			currSec = macho_build_section("__bss", "__DATA", S_ZEROFILL);
			macho_add_section(currSec, &mm);
			currSec->data = curr->e.seginfo->CodeBuffer;
			currSec->size = curr->e.seginfo->bytes_written;
			currSec->section.size = currSec->size;
			currSec->section.addr = currAddr;
			currAddr = ROUND_UP(currAddr, 16);
			currAddr += currSec->size;
		}
		fileofs += sizeof(struct section_64);
		pCmd->vmsize += currSec->size;
	}
	/* At this point only the section offsets (file) need to still be set 
	-> Once we have the size of the remaining commands. */

	/* Build sym table command */
	pSymCmd = macho_build_symtbl_cmd();
	mm.pSymTblCmd = pSymCmd;
	mm.header.ncmds++;
	mm.header.sizeofcmds += sizeof(struct symtab_command);
	fileofs += sizeof(struct symtab_command);

	/* Build dsym table command */
	pdySymCmd = macho_build_dysymtbl_cmd();
	mm.pdySymTblCmd = pdySymCmd;
	mm.header.ncmds++;
	mm.header.sizeofcmds += sizeof(struct dysymtab_command);
	fileofs += sizeof(struct dysymtab_command);

	/* Set section file offsets */
	sectionDataSize = 0;
	for (currSec = mm.sections;currSec;currSec = currSec->next)
	{
		currSec->section.offset = fileofs + sectionDataSize;
		currSec->ofs = fileofs + sectionDataSize;
		sectionDataSize += currSec->size;
	}

	/* Build the string table data */
	stringTableSize = macho_build_string_tbl(pSymCmd,&mm);

	/* Set symbol table sizes and offsets */
	pSymCmd->nsyms = mm.symCount;
	pSymCmd->symoff = fileofs + sectionDataSize;
	pSymCmd->strsize = stringTableSize;
	pSymCmd->stroff = fileofs + sectionDataSize + (sizeof(struct nlist_64)*pSymCmd->nsyms);

	/* Write out the macho header */
	if (fwrite(&mm.header, 1, sizeof(mm.header), CurrFile[OBJ]) != sizeof(mm.header))
		WriteError();

	/* Write out the segment command */
	if (fwrite(pCmd, 1, sizeof(struct segment_command_64), CurrFile[OBJ]) != sizeof(struct segment_command_64))
		WriteError();

	/* Write out the section_64 list */
	for (currSec = mm.sections;currSec;currSec = currSec->next)
	{
		if (fwrite(&currSec->section, 1, sizeof(struct section_64), CurrFile[OBJ]) != sizeof(struct section_64))
			WriteError();
	}

	/* Write out symbol table commands */
	if (fwrite(pSymCmd, 1, sizeof(struct symtab_command), CurrFile[OBJ]) != sizeof(struct symtab_command))
		WriteError();
	if (fwrite(pdySymCmd, 1, sizeof(struct dysymtab_command), CurrFile[OBJ]) != sizeof(struct dysymtab_command))
		WriteError();

	/* Write out the section data */
	for (currSec = mm.sections;currSec;currSec = currSec->next)
	{
		if (fwrite(currSec->data, 1, currSec->size, CurrFile[OBJ]) != currSec->size)
			WriteError();
	}

	/* Write out symbol table entries */
	for (currStr = mm.strings;currStr;currStr = currStr->next)
	{

	}

	/* Write out relocation command */
	/* Write out nlist64 entries */

	/* Write out string table */
	for (currStr = mm.strings;currStr;currStr = currStr->next)
	{
		int len = strlen(currStr->pstr) + 1;
		if (fwrite(currStr->pstr, 1, len, CurrFile[OBJ]) != len)
			WriteError();
	}
}

static ret_code macho_write_module( struct module_info *modinfo )
{
	struct macho_module mm;
	int fileofs = 0;

	DebugMsg(("macho_write_module: enter\n"));

	memset(&mm, 0, sizeof(mm));
	mm.srcname = CurrFName[ASM];
#if 1
	/* the path part is stripped. todo: check if this is ok to do */
	mm.srcname += strlen(mm.srcname);
	while (mm.srcname > CurrFName[ASM] &&
		*(mm.srcname - 1) != '/' &&
		*(mm.srcname - 1) != '\\') mm.srcname--;
#endif
	/* position at 0 ( probably unnecessary, since there were no writes yet ) */
	fseek(CurrFile[OBJ], 0, SEEK_SET);
	
	if( modinfo->defOfssize == USE64)
	{
		mm.header.magic = MH_MAGIC_64;
		mm.header.cputype = CPU_TYPE_X86_64;
		mm.header.cpusubtype = CPU_SUBTYPE_LITTLE_ENDIAN;
		mm.header.filetype = MH_OBJECT;
		mm.header.ncmds = 1;
		mm.header.sizeofcmds = sizeof(struct segment_command_64);
		mm.header.flags = NULL;
		
		macho_build_structures(modinfo, mm);	
	}
	else
	{
		EmitError(MACHO_NOT_64);
		return(ERROR);
	}

	DebugMsg(("macho_write_module: exit\n"));
	return(NOT_ERROR);
}

void macho_init( struct module_info *modinfo )
{
	modinfo->osx_osabi = MACHOABI_OSX64;
	modinfo->g.WriteModule = macho_write_module;
	return;
}