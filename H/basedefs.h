#pragma once

#ifndef _BASEDEFS_H_
#define _BASEDEFS_H_

// Helper macros to convert value of macro to string literal.
#ifndef _uasm_Stringer
#       define _uasm_Stringer(x) #x
#endif
#ifndef uasm_Stringer
#       define uasm_Stringer(x)  _uasm_Stringer(x)
#endif

#ifndef _uasm_Con_Stringer
#define _uasm_Con_Stringer(a, b) a##b
#endif
#ifndef uasm_Con_Stringer
#define uasm_Con_Stringer(a, b) _uasm_Con_Stringer(a, b)
#endif

/**
Compiler defines
*/
#if defined(_MSC_VER) && (!defined(__INTEL_COMPILER) && !defined(__clang__) && !defined(__CUDA_ARCH__) && !defined(__CUDACC__))
#ifndef uasm_VC
#       define uasm_VC 1  /* MSVC Compiler */
#endif
#ifndef uasm_MSVC_COMPILER
#       define uasm_MSVC_COMPILER 1  /* MSVC Compiler */
#endif
#undef uasm_COMPILER_STR
#       define uasm_COMPILER_STR "vc"
#   if defined(_MSC_VER) && (_MSC_VER == 1200)
#       define uasm_VC6 1
#       define uasm_COMPILER "Microsoft Visual C++ 6"
#   elif defined(_MSC_VER) && (_MSC_VER == 1300)
#       define uasm_VC7 1
#       define uasm_COMPILER "Microsoft Visual C++ 7"
#   elif defined(_MSC_VER) && (_MSC_VER == 1400)
#       define uasm_VC8 1
#       define uasm_COMPILER "Microsoft Visual C++ 8"
#   elif defined(_MSC_VER) && (_MSC_VER == 1500)
#       define uasm_VC9 1
#       define uasm_COMPILER "Microsoft Visual C++ 9"
#   elif defined(_MSC_VER) && (_MSC_VER == 1600)
#       define uasm_VC10 1
#       define uasm_COMPILER "Microsoft Visual C++ 10"
#   elif defined(_MSC_VER) && (_MSC_VER == 1700)
#       define uasm_VC11 1
#       define uasm_COMPILER "Microsoft Visual C++ 11"
#   elif defined(_MSC_VER) && (_MSC_VER == 1800)
#       define uasm_VC12 1
#       define uasm_COMPILER "Microsoft Visual C++ 12"
#   elif defined(_MSC_VER) && (_MSC_VER == 1900)
#       define uasm_VC14 1
#       define uasm_COMPILER "Microsoft Visual C++ 14"
#   elif defined(_MSC_VER) && (_MSC_VER == 1910)
#       define uasm_VC14_1 1
#       define uasm_COMPILER "Microsoft Visual C++ 15.0"
#   elif defined(_MSC_VER) && (_MSC_VER == 1911)
#       define uasm_VC14_11 1
#       define uasm_COMPILER "Microsoft Visual C++ 15.3"
#   elif defined(_MSC_VER) && (_MSC_VER == 1912)
#       define uasm_VC14_12 1
#       define uasm_COMPILER "Microsoft Visual C++ 15.5"
#   elif defined(_MSC_VER) && (_MSC_VER == 1913)
#       define uasm_VC14_13 1
#       define uasm_COMPILER "Microsoft Visual C++ 15.6"
#   elif defined(_MSC_VER) && (_MSC_VER == 1914)
#       define uasm_VC14_14 1
#       define uasm_COMPILER "Microsoft Visual C++ 15.7"
#   elif defined(_MSC_VER) && (_MSC_VER == 1915)
#       define uasm_VC14_15 1
#       define uasm_COMPILER "Microsoft Visual C++ 15.8"
#   elif defined(_MSC_VER) && (_MSC_VER == 1916)
#       define uasm_VC14_16 1
#       define uasm_COMPILER "Microsoft Visual C++ 15.9"
#   elif defined(_MSC_VER) && (_MSC_VER == 1920)
#       define uasm_VC14_2 1
#       define uasm_COMPILER "Microsoft Visual C++ 16.0"
#   elif defined(_MSC_VER) && (_MSC_VER == 1921)
#       define uasm_VC14_21 1
#       define uasm_COMPILER "Microsoft Visual C++ 16.1.2"
#   elif defined(_MSC_VER) && (_MSC_VER == 1922)
#       define uasm_VC14_22 1
#       define uasm_COMPILER "Microsoft Visual C++ 16.2.0"
#   elif defined(_MSC_VER) && (_MSC_VER == 1923)
#       define uasm_VC14_23 1
#       define uasm_COMPILER "Microsoft Visual C++ 16.2.3"
#   elif defined(_MSC_VER) && (_MSC_VER == 1924)
#       define uasm_VC14_24 1
#       define uasm_COMPILER "Microsoft Visual C++ 16.2.4"
#   elif defined(_MSC_VER) && (_MSC_VER == 1925)
#       define uasm_VC14_25 1
#       define uasm_COMPILER "Microsoft Visual C++ 16.2.5"
#   elif defined(_MSC_VER) && (_MSC_VER == 1926)
#       define uasm_VC14_26 1
#       define uasm_COMPILER "Microsoft Visual C++ 16.2.6"
#   elif defined(_MSC_VER) && (_MSC_VER == 1927)
#       define uasm_VC14_27 1
#       define uasm_COMPILER "Microsoft Visual C++ 16.2.7"
#   elif defined(_MSC_VER) && (_MSC_VER == 1928)
#       define uasm_VC14_28 1
#       define uasm_COMPILER "Microsoft Visual C++ 16.2.8"
#   else
#error ERROR: add your vc compiler version
#   endif
#   if defined(_MSC_VER) && ((_MSC_VER >= 1600) && (_MSC_VER < 1800))
#     ifdef uasm_COMPILER_INTRIN
#       undef uasm_COMPILER_INTRIN
#     endif
#       define uasm_COMPILER_INTRIN 50
#   endif
#   if defined(_MSC_VER) && ((_MSC_VER >= 1700) && (_MSC_VER < 1911))
#     ifdef uasm_COMPILER_INTRIN
#       undef uasm_COMPILER_INTRIN
#     endif
#       define uasm_COMPILER_INTRIN 52
#   endif
#   if defined(_MSC_VER) && (_MSC_VER >= 1911)
#     ifdef uasm_COMPILER_INTRIN
#       undef uasm_COMPILER_INTRIN
#     endif
#       define uasm_COMPILER_INTRIN 60
#   endif
#elif defined(__INTEL_COMPILER) && !defined(__CUDA_ARCH__) && !defined(__CUDACC__)
# if defined(_MSC_VER)
#  ifndef uasm_ICW
#       define uasm_ICW 1 /* Intel compiler for Windows */
#  endif
#undef uasm_COMPILER_STR
#       define uasm_COMPILER_STR "icw"
#else
#  ifndef uasm_ICU
#       define uasm_ICU 1 /* Intel compiler for Unix/Linux/Mac OSX */
#  endif
#undef uasm_COMPILER_STR
#       define uasm_COMPILER_STR "icu"
# endif
#  ifndef uasm_ICC
#       define uasm_ICC 1 /* Intel compiler for Windows/Unix/Linux/Mac OSX */
#  endif
#  ifndef uasm_INTEL_COMPILER
#       define uasm_INTEL_COMPILER 1 /* Intel compiler */
#  endif
#if defined(__INTEL_COMPILER) && (__INTEL_COMPILER == 1010)
#       define uasm_ICC101 1
#       define uasm_COMPILER "Intel C++ Compiler 10.1"
#elif defined(__INTEL_COMPILER) && (__INTEL_COMPILER == 1100)
#       define uasm_ICC110 1
#       define uasm_COMPILER "Intel C++ Compiler 11.0"
#elif defined(__INTEL_COMPILER) && (__INTEL_COMPILER == 1110)
#       define uasm_ICC111 1
#       define uasm_COMPILER "Intel C++ Compiler 11.1"
#elif defined(__INTEL_COMPILER) && (__INTEL_COMPILER == 1200)
#       define uasm_ICC120 1
#       define uasm_COMPILER "Intel C++ Compiler 12.0"
#elif defined(__INTEL_COMPILER) && (__INTEL_COMPILER == 1210)
#       define uasm_ICC121 1
#       define uasm_COMPILER "Intel C++ Compiler 12.1"
#elif defined(__INTEL_COMPILER) && (__INTEL_COMPILER == 1300)
#       define uasm_ICC130 1
#       define uasm_COMPILER "Intel C++ Compiler 13.0"
#elif defined(__INTEL_COMPILER) && (__INTEL_COMPILER == 1310)
#       define uasm_ICC131 1
#       define uasm_COMPILER "Intel C++ Compiler 13.1"
#elif defined(__INTEL_COMPILER) && (__INTEL_COMPILER == 1400)
#       define uasm_ICC140 1
#       define uasm_COMPILER "Intel C++ Compiler 14.0"
#elif defined(__INTEL_COMPILER) && (__INTEL_COMPILER == 1410)
#       define uasm_ICC141 1
#       define uasm_COMPILER "Intel C++ Compiler 14.1"
#       define uasm_COMPILER_INTRIN 52
#elif defined(__INTEL_COMPILER) && (__INTEL_COMPILER == 1500)
#       define uasm_ICC150 1
#       define uasm_COMPILER "Intel C++ Compiler 15.0"
#       define uasm_COMPILER_INTRIN 52
#elif defined(__INTEL_COMPILER) && (__INTEL_COMPILER == 1501)
#       define uasm_ICC1501 1
#       define uasm_COMPILER "Intel C++ Compiler 15.0.1"
#       define uasm_COMPILER_INTRIN 60
#elif defined(__INTEL_COMPILER) && (__INTEL_COMPILER == 1600)
#       define uasm_ICC1600 1
#       define uasm_COMPILER "Intel C++ Compiler 16.0.0"
#       define uasm_COMPILER_INTRIN 60
#elif defined(__INTEL_COMPILER) && (__INTEL_COMPILER == 1700)
#       define uasm_ICC1700 1
#       define uasm_COMPILER "Intel C++ Compiler 17.0.0"
#       define uasm_COMPILER_INTRIN 60
#elif defined(__INTEL_COMPILER) && (__INTEL_COMPILER == 1800)
#       define uasm_ICC1800 1
#       define uasm_COMPILER "Intel C++ Compiler 18.0.0"
#       define uasm_COMPILER_INTRIN 60
#elif defined(__INTEL_COMPILER) && (__INTEL_COMPILER == 1900)
#       define uasm_ICC1900 1
#       define uasm_COMPILER "Intel C++ Compiler 19.0.0"
#       define uasm_COMPILER_INTRIN 60
#elif defined(__INTEL_COMPILER) && (__INTEL_COMPILER == 9999)
#       define uasm_ICC9999 1
#       define uasm_COMPILER "Intel C++ Compiler mainline"
#else
#error ERROR: Unknown version or add your Intel compiler version
#endif
#elif defined(__clang__) && !defined(__CUDA_ARCH__) && !defined(__CUDACC__)
# if defined(_MSC_VER)
#  ifndef uasm_CLANGW
#       define uasm_CLANGW 1 /* Clang compiler for Windows */
#  endif
#undef uasm_COMPILER_STR
#       define uasm_COMPILER_STR "clangw"
#else
#  ifndef uasm_CLANGU
#       define uasm_CLANGU 1 /* Clang compiler for Unix/Linux/Mac OSX */
#  endif
#undef uasm_COMPILER_STR
#       define uasm_COMPILER_STR "clangu"
# endif
#ifndef uasm_CLANG
#       define uasm_CLANG 1
#endif
#       define uasm_COMPILER "Clang " uasm_Stringer(__clang_major__) "." uasm_Stringer(__clang_minor__)
# if defined(__clang_major__) && (((__clang_major__ >=3) && (__clang_minor__ >=9)) || (__clang_major__ >=4))
#       define uasm_COMPILER_INTRIN 60
# endif
#elif (defined(__GNUC__) || defined(__GCC__) || defined(__SNC__)) && !defined(__clang__) && !defined(__INTEL_COMPILER) && !defined(__CUDA_ARCH__) && !defined(__CUDACC__)
# if defined(__GNUC__)
#       define uasm_GNUC 1
# endif
# if  defined(__GCC__)
#   if defined(_MSC_VER)
#       define uasm_GCCW 1
#   else
#       define uasm_GCCU 1
#   endif
#       define uasm_GCC 1
# endif
# if  defined(__SNC__)
#       define uasm_SNC 1
# endif
#       define uasm_COMPILER "GNUC " uasm_Stringer(__GNUC__) "." uasm_Stringer(__GNUC_MINOR__)
# if defined(__GNUC__) && (((__GNUC__ >=4) && (__GNUC_MINOR__ >=9)) || (__GNUC__ >=5))
#       define uasm_COMPILER_INTRIN 60
# endif
#elif defined(__xlc__) || defined(__xlC__) || defined(__IBMC__) || defined(__IBMCPP__) && !defined(__CUDA_ARCH__) && !defined(__CUDACC__)
#       define uasm_IBMC 1
#       define uasm_IBM_COMPILER 1
#undef uasm_COMPILER_STR
#       define uasm_COMPILER_STR "ibmc"
#       define uasm_COMPILER "IBMC " uasm_Stringer(__IBMC__) "." uasm_Stringer(__IBMC_MINOR__)
#elif defined(__PGI) && !defined(__CUDA_ARCH__) && !defined(__CUDACC__)
#       define uasm_PGI 1
#       define uasm_PGI_COMPILER 1
#undef uasm_COMPILER_STR
#       define uasm_COMPILER_STR "pgi"
#       define uasm_COMPILER "PGI " uasm_Stringer(__PGI__) "." uasm_Stringer(__PGI_MINOR__)
#elif defined(__APPLE_CC__) && !defined(__CUDA_ARCH__) && !defined(__CUDACC__)
#       define uasm_APPLECC 1
#       define uasm_APPLE_COMPILER 1
#undef uasm_COMPILER_STR
#       define uasm_COMPILER_STR "applecc"
#       define uasm_COMPILER "APPLECC " uasm_Stringer(__APPLE_CC__) "." uasm_Stringer(__APPLE_CC_MINOR__)
#elif defined(__BORLANDC__) || defined(__CODEGEARC__) && !defined(__CUDA_ARCH__) && !defined(__CUDACC__)
#       define uasm_BORLAND 1
#undef uasm_COMPILER_STR
#       define uasm_COMPILER_STR "borland"
#       define uasm_COMPILER "EMBARCADERO " uasm_Stringer(__BORLANDC__) "." uasm_Stringer(__BORLANDC_MINOR__)
#elif defined(__PATHCC__) && !defined(__CUDA_ARCH__) && !defined(__CUDACC__)
#       define uasm_PATHCC 1
#       define uasm_PATHCC_COMPILER 1
#undef uasm_COMPILER_STR
#       define uasm_COMPILER_STR "pathscale"
#       define uasm_COMPILER "Pathscale " uasm_Stringer(__PATHCC__) "." uasm_Stringer(__PATHCC_MINOR__)
#elif defined(__ghs__) && !defined(__CUDA_ARCH__) && !defined(__CUDACC__)
#       define uasm_GHS 1
#elif defined(__CC_ARM) || defined(__ARMCC__)
#       define uasm_ARMCC 1
#       define uasm_ARM_COMPILER 1
#undef uasm_COMPILER_STR
#       define uasm_COMPILER_STR "armcc"
#       define uasm_COMPILER "ARMCC " uasm_Stringer(__ARMCC__) "." uasm_Stringer(__ARMCC_MINOR__)
#elif defined(__MWERKS__) && !defined(__CUDA_ARCH__) && !defined(__CUDACC__)
#       define uasm_MWERKS 1
#elif defined(__CUDA_ARCH__) || defined(__CUDACC__)
#       define uasm_CUDA 1
#       define uasm_CUDACC 1
#       define uasm_CUDA_COMPILER 1
#  if defined(_MSC_VER)
#       define uasm_CUDAW 1 /* Nvidia Cuda compiler for Windows */
#  else
#       define uasm_CUDAU 1 /* Nvidia Cuda compiler for Unix */
#  endif
#undef uasm_COMPILER_STR
#       define uasm_COMPILER_STR "cudacc"
#       define uasm_COMPILER "Nvidia Cuda Compiler " uasm_Stringer(__CUDACC__) "." uasm_Stringer(__CUDACC_MINOR__)
#else
# error ERROR: Unknown compiler
# error ERROR: Compiler needs to be implemented
#endif

