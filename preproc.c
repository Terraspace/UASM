/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:  preprocessor
*
****************************************************************************/

#include <ctype.h>
#include <stdarg.h>

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "condasm.h"
#include "tokenize.h"
#include "equate.h"
#include "macro.h"
#include "input.h"
#include "fastpass.h"
#include "listing.h"
#include "proc.h"
#include "expreval.h"
#include "assume.h"
#include "lqueue.h"
#include "reswords.h"

#define REMOVECOMENT 0 /* 1=remove comments from source       */

extern ret_code (* const directive_tab[])( int, struct asm_tok[] );

#ifdef DEBUG_OUT
int_32 cntppl0;    /* count preprocessed lines 1 */
int_32 cntppl1;    /* count preprocessed lines 2 */
int_32 cntppl2;    /* count lines NOT handled by preprocessor */
#endif

/* preprocessor directive or macro procedure is preceded
 * by a code label.
 */
ret_code WriteCodeLabel( char *line, struct asm_tok tokenarray[] )
/****************************************************************/
{
    int oldcnt;
    int oldtoken;
    char oldchar;

    if ( tokenarray[0].token != T_ID ) {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[0].string_ptr ) );
    }
    /* ensure the listing is written with the FULL source line */
    if ( CurrFile[LST] ) LstWrite( LSTTYPE_LABEL, 0, NULL );
    /* v2.04: call ParseLine() to parse the "label" part of the line */
    oldcnt = Token_Count;
    oldtoken = tokenarray[2].token;
    oldchar = *tokenarray[2].tokpos;
    Token_Count = 2;
    tokenarray[2].token = T_FINAL;
    *tokenarray[2].tokpos = NULLC;
    ParseLine( tokenarray );
    if ( Options.preprocessor_stdout == TRUE )
        WritePreprocessedLine( line );
    Token_Count = oldcnt;
    tokenarray[2].token = oldtoken;
    *tokenarray[2].tokpos = oldchar;
    return( NOT_ERROR );
}

/* Verify a matched pair of function call brackets, assuming initial opening bracket position
   and return the closing bracket position or -1.
*/
int VerifyBrackets(struct asm_tok tokenarray[], int openIdx, bool inParam)
{
	int len;
	int i = openIdx;
	int opCnt = 0;
	if (tokenarray[i].token != T_OP_BRACKET)
	{
		EmitErr(MISSING_LEFT_PARENTHESIS_IN_EXPRESSION);
		return(-1);
	}

	if (!inParam)
	{
		for (i = 0;i < openIdx;i++)
		{
			if (tokenarray[i].token == T_OP_BRACKET || tokenarray[i].token == '(')
				opCnt++;
		}
	}

	if (tokenarray[i + 1].token == T_CL_BRACKET)
		return(i + 1);

	for (i = Token_Count-1;i > openIdx; i--)
	{
		if (tokenarray[i].token == T_CL_BRACKET && opCnt == 0)
			return(i);
		else if (tokenarray[i].token == T_CL_BRACKET)
			opCnt--;
	}

	EmitErr(MISSING_RIGHT_PARENTHESIS_IN_EXPRESSION);
	return(-1);
}

/* Source reconstructed from tokens uses MASM doubled quote escaping. */
static char *SkipCallString(char *p)
{
    char quote = *p++;
    while (*p) {
        if (*p++ == quote) {
            if (*p != quote) break;
            p++;
        }
    }
    return p;
}

static bool CallAppend(char *out, const char *text, size_t length);

