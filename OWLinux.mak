
# this makefile (WMake) creates the Linux binary of HJWasm.
# Open Watcom v1.8-v1.9 may be used.

name = hjwasm

!ifndef WATCOM
WATCOM=\Watcom
!endif
!ifndef DEBUG
DEBUG=0
!endif

!ifndef OUTD
!if $(DEBUG)
OUTD=OWLinuxD
!else
OUTD=OWLinuxR
!endif
!endif

# calling convention for compiler: s=Stack, r=Register
CCV=r

inc_dirs  = -IH -I$(WATCOM)\LH

# to track memory leaks, the Open Watcom TRMEM module can be included
!ifndef TRMEM
TRMEM=0
!endif

!ifdef JWLINK
LINK = jwlink.exe
c_flags = -zc
!else
LINK = $(WATCOM)\Binnt\wlink.exe
c_flags = -zc
!endif

#cflags stuff
#########
extra_c_flags =
!if $(DEBUG)
extra_c_flags += -od -d2 -DDEBUG_OUT
!else
extra_c_flags += -ot -s -DNDEBUG
!endif

!if $(TRMEM)
extra_c_flags += -DTRMEM -DFASTMEM=0
!endif

#lflags stuff
#########
!if $(DEBUG)
LOPTD = debug dwarf op symfile
!endif

CC = $(WATCOM)\Binnt\wcc386 -q -3$(CCV) $(c_flags) -bc -bt=linux $(inc_dirs) $(extra_c_flags) -fo$@

.c{$(OUTD)}.obj:
	$(CC) $<

proj_obj = &
!include owmod.inc

!if $(TRMEM)
proj_obj += $(OUTD)/trmem.obj
!endif

ALL: $(OUTD) $(OUTD)/$(name)

$(OUTD):
	@if not exist $(OUTD) mkdir $(OUTD)

$(OUTD)/$(name) : $(OUTD)/main.obj $(proj_obj)
	$(LINK) @<<
format elf runtime linux
$(LOPTD)
libpath $(WATCOM)/lib386
libpath $(WATCOM)/lib386/linux
op map=$^*, norelocs, quiet, stack=0x20000
file { $(OUTD)/main.obj $(proj_obj) }
name $@.
<<

$(OUTD)/msgtext.obj: msgtext.c H/msgdef.h H/globals.h
	$(CC) msgtext.c

$(OUTD)/reswords.obj: reswords.c H/instruct.h H/special.h H/directve.h
	$(CC) reswords.c

######

clean: .SYMBOLIC
	@if exist $(OUTD)\*.    erase $(OUTD)\*.
	@if exist $(OUTD)\*.obj erase $(OUTD)\*.obj
	@if exist $(OUTD)\*.map erase $(OUTD)\*.map
