/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  command line argument parser
*
****************************************************************************/

//#include <stdarg.h>
#include <stddef.h>
#include <ctype.h>

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "msgtext.h"
#include "dbgcv.h"
#include "cmdline.h"
#include "myassert.h"
#include "input.h" /* GetFNamePart() */

//#ifdef __OSI__
//  #include "ostype.h"
//#endif

#if defined(__UNIX__) || defined(__CYGWIN__) || defined(__DJGPP__)

#define HANDLECTRLZ 0
#define SWITCHCHAR 0

#else

#define HANDLECTRLZ 1
#define SWITCHCHAR 1

#endif

#ifdef __I86__
#define OPTQUAL __near
#else
#define OPTQUAL
#endif

extern char     banner_printed;

struct global_options Options = {
    /* quiet            */          FALSE,
    /* line_numbers     */          FALSE,
    /* debug_symbols    */          0,
    /* debug_ext        */          0, /* v2.10 */
    /* floating_point   */          FPO_NO_EMULATION,

    /* error_limit      */          50,
    /* no error display */          FALSE,
    /* warning_level    */          2,
    /* warning_error    */          FALSE,
#ifdef DEBUG_OUT
    /* debug            */          FALSE,
    /* nobackpatch      */          FALSE,
#if FASTPASS
    /* nofastpass       */          FALSE,
    /* print_linestore  */          FALSE,
#endif
    /* max_passes       */          0,
    /* skip_preprocessor */         0,
    /* log_all_files    */          0,
    /* dump_reswords    */          FALSE,
    /* dump_reswords_hash */        FALSE,
    /* dump_symbols     */          FALSE,
    /* dump_symbols_hash */         FALSE,
#endif
    /* names            */          {
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
#if BUILD_TARGET
        NULL,
#endif
#if MANGLERSUPP
        NULL
#endif
    },
    /* queues           */          { NULL, NULL, NULL },
#if COCTALS
    /* allow_c_octals        */     FALSE,
#endif
    /* no_comment_data_in_code_records */   FALSE,
    /* no_opt_farcall        */     FALSE,
    /* no_dependencies       */ //    FALSE,
#if COFF_SUPPORT
    /* no_file_entry         */     FALSE,
    /* no_static_procs       */     FALSE,
    /* no_section_aux_entry  */     FALSE,
#endif
    /* no_cdecl_decoration   */     FALSE,
    /* stdcall_decoration    */     STDCALL_FULL,
    /* no_export_decoration  */     FALSE,
    /* entry_decorated       */     FALSE,
    /* write_listing         */     FALSE,
    /* write_impdef          */     FALSE,
    /* case_sensitive        */     FALSE,
    /* convert_uppercase     */     FALSE,
    /* preprocessor_stdout   */     FALSE,
    /* masm51_compat         */     FALSE,
    /* strict_masm_compat    */     FALSE,
    /* masm_compat_gencode   */     FALSE,
    /* masm8_proc_visibility */     FALSE,

    /* listif                */     FALSE,
    /* list_generated_code   */     FALSE,
    /* list_macro            */     LM_LISTMACRO,
    /* no_symbol_listing     */     FALSE,
    /* first_pass_listing    */     FALSE,

    /* all_symbols_public    */     FALSE,
    /* safeseh               */     FALSE,
    /* ignore_include        */     FALSE,
    /* output_format         */     OFORMAT_OMF,
    /* sub_format            */     SFORMAT_NONE,
    /* alignment_default     */     0,
    /* langtype              */     LANG_NONE,
    /* model                 */     MODEL_NONE,
    /* cpu                   */     P_86,
    /* fastcall type         */     FCT_MSC,
    /* syntax check only     */     FALSE,
#if MANGLERSUPP
    /* naming_convention*/          NC_DO_NOTHING,
#endif
};

char *DefaultDir[NUM_FILE_TYPES] = { NULL, NULL, NULL, NULL };
//static char *DefaultExt[NUM_FILE_TYPES] = { OBJ_EXT, LST_EXT, ERR_EXT };

#define MAX_RSP_NESTING 15  /* nesting of response files */

static unsigned         OptValue;  /* value of option's numeric argument  */
static char             *OptName;  /* value of option's name argument     */
static const char       *cmdsave[MAX_RSP_NESTING]; /* response files */
static const char       *cmdbuffers[MAX_RSP_NESTING]; /* response files */
static int              rspidx = 0; /* response file level */

/* array for options -0 ... -10 */
static const enum cpu_info cpuoption[] = {
    P_86, P_186, P_286, P_386,          /* 0-3 */
    P_486, P_586, P_686, P_686 | P_MMX, /* 4-7 */
    P_686 | P_MMX | P_SSE1,             /* 8   */
    P_686 | P_MMX | P_SSE1 | P_SSE2,    /* 9   */
#if AMD64_SUPPORT
    P_64,                               /* 10  */
#endif
};

