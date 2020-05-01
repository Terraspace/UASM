; MREAL macros, by qWord, 2014
; Version 1.0.4
; This file is best viewed with a fixed-width font and a tab size of 4.
;
; Overview
;    The MREAL macros allows arbitrary** precision floating point arithmetic while assembling. The values are stored
;    in a collection of equates, following a strict naming pattern. For the further documentation this equates are called 
;    "MREAL value" or "MREAL variable".
;    The goal of the macros is to implement a subset of the IEEE 754-2008 standard.
;    (** multiples of 16 bit: 16,32,48,...)
;
;    Currently the following features are implemented:
;     - correctly rounded arithmetic: addition, subtraction, multiplication, division, square root and fused multiply accumulate.
;     - rounding modes: round to nearest ties to even and ties away from zero, round toward +Infinity (=round up),
;                       round toward -Infinity (=round down) and round toward zero (=truncate).
;
;    The most important difference to IEEE 754 are:
;     - precision: multiplies of 16: 16, 32, 48, 64, ... bit
;       (However, single and double precision could be simulated if needed)
;     - denormal numbers are not supported
;     - there is no negative zero (-0) **
;     - propagation of special values: +-Infinity as input
;       always produce NaN as result. **
;
;       ** This might be implemented in future versions as required by IEEE754-2008.
;    
;
; Internal representation of MREAL values
;
;            equate          |   type    |  description
;    ------------------------+-----------+-------------------------------------------------------------------------------------
;    MREAL_&name&_exp        |  Integer  |  exponent
;    MREAL_&name&_w0...(N-1) |  WORD     |  unsigned mantissa bits, starting with the most significant WORD. N = MREAL_XDIM
;                            |           |  The mantissa is normalized to 2^(-1) = 0.5, which is the MSB and is always present.
;                            |           |  The LSB is 2^(-MREAL_XDIM*16). Denormal numbers are not supported.
;                            |           |  Only the low words of the equates are used by the macros, but it is expected that
;                            |           |  the high words are zero - nonzero high words cause unpredictable behavior!
;                            |           | 
;    MREAL_&name&_flg        |  DWORD    |  flags:
;                            |           |    value   | description  |  combinable?
;                            |           |  ----------+--------------+---------------
;                            |           |  00000001h |  Zero        | no 
;                            |           |  00000002h |  Infinity    | with Sign
;                            |           |  00000004h |  NaN         | no
;                            |           |  80000000h |  Sign        | with Infinity
;                            |           |    others  |  reserved=0  |
;                            |           | 
;                            |           |  For the flags "zero", "Infinity" and "NaN" the exponent and mantissa are ignored.
;                            |           |
;
;    Internally used constants may have two additional equates:
;
;            equate          |   type    |  description
;    ------------------------+-----------+--------------------------------------------------------------------------
;       MREAL_&name&_n       |  DWORD    | number of mantissa WORDs.
;       MREAL_&name&_nSig    |  DWORD    | number of nonzero mantissa WORDs, starting with the most significant WORD.
;   
;    Examples:
;      The following examples assumes that MREAL_XDIM = 1, means 16 bit precision. The MREAL name\ID is "X".                                     
;      value = +1.0 :
;              MREAL_X_flg = 0
;              MREAL_X_exp = 1
;              MREAL_X_w0  = 8000h
;              ==> +(0.5)*2^1 == 0.5*2 == 1.0
;      value = -3.0 :
;              MREAL_X_flg = 80000000h
;              MREAL_X_exp = 2
;              MREAL_X_w0  = 0C000h
;              ==> -(0.75)*2^2 == -0.75*4 == -3.0
;      value = 0.0  :
;              MREAL_X_flg = 1
;              MREAL_X_exp = arbitrary value
;              MREAL_X_w0  = arbitrary value
;
; Rounding modes
;    The macros support 5 different rounding modes:
;     round:
;           - to nearest with tie-breaking rules:
;              - ties to even        (round half to even, IEEE754 default for binary formats)
;              - ties away from zero (round half away from zero, actual IEEE754-2008 requires this mode only for decimal formats)
;           - toward -Infinity (down)
;           - toward +Infinity (up)
;           - toward zero (truncate)
;    
;   The default rounding mode is "round to nearest, ties to even".
;
; Under- and Overflow
;    Exponent Over- and Underflow are detected after
;    the actual operation. In such cases the result is rounded
;    according to IEEE754-2008.
; 
; Detecting inexact operations
;    If the global equate MREAL_TEST_INEXACT is nonzero, all arithmetic, rounding and conversion 
;    operations does set the equate MREAL_INEXACT to -1 if the result is not exact representable
;    in the current number format (precision and exponent setting).
;    By default the test is disabled (MREAL_TEST_INEXACT=0).
;
; Important notes on the macros
;    - the result parameter can also be an input parameter
;    - IDs/names of MREAL values must not have leading or trailing white spaces.
;    - MREAL values are implicit created for result parameters!
;    - generally, do not pass unprocessed/unevaluated expression to the macros, 
;      especially for numeric parameters -> use MASM's expansion operator % if needed.
;    - remarks that MREAL IDs/names reside in their own name space due to the internal representation of MREAL values.
;      This means they can have (for example) the same name as local or global variables.
;    - Names beginning with a question mark followed by one lower-case character (a-z, e.g. "?q") might be internally 
;      used by the MREAL macros. Furthermore some macros use names of the form "xTmp", whereas x is a shortcut
;      of the macro name in lower case.
;
; End user macros
;   [r, x, y, a, b, c denotes MREAL values. The value for TRUE is -1, FALSE is 0. |x| is the  
;   absolute value of x. round(x) rounds x to an integer in current rounding mode. pwr2, N and "value" are
;   MASM integer expression. "^" means exponentiation]
;
;   Procedures:
;     MR_ADD r,x,y              -> r = x+y
;     MR_SUB r,x,y              -> r = x-y
;     MR_MUL r,x,y              -> r = x*y
;     MR_DIV r,x,y              -> r = x/y
;     MR_SQRT r,x               -> r = x^(1/2)
;     MR_FMADD r,a,b,c          -> r = a*b + c
;     MR_FMSUB r,a,b,c          -> r = a*b - c
;     MR_FNMADD r,a,b,c         -> r = -a*b + c
;     MR_FNMSUB r,a,b,c         -> r = -a*b - c
;     MR_MOV r,x                -> r = x
;     MR_SET_ZERO r             -> r = 0
;     MR_CREATE r               -> r = 0
;     MR_ROUND r,x,pwr2         -> r = round(x*2^(-pwr2))*2^pwr2
;     MR_DEF_REAL10 lbl,x       -> define REAL10 variable/constant in current segment, initialized with value x.
;                                  This macro is a bug fix for MASM v6-7.
;     MR_CONVERT r,x,nx,nr      -> convert x to r. nx and nr specifies the number of precision WORDs.
;     MR_ABS r,x                -> r = |x|
;     MR_NEG r,x                -> r = -x
;     MR_COPY_SIGN r,x,y        -> r = sgn(y)*|x|
;     MR_CMP x,y                -> compare x with y and store the result in the equate mr_cmp.
;                                  mr_cmp =  -2  ->  unordered (x or/and y are NaN)
;                                            -1  ->  x < y
;                                             0  ->  x == y
;                                             1  ->  x > y
;                                  This macro allows to compare infinite values.
;     MR_FROM_EXPR32 r,value    -> convert the numeric expression "value" (MASM expression, 32 bit) to MREAL r.
;     MR_XMUL r,x,y,nr,nx,ny    -> r=x*y, multiplication with operands of different precision. Remarks that 1 <= nr <= nx+ny.
;     MR_SCALE r,x,y            -> r = x * 2^round(y)
;     MR_CSCALE r,x,pwr2        -> r = x * 2^pwr2
;     MR_FROM_STR r,literal     -> Convert numeric literal to MREAL value. The literal could be of the format:
;
;                                         Description           |   Example   |   Notes                   |           regex (PCRE)                                        
;                                  -----------------------------+-------------+---------------------------+---------------------------------------------------------------
;                                   hexadecimal integer literal | 0ffh        |                           | ^[+-]?[0-9][0-9a-fA-F]*[Hh]$                                  
;                                  -----------------------------+-------------+---------------------------+---------------------------------------------------------------
;                                   MASM hexadecimal floating   | 07f800000r  | Remarks the type specific | ^[+-]?[0-9][0-9a-fA-F]*[Rr]$                                  
;                                   point initializer           |             | size constraints          |                                                               
;                                  -----------------------------+-------------+---------------------------+---------------------------------------------------------------
;                                   decimal integer literal     | 123         |                           | ^[+-]?[0-9]+[Tt]?$                                            
;                                  -----------------------------+-------------+---------------------------+---------------------------------------------------------------
;                                   decimal floating point      | -1.0E-3     | The exponent should be in | ^[+-]?[0-9]+\.[0-9]*([Ee][+-]?[0-9]+)?$                       
;                                   literal                     | 123.4       | the range -4800 to 4800   |                                                               
;                                  -----------------------------+-------------+---------------------------+---------------------------------------------------------------
;                                   IEEE754-2008 hexadecimal-   | 0x123       |                           | ^[+-]*0[Xx][0-9a-fA-F]+\.?([0-9a-fA-F]+)?([Pp][+-]?[0-9]+)?$  
;                                   significant character       | 0x123.FFF   |                           | or                                                            
;                                   sequence                    | 0xF.1p-123  |                           | ^[+-]*0[Xx]\.?[0-9a-fA-F]+([Pp][+-]?[0-9]+)?$                 
;                                  -----------------------------+-------------+---------------------------+---------------------------------------------------------------
;
;                                  Leading and trailing blanks are ignored. Hexadecimal literals always produce correctly rounded MREAL values.
;                                  For decimal values the result is only correctly rounded, if the value is representable as quotient or product
;                                  of two integers, whereby the decimal exponent of these integers is below or equal to 105.
;                                  e.g. for values with 30 significant digits the decimal exponent range is at least -75 to 75. For 20 digits the range is extended to -85 to 85.
;                                  Decimal values with larger exponents are approximated - in such cases (and only in this cases) the flag MREAL_INEXACT is set to -2.
;
;     MR_LOAD_CONST r,name,pwr2 -> Load specified constant.
;                                  The name is not case-sensitive and could be: pi, rpi, e, one, zero, deg, rad, Infinity, NaN , max, min.
;                                  Except for NaN, the names can be prefixed with a sign.
;                                  The parameter pwr2 is added to the binary exponent of finite values.
;                                  For more details see the macro declaration.
;     MR_SET_CONST name,flg,
;                  exp,n,
;                  mantissa     -> Store MREAL constant. Parameters:
;                                    flg      : Could be <+>,<->,<+Infinity>,<-Infinity>,<NaN> or <zero>.
;                                    exp      : The exponent for finite values.
;                                    n        : Number of mantissa WORDs.
;                                    mantissa : [VARARG] Mantissa WORDs. The values will be masked with 0ffffh, missing values are set to zero.
;                                  This macro does fill the equates MREAL_&name&_n and MREAL_&name&_nSig.
;                                  Remarks that the macro assumes the values to be normalized to 2^1 = 1 (as for IEEE binary interchange formats).
;
;     MREAL x = literal1,
;           y = literal2, ...   -> Initialize one or more MREAL values from numeric literals. To override the default precision, each assignment can contain
;                                  a brace-expression that specifies the precision to use. For example, "MREAL x{8} = 0.123" initialize x with a precision of 8*16 bit.
;
;   Functions:
;     MR_TO_IEEE(<type>,x)    := Convert x to target precision and return a text macro that holds the corresponding hexadecimal floating point initializer.
;                                Type specifier can be: REAL4, REAL8, REAL10, single, double, double-extended,
;                                binary16, binary32, binary64.
;                                Due to a bug in MASM v6-7 this macro cannot directly used to initialize REAL10 values - use MR_DEF_REAL10 instead.
;                                For more details see the macro declaration.
;     MR_TO_INT32(x,errVal)   := returns x rounded to an integer. If the rounded value is not in the range -2^31 to 2^31-1, then errVal is returned.
;                                If errVal is non-numeric, an error is thrown instead.
;     MR_TO_UINT32(x,errVal)  := returns x rounded to an unsigned integer. If the rounded value is not in the range 0 to 2^32-1, then errVal is returned.
;                                If errVal is non-numeric, an error is thrown instead.
;     MR_TO_INT64(x,errVal)   := returns x rounded to an integer. If the rounded value is not in the range -2^63 to 2^63-1, then errVal is returned.
;                                If errVal is non-numeric, an error is thrown instead.
;     MR_TO_UINT64(x,errVal)  := returns x rounded to an unsigned integer. If the rounded value is not in the range 0 to 2^64-1, then errVal is returned.
;                                If errVal is non-numeric, an error is thrown instead.
;     MR_IS_ZERO(x)           := returns TRUE if x==0
;     MR_IS_SIGN_MINUS(x)     := returns TRUE if x<0 (also for -Infinity)
;     MR_IS_NORMAL(x)         := returns TRUE if x is not: zero, +-Infinity or NaN. (In other words: returns TRUE if the value requires a mantissa)
;     MR_IS_FINITE(x)         := returns TRUE if x is not: +-Infinity or NaN
;     MR_IS_INFINITE(x)       := returns TRUE if x is +-Infinity
;     MR_IS_NAN(x)            := returns TRUE if x is NaN
;     MR_EQ(x,y)              := returns TRUE if x == y
;     MR_NE(x,y)              := returns TRUE if x != y
;     MR_GT(x,y)              := returns TRUE if x >  y
;     MR_GE(x,y)              := returns TRUE if x >= y
;     MR_LT(x,y)              := returns TRUE if x <  y
;     MR_LE(x,y)              := returns TRUE if x <= y
;     MR_UN(x,y)              := returns TRUE if unordered
;     MR_NOT_UN(x,y)          := returns TRUE if not unordered
;     MR_NOT_GT(x,y)          := returns TRUE if x <= y or unordered
;     MR_GT_UN(x,y)           := returns TRUE if x >  y or unordered
;     MR_LT_UN(x,y)           := returns TRUE if x <  y or unordered
;     MR_NOT_LT(x,y)          := returns TRUE if x >= y or unordered
;     MR_TO_DECIMAL(x,N)      := returns a decimal literal that approximates the MREAL value x. This macro is mainly intended
;                                for debugging purpose -> Do not use this macro to initialize REAL4/8/10 values!
;                                The parameter N specifies the number of significant decimal digits (default=8).
;     MR_TO_IEEE_HEX_SEQ(x,N) := returns IEEE754-2008 hexadecimal-significant character sequence for x using N hexadecimal mantissa digits.
;                                If N is zero, (=default value) all mantissa digits are used.
;     MR_EXPONENT(x)          := returns the equate that hold the binary exponent of MREAL value x.
;     MR_ID_IS_MREAL(ID)      := returns TRUE if ID is an MREAL value
;
;     MR_GET_N_SIGNIFICANT_WORDS(x,n) := returns the number of significant mantissa WORDs. n is the number of mantissa WORDs.
;     MR_GET_N_SIGNIFICANT_BITS(x,n)  := returns the number of significant bits. n is the number of mantissa WORDs.
;
;
; Global states
;
;    The global precision setting, rounding mode and exponent limits are stored
;    in the equates:
;       MREAL_XDIM         := number of precision bits in multiples of 16.
;                             default value: 4 = 64 bit precision
;       MREAL_ROUND_MODE   := rounding mode -> see declaration of MRRM_* constants.
;                             default value: MRRM_ROUND_TO_NEAREST_TIES_TO_EVEN
;       MREAL_MAX_EXP      := maximal binary exponent.
;                             default value: 16382 -> correspond to double-extended precision values (REAL10)
;       MREAL_MIN_EXP      := minimal binary exponent.
;                             default value: -16381 -> correspond to double-extended precision values (REAL10)
; 
;    These equates can be dynamically changed, but MREAL values created with different
;    precision setting should not be mixed - instead the values should be converted using the MR_CONVERT macro.
;    All arithmetic macros have additional parameters that allows to locally overwrite the global settings
;    (commonly named: "n", "nx", "ny", "nr" or "p" for the precision and "rm" for the rounding mode).
;    
; MASM environment
;    - The macros are case-sensitive thus OPTION CASEMAP:NONE is needed.
;    - The expression word size must be at least 32 bit (OPTION EXPR32, default for MASM v6+).
;    - The macros assumes radix 10 (MASM default radix).
;
; MASM limits
;    The memory usage is the most important limiting factor of the MREAL macros. Each macro line and macro loop iteration
;    enlarges the "virtual" source file while assembling and thus MASM's memory usage. 
;    Remarks that the memory usage will dramatically increase if a listing is created (command line option "/Fl").
;    
; Simulating IEEE754 single and double precision arithmetic (24 and 53 bit precision)
;    This could be done by using an higher precision for the arithmetic (e.g. 32 bit for
;    single precision and 64 bit for double precision) and call MR_ROUND after
;    each operation as:
;           MR_ROUND x,x,24,<bits>   ; round x to single precision
;           MR_ROUND x,x,53,<bits>   ; round x to double precision
;
; Creating MREAL constants in computer algebra systems:
;    The following pseudo code shows how a conversion from any finite
;    nonzero value to MREAL could be done:
;
;        // Some definitions:
;        // sgn(x)    -> returns a boolean value: true => x is negative, false => x is positive.
;        // abs(x)    -> gives the absolute value of x.
;        // log2(x)   -> returns the logarithm of x to base 2.
;        // floor(x)  -> returns the largest integer not greater than x.
;        // round(x)  -> round x to an integer in wished rounding mode.
;        // "^"       -> means exponentiation.
;        // assert: c -> test condition c and throws an error if not true.
;        // w[]       -> is array 0 to nw-1 of unsigned integer (at least 16 bit). w[0] holds the most significant bits.
;     
;        toMREAL(x,nw) {    // x = value to convert, nw = number of mantissa words (word = unsigned 16 bit)
;            sign = sgn(x);
;            a = abs(x);
;            e = floor(log2(a));
;            mx = round(a*2^(-e-1+nw*16))*2^(-nw*16);
;            for(i=0; i<nw; i++) {
;                v = mx * 2^16;
;                w[i] = floor(v);
;                mx = v - w[i];
;            }
;            assert: mx == 0;
;            return {sign,e,nw,w};
;        }
;        
;        The return vector {sign,e,nw,w} could be used to setup a call to MR_SET_CONST.
;
; Changelog
;  27.05.2014  Version 1.0.1
;              bugfix:       - MR_TO_DECIMAL(): mrtiTmp was used, even if it was invalid.
;  26.06.2014  Version 1.0.2
;              added:        - MREAL macro.
;  26.06.2014  Version 1.0.3
;              improvement:  - test for case-sensitive symbol recognition added (option casemap:none)
;              bugfix:       - MREAL-macro: did not work correct for integer literals greater than 32 bit (affects only ml64.exe and jWasm).
;  25.09.2015  Version 1.0.4
;              added:        - MR_ID_IS_MREAL macro
;              improvement:  - include guard added
;              bugfix:       - @ScanForFlt: wrong position were returned for integers. Also partial correct literals were discarded if parameter chr was blank.
;                            - MR_SCALE: wrong input operand was used as exponent.
;              change:       - MR_DECL_REAL10 macro has been renamed to MR_DEF_REAL10. To keep backward compatibility MR_DECL_REAL10 is an alias for MR_DEF_REAL10.
;
; Literature
;  [1]  J.-M. Muller, N. Brisebarre, F. de Dinechin, C.-P. Jeannerod, V. Lefevre, G. Melquiond, N. Revol, D. Stehle, S. Torres.
;       Handbook of Floating-Point Arithmetic. Birkhäuser Boston, 2009.
;  [2]  U. Kulisch. Computer Arithmetic and Validity; Theory, Implementation, and Applications.
;       de Gruyter Berlin/Boston, 2nd edition, 2013.
;  [3]  J.-M. Muller. Elementary Functions, Algorithms and Implementation.
;       Birkhäuser Boston, 2nd edition, 2006.
;  [4]  I. Koren. Computer Arithmetic Algorithms.
;       A K Peters, Natick Massachusetts, 2nd edition, 2002.
;  [5]  IEEE Computer Society. IEEE Standard for Floating-Point Arithmetic; IEEE Std 754-2008.
;       The Institute of Electrical and Electronics Engineers, New York. 2008.
;


IFNDEF MR_VERSION

MR_VERSION EQU 104 ; 1.0.4

MREAL_XDIM 		= 4
MREAL_WMSK 		EQU 0ffffh
MREAL_MAX_EXP	EQU (16383+1)	; default values are compatible with REAL10
MREAL_MIN_EXP	EQU (2-16383)	;

;/* symbol recognition must be case-sensitive */
IFDEF MrEaL_XdIm
	.err <option casemap:none is needed>
ENDIF

;/* rounding modes */
MRRM_ROUND_TO_NEAREST_TIES_TO_EVEN			EQU 0	;; IEEE 754 default mode; tie-breaking rule: round half to even; also called "round to even" or "banker’s rounding"
MRRM_ROUND_TOWARD_NEGATIVE					EQU 1
MRRM_ROUND_TOWARD_POSITIVE					EQU 2
MRRM_ROUND_TOWARD_ZERO						EQU 3
MRRM_ROUND_TO_NEAREST_TIES_AWAY_FROM_ZERO	EQU 4	;; tie-breaking rule: round half away from zero
MRRM__MINVALUE								EQU 0
MRRM__MAXVALUE								EQU 4
;/* alias */
MRRM_TRUNCATE		EQU MRRM_ROUND_TOWARD_ZERO
MRRM_ROUND_TO_EVEN	EQU MRRM_ROUND_TO_NEAREST_TIES_TO_EVEN
MRRM_ROUND_DOWN		EQU MRRM_ROUND_TOWARD_NEGATIVE
MRRM_ROUND_UP		EQU MRRM_ROUND_TOWARD_POSITIVE
;/* short names */
MRRM_NEAR_EVEN  = MRRM_ROUND_TO_NEAREST_TIES_TO_EVEN
MRRM_NEAR_AWAY  = MRRM_ROUND_TO_NEAREST_TIES_AWAY_FROM_ZERO

;/* set default rounding mode */
MREAL_ROUND_MODE = MRRM_ROUND_TO_NEAREST_TIES_TO_EVEN

;/* error control values (boolean values: 0 == FALSE, -1 == TRUE) */
MREAL_ERROR_FOR_NAN_INPUT	=  0	; throw error for NaN and +-Infinity as macro input
MREAL_ERROR_FOR_NAN_OUTPUT	=  0	; throw error for NaN and +-Infinity as macro result
MREAL_ERROR_FOR_DIV_ZERO	= -1
MREAL_UNDERFLOW_IS_ERROR	=  0	; throw error if the exponent of the result underflows (exponent < MREAL_MIN_EXP)
MREAL_OVERFLOW_IS_ERROR		=  0	; throw error if the exponent of the result overflows (exponent > MREAL_MAX_EXP)

;/* inexact handling */
MREAL_TEST_INEXACT = 0
MREAL_INEXACT = 0

;/* MREAL-flags (do not change!) */
MREAL_FLG_VALID				EQU 0
MREAL_FLG_ZERO				EQU 1
MREAL_FLG_INF				EQU 2
MREAL_FLG_NAN				EQU 4
MREAL_FLG_SIGN				EQU 080000000h
;/* masks */
MREAL_FLG_NON_NUMERIC_TEST	EQU 07ffffffeh
MREAL_FLG_NO_MANTISSA_TEST	EQU 07fffffffh
MREAL_ALL_FLGS = MREAL_FLG_ZERO OR MREAL_FLG_INF OR MREAL_FLG_NAN OR MREAL_FLG_SIGN
MREAL_SINGLE_FLGS TEXTEQU <MREAL_FLG_ZERO,MREAL_FLG_NAN>

;/* MR_GLB_STATE_STACK is used by MR_PUSH/POP_STATE */
MR_GLB_STATE_STACK = 0

;;/**
;; * Push one or more equates on a virtual stack.
;; */
MR_PUSH_STATE macro states:VARARG
	MR_GLB_STATE_STACK = MR_GLB_STATE_STACK + 1
	@CatStr(<MRGSS_STATES>,%MR_GLB_STATE_STACK) TEXTEQU <&states>
	FOR state,<&states>
		@CatStr(<MRGSS_&state&>,%MR_GLB_STATE_STACK) = state
	ENDM
endm

;;/* Pop previously saved equates from virtual stack */
MR_POP_STATE macro
	IFE MR_GLB_STATE_STACK
		.err <stack underrun>
		EXITM
	ENDIF
%	FOR state,<@CatStr(<MRGSS_STATES>,%MR_GLB_STATE_STACK)>
		state = @CatStr(<MRGSS_&state&>,%MR_GLB_STATE_STACK)
	ENDM
	MR_GLB_STATE_STACK = MR_GLB_STATE_STACK - 1
endm

;;/* returns TRUE, if ID is a MREAL value */
MR_ID_IS_MREAL macro ID:req
	IFNDEF MREAL_&ID&_flg
		EXITM <0>
	ENDIF
	EXITM <-1>
endm

;;/* create MREAL value and set it to zero (also all mantissa WORDs) */
MR_CREATE macro name:req,n:=<MREAL_XDIM>
	MREAL_&name&_flg = MREAL_FLG_ZERO
	MREAL_&name&_exp = 0
	mrc_cntr = 0
	REPEAT n
	%	@CatStr(<MREAL_&name&_w>,%mrc_cntr) = 0
		mrc_cntr = mrc_cntr + 1
	ENDM
endm
MR_SET_ZERO EQU MR_CREATE

;;/* Copy src to dest. */
MR_MOV macro dest:req,src:req,n:=<MREAL_XDIM>
	IFIDN <&dest>,<&src>
		EXITM
	ENDIF
	MREAL_&dest&_exp = MREAL_&src&_exp
	MREAL_&dest&_flg = MREAL_&src&_flg
	mrc_cntr = 0
	REPEAT n
		mrc_tcntr TEXTEQU %mrc_cntr
	%	MREAL_&dest&_w&mrc_tcntr& = MREAL_&src&_w&mrc_tcntr&
		mrc_cntr = mrc_cntr + 1
	ENDM
endm

; This macro assumes input values normalized to 2^0 = 1 (as for IEEE754 binary interchange formats).
; flg 	   = <+> or blank : positive number
;            <->          : negative number
;            <zero>       :
;            <+Infinity>  :
;            <-Infinity>  : 
;            <NaN>        : not a number 
; exp 	   = binary exponent (2^exp) in the range MREAL_MIN_EXP to MREAL_MAX_EXP (default: -16382 to 16383)
; mantissa = mantissa WORDs starting with the most significant WORD (holding the leading 1).
;            The values are masked with 0FFFFh. Unspecified WORDs are set to zero.
; example: 
;           +1.0:      MR_RAW_SET cOne,+,0,8000h
;           -0.5:      MR_RAW_SET cMinusHalf,-,-1,8000h
;          +INFINITY:  MR_RAW_SET cInf,+Infinity
;            0.0:      MR_RAW_SET cZero,zero
MR_RAW_SET macro name,flg:=<>,exp:=<0>,mantissa:VARARG
	MR_RAW_SET_N name,flg,exp,,mantissa
endm

MR_RAW_SET_N macro name,flg:=<>,exp:=<0>,n:=<MREAL_XDIM>,mantissa:VARARG
	
	IFB <&flg>
		MREAL_&name&_flg = MREAL_FLG_VALID
	ELSEIFIDNI <&flg>,<zero>
		MREAL_&name&_flg = MREAL_FLG_ZERO
	ELSEIFIDNI <&flg>,<+>
		MREAL_&name&_flg = MREAL_FLG_VALID
	ELSEIFIDNI <&flg>,<->
		MREAL_&name&_flg = MREAL_FLG_SIGN
	ELSEIFIDNI <&flg>,<+Infinity>
		MREAL_&name&_flg = MREAL_FLG_INF
	ELSEIFIDNI <&flg>,<-Infinity>
		MREAL_&name&_flg = MREAL_FLG_INF OR MREAL_FLG_SIGN
	ELSEIFIDNI <&flg>,<NaN>
		MREAL_&name&_flg = MREAL_FLG_NAN
	ELSE
		.err <invalid flag-specifier for &name: flg>
		EXITM
	ENDIF

	IF (exp LT MREAL_MIN_EXP) OR (exp GT MREAL_MAX_EXP)
		.err <exponent value of &name is out of range>
		EXITM
	ENDIF
	
	MREAL_&name&_exp = exp + 1
	mrc_cntr = 0
	mrc_nzero = 0
	mrc_tcntr TEXTEQU %mrc_cntr
	FOR arg,<&mantissa>
		IFNB <&arg>
			IF mrc_cntr GE n
				.err @CatStr(<to many arguments for mant>,<issa of &name>)
				EXITM
			ENDIF
			IF (mrc_cntr EQ 0) AND ((MREAL_&name&_flg AND MREAL_FLG_NO_MANTISSA_TEST) EQ 0) AND ((arg AND 8000h) EQ 0)
				.err @CatStr(<man>,<tissa of &name is denormalized>)
				EXITM
			ENDIF
		%	MREAL_&name&_w&mrc_tcntr& = (arg) AND MREAL_WMSK
			mrc_nzero = mrc_nzero+1 AND ((arg) AND MREAL_WMSK) EQ 0
		ELSE
		%	MREAL_&name&_w&mrc_tcntr& = 0
			mrc_nzero = mrc_nzero + 1
		ENDIF
		mrc_cntr = mrc_cntr + 1
		mrc_tcntr TEXTEQU %mrc_cntr
	ENDM
	WHILE mrc_cntr LT n
	%	MREAL_&name&_w&mrc_tcntr& = 0
		mrc_nzero = mrc_nzero + 1
		mrc_cntr = mrc_cntr + 1
		mrc_tcntr TEXTEQU %mrc_cntr
	ENDM
	MREAL_&name&_n = n
	MREAL_&name&_nSig = n-mrc_nzero
endm

MR_SET_CONST EQU MR_RAW_SET_N


MR_RAW_COMPOSE macro name,flg,exp,mantissa_src,n:=<MREAL_XDIM>
	MREAL_&name&_exp = exp
	MREAL_&name&_flg = flg
	mrc_cntr = 0
	mrc_tcntr TEXTEQU %mrc_cntr
	WHILE mrc_cntr LT n
	%	MREAL_&name&_w&mrc_tcntr& = MREAL_&mantissa_src&_w&mrc_tcntr& AND MREAL_WMSK
		mrc_cntr = mrc_cntr + 1
		mrc_tcntr TEXTEQU %mrc_cntr
	ENDM
endm

;;/**
;; * Produce the largest postive finite value (according
;; * to the current precision and exponent settings) and negate it,
;; * if "sign" is not zero.
;; */
MR_RAW_MAXVALUE macro name:req,sign:=<0>,n:=<MREAL_XDIM>,emax:=<MREAL_MAX_EXP>
	MREAL_&name&_exp = emax
	MREAL_&name&_flg = (sign NE 0) AND MREAL_FLG_SIGN
	mrc_cntr = 0
	WHILE mrc_cntr LT n
		@CatStr(<MREAL_&name&_w>,%mrc_cntr) = 0ffffh
		mrc_cntr = mrc_cntr + 1
	ENDM
endm

;;/**
;; * Produce the smallest postive finite nonzero value (according
;; * to the current precision and exponent settings) and negate it,
;; * if "sign" is not zero.
;; */
MR_RAW_MINVALUE macro name:req,sign:=<0>,n:=<MREAL_XDIM>,emin:=<MREAL_MIN_EXP>
	MREAL_&name&_exp = emin
	MREAL_&name&_flg = (sign NE 0) AND MREAL_FLG_SIGN
	MREAL_&name&_w0 = 8000h
	mrc_cntr = 1
	WHILE mrc_cntr LT n
		@CatStr(<MREAL_&name&_w>,%mrc_cntr) = 0
		mrc_cntr = mrc_cntr + 1
	ENDM
endm

