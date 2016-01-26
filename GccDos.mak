
# This makefile creates the HJWasm 32-bit DOS binary with DJGPP.
#  'make -f GccDos.mak'

name = hjwasm

ifndef DEBUG
DEBUG=0
endif

inc_dirs  = -IH

#cflags stuff

ifeq ($(DEBUG),1)
extra_c_flags = -DDEBUG_OUT -g
OUTD=DJGPPd
else
extra_c_flags = -DNDEBUG -O2
OUTD=DJGPPr
endif

c_flags = $(extra_c_flags)

CC=gcc.exe -c $(inc_dirs) $(c_flags)

$(OUTD)/%.o: %.c
	$(CC) -o $(OUTD)/$*.o $<

include gccmod.inc

TARGET1=$(OUTD)/$(name).exe

ALL: $(OUTD) $(TARGET1)

$(OUTD):
	mkdir $(OUTD)

$(OUTD)/$(name).exe : $(OUTD)/main.o $(proj_obj)
	gcc.exe $(OUTD)/main.o $(proj_obj) -s -o $(OUTD)/$(name).exe -Wl,-Map,$(OUTD)/$(name).map

$(OUTD)/msgtext.o: msgtext.c H/msgdef.h H/globals.h
	$(CC) -o $(OUTD)/msgtext.o msgtext.c

$(OUTD)/reswords.o: reswords.c H/instruct.h H/special.h H/directve.h
	$(CC) -o $(OUTD)/reswords.o reswords.c

######

clean:
	@erase $(OUTD)\*.exe
	@erase $(OUTD)\*.obj
	@erase $(OUTD)\*.map