static void ExpandObjCalls(char *line, struct asm_tok tokenarray[])
{
	int i,j;
	struct dsym *sym;
	struct dsym *type = NULL;
	struct dsym *tsym;
	struct dsym *param;
	bool foundType = FALSE;
	bool foundProc = FALSE;
	int derefCount = 0;
	int opIdx = 0;
	int clIdx = 0;
	int clSqIdx = 0;
	int opSqIdx = 0;
	char newline[MAX_LINE_LEN];
	bool gotOpen = FALSE;
	bool gotClose = FALSE;
	bool gotCloseSqr = FALSE;
	bool gotOpenSqr = FALSE;
	char methodName[MAX_LINE_LEN];
	char indirectAddr[MAX_LINE_LEN];
    char receiverType[MAX_LINE_LEN];
	char *pMethodStr = methodName;
	char *pStr = newline;
	char *pType = NULL;
	bool inExpr = FALSE;
	bool hasExprBracket = FALSE;
	bool inParam = FALSE;
	bool inProc = FALSE;
	int firstDeRefIdx = 0;
	int paramCount = 0;
	char pcs[16];
	bool didExpand = TRUE;
	char refStr[MAX_LINE_LEN];
	struct sfield *field = NULL;

	strcpy(newline, line);

	// Scan through tokens, looking for pointer operators.
	while (didExpand)
	{
		memset(indirectAddr, 0, MAX_LINE_LEN);
		memset(methodName, 0, MAX_LINE_LEN);
		memset(newline, 0, MAX_LINE_LEN);
		memset(&refStr, 0, MAX_LINE_LEN);
		pStr = newline;
		didExpand = FALSE;
        derefCount = 0;
        type = NULL;
        inExpr = inParam = FALSE;
		paramCount = 0;
		for (i = 0; i < Token_Count; i++)
		{
			if (tokenarray[i].token == T_POINTER)
			{

				/* Scan backwards to check if we're in an HLL expression or call parameter */
				if (i > 0)
				{
					for (j = i - 1; j >= 0; j--)
					{
						tsym = (struct dsym *)SymCheck(tokenarray[j].string_ptr);
						if (tokenarray[j].token == T_DIRECTIVE && (tokenarray[j].dirtype == DRT_HLLSTART || tokenarray[j].dirtype == DRT_HLLEND))
						{
							inExpr = TRUE;
							if (tokenarray[j + 1].token == T_OP_BRACKET || tokenarray[j + 1].tokval == '(')
								hasExprBracket = TRUE;
							else
								hasExprBracket = FALSE;
							break;
						}
						else if ((tokenarray[j].token == T_DIRECTIVE && tokenarray[j].dirtype == DRT_INVOKE) ||
							strcmp(tokenarray[j].string_ptr, "arginvoke") == 0 ||
							strcmp(tokenarray[j].string_ptr, "_INVOKE") == 0 ||
							strcmp(tokenarray[j].string_ptr, "_I") == 0 ||
							strcmp(tokenarray[j].string_ptr, "_VINVOKE") == 0 ||
							strcmp(tokenarray[j].string_ptr, "_V") == 0 ||
							strcmp(tokenarray[j].string_ptr, "_SINVOKE") == 0 ||
							strcmp(tokenarray[j].string_ptr, "_DEREF") == 0 ||
							strcmp(tokenarray[j].string_ptr, "_DEREFI") == 0 ||
							strcmp(tokenarray[j].string_ptr, "uinvoke") == 0)
						{
							inParam = TRUE;
							break;
						}
						else if (tokenarray[j].token == T_ID && tsym && tsym->sym.isproc)
						{
							inParam = TRUE;
							inProc = TRUE;
							break;
						}
					}
				}

				if(derefCount == 0)
					foundType = FALSE;
				foundProc = FALSE;
				// The item to the left of the pointer must be an ID with type or register or register indirect.
				if (i == 0)
				{
					EmitError(INVALID_POINTER);
                    return;
				}
				/* Variable object reference */
				else if (tokenarray[i - 1].token == T_ID)
				{
					if (derefCount == 0)
					{
						sym = (struct dsym *)SymCheck(tokenarray[i - 1].string_ptr);
						if (sym && sym->sym.target_type && sym->sym.target_type > 0x200000 && (sym->sym.target_type->isClass || sym->sym.target_type->isPtrTable))
						{
							foundType = TRUE;
							pType = tokenarray[i - 1].string_ptr;
							type = (struct dsym *)sym->sym.target_type;
							firstDeRefIdx = i - 2; /* pointer->item */
						}
						else if (sym && sym->sym.type && sym->sym.type->target_type && sym->sym.type->target_type > 0x200000 && sym->sym.type->target_type->isClass)
						{
							foundType = TRUE;
							pType = tokenarray[i - 1].string_ptr;
							type = (struct dsym *)sym->sym.type->target_type;
							firstDeRefIdx = i - 2; /* pointer->item */
						}
						else if (sym && sym->sym.type && sym->sym.type->target_type && sym->sym.type->target_type > 0x200000 && sym->sym.type->target_type->isPtrTable)
						{
							foundType = TRUE;
							pType = tokenarray[i - 1].string_ptr;
							type = (struct dsym *)sym->sym.type->target_type;
							firstDeRefIdx = i - 2; /* pointer->item */
						}
						/* Indirect register using .TYPE */
						else if (sym && (sym->sym.isClass || sym->sym.isPtrTable))
						{
							gotCloseSqr = TRUE;
							gotOpenSqr = FALSE;
							clSqIdx = i - 3;
							// Scan back to find opening square bracket.
							for (j = i - 1; j >= 0; j--)
							{
								if (tokenarray[j].token == T_OP_SQ_BRACKET)
								{
									opSqIdx = j;
									gotOpenSqr = TRUE;
									break;
								}
							}
							if (!gotOpenSqr || !gotCloseSqr)
								EmitError(INVALID_POINTER);
							// The tokens between opSqIdx and clSqIdx make up the indirect address.
							// -> the first register(base) must be assumed to an object pointer.
							if (sym && (sym->sym.isClass || sym->sym.isPtrTable))
							{
								foundType = TRUE;
								pType = indirectAddr;
								pType = strcpy(pType, "[") + 1;
								for (j = opSqIdx + 1; j < clSqIdx; j++)
								{
									strcpy(pType, tokenarray[j].string_ptr);
									pType += strlen(tokenarray[j].string_ptr);
								}
								pType = strcpy(pType, "]") + 1;
								pType = indirectAddr;
								type = (struct dsym *)sym;
								firstDeRefIdx = opSqIdx - 1; /* pointer->item */
							}
							else
								EmitError(INVALID_POINTER);
						}
					}
					else
					{
						// Ensure tokenarray[i - 1].string_ptr is a field of the current TYPE, then get it's target type.
						bool gotField = FALSE;
						field = type->e.structinfo->head;
						for (; field; field = field->next)
						{
							if (_stricmp(field->sym.name, tokenarray[i - 1].string_ptr) == 0)
							{
								gotField = TRUE;
								break;
							}
						}
						if (gotField)
						{
							type = (struct dsym *)field->sym.target_type;
							if (!type || type < 0x10)
								type = (struct dsym *)field->sym.type->target_type;
							if (!type || type < 0x10)
								EmitError(INVALID_POINTER);
						}
						else
							EmitError(INVALID_POINTER);

						// Append the item to the pType.
						strcpy(pType + strlen(pType), ".");
						strcpy(pType + strlen(pType), tokenarray[i - 1].string_ptr);

					}
					if (!foundType)
						EmitError(INVALID_POINTER);
				}
				/* Direct register object reference */
				else if (tokenarray[i - 1].token == T_REG)
				{
					sym = (struct dsym *)StdAssumeTable[GetRegNo(tokenarray[i - 1].tokval)].symbol;
					if (sym && sym->sym.target_type)
					{
						foundType = TRUE;
						pType = tokenarray[i - 1].string_ptr;
						type = (struct dsym *)sym->sym.target_type;
						firstDeRefIdx = i - 2; /* pointer->item */
					}
					else
						EmitError(INVALID_POINTER);
				}
				/* Indirect memory address type object reference */
				else if (tokenarray[i - 1].token == T_CL_SQ_BRACKET)
				{
					gotCloseSqr = TRUE;
					gotOpenSqr = FALSE;
					clSqIdx = i - 1;
					// Scan back to find opening square bracket.
					for (j = i - 1; j >= 0; j--)
					{
						if (tokenarray[j].token == T_OP_SQ_BRACKET)
						{
							opSqIdx = j;
							gotOpenSqr = TRUE;
							break;
						}
					}
					if (!gotOpenSqr || !gotCloseSqr)
						EmitError(INVALID_POINTER);
					// The tokens between opSqIdx and clSqIdx make up the indirect address.
					// -> the first register(base) must be assumed to an object pointer.
					sym = (struct dsym *)StdAssumeTable[GetRegNo(tokenarray[opSqIdx + 1].tokval)].symbol;
					if (sym && sym->sym.target_type)
					{
						foundType = TRUE;
						pType = indirectAddr;
						pType = strcpy(pType, "[") + 1;
						for (j = opSqIdx + 1; j < clSqIdx; j++)
						{
							strcpy(pType, tokenarray[j].string_ptr);
							pType += strlen(tokenarray[j].string_ptr);
						}
						pType = strcpy(pType, "]") + 1;
						pType = indirectAddr;
						type = (struct dsym *)sym->sym.target_type;
						firstDeRefIdx = opSqIdx-1; /* pointer->item */
					}
					else
						EmitError(INVALID_POINTER);
				}

				// The right of the pointer must be an ID (either a method(proc) or another type).
				if (!type || tokenarray[i + 1].token != T_ID)
					EmitError(INVALID_POINTER);
				else
				{
					pMethodStr = methodName;
					{
                        const char *leaf = SymLeafName(type->sym.name);
                        size_t prefix = leaf - type->sym.name;
                        memcpy(pMethodStr, type->sym.name, prefix); pMethodStr += prefix;
                        *pMethodStr++ = '_';
                        strcpy(pMethodStr, leaf); pMethodStr += strlen(leaf);
                    }
					pMethodStr = strcpy(pMethodStr, "_") + 1;
					strcpy(pMethodStr, tokenarray[i + 1].string_ptr);
					pMethodStr += strlen(tokenarray[i + 1].string_ptr);
					pMethodStr = methodName;

					sym = (struct dsym *)SymCheck(pMethodStr);
					if (sym && sym->sym.isproc)
					{
						foundProc = TRUE;
						pMethodStr = tokenarray[i + 1].string_ptr;
						for (param = sym->e.procinfo->paralist; param; param = param->nextparam)
						{
							paramCount++;
						}
					}
                    else if (type && type->sym.isClass) {
                        foundProc = FALSE;
                        if (derefCount == 0) {
                            if (!CallAppend(refStr,pType,strlen(pType)) ||
                                !CallAppend(refStr,",",1) ||
                                !CallAppend(refStr,type->sym.name,strlen(type->sym.name))) return;
                        } else {
                            /* Record the parent's field path before changing to
                             * the next object's type (supports chains beyond two). */
                            if (!CallAppend(refStr,",rcx,",5) ||
                                !CallAppend(refStr,pType,strlen(pType))) return;
                        }
                        strcpy(receiverType,type->sym.name);
                        pType = receiverType; /* Never overwrite token storage. */
                    }
					else
						EmitError(INVALID_POINTER);
				}

				// Find the proc open/close brackets.
				if (foundProc)
				{
					int openCount = 1;
					for (j = i; j < Token_Count; j++)
					{
						if (tokenarray[j].token == T_OP_BRACKET || tokenarray[j].tokval == '(')
						{
							opIdx = j;
							gotOpen = TRUE;
							break;
						}
					}

					for (j = opIdx + 1; j < Token_Count; j++)
					{
						if (tokenarray[j].token == T_CL_BRACKET || tokenarray[j].tokval == ')')
							openCount--;

						if (tokenarray[j].token == T_OP_BRACKET || tokenarray[j].tokval == '(')
							openCount++;

						if (openCount == 0)
						{
							clIdx = j;
							gotClose = TRUE;
							break;
						}
					}

					if (!gotOpen)
						EmitError(MISSING_LEFT_PARENTHESIS_IN_EXPRESSION);
					if (!gotClose)
						EmitError(MISSING_RIGHT_PARENTHESIS_IN_EXPRESSION);
				}

                if (foundProc) {
                    int actual = 0, depth = 0;
                    int required = paramCount - (type->sym.isPtrTable ? 0 : 1);
                    if (!gotOpen || !gotClose) return;
                    if (clIdx > opIdx + 1) {
                        actual = 1;
                        for (j = opIdx + 1; j < clIdx; ++j) {
                            if (tokenarray[j].token == T_OP_BRACKET || tokenarray[j].token == T_OP_SQ_BRACKET) ++depth;
                            else if (tokenarray[j].token == T_CL_BRACKET || tokenarray[j].token == T_CL_SQ_BRACKET) --depth;
                            else if (!depth && tokenarray[j].token == T_COMMA) ++actual;
                        }
                    }
                    if (sym->e.procinfo->has_vararg) --required;
                    if (actual < required) { EmitErr(TOO_FEW_ARGUMENTS_TO_INVOKE, sym->sym.name); return; }
                    if (actual > required && !sym->e.procinfo->has_vararg) { EmitError(TOO_MANY_ARGUMENTS_TO_INVOKE); return; }
                    if (sym->e.procinfo->has_vararg) paramCount = actual + (type->sym.isPtrTable ? 0 : 1);
                }

                if (foundProc && type->sym.isPtrTable) {
                    int first = firstDeRefIdx + 1;
                    bool expression = first != 0;
                    bool indirect = pType[0] == '[';
                    const char *helper = expression ? (indirect ? "_RAWRI(" : "_RAWI(") :
                        (indirect ? "_RAWRINVOKE " : "_RAWINVOKE ");
                    const char *scan, *start;
                    /* RAW receivers use R11 while INVOKE marshals arguments.
                     * Do not silently overwrite an explicitly supplied operand. */
                    {
                        for (j = opIdx + 1; j < clIdx; ++j)
                            if (tokenarray[j].token == T_REG &&
                                (GetValueSp(tokenarray[j].tokval) & OP_R) &&
                                GetRegNo(tokenarray[j].tokval) == 11) {
                                EmitErr(SYNTAX_ERROR_EX, "RAW call argument conflicts with R11 dispatch scratch register");
                                return;
                            }
                    }
                    newline[0] = 0;
                    if (!CallAppend(newline,tokenarray[0].tokpos,tokenarray[first].tokpos-tokenarray[0].tokpos) ||
                        !CallAppend(newline,helper,strlen(helper)) ||
                        !CallAppend(newline,type->sym.name,strlen(type->sym.name)) ||
                        !CallAppend(newline,",",1) || !CallAppend(newline,pMethodStr,strlen(pMethodStr)) ||
                        !CallAppend(newline,",",1) || !CallAppend(newline,pType,strlen(pType))) return;
                    if (clIdx > opIdx+1) {
                        if (!CallAppend(newline,",",1)) return;
                        start=scan=tokenarray[opIdx].tokpos+1;
                        while (scan < tokenarray[clIdx].tokpos) {
                            if (*scan == '"' || *scan == 39) { scan=SkipCallString((char *)scan); continue; }
                            if (*scan == '&') {
                                if (!CallAppend(newline,start,scan-start) || !CallAppend(newline," ADDR ",6)) return;
                                start=scan+1;
                            }
                            ++scan;
                        }
                        if (!CallAppend(newline,start,scan-start)) return;
                    }
                    if (expression && !CallAppend(newline,")",1)) return;
                    if (!CallAppend(newline,tokenarray[clIdx].tokpos+1,strlen(tokenarray[clIdx].tokpos+1))) return;
                    didExpand=TRUE;
                    break;
                }

                if (foundProc) {
                    for (j = 0; j <= firstDeRefIdx; ++j)
                        if (tokenarray[j].token == T_INSTRUCTION) inExpr = TRUE;
                }
				if (foundProc)
				{
					if (!type->sym.isPtrTable)
					{
						for (j = 0; j <= firstDeRefIdx; j++)
						{
							pStr = strcpy(pStr, " ") + 1;
							strcpy(pStr, tokenarray[j].string_ptr);
							pStr += strlen(tokenarray[j].string_ptr);
							pStr = strcpy(pStr, " ") + 1;
						}
					}
					if (inExpr || inParam)
						pStr = strcpy(pStr, "_DEREFI(") + 8;
					else if (!type->sym.isPtrTable)
						pStr = strcpy(pStr, "_DEREF ") + 7;
					else if (type->sym.isPtrTable)
					{
						if (tokenarray[i - 3].token == T_CL_SQ_BRACKET)
						{
							pStr = strcpy(pStr, "_DEREFRR ") + 9;
							strcpy(pStr, pType);
							pStr += strlen(pType);
							pStr = strcpy(pStr, ",") + 1;
						}
						else
						{
							pStr = strcpy(pStr, "_DEREFR ") + 8;
							strcpy(pStr, tokenarray[i - 1].string_ptr);
							pStr += strlen(tokenarray[i - 1].string_ptr);
							pStr = strcpy(pStr, ",") + 1;
						}
					}
					strcpy(pStr, type->sym.name);
					pStr += strlen(type->sym.name);
					pStr = strcpy(pStr, ",") + 1;
					strcpy(pStr, pMethodStr);
					pStr += strlen(pMethodStr);
					pStr = strcpy(pStr, ",") + 1;

					if(type->sym.isPtrTable)
						sprintf(pcs, "%d", paramCount); // no -1, these are raw functions
					else
						sprintf(pcs, "%d", paramCount - 1); //-1 due to thisPtr implicit
					strcpy(pStr, pcs);
					pStr += strlen(pcs);

					pStr = strcpy(pStr, ",") + 1;

                    /* A dummy first argument is skipped by the dispatch helper. */
                    if (!type->sym.isPtrTable) {
                        *pStr++ = '0';
                        if (clIdx > opIdx + 1) *pStr++ = ',';
                        *pStr = 0;
                    }

					for (j = opIdx + 1; j < clIdx; j++)
					{
						if (*tokenarray[j].string_ptr == '&')
							pStr = strcpy(pStr, " ADDR ") + 6;
						else
						{
							strcpy(pStr, tokenarray[j].string_ptr);
							pStr += strlen(tokenarray[j].string_ptr);
							if (strncmp(tokenarray[j].string_ptr, "ADDR",4) == 0)
								pStr = strcpy(pStr, " ") + 1;
						}
					}

					if(!type->sym.isPtrTable)
						pStr = strcpy(pStr, ",") + 1;

					if (derefCount > 0)
					{
						strcpy(pStr, refStr);
						pStr += strlen(refStr);
						pStr = strcpy(pStr, ",") + 1;
					}
					if (derefCount == 0 && !type->sym.isPtrTable)
					{
						strcpy(pStr, pType);
						pStr += strlen(pType);
						pStr = strcpy(pStr, ",") + 1;
						strcpy(pStr, type->sym.name);
						pStr += strlen(type->sym.name);
					}
					else if(!type->sym.isPtrTable)
					{
						pStr = strcpy(pStr, "rcx,") + 4;
						strcpy(pStr, pType);
						pStr += strlen(pType);
					}

					if (inExpr || inParam)
						pStr = strcpy(pStr, ")") + 1;
					for (j = clIdx + 1; j < Token_Count; j++)
					{
						pStr = strcpy(pStr, " ") + 1;
						strcpy(pStr, tokenarray[j].string_ptr);
						pStr += strlen(tokenarray[j].string_ptr);
						pStr = strcpy(pStr, " ") + 1;
					}

					didExpand = TRUE;
					break;
				}

				derefCount++;
			}
		}

		/* Transfer new source line back for token rescan */
		if (didExpand)
		{
			strcpy(line, newline);
			Token_Count = Tokenize(line, 0, tokenarray, TOK_RESCAN);
		}
	}


}