; return: 0/-1 => invalid/valid. Error description is emitted to the build console
MR_RAW_IS_VALID macro name,n:=<MREAL_XDIM>
	mrriv_exp? = -1
	mrriv_expinv? = 0
	mrriv_all_mantissa? = -1
	mrriv_flg? = -1
	mrriv_flginv? = 0
	mrriv_denorm? = 0
	mrriv_inv_mx? = 0
	IFNDEF MREAL_&name&_exp
		mrriv_exp? = 0
	ELSEIF (MREAL_&name&_exp LT MREAL_MIN_EXP) OR (MREAL_&name&_exp  GT MREAL_MAX_EXP)
		mrriv_expinv? = -1
	ENDIF
	IFNDEF MREAL_&name&_flg
		mrriv_flg? = 0
	ELSEIF (MREAL_&name&_flg AND (NOT MREAL_ALL_FLGS)) NE 0
		mrriv_flginv? = -1
	ELSEIF ((MREAL_&name&_flg AND MREAL_FLG_SIGN ) NE 0) AND ((MREAL_&name&_flg AND (NOT (MREAL_FLG_INF OR MREAL_FLG_SIGN))) NE 0)
		mrriv_flginv? = -1
	ELSE
	%	FOR msk,<&MREAL_SINGLE_FLGS>
			IF ((MREAL_&name&_flg AND msk) NE 0) AND ((MREAL_&name&_flg AND (NOT (msk))) NE 0)
				mrriv_flginv? = -1
				EXITM
			ENDIF
		ENDM
	ENDIF
	mrriv_missing TEXTEQU <>
	mrriv_invmx TEXTEQU <>
	mrriv_mc = 0
	mrriv_cntr = 0
	mrriv_tcntr TEXTEQU %mrriv_cntr
	WHILE mrriv_cntr LT n
	%	IFNDEF MREAL_&name&_w&mrriv_tcntr&
			IFB mrriv_missing
				mrriv_missing TEXTEQU mrriv_tcntr
			ELSE
				mrriv_missing TEXTEQU mrriv_missing,<,>,mrriv_tcntr
			ENDIF
			mrriv_mc = mrriv_mc + 1
		ELSE
			IF mrriv_cntr EQ 0
			%	IFE MREAL_&name&_w&mrriv_tcntr& AND 8000h
					mrriv_denorm? = -1
				ENDIF
			ENDIF
		%	IF (MREAL_&name&_w&mrriv_tcntr& AND (NOT MREAL_WMSK)) NE 0
				IFB mrriv_invmx
					mrriv_invmx TEXTEQU mrriv_tcntr
				ELSE
					mrriv_invmx TEXTEQU mrriv_invmx,<,>,mrriv_tcntr
				ENDIF
			ENDIF
		ENDIF
		mrriv_cntr = mrriv_cntr + 1
		mrriv_tcntr TEXTEQU %mrriv_cntr
	ENDM
	IFNB mrriv_missing
		mrriv_all_mantissa? = 0
	ENDIF
	IFNB mrriv_invmx
		mrriv_inv_mx? = -1
	ENDIF
	
	IF mrriv_flg? AND mrriv_exp? AND mrriv_all_mantissa? AND (NOT mrriv_flginv?)
		IF MREAL_&name&_flg AND (MREAL_FLG_NON_NUMERIC_TEST OR MREAL_FLG_ZERO)
			EXITM <-1>
		ENDIF
	ENDIF
	IF mrriv_exp? AND mrriv_all_mantissa? AND (NOT mrriv_expinv?) AND (NOT mrriv_inv_mx?) AND (NOT mrriv_denorm?) AND mrriv_flg? AND (NOT mrriv_flginv?)
		EXITM <-1>
	ENDIF
	IF (NOT mrriv_flg?) AND (NOT mrriv_exp?) AND (mrriv_mc EQ n)
		echo symbol <&name> is not a MREAL-value
		EXITM <0>
	ENDIF
	    echo MREAL <&name> is invalid because of:
	IFE mrriv_flg?
		echo .   - has no flags (missing EQU)
	ENDIF
	IF mrriv_flginv?
		echo .   - invalid flags
	ENDIF
	IFE mrriv_exp?
		echo .   - has no exponent (missing EQU)
	ENDIF
	IF mrriv_expinv?
		echo .   - exponent value is out of range (MREAL_MIN_EXP to MREAL_MAX_EXP)
	ENDIF
	IFE mrriv_all_mantissa?
	%	echo .   - one or more mantissa values are missing (EQU). Indexes: &mrriv_missing&
	ENDIF
	IF mrriv_inv_mx?
	%	echo .   - one or more mantissa values are out of range. Indexes: &mrriv_invmx&
	ENDIF
	IF mrriv_denorm?
		echo .   - the mantissa is denormalized
	ENDIF
	IF mrriv_all_mantissa? AND mrriv_flg? AND mrriv_exp?
		EXITM <-1>
	ELSE
		EXITM <0>
	ENDIF
endm

; print MREAL "name" to the build console: <+-><hexadecimal mantissa>*2^<decimal exponent>
MR_RAW_OUT macro name:req,n:=<MREAL_XDIM>,accum
	
	IFE MR_RAW_IS_VALID(name,n)
		EXITM
	ENDIF
	
	IF (MREAL_&name&_flg AND MREAL_FLG_ZERO) NE 0
		mrc_outtxt TEXTEQU <name is: zero (0)>
	ELSEIF ((MREAL_&name&_flg AND MREAL_FLG_INF) NE 0) AND ((MREAL_&name&_flg AND MREAL_FLG_SIGN) NE 0)
		mrc_outtxt TEXTEQU <name is: -Infinity>
	ELSEIF (MREAL_&name&_flg AND MREAL_FLG_INF) NE 0
		mrc_outtxt TEXTEQU <name is: +Infinity>
	ELSEIF (MREAL_&name&_flg AND MREAL_FLG_NAN) NE 0
		mrc_outtxt TEXTEQU <name is: not a number (NaN)>
	ELSE
		mrc_outtxt TEXTEQU <name is: >
		IF (MREAL_&name&_flg AND MREAL_FLG_SIGN) NE 0
			mrc_outtxt TEXTEQU mrc_outtxt,<->
		ELSE
			mrc_outtxt TEXTEQU mrc_outtxt,<+>
		ENDIF
		mrc_cntr = 0
		WHILE mrc_cntr LT n AND mrc_cntr LT 32
			mrc_val = @CatStr(<MREAL_&name&_w>,%mrc_cntr)
			.radix 16
				mrc_txt TEXTEQU %mrc_val
			.radix 10
			IF @SizeStr(%mrc_txt) EQ 1
				mrc_txt TEXTEQU <000>,mrc_txt
			ELSEIF @SizeStr(%mrc_txt) EQ 2
				mrc_txt TEXTEQU <00>,mrc_txt
			ELSEIF @SizeStr(%mrc_txt) EQ 3
				mrc_txt TEXTEQU <0>,mrc_txt
			ENDIF
			IF mrc_cntr NE 0
				mrc_txt TEXTEQU <_>,mrc_txt
			ENDIF
			mrc_outtxt TEXTEQU mrc_outtxt,mrc_txt
			mrc_cntr = mrc_cntr + 1
		ENDM
		mrc_accum TEXTEQU <>
		IFNB <&accum>
			WHILE mrc_cntr LT n*2+1
				mrc_tcntr TEXTEQU %mrc_cntr
			%	IFNDEF MREAL_&name&_w&mrc_tcntr&
					EXITM
				ENDIF
			%	mrc_val = MREAL_&name&_w&mrc_tcntr&
				.radix 16
					mrc_txt TEXTEQU %mrc_val
				.radix 10
				IF @SizeStr(%mrc_txt) EQ 1
					mrc_txt TEXTEQU <000>,mrc_txt
				ELSEIF @SizeStr(%mrc_txt) EQ 2
					mrc_txt TEXTEQU <00>,mrc_txt
				ELSEIF @SizeStr(%mrc_txt) EQ 3
					mrc_txt TEXTEQU <0>,mrc_txt
				ENDIF
				mrc_accum TEXTEQU mrc_accum,<_>,mrc_txt
				mrc_cntr = mrc_cntr + 1
			ENDM
		ENDIF
		IF n LT 32
			mrc_outtxt TEXTEQU mrc_outtxt,mrc_accum,<*2^>,@CatStr(%MREAL_&name&_exp-1)
		ENDIF
	ENDIF
	%echo mrc_outtxt
	IF n GT 32
		mrc_cntr = 32
		WHILE mrc_cntr LT n
			mrc_outtxt TEXTEQU <>
			REPEAT 32
				IF mrc_cntr GE n
					EXITM
				ENDIF
				mrc_val = @CatStr(<MREAL_&name&_w>,%mrc_cntr)
				.radix 16
					mrc_txt TEXTEQU %mrc_val
				.radix 10
				IF @SizeStr(%mrc_txt) EQ 1
					mrc_txt TEXTEQU <000>,mrc_txt
				ELSEIF @SizeStr(%mrc_txt) EQ 2
					mrc_txt TEXTEQU <00>,mrc_txt
				ELSEIF @SizeStr(%mrc_txt) EQ 3
					mrc_txt TEXTEQU <0>,mrc_txt
				ENDIF
				IF mrc_cntr NE 0
					mrc_txt TEXTEQU <_>,mrc_txt
				ENDIF
				mrc_outtxt TEXTEQU mrc_outtxt,mrc_txt
				mrc_cntr = mrc_cntr + 1
			ENDM
			IF mrc_cntr EQ n
				%echo @CatStr(%mrc_outtxt,<*2^>,%MREAL_&name&_exp-1)
			ELSE
				%echo mrc_outtxt
			ENDIF
		ENDM
	ENDIF
endm

;/* shift mantissa bits of r s-times left (mantissa=mantissa*2^s) */
MR_LSHIFT macro r,s,n:=<MREAL_XDIM>
	IFE s
		EXITM
	ENDIF
	mrls_iHigh = 0
	mrls_tiHigh TEXTEQU %mrls_iHigh
	IF s LT 16*(n)
		mrls_iLow = s/16
		mrls_tiLow TEXTEQU %mrls_iLow
		mrls_lshift = s mod 16
		mrls_rshift = 16 - mrls_lshift
		mrls_limit = n - 1
		WHILE mrls_iLow LT mrls_limit
			mrls_tiLowP1 TEXTEQU %mrls_iLow+1
		%	MREAL_&r&_w&mrls_tiHigh& = LOWWORD (MREAL_&r&_w&mrls_tiLow& SHL mrls_lshift OR MREAL_&r&_w&mrls_tiLowP1& SHR mrls_rshift)
			mrls_iHigh = mrls_iHigh + 1
			mrls_tiHigh TEXTEQU %mrls_iHigh
			mrls_iLow = mrls_tiLowP1
			mrls_tiLow TEXTEQU mrls_tiLowP1
		ENDM
	%	MREAL_&r&_w&mrls_tiHigh& = LOWWORD (MREAL_&r&_w&mrls_tiLow& SHL mrls_lshift)
		mrls_iHigh = mrls_iHigh + 1
		mrls_tiHigh TEXTEQU %mrls_iHigh
	ENDIF
	WHILE mrls_iHigh LE (n - 1)
	%	MREAL_&r&_w&mrls_tiHigh& = 0
		mrls_iHigh = mrls_iHigh + 1
		mrls_tiHigh TEXTEQU %mrls_iHigh
	ENDM
endm

;/* shift mantissa bits of r s-times right (mantissa=mantissa*2^(-s)) */
MR_RSHIFT macro r,s,n:=<MREAL_XDIM>
	IFE s
		EXITM
	ENDIF
	mrrs_iLow = n - 1
	mrrs_tiLow TEXTEQU %mrrs_iLow
	IF s LT 16*(n)
		mrrs_iHigh = mrrs_iLow - s/16
		mrrs_tiHigh TEXTEQU %mrrs_iHigh
		mrrs_rshift = s mod 16
		mrrs_lshift = 16 - mrrs_rshift
		WHILE mrrs_iHigh GT 0
			mrrs_tiHighM1 TEXTEQU %mrrs_iHigh-1
		%	MREAL_&r&_w&mrrs_tiLow& = LOWWORD (MREAL_&r&_w&mrrs_tiHigh& SHR mrrs_rshift OR MREAL_&r&_w&mrrs_tiHighM1& SHL mrrs_lshift)
			mrrs_iHigh = mrrs_tiHighM1
			mrrs_tiHigh TEXTEQU mrrs_tiHighM1
			mrrs_iLow = mrrs_iLow - 1
			mrrs_tiLow TEXTEQU %mrrs_iLow
		ENDM
	%	MREAL_&r&_w&mrrs_tiLow& = LOWWORD (MREAL_&r&_w&mrrs_tiHigh& SHR mrrs_rshift)
		mrrs_iLow = mrrs_iLow - 1
		mrrs_tiLow TEXTEQU %mrrs_iLow
	ENDIF
	WHILE mrrs_iLow GE 0
	%	MREAL_&r&_w&mrrs_tiLow& = 0
		mrrs_iLow = mrrs_iLow - 1
		mrrs_tiLow TEXTEQU %mrrs_iLow
	ENDM
endm

MR_RSHIFT_1 macro r,n:=<MREAL_XDIM>
	mrrs_cntr = 0
	mrrs_tmp = 0
	REPEAT n
		mrrs_tcntr TEXTEQU %mrrs_cntr
	%	mrrs_tmp = MREAL_&r&_w&mrrs_tcntr& OR LOWWORD mrrs_tmp SHL 16
	%	MREAL_&r&_w&mrrs_tcntr& = LOWWORD (mrrs_tmp SHR 1)
		mrrs_cntr = mrrs_cntr + 1
	ENDM
endm

MR_LSHIFT_1 macro r,n:=<MREAL_XDIM>
	mrrs_cntr = (n)-1
	mrrs_tmp = 0
	REPEAT n
		mrrs_tcntr TEXTEQU %mrrs_cntr
	%	mrrs_tmp = MREAL_&r&_w&mrrs_tcntr& SHL 16 OR HIGHWORD mrrs_tmp
	%	MREAL_&r&_w&mrrs_tcntr& = HIGHWORD (mrrs_tmp SHL 1)
		mrrs_cntr = mrrs_cntr - 1
	ENDM
endm


MR_PREPARE_ACCUMULATOR macro name,s:=<MREAL_XDIM>,n:=<MREAL_XDIM*2+1>
	mrpa_cntr = s
	WHILE mrpa_cntr LT n
		@CatStr(<MREAL_&name&_w>,%mrpa_cntr) = 0
		mrpa_cntr = mrpa_cntr + 1
	ENDM
endm

;;/* returns the number of significant bits in r */
MR_GET_N_SIGNIFICANT_BITS macro r:req,n:=<MREAL_XDIM>
	IF MREAL_&r&_flg AND MREAL_FLG_ZERO
		EXITM <0>
	ELSEIF MREAL_&r&_flg AND MREAL_FLG_NO_MANTISSA_TEST
		.err <invalid input value: r>
		EXITM <0>
	ENDIF
	mrgnsb_cntr = n-1
	REPEAT n
		IF @CatStr(<MREAL_&r&_w>,%mrgnsb_cntr)
			EXITM
		ENDIF
		mrgnsb_cntr = mrgnsb_cntr - 1
	ENDM
	IF mrgnsb_cntr LT 0
		.err <denormal mantissa: r>
		EXITM <0>
	ENDIF
	mrgnsb_val = @CatStr(<MREAL_&r&_w>,%mrgnsb_cntr)
	.radix 16
		mrgnsb_txt TEXTEQU %mrgnsb_val
	.radix 10
	mrgnsb_size SIZESTR mrgnsb_txt
	IF @CatStr(<0>,@SubStr(%mrgnsb_txt,%mrgnsb_size,1),<h>)
		mrgnsb_pos = mrgnsb_size
	ELSEIF @CatStr(<0>,@SubStr(%mrgnsb_txt,%mrgnsb_size-1,1),<h>)
		mrgnsb_pos = mrgnsb_size-1
	ELSEIF @CatStr(<0>,@SubStr(%mrgnsb_txt,%mrgnsb_size-2,1),<h>)
		mrgnsb_pos = mrgnsb_size-2
	ELSEIF @CatStr(<0>,@SubStr(%mrgnsb_txt,%mrgnsb_size-3,1),<h>)
		mrgnsb_pos = mrgnsb_size-3
	ELSE
		.err <invalid matnissa WORD in r>
		EXITM <0>
	ENDIF
	mrgnsb_txt SUBSTR <434243414342434>,@CatStr(<0>,@SubStr(%mrgnsb_txt,%mrgnsb_pos,1),<h>),1
	EXITM %mrgnsb_cntr*16+(mrgnsb_pos+(4-mrgnsb_size)-1)*4+mrgnsb_txt
endm

;;/* returns the number of significant WORDs in r */
MR_GET_N_SIGNIFICANT_WORDS macro r:req,n:=<MREAL_XDIM>
	IF MREAL_&r&_flg AND MREAL_FLG_ZERO
		EXITM <0>
	ELSEIF MREAL_&r&_flg AND MREAL_FLG_NO_MANTISSA_TEST
		.err <invalid input value: r>
		EXITM <0>
	ENDIF
	mrgnsb_cntr = n-1
	REPEAT n
		IF @CatStr(<MREAL_&r&_w>,%mrgnsb_cntr)
			EXITM
		ENDIF
		mrgnsb_cntr = mrgnsb_cntr - 1
	ENDM
	IF mrgnsb_cntr LT 0
		.err <denormal mantissa: r>
		EXITM <0>
	ENDIF
	EXITM %mrgnsb_cntr+1
endm

;;/* get the absolute value of x */
MR_ABS macro r:req,x:req,n:=<MREAL_XDIM>
	IF MREAL_&x&_flg AND MREAL_FLG_NAN
		IF MREAL_ERROR_FOR_NAN_INPUT
			.err <x is not a numeric value>
		ENDIF
		MR_RAW_SET_N r,NaN,,n
		EXITM
	ELSEIF MREAL_&x&_flg AND MREAL_FLG_ZERO
		MR_SET_ZERO r,n
		EXITM
	ENDIF
	MR_MOV r,x,n
	MREAL_&r&_flg = MREAL_&r&_flg AND (NOT MREAL_FLG_SIGN)
endm

;;/* r = -x */
MR_NEG macro r:req,x:req,n:=<MREAL_XDIM>
	IF MREAL_&x&_flg AND MREAL_FLG_NAN
		IF MREAL_ERROR_FOR_NAN_INPUT
			.err <x is not a numeric value>
		ENDIF
		MR_RAW_SET_N r,NaN,,n
		EXITM
	ELSEIF MREAL_&x&_flg AND MREAL_FLG_ZERO
		MR_SET_ZERO r,n
		EXITM
	ENDIF
	MR_MOV r,x,n
	MREAL_&r&_flg = MREAL_&r&_flg XOR MREAL_FLG_SIGN
endm

;;/* r = sgn(y)*|x| */
MR_COPY_SIGN macro r:req,x:req,y:req,n:=<MREAL_XDIM>
	IF MREAL_&x&_flg AND MREAL_FLG_NAN
		IF MREAL_ERROR_FOR_NAN_INPUT
			.err <x is not a numeric value>
		ENDIF
		MR_RAW_SET_N r,NaN,,n
		EXITM
	ELSEIF MREAL_&y&_flg AND MREAL_FLG_NAN
		IF MREAL_ERROR_FOR_NAN_INPUT
			.err <y is not a numeric value>
		ENDIF
		MR_RAW_SET_N r,NaN,,n
		EXITM
	ELSEIF MREAL_&x&_flg AND MREAL_FLG_ZERO
		MR_SET_ZERO r,n
		EXITM
	ENDIF
	MR_MOV r,x,n
	MREAL_&r&_flg = (MREAL_&r&_flg AND (NOT MREAL_FLG_SIGN)) OR MREAL_&y&_flg AND MREAL_FLG_SIGN
endm


;;/* cosmetic: @CatStr() is used to get <-1> as result and not <4294967295> */
MR_IS_ZERO macro x:req
	EXITM @CatStr(%(MREAL_&x&_flg AND MREAL_FLG_ZERO) NE 0)
endm

MR_IS_SIGN_MINUS macro x:req
	EXITM @CatStr(%(MREAL_&x&_flg AND MREAL_FLG_SIGN) NE 0)
endm

MR_IS_NORMAL macro x:req
	EXITM @CatStr(%(MREAL_&x&_flg AND MREAL_FLG_NO_MANTISSA_TEST) EQ 0)
endm

MR_IS_FINITE macro x:req
	EXITM @CatStr(%(MREAL_&x&_flg AND MREAL_FLG_NON_NUMERIC_TEST) EQ 0)
endm

MR_IS_INFINITE macro x:req
	EXITM @CatStr(%(MREAL_&x&_flg AND MREAL_FLG_INF) NE 0)
endm

MR_IS_NAN macro x:req
	EXITM @CatStr(%(MREAL_&x&_flg AND MREAL_FLG_NAN) NE 0)
endm

;;/* returns equate holding the binary exponent of x */
MR_EXPONENT macro x
	EXITM <MREAL_&x&_exp>
endm

;;/* convert signed or unsigned integer expression "value" (32 bit) to MREAL r */
MR_FROM_EXPR32 macro r:req,value:=<0>,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>
	MREAL_INEXACT = 0
	IFE value
		MR_SET_ZERO r,n
		EXITM
	ENDIF
	IF value LT 0
		mrfv_val = -(value)
		mrfv_sign = -1
	ELSE
		mrfv_val = value
		mrfv_sign = 0
	ENDIF
	;/* make sure that mrfv_val is unsigned */
	mrfv_val = mrfv_val AND 0ffffffffh
	.radix 2
		mrfv_txt TEXTEQU %mrfv_val
	.radix 10
	mrfv_log2p1 = @SizeStr(%mrfv_txt)
	mrfv_val = mrfv_val SHL (32-mrfv_log2p1)
	MREAL_&r&_flg = mrfv_sign AND MREAL_FLG_SIGN
	MREAL_&r&_w0 = HIGHWORD mrfv_val
	MREAL_&r&_w1 = LOWWORD mrfv_val
	MREAL_&r&_exp = mrfv_log2p1
	;;/* round if needed */
	MR_ROUND r,r,%(n)*16,<bits>,rm,2
	;;/* zero extend mantissa if needed */
	mrfv_cntr = 2
	WHILE mrfv_cntr LT n
		@CatStr(<MREAL_&r&_w>,%mrfv_cntr) = 0
		mrfv_cntr = mrfv_cntr + 1
	ENDM
endm

;;/* convert "value" to MREAL r without rounding and exponent check */
MR_RAW_FROM_VALUE macro r:req,value:=<0>,n:=<MREAL_XDIM>
	MREAL_INEXACT = 0
	IF value LT 0
		mrfv_val = -(value)
		mrfv_sign = -1
	ELSE
		mrfv_val = value
		mrfv_sign = 0
	ENDIF
	mrfv_val = mrfv_val AND 0ffffffffh
	.radix 2
		mrfv_txt TEXTEQU %mrfv_val
	.radix 10
	mrfv_log2p1 = @SizeStr(%mrfv_txt)
	mrfv_val = mrfv_val SHL (32-mrfv_log2p1)
	MREAL_&r&_flg = mrfv_sign AND MREAL_FLG_SIGN
	MREAL_&r&_w0 = HIGHWORD mrfv_val
	MREAL_&r&_w1 = LOWWORD mrfv_val
	MREAL_&r&_exp = mrfv_log2p1
	mrfv_cntr = 2
	WHILE mrfv_cntr LT n
		@CatStr(<MREAL_&r&_w>,%mrfv_cntr) = 0
		mrfv_cntr = mrfv_cntr + 1
	ENDM
endm


;;/**
;; * Round x to an integer and return the corresponding numeric literal.
;; * If the rounded value is out of  range [-2^31, 2^31-1] or not finite, 
;; * then the parameter indefiniteValue is returned. If the function should
;; * throw an error instead, a noninteger token must be passed to the parameter indefiniteValue.
;; * e.g.:
;; *   foo = MR_TO_INT32(x,throws)
;; */
MR_TO_INT32 macro x:req,indefiniteValue:=<80000000h>,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>
	MREAL_INEXACT = 0
	IF MREAL_&x&_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF (OPATTR indefiniteValue) NE 24h
			.err <x is not a numeric value>
			EXITM <0>
		ELSE
			EXITM <&indefiniteValue>
		ENDIF
	ELSEIF MREAL_&x&_flg AND MREAL_FLG_ZERO
		EXITM <0>
	ENDIF
	;;/* round to int32 */
	MR_ROUND mrtiTmp,x,0,,rm,n,1,32,-1
	IF MREAL_mrtiTmp_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF (OPATTR indefiniteValue) NE 24h
			.err <rounded value is out of int32 range>
			EXITM <0>
		ELSE
			EXITM <&indefiniteValue>
		ENDIF
	ELSEIF MREAL_&x&_flg AND MREAL_FLG_ZERO
		EXITM <0>
	ENDIF
	IF n EQ 1
		mrti_value = MREAL_mrtiTmp_w0 SHL 16
	ELSE
		mrti_value = (MREAL_mrtiTmp_w0 SHL 16 OR MREAL_mrtiTmp_w1)
	ENDIF
	mrti_shr = 32-MREAL_mrtiTmp_exp
	mrti_value = mrti_value SHR mrti_shr
	mrti_sign = (MREAL_mrtiTmp_flg AND MREAL_FLG_SIGN) NE 0
	IF mrti_value GT 2147483647 AND (NOT mrti_sign) OR mrti_value GT 2147483648 AND mrti_sign
		IF (OPATTR indefiniteValue) NE 24h
			.err <rounded value is out of int32 range>
			EXITM <0>
		ELSE
			EXITM <&indefiniteValue>
		ENDIF
	ENDIF
	mrti_tvalue TEXTEQU %mrti_value
	EXITM @CatStr(@SubStr(<-+>,2+mrti_sign,1),%mrti_tvalue)
endm

;;/**
;; * Round x to an unsigned integer. If the rounded value is out of 
;; * range [0, 2^32-1] or not finite, then the parameter
;; * indefiniteValue is returned. If the function should thorw an error instead,
;; * a noninteger token must be passed to the parameter indefiniteValue.
;; * e.g.:
;; *   foo = MR_TO_UINT32(x,throws)
;; */
MR_TO_UINT32 macro x:req,indefiniteValue:=<80000000h>,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>
	MREAL_INEXACT = 0
	IF MREAL_&x&_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF (OPATTR indefiniteValue) NE 24h
			.err <x is not a numeric value>
			EXITM <0>
		ELSE
			EXITM <&indefiniteValue>
		ENDIF
	ELSEIF MREAL_&x&_flg AND MREAL_FLG_ZERO
		EXITM <0>
	ENDIF
	;;/* round to uint32 */
	MR_ROUND mrtiTmp,x,0,,rm,n,1,32,-1
	IF MREAL_mrtiTmp_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF (OPATTR indefiniteValue) NE 24h
			.err <rounded value is out of uint32 range>
			EXITM <0>
		ELSE
			EXITM <&indefiniteValue>
		ENDIF
	ELSEIF MREAL_mrtiTmp_flg AND MREAL_FLG_SIGN
		IF (OPATTR indefiniteValue) NE 24h
			.err <rounded value is negative>
			EXITM <0>
		ELSE
			EXITM <&indefiniteValue>
		ENDIF
	ELSEIF MREAL_&x&_flg AND MREAL_FLG_ZERO
		EXITM <0>
	ENDIF
	IF n EQ 1
		mrti_value = MREAL_mrtiTmp_w0 SHL 16
	ELSE
		mrti_value = (MREAL_mrtiTmp_w0 SHL 16 OR MREAL_mrtiTmp_w1)
	ENDIF
	mrti_shr = 32-MREAL_mrtiTmp_exp
	mrti_value = mrti_value SHR mrti_shr
	mrti_sign = (MREAL_mrtiTmp_flg AND MREAL_FLG_SIGN) NE 0
	mrti_tvalue TEXTEQU %mrti_value
	EXITM mrti_tvalue
endm


;;/* declare constants used by MR_TO_INT64 */
MR_SET_CONST mrtiMaxI64_n,+,63,4,8000h,0h,0h,0h               ;; 2^63
MR_SET_CONST mrtiMaxI64_p,+,62,4,0ffffh,0ffffh,0ffffh,0fffeh  ;; 2^63-1

;;/**
;; * Round x to an integer (64 bit) and return the corresponding numeric literal.  
;; * If the rounded value is out of range [-2^63, 2^63-1] or not finite, then the parameter
;; * indefiniteValue is returned. If the function should thorw an error instead, a noninteger
;; * token must be passed to the parameter indefiniteValue.
;; * e.g.:
;; *   .data
;; *   myQword QWORD MR_TO_INT64(x,throws)
;; */
MR_TO_INT64 macro x:req,indefiniteValue:=<8000000000000000h>,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>
	MREAL_INEXACT = 0
	IF MREAL_&x&_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF @ScanForFlt(1,<&indefiniteValue>) NE 2
			.err <x is not a numeric value>
			EXITM <0>
		ELSE
			EXITM <&indefiniteValue>
		ENDIF
	ELSEIF MREAL_&x&_flg AND MREAL_FLG_ZERO
		EXITM <0>
	ENDIF
	;;/* round to int64 */
	MR_ROUND mrtiTmp,x,0,,rm,n,1,64,-1
	IF MREAL_mrtiTmp_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF @ScanForFlt(1,<&indefiniteValue>) NE 2
			.err <rounded value is out of int64 range>
			EXITM <0>
		ELSE
			EXITM <&indefiniteValue>
		ENDIF
	ELSEIF MREAL_&x&_flg AND MREAL_FLG_ZERO
		EXITM <0>
	ENDIF
	;;/* zero extend mrtiTmp if needed */
	mrti_cntr = n
	WHILE mrti_cntr LT 4
		@CatStr(<MREAL_mrtiTmp_w>,%mrti_cntr) = 0
		mrti_cntr = mrti_cntr + 1
	ENDM
	mrti_sign = (MREAL_mrtiTmp_flg AND MREAL_FLG_SIGN) NE 0
	;;/* check if value is out of range: -2^63 ... 2^63-1 */
	IF mrti_sign
		MR_CMP mrtiTmp,mrtiMaxI64_n,n
	ELSE
		MR_CMP mrtiTmp,mrtiMaxI64_p,n
	ENDIF
	IF mr_cmp GT 0
		;;/* case: number out of range */
		IF @ScanForFlt(1,<&indefiniteValue>) NE 2
			.err <rounded value is out of int64 range>
			EXITM <0>
		ELSE
			EXITM <&indefiniteValue>
		ENDIF
	ENDIF
	;;/* bring the 64 mantissa bits in right possition */
	MR_RSHIFT mrtiTmp,%64-MREAL_mrtiTmp_exp,4
	
	;;/* convert mantissa WORDs to 64 bit hexadecimal literal */
	mrti_tbits TEXTEQU <>
	mrti_cntr = 0
	WHILE mrti_cntr LT 4
		.radix 16
		mrti_txt TEXTEQU %@CatStr(<MREAL_mrtiTmp_w>,%mrti_cntr)
		.radix 10
		mrti_size SIZESTR mrti_txt
		IF mrti_size NE 4
			mrti_txt TEXTEQU @SubStr(<000>,mrti_size,),mrti_txt
		ENDIF
		mrti_tbits TEXTEQU mrti_tbits,mrti_txt
		mrti_cntr = mrti_cntr + 1
	ENDM
	mrti_tbits TEXTEQU <0>,mrti_tbits,<h>
	EXITM @CatStr(@SubStr(<-+>,2+mrti_sign,1),%mrti_tbits)
endm


;;/**
;; * Round x to an unsigned integer (64 bit) and return the corresponding numeric literal.  
;; * If the rounded value is out of range [0, 2^64-1] or not finite, then the parameter
;; * indefiniteValue is returned. If the function should thorw an error instead, a noninteger
;; * token must be passed to the parameter indefiniteValue.
;; * e.g.:
;; *   .data
;; *   myQword QWORD MR_TO_UINT64(x,throws)
;; */
MR_TO_UINT64 macro x:req,indefiniteValue:=<8000000000000000h>,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>
	MREAL_INEXACT = 0
	IF MREAL_&x&_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF @ScanForFlt(1,<&indefiniteValue>) NE 2
			.err <x is not a numeric value>
			EXITM <0>
		ELSE
			EXITM <&indefiniteValue>
		ENDIF
	ELSEIF MREAL_&x&_flg AND MREAL_FLG_ZERO
		EXITM <0>
	ENDIF
	;;/* round to uint64 */
	MR_ROUND mrtiTmp,x,0,,rm,n,1,64,-1
	IF MREAL_mrtiTmp_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF @ScanForFlt(1,<&indefiniteValue>) NE 2
			.err <rounded value is out of uint64 range>
			EXITM <0>
		ELSE
			EXITM <&indefiniteValue>
		ENDIF
	ELSEIF MREAL_mrtiTmp_flg AND MREAL_FLG_SIGN
		IF @ScanForFlt(1,<&indefiniteValue>) NE 2
			.err <rounded value is negative>
			EXITM <0>
		ELSE
			EXITM <&indefiniteValue>
		ENDIF
	ELSEIF MREAL_&x&_flg AND MREAL_FLG_ZERO
		EXITM <0>
	ENDIF
	
	;;/* zero extend mrtiTmp if needed */
	mrti_cntr = n
	WHILE mrti_cntr LT 4
		@CatStr(<MREAL_mrtiTmp_w>,%mrti_cntr) = 0
		mrti_cntr = mrti_cntr + 1
	ENDM

	;;/* bring the 64 mantissa bits in right possition */
	MR_RSHIFT mrtiTmp,%64-MREAL_mrtiTmp_exp,4
	
	;;/* convert mantissa WORDs to 64 bit hexadecimal literal */
	mrti_tbits TEXTEQU <>
	mrti_cntr = 0
	WHILE mrti_cntr LT 4
		.radix 16
		mrti_txt TEXTEQU %@CatStr(<MREAL_mrtiTmp_w>,%mrti_cntr)
		.radix 10
		mrti_size SIZESTR mrti_txt
		IF mrti_size NE 4
			mrti_txt TEXTEQU @SubStr(<000>,mrti_size,),mrti_txt
		ENDIF
		mrti_tbits TEXTEQU mrti_tbits,mrti_txt
		mrti_cntr = mrti_cntr + 1
	ENDM
	mrti_tbits TEXTEQU <0>,mrti_tbits,<h>
	EXITM mrti_tbits
