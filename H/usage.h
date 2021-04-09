#if AMD64_SUPPORT
"-<0|1|..|10>[p]\0" "Set CPU: 0=8086 (default), 1=80186, 2=80286, 3=80386,\0"
"\0"                "4=80486, 5=Pentium, 6=PPro, 7=P2, 8=P3, 9=P4, 10=x86-64;\0"
"\0"                "<p> allows privileged instructions\0"
#else
"-<0|1|..|6>[p]\0"  "Set CPU: 0=8086 (default), 1=80186, 2=80286, 3=80386,\0"
"\0"                "4=80486, 5=Pentium, 6=Pentium Pro;\0"
"\0"                "<p> allows privileged instructions\0"
#endif
"-c\0"              "Assemble without linking (always set)\0"
"-C<p|u|x>\0"       "Set OPTION CASEMAP: p=NONE, u=ALL, x=NOTPUBLIC (default)\0"
"-archSSE\0"		"Set OPTION ARCH: SSE = Use SSE in generated code (default)\0"
"-archAVX\0"		"Set OPTION ARCH: AVX = Use AVX in generated code\0"
"-nomlib\0"         "Disable internal Macro Library\0"
"-D<name>[=text]\0" "Define text macro\0"
"-e<number>\0"      "Set error limit number (default=50)\0"
"-EP\0"             "Output preprocessed listing to stdout\0"
"-eq\0"             "don't display error messages\0"
#if DLLIMPORT
"-Fd[=<file_name>]\0"  "Write import definition file\0"
#endif
"-Fi<file_name>\0"  "Force <file_name> to be included\0"
"-Fs[=<file_name>]\0" "Write symbolic debug info\0"
"-Fl[=<file_name>]\0" "Write listing file\0"
"-Fo<file_name>\0"  "Set object file name\0"
"-Fw<file_name>\0"  "Set errors file name\0"
"-FPi\0"            "80x87 instructions with emulation fixups\0"
"-FPi87\0"          "80x87 instructions (default)\0"
"-fpc\0"            "Disallow floating-point instructions (.NO87)\0"
"-fp<n>\0"          "Set FPU, <n> is: 0=8087 (default), 2=80287, 3=80387\0"
"-G<c|d|r|z>\0"     "Use Pascal, C, Fastcall or Stdcall calling convention\0"
"-I<directory>\0"   "Add directory to list of include directories\0"
"-m<t|s|c|m|l|h|f>\0" "Set memory model:\0"
"\0"                "(Tiny, Small, Compact, Medium, Large, Huge, Flat)\0"
"-nc=<name>\0"       "Set class name of code segment\0"
"-n<d|m|t>=<name>\0" "Set name of d)ata segment, m)odule or t)ext segment\0"
#if COCTALS
"-o\0"              "Allow C form of octal constants\0"
#endif
"-q, -nologo\0"     "Don't display version and copyright information\0"
"-less\0"           "Reduce console output information (be less verbose)\0"
"-Sa\0"             "Maximize source listing\0"
#if COFF_SUPPORT
"-safeseh\0"        "Assert all exception handlers are declared\0"
#endif
"-Sf\0"             "Generate first pass listing\0"
"-Sg\0"             "Display generated code in listing\0"
"-Sn\0"             "Suppress symbol-table listing\0"
"-Sp[n]\0"          "Set segment alignment, n=<1|2|4|8|16|32 ...>\0"
"-Sx\0"             "List false conditionals\0"
"-w\0"              "Same as /W0 /WX\0"
"-W<number>\0"      "Set warning level number (default=2, max=4)\0"
"-WX\0"             "Treat all warnings as errors\0"
"-X\0"              "Ignore INCLUDE environment path\0"
"-zcm\0"            "C names are decorated with '_' prefix (default)\0"
"-zcw\0"            "No name decoration for C symbols\0"
"-Zd\0"             "Add line number debug info (OMF & COFF only)\0"
"-Zf\0"             "Make all symbols public\0"
#if OWFC_SUPPORT
"-zf<0|1|2>\0"      "Set FASTCALL type: 0=MS VC style (default),\0"
"\0"                "1=OW register calling convention,\0"
"\0"				"2=Borland register convention\0"
#endif
"-Zg\0"             "Generated code is to exactly match Masm's one\0"
"-Zi[0|1|2|3|5|8]\0"    "Add symbolic debug info (OMF & COFF): 0=globals\0"
"\0"                "1= +locals, 2= +types (default), 3= +constants, 5=CodeView5, 8=CodeView8\0"
"-zlc\0"            "No OMF records about data in code\0"
"-zld\0"            "No OMF records about far call optimization\0"
#if COFF_SUPPORT
"-zl<f|p|s>\0"      "Suppress items in COFF symbol table: f=no .file entry,\0"
"\0"                "p=no static procs, s=no auxiliary entries for sections\0"
#endif
"-Zm\0"             "Masm v5.1 compatibility\0"
"-Zne\0"            "Disable syntax extensions not supported by Masm\0"
"-Zp[n]\0"          "Set structure alignment, n=<1|2|4|8|16|32>\0"
"-Zs\0"             "Perform syntax check only\0"
"-zt<0|1|2>\0"      "Set STDCALL symbol decoration: 0=No name decoration,\0"
"\0"                "1=No '@size' suffix for functions, 2=Full (default)\0"
"-zv<0|1|2>\0"      "Set VECTORCALL symbol decoration: 0=No name decoration,\0"
"\0"                "1=No '@size' suffix for functions, 2=Full (default)\0"
"-Zv8\0"            "Enable Masm v8+ PROC visibility\0"
"-zze\0"            "No name decoration for exported symbols\0"
#if COFF_SUPPORT
"-zzs\0"            "Store decorated name of start address (COFF only)\0"
#endif
"@env_var\0"        "Environment variable or file containing further commands\0"
"output formats:\0\0"
#if BIN_SUPPORT
"-bin\0"            "plain binary file\0"
#endif
#if COFF_SUPPORT
"-coff\0"           "COFF object file\0"
#endif
#if COFF_SUPPORT && DJGPP_SUPPORT
"-djgpp\0"          "Djgpp's variant of 32-bit COFF object file\0"
#endif
#if ELF_SUPPORT
"-elf\0"            "32-bit ELF object file\0"
#if AMD64_SUPPORT
"-elf64\0"          "64-bit ELF object file\0"
#endif
#endif
#if BIN_SUPPORT && MZ_SUPPORT
"-mz\0"             "DOS MZ binary file\0"
#endif
"-omf\0"            "OMF object file (default)\0"
#if PE_SUPPORT
"-pe\0"             "PE binary file, 32/64-bit\0"
#endif
#if AMD64_SUPPORT
"-win64\0"          "64-bit COFF object file\0"
#endif
#if MACHO_SUPPORT
"-macho64\0"        "64-bit Mach-O object file\0"
#endif
"-pie\0"            "Generate Position Independant Executable (ELF64/MACHO64)\0"
#ifdef DEBUG_OUT
"Debug options:\0\0"
"-af\0"             "Display all files used in assembly process\0"
"-ce\0"             "Cause an exception\0"
"-dm\0"             "Display all messages\0"
"-dr\0"             "Display reserved words\0"
"-drh\0"            "Display reserved words hash table\0"
"-ds\0"             "Display global symbols\0"
"-dsh\0"            "Display global symbols hash table\0"
"-dt\0"             "Display debug trace\0"
#if FASTPASS
"-ls\0"             "Display preprocessed line storage\0"
#endif
"-nbp\0"            "Disable backpatching\0"
#if FASTPASS
"-nfp\0"            "Do full subsequent passes (disables \"fastpass\")\0"
#endif
"-pm=<n>\0"         "Stop assembly after <n> passes\0"
"-sp\0"             "Skip preprocessor step\0"
#endif
"\n"
