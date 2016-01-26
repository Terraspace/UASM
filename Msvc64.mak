
# this makefile (NMake) creates the HJWasm Win64 binary with MS Visual Studio 2010.

name = hjwasm

# directory paths to adjust
# VCDIR  - root directory for VC include and lib files.
# W64LIB - directory for Win64 import library files (kernel32.lib, ...).
#          Default is WinInc ( may be changed to the MS Platform SDK ).

# PLEASE NOTE: I didn't install the whole MS Visual Studio stuff,
# just copied the VC branch to D:\MSVC10. However, some binaries
# related to MS symbol files ( mspdbsrv.exe, mspdb100.dll, mspdbcore.dll ),
# which are to be found in \<MSVS root>\Common7\IDE, must then be copied
# manually to a directory in the path ( here: d:\msvc10\bin ).

!ifndef VCDIR
VCDIR  = d:\msvc10
!endif
!ifndef W64LIB
W64LIB = \WinInc\Lib64
!endif

VCBIN  = $(VCDIR)\bin\x86_amd64
PATH   = $(VCDIR)\bin;$(PATH)

# use the MS linker or jwlink
!ifndef MSLINK
MSLINK=1
!endif

!ifndef DEBUG
DEBUG=0
!endif

!ifndef OUTD
!if $(DEBUG)
OUTD=MSVC64D
!else
OUTD=MSVC64R
!endif
!endif

inc_dirs  = -IH -I"$(VCDIR)\include"

linker = $(VCBIN)\link.exe
lib = $(VCBIN)\lib.exe

!if $(DEBUG)
extra_c_flags = -Zd -Od -DDEBUG_OUT -FAa -Fa$* 
!else
extra_c_flags = -O2 -Ox -GS- -DNDEBUG
#extra_c_flags = -Ox -DNDEBUG
!endif

c_flags =-D__NT__ $(extra_c_flags)

# if MSVC++ 2005 EE is used:
# 1. define __STDC_WANT_SECURE_LIB__=0 to avoid "deprecated" warnings
# 2. define -GS- to disable security checks
#c_flags =-D__NT__ $(extra_c_flags) -D__STDC_WANT_SECURE_LIB__=0 -GS-

#lflags stuff
#########
LOPT = /NOLOGO
!if $(DEBUG)
LOPTD = /debug
!endif

lflagsw = $(LOPTD) /SUBSYSTEM:CONSOLE $(LOPT) /map:$^*.map

CC=$(VCBIN)\cl.exe -c -nologo $(inc_dirs) $(c_flags)

.c{$(OUTD)}.obj:
	@$(CC) -Fo$* $<

proj_obj = \
!include msmod.inc

ALL: $(OUTD) $(OUTD)\$(name).exe

$(OUTD):
	@mkdir $(OUTD)

$(OUTD)\$(name).exe : $(OUTD)/main.obj $(OUTD)/$(name).lib
!if $(MSLINK)
	@$(linker) @<<
$(lflagsw) $(OUTD)/main.obj $(OUTD)/$(name).lib
/LIBPATH:"$(VCDIR)/Lib/amd64" "$(W64LIB)/kernel32.lib" /OUT:$@
<<
!else
	@jwlink.exe format windows pe file $(OUTD)/main.obj name $@ lib $(OUTD)/$(name).lib libpath "$(VCDIR)/Lib/amd64" lib "$(W64LIB)/kernel32.lib" op start=mainCRTStartup, norelocs, eliminate, map=$(OUTD)/$(name).map
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