endm


;;/* r = x*2^round(y) */
MR_SCALE macro r:req,x:req,y:req,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>
	MREAL_INEXACT = 0
	IF MREAL_&x&_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF MREAL_ERROR_FOR_NAN_INPUT
			.err <x is not a numeric value>
		ENDIF
		MR_RAW_SET_N r,NaN,,n
		EXITM
	ELSEIF MREAL_&y&_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF MREAL_ERROR_FOR_NAN_INPUT
			.err <y is not a numeric value>
		ENDIF
		MR_RAW_SET_N r,NaN,,n
		EXITM
	ELSEIF MREAL_&x&_flg AND MREAL_FLG_ZERO
		MR_SET_ZERO r,n
		EXITM
	ELSEIF MREAL_&y&_flg AND MREAL_FLG_ZERO
		MR_MOV r,x,n
		EXITM
	ENDIF
	
	;;/* get exponent value */
	IF MREAL_&y&_flg AND MREAL_FLG_SIGN
		mrsb_pwr2 = MR_TO_INT32(y,80000000h,rm,n)
	ELSE
		mrsb_pwr2 = MR_TO_INT32(y,7fffffffh,rm,n)
	ENDIF
	MR_MOV r,x
	;;/* scale */
	MREAL_&r&_exp = MREAL_&r&_exp + mrsb_pwr2
	
	mrce_errstr_overflow  TEXTEQU <x*2^round(y): exponent overflow>
	mrce_errstr_underflow TEXTEQU <x*2^round(y): exponent underflow>
	MR_CHECK_EXPONENT r,,,n,rm
	IFNB mrce_errstr
		.err mrce_errstr
	ENDIF
endm

;;/* r = x*2^pwr2 */
MR_CSCALE macro r:req,x:req,pwr2:=<0>,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>
	MREAL_INEXACT = 0
	IF MREAL_&x&_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF MREAL_ERROR_FOR_NAN_INPUT
			.err <x is not a numeric value>
		ENDIF
		MR_RAW_SET_N r,NaN,,n
		EXITM
	ELSEIF MREAL_&x&_flg AND MREAL_FLG_ZERO
		MR_SET_ZERO r,n
		EXITM
	ELSEIFE pwr2
		MR_MOV r,x,n
		EXITM
	ENDIF
	MR_MOV r,x
	MREAL_&r&_exp = MREAL_&r&_exp + pwr2

	mrce_errstr_overflow  TEXTEQU <x*2^pwr2 : exponent overflow>
	mrce_errstr_underflow TEXTEQU <x*2^pwr2 : exponent underflow>
	MR_CHECK_EXPONENT r,,,n,rm
	IFNB mrce_errstr
		.err mrce_errstr
	ENDIF
endm


;;/* TRUE if: x == y */
MR_EQ macro x:req,y:req,n:=<MREAL_XDIM>
	MR_CMP x,y,n
	IFE mr_cmp
		EXITM <-1>
	ENDIF
	EXITM <0>
endm

;;/* TRUE if: x != y or unordered */
MR_NE macro x:req,y:req,n:=<MREAL_XDIM>
	MR_CMP x,y,n
	IF mr_cmp NE 0
		EXITM <-1>
	ENDIF
	EXITM <0>
endm

;;/* TRUE if: x>y */
MR_GT macro x:req,y:req,n:=<MREAL_XDIM>
	MR_CMP x,y,n
	IF mr_cmp EQ 1
		EXITM <-1>
	ENDIF
	EXITM <0>
endm

;;/* TRUE if: x>=y */
MR_GE macro x:req,y:req,n:=<MREAL_XDIM>
	MR_CMP x,y,n
	IF mr_cmp GE 0
		EXITM <-1>
	ENDIF
	EXITM <0>
endm

;;/* TRUE if: x<y */
MR_LT macro x:req,y:req,n:=<MREAL_XDIM>
	MR_CMP x,y,n
	IF mr_cmp EQ -1
		EXITM <-1>
	ENDIF
	EXITM <0>
endm

;;/* TRUE if: x<=y */
MR_LE macro x:req,y:req,n:=<MREAL_XDIM>
	MR_CMP x,y,n
	IF mr_cmp LE 0 AND mr_cmp NE -2
		EXITM <-1>
	ENDIF
	EXITM <0>
endm

;;/* TRUE if: unordered */
MR_UN macro x:req,y:req,n:=<MREAL_XDIM>
	MR_CMP x,y,n
	IF mr_cmp EQ -2
		EXITM <-1>
	ENDIF
	EXITM <0>
endm

;;/* TRUE if: x<=y or unordered */
MR_NOT_GT macro x:req,y:req,n:=<MREAL_XDIM>
	MR_CMP x,y,n
	IF mr_cmp LE 0
		EXITM <-1>
	ENDIF
	EXITM <0>
endm

;;/* TRUE if: x<y or unordered */
MR_LT_UN macro x:req,y:req,n:=<MREAL_XDIM>
	MR_CMP x,y,n
	IF mr_cmp LT 0
		EXITM <-1>
	ENDIF
	EXITM <0>
endm

;;/* TRUE if: x>=y or unordered */
MR_NOT_LT macro x:req,y:req,n:=<MREAL_XDIM>
	MR_CMP x,y,n
	IF mr_cmp GE 0 OR mr_cmp EQ -2
		EXITM <-1>
	ENDIF
	EXITM <0>
endm

;;/* TRUE if: x>y or unordered */
MR_GT_UN macro x:req,y:req,n:=<MREAL_XDIM>
	MR_CMP x,y,n
	IF mr_cmp EQ 1 OR mr_cmp EQ -2
		EXITM <-1>
	ENDIF
	EXITM <0>
endm

;;/* TRUE if: not unordered */
MR_NOT_UN macro x:req,y:req,n:=<MREAL_XDIM>
	MR_CMP x,y,n
	IF mr_cmp NE -2
		EXITM <-1>
	ENDIF
	EXITM <0>
endm


;;/**
;; * Compare x with y and stores the result in the equate
;; * mr_cmp, which indicates the relation between x and y.
;; *
;; *  mr_cmp:  -2  ->  unordered (NaN as input)
;; *           -1  ->  x < y
;; *            0  ->  x == y
;; *            1  ->  x > y
;; *
;; * This macro does not modify MREAL_INEXACT.
;; */
MR_CMP macro x:req,y:req,n:=<MREAL_XDIM>
	
	;;/**
	;; * handle special values and trivial cases
	;; */
	IF MREAL_&x&_flg AND MREAL_FLG_NAN OR MREAL_&y&_flg AND MREAL_FLG_NAN
		mr_cmp = -2
		EXITM
	ELSEIF (MREAL_&x&_flg OR MREAL_&y&_flg) AND MREAL_FLG_INF
		;;/**
		;; * get LUT index from sign and Infinity-flag:
		;; *   bit 0 -> Inf flg of x
		;; *       1 -> sign of x
		;; *       2 -> Inf flg of y
		;; *       3 -> sign of y
		;; * LUT:
		;; *    value   x     y     relation LUT  |  value   x     y     relation LUT
		;; *    0000y  +x    +y       ---    --   |  1000y  +x    -y       ---    -- 
		;; *    0001y  +Inf  +y       x>y    +1   |  1001y  +Inf  -y       x>y    +1 
		;; *    0010y  -x    +y       ---    --   |  1010y  -x    -y       ---    -- 
		;; *    0011y  -Inf  +y       x<y    -1   |  1011y  -Inf  -y       x<y    -1 
		;; *    0100y  +x    +Inf     x<y    -1   |  1100y  +x    -Inf     x>y    +1 
		;; *    0101y  +Inf  +Inf     x=y    00   |  1101y  +Inf  -Inf     x>y    +1 
		;; *    0110y  -x    +Inf     x<y    -1   |  1110y  -x    -Inf     x>y    +1 
		;; *    0111y  -Inf  +Inf     x<y    -1   |  1111y  -Inf  -Inf     x=y    00 
		;; *
		;; */
		mrcmp_index = MREAL_&x&_flg SHR 31 AND 1 OR MREAL_&x&_flg AND 2 OR MREAL_&y&_flg SHR 29 AND 4 OR MREAL_&y&_flg SHL 2 AND 8
		mr_cmp = @SubStr(<..+1..-1-100-1-1..+1..-1+1+1+100>,mrcmp_index*2+1,2)
		EXITM
	ELSEIF MREAL_&x&_flg AND MREAL_&y&_flg AND MREAL_FLG_ZERO
		mr_cmp = 0
		EXITM
	ELSEIF MREAL_&x&_flg AND MREAL_FLG_ZERO
		IF MREAL_&y&_flg AND MREAL_FLG_SIGN
			mr_cmp = 1
		ELSE
			mr_cmp = -1
		ENDIF
		EXITM
	ELSEIF MREAL_&y&_flg AND MREAL_FLG_ZERO
		IF MREAL_&x&_flg AND MREAL_FLG_SIGN
			mr_cmp = -1
		ELSE
			mr_cmp = 1
		ENDIF
		EXITM
	ELSEIF (MREAL_&x&_flg XOR MREAL_&y&_flg) AND MREAL_&x&_flg AND MREAL_FLG_SIGN
		mr_cmp = -1
		EXITM
	ELSEIF (MREAL_&x&_flg XOR MREAL_&y&_flg) AND MREAL_&y&_flg AND MREAL_FLG_SIGN
		mr_cmp = 1
		EXITM
	ELSEIF MREAL_&x&_exp GT MREAL_&y&_exp
		mr_cmp = 1
		EXITM
	ELSEIF MREAL_&x&_exp LT MREAL_&y&_exp
		mr_cmp = -1
		EXITM
	ENDIF
	
	;;/**
	;; * case: x and y are normal values with
	;; * the same sign and exponent -> compare mantissas.
	;; */
	mrcmp_cntr = 0
	REPEAT n
		mrcmp_tcntr TEXTEQU %mrcmp_cntr
	%	IF MREAL_&x&_w&mrcmp_tcntr& NE MREAL_&y&_w&mrcmp_tcntr&
			EXITM
		ENDIF
		mrcmp_cntr = mrcmp_cntr + 1
	ENDM
	IF mrcmp_cntr EQ n
		mr_cmp = 0
		EXITM
	ENDIF
%	IF MREAL_&x&_w&mrcmp_tcntr& LT MREAL_&y&_w&mrcmp_tcntr&
		mr_cmp = -1
	ELSE
		mr_cmp = 1
	ENDIF
	EXITM
endm



MR_ADD macro r:req,x:req,y:req,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>
	MR_SUM r,x,y,0,rm,n,n
endm

MR_SUB macro r:req,x:req,y:req,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>
	MR_SUM r,x,y,-1,rm,n,n
endm

;;/**
;; * Add or subtract two MREAL-numbers and round
;; * the result according to the current rounding mode.
;; * pseudo code:
;; *  if x or y is NaN or infinite
;; *    r = NaN;
;; *  else
;; *    r = (op==0)?(x+y):(x-y);
;; *
;; * Remarks: 1 <= nr <= n
;; */
MR_SUM macro r:req,x:req,y:req,op:=<0>,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>,nr:=<MREAL_XDIM>

	MREAL_INEXACT = 0
	
	;;/* check precision settings */
	IF nr LT 1 OR nr GT n
		.err <invalid parameter(7): _nr=nr is out of range 1 to _n=n>
		EXITM
	ENDIF
	
	;;/**
	;; * process special input values
	;; */
	IF MREAL_&x&_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF MREAL_ERROR_FOR_NAN_INPUT
			.err <x is not a numeric value>
		ENDIF
		MR_RAW_SET_N r,NaN,,nr
		EXITM
	ELSEIF MREAL_&y&_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF MREAL_ERROR_FOR_NAN_INPUT
			.err <y is not a numeric value>
		ENDIF
		MR_RAW_SET_N r,NaN,,nr
		EXITM
	ELSEIF MREAL_&x&_flg AND MREAL_&y&_flg AND MREAL_FLG_ZERO
		MR_SET_ZERO r,nr
		EXITM
	ELSEIF MREAL_&x&_flg AND MREAL_FLG_ZERO
		MR_CONVERT r,y,n,nr,rm,0
		MREAL_&r&_flg = MREAL_&r&_flg XOR ((op NE 0) AND MREAL_FLG_SIGN)
		EXITM
	ELSEIF MREAL_&y&_flg AND MREAL_FLG_ZERO
		MR_CONVERT r,x,n,nr,rm,0
		EXITM
	ENDIF

	mra_x TEXTEQU <&x>
	mra_y TEXTEQU <&y>
	mra_sgnx = (MREAL_&x&_flg AND MREAL_FLG_SIGN) NE 0
	mra_sgny = ((MREAL_&y&_flg AND MREAL_FLG_SIGN) NE 0) XOR (op NE 0)

	;;/**
	;; * make sure that |A| > |B| for C=A+B
	;; */
	IF MREAL_&x&_exp LT MREAL_&y&_exp
		mra_x TEXTEQU <&y>
		mra_y TEXTEQU <&x>
		mra_sgnx = ((MREAL_&y&_flg AND MREAL_FLG_SIGN) NE 0) XOR (op NE 0)
		mra_sgny = (MREAL_&x&_flg AND MREAL_FLG_SIGN) NE 0
	ELSEIF MREAL_&x&_exp EQ MREAL_&y&_exp
		;;/**
		;; * determine greater mantissa
		;; */
		mra_cntr = 0
		mra_tcntr TEXTEQU %mra_cntr
		WHILE mra_cntr LT n
		%	IF MREAL_&x&_w&mra_tcntr& NE MREAL_&y&_w&mra_tcntr&
				EXITM
			ENDIF
			mra_cntr = mra_cntr + 1
			mra_tcntr TEXTEQU %mra_cntr
		ENDM
		IF mra_cntr NE n
			;;/* x < y --> swap x,y */
		%	IF MREAL_&x&_w&mra_tcntr& LT MREAL_&y&_w&mra_tcntr&
				mra_x TEXTEQU <&y>
				mra_y TEXTEQU <&x>
				mra_sgnx = ((MREAL_&y&_flg AND MREAL_FLG_SIGN) NE 0) XOR (op NE 0)
				mra_sgny = (MREAL_&x&_flg AND MREAL_FLG_SIGN) NE 0
			ENDIF
		ELSE
			;;/**
			;; * case: exponent and mantissa bits of x and y are equal.
			;; * If the signs differs, the result is zero. Otherwise
			;; * the result is: 2*x, respectively 2*y.
			;; * The rounding mode has no effect for multiplications with 2^n,
			;; * because all additional accumulator bits would be zero.
			;; */
			IF (MREAL_&x&_flg XOR (MREAL_&y&_flg XOR (op NE 0))) AND MREAL_FLG_SIGN
				MR_SET_ZERO r,nr
			ELSE
				MR_RAW_COMPOSE r,%MREAL_&x&_flg,%MREAL_&x&_exp+1,x,n
				MR_CONVERT r,r,n,nr,rm,0
			ENDIF
			EXITM
		ENDIF
	ENDIF

%	mra_ex = MREAL_&mra_x&_exp
%	mra_ey = MREAL_&mra_y&_exp
	
	;;/**
	;; * copy: y --> mraTmp
	;; *       x --> r
	;; */
	MR_MOV mraTmp,%mra_y,n
	MR_MOV r,%mra_x,n
	mra_y TEXTEQU <mraTmp>
	
	;;/* extend the mantissa bits: (2*(n)+1)*16 */
	MR_PREPARE_ACCUMULATOR r,n,%(n)*2+1
	MR_PREPARE_ACCUMULATOR %mra_y,n,%(n)*2+1
	
	IF (mra_ex-mra_ey) GE ((n)*16+2)
		;;/**
		;; * y is too small to affect the bits of x.
		;; * However, for RM "up" or "down" an arbitrary smaller value can change
		;; * the result. To respect that the mantissa of y gets the value sgn(y)*2^(-((n)*16+3)).
		;; */
		mra_cntr = 0
		mra_tcntr TEXTEQU %mra_cntr
		WHILE mra_cntr LT n
		%	MREAL_&mra_y&_w&mra_tcntr& = 0
			mra_cntr = mra_cntr + 1
			mra_tcntr TEXTEQU %mra_cntr
		ENDM
	%	MREAL_&mra_y&_w&mra_tcntr& = 2000h
	ELSE
		;;/* bring y in right position */
		MR_RSHIFT %mra_y,%(mra_ex-mra_ey),%(n)*2+1
	ENDIF
	
	;;/**
	;; * Sum up x and y.
	;; * For unlike signs the operation is r=|x|-|y|, otherwise it is r=|x|+|y|.
	;; * The sign of the result is determined by the greater absolute value, which
	;; * is the left-sided operand r=x (due to preceding sorting).
	;; * For subtraction the final carry has no meaning, because the result can't
	;; * get negative (|r| > 0).
	;; */
	MREAL_&r&_flg = mra_sgnx AND MREAL_FLG_SIGN
	mra_sub = mra_sgnx XOR mra_sgny
	mra_msk = LOWWORD mra_sub
	mra_carry = mra_sub AND 1
	mra_cntr = (n)*2
	WHILE mra_cntr GE 0
		mra_tcntr TEXTEQU %mra_cntr
	%	mra_tmp = MREAL_&r&_w&mra_tcntr& + (MREAL_&mra_y&_w&mra_tcntr& XOR mra_msk) + mra_carry
	%	MREAL_&r&_w&mra_tcntr& = LOWWORD mra_tmp
		mra_carry = HIGHWORD mra_tmp
		mra_cntr = mra_cntr - 1
	ENDM
	IF mra_sub
		mra_carry = 0
	ENDIF
	MR_NORMALIZE_ACCUM r,%mra_carry,%(n)*2+1
	
	MR_ROUND_ACCUMULATOR r,nr,%(n)*2+1,rm
	
	;;/**
	;; * check for exponent over- or underflow.
	;; */
	mrce_errstr_overflow  TEXTEQU <the sum of x and y exceeds the exponent limit (MREAL_MAX_EXP)>
	mrce_errstr_underflow TEXTEQU <the sum of x and y is too small (exponent underflow (MREAL_MIN_EXP))>
	MR_CHECK_EXPONENT r,,,nr,rm
	IFNB mrce_errstr
		.err mrce_errstr
	ENDIF
	;; job done :-D
endm


;;/**
;; * Multiply two MREAL-values and round them according 
;; * to the current rounding mode.
;; * Pseudo code:
;; *  if x or y is NaN or infinite
;; *    r = NaN;
;; *  else
;; *    r = x * y;
;; */
MR_MUL macro r:req,x:req,y:req,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>
	
	MREAL_INEXACT = 0
	
	;;/**
	;; * process special input values
	;; */
	IF MREAL_&x&_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF MREAL_ERROR_FOR_NAN_INPUT
			.err <x is not a numeric value>
		ENDIF
		MR_RAW_SET_N r,NaN,,n
		EXITM
	ELSEIF MREAL_&y&_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF MREAL_ERROR_FOR_NAN_INPUT
			.err <y is not a numeric value>
		ENDIF
		MR_RAW_SET_N r,NaN,,n
		EXITM
	ELSEIF ((MREAL_&x&_flg AND MREAL_FLG_ZERO) NE 0) OR ((MREAL_&y&_flg AND MREAL_FLG_ZERO) NE 0)
		MR_SET_ZERO r,n
		EXITM
	ENDIF

    mrm_sgn = ((MREAL_&x&_flg AND MREAL_FLG_SIGN) NE 0) XOR ((MREAL_&y&_flg AND MREAL_FLG_SIGN) NE 0)

	;;/* set exponent and sign of intermediate result */
	MREAL_mrmTmp_flg = mrm_sgn AND MREAL_FLG_SIGN
	MREAL_mrmTmp_exp = MREAL_&x&_exp + MREAL_&y&_exp
	
	;;/**
	;; * For multiplication the mantissas are treated as integers:
	;; * 
	;; *    r = (a_i*2^(i*16) + ... + a_1*2^16 + a_0*2^0) * (b_j*2^(j*16) + ... + b_1*2^16 + b_0*2^0)
	;; *
	;; * The elements {a_0,a_1,...a_i} and {b_0,b_1...b_j} represent the mantissa WORDs
	;; * in ascending order (e.g a_0 holds the LSB).
	;; *
	;; * Pseudo code:   
	;; *
	;; *    assert: size of unsigned long integer == 2 * (size of unsigned short integer)
	;; *    a,b   -> is array 0 to n-1   of unsigned short integer
	;; *    r     -> is array 0 to 2*n-1 of unsigned short integer
	;; *    d,l,h -> is unsigned long integer
	;; *    r = 0
	;; *    l = h = 0
	;; *    for k = 0 to 2*n-2
	;; *    {
	;; *      for each pair (i,j) with i+j == k and n-1 >= i >= 0 and n-1 >= j >= 0
	;; *      {
	;; *        d = a[i] * b[j]
	;; *        l = l + d.low
	;; *        h = h + d.high
	;; *      }
	;; *      r[k] = l.low
	;; *      l = h.low + l.high
	;; *      h = h.high
	;; *    }
	;; *    r[2*n-1] = l.low
	;; * 
	;; * The inner loop accumulates all pairs a_i*b_j*2^((i+j)*16) with the same factor
	;; *  2^((i+j)*16).
	;; *
	;; * The following pseudo code shows the used implementation:
	;; *
	;; *    r = l = h = 0;                     
	;; *    for (k = 0 to 2*n-2) {                             
	;; *      p = max(0,k-n+1);            
	;; *      i=p; j=k-p;                  
	;; *      while (j >= p) {                           
	;; *        d = x[i] * y[j];           
	;; *        l = l + (d & 0xffff);      
	;; *        h = h + (d >> 16);         
	;; *        i++; j--;                  
	;; *      }                           
	;; *      r[k] = l & 0xffff;                    
	;; *      l = (h & 0xffff) + (l >> 16);
	;; *      h = h >> 16;                 
	;; *    }
	;; *    r[2*n-1]= l & 0xffff;                          
	;; * 
	;; * Remark that the below code reverses the indexes, because the mantissa bits
	;; * are saved starting with the most significant WORD.
	;; *
	;; */
	
	mrm_l = 0
	mrm_h = 0
	mrm_n = n-1
	mrm_o = 2*(n)-1
	mrm_k = 0
	mrm_lmax = 2*(n)-2
	WHILE mrm_k LE mrm_lmax
		mrm_p = mrm_k-mrm_n AND mrm_k-mrm_n GE 0
		mrm_i = mrm_p
		mrm_j = mrm_k - mrm_p 
		WHILE mrm_j GE mrm_p
			mrm_d = @CatStr(<MREAL_&x&_w>,%mrm_n-mrm_i) * @CatStr(<MREAL_&y&_w>,%mrm_n-mrm_j)
			mrm_l = mrm_l + LOWWORD mrm_d
			mrm_h = mrm_h + HIGHWORD mrm_d
			mrm_i = mrm_i+1
			mrm_j = mrm_j-1
		ENDM
		@CatStr(<MREAL_mrmTmp_w>,%mrm_o-mrm_k) = LOWWORD mrm_l
		mrm_l = LOWWORD mrm_h + HIGHWORD mrm_l
		mrm_h = HIGHWORD mrm_h
		mrm_k = mrm_k + 1
	ENDM
	;;/* mrm_l holds the most significant WORD */
	MREAL_mrmTmp_w0 = LOWWORD mrm_l

	;;/**
	;; * Because the input values x and y are normalized,
	;; * the result can never get smaller than 2^(-2 + (expX+expY)).
	;; * Thus the normalization consist of a left shift 
	;; * by 1 bit if the result is below 2^(-1 + (expX+expY)).
	;; */
	IFE mrm_l AND 8000h
		MR_LSHIFT_1 mrmTmp,%2*(n)
		MREAL_mrmTmp_exp = MREAL_mrmTmp_exp - 1
	ENDIF

	MR_ROUND_ACCUMULATOR mrmTmp,n,%2*(n),rm
	
	;;/**
	;; * check for exponent over- or underflow.
	;; */
	mrce_errstr_overflow  TEXTEQU <the product x*y exceeds the exponent limit (MREAL_MAX_EXP)>
	mrce_errstr_underflow TEXTEQU <the product x*y is too small (exponent underflow (MREAL_MIN_EXP))>
	MR_CHECK_EXPONENT mrmTmp,,,n,rm
	IFNB mrce_errstr
		.err mrce_errstr
	ENDIF
	
	;;/* store result */
	MR_MOV r,mrmTmp,n
	;;  job done :-D
endm


;;/**
;; * Generalization of MR_MUL: Multiply x and y with the 
;; * precision nx+ny and then round the result to precision rn.
;; * Remarks: 1 <= nr <= nx+ny
;; */
MR_XMUL macro r:req,x:req,y:req,nr:=<MREAL_XDIM>,nx:=<MREAL_XDIM>,ny:=<MREAL_XDIM>,rm:=<MREAL_ROUND_MODE>
	
	MREAL_INEXACT = 0
	
	;;/* check precision settings */
	IF nr LT 1 OR nr GT nx+ny
		.err <invalid parameter(4): _nr=nr is out of range 1 to nx+ny>
		EXITM
	ENDIF
	
	;;/**
	;; * process special input values
	;; */
	IF MREAL_&x&_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF MREAL_ERROR_FOR_NAN_INPUT
			.err <x is not a numeric value>
		ENDIF
		MR_RAW_SET_N r,NaN,,nr
		EXITM
	ELSEIF MREAL_&y&_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF MREAL_ERROR_FOR_NAN_INPUT
			.err <y is not a numeric value>
		ENDIF
		MR_RAW_SET_N r,NaN,,nr
		EXITM
	ELSEIF ((MREAL_&x&_flg AND MREAL_FLG_ZERO) NE 0) OR ((MREAL_&y&_flg AND MREAL_FLG_ZERO) NE 0)
		MR_SET_ZERO r,nr
		EXITM
	ENDIF

    mrm_sgn = ((MREAL_&x&_flg AND MREAL_FLG_SIGN) NE 0) XOR ((MREAL_&y&_flg AND MREAL_FLG_SIGN) NE 0)

	;;/* set exponent and sign of intermediate result */
	MREAL_mrmTmp_flg = mrm_sgn AND MREAL_FLG_SIGN
	MREAL_mrmTmp_exp = MREAL_&x&_exp + MREAL_&y&_exp
	
	;;/**
	;; * For multiplication the mantissas are treated as integers:
	;; * 
	;; *    r = (a_i*2^(i*16) + ... + a_1*2^16 + a_0*2^0) * (b_j*2^(j*16) + ... + b_1*2^16 + b_0*2^0)
	;; *
	;; * The elements {a_0,a_1,...a_i} and {b_0,b_1...b_j} represent the mantissa WORDs
	;; * in ascending order (e.g a_0 holds the LSB).
	;; *
	;; * Pseudo code:   
	;; *
	;; *    assert: size of unsigned long integer == 2 * (size of unsigned short integer)
	;; *    a     -> is array 0 to na-1    of unsigned short integer
	;; *    b     -> is array 0 to nb-1    of unsigned short integer
	;; *    r     -> is array 0 to na+nb-1 of unsigned short integer
	;; *    d,l,h -> is unsigned long integer
	;; *    r = 0
	;; *    l = h = 0
	;; *    n = na+nb
	;; *    for k = 0 to n-2
	;; *    {
	;; *      for each pair (i,j) with i+j == k and na-1 >= i >= 0 and nb-1 >= j >= 0
	;; *      {
	;; *        d = a[i] * b[j]
	;; *        l = l + d.low
	;; *        h = h + d.high
	;; *      }
	;; *      r[k] = l.low
	;; *      l = h.low + l.high
	;; *      h = h.high
	;; *    }
	;; *    r[n-1] = l.low
	;; * 
	;; * The inner loop accumulates all pairs a_i*b_j*2^((i+j)*16) with the same factor
	;; *  2^((i+j)*16).
	;; *
	;; * The following pseudo code shows the used implementation:
	;; *
	;; *    r = l = h = 0;
	;; *    n = na+nb;
	;; *    iu = 0                    // maximal i for current k
	;; *    ju = 0                    // maximal j for current k                 
	;; *    for (k = 0 to n-2) {                             
	;; *      j = min(nb-1, ju);
	;; *      ic = min(na-1, iu);         
	;; *      i = abs(k-j);
	;; *      while (i <= ic) {                           
	;; *        d = x[i] * y[j];           
	;; *        l = l + (d & 0xffff);      
	;; *        h = h + (d >> 16);         
	;; *        i++; j--;                  
	;; *      }                           
	;; *      r[k] = l & 0xffff;                    
	;; *      l = (h & 0xffff) + (l >> 16);
	;; *      h = h >> 16;
	;; *      iu++; ju++;               
	;; *    }
	;; *    r[n-1]= l & 0xffff;                     
	;; * 
	;; * Remark that the below code reverses the indexes, because the mantissa bits
	;; * are saved starting with the most significant WORD.
	;; *
	;; */
	
	mrm_na = nx-1
	mrm_nb = ny-1
	mrm_o = nx+ny-1
	mrm_lmax = mrm_o - 1
	mrm_l = 0
	mrm_h = 0
	mrm_k = 0
	mrm_iu = 0
	mrm_ju = 0
	WHILE mrm_k LE mrm_lmax
		mrm_j = mrm_ju AND mrm_ju LE mrm_nb OR mrm_nb AND mrm_ju GT mrm_nb
		mrm_ic = mrm_iu AND mrm_iu LE mrm_na OR mrm_na AND mrm_iu GT mrm_na
		mrm_i = mrm_k - mrm_j
		mrm_i = mrm_i AND mrm_i GE 0 OR -mrm_i AND mrm_i LT 0
		WHILE mrm_i LE mrm_ic
			mrm_d = @CatStr(<MREAL_&x&_w>,%mrm_na-mrm_i) * @CatStr(<MREAL_&y&_w>,%mrm_nb-mrm_j)
			mrm_l = mrm_l + LOWWORD mrm_d
			mrm_h = mrm_h + HIGHWORD mrm_d
			mrm_i = mrm_i+1
			mrm_j = mrm_j-1
		ENDM
		@CatStr(<MREAL_mrmTmp_w>,%mrm_o-mrm_k) = LOWWORD mrm_l
		mrm_l = LOWWORD mrm_h + HIGHWORD mrm_l
		mrm_h = HIGHWORD mrm_h
		mrm_iu = mrm_iu + 1
		mrm_ju = mrm_ju + 1
		mrm_k = mrm_k + 1
	ENDM
	;;/* mrm_l holds the most significant WORD */
	MREAL_mrmTmp_w0 = LOWWORD mrm_l

	;;/**
	;; * Because the input values x and y are normalized,
	;; * the result can never get smaller than 2^(-2 + (expX+expY)).
	;; * Thus the normalization consist of a left shift 
	;; * by 1 bit if the result is below 2^(-1 + (expX+expY)).
	;; */
	IFE mrm_l AND 8000h
		MR_LSHIFT_1 mrmTmp,%(nx+ny)
		MREAL_mrmTmp_exp = MREAL_mrmTmp_exp - 1
	ENDIF

	MR_ROUND_ACCUMULATOR mrmTmp,nr,%(nx+ny),rm
	
	;;/**
	;; * check for exponent over- or underflow.
	;; */
	mrce_errstr_overflow  TEXTEQU <the product x*y exceeds the exponent limit (MREAL_MAX_EXP)>
	mrce_errstr_underflow TEXTEQU <the product x*y is too small (exponent underflow (MREAL_MIN_EXP))>
	MR_CHECK_EXPONENT mrmTmp,,,nr,rm
	IFNB mrce_errstr
		.err mrce_errstr
	ENDIF
	
	;;/* store result */
	MR_MOV r,mrmTmp,nr
endm


;;/**
;; * fused multiply–add
;; *    r = a*b + c 
;; */
MR_FMADD macro r:req,a:req,b:req,c:req,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>
	MR_FMC r,c,a,b,0,0,rm,n
endm

;;/**
;; * fused multiply–subtract
;; *    r = a*b - c 
;; */
MR_FMSUB macro r:req,a:req,b:req,c:req,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>
	MR_FMC r,c,a,b,-1,0,rm,n
endm

;;/**
;; * fused negative-multiply–add
;; *    r = -a*b + c
;; */
MR_FNMADD macro r:req,a:req,b:req,c:req,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>
	MR_FMC r,c,a,b,0,-1,rm,n
endm

;;/**
;; * fused negative-multiply–subtract
;; *    r = -a*b - c
;; */
MR_FNMSUB macro r:req,a:req,b:req,c:req,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>
	MR_FMC r,c,a,b,-1,-1,rm,n
endm

