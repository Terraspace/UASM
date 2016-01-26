
# This makefile (NMake) creates the HJWasm Win32 binary with TCC.

name = hjwasm

!ifndef TCCDIR
TCCDIR  = \tcc
!endif
!ifndef DEBUG
DEBUG=0
!endif

!if $(DEBUG)
OUTD=TCCD
!else
OUTD=TCCR
!endif

!include gccmod.inc

inc_dirs  = -IH -I"$(TCCDIR)\include"

!if $(DEBUG)
extra_c_flags = -g -DDEBUG_OUT
!else
extra_c_flags = -DNDEBUG
!endif

CC=@$(TCCDIR)\tcc.exe -c $(inc_dirs) -D__NT__ $(extra_c_flags)

.c{$(OUTD)}.o:
	@$(CC) -o$*.o $<

ALL: $(OUTD) $(OUTD)\$(name).exe

$(OUTD):
	@mkdir $(OUTD)

$(OUTD)\$(name).exe : $(OUTD)/main.o $(proj_obj)
	$(TCCDIR)\tcc.exe -o$(OUTD)\hjwasm.exe $(OUTD)/main.o $(proj_obj)

clean:
	@erase $(OUTD)\$(name).exe
	@erase $(OUTD)\*.o
