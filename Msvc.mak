
# this makefile (NMake) creates the HJWasm Win32 binary with MS Visual C++.
# it has been tested with:
# - VC++ 5
# - VC++ 6
# - VC++ Toolkit 2003 ( = VC++ 7.1 )
# - VC++ 2005 EE ( not recommended; creates slow binary )
# - VC++ 2008 EE ( not recommended; creates slow binary )
#
# optionally, a DOS binary can be created. Then the HXDEV package is needed.
#
# to use jwlink instead of MS link, enter: "nmake -f msvc.mak mslink=0
# to additionally create a DOS binary, enter: "nmake -f msvc.mak dos=1 mslink=0"

name = hjwasm
WIN=1

!ifndef DOS
DOS=0
!endif
!ifndef MSLINK
MSLINK=1
!endif

# directory paths to adjust
# VCDIR  - root directory for VC compiler, linker, include and lib files
# W32LIB - directory for Win32 import library files (kernel32.lib).
#          Default is WinInc ( may be changed to the MS Platform SDK ).
# HXDIR  - for DOS=1 only: root directory to search for stub LOADPEX.BIN,
#          libs DKRNL32S.LIB + IMPHLP.LIB and tool PATCHPE.EXE.

!ifndef VCDIR
VCDIR  = \msvc71
!endif
!ifndef W32LIB
W32LIB = \WinInc\Lib
!endif
!if $(DOS)
HXDIR  = \HX
!endif

!ifndef DEBUG
DEBUG=0
!endif

!ifndef OUTD
!if $(DEBUG)
OUTD=MSVCD
!else
OUTD=MSVCR
!endif
!endif

inc_dirs  = -IH -I"$(VCDIR)\include"

linker = $(VCDIR)\Bin\link.exe
lib = $(VCDIR)\Bin\lib.exe

!ifndef TRMEM
TRMEM=0
!endif

!if $(DEBUG)
#extra_c_flags = -Zi -Od -DDEBUG_OUT -FAa -Fa$* 
extra_c_flags = -Z7 -Od -DDEBUG_OUT
!else
extra_c_flags = -O2 -Gs -DNDEBUG
#extra_c_flags = -Ox -DNDEBUG
!endif

!if $(TRMEM)
extra_c_flags = $(extra_c_flags) -DTRMEM -DFASTMEM=0
!endif

c_flags =-D__NT__ $(extra_c_flags)

# if MSVC++ 2005 EE is used:
# 1. define __STDC_WANT_SECURE_LIB__=0 to avoid "deprecated" warnings
# 2. define -GS- to disable security checks
#c_flags =-D__NT__ $(extra_c_flags) -D__STDC_WANT_SECURE_LIB__=0 -GS-

#########

# linker option /OPT:NOWIN98 is not accepted by all MS linkers
#LOPT = /NOLOGO
LOPT = /NOLOGO /OPT:NOWIN98
!if $(DEBUG)
LOPTD = /debug
!endif

lflagsd = $(LOPTD) /SUBSYSTEM:CONSOLE $(LOPT) /map:$^*.map /Libpath:$(HXDIR)\lib
lflagsw = $(LOPTD) /SUBSYSTEM:CONSOLE $(LOPT) /map:$^*.map

CC=$(VCDIR)\bin\cl.exe -c -nologo $(inc_dirs) $(c_flags)

.c{$(OUTD)}.obj:
	@$(CC) -Fo$* $<

proj_obj = \
!include msmod.inc

!if $(TRMEM)
proj_obj = $(proj_obj) $(OUTD)/trmem.obj
!endif

!if $(WIN)
TARGET1=$(OUTD)\$(name).exe
!endif
!if $(DOS)
TARGET2=$(OUTD)\$(name)d.exe
!endif

ALL: $(OUTD) $(TARGET1) $(TARGET2)

$(OUTD):
	@mkdir $(OUTD)

$(OUTD)\$(name).exe : $(OUTD)/main.obj $(OUTD)/$(name).lib
!if $(MSLINK)
	@$(linker) @<<
$(lflagsw) $(OUTD)/main.obj $(OUTD)/$(name).lib
/LIBPATH:"$(VCDIR)/Lib" "$(W32LIB)/kernel32.lib" /OUT:$@
<<
!else
	@jwlink @<<
format windows pe file $(OUTD)/main.obj 
name $@ 
lib $(OUTD)/$(name).lib 
libpath "$(VCDIR)/Lib" lib "$(W32LIB)/kernel32.lib" 
op start=_mainCRTStartup, norelocs, eliminate, map=$(OUTD)/$(name).map
#sort global op statics
disable 173
<<
!endif

$(OUTD)\$(name)d.exe : $(OUTD)/main.obj $(OUTD)/$(name).lib
!if $(MSLINK)
	@$(linker) @<<
$(lflagsd) /NODEFAULTLIB initw32.obj $(OUTD)/main.obj $(OUTD)/$(name).lib /LIBPATH:$(VCDIR)\Lib
libc.lib oldnames.lib /LIBPATH:$(HXDIR)\Lib imphlp.lib dkrnl32s.lib /STUB:$(HXDIR)\Bin\LOADPEX.BIN
/OUT:$@ /FIXED:NO
<<
	@$(HXDIR)\bin\patchpe $@
!else
	@jwlink @<<
format windows pe hx file $(HXDIR)/lib/initw32.obj, $(OUTD)/main.obj name $@ lib $(OUTD)/$(name).lib
libpath $(VCDIR)/Lib
libpath $(HXDIR)/Lib lib imphlp.lib, dkrnl32s.lib, hxemu387.lib reference EMUInit 
op start=_start, eliminate, map=$(OUTD)/$(name)d.map, stub=$(HXDIR)\Bin\LOADPEX.BIN
<<
!endif

$(OUTD)\$(name).lib : $(proj_obj)
	@$(lib) /nologo /out:$(OUTD)\$(name).lib $(proj_obj)

$(OUTD)/msgtext.obj: msgtext.c H/msgdef.h H/globals.h
	@$(CC) -Fo$* msgtext.c

$(OUTD)/reswords.obj: reswords.c H/instruct.h H/special.h H/directve.h H/opndcls.h H/instravx.h
	@$(CC) -Fo$* reswords.c

######

clean:
	@erase $(OUTD)\*.exe
	@erase $(OUTD)\*.obj
	@erase $(OUTD)\*.map
