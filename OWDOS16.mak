
# this makefile creates a DOS 16-bit real-mode version of HJWasm (HJWASMR.EXE).
# tools used:
# - Open Watcom v1.8/v1.9

name = HJWasm

!ifndef WATCOM
WATCOM = \Watcom
!endif
!ifndef DEBUG
DEBUG=0
!endif

!if $(DEBUG)
OUTD=OWDOS16D
!else
OUTD=OWDOS16R
!endif

inc_dirs  = -IH -I$(WATCOM)\H

# to track memory leaks, the Open Watcom TRMEM module can be included.
# it's useful only if FASTMEM=0 is set, though, otherwise most allocs 
# won't use the C heap.
!ifndef TRMEM
TRMEM=0
!endif

LINK = $(WATCOM)\binnt\wlink.exe

#cflags stuff
#########
extra_c_flags =
!if $(DEBUG)
!if $(TRMEM)
extra_c_flags += -od -d2 -DDEBUG_OUT -DTRMEM
!else
extra_c_flags += -od -d2 -DDEBUG_OUT
!endif
!else
extra_c_flags += -obmilrs -s -DNDEBUG
!endif

#########

!if $(DEBUG)
LOPTD = debug dwarf op symfile
!endif

lflagsd = $(LOPTD) sys dos op map=$^*, stack=0x8400

CC=$(WATCOM)\binnt\wcc -q -0 -w3 -zc -ml -bc -bt=dos $(inc_dirs) $(extra_c_flags) -fo$@ -DFASTMEM=0 -DFASTPASS=0 -DCOFF_SUPPORT=0 -DELF_SUPPORT=0 -DAMD64_SUPPORT=0 -DSSSE3SUPP=0 -DSSE4SUPP=0 -DOWFC_SUPPORT=0 -DDLLIMPORT=0 -DAVXSUPP=0 -DPE_SUPPORT=0 -DVMXSUPP=0 -DSVMSUPP=0 -DCVOSUPP=0 -DCOMDATSUPP=0 -DSTACKBASESUPP=0 -zt=12000

.c{$(OUTD)}.obj:
	@$(CC) $<

proj_obj = &
!include owmod.inc

!if $(TRMEM)
proj_obj += $(OUTD)/trmem.obj
!endif

ALL: $(OUTD) $(OUTD)/$(name)r.exe

$(OUTD):
	@if not exist $(OUTD) mkdir $(OUTD)

$(OUTD)/$(name)r.exe: $(OUTD)/$(name).lib $(OUTD)/main.obj
	@set LIB=$(WATCOM)\Lib286;$(WATCOM)\Lib286\DOS
	@$(LINK) $(lflagsd) file $(OUTD)/main.obj name $@ lib $(OUTD)/$(name).lib

$(OUTD)/$(name).lib: $(proj_obj)
	@cd $(OUTD)
	@wlib -q -n $(name).lib $(proj_obj:$(OUTD)/=+)
	@cd ..

$(OUTD)/msgtext.obj: msgtext.c H/msgdef.h H/globals.h
	@$(CC) msgtext.c

$(OUTD)/reswords.obj: reswords.c H/instruct.h H/special.h H/directve.h
	@$(CC) reswords.c

######

clean: .SYMBOLIC
	@if exist $(OUTD)\*.obj        erase $(OUTD)\*.obj
	@if exist $(OUTD)\$(name)r.exe erase $(OUTD)\$(name)r.exe
	@if exist $(OUTD)\$(name)r.map erase $(OUTD)\$(name)r.map
