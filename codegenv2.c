
//vsib
//displacement
//comp displacement
//evex
//vex

#include "codegenv2.h"

#include <time.h>
#include "globals.h"
#include "parser.h"
#include "segment.h"
#include "extern.h"
#include "fixup.h"
#include "fastpass.h"
#include "myassert.h"
#include "types.h"
#include "macro.h"
#include "listing.h"

#define OutputCodeByte( x ) OutputByte( x )

struct Mem_Def MemTable[] = {
	/* INDEX---> NONE							                                      AX CX DX BX SP BP  SI DI R8 R9 R10 R11 R12  R13 R14 R15 RIP */
	/* BASE																																		  */
	/*  |																																		  */																							
	/*  v																																		  */
	/* AX */     { (NO_MOD | RM_AX), MEMF_USEMODRM, 0x00, (X16 | X32 | X64), NO_REX },
	/* CX */     { (NO_MOD | RM_CX), MEMF_USEMODRM, 0x00, (X16 | X32 | X64), NO_REX },
	/* DX */     { (NO_MOD | RM_DX), MEMF_USEMODRM, 0x00, (X16 | X32 | X64), NO_REX },
	/* BX */     { (NO_MOD | RM_BX), MEMF_USEMODRM, 0x00, (X16 | X32 | X64), NO_REX },
};

struct Instr_Def* InstrHash[16384];

struct Instr_Def InstrTableV2[] = {
	
