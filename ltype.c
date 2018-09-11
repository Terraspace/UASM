
#include "globals.h"

unsigned char _ltype[257] = {
	0,			/* -1 EOF   */
	_LCONTROL,		/* 00 (NUL) */
	_LCONTROL,		/* 01 (SOH) */
	_LCONTROL,		/* 02 (STX) */
	_LCONTROL,		/* 03 (ETX) */
	_LCONTROL,		/* 04 (EOT) */
	_LCONTROL,		/* 05 (ENQ) */
	_LCONTROL,		/* 06 (ACK) */
	_LCONTROL,		/* 07 (BEL) */
	_LCONTROL,		/* 08 (BS)  */
	_LSPACE + _LCONTROL,	/* 09 (HT)  */
	_LSPACE + _LCONTROL,	/* 0A (LF)  */
	_LSPACE + _LCONTROL,	/* 0B (VT)  */
	_LSPACE + _LCONTROL,	/* 0C (FF)  */
	_LSPACE + _LCONTROL,	/* 0D (CR)  */
	_LCONTROL,		/* 0E (SI)  */
	_LCONTROL,		/* 0F (SO)  */
	_LCONTROL,		/* 10 (DLE) */
	_LCONTROL,		/* 11 (DC1) */
	_LCONTROL,		/* 12 (DC2) */
	_LCONTROL,		/* 13 (DC3) */
	_LCONTROL,		/* 14 (DC4) */
	_LCONTROL,		/* 15 (NAK) */
	_LCONTROL,		/* 16 (SYN) */
	_LCONTROL,		/* 17 (ETB) */
	_LCONTROL,		/* 18 (CAN) */
	_LCONTROL,		/* 19 (EM)  */
	_LCONTROL,		/* 1A (SUB) */
	_LCONTROL,		/* 1B (ESC) */
	_LCONTROL,		/* 1C (FS)  */
	_LCONTROL,		/* 1D (GS)  */
	_LCONTROL,		/* 1E (RS)  */
	_LCONTROL,		/* 1F (US)  */
	_LSPACE,		/* 20 SPACE */
	_LPUNCT,		/* 21 !	    */
	_LPUNCT,		/* 22 ""    */
	_LPUNCT,		/* 23 #	    */
	_LPUNCT + _LABEL,		/* 24 $	    */
	_LPUNCT,		/* 25 %	    */
	_LPUNCT,		/* 26 &	    */
	_LPUNCT,		/* 27 '     */
	_LPUNCT,		/* 28 (	    */
	_LPUNCT,		/* 29 )	    */
	_LPUNCT,		/* 2A *	    */
	_LPUNCT,		/* 2B +	    */
	_LPUNCT,		/* 2C ,	    */
	_LPUNCT,		/* 2D -	    */
	_LPUNCT,		/* 2E .	    */
	_LPUNCT,		/* 2F /	    */
	_LDIGIT + _LHEX,		/* 30 0	    */
	_LDIGIT + _LHEX,		/* 31 1	    */
	_LDIGIT + _LHEX,		/* 32 2	    */
	_LDIGIT + _LHEX,		/* 33 3	    */
	_LDIGIT + _LHEX,		/* 34 4	    */
	_LDIGIT + _LHEX,		/* 35 5	    */
	_LDIGIT + _LHEX,		/* 36 6	    */
	_LDIGIT + _LHEX,		/* 37 7	    */
	_LDIGIT + _LHEX,		/* 38 8	    */
	_LDIGIT + _LHEX,		/* 39 9	    */
	_LPUNCT,		/* 3A :	    */
	_LPUNCT,		/* 3B ;	    */
	_LPUNCT,		/* 3C <	    */
	_LPUNCT,		/* 3D =	    */
	_LPUNCT,		/* 3E >	    */
	_LPUNCT + _LABEL,		/* 3F ?	    */
	_LPUNCT + _LABEL,		/* 40 @	    */
	_LUPPER + _LABEL + _LHEX,	/* 41 A	    */
	_LUPPER + _LABEL + _LHEX,	/* 42 B	    */
	_LUPPER + _LABEL + _LHEX,	/* 43 C	    */
	_LUPPER + _LABEL + _LHEX,	/* 44 D	    */
	_LUPPER + _LABEL + _LHEX,	/* 45 E	    */
	_LUPPER + _LABEL + _LHEX,	/* 46 F	    */
	_LUPPER + _LABEL,		/* 47 G	    */
	_LUPPER + _LABEL,		/* 48 H	    */
	_LUPPER + _LABEL,		/* 49 I	    */
	_LUPPER + _LABEL,		/* 4A J	    */
	_LUPPER + _LABEL,		/* 4B K	    */
	_LUPPER + _LABEL,		/* 4C L	    */
	_LUPPER + _LABEL,		/* 4D M	    */
	_LUPPER + _LABEL,		/* 4E N	    */
	_LUPPER + _LABEL,		/* 4F O	    */
	_LUPPER + _LABEL,		/* 50 P	    */
	_LUPPER + _LABEL,		/* 51 Q	    */
	_LUPPER + _LABEL,		/* 52 R	    */
	_LUPPER + _LABEL,		/* 53 S	    */
	_LUPPER + _LABEL,		/* 54 T	    */
	_LUPPER + _LABEL,		/* 55 U	    */
	_LUPPER + _LABEL,		/* 56 V	    */
	_LUPPER + _LABEL,		/* 57 W	    */
	_LUPPER + _LABEL,		/* 58 X	    */
	_LUPPER + _LABEL,		/* 59 Y	    */
	_LUPPER + _LABEL,		/* 5A Z	    */
	_LPUNCT,		/* 5B [	    */
	_LPUNCT,		/* 5C \	    */
	_LPUNCT,		/* 5D ]	    */
	_LPUNCT,		/* 5E ^	    */
	_LPUNCT + _LABEL,		/* 5F _	    */
	_LPUNCT,		/* 60 `	    */
	_LLOWER + _LABEL + _LHEX,	/* 61 a	    */
	_LLOWER + _LABEL + _LHEX,	/* 62 b	    */
	_LLOWER + _LABEL + _LHEX,	/* 63 c	    */
	_LLOWER + _LABEL + _LHEX,	/* 64 d	    */
	_LLOWER + _LABEL + _LHEX,	/* 65 e	    */
	_LLOWER + _LABEL + _LHEX,	/* 66 f	    */
	_LLOWER + _LABEL,		/* 67 g	    */
	_LLOWER + _LABEL,		/* 68 h	    */
	_LLOWER + _LABEL,		/* 69 i	    */
	_LLOWER + _LABEL,		/* 6A j	    */
	_LLOWER + _LABEL,		/* 6B k	    */
	_LLOWER + _LABEL,		/* 6C l	    */
	_LLOWER + _LABEL,		/* 6D m	    */
	_LLOWER + _LABEL,		/* 6E n	    */
	_LLOWER + _LABEL,		/* 6F o	    */
	_LLOWER + _LABEL,		/* 70 p	    */
	_LLOWER + _LABEL,		/* 71 q	    */
	_LLOWER + _LABEL,		/* 72 r	    */
	_LLOWER + _LABEL,		/* 73 s	    */
	_LLOWER + _LABEL,		/* 74 t	    */
	_LLOWER + _LABEL,		/* 75 u	    */
	_LLOWER + _LABEL,		/* 76 v	    */
	_LLOWER + _LABEL,		/* 77 w	    */
	_LLOWER + _LABEL,		/* 78 x	    */
	_LLOWER + _LABEL,		/* 79 y	    */
	_LLOWER + _LABEL,		/* 7A z	    */
	_LPUNCT,		/* 7B {	    */
	_LPUNCT,		/* 7C |	    */
	_LPUNCT,		/* 7D }	    */
	_LPUNCT,		/* 7E ~	    */
	_LCONTROL,		/* 7F (DEL) */
					/* and the rest are 0... */
};