;; fused multiply–accumulate
;; if negA == 0
;;   if negBxC == 0
;;     r = a + b*c
;;   else
;;     r = a - b*c
;; else
;;   if negBxC == 0
;;     r = -a + b*c
;;   else
;;     r = -a - b*c
MR_FMC macro r:req,a:req,b:req,c:req,negA:=<0>,negBxC:=<0>,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>
	
	MREAL_INEXACT = 0
	
	;;/**
	;; * process special input values
	;; */
	IF MREAL_&a&_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF MREAL_ERROR_FOR_NAN_INPUT
			.err <a is not a numeric value>
		ENDIF
		MR_RAW_SET_N r,NaN,,n
		EXITM
	ELSEIF MREAL_&b&_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF MREAL_ERROR_FOR_NAN_INPUT
			.err <b is not a numeric value>
		ENDIF
		MR_RAW_SET_N r,NaN,,n
		EXITM
	ELSEIF MREAL_&c&_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF MREAL_ERROR_FOR_NAN_INPUT
			.err <c is not a numeric value>
		ENDIF
		MR_RAW_SET_N r,NaN,,n
		EXITM
	ELSEIF ((MREAL_&b&_flg AND MREAL_FLG_ZERO) NE 0) OR ((MREAL_&c&_flg AND MREAL_FLG_ZERO) NE 0)
		IF (MREAL_&a&_flg AND MREAL_FLG_ZERO) NE 0
			MR_SET_ZERO r,n
		ELSE
			MR_MOV r,a,n
			MREAL_&r&_flg = MREAL_&r&_flg XOR (MREAL_FLG_SIGN AND (negA NE 0))
		ENDIF
		EXITM
	ENDIF
	
	;;/**
	;; * Get the sign of c*b and prepare fmcTmp
	;; */
    mrf_sgnBxC = (((MREAL_&b&_flg AND MREAL_FLG_SIGN) NE 0) XOR ((MREAL_&c&_flg AND MREAL_FLG_SIGN) NE 0)) XOR (negBxC NE 0)
	MREAL_fmcTmp_flg = mrf_sgnBxC AND MREAL_FLG_SIGN
	MREAL_fmcTmp_exp = MREAL_&b&_exp + MREAL_&c&_exp

	;;/**
	;; * The following pseudo code shows the multiplication fmcTmp = b*c.
	;; *    
	;; *    n = MREAL_XDIM
	;; *    r = l = h = 0;                     
	;; *    for (k = 0 to 2*n-2) {                             
	;; *      p = max(0,k-n+1);            
	;; *      i=p; j=k-p;                  
	;; *      while (j >= p) {                           
	;; *        d = b[i] * c[j];           
	;; *        l = l + (d & 0xffff);      
	;; *        h = h + (d >> 16);         
	;; *        i++; j--;                  
	;; *      }                           
	;; *      fmcTmp[k] = l & 0xffff;                    
	;; *      l = (h & 0xffff) + (l >> 16);
	;; *      h = h >> 16;                 
	;; *    }
	;; *    fmcTmp[2*n-1]= l & 0xffff;                          
	;; * 
	;; * Remark that the below code reverses the indexes, because the mantissa bits
	;; * are saved starting with the most significant WORD.
	;; *
	;; */
	mrf_l = 0
	mrf_h = 0
	mrf_n = n-1
	mrf_o = 2*(n)-1
	mrf_k = 0
	mrf_lmax = 2*(n)-2
	WHILE mrf_k LE mrf_lmax
		mrf_p = mrf_k-mrf_n AND mrf_k-mrf_n GE 0
		mrf_i = mrf_p
		mrf_j = mrf_k - mrf_p 
		WHILE mrf_j GE mrf_p
			mrf_d = @CatStr(<MREAL_&b&_w>,%mrf_n-mrf_i) * @CatStr(<MREAL_&c&_w>,%mrf_n-mrf_j)
			mrf_l = mrf_l + LOWWORD mrf_d
			mrf_h = mrf_h + HIGHWORD mrf_d
			mrf_i = mrf_i+1
			mrf_j = mrf_j-1
		ENDM
		@CatStr(<MREAL_fmcTmp_w>,%mrf_o-mrf_k) = LOWWORD mrf_l
		mrf_l = LOWWORD mrf_h + HIGHWORD mrf_l
		mrf_h = HIGHWORD mrf_h
		mrf_k = mrf_k + 1
	ENDM
	MREAL_fmcTmp_w0 = LOWWORD mrf_l
	IFE mrf_l AND 8000h
		MR_LSHIFT_1 fmcTmp,%2*(n)
		MREAL_fmcTmp_exp = MREAL_fmcTmp_exp - 1
	ENDIF
	
	;;/**
	;; * The accumulator of fmcTmp holds the normalized, unrounded
	;; * result of b*c (2*n bits)
	;; * If a==0 then FMC behaves like MUL --> round and exit.
	;; */
	IF (MREAL_&a&_flg AND MREAL_FLG_ZERO) NE 0
		MR_ROUND_ACCUMULATOR fmcTmp,n,%2*(n),rm
		mrce_errstr_overflow  TEXTEQU <the product b*c exceeds the exponent limit (MREAL_MAX_EXP)>
		mrce_errstr_underflow TEXTEQU <the product b*c is too small (exponent underflow (MREAL_MIN_EXP))>
		MR_CHECK_EXPONENT fmcTmp,,,n,rm
		IFNB mrce_errstr
			.err mrce_errstr
		ENDIF
		MR_MOV r,fmcTmp,n
		EXITM
	ENDIF
	
	;;/**
	;; * extend the accumulators to n*3*16+1 bit
	;; */
	MR_PREPARE_ACCUMULATOR a,n,%(n)*3+1
	MR_PREPARE_ACCUMULATOR fmcTmp,%(n)*2,%(n)*3+1
	
	;;/**
	;; * Prepare addition/subtraction.
	;; * Remarks that "a" and "c*b" will be renamed to x and y.
	;; */
	mrf_x TEXTEQU <&a>
	mrf_y TEXTEQU <fmcTmp>
	mrf_a_GT_bc = -1
	mrf_sgnx = (MREAL_&a&_flg XOR (MREAL_FLG_SIGN AND (negA NE 0))) NE 0
	mrf_sgny = mrf_sgnBxC
	
	;;/* make sure that |x| > |y| */
	IF MREAL_&a&_exp LT MREAL_fmcTmp_exp
		mrf_x TEXTEQU <fmcTmp>
		mrf_y TEXTEQU <&a>
		mrf_a_GT_bc = 0
		mrf_sgnx = mrf_sgnBxC
		mrf_sgny = MREAL_&a&_flg XOR (MREAL_FLG_SIGN AND (negA NE 0))
	ELSEIF MREAL_&a&_exp EQ MREAL_fmcTmp_exp
		;;/* compare accumulators */
		mrf_cntr = 0
		mrf_tcntr TEXTEQU %mrf_cntr
		WHILE mrf_cntr LT 2*(n)
		%	IF MREAL_&a&_w&mrf_tcntr& NE MREAL_fmcTmp_w&mrf_tcntr&
				EXITM
			ENDIF
			mrf_cntr = mrf_cntr + 1
			mrf_tcntr TEXTEQU %mrf_cntr
		ENDM
		IF mrf_cntr NE 2*(n)
		%	IF MREAL_&a&_w&mrf_tcntr& LT MREAL_fmcTmp_w&mrf_tcntr&
				mrf_x TEXTEQU <fmcTmp>
				mrf_y TEXTEQU <&a>
				mrf_a_GT_bc = 0
				mrf_sgnx = mrf_sgnBxC
				mrf_sgny = MREAL_&a&_flg XOR (MREAL_FLG_SIGN AND (negA NE 0))
			ENDIF
		ELSE
			;;/* case: |a| == |c*b| */
			IF mrf_sgnx XOR mrf_sgny
				MR_SET_ZERO r,n
			ELSE
				MR_RAW_COMPOSE r,%MREAL_&a&_flg,%MREAL_&a&_exp+1,a,n
				mrce_errstr_overflow  TEXTEQU <the sum of a and b*c exceeds the exponent limit (MREAL_MAX_EXP)>
				mrce_errstr_underflow TEXTEQU <the sum of a and b*c is too small (exponent underflow (MREAL_MIN_EXP))>
				MR_CHECK_EXPONENT r,,,n,rm
				IFNB mrce_errstr
					.err mrce_errstr
				ENDIF
			ENDIF
			EXITM
		ENDIF
	ENDIF

%	mrf_ex = MREAL_&mrf_x&_exp
%	mrf_ey = MREAL_&mrf_y&_exp
	
	;;/**
	;; * copy: y --> mraTmp
	;; *       x --> r
	;; */
	MR_MOV mraTmp,%mrf_y,%(n)*3+1
	MR_MOV r,%mrf_x,%(n)*3+1
	mrf_y TEXTEQU <mraTmp>

	IF (mrf_ex-mrf_ey) GE ((n)*2*16+2) AND mrf_a_GT_bc NE 0
		;;/**
		;; * y=b*c is too small to affect the bits of x=a.
		;; * However, for RM "up" or "down" an arbitrary smaller value can change
		;; * the result. To respect that the mantissa of y gets the value sgn(y)*2^(-(n*2*16+3)).
		;; */
		mrf_cntr = 0
		mrf_tcntr TEXTEQU %mrf_cntr
		WHILE mrf_cntr LT 2*(n)
		%	MREAL_&mrf_y&_w&mrf_tcntr& = 0
			mrf_cntr = mrf_cntr + 1
			mrf_tcntr TEXTEQU %mrf_cntr
		ENDM
	%	MREAL_&mrf_y&_w&mrf_tcntr& = 2000h
	ELSEIF (mrf_ex-mrf_ey) GE ((n)*16+2) AND mrf_a_GT_bc EQ 0
		;;/**
		;; * y=a is too small to affect the bits of x=b*c.
		;; * However, for RM "up" or "down" or "to nearest, ties to even" an arbitrary smaller value can change
		;; * the result. To respect that the mantissa of y gets the value sgn(y)*2^(-(n*2*16+3)).
		;; */
		mrf_cntr = 0
		mrf_tcntr TEXTEQU %mrf_cntr
		WHILE mrf_cntr LT n
		%	MREAL_&mrf_y&_w&mrf_tcntr& = 0
			mrf_cntr = mrf_cntr + 1
			mrf_tcntr TEXTEQU %mrf_cntr
		ENDM
	%	MREAL_&mrf_y&_w&mrf_tcntr& = 2000h
	ELSE
		;;/* bring y in right position */
		MR_RSHIFT %mrf_y,%(mrf_ex-mrf_ey),%n*3+1
	ENDIF
	
	;;/**
	;; * Sum up x and y.
	;; */
	mrf_sub = mrf_sgnx XOR mrf_sgny
	mrf_msk = LOWWORD mrf_sub
	mrf_carry = mrf_sub AND 1
	mrf_cntr = (n)*3
	WHILE mrf_cntr GE 0
		mrf_tcntr TEXTEQU %mrf_cntr
	%	mrf_tmp = MREAL_&r&_w&mrf_tcntr& + (MREAL_&mrf_y&_w&mrf_tcntr& XOR mrf_msk) + mrf_carry
	%	MREAL_&r&_w&mrf_tcntr& = LOWWORD mrf_tmp
		mrf_carry = HIGHWORD mrf_tmp
		mrf_cntr = mrf_cntr - 1
	ENDM
	IF mrf_sub
		mrf_carry = 0
	ENDIF
	MR_NORMALIZE_ACCUM r,%mrf_carry,%(n)*3+1
	
	MR_ROUND_ACCUMULATOR r,n,%(n)*3+1,rm
	
	;;/**
	;; * check for exponent over- or underflow.
	;; */
	mrce_errstr_overflow  TEXTEQU <the sum of a and b*c exceeds the exponent limit (MREAL_MAX_EXP)>
	mrce_errstr_underflow TEXTEQU <the sum of a and b*c is too small (exponent underflow (MREAL_MIN_EXP))>
	MR_CHECK_EXPONENT r,,,n,rm
	IFNB mrce_errstr
		.err mrce_errstr
	ENDIF
	;;  job done :-D
endm

;;/**
;; * Divide two MREAL-values and round the result  
;; * according to the current rounding mode.
;; * Pseudo code:
;; *  if x or y is NaN or infinite
;; *    r = NaN;
;; *  else
;; *    tmp = x / y;
;; *    r = round(tmp);
;; *
;; * The parameter p can be used to request results
;; * with a precision of p*16 bits (1 <= p <= n).
;; */
MR_DIV macro r:req,x:req,y:req,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>,p
	
	MREAL_INEXACT = 0
	
	;;/**
	;; * p must be in the range 1 to n
	;; */
	IFNB <&p>
		IF p GT n
			.err <invalid parameter(6): _p GT _n: p GT n>
			EXITM
		ELSEIF p LE 0
			.err <invalid parameter(6): <&p> : expected positive nonzero value>
			EXITM
		ENDIF
		mrd_p = p
	ELSE
		mrd_p = n
	ENDIF
	
	;;/**
	;; * process special input values
	;; */
	IF MREAL_&x&_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF MREAL_ERROR_FOR_NAN_INPUT
			.err <x is not a numeric value>
		ENDIF
		MR_RAW_SET_N r,NaN,,n
		EXITM
	ELSEIF MREAL_&y&_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF MREAL_ERROR_FOR_NAN_INPUT
			.err <y is not a numeric value>
		ENDIF
		MR_RAW_SET_N r,NaN,,n
		EXITM
	ELSEIF ((MREAL_&x&_flg AND MREAL_FLG_ZERO) NE 0) AND ((MREAL_&y&_flg AND MREAL_FLG_ZERO) NE 0)
		IF MREAL_ERROR_FOR_NAN_OUTPUT
			.err <the division 0/0 is not defined (x/y)>
		ENDIF
		MR_RAW_SET_N r,NaN,,n
		EXITM
	ELSEIF (MREAL_&x&_flg AND MREAL_FLG_ZERO) NE 0
		MR_SET_ZERO r,n
		EXITM
	ELSEIF (MREAL_&y&_flg AND MREAL_FLG_ZERO) NE 0
		IF (MREAL_&x&_flg AND MREAL_FLG_SIGN) NE 0
			MR_RAW_SET_N r,-Infinity,,n
		ELSE
			MR_RAW_SET_N r,+Infinity,,n
		ENDIF
		IF MREAL_ERROR_FOR_NAN_OUTPUT OR MREAL_ERROR_FOR_DIV_ZERO
			.err <division by zero: x/y>
		ENDIF
		EXITM
	ENDIF

	mrd_sgn = ((MREAL_&x&_flg AND MREAL_FLG_SIGN) NE 0) XOR ((MREAL_&y&_flg AND MREAL_FLG_SIGN) NE 0)
	
	;;/**
	;; * The quotient bits are calculate using a shift-subtract algorithm (see [4])
	;; * Pseudo code:
	;; * ("^" denotes exponentiation, "|x|" means absolute value of x)
	;; *
	;; *     Input: mx*2^ex , my*2^ey
	;; *            n = number of needed quotient bits
	;; *     Out:   mq*2^eq , r
	;; *
	;; *     assert: 0.5 <= |mx|,|my| < 1;
	;; *     r = |mx|;
	;; *     d = |my|;
	;; *     eq = ex-ey;
	;; *     mq = 0;
	;; *     if(r >= d) {
	;; *       d = d * 2;
	;; *       eq = eq + 1;
	;; *     } 
	;; *     for (i = -1 to -n) {
	;; *       r = 2*r;
	;; *       tmp = r - d;
	;; *       if(tmp >= 0) {     // if( 2*r >= d)
	;; *         mq = mq + 2^i;   //   set bit i in mq
	;; *         r = tmp;
	;; *       }
	;; *     }
	;; *     assert: 1 > q >= 0.5;   // mq is normalized to 0.5
	;; *     return (sgn(mx)*sgn(my)*mq*2^eq, r);
	;; *
	;; *  To allow correct rounding, n*16+1 bits are calculated.
	;; *  To respect RM "up", "down" and "towards zero", the bit 2^(-(n*16+3) + eq)
	;; *  is set to one, if the remainder is not zero.
	;; * 
	;; */
	
	;;/**
	;; *  - copy: x -> partial remainder "?rX"
	;; *          y -> divisor "?dX"
	;; *  - calculate carry of x-y.
	;; *  - eq = ex - ey
	;; **/
	mrd_eq = MREAL_&x&_exp - MREAL_&y&_exp
	mrd_cntr = n-1
	mrd_xGEy = 1
	WHILE mrd_cntr GE 0
		mrd_tcntr TEXTEQU %mrd_cntr
	%	?d&mrd_tcntr& = MREAL_&y&_w&mrd_tcntr&
	%	?r&mrd_tcntr& = MREAL_&x&_w&mrd_tcntr&
	%	mrd_xGEy = HIGHWORD ( mrd_xGEy + MREAL_&x&_w&mrd_tcntr& + (MREAL_&y&_w&mrd_tcntr& XOR 0ffffh))
		mrd_cntr = mrd_cntr - 1
	ENDM
	
	;;/**
	;; * Zero-extend by one WORD:
	;; *  - divisor bits ?dX
	;; *  - partial remainder ?rX
	;; * This simplifies the left shift.
	;; */
	@CatStr(<?d>,%n) = 0
	@CatStr(<?r>,%n) = 0
	
	;;/** 
	;; * if |mx| >= |my| then  multiply the divisor
	;; * by 2 and increase the quotient exponent
	;; */
	IF mrd_xGEy
		mrd_eq = mrd_eq + 1
		?d0 = ?d0 SHL 1 OR ?d1 SHR 15
		mrd_cntr = 1
		WHILE mrd_cntr LT n
			mrd_tcntr TEXTEQU %mrd_cntr
		%	?d&mrd_tcntr& = LOWWORD (?d&mrd_tcntr& SHL 1 OR @CatStr(<?d>,%mrd_cntr+1) SHR 15)
			mrd_cntr = mrd_cntr + 1
		ENDM
	ENDIF
	;;/**
	;; * - negate divisor
	;; * - prepare quotient (q=0)
	;; */
	mrd_cntr = n-1
	mrd_t = 10000h
	WHILE mrd_cntr GE 1
		mrd_tcntr TEXTEQU %mrd_cntr
	%	mrd_t = (?d&mrd_tcntr& XOR 0ffffh) + HIGHWORD mrd_t
	%	?d&mrd_tcntr& = LOWWORD mrd_t
	%   ?q&mrd_tcntr& = 0
		mrd_cntr = mrd_cntr - 1
	ENDM
	?d0 = (?d0 XOR 0ffffffffh) + HIGHWORD mrd_t
	?q0 = 0
	
	;;/**
	;; * Calculate p*16 quotient bits.
	;; */
	mrd_iq = 0
	REPEAT mrd_p*16
		;;/**
		;; * r = r*2
		;; * t = r-d
		;; */
		mrd_cntr = n-1
		mrd_t = 0
		mrd_k = 0
		REPEAT n-1
			mrd_tcntr TEXTEQU %mrd_cntr
		%	mrd_t = ?r&mrd_tcntr& SHL 1 OR HIGHWORD mrd_t
		%   mrd_k = LOWWORD mrd_t + ?d&mrd_tcntr& + HIGHWORD mrd_k
		%   ?t&mrd_tcntr& = mrd_k
		%	?r&mrd_tcntr& = LOWWORD mrd_t
			mrd_cntr = mrd_cntr - 1
		ENDM
		?r0 = ?r0 SHL 1 OR HIGHWORD mrd_t
		?t0 = ?r0 + ?d0 + HIGHWORD mrd_k
		
		;;/* if r >= d */
		IFE ?t0 AND 80000000h
			;;/* q = q + 2^i */
			@CatStr(<?q>,%mrd_iq SHR 4) = @CatStr(<?q>,%mrd_iq SHR 4) OR 8000h SHR (mrd_iq AND 0fh)
			;;/* r = t */
			mrd_cntr = n-1
			REPEAT n-1
				mrd_tcntr TEXTEQU %mrd_cntr
			%	?r&mrd_tcntr& = LOWWORD ?t&mrd_tcntr&
				mrd_cntr = mrd_cntr - 1
			ENDM
			?r0=?t0
		ENDIF
		mrd_iq = mrd_iq + 1
	ENDM
	
	;;/**
	;; * Calculate one more quotient digit and
	;; * check whether the (new) remainder is zero.
	;; */
	mrd_cntr = n-1
	mrd_t = 0
	mrd_k = 0
	mrd_zp1 = -1
	mrd_zp2 = -1
	REPEAT n-1
		mrd_tcntr TEXTEQU %mrd_cntr
	%	mrd_t = ?r&mrd_tcntr& SHL 1 OR HIGHWORD mrd_t
	%   mrd_k = LOWWORD mrd_t + ?d&mrd_tcntr& + HIGHWORD mrd_k
		mrd_zp1 = mrd_zp1 AND LOWWORD mrd_t EQ 0
		mrd_zp2 = mrd_zp2 AND LOWWORD mrd_k EQ 0
		mrd_cntr = mrd_cntr - 1
	ENDM
	mrd_t = ?r0 SHL 1 OR HIGHWORD mrd_t
	mrd_k = mrd_t + ?d0 + HIGHWORD mrd_k
	;;/**
	;; *  mrd_qr is the additional quotient bit 2^(-(p*16)+1+eq).
	;; *  mrd_rnz indicates whether the remainder is not zero.
	;; */
	mrd_qr = (mrd_k AND 80000000h) EQ 0
	IF mrd_qr
		mrd_rnz = (mrd_zp2 AND mrd_k EQ 0) EQ 0
	ELSE
		mrd_rnz = (mrd_zp1 AND mrd_t EQ 0) EQ 0
	ENDIF
	
	;;/* copy q[0...p-1] --> result */
	mrd_cntr = 0
	REPEAT mrd_p
		mrd_tcntr TEXTEQU %mrd_cntr
	%	MREAL_&r&_w&mrd_tcntr& = ?q&mrd_tcntr&
		mrd_cntr = mrd_cntr + 1
	ENDM 
	MREAL_&r&_exp = mrd_eq
	MREAL_&r&_flg = mrd_sgn AND MREAL_FLG_SIGN
	
	;;/**
	;; * set additional bits for rounding:
	;; *  2^(-(p*16)+ 1 +eq)
	;; *  2^(-(p*16)+ 3 +eq)
	;; */
	@CatStr(<MREAL_&r&_w>,%mrd_p) = (8000h AND mrd_qr) OR (02000h AND mrd_rnz)
	
	MR_ROUND_ACCUMULATOR r,%mrd_p,%mrd_p+1,rm
	
	;/* zero extend p to n bits */
	REPEAT n-mrd_p
		@CatStr(<MREAL_&r&_w>,%mrd_cntr) = 0
		mrd_cntr = mrd_cntr + 1
	ENDM

	;;/**
	;; * check for exponent over- or underflow.
	;; */
	mrce_errstr_overflow  TEXTEQU <the quotient x/y exceeds the exponent limit (MREAL_MAX_EXP)>
	mrce_errstr_underflow TEXTEQU <the quotient x/y is too small (exponent underflow (MREAL_MIN_EXP))>
	MR_CHECK_EXPONENT r,,,n,rm
	IFNB mrce_errstr
		.err mrce_errstr
	ENDIF
	;;  job done :-D
endm


;;/**
;; * Calculate the square root of MREAL-value x and round the result  
;; * according to the current rounding mode.
;; * The parameter p can be used to request results
;; * with a precision of p*16 bits (1 <= p <= n).
;; */
MR_SQRT macro r:req,x:req,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>,p

	MREAL_INEXACT = 0
	
	;;/**
	;; * p must be in the range 1 to n
	;; */
	IFNB <&p>
		IF p GT n
			.err <invalid parameter(6): _p GT _n: p GT n>
			EXITM
		ELSEIF p LE 0
			.err <invalid parameter(6): <&p> : expected positive nonzero value>
			EXITM
		ENDIF
		mrd_p = p
	ELSE
		mrd_p = n
	ENDIF
	
	;;/**
	;; * process special input values
	;; */
	IF MREAL_&x&_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF MREAL_ERROR_FOR_NAN_INPUT
			.err <x is not a numeric value>
		ENDIF
		MR_RAW_SET_N r,NaN,,n
		EXITM
	ELSEIF MREAL_&x&_flg AND MREAL_FLG_SIGN
		IF MREAL_ERROR_FOR_NAN_OUTPUT
			.err <square root of negative value is not defined>
		ENDIF
		MR_RAW_SET_N r,NaN,,n
		EXITM
	ELSEIF (MREAL_&x&_flg AND MREAL_FLG_ZERO) NE 0
		MR_SET_ZERO r,n
		EXITM
	ENDIF
	
	;;/**
	;; * The quotient bits are calculate using a shift-subtract algorithm (see [4])
	;; * Pseudo code:
	;; * ("^" denotes exponentiation, "|x|" means absolute value of x)
	;; *
	;; *     Input: mx*2^ex = radicand
	;; *            n = number of needed quotient bits
	;; *     Out:   mq*2^eq
	;; *
	;; *     assert: 0.5 <= |mx| < 1;
	;; *     assert: ex is integer;
	;; *     mr = |mx|;           // mr is the partial remainder with the radicand as initial value
	;; *     mq = 0;
	;; *
	;; *     if( ex & 1 ) {       // if exponent is odd
	;; *       eq = (ex + 1) / 2;
	;; *       mr = mr / 2;       // shift radicand bits right
	;; *       oddExp = 1;
	;; *     } else {
	;; *       eq = ex / 2;
	;; *       oddExp = 0;
	;; *     }
	;; *     // At this point mr satisfies: oddExp == 0 and 0.5 <= mr < 1 or oddExp != 0 and 0.25 <= mr < 0.5
	;; *
	;; *     for (i = -1 to -n) {        // for all mantissa bits 
	;; *       rm = 2*rm;
	;; *       tmp = rm - (2*mq + 2^i);
	;; *       if(tmp >= 0) {            // if( rm >= 2*mq + 2^i )
	;; *         mq = mq + 2^i;          //   set bit i in mq
	;; *         rm = tmp;               //   store new remainder
	;; *       }
	;; *     }
	;; *     if(oddExp) {
	;; *       assert: 0.5 <= mq < sqrt(0.5);   // sqrt(0.5) = 0.7071...
	;; *     } else {
	;; *       assert: sqrt(0.5) <= mq < 1;
	;; *     }
	;; *     return (sgn(mx)*mq*2^eq);
	;; *  
	;; *  In the implementation below, n+1 bits are calculate to allow correct rounding.
	;; *  To respect RM "up", "down" and "towards zero" one more nonzero bit is appended
	;; *  to the mantissa, if the remainder rm is not zero.
	;; */
	
	;;/**
	;; *  - partial remainder ?rX = radicand * 2^1.
	;; *    The shift is required to make sure that the whole calculation takes place in
	;; *    n mantissa WORDs, whereas the upper 16 bit of the most significant mantissa-equates are also used.
	;; *  - square root ?qX = 0
	;; *  - eq = ex
	;; **/
	mrd_eq = MREAL_&x&_exp
	mrd_cntr = n-1
	mrd_tmp = 0
	WHILE mrd_cntr GE 0
		mrd_tcntr TEXTEQU %mrd_cntr
	%	?q&mrd_tcntr& = 0
	%	?b&mrd_tcntr& = 0
	%	mrd_tmp = MREAL_&x&_w&mrd_tcntr& SHL 16 OR HIGHWORD mrd_tmp 
	%	?r&mrd_tcntr& = HIGHWORD (mrd_tmp SHL 1)
		mrd_cntr = mrd_cntr - 1
	ENDM
	?r0 = HIGHWORD mrd_tmp SHL 1 OR LOWWORD mrd_tmp SHR 15
	
	;;/* calcualte final exponent eq */
	IF mrd_eq AND 1
		mrd_eq = (mrd_eq + 1) / 2
		mrd_oddExp = 1
	ELSE
		mrd_eq = mrd_eq / 2
		mrd_oddExp = 0
	ENDIF
	
	mrd_lq TEXTEQU <?b0>
	
	;;/**
	;; * Calculate p*16+1 bits.
	;; */
	mrd_iq = 0
	REPEAT mrd_p*16+1
		;;/**
		;; * b = 0
		;; * b = 2^(-i)
		;; * ?bX holds only one bit.
		;; */
	%	&mrd_lq = 0
		mrd_tmp = mrd_iq-1-mrd_oddExp
		IF mrd_tmp GE 0
			mrd_lq TEXTEQU <?b>,%mrd_tmp SHR 4
		%	&mrd_lq = 8000h SHR (mrd_tmp AND 0fh)
		ELSE
			mrd_lq TEXTEQU <?b0>
		%	&mrd_lq = 10000h SHL mrd_oddExp
		ENDIF

		;;/**
		;; * r = r*2
		;; * t = r-(2*q OR b)
		;; */
		mrd_cntr = n-1
		mrd_t = 0
		mrd_k = 10000h
		REPEAT n-1
			mrd_tcntr TEXTEQU %mrd_cntr
		%	mrd_t = ?r&mrd_tcntr& SHL 1 OR HIGHWORD mrd_t
		%   mrd_k = LOWWORD mrd_t + (?q&mrd_tcntr& OR ?b&mrd_tcntr& XOR 0ffffh) + HIGHWORD mrd_k
		%   ?t&mrd_tcntr& = mrd_k
		%	?r&mrd_tcntr& = LOWWORD mrd_t
			mrd_cntr = mrd_cntr - 1
		ENDM
		?r0 = ?r0 SHL 1 OR HIGHWORD mrd_t
		?t0 = ?r0 + (?q0 OR ?b0 XOR 0ffffffffh) + HIGHWORD mrd_k
		
		;;/* if r >= (2*q OR b) */
		IFE ?t0 AND 80000000h
			;;/* q = q + 2^(1+i) */
			mrd_tmp = mrd_iq-2-mrd_oddExp
			IF mrd_tmp GE 0
				@CatStr(<?q>,%mrd_tmp SHR 4) = @CatStr(<?q>,%mrd_tmp SHR 4) OR 8000h SHR (mrd_tmp AND 0fh)
			ELSE
				?q0 = ?q0 OR 8000h SHL -mrd_tmp
			ENDIF
			;;/* r = t */
			mrd_cntr = n-1
			REPEAT n-1
				mrd_tcntr TEXTEQU %mrd_cntr
			%	?r&mrd_tcntr& = LOWWORD ?t&mrd_tcntr&
				mrd_cntr = mrd_cntr - 1
			ENDM
			?r0=?t0
		ENDIF
		mrd_iq = mrd_iq + 1
	ENDM
	
	;;/* test remainder for zero */
	mrd_rnz = 0
	mrd_cntr = 0
	REPEAT n
		IF @CatStr(<?r>,%mrd_cntr)
			mrd_rnz = 8000h
			EXITM
		ENDIF
		mrd_cntr = mrd_cntr + 1
	ENDM
	
	;;/* append stick bit */
	@CatStr(<?q>,%mrd_p) = mrd_rnz
	
	;;/**
	;; * Shift the sqare root bits in correct position.
	;; */
	mrd_cntr = 1
	mrd_tmp = ?q0
	MREAL_&r&_w0 = ?q0 SHR (2+mrd_oddExp)
	REPEAT mrd_p
		mrrs_tcntr TEXTEQU %mrd_cntr
	%	mrd_tmp = ?q&mrrs_tcntr& OR LOWWORD mrd_tmp SHL 16
	%	MREAL_&r&_w&mrrs_tcntr& = LOWWORD (mrd_tmp SHR (2+mrd_oddExp))
		mrd_cntr = mrd_cntr + 1
	ENDM

	MREAL_&r&_exp = mrd_eq
	MREAL_&r&_flg = 0
	
	MR_ROUND_ACCUMULATOR r,%mrd_p,%mrd_p+1,rm
	
	;/* zero extend p to n bits */
	mrd_cntr = mrd_p
	REPEAT n-mrd_p
		@CatStr(<MREAL_&r&_w>,%mrd_cntr) = 0
		mrd_cntr = mrd_cntr + 1
	ENDM

	;;/**
	;; * check for exponent over- or underflow.
	;; */
	mrce_errstr_overflow  TEXTEQU <the quotient x/y exceeds the exponent limit (MREAL_MAX_EXP)>
	mrce_errstr_underflow TEXTEQU <the quotient x/y is too small (exponent underflow (MREAL_MIN_EXP))>
	MR_CHECK_EXPONENT r,,,n,rm
	IFNB mrce_errstr
		.err mrce_errstr
	ENDIF
	;;  job done :-D
endm


MR_NORMALIZE_ACCUM macro r,carry,n:=<MREAL_XDIM*2+1>
	IF carry NE 0
		MR_RSHIFT_1 r,%(n)
		MREAL_&r&_exp = MREAL_&r&_exp + 1
	ELSE
		mrna_cntr = 0
		mrna_tcntr TEXTEQU %mrna_cntr
		WHILE mrna_cntr LT n
		%	IF MREAL_&r&_w&mrna_tcntr& NE 0
				EXITM
			ENDIF
			mrna_cntr = mrna_cntr + 1
			mrna_tcntr TEXTEQU %mrna_cntr
		ENDM
		.radix 2
		mrna_txt TEXTEQU %@CatStr(<MREAL_&r&_w>,%mrna_tcntr)
		.radix 10
		mrna_lshift = 16-@SizeStr(%mrna_txt) + mrna_cntr*16
		MR_LSHIFT r,%mrna_lshift,%(n)
		MREAL_&r&_exp = MREAL_&r&_exp - mrna_lshift
	ENDIF
	MREAL_&r&_w0 = MREAL_&r&_w0 OR 8000h