#if 0 /* v2.10: removed, because factually never called */
static void StripQuotes( char *fname )
/************************************/
{
    char *s;
    char *d;

    if( *fname == '"' ) {
        /* string will shrink so we can reduce in place */
        d = fname;
        for( s = d + 1; *s && *s != '"'; ++s ) {
            /* collapse double backslashes, only then look for escaped quotes */
            if( s[0] == '\\' && s[1] == '\\' ) {
                ++s;
            } else if( s[0] == '\\' && s[1] == '"' ) {
                ++s;
            }
            *d++ = *s;
        }
        *d = '\0';
    }
}

static char *GetAFileName( void )
/*******************************/
{
    DebugMsg(("GetAFileName() enter, OptName=>%s<\n", OptName ));
    StripQuotes( OptName );
    return( OptName );
}
#else
#define GetAFileName() OptName
#endif

#if BUILD_TARGET
static void SetTargName( char *name, unsigned len )
/*************************************************/
{
    if( Options.names[OPTN_BUILD_TARGET] != NULL ) {
        MemFree( Options.names[OPTN_BUILD_TARGET] );
        Options.names[OPTN_BUILD_TARGET] = NULL;
    }
    if( name == NULL || len == 0 )
        return;
    Options.names[OPTN_BUILD_TARGET] = MemAlloc( len + 1 );
    strcpy( Options.names[OPTN_BUILD_TARGET], name );
    _strupr( Options.names[OPTN_BUILD_TARGET] );
}
#endif

/* called by -0, -1, ... argument */

