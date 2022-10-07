/****************************************************************************
*
* This is a filter for pseudo instructions to reuce tons of instructions data
*
*****************************************************************************/
#include <ctype.h>

#include "globals.h"
#include "parser.h"

#ifdef _WIN32
#else

/**
	 * C++ version 0.4 char* style "itoa":
	 * Written by Lukás Chmela
	 * Released under GPLv3.

	 */
char* itoa(int value, char* result, int base) {
	// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, * ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + (tmp_value - value * base)];
	} while (value);

	// Apply negative sign
	if (tmp_value < 0)* ptr++ = '-';
	*ptr-- = '\0';
	while (ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr-- = *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}

#endif

int get_pseudoCMPXX(char* dst, char* p1, int index)
/******************************************************************/
{
  int i;

  switch (index) {
  case T_CMPEQPD:
  case T_CMPLTPD:
  case T_CMPLEPD:
  case T_CMPUNORDPD:
  case T_CMPNEQPD:
  case T_CMPNLTPD:
  case T_CMPNLEPD:
  case T_CMPORDPD:
    i = index - T_CMPEQPD;
    index = T_CMPPD;
    strcpy(dst, "cmppd");
    break;
  case T_CMPEQPS:
  case T_CMPLTPS:
  case T_CMPLEPS:
  case T_CMPUNORDPS:
  case T_CMPNEQPS:
  case T_CMPNLTPS:
  case T_CMPNLEPS:
  case T_CMPORDPS:
    i = index - T_CMPEQPS;
    index = T_CMPPS;
    strcpy(dst, "cmpps");
    break;
  case T_CMPEQSD:
  case T_CMPLTSD:
  case T_CMPLESD:
  case T_CMPUNORDSD:
  case T_CMPNEQSD:
  case T_CMPNLTSD:
  case T_CMPNLESD:
  case T_CMPORDSD:
    i = index - T_CMPEQSD;
    index = T_CMPSD;
    strcpy(dst, "cmpsd");
    break;
  case T_CMPEQSS:
  case T_CMPLTSS:
  case T_CMPLESS:
  case T_CMPUNORDSS:
  case T_CMPNEQSS:
  case T_CMPNLTSS:
  case T_CMPNLESS:
  case T_CMPORDSS:
    i = index - T_CMPEQSS;
    index = T_CMPSS;
    strcpy(dst, "cmpss");
    break;
  }
  memcpy(p1,dst,5);
  for (p1 += 5; *p1 > ' ';p1++)
    *p1 = ' ';
  while (*p1) p1++;
  *p1 = ',';
  p1++;
  *p1 = i + 0x30;
  p1++;
  *p1 = 0;
  return index;
}