static bool CallAppend(char *out, const char *text, size_t length);

/* Rewrite one static method at a time, then rescan. Raw source slices retain
 * literal spelling and whitespace; the bounded builder also covers siblings
 * and nested static calls without appending to an old expansion buffer. */
static void ExpandStaticObjCalls(char *line, struct asm_tok tokenarray[])
{
    int i;
    for (i=0;i+3<Token_Count;++i) {
        struct asym *sym;
        int close, depth;
        bool expression;
        const char *source, *begin, *end, *scan, *part;
        char rewritten[MAX_LINE_LEN];
        if (tokenarray[i].token != T_ID || tokenarray[i+1].token != T_DOT ||
            tokenarray[i+2].token != T_ID || tokenarray[i+3].token != T_OP_BRACKET)
            continue;
        sym=SymSearch(tokenarray[i].string_ptr);
        if (!sym || !sym->isClass) continue;
        depth=1;
        for (close=i+4;close<Token_Count && depth;++close) {
            if (tokenarray[close].token == T_OP_BRACKET) ++depth;
            if (tokenarray[close].token == T_CL_BRACKET) --depth;
        }
        if (depth) { EmitErr(SYNTAX_ERROR_EX,"unmatched static-call parentheses"); return; }
        --close;
        expression=i != 0;
        source=tokenarray[0].tokpos;
        begin=tokenarray[i+3].tokpos+1;
        end=tokenarray[close].tokpos;
        rewritten[0]=0;
        if (!CallAppend(rewritten,source,tokenarray[i].tokpos-source) ||
            !CallAppend(rewritten,expression ? "_STATIC(" : "_SINVOKE ",expression ? 8 : 9) ||
            !CallAppend(rewritten,sym->name,strlen(sym->name)) ||
            !CallAppend(rewritten,",",1) ||
            !CallAppend(rewritten,tokenarray[i+2].string_ptr,strlen(tokenarray[i+2].string_ptr))) return;
        if (close > i+4) {
            if (!CallAppend(rewritten,",",1)) return;
            part=scan=begin;
            while (scan<end) {
                if (*scan == '"' || *scan == 39) { scan=SkipCallString((char *)scan); continue; }
                if (*scan == '&') {
                    if (!CallAppend(rewritten,part,scan-part) || !CallAppend(rewritten,"ADDR ",5)) return;
                    part=++scan;
                } else ++scan;
            }
            if (!CallAppend(rewritten,part,end-part)) return;
        }
        if (expression && !CallAppend(rewritten,")",1)) return;
        if (!CallAppend(rewritten,end+1,strlen(end+1))) return;
        strcpy(line,rewritten);
        Token_Count=Tokenize(line,0,tokenarray,TOK_RESCAN);
        i=-1;
    }
}

