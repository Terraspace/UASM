
# this makefile (NMake) creates the HJWasm Win64 binary with the Intel C++
# compiler. It has been tested with:
# - Intel C++ on IA-32, v11.1
# the Intel compiler needs external includes and libraries, compatible with
# MS Visual C. MS VC 2008 has been used here.
# directory paths to adjust:
# CDIR   - root directory of the Intel C compiler
# VCDIR  - root directory for Visual C includes and libraries
# W64LIB - directory for Win64 import library files (kernel32.lib).
#          Default is WinInc ( may be changed to the MS Platform SDK ).

name = hjwasm

CDIR  = \intelcpp
VCDIR = \msvc9
W64LIB = \WinInc\Lib64

# use the MS linker or jwlink (jwlink is experimental!)
!ifndef MSLINK
MSLINK=1
!endif

!ifndef DEBUG
DEBUG=0
!endif

!ifndef OUTD
!if $(DEBUG)
OUTD=IC64D
!else
OUTD=IC64R
!endif
!endif

inc_dirs  = -IH -I"$(CDIR)\include" -I"$(VCDIR)\include"

linker = $(CDIR)\bin64\xilink.exe
lib = $(CDIR)\bin64\xilib.exe

!if $(DEBUG)
extra_c_flags = -Zd -Od -DDEBUG_OUT
!else
extra_c_flags = -O2 -Gs -DNDEBUG
#extra_c_flags = -Ox -DNDEBUG
!endif

c_flags =-D_WIN64 $(extra_c_flags) $(c_flags64)

#lflags stuff
#########
LOPT = /NOLOGO
!if $(DEBUG)
#LOPTD = /debug
!endif

lflagsw = $(LOPTD) /SUBSYSTEM:CONSOLE $(LOPT) /map:$^*.map

CC=$(CDIR)\bin64\icl.exe -c -nologo $(inc_dirs) $(c_flags)

.c{$(OUTD)}.obj:
	@$(CC) -Fo$* $<

proj_obj = \
!include msmod.inc

TARGET1=$(OUTD)\$(name).exe

ALL: $(OUTD) $(TARGET1)

$(OUTD):
	@mkdir $(OUTD)

$(OUTD)\$(name).exe : $(OUTD)/main.obj $(OUTD)/$(name).lib
!if $(MSLINK)
	@$(linker) @<<
$(lflagsw) $(OUTD)/main.obj $(OUTD)/$(name).lib
/LIBPATH:"$(CDIR)\Lib\Intel64" /LIBPATH:"$(VCDIR)\Lib64" /LIBPATH:"$(W64LIB)" /OUT:$@
<<
!else
	@jwlink format windows pe file $(OUTD)/main.obj name $@ lib $(OUTD)/$(name).lib libpath "$(CDIR)\Lib\Ia32" libpath "$(VCDIR)\Lib64" libpath "$(W64LIB)" op start=_mainCRTStartup, norelocs, eliminate, map=$(OUTD)/$(name).map
!endif

$(OUTD)\$(name).lib : $(proj_obj)
	@$(lib) /nologo /out:$(OUTD)\$(name).lib $(proj_obj)

$(OUTD)/msgtext.obj: msgtext.c H/msgdef.h H/globals.h
	@$(CC) -Fo$* msgtext.c

$(OUTD)/reswords.obj: reswords.c H/instruct.h H/special.h H/directve.h
	@$(CC) -Fo$* reswords.c

######

clean:
	@erase $(OUTD)\*.exe
	@erase $(OUTD)\*.obj
	@erase $(OUTD)\*.map
