/****************************************************************************
*
* Description:  prototypes for cpumodel.c
*
****************************************************************************/


#ifndef _CPUMODEL_H_INCLUDED_
#define _CPUMODEL_H_INCLUDED_

extern ret_code   SetCPU( enum cpu_info );
extern void       SetModel(void);
static struct asym *sym_CodeSize; /* numeric. requires model */
static struct asym *sym_DataSize; /* numeric. requires model */

#endif
