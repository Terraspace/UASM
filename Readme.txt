JWasm Readme


    1. About JWasm

    JWasm is intended to be a free Masm-compatible assembler. It supports
    16-, 32- and 64-bit code generation and instructions up to AVX.

    Various output formats are supported:

    format     option     comment
    -----------------------------------------------------------------------
    OMF        -omf       (default) object format, 16- and 32-bit supported
    BIN        -bin       plain binary format (boot sector, BIOS, DOS COM)
    COFF       -coff      MS Win32 object format
    WIN64      -win64     MS Win64 object format
    MZ         -mz        DOS native binary format (.EXE)
    PE         -pe        Win32/Win64 PE binary format
    ELF32      -elf       Linux 32-bit object format
    ELF64      -elf64     Linux 64-bit object format
    DJGPP      -djgpp     Djgpp's 32-bit COFF variant (optional).

    JWasm is distributed in several packages. Besides the source package
    there are some which contain precompiled binaries for Windows, DOS and
    Linux. Other OSes like OS/2 and FreeBSD are also supported, but no binary
    is supplied, it must be created from the sources.

    JWasm has its roots in Open Watcom's Wasm. The source is released under
    the Sybase Open Watcom Public License (see license.txt for details).


    2. Requirements

    - JWASM.EXE, a precompiled Win32 binary, should run on any 32- or 64-bit
      Windows.

    - JWASMD.EXE, a precompiled DOS binary, runs in DOS 32bit protected-mode.
      It requires a 80386 cpu and needs a MS-DOS v5 compatible DOS to run
      (FreeDOS v1 will do). Long filenames (LFN) are supported. JWASMD.EXE
      won't run on 64-bit Windows.

    - JWASMR.EXE is a DOS real-mode program which runs on any x86 cpu.
      Similar to JWASMD.EXE it needs a MS-DOS v5 compatible DOS. This version
      has some restrictions, to limit the amount of memory the binary will need.

    Memory requirements depend on the source which is assembled. The source
    itself is not kept in memory, but the symbol table is, and this table
    can easily grow to several MBs if huge amounts of equates are defined.
    That's why JWASMR.EXE might be unable to assemble large sources.


    3. Installation

    The precompiled binaries are supplied as a compressed file. The simplest
    and best approach to "install" JWasm is to create a directory named JWasm,
    copy the compressed file ( i.e. jwasm205w.zip ) into this directory and
    "unzip" it. If you want to run JWasm without having to type the full path
    name, you'll either have to add the JWasm directory to your PATH
    environment variable or to copy the JWasm binary to a directory that's
    included in your PATH.
     If you want to deinstall JWasm, delete the JWasm directory. If you had
    added the directory to your PATH environment variable, remove it from
    there.


    4. Documentation

    JWasm's documentation consists of

    - Readme.txt (this file)
    - a Manual, which describes the differences to Masm. It may be in
      HTML (Manual.html) or Windows HTMLHelp (JWasm.ch*) format.
    - History.txt, which describes bugfixes and changes of all JWasm versions.
    - License.txt, which is a copy of the Sybase Open Watcom Public License.


    5. Samples

    The binary packages contain samples in subdirectory SAMPLES.

    For output formats other than BIN, MZ or PE, JWasm's output has to be
    linked to create an executable binary. The following set of linkers
    have been verified to cooperate with JWasm:

    Format  Linker    Comment
    -------------------------------------------------------------
    OMF     Wlink     contained in Open Watcom, free, open source
    OMF     ALink     by A. Williams, free
    OMF     ValX      by David Lindauer (Ladsoft), free
    OMF     OptLink   from Digital Mars, free
    OMF     Link16    the old OMF linker (v5.60) from Microsoft
    OMF     TLink     from Borland
    COFF    Wlink     this linker accepts OMF and COFF modules
    COFF    MS Link   will also accept OMF modules
    COFF    PoLink    supplied with PellesC, free
    WIN64   MS Link   must be version 7.10 or newer
    WIN64   Polink    must be version 5 or newer
    WIN64   JWlink    fork of OW Wlink
    ELF32   LD        the GNU linker
    ELF64   LD        the GNU linker
    ELF64   JWlink    fork of OW Wlink

    Note that the name of the MS OMF linker binary is LINK.EXE, identical
    to the MS COFF linker name.


    6. How to Create the JWasm Binaries

     JWasm is written in C. It's virtually C89, but 64-bit integers and
    structures/unions as unnamed members of structures/unions must be 
    supported by the compiler.

    The following Makefiles are supplied in the source package: 

    name         tool chain used               creates binary for
    ---------------------------------------------------------------
    Makefile     Open Watcom v1.8-v1.9         Win32 [, DOS (32-bit)]
    OWDOS16.MAK  Open Watcom v1.8-v1.9         DOS (16-bit)
    OWOS2.MAK    Open Watcom v1.8-v1.9         OS/2 (32-bit)
    OWLinux.MAK  Open Watcom v1.8-v1.9         Linux
    OWWinDll.MAK Open Watcom v1.8-v1.9         Win32 (JWasm.dll)
    Msvc.MAK     VC++ TK 2003/VC++ 2008 EE     Win32 [, DOS (32-bit)]
    Msvc64.MAK   VC++ 2010                     Win64
    MsvcDll.MAK  VC++ TK 2003                  Win32 (JWasm.dll)
    GccWin.MAK   GCC, MinGW/Cygwin             Win32
    GccWin64.MAK GCC, MinGW-w64                Win64
    GccDos.MAK   GCC, DJGPP                    DOS (32-bit)
    GccUnix.MAK  GCC, FreeBSD/Linux            FreeBSD [, Linux]
    ---------------------------------------------------------------
    BCC.MAK      Borland C++ Cmdline Tools     Win32
    OC.MAK       Orange C                      Win32
    PCC.MAK      PCC                           Win32
    PellesC.MAK  Pelles C v7                   Win32, Win64
    TCC.MAK      Tiny C                        Win32
    IntelC32.MAK Intel C++ Compiler, MSVC      Win32
    IntelC64.MAK Intel C++ Compiler, MSVC      Win64

     The makefiles that use the OW tool chain are supposed to be run
    with Open Watcom's WMake, Msvc*.MAK and IntelC*.MAK should be run with
    MS NMAKE, PellesC.MAK expects POMAKE and for Gcc*.MAK GNU make is to be
    used.

    More detailed information may be found in the makefiles themselves!

    Please note that only the binaries created with toolchains Open Watcom,
    VC++ and GCC are regularily tested to pass the JWasm regression test.


    7. Using JWasm with Visual Studio

    a) VS 2005/2008

    To integrate JWasm into VS, copy file jwasm.rules to directory
    <vc_dir>\VC\VCProjectDefaults. After this is done, JWasm can be
    selected as assembler inside the VS IDE.

    b) VS 2010/2012

    - Unzip file VS2010CustomBuildRule.zip. The result are 3 files,
      jwasm.props, jwasm.targets and jwasm.xml.
    - Copy those files to MSBUILD's build customization directory.


    8. Contributors

    These people contributed to JWasm ( additions, bugfixes, bug reports):

    agner, BlackVortex, dosfan01, drizz, Paul Edwards, filofel, Peter Flass,
    James C. Fuller, gfalen, habran, Japheth, Jimg, jj2007, John Hankinson,
    Khusraw, Alex Kozlov, Peter Kuznetsov, misca, Michal Necasek, H. Nidudsson,
    Nikitakita, Jose Pascoa, Terry Philips, qWord, RotateRight, Ito Toshimitsu,
    Vortex.

    Japheth