static struct asym * TraverseEquate(struct asym *sym)
{
	struct asym *resultSym = sym;
	if (sym)
	{
		while (resultSym->state == SYM_TMACRO && resultSym->string_ptr != NULL)
		{
			resultSym = SymLookup(resultSym->string_ptr);
		}
	}
	return(resultSym);
}

/* Bounded C-style call lowering. Only return values are materialized: user
 * operands remain assembler expressions, with volatile-register conflicts
 * diagnosed instead of introducing implicit snapshots. */
#define CALL_RESULT_LIMIT 32
struct bounded_call {
    int first, last, parent, depth, order, helper;
    struct dsym *proc;
    struct asym *temp;
    const char *type, *reg, *store;
    unsigned size;
    char replacement[128];
};

static bool CallReturn(struct bounded_call *c)
{
    enum returntype r = c->proc->e.procinfo->ret_type;
    c->store = "mov";
    if (!c->proc->e.procinfo->explicit_return || r == RT_NONE) {
        EmitErr(SYNTAX_ERROR_EX, "value-producing call requires an explicit non-void return type");
        return FALSE;
    }
    switch (r) {
    case RT_BYTE: case RT_SBYTE: c->type = r == RT_BYTE ? "byte" : "sbyte"; c->reg="al"; c->size=1; break;
    case RT_WORD: case RT_SWORD: c->type = r == RT_WORD ? "word" : "sword"; c->reg="ax"; c->size=2; break;
    case RT_DWORD: case RT_SDWORD: c->type = r == RT_DWORD ? "dword" : "sdword"; c->reg="eax"; c->size=4; break;
    case RT_PTR: case RT_QWORD: case RT_SQWORD:
        if (ModuleInfo.Ofssize != USE64 && r != RT_PTR) goto unsupported;
        c->size = ModuleInfo.Ofssize == USE64 ? 8 : 4;
        c->type = c->size == 8 ? "qword" : "dword";
        c->reg = c->size == 8 ? "rax" : "eax"; break;
    case RT_REAL4: case RT_REAL8:
        /* UASM explicit REAL return contracts use XMM0, including Win32. */
        c->size = r == RT_REAL4 ? 4 : 8;
        c->type = r == RT_REAL4 ? "real4" : "real8";
        c->store = r == RT_REAL4 ? (MODULEARCH == ARCH_AVX ? "vmovss" : "movss") : (MODULEARCH == ARCH_AVX ? "vmovsd" : "movsd");
        c->reg = "xmm0"; break;
    case RT_XMM:
        if (ModuleInfo.Ofssize != USE64) goto unsupported;
        c->size=16; c->type="xmmword"; c->reg="xmm0"; c->store=MODULEARCH == ARCH_AVX ? "vmovdqu" : "movdqu"; break;
    case RT_YMM:
        if (ModuleInfo.Ofssize != USE64) goto unsupported;
        c->size=32; c->type="ymmword"; c->reg="ymm0"; c->store="vmovdqu"; break;
    case RT_ZMM:
        if (ModuleInfo.Ofssize != USE64) goto unsupported;
        c->size=64; c->type="zmmword"; c->reg="zmm0"; c->store="vmovdqu64"; break;
    default: goto unsupported;
    }
    return TRUE;
unsupported:
    EmitErr(SYNTAX_ERROR_EX, "unsupported nested-call return convention");
    return FALSE;
}

static bool CallVolatile(unsigned reg, bool sysv)
{
    unsigned kind = GetValueSp(reg), n = GetRegNo(reg);
    if (kind & (OP_XMM | OP_YMM | OP_ZMM)) {
        if (ModuleInfo.Ofssize != USE64 || sysv) return TRUE;
        /* Win64 preserves only the low 128 bits of XMM6..15. */
        return n < 6 || n > 15 || (kind & (OP_YMM | OP_ZMM));
    }
    if (kind & OP_R) {
        if (reg == T_AH) n=0;
        if (reg == T_CH) n=1;
        if (reg == T_DH) n=2;
        if (reg == T_BH) n=3;
        return n <= 2 || (ModuleInfo.Ofssize == USE64 &&
            ((n >= 8 && n <= 11) || (sysv && (n == 6 || n == 7))));
    }
    return FALSE;
}

/* Text equates and register aliases must not hide a conflicting address.
 * Scan their identifiers without interpreting quoted literal contents. */
static bool CallTextVolatile(const char *text, bool sysv, unsigned depth)
{
    char name[MAX_ID_LEN+1];
    if (depth > 16) return TRUE;
    while (*text) {
        const char *begin;
        size_t length;
        unsigned reg;
        struct asym *sym;
        if (*text == '"' || *text == 39) { text=SkipCallString((char *)text); continue; }
        if (!is_valid_id_start(*text) && !(text[0] == ':' && text[1] == ':')) { ++text; continue; }
        begin=text;
        if (text[0] == ':') text+=2; else ++text;
        while (is_valid_id_char(*text) || (text[0] == ':' && text[1] == ':')) {
            if (text[0] == ':') text+=2; else ++text;
        }
        length=text-begin;
        if (!length || length > MAX_ID_LEN) return TRUE;
        memcpy(name,begin,length); name[length]=0;
        reg=FindResWord(name,(unsigned char)length);
        if (reg && reg < SPECIAL_LAST && SpecialTable[reg].type == RWT_REG) {
            if (CallVolatile(reg,sysv)) return TRUE;
        } else if ((sym=SymCheck(name)) && sym->state == SYM_TMACRO && sym->string_ptr) {
            if (CallTextVolatile(sym->string_ptr,sysv,depth+1)) return TRUE;
        }
    }
    return FALSE;
}