endm

;; r must be normalized
MR_ROUND_ACCUMULATOR macro r,n:=<MREAL_XDIM>,na:=<MREAL_XDIM*2+1>,rm:=<MREAL_ROUND_MODE>
	IF na EQ n
		EXITM
	ELSEIF na LT n
		.err <fatal error: _na LE _n : na LE n>
	ENDIF
	;;/* test for exact result before rounding */
	IF MREAL_TEST_INEXACT
		;;/* test bits below the LSB of the mantissa */
		mrra_cntr = n
		WHILE mrra_cntr LT na
			IF @CatStr(<MREAL_&r&_w>,%mrra_cntr)
				EXITM
			ENDIF
			mrra_cntr = mrra_cntr + 1
		ENDM
		IF mrra_cntr EQ na
			;;/* case: exact result -> no rounding needed */
			EXITM
		ENDIF
		MREAL_INEXACT = -1
	ENDIF
	IF rm NE MRRM_ROUND_TOWARD_ZERO
		;;/**
		;; * Handle rounding modes:
		;; *  - Round to nearest, ties to even:
		;; *    If the value is not a midpoint between two FP values, then it
		;; *    is rounded up if the mantissa bit 2^-(n*16+1) is not zero.
		;; *    If the value is a midpoint, then the truncated result is round up if the LSB
		;; *    is 1. Rounding up is done by adding 2^-(n*16)==LSB to the mantissa.
		;; *
		;; *  - Round to nearest, ties away from zero:
		;; *    Add 2^-(n*16) to the mantissa, if the bit 2^-(n*16+1)
		;; *    is not zero. Remarks that 2^-(n*16) is the LSB of the mantissa.
		;; *
		;; *  - Round down:
		;; *    If the value is positive, it will be truncated. If the value
		;; *    is negative and the accumulator bits "below" the LSB are not zero,
		;; *    2^-(n*16) is added to the mantissa of the result.
		;; *
		;; *  - Round up:
		;; *    If the value is negative, it will be truncated. If the value
		;; *    is positive and the accumulator bits "below" the LSB are not zero,
		;; *    2^-(n*16) is added to the mantissa of the result.
		;; *
		;; *  If an addition occurs and the mantissa overflows (carry), then
		;; *  the result must be normalized again.
		;; *  
		;; */
		mrra_sgn = (MREAL_&r&_flg AND MREAL_FLG_SIGN) NE 0
		mrra_carry = 0
		IF rm EQ MRRM_ROUND_TO_NEAREST_TIES_TO_EVEN
			;;/* check for midpoint */
			mrra_cntr = n
			mrra_tcntr TEXTEQU %mrra_cntr
		%	IF MREAL_&r&_w&mrra_tcntr& EQ 8000h
				mrra_cntr = mrra_cntr + 1
				WHILE mrra_cntr LT na
					mrra_tcntr TEXTEQU %mrra_cntr
				%	IF MREAL_&r&_w&mrra_tcntr&
						EXITM
					ENDIF
					mrra_cntr = mrra_cntr + 1
				ENDM
			ENDIF
			;;/**
			;; * If value is a midpoint then use the tie-breaking rule
			;; * "round half to even", otherwise round up if bit 2^-(n*16+1) is not zero.
			;; */
			IF mrra_cntr EQ na
				;;/**
				;; * The value (r) is a midpoint.
				;; * If the LSB of the mantissa is zero, the nearest even number
				;; * is the truncated value. Otherwise the value must be round up.
				;; */
				mrra_tcntr TEXTEQU %n-1
			%	IF MREAL_&r&_w&mrra_tcntr& AND 1
					mrra_carry = 1
				ENDIF
		%	ELSEIF MREAL_&r&_w&mrra_tcntr& AND 8000h
				;;/* see MRRM_ROUND_TO_NEAREST_TIES_AWAY_FROM_ZERO */
				mrra_carry = 1
			ENDIF
		ELSEIF rm EQ MRRM_ROUND_TO_NEAREST_TIES_AWAY_FROM_ZERO
			;;/**
			;; * Add 2^-(n*16) if the bit
			;; * 2^-(n*16+1) is not zero.
			;; */
			mrra_tcntr TEXTEQU %n
		%	IF MREAL_&r&_w&mrra_tcntr& AND 8000h
				mrra_carry = 1
			ENDIF
		ELSEIF ((rm EQ MRRM_ROUND_UP) AND (NOT mrra_sgn)) OR ((rm EQ MRRM_ROUND_DOWN) AND mrra_sgn)
			;;/**
			;; *  Test accumulator bits in the range
			;; *    2^-(n*16+1) to 2^-(na*16)
			;; *  for zero.
			;; */
			mrra_cntr = na-1
			mrra_tcntr TEXTEQU %mrra_cntr
			WHILE mrra_cntr GE n
			%	IF MREAL_&r&_w&mrra_tcntr&
					EXITM
				ENDIF
				mrra_cntr = mrra_cntr - 1
				mrra_tcntr TEXTEQU %mrra_cntr
			ENDM
			;;/* if not zero: add 2^-(n*16) */
			IF mrra_cntr GT (n-1)
				mrra_carry = 1
			ENDIF
		ELSEIF (rm EQ MRRM_ROUND_UP) OR (rm EQ MRRM_ROUND_DOWN)
			;;/* truncate */
		ELSE
			.err @CatStr(<invalid rounding mode: >,%rm)
			EXITM
		ENDIF
		IF mrra_carry
			;;/**
			;; * Do addition: 
			;; *   mantissa(r) = mantissa(r) + 2^-(n*16)
			;; */
			mrra_cntr = n-1
			mrra_tcntr TEXTEQU %mrra_cntr
			WHILE mrra_cntr GE 0
			%	mrra_tmp = MREAL_&r&_w&mrra_tcntr& + mrra_carry
			%	MREAL_&r&_w&mrra_tcntr& = LOWWORD mrra_tmp
				mrra_carry = HIGHWORD mrra_tmp
				IFE mrra_carry
					EXITM
				ENDIF
				mrra_cntr = mrra_cntr - 1
				mrra_tcntr TEXTEQU %mrra_cntr
			ENDM
		ENDIF
		IF mrra_carry
			;;/* normalize result */
			MR_RSHIFT_1 r,%n
			MREAL_&r&_w0 = MREAL_&r&_w0 OR 8000h
			MREAL_&r&_exp = MREAL_&r&_exp + 1
		ENDIF
	ENDIF
endm

mrce_errstr_overflow TEXTEQU <>
mrce_errstr_underflow TEXTEQU <>
;;/* r must be numeric value (NOT: zero, infinity or NaN) */
MR_CHECK_EXPONENT macro r,emin:=<MREAL_MIN_EXP>,emax:=<MREAL_MAX_EXP>,n:=<MREAL_XDIM>,rm:=<MREAL_ROUND_MODE>
	mrce_errstr TEXTEQU <>
	mrce_rm = rm
	mrce_sign = (MREAL_&r&_flg AND MREAL_FLG_SIGN) NE 0
	mrce_exp = MREAL_&r&_exp
	IF mrce_exp GT emax
		;;/**
		;; * Exponent overflow: |r| lies between
		;; * infinity and 2^emax*(1-2^MREAL_XDIM). Remarks that
		;; * 2^emax*(1-2^MREAL_XDIM) is the greatest representable
		;; * number for the current precision and exponent settings.
		;; * For rounding mode "to nearest, ties to even" and
		;; * "to nearest, ties away from zero" the result is +-Infinity.
		;; * For the rounding modes "up" and "down" the result
		;; * might be +-2^emax*(1-2^MREAL_XDIM), depending on the sign.
		;; * For RM "toward zero" it is always +-2^emax*(1-2^MREAL_XDIM).
		;; */
		MREAL_INEXACT = -1
		IF mrce_sign
			IF mrce_rm EQ MRRM_NEAR_EVEN OR mrce_rm EQ MRRM_NEAR_AWAY OR mrce_rm EQ MRRM_ROUND_DOWN
				MR_RAW_SET_N r,-Infinity,,n
			ELSE
				MR_RAW_MAXVALUE r,-1,n,emax
			ENDIF
		ELSE
			IF mrce_rm EQ MRRM_NEAR_EVEN OR mrce_rm EQ MRRM_NEAR_AWAY OR mrce_rm EQ MRRM_ROUND_UP
				MR_RAW_SET_N r,+Infinity,,n
			ELSE
				MR_RAW_MAXVALUE r,0,n,emax
			ENDIF
		ENDIF
		IF (MREAL_ERROR_FOR_NAN_OUTPUT NE 0 AND (MREAL_&r&_flg AND MREAL_FLG_NON_NUMERIC_TEST) NE 0) OR MREAL_OVERFLOW_IS_ERROR NE 0
			mrce_errstr TEXTEQU mrce_errstr_overflow
		ENDIF
	ELSEIF mrce_exp LT emin
		IF MREAL_UNDERFLOW_IS_ERROR NE 0
			mrce_errstr TEXTEQU mrce_errstr_underflow
		ENDIF
		;;/**
		;; * Exponent underflow: r lies between
		;; * 2^MIN_EXP and -2^MIN_EXP thus the rounded
		;; * result is either 0 or sgn(r)*2^MIN_EXP;
		;; * The following pseudo code shows how to
		;; * get the correctly rounded result:
		;; *
		;; *  minVal = sgn(r)*2^MIN_EXP;
		;; *  if(RM == "down")
		;; *     return (r<0)? minVal : 0;
		;; *  if(RM == "up")
		;; *     return (r<0)? 0 : minVal;
		;; *  if(RM == "towards zero")
		;; *     return 0;
		;; *  if(RM == "to nearest, ties away from zero")
		;; *     return (|r|<|minVal/2|)? 0 : minVal;
		;; *  if(RM == "to nearest, ties to even")
		;; *     return (|r|<=|minVal/2|)? 0 : minVal;
		;; * 
		;; */
		MREAL_INEXACT = -1
		IF (mrce_rm EQ MRRM_ROUND_DOWN AND mrce_sign NE 0)\
		OR (mrce_rm EQ MRRM_ROUND_UP   AND mrce_sign EQ 0)\
		OR (mrce_rm EQ MRRM_NEAR_AWAY  AND mrce_exp EQ emin-1)
			MR_RAW_MINVALUE r,%mrce_sign,n,emin
		ELSEIF mrce_rm EQ MRRM_NEAR_EVEN AND mrce_exp EQ emin-1
			;;/* test if r == 2^(emin-1)*/
			mrce_cntr = 0
			IF MREAL_&r&_w0 EQ 8000h
				mrce_cntr = 1
				WHILE mrce_cntr LT n
					IF @CatStr(<MREAL_&r&_w>,%mrce_cntr)
						EXITM
					ENDIF
					mrce_cntr = mrce_cntr + 1
				ENDM
			ENDIF
			;;/**
			;; * if(r == 2^(emin-1))
			;; *    return 0;
			;; * else
			;; *    return 2^emin;
			;; */
			IF mrce_cntr EQ n
				MR_RAW_SET_N r,zero,,n
			ELSE
				MR_RAW_MINVALUE r,%mrce_sign,n,emin
			ENDIF
		ELSE
			MR_RAW_SET_N r,zero,,n
		ENDIF
	ENDIF
endm

;;/**
;; * convert MREAL x of precision nx to MREAL r of precision nr. This routine does not
;; * throws errors for NaN or infinite input/output.
;; *
;; * Pseudo code:
;; *  if( nr == nx || x == NaN )
;; *    r = x;
;; *  if( nr < nx  )
;; *    r = round(x);
;; *  if( nr > nx  )
;; *    r = zero_extended(x);
;; *
;; * Remarks: the "quite" parameter is for internal usage -> do not use.
;; */
MR_CONVERT macro r:req,x:req,nx:=<MREAL_XDIM>,nr:=<MREAL_XDIM>,rm:=<MREAL_ROUND_MODE>,quiet:=<-1>
	
	MREAL_INEXACT = 0
	
	;;/* check nx and nr */
	IF nx LE 0
		.err <invalid parameter(3): <&nx> : expected positive nonzero value>
		EXITM
	ELSEIF nr LE 0
		.err <invalid parameter(4): <&nr> : expected positive nonzero value>
		EXITM
	ENDIF
	;;/* process special input values */
	IF MREAL_&x&_flg AND MREAL_FLG_NON_NUMERIC_TEST
		MR_SET_ZERO r,nr
		MREAL_&r&_flg = MREAL_&x&_flg
		EXITM
	ELSEIF MREAL_&x&_flg AND MREAL_FLG_ZERO
		MR_SET_ZERO r,nr
		EXITM
	ENDIF
	
	IF nx EQ nr
		MR_MOV r,x,nx
	ELSEIF nx LT nr
		;;/* zero extend */
		MR_MOV r,x,nx
		mrc_cntr = nx
		WHILE mrc_cntr LT nr
			@CatStr(<MREAL_&r&_w>,%mrc_cntr) = 0
			mrc_cntr = mrc_cntr + 1
		ENDM
	ELSE
		;;/* round to nr*16 bits */
		MR_ROUND r,x,%nr*16,<bits>,rm,%nx,,,quiet
	ENDIF
endm

;;/**
;; * Round MREAL x according to specified rounding mode and store the result in r.
;; * Parameters
;; *   r:             Result.
;; *   x:             Value to round.
;; *
;; *   mode:          [optional, default = <normal>]
;; *                   <normal> -> pwr2 specifies the rounding digit. For example, if pwr2 = 0 the rounding digit is 2^0=1 (--> round to integer).
;; *                   <bits>   -> pwr2 specifies the number if significant mantissa bits.
;; *
;; *   pwr2:          [optional, default = 0]
;; *                  See mode-parameter. If mode and pwr2 are not specified, the MREAL value is round to an integer.
;; *
;; *   rounding_mode: [optional, default = global rounding mode]
;; *                  Specifies the round mode to use.
;; *
;; *   n:             [optional, default = MREAL_XDIM]
;; *                  Number of mantissa WORDs.
;; *
;; *   emin/max:      [optional, default = REAL10 exponent range]
;; *                  Binary exponent limit. Remarks that MREAL values are normalized to 2^(-1)=0.5.
;; *
;; *   quiet:         internal - do not use
;; */
MR_ROUND macro r:req,x:req,pwr2:=<0>,mode:=<normal>,rounding_mode:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>,emin:=<MREAL_MIN_EXP>,emax:=<MREAL_MAX_EXP>,quiet:=<0>
	
	MREAL_INEXACT = 0
	
	;/* check parameters */
	IFIDNI <&mode>,<normal>
		mrr_mode = 0
	ELSEIFIDNI <&mode>,<bits>
		mrr_mode = 1
		IF pwr2 LE 0
			.err <invalid parameter(3): <&pwr2> : expected positive nonzero value>
			EXITM
		ENDIF
	ELSE
		.err <invalid parameter(4): <&mode> : expected : <normal> or <bits>>
		EXITM
	ENDIF
	IF rounding_mode LT MRRM__MINVALUE OR rounding_mode GT MRRM__MAXVALUE
		.err <invalid parameter(5): <&rounding_mode>>
		EXITM
	ENDIF
	IF n LE 0
		.err <invalid parameter(6): <&n> : expected positive nonzero value>
		EXITM
	ENDIF
	
	mrce_errstr_overflow  TEXTEQU <the rounded value r exceeds the exponent limit (MREAL_MAX_EXP)>
	mrce_errstr_underflow TEXTEQU <the rounded value r is too small (exponent underflow (MREAL_MIN_EXP))>
	
	;;/**
	;; * process special input values
	;; */
	IF MREAL_&x&_flg AND MREAL_FLG_NON_NUMERIC_TEST
		IF MREAL_ERROR_FOR_NAN_INPUT NE 0 AND quiet EQ 0
			.err <x is not a numeric value>
		ENDIF
		MR_MOV r,x,n
		EXITM
	ELSEIF MREAL_&x&_flg AND MREAL_FLG_ZERO
		MR_SET_ZERO r,n
		EXITM
	ENDIF
	
	mrr_exp = MREAL_&x&_exp
	
	IFE mrr_mode
		mrr_rpos = pwr2 - mrr_exp
	ELSE
		mrr_rpos = -(pwr2)
	ENDIF
    ;;/**
    ;; *  mrr_rpos = bit position in mantissa
    ;; *  mrr_rpos:   0 -1           -n*16            
    ;; *              |  |             |
    ;; *              \ /              |
    ;; *               |<-- mantissa -->|             
    ;; *               |                |             
    ;; *          x = 0.1xxxRHssss...sss|00... * 2^exp
    ;; *                    ||\--------/              
    ;; *                    ||     |                  
    ;; *                    ||     +- sticky bits S     
    ;; *                    ||                        
    ;; *                    |+-- half-away bit H                 
    ;; *                    |                         
    ;; *                    +--- rounding digit R (pos. through pwr2)
    ;; */ 

	mrr_sign = (MREAL_&x&_flg AND MREAL_FLG_SIGN) NE 0

	;;/**
	;; * Handle cases where the rounding digit lies outside the mantissa
	;; */
	IF mrr_rpos LE -16*(n)
		;;/* all remaining digts after rounding digit are zero -> no rounding needed */
		MR_MOV r,x,n
		MR_CHECK_EXPONENT r,emin,emax,n
		IFNB mrce_errstr
			IFE quiet
				.err mrce_errstr
			ENDIF
		ENDIF
		EXITM
	ELSEIF mrr_rpos EQ 0
		;;/* manitssa is: R.1xxxxxx... with R=0=rounding digit */
		MREAL_INEXACT = -1
		IF rounding_mode EQ MRRM_ROUND_TO_NEAREST_TIES_TO_EVEN
			;;/* always half-away case: test sticky bits */
			mrr_cntr = 0
			IFE MREAL_&x&_w0 AND 07fffh
				mrr_cntr = 1
				WHILE mrr_cntr LT n
					IF @CatStr(<MREAL_&x&_w>,%mrr_cntr)
						EXITM
					ENDIF
					mrr_cntr = mrr_cntr + 1
				ENDM
			ENDIF
			IF mrr_cntr EQ n
				;;/**
				;; * mantissa is: 0.1000...0
				;; *  -> round towards zero
				;; */
				MR_SET_ZERO r,n
				EXITM
			ENDIF
			;;/**
			;; * mantissa is: 0.1sss...s  with sticky bits != 0
			;; *  -> round away from zero
			;; */
			MR_RAW_SET_N r,@SubStr(<-+>,2+mrr_sign,1),%(pwr2),n,8000h
			MR_CHECK_EXPONENT r,emin,emax,n
			IFNB mrce_errstr
				IFE quiet
					.err mrce_errstr
				ENDIF
			ENDIF
			EXITM
		ELSEIF rounding_mode EQ MRRM_ROUND_TO_NEAREST_TIES_AWAY_FROM_ZERO
			MR_RAW_SET_N r,@SubStr(<-+>,2+mrr_sign,1),%(pwr2),n,8000h
		ELSEIF rounding_mode EQ MRRM_ROUND_TOWARD_POSITIVE AND mrr_sign EQ 0
			MR_RAW_SET_N r,+,%(pwr2),n,8000h
		ELSEIF rounding_mode EQ MRRM_ROUND_TOWARD_NEGATIVE AND mrr_sign NE 0
			MR_RAW_SET_N r,-,%(pwr2),n,8000h
		ELSE
			MR_SET_ZERO r,n
			EXITM
		ENDIF
		MR_CHECK_EXPONENT r,emin,emax,n
		IFNB mrce_errstr
			IFE quiet
				.err mrce_errstr
			ENDIF
		ENDIF
		EXITM
	ELSEIF mrr_rpos GE 1
		;;/* manitssa is: R0+.1xxxxxx... with R=0=rounding digit and "0+" = one or more zero digits */
		MREAL_INEXACT = -1
		IF rounding_mode EQ MRRM_ROUND_TOWARD_POSITIVE AND mrr_sign EQ 0
			MR_RAW_SET_N r,+,%(pwr2),n,8000h
		ELSEIF rounding_mode EQ MRRM_ROUND_TOWARD_NEGATIVE AND mrr_sign NE 0
			MR_RAW_SET_N r,-,%(pwr2),n,8000h
		ELSE
			MR_SET_ZERO r,n
			EXITM
		ENDIF
		MR_CHECK_EXPONENT r,emin,emax,n
		IFNB mrce_errstr
			IFE quiet
				.err mrce_errstr
			ENDIF
		ENDIF
		EXITM
	ENDIF
	
	;;/**
	;; * Case: rounding digit lies inside the mantissa.
	;; * Do:
	;; * - copy: x --> r
	;; * - get rounding digit R
	;; * - get half-away bit H
	;; * - get stick bits S
	;; * - zero all bits below rounding digit (truncate)
	;; */
	
	MREAL_&r&_flg = MREAL_&x&_flg
	MREAL_&r&_exp = MREAL_&x&_exp
	
	mrr_iR = (-mrr_rpos-1) / 16
	mrr_iH = (-mrr_rpos  ) / 16
	mrr_iZ = mrr_iH
	mrr_iS = (-mrr_rpos+1) / 16
	mrr_msk_R = 08000h SHR ((-mrr_rpos-1) MOD 16)
	mrr_msk_H = 08000h SHR ((-mrr_rpos  ) MOD 16)
	mrr_msk_Z = 0ffffh SHR ((-mrr_rpos  ) MOD 16) XOR 0ffffh
	mrr_msk_S = 0ffffh SHR ((-mrr_rpos+1) MOD 16)
	mrr_R = 0
	mrr_H = 0
	mrr_S = 0
	
	mrr_cntr = 0
	WHILE mrr_cntr LT n
		mrr_tcntr TEXTEQU %mrr_cntr
	%	mrr_value_i = MREAL_&x&_w&mrr_tcntr&
		IF mrr_cntr EQ mrr_iR
			mrr_R = (mrr_value_i AND mrr_msk_R) NE 0
		ENDIF
		IF mrr_cntr EQ mrr_iH
			mrr_H = (mrr_value_i AND mrr_msk_H) NE 0
		ENDIF	
		IF mrr_cntr EQ mrr_iS
			mrr_S = (mrr_value_i AND mrr_msk_S) NE 0
		ELSEIF mrr_cntr GT mrr_iS
			mrr_S = mrr_S OR (mrr_value_i NE 0)
		ENDIF
		IF mrr_cntr LT mrr_iZ
		%	MREAL_&r&_w&mrr_tcntr& = mrr_value_i
		ELSEIF mrr_cntr EQ mrr_iZ
		%	MREAL_&r&_w&mrr_tcntr& = mrr_value_i AND mrr_msk_Z
		ELSE
		%	MREAL_&r&_w&mrr_tcntr& = 0	
		ENDIF
		mrr_cntr = mrr_cntr + 1
	ENDM
	
	mrr_G = mrr_H OR mrr_S
	
	;;/* set inexact */
	MREAL_INEXACT = mrr_G
	
	;;/**
	;; * apply rounding mode to truncated value
	;; */
	mrr_carry = 0
	IF rounding_mode EQ MRRM_ROUND_TO_NEAREST_TIES_TO_EVEN AND ((mrr_H AND (NOT mrr_S) AND mrr_R) OR (mrr_H AND mrr_S))
		mrr_carry = 1
	ELSEIF mrr_H AND rounding_mode EQ MRRM_ROUND_TO_NEAREST_TIES_AWAY_FROM_ZERO
		mrr_carry = 1
	ELSEIF mrr_sign AND mrr_G AND rounding_mode EQ MRRM_ROUND_TOWARD_NEGATIVE
		mrr_carry = 1
	ELSEIF (NOT mrr_sign) AND mrr_G AND rounding_mode EQ MRRM_ROUND_TOWARD_POSITIVE
		mrr_carry = 1
	ENDIF

	IF mrr_carry
		;;/* Add 1 to the LSB of the truncated mantissa */
		mrr_cntr = mrr_iR
		mrr_carry = mrr_msk_R
		WHILE mrr_cntr GE 0
			mrr_tcntr TEXTEQU %mrr_cntr
		%	mrr_tmp = MREAL_&r&_w&mrr_tcntr& + mrr_carry
		%	MREAL_&r&_w&mrr_tcntr& = LOWWORD mrr_tmp
			mrr_carry = HIGHWORD mrr_tmp
			IFE mrr_carry
				EXITM
			ENDIF
			mrr_cntr = mrr_cntr - 1
		ENDM
	ENDIF
	IF mrr_carry
		;;/* normalize result */
		MR_RSHIFT_1 r,%(n)
		MREAL_&r&_w0 = MREAL_&r&_w0 OR 8000h
		MREAL_&r&_exp = MREAL_&r&_exp + 1
	ENDIF

	MR_CHECK_EXPONENT r,emin,emax,n
	IFNB mrce_errstr
		IFE quiet
			.err mrce_errstr
		ENDIF
	ENDIF
	;; job done :-D
endm

; out: mrrmth_hextxt
MR_RAW_MANTISSA_TO_HEX macro value,n:=<MREAL_XDIM>
	mrrmth_hextxt TEXTEQU <>
	mrrmth_cntr = 0
	REPEAT n
		mrrmth_val = @CatStr(<MREAL_&value&_w>,%mrrmth_cntr)
		.radix 16
			mrrmth_txt TEXTEQU %mrrmth_val
		.radix 10
		mrrmth_size SIZESTR mrrmth_txt
		IF mrrmth_size LE 3
			mrrmth_txt TEXTEQU @SubStr(<000>,mrrmth_size),mrrmth_txt
		ENDIF
		mrrmth_hextxt TEXTEQU mrrmth_hextxt,mrrmth_txt
		mrrmth_cntr = mrrmth_cntr + 1
	ENDM
endm

;/**
; * Storage parameters for IEEE 754-1985/2008
; * binary interchange format encodings.
; */
ieee754_bin16_nPrecisionBits = 11
ieee754_bin16_hb = -1				; hb = hidden bit
ieee754_bin16_nExponentBits = 5
ieee754_bin16_bias = 15
ieee754_bin16_cw = 1				; cw = size in WORDs
ieee754_bin16_masm_type = 0			; MASM support this type? 

ieee754_bin32_nPrecisionBits = 24
ieee754_bin32_hb = -1
ieee754_bin32_nExponentBits = 8
ieee754_bin32_bias = 127
ieee754_bin32_cw = 2
ieee754_bin32_masm_type = -1

ieee754_bin64_nPrecisionBits = 53
ieee754_bin64_hb = -1
ieee754_bin64_nExponentBits = 11
ieee754_bin64_bias = 1023
ieee754_bin64_cw = 4
ieee754_bin64_masm_type = -1

ieee754_bin80_nPrecisionBits = 64
ieee754_bin80_hb = 0
ieee754_bin80_nExponentBits = 15
ieee754_bin80_bias = 16383
ieee754_bin80_cw = 5
ieee754_bin80_masm_type = -1

mrti_glbl_last_line = -1
mrti_glbl_cntr = 0

;;/**
;; * Convert MREAL value to MASM floating point initializer (hexadecimal format). Denormal values in target format are not supported.
;; * Parameters:
;; *  type:   specifies the target format:
;; *                  type      |   IEEE 754-2008   |   IEEE 754-1985    |  MASM type  | precision | hidden bit | storage size | exponent max\min | bias   
;; *          ------------------+-------------------+--------------------+-------------+-----------+------------+--------------+------------------+------- 
;; *          <REAL4>           |     binary32      |  single precision  |    REAL4    |  24 bit   |    yes     |  4 Bytes     |    127 \ -126    | 127    
;; *          <single>          |                   |                    |             |           |            |              |                  |        
;; *          <binary32>        |                   |                    |             |           |            |              |                  |        
;; *          ------------------+-------------------+--------------------+-------------+-----------+------------+--------------+------------------+------- 
;; *          <REAL8>           |     binary64      |  double precision  |    REAL8    |  53 bit   |    yes     |  8 Bytes     |   1023 \ -1022   | 1023   
;; *          <double>          |                   |                    |             |           |            |              |                  |        
;; *          <binary64>        |                   |                    |             |           |            |              |                  |        
;; *          ------------------+-------------------+--------------------+-------------+-----------+------------+--------------+------------------+------- 
;; *          <REAL10>          |        -          |  double extended   |    REAL10   |  64 bit   |    no      | 10 Bytes     |  16383 \ -16382  | 16383  
;; *          <double-extended> |                   |  precision         |             |           |            |              |                  |        
;; *                            |                   |                    |             |           |            |              |                  |        
;; *          ------------------+-------------------+--------------------+-------------+-----------+------------+--------------+------------------+------- 
;; *          <binary16>        |     binary16      |         -          |      -      |  11 bit   |    yes     |  2 Bytes     |     15 \ -14     | 15     
;; *          ------------------+-------------------+--------------------+-------------+-----------+------------+--------------+------------------+------- 
;; * 
;; *  Return: a text macro that holds the hexadecimal floating point initializer. For binary16 a WORD-sized integer constant is used.
;; *          Due to a bug** in MASM v6-7 this macro cannot directly used to initialize REAL10 values (see MR_DEF_REAL10 macro).
;; *          
;; *          ** MASM reject hexadecimal initializers for REAL10 values that have a leading zero, even if the zero is required (e.g. -1.0 = 0Bfff8000000000000000r)
;; */
MR_TO_IEEE macro type:=<double-extended>,value:req,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>
	MREAL_INEXACT = 0

	;;/* needed for bugfix (MASM v8+) */
	IF mrti_glbl_last_line NE @Line
		mrti_glbl_last_line = @Line
		mrti_glbl_cntr = 0
	ELSE
		mrti_glbl_cntr = mrti_glbl_cntr + 1
	ENDIF
	??BADVALUE TEXTEQU <0.0>
	
	FOR t,<&type>
		mrti_t TEXTEQU <&t>
		EXITM
	ENDM
	mrti_itype = -1
	FOR t,<REAl4,REAl8,REAl10,single,double,double-extended,binary16,binary32,binary64>
		IFIDNI <&t>,mrti_t
			mrti_itype = mrti_itype + 1
			EXITM
		ENDIF
		mrti_itype = mrti_itype + 1
	ENDM
	IF mrti_itype EQ -1
		.err <unknown _type specifier: type>
		EXITM <??BADVALUE>
	ENDIF
	mrti_itype = @SubStr(<040810040810020408>,mrti_itype*2+1,2)
	
	;;/**
	;; * Get storage format parameters
	;; */
	mrti_nPrecisionBits = @CatStr(<ieee754_bin>,%mrti_itype*8,<_nPrecisionBits>)
	;;/* hb = hidden bit? = 0 or -1 */
	mrti_hb = @CatStr(<ieee754_bin>,%mrti_itype*8,<_hb>)
	mrti_nExponentBits = @CatStr(<ieee754_bin>,%mrti_itype*8,<_nExponentBits>)
	mrti_bias = @CatStr(<ieee754_bin>,%mrti_itype*8,<_bias>)
	;;/* cw = size of target format in WORDs */
	mrti_cw = @CatStr(<ieee754_bin>,%mrti_itype*8,<_cw>)
	mrti_masm_type = @CatStr(<ieee754_bin>,%mrti_itype*8,<_masm_type>)
	
	;;/**
	;; * Add 1 to IEEE-emin/emax to respect
	;; * different normalization ( 2^0 vs. 2^(-1) )
	;; */
	mrti_emax = mrti_bias+1		;; IEEE: emax = bias
	mrti_emin = 2 - mrti_bias	;; IEEE: emin = 1-emax
	
	;;/* get number of WORDs needed for precission bits */
	mrti_cwPBitsSrc = mrti_nPrecisionBits/16 + (((mrti_nPrecisionBits MOD 16) NE 0) AND 1)
	
	;;/* copy: value --> mrtiTmp */
	MR_MOV mrtiTmp,value
	mrti_size = n
	
	IFE MREAL_mrtiTmp_flg AND MREAL_FLG_NO_MANTISSA_TEST
		;;/* numeric value (use mantissa) */
		IF (n)*16 GT mrti_nPrecisionBits
			;;/* value must be rounded */
			MR_ROUND mrtiTmp,value,%mrti_nPrecisionBits,<bits>,rm,n,%mrti_emin,%mrti_emax,-1
		ELSEIF (n)*16 LT mrti_nPrecisionBits
			;;/* zero extend value */
			mrti_cntr = mrti_cwPBitsSrc-1
			WHILE mrti_cntr GE n
				@CatStr(<MREAL_mrtiTmp_w>,%mrti_cntr) = 0
				mrti_cntr = mrti_cntr - 1
			ENDM
			mrti_size = mrti_cwPBitsSrc
		ENDIF
		;;/* check exponent limits */
		mrce_errstr_overflow  TEXTEQU <>
		mrce_errstr_underflow TEXTEQU <>
		MR_CHECK_EXPONENT mrtiTmp,%mrti_emin,%mrti_emax,%mrti_size,rm
	ENDIF

	IF MREAL_mrtiTmp_flg AND MREAL_FLG_NO_MANTISSA_TEST
		;;/* build special values */
		IF MREAL_mrtiTmp_flg AND MREAL_FLG_INF
			MR_RAW_MAXVALUE mrtiTmp,0,%mrti_cw
			MR_LSHIFT mrtiTmp,%mrti_nPrecisionBits-1,%mrti_cw
			MREAL_mrtiTmp_w0 = (MREAL_mrtiTmp_w0 AND 7fffh) OR (8000h AND ((MREAL_&value&_flg AND MREAL_FLG_SIGN) NE 0))
		ELSEIF MREAL_mrtiTmp_flg AND MREAL_FLG_NAN
			MR_RAW_MAXVALUE mrtiTmp,0,%mrti_cw
			MR_LSHIFT mrtiTmp,%mrti_nPrecisionBits-2,%mrti_cw
			MREAL_mrtiTmp_w0 = MREAL_mrtiTmp_w0 AND 7fffh
		ELSEIF MREAL_mrtiTmp_flg AND MREAL_FLG_ZERO
			MR_SET_ZERO mrtiTmp,%mrti_cw
		ELSE
			.err <invalid flags for: value>
			EXITM <??BADVALUE>
		ENDIF
		MR_RAW_MANTISSA_TO_HEX mrtiTmp,%mrti_cw
		IF mrti_masm_type
			@CatStr(<??IEEEVAL>,%mrti_glbl_cntr) TEXTEQU <0>,mrrmth_hextxt,<r>
		ELSE
			@CatStr(<??IEEEVAL>,%mrti_glbl_cntr) TEXTEQU <0>,mrrmth_hextxt,<h>
		ENDIF
		EXITM @CatStr(<??IEEEVAL>,%mrti_glbl_cntr)
	ENDIF
	
	;;/**
	;; * Compose IEEE binary format in mantissa
	;; * of mrtiTmp.
	;; */
	mrti_exp = MREAL_mrtiTmp_exp + mrti_bias - 1
	
	;;/* allocate space for exponent and sign field */
	mrti_cntr = mrti_cw-1
	WHILE mrti_cntr GE mrti_size
		@CatStr(<MREAL_mrtiTmp_w>,%mrti_cntr) = 0
		mrti_cntr = mrti_cntr - 1
	ENDM
	
	;;/* discard hidden bit */
	IF mrti_hb
		MR_LSHIFT_1 mrtiTmp,%mrti_cw
	ENDIF
	
	;;/* make room for exponent bits */
	MR_RSHIFT mrtiTmp,%mrti_nExponentBits,%mrti_cw
	;;/* save exponent field */
	mrti_bits = mrti_exp SHL (16-mrti_nExponentBits)
	MREAL_mrtiTmp_w0 = MREAL_mrtiTmp_w0 OR mrti_bits
	;;/* make room for sign bit */
	MR_RSHIFT_1 mrtiTmp,%mrti_cw
	;;/* set sign bit */
	MREAL_mrtiTmp_w0 = MREAL_mrtiTmp_w0 OR (8000h AND ((MREAL_&value&_flg AND MREAL_FLG_SIGN) NE 0))
	
	;;/* get hexadecimal string */
	MR_RAW_MANTISSA_TO_HEX mrtiTmp,%mrti_cw
	IF mrti_masm_type
		@CatStr(<??IEEEVAL>,%mrti_glbl_cntr) TEXTEQU <0>,mrrmth_hextxt,<r>
	ELSE
		@CatStr(<??IEEEVAL>,%mrti_glbl_cntr) TEXTEQU <0>,mrrmth_hextxt,<h>
	ENDIF
	EXITM @CatStr(<??IEEEVAL>,%mrti_glbl_cntr)