	/* | mnemonic | operand count | operand types | encoding group | flags | opcode len | opcode bytes | op size | modRM | sib | OSO | ASO | Valid segment modes | opnd direction | mandatory prefix type | immediate Operand? | memory Operand? | CPU mode | */
	/* General Purpose Reg->Reg moves */
	{ "mov", 2, { R8,      R8      }, GP0, (F_MODRM | F_MODRM_REG | F_MODRM_RM),							  1, { 0x88, 0x00, 0x00 }, 1, MOD_REG_REG, 0, 0,                0,                  (X16 | X32 | X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_86,  0, NULL },
	{ "mov", 2, { R8,      R8H     }, GP0, (F_MODRM | F_MODRM_REG | F_MODRM_RM),							  1, { 0x88, 0x00, 0x00 }, 1, MOD_REG_REG, 0, 0,                0,                  (X16 | X32 | X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_86,  0, NULL },
	{ "mov", 2, { R8H,     R8      }, GP0, (F_MODRM | F_MODRM_REG | F_MODRM_RM),							  1, { 0x88, 0x00, 0x00 }, 1, MOD_REG_REG, 0, 0,                0,                  (X16 | X32 | X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_86,  0, NULL },
	{ "mov", 2, { R8H,     R8H     }, GP0, (F_MODRM | F_MODRM_REG | F_MODRM_RM),							  1, { 0x88, 0x00, 0x00 }, 1, MOD_REG_REG, 0, 0,                0,                  (X16 | X32 | X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_86,  0, NULL },
	{ "mov", 2, { R8E,     R8E     }, GP3, (REX | REXB | REXR) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),		  1, { 0x88, 0x00, 0x00 }, 1, MOD_REG_REG, 0, 0,                0,                  (            X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R8,      R8E     }, GP3, (REX | REXR) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  1, { 0x88, 0x00, 0x00 }, 1, MOD_REG_REG, 0, 0,                0,                  (			 X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R8E,     R8      }, GP3, (REX | REXB) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  1, { 0x88, 0x00, 0x00 }, 1, MOD_REG_REG, 0, 0,                0,                  (		   	 X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R8U,     R8      }, GP3, (REX) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),					  1, { 0x88, 0x00, 0x00 }, 1, MOD_REG_REG, 0, 0,                0,                  (		     X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R16,     R16     }, GP0, (F_MODRM | F_MODRM_REG | F_MODRM_RM),							  1, { 0x89, 0x00, 0x00 }, 2, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (X16 | X32 | X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_86,  0, NULL },
	{ "mov", 2, { R16E,    R16E    }, GP3, (REX | REXB | REXR) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),		  1, { 0x89, 0x00, 0x00 }, 2, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (            X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R16E,    R16     }, GP3, (REX | REXB) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  1, { 0x89, 0x00, 0x00 }, 2, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (            X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R16,     R16E    }, GP3, (REX | REXR) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  1, { 0x89, 0x00, 0x00 }, 2, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (            X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R32,     R32     }, GP0, (F_MODRM | F_MODRM_REG | F_MODRM_RM),							  1, { 0x89, 0x00, 0x00 }, 4, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (X16 | X32 | X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_86,  0, NULL },
	{ "mov", 2, { R32E,    R32E    }, GP3, (REX | REXB | REXR) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),		  1, { 0x89, 0x00, 0x00 }, 4, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (            X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R32E,    R32     }, GP3, (REX | REXB) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  1, { 0x89, 0x00, 0x00 }, 4, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (            X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R32,     R32E    }, GP3, (REX | REXR) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  1, { 0x89, 0x00, 0x00 }, 4, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (            X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R64,     R64     }, GP3, (REX | REXW) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),		          1, { 0x89, 0x00, 0x00 }, 8, MOD_REG_REG, 0, 0,                0,                  (            X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R64E,    R64E    }, GP3, (REX | REXR | REXB | REXW) | (F_MODRM | F_MODRM_REG | F_MODRM_RM), 1, { 0x89, 0x00, 0x00 }, 8, MOD_REG_REG, 0, 0,                0,                  (			 X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R64,     R64E    }, GP3, (REX | REXR | REXW) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),		  1, { 0x89, 0x00, 0x00 }, 8, MOD_REG_REG, 0, 0,                0,                  (			 X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R64E,    R64     }, GP3, (REX | REXB | REXW) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),		  1, { 0x89, 0x00, 0x00 }, 8, MOD_REG_REG, 0, 0,                0,                  (			 X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	/* CR0-CR8 register moves */
	{ "mov", 2, { R32,     R_CR    }, GP0, (F_MODRM | F_MODRM_REG | F_MODRM_RM),							  2, { 0x0f, 0x20, 0x00 }, 4, MOD_REG_REG, 0, 0,                0,                  (X16 | X32      ), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_86,  0, NULL },
	{ "mov", 2, { R64,     R_CR    }, GP0, (F_MODRM | F_MODRM_REG | F_MODRM_RM),							  2, { 0x0f, 0x20, 0x00 }, 8, MOD_REG_REG, 0, 0,                0,                  (		     X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R64E,    R_CR    }, GP3, (REX | REXB) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),			      2, { 0x0f, 0x20, 0x00 }, 8, MOD_REG_REG, 0, 0,                0,                  (			 X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R64,     R_CR8   }, GP3, (REX | REXR) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  2, { 0x0f, 0x20, 0x00 }, 8, MOD_REG_REG, 0, 0,                0,                  (			 X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R64E,    R_CR8   }, GP3, (REX | REXB | REXR) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),	      2, { 0x0f, 0x20, 0x00 }, 8, MOD_REG_REG, 0, 0,                0,                  (			 X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R_CR,    R32     }, GP0, (F_MODRM | F_MODRM_REG | F_MODRM_RM),							  2, { 0x0f, 0x22, 0x00 }, 4, MOD_REG_REG, 0, 0,                0,                  (X16 | X32      ), REG_DST, NO_PREFIX, NO_IMM,     NO_MEM,     P_86,  0, NULL },
	{ "mov", 2, { R_CR,    R64     }, GP0, (F_MODRM | F_MODRM_REG | F_MODRM_RM),							  2, { 0x0f, 0x22, 0x00 }, 8, MOD_REG_REG, 0, 0,                0,                  (			 X64), REG_DST, NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R_CR,    R64E    }, GP3, (REX | REXB) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  2, { 0x0f, 0x22, 0x00 }, 8, MOD_REG_REG, 0, 0,                0,                  (			 X64), REG_DST, NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R_CR8,   R64     }, GP3, (REX | REXR) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  2, { 0x0f, 0x22, 0x00 }, 8, MOD_REG_REG, 0, 0,                0,                  (            X64), REG_DST, NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R_CR8,   R64E    }, GP3, (REX | REXB | REXR) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),		  2, { 0x0f, 0x22, 0x00 }, 8, MOD_REG_REG, 0, 0,                0,                  (            X64), REG_DST, NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	/* DR0-DR7 register moves */
	{ "mov", 2, { R32,     R_DR    }, GP0, (F_MODRM | F_MODRM_REG | F_MODRM_RM),							  2, { 0x0f, 0x21, 0x00 }, 4, MOD_REG_REG, 0, 0,                0,                  (X16 | X32      ), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_86,  0, NULL },
	{ "mov", 2, { R64,     R_DR    }, GP0, (F_MODRM | F_MODRM_REG | F_MODRM_RM),							  2, { 0x0f, 0x21, 0x00 }, 8, MOD_REG_REG, 0, 0,                0,                  (			 X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R64E,    R_DR    }, GP3, (REX | REXB) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),			      2, { 0x0f, 0x21, 0x00 }, 8, MOD_REG_REG, 0, 0,                0,                  (	         X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R_DR,    R32     }, GP0, (F_MODRM | F_MODRM_REG | F_MODRM_RM),							  2, { 0x0f, 0x23, 0x00 }, 4, MOD_REG_REG, 0, 0,                0,                  (X16 | X32      ), REG_DST, NO_PREFIX, NO_IMM,     NO_MEM,     P_86,  0, NULL },
	{ "mov", 2, { R_DR,    R64     }, GP0, (F_MODRM | F_MODRM_REG | F_MODRM_RM),							  2, { 0x0f, 0x23, 0x00 }, 8, MOD_REG_REG, 0, 0,                0,                  (			 X64), REG_DST, NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R_DR,    R64E    }, GP3, (REX | REXB) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  2, { 0x0f, 0x23, 0x00 }, 8, MOD_REG_REG, 0, 0,                0,                  (			 X64), REG_DST, NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	/* Segment register to register moves */
	{ "mov", 2, { R16,     R_SEG   }, GP0, (F_MODRM | F_MODRM_REG | F_MODRM_RM),							  1, { 0x8c, 0x00, 0x00 }, 2, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (X16 | X32 | X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_86,  0, NULL },
	{ "mov", 2, { R16,     R_SEGE  }, GP0, (F_MODRM | F_MODRM_REG | F_MODRM_RM),							  1, { 0x8c, 0x00, 0x00 }, 2, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (      X32 | X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_386, 0, NULL },
	{ "mov", 2, { R32,     R_SEG   }, GP0, (F_MODRM | F_MODRM_REG | F_MODRM_RM),							  1, { 0x8c, 0x00, 0x00 }, 4, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (      X32 | X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_386, 0, NULL },
	{ "mov", 2, { R32,     R_SEGE  }, GP0, (F_MODRM | F_MODRM_REG | F_MODRM_RM),							  1, { 0x8c, 0x00, 0x00 }, 4, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (      X32 | X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_386, 0, NULL },
	{ "mov", 2, { R64,     R_SEG   }, GP3, (REX | REXW) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  1, { 0x8c, 0x00, 0x00 }, 8, MOD_REG_REG, 0, 0,				0,                  (            X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R64,     R_SEGE  }, GP3, (REX | REXW) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  1, { 0x8c, 0x00, 0x00 }, 8, MOD_REG_REG, 0, 0,				0,                  (            X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R16E,    R_SEG   }, GP3, (REX | REXB) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  1, { 0x8c, 0x00, 0x00 }, 2, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (            X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R16E,    R_SEGE  }, GP3, (REX | REXB) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  1, { 0x8c, 0x00, 0x00 }, 2, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (            X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R32E,    R_SEG   }, GP3, (REX | REXB) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  1, { 0x8c, 0x00, 0x00 }, 4, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (            X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R32E,    R_SEGE  }, GP3, (REX | REXB) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  1, { 0x8c, 0x00, 0x00 }, 4, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (            X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R64E,    R_SEG   }, GP3, (REX | REXB | REXW) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),		  1, { 0x8c, 0x00, 0x00 }, 8, MOD_REG_REG, 0, 0,				0,                  (            X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R64E,    R_SEGE  }, GP3, (REX | REXB | REXW) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),		  1, { 0x8c, 0x00, 0x00 }, 8, MOD_REG_REG, 0, 0,				0,                  (            X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R_SEG,   R16     }, GP0, (F_MODRM | F_MODRM_REG | F_MODRM_RM),							  1, { 0x8e, 0x00, 0x00 }, 2, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (X16 | X32 | X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_86,  0, NULL },
	{ "mov", 2, { R_SEGE,  R16     }, GP0, (F_MODRM | F_MODRM_REG | F_MODRM_RM),							  1, { 0x8e, 0x00, 0x00 }, 2, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (      X32 | X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_386, 0, NULL },
	{ "mov", 2, { R_SEG,   R32     }, GP0, (F_MODRM | F_MODRM_REG | F_MODRM_RM),							  1, { 0x8e, 0x00, 0x00 }, 4, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (      X32 | X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_386, 0, NULL },
	{ "mov", 2, { R_SEGE,  R32     }, GP0, (F_MODRM | F_MODRM_REG | F_MODRM_RM),							  1, { 0x8e, 0x00, 0x00 }, 4, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (      X32 | X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_386, 0, NULL },
	{ "mov", 2, { R_SEG,   R64     }, GP3, (REX | REXW) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  1, { 0x8e, 0x00, 0x00 }, 8, MOD_REG_REG, 0, 0,				0,                  (            X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R_SEGE,  R64     }, GP3, (REX | REXW) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  1, { 0x8e, 0x00, 0x00 }, 8, MOD_REG_REG, 0, 0,				0,                  (			 X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R_SEG,   R16E    }, GP3, (REX | REXR) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  1, { 0x8e, 0x00, 0x00 }, 2, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (			 X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R_SEGE,  R16E    }, GP3, (REX | REXR) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  1, { 0x8e, 0x00, 0x00 }, 2, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (			 X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R_SEG,   R32E    }, GP3, (REX | REXR) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  1, { 0x8e, 0x00, 0x00 }, 4, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (			 X64), RM_DST,  NO_PREFIX, NO_IMM,	   NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R_SEGE,  R32E    }, GP3, (REX | REXR) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  1, { 0x8e, 0x00, 0x00 }, 4, MOD_REG_REG, 0, OP_SIZE_OVERRIDE, 0,                  (			 X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R_SEG,   R64E    }, GP3, (REX | REXR | REXW) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),		  1, { 0x8e, 0x00, 0x00 }, 8, MOD_REG_REG, 0, 0,				0,                  (			 X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R_SEGE,  R64E    }, GP3, (REX | REXR | REXW) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),		  1, { 0x8e, 0x00, 0x00 }, 8, MOD_REG_REG, 0, 0,				0,                  (			 X64), RM_DST,  NO_PREFIX, NO_IMM,     NO_MEM,     P_64,  0, NULL },
	/* Reg->Immediate moves */
	{ "mov", 2, { R8,      IMM8    }, GP0, (F_OPCODE_REG),												      1, { 0xb0, 0x00, 0x00 }, 1, NO_MOD,      0, 0,				0,                  (X16 | X32 | X64), NO_DST,  NO_PREFIX, IMM_OPND_1, NO_MEM,     P_86,  0, NULL },
	{ "mov", 2, { R8H,     IMM8    }, GP0, (F_OPCODE_REG),													  1, { 0xb0, 0x00, 0x00 }, 1, NO_MOD,      0, 0,				0,                  (X16 | X32 | X64), NO_DST,  NO_PREFIX, IMM_OPND_1, NO_MEM,     P_86,  0, NULL },
	{ "mov", 2, { R8U,     IMM8    }, GP3, (REX | REXB) | (F_OPCODE_REG),									  1, { 0xb0, 0x00, 0x00 }, 1, NO_MOD,      0, 0,				0,                  (			 X64), NO_DST,  NO_PREFIX, IMM_OPND_1, NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R8E,     IMM8    }, GP3, (REX | REXB) | (F_OPCODE_REG),							          1, { 0xb0, 0x00, 0x00 }, 1, NO_MOD,      0, 0,				0,                  (			 X64), NO_DST,  NO_PREFIX, IMM_OPND_1, NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R16,     IMM16   }, GP0, (F_OPCODE_REG),												      1, { 0xb8, 0x00, 0x00 }, 2, NO_MOD,      0, OP_SIZE_OVERRIDE, 0,                  (X16 | X32 | X64), NO_DST,  NO_PREFIX, IMM_OPND_1, NO_MEM,     P_86,  0, NULL },
	{ "mov", 2, { R16E,    IMM16   }, GP3, (REX | REXB) | (F_OPCODE_REG),								      1, { 0xb8, 0x00, 0x00 }, 2, NO_MOD,      0, OP_SIZE_OVERRIDE,	0,                  (            X64), NO_DST,  NO_PREFIX, IMM_OPND_1, NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R32,     IMM32   }, GP0, (F_OPCODE_REG),												      1, { 0xb8, 0x00, 0x00 }, 4, NO_MOD,      0, OP_SIZE_OVERRIDE, 0,                  (X16 | X32 | X64), NO_DST,  NO_PREFIX, IMM_OPND_1, NO_MEM,     P_86,  0, NULL },
	{ "mov", 2, { R32E,    IMM32   }, GP3, (REX | REXB) | (F_OPCODE_REG),								      1, { 0xb8, 0x00, 0x00 }, 4, NO_MOD,      0, OP_SIZE_OVERRIDE,	0,                  (            X64), NO_DST,  NO_PREFIX, IMM_OPND_1, NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R64,     IMM64   }, GP3, (REX | REXW) | (F_OPCODE_REG),								      1, { 0xb8, 0x00, 0x00 }, 8, NO_MOD,      0, 0,				0,                  (            X64), NO_DST,  NO_PREFIX, IMM_OPND_1, NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R64E,    IMM64   }, GP3, (REX | REXW | REXB) | (F_OPCODE_REG),						      1, { 0xb8, 0x00, 0x00 }, 8, NO_MOD,      0, 0,				0,                  (            X64), NO_DST,  NO_PREFIX, IMM_OPND_1, NO_MEM,     P_64,  0, NULL },
	{ "mov", 2, { R64,     IMM32   }, GP3, (REX | REXW) | (F_OPCODE_REG),								      1, { 0xc7, 0x00, 0x00 }, 8, NO_MOD,      0, 0,				0,                  (            X64), NO_DST,  NO_PREFIX, IMM_OPND_1, NO_MEM,	   P_64,  0, NULL },
	{ "mov", 2, { R64E,    IMM32   }, GP3, (REX | REXW | REXB) | (F_OPCODE_REG),						      1, { 0xc7, 0x00, 0x00 }, 8, NO_MOD,      0, 0,				0,                  (            X64), NO_DST,  NO_PREFIX, IMM_OPND_1, NO_MEM,	   P_64,  0, NULL },
	/* Mem->Reg moves */
	{ "mov", 2, { R8,      M_ANY   }, GP0, ALLOW_SEG | (F_MODRM | F_MODRM_REG | F_MODRM_RM),				  1, { 0x8a, 0x00, 0x00 }, 1, MOD_REG_MEM, 0, 0,				0,                  (X16 | X32 | X64), REG_DST, NO_PREFIX, NO_IMM    , MEM_OPND_1, P_86,  0, NULL },
	{ "mov", 2, { R8E,     M_ANY   }, GP0, ALLOW_SEG | (REX | REXB) | (F_MODRM | F_MODRM_REG | F_MODRM_RM),	  1, { 0x8a, 0x00, 0x00 }, 1, MOD_REG_MEM, 0, 0,				0,                  (            X64), REG_DST, NO_PREFIX, NO_IMM    , MEM_OPND_1, P_64,  0, NULL },

	/* Mem->Immediate moves*/
};

