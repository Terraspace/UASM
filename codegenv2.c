
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

struct Instr_Def* InstrHash[16384];

struct Instr_Def InstrTableV2[] = {
	
	/* | mnemonic | operand count | operand types | encoding group | flags | opcode len | opcode bytes | OSO | ASO | */
	{ "mov", 2, { R8,  R8  }, GP0, NO_FLAGS, 1, 0x88, 0x0, 0x0, 0,                0, 0, NULL },
	{ "mov", 2, { R8E, R8E }, GP0, REX,      1, 0x88, 0x0, 0x0, 0,                0, 0, NULL },
	{ "mov", 2, { R16, R16 }, GP0, NO_FLAGS, 1, 0x89, 0x0, 0x0, OP_SIZE_OVERRIDE, 0, 0, NULL },
	{ "mov", 2, { R32, R32 }, GP0, NO_FLAGS, 1, 0x89, 0x0, 0x0, OP_SIZE_OVERRIDE, 0, 0, NULL },
	{ "mov", 2, { R64, R64 }, GP0, REXW,     1, 0x89, 0x0, 0x0, 0,                0, 0, NULL },

	{ "mov", 2, { M8,  R8  }, GP0, NO_FLAGS, 1, 0x88, 0x0, 0x0, 0,                ADDR_SIZE_OVERRIDE, 0, NULL },
	{ "mov", 2, { M8,  R8E }, GP0, REX,      1, 0x88, 0x0, 0x0, 0,                ADDR_SIZE_OVERRIDE, 0, NULL },
	{ "mov", 2, { M16, R16 }, GP0, NO_FLAGS, 1, 0x89, 0x0, 0x0, OP_SIZE_OVERRIDE, ADDR_SIZE_OVERRIDE, 0, NULL },
	{ "mov", 2, { M32, R32 }, GP0, NO_FLAGS, 1, 0x89, 0x0, 0x0, OP_SIZE_OVERRIDE, ADDR_SIZE_OVERRIDE, 0, NULL },
	{ "mov", 2, { M64, R64 }, GP0, REXW,     1, 0x89, 0x0, 0x0, 0,                ADDR_SIZE_OVERRIDE, 0, NULL },

	{ "mov", 2, { R8,  M8  }, GP0, NO_FLAGS, 1, 0x8a, 0x0, 0x0, 0,                ADDR_SIZE_OVERRIDE, 0, NULL },
	{ "mov", 2, { R8E, M8  }, GP0, REX,      1, 0x8a, 0x0, 0x0, 0,                ADDR_SIZE_OVERRIDE, 0, NULL },
	{ "mov", 2, { R16, M16 }, GP0, NO_FLAGS, 1, 0x8b, 0x0, 0x0, OP_SIZE_OVERRIDE, ADDR_SIZE_OVERRIDE, 0, NULL },
	{ "mov", 2, { R32, M32 }, GP0, NO_FLAGS, 1, 0x8b, 0x0, 0x0, OP_SIZE_OVERRIDE, ADDR_SIZE_OVERRIDE, 0, NULL },
	{ "mov", 2, { R64, M64 }, GP0, REXW,     1, 0x8b, 0x0, 0x0, 0,                ADDR_SIZE_OVERRIDE, 0, NULL },

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
		ret = R8;
	else if (op == R16_AX)
		ret = R16;
	else if (op == R32_EAX)
		ret = R32;
	else if (op == R64_RAX)
		ret = R64;
	return(ret);
}

//void MatchOperand();

//

ret_code CodeGenV2(struct code_info *CodeInfo, uint_32 oldofs) 
{
	ret_code retcode = ERROR;
	retcode = EMPTY;
	return retcode;
}