
# This makefile (NMake) creates the HJWasm Win32 binary with PCC.

name = hjwasm

!ifndef PCCROOT
PCCROOT  = \pcc
!endif
!ifndef DEBUG
DEBUG=0
!endif

!if $(DEBUG)
OUTD=PCCD
!else
OUTD=PCCR
!endif

inc_dirs  = -IH -I"$(PCCROOT)\include"

!if $(DEBUG)
extra_c_flags = -g -DDEBUG_OUT
!else
extra_c_flags = -DNDEBUG
!endif

CC=$(PCCROOT)\bin\pcc.exe $(inc_dirs) -D__NT__ $(extra_c_flags)

ALL: $(OUTD) $(OUTD)\$(name).exe

$(OUTD):
	@mkdir $(OUTD)

$(OUTD)\$(name).exe: *.c
	set PCCDIR=$(PCCROOT)
	$(CC) -o $(OUTD)\$(name).exe *.c

clean:
	@erase $(OUTD)\$(name).exe