int get_pseudoVCMPXX(char* dst, char* p1, int index)
/******************************************************************/
{
  int i;
  bool hadComment = FALSE;
  switch (index) {
  case T_VCMPEQPD:
  case T_VCMPLTPD:
  case T_VCMPLEPD:
  case T_VCMPUNORDPD:
  case T_VCMPNEQPD:
  case T_VCMPNLTPD:
  case T_VCMPNLEPD:
  case T_VCMPORDPD:
  case T_VCMPEQ_UQPD:
  case T_VCMPNGEPD:
  case T_VCMPNGTPD:
  case T_VCMPFALSEPD:
  case T_VCMPNEQ_OQPD:
  case T_VCMPGEPD:
  case T_VCMPGTPD:
  case T_VCMPTRUEPD:
  case T_VCMPEQ_OSPD:
  case T_VCMPLT_OQPD:
  case T_VCMPLE_OQPD:
  case T_VCMPUNORD_SPD:
  case T_VCMPNEQ_USPD:
  case T_VCMPNLT_UQPD:
  case T_VCMPNLE_UQPD:
  case T_VCMPORD_SPD:
  case T_VCMPEQ_USPD:
  case T_VCMPNGE_UQPD:
  case T_VCMPNGT_UQPD:
  case T_VCMPFALSE_OSPD:
  case T_VCMPNEQ_OSPD:
  case T_VCMPGE_OQPD:
  case T_VCMPGT_OQPD:
  case T_VCMPTRUE_USPD:
    i = index - T_VCMPEQPD;
    index = T_VCMPPD;
    strcpy(dst, "vcmppd");
    break;
  case T_VCMPEQPS:
  case T_VCMPLTPS:
  case T_VCMPLEPS:
  case T_VCMPUNORDPS:
  case T_VCMPNEQPS:
  case T_VCMPNLTPS:
  case T_VCMPNLEPS:
  case T_VCMPORDPS:
  case T_VCMPEQ_UQPS:
  case T_VCMPNGEPS:
  case T_VCMPNGTPS:
  case T_VCMPFALSEPS:
  case T_VCMPNEQ_OQPS:
  case T_VCMPGEPS:
  case T_VCMPGTPS:
  case T_VCMPTRUEPS:
  case T_VCMPEQ_OSPS:
  case T_VCMPLT_OQPS:
  case T_VCMPLE_OQPS:
  case T_VCMPUNORD_SPS:
  case T_VCMPNEQ_USPS:
  case T_VCMPNLT_UQPS:
  case T_VCMPNLE_UQPS:
  case T_VCMPORD_SPS:
  case T_VCMPEQ_USPS:
  case T_VCMPNGE_UQPS:
  case T_VCMPNGT_UQPS:
  case T_VCMPFALSE_OSPS:
  case T_VCMPNEQ_OSPS:
  case T_VCMPGE_OQPS:
  case T_VCMPGT_OQPS:
  case T_VCMPTRUE_USPS:
    i = index - T_VCMPEQPS;
    index = T_VCMPPS;
    strcpy(dst, "vcmpps");
    break;
  case T_VCMPEQSD:
  case T_VCMPLTSD:
  case T_VCMPLESD:
  case T_VCMPUNORDSD:
  case T_VCMPNEQSD:
  case T_VCMPNLTSD:
  case T_VCMPNLESD:
  case T_VCMPORDSD:
  case T_VCMPEQ_UQSD:
  case T_VCMPNGESD:
  case T_VCMPNGTSD:
  case T_VCMPFALSESD:
  case T_VCMPNEQ_OQSD:
  case T_VCMPGESD:
  case T_VCMPGTSD:
  case T_VCMPTRUESD:
  case T_VCMPEQ_OSSD:
  case T_VCMPLT_OQSD:
  case T_VCMPLE_OQSD:
  case T_VCMPUNORD_SSD:
  case T_VCMPNEQ_USSD:
  case T_VCMPNLT_UQSD:
  case T_VCMPNLE_UQSD:
  case T_VCMPORD_SSD:
  case T_VCMPEQ_USSD:
  case T_VCMPNGE_UQSD:
  case T_VCMPNGT_UQSD:
  case T_VCMPFALSE_OSSD:
  case T_VCMPNEQ_OSSD:
  case T_VCMPGE_OQSD:
  case T_VCMPGT_OQSD:
  case T_VCMPTRUE_USSD:
    i = index - T_VCMPEQSD;
    index = T_VCMPSD;
    strcpy(dst, "vcmpsd");
    break;
  case T_VCMPEQSS:
  case T_VCMPLTSS:
  case T_VCMPLESS:
  case T_VCMPUNORDSS:
  case T_VCMPNEQSS:
  case T_VCMPNLTSS:
  case T_VCMPNLESS:
  case T_VCMPORDSS:
  case T_VCMPEQ_UQSS:
  case T_VCMPNGESS:
  case T_VCMPNGTSS:
  case T_VCMPFALSESS:
  case T_VCMPNEQ_OQSS:
  case T_VCMPGESS:
  case T_VCMPGTSS:
  case T_VCMPTRUESS:
  case T_VCMPEQ_OSSS:
  case T_VCMPLT_OQSS:
  case T_VCMPLE_OQSS:
  case T_VCMPUNORD_SSS:
  case T_VCMPNEQ_USSS:
  case T_VCMPNLT_UQSS:
  case T_VCMPNLE_UQSS:
  case T_VCMPORD_SSS:
  case T_VCMPEQ_USSS:
  case T_VCMPNGE_UQSS:
  case T_VCMPNGT_UQSS:
  case T_VCMPFALSE_OSSS:
  case T_VCMPNEQ_OSSS:
  case T_VCMPGE_OQSS:
  case T_VCMPGT_OQSS:
  case T_VCMPTRUE_USSS:
    i = index - T_VCMPEQSS;
    index = T_VCMPSS;
    strcpy(dst, "vcmpss");
    break;
  }
  memcpy(p1, dst, 6);
  for (p1 += 6; *p1 > ' '; p1++)
    * p1 = ' ';
  while (*p1) {
      if (*p1 == ';') {
          hadComment = TRUE;
          break;
      }
      p1++;
  }
  *(p1)++ = ',';
  if (i <= 9) {
    *(p1)++ = i + 0x30;
    *p1 = 0;
  }
  else {
    itoa(i,p1,10);
  }
  return index;
}

