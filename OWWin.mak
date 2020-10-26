
# this makefile in OW WMake style creates HJWasm.EXE (Win32) and optionally
# HJWasmD.EXE (DOS).
# tools used:
# - Open Watcom v1.9
# - jwlink ( optionally OW Wlink may be used, see below )
# - HXDev  ( needed only if a DOS version is to be created )
#
# "WMake"         - creates the Win32 version.
# "WMake debug=1" - creates the Win32 debug version.
# "WMake dos=1"   - creates both Win32 and DOS version (HJWasmD.exe)
# "WMake djgpp=1" - creates a Win32 version with DJGPP support.
# "WMake wlink=1" - create a Win32 version that is linked with OW Wlink.

name = HJWasm

WIN=1

# Open Watcom root directory
!ifndef WATCOM
WATCOM = \Watcom
!endif
# if a DOS version is to be created, HXDIR must contain the HX root directory
!ifndef HXDIR
HXDIR = \HX
!endif

!ifndef DEBUG
DEBUG=0
!endif
!ifndef DOS
DOS=0
!endif
!ifndef DJGPP
DJGPP=0
!endif

# to track memory leaks, the Open Watcom TRMEM module can be included.
# it's useful only if FASTMEM=0 is set, though, otherwise most allocs 
# won't use the C heap.
!ifndef TRMEM
TRMEM=0
!endif

!ifndef OUTD
!if $(DEBUG)
OUTD=Debug
!else
OUTD=Release
!endif
!endif

inc_dirs  = -IH -I$(WATCOM)\H
c_flags = -q -bc -bt=nt -3r -fpi87

# -zc flag makes wcc386 place constant data in code segment.
# used with wlink because it won't accept readonly attribute for segments
!ifdef WLINK
LINK = $(WATCOM)\binnt\wlink.exe
c_flags += -zc
!else
LINK = jwlink.exe
!endif

#cflags stuff
#########
extra_c_flags =
!if $(DEBUG)
extra_c_flags += -od -d2 -w3 -hc -DDEBUG_OUT
!else
#extra_c_flags += -obmilrt -s -DNDEBUG
extra_c_flags += -oxa -s -DNDEBUG
!endif

!if $(TRMEM)
extra_c_flags += -of -DTRMEM -DFASTMEM=0
!endif
!if $(DJGPP)
extra_c_flags += -DDJGPP_SUPPORT=1
!endif
#########

!if $(DEBUG)
# for OW v1.8, the debug version needs user32.lib to resolve CharUpperA()
# without it, WD(W) will crash immediately.
LOPTD = debug c op cvp, symfile lib user32.lib
!else
LOPTD =
!endif

CC=$(WATCOM)\binnt\wcc386 $(c_flags) $(inc_dirs) $(extra_c_flags) -fo$@
LIB=$(WATCOM)\binnt\wlib

.c{$(OUTD)}.obj:
	$(CC) $<

proj_obj = &
!include owmod.inc

!if $(TRMEM)
proj_obj += $(OUTD)/trmem.obj
!endif

!if $(WIN)
TARGET1=$(OUTD)/$(name).exe
!endif
!if $(DOS)
TARGET2=$(OUTD)/$(name)d.exe
!endif

ALL: $(OUTD) $(TARGET1) $(TARGET2)

$(OUTD):
	@if not exist $(OUTD) mkdir $(OUTD)

$(OUTD)/$(name).exe: $(OUTD)/main.obj $(proj_obj)
	$(LINK) @<<
$(LOPTD)
format windows pe runtime console
file { $(OUTD)/main.obj $(proj_obj) } name $@
Libpath $(WATCOM)\lib386\nt;$(WATCOM)\lib386
Library kernel32.lib
op quiet, stack=0x40000, heapsize=0x100000, map=$^*, norelocs
com stack=0x1000
disable 171
!ifndef NOGBL
sort global
!endif
op statics
!ifndef WLINK
segment CONST readonly
segment CONST2 readonly
!endif
<<
!if $(DEBUG)
	@if not exist TEST mkdir TEST
	copy $(OUTD)\$(name).exe TEST\*.* >NUL
	copy $(OUTD)\$(name).sym TEST\*.* >NUL
!endif

$(OUTD)/$(name)d.exe: $(OUTD)/main.obj $(proj_obj)
	$(LINK) @<<
$(LOPTD)
!ifndef WLINK
format windows pe hx runtime console
!else
format windows pe runtime console
!endif
file { $(OUTD)/main.obj $(proj_obj) } name $@
Libpath $(WATCOM)\lib386\nt;$(WATCOM)\lib386
Libfile cstrtwhx.obj
libpath $(HXDIR)\lib
Library imphlp.lib, dkrnl32s.lib, HXEmu387.lib
reference EMUInit
op quiet, stack=0x40000, heapsize=0x40000, map=$^*, stub=$(HXDIR)\Bin\loadpex.bin
sort global op statics
!ifndef WLINK
segment CONST readonly
segment CONST2 readonly
!endif
<<
!ifdef WLINK
#	$(HXDIR)\Bin\pestub.exe -x -z -n $@
	pestub.exe -x -z -n $@
!endif

$(OUTD)/msgtext.obj: msgtext.c H/msgdef.h H/globals.h
	$(CC) msgtext.c

$(OUTD)/reswords.obj: reswords.c H/instruct.h H/special.h H/directve.h H/opndcls.h H/instravx.h
	$(CC) reswords.c

######

clean: .SYMBOLIC
	@if exist $(OUTD)\$(name).exe erase $(OUTD)\$(name).exe
	@if exist $(OUTD)\$(name)d.exe erase $(OUTD)\$(name)d.exe
	@if exist $(OUTD)\$(name).map erase $(OUTD)\$(name).map
	@if exist $(OUTD)\$(name)d.map erase $(OUTD)\$(name)d.map
	@if exist $(OUTD)\*.obj erase $(OUTD)\*.obj
