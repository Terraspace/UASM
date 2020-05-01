; constant expression evaluation macros, by qWord, 2015-2016
; Version 1.0.2
; This file is best viewed with a fixed-width font and a tab size of 4.
;
;(1) Overview
;
;    The macros in this file allows to evaluate mathematical expressions with real numbers
;    while assembling. The calculations are done using the MREAL macros (see real_math.inc).
;    By default the calculations are done with 64 bit precision (REAL10) and the rounding
;    mode is "round to nearest, half to even" (like the x87 FPU). The basic operations
;    addition, subtraction, multiplication, division and extracting of square roots results in
;    correctly rounded results (as required by the IEEE 754 standard).
;
;    Example:
;                   ceval x = (1-2*3^4)/sqrt(123.45E+6)        ; x = implicit created MREAL variable
;                   echo_mreal x
;
;                   ceval x/fac(1) - x^3/fac(3) + x^5/fac(5)   ; fac = factorial
;                   echo_mreal ans
;
;(2) Operands
;
;(2.1)  Numerical literals
;
;       The evaluator accepts decimal and hexadecimal initializer for both, integer and floating point values.
;
;                Description           |   Example   |   Notes
;         -----------------------------+-------------+-------------------------------------------------
;          hexadecimal integer literal | 0ffh        |
;         -----------------------------+-------------+-------------------------------------------------
;          MASM hexadecimal floating   | 07f800000r  | Remarks the type specific size constraints
;          point initializer           |             |
;         -----------------------------+-------------+-------------------------------------------------
;          decimal integer literal     | 123         |
;         -----------------------------+-------------+-------------------------------------------------
;          decimal floating point      | -1.0E-3     | The exponent should be in range -4800 to 4800.
;          literal                     | 123.4       | The decimal dot is required.
;
;       Decimal literals results only in correctly rounded MREAL values, if the input value is representable as
;       quotient or product of two integers, whereby the decimal exponent of these integers is below or equal to 105.
;       e.g. for values with 30 significant digits the decimal exponent range is at least -75 to 75.
;       For 20 digits the range is extended to -85 to 85. Decimal values with larger exponents are approximated.
;
;
;(2.2)  MREAL variables
;
;       Any ID that is not an operator nor a function is interpreted as ID of a MREAL variable.
;       An ID can consist of the following characters:
;
;              _$?AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789
;
;       A digit as first character is not allowed. IDs are case sensitive.
;       Also, IDs should not start with a question mark or the prefix "tmp", because this might cause
;       a name conflict with internally used IDs.
;
;
;(2.3)  MASM equates
;
;       Equates (x EQU value; x = value) can be used as source operands, if preceded by an ampersand.
;       For example:
;                      cntr = 1               ;; cntr is MASM equate
;                      ceval x = 2 ^ &cntr    ;;
;
;       Remarks that no white spaces is allowed between the ampersand and the ID. Also, if the equate-IDs
;       are not preceded by an ampersand, then they are interpreted as MREAL ID.
;
;(2.4)  Predefined constants
;
;       The following constants are predefined and thus reserved words (case sensitive):
;
;                      name  |  description
;                     -------+------------------
;                       pi   |   3.1415...
;                       e    |   2.7182...
;                      true  |   1
;                      false |   0
;
;(3) Operators
;
;        operator | precedence | associativity |  description                                      |  correctly rounded?
;       ----------+------------+---------------+---------------------------------------------------+---------------------
;           ^     |      7     | Right-to-left | Exponentiation. The exponent will be round to an  |
;                 |            |               | integer in current rounding mode. The exponent    |         no
;                 |            |               | value must be in range [-2147483647, 2147483647]. |
;       ----------+------------+---------------+---------------------------------------------------+---------------------
;           -     |      6     | Right-to-left | unary minus (negation)                            |
;       ----------+------------+---------------+---------------------------------------------------+---------------------
;          not    |      6     | Right-to-left | logical NOT                                       |
;       ----------+------------+---------------+---------------------------------------------------+---------------------
;           *     |      5     | Left-to-right | multiplication                                    |         yes
;       ----------+------------+---------------+---------------------------------------------------+---------------------
;           /     |      5     | Left-to-right | division                                          |         yes
;       ----------+------------+---------------+---------------------------------------------------+---------------------
;           +     |      4     | Left-to-right | addition                                          |         yes
;       ----------+------------+---------------+---------------------------------------------------+---------------------
;           -     |      4     | Left-to-right | binary minus (subtraction)                        |         yes
;       ----------+------------+---------------+---------------------------------------------------+---------------------
;         eq  ==  |      3     | Left-to-right | equal to                                          |
;       ----------+------------+---------------+---------------------------------------------------+---------------------
;         ne  /=  |      3     | Left-to-right | not equal to                                      |
;       ----------+------------+---------------+---------------------------------------------------+---------------------
;           lt    |      3     | Left-to-right | less than                                         |
;       ----------+------------+---------------+---------------------------------------------------+---------------------
;           gt    |      3     | Left-to-right | greater than                                      |
;       ----------+------------+---------------+---------------------------------------------------+---------------------
;           le    |      3     | Left-to-right | less than or equal to                             |
;       ----------+------------+---------------+---------------------------------------------------+---------------------
;           ge    |      3     | Left-to-right | greater than or equal to                          |
;       ----------+------------+---------------+---------------------------------------------------+---------------------
;          and    |      2     | Left-to-right | logical AND                                       |
;       ----------+------------+---------------+---------------------------------------------------+---------------------
;           or    |      1     | Left-to-right | logical OR                                        |
;       ----------+------------+---------------+---------------------------------------------------+---------------------
;           =     |      0     | Right-to-left | assignment (to MREAL variable)                    |
;
;       The relational operators does return Boolean values, represent by 1=true and 0=false. The logical operators
;       interpret any nonzero values as true.
;       Remarks that non-symbol operators are case sensitive.
;
;
;(4) Functions
;
;          function      |  description                                  |  correctly rounded?
;    --------------------+-----------------------------------------------+---------------------
;          sqrt(x)       |  square root                                  |         yes
;    --------------------+-----------------------------------------------+---------------------
;           neg(x)       |  negate                                       |
;    --------------------+-----------------------------------------------+---------------------
;           abs(x)       |  absolute value                               |
;    --------------------+-----------------------------------------------+---------------------
;           fac(x)       |  factorial, x >= 0, x rounded to an integer   |         yes
;    --------------------+-----------------------------------------------+---------------------
;          min(x,y)      |  returns minimum of x and y                   |
;    --------------------+-----------------------------------------------+---------------------
;          max(x,y)      |  returns maximum of x and y                   |
;    --------------------+-----------------------------------------------+---------------------
;        fmadd(x,y,z)    |  fused multiply-add.                          |         yes
;                        |  result = round(x * y + z)                    |
;    --------------------+-----------------------------------------------+---------------------
;           int(x)       |  round x to nearest integer, half to even     |         yes
;    --------------------+-----------------------------------------------+---------------------
;          ceil(x)       |  round up                                     |         yes
;    --------------------+-----------------------------------------------+---------------------
;          floor(x)      |  round down                                   |         yes
;    --------------------+-----------------------------------------------+---------------------
;         truncate(x)    |  round toward zero                            |         yes
;    --------------------+-----------------------------------------------+---------------------
;         scale(x,y)     |  result = x * 2 ^ round(y)                    |
;                        |  Rounding is done in current rounding mode    |
;    --------------------+-----------------------------------------------+---------------------
;           sgn(x)       |  returns -1 if x < 0, 1 if x > 0 and          |
;                        |  zero if x == 0                               |
;
;     Remarks that function names are case sensitive.
;
;
;(5) Expressions
;
;    Expressions does consist of operators, operands, bracket terms and function calls.
;    For bracket terms there is no nesting limit. The expression is evaluated  from left to
;    right, respecting the precedence and associativity of operators.
;
;
;
;(6) Precision of calculation and rounding control
;
;    The used precision is by default 64 bit (like x87-FPU). The default rounding
;    mode is: round to nearest, half to even.
;    Both, precision and rounding mode, can be changed using the corresponding
;    equates (MREAL_XDIM, MREAL_ROUND_MODE) -> see real_math.inc for details.
;
;(7) Macros
;
;(7.1)  ceval expression
;
;       Macro procedure that does evaluate given expression.
;       The result is always stored in the MREAL value "ans".
;       Examples:
;                      ceval 1 - 2*3^-4 + 5^sqrt(min(7, 1.E+100))
;                      echo_mreal ans
;
;                      ceval x = y = true and not false
;                      echo_mreal ans
;                      echo_mreal x
;                      echo_mreal y
;
;
;(7.2)  ccond(expression)
;
;       Macro function that evaluates expression and then interpret the
;       result as Boolean value to return a corresponding integer value.
;       If the expression is not zero, it is interpreted as true and -1 is returned,
;       otherwise zero. The result is also stored in MREAL "ans".
;       Example:
;                      IF ccond( x lt pi && not z || x gt 123.456 || x == z && x /= y )
;                          ;...
;                      ENDIF
;
;       Do not use this macro as condition for WHILE, REPEAT or ELSE-clauses.
;
;
;(7.3)  cReal4(expression), cReal8(expression)
;
;       Macro functions that evaluate expression and return the result
;       as hexadecimal floating point initializer (MASM specific).
;       The result is also stored in MREAL "ans".
;       Example:
;                      .const
;                      someConst REAL8 cReal8( sqrt(2^-13) )
;
;
;(7.4)  defReal10 label, expression
;
;       Macro procedure that defines REAL10 value in current segment, initialized
;       with result of evaluation. The result is also stored in MREAL "ans".
;       This macro is a bug fix for MASM v6-7.
;       Example:
;                     .const
;                     defReal10 someConst, sqrt(2^-13)
;
;(7.5)  cInt32 / cUint32 / cInt64 / cUint64(expression)
;
;       Macro functions that does evaluate the given expression and then return
;       corresponding integer literals. If the required conversion fails, an error
;       is thrown.
;                     macro  |  result range
;                   ---------+-----------------
;                    cInt32  | -2^31 to 2^31-1
;                    cUint32 |   0   to 2^32-1
;                    cInt64  | -2^63 to 2^63-1
;                    cUint64 |   0   to 2^64-1
;       Examples:
;                    xyz = cInt32( floor(sqrt(pi^3/10)))
;                    .const
;                    foo QWORD cInt64( -123456789 * sqrt(2) )
;                    %echo cInt64( ans )
;
;
;(7.6)  echo_mreal id, n_digits
;
;       Macro procedure that prints MREAL value to build console. The optional
;       parameter n_digits can be used to specify the number of printed digits.
;       Example:
;                     ceval x = pi
;                     echo_mreal x,19
;
;(7.7)  echo_mreal_hex id, n_digits
;
;       The same as echo_mreal, but prints the value as IEEE754-2008
;       hexadecimal-significant character sequence.
;
;
;(8) MASM environment
;
;    - The macros are case-sensitive thus OPTION CASEMAP:NONE is needed.
;    - The expression word size must be at least 32 bit (OPTION EXPR32, default for MASM v6+).
;    - The macros assumes radix 10 (MASM default radix).
;
;
;(9) Debugging
;
;    If the equate RPNE_DEBUG is set to an positive value, the evaluation
;    steps are printed to the build console. The value of RPNE_DEBUG specifies
;    how many digits should be printed for numeric values.
;
;
;(10) Changelog
;       25.09.2015  Version 1.0.0
;                   Initial release
;       11.10.2015  Version 1.0.1
;                   improvement:  - check for invalid IDs at top of operator stack after RPN evaluation
;       16.06.2016  Version 1.0.2
;                   bugfix: - If the first two or three characters of an ID were equal to an operator name
;                             they were interpreted as that operator. For example, 'negative' were interpreted as
;                             operator 'ne' and ID 'gative'.
;


