
/* prototypes of functions defined in elf.c */
#pragma once

#ifndef _ELF_H_INCLUDED_
#define _ELF_H_INCLUDED_

#include "basedefs.h"

uasm_PACK_PUSH_STACK

void     elf_init(struct module_info*);

uasm_PACK_POP

#endif // _ELF_H_INCLUDED_
