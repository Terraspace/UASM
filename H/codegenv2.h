#pragma once

#include "globals.h"
#include "expreval.h"

/* This order must remain as-is! */
enum instr_group {
	GP0,		/* i86+ encoding group  */
	GP1,		/* i286+ encoding group */
	GP2,		/* i386+ encoding group */
	GP3,        /* 64bit only */
	SSE0,       /* SSE */
	VEX0,
	EVEX0,
	MVEX0,
	FP0,
	FP1
};

enum seg_prefix {
	PREFIX_ES = 0x26,
	PREFIX_CS = 0x2E,
	PREFIX_SS = 0x36,
	PREFIX_DS = 0x3E,
	PREFIX_FS = 0x64,
	PREFIX_GS = 0x65
};

enum legacy_prefix {
	LOCK  = 0xf0,
	REPNE = 0xf2,
	REPNZ = 0xf2,
	REP   = 0xf3,
	REPE  = 0xf3,
	REPZ  = 0xf3,
	BND   = 0xf2,
	FWAIT = 0x00
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
	/* Special CL/CX/ECX/RCX only register */
	R8_CL,
	R16_CX,
	R32_ECX,
	R64_RCX,
	/* 8 - 64bit sized general purpose registers (64bit mode only) --> EXCLUDING high byte access (AH,BH,CH,DH) and SIL,DIL,BPL,SPL */
	R8E,
	R16E,
	R32E,
	R64E,
	/* control and debug registers */
	R_CR8,
	R_CR,
	R_DR,
	/* high byte access registers (AH,BH,CH,DH) */
	R8H,
	/* Uniform low byte 64bit registers (SIL,DIL,BPL,SPL) */
	R8U,
	/* FPU 32 - 80bit sized registers */
	F32,
	F64,
	F80,
	/* segment registers (CS,DS,ES,SS) */
	R_SEG,
	/* 386+ segment register (FS,GS) */
	R_SEGE,
	/* MMX registers */
	MMX64,

	/* x86 XMM registers (xmm0-xmm7)  */
	R_XMM,
	/* x64 XMM registers (xmm8-xmm15) */
	R_XMME,
	/* x86 YMM registers (ymm0-ymm7)  */
	R_YMM,
	/* x64 YMM registers (ymm8-ymm15) */
	R_YMME,

	/* AVX 512 registers (zmm0-31) */
	AVX512,
	AVX512_128,
	AVX512_256,
	/* RIP Register and K Registers */
	R_RIP,
	R_K,
	/* Generic memory operands (8-64bit) */
	M8,
	M16,
	M32,
	M64,
	M48,
	M80,
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
	IMM,
	IMM8,
	IMM16,
	IMM32,
	IMM64, /* 64bit ONLY immediate */	
};

#define NO_FLAGS     (0)
#define ALLOW_REP    (1<<0)		/* Instruction allows use of rep prefix */
#define ALLOW_LOCK   (1<<1)		/* Instruction allows use of lock prefix */
#define IS_BRANCH    (1<<2)		/* Instruction is a branch */
#define ALLOW_BND    (1<<3)		/* Instruction allows a BND prefix */
#define REX          (1<<4)		/* Instruction requires a REX prefix */
#define REXW         (1<<5)		/* Instruction uses REX.W to extend it's default mode to 64bit */
#define REXR         (1<<6)		/* Instruction uses REX.R to extend ModRM.reg */
#define REXB         (1<<7)		/* Instruction uses REX.B to extend ModRM.rm */
#define REXX         (1<<8)		/* Instruction uses REX.X to extend SIB.index */
#define F_MODRM      (1<<9)		/* Instruction requires a ModRM byte */
#define F_MODRM_REG  (1<<10)	/* Instruction uses ModRM.reg */
#define F_MODRM_RM   (1<<11)	/* Instruction uses ModRM.rm */
#define F_SIB        (1<<12)	/* Instruction requires a SIB byte */
#define F_ADDST      (1<<13)	/* ST(n) register number is added to opcode byte */
#define F_OPCODE_REG (1<<14)	/* Register value is encoded in low 3 bits of opcode byte + REX.b */
#define ALLOW_SEG    (1<<15)	/* Instruction permits a segment override prefix */
#define VEX          (1<<16)
#define VEX_2BYTE    (1<<17)
#define VEX_3BYTE    (1<<18)
#define VEX_NR       (1<<19)
#define EVEX         (1<<20)
#define DSPW         (1<<21)	/* Instruction requires a machine-word sized displacement always */
#define ALLOW_SEGX   (1<<22)	/* movabs allows encoding of segment register other than fs/gs, this indicates that condition */
#define REXP_MEM     (1<<23)	/* Instruction promoted to 64bit special mode if specified memory operand is qword sized */
#define FWAIT        (1<<24)
#define NO_FWAIT     (1<<25)
#define NO_MEM_REG   (1<<26)	/* This indicates that only an absolute or displacement only memory address is supported */
#define NO_PREFIX    (1<<27)    /* Manual refers to this as NP (66/f2/f3 prefixes prohibited) */

