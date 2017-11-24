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

/* We only allow a single level of nested calls */
static void VerifyNesting(char *line, bool exprBracket)
{
	int depth = 0;
	int maxdepth = (exprBracket) ? 3 : 2;
	
	// Reduce allowed nesting for system-v calls as arginvoke doesn't support it yet.
	if ((Options.output_format == OFORMAT_ELF || Options.output_format == OFORMAT_MAC) && Options.sub_format == SFORMAT_64BIT)
		maxdepth = (exprBracket) ? 2 : 1;
	
	// Same for 32bit code for now..
	if (Options.sub_format != SFORMAT_64BIT)
		maxdepth = (exprBracket) ? 2 : 1;

	char *p = line;
	while (*p)
	{
		if (*p == '(')
			depth++;
		if (*p == ')')
			depth--;
		if (depth > maxdepth)
		{
			EmitErr(MAX_C_NESTING);
			return;
		}
		p++;
	}
}

static void ExpandObjCalls(char *line, struct asm_tok tokenarray[])
{
	int i, j;
	struct dsym *sym;
	struct asym *type;
	char newline[MAX_LINE_LEN];
	char preline[MAX_LINE_LEN];
	char addrStr[MAX_LINE_LEN];
	char *pSrc;
	char *pDst;
	int len;
	bool inParam = FALSE;
	bool inExpr = FALSE;
	bool hasExprBracket = FALSE;
	bool foundType = FALSE;
	bool ptrInvocation = FALSE;
	bool gotOpen = FALSE;
	bool gotClose = FALSE;

	/* HLL c-style obj calls can only exist inside code sections */
	if (CurrSeg && strcmp(CurrSeg->sym.name, "_TEXT") != 0)
		return;

	memset(&newline, 0, MAX_LINE_LEN);
	memset(&addrStr, 0, MAX_LINE_LEN);
	strcpy(&newline, line);
	strcpy(&preline, line);
	
	for (i = 0;i < Token_Count;i++)
	{
		foundType = FALSE;
		ptrInvocation = FALSE;
		gotOpen = FALSE;
		gotClose = FALSE;
		if (tokenarray[i].token == T_ID)
		{
			sym = SymSearch(tokenarray[i].string_ptr);
			if ( sym && 
				sym->sym.target_type &&
				sym->sym.target_type > 0x200000 &&
				sym->sym.target_type->isClass )
			{
				// Found pointer operator.
				if (i < Token_Count - 4 && tokenarray[i + 1].token == T_POINTER && tokenarray[i + 3].token == T_OP_BRACKET)
				{
					foundType = TRUE;
					type = sym->sym.target_type;
				}
			}
			else if (sym &&
				sym->sym.type &&
				sym->sym.type->target_type &&
				sym->sym.type->target_type > 0x200000 &&
				sym->sym.type->target_type->isClass)
			{
				// Found pointer operator.
				if (i < Token_Count - 4 && tokenarray[i + 1].token == T_POINTER && tokenarray[i + 3].token == T_OP_BRACKET)
				{
					foundType = TRUE;
					type = sym->sym.type->target_type;
				}
			}
			else if (sym && sym->sym.isClass && tokenarray[i-1].token == T_DOT && tokenarray[i-2].token == T_CL_SQ_BRACKET)
			{
				for (j = i + 1;j < Token_Count;j++)
				{
					if (tokenarray[j].token == T_OP_BRACKET)
						gotOpen = TRUE;
					if (tokenarray[j].token == T_CL_BRACKET)
						gotClose = TRUE;
					if (gotOpen && gotClose)
						break;
				}
				if (gotOpen && gotClose)
				{
					foundType = TRUE;
					type = sym;
					ptrInvocation = TRUE;
				}
			}

			if (foundType)
			{
				/* Scan backwards to check if we're in an HLL expression or call parameter */
				if (i > 0)
				{
					for (j = i - 1;j >= 0;j--)
					{
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
							strcmp(tokenarray[j].string_ptr, "uinvoke") == 0)
						{
							inParam = TRUE;
							break;
						}
					}
				}

				pSrc = tokenarray[0].tokpos;
				if (!ptrInvocation)
					j = tokenarray[i].tokpos - pSrc;
				else
				{
					for (j = i;j >= 0;j--)
					{
						if (tokenarray[j].token == T_OP_SQ_BRACKET)
							break;
					}
					j = tokenarray[j].tokpos - pSrc;
				}
				pDst = &preline;
				while (j-- > 0)
					*pDst++ = *pSrc++;
				*pDst = 0;
				if (!inParam && !inExpr)
				{
					if (ptrInvocation)
					{
						pDst = tokenarray[i - 2].tokpos;
						pSrc = tokenarray[i - 2].tokpos - 1;
						while (pSrc > tokenarray[0].tokpos)
						{
							if (*pSrc == '[')
								break;
							pSrc--;
						}
						len = pDst - pSrc;
						pDst = &addrStr;
						for (;len >= 0;len--)
							*pDst++ = *pSrc++;
						sprintf(newline, "%s _VINVOKE %s,%s,%s,", preline, addrStr, type->name, tokenarray[i + 2].string_ptr);
					}
					else
						sprintf(newline, "%s _VINVOKE %s,%s,%s,", preline, sym->sym.name, type->name, tokenarray[i + 2].string_ptr);
					pSrc = tokenarray[i + 3].tokpos + 1;
					len = strlen(newline);
					pDst = &(newline[len]);
					while (*pSrc != 0 && *pSrc != ')')
						*pDst++ = *pSrc++;
				}
				else
				{
					if (ptrInvocation)
					{
						pDst = tokenarray[i - 2].tokpos;
						pSrc = tokenarray[i - 2].tokpos - 1;
						while (pSrc > tokenarray[0].tokpos)
						{
							if (*pSrc == '[')
								break;
							pSrc--;
						}
						len = pDst - pSrc;
						pDst = &addrStr;
						for (;len >= 0;len--)
							*pDst++ = *pSrc++;
						sprintf(newline, "%s _V(%s,%s,%s,", preline, addrStr, type->name, tokenarray[i + 2].string_ptr);
					}
					else
						sprintf(newline, "%s _V(%s,%s,%s,", preline, sym->sym.name, type->name, tokenarray[i + 2].string_ptr);
					pSrc = tokenarray[i + 3].tokpos + 1;
					len = strlen(newline);
					pDst = &(newline[len]);
					if (!ptrInvocation)
					{
						while (*pSrc != 0)
							*pDst++ = *pSrc++;
					}
					else
					{
						while (*pSrc != 0 && *pSrc != ')')
							*pDst++ = *pSrc++;
					}
				}
			}
		}
	}

	strcpy(line, &newline);
}