endm

REAL10_TO_TBYTE macro r10HexInitializer:=<>
	rtttb_val SUBSTR r10HexInitializer,1,21
	rtttb_val TEXTEQU rtttb_val,<h>
	EXITM rtttb_val
endm

;;/**
;; * This macro defines a REAL10 value in current segment.
;; */
MR_DEF_REAL10 macro lbl,x:req,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>
	IFNB <&lbl>
		lbl LABEL REAL10
	ENDIF
	TBYTE REAL10_TO_TBYTE(MR_TO_IEEE(<REAL10>,x,rm,n))
endm
MR_DECL_REAL10 TEXTEQU <MR_DEF_REAL10>


;-----------------------------------------------------------------------------------------------------------;
;Name:          @ScanForFlt(pos,txt,Chr) - scan for float                                                   ;
;Description:   scans in given string for a floating point or integer value. The integer value can          ;
;               be written in hexadecimal or decimal notation.                                              ;
;               There is no size-checking, only syntax (MASM-specific)                                      ;
;               Number format:   1. [+-]{0-9}[Tt]                   e.g.: -12345     , +12345t              ;
;                                2. [+-]{0-9}[0-9a-fA-F]{Hh}        e.g.: +0ab3fh    , 0FFFFFFFFh           ;
;                                3. [+-]{0-9}{.}[0-9]               e.g.: -999.99    , 12.0  , 1.           ;
;                                4. [+-]{0-9}{.}[0-9]{Ee}[+-]{0-9}  e.g.: +10.9E-12  , 3.E8                 ;
;                                5. [+-][0]{0-9a-fA-F}{Rr}          e.g.: 3F800000r  , 03F800000r           ;
;                                   {}=needed , []=optional                                                 ;
;                                   leading blanks are ignored (space/tab)                                  ;
;               The size for (5.) is restricted by the target type: 8 digits for REAL4, 16 for REAL8 and    ;
;               20 for REAL10. One more leading zero is allowed and required if the numbers begins          ;
;               with A-F or has leading zeros. For example the REAL4 0x0123 must be written as:             ;
;               000000123r (9 digits). Furthermore, the numeric string may be modified so that it           ;
;               has always a leading zero and the possible negative sign is moved into the hex-encoding     ;
;               (because MASM do not allow signs).                                                          ;
;                                                                                                           ;
;                                                                                                           ;
; Parameter:                                                                                                ;
;       pos:    start position in given expression                                                          ;
;       txt:    expression to scan                                                                          ;
;       Chr:    [optional] a string containing all characters that can follow a numeric expression.         ;
;               This test applies to the character directly following the numeric expression (one char.     ;
;               is tested)                                                                                  ;
;               If you specify "default" then for the follow char. is tested:                               ;
;                                         space,tab,+,-,*,/,),","                                           ;
;               Another key word is "blank", which cause to test for space and tab.                         ;
;               The key word "blanks" let the macro test all(!) remaining characters in the string          ;
;               If this parameter is blank, the macro doesn't care the char.                                ;
;               following a valid numeric expression, even if this invalidate it.                           ;
;               (see Example 6,7,8)                                                                         ;
;                                                                                                           ;
; Out:                                                                                                      ;
;   EXITM <>    0 => not a numeric expression   (if sff_type == -1: pos past end of string)                 ;
;               1 => floating point number                                                                  ;
;                    To differ between hexadecimal and decimal notation test for the                        ;
;                    SFF_HEX_REAL-flag.                                                                     ;
;               2 => integer                                                                                ;
;                    To differ between hexadecimal and decimal notation test for the                        ;
;                    SFF_HEX_SUFFIX-flag.                                                                   ;
;                                                                                                           ;
;   sff_type:   0,1,2 (same as EXITM <>)                                                                    ;
;                                                                                                           ;
;   sff_flag:   a combination of the following flags (according to num-type):                               ;
;   +-----------------------------+--------------------+-------------------------------------------------+  ;
;   |       valid for:            |        Flag        |    Description                                  |  ;
;   |float|float(hex)|int|int(hex)|                    |                                                 |  ;
;   +-----|----------+---+--------+--------------------+-------------------------------------------------+  ;
;   |  X  |          | X |    X   | SFF_SIGN           | the number has an sign                          |  ;
;   |  X  |          |   |        | SFF_EXPONENT       | an exponent is present                          |  ;
;   |  X  |          |   |        | SFF_EXP_SIGN       | the exponent has a sign                         |  ;
;   |     |          | X |        | SFF_DECIMAL_SUFFIX | the decimal-number ends with an "t" or "T"      |  ;
;   |     |          |   |    X   | SFF_HEX_SUFFIX     | the integer is writen in hexadecimal notation   |  ;
;   |     |    X     |   |        | SFF_HEX_REAL       | floating point value in hexadecimal notation    |  ;
;   |     |    X     |   |        | SFF_HEX_REAL4/8/10 | the type of FP value when written in            |  ;
;   |     |          |   |        |                    | hexadecimal notation                            |  ;
;   +-----+----------+---+--------+--------------------+-------------------------------------------------+  ;
;                                                                                                           ;
;   sff_numstr:         extracted numeric expression (all blanks are removed)                               ;
;   sff_pos:            points to next char. following numeric string (this could be out of string-range)   ;
;   sff_num_pos:        points to begin of num (in txt)                                                     ;
;                                                                                                           ;
;   The following TEXTEQUs depends on sff_flag and/or the type of num:                                      ;
;    +------------------+------------------+-----+------------------------+-------------------------+       ;
;    |      name        |      flag        |type |      description       |  characters             |       ;
;    +------------------+------------------+-----+------------------------+-------------------------+       ;
;    | sff_sign         | SFF_SIGN         | 1,2 | sign of num. Not used  | <+->                    |       ;
;    |                  |                  |     | for FP values in       |                         |       ;
;    |                  |                  |     | hex. notation.         |                         |       ;
;    | sff_pre_decimal  |                  | 1,2 | pre-decimal positions  | <0123456789>            |       ;
;    | sff_fract_digits | SFF_FRACT_DIGITS | 1   | post decimal positions,| <0123456789>            |       ;
;    | sff_exp_sign     | SFF_EXP_SIGN     | 1   | sign of the exponent   | <+->                    |       ;
;    |                  | +SFF_EXPONENT    |     |                        |                         |       ;
;    | sff_exp_digits   | SFF_EXPONENT     | 1   | exponent-digits        | <0123456789>            |       ;
;    | sff_hex_digits   | SFF_HEX_SUFFIX   | 1,2 | hex-digits             | <0123456789abcdefABCDEF>|       ;
;    +------------------+------------------+-----+------------------------+-------------------------+       ;
;                                                                                                           ;
; Examples:                                                                                                 ;
;   1       @ScanForFlt(1,< 1.0E-19 >)     --> 1 , sff_numstr=<1.0E-19> , sff_pos=9                         ;
;   2       @ScanForFlt(1,<-1.0*x>)        --> 1 , sff_numstr=<-1.0>    , sff_pos=5                         ;
;   3       @ScanForFlt(1,< -100 + x>)     --> 2 , sff_numstr=<-100>    , sff_pos=6                         ;
;   4     ! @ScanForFlt(1,<-1E-2>)         --> 2 , sff_numstr=<-1>      , sff_pos=3                         ;
;   5       @ScanForFlt(1,< 0ffh >)        --> 2 , sff_numstr=<0ffh>    , sff_pos=6                         ;
;                                                                                                           ;
;   6       @ScanForFlt(1,<12()>)          --> 2 , sff_numstr=<12>      , sff_pos=3                         ;
;   7       @ScanForFlt(1,<12()>,default)  --> 0                                                            ;
;   8       myChars TEXTEQU <   +-*/()>                                                                     ;
;           @ScanForFlt(1,<12()>,myChars)  --> 2 , sff_numstr=<12>      , sff_pos=3                         ;
;                                                                                       by qWord, 2008-2015 ;
;-----------------------------------------------------------------------------------------------------------;
@ScanForFlt macro pos:req,txt:=<>,Chr

	IFNDEF SFF_PRE_DECIMAL
		SFF_PRE_DECIMAL		EQU 1
		SFF_FRACT_DIGITS	EQU 2
		SFF_DOT				EQU 4
		SFF_EXPONENT		EQU 8
		SFF_EXP_DIGITS		EQU 16
		SFF_SIGN			EQU 32
		SFF_EXP_SIGN		EQU 64
		SFF_DECIMAL_SUFFIX	EQU 128
		SFF_HEX_DIGITS		EQU 256
		SFF_HEX_SUFFIX		EQU 512
		SFF_HEX_REAL		EQU 1024
		SFF_HEX_REAL4		EQU 2048
		SFF_HEX_REAL8		EQU 4096
		SFF_HEX_REAL10		EQU 8192
	ENDIF

	sff_txt 			TEXTEQU <txt>
	sff_size 			SIZESTR sff_txt	
	sff_err 			= 0				
	sff_last_decimal	= 0				
	
	sff_pos				= pos			
	sff_num_pos 		= 0             
	sff_flag			= 0             
	sff_type			= 0             
	sff_numstr			TEXTEQU <>      
	sff_sign			TEXTEQU <>      
	sff_pre_decimal		TEXTEQU <>      
	sff_fract_digits	TEXTEQU <>      
	sff_exp_sign		TEXTEQU <>      
	sff_exp_digits		TEXTEQU <>      
	sff_hex_digits		TEXTEQU <>		
	sff_skip_to_check  = 0
	IF sff_pos GT sff_size
		sff_flag = -1
		EXITM <0>
	ENDIF
	
	sff_cntr = 1 
	REPEAT sff_size-pos+1
		sff_blank SUBSTR sff_txt,pos,sff_cntr
		IFNB sff_blank
			sff_num_pos = sff_pos
			EXITM
		ENDIF
		sff_pos = sff_pos + 1
		sff_cntr = sff_cntr + 1	
	ENDM

	IF sff_pos GT sff_size
		EXITM <0>
	ENDIF

	sff_char SUBSTR sff_txt,sff_pos,1
	IFIDN sff_char,<+>
		sff_flag = sff_flag OR SFF_SIGN
		sff_sign TEXTEQU <+>
		sff_pos = sff_pos + 1
	ELSEIFIDN sff_char,<->
		sff_flag = sff_flag OR SFF_SIGN
		sff_sign TEXTEQU <->
		sff_pos = sff_pos + 1
	ENDIF
	
	IF sff_pos GT sff_size
		EXITM <0>
	ENDIF
;:sff_pre_dig	
	REPEAT sff_size-sff_pos+1
		sff_char SUBSTR sff_txt,sff_pos,1
		sff_cntr INSTR 1,<0123456789abcdefABCDEF>,sff_char
		IF sff_cntr NE 0
			sff_pos = sff_pos + 1
			IF sff_cntr GE 11
				IF (sff_flag AND SFF_PRE_DECIMAL) EQ 0
					sff_pos = sff_pos - 1
					sff_err = 1
					EXITM
				ENDIF
				IF sff_last_decimal EQ 0
					sff_last_decimal = sff_pos-1
				ENDIF
				sff_flag = sff_flag OR SFF_HEX_DIGITS
			ELSE
				sff_last_decimal = sff_pos-1
				sff_flag = sff_flag OR SFF_PRE_DECIMAL
			ENDIF
			sff_pre_decimal CATSTR sff_pre_decimal,sff_char
			sff_err = 0
		ELSE
			sff_err = 1
			EXITM
		ENDIF
	ENDM

	IF sff_err EQ 1
		IFIDN sff_char,<.>
			IF (sff_flag AND SFF_HEX_DIGITS) EQ 0
				sff_pos  = sff_pos + 1
				sff_flag = sff_flag OR SFF_DOT
			ELSE
				sff_skip_to_check = 1
			ENDIF
		ELSEIFIDNI sff_char,<t>
			sff_flag = sff_flag OR SFF_DECIMAL_SUFFIX
			sff_pos  = sff_pos + 1
			sff_skip_to_check = 1
		ELSEIFIDNI sff_char,<h>
			sff_flag = sff_flag OR SFF_HEX_SUFFIX
			sff_pos  = sff_pos + 1
			sff_skip_to_check = 1
		ELSEIFIDNI sff_char,<r>
			sff_flag = sff_flag OR SFF_HEX_REAL
			sff_pos  = sff_pos + 1
			sff_skip_to_check = 1
		ELSE
			sff_skip_to_check = 1
		ENDIF
	ELSE
		sff_skip_to_check = 1
	ENDIF

;:sff_fract	
	IF sff_pos GT sff_size
		sff_skip_to_check = 1
	ENDIF
	IF sff_skip_to_check EQ 0
		REPEAT sff_size-sff_pos+1
			sff_char SUBSTR sff_txt,sff_pos,1
			sff_cntr INSTR 1,<0123456789>,sff_char
			IF sff_cntr NE 0
				sff_pos = sff_pos + 1
				sff_flag = sff_flag OR SFF_FRACT_DIGITS
				sff_fract_digits CATSTR sff_fract_digits,sff_char
				sff_err = 0
			ELSE
				sff_err = 1
				EXITM
			ENDIF
		ENDM
		
		IF sff_err EQ 1
			IFIDNI sff_char,<E>
				sff_pos  = sff_pos + 1
				sff_flag = sff_flag OR SFF_EXPONENT
			ELSE
				sff_skip_to_check = 1
			ENDIF
		ELSE
			sff_skip_to_check = 1
		ENDIF
	
		IF sff_pos GT sff_size
			sff_skip_to_check = 1
		ENDIF
		IF sff_skip_to_check EQ 0
			sff_char SUBSTR sff_txt,sff_pos,1
			IFIDN sff_char,<+>
				sff_flag = sff_flag OR SFF_EXP_SIGN
				sff_exp_sign TEXTEQU <+>
				sff_pos = sff_pos + 1
			ELSEIFIDN sff_char,<->
				sff_flag = sff_flag OR SFF_EXP_SIGN
				sff_exp_sign TEXTEQU <->
				sff_pos = sff_pos + 1
			ENDIF
		
;		:sff_exp_dig
			IF sff_pos GT sff_size
				sff_skip_to_check = 1
			ENDIF
			
			IF sff_skip_to_check EQ 0
				REPEAT sff_size-sff_pos+1
					sff_char SUBSTR sff_txt,sff_pos,1
					sff_cntr INSTR 1,<0123456789>,sff_char
					IF sff_cntr NE 0
						sff_pos = sff_pos + 1
						sff_flag = sff_flag OR SFF_EXP_DIGITS
						sff_exp_digits CATSTR sff_exp_digits,sff_char
					ELSE
						EXITM
					ENDIF
				ENDM
			ENDIF
		ENDIF
	ENDIF	
;:sff_check
	IF (sff_flag AND (NOT (SFF_SIGN OR SFF_DECIMAL_SUFFIX))) EQ SFF_PRE_DECIMAL 
		sff_numstr SUBSTR sff_txt,sff_num_pos,sff_pos-sff_num_pos
		sff_type = 2
	ELSEIF (sff_flag AND (NOT (SFF_SIGN OR SFF_FRACT_DIGITS))) EQ (SFF_PRE_DECIMAL OR SFF_DOT )
		sff_numstr SUBSTR sff_txt,sff_num_pos,sff_pos-sff_num_pos
		sff_type = 1
	ELSEIF (sff_flag AND (NOT (SFF_SIGN OR SFF_EXP_SIGN OR SFF_FRACT_DIGITS))) EQ (SFF_PRE_DECIMAL OR SFF_DOT OR SFF_EXPONENT OR SFF_EXP_DIGITS)
		sff_numstr SUBSTR sff_txt,sff_num_pos,sff_pos-sff_num_pos
		sff_type = 1
	ELSEIF (sff_flag AND (NOT (SFF_SIGN OR SFF_HEX_DIGITS))) EQ (SFF_PRE_DECIMAL OR SFF_HEX_SUFFIX) 
		sff_numstr SUBSTR sff_txt,sff_num_pos,sff_pos-sff_num_pos
		sff_hex_digits TEXTEQU sff_pre_decimal
		sff_type = 2
	ELSEIF (sff_flag AND (NOT (SFF_SIGN OR SFF_HEX_DIGITS))) EQ (SFF_PRE_DECIMAL OR SFF_HEX_REAL)
		sff_hex_digits TEXTEQU sff_pre_decimal
		sff_size2 SIZESTR sff_hex_digits
		IF NOT ((sff_size2 AND -2) EQ 8 OR (sff_size2 AND -2) EQ 16 OR (sff_size2 AND -2) EQ 20)  ; MASM bug (all versions) : when using a ELSE clausel here, MASM lost track of nesting.
			sff_type = 0
			EXITM <0>
		ENDIF
		sff_type = 1
		IF (sff_size2 MOD 2) EQ 0
			sff_hex_digits CATSTR <0>,sff_hex_digits
	%	ELSEIFDIF <0>,<@SubStr(%sff_hex_digits,1,1)>
			sff_type = 0
			EXITM <0>
		ENDIF
		IF (sff_size2 AND -2) EQ 8
			sff_flag = sff_flag or SFF_HEX_REAL4
		ELSEIF (sff_size2 AND -2) EQ 16
			sff_flag = sff_flag or SFF_HEX_REAL8
		ELSEIF (sff_size2 AND -2) EQ 20
			sff_flag = sff_flag or SFF_HEX_REAL10
		ENDIF
		IF (sff_flag AND SFF_SIGN) NE 0
			IFIDN sff_sign,<->
				sff_hex_digits TEXTEQU @SubStr(%sff_hex_digits,1,1),@SubStr(<89abcdef01234567>,%1+@CatStr(<0>,@SubStr(%sff_hex_digits,2,1),<h>),1),@SubStr(%sff_hex_digits,3)
			ENDIF
			sff_flag = sff_flag AND (NOT SFF_SIGN)
		ENDIF
		sff_numstr TEXTEQU sff_hex_digits,sff_char
	ELSEIF (sff_flag AND SFF_PRE_DECIMAL) NE 0 AND (sff_flag AND SFF_HEX_DIGITS) EQ 0
		sff_pos = sff_last_decimal + 1
		sff_numstr CATSTR sff_sign,sff_pre_decimal
		sff_type = 2
	ELSEIFB <&Chr>
		IF (sff_flag AND (SFF_PRE_DECIMAL OR SFF_DOT OR SFF_FRACT_DIGITS)) EQ (SFF_PRE_DECIMAL OR SFF_DOT OR SFF_FRACT_DIGITS)
			sff_numstr TEXTEQU sff_pre_decimal,<.>,sff_fract_digits
			IF sff_flag AND SFF_SIGN
				sff_numstr TEXTEQU sff_sign,sff_numstr
			ENDIF
			sff_pos SIZESTR sff_numstr
			sff_pos = sff_pos + sff_num_pos
			sff_type = 1
			sff_flag = sff_flag AND (SFF_SIGN OR SFF_PRE_DECIMAL OR SFF_DOT OR SFF_FRACT_DIGITS)
		ELSEIF (sff_flag AND (SFF_PRE_DECIMAL OR SFF_DOT)) EQ (SFF_PRE_DECIMAL OR SFF_DOT)
			sff_numstr TEXTEQU sff_pre_decimal,<.>
			IF sff_flag AND SFF_SIGN
				sff_numstr TEXTEQU sff_sign,sff_numstr
			ENDIF
			sff_pos SIZESTR sff_numstr
			sff_pos = sff_pos + sff_num_pos
			sff_type = 1
			sff_flag = sff_flag AND (SFF_SIGN OR SFF_PRE_DECIMAL OR SFF_DOT )
		ELSEIF (sff_flag AND SFF_PRE_DECIMAL) NE 0
			sff_numstr SUBSTR sff_txt,sff_num_pos,sff_last_decimal-sff_num_pos+1
			sff_pos = sff_last_decimal + 1
			sff_type = 2
		ELSE
			EXITM <0>
		ENDIF
	ELSE
		EXITM <0>
	ENDIF

	IFB <&Chr>
		EXITM %sff_type
	ELSE
		IF sff_pos LE sff_size
			IFIDNI <&Chr>,<default>
				sff_validchar TEXTEQU < 	+-*/!)!,>
			ELSEIFIDNI <&Chr>,<blank>
				sff_validchar TEXTEQU < 	>
			ELSE
				sff_validchar TEXTEQU <&Chr>
			ENDIF
			IFDIFI <&Chr>,<blanks>
				sff_char SUBSTR sff_txt,sff_pos,1
				sff_valid INSTR 1,sff_validchar,sff_char
				IF sff_valid EQ 0
					sff_type = 0
					EXITM <0>
				ENDIF
			ELSE
				sff_char SUBSTR sff_txt,sff_pos
				IFNB sff_char
					sff_type = 0
					EXITM <0>
				ENDIF
			ENDIF
		ENDIF
	ENDIF
	EXITM %sff_type
endm

