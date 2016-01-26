
# This makefile creates the HJWasm Elf binary for Linux/FreeBSD.

TARGET1=hjwasm

ifndef DEBUG
DEBUG=0
endif

inc_dirs  = -IH

#cflags stuff

ifeq ($(DEBUG),0)
extra_c_flags = -DNDEBUG -O2
OUTD=GccUnixR
else
extra_c_flags = -DDEBUG_OUT -g
OUTD=GccUnixD
endif

c_flags =-D__UNIX__ $(extra_c_flags)

CC = gcc

.SUFFIXES:
.SUFFIXES: .c .o

include gccmod.inc

#.c.o:
#	$(CC) -c $(inc_dirs) $(c_flags) -o $(OUTD)/$*.o $<
$(OUTD)/%.o: %.c
	$(CC) -c $(inc_dirs) $(c_flags) -o $(OUTD)/$*.o $<

all:  $(OUTD) $(OUTD)/$(TARGET1)

$(OUTD):
	mkdir $(OUTD)

$(OUTD)/$(TARGET1) : $(OUTD)/main.o $(proj_obj)
ifeq ($(DEBUG),0)
	$(CC) $(OUTD)/main.o $(proj_obj) -s -o $@ -Wl,-Map,$(OUTD)/$(TARGET1).map
else
	$(CC) $(OUTD)/main.o $(proj_obj) -o $@ -Wl,-Map,$(OUTD)/$(TARGET1).map
endif

$(OUTD)/msgtext.o: msgtext.c H/msgdef.h
	$(CC) -c $(inc_dirs) $(c_flags) -o $*.o msgtext.c

$(OUTD)/reswords.o: reswords.c H/instruct.h H/special.h H/directve.h H/opndcls.h H/instravx.h
	$(CC) -c $(inc_dirs) $(c_flags) -o $*.o reswords.c

######

clean:
	rm $(OUTD)/$(TARGET1)
	rm $(OUTD)/*.o
	rm $(OUTD)/*.map

