#pragma once

#include "globals.h"

enum instr_group {
	GP0,
	VEX0,
	EVEX0,
	MVEX0
};

enum op_type {
	/* Unused operand */
	OP_N,
	/* 8 - 64bit sized general purpose registers */
	R8,
	R16,
	R32,
	R64,
	/* Special AL/AX/EAX/RAX only register */
	R8_AL,
	R16_AX,
	R32_EAX,
	R64_RAX,
	/* 8 - 64bit sized general purpose registers (64bit mode only), including uniform sil/dil/extended EXCLUDING high byte access (AH,BH,CH,DH) */
	R8E,
	R16E,
	R32E,
	R64E,
	/* control and debug registers */
	CR,
	DR,
	/* FPU 32 - 80bit sized registers */
	F32,
	F64,
	F80,
	/* segment registers */
	SEG_REG,
	/* MMX registers */
	MMX64,
	/* SSE registers (xmm0-xmm7) */
	SSE128,
	/* AVX 128 (xmm0-xmm15) or 256bit (ymm0-ymm15) registers */
	AVX128,
	AVX256,
	/* AVX 512 registers (zmm0-31) */
	AVX512,
	/* Generic memory operands (8-64bit) */
	M8,
	M16,
	M32,
	M64,
	/* Memory operands (8-64 bit unsigned) */
	M8UINT,
	M16UINT,
	M32UINT,
	M64UINT,
	/* Memory operands (8-64 bit signed) */
	M8SINT,
	M16SINT,
	M32SINT,
	M64SINT,
	/* Memory operands - Floating point scalar */
	M32FLOAT,
	M64FLOAT,
	/* Memory operands SSE, AVX, AVX512 */
	M128,
	M256,
	M512,
	M_ANY,
	/* Immediate operand (8-64bit) */
	IMM8,
	IMM16,
	IMM32,
	IMM64
};

#define NO_FLAGS   (0)
#define ALLOW_REP  (1<<0)
#define ALLOW_LOCK (1<<1)
#define IS_BRANCH  (1<<2)
#define ALLOW_BND  (1<<3)
#define REX        (1<<4)
#define REXW       (1<<5)

#define OP_SIZE_OVERRIDE   0x66
#define ADDR_SIZE_OVERRIDE 0x67

struct Instr_Def {
	const char*       mnemonic;
	char              operand_count;
	enum op_type      operand_types[5];
	enum instr_group  group;
	unsigned int      flags;
	unsigned char     opcode_bytes;
	unsigned char     opcode0;
	unsigned char     opcode1;
	unsigned char     opcode2;
	unsigned char     opcode3;
	unsigned char     useOSO;
	unsigned char     useASO;
	unsigned int      hash;
	struct Instr_Def* next;
};

/* Public data */
extern struct Instr_Def InstrTableV2[];

/* Public functions */
extern void BuildInstructionTable(void);
extern ret_code CodeGenV2(struct code_info *CodeInfo, uint_32 oldofs);

/* Private functions */
void InsertInstruction(struct Instr_Def* pInstruction, uint_32 hash);
struct Instr_Def* AllocInstruction();
uint_32 GenerateInstrHash(struct Instr_Def* pInstruction);