static void SetCpuCmdline( enum cpu_info value, const char *parm )
/****************************************************************/
{

    Options.cpu &= ~(P_CPU_MASK | P_EXT_MASK | P_PM);
    Options.cpu |= value;

    for( ; *parm ; parm++ ) {
        if( *parm == 'p' && Options.cpu >= P_286 ) {
            Options.cpu |= P_PM;      /* set privileged mode */
#if MANGLERSUPP
        } else if( *parm == '"' ) {       /* set default mangler */
            char *dest;
            parm++;
            dest = strchr( parm, '"' );
            if( Options.names[OPTN_DEFNAME_MANGLER] != NULL ) {
                MemFree( Options.names[OPTN_DEFNAME_MANGLER );
            }
            Options.names[OPTN_DEFNAME_MANGLER = MemAlloc( dest - parm + 1 );
            dest = Options.names[OPTN_DEFNAME_MANGLER];
            for( ; *parm != '"'; dest++, parm++ ) {
                *dest = *parm;
            }
            *dest = NULLC;
#endif
        } else {
            EmitWarn( 1, CPU_OPTION_INVALID, parm );
            break;
        }
    }
}

/* queue a text macro, include path or "forced" include files.
   this is called for cmdline options -D, -I and -Fi
 */

static void queue_item( int i, const char *string )
/*************************************************/
{
    struct qitem *p;
    struct qitem *q;

    DebugMsg(("queue_item(%u, %s) enter\n", i, string));
    p = MemAlloc( sizeof(struct qitem) + strlen( string ) );
    p->next = NULL;
    strcpy( p->value, string );
    q = Options.queues[i];
    if ( q ) {
        for ( ; q->next; q = q->next );
        q->next = p;
    } else
        Options.queues[i] = p;
    return;
}

static void get_fname( int type, const char *token )
/**************************************************/
/*
 * called by -Fo, -Fw or -Fl (for .OBJ, .ERR or .LST filenames ).
 * also called by -Fd; in this case type is > NUM_FILE_TYPES!
 * v2.12: _splitpath()/_makepath() removed.
 */
{
    const char  *pName;
    char        name [ FILENAME_MAX ];

    DebugMsg(("get_fname( type=%u, >%s< ) enter\n", type, token ));
    //_splitpath( token, drive, dir, fname, ext );
    pName = GetFNamePart( token );
    /*
     * If name's ending with a '\' (or '/' in Unix), it's supposed
     * to be a directory name only.
     */
    if( *pName == NULLC ) {
        DebugMsg(("get_fname(%u, >%s< ) name is empty or a directory\n", type, token ));
        /* v2.10: ensure type is < NUM_FILE_TYPES */
        if ( type < NUM_FILE_TYPES ) {
            if ( DefaultDir[type] )
                MemFree( DefaultDir[type]);
            DefaultDir[type] = MemAlloc( strlen( token ) + 1 );
            strcpy( DefaultDir[type], token );
        }
        return;
    }
    /* v2.10: ensure type is < NUM_FILE_TYPES */
    //if ( drive[0] == NULLC && dir[0] == NULLC && type < NUM_FILE_TYPES && DefaultDir[type] ) {
    name[0] = NULLC;
    if ( pName == token && type < NUM_FILE_TYPES && DefaultDir[type] ) {
        DebugMsg(("get_fname: default drive+dir used: %s\n" ));
        //_splitpath( DefaultDir[type], drive, dir, NULL, NULL );
        strcpy( name, DefaultDir[type] );
    }
    strcat( name, token );
#if 0 /* v2.12: extension will be set in SetFileNames() */
    if( type && type < NUM_FILE_TYPES ) {
        char *pExt = GetExtPart( name );
        if ( *pExt == NULLC ) {
            *pExt++ = '.';
            strcpy( pExt, DefaultExt[type-1] );
        }
    }
#endif
    //_makepath( name, drive, dir, fname, pExt );
    if( Options.names[type] != NULL ) {
        MemFree( Options.names[type] );
    }
    Options.names[type] = MemAlloc( strlen( name ) + 1 );
    strcpy( Options.names[type], name );
}

static void set_option_n_name( int idx, const char *name )
/********************************************************/
/* option -n: set name of
 * - nd: data seg
 * - nm: module name
 * - nt: text seg
 * - nc: code class
 */
{
    if ( *name != '.' && !is_valid_id_char( *name ) ) {
        EmitError( N_OPTION_NEEDS_A_NAME_PARAMETER );
        return;
    }

    if( Options.names[idx] != NULL ) {
        MemFree( Options.names[idx] );
    }
    Options.names[idx] = MemAlloc( strlen( name ) + 1 );
    strcpy( Options.names[idx], name );
}

//static void OPTQUAL Ignore( void ) {};

#if BUILD_TARGET
static void OPTQUAL Set_bt( void ) { SetTargName( OptName,  strlen(OptName) ); }
#endif

static void OPTQUAL Set_c( void ) { }

#ifdef DEBUG_OUT
static void OPTQUAL Set_ce( void ) { rspidx = 1 / rspidx; }
#endif

static void OPTQUAL Set_Cp( void ) { Options.case_sensitive = TRUE;   Options.convert_uppercase = FALSE; }
static void OPTQUAL Set_Cu( void ) { Options.case_sensitive = FALSE;  Options.convert_uppercase = TRUE;  }
static void OPTQUAL Set_Cx( void ) { Options.case_sensitive = FALSE;  Options.convert_uppercase = FALSE; }

static void OPTQUAL Set_Zd( void ) { Options.line_numbers = TRUE; }
static void OPTQUAL Set_Zi( void )
{
    Set_Zd();
    Options.debug_symbols = CV_SIGNATURE;
    /* v2.10: added optional numeric argument for -Zi */
    if ( OptValue <= CVEX_MAX )
        Options.debug_ext = OptValue;
    else
        EmitWarn( 1, INVALID_CMDLINE_VALUE, "Zi" );
}

static void OPTQUAL Set_Zp( void )
/********************************/
{
    uint_8 power;
    for ( power = 0; (1 << power) <= MAX_STRUCT_ALIGN; power++ )
        if ( ( 1 << power ) == OptValue ) {
            Options.fieldalign = power;
            return;
        }
    EmitWarn( 1, INVALID_CMDLINE_VALUE, "Zp" );
    return;
}

static void OPTQUAL Set_D( void )  { queue_item( OPTQ_MACRO,    GetAFileName() ); }
static void OPTQUAL Set_Fi( void ) { queue_item( OPTQ_FINCLUDE, GetAFileName() ); }
static void OPTQUAL Set_I( void )  { queue_item( OPTQ_INCPATH,  GetAFileName() ); }

static void OPTQUAL Set_e( void ) { Options.error_limit = OptValue; }

static void OPTQUAL Set_nologo( void ) { banner_printed = TRUE; }
static void OPTQUAL Set_q( void )      { Set_nologo(); Options.quiet = TRUE; }
static void OPTQUAL Set_EP( void ) { Options.preprocessor_stdout = TRUE; Set_q(); }

#if DLLIMPORT
static void OPTQUAL Set_Fd( void ) { get_fname( OPTN_LNKDEF_FN, GetAFileName() ); Options.write_impdef = TRUE;}
#endif
static void OPTQUAL Set_Fw( void ) { get_fname( OPTN_ERR_FN, GetAFileName() ); }
static void OPTQUAL Set_Fl( void ) { get_fname( OPTN_LST_FN, GetAFileName() ); Options.write_listing = TRUE;}
static void OPTQUAL Set_Fo( void ) { get_fname( OPTN_OBJ_FN, GetAFileName() ); }

static void OPTQUAL Set_fp( void ) { Options.cpu &= ~P_FPU_MASK; Options.cpu = OptValue; }
static void OPTQUAL Set_FPx( void ) { Options.floating_point = OptValue; }
static void OPTQUAL Set_G( void ) { Options.langtype = OptValue; }

static void OPTQUAL Set_Sa( void )
/********************************/
{
    Options.listif = TRUE;
    Options.list_generated_code = TRUE;
    Options.list_macro = LM_LISTMACROALL;
}

static void OPTQUAL Set_True( void )
/**********************************/
{
    char *p = ((char *)&Options) + OptValue;
    *p = TRUE;
}

static void OPTQUAL Set_m( void ) { Options.model = OptValue; }
static void OPTQUAL Set_n( void ) { set_option_n_name( OptValue, OptName ); }

#ifdef DEBUG_OUT
static void OPTQUAL Set_pm( void ) { Options.max_passes = OptValue; };
#endif

static void OPTQUAL Set_WX( void ) { Options.warning_error = TRUE; }

static void OPTQUAL Set_w( void ) { Set_WX(); Options.warning_level = 0; }

static void OPTQUAL Set_W( void )
/*******************************/
{
    if ( OptValue <= 4 )
        Options.warning_level = OptValue;
    else
        EmitWarn( 1, INVALID_CMDLINE_VALUE, "W" );
}

static void OPTQUAL Set_ofmt( void )
/**********************************/
{
    Options.output_format = OptValue & 0xff;
    Options.sub_format = OptValue >> 8;
}

static void OPTQUAL Set_zcm( void ) { Options.no_cdecl_decoration = FALSE; }
#if OWFC_SUPPORT
static void OPTQUAL Set_zf( void )  { Options.fctype = OptValue; }
#endif

static void OPTQUAL Set_zt( void ) { Options.stdcall_decoration = OptValue; }
#ifndef __SW_BD
static void OPTQUAL Set_h( void ) {  PrintUsage();  exit(1); }
#endif

#ifdef DEBUG_OUT
static void OPTQUAL Set_dm( void )
{
    int i;
    for ( i = 0; i < MSG_LAST; i++ ) {
        printf("%3u: %s\n", i, MsgGetEx(i) );
    }
}
static void OPTQUAL Set_dt( void )
/********************************/
{
    Options.debug = TRUE;
    ModuleInfo.cref = TRUE; /* enable debug displays */
    DebugMsg(( "debugging output on\n" ));
}
#if FASTPASS
static void OPTQUAL Set_nfp( void )
/*********************************/
{
    Options.nofastpass = TRUE;
    DebugMsg(( "FASTPASS disabled\n" ));
}
#endif
static void OPTQUAL Set_nbp( void )
/*********************************/
{
    Options.nobackpatch = TRUE;
    DebugMsg(( "backpatching disabled\n" ));
}
#endif

struct  cmdloption {
    const char  *name;
    unsigned    value;
    void OPTQUAL (*function)( void );
};

#define optofs( x ) offsetof( struct global_options, x )

/*
 * '#': collect a number
 * '$': collect an identifer[=value]
 * '@': collect a filename
 * '=': collect an optional '='
 * '^': skip spaces before argument
 */
static struct cmdloption const cmdl_options[] = {
#ifndef __SW_BD
    { "?",      0,        Set_h },
#endif
#ifdef DEBUG_OUT
    { "af",     optofs( log_all_files ), Set_True },
#endif
#if BIN_SUPPORT
    { "bin",    OFORMAT_BIN | (SFORMAT_NONE << 8), Set_ofmt },
#endif
#if BUILD_TARGET
    { "bt=$",   0,        Set_bt },
#endif
    { "Cp",     0,        Set_Cp },
    { "Cu",     0,        Set_Cu },
    { "Cx",     0,        Set_Cx },
#ifdef DEBUG_OUT
    { "ce",     0,        Set_ce },
#endif
#if COFF_SUPPORT
    { "coff",   OFORMAT_COFF | (SFORMAT_NONE << 8), Set_ofmt },
#endif
    { "c",      0,        Set_c },
#if COFF_SUPPORT && DJGPP_SUPPORT
    { "djgpp",  OFORMAT_COFF | (SFORMAT_DJGPP << 8), Set_ofmt },
#endif
#ifdef DEBUG_OUT
    { "dm",     0,        Set_dm },
    { "drh",    optofs( dump_reswords_hash ), Set_True },
    { "dr",     optofs( dump_reswords ),    Set_True },
    { "dsh",    optofs( dump_symbols_hash ), Set_True },
    { "ds",     optofs( dump_symbols ),     Set_True },
    { "dt",     0,        Set_dt },
#endif
    { "D^$",    0,        Set_D },
#if ELF_SUPPORT
#if AMD64_SUPPORT
    { "elf64",  OFORMAT_ELF | (SFORMAT_64BIT << 8), Set_ofmt },
#endif
    { "elf",    OFORMAT_ELF | (SFORMAT_NONE << 8), Set_ofmt },
#endif
    { "EP",     0,        Set_EP },
    { "eq",     optofs( no_error_disp ),        Set_True },
    { "e=#",    0,        Set_e },
#if DLLIMPORT
    { "Fd=@",   0,        Set_Fd },
#endif
    { "Fi=^@",  0,        Set_Fi },
    { "Fl=@",   0,        Set_Fl },
    { "Fo=^@",  0,        Set_Fo },
    { "FPi87",  FPO_NO_EMULATION, Set_FPx },
    { "FPi",    FPO_EMULATION,    Set_FPx },
    { "fp0",    P_87,     Set_fp },
    { "fp2",    P_287,    Set_fp },
    { "fp3",    P_387,    Set_fp },
#if 0
    { "fp5",    P_387,    Set_fp },
    { "fp6",    P_387,    Set_fp },
#endif
    { "fpc",    P_NO87,   Set_fp },
    { "Fw=^@",  0,        Set_Fw },
    { "Gc",     LANG_PASCAL,  Set_G },
    { "Gd",     LANG_C,       Set_G },
    { "Gr",     LANG_FASTCALL,Set_G },
    { "Gz",     LANG_STDCALL, Set_G },
    { "h",      0,        Set_h },
    { "I=^@",   0,        Set_I },
#ifdef DEBUG_OUT
#if FASTPASS
    { "ls",     optofs( print_linestore ), Set_True },
#endif
#endif
    { "mc",     MODEL_COMPACT, Set_m },
    { "mf",     MODEL_FLAT,    Set_m },
    { "mh",     MODEL_HUGE,    Set_m },
    { "ml",     MODEL_LARGE,   Set_m },
    { "mm",     MODEL_MEDIUM,  Set_m },
    { "ms",     MODEL_SMALL,   Set_m },
    { "mt",     MODEL_TINY,    Set_m },
#if BIN_SUPPORT
#if MZ_SUPPORT
    { "mz",     OFORMAT_BIN | (SFORMAT_MZ << 8), Set_ofmt },
#endif
#endif
#ifdef DEBUG_OUT
    { "nbp",    0,                  Set_nbp },
#endif
    { "nc=$",   OPTN_CODE_CLASS,    Set_n },
    { "nd=$",   OPTN_DATA_SEG,      Set_n },
#if FASTPASS && defined(DEBUG_OUT)
    { "nfp",    0,                  Set_nfp },
#endif
    { "nm=$",   OPTN_MODULE_NAME,   Set_n },
    { "nologo", 0,                  Set_nologo },
    { "nt=$",   OPTN_TEXT_SEG,      Set_n },
    { "omf",    OFORMAT_OMF | (SFORMAT_NONE << 8), Set_ofmt },
#if COCTALS
    { "o",      optofs( allow_c_octals ),   Set_True },
#endif
#if PE_SUPPORT
    { "pe",     OFORMAT_BIN | (SFORMAT_PE << 8), Set_ofmt },
#endif
#ifdef DEBUG_OUT
    { "pm=#",   0,        Set_pm },
#endif
    { "q",      0,        Set_q },
    { "Sa",     0,        Set_Sa },
    { "Sf",     optofs( first_pass_listing  ), Set_True },
    { "Sg",     optofs( list_generated_code ), Set_True },
    { "Sn",     optofs( no_symbol_listing   ), Set_True },
    { "Sx",     optofs( listif              ), Set_True },
#if COFF_SUPPORT
    { "safeseh",optofs( safeseh ),        Set_True },
#endif
#ifdef DEBUG_OUT
    { "sp",     optofs( skip_preprocessor ), Set_True },
#endif
    { "WX",     0,        Set_WX },
    { "W=#",    0,        Set_W },
#if AMD64_SUPPORT
    { "win64",  OFORMAT_COFF | (SFORMAT_64BIT << 8), Set_ofmt },
#endif
    { "w",      0,        Set_w },
    { "X",      optofs( ignore_include ), Set_True },
    { "Zd",     0,        Set_Zd },
    { "Zf",     optofs( all_symbols_public ),  Set_True },
    { "Zg",     optofs( masm_compat_gencode ), Set_True },
    { "Zi=#",   CVEX_NORMAL, Set_Zi },
    { "Zm",     optofs( masm51_compat ),      Set_True },
    { "Zne",    optofs( strict_masm_compat ), Set_True },
    { "Zp=#",   0,        Set_Zp },
    { "zcm",    0,        Set_zcm },
    { "zcw",    optofs( no_cdecl_decoration ), Set_True },
#if OWFC_SUPPORT
    { "zf0",    FCT_MSC,     Set_zf },
    { "zf1",    FCT_WATCOMC, Set_zf },
#endif
    { "zlc",    optofs( no_comment_data_in_code_records ), Set_True },
    { "zld",    optofs( no_opt_farcall ),       Set_True },
#if COFF_SUPPORT
    { "zlf",    optofs( no_file_entry ),        Set_True },
    { "zlp",    optofs( no_static_procs ),      Set_True }, /* v2.10: added */
    { "zls",    optofs( no_section_aux_entry ), Set_True },
#endif
    { "Zs",     optofs( syntax_check_only ), Set_True },
    { "zt0",    STDCALL_NONE, Set_zt },
    { "zt1",    STDCALL_HALF, Set_zt },
    { "zt2",    STDCALL_FULL, Set_zt },
    { "Zv8",    optofs( masm8_proc_visibility ), Set_True },
    { "zze",    optofs( no_export_decoration ),  Set_True },
#if COFF_SUPPORT
    { "zzs",    optofs( entry_decorated ),       Set_True },
#endif
//    { NULL,     0,        0 }
};

/*
 * get a "name"
 * type=@ : filename ( -Fd, -Fi, -Fl, -Fo, -Fw, -I )
 * type=$ : (macro) identifier [=value] ( -D, -nc, -nd, -nm, -nt )
 * type=0 : something else ( -0..-10 )
 */
static const char *GetNameToken( char *dst, const char *str, int max, char type )
/*******************************************************************************/
{
    bool equatefound = FALSE;

    DebugMsg(("GetNameToken( %s, %u, '%c' ) enter, rspidx=%u\n", str, max, type, rspidx ));
    //while( isspace( *str ) ) ++str;  /* no spaces allowed! */
is_quote:
    if( *str == '"' ) {
        ++str;
        for( ; max && *str; max-- ) {
            if ( *str == '"' ) {
                ++str;
                break;
            }
            /* handle the \" case */
            if ( *str == '\\' && *(str+1) == '"' ) {
                ++str;
            }
            *dst++ = *str++;
        }
    } else {
        for( ; max; max-- ) {
            /* v2.10: don't stop for white spaces */
            //if ( *str == NULLC || *str == ' ' || *str == '\t' )
            if ( *str == NULLC )
                break;
            /* v2.10: don't stop for white spaces if filename is expected and true cmdline is parsed */
            if ( ( *str == ' ' || *str == '\t' ) && ( rspidx || type != '@' ) )
                break;
            if ( type == 0 )
                if ( *str == '-'
#if SWITCHCHAR
                    || *str == '/'
#endif
                   )
                    break;
            if ( *str == '=' && type == '$' && equatefound == FALSE ) {
                equatefound = TRUE;
                *dst++ = *str++;
                if (*str == '"')
                    goto is_quote;
            }
            *dst++ = *str++;
        }
    }
    *dst = NULLC;
    return( str );
}

/*
 * A '@' was found in the cmdline. It's not an environment variable,
 * so check if it is a file and, if yes, read it.
 */

static char *ReadParamFile( const char *name )
/********************************************/
{
    char        *env;
    char        *str;
    FILE        *file;
    int         len;
    char        ch;

    DebugMsg(("ReadParamFile(%s) enter\n"));
    env = NULL;
    file = fopen( name, "rb" );
    if( file == NULL ) {
        /* v2.10: changed to fatal error */
        //EmitErr( CANNOT_OPEN_FILE, name, ErrnoStr() );
        Fatal( CANNOT_OPEN_FILE, name, ErrnoStr() );
        return( NULL );
    }
    len = 0;
    if ( fseek( file, 0, SEEK_END ) == 0 ) {
        len = ftell( file );
        rewind( file );
        env = MemAlloc( len + 1 );
#if defined(__GNUC__) /* gcc warns if return value of fread() is "ignored" */
        if ( fread( env, 1, len, file ) );
#else
        fread( env, 1, len, file );
#endif
        env[len] = NULLC;
    }
    fclose( file );
    if ( len == 0)
        return( NULL );
    /* zip through characters changing \r, \n etc into ' ' */
    str = env;
    while( *str ) {
        ch = *str;
        if( ch == '\r' || ch == '\n' ) {
            *str = ' ';
        }
#if HANDLECTRLZ
        if( ch == 0x1A ) {      /* if end of file */
            *str = '\0';        /* - mark end of str */
            break;
        }
#endif
        ++str;
    }
    return( env );
}

/* current cmdline string is done, get the next one! */

static const char *getnextcmdstring( const char **cmdline )
/*********************************************************/
{
    const char **src;
    const char **dst;

    /* something onto the response file stack? */
    if ( rspidx ) {
        rspidx--;
        if ( cmdbuffers[rspidx] )
            MemFree( (void *)cmdbuffers[rspidx] );
        return( cmdsave[rspidx] );
    }
    for ( dst = cmdline, src = cmdline+1; *src; )
        *dst++ = *src++;
    *dst = *src;
    return( *cmdline );
}

static const char *GetNumber( const char *p )
/*******************************************/
{
    OptValue = 0;
    for( ;*p >= '0' && *p <= '9'; p++ )
        OptValue = OptValue * 10 + *p - '0';
    return( p );
}

#if SWITCHCHAR
#define IsOptionDelimiter( x ) (x == ' ' || x == '-' || x == '/' || x == NULLC || x == '\t' )
#else
#define IsOptionDelimiter( x ) (x == ' ' || x == '-' || x == NULLC || x == '\t' )
#endif

/* scan option table and if option is known, process it */

static void ProcessOption( const char **cmdline, char *buffer )
/*************************************************************/
{
    int   i;
    int   j;
    const char *p = *cmdline;
    const char *opt;
    //char  c;

    DebugMsg(("ProcessOption(%s)\n", p ));

    /* numeric option (-0, -1, ... ) handled separately since
     * the value can be >= 10.
     */
    if ( *p >= '0' && *p <= '9' ) {
        p = GetNumber( p );
        if ( OptValue < sizeof(cpuoption)/sizeof(cpuoption[0]) ) {
            p = GetNameToken( buffer, p, 16, 0 ); /* get optional 'p' */
            *cmdline = p;
            SetCpuCmdline( cpuoption[OptValue], buffer );
            return;
        }
        p = *cmdline; /* v2.11: restore option pointer */
    }
    for( i = 0; i < ( sizeof(cmdl_options) / sizeof(cmdl_options[0]) ); i++ ) {
        //DebugMsg(("ProcessOption(%s): %s\n", p, opt ));
        if( *p == *cmdl_options[i].name ) {
            for ( opt = cmdl_options[i].name+1, j = 1 ; isalnum(*opt) && *opt == p[j]; opt++, j++ );
            /* make sure end of option is reached */
            if ( isalnum(*opt) )
                continue;
            p += j;
            OptValue = cmdl_options[i].value;
            //DebugMsg(("ProcessOption(%s): Option found\n", p ));
            for( ;; opt++) {
                switch ( *opt ) {
                //case '*': /* don't know what this is supposed to do? */
                case NULLC:
                    if ( !IsOptionDelimiter( *p ) )
                        goto opt_error_exit;
                    *cmdline = p;
                    cmdl_options[i].function();
                    return; /* option processed successfully */
                    break;
                case '#':             /* collect a number */
                    if( *p >= '0' && *p <= '9' )
                        p = GetNumber( p );
                    break;
                case '$':      /* collect an identifer+value */
                case '@':      /* collect a filename */
                    OptName = buffer;
#if 0  /* v2.05: removed */
                    if ( rspidx )
                        p = GetNameToken( buffer, p, FILENAME_MAX - 1, *opt );
                    else {
                        j = strlen( p );
                        memcpy( buffer, p, (j >= FILENAME_MAX) ? FILENAME_MAX : j + 1 );
                        p += j;
                    }
#else
                    /* v2.10: spaces in filename now handled inside GetNameToken() */
                    p = GetNameToken( buffer, p, FILENAME_MAX - 1, *opt );
#endif
                    break;
                case '=':    /* collect an optional '=' */
                    if ( *p == '=' || *p == '#' )
                        p++;
                    break;
                case '^':    /* skip spaces before argument */
                    while ( isspace(*p) ) p++;
                    if ( *p == NULLC ) {
                        p = getnextcmdstring( cmdline );
                        if ( p == NULL ) {
                            EmitWarn( 1, MISSING_ARGUMENT_FOR_CMDLINE_OPTION );
                            return;
                        }
                    }
                    break;
                default:
                    /* internal error: unknown format of option item! */
                    DebugMsg(( "ProcessOption: unknown option specifier: %s\n", opt ));
                    /**/myassert( 0 );
                    break;
                }
            }
        }
    }
opt_error_exit:
    EmitWarn( 1, INVALID_CMDLINE_OPTION, *cmdline - 1 );
    *cmdline = "";
    return;
}

#if BUILD_TARGET

#define MAX_OS_NAME_SIZE 7

static void set_default_build_target( void )
/******************************************/
{

    if( Options.names[OPTN_BUILD_TARGET] == NULL ) {
        Options.names[OPTN_BUILD_TARGET] = MemAlloc( MAX_OS_NAME_SIZE + 1 );
#if defined(__OSI__)
        if( __OS == OS_DOS ) {
            strcpy( Options.names[OPTN_BUILD_TARGET], "DOS" );
        } else if( __OS == OS_OS2 ) {
            strcpy( Options.names[OPTN_BUILD_TARGET], "OS2" );
        } else if( __OS == OS_NT ) {
            strcpy( Options.names[OPTN_BUILD_TARGET], "NT" );
        } else if( __OS == OS_WIN ) {
            strcpy( Options.names[OPTN_BUILD_TARGET], "WINDOWS" );
        } else {
            strcpy( Options.names[OPTN_BUILD_TARGET], "XXX" );
        }
#elif defined(__QNX__)
        strcpy( Options.names[OPTN_BUILD_TARGET], "QNX" );
#elif defined(__LINUX__)
        strcpy( Options.names[OPTN_BUILD_TARGET], "LINUX" );
#elif defined(__BSD__)
        strcpy( Options.names[OPTN_BUILD_TARGET], "BSD" );
#elif defined(__OSX__) || defined(__APPLE__)
        strcpy( Options.names[OPTN_BUILD_TARGET], "OSX" );
#elif defined(__DOS__)
        strcpy( Options.names[OPTN_BUILD_TARGET], "DOS" );
#elif defined(__OS2__)
        strcpy( Options.names[OPTN_BUILD_TARGET], "OS2" );
#elif defined(__NT__)
        strcpy( Options.names[OPTN_BUILD_TARGET], "NT" );
#else
        #error unknown host OS
#endif
    }
    return;
}
#endif

/* parse cmdline:
 * - process cmdline options
 * - get filename argument
 * - handle (nested) response files
 */

char * EXPQUAL ParseCmdline( const char **cmdline, int *pCntArgs )
/****************************************************************/
{
    int i;
    const char *str = *cmdline;
    char paramfile[FILENAME_MAX];

    for ( i = 0; i < NUM_FILE_TYPES; i++ )
        if ( Options.names[i] != NULL ) {
            MemFree( Options.names[i] );
            Options.names[i] = NULL;
        }

    /* enable next line if debug log is to be active, but -dt cannot be set */
    //Set_dt();

    for( ; str; ) {
        switch( *str ) {
        case ' ':
        case '\t':
            str++;
            break;
        case NULLC:
            str = getnextcmdstring( cmdline );
            break;
        case '-':
#if SWITCHCHAR
        case '/':
#endif
            str++;
            *cmdline = str;
            ProcessOption( cmdline, paramfile );
            (*pCntArgs)++;
            str = *cmdline;
            break;
        case '@':
            if ( rspidx >= MAX_RSP_NESTING ) {
                EmitErr( NESTING_LEVEL_TOO_DEEP );
                *cmdline = "";
                return( NULL );
            }
            str++;
#if 1 /* v2.06: was '0' in v2.05, now '1' again since it didn't work with quoted names */
            /* todo: might be unnecessary since v.2.10, since GetNameToken() handles spaces inside filenames differently */
            if ( rspidx ) {
                cmdsave[rspidx] = GetNameToken( paramfile, str, sizeof( paramfile ) - 1, '@' );
            } else {
                strcpy( paramfile, str ); /* fixme: no overflow check */
                cmdsave[rspidx] = str + strlen(str);
            }
#else
            cmdsave[rspidx] = GetNameToken( paramfile, str, sizeof( paramfile ) - 1, '@' );
#endif
            cmdbuffers[rspidx] = NULL;
            str = NULL;
            if ( paramfile[0] )
                str = getenv( paramfile );
            if( str == NULL ) {
                str = ReadParamFile( paramfile );
                cmdbuffers[rspidx] = str;
                if ( str == NULL ) {
                    str = cmdsave[rspidx];
                    break;
                }
            }
            rspidx++;
            break;
        default: /* collect  file name */
#if BUILD_TARGET
            set_default_build_target();
#endif
#if 1 /* v2.06: activated (was removed in v2.05). Needed for quoted filenames */
            if ( rspidx ) {
                str = GetNameToken( paramfile, str, sizeof( paramfile ) - 1, '@' );
                get_fname( OPTN_ASM_FN, paramfile );
            } else {
                int len;
                len = strlen( str );
                get_fname( OPTN_ASM_FN, str );
                str += len;
            }
#else
            str = GetNameToken( paramfile, str, sizeof( paramfile ) - 1, '@' );
            Options.names[ASM] = MemAlloc( strlen( paramfile ) + 1 );
            strcpy( Options.names[ASM], paramfile );
#endif
            DebugMsg(("ParseCmdLine: file=>%s< rest=>%s<\n", Options.names[ASM], str ? str : "NULL" ));
            (*pCntArgs)++;
            *cmdline = str;
            return( Options.names[ASM] );
        }
    }
    *cmdline = str;
    return( NULL );
}

void EXPQUAL CmdlineFini( void )
/******************************/
/* Free resources allocated by cmdline options */
{
    int i;
    DebugMsg(("CmdLineFini enter\n" ));
    for ( i = 0; i < NUM_FILE_TYPES; i++ ) {
        if ( DefaultDir[i] != NULL ) {
            MemFree( DefaultDir[i] );
            DefaultDir[i] = NULL;
        }
    }
    for ( i = 0; i < OPTN_LAST; i++ )
        if ( Options.names[i] != NULL ) {
            MemFree( Options.names[i] );
            Options.names[i] = NULL;
        }
    for ( i = 0; i < OPTQ_LAST; i++ ) {
        struct qitem *p;
        struct qitem *q;
        for ( q = Options.queues[i]; q; ) {
            p = q->next;
            MemFree( q );
            q = p;
        }
        Options.queues[i] = NULL;
    }
    DebugMsg(("CmdLineFini exit\n" ));
    return;
}

