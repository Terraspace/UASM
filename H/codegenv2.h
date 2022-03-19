#pragma once

#include "globals.h"
#include "expreval.h"

/* This order must remain as-is! */
enum instr_group {
	GP0,		/* i86+ encoding group  */
	GP1,		/* i286+ encoding group */
	GP2,		/* i386+ encoding group */
	GP3,        /* 64bit only */
	GP4,        /* 32bit only */
	SSE0,       /* SSE */
	AVX0,
	AVX1,
	EVX0,
	MVX0,
	FP0,
	FP1,
	MMX0,
	EVX1
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
	FWAIT = 0x9b
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
	/* Special DX only register */
	R16_DX,
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
	/* ANY XMM register (used as a demoted type for 3 opnd forms) */
	R_XMM_ANY,
	/* x86 YMM registers (ymm0-ymm7)  */
	R_YMM,
	/* x64 YMM registers (ymm8-ymm15) */
	R_YMME,
	/* ANY YMM register (used as a demoted type for 3 opnd forms) */
	R_YMM_ANY,
	/* AVX 512 registers (zmm0-31) */
	R_ZMM,

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
    IMM48,
	IMM64, /* 64bit ONLY immediate */	
	R_STI,
	R_ST0,
	R_ST
};

#define NO_FLAGS      (0)
#define ALLOW_REP     (1<<0)	/* Instruction allows use of rep prefix */
#define ALLOW_LOCK    (1<<1)	/* Instruction allows use of lock prefix */
#define IS_BRNCH      (1<<2)	/* Instruction is a branch */
#define ALLOW_BND     (1<<3)	/* Instruction allows a BND prefix */
#define REX           (1<<4)	/* Instruction requires a REX prefix */
#define REXW          (1<<5)	/* Instruction uses REX.W to extend it's default mode to 64bit */
#define REXR          (1<<6)	/* Instruction uses REX.R to extend ModRM.reg */
#define REXB          (1<<7)	/* Instruction uses REX.B to extend ModRM.rm */
#define REXX          (1<<8)	/* Instruction uses REX.X to extend SIB.index */
#define F_MODRM       (1<<9)	/* Instruction requires a ModRM byte */
#define F_MODRM_REG   (1<<10)	/* Instruction uses ModRM.reg */
#define F_MODRM_RM    (1<<11)	/* Instruction uses ModRM.rm */
#define F_SIB         (1<<12)	/* Instruction requires a SIB byte */
#define F_ADDST       (1<<13)	/* ST(n) register number is added to opcode byte */
#define F_OPCODE_REG  (1<<14)	/* Register value is encoded in low 3 bits of opcode byte + REX.b */
#define F_OPCODE2_REG (1<<15)   /* Register value is encoded in low 3 bits of second opcode  */
#define F_OPCODE_REG2 (1<<16)   /* Register value is encoded in low 3 bits of second opcode  */
#define ALLOW_SEG     (1<<17)	/* Instruction permits a segment override prefix */
#define DSPW          (1<<18)	/* Instruction requires a machine-word sized displacement always */
#define ALLOW_SEGX    (1<<19)	/* movabs allows encoding of segment register other than fs/gs, this indicates that condition */
#define REXP_MEM      (1<<20)	/* Instruction promoted to 64bit special mode if specified memory operand is qword sized */
#define ALLOW_FWAIT   (1<<21)
#define NO_FWAIT      (1<<22)
#define NO_MEM_REG    (1<<23)	/* This indicates that only an absolute or displacement only memory address is supported */
#define NO_PREFIX     (1<<24)   /* Manual refers to this as NP (66/f2/f3 prefixes prohibited) */
#define IMM8_ONLY     (1<<25)	/* The instruction entry assume immediates match the opsize, however some instructions use ONLY an imm8 */
#define EREX          (1<<26)	/* The instruction is extended with a REX prefix only if the src/dst register no > 7 */
#define SRCHDSTL      (1<<27)	/* Some instructions have an optimised encodable form, ie: vmovaps by using a different opcode with swapped reg, rm dst and this flag limits instruction search for these */
#define OPCODE_EXT    (1<<28)	/* The Mod RM field uses only the RM portion, the Reg field contains an opcode extension value as noted /digit in the Intel manuals */
#define F_OPCODE2_STI (1<<29)

/* VEX flags */
#define NO_VEX		 (0)
#define VEX          (1<<0)		/* Instruction requires a VEX prefix */
#define VEX_WIG      (1<<1)		/* Instruction can use C5h(2byte) form (if no VEX.mmmmm) or VEX.W is ignored in C4H(3byte) form */
#define VEX_W0       (1<<2)     /* VEX.W = 0, extended opcode bit, or promotion to 64bit of gp register or memory operand */
#define VEX_W1       (1<<3)		/* "" */
#define VEX_66		 (1<<4)
#define VEX_F2       (1<<5)
#define VEX_F3       (1<<6)
#define VEX_0F		 (1<<7)
#define VEX_0F3A     (1<<8)
#define VEX_0F38     (1<<9)
#define VEX_LIG      (1<<10)
#define VEX_NDS      (1<<11)	/* Specifies VEX.vvvv is valid for encoding of register operand NDS encodes first source */
#define VEX_NDD      (1<<12)    /* NDD encode destination not encodable in ModR/M:reg field */
#define VEX_DDS      (1<<13)	/* DDS encode the second source register in 3-op form when first source overwritten by result */
#define VEX_R		 (1<<14)
#define VEX_B        (1<<15)
#define VEX_X        (1<<16)
#define VEX_DUP_NDS  (1<<17)	/* We allow special 2 opnd vex forms which are automatically promoted to 3 with duplicate destination and first source */
#define VEX_2OPND    (1<<18)	/* This is just for clarity sake but has the same effect of using a 2 opnd form for modrm+sib calculations as a DUP_NDS */
#define VEX_VSIB     (1<<19)	/* Instruction uses VSIB addressing */
#define VEX_4OPND    (1<<20)	/* Special 4 opnd form where final register is immediate-encoded */
#define VEX_3RD_OP   (1<<21)	/* Some VEX encoded instructions put the 3rd operand into the VEX prefix - functionality equivalent to the above */
#define EVEX         (1<<22)	/* Does this VEX instruction have an extended EVEX form available ? */