static unsigned int hash(const uint_8* data, int size)
/******************************************/
{
	uint_64 fnv_basis = 14695981039346656037;
	uint_64 register fnv_prime = 1099511628211;
	uint_64 h = fnv_basis;
	int cnt = 0;
	for (cnt = 0; cnt<size; cnt++) {
		h ^= *data;
		h *= fnv_prime;
	}
	return((((h >> 16) ^ h) & 0xffff));
}

struct Instr_Def* AllocInstruction() 
{
	return malloc(sizeof(struct Instr_Def));
}

void InsertInstruction(struct Instr_Def* pInstruction, uint_32 hash)
{
	struct Instr_Def* curPtr = NULL;
	curPtr = InstrHash[hash];
	if (curPtr == NULL)
	{
		InstrHash[hash] = pInstruction;
		return;
	}
	while (curPtr->next != NULL)
	{
		curPtr = curPtr->next;
	}
	curPtr->next = pInstruction;
}

uint_32 GenerateInstrHash(struct Instr_Def* pInstruction)
{
	uint_8 hashBuffer[32];
	int len = 0;
	char* pDst = (char*)&hashBuffer;
	strcpy(pDst, pInstruction->mnemonic);
	len += strlen(pInstruction->mnemonic);
	pDst += len;
	*(pDst + 0) = pInstruction->operand_types[0];
	*(pDst + 1) = pInstruction->operand_types[1];
	*(pDst + 2) = pInstruction->operand_types[2];
	*(pDst + 3) = pInstruction->operand_types[3];
	*(pDst + 4) = pInstruction->operand_types[4];
	len  += 4;
	pDst += 4;
	return hash(&hashBuffer, len);
}