/* Required ASO/OSO flags */
#define OP_SIZE_OVERRIDE   0x66
#define ADDR_SIZE_OVERRIDE 0x67

/* Valid CPU modes */
#define X16 0x01
#define X32 0x02
#define X64 0x04

/* mandatory_prefix -> Which mandatory prefix sequence is used by the instruction */
#define NO_PREFIX  0
#define PFX_0xF    1

/* op_dir -> operation direction */
#define REG_DST  0
#define RM_DST   1
#define REG_SRC1 2
#define RM_SRC1  3
#define NO_DST   4

/* immOpnd -> Which operand contains an immediate? */
#define NO_IMM     4
#define IMM_OPND_0 0
#define IMM_OPND_1 1
#define IMM_OPND_2 2
#define IMM_OPND_3 3

/* memOpnd -> Which operand contains an indirect memory address? */
#define NO_MEM     5
#define MEM_OPND_0 0
#define MEM_OPND_1 1
#define MEM_OPND_2 2
#define MEM_OPND_3 3
#define MEM_ABS_0  8+0	/* Used for special moffset type memory operands */
#define MEM_ABS_1  8+1	/* Used for special moffset type memory operands */
#define MEM_ABS_2  8+2	/* Used for special moffset type memory operands */
#define MEM_ABS_3  8+3	/* Used for special moffset type memory operands */

/* ModRM Modes */
#define NO_MOD      0x00
#define MOD_REG_REG 0xc0
#define MOD_REG_MEM 0x00
#define MOD_MEM_REG 0x00
#define MOD_MEM_IMM 0x00
#define MOD_REG_IMM 0xc0

#define MODRM_DISP8 0x40	/* ModRM mode for 8bit displacement        */
#define MODRM_DISP  0x80	/* ModRM mode for 16bit/32bit displacement */

/* Memory Address Encoding Info */
#define MEMF_MODRM (1<<0)	/* Memory address requires modrm byte */
#define MEMF_SIB   (1<<1)	/* Memory address requires sib byte */
#define MEMF_DSP   (1<<2)	/* Memory address requires displacement (even if 0) */
#define MEMF_DSP32 (1<<3)	/* Memory address requires 32bit displacement (even if 0) */
#define NO_ENCODE  (1<<4)	/* This mode is not encodable! */

/* ModRM values */
#define SIB_ONLY  0x04		/* ModRM value when Encoding uses SIB for both base and index */
#define MRM_AX    0x00
#define MRM_CX    0x01
#define MRM_DX    0x02
#define MRM_BX    0x03
#define MRM_SP    0x04
#define MRM_BP    0x05
#define MRM_SI    0x06
#define MRM_DI    0x07
#define MRM_R8    0x00
#define MRM_R9    0x01
#define MRM_R10   0x02
#define MRM_R11   0x03
#define MRM_R12   0x04
#define MRM_R13   0x05
#define MRM_R14   0x06
#define MRM_R15   0x07
#define MRM_RIP   0x05
#define MRM_ABS   0x04

/* SIB values */
#define NO_SIB       0x00		/* Encoding has no SIB value */
#define SIB_BASE_AX  0x00
#define SIB_BASE_CX  0x01
#define SIB_BASE_DX  0x02
#define SIB_BASE_BX  0x03
#define SIB_BASE_SP  0x04
#define SIB_BASE_BP  0x05
#define SIB_BASE_SI  0x06
#define SIB_BASE_DI  0x07
#define SIB_BASE_R8  0x00
#define SIB_BASE_R9  0x01
#define SIB_BASE_R10 0x02
#define SIB_BASE_R11 0x03
#define SIB_BASE_R12 0x04
#define SIB_BASE_R13 0x05
#define SIB_BASE_R14 0x06
#define SIB_BASE_R15 0x07
#define SIB_BASE_RIP 0x05