IFNDEF CEVAL_VERSION

	CEVAL_VERSION EQU 102
	
	mstck_init macro stack
		mstack_&stack&_N = 0
	endm
	
	mstck_set macro stack,index,tm,eqt
		mstack_&stack&_tm&index TEXTEQU &tm
		mstack_&stack&_&index = &eqt
	endm
	
	mstck_get macro stack,index,tm,eqt
		&tm TEXTEQU mstack_&stack&_tm&index
		&eqt = mstack_&stack&_&index
	endm
	
	mstck_push macro stack:req,tm:req,eqt:req
		mstck_set stack,%mstack_&stack&_N,tm,eqt
		mstack_&stack&_N = mstack_&stack&_N + 1
	endm
	
	mstck_pop macro stack:req,tm:req,eqt:req
		IF mstack_&stack&_N EQ 0
			.err <!stack underrun>
			EXITM
		ENDIF
		mstack_&stack&_N = mstack_&stack&_N - 1
		mstck_get stack,%mstack_&stack&_N,tm,eqt
	endm
	
	mstck_peek macro stack:req,tm:req,eqt:req
		IFE mstck_size(stack)
			tm TEXTEQU <>
			eqt = 0
			mstack_peek_successfull = 0
			EXITM
		ENDIF
		mstack_peek_successfull = -1 
		mstck_get stack,%mstack_&stack&_N-1,tm,eqt
	endm
	
	mstck_pop_push macro from,to
		mstck_pop from,syapp_token,syapp_token_type
		mstck_push to,syapp_token,syapp_token_type
	endm
	
	mstck_transfer macro from:req,to:req,N:=<-1>
		mstckt_cntr = N
		WHILE mstack_&from&_N NE 0 AND mstckt_cntr NE 0
			mstck_pop_push from,to
			mstckt_cntr = mstckt_cntr - 1
		ENDM
	endm
	
	mstck_size macro stack:req
		IFNDEF mstack_&stack&_N
			EXITM <0>
		ELSE
			EXITM %mstack_&stack&_N
		ENDIF
	endm


	sya_functions TEXTEQU <sqrt,neg,abs,fac,min,max,fmadd,int,ceil,floor,truncate,scale,sgn>
	
	SYATT_INVALID 	EQU 0
	SYATT_NUMBER	EQU 1
	SYATT_ID		EQU 2
	SYATT_OPERATOR	EQU 4
	SYATT_FUNCTION	EQU 8
	SYATT_END		EQU 16
	SYATT_COMMA		EQU 32
	SYATT_L_BRACKET	EQU 64
	SYATT_R_BRACKET EQU 128
	
	SYA_LEFT_ASSOCIATIVE	EQU 0
	SYA_RIGHT_ASSOCIATIVE	EQU 1
	
	SYA_REG_ERROR macro ID,value,txt
		ID EQU value
		say_error_&value&_msg TEXTEQU <&txt>
	endm
	
	SYA_REG_ERROR SYA_SUCCESS                    , 0, <success>
	SYA_REG_ERROR SYA_ERROR_INVALID_TOKEN        , 1, <invalid token in expression>
	SYA_REG_ERROR SYA_ERROR_SEPARATOR_MISPLACED  , 2, <comma misplaced or unexpected closing bracket>
	SYA_REG_ERROR SYA_ERROR_UNEXPECTED_R_BRACKET , 3, <unexpected closing bracket>
	SYA_REG_ERROR SYA_ERROR_MISSING_R_BRACKET    , 4, <missing closing bracket>
	SYA_REG_ERROR SYA_ERROR_UNKNOWN              , 5, <unknown>

	SYA_ERROR_MIN	EQU 0	
	SYA_ERROR_MAX	EQU 5
	
	sya_get_error_msg macro
		IF sya_error LT SYA_ERROR_MIN OR sya_error GT SYA_ERROR_MAX
			sya_error = SYA_ERROR_UNKNOWN
		ENDIF
		syagem_txt TEXTEQU <say_error_>,%sya_error,<_msg>
		EXITM syagem_txt
	endm
		
	sya_ltrim macro
		sya_char TEXTEQU <>
		WHILE sya_pos LE sya_size
			sya_char SUBSTR sya_txt,sya_pos,1
			IFNB sya_char
				EXITM
			ENDIF
			sya_pos = sya_pos + 1
		ENDM
	endm
	
	sya_read_number macro
		syarn_discard = @ScanForFlt(%sya_pos,<%sya_txt>)
		sya_token TEXTEQU sff_numstr
		sya_pos = sff_pos
		sya_token_type = SYATT_NUMBER	
	endm
	
	sya_read_id macro
		sya_token TEXTEQU <>
		sya_char TEXTEQU <>
		WHILE sya_pos LE sya_size
			sya_char SUBSTR sya_txt,sya_pos,1
			syarid_isIdChar INSTR <_$?AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789>,sya_char
			IFE syarid_isIdChar
				EXITM
			ENDIF
			sya_token TEXTEQU sya_token,sya_char
			sya_pos = sya_pos + 1
		ENDM
		sya_token_type = SYATT_ID
	endm
	
	sya_check_if_function macro
	%	FOR _fnc_,<&sya_functions>
			IFIDN <&_fnc_>,sya_token
				sya_token_type = SYATT_FUNCTION
				EXITM
			ENDIF
		ENDM
	endm
	
	sya_substitute_known_constants macro
		IFIDN <pi>,sya_token
			sya_token TEXTEQU <?MRC_PI>
		ELSEIFIDN <e>,sya_token
			sya_token TEXTEQU <?MRC_E>
		ELSEIFIDN <true>,sya_token
			sya_token TEXTEQU <?MRC_ONE>
		ELSEIFIDN <false>,sya_token
			sya_token TEXTEQU <?MRC_ZERO>
		ENDIF
	endm
	
	sya_token_is_unary_minus macro
		IF sya_previous_token_type EQ SYATT_COMMA OR sya_previous_token_type EQ SYATT_L_BRACKET OR sya_previous_token_type EQ SYATT_OPERATOR OR sya_previous_token_type EQ SYATT_INVALID
			EXITM <-1>
		ENDIF
		EXITM <0>
	endm
	
	sya_is_delimiter_at_pos macro pos:req
		;; if not end of string
		IF pos LE sya_size
			syamco_delimiter SUBSTR sya_txt,pos,1
			syamco_is_delimiter INSTR < 	=+-*/^(),&>,syamco_delimiter
			EXITM @CatStr(%syamco_is_delimiter NE 0)
		ENDIF
		EXITM <-1>
	endm
	
	sya_is_multichar_operator macro
		
		syamco_isTwoCharOperatorPossible INSTR </=&|lgeno>,sya_char
		syamco_isThreeCharOperatorPossible INSTR <an>,sya_char
		
		IF syamco_isTwoCharOperatorPossible EQ 0 AND syamco_isThreeCharOperatorPossible EQ 0 OR sya_pos+1 GT sya_size
			EXITM <0>
		ENDIF
		
		syamco_operator SUBSTR sya_txt,sya_pos,2
		syamco_isTwoCharOperator INSTR <==#/=#&&#||#eq#ne#lt#gt#le#ge#or>,syamco_operator
		IF syamco_isTwoCharOperator
			;; if non-symbol operators: check for delimiter
			IF syamco_isTwoCharOperator GE 13 AND NOT sya_is_delimiter_at_pos(sya_pos+2)
				EXITM <0>
			ENDIF
			IFIDN <==>,syamco_operator
				sya_token TEXTEQU <eq>
			ELSEIFIDN </=>,syamco_operator
				sya_token TEXTEQU <ne>
			ELSEIFIDN <or>,syamco_operator
				sya_token TEXTEQU <||>
			ELSE
				sya_token TEXTEQU syamco_operator
			ENDIF
			sya_pos = sya_pos + 2
			sya_token_type = SYATT_OPERATOR
			EXITM <-1>
		ENDIF
		IF syamco_isThreeCharOperatorPossible EQ 0 OR sya_pos+2 GT sya_size
			EXITM <0>
		ENDIF
		
		syamco_operator SUBSTR sya_txt,sya_pos,3
		syamco_isThreeCharOperator INSTR <and#not>,syamco_operator
		IF syamco_isThreeCharOperator
			IF NOT sya_is_delimiter_at_pos(sya_pos+3)
				EXITM <0>
			ENDIF
			IFIDN <and>,syamco_operator
				sya_token TEXTEQU <&&>
			ELSE
				sya_token TEXTEQU syamco_operator
			ENDIF
			sya_pos = sya_pos + 3
			sya_token_type = SYATT_OPERATOR
			EXITM <-1>
		ENDIF
		
		EXITM <0>
	endm
	
	sya_get_next_token macro
		
		sya_previous_token_type = sya_token_type
		sya_token TEXTEQU <>
		sya_token_type = SYATT_INVALID
		sya_ltrim
		
		syagnt_isDigit INSTR <0123456789>,sya_char
		syagnt_isOperator INSTR <=+-*/^(),&>,sya_char
		syagnt_isIdChar INSTR <_$?AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz>,sya_char
		
		IF sya_is_multichar_operator()
			EXITM
		ENDIF
		
		IF syagnt_isDigit
			sya_read_number
		ELSEIF syagnt_isIdChar
			sya_read_id
			sya_check_if_function
			sya_substitute_known_constants
		ELSEIF syagnt_isOperator
			sya_token TEXTEQU sya_char
			sya_pos = sya_pos + 1
			IF syagnt_isOperator LT 7
				sya_token_type = SYATT_OPERATOR
			ELSEIF syagnt_isOperator EQ 7
				sya_token_type = SYATT_L_BRACKET
			ELSEIF syagnt_isOperator EQ 8
				sya_token_type = SYATT_R_BRACKET
			ELSEIF syagnt_isOperator EQ 9
				sya_token_type = SYATT_COMMA
			ELSE
				sya_read_id
				sya_token TEXTEQU @CatStr(%(sya_token))
				sya_token_type = SYATT_NUMBER
			ENDIF
		ELSEIFB sya_char
			sya_token_type = SYATT_END
		ENDIF
		
		IFDIF <->,sya_token
			EXITM
		ENDIF
		
		IF sya_token_is_unary_minus()
			sya_token TEXTEQU <~>
		ENDIF
	endm
	
	sya_get_precedence_and_associativity macro token,precedence,associativity
		syagpaa_size SIZESTR token
		IF syagpaa_size EQ 1
			syagpaa_pos       INSTR <=+-*/~^>,token
			precedence    = @SubStr(<0445567>,%syagpaa_pos,1)
			associativity = @SubStr(<1000011>,%syagpaa_pos,1)
		ELSEIF syagpaa_size EQ 2
			syagpaa_pos       INSTR <==#/=#&&#||#eq#ne#lt#gt#le#ge>,token
			precedence    = @SubStr(<3  3  2  1  3  3  3  3  3  3 >,%syagpaa_pos,1)
			associativity = @SubStr(<0  0  0  0  0  0  0  0  0  0 >,%syagpaa_pos,1)
		ELSE
			syagpaa_pos       INSTR <not>,token
			precedence    = @SubStr(<6  >,%syagpaa_pos,1)
			associativity = @SubStr(<1  >,%syagpaa_pos,1)
		ENDIF
	endm
	
	sya_is_unary_operator macro operator
		IFIDN <~>,operator
			EXITM <-1>
		ELSEIFIDN <not>,operator
			EXITM <-1>
		ENDIF
		EXITM <0>
	endm 
	
	; Shunting-yard algorithm
	sya macro txt
		
		; global const (expression and size of expression)
		sya_txt TEXTEQU <&txt>
		sya_size SIZESTR sya_txt
		
		; current state (token, token type, position in expression, error level)
		sya_token TEXTEQU <>
		sya_token_type = SYATT_INVALID
		sya_pos = 1
		sya_error = SYA_SUCCESS
		sya_previous_token_type = SYATT_INVALID
		
		; initialize operator stack and output queue
		; (because no pop-operationios is done on the output queue, a stack is used here)
		mstck_init output
		mstck_init operators
		
		WHILE 1
		
			sya_get_next_token
			
			IF sya_token_type EQ SYATT_END
				
				EXITM
			
			ELSEIF sya_token_type EQ SYATT_INVALID
				
				sya_error = SYA_ERROR_INVALID_TOKEN
				EXITM
				
			ELSEIF sya_token_type EQ SYATT_NUMBER OR sya_token_type EQ SYATT_ID
			
				mstck_push output,sya_token,sya_token_type
				
			ELSEIF sya_token_type EQ SYATT_FUNCTION
			
				mstck_push operators,sya_token,sya_token_type
			
			ELSEIF sya_token_type EQ SYATT_OPERATOR
				
				sya_operator1 TEXTEQU sya_token
				sya_operator1_type = sya_token_type
				
				; do not pop any operator in case of unary operator
				IF NOT sya_is_unary_operator(sya_operator1)
					
					sya_get_precedence_and_associativity sya_operator1, sya_precedence1, sya_associativity1
					
					mstck_peek operators,sya_operator2,sya_operator2_type
					
					WHILE mstack_peek_successfull AND sya_operator2_type EQ SYATT_OPERATOR
						
						sya_get_precedence_and_associativity sya_operator2, sya_precedence2, sya_associativity2
						
						IFE (sya_associativity1 EQ SYA_LEFT_ASSOCIATIVE  AND sya_precedence1 LE sya_precedence2) \
						 OR (sya_associativity1 EQ SYA_RIGHT_ASSOCIATIVE AND sya_precedence1 LT sya_precedence2)
							EXITM
						ENDIF
						
						mstck_transfer operators,output,1
						
						mstck_peek operators,sya_operator2,sya_operator2_type
					ENDM
					
				ENDIF
				
				mstck_push operators,sya_operator1,sya_operator1_type
				
			ELSEIF sya_token_type EQ SYATT_L_BRACKET
			
				mstck_push operators,sya_token,sya_token_type
			
			ELSEIF sya_token_type EQ SYATT_R_BRACKET
				
				mstck_peek operators,sya_operator,sya_operator_type
				
				WHILE mstack_peek_successfull AND sya_operator_type NE SYATT_L_BRACKET
					
					mstck_transfer operators,output,1
					
					mstck_peek operators,sya_operator,sya_operator_type
					
				ENDM
				
				IF NOT mstack_peek_successfull
					sya_error = SYA_ERROR_UNEXPECTED_R_BRACKET
					EXITM
				ENDIF
				
				mstck_pop operators,sya_discard_token,sya_discard_token_type
				
				mstck_peek operators,sya_operator,sya_operator_type
				
				IF mstack_peek_successfull AND sya_operator_type EQ SYATT_FUNCTION
					mstck_transfer operators,output,1
				ENDIF
			
			ELSEIF sya_token_type EQ SYATT_COMMA
				
				mstck_peek	operators,sya_operator,sya_operator_type
				
				WHILE mstack_peek_successfull AND sya_operator_type NE SYATT_L_BRACKET
					
					mstck_transfer operators,output,1
					
					mstck_peek operators,sya_operator,sya_operator_type
					
				ENDM
				
				IF NOT mstack_peek_successfull
					sya_error = SYA_ERROR_SEPARATOR_MISPLACED
					EXITM
				ENDIF
				
			ELSE
			
				sya_error = SYA_ERROR_UNKNOWN
				EXITM
			
			ENDIF
		ENDM
		
		mstck_init rpn
		
		IF sya_error EQ SYA_SUCCESS
		
			REPEAT mstck_size(operators)
				
				mstck_pop operators,sya_operator,sya_operator_type
				
				IF sya_operator_type EQ SYATT_L_BRACKET
					sya_error = SYA_ERROR_MISSING_R_BRACKET
					EXITM
				ENDIF
				
				mstck_push output,sya_operator,sya_operator_type
				
			ENDM
			IF sya_error EQ SYA_SUCCESS
				mstck_transfer output,rpn
			ENDIF
		ENDIF
		
	endm
	
		
	RPNE_REG_ERROR macro ID,txt
		RPNE_ERROR_MAX = RPNE_ERROR_MAX + 1
		ID = RPNE_ERROR_MAX
		@CatStr(<rpne_error_>,%RPNE_ERROR_MAX,<_msg>) TEXTEQU <&txt>
	endm

	RPNE_ERROR_MIN	EQU 0	
	RPNE_ERROR_MAX	= -1
	
	RPNE_REG_ERROR RPNE_SUCCESS                    , <success>
	RPNE_REG_ERROR RPNE_ERROR_MISSING_ARGUMENTS    , <one ore more missing arguments for operator or function: >
	RPNE_REG_ERROR RPNE_ERROR_UNDEFINED_FUNCTION   , <unimplemented function used: >
	RPNE_REG_ERROR RPNE_ERROR_TOO_MANY_VALUES      , <too many arguments in function call OR typing error OR syntax error>
	RPNE_REG_ERROR RPNE_ERROR_UNKNOWN              , <unknown>
	RPNE_REG_ERROR RPNE_ERROR_ID_IS_NOT_MREAL      , <operand is ID, but not a MREAL value: >
	RPNE_REG_ERROR RPNE_ERROR_INVALID_DEST         , <left-handed operand of assignment must be an ID: >
	RPNE_REG_ERROR RPNE_ERROR_CONST_AS_DEST        , <left-handed operand of assignment is a constant value>

	rpne_get_error_msg macro
		IF rpne_error LT RPNE_ERROR_MIN OR rpne_error GT RPNE_ERROR_MAX
			rpne_error = RPNE_ERROR_UNKNOWN
		ENDIF
		rpnegem_txt TEXTEQU <rpne_error_>,%rpne_error,<_msg>
		rpnegem_txt TEXTEQU rpnegem_txt,rpne_error_tkn
		EXITM rpnegem_txt
	endm
	
	rpne_set_error macro id,msg_token
		rpne_error = id
		rpne_error_tkn TEXTEQU msg_token
	endm
	
	rpne_debugging macro
		IFDEF RPNE_DEBUG
			IF RPNE_DEBUG NE 0
				EXITM <-1>
			ENDIF
		ENDIF
		EXITM <0>
	endm
	
	rpne_alloc_tmp_sym macro
		rpne_local_sym_cntr = rpne_local_sym_cntr + 1
		EXITM @CatStr(<?$??>,%rpne_local_sym_cntr)
	endm
	
	rpne_is_tmp_sym macro sym
		rpneits_pos INSTR <&sym>,<?$??>
		EXITM %(rpneits_pos EQ 1)
	endm
	
	
	; evaluate reverse Polish notation
	rpn_eval macro
		IF rpne_debugging()
			%echo RPNE: sya_txt
		ENDIF
		
		rpne_local_sym_cntr = 0
		
		mstck_init operands
		
		rpne_error = RPNE_SUCCESS
		rpne_error_tkn TEXTEQU <>
		
		WHILE 1
			IF mstck_size(rpn) EQ 0 OR rpne_error NE RPNE_SUCCESS
				EXITM
			ENDIF
			
			mstck_pop rpn,rpne_token,rpne_token_type
			
			IF rpne_token_type EQ SYATT_NUMBER OR rpne_token_type EQ SYATT_ID
			
				mstck_push operands,rpne_token,rpne_token_type
			
			ELSEIF rpne_token_type EQ SYATT_OPERATOR OR rpne_token_type EQ SYATT_FUNCTION
				
				IFIDN rpne_token,<+>
					rpne_fn TEXTEQU <add>
				ELSEIFIDN rpne_token,<->
					rpne_fn TEXTEQU <sub>
				ELSEIFIDN rpne_token,<*>
					rpne_fn TEXTEQU <mul>
				ELSEIFIDN rpne_token,</>
					rpne_fn TEXTEQU <div>
				ELSEIFIDN rpne_token,<^>
					rpne_fn TEXTEQU <ipow>
				ELSEIFIDN rpne_token,<=>
					rpne_fn TEXTEQU <assign>
				ELSEIFIDN rpne_token,<~>
					rpne_fn TEXTEQU <neg>
				ELSEIFIDN rpne_token,<&&>
					rpne_fn TEXTEQU <land>
				ELSEIFIDN rpne_token,<||>
					rpne_fn TEXTEQU <lor>
				ELSE
					rpne_fn TEXTEQU rpne_token
				ENDIF
			
				rpne_fn TEXTEQU <RPNE_FNC_>,rpne_fn
			
			%	IFNDEF &rpne_fn
					rpne_set_error RPNE_ERROR_UNDEFINED_FUNCTION, rpne_token
			%	ELSEIF mstck_size(operands) LT &rpne_fn&_nargs
					rpne_set_error RPNE_ERROR_MISSING_ARGUMENTS, rpne_token
				ELSE
					rpne_fn
				ENDIF
			ELSE
				rpne_error = RPNE_ERROR_UNKNOWN
			ENDIF
		ENDM
		IF rpne_error EQ RPNE_SUCCESS AND mstck_size(operands) NE 1
			rpne_error = RPNE_ERROR_TOO_MANY_VALUES
		ELSEIF rpne_error EQ RPNE_SUCCESS
			mstck_peek operands,rpne_token,rpne_token_type
			IF rpne_token_type NE SYATT_ID
				EXITM
			ENDIF
			IF NOT MR_ID_IS_MREAL(<%rpne_token>)
				rpne_set_error RPNE_ERROR_ID_IS_NOT_MREAL, rpne_token
			ENDIF
		ENDIF
	endm
	

	
	RPNE_DECLR_BIN_FNC macro m_suffix,mr_suffix,symbol,relation
		RPNE_FNC_&m_suffix&_nargs = 2
		RPNE_FNC_&m_suffix macro
			RPNE_FNC_MR_BIN <&mr_suffix>,<&symbol>,<&relation>
		endm
	endm

	RPNE_BINARY_FUNCTIONS macro tuples:VARARG
		FOR tuple,<tuples>
			RPNE_DECLR_BIN_FNC tuple
		ENDM
	endm
	
	RPNE_BINARY_FUNCTIONS < <<add>,<ADD>,<+>>, <<sub>,<SUB>,<->>, <<mul>,<MUL>,<*>>, <<div>,<DIV>,</>>, <<ipow>,<IPOW>,<^>>, <<scale>,<SCALE>,<* 2 ^ round >> >
	RPNE_BINARY_FUNCTIONS < <<min>,<MIN>,<min>>, <<max>,<MAX>,<max>> >
	RPNE_BINARY_FUNCTIONS < <<eq>,<>,<eq>,<eq>>, <<ne>,<>,<ne>,<ne>>, <<lt>,<>,<lt>,<lt>>, <<gt>,<>,<gt>,<gt>>, <<le>,<>,<le>,<le>>, <<ge>,<>,<ge>,<ge>> >
	RPNE_BINARY_FUNCTIONS < <<land>,<LAND>,<and>>, <<lor>,<LOR>,<or>> >

	RPNE_DECLR_UNARY_FNC macro m_suffix,mr_suffix,symbol
		RPNE_FNC_&m_suffix&_nargs = 1
		RPNE_FNC_&m_suffix macro
			RPNE_FNC_ONE_ARG <&mr_suffix>,<&symbol>
		endm
	endm

	RPNE_UNARY_FUNCTIONS macro tuples:VARARG
		FOR tuple,<tuples>
			RPNE_DECLR_UNARY_FNC tuple
		ENDM
	endm

	RPNE_UNARY_FUNCTIONS < <<sqrt>,<SQRT>,<sqrt>>, <<abs>,<ABS>,<abs>>, <<neg>,<NEG>,<neg>>, <<not>,<LNOT>,<not>>, <<fac>,<FACTORIAL>,<factorial>>, <<sgn>,<SGN>,<sgn>> >
	RPNE_UNARY_FUNCTIONS < <<ceil>,<CEIL>,<ceil>>, <<floor>,<FLOOR>,<floor>>, <<int>,<ROUND_TO_INT>,<int>>, <<truncate>,<TRUNCATE>,<truncate>> >

	MR_IPOW macro r,o1,o2
		
		mrpow_exp = MR_TO_INT32(o2,80000000h)
		IF mrpow_exp LT 0
			mrpow_exp_abs = -mrpow_exp
		ELSE
			mrpow_exp_abs = mrpow_exp
		ENDIF
		IF mrpow_exp_abs EQ 0
			MR_LOAD_CONST r, one
			EXITM
		ELSEIF mrpow_exp_abs EQ 80000000h
			MR_LOAD_CONST r,NaN
			.err @CatStr(<IPOW: exponent out of integer range: >,%mrpow_exp)
			EXITM
		ENDIF
		
		MR_MOV ?o1?,o1
		MR_LOAD_CONST ?r?, one
		WHILE mrpow_exp_abs GT 0
			IF mrpow_exp_abs MOD 2
				MR_MUL ?r?,?r?,?o1?
			ENDIF
			MR_MUL ?o1?,?o1?,?o1?
			mrpow_exp_abs = mrpow_exp_abs / 2
		ENDM
		
		IF mrpow_exp LT 0
			MR_LOAD_CONST r, one
			MR_DIV r,r,?r?
		ELSE
			MR_MOV r,?r?	
		ENDIF
	endm
	
	MR_MIN macro r,o1,o2
		MR_CMP o1,o2
		IF mr_cmp LE 0
			MR_MOV r,o1
		ELSE
			MR_MOV r,o2
		ENDIF
	endm
	
	MR_MAX macro r,o1,o2
		MR_CMP o1,o2
		IF mr_cmp GE 0
			MR_MOV r,o1
		ELSE
			MR_MOV r,o2
		ENDIF
	endm
	
	MR_CMP_RET_BOOL macro r,o1,o2,rel
		MR_CMP o1,o2
		IF mr_cmp rel 0
			MR_LOAD_CONST r,one
		ELSE
			MR_LOAD_CONST r,zero
		ENDIF
	endm
	
	MR_LAND macro r,o1,o2
		IF MR_IS_ZERO(o1) OR MR_IS_ZERO(o2)
			MR_LOAD_CONST r,zero
		ELSE
			MR_LOAD_CONST r,one
		ENDIF
	endm
	
	MR_LOR macro r,o1,o2
		IF MR_IS_ZERO(o1) AND MR_IS_ZERO(o2)
			MR_LOAD_CONST r,zero
		ELSE
			MR_LOAD_CONST r,one
		ENDIF
	endm
	
	MR_LNOT macro r,o1
		IF MR_IS_ZERO(o1)
			MR_LOAD_CONST r,one
		ELSE
			MR_LOAD_CONST r,zero
		ENDIF
	endm
	
	MR_ROUND_TO_INT macro r,o1
		MR_ROUND r,o1,,,MRRM_ROUND_TO_EVEN
	endm
	
	MR_CEIL macro r,o1
		MR_ROUND r,o1,,,MRRM_ROUND_UP
	endm
	
	MR_FLOOR macro r,o1
		MR_ROUND r,o1,,,MRRM_ROUND_DOWN
	endm
	
	MR_TRUNCATE macro r,o1
		MR_ROUND r,o1,,,MRRM_TRUNCATE
	endm
	
	MR_FACTORIAL macro r,o1
	    MR_MOV r,?MRC_ONE
	    MR_MOV mrf_y,?MRC_ONE
	    mrf_pr = 1
	    mrf_py = 1
	    mrf_cntr = 0
	    WHILE mrf_cntr NE MR_TO_UINT32(o1)
	        MR_XMUL r,r,mrf_y,%mrf_pr+mrf_py,mrf_pr,mrf_py
            mrf_pr = MR_GET_N_SIGNIFICANT_WORDS(r,%mrf_pr+mrf_py)
            MR_ADD mrf_y,mrf_y,?MRC_ONE,,mrf_py
            mrf_cntr = mrf_cntr + 1
	    ENDM
		MR_CONVERT r,r,mrf_pr
	endm
	
	MR_SGN macro r,o1
		IF MR_IS_ZERO(o1)
			MR_LOAD_CONST r,zero
			EXITM
		ENDIF
		IF MR_IS_SIGN_MINUS(o1)
			MR_LOAD_CONST r,-one
			EXITM
		ENDIF
		MR_LOAD_CONST r,+one
	endm
	

	rpne_load_operand macro mreal,oprnd1,oprnd1_type
		IF oprnd1_type EQ SYATT_ID
			IF NOT MR_ID_IS_MREAL(<%oprnd1>)
				rpne_set_error RPNE_ERROR_ID_IS_NOT_MREAL, oprnd1
				EXITM
			ENDIF
		%	MR_MOV mreal,&oprnd1
		ELSE
		%	MREAL mreal = &oprnd1
		ENDIF
	endm

	RPNE_FNC_ONE_ARG macro FNC,sym
		
		rpnefoa_r TEXTEQU rpne_alloc_tmp_sym()
		
		mstck_pop operands,rpne_arg,rpne_arg_type
	
		rpne_load_operand ?o1?,rpne_arg,rpne_arg_type
		IF rpne_error
			EXITM
		ENDIF
		
	%	MR_&FNC &rpnefoa_r,?o1?

		IF rpne_debugging()
		%	echo sym( MR_TO_DECIMAL(?o1?,%RPNE_DEBUG) ) == MR_TO_DECIMAL(%rpnefoa_r,%RPNE_DEBUG)
		ENDIF
		
		rpne_result TEXTEQU rpnefoa_r
		mstck_push operands,rpne_result,SYATT_ID
	endm

	RPNE_FNC_MR_BIN macro FNC,sym,rel
		
		rpnefb_r TEXTEQU rpne_alloc_tmp_sym()
		
		mstck_pop operands,rpne_oprnd2,rpne_oprnd2_type
		mstck_pop operands,rpne_oprnd1,rpne_oprnd1_type
		
		rpne_load_operand ?o1?,rpne_oprnd1,rpne_oprnd1_type
		IF rpne_error
			EXITM
		ENDIF
		
		rpne_load_operand ?o2?,rpne_oprnd2,rpne_oprnd2_type
		IF rpne_error
			EXITM
		ENDIF
		IFNB <&rel>
		%	MR_CMP_RET_BOOL rpnefb_r,?o1?,?o2?,rel
		ELSE
		%	MR_&FNC rpnefb_r,?o1?,?o2?
		ENDIF
		IF rpne_debugging()
			%echo MR_TO_DECIMAL(?o1?,%RPNE_DEBUG) sym MR_TO_DECIMAL(?o2?,%RPNE_DEBUG) == MR_TO_DECIMAL(%rpnefb_r,%RPNE_DEBUG)
		ENDIF
		
		rpne_result TEXTEQU rpnefb_r
		mstck_push operands,rpne_result,SYATT_ID
	endm
	
	RPNE_FNC_assign_nargs = 2
		
	RPNE_FNC_assign macro
		
		rpnea_r TEXTEQU rpne_alloc_tmp_sym()
		
		mstck_pop operands,rpne_rhs,rpne_rhs_type
		mstck_pop operands,rpne_lhs,rpne_lhs_type
		
		IF rpne_lhs_type EQ SYATT_ID
			IF NOT MR_ID_IS_MREAL(<%rpne_lhs>)
			%	MR_CREATE &rpne_lhs
			ENDIF
			IFIDN <?MRC_PI>,rpne_lhs
				rpne_set_error RPNE_ERROR_CONST_AS_DEST, <<: pi>>
				EXITM
			ELSEIFIDN <?MRC_E>,rpne_lhs
				rpne_set_error RPNE_ERROR_CONST_AS_DEST, <<: e>>
				EXITM
			ELSEIFIDN <?MRC_ONE>,rpne_lhs
				rpne_set_error RPNE_ERROR_CONST_AS_DEST, <<: true>>
				EXITM
			ELSEIFIDN <?MRC_ZERO>,rpne_lhs
				rpne_set_error RPNE_ERROR_CONST_AS_DEST, <<: false>>
				EXITM
			ENDIF
			IF rpne_is_tmp_sym(<%rpne_lhs>)
				rpne_set_error RPNE_ERROR_CONST_AS_DEST, <<>>
				EXITM
			ENDIF
		ELSE
			rpne_set_error RPNE_ERROR_INVALID_DEST, rpne_lhs
			EXITM
		ENDIF
		
		rpne_load_operand ?o2?,rpne_rhs,rpne_rhs_type
		IF rpne_error
			EXITM
		ENDIF
		IF rpne_debugging()
		%	echo &rpne_lhs = MR_TO_DECIMAL(?o2?,%RPNE_DEBUG)
		ENDIF
	%	MR_MOV &rpne_lhs,?o2?
	%	MR_MOV &rpnea_r,?o2?
		rpne_result TEXTEQU rpnea_r
		mstck_push operands,rpne_result,SYATT_ID
	endm
	
	
	RPNE_FNC_fmadd_nargs = 3
		
	RPNE_FNC_fmadd macro
		
		rpnefma_r TEXTEQU rpne_alloc_tmp_sym()
		
		mstck_pop operands,rpne_o3,rpne_o3_type
		mstck_pop operands,rpne_o2,rpne_o2_type
		mstck_pop operands,rpne_o1,rpne_o1_type
		
		rpne_load_operand ?o1?,rpne_o1,rpne_o1_type
		IF rpne_error
			EXITM
		ENDIF		
		rpne_load_operand ?o2?,rpne_o2,rpne_o2_type
		IF rpne_error
			EXITM
		ENDIF
				
		rpne_load_operand ?o3?,rpne_o3,rpne_o3_type
		IF rpne_error
			EXITM
		ENDIF
	%	MR_FMADD &rpnefma_r,?o1?,?o2?,?o3?

		IF rpne_debugging()
			%echo fmadd: MR_TO_DECIMAL(?o1?,%RPNE_DEBUG) * MR_TO_DECIMAL(?o2?,%RPNE_DEBUG) + MR_TO_DECIMAL(?o3?,%RPNE_DEBUG) = MR_TO_DECIMAL(%rpnefma_r,%RPNE_DEBUG)
		ENDIF
	
		rpne_result TEXTEQU rpnefma_r
		mstck_push operands,rpne_result,SYATT_ID
	endm
	

	ceval macro expr:VARARG
		
		MR_SET_ZERO ans
		
		sya <&expr>
		IF sya_error
			.err sya_get_error_msg()
			EXITM
		ENDIF
		
		rpn_eval
		IF rpne_error
			.err rpne_get_error_msg()
			EXITM
		ENDIF
		
		mstck_pop operands,ceval_ans,ceval_ans_type
		IF ceval_ans_type EQ SYATT_ID
		%	MR_MOV ans,&ceval_ans
		ELSE
		%	MREAL ans = &ceval_ans
		ENDIF

	endm
	
	ccond macro expr:VARARG
		ceval expr
		IF MR_IS_ZERO(ans)
			EXITM <0>
		ENDIF
		EXITM <-1>
	endm
	
	cReal8 macro expr:VARARG
		ceval expr
		EXITM MR_TO_IEEE(<REAL8>,ans)
	endm
	
	cReal4 macro expr:VARARG
		ceval expr
		EXITM MR_TO_IEEE(<REAL4>,ans)
	endm
	
	cInt32 macro expr:VARARG
		ceval expr
		EXITM MR_TO_INT32(ans,throws)
	endm
	
	cUint32 macro expr:VARARG
		ceval expr
	%	EXITM MR_TO_UINT32(ans,throws)
	endm
	
	cInt64 macro expr:VARARG
		ceval expr
	%	EXITM MR_TO_INT64(ans,throws)
	endm
	
	cUint64 macro expr:VARARG
		ceval expr
	%	EXITM MR_TO_UINT64(ans,throws)
	endm
	
	defReal10 macro lbl:req,expr:VARARG
		ceval expr
		MR_DEF_REAL10 lbl,ans
	endm
	
	echo_mreal macro id:req,n_digits:=<6>
		IF NOT MR_ID_IS_MREAL(id)
			.err <id is not a MREAL value>
			EXITM
		ENDIF
		%echo id = MR_TO_DECIMAL(id,n_digits)
	endm
	
	echo_mreal_hex macro id:req,n_digits:=<6>
		IF NOT MR_ID_IS_MREAL(id)
			.err <id is not a MREAL value>
			EXITM
		ENDIF
		%echo id = MR_TO_IEEE_HEX_SEQ(id,n_digits)
	endm
	
ENDIF ; IFNDEF CEVAL_VERSION