void BuildInstructionTable(void) 
{
	uint_32 hash = 0;
	struct Instr_Def* pInstrTbl = &InstrTableV2;
	memset(InstrHash, 0, sizeof(InstrHash));
	uint_32 i = 0;
	uint_32 instrCount = sizeof(InstrTableV2) / sizeof(struct Instr_Def);

	for (i = 0; i < instrCount; i++, pInstrTbl++)
	{
		struct Instr_Def* pInstr = AllocInstruction();
		memcpy(pInstr, pInstrTbl, sizeof(struct Instr_Def));
		hash = GenerateInstrHash(pInstr);
		InsertInstruction(pInstr, hash);
	}
}

/* =====================================================================
	Some instruction forms require specific registers such as AX or CL.
	Demotion allows us to check the instruction table twice, once using the explicit register should it exist,
	secondly after demotion to look for a generic case.
===================================================================== */
enum op_type DemoteOperand(enum op_type op) {
	enum op_type ret = op;
	if (op == R8_AL)
		ret = R8;
	else if (op == R16_AX)
		ret = R16;
	else if (op == R32_EAX)
		ret = R32;
	else if (op == R64_RAX)
		ret = R64;
	else if (op == R8_CL)
		ret = R8;
	else if (op == R16_CX)
		ret = R16;
	else if (op == R32_ECX)
		ret = R32;
	else if (op == R64_RCX)
		ret = R64;
	return(ret);
}