static bool CallOperandVolatile(struct asm_tok *token, bool sysv)
{
    struct asym *sym;
    if (token->token == T_REG) return CallVolatile(token->tokval,sysv);
    if (token->token == T_ID && (sym=SymCheck(token->string_ptr)) &&
        sym->state == SYM_TMACRO && sym->string_ptr)
        return CallTextVolatile(sym->string_ptr,sysv,0);
    return FALSE;
}

/* _DEREF's later receiver pairs contain a generated RCX, loaded by the
 * helper after child calls. It is not a user value that must survive them.
 * The initial receiver and every ordinary argument still undergo checks. */
static bool CallDerefScratch(struct asm_tok *tokens, int first, int operand)
{
    int begin, argc, j, depth = 0, argument = 0;
    if (tokens[operand].token != T_REG || tokens[operand].tokval != T_RCX) return FALSE;
    if (_stricmp(tokens[first].string_ptr, "_DEREFI") == 0) begin = first + 2;
    else if (_stricmp(tokens[first].string_ptr, "_DEREF") == 0) begin = first + 1;
    else return FALSE;
    if (begin + 4 >= Token_Count || tokens[begin+4].token != T_NUM) return FALSE;
    argc = atoi(tokens[begin+4].string_ptr);
    for (j = begin; j < operand; ++j) {
        if (tokens[j].token == T_OP_BRACKET || tokens[j].token == T_OP_SQ_BRACKET) ++depth;
        else if (tokens[j].token == T_CL_BRACKET || tokens[j].token == T_CL_SQ_BRACKET) --depth;
        else if (!depth && tokens[j].token == T_COMMA) ++argument;
    }
    return !depth && argument >= argc + 6 && !((argument - argc - 6) & 1) &&
        tokens[operand-1].token == T_COMMA && tokens[operand+1].token == T_COMMA;
}

static bool CallAppend(char *out, const char *text, size_t length)
{
    size_t used = strlen(out);
    if (used + length >= MAX_LINE_LEN) {
        EmitError(STRING_OR_TEXT_LITERAL_TOO_LONG);
        return FALSE;
    }
    memcpy(out+used, text, length); out[used+length]=0;
    return TRUE;
}

/* Copy source text, replacing immediate child calls with typed frame operands. */
static bool CallRender(char *out, const char *begin, const char *end,
                       int parent, struct bounded_call *calls, int count,
                       struct asm_tok *tokens)
{
    int i;
    for (i=0; i<count; ++i) if (calls[i].parent == parent) {
        const char *first=tokens[calls[i].first].tokpos;
        const char *last=tokens[calls[i].last].tokpos+1;
        if (first < begin || last > end) continue;
        if (!CallAppend(out,begin,first-begin) ||
            !CallAppend(out,calls[i].replacement,strlen(calls[i].replacement))) return FALSE;
        begin=last;
    }
    return CallAppend(out,begin,end-begin);
}

static void CallOrder(int node, struct bounded_call *calls, int count, int *order)
{
    int i;
    for (i=0; i<count; ++i) if (calls[i].parent == node) CallOrder(i,calls,count,order);
    calls[node].order=(*order)++;
}

/* The OO macrolib records the same explicit return contract on its generated
 * PROC and prototype symbols. Resolve that contract before invoking the helper. */
static struct dsym *CallMethodPrototype(struct asm_tok *tokens, int first, int helper)
{
    const char *name, *leaf, *method;
    size_t head;
    char full[MAX_ID_LEN+1];
    struct asym *sym;
    unsigned depth=0;
    if (first+5 >= Token_Count || tokens[first+3].token != T_COMMA) return NULL;
    name=tokens[first+2].string_ptr;
    method=tokens[first+4].string_ptr;
    leaf=SymLeafName(name); head=leaf-name;
    if (strlen(name)+strlen(method)+6 > MAX_ID_LEN) return NULL;
    memcpy(full,name,head);
    sprintf(full+head,"_%s_%s%s",leaf,method,helper>=2 ? "Pto" : "");
    sym=SymCheck(full);
    while (sym && !sym->isproc && sym->target_type && depth++<16) sym=sym->target_type;
    return sym && sym->isproc ? (struct dsym *)sym : NULL;
}

/* Returns -1 for a diagnosed error, 0 for the existing flat path, 1 when
 * children have been emitted and line contains the remaining outer call. */