#if defined(uasm_VC) || defined(uasm_CLANGW) || defined(uasm_ICW) || defined(uasm_GCCW) /*|| defined(uasm_CLANGW) incompatible types definitions*/
#       define uasm_MSVC_COMPATIBLE_COMPILER 1
#endif

#if defined(uasm_GNUC) || defined(uasm_GCC) || defined(uasm_SNC) || defined(uasm_ICU) || defined(uasm_CLANGU) || defined(uasm_ARMCC) || defined(uasm_GHS)
#       define uasm_GCC_COMPATIBLE_COMPILER 1
#endif

////////////////////////////////////////////////////////////////////////////
// Arch type :
//
//          1 32-bits x86
//          2 64-bits x86_64
//          3 Xbox 360
//          4 ps3
//          5 wiiu
//          6 ppc
//          7 ppc64
//          8 arm32bits
//          9 arm64bits
#       define uasm_ARCH 0

#       define uasm_ENDIAN_LITTLE 0
#       define uasm_ENDIAN_BIG    0

/* CUDA targets must be detected first as nvcc also predefined gcc macros for CPU architecture */
#if defined(__CUDA_ARCH__) || defined(__CUDACC__)
#       define uasm_CUDA_GPU 1
#elif (defined(_M_IX86) || defined(_WIN32) || defined(__i386__) || defined(i386) || defined(__i386) || defined(_X86_) || defined(__X86__) \
    || defined(__I86__) || defined(__INTEL__) || defined(__THW_INTEL__))  && !defined(_WIN64) && ! defined(_M_ARM) && !defined(_ARM) && !defined(__KNC__) && !defined(__MIC__)