;;/* decimal exponent table 10^x, 0 <= x <= MAXEXP */
MR_SET_CONST ?MRC_1E0,+,0,22,8000h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^0
MR_SET_CONST ?MRC_1E1,+,3,22,0a000h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^1
MR_SET_CONST ?MRC_1E2,+,6,22,0c800h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^2
MR_SET_CONST ?MRC_1E3,+,9,22,0fa00h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^3
MR_SET_CONST ?MRC_1E4,+,13,22,9c40h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^4
MR_SET_CONST ?MRC_1E5,+,16,22,0c350h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^5
MR_SET_CONST ?MRC_1E6,+,19,22,0f424h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^6
MR_SET_CONST ?MRC_1E7,+,23,22,9896h,8000h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^7
MR_SET_CONST ?MRC_1E8,+,26,22,0bebch,2000h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^8
MR_SET_CONST ?MRC_1E9,+,29,22,0ee6bh,2800h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^9
MR_SET_CONST ?MRC_1E10,+,33,22,9502h,0f900h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^10
MR_SET_CONST ?MRC_1E11,+,36,22,0ba43h,0b740h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^11
MR_SET_CONST ?MRC_1E12,+,39,22,0e8d4h,0a510h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^12
MR_SET_CONST ?MRC_1E13,+,43,22,9184h,0e72ah,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^13
MR_SET_CONST ?MRC_1E14,+,46,22,0b5e6h,20f4h,8000h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^14
MR_SET_CONST ?MRC_1E15,+,49,22,0e35fh,0a931h,0a000h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^15
MR_SET_CONST ?MRC_1E16,+,53,22,8e1bh,0c9bfh,400h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^16
MR_SET_CONST ?MRC_1E17,+,56,22,0b1a2h,0bc2eh,0c500h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^17
MR_SET_CONST ?MRC_1E18,+,59,22,0de0bh,6b3ah,7640h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^18
MR_SET_CONST ?MRC_1E19,+,63,22,8ac7h,2304h,89e8h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^19
MR_SET_CONST ?MRC_1E20,+,66,22,0ad78h,0ebc5h,0ac62h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^20
MR_SET_CONST ?MRC_1E21,+,69,22,0d8d7h,26b7h,177ah,8000h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^21
MR_SET_CONST ?MRC_1E22,+,73,22,8786h,7832h,6each,9000h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^22
MR_SET_CONST ?MRC_1E23,+,76,22,0a968h,163fh,0a57h,0b400h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^23
MR_SET_CONST ?MRC_1E24,+,79,22,0d3c2h,1bceh,0ccedh,0a100h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^24
MR_SET_CONST ?MRC_1E25,+,83,22,8459h,5161h,4014h,84a0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^25
MR_SET_CONST ?MRC_1E26,+,86,22,0a56fh,0a5b9h,9019h,0a5c8h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^26
MR_SET_CONST ?MRC_1E27,+,89,22,0cecbh,8f27h,0f420h,0f3ah,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^27
MR_SET_CONST ?MRC_1E28,+,93,22,813fh,3978h,0f894h,984h,4000h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^28
MR_SET_CONST ?MRC_1E29,+,96,22,0a18fh,7d7h,36b9h,0be5h,5000h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^29
MR_SET_CONST ?MRC_1E30,+,99,22,0c9f2h,0c9cdh,467h,4edeh,0a400h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^30
MR_SET_CONST ?MRC_1E31,+,102,22,0fc6fh,7c40h,4581h,2296h,4d00h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^31
MR_SET_CONST ?MRC_1E32,+,106,22,9dc5h,0ada8h,2b70h,0b59dh,0f020h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^32
MR_SET_CONST ?MRC_1E33,+,109,22,0c537h,1912h,364ch,0e305h,6c28h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^33
MR_SET_CONST ?MRC_1E34,+,112,22,0f684h,0df56h,0c3e0h,1bc6h,0c732h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^34
MR_SET_CONST ?MRC_1E35,+,116,22,9a13h,0b96h,3a6ch,115ch,3c7fh,4000h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^35
MR_SET_CONST ?MRC_1E36,+,119,22,0c097h,0ce7bh,0c907h,15b3h,4b9fh,1000h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^36
MR_SET_CONST ?MRC_1E37,+,122,22,0f0bdh,0c21ah,0bb48h,0db20h,1e86h,0d400h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^37
MR_SET_CONST ?MRC_1E38,+,126,22,9676h,9950h,0b50dh,88f4h,1314h,4480h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^38
MR_SET_CONST ?MRC_1E39,+,129,22,0bc14h,3fa4h,0e250h,0eb31h,17d9h,55a0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^39
MR_SET_CONST ?MRC_1E40,+,132,22,0eb19h,4f8eh,1ae5h,25fdh,5dcfh,0ab08h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^40
MR_SET_CONST ?MRC_1E41,+,136,22,92efh,0d1b8h,0d0cfh,37beh,5aa1h,0cae5h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^41
MR_SET_CONST ?MRC_1E42,+,139,22,0b7abh,0c627h,503h,5adh,0f14ah,3d9eh,4000h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^42
MR_SET_CONST ?MRC_1E43,+,142,22,0e596h,0b7b0h,0c643h,0c719h,6d9ch,0cd05h,0d000h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^43
MR_SET_CONST ?MRC_1E44,+,146,22,8f7eh,32ceh,7beah,5c6fh,0e482h,23h,0a200h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^44
MR_SET_CONST ?MRC_1E45,+,149,22,0b35dh,0bf82h,1ae4h,0f38bh,0dda2h,802ch,8a80h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^45
MR_SET_CONST ?MRC_1E46,+,152,22,0e035h,2f62h,0a19eh,306eh,0d50bh,2037h,0ad20h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^46
MR_SET_CONST ?MRC_1E47,+,156,22,8c21h,3d9dh,0a502h,0de45h,4526h,0f422h,0cc34h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^47
MR_SET_CONST ?MRC_1E48,+,159,22,0af29h,8d05h,0e43h,95d6h,9670h,0b12bh,7f41h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^48
MR_SET_CONST ?MRC_1E49,+,162,22,0daf3h,0f046h,51d4h,7b4ch,3c0ch,0dd76h,5f11h,4000h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^49
MR_SET_CONST ?MRC_1E50,+,166,22,88d8h,762bh,0f324h,0cd0fh,0a588h,0a69h,0fb6ah,0c800h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^50
MR_SET_CONST ?MRC_1E51,+,169,22,0ab0eh,93b6h,0efeeh,53h,8eeah,0d04h,7a45h,7a00h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^51
MR_SET_CONST ?MRC_1E52,+,172,22,0d5d2h,38a4h,0abe9h,8068h,72a4h,9045h,98d6h,0d880h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^52
MR_SET_CONST ?MRC_1E53,+,176,22,85a3h,6366h,0eb71h,0f041h,47a6h,0da2bh,7f86h,4750h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^53
MR_SET_CONST ?MRC_1E54,+,179,22,0a70ch,3c40h,0a64eh,6c51h,9990h,90b6h,5f67h,0d924h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^54
MR_SET_CONST ?MRC_1E55,+,182,22,0d0cfh,4b50h,0cfe2h,765h,0fff4h,0b4e3h,0f741h,0cf6dh,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^55
MR_SET_CONST ?MRC_1E56,+,186,22,8281h,8f12h,81edh,449fh,0bff8h,0f10eh,7a89h,21a4h,2000h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^56
MR_SET_CONST ?MRC_1E57,+,189,22,0a321h,0f2d7h,2268h,95c7h,0aff7h,2d52h,192bh,6a0dh,2800h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^57
MR_SET_CONST ?MRC_1E58,+,192,22,0cbeah,6f8ch,0eb02h,0bb39h,9bf4h,0f8a6h,9f76h,4490h,7200h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^58
MR_SET_CONST ?MRC_1E59,+,195,22,0fee5h,0b70h,25c3h,6a08h,2f2h,36d0h,4753h,0d5b4h,8e80h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^59
MR_SET_CONST ?MRC_1E60,+,199,22,9f4fh,2726h,179ah,2245h,1d7h,6242h,2c94h,6590h,0d910h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^60
MR_SET_CONST ?MRC_1E61,+,202,22,0c722h,0f0efh,9d80h,0aad6h,424dh,3ad2h,0b7b9h,7ef5h,0f54h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^61
MR_SET_CONST ?MRC_1E62,+,205,22,0f8ebh,0ad2bh,84e0h,0d58bh,0d2e0h,8987h,65a7h,0deb2h,5329h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^62
MR_SET_CONST ?MRC_1E63,+,209,22,9b93h,4c3bh,330ch,8577h,63cch,55f4h,9f88h,0eb2fh,73f9h,0a000h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^63
MR_SET_CONST ?MRC_1E64,+,212,22,0c278h,1f49h,0ffcfh,0a6d5h,3cbfh,6b71h,0c76bh,25fbh,50f8h,800h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^64
MR_SET_CONST ?MRC_1E65,+,215,22,0f316h,271ch,7fc3h,908ah,8befh,464eh,3945h,0ef7ah,2536h,0a00h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^65
MR_SET_CONST ?MRC_1E66,+,219,22,97edh,0d871h,0cfdah,3a56h,9775h,8bf0h,0e3cbh,0b5ach,5741h,0c640h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^66
MR_SET_CONST ?MRC_1E67,+,222,22,0bde9h,4e8eh,43d0h,0c8ech,3d52h,0eeedh,1cbeh,0a317h,6d12h,37d0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^67
MR_SET_CONST ?MRC_1E68,+,225,22,0ed63h,0a231h,0d4c4h,0fb27h,4ca7h,0aaa8h,63eeh,4bddh,4856h,0c5c4h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^68
MR_SET_CONST ?MRC_1E69,+,229,22,945eh,455fh,24fbh,1cf8h,8fe8h,0caa9h,3e74h,0ef6ah,4d36h,3b9ah,8000h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^69
MR_SET_CONST ?MRC_1E70,+,232,22,0b975h,0d6b6h,0ee39h,0e436h,0b3e2h,0fd53h,8e12h,2b44h,0e083h,0ca81h,2000h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^70
MR_SET_CONST ?MRC_1E71,+,235,22,0e7d3h,4c64h,0a9c8h,5d44h,60dbh,0bca8h,7196h,0b616h,18a4h,0bd21h,6800h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^71
MR_SET_CONST ?MRC_1E72,+,239,22,90e4h,0fbeh,0ea1dh,3a4ah,0bc89h,55e9h,46feh,31cdh,0cf66h,0f634h,0e100h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^72
MR_SET_CONST ?MRC_1E73,+,242,22,0b51dh,13aeh,0a4a4h,88ddh,6babh,0ab63h,98bdh,0be41h,4340h,0b3c2h,1940h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^73
MR_SET_CONST ?MRC_1E74,+,245,22,0e264h,589ah,4dcdh,0ab14h,0c696h,963ch,7eedh,2dd1h,9410h,0e0b2h,9f90h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^74
MR_SET_CONST ?MRC_1E75,+,249,22,8d7eh,0b760h,70a0h,8aech,0fc1eh,1de5h,0cf54h,3ca2h,0fc8ah,8c6fh,0a3bah,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^75
MR_SET_CONST ?MRC_1E76,+,252,22,0b0deh,6538h,8cc8h,0ada8h,3b25h,0a55fh,4329h,4bcbh,0bbadh,2f8bh,8ca8h,8000h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^76
MR_SET_CONST ?MRC_1E77,+,255,22,0dd15h,0fe86h,0affah,0d912h,49efh,0eb7h,13f3h,9ebeh,0aa98h,7b6eh,6fd2h,0a000h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^77
MR_SET_CONST ?MRC_1E78,+,259,22,8a2dh,0bf14h,2dfch,0c7abh,6e35h,6932h,6c78h,4337h,2a9fh,4d25h,5e3h,0a400h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^78
MR_SET_CONST ?MRC_1E79,+,262,22,0acb9h,2ed9h,397bh,0f996h,49c2h,0c37fh,796h,5404h,0f547h,206eh,475ch,8d00h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^79
MR_SET_CONST ?MRC_1E80,+,265,22,0d7e7h,7a8fh,87dah,0f7fbh,0dc33h,745eh,0c97bh,0e906h,3298h,0e889h,0d933h,0b040h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^80
MR_SET_CONST ?MRC_1E81,+,269,22,86f0h,0ac99h,0b4e8h,0dafdh,69a0h,28bbh,3dedh,71a3h,0df9fh,9156h,27c0h,4e28h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^81
MR_SET_CONST ?MRC_1E82,+,272,22,0a8ach,0d7c0h,2223h,11bch,0c408h,32eah,0d68h,0ce0ch,0d787h,75abh,0b1b0h,61b2h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^82
MR_SET_CONST ?MRC_1E83,+,275,22,0d2d8h,0db0h,2aabh,0d62bh,0f50ah,3fa4h,90c3h,190h,0d69h,5316h,9e1ch,7a1eh,8000h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^83
MR_SET_CONST ?MRC_1E84,+,279,22,83c7h,88eh,1aabh,65dbh,7926h,67c6h,0da79h,0e0fah,861h,0d3eeh,22d1h,0cc53h,1000h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^84
MR_SET_CONST ?MRC_1E85,+,282,22,0a4b8h,0cab1h,0a156h,3f52h,5770h,1b8h,9118h,5938h,8a7ah,48e9h,0ab86h,3f67h,0d400h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^85
MR_SET_CONST ?MRC_1E86,+,285,22,0cde6h,0fd5eh,9abh,0cf26h,0ed4ch,226h,0b55eh,6f86h,0ad18h,0db24h,1667h,0cf41h,0c900h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^86
MR_SET_CONST ?MRC_1E87,+,289,22,80b0h,5e5ah,0c60bh,6178h,544fh,8158h,315bh,5b4h,2c2fh,88f6h,8e00h,0e189h,1da0h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^87
MR_SET_CONST ?MRC_1E88,+,292,22,0a0dch,75f1h,778eh,39d6h,6963h,61aeh,3db1h,0c721h,373bh,6b34h,3181h,19ebh,6508h,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^88
MR_SET_CONST ?MRC_1E89,+,295,22,0c913h,936dh,0d571h,0c84ch,3bch,3a19h,0cd1eh,38e9h,850ah,4601h,3de1h,6066h,3e4ah,0h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^89
MR_SET_CONST ?MRC_1E90,+,298,22,0fb58h,7849h,4aceh,3a5fh,4abh,48a0h,4065h,0c723h,0e64ch,0d781h,8d59h,0b87fh,0cddch,8000h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^90
MR_SET_CONST ?MRC_1E91,+,302,22,9d17h,4b2dh,0cec0h,0e47bh,62ebh,0d64h,283fh,9c76h,6ff0h,6b0h,0f858h,134fh,0e0a9h,0d000h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^91
MR_SET_CONST ?MRC_1E92,+,305,22,0c45dh,1df9h,4271h,1d9ah,3ba5h,0d0bdh,324fh,8394h,0bech,85dh,366eh,1823h,0d8d4h,4400h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^92
MR_SET_CONST ?MRC_1E93,+,308,22,0f574h,6577h,930dh,6500h,0ca8fh,44ech,7ee3h,6479h,0ee7h,0a74h,8409h,9e2ch,0cf09h,5500h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^93
MR_SET_CONST ?MRC_1E94,+,312,22,9968h,0bf6ah,0bbe8h,5f20h,7e99h,8b13h,0cf4eh,1ecbh,0a950h,6688h,0d286h,2dch,165h,0d520h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^94
MR_SET_CONST ?MRC_1E95,+,315,22,0bfc2h,0ef45h,6ae2h,76e8h,9e3fh,0edd8h,0c321h,0a67eh,93a4h,802bh,727h,8393h,1bfh,4a68h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^95
MR_SET_CONST ?MRC_1E96,+,318,22,0efb3h,0ab16h,0c59bh,14a2h,0c5cfh,0e94eh,0f3eah,101eh,388dh,0a035h,0c8f1h,6477h,0c22fh,1d02h,0h,0h,0h,0h,0h,0h,0h,0h ;; 10^96
MR_SET_CONST ?MRC_1E97,+,322,22,95d0h,4aeeh,3b80h,0ece5h,0bba1h,0f1d1h,5872h,4a12h,0e358h,8421h,9d96h,0decah,0d95dh,7221h,4000h,0h,0h,0h,0h,0h,0h,0h ;; 10^97
MR_SET_CONST ?MRC_1E98,+,325,22,0bb44h,5da9h,0ca61h,281fh,2a8ah,6e45h,0ae8eh,0dc97h,9c2eh,0a52ah,4fch,967dh,8fb4h,0cea9h,9000h,0h,0h,0h,0h,0h,0h,0h ;; 10^98
MR_SET_CONST ?MRC_1E99,+,328,22,0ea15h,7514h,3cf9h,7226h,0f52dh,9d7h,1a32h,93bdh,833ah,4e74h,863bh,0bc1ch,0f3a2h,253h,0f400h,0h,0h,0h,0h,0h,0h,0h ;; 10^99
MR_SET_CONST ?MRC_1E100,+,332,22,924dh,692ch,0a61bh,0e758h,593ch,2626h,705fh,9c56h,7204h,7108h,0d3e5h,5592h,1845h,4174h,7880h,0h,0h,0h,0h,0h,0h,0h ;; 10^100
MR_SET_CONST ?MRC_1E101,+,335,22,0b6e0h,0c377h,0cfa2h,0e12eh,6f8bh,2fb0h,0c77h,836ch,0e85h,8d4bh,8deh,0aaf6h,9e56h,91d1h,96a0h,0h,0h,0h,0h,0h,0h,0h ;; 10^101
MR_SET_CONST ?MRC_1E102,+,338,22,0e498h,0f455h,0c38bh,997ah,0b6dh,0fb9ch,0f95h,6447h,1226h,0f09dh,0cb16h,55b4h,45ech,3645h,0fc48h,0h,0h,0h,0h,0h,0h,0h ;; 10^102
MR_SET_CONST ?MRC_1E103,+,342,22,8edfh,98b5h,9a37h,3fech,4724h,0bd41h,89bdh,5each,6b58h,5662h,9eedh,0f590h,0abb3h,0a1ebh,0bdadh,0h,0h,0h,0h,0h,0h,0h ;; 10^103
MR_SET_CONST ?MRC_1E104,+,345,22,0b297h,7ee3h,0c5h,0fe7h,58edh,0ec91h,0ec2ch,0b657h,862eh,6bfbh,46a9h,72f4h,0d6a0h,8a66h,0ad18h,4000h,0h,0h,0h,0h,0h,0h ;; 10^104
MR_SET_CONST ?MRC_1E105,+,348,22,0df3dh,5e9bh,0c0f6h,53e1h,2f29h,67b6h,6737h,0e3edh,67bah,6fah,1853h,0cfb2h,0c48h,0ad00h,585eh,5000h,0h,0h,0h,0h,0h,0h ;; 10^105

;;/* rounded values (to nearest even) */
MR_SET_CONST ?MRC_1E200,+,664,22,0a738h,0c6beh,0bb12h,0d16ch,0b428h,0f8ach,165h,61dbh,40a0h,0f74ch,0da22h,1398h,3476h,9efh,9249h,0c8feh,0edd3h,634h,26a2h,0a304h,4f43h,0ef44h ;; 10^200
MR_SET_CONST ?MRC_1E300,+,996,22,0bf21h,0e440h,3ach,0dd2ch,0e047h,0a63h,0e6bdh,56c3h,5252h,2c08h,4fc8h,0e10eh,2b8eh,0df42h,6a96h,0c9b7h,0a255h,0f451h,0eadah,4608h,4ach,0ece8h ;; 10^300
MR_SET_CONST ?MRC_1E400,+,1328,22,0da76h,3fc8h,0cb9fh,0f9e5h,8e67h,937dh,0e0bbh,0e1c6h,0db72h,0a2c1h,6f12h,0c7fah,8c85h,0c5e0h,0a857h,0d6d9h,0c018h,72e8h,5bdfh,0a809h,72eh,735h ;; 10^400
MR_SET_CONST ?MRC_1E500,+,1660,22,0f9b2h,0ff64h,9b86h,95d7h,71a5h,8a83h,9043h,0c752h,9665h,0d2f3h,30f1h,7a7dh,0ed13h,0f15ah,1de3h,2f4ah,940ah,7a30h,0c3dfh,0a3b2h,37cbh,72bh ;; 10^500
MR_SET_CONST ?MRC_1E600,+,1993,22,8eb3h,9714h,297eh,0fb27h,0bcafh,0dba9h,6ebch,0b609h,46e8h,1644h,43a0h,87bh,6ae0h,308bh,31efh,0a4f5h,0d485h,0c818h,9c29h,0d294h,0e33ch,87d1h ;; 10^600
MR_SET_CONST ?MRC_1E700,+,2325,22,0a31bh,259ch,0fa50h,498fh,7478h,0a3cbh,0ba44h,0ec48h,8296h,69dfh,4adh,0c7efh,0dfd8h,0ba52h,0ccb2h,0d493h,17dh,0fa8ah,8aaeh,0a4f2h,0db3eh,1c83h ;; 10^700
MR_SET_CONST ?MRC_1E800,+,2657,22,0ba6dh,9b40h,0d7cch,9ecch,0df14h,3bbeh,4629h,1876h,0d9f9h,22f5h,0d6b0h,23a3h,0b7bch,579eh,9a5ah,1a51h,0d139h,0d72bh,336ah,0a42eh,17eeh,9f5fh ;; 10^800
MR_SET_CONST ?MRC_1E900,+,2989,22,0d515h,0c434h,4c1eh,8ef2h,9158h,61c3h,76f9h,0d550h,8212h,0fd06h,0affah,17a6h,6984h,10a4h,162bh,0feebh,77adh,409ch,0b184h,3a34h,7bb7h,10e9h ;; 10^900
MR_SET_CONST ?MRC_1E1000,+,3321,22,0f38dh,0b1f9h,0dd3dh,0ac05h,78d2h,9695h,39bch,0b6d2h,0afa1h,0f2ach,0ab8ch,0b1e8h,0fa3bh,3cd9h,14edh,66a8h,851ah,0cbc4h,4875h,7bf5h,0fc57h,34ddh ;; 10^1000
MR_SET_CONST ?MRC_1E2000,+,6643,22,0e7b6h,4e4dh,0e2fch,4251h,4a72h,9f6eh,4aafh,0abe8h,0f7d3h,0c138h,0c0b5h,57e9h,0ab8dh,0ce4bh,0bb1ah,58f8h,4219h,7134h,983bh,0ae3h,36cbh,0df3dh ;; 10^2000
MR_SET_CONST ?MRC_1E3000,+,9965,22,0dc72h,4cd4h,4411h,0af53h,37b2h,4bf1h,0b205h,0e08ch,2c95h,2765h,0c007h,29f0h,90dh,7cd9h,6f6fh,1c64h,991eh,0e0b0h,56abh,2608h,7f9ah,4afh ;; 10^3000
MR_SET_CONST ?MRC_1E4000,+,13287,22,0d1bah,8323h,0fe55h,8c61h,0d5ch,82a2h,8661h,4f3eh,0c255h,5823h,0c55h,0f78h,930h,88d8h,0cc8fh,6622h,0ef18h,6802h,2598h,322h,66e9h,0d763h ;; 10^4000


;/* x is expr32: 0 <= x <= 4999 */
MR_GET_10pX macro r,x,n:=<MREAL_XDIM>
	IF x LT 0
		.err <fatal>
		MR_SET_ZERO r,n
		EXITM
	ELSEIF x GT 4999
		MR_RAW_SET_N r,+Infinity,,n
		EXITM
	ELSEIF x LE 100
		MR_CONVERT r,@CatStr(<?MRC_1E>,%x),@CatStr(<MREAL_?MRC_1E>,%x,<_nSig>),n,MRRM_ROUND_TO_EVEN,-1
		EXITM
	ENDIF	
	mrgtpx_txt TEXTEQU %(x)
	mrgtpx_size SIZESTR mrgtpx_txt
	
	mrgtpx_deca SUBSTR mrgtpx_txt,mrgtpx_size-1,2
	MR_CONVERT r,@CatStr(<?MRC_1E>,%(mrgtpx_deca)),@CatStr(<MREAL_?MRC_1E>,%(mrgtpx_deca),<_nSig>),n,MRRM_ROUND_TO_EVEN,-1
	
	mrgtpx_hecto SUBSTR mrgtpx_txt,mrgtpx_size-2,1
	mrgtpx_hecto_n = @CatStr(<MREAL_?MRC_1E>,%mrgtpx_hecto*100,<_nSig>)
	MR_XMUL r,r,@CatStr(<?MRC_1E>,%(mrgtpx_hecto*100)),n,n,mrgtpx_hecto_n,MRRM_ROUND_TO_EVEN
	IF mrgtpx_size LT 4
		EXITM
	ENDIF
	
	mrgtpx_kilo SUBSTR mrgtpx_txt,1,1
	mrgtpx_kilo_n = @CatStr(<MREAL_?MRC_1E>,%(mrgtpx_kilo*1000),<_nSig>)
	MR_XMUL r,r,@CatStr(<?MRC_1E>,%(mrgtpx_kilo*1000)),n,n,mrgtpx_kilo_n,MRRM_ROUND_TO_EVEN
	EXITM
endm


;;/**
;; * ?MRLUT_PT2PB is used to get the number of needed 
;; * precision WORDs from the number of decimal digits.
;; * The hexadecimal encoded BYTEs does have the value:
;; *     byte[e-1] = Ceiling(Ceiling(Log2(10^e-1))/16) with 0 < e <= maxexp 
;; */
?MRLUT_PT2PB TEXTEQU <010101010202020202030303030304040404040505050505060606060707070707080808080809090909090a0a0a0a0a0b0b0b0b0c0c0c0c0c0d0d0d0d0d0e0e0e0e0e0f0f0f0f0f101010101011111111121212121213131313131414141414151515151516161616>
?MRLUT_PT2PB_MAXEXP SIZESTR ?MRLUT_PT2PB
?MRLUT_PT2PB_MAXEXP = ?MRLUT_PT2PB_MAXEXP / 2
?MRLUT_PT2PB_MAX_N = 16h
?PT2PB macro pwr10
	?PT2PB_I = (pwr10-1)*2+1
	?PT2PB_TVAL SUBSTR ?MRLUT_PT2PB,?PT2PB_I,2
	?PT2PB_TVAL TEXTEQU <0>,?PT2PB_TVAL,<h>
	EXITM %?PT2PB_TVAL
endm


;;/* Internal - do not use */
_MR_FROM_HEX_FP_ macro dest,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>
	
	MREAL_INEXACT = 0
	
	;;/* check for +-zero */
	mrfhfp_zero = 0
	mrfhfp_txt TEXTEQU @SubStr(%sff_hex_digits,1,2),<h>
	IFE mrfhfp_txt AND 7h
		mrfhfp_zero = -1
	%	FORC char,<@SubStr(%sff_hex_digits,3,)>
			IFDIF <&char>,<0>
				mrfhfp_zero = 0
				EXITM
			ENDIF
		ENDM
	ENDIF
	IF mrfhfp_zero
		;;/* case: +-zero */
		MR_SET_ZERO dest,n
		EXITM
	ENDIF
	mrfhfp_special = 0
	IF sff_flag AND (SFF_HEX_REAL4 OR SFF_HEX_REAL8)
		;;/* case: binary32 or binary64 */
		mrfhfp_texp SUBSTR sff_hex_digits,2,3
		mrfhfp_tbits SUBSTR sff_hex_digits,4+(((sff_flag AND SFF_HEX_REAL8) NE 0) AND 1)
		mrfhfp_exp = @CatStr(<0>,%mrfhfp_texp,<h>)
		mrfhfp_sign = (mrfhfp_exp AND 800h) NE 0
		mrfhfp_msk = (07f8h AND ((sff_flag AND SFF_HEX_REAL4) NE 0)) OR (07ffh AND ((sff_flag AND SFF_HEX_REAL8) NE 0))
		IF (mrfhfp_exp AND mrfhfp_msk) EQ mrfhfp_msk
			;;/* case: NaN */
			mrfhfp_special = 1
		ELSEIFE mrfhfp_exp AND mrfhfp_msk
			;;/* case: denormal\subnormal number */
			mrfhfp_special = 2
		ELSEIF sff_flag AND SFF_HEX_REAL4
			;;/* case: normal binary32. Store hidden bit (integer bit); get exponent */
			mrfhfp_tbits TEXTEQU @SubStr(<89abcdef01234567>,%1+@CatStr(<0>,@SubStr(%mrfhfp_tbits,2,1),<h>),1),@SubStr(%mrfhfp_tbits,3)
			mrfhfp_exp = (mrfhfp_exp SHR 3 AND 0ffh) - 127
		ELSE
			;;/* case: normal binary64. Get exponent (hidden bit is later processed) */
			mrfhfp_exp = (mrfhfp_exp AND 07ffh) - 1023
		ENDIF
	ELSEIF sff_flag AND SFF_HEX_REAL10
		;;/* case: double extended precision */
		mrfhfp_texp SUBSTR sff_hex_digits,2,4
		mrfhfp_tbits SUBSTR sff_hex_digits,6
		mrfhfp_exp = @CatStr(<0>,%mrfhfp_texp,<h>)
		mrfhfp_sign = (mrfhfp_exp AND 8000h) NE 0
		IF (mrfhfp_exp AND 7fffh) EQ 7fffh
			;;/* case: NaN */
			mrfhfp_special = 1
		ELSEIFE mrfhfp_exp AND 7fffh
			;;/* case denormal\subnormal number */
			mrfhfp_special = 2
		ELSE
			;;/* case: normal number */
			mrfhfp_exp = (mrfhfp_exp AND 07fffh) - 16383
		ENDIF
		mrfhfp_txt SUBSTR mrfhfp_tbits,1,1
		;;/* test explict integer bit */
		IF mrfhfp_special EQ 0 AND (@CatStr(<0>,%mrfhfp_txt,<h>) AND 8h) EQ 0
			;;/* case: unnormal number */
			mrfhfp_special = 2
		ENDIF
	ELSE
		.err <fatal: invalid parameter>
		MR_RAW_SET_N dest,NaN,,n
		EXITM
	ENDIF
	
	IF mrfhfp_special EQ 2
		;;/**
		;; * case: denormal\subnormal number.
		;; * This values could be converted, but the support for 
		;; * denormal values as input is intentionally left out.
		;; */
		.err <hexadecimal floating point initializer is denormal/subnormal>
		MR_SET_ZERO dest,n
		EXITM
	ENDIF
	
	;;/* store mantissa bits in MREAL mantissa */
	mrfhfp_size SIZESTR mrfhfp_tbits
	mrfhfp_n = 0
	WHILE mrfhfp_size GT 4
		mrfhfp_txt SUBSTR mrfhfp_tbits,1,4
		@CatStr(<MREAL_&dest&_w>,%mrfhfp_n) = @CatStr(<0>,%mrfhfp_txt,<h>)
		mrfhfp_tbits SUBSTR mrfhfp_tbits,5
		mrfhfp_size SIZESTR mrfhfp_tbits
		mrfhfp_n = mrfhfp_n + 1
	ENDM
	IF mrfhfp_size
		mrfhfp_txt SUBSTR <000h>,mrfhfp_size
		@CatStr(<MREAL_&dest&_w>,%mrfhfp_n) = @CatStr(<0>,%mrfhfp_tbits,%mrfhfp_txt)
		mrfhfp_n = mrfhfp_n + 1
	ENDIF
	;;/* At this point mrfhfp_n holds the number of precision WORDs */
	
	IF sff_flag AND SFF_HEX_REAL8
		;;/* case: binary64. Prepend hidden bit (integer bit) */
		MR_RSHIFT_1 dest,mrfhfp_n
		MREAL_&dest&_w0 = MREAL_&dest&_w0 OR 8000h
	ENDIF
	
	IFE mrfhfp_special
		;;/**
		;; * Case: normal number.
		;; * Set exponent and sign flag of MREAL value. The mantissa
		;; * is already filled.
		;; */
		MREAL_&dest&_exp = mrfhfp_exp+1	;; IEEE-exponent to MREAL -> +1
		MREAL_&dest&_flg = MREAL_FLG_SIGN AND mrfhfp_sign
		
		;;/* convert MREAL value to target precision */
		MR_CONVERT dest,dest,%mrfhfp_n,n,rm
		EXITM
	ELSEIF mrfhfp_special EQ 1
		;;/**
		;; * Process NaN.
		;; * Test IEEE-mantissa for: 1.000... => Infinity
		;; */
		IF MREAL_&dest&_w0 EQ 8000h
			mrfhfp_cntr = 1
			WHILE mrfhfp_cntr LT mrfhfp_n
				IF @CatStr(<MREAL_&dest&_w>,%mrfhfp_cntr)
					EXITM
				ENDIF
				mrfhfp_cntr = mrfhfp_cntr + 1
			ENDM
			IF mrfhfp_cntr EQ mrfhfp_n
				;;/* case: +-Infinity */
				MR_RAW_SET_N dest,@CatStr(@SubStr(<-+>,2+mrfhfp_sign,1),<Infinity>),,n
				EXITM
			ENDIF
		ENDIF
		;;/* case: any NaN */
		MR_RAW_SET_N dest,NaN,,n
		EXITM
	ENDIF
	
endm

;; internal - do not use 
_MR_FROM_IEEE754_08_HEX_SEQ_ macro dest,txt,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>
	
	mrfhs_done = 0
	mrfhs_pos INSTR <&txt>,<,>
	IF mrfhs_pos
		EXITM
	ENDIF
	;;/* trim literal */
	mrfhs_txt TEXTEQU <>
	FOR lit,<&txt>
		mrfhs_txt TEXTEQU <&lit>
		EXITM
	ENDM
	mrfhs_size SIZESTR mrfhs_txt
	IF mrfhs_size LT 3
		;;/* case: blank argument or invalid size */
		EXITM
	ENDIF

	mrfhs_pos = 1
	;;/* check for sign */
	mrfhs_tsign SUBSTR mrfhs_txt,1,1
	IFIDN mrfhs_tsign,<+>
		mrfhs_sign = 0
		mrfhs_pos = mrfhs_pos + 1
	ELSEIFIDN mrfhs_tsign,<->
		mrfhs_sign = -1
		mrfhs_pos = mrfhs_pos + 1
	ELSEIFIDN mrfhs_tsign,<0>
		mrfhs_sign = 0
	ELSE
		;;/* invalid character */
		EXITM
	ENDIF
	
	;;/* test for hexIndicator */
	IF mrfhs_pos+1 GT mrfhs_size
		;;/* case: no room for hexIndicator */
		EXITM
	ENDIF
	mrfhs_hexIndicator SUBSTR mrfhs_txt,mrfhs_pos,2
	IFDIFI mrfhs_hexIndicator,<0x>
		;;/* case: no hexIndicator */
		EXITM
	ENDIF
	mrfhs_pos = mrfhs_pos + 2
	IF mrfhs_pos GT mrfhs_size
		;;/* case: no room for digits */
		EXITM
	ENDIF
	
	;;/* check and record hex digits */
	mrfhs_hexp = 0
	mrfhs_dot = 0
	mrfhs_res = 0
	mrfhs_hdigits TEXTEQU <>
%	FORC char,<@SubStr(%mrfhs_txt,mrfhs_pos,)>
		mrfhs_pos2 INSTR <0123456789abcdefABCDEF>,<&char>
		IF mrfhs_pos2
			;;/* discard leading zeros */
			IFB mrfhs_hdigits
				IF mrfhs_pos2 GT 1
					mrfhs_hdigits TEXTEQU mrfhs_hdigits,<&char>
				ENDIF
			ELSE
				mrfhs_hdigits TEXTEQU mrfhs_hdigits,<&char>
			ENDIF
			mrfhs_hexp = mrfhs_hexp - mrfhs_dot
		ELSEIFIDN <&char>,<.>
			IF mrfhs_dot
				;;/* case: second dot found -> invalid format */
				mrfhs_res = -1
				EXITM
			ELSE
				mrfhs_dot = 1
			ENDIF
		ELSEIFIDNI <&char>,<p>
			;;/* case: exponent found */
			mrfhs_res = 1
			EXITM
		ELSE
			;;/* case: invalid character */
			mrfhs_res = -1
			EXITM
		ENDIF
		mrfhs_pos = mrfhs_pos + 1
	ENDM
	IF mrfhs_res EQ -1
		EXITM
	ELSEIF mrfhs_res EQ 1
		mrfhs_thexp TEXTEQU <>
		mrfhs_hexp_sign = 1
		
		;;/* read decimal exponent */
		mrfhs_pos = mrfhs_pos + 1
		IF mrfhs_pos GT mrfhs_size
			;;/* case: no room for exponent */
			EXITM
		ENDIF
		mrfhs_tsign SUBSTR mrfhs_txt,mrfhs_pos,1
		IFIDNI mrfhs_tsign,<+>
			mrfhs_hexp_sign = 1
			mrfhs_pos = mrfhs_pos + 1
		ELSEIFIDNI mrfhs_tsign,<->
			mrfhs_hexp_sign = -1
			mrfhs_pos = mrfhs_pos + 1
		ENDIF
		IF mrfhs_pos GT mrfhs_size
			;;/* case: no room for exponent */
			EXITM
		ENDIF
		
		;;/* check and record exponent digits */
		mrfhs_res = 0
	%	FORC char,<@SubStr(%mrfhs_txt,mrfhs_pos,)>
			mrfhs_pos2 INSTR <0123456789>,<&char>
			IF mrfhs_pos2
				;;/* discard leading zeros */
				IFB mrfhs_thexp
					IF char
						mrfhs_thexp TEXTEQU mrfhs_thexp,<&char>
					ENDIF
				ELSE
					mrfhs_thexp TEXTEQU mrfhs_thexp,<&char>
				ENDIF
			ELSE
				;;/* case: invalid character */
				mrfhs_res = -1
				EXITM
			ENDIF
			mrfhs_pos = mrfhs_pos + 1
		ENDM
		IF mrfhs_res EQ -1
			EXITM
		ENDIF
		IFB mrfhs_thexp
			mrfhs_thexp TEXTEQU <0>
		ENDIF
		;;/* check exponent limits */
		mrfhs_size2 SIZESTR mrfhs_thexp
		IF mrfhs_size2 GT 8
			.err <exponet value to large: must be in range: -99999999 to +99999999>
			MR_RAW_SET_N dest,NaN,,n
			mrfhs_done = -1
			EXITM
		ENDIF
		;;/* calculate binary exponent+4 */
		mrfhs_size2 SIZESTR mrfhs_hdigits
		mrfhs_exp = (mrfhs_size2 + mrfhs_hexp)*4 + mrfhs_hexp_sign*(mrfhs_thexp)
	ELSE
		;;/* case: no exponent -> calculate binary exponent+4 */
		mrfhs_size2 SIZESTR mrfhs_hdigits
		mrfhs_exp = (mrfhs_size2 + mrfhs_hexp)*4
	ENDIF

	IFB mrfhs_hdigits
		;;/* case: mantissa is zero */
		MR_SET_ZERO dest,n
		mrfhs_done = -1
		EXITM
	ENDIF
	
	;;/* store sign and preliminary exponent */
	MREAL_&dest&_flg = mrfhs_sign AND MREAL_FLG_SIGN
	MREAL_&dest&_exp = mrfhs_exp
	
	;;/* convert hex digits to mantissa WORDs */
	mrfhs_size SIZESTR mrfhs_hdigits
	mrfhs_n = 0
	WHILE mrfhs_size GT 4
		mrfhs_txt SUBSTR mrfhs_hdigits,1,4
		@CatStr(<MREAL_&dest&_w>,%mrfhs_n) = @CatStr(<0>,%mrfhs_txt,<h>)
		mrfhs_hdigits SUBSTR mrfhs_hdigits,5
		mrfhs_size SIZESTR mrfhs_hdigits
		mrfhs_n = mrfhs_n + 1
	ENDM
	IF mrfhs_size
		mrfhs_txt SUBSTR <000h>,mrfhs_size
		@CatStr(<MREAL_&dest&_w>,%mrfhs_n) = @CatStr(<0>,%mrfhs_hdigits,%mrfhs_txt)
		mrfhs_n = mrfhs_n + 1
	ENDIF
	
	MR_NORMALIZE_ACCUM dest,0,mrfhs_n
	MR_CONVERT dest,dest,mrfhs_n,n,rm
	mrfhs_done = -1
endm

MR_FROM_STR macro dest:req,txt:req,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>
	
	MREAL_INEXACT = 0
	
	IFE @ScanForFlt(1,txt,blanks)
		;;/* if found, process IEEE754-2008 hexadecimal-significant character sequences */
		_MR_FROM_IEEE754_08_HEX_SEQ_ dest,txt,rm,n
		IFE mrfhs_done
			.err <invalid input: &txt>
			MR_RAW_SET_N dest,NaN,,n
		ENDIF
		EXITM
	ENDIF
	
	IF sff_type EQ 1
		IF sff_flag AND (SFF_HEX_REAL4 OR SFF_HEX_REAL8 OR SFF_HEX_REAL10)
			;;/**
			;; * case: hexadecimal floating point initializer.
			;; * Due to @ScanForFlt the initializers have always a leading zero. 
			;; */
			_MR_FROM_HEX_FP_ dest,rm,n
			EXITM
		ELSE
			;;/**
			;; * case: floating point number
			;; */
			mrscvt_digits TEXTEQU sff_pre_decimal,sff_fract_digits
			mrscvt_dexp SIZESTR sff_pre_decimal
			mrscvt_dexp = mrscvt_dexp - 1
			IF sff_flag AND SFF_EXPONENT
				mrscvt_dexp = mrscvt_dexp  + @CatStr(%sff_exp_sign,%sff_exp_digits)
			ENDIF
		ENDIF
	ELSEIF sff_type EQ 2
		IF sff_flag AND SFF_HEX_SUFFIX
			;;/**
			;; * case: hexadecimal integer
			;; */
			mrscvt_digits TEXTEQU sff_hex_digits
		ELSE
			;;/**
			;; * case: decimal integer
			;; */
			mrscvt_digits TEXTEQU sff_pre_decimal
		ENDIF
		mrscvt_dexp SIZESTR mrscvt_digits
		mrscvt_dexp = mrscvt_dexp - 1
	ENDIF
	
	;;/* get sign (0,-1) */
	IF sff_flag AND SFF_SIGN
		mrscvt_sign = 1-@InStr(1,<+->,%sff_sign)
	ELSE
		mrscvt_sign = 0
	ENDIF

	;;/**
	;; * remove leading zeros and 
	;; * correct exponent.
	;; */
	mrscvt_size SIZESTR mrscvt_digits
	mrscvt_pos = 1
