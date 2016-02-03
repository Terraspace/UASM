
# This makefile creates a Win64 binary of JWasm with MinGW-w64.
#  'make -f GccWin64.mak'

name = hjwasm

ifndef DEBUG
DEBUG=0
endif

inc_dirs  = -IH

#cflags stuff

ifeq ($(DEBUG),1)
extra_c_flags = -DDEBUG_OUT -g
OUTD=MinGW-w64D
else
extra_c_flags = -DNDEBUG -O2
OUTD=MinGW-w64R
endif

c_flags = -D__NT__ $(extra_c_flags)

CC=x86_64-w64-mingw32-gcc.exe -c $(inc_dirs) $(c_flags)

$(OUTD)/%.o: %.c
	$(CC) -o $(OUTD)/$*.o $<

include gccmod.inc

TARGET1=$(OUTD)/$(name).exe

ALL: $(OUTD) $(TARGET1)

$(OUTD):
	mkdir $(OUTD)

$(OUTD)/$(name).exe : $(OUTD)/main.o $(proj_obj)
	x86_64-w64-mingw32-gcc.exe $(OUTD)/main.o $(proj_obj) -s -o $(OUTD)/$(name).exe -Wl,-Map,$(OUTD)/$(name).map

$(OUTD)/msgtext.o: msgtext.c H/msgdef.h
	$(CC) -o $(OUTD)/msgtext.o msgtext.c

$(OUTD)/reswords.o: reswords.c H/instruct.h H/special.h H/directve.h
	$(CC) -o $(OUTD)/reswords.o reswords.c

######

clean:
	@rm $(OUTD)/*.exe
	@rm $(OUTD)/*.obj
	@rm $(OUTD)/*.map