static int LowerBoundedCalls(char *line, struct asm_tok *tokens)
{
    struct bounded_call calls[CALL_RESULT_LIMIT+1];
    int count=0, i,j,k,paren,order=0,roots=0,slot=0,root=-1;
    bool sysv = Options.output_format == OFORMAT_ELF && ModuleInfo.Ofssize == USE64;
    bool directInvoke = tokens[0].tokval == T_INVOKE ||
        _stricmp(tokens[0].string_ptr,"_SINVOKE") == 0 || _stricmp(tokens[0].string_ptr,"_DEREF") == 0 ||
        _stricmp(tokens[0].string_ptr,"_VINVOKE") == 0 || _stricmp(tokens[0].string_ptr,"_INVOKE") == 0 ||
        _stricmp(tokens[0].string_ptr,"_DEREFR") == 0 || _stricmp(tokens[0].string_ptr,"_DEREFRR") == 0 ||
        _stricmp(tokens[0].string_ptr,"_RAWINVOKE") == 0 || _stricmp(tokens[0].string_ptr,"_RAWRINVOKE") == 0;
    char rewritten[MAX_LINE_LEN], generated[CALL_RESULT_LIMIT][MAX_LINE_LEN];
    char stores[CALL_RESULT_LIMIT][256];
    const char *source=tokens[0].tokpos;
    memset(calls,0,sizeof(calls));
    for (i=0;i<Token_Count-1;++i) {
        struct dsym *proc;
        int helper;
        if (tokens[i].token != T_ID || tokens[i+1].token != T_OP_BRACKET) continue;
        helper = _stricmp(tokens[i].string_ptr,"_STATIC") == 0 ? 1 :
                 (_stricmp(tokens[i].string_ptr,"_DEREFI") == 0 ? 2 :
                 (_stricmp(tokens[i].string_ptr,"_RAWI") == 0 ? 3 :
                 (_stricmp(tokens[i].string_ptr,"_RAWRI") == 0 ? 4 : 0)));
        proc=helper ? CallMethodPrototype(tokens,i,helper) :
            (struct dsym *)TraverseEquate(SymCheck(tokens[i].string_ptr));
        if (!proc || !proc->sym.isproc) {
            if (helper) { EmitErr(SYNTAX_ERROR_EX,"method call requires a resolved typed prototype"); return -1; }
            continue;
        }
        if (i && (tokens[i-1].tokval == T_PROTO || tokens[i-1].tokval == T_PROC)) continue;
        paren=1;
        for (j=i+2;j<Token_Count && paren;++j) {
            if (tokens[j].token == T_OP_BRACKET) ++paren;
            if (tokens[j].token == T_CL_BRACKET) --paren;
        }
        if (paren) { EmitError(EXPECTED_CL_SQ_BRACKET); return -1; }
        if (count == CALL_RESULT_LIMIT+1) {
            EmitErr(SYNTAX_ERROR_EX,"too many nested-call results (maximum 32)"); return -1;
        }
        calls[count].first=i; calls[count].last=j-1; calls[count].proc=proc; calls[count].helper=helper;
        calls[count].parent=-1; calls[count].depth=directInvoke ? 2 : 1;
        for (k=count-1;k>=0;--k) if (calls[k].last > i) {
            calls[count].parent=k; calls[count].depth=calls[k].depth+1; break;
        }
        if (calls[count].depth > 3) { EmitError(MAX_C_NESTING); return -1; }
        if (calls[count].parent == -1) { ++roots; root=count; }
        ++count;
    }
    if (!count) return 0;
    /* These directives arrange their condition at another control-flow site.
     * Emitting a call before the directive would execute it in the wrong block. */
    if (tokens[0].tokval == T_DOT_WHILE || tokens[0].tokval == T_DOT_ELSEIF) {
        EmitErr(SYNTAX_ERROR_EX,"inline calls in .WHILE/.ELSEIF conditions require explicit control flow");
        return -1;
    }
    for (i=0;i<count;++i)
        if (calls[i].proc->sym.langtype == LANG_SYSVCALL) sysv=TRUE;
    /* Registers read by the enclosing expression survive every call too.
     * A plain MOV/LEA register destination is written, not consumed. */
    if (!directInvoke && roots == 1 && calls[root].first) {
        for (j=0;j<Token_Count;++j) {
            if (j == calls[root].first) { j=calls[root].last; continue; }
            if (j == 1 && (tokens[0].tokval == T_LEA || strncasecmp(tokens[0].string_ptr,"mov",3) == 0 || strncasecmp(tokens[0].string_ptr,"vmov",4) == 0)) continue;
            if (CallOperandVolatile(&tokens[j],sysv)) {
                EmitErr(SYNTAX_ERROR_EX,"volatile register operand conflicts with value-producing call"); return -1;
            }
        }
    }
    /* A single flat expression still needs an explicit return contract. */
    if (count == 1 && !directInvoke) {
        if (calls[0].first && !CallReturn(&calls[0])) return -1;
        return 0;
    }
    if (!directInvoke && roots != 1) { EmitError(MAX_C_CALLS); return -1; }
    if (count - (directInvoke ? 0 : 1) > CALL_RESULT_LIMIT) {
        EmitErr(SYNTAX_ERROR_EX,"too many nested-call results (maximum 32)"); return -1;
    }
    if (!CurrProc || ModuleInfo.Ofssize == USE16 || ModuleInfo.prologuemode != PEM_DEFAULT ||
        (ModuleInfo.Ofssize == USE64 && CurrProc->e.procinfo->isframe && !ModuleInfo.frame_auto)) {
        EmitErr(SYNTAX_ERROR_EX,"nested calls require an automatic procedure frame"); return -1;
    }
    for (i=0;i<count;++i) if (calls[i].parent == -1) CallOrder(i,calls,count,&order);
    for (i=0;i<count;++i) {
        bool value = directInvoke || i != root || calls[i].first != 0;
        if (value && !CallReturn(&calls[i])) return -1;
        /* Values consumed after any child/sibling call cannot depend on a
         * volatile register, even through a memory-address expression. */
        if (!calls[i].order) continue;
        for (j=calls[i].first+2;j<calls[i].last;++j) {
            for (k=0;k<count;++k) if (calls[k].parent == i && calls[k].first == j) break;
            if (k<count) { j=calls[k].last; continue; }
            if (CallOperandVolatile(&tokens[j],sysv) && !CallDerefScratch(tokens,calls[i].first,j)) {
                EmitErr(SYNTAX_ERROR_EX,"volatile register operand conflicts with nested call"); return -1;
            }
        }
    }
    if (directInvoke) {
        for (j=1;j<Token_Count;++j) {
            for (k=0;k<count;++k) if (calls[k].parent == -1 && calls[k].first == j) break;
            if (k<count) { j=calls[k].last; continue; }
            if (CallOperandVolatile(&tokens[j],sysv) && !CallDerefScratch(tokens,0,j)) {
                EmitErr(SYNTAX_ERROR_EX,"volatile register operand conflicts with nested call"); return -1;
            }
        }
    }
    /* Assign stable slots before rendering. Results are reused between source
     * statements, but never between simultaneously live calls. */
    for (i=0;i<count;++i) if (directInvoke || i != root) {
        calls[i].temp=ProcCallTemp(slot++,calls[i].size);
        if (!calls[i].temp) { EmitErr(SYNTAX_ERROR_EX,"nested-call temporary unavailable"); return -1; }
        sprintf(calls[i].replacement,"%s ptr %s",calls[i].type,calls[i].temp->name);
    }
    for (k=0;k<count;++k) for (i=0;i<count;++i) if (calls[i].order==k && (directInvoke || i!=root)) {
        char *out=generated[k];
        if (calls[i].helper) strcpy(out,calls[i].helper == 1 ? "_SINVOKE " :
            (calls[i].helper == 2 ? "_DEREF " : (calls[i].helper == 3 ? "_RAWINVOKE " : "_RAWRINVOKE ")));
        else {
            strcpy(out,"invoke ");
            if (!CallAppend(out,tokens[calls[i].first].tokpos,
                            tokens[calls[i].first+1].tokpos-tokens[calls[i].first].tokpos)) return -1;
        }
        if (calls[i].last > calls[i].first+2) {
            if (!calls[i].helper) strcat(out,",");
            if (!CallRender(out,tokens[calls[i].first+1].tokpos+1,tokens[calls[i].last].tokpos,
                            i,calls,count,tokens)) return -1;
        }
        {
            char addressed[MAX_LINE_LEN];
            const char *scan=out, *start=out;
            addressed[0]=0;
            while (*scan) {
                if (*scan == '"' || *scan == 39) { scan=SkipCallString((char *)scan); continue; }
                if (*scan == '&') {
                    if (!CallAppend(addressed,start,scan-start) || !CallAppend(addressed,"ADDR ",5)) return -1;
                    start=++scan;
                } else ++scan;
            }
            if (!CallAppend(addressed,start,scan-start)) return -1;
            strcpy(out,addressed);
        }
        sprintf(stores[k],"%s %s,%s",calls[i].store,calls[i].replacement,calls[i].reg);
    }
    rewritten[0]=0;
    if (directInvoke) {
        if (!CallRender(rewritten,source,source+strlen(source),-1,calls,count,tokens)) return -1;
    } else {
        const char *begin=tokens[calls[root].first+1].tokpos+1;
        const char *end=tokens[calls[root].last].tokpos;
        if (!CallAppend(rewritten,source,begin-source) ||
            !CallRender(rewritten,begin,end,root,calls,count,tokens) ||
            !CallAppend(rewritten,end,strlen(end))) return -1;
    }
    for (k=0;k<slot;++k) { AddLineQueue(generated[k]); AddLineQueue(stores[k]); }
    RunSourceLineQueue(FALSE);
    strcpy(line,rewritten);
    Token_Count=Tokenize(line,0,tokens,TOK_RESCAN);
    return 1;
}