#       define uasm_X86 1
#       define uasm_X86_CPU 1
#       define uasm_X86_ABI 1
#       define uasm_ARCH_X86 1
#       define uasm_PLATFORM_X86 1
#undef uasm_ENDIAN_LITTLE
#       define uasm_ENDIAN_LITTLE 1
#       define uasm_PTR_SIZE 4
#       define uasm_SIZE_T_SIZE 4
#       define uasm_STACK_SIZE 8
#       define uasm_INTRINSICS 1
#       define uasm_ARCH_SUPPORTS_INT64 1
#       define uasm_NUM_SIMD_REGISTERS 8
#       define uasm_ARCH_STR "x86"
#undef uasm_ARCH
#       define uasm_ARCH 1
# elif defined(_M_X64) || defined(_M_AMD64) || defined(_WIN64) || defined(__amd64__) || defined(__amd64) || defined(__x86_64) || defined(__x86_64__) || defined(_LP64) || defined(__LP64__) && !defined(__KNC__) && !defined(__MIC__)
#       define uasm_X64 1
#       define uasm_X64_CPU 1
#       define uasm_X64_ABI 1
#       define uasm_ARCH_X64 1
#undef uasm_ENDIAN_LITTLE
#       define uasm_ENDIAN_LITTLE 1
#       define uasm_PTR_SIZE 8
#       define uasm_SIZE_T_SIZE 8
#       define uasm_STACK_SIZE 16
#       define uasm_INTRINSICS 1
#       define uasm_ARCH_SUPPORTS_DOUBLE 1
#       define uasm_ARCH_SUPPORTS_INT64 1
#       define uasm_NUM_SIMD_REGISTERS 16
#undef uasm_ARCH
#       define uasm_ARCH 2
#   if defined(__ORBIS__)
#       define uasm_PS4 1
#       define uasm_ARCH_PS4 1
#       define uasm_PLATFORM_PS4 1
#       define uasm_PLATFORM_IS_CONSOLE 1
#       define uasm_ARCH_STR "PS4"
#   elif defined(_XBOX_ONE)
#       define uasm_XBOXONE 1
#       define uasm_ARCH_XBOXONE 1
#       define uasm_PLATFORM_XBOXONE 1
#       define uasm_PLATFORM_IS_CONSOLE 1
#       define uasm_ARCH_STR "XBOXOne"
#   else
#       define uasm_ARCH_STR "x64"
#   endif
#       define uasm_PLATFORM_X64 1
#elif  defined(__KNC__) || defined(__MIC__)
#  ifndef uasm_MIC
#       define uasm_MIC 1 /* Intel MIC or Xeon Phi architecture */
#  endif
#       define uasm_MIC_ARCH 1 /* Intel MIC or Xeon Phi architecture */
#       define uasm_PLATFORM_MIC 1
#       define uasm_PLATFORM_IS_CPU_ACCELARATOR 1
# if defined(_M_IX86) /*|| defined(_WIN32)*/ || defined(__i386__) || defined(i386) || defined(__i386) || defined(_X86_) || defined(__X86__) || defined(__I86__)
# error ERROR: Unavailable for Intel Intel® Xeon Phi™ builds.
# error ERROR: Solutions/projects targeting the Intel® Xeon Phi™ coprocessor are limited to using the x64 Debug | Release configuration.
# error ERROR: Please change your build enviroment to X64 builds.
/*
#       define uasm_X86 1
#       define uasm_X86_ABI 1
#       define uasm_ARCH_X86 1
#       define uasm_PLATFORM_X86 1
#undef uasm_ENDIAN_LITTLE
#       define uasm_ENDIAN_LITTLE 1
#       define uasm_PTR_SIZE 4
#       define uasm_SIZE_T_SIZE 4
#       define uasm_STACK_SIZE 8
#       define uasm_INTRINSICS 1
#       define uasm_NUM_SIMD_REGISTERS 16
#       define uasm_ARCH_STR "x86"
#undef uasm_ARCH
#       define uasm_ARCH 1*/
# elif defined(_M_X64) || defined(_M_AMD64) || defined(_WIN64) || defined(__amd64__) || defined(__amd64) || defined(__x86_64) || defined(__x86_64__) || defined(__LP64__)
#       define uasm_X64 1
#       define uasm_X64_CPU 1
#       define uasm_X64_ABI 1
#       define uasm_ARCH_X64 1
#undef uasm_ENDIAN_LITTLE
#       define uasm_ENDIAN_LITTLE 1
#       define uasm_PTR_SIZE 8
#       define uasm_SIZE_T_SIZE 8
#       define uasm_STACK_SIZE 16
#       define uasm_INTRINSICS 1
#       define uasm_ARCH_SUPPORTS_DOUBLE 1
#       define uasm_ARCH_SUPPORTS_INT64 1
#       define uasm_NUM_SIMD_REGISTERS 32
#       define uasm_ARCH_STR "x64"
#       define uasm_PLATFORM_X64 1
#undef uasm_ARCH
#       define uasm_ARCH 2
# endif
#elif defined(_M_IA64) || defined(__itanium__) || defined(__ia64) || defined(__ia64__) || defined(_IA64) || defined(__IA64__)
#       define uasm_IA64 1
#       define uasm_ARCH_IA64 1
#       define uasm_IA64_ABI 1
#elif defined(_M_PPC) || defined(_M_PPCBE) || defined(_PPC_) || defined(__ppc__) || defined(__POWERPC__) || defined(GEKKO) || defined(EPPC) || defined(__PPCGEKKO__) || defined(__powerpc) || defined(__powerpc__)
#       define uasm_PPC 1
#       define uasm_PPC32 1
#       define uasm_PPC_ABI 1
#       define uasm_PPC32_ABI 1
#       define uasm_ARCH_PPC 1
#       define uasm_ARCH_PPC32 1
#       define uasm_PLATFORM_PPC 1
#       define uasm_PLATFORM_PPC32 1
#if defined(__VEC__) || defined(__ALTIVEC__)
#       define uasm_ALTIVEC 1
#       define uasm_VMX 1
#endif
#       define uasm_INTRINSICS 1
#undef uasm_ENDIAN_BIG
#       define uasm_ENDIAN_BIG    1
#       define uasm_PTR_SIZE 4
#       define uasm_SIZE_T_SIZE 4
#       define uasm_STACK_SIZE 8
#       define uasm_ARCH_SUPPORTS_DOUBLE 1
#       define uasm_ARCH_SUPPORTS_INT64 1
#       define uasm_NUM_SIMD_REGISTERS 8
#undef uasm_ARCH
#       define uasm_ARCH 6
#  if defined(uasm_MSVC_COMPATIBLE_COMPILER) && defined(_M_PPCBE)
#       define uasm_XBOX360 1
#       define uasm_VMX
#       define uasm_VMX128X360 1
#       define uasm_ARCH_X360 1
#       define uasm_PLATFORM_XBOX360 1
#       define uasm_PLATFORM_IS_CONSOLE 1
#       define uasm_ARCH_STR "X360"
#undef uasm_ARCH
#       define uasm_ARCH 3
#  elif defined(CAFE) || defined(uasm_GHS)
#   include <cafe.h>
#   include <ppc_ghs.h> // allow use of intrinsics throughout code
#       define uasm_WIIU 1
#       define uasm_ARCH_WIIU 1
#       define uasm_PLATFORM_WIIU 1
#       define uasm_ENABLE_PAIRED_SINGLE_OPTS 1
#       define uasm_VECTOR_PARTS_MUST_BE_VALID 1
#       define uasm_PLATFORM_IS_CONSOLE 1
#       define uasm_ARCH_STR "WIIU"
#undef uasm_ARCH
#       define uasm_ARCH  5
#  elif defined(GEKKO) || defined(__PPCGEKKO__) //Also have custom added uasm_REVOLUTION compiler switch
#       define uasm_GEKKO 1
#       define uasm_ARCH_GEKKO 1
#       define uasm_PLATFORM_GEKKO 1
#   if defined(RVL_OS)
#       define uasm_ENABLE_PAIRED_SINGLE_OPTS 1
#       define uasm_ARCH_RVL 1
#       define uasm_PLATFORM_RVL 1
#   endif
#       define uasm_PLATFORM_IS_CONSOLE 1
#  endif
#elif defined(__ppc64__) || defined(__PPC64__) || defined(_ARCH_PPC64) || defined(__powerpc64__)
#       define uasm_PPC 1
#       define uasm_PPC64 1
#       define uasm_PPC_ABI 1
#       define uasm_PPC64_ABI 1
#       define uasm_ARCH_PPC 1
#       define uasm_ARCH_PPC64 1
#       define uasm_PLATFORM_PPC 1
#       define uasm_PLATFORM_PPC64 1
#if defined(__VEC__) || defined(__ALTIVEC__)
#       define uasm_ALTIVEC 1
#       define uasm_VMX 1
#endif
#       define uasm_INTRINSICS 1
#undef uasm_ENDIAN_BIG
#       define uasm_ENDIAN_BIG    1
#       define uasm_PTR_SIZE 4
#       define uasm_SIZE_T_SIZE 4
#       define uasm_STACK_SIZE 8
#       define uasm_ARCH_SUPPORTS_DOUBLE 1
#       define uasm_ARCH_SUPPORTS_INT64 1
#       define uasm_NUM_SIMD_REGISTERS 8
#undef uasm_ARCH
#       define uasm_ARCH 7
#elif defined(__sparc__) || defined(__sparc)
#       define uasm_SPARC 1
#       define uasm_ARCH_SPARC 1
#       define uasm_SPARC_ABI 1
#elif defined(_M_MRX000) || defined(_MIPS_) || defined(_MIPS64) || defined(__mips__) || defined(__mips) || defined(__MIPS__)
#       define uasm_MIPS 1
#       define uasm_ARCH_MIPS 1
#  if defined(__mips) && (__mips == 64)
#       define uasm_MIPS64_ABI 1
#  else
#       define uasm_MIPS32_ABI 1
#  endif
#elif defined(__PPU__) && defined(__CELLOS_LV2__)
#       define uasm_PS3 1
#       define uasm_PS3_PPU 1
#       define uasm_PPU 1
#       define uasm_ARCH_PS3 1
#       define uasm_ARCH_PS3_PPU 1
#       define uasm_PLATFORM_PS3 1
#       define uasm_VMX 1
#       define uasm_VMX128PS3 1
#       define uasm_INTRINSICS 1
#undef uasm_ENDIAN_BIG
#       define uasm_ENDIAN_BIG    1
#       define uasm_PTR_SIZE 4
#       define uasm_SIZE_T_SIZE 4
#       define uasm_STACK_SIZE 8
#       define uasm_ARCH_SUPPORTS_DOUBLE 1
#       define uasm_ARCH_SUPPORTS_INT64
#       define uasm_NUM_SIMD_REGISTERS 32
#       define uasm_PLATFORM_IS_CONSOLE 1
#       define uasm_ARCH_STR "PS3"
#undef uasm_ARCH
#       define uasm_ARCH 4
#elif defined(__SPU__) && defined(__CELLOS_LV2__)
#       define uasm_PS3 1
#       define uasm_PS3_SPU 1
#       define uasm_SPU 1
#       define uasm_ARCH_PS3 1
#       define uasm_ARCH_PS3_SPU 1
#       define uasm_PLATFORM_PS3 1
#       define uasm_SPU128PS3 1
#       define uasm_INTRINSICS 1
#undef uasm_ENDIAN_BIG
#       define uasm_ENDIAN_BIG    1
#       define uasm_PTR_SIZE 4
#       define uasm_SIZE_T_SIZE 4
#       define uasm_STACK_SIZE 8
#       define uasm_ARCH_SUPPORTS_INT64 1
#       define uasm_NUM_SIMD_REGISTERS 128
#       define uasm_PLATFORM_IS_CONSOLE 1
#       define uasm_ARCH_STR "PS3"
#undef uasm_ARCH
#       define uasm_ARCH 4
#elif defined(_M_ARM) || defined(_M_ARMT) || defined(__arm__) || defined(arm) || defined(__aarch64__) ||  defined(__thumb__) || defined(__arm) || defined(_ARM)
#       define uasm_ARM 1
#       define uasm_ARM_ABI 1
#       define uasm_ARCH_ARM 1
//////////////////////////////////////////////////////////////////////////
// uasm_ARM_ARCH_PROF :
//                      1-A
//                      2-R
//                      3-M
#  if defined(__ARM_ARCH_9A__) || defined(__ARM_ARCH_9__) || defined(__ARM_ARCH_9R__) || defined (__ARM_ARCH_9M__) || defined(__ARM_ARCH_9S__) || ( defined(_M_ARM) && (_M_ARM >= 9) ) || (defined(__ARM_ARCH) && (__ARM_ARCH >= 9) )
#       define uasm_ARCH_ARM_V9 1
#       define uasm_ARCH_ARM_VSET 9
#   if defined(__ARM_ARCH_9A__) || (defined(__ARM_ARCH_PROFILE) && (__ARM_ARCH_PROFILE == A))
#       define uasm_ARM_ARCH_PROF_A 1
#       define uasm_ARM_ARCH_PROF 1
#  endif
#   if defined(__ARM_ARCH_9R__) || (defined(__ARM_ARCH_PROFILE) && (__ARM_ARCH_PROFILE == R))
#       define uasm_ARM_ARCH_PROF_R 1
#       define uasm_ARM_ARCH_PROF 2
#  endif
#   if defined(__ARM_ARCH_9M__) || (defined(__ARM_ARCH_PROFILE) && (__ARM_ARCH_PROFILE == M))
#       define uasm_ARM_ARCH_PROF_M 1
#       define uasm_ARM_ARCH_PROF 3
#  endif
#  elif defined(__ARM_ARCH_8A__) || defined(__ARM_ARCH_8__) || defined(__ARM_ARCH_8R__) || defined (__ARM_ARCH_8M__) || defined(__ARM_ARCH_8S__) || ( defined(_M_ARM) && (_M_ARM >= 8) ) || (defined(__ARM_ARCH) && (__ARM_ARCH >= 8) )
#       define uasm_ARCH_ARM_V8 1
#       define uasm_ARCH_ARM_VSET 8
#   if defined(__ARM_ARCH_8A__) || (defined(__ARM_ARCH_PROFILE) && (__ARM_ARCH_PROFILE == A))
#       define uasm_ARM_ARCH_PROF_A 1
#       define uasm_ARM_ARCH_PROF 1
#  endif
#   if defined(__ARM_ARCH_8R__) || (defined(__ARM_ARCH_PROFILE) && (__ARM_ARCH_PROFILE == R))
#       define uasm_ARM_ARCH_PROF_R 1
#       define uasm_ARM_ARCH_PROF 2
#  endif
#   if defined(__ARM_ARCH_8M__) || (defined(__ARM_ARCH_PROFILE) && (__ARM_ARCH_PROFILE == M))
#       define uasm_ARM_ARCH_PROF_M 1
#       define uasm_ARM_ARCH_PROF 3
#  endif
#  elif defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7R__) || defined (__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__) || ( defined(_M_ARM) && (_M_ARM >= 7) ) || (defined(__ARM_ARCH) && (__ARM_ARCH >= 7) )
#       define uasm_ARCH_ARM_V7 1
#       define uasm_ARCH_ARM_VSET 7
#   if defined(__ARM_ARCH_7A__) || defined(_M_ARM) || (defined(__ARM_ARCH_PROFILE) && (__ARM_ARCH_PROFILE == A))
#       define uasm_ARM_ARCH_PROF_A 1
#       define uasm_ARM_ARCH_PROF 1
#  endif
#   if defined(__ARM_ARCH_7R__) || (defined(__ARM_ARCH_PROFILE) && (__ARM_ARCH_PROFILE == R))
#       define uasm_ARM_ARCH_PROF_R 1
#       define uasm_ARM_ARCH_PROF 2
#  endif
#   if defined(__ARM_ARCH_7M__) || (defined(__ARM_ARCH_PROFILE) && (__ARM_ARCH_PROFILE == M))
#       define uasm_ARM_ARCH_PROF_M 1
#       define uasm_ARM_ARCH_PROF 3
#  endif
#  elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__) || defined(__ARM_ARCH_6T2__) || defined(NN_PROCESSOR_ARM) || defined(NN_PROCESSOR_ARM_V6) || ( defined(_M_ARM) && (_M_ARM < 7) ) || (defined(__ARM_ARCH) && (__ARM_ARCH >= 6) )
#       define uasm_ARCH_ARM_V6 1
#       define uasm_ARCH_ARM_VSET 6
#  else
#       error ERROR: Unexpected ARM arch
#  endif
#  if defined(_M_ARM_FP)
#  endif
#  if defined(__ARMEB__)
#undef uasm_ENDIAN_BIG
#      define uasm_ENDIAN_BIG 1
#  else
#undef uasm_ENDIAN_LITTLE
#      define uasm_ENDIAN_LITTLE 1
#  endif
#  if (defined(uasm_ARCH_ARM_VSET) && (uasm_ARCH_ARM_VSET >= 8)) && defined(__aarch64__) && defined(uasm_ARM_ARCH_PROF_A)
#       define uasm_ARCH_A64 1
#       define uasm_A64 1
#       define uasm_A64_CPU 1
#undef uasm_ARCH
#       define uasm_ARCH 9
#       define uasm_PLATFORM_A64 1
#       define uasm_ARM_ABI64 1
#       define uasm_PTR_SIZE 8
#       define uasm_SIZE_T_SIZE 8
#       define uasm_STACK_SIZE 16
#       define uasm_ARCH_SUPPORTS_DOUBLE 1
#       define uasm_ARCH_SUPPORTS_INT64 1
#       define uasm_NUM_SIMD_REGISTERS 16
#       define uasm_ARCH_STR "Arm64"
#undef uasm_ENDIAN_LITTLE
#      define uasm_ENDIAN_LITTLE 1
#  elif defined(__arm__) || (defined(_M_ARM) && (_M_ARM >= 7)) && defined(uasm_ARM_ARCH_PROF_A)
#       define uasm_ARCH_A32 1
#       define uasm_A32 1
#       define uasm_A32_CPU 1
#undef uasm_ARCH
#       define uasm_ARCH 8
#       define uasm_PLATFORM_A32 1
#       define uasm_ARM_ABI32 1
#       define uasm_PTR_SIZE 4
#       define uasm_SIZE_T_SIZE 4
#       define uasm_STACK_SIZE 8
#       define uasm_ARCH_SUPPORTS_INT64 1
#       define uasm_NUM_SIMD_REGISTERS 8
#       define uasm_ARCH_STR "Arm32"
#   if defined(__ARMEB__)
#undef uasm_ENDIAN_BIG
#      define uasm_ENDIAN_BIG 1
#   else
#undef uasm_ENDIAN_LITTLE
#      define uasm_ENDIAN_LITTLE 1
#   endif
#  else
#       error ERROR: Unexpected ARM platform arch or not implemented yet
#  endif