int get_pseudoPCLMULXX(char* dst, char* p1, int index)
/******************************************************************/
{
    bool hadComment = FALSE;
    strcpy(dst, "pclmulqdq");
    memcpy(p1, dst, 9);
    for (p1 += 9; *p1 > ' '; p1++)
        * p1 = ' ';
    while (*p1)
    {
        if (*p1 == ';') {
            hadComment = TRUE;
            break;
        }
        p1++;
    } 
    *(p1)++ = ',';
    switch (index) {
    case T_PCLMULLQLQDQ:
        *(p1)++ = '0';
        if (hadComment) {
            *(p1)++ = ';';
        }
        break;
  case T_PCLMULHQLQDQ:
        *(p1)++ = '1';
        if (hadComment) {
            *(p1)++ = ';';
        }
        break;
  case T_PCLMULLQHQDQ:
        *(p1)++ = '1';
        *(p1)++ = '6';
        if (hadComment) {
            *(p1)++ = ';';
        }
        break;
  case T_PCLMULHQHQDQ:
        *(p1)++ = '1';
        *(p1)++ = '7';
        if (hadComment) {
            *(p1)++ = ';';
        }
        break;
  }
  index = T_PCLMULQDQ;
  *p1 = 0;
  return index;
}

int get_pseudoVPCLMULXX(char* dst, char* p1, int index)
/******************************************************************/
{
    bool hadComment = FALSE;
    strcpy(dst, "vpclmulqdq");
    memcpy(p1, dst, 10);
    for (p1 += 10; *p1 > ' '; p1++)
        * p1 = ' ';
    while (*p1) {
        if (*p1 == ';') {
            hadComment = TRUE;
            break;
        }
        p1++;
    }
    *(p1)++ = ',';
    switch (index) {
    case T_VPCLMULLQLQDQ:
        *(p1)++ = '0';
        if (hadComment) {
            *(p1)++ = ';';
        }
        break;
    case T_VPCLMULHQLQDQ:
        *(p1)++ = '1';
        if (hadComment) {
            *(p1)++ = ';';
        }
        break;
    case T_VPCLMULLQHQDQ:
        *(p1)++ = '1';
        *(p1)++ = '6';
        if (hadComment) {
            *(p1)++ = ';';
        }
        break;
    case T_VPCLMULHQHQDQ:
        *(p1)++ = '1';
        *(p1)++ = '7';
        if (hadComment) {
            *(p1)++ = ';';
        }
        break;
    }
    index = T_VPCLMULQDQ;
    *p1 = 0;
    return index;
}