static void ExpandHllCalls(char *line, struct asm_tok tokenarray[], bool inParam, int argIdx, bool inExpr)
{
	int i, j;
	struct dsym *sym;
	char newline[MAX_LINE_LEN];
	int clIdx, opIdx;
	int tokenCount;
	struct asm_tok *tokenarray2;
	char *p = &newline;
	char idxStack[] = { 0, 0, 0, 0 };
	int stackPt = -1;
	char idxline[MAX_LINE_LEN];
	char invCnt = 1;
	bool hasExprBracket = FALSE;
	bool expandedCall = FALSE;
	char uCnt = 0;

	strcpy(&newline, line);
	memset(&idxline, 0, MAX_LINE_LEN);

	for (i = 0;i < Token_Count;i++)
	{
		if (tokenarray[i].token == T_ID)
		{
			sym = SymSearch(tokenarray[i].string_ptr);
			if(sym && sym->sym.isproc && tokenarray[i+1].tokval != T_PROC && tokenarray[i+1].tokval != T_PROTO && 
				tokenarray[i+1].tokval != T_ENDP && tokenarray[i+1].tokval != T_EQU && tokenarray[i+1].token == T_OP_BRACKET) 
			{ 
				/* HLL c-style calls can only exist inside code sections */
				if (CurrSeg && strcmp(CurrSeg->sym.name, "_TEXT") == 0)
				{
		
					/* Scan backwards to check if we're in an HLL expression or call parameter */
					if (i > 0)
					{
						for (j = i - 1;j >= 0;j--)
						{
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
					if (tokenarray[i - 1].token == T_COMMA)
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
					
					expandedCall = TRUE;

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
							tokenarray[i].string_ptr = "arginvoke(%%,%%,";
							tokenarray[i + 1].string_ptr = ""; 
							tokenarray[i + 1].token = 0; 
						}
					}
					
					i += 2;
					
					/* Rebuild string */
					for (j = 0;j <= Token_Count; j++)
					{
						strcpy(p, tokenarray[j].string_ptr);
						tokenarray[j].tokpos = p;
						p += strlen(tokenarray[j].string_ptr);
						if (j == 0 || tokenarray[j].tokval == T_ADDR || tokenarray[j].tokval == T_OFFSET)
						{
							strcpy(p, " ");
							p++;
						}
					}

					/* Reset string pointer*/
					p = &newline;
				}
			}
		}
	}

	/* Scan string and insert argument numbers */
	// MyProc(MyProc3(), 20)	 MyProc(10, MyProc4())
	// invoke MyProc,arginvoke(0,MyProc3),20
	// invoke MyProc,10,arginvoke(0,MyProc4)
	//find invoke, increment stackPt and set argno 1... for every comma not in () increment argno
	//find uinvoke or arginvoke increment stackPt and set argno 1... for every comma after opIdx and before closeIdx and not in () increment argno... at closeIdx decrement StackPt
	//at each step write argno to idxline string
	//finally replace place-holder with idxline value
	if (expandedCall)
	{
		p = &newline;
		p = strstr(p, "invoke"); // even if the line only contains uinvoke, such as in an HLL expression this will still find it.
		if (p != NULL)
		{
			bool inBrackets = FALSE;
			j = (int)(p - (char *)&newline);
			stackPt++;
			idxStack[stackPt] = 0;
			while (*p)
			{
				idxline[j++] = idxStack[stackPt];
				if (*p == '(')
					inBrackets = TRUE;
				if (*p == ')')
					inBrackets = FALSE;
				if (!inBrackets && *p == ',')
					idxStack[stackPt]++;
				p++;
			}
		}
		p = &newline;
		p = strstr(p, "arginvoke(");
		j = (int)(p - (char *)&newline);
		while (p)
		{
			if (idxline[j] == 0) idxline[j] = 1;
			*(p + 10) = (char)(((idxline[j] & 0xf0) >> 4) + 48);
			*(p + 11) = (char)(((idxline[j] & 0x0f)) + 48);
			*(p + 13) = (char)(((invCnt & 0xf0) >> 4) + 48);
			*(p + 14) = (char)(((invCnt & 0x0f)) + 48);
			p = strstr(p + 1, "arginvoke(");
			invCnt++;
			j = (int)(p - (char *)&newline);
		}

		/* Ensure max nesting depth isn't exceeded */
		VerifyNesting(&newline, hasExprBracket);
	}

	/* Transfer new source line back for token rescan */
	strcpy(line, &newline);
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
			recsym = SymSearch(tokenarray[i].string_ptr);
			if (recsym && recsym->sym.typekind == TYPE_RECORD && CurrProc)
			{
				if (EvalOperand(&i, tokenarray, Token_Count, &opndx[0], 0) == ERROR)
				{
					EmitErr(INVALID_INSTRUCTION_OPERANDS);
					return(FALSE);
				}
			}
			if (recsym)
				recsym->sym.used = FALSE;
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

	if (!Options.nomlib)
	{
		strcpy(&cline, line);
		ExpandObjCalls(&cline, tokenarray, FALSE, 0, FALSE);
		if (strcmp(&cline, line) != 0)
		{
			strcpy(line, &cline);
			Token_Count = Tokenize(line, 0, tokenarray, TOK_RESCAN);
		}
		strcpy(&cline, line);
		ExpandHllCalls(&cline, tokenarray, FALSE, 0, FALSE);
		if (strcmp(&cline, line) != 0)
		{
			strcpy(line, &cline);
			Token_Count = Tokenize(line, 0, tokenarray, TOK_RESCAN);
		}
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