#  if defined(uasm_SNC)
#       define uasm_PSP2 1
#       define uasm_ARCH_PSP2 1
#       define uasm_PLATFORM_PSP2 1
#       define uasm_PSVITA 1
#       define uasm_ARCH_PSVITA 1
#       define uasm_PLATFORM_PSVITA 1
#       define uasm_PLATFORM_IS_CONSOLE 1
#undef uasm_ARCH_STR
#       define uasm_ARCH_STR "PSVITA"
#  endif
#       define uasm_INTRINSICS 1
#elif defined(__OPENCL_VERSION__)
#       define uasm_OPENCL_DEVICE 1
#  if defined(__CPU__)
#       define uasm_OPENCL_CPU 1
#  elif defined(__GPU__)
#       define uasm_OPENCL_GPU 1
#  endif
#else
#       error ERROR: Unknown platform
#endif

#if defined(uasm_MSVC_COMPATIBLE_COMPILER)
#   define uasm_PACK_PUSH_DEF(X)          __pragma( pack(push, X) )
#   define uasm_PACK_PUSH_1                __pragma( pack(push, 1) )
#   define uasm_PACK_PUSH_2                __pragma( pack(push, 2) )
#   define uasm_PACK_PUSH_4                __pragma( pack(push, 4) )
#   define uasm_PACK_PUSH_8                __pragma( pack(push, 8) )
#   define uasm_PACK_PUSH_16               __pragma( pack(push, 16) )
#   define uasm_PACK_DEF(X)           __pragma( pack(X) )
#   define uasm_PACK_1                 __pragma( pack(1) )
#   define uasm_PACK_2                 __pragma( pack(2) )
#   define uasm_PACK_4                 __pragma( pack(4) )
#   define uasm_PACK_8                 __pragma( pack(8) )
#   define uasm_PACK_16                __pragma( pack(16) )
# if (defined(_MSC_VER) && (_MSC_VER >= 1600)) || (defined(_MSC_VER) && (__INTEL_COMPILER >= 1300))
#   define uasm_PACK_PUSH_32               __pragma( pack(push, 32) )
#   define uasm_PACK_PUSH_64               __pragma( pack(push, 64) )
#   define uasm_PACK_PUSH_128              __pragma( pack(push, 128) )
#   define uasm_PACK_PUSH_256              __pragma( pack(push, 256) )
#   define uasm_PACK_PUSH_512              __pragma( pack(push, 512) )
#   define uasm_PACK_32                __pragma( pack(32) )
#   define uasm_PACK_64                __pragma( pack(64) )
#   define uasm_PACK_128               __pragma( pack(128) )
#   define uasm_PACK_256               __pragma( pack(256) )
#   define uasm_PACK_512               __pragma( pack(512) )
#else
#   define uasm_PACK_PUSH_32               __pragma( pack(push, 16) )
#   define uasm_PACK_PUSH_64               __pragma( pack(push, 16) )
#   define uasm_PACK_PUSH_128              __pragma( pack(push, 16) )
#   define uasm_PACK_PUSH_256              __pragma( pack(push, 16) )
#   define uasm_PACK_PUSH_512              __pragma( pack(push, 16) )
#   define uasm_PACK_32                __pragma( pack(16) )
#   define uasm_PACK_64                __pragma( pack(16) )
#   define uasm_PACK_128               __pragma( pack(16) )
#   define uasm_PACK_256               __pragma( pack(16) )
#   define uasm_PACK_512               __pragma( pack(16) )
# endif
#   define uasm_PACK_PUSH_STACK           __pragma( pack(push, uasm_STACK_SIZE) )
#   define uasm_PACK_PUSH_SIZE_T          __pragma( pack(push, uasm_SIZE_T_SIZE) )
#   define uasm_PACK_PUSH_PTR             __pragma( pack(push, uasm_PTR_SIZE) )
#   define uasm_PACK_STACK                __pragma( pack(uasm_STACK_SIZE) )
#   define uasm_PACK_SIZE_T               __pragma( pack(uasm_SIZE_T_SIZE) )
#   define uasm_PACK_PTR                  __pragma( pack(uasm_PTR_SIZE) )
#   define uasm_PACK_POP                  __pragma( pack(pop) )
#   define uasm_PRAGMA_ONCE               __pragma(once)
#   define uasm_PRAGMA(exprs)             __pragma(exprs)
#   define uasm_PRAGMA_OPTIMIZE_OFF           __pragma(optimize("", off))
#   define uasm_PRAGMA_OPTIMIZE_ON            __pragma(optimize("", on))
#elif (uasm_GCC_COMPATIBLE_COMPILER) && !defined(__SPU__)
#   define uasm_PACK_PUSH_DEF(X)          _Pragma("pack(push, X)")
#   define uasm_PACK_PUSH_1               _Pragma("pack(push, 1)")
#   define uasm_PACK_PUSH_2               _Pragma("pack(push, 2)")
#   define uasm_PACK_PUSH_4               _Pragma("pack(push, 4)")
#   define uasm_PACK_PUSH_8               _Pragma("pack(push, 8)")
#   define uasm_PACK_PUSH_16              _Pragma("pack(push, 16)")
#   define uasm_PACK_PUSH_32              _Pragma("pack(push, 32)")
#   define uasm_PACK_PUSH_64              _Pragma("pack(push, 64)")
#   define uasm_PACK_PUSH_128             _Pragma("pack(push, 128)")
#   define uasm_PACK_PUSH_256             _Pragma("pack(push, 256)")
#   define uasm_PACK_PUSH_512             _Pragma("pack(push, 512)")
#   define uasm_PACK_PUSH_STACK           _Pragma("pack(push, uasm_STACK_SIZE)")
#   define uasm_PACK_PUSH_SIZE_T          _Pragma("pack(push, uasm_SIZE_T_SIZE)")
#   define uasm_PACK_PUSH_PTR         _Pragma("pack(push, uasm_PTR_SIZE)")
#   define uasm_PACK_DEF(X)           _Pragma("pack(X)")
#   define uasm_PACK_1                _Pragma("pack(1)")
#   define uasm_PACK_2                _Pragma("pack(2)")
#   define uasm_PACK_4                _Pragma("pack(4)")
#   define uasm_PACK_8                _Pragma("pack(8)")
#   define uasm_PACK_16               _Pragma("pack(16)")
#   define uasm_PACK_32               _Pragma("pack(32)")
#   define uasm_PACK_64               _Pragma("pack(64)")
#   define uasm_PACK_128              _Pragma("pack(128)")
#   define uasm_PACK_256              _Pragma("pack(256)")
#   define uasm_PACK_512              _Pragma("pack(512)")
#   define uasm_PACK_STACK            _Pragma("pack(uasm_STACK_SIZE)")
#   define uasm_PACK_SIZE_T           _Pragma("pack(uasm_SIZE_T_SIZE)")
#   define uasm_PACK_PTR              _Pragma("pack(uasm_PTR_SIZE)")
#   define uasm_PACK_POP                  _Pragma("pack(pop)")
#   define uasm_PRAGMA_ONCE               _Pragma("once")
#   define uasm_PRAGMA(exprs)             _Pragma(uasm_Stringer(exprs))
# if defined(__clang__)
#   define uasm_PRAGMA_OPTIMIZE_OFF     _Pragma("clang optimize(off)")
#   define uasm_PRAGMA_OPTIMIZE_ON      _Pragma("clang optimize(on)")
# elif defined(__GNUC__)
#   define uasm_PRAGMA_OPTIMIZE_OFF     _Pragma("gcc optimize(off)")
#   define uasm_PRAGMA_OPTIMIZE_ON      _Pragma("gcc optimize(on)")
# endif
#elif defined(uasm_IBMC)
#   define uasm_PACK_PUSH_DEF(X)          _Pragma("pack(X)")
#   define uasm_PACK_PUSH_1                _Pragma("pack(1)")
#   define uasm_PACK_PUSH_2                _Pragma("pack(2)")
#   define uasm_PACK_PUSH_4                _Pragma("pack(4)")
#   define uasm_PACK_PUSH_8                _Pragma("pack(8)")
#   define uasm_PACK_PUSH_16               _Pragma("pack(16)")
#   define uasm_PACK_PUSH_32               _Pragma("pack(32)")
#   define uasm_PACK_PUSH_64               _Pragma("pack(64)")
#   define uasm_PACK_PUSH_128              _Pragma("pack(128)")
#   define uasm_PACK_PUSH_256              _Pragma("pack(256)")
#   define uasm_PACK_PUSH_512              _Pragma("pack(512)")
#   define uasm_PACK_PUSH_STACK            _Pragma("pack(uasm_STACK_SIZE)")
#   define uasm_PACK_PUSH_SIZE_T           _Pragma("pack(uasm_SIZE_T_SIZE)")
#   define uasm_PACK_PUSH_PTR         _Pragma("pack(uasm_PTR_SIZE)")
#   define uasm_PACK_DEF(X)           _Pragma("pack(X)")
#   define uasm_PACK_1                 _Pragma("pack(1)")
#   define uasm_PACK_2                 _Pragma("pack(2)")
#   define uasm_PACK_4                 _Pragma("pack(4)")
#   define uasm_PACK_8                 _Pragma("pack(8)")
#   define uasm_PACK_16                _Pragma("pack(16)")
#   define uasm_PACK_32                _Pragma("pack(32)")
#   define uasm_PACK_64                _Pragma("pack(64)")
#   define uasm_PACK_128               _Pragma("pack(128)")
#   define uasm_PACK_256               _Pragma("pack(256)")
#   define uasm_PACK_512               _Pragma("pack(512)")
#   define uasm_PACK_STACK            _Pragma("pack(uasm_STACK_SIZE)")
#   define uasm_PACK_SIZE_T           _Pragma("pack(uasm_SIZE_T_SIZE)")
#   define uasm_PACK_PTR              _Pragma("pack(uasm_PTR_SIZE)")
#   define uasm_PACK_POP                  _Pragma("pack(pop)")
#   define uasm_PRAGMA_ONCE               _Pragma("once")
#   define uasm_PRAGMA(exprs)             _Pragma(uasm_Stringer(exprs))
#   define uasm_PRAGMA_OPTIMIZE_OFF     _Pragma("ibmc optimize(off)")
#   define uasm_PRAGMA_OPTIMIZE_ON      _Pragma("ibmc optimize(on)")
#else
#   define uasm_PACK_PUSH_DEF(X)
#   define uasm_PACK_PUSH_1
#   define uasm_PACK_PUSH_2
#   define uasm_PACK_PUSH_4
#   define uasm_PACK_PUSH_8
#   define uasm_PACK_PUSH_16
#   define uasm_PACK_PUSH_32
#   define uasm_PACK_PUSH_64
#   define uasm_PACK_PUSH_128
#   define uasm_PACK_PUSH_256
#   define uasm_PACK_PUSH_512
#   define uasm_PACK_PUSH_STACK
#   define uasm_PACK_PUSH_SIZE_T
#   define uasm_PACK_PUSH_PTR
#   define uasm_PACK_DEF(X)
#   define uasm_PACK_1
#   define uasm_PACK_2
#   define uasm_PACK_4
#   define uasm_PACK_8
#   define uasm_PACK_16
#   define uasm_PACK_32
#   define uasm_PACK_64
#   define uasm_PACK_128
#   define uasm_PACK_256
#   define uasm_PACK_512
#   define uasm_PACK_STACK
#   define uasm_PACK_SIZE_T
#   define uasm_PACK_PTR
#   define uasm_PACK_POP
#   define uasm_PRAGMA_ONCE
#   define uasm_PRAGMAERROR(exprs)
#   define uasm_PRAGMA(exprs)
#   define uasm_PRAGMA_OPTIMIZE_OFF
#   define uasm_PRAGMA_OPTIMIZE_ON
#endif

#endif // _BASEDEFS_H_