enum op_type MatchOperand(struct code_info *CodeInfo, struct opnd_item op, struct expr opExpr) {
	enum op_type result;
	switch (op.type)
	{
		case OP_M:
			result = M_ANY;
			break;
		case OP_M08:
			result = M_ANY;
			break;
		case OP_M16:
			result = M_ANY;
			break;
		case OP_M32:
			result = M_ANY;
			break;
		case OP_M64:
			result = M_ANY;
			break;
		case OP_M48:
			result = M_ANY;
			break;
		case OP_M80:
			result = M_ANY;
			break;
		case OP_M128:
			result = M_ANY;
			break;
		case OP_M256:
			result = M_ANY;
			break;
		case OP_M512:
			result = M_ANY;
			break;
		case OP_SR86:
			result = R_SEG;
			break;
		case OP_SR:
			result = R_SEG;
			break;
		case OP_SR386:
			result = R_SEGE;
			break;
		case OP_RSPEC:
			result = R_RIP;
			/* If the register operand is cr0-cr8 (Parser error generates OP.type == RSPEC for these) */
			if (strcasecmp(opExpr.base_reg->string_ptr, "cr0") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "cr2") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "cr3") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "cr4") == 0)
			{
				result = R_CR;
			}
			else if (strcasecmp(opExpr.base_reg->string_ptr, "cr8") == 0)
			{
				result = R_CR8;
			}
			/* If the register operand is dr0-dr7 (Parser error generates OP.type == R_RIP for these) */
			else if (strcasecmp(opExpr.base_reg->string_ptr, "dr0") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "dr1") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "dr2") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "dr3") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "dr4") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "dr5") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "dr6") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "dr7") == 0)
			{
				result = R_DR;
			}
			break;
		case OP_K:
			result = R_K;
			break;
		case OP_RIP:
			result = R_RIP;
			/* If the register operand is cr0-cr8 (Parser error generates OP.type == R_RIP for these) */
			if (strcasecmp(opExpr.base_reg->string_ptr, "cr0") == 0 ||
			strcasecmp(opExpr.base_reg->string_ptr, "cr2") == 0 ||
			strcasecmp(opExpr.base_reg->string_ptr, "cr3") == 0 ||
			strcasecmp(opExpr.base_reg->string_ptr, "cr4") == 0 ||
			strcasecmp(opExpr.base_reg->string_ptr, "cr8") == 0)
			{
				result = R_CR;
			}
			else if (strcasecmp(opExpr.base_reg->string_ptr, "cr8") == 0)
			{
				result = R_CR8;
			}
			/* If the register operand is dr0-dr7 (Parser error generates OP.type == R_RIP for these) */
			else if (strcasecmp(opExpr.base_reg->string_ptr, "dr0") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "dr1") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "dr2") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "dr3") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "dr4") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "dr5") == 0 || 
				strcasecmp(opExpr.base_reg->string_ptr, "dr6") == 0 || 
				strcasecmp(opExpr.base_reg->string_ptr, "dr7") == 0)
			{
				result = R_DR;
			}
			break;
		case OP_AL:
			result = R8_AL;
			break;
		case OP_CL:
			result = R8_CL;
			break;
		case OP_AX:
			result = R16_AX;
			break;
		case OP_EAX:
			result = R32_EAX;
			break;
		case OP_RAX:
			result = R64_RAX;
			break;
		case OP_NONE:
			result = OP_N;
			break;
		case OP_R8:
			result = R8;
			/* If the register operand is ah,bh,ch,dh */
			if (strcasecmp(opExpr.base_reg->string_ptr, "ah") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "bh") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "ch") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "dh") == 0)
			{
				result = R8H;
			}
			/* If the register operand is r8b-r15b */
			else if (strcasecmp(opExpr.base_reg->string_ptr, "r8b") == 0 ||
					 strcasecmp(opExpr.base_reg->string_ptr, "r9b") == 0 ||
					 strcasecmp(opExpr.base_reg->string_ptr, "r10b") == 0 ||
					 strcasecmp(opExpr.base_reg->string_ptr, "r11b") == 0 ||
					 strcasecmp(opExpr.base_reg->string_ptr, "r12b") == 0 ||
					 strcasecmp(opExpr.base_reg->string_ptr, "r13b") == 0 ||
					 strcasecmp(opExpr.base_reg->string_ptr, "r14b") == 0 ||
					 strcasecmp(opExpr.base_reg->string_ptr, "r15b") == 0)
			{
				result = R8E;
			}
			else if (strcasecmp(opExpr.base_reg->string_ptr, "sil") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "dil") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "spl") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "bpl") == 0)
			{
				result = R8U;
			}
			break;
		case OP_DX:
			result = R16;
			break;
		case OP_R16:
			result = R16;
			/* If the register operand is r8w-r15w */
			if (strcasecmp(opExpr.base_reg->string_ptr, "r8w") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "r9w") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "r10w") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "r11w") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "r12w") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "r13w") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "r14w") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "r15w") == 0)
			{
				result = R16E;
			}
			break;
		case OP_R32:
			result = R32;
			/* If the register operand is r8d-r15d */
			if (strcasecmp(opExpr.base_reg->string_ptr, "r8d") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "r9d") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "r10d") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "r11d") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "r12d") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "r13d") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "r14d") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "r15d") == 0)
			{
				result = R32E;
			}
			break;
		case OP_R64:
			result = R64;
			/* If the register operand is r8-r15 */
			if (strcasecmp(opExpr.base_reg->string_ptr, "r8") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "r9") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "r10") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "r11") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "r12") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "r13") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "r14") == 0 ||
				strcasecmp(opExpr.base_reg->string_ptr, "r15") == 0)
			{
				result = R64E;
			}
			break;
		case OP_I8:
			result = IMM8;
			break;
		case OP_I16:
			result = IMM16;
			break;
		case OP_I32:
			result = IMM32;
			break;
		case OP_I64:
			result = IMM64;
			break;
		case OP_XMM:
			result = SSE128;
			/* If register xmm8-xmm15 USE AVX128 */
			/* If register xmm16-xmm31 USE AVX512_128 */
			break;
		case OP_YMM:
			result = AVX256;
			/* If register ymm16-ymm31 USE AVX512_256 */
			break;
		case OP_ZMM:
			result = AVX512;
			break;
	}
	return result;
}

struct Instr_Def* LookupInstruction(struct Instr_Def* instr) {
	uint_32           hash;
	struct Instr_Def* pInstruction = NULL;
	bool              matched      = FALSE;

	hash = GenerateInstrHash(instr);
    pInstruction = InstrHash[hash];
	while (pInstruction != NULL)
	{
		if (strcasecmp(pInstruction->mnemonic, instr->mnemonic) == 0 &&
			pInstruction->operand_types[0] == instr->operand_types[0] &&
			pInstruction->operand_types[1] == instr->operand_types[1] &&
			pInstruction->operand_types[2] == instr->operand_types[2] &&
			pInstruction->operand_types[3] == instr->operand_types[3]) {
			matched = TRUE;
			break;
		}
		pInstruction = pInstruction->next;
	}
	if (!matched)
		pInstruction = NULL;
	return pInstruction;
}

bool Require_OPND_Size_Override(struct Instr_Def* instr, struct code_info* CodeInfo)
{
	if (instr->useOSO == OP_SIZE_OVERRIDE)
	{
		if (instr->op_size == 2 && (ModuleInfo.Ofssize == USE32 || ModuleInfo.Ofssize == USE64))
			return TRUE;
		if (instr->op_size == 4 && ModuleInfo.Ofssize == USE16)
			return TRUE;
	}
	return FALSE;
}

bool Require_ADDR_Size_Override(struct Instr_Def* instr, struct code_info* CodeInfo)
{
	return FALSE;
}

bool IsValidInCPUMode(struct Instr_Def* instr)
{
	bool          result   = TRUE;
	unsigned char cpuModes = instr->validModes;

	/* Don't allow a 64bit instruction in a non 64bit segment */
	if (ModuleInfo.Ofssize != USE64 && cpuModes == X64)
		result = FALSE;

	/* Are we allowing assembly of priviledge instructions? */
	if ((instr->cpu & P_PM) > (ModuleInfo.curr_cpu & P_PM))
		result = FALSE;

	return result;
}

bool SegmentPrefixAllowed()
{
	return TRUE;
}

/* =====================================================================
  Given an input token (string) for a register name, match it and return
  the correct register number for encoding reg/rm fields.
  ===================================================================== */