#define SIB_IDX_AX  (0x00) << 3
#define SIB_IDX_CX  (0x01) << 3
#define SIB_IDX_DX  (0x02) << 3
#define SIB_IDX_BX  (0x03) << 3
#define SIB_IDX_SP  (0x04) << 3
#define SIB_IDX_BP  (0x05) << 3
#define SIB_IDX_SI  (0x06) << 3
#define SIB_IDX_DI  (0x07) << 3
#define SIB_IDX_R8  (0x00) << 3
#define SIB_IDX_R9  (0x01) << 3
#define SIB_IDX_R10 (0x02) << 3
#define SIB_IDX_R11 (0x03) << 3
#define SIB_IDX_R12 (0x04) << 3
#define SIB_IDX_R13 (0x05) << 3
#define SIB_IDX_R14 (0x06) << 3
#define SIB_IDX_R15 (0x07) << 3
#define SIB_IDX_RIP (0x05) << 3

struct Mem_Def {
	unsigned char  modRM;
	unsigned char  flags;
	unsigned char  SIB;
};

struct Instr_Def {
	const char*       mnemonic;
	char              operand_count;
	enum op_type      operand_types[5];
	enum instr_group  group;
	uint_32			  flags;
	unsigned char     opcode_bytes;
	unsigned char     opcode[4];
	unsigned char     op_size;			/* Size in bytes of operation */
	unsigned char     modRM;
	unsigned char     SIB;		
	unsigned char     useOSO;			/* Must use Operand Size Override when required */
	unsigned char     useASO;			/* Must use Address Size Override when required */
	unsigned char     validModes;		/* Valid CPU modes */
	unsigned char     op_dir;			/* ModRM direction Reg->RM or RM->Reg */
	unsigned char     mandatory_prefix;	/* Mandatory encoding prefix bytes */
	unsigned char     immOpnd;			/* Which operand is an immediate ? (1-4) */
	unsigned char     memOpnd;          /* Which operand is a memory address ? (1-4) */
	unsigned short    cpu;              /* Minimum CPU supported */
	unsigned int      hash;
	struct Instr_Def* next;
};

/* Public data */
extern struct Instr_Def InstrTableV2[];

/* Public functions */
extern void     BuildInstructionTable(void);
extern ret_code CodeGenV2(const char* instr, struct code_info *CodeInfo, uint_32 oldofs, uint_32 opCount, struct expr opExpr[4]);

/* Private functions */
enum op_type      DemoteOperand(enum op_type op);
void              InsertInstruction(struct Instr_Def* pInstruction, uint_32 hash);
struct Instr_Def* AllocInstruction();
uint_32           GenerateInstrHash(struct Instr_Def* pInstruction);
struct Instr_Def* LookupInstruction(struct Instr_Def* instr, bool memReg);
enum op_type      MatchOperand(struct code_info *CodeInfo, struct opnd_item op, struct expr opExpr);

bool Require_OPND_Size_Override(struct Instr_Def* instr, struct code_info* CodeInfo);
bool Require_ADDR_Size_Override(struct Instr_Def* instr, struct code_info* CodeInfo);
bool IsValidInCPUMode(struct Instr_Def* instr);

unsigned char BuildModRM(unsigned char modRM, struct Instr_Def* instr, struct expr opnd[4], bool* needRM, bool* needSIB);	/* Build instruction ModRM byte */
unsigned char BuildREX(unsigned char RexByte, struct Instr_Def* instr, struct expr opnd[4]);								/* Build REX prefix byte        */
void          BuildVEX();																									/* Build VEX prefix bytes       */
int           BuildMemoryEncoding(unsigned char* pmodRM, unsigned char* pSIB, unsigned char* pREX, bool* needRM, bool* needSIB,
	                              unsigned int* dispSize, int* pDisp, struct Instr_Def* instr, struct expr opExpr[4]);
unsigned char GetRegisterNo(struct asm_tok *regTok);												/* Get Register Encoding Number from Token */