static void ExpandHllCalls(char *line, struct asm_tok tokenarray[], bool inParam, int argIdx, bool inExpr)
{
	int i, j;
	struct dsym *sym;
	char newline[MAX_LINE_LEN];
	int clIdx, opIdx;
	char *p = newline;
	char uCnt = 0;

	strcpy(newline, line);

	for (i = 0;i < Token_Count;i++)
	{
		if (tokenarray[i].token == T_ID)
		{
			sym = (struct dsym *)SymCheck(tokenarray[i].string_ptr);

			sym = (struct dsym *)TraverseEquate((struct asym *)sym); /* We may have an equate chain that points to a proc, as we expand here before macro substitution we need to consider this */

			if(sym && (sym->sym.isproc || (sym->sym.isfunc && sym->sym.state == SYM_EXTERNAL)) && tokenarray[i+1].tokval != T_PROC && tokenarray[i+1].tokval != T_PROTO && 
				tokenarray[i+1].tokval != T_ENDP && tokenarray[i+1].tokval != T_EQU && tokenarray[i+1].token == T_OP_BRACKET) 
			{ 
		
				/* Scan backwards to check if we're in an HLL expression or call parameter */
				if (i > 0)
				{
					for (j = i - 1;j >= 0;j--)
					{
						if (tokenarray[j].token == T_DIRECTIVE && (tokenarray[j].dirtype == DRT_HLLSTART || tokenarray[j].dirtype == DRT_HLLEND))
						{
							inExpr = TRUE;
							break;
						}
						else if ((tokenarray[j].token == T_DIRECTIVE && tokenarray[j].dirtype == DRT_INVOKE) ||
							strcmp(tokenarray[j].string_ptr, "arginvoke") == 0 ||
							strcmp(tokenarray[j].string_ptr, "_INVOKE") == 0 ||
							strcmp(tokenarray[j].string_ptr, "_I") == 0 ||
							strcmp(tokenarray[j].string_ptr, "_VINVOKE") == 0 ||
							strcmp(tokenarray[j].string_ptr, "_SINVOKE") == 0 ||
							strcmp(tokenarray[j].string_ptr, "_V") == 0 ||
							strcmp(tokenarray[j].string_ptr, "_DEREF") == 0 ||
							strcmp(tokenarray[j].string_ptr, "_DEREFI") == 0 ||
							strcmp(tokenarray[j].string_ptr, "uinvoke") == 0)
						{
							inParam = TRUE;
							break;
						}
					}
				}

				/* If we've identifed a Proc Name, there are several more cases where it must not be expanded */
				if (i > 0 && (tokenarray[i - 1].token == T_COLON || tokenarray[i - 1].tokval == T_EQU ||  //(tokenarray[i - 1].token == T_COMMA && !inParam) ||
					tokenarray[i - 1].tokval == T_INVOKE || tokenarray[i - 1].token == T_INSTRUCTION || tokenarray[i - 1].tokval == T_ADDR ||
					tokenarray[i - 1].tokval == T_OFFSET || tokenarray[i - 1].tokval == T_PTR || tokenarray[i - 1].tokval == T_END || 
					(tokenarray[i - 1].token == T_DIRECTIVE && tokenarray[i - 1].dirtype == DRT_DATADIR) || tokenarray[i - 1].token == T_UNARY_OPERATOR ||  tokenarray[i - 1].tokval == T_PROC ||
					strcmp(tokenarray[i - 1].string_ptr,"arginvoke") == 0 || strcmp(tokenarray[i - 1].string_ptr, "@what") == 0)) continue;
					
				// Allow expansion in an instruction.
				if (i > 0 && tokenarray[i - 1].token == T_COMMA)
					inExpr = TRUE;
					
				// Allow expansion in a memory address [].
				if (i > 0)
				{
					for (j = i - 1;j >= 0;j--)
					{
						if (tokenarray[j].token == T_OP_SQ_BRACKET)
						{
							inExpr = TRUE;
							break;
						}
					}
				}

				/* Verify c-style procedure call has matching brackets */
				opIdx = i + 1;
				clIdx = VerifyBrackets(tokenarray, opIdx, inParam);
				if (clIdx == -1)
					return;
					

				/* scan all tokens between opIdx and clIdx and replace & operator with ADDR */
				for (j = opIdx; j < clIdx; j++)
				{
					if (*(tokenarray[j].string_ptr) == '&')
					{
						// token identifier begins with address of operator.
						//strcpy(tokenarray[j].string_ptr, "ADDR ");
						tokenarray[j].string_ptr = "ADDR ";
					}
				}

				if (!inParam && !inExpr)
				{
					/* Shift all the tokens up to remove the close bracket and make space for invoke */
					for (j = clIdx; j > i; j--)
						tokenarray[j] = tokenarray[j - 1];

					if (clIdx > opIdx + 1)
					{
						tokenarray[clIdx + 1].token = T_FINAL;
						tokenarray[opIdx + 1].string_ptr = ",";
						tokenarray[opIdx + 1].token = T_COMMA;
					}
					/* Proc with no params */
					else
					{
						tokenarray[opIdx + 1].string_ptr = "";
						tokenarray[opIdx + 1].token = T_FINAL;
					}
					tokenarray[i].token = T_DIRECTIVE;
					tokenarray[i].tokval = T_INVOKE;
					tokenarray[i].dirtype = DRT_INVOKE;
					tokenarray[i].string_ptr = "invoke";
				}
				else
				{
					/* Shift all the tokens up to remove the close bracket and make space for invoke */
					for (j = Token_Count; j > i; j--)
						tokenarray[j] = tokenarray[j - 1];

					/* Shift all the tokens up to add new open bracket */
					for (j = Token_Count+1; j > i; j--)
						tokenarray[j] = tokenarray[j - 1];

					Token_Count+=2;
					tokenarray[Token_Count].string_ptr = "";
					tokenarray[Token_Count].token = T_FINAL;
					if (clIdx > opIdx + 1)
					{
						tokenarray[opIdx + 2].string_ptr = ",";
						tokenarray[opIdx + 2].token = T_COMMA;
					}
					else
					{
						tokenarray[opIdx + 2].string_ptr = " ";
					}
					tokenarray[i].token = T_ID;
					tokenarray[i].tokval = 0;
					tokenarray[i].dirtype = 0;
					if (inExpr && !inParam)
					{
						tokenarray[i].string_ptr = "uinvoke";
						tokenarray[i + 1].string_ptr = "(";
						tokenarray[i + 1].token = '(';
						uCnt++; // Increment count of uinvokes, as we only allow 1 per expression.
						if (uCnt > 1)
						{
							EmitErr(MAX_C_CALLS);
						}
					}
					else if (inParam)
					{
                        EmitErr(SYNTAX_ERROR_EX,"nested call requires a directly resolved typed procedure");
                        return;
					}
				}
					
				i += 2;
					
				/* Rebuild string */
				for (j = 0;j <= Token_Count; j++)
				{
					if (tokenarray[j].tokval == T_PTR)
					{
						// Ensure we put a space between type and PTR UASM 2.50
						strcpy(p, " ");
						p++;
					}
					{
                        const char *text = tokenarray[j].string_ptr;
                        size_t k, length = strlen(text);
                        bool quoted = tokenarray[j].token == T_STRING && tokenarray[j].string_delim == '"';
                        /* Retokenization must not merge adjacent words (for example,
                         * flags OR mask, SIZEOF value, or DWORD PTR value). Keep
                         * punctuation adjacent, including qualified names and members. */
                        if (length && p > newline && is_valid_id_char(p[-1]) &&
                            is_valid_id_char(text[0])) {
                            if (p - newline >= MAX_LINE_LEN - 3) {
                                EmitError(STRING_OR_TEXT_LITERAL_TOO_LONG);
                                return;
                            }
                            *p++ = ' ';
                        }
                        tokenarray[j].tokpos = p;
                        for (k = 0; k < length; k++) {
                            if (p - newline >= MAX_LINE_LEN - 3) {
                                EmitError(STRING_OR_TEXT_LITERAL_TOO_LONG);
                                return;
                            }
                            *p++ = text[k];
                            if (quoted && k && k+1 < length && text[k] == '"') *p++ = '"';
                        }
                        *p = 0;
                    }
					if (j == 0 || tokenarray[j].tokval == T_PTR || tokenarray[j].tokval == T_ADDR || tokenarray[j].tokval == T_OFFSET)
					{
						strcpy(p, " ");
						p++;
					}
				}

				/* Reset string pointer*/
				p = newline;
			}
		}
	}

	/* Transfer new source line back for token rescan */
	strcpy(line, newline);
}

static bool PossibleCallExpansion(struct asm_tok tokenarray[])
{
	bool result = FALSE;
	bool gotOp = FALSE;
	bool gotCl = FALSE;
	int i = 0;
	for (i = 0;i < Token_Count;i++)
	{
		if (tokenarray[i].token == T_POINTER)
		{
			result = TRUE;
			break;
		}
		if (tokenarray[i].token == T_OP_BRACKET && i > 0)
		{
			if (tokenarray[i - 1].token == T_ID)
			{
				gotOp = TRUE;
			}
		}
		if (tokenarray[i].token == T_CL_BRACKET)
			gotCl = TRUE;
	}

	if (gotOp && gotCl)
		result = TRUE;

	return(result);
}