unsigned char GetRegisterNo(struct asym *regTok)
{
	unsigned char regNo = 0;

	if (strcasecmp(regTok->name, "al") == 0)
		regNo = 0;
	else if (strcasecmp(regTok->name, "cl") == 0)
		regNo = 1;
	else if (strcasecmp(regTok->name, "dl") == 0)
		regNo = 2;
	else if (strcasecmp(regTok->name, "bl") == 0)
		regNo = 3;
	else if (strcasecmp(regTok->name, "ah") == 0 || strcasecmp(regTok->name, "spl") == 0)
		regNo = 4;
	else if (strcasecmp(regTok->name, "ch") == 0 || strcasecmp(regTok->name, "bpl") == 0)
		regNo = 5;
	else if (strcasecmp(regTok->name, "dh") == 0 || strcasecmp(regTok->name, "sil") == 0)
		regNo = 6;
	else if (strcasecmp(regTok->name, "bh") == 0 || strcasecmp(regTok->name, "dil") == 0)
		regNo = 7;
	else if (strcasecmp(regTok->name, "r8b") == 0)
		regNo = 8;
	else if (strcasecmp(regTok->name, "r9b") == 0)
		regNo = 9;
	else if (strcasecmp(regTok->name, "r10b") == 0)
		regNo = 10;
	else if (strcasecmp(regTok->name, "r11b") == 0)
		regNo = 11;
	else if (strcasecmp(regTok->name, "r12b") == 0)
		regNo = 12;
	else if (strcasecmp(regTok->name, "r13b") == 0)
		regNo = 13;
	else if (strcasecmp(regTok->name, "r14b") == 0)
		regNo = 14;
	else if (strcasecmp(regTok->name, "r15b") == 0)
		regNo = 15;
	else if (strcasecmp(regTok->name, "ax") == 0)
		regNo = 0;
	else if (strcasecmp(regTok->name, "cx") == 0)
		regNo = 1;
	else if (strcasecmp(regTok->name, "dx") == 0)
		regNo = 2;
	else if (strcasecmp(regTok->name, "bx") == 0)
		regNo = 3;
	else if (strcasecmp(regTok->name, "sp") == 0)
		regNo = 4;
	else if (strcasecmp(regTok->name, "bp") == 0)
		regNo = 5;
	else if (strcasecmp(regTok->name, "si") == 0)
		regNo = 6;
	else if (strcasecmp(regTok->name, "di") == 0)
		regNo = 7;
	else if (strcasecmp(regTok->name, "r8w") == 0)
		regNo = 8;
	else if (strcasecmp(regTok->name, "r9w") == 0)
		regNo = 9;
	else if (strcasecmp(regTok->name, "r10w") == 0)
		regNo = 10;
	else if (strcasecmp(regTok->name, "r11w") == 0)
		regNo = 11;
	else if (strcasecmp(regTok->name, "r12w") == 0)
		regNo = 12;
	else if (strcasecmp(regTok->name, "r13w") == 0)
		regNo = 13;
	else if (strcasecmp(regTok->name, "r14w") == 0)
		regNo = 14;
	else if (strcasecmp(regTok->name, "r15w") == 0)
		regNo = 15;
	else if (strcasecmp(regTok->name, "eax") == 0)
		regNo = 0;
	else if (strcasecmp(regTok->name, "ecx") == 0)
		regNo = 1;
	else if (strcasecmp(regTok->name, "edx") == 0)
		regNo = 2;
	else if (strcasecmp(regTok->name, "ebx") == 0)
		regNo = 3;
	else if (strcasecmp(regTok->name, "esp") == 0)
		regNo = 4;
	else if (strcasecmp(regTok->name, "ebp") == 0)
		regNo = 5;
	else if (strcasecmp(regTok->name, "esi") == 0)
		regNo = 6;
	else if (strcasecmp(regTok->name, "edi") == 0)
		regNo = 7;
	else if (strcasecmp(regTok->name, "r8d") == 0)
		regNo = 8;
	else if (strcasecmp(regTok->name, "r9d") == 0)
		regNo = 9;
	else if (strcasecmp(regTok->name, "r10d") == 0)
		regNo = 10;
	else if (strcasecmp(regTok->name, "r11d") == 0)
		regNo = 11;
	else if (strcasecmp(regTok->name, "r12d") == 0)
		regNo = 12;
	else if (strcasecmp(regTok->name, "r13d") == 0)
		regNo = 13;
	else if (strcasecmp(regTok->name, "r14d") == 0)
		regNo = 14;
	else if (strcasecmp(regTok->name, "r15d") == 0)
		regNo = 15;
	else if (strcasecmp(regTok->name, "rax") == 0)
		regNo = 0;
	else if (strcasecmp(regTok->name, "rcx") == 0)
		regNo = 1;
	else if (strcasecmp(regTok->name, "rdx") == 0)
		regNo = 2;
	else if (strcasecmp(regTok->name, "rbx") == 0)
		regNo = 3;
	else if (strcasecmp(regTok->name, "rsp") == 0)
		regNo = 4;
	else if (strcasecmp(regTok->name, "rbp") == 0)
		regNo = 5;
	else if (strcasecmp(regTok->name, "rsi") == 0)
		regNo = 6;
	else if (strcasecmp(regTok->name, "rdi") == 0)
		regNo = 7;
	else if (strcasecmp(regTok->name, "r8") == 0)
		regNo = 8;
	else if (strcasecmp(regTok->name, "r9") == 0)
		regNo = 9;
	else if (strcasecmp(regTok->name, "r10") == 0)
		regNo = 10;
	else if (strcasecmp(regTok->name, "r11") == 0)
		regNo = 11;
	else if (strcasecmp(regTok->name, "r12") == 0)
		regNo = 12;
	else if (strcasecmp(regTok->name, "r13") == 0)
		regNo = 13;
	else if (strcasecmp(regTok->name, "r14") == 0)
		regNo = 14;
	else if (strcasecmp(regTok->name, "r15") == 0)
		regNo = 15;

	else if (strcasecmp(regTok->name, "cr0") == 0)
		regNo = 0;
	else if (strcasecmp(regTok->name, "cr2") == 0)
		regNo = 2;
	else if (strcasecmp(regTok->name, "cr3") == 0)
		regNo = 3;
	else if (strcasecmp(regTok->name, "cr4") == 0)
		regNo = 4;
	else if (strcasecmp(regTok->name, "cr8") == 0)
		regNo = 8;

	else if (strcasecmp(regTok->name, "dr0") == 0)
		regNo = 0;
	else if (strcasecmp(regTok->name, "dr1") == 0)
		regNo = 1;
	else if (strcasecmp(regTok->name, "dr2") == 0)
		regNo = 2;
	else if (strcasecmp(regTok->name, "dr3") == 0)
		regNo = 3;
	else if (strcasecmp(regTok->name, "dr4") == 0)
		regNo = 4;
	else if (strcasecmp(regTok->name, "dr5") == 0)
		regNo = 5;
	else if (strcasecmp(regTok->name, "dr6") == 0)
		regNo = 6;
	else if (strcasecmp(regTok->name, "dr7") == 0)
		regNo = 7;

	else if (strcasecmp(regTok->name, "cs") == 0)
		regNo = 1;
	else if (strcasecmp(regTok->name, "ds") == 0)
		regNo = 3;
	else if (strcasecmp(regTok->name, "es") == 0)
		regNo = 0;
	else if (strcasecmp(regTok->name, "fs") == 0)
		regNo = 4;
	else if (strcasecmp(regTok->name, "gs") == 0)
		regNo = 5;
	else if (strcasecmp(regTok->name, "ss") == 0)
		regNo = 2;

	return regNo;

}

