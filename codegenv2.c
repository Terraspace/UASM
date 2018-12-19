
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

#define OutputCodeByte( x ) OutputByte( x )

struct Instr_Def* InstrHash[16384];

struct Instr_Def InstrTableV2[] = {
	
	/* | mnemonic | operand count | operand types | encoding group | flags | opcode len | opcode bytes | op size | modRM | sib | OSO | ASO | Valid CPU modes | opnd direction | mandatory prefix type | */
	{ "mov", 2, { R8,  R8  }, GP0, F_MODRM,        1, { 0x88, 0x0, 0x0 }, 1, 0xc0, 0, 0,                0,                  (X16 | X32 | X64), REG_DST, NO_PREFIX, 0, NULL },
	{ "mov", 2, { R8E, R8E }, GP0, REX | F_MODRM,  1, { 0x88, 0x0, 0x0 }, 1, 0xc0, 0, 0,                0,                  (            X64), REG_DST, NO_PREFIX, 0, NULL },
	{ "mov", 2, { R16, R16 }, GP0, F_MODRM,        1, { 0x89, 0x0, 0x0 }, 2, 0xc0, 0, OP_SIZE_OVERRIDE, 0,                  (X16 | X32 | X64), REG_DST, NO_PREFIX, 0, NULL },
	{ "mov", 2, { R32, R32 }, GP0, F_MODRM,        1, { 0x89, 0x0, 0x0 }, 4, 0xc0, 0, OP_SIZE_OVERRIDE, 0,                  (X16 | X32 | X64), REG_DST, NO_PREFIX, 0, NULL },
	{ "mov", 2, { R64, R64 }, GP0, REXW | F_MODRM, 1, { 0x89, 0x0, 0x0 }, 8, 0xc0, 0, 0,                0,                  (            X64), REG_DST, NO_PREFIX, 0, NULL },

	{ "mov", 2, { M8,  R8  }, GP0, F_MODRM,        1, { 0x88, 0x0, 0x0 }, 1, 0xc0, 0, 0,                ADDR_SIZE_OVERRIDE, (X16 | X32 | X64), REG_DST, NO_PREFIX, 0, NULL },
	{ "mov", 2, { M8,  R8E }, GP0, REX | F_MODRM,  1, { 0x88, 0x0, 0x0 }, 1, 0xc0, 0, 0,                ADDR_SIZE_OVERRIDE, (            X64), REG_DST, NO_PREFIX, 0, NULL },
	{ "mov", 2, { M16, R16 }, GP0, F_MODRM,        1, { 0x89, 0x0, 0x0 }, 2, 0xc0, 0, OP_SIZE_OVERRIDE, ADDR_SIZE_OVERRIDE, (X16 | X32 | X64), REG_DST, NO_PREFIX, 0, NULL },
	{ "mov", 2, { M32, R32 }, GP0, F_MODRM,        1, { 0x89, 0x0, 0x0 }, 4, 0xc0, 0, OP_SIZE_OVERRIDE, ADDR_SIZE_OVERRIDE, (X16 | X32 | X64), REG_DST, NO_PREFIX, 0, NULL },
	{ "mov", 2, { M64, R64 }, GP0, REXW | F_MODRM, 1, { 0x89, 0x0, 0x0 }, 8, 0xc0, 0, 0,                ADDR_SIZE_OVERRIDE, (            X64), REG_DST, NO_PREFIX, 0, NULL },