/*
Perform evaluation of any items required before pre-processing (ie: substitution or macro expansion).
-> Evaluation of inline RECORD items to allow them to be handled by invoke/macros etc.
*/
void EvaluatePreprocessItems(char *line, struct asm_tok tokenarray[])
{
	int i;
	struct dsym *recsym;
	struct expr opndx[1];

	memset(&opndx, 0, sizeof(opndx));

	/* pre parse inline records and c-style procedure calls UASM v2.46 */
	for (i = 0;i < Token_Count; i++)
	{
		/* only a token of type ID could possibly be an inline record */
		if (tokenarray[i].token == T_ID)
		{
			recsym = (struct dsym *)SymCheck(tokenarray[i].string_ptr);
			if (recsym && recsym->sym.typekind == TYPE_RECORD && CurrProc)
			{
				if (CurrSeg && (strcmp(CurrSeg->sym.name, "_TEXT") == 0 || strcmp(CurrSeg->sym.name, "_flat") == 0))
				{
					if (EvalOperand(&i, tokenarray, Token_Count, &opndx[0], 0) == ERROR)
						EmitErr(INVALID_INSTRUCTION_OPERANDS);
					recsym->sym.used = FALSE;
				}
			}

		}
	}
}

/* PreprocessLine() is the "preprocessor".
 * 1. the line is tokenized with Tokenize(), Token_Count set
 * 2. (text) macros are expanded by ExpandLine()
 * 3. "preprocessor" directives are executed
 */
int PreprocessLine( char *line, struct asm_tok tokenarray[] )
/***********************************************************/
{
    int i;
	char cline[MAX_LINE_LEN];

	ModuleInfo.CurrComment = NULL;
    ModuleInfo.line_flags = 0;

    Token_Count = Tokenize( line, 0, tokenarray, TOK_DEFAULT );

#ifdef DEBUG_OUT
    cntppl0++;
    if ( ModuleInfo.GeneratedCode )
        DebugMsg1(("PreprocessLine: >%s<\n", line ));
    else
        DebugMsg1(("PreprocessLine(%s): >%s< cmt=%s\n", GetTopSrcName(), line, ModuleInfo.CurrComment ? ModuleInfo.CurrComment : "" ));
#endif

#if REMOVECOMENT == 0
    if ( Token_Count == 0 && ( CurrIfState == BLOCK_ACTIVE || ModuleInfo.listif ) )
        LstWriteSrcLine();
#endif

    if ( Token_Count == 0 )
        return( 0 );

#ifdef DEBUG_OUT
    /* option -np, skip preprocessor? */
    if ( Options.skip_preprocessor )
        return( Token_Count );
#endif

	if (!Options.nomlib && Options.hlcall && CurrIfState == BLOCK_ACTIVE)
	{
		// Hll and Object style call expansion is only valid inside a code section, AND if the line contains ( ) or ->.
		if (CurrSeg && (strcmp(CurrSeg->sym.name, "_TEXT") == 0 || strcmp(CurrSeg->sym.name, "_flat") == 0) && PossibleCallExpansion( tokenarray ))
		{
			strcpy(cline, line);
			ExpandStaticObjCalls(cline, tokenarray);
			if (strcmp(cline, line) != 0)
			{
				strcpy(line, cline);
				Token_Count = Tokenize(line, 0, tokenarray, TOK_RESCAN);
			}
            {
                unsigned errors = ModuleInfo.g.error_count;
                ExpandObjCalls(cline, tokenarray);
                if (ModuleInfo.g.error_count != errors) return 0;
            }
			if (strcmp(cline, line) != 0)
			{
				strcpy(line, cline);
				Token_Count = Tokenize(line, 0, tokenarray, TOK_RESCAN);
			}
			if (LowerBoundedCalls(cline, tokenarray) < 0) return 0;
            ExpandHllCalls(cline, tokenarray, FALSE, 0, FALSE);
			if (strcmp(cline, line) != 0)
			{
				strcpy(line, cline);
				Token_Count = Tokenize(line, 0, tokenarray, TOK_RESCAN);
			}
		}
	}

    if (!MacroLevel && !ModuleInfo.GeneratedCode && CurrIfState == BLOCK_ACTIVE &&
        tokenarray[0].token == T_ID && strstr(tokenarray[0].string_ptr, "::") &&
        (tokenarray[1].token == T_COLON || tokenarray[1].token == T_DBL_COLON ||
         tokenarray[1].token == T_STYPE ||
         (tokenarray[1].token == T_DIRECTIVE && (GetValueSp(tokenarray[1].tokval) & DF_LABEL)))) {
        EmitErr(SYNTAX_ERROR_EX, "qualified definition: use a NAMESPACE block");
        return 0;
    }
	EvaluatePreprocessItems( line, tokenarray );

    /* CurrIfState != BLOCK_ACTIVE && Token_Count == 1 | 3 may happen
     * if a conditional assembly directive has been detected by Tokenize().
     * However, it's important NOT to expand then */
    if ( CurrIfState == BLOCK_ACTIVE ) 
	{
        if ( ( tokenarray[Token_Count].bytval & TF3_EXPANSION ? ExpandText( line, tokenarray, TRUE ) : ExpandLine( line, tokenarray ) ) < NOT_ERROR )
            return( 0 );
    }

    DebugCmd( cntppl1++ );

    i = 0;
    if ( Token_Count > 2 && ( tokenarray[1].token == T_COLON || tokenarray[1].token == T_DBL_COLON ) )
        i = 2;

    /* handle "preprocessor" directives:
     * IF, ELSE, ENDIF, ...
     * FOR, REPEAT, WHILE, ...
     * PURGE
     * INCLUDE
     * since v2.05, error directives are no longer handled here!
     */
    if ( tokenarray[i].token == T_DIRECTIVE && tokenarray[i].dirtype <= DRT_INCLUDE ) 
	{
        /* if i != 0, then a code label is located before the directive */
        if ( i > 1 ) 
		{
            if ( ERROR == WriteCodeLabel( line, tokenarray ) )
                return( 0 );
        }
        directive_tab[tokenarray[i].dirtype]( i, tokenarray );
        return( 0 );
    }

    /* handle preprocessor directives which need a label */
    if ( tokenarray[0].token == T_ID && tokenarray[1].token == T_DIRECTIVE ) 
	{
        struct asym *sym;
        switch ( tokenarray[1].dirtype ) {
        case DRT_EQU:
            /*
             * EQU is a special case:
             * If an EQU directive defines a text equate
             * it MUST be handled HERE and 0 must be returned to the caller.
             * This will prevent further processing, nothing will be stored
             * if FASTPASS is on.
             * Since one cannot decide whether EQU defines a text equate or
             * a number before it has scanned its argument, we'll have to
             * handle it in ANY case and if it defines a number, the line
             * must be stored and, if -EP is set, written to stdout.
             */
            if ( sym = CreateConstant( tokenarray ) ) {
                if ( sym->state != SYM_TMACRO ) {
#if FASTPASS
                    if ( StoreState ) FStoreLine( 0 );
#endif
                    if ( Options.preprocessor_stdout == TRUE )
                        WritePreprocessedLine( line );
                }
                /* v2.03: LstWrite() must be called AFTER StoreLine()! */
                if ( ModuleInfo.list == TRUE ) {
                    LstWrite( sym->state == SYM_INTERNAL ? LSTTYPE_EQUATE : LSTTYPE_TMACRO, 0, sym );
                }
            }
            return( 0 );
        case DRT_MACRO:
        case DRT_CATSTR: /* CATSTR + TEXTEQU directives */
        case DRT_SUBSTR:
            directive_tab[tokenarray[1].dirtype]( 1, tokenarray );
            return( 0 );
        }
    }

    DebugCmd( cntppl2++ );
    return( Token_Count );
}