%	FORC char,<&mrscvt_digits>
		IFDIF <&char>,<0>
			EXITM
		ENDIF
		mrscvt_pos = mrscvt_pos + 1
	ENDM
	IF mrscvt_pos GT mrscvt_size
		;;/* case: mantissa is zero */
		MR_SET_ZERO dest,n
		EXITM
	ELSE
		mrscvt_digits SUBSTR mrscvt_digits,mrscvt_pos
		mrscvt_dexp = mrscvt_dexp - mrscvt_pos+1
	ENDIF
	
	;;/* remove trailing zeros */
	mrscvt_size SIZESTR mrscvt_digits
	mrscvt_pos = mrscvt_size
	REPEAT mrscvt_size
		mrscvt_char SUBSTR mrscvt_digits,mrscvt_pos,1
		IFDIF mrscvt_char,<0>
			EXITM
		ENDIF
		mrscvt_pos = mrscvt_pos - 1
	ENDM
	IF mrscvt_pos NE mrscvt_size
		mrscvt_digits SUBSTR mrscvt_digits,1,mrscvt_pos
		mrscvt_size SIZESTR mrscvt_digits
	ENDIF
	
	IF sff_type EQ 2 AND (sff_flag AND SFF_HEX_SUFFIX) NE 0
		;;/**
		;; * continue case: hexadecimal integer.
		;; *  - store mantissa bits
		;; *  - normalize if needed
		;; *  - convert to target precision (zero extend or round)
		;; */
		mrscvt_i = 0
		WHILE mrscvt_size GT 4
			mrscvt_txt SUBSTR mrscvt_digits,1,4
			@CatStr(<MREAL_&dest&_w>,%mrscvt_i) = @CatStr(<0>,%mrscvt_txt,<h>)
			mrscvt_digits SUBSTR mrscvt_digits,5
			mrscvt_size SIZESTR mrscvt_digits
			mrscvt_i = mrscvt_i + 1
		ENDM
		IF mrscvt_size
			mrscvt_txt SUBSTR <000h>,mrscvt_size
			@CatStr(<MREAL_&dest&_w>,%mrscvt_i) = @CatStr(<0>,%mrscvt_digits,%mrscvt_txt)
			mrscvt_i = mrscvt_i + 1
		ENDIF
		MREAL_&dest&_flg = mrscvt_sign AND MREAL_FLG_SIGN
		MREAL_&dest&_exp = (mrscvt_dexp+1)*4
		MR_NORMALIZE_ACCUM dest,0,mrscvt_i
		MR_CONVERT dest,dest,mrscvt_i,n,rm
		EXITM
	ENDIF
	
	
	mrscvt_char SUBSTR mrscvt_digits,1,1
	IF (mrscvt_dexp GE 0 AND (mrscvt_dexp LT 9 OR mrscvt_dexp EQ 9 AND mrscvt_char LE 3)) AND mrscvt_dexp+1-mrscvt_size GE 0
		;;/**
		;; * case: integer range 0...3999999999
		;; */
		
		;;/* attach zeros to normalized number */
		IF mrscvt_dexp+1-mrscvt_size
			mrscvt_digits TEXTEQU mrscvt_digits,@SubStr(<000000000>,1,1+mrscvt_dexp-mrscvt_size)
		ENDIF
		;;/* add sign */
		mrscvt_digits TEXTEQU @SubStr(<- >,2+mrscvt_sign,1),mrscvt_digits
		;;/* convert */
		MR_FROM_EXPR32 dest,%mrscvt_digits,rm,n
		EXITM
	ENDIF
	
	;;/* truncate decimal digits if to large! */
	IF mrscvt_size GT ?MRLUT_PT2PB_MAXEXP
		mrscvt_digits SUBSTR mrscvt_digits,1,?MRLUT_PT2PB_MAXEXP
		mrscvt_size SIZESTR mrscvt_digits
		%echo WARNING: @CatStr(%@FileCur,<, line:> %@Line) -> too much significant digits - value truncated
	ENDIF
	
	;;/**
	;; * Convert decimal digits. Pseudo code:
	;; * 
	;; *  Input variables {
	;; *    digits   : is array (0 to nDigits-1) of unsigned integer; // containing the decimal digits
	;; *    nDigits  : is integer;                                    // number of digits
	;; *  }
	;; *  Local variables {
	;; *    uiTmp    : is unsigned integer range 0 to 2^32-1;
	;; *    p,p2,nd  : is integer;                                    // p is current precision, nd the number of converted digits.
	;; *    b        : is MREAL;
	;; *  }
	;; *
	;; *   nd = modulo(nDigits,9);
	;; *   if( nd != 0 ){
	;; *      uiTmp = convert digits[0 to nd-1] to unsigned integer;
	;; *      p = Ceiling(Ceiling(Log2(10^nd-1))/16);                 // get the precision that is needed to hold the integer (exact).
	;; *      b = convert uiTmp to MREAL of precision p;
	;; *   }else{
	;; *      b = 0;                                                  // any precision.
	;; *      p = 1;
	;; *   }
	;; *   while (nDigits > nd) {
	;; *      p2 = Ceiling(Ceiling(Log2(10^(nd+9)-1))/16);            // get the precision that is needed to hold the integer (exact).
	;; *      convert b from p to p2 bit precision;                   // zero extend.
	;; *      p = p2;
	;; *      uiTmp = convert digits[nd to nd+8] to unsigned integer; // convert 9-digit-integer
	;; *      mrTmp = convert uiTmp to MREAL of precision p;
	;; *      b = b * 10^9 + mrTmp;
	;; *      nd = nd + 9;
	;; *   }
	;; *   result = b;
	;; * -----------------
	;; * Addendum 11042014: the loop body has been optimized with MR_XMUL to 
	;; *          significantly reduce the number of needed multiplications.
	;; */
	MR_PUSH_STATE MREAL_TEST_INEXACT
	MREAL_TEST_INEXACT = 0
	mrscvt_nd = mrscvt_size MOD 9
	IF mrscvt_nd
		mrscvt_p = ?PT2PB(%mrscvt_nd)
		mrscvt_d SUBSTR mrscvt_digits,1,mrscvt_nd
		MR_RAW_FROM_VALUE ?s2mr,%mrscvt_d,mrscvt_p
	ELSE
		mrscvt_p = 1
		MR_SET_ZERO ?s2mr,1
	ENDIF
;; 11042014: old loop body
;;		mrscvt_pnew = ?PT2PB(%mrscvt_nd+9)
;;		MR_CONVERT ?s2mr,?s2mr,mrscvt_p,mrscvt_pnew
;;		mrscvt_p = mrscvt_pnew
;;		mrscvt_d SUBSTR mrscvt_digits,mrscvt_nd+1,9
;;		MR_RAW_FROM_VALUE ?s2mrTmp,%mrscvt_d,mrscvt_p
;;		MR_MUL ?s2mr,?s2mr,?MRC_1E9,MRRM_TRUNCATE,mrscvt_p
;;		MR_ADD ?s2mr,?s2mr,?s2mrTmp,MRRM_TRUNCATE,mrscvt_p
;;		mrscvt_nd = mrscvt_nd + 9
	WHILE mrscvt_size-mrscvt_nd GT 0
		mrscvt_pnew = ?PT2PB(%mrscvt_nd+9)
		mrscvt_d SUBSTR mrscvt_digits,mrscvt_nd+1,9
		MR_RAW_FROM_VALUE ?s2mrTmp,%mrscvt_d,mrscvt_pnew
		MR_XMUL ?s2mr,?s2mr,?MRC_1E9,%mrscvt_p+2,mrscvt_p,2,MRRM_TRUNCATE
		MR_CONVERT ?s2mr,?s2mr,%mrscvt_p+2,mrscvt_pnew
		mrscvt_p = mrscvt_pnew
		MR_ADD ?s2mr,?s2mr,?s2mrTmp,MRRM_TRUNCATE,mrscvt_p
		mrscvt_nd = mrscvt_nd + 9
	ENDM
	MR_MOV dest,?s2mr,%mrscvt_p
	MR_POP_STATE
	
	;;/* set sign */
	MREAL_&dest&_flg = mrscvt_sign AND MREAL_FLG_SIGN
	
	;;/* get decimal exponent */
	mrscvt_dexp = mrscvt_dexp - (mrscvt_size-1)
	
	;;/**
	;; * Handel decimal exponent. Possible cases:
	;; *   - dexp == 0
	;; *     Number is an integer -> round if needed.
	;; *
	;; *   - -emax <= dexp < 0
	;; *     Divide value by 10^dexp.
	;; *   
	;; *   - emax >= dexp > 0
	;; *     Multiply value by 10^dexp.
	;; *
	;; *   - dexp > emax
	;; *     approximation: construct 10^dexp and multiply with value.
	;; *
	;; *   - dexp < -emax
	;; *     approximation: construct 10^dexp and divide value.
	;; *
	;; */
	IF mrscvt_dexp EQ 0
		MR_CONVERT dest,dest,mrscvt_p,n
	ELSEIF mrscvt_dexp GE -?MRLUT_PT2PB_MAXEXP AND mrscvt_dexp LT 0
		IF mrscvt_p LT @CatStr(<MREAL_?MRC_1E>,%-mrscvt_dexp,<_nSig>)
			mrscvt_p2 = @CatStr(<MREAL_?MRC_1E>,%-mrscvt_dexp,<_nSig>)
		ELSE
			mrscvt_p2 = mrscvt_p
		ENDIF
		IF mrscvt_p2 LT n
			mrscvt_p2 = n
		ENDIF
		IF n GT mrscvt_p2
			MR_CONVERT ?MSCP10,@CatStr(<?MRC_1E>,%-mrscvt_dexp),@CatStr(<MREAL_?MRC_1E>,%-mrscvt_dexp,<_nSig>),n
			MR_CONVERT dest,dest,mrscvt_p2,n,rm
			MR_DIV dest,dest,?MSCP10,rm,n
		ELSE
			MR_CONVERT ?MSCP10,@CatStr(<?MRC_1E>,%-mrscvt_dexp),@CatStr(<MREAL_?MRC_1E>,%-mrscvt_dexp,<_nSig>),mrscvt_p2
			MR_CONVERT dest,dest,mrscvt_p,mrscvt_p2
			MR_DIV dest,dest,?MSCP10,rm,mrscvt_p2,n
		ENDIF
	ELSEIF mrscvt_dexp LE ?MRLUT_PT2PB_MAXEXP AND mrscvt_dexp GT 0
		IF n GT mrscvt_p+@CatStr(<MREAL_?MRC_1E>,%mrscvt_dexp,<_nSig>)
			mrscvt_p2 = mrscvt_p+@CatStr(<MREAL_?MRC_1E>,%mrscvt_dexp,<_nSig>)
		ELSE
			mrscvt_p2 = n
		ENDIF
		MR_XMUL dest,dest,@CatStr(<?MRC_1E>,%mrscvt_dexp),mrscvt_p2,mrscvt_p,@CatStr(<MREAL_?MRC_1E>,%mrscvt_dexp,<_nSig>),rm
		IF n NE mrscvt_p2
			MR_CONVERT dest,dest,mrscvt_p2,n
		ENDIF
	ELSEIF mrscvt_dexp GT 0 AND mrscvt_dexp LE 4999
		IF mrscvt_p LT n
			mrscvt_p2 = n+1
		ELSE
			mrscvt_p2 = mrscvt_p
		ENDIF
		MR_GET_10pX mrscvtTmp,%mrscvt_dexp,mrscvt_p2
		IF MREAL_mrscvtTmp_flg AND MREAL_FLG_NON_NUMERIC_TEST
			MR_RAW_SET_N dest,@CatStr(@SubStr(<-+>,2+mrscvt_sign,1),<Infinity>),,n
			MREAL_INEXACT = -2
			EXITM
		ENDIF
		MR_XMUL dest,dest,mrscvtTmp,n,%mrscvt_p,mrscvt_p2,rm
		MREAL_INEXACT = -2
	ELSEIF mrscvt_dexp LT 0 AND mrscvt_dexp GE -4999
		IF mrscvt_p LT n
			mrscvt_p2 = n+1
		ELSE
			mrscvt_p2 = mrscvt_p
		ENDIF
		MR_GET_10pX mrscvtTmp,%-mrscvt_dexp,mrscvt_p2
		IF MREAL_mrscvtTmp_flg AND MREAL_FLG_NON_NUMERIC_TEST
			MR_RAW_SET_N dest,@CatStr(@SubStr(<-+>,2+mrscvt_sign,1),<Infinity>),,n
			MREAL_INEXACT = -2
			EXITM
		ENDIF
		MR_CONVERT dest,dest,%mrscvt_p,mrscvt_p2		;; zero extend
		MR_DIV dest,dest,mrscvtTmp,rm,mrscvt_p2,n
		MREAL_INEXACT = -2
	ELSE
		.err <sorry - value to large or small for conversion>
		MR_RAW_SET_N dest,NaN,,n
	ENDIF
endm

;;/* declare some constants (precision = 33*16 bit, round to nearest even) */
;;/* Pi */
MR_SET_CONST ?MRC_PI,+,1,33,0c90fh,0daa2h,2168h,0c234h,0c4c6h,628bh,80dch,1cd1h,2902h,4e08h,8a67h,0cc74h,20bh,0bea6h,3b13h,9b22h,514ah,879h,8e34h,4ddh,0ef95h,19b3h,0cd3ah,431bh,302bh,0a6dh,0f25fh,1437h,4fe1h,356dh,6d51h,0c245h,0e486h
;;/* 1/Pi */
MR_SET_CONST ?MRC_RPI,+,-2,33,0a2f9h,836eh,4e44h,1529h,0fc27h,57d1h,0f534h,0ddc0h,0db62h,9599h,3c43h,9041h,0fe51h,63abh,0debbh,0c561h,0b724h,6e3ah,424dh,0d2e0h,649h,2eeah,9d1h,921ch,0fe1dh,0eb1ch,0b129h,0a73eh,0e882h,35f5h,2ebbh,4484h,0e99ch
;;/* exponential constant "e" */
MR_SET_CONST ?MRC_E,+,1,33,0adf8h,5458h,0a2bbh,4a9ah,0afdch,5620h,273dh,3cf1h,0d8b9h,0c583h,0ce2dh,3695h,0a9e1h,3641h,1464h,33fbh,0cc93h,9dceh,249bh,3ef9h,7d2fh,0e363h,630ch,75d8h,0f681h,0b202h,0aec4h,617ah,0d3dfh,1ed5h,0d5fdh,6561h,2434h
;;/* Pi/180 */
MR_SET_CONST ?MRC_DEG,+,-6,33,8efah,3512h,94e9h,0c8aeh,0ec5h,0f66eh,9485h,0c4d9h,0b7h,0aef5h,1b5h,0e6b8h,0e502h,0a9b4h,0c94ch,8512h,0b6f6h,1167h,8191h,1487h,10c5h,0c96h,9d51h,40c9h,60d4h,0a6b4h,9598h,0f1eeh,71b1h,370fh,3cabh,0eadch,5e3dh
;;/* 180/Pi */
MR_SET_CONST ?MRC_RAD,+,5,33,0e52eh,0e0d3h,1e0fh,0bdc3h,0a97h,537fh,40d2h,57d7h,3482h,0a25fh,7cbfh,2dch,0cda2h,7429h,0b138h,0d91h,698bh,3b01h,0ed3dh,708bh,8d6h,0e9f9h,1dceh,0b578h,0c55ah,12a0h,5922h,9330h,76f7h,1be0h,0c9b7h,585ah,0e884h
;;/* 1/log2(10) */
MR_SET_CONST ?MRC_RLDT,+,-2,33,9a20h,9a84h,0fbcfh,0f798h,8f89h,59ach,0b7ch,9178h,26adh,30c5h,43d1h,0f349h,8a5eh,6f26h,0b7cch,63cbh,286ah,2d81h,919fh,0abd0h,9e5ch,0bc73h,3471h,0bd12h,9147h,3495h,0b18bh,921eh,58b5h,27f5h,2552h,0d2cch,5f83h
;;/* 10 */
MR_SET_CONST ?MRC_TEN,+,3,33,0a000h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h,0h
;;/* 0 */
MR_SET_ZERO ?MRC_ZERO,33
;;/* 1.0 */
MR_RAW_SET_N ?MRC_ONE,+,0,33,08000h

;;/** 
;; * Load correctly rounded constant.
;; * Parameter    Description
;; *   r          result
;; *   name       constant name:
;; *              <one>      -> 1.0
;; *              <zero>     -> 0
;; *              <pi>       -> Pi = 3.141...
;; *              <rpi>      -> 1/Pi = 0.318309886...
;; *              <e>        -> exponential constant = 2.7182...
;; *              <deg>      -> Pi/180
;; *              <rad>      -> 180/Pi
;; *              <Infinity> -> Infinity
;; *              <max>      -> largest finite value for current precision and exponent settings
;; *              <min>      -> smallest finite value for current precision and exponent settings
;; *              <NaN>      -> not a number
;; *              <rldt>     -> 1/log2(10)
;; *              The constant names are not case-sensitive.
;; *              Except NaN, all constants can have a sign <+->.
;; *              Remarks that the name must not have leading or trailing blanks (unless using angle bracktes, MASM does trim macro arguments).
;; *   pwr2       This value is added to the binary exponent (MASM integer expression)
;; *   rm         rounding mode
;; *   n          precision. The current limit is 32 (=> 512 bit precision).
;; *
;; * Examples:
;; *   MR_LOAD_CONST r, -Pi     ; r = -Pi
;; *   MR_LOAD_CONST r, Pi,2    ; r = Pi*2^2 = 4*Pi
;; */
MR_LOAD_CONST macro r:req,name:req,pwr2:=<0>,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>
	
	MREAL_INEXACT = 0
	
	mrlc_sign = 0
	mrlc_name TEXTEQU <&name>
	mrlc_tsign TEXTEQU <>
	IF @SizeStr(<&name>) GT 1
		mrlc_tsign SUBSTR <&name>,1,1
		IFIDN mrlc_tsign,<+>
			mrlc_sign = 0
			mrlc_name SUBSTR <&name>,2
		ELSEIFIDN mrlc_tsign,<->
			mrlc_sign = -1
			mrlc_name SUBSTR <&name>,2
		ELSE
			mrlc_tsign TEXTEQU <>
		ENDIF
	ENDIF
	IFIDNI mrlc_name,<one>
		MR_RAW_SET_N r,@SubStr(<-+>,2+mrlc_sign,1),pwr2,n,08000h
		EXITM
	ELSEIFIDNI mrlc_name,<pi>
		mrlc_name TEXTEQU <?MRC_PI>
	ELSEIFIDNI mrlc_name,<rpi>
		mrlc_name TEXTEQU <?MRC_RPI>
	ELSEIFIDNI mrlc_name,<e>
		mrlc_name TEXTEQU <?MRC_E>
	ELSEIFIDNI mrlc_name,<deg>
		mrlc_name TEXTEQU <?MRC_DEG>
	ELSEIFIDNI mrlc_name,<rad>
		mrlc_name TEXTEQU <?MRC_RAD>
	ELSEIFIDNI mrlc_name,<rldt>
		mrlc_name TEXTEQU <?MRC_RLDT>
	ELSEIFIDNI mrlc_name,<zero>
		MR_SET_ZERO r,n
		EXITM
	ELSEIFIDNI mrlc_name,<max>
		MR_RAW_MAXVALUE r,mrlc_sign,n
		IF pwr2
			MR_CSCALE r,r,pwr2,rm,n
		ENDIF
		EXITM
	ELSEIFIDNI mrlc_name,<min>
		MR_RAW_MINVALUE r,mrlc_sign,n
		IF pwr2
			MR_CSCALE r,r,pwr2,rm,n
		ENDIF
		EXITM
	ELSEIFIDNI mrlc_name,<Infinity>
		MR_RAW_SET_N r,@CatStr(@SubStr(<-+>,2+mrlc_sign,1),<Infinity>),,n
		EXITM
	ELSEIFIDNI <&name>,<NaN>
		IFNB mrlc_tsign
			.err <invalid constant _name: name>
		ENDIF
		MR_RAW_SET_N r,NaN,,n
		EXITM
	ELSE
		.err <invalid constant _name: name>
		MR_RAW_SET_N r,NaN,,n
		EXITM
	ENDIF

%	IF n GT MREAL_&mrlc_name&_n-1
%		mrlc_prec = MREAL_&mrlc_name&_n-1
		.err @CatStr(<requested precision (n) is not supported. Maximal value for _n is: >,%mrlc_prec)
		MR_SET_ZERO r,n
		EXITM
	ENDIF
%	MR_CONVERT r,&mrlc_name,%n+1,n,rm
	IF pwr2
		MR_CSCALE r,r,pwr2,rm,n
	ENDIF
	IF mrlc_sign
		MR_NEG r,r,n
	ENDIF
	MREAL_INEXACT = -1
	EXITM
endm

;;/**
;; * Returns a decimal approximation of MREAL value x.
;; * This macro is mainly intended for debugging purpose.
;; * Do not use this macro to initialize REAL4/8/10 values!
;; */
MR_TO_DECIMAL macro x:req,nDigits:=<8>,n:=<MREAL_XDIM>
	
	IF nDigits LT 1
		.err <invalid parameter _nDigits: positive nonzero value expected>
		EXITM <0>
	ENDIF
	
	;;/* process special values */
	IF MREAL_&x&_flg AND MREAL_FLG_NAN
		EXITM <NaN>
	ELSEIF MREAL_&x&_flg EQ MREAL_FLG_INF
		EXITM <+Infinity>
	ELSEIF MREAL_&x&_flg EQ (MREAL_FLG_INF OR MREAL_FLG_SIGN)
		EXITM <-Infinity>
	ELSEIF MREAL_&x&_flg AND MREAL_FLG_ZERO
		EXITM <0>
	ENDIF
	;;/* x is a normal value */
	
	;;/* set working precision */
	IF n+2 GT MREAL_?MRC_RLDT_n-1
		mrtd_p = MREAL_?MRC_RLDT_n-1
	ELSE
		mrtd_p = n + 2
	ENDIF
	MR_CONVERT mrtd_x,x,n,mrtd_p,MRRM_ROUND_TO_EVEN,-1
	MR_CONVERT mrtd_c,?MRC_RLDT,%mrtd_p+1,mrtd_p,MRRM_ROUND_TO_EVEN,-1
	MR_ABS mrtd_x,mrtd_x
	
	;;/* test intermediate result */
	IF MREAL_mrtd_x_flg AND MREAL_FLG_NAN
		EXITM <NaN>
	ELSEIF MREAL_mrtd_x_flg EQ MREAL_FLG_INF
		EXITM <+Infinity>
	ELSEIF MREAL_mrtd_x_flg EQ (MREAL_FLG_INF OR MREAL_FLG_SIGN)
		EXITM <-Infinity>
	ELSEIF MREAL_mrtd_x_flg AND MREAL_FLG_ZERO
		EXITM <0>
	ENDIF
	
	;;/**
	;; * Find approximation dexp
	;; * dexp ~=~ floor(log10(|x|)) = floor(log2(|x|)/log2(10))
	;; * thus
	;; * 0 <= |x|*10^-dexp < 10
	;; */
	MR_FROM_EXPR32 mrtd_k,%MREAL_mrtd_x_exp-1,MRRM_ROUND_TO_EVEN,mrtd_p
	MR_MUL mrtd_k,mrtd_k,mrtd_c,MRRM_TRUNCATE,mrtd_p
	mrtd_dexp = MR_TO_INT32(mrtd_k,,MRRM_TRUNCATE,mrtd_p)
	IF mrtd_dexp GE 0
		MR_GET_10pX mrtd_e,mrtd_dexp,mrtd_p
		MR_DIV mrtd_q,mrtd_x,mrtd_e,MRRM_ROUND_TO_EVEN,mrtd_p
	ELSE
		MR_GET_10pX mrtd_e,%-mrtd_dexp,mrtd_p
		MR_MUL mrtd_q,mrtd_x,mrtd_e,MRRM_ROUND_TO_EVEN,mrtd_p
	ENDIF
	mrtd_res = 0
	WHILE 1
		IF MREAL_mrtd_q_flg AND MREAL_FLG_NON_NUMERIC_TEST
			;;/* error case */
			mrtd_res = MREAL_mrtd_q_flg
			EXITM
		ENDIF
		IF (MREAL_mrtd_q_flg AND MREAL_FLG_SIGN) NE 0 OR MREAL_mrtd_q_exp LT 1
			;;/* case: |x|*10^-k < 0  --> k-- */
			mrtd_dexp = mrtd_dexp - 1
		ELSE
			MR_CMP mrtd_q,?MRC_TEN,mrtd_p
			IF mr_cmp GE 0
				;;/* case: |x|*10^-k >= 10  --> k++ */
				mrtd_dexp = mrtd_dexp + 1
			ELSE
				EXITM
			ENDIF
		ENDIF
		;;/* update q(dexp) */
		IF mrtd_dexp GE 0
			MR_GET_10pX mrtd_e,mrtd_dexp,mrtd_p
			MR_DIV mrtd_q,mrtd_x,mrtd_e,MRRM_ROUND_TO_EVEN,mrtd_p
		ELSE
			MR_GET_10pX mrtd_e,%-mrtd_dexp,mrtd_p
			MR_MUL mrtd_q,mrtd_x,mrtd_e,MRRM_ROUND_TO_EVEN,mrtd_p
		ENDIF
	ENDM
	IF mrtd_res
		EXITM <NaN>
	ENDIF
	
	;;/* get decimal digits */
	mrtd_digits TEXTEQU <>
	mrtd_cntr = (nDigits + 7) AND -8
	mrtd_exp TEXTEQU <?MRC_1E7>
	WHILE mrtd_cntr GE 8
	%	MR_XMUL mrtd_k,mrtd_q,&mrtd_exp,mrtd_p,mrtd_p,MREAL_&mrtd_exp&_nSig,MRRM_ROUND_TO_EVEN
		mrtd_val = MR_TO_UINT32(mrtd_k,,MRRM_TRUNCATE,mrtd_p)
		;;/* use the internal MREAL mrtiTmp of MR_TO_UINT32 if valid */
		IF (MREAL_mrtiTmp_flg AND MREAL_FLG_NO_MANTISSA_TEST) EQ 0 AND mrtd_val NE 0
			MR_SUB mrtd_q,mrtd_k,mrtiTmp,MRRM_ROUND_TO_EVEN,mrtd_p
		ENDIF
		mrtd_txt TEXTEQU %mrtd_val
		mrtd_size SIZESTR mrtd_txt
		IF mrtd_size LT 8
			mrtd_txt TEXTEQU @SubStr(<0000000>,%mrtd_size,),mrtd_txt
		ENDIF
		mrtd_digits TEXTEQU mrtd_digits,mrtd_txt
		mrtd_cntr = mrtd_cntr - @SubStr(<%mrtd_exp>,8,1)
		mrtd_exp TEXTEQU <?MRC_1E8>
	ENDM
	
	;;/* compose output format */
	mrtd_digits SUBSTR mrtd_digits,1,nDigits
	IF nDigits GT 1
		mrtd_digits TEXTEQU @SubStr(%mrtd_digits,1,1),<.>,@SubStr(%mrtd_digits,2,),<E>
	ELSE
		mrtd_digits TEXTEQU @SubStr(%mrtd_digits,1,1),<.0E>
	ENDIF
	IF mrtd_dexp LT 0
		mrtd_digits TEXTEQU mrtd_digits,<->,%(-mrtd_dexp)
	ELSE
		mrtd_digits TEXTEQU mrtd_digits,<+>,%mrtd_dexp
	ENDIF
	IF MREAL_&x&_flg AND MREAL_FLG_SIGN
		mrtd_digits TEXTEQU <->,mrtd_digits
	ENDIF
	
	EXITM mrtd_digits
endm

;;/**
;; * Create IEEE 754-2008 hexadecimal-significant character sequence.
;; * nDigits determines the number of hexadecimal mantissa digits to use.
;; * If nDigits is zero, all manstissa digits are used, otherwise
;; * the value is rounded appropriate. Due to MASM's line length limit, 
;; * the number of digit is also limit (internal) to 240.
;; */
MR_TO_IEEE_HEX_SEQ macro x:req,nDigits:=<0>,rm:=<MREAL_ROUND_MODE>,n:=<MREAL_XDIM>
	
	;;/* handel special values */
	IF MREAL_&x&_flg AND MREAL_FLG_NAN
		EXITM <NaN>
	ELSEIF MREAL_&x&_flg EQ MREAL_FLG_INF
		EXITM <+Infinity>
	ELSEIF MREAL_&x&_flg EQ (MREAL_FLG_INF OR MREAL_FLG_SIGN)
		EXITM <-Infinity>
	ELSEIF MREAL_&x&_flg AND MREAL_FLG_ZERO
		EXITM <0x0>
	ENDIF
	
	IF nDigits LE 0 OR nDigits GT (n)*4
		mtih_ndigits = (n)*4
	ELSE
		mtih_ndigits = nDigits
	ENDIF
	
	;;/**
	;; * MASM's line length limit determines the maximal
	;; * number of digits.
	;; */
	IF mtih_ndigits GT 240
		mtih_ndigits = 240
	ENDIF

	MR_ROUND mtihTmp,x,%mtih_ndigits*4,<bits>,rm,n,,,-1
	IF MREAL_mtihTmp_flg EQ MREAL_FLG_INF
		EXITM <+Infinity>
	ELSEIF MREAL_mtihTmp_flg EQ (MREAL_FLG_INF OR MREAL_FLG_SIGN)
		EXITM <-Infinity>
	ELSEIF MREAL_mtihTmp_flg AND MREAL_FLG_ZERO
		EXITM <0x0>
	ENDIF
	
	;;/* get hexadecimal digits */
	mtih_digits TEXTEQU <>
	mtih_cntr = 0
	REPEAT ((mtih_ndigits+3) AND -4)/4
		mtih_val = @CatStr(<MREAL_mtihTmp_w>,%mtih_cntr)
		.radix 16
		mtih_txt TEXTEQU %mtih_val
		.radix 10
		mtih_size SIZESTR mtih_txt
		IF mtih_size LT 4
			mtih_txt TEXTEQU @SubStr(<000>,mtih_size,),mtih_txt
		ENDIF
		mtih_digits TEXTEQU mtih_digits,mtih_txt
		mtih_cntr = mtih_cntr + 1
	ENDM
	mtih_digits SUBSTR mtih_digits,1,mtih_ndigits
	
	IFE MREAL_mtihTmp_exp
		mtih_digits TEXTEQU <0x0.>,mtih_digits
	ELSE
		mtih_digits TEXTEQU <0x0.>,mtih_digits,<p>,@CatStr(%MREAL_mtihTmp_exp)
	ENDIF
	IF MREAL_mtihTmp_flg AND MREAL_FLG_SIGN
		mtih_digits TEXTEQU <->,mtih_digits
	ENDIF
	EXITM mtih_digits
endm

;;/**
;; * Initialize one or more MREAL values from numeric literals
;; * Syntax:
;; *
;; *    MREAL name1 = literal1, name2 = literal2, ...
;; *
;; * To override the default precision, each assignment can contain
;; * a brace-expression that specifies the precision to use:
;; *
;; *    MREAL x{8} = 123.456E-7   ; 8*16=128 bit precision
;; *
;; * (The brace-expression could be placed anywhere in the assignment)
;; * 
;; * Example:
;; *
;; *    MREAL x = -123 , y = 0x123 , z = 0.005 , k = 0f00h
;; */
MREAL macro expr:VARARG
	FOR txt,<&expr>
		mreal_txt TEXTEQU < &txt >
		mreal_pos1 INSTR mreal_txt,<{>
		mreal_tn TEXTEQU <MREAL_XDIM>
		IF mreal_pos1
			mreal_pos2 INSTR mreal_txt,<}>
			IF mreal_pos2 EQ 2 OR mreal_pos2 EQ mreal_pos1+1 OR mreal_pos2 LT mreal_pos1
				.err <invalid use of braces {}>
			ELSE
				mreal_txt1 SUBSTR mreal_txt,1,mreal_pos1-1
				mreal_tn SUBSTR mreal_txt,mreal_pos1+1,mreal_pos2-mreal_pos1-1
				mreal_txt2 SUBSTR mreal_txt,mreal_pos2+1
				mreal_txt TEXTEQU mreal_txt1,mreal_txt2
			ENDIF
		ENDIF
		mreal_pos1 INSTR mreal_txt,<=>
		IF mreal_pos1
			mreal_txt1 SUBSTR mreal_txt,1,mreal_pos1-1
			mreal_txt2 SUBSTR mreal_txt,mreal_pos1+1
		%	MR_FROM_STR &mreal_txt1,&mreal_txt2,,&mreal_tn
		ELSE
			.err <invalid macro usage: expected: dest1 = value1, dest2 = value2, ...>
		ENDIF
	ENDM
endm


ENDIF ; IFNDEF MR_VERSION

