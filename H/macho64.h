#pragma once

/* prototypes of functions defined in macho64.c */

#ifndef _MACHO64_H_INCLUDED_
#define _MACHO64_H_INCLUDED_

#include "basedefs.h"

uasm_PACK_PUSH_STACK

void     macho_init(struct module_info*);

uasm_PACK_POP

#endif // _MACHO64_H_INCLUDED_