/* EVEX flags */
#define NO_EVEX      (0)
#define EVEX_ONLY    (1<<0)		/* Instruction can ONLY be encoded as an EVEX instruction */
#define EVEX_NR      (1<<1)
#define EVEX_W0      (1<<2)
#define EVEX_W1      (1<<3)
#define EVEX_BRD     (1<<4)		/* EVEX encoded instruction allows broadcast flags {1to2},{1to4},{1to8},{1to16}*/
#define EVEX_MASK    (1<<5)		/* EVEX encoded instruction allows a k opmask */
#define EVEX_Z       (1<<6)		/* EVEX encoded instructions allows a {z} mask */
#define EVEX_SAE     (1<<7)		/* EVEX encoded instruction allows SAE flag */
#define EVEX_RND     (1<<8)		/* EVEX encoded instruction allows rounding mode specifier */
#define EVEX_COMP8   (1<<9)		/* EVEX encoded instruction requires comp8 displacement */
#define EVEX_K       (1<<10)	/* {kN} mask register is mandatory */
#define EVEX_VSIB    (1<<11)	/* EVEX instruction uses VSIB and may require V' extension */

/* Required ASO/OSO flags */
#define OP_SIZE_OVERRIDE   0x66
#define ADDR_SIZE_OVERRIDE 0x67

/* Valid CPU modes */
#define X16 0x01
#define X32 0x02
#define X64 0x04

/* mandatory_prefix -> Which mandatory prefix sequence is used by the instruction */
#define PFX_0xF     1
#define PFX_0xF3    2
#define PFX_0x66F   3
#define PFX_0x66F38 4
#define PFX_0x66F3A 5
#define PFX_0xF30F  6
#define PFX_0xF20F  7
#define PFX_0x0F38  8
#define PFX_0xF3F38 9
#define PFX_0xF2F38 10

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
	uint_32			  vexflags;
	uint_32			  evexflags;
	unsigned char     op_elements;		/* Number of elements effected by operation */
	unsigned char     opcode_bytes;
	unsigned char     opcode[4];
	unsigned char     op_size;			/* Size in bytes of operation */
	unsigned char     srcidx;			/* Which operand is the final source (IE: Not NDS) */
	unsigned char     modRM;
	unsigned char     SIB;		
	unsigned char     useOSO;			/* Must use Operand Size Override when required */
	unsigned char     useASO;			/* Must use Address Size Override when required */
	unsigned char     validModes;		/* Valid CPU modes */
	unsigned char     op_dir;			/* ModRM direction Reg->RM or RM->Reg */
	uint_32           mandatory_prefix;	/* Mandatory encoding prefix bytes */
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
struct Instr_Def* LookupInstruction(struct Instr_Def* instr, bool memReg, unsigned char encodeMode, 
	                                int srcRegNo, int dstRegNo, struct code_info *CodeInfo);
enum op_type      MatchOperand(struct code_info *CodeInfo, struct opnd_item op, struct expr opExpr);

bool Require_OPND_Size_Override(struct Instr_Def* instr, struct code_info* CodeInfo);
bool Require_ADDR_Size_Override(struct Instr_Def* instr, struct code_info* CodeInfo);
bool IsValidInCPUMode(struct Instr_Def* instr);

unsigned char BuildModRM(unsigned char modRM, struct Instr_Def* instr, struct expr opnd[4], bool* needRM, bool* needSIB,
						 bool isVEX);																						/* Build instruction ModRM byte */
unsigned char BuildREX(unsigned char RexByte, struct Instr_Def* instr, struct expr opnd[4]);								/* Build REX prefix byte        */
void          BuildVEX(bool* needVex, unsigned char* vexSize, unsigned char* vexBytes, 
	                   struct Instr_Def* instr, struct expr opnd[4], bool needB, bool needX, uint_32 opCount);				/* Build VEX prefix bytes       */
void          BuildEVEX(bool* needEvex, unsigned char* evexBytes, struct Instr_Def* instr, struct expr opnd[4],
						bool needB, bool needX, bool needRR, uint_32 opCount, struct code_info* CodeInfo);					/* Build EVEX prefix bytes      */
int           BuildMemoryEncoding(unsigned char* pmodRM, unsigned char* pSIB, unsigned char* pREX, bool* needRM, bool* needSIB,
	                              unsigned int* dispSize, uint_64* pDisp, struct Instr_Def* instr,
								  struct expr opExpr[4], bool* needB, bool* needX, 
								  bool* needRR, struct code_info *CodeInfo);											    /* Build Memory encoding ModRM/SIB bytes   */
unsigned char GetRegisterNo(struct asm_tok *regTok);																		/* Get Register Encoding Number from Token */