/* =====================================================================
  Build up instruction ModRM byte.
  ===================================================================== */
unsigned char BuildModRM(unsigned char modRM, struct Instr_Def* instr, struct expr opnd[4])
{
	if (instr->flags & F_MODRM)			// Only if the instruction requires a ModRM byte, else return 0.
	{
		//  7       5           2       0
		// +---+---+---+---+---+---+---+---+
		// |  mod  |    reg    |    rm     |
		// +---+---+---+---+---+---+---+---+
		// MODRM.mod (2bits) == b11, register to register direct, otherwise register indirect.
		// MODRM.reg (3bits) == 3bit opcode extension, 3bit register value as source. REX.R, VEX.~R can 1bit extend this field.
		// MODRM.rm  (3bits) == 3bit direct or indirect register operand, optionally with displacement. REX.B, VEX.~B can 1bit extend this field.
		if (instr->flags & F_MODRM_REG && instr->op_dir == REG_DST)
		{
			// Build REG field as destination.
			modRM |= (GetRegisterNo(opnd[0].base_reg) & 0x07) << 3;
		}
		else if (instr->flags & F_MODRM_REG && instr->op_dir == RM_DST)
		{
			// Build REG field as source.
			modRM |= (GetRegisterNo(opnd[1].base_reg) & 0x07) << 3;
		}
		if (instr->flags & F_MODRM_RM && instr->op_dir == REG_DST)
		{
			// Build RM field as source.
			modRM |= (GetRegisterNo(opnd[1].base_reg) & 0x07);
		}
		else if (instr->flags & F_MODRM_RM && instr->op_dir == RM_DST)
		{
			// Build RM field as destination.
			modRM |= (GetRegisterNo(opnd[0].base_reg) & 0x07);
		}
	}
	return modRM;
}

/* =====================================================================
  Build up instruction REX prefix byte.
  ===================================================================== */
unsigned char BuildREX(unsigned char RexByte, struct Instr_Def* instr, struct expr opnd[4])
{
	// Only if the identified instruction requires a REX prefix.
	if (((uint_32)instr->flags & (uint_32)REX) != 0)
	{
		/* +---+---+---+---+---+---+---+---+ */
		/* | 0 | 1 | 0 | 0 | W | R | X | B | */
		/* +---+---+---+---+---+---+---+---+ */
		// W == 1=64bit operand size, else default operand size used (usually 32bit).
		// R == extend ModRM.reg
		// X == extend SIB.index
		// B == extend ModRM.rm or SIB.base

		RexByte |= 0x40;		// Fixed base value for REX prefix.
		
		if ((instr->flags & (uint_32)REXB) != 0)
			RexByte |= 0x01;
		if ((instr->flags & (uint_32)REXX) != 0)
			RexByte |= 0x02;
		if ((instr->flags & (uint_32)REXR) != 0)
			RexByte |= 0x04;
		if ((instr->flags & (uint_32)REXW) != 0)
			RexByte |= 0x08;

	}
	return RexByte;
}

/* =====================================================================
  Build up instruction SIB, ModRM and REX bytes for memory operand.
  ===================================================================== */
void BuildMemoryEncoding(unsigned char* pmodRM, unsigned char* pSIB, unsigned char* pREX, 
	                     unsigned int* dispSize, int* pDisp, struct Instr_Def* instr, struct expr opExpr[4]) 
{
	unsigned char sibScale = 0;
	unsigned char retType = 0;

	if (instr->operand_types[0] == M_ANY)
		retType = 1;
	if (instr->operand_types[instr->memOpnd] == M_ANY)
		retType = 2;

	// Does the memory address require a displacement?
	// Either user specified, or RIP relative addressing mandates it.
	if (opExpr[instr->memOpnd].value != 0 || (ModuleInfo.Ofssize == USE64 && opExpr[instr->memOpnd].base_reg->token == T_RIP))
	{
		// Is it 8bit or 16/32bit (RIP only allows 32bit)?
		if (opExpr[instr->memOpnd].value >= -128 && opExpr[instr->memOpnd].value <= 127 && opExpr[instr->memOpnd].base_reg->token != T_RIP)
		{
			*dispSize = 1;
			*pmodRM |= MODRM_DISP8;
		}
		else
		{
			if (ModuleInfo.Ofssize == USE16)
				*dispSize = 2;	// 16bit addressing.
			else
				*dispSize = 4;	// 32bit or 64bit addressing.
			*pmodRM |= MODRM_DISP;
		}
		*pDisp = opExpr[instr->memOpnd].value;
	}

	//  scale index    base
	// +--+--+--+--+--+--+--+--+
	// | 7   | 5      | 2      |
	// +--+--+--+--+--+--+--+--+
	// SIB.scale == 0,1,2,3 = (1,2,4,8) scale factor.
	// SIB.index == index register to use, extended via REX.X or VEX.~X
	// SIB.base  == base register to use, extended via REX.B or VEX.~B
	if (opExpr[instr->memOpnd].scale > 1)
	{
		switch (opExpr[instr->memOpnd].scale)
		{
		case 1:
			sibScale = 0;
			break;
		case 2:
			sibScale = 1;
			break;
		case 4:
			sibScale = 2;
			break;
		case 8:
			sibScale = 3;
			break;
		}
		*pSIB |= (sibScale << 6);
	}

}

