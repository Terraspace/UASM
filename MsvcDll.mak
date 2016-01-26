
# this makefile (NMake) creates the HJWasm Win32 dll with MS Visual C++.
# it has been tested with:
# - VC++ Toolkit 2003 ( = VC++ 7.1 )

name = hjwasm

# directory paths to adjust
# VCDIR  - root directory for VC compiler, linker, include and lib files
# W32LIB - directory for Win32 import library files (kernel32.lib)
!ifndef VCDIR
VCDIR  = \msvc71
!endif
!ifndef W32LIB
W32LIB = \wininc\lib
!endif
!ifndef DEBUG
DEBUG=0
!endif

!ifndef OUTD
!if $(DEBUG)
OUTD=MsvcDllD
!else
OUTD=MsvcDllR
!endif
!endif

inc_dirs  = -IH -I"$(VCDIR)\include"

linker = $(VCDIR)\Bin\link.exe
lib = $(VCDIR)\Bin\lib.exe

!if $(DEBUG)
extra_c_flags = -Zd -Od -DDEBUG_OUT
!else
extra_c_flags = -O2 -Gs -DNDEBUG
#extra_c_flags = -Ox -DNDEBUG
!endif

c_flags =-D__NT__ -D__SW_BD $(extra_c_flags) $(c_flags64)

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

lflagsw = $(LOPTD) $(LOPT) /map:$^*.map /OPT:NOWIN98

CC=@$(VCDIR)\bin\cl.exe -c -nologo $(inc_dirs) $(c_flags)

.c{$(OUTD)}.obj:
	$(CC) -Fo$* $<

proj_obj = \
!include msmod.inc

ALL: $(OUTD) $(OUTD)\$(name).dll

$(OUTD):
	@mkdir $(OUTD)

$(OUTD)\$(name).dll : $(OUTD)/$(name)s.lib
	$(linker) @<<
$(lflagsw) $(OUTD)/$(name)s.lib
/LIBPATH:"$(VCDIR)\Lib" /DLL "$(W32LIB)/kernel32.lib" /OUT:$@
/EXPORT:AssembleModule /EXPORT:ParseCmdline /EXPORT:CmdlineFini
<<

$(OUTD)\$(name)s.lib : $(proj_obj)
	@$(lib) /out:$(OUTD)\$(name)s.lib $(proj_obj)

$(OUTD)/msgtext.obj: msgtext.c H/msgdef.h H/globals.h
	$(CC) -Fo$* msgtext.c

$(OUTD)/reswords.obj: reswords.c H/instruct.h H/special.h H/directve.h
	$(CC) -Fo$* reswords.c

######

clean:
	@erase $(OUTD)\*.dll
	@erase $(OUTD)\*.obj
	@erase $(OUTD)\*.map