	{ "mov", 2, { R8,  M8  }, GP0, F_MODRM,        1, { 0x8a, 0x0, 0x0 }, 1, 0xc0, 0, 0,                ADDR_SIZE_OVERRIDE, (X16 | X32 | X64), REG_DST, NO_PREFIX, 0, NULL },
	{ "mov", 2, { R8E, M8  }, GP0, REX | F_MODRM,  1, { 0x8a, 0x0, 0x0 }, 1, 0xc0, 0, 0,                ADDR_SIZE_OVERRIDE, (            X64), REG_DST, NO_PREFIX, 0, NULL },
	{ "mov", 2, { R16, M16 }, GP0, F_MODRM,        1, { 0x8b, 0x0, 0x0 }, 2, 0xc0, 0, OP_SIZE_OVERRIDE, ADDR_SIZE_OVERRIDE, (X16 | X32 | X64), REG_DST, NO_PREFIX, 0, NULL },
	{ "mov", 2, { R32, M32 }, GP0, F_MODRM,        1, { 0x8b, 0x0, 0x0 }, 4, 0xc0, 0, OP_SIZE_OVERRIDE, ADDR_SIZE_OVERRIDE, (X16 | X32 | X64), REG_DST, NO_PREFIX, 0, NULL },
	{ "mov", 2, { R64, M64 }, GP0, REXW | F_MODRM, 1, { 0x8b, 0x0, 0x0 }, 8, 0xc0, 0, 0,                ADDR_SIZE_OVERRIDE, (            X64), REG_DST, NO_PREFIX, 0, NULL },

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

enum op_type DemoteOperand(enum op_type op) {
	enum op_type ret = op;
	if (op == R8_AL)
		ret = R8E;
	else if (op == R8E)
		ret = R8;
	else if (op == R16_AX)
		ret = R16;
	else if (op == R32_EAX)
		ret = R32;
	else if (op == R64_RAX)
		ret = R64;
	return(ret);
}

enum op_type MatchOperand(struct opnd_item op) {
	enum op_type result;
	switch (op.type)
	{
		case OP_K:
			result = R_K;
			break;
		case OP_RIP:
			result = R_RIP;
			break;
		case OP_AL:
			result = R8_AL;
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
			/* If the register operand is sil,dil,spl,bpl,r8b-r15b */
			
			break;
		case OP_R16:
			result = R16;
			break;
		case OP_R32:
			result = R32;
			break;
		case OP_R64:
			result = R64;
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
		case OP_M08:
			result = M8;
			break;
		case OP_M16:
			result = M16;
			break;
		case OP_M32:
			result = M32;
			break;
		case OP_M64:
			result = M64;
			break;
		case OP_M128:
			result = M128;
			break;
		case OP_M256:
			result = M256;
			break;
		case OP_M512:
			result = M512;
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
	uint_32 hash;
	struct Instr_Def* pInstruction = NULL;
	bool first = TRUE;
	bool matched = FALSE;
	hash = GenerateInstrHash(instr);
    pInstruction = InstrHash[hash];
	while (pInstruction->next != NULL || first)
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
		first = FALSE;
	}
	if (!matched)
		pInstruction = NULL;
	return pInstruction;
}

bool Require_OPND_Size_Override(struct Instr_Def* instr, struct code_info* CodeInfo)
{
	if ((instr->op_size == 2 || instr->op_size == 4) &&
		CodeInfo->Ofssize != ModuleInfo.Ofssize)
		return TRUE;
	return FALSE;
}

bool Require_ADDR_Size_Override(struct Instr_Def* instr, struct code_info* CodeInfo)
{
	return FALSE;
}

bool IsValidInCPUMode(struct Instr_Def* instr)
{
	bool result = TRUE;
	unsigned char cpuModes = instr->validModes;
	if (ModuleInfo.Ofssize != 8 && cpuModes == X64)
		result = FALSE;
	return result;
}

unsigned char BuildModRM(struct Instr_Def* instr)
{
	unsigned char modRM = instr->modRM;
	return modRM;
}

unsigned char BuildSIB(struct Instr_Def* instr)
{
	unsigned char sib = 0;
	return sib;
}

unsigned char GetRegisterNo(void)
{
	unsigned char regNo = 0;
	return regNo;
}

ret_code CodeGenV2(const char* instr, struct code_info *CodeInfo, uint_32 oldofs, uint_32 opCount)
{
	ret_code retcode = NOT_ERROR;
	struct Instr_Def instrToMatch;
	struct Instr_Def* matchedInstr = NULL;
	uint_32 i = 0;
	unsigned char modRM = 0;
	unsigned char sib   = 0;

	return EMPTY; // stubbed out for now

	memset(&instrToMatch, 0, sizeof(struct Instr_Def));
	instrToMatch.mnemonic      = instr;		/* Instruction mnemonic string */
	instrToMatch.operand_count = opCount;	/* Number of operands */
	for (i = 0; i < opCount; i++)			/* Translate to CodeGenV2 operand types */
		instrToMatch.operand_types[i] = MatchOperand(CodeInfo->opnd[i]); //need more info, actual register name etc.

	/* Lookup the instruction */
	matchedInstr = LookupInstruction(&instrToMatch);
	/* We don't have it in CodeGenV2 so fall-back */
	if(matchedInstr == NULL)
		retcode = EMPTY;
	/* Proceed to generate the instruction */
	else
	{
		// Add line number debugging info.
		if (Options.line_numbers)
			AddLinnumDataRef(get_curr_srcfile(), GetLineNumber());

		// Check if instruction is valid in current mode.
		if (!IsValidInCPUMode(matchedInstr))
		{
			EmitError(NOT_SUPPORTED_WITH_CURR_FORMAT);
			return;
		}

		// Check if address or operand size override prefixes are required.
		if (Require_OPND_Size_Override(matchedInstr, CodeInfo))
			OutputCodeByte(OP_SIZE_OVERRIDE);

		if (Require_ADDR_Size_Override(matchedInstr, CodeInfo))
			OutputCodeByte(ADDR_SIZE_OVERRIDE);

		// Output FPU FWAIT if required.

		// Output mandatory prefix.
		if (matchedInstr->mandatory_prefix != 0)
		{
			
		}

		// Output opcode bytes.
		for(i=0;i<matchedInstr->opcode_bytes;i++)
			OutputCodeByte(matchedInstr->opcode[i]);

		// Output ModR/M
		if ((matchedInstr->flags | F_MODRM) != 0) {
			modRM = BuildModRM(matchedInstr);
			OutputCodeByte(modRM);
		}

		// Output SIB
		sib = BuildSIB(matchedInstr);
		if (sib != 0)
			OutputCodeByte(sib);

		// Output Displacement.

		// Output Immediate Data.
	}
	return retcode;
}

//  /c /DX86_64 /DWINDOWS64 -win64 /DARCH=SKX -Fl=out.lst /Foamd64\zr4dwpn_skx.obj zr4dwpn.asm
//  d:\foo2