ret_code CodeGenV2(const char* instr, struct code_info *CodeInfo, uint_32 oldofs, uint_32 opCount, struct expr opExpr[4])
{
	ret_code retcode = NOT_ERROR;
	struct Instr_Def instrToMatch;
	struct Instr_Def* matchedInstr = NULL;
	uint_32 i = 0;
	unsigned char opcodeByte = 0;
	unsigned char rexByte    = 0;
	unsigned char modRM      = 0;
	unsigned char sib        = 0;
	unsigned int  dispSize   = 0;
	
	union
	{
		int displacement32;
		unsigned char byte[4];
	} displacement;

	union
	{
		uint_64 full;
		unsigned char byte[8];
	} immValue;

	//return EMPTY; // stubbed out for now

	memset(&instrToMatch, 0, sizeof(struct Instr_Def));
	instrToMatch.mnemonic      = instr;		/* Instruction mnemonic string */
	instrToMatch.operand_count = opCount;	/* Number of operands */
	for (i = 0; i < opCount; i++)			/* Translate to CodeGenV2 operand types */
		instrToMatch.operand_types[i] = MatchOperand(CodeInfo, CodeInfo->opnd[i], opExpr[i]); 

	/* Lookup the instruction */
	matchedInstr = LookupInstruction(&instrToMatch);

	/* Try once again with demoted operands */
	if (matchedInstr == NULL)
	{
		for (i = 0; i < opCount; i++)
			instrToMatch.operand_types[i] = DemoteOperand(instrToMatch.operand_types[i]);
		matchedInstr = LookupInstruction(&instrToMatch);
	}

	/* We don't have it in CodeGenV2 so fall-back */
	if(matchedInstr == NULL)
		retcode = EMPTY;

	/* Proceed to generate the instruction */
	else
	{
		//----------------------------------------------------------
		// Add line number debugging info.
		//----------------------------------------------------------
		if (Options.line_numbers)
			AddLinnumDataRef(get_curr_srcfile(), GetLineNumber());

		//----------------------------------------------------------
		// Check if instruction is valid in current mode.
		//----------------------------------------------------------
		if (!IsValidInCPUMode(matchedInstr))
		{
			EmitError(INSTRUCTION_OR_REGISTER_NOT_ACCEPTED_IN_CURRENT_CPU_MODE);
			return;
		}
	
		//----------------------------------------------------------
		// Build Memory Encoding Format.
		// -> When an indirect memory operand is used, this will build
		// -> up the respective rex, modrm and sib values.
		// Alternatively directly encode the modRM, rex and SIB values.
		//----------------------------------------------------------
		/* If the matched instruction requires processing of a memory address */
		if(matchedInstr->memOpnd != NO_MEM)
			BuildMemoryEncoding(&modRM, &sib, &rexByte, 
				                &dispSize, &displacement, matchedInstr, opExpr);	/* This could result in modifications to REX, modRM and SIB bytes */
		modRM   |= BuildModRM(matchedInstr->modRM, matchedInstr, opExpr);			/* Modify the modRM value for any non-memory operands */
		rexByte |= BuildREX(rexByte, matchedInstr, opExpr);							/* Modify the REX prefix for non-memory operands/sizing */
		
		//----------------------------------------------------------
		// Output Segment Prefix if required and allowed.
		//----------------------------------------------------------

		//----------------------------------------------------------
		// Check if address or operand size override prefixes are required.
		//----------------------------------------------------------
		if (Require_OPND_Size_Override(matchedInstr, CodeInfo))
			OutputCodeByte(OP_SIZE_OVERRIDE);

		if (Require_ADDR_Size_Override(matchedInstr, CodeInfo))
			OutputCodeByte(ADDR_SIZE_OVERRIDE);

		// Output FPU FWAIT if required.

		//----------------------------------------------------------
		// Output mandatory prefix.
		//----------------------------------------------------------
		if (matchedInstr->mandatory_prefix != 0)
		{
			
		}

		//----------------------------------------------------------
		// Output VEX prefix if required.
		//----------------------------------------------------------

		//----------------------------------------------------------
		// Output REX prefix if required.
		//----------------------------------------------------------
		if (rexByte != 0)
			OutputCodeByte(rexByte);

		//----------------------------------------------------------
		// Output opcode byte(s).
		//----------------------------------------------------------
		// Single opcode byte with embedded register.
		if ((matchedInstr->flags & F_OPCODE_REG) != 0)
		{
			opcodeByte = matchedInstr->opcode[0];
			opcodeByte += (GetRegisterNo(opExpr[0].base_reg) & 0x07);
			OutputCodeByte(opcodeByte);
		}
		// Normal opcode byte sequence.
		else
		{
			for (i = 0; i < matchedInstr->opcode_bytes; i++)
				OutputCodeByte(matchedInstr->opcode[i]);
		}

		//----------------------------------------------------------
		// Output ModR/M
		//----------------------------------------------------------
		if (modRM != 0)
			OutputCodeByte(modRM);

		//----------------------------------------------------------
		// Output SIB
		//----------------------------------------------------------
		if (sib != 0)
			OutputCodeByte(sib);

		//----------------------------------------------------------
		// Output Displacement.
		//----------------------------------------------------------
		if (dispSize == 1)
			OutputCodeByte(displacement.byte[0]);
		else if (dispSize == 4)
		{
			for (i = 0; i < 4; i++)
				OutputCodeByte(displacement.byte[i]);
		}

		//----------------------------------------------------------
		// Output Immediate Data.
		//----------------------------------------------------------
		if (matchedInstr->immOpnd != NO_IMM)
		{
			immValue.full = CodeInfo->opnd[matchedInstr->immOpnd].data64;
			//----------------------------------------------------------
			// Validate Immediate (type and magnitude).
			//----------------------------------------------------------

			for (i = 0; i < matchedInstr->op_size; i++)
				OutputCodeByte(immValue.byte[i]);
		}
	}

	// Write out listing.
	if (retcode == NOT_ERROR)
	{
		if (CurrFile[LST])
			LstWrite(LSTTYPE_CODE, oldofs, NULL);
	}

	return retcode;
}

//  /c /DX86_64 /DWINDOWS64 -win64 /DARCH=SKX -Fl=out.lst /Foamd64\zr4dwpn_skx.obj zr4dwpn.asm
//  d:\foo2