
# This makefile creates the UASM Elf binary for Linux/FreeBSD.

TARGET1=uasm

ifndef DEBUG
DEBUG=0
endif

inc_dirs  = -IH

#cflags stuff

#-Wno-error=implicit-function-declaration
#-fwritable-strings
ifeq ($(DEBUG),0)
extra_c_flags = -DNDEBUG -O2 -funsigned-char -Wno-incompatible-pointer-types -Wno-implicit-function-declaration
OUTD=GccUnixR
else
extra_c_flags = -DDEBUG_OUT -g
OUTD=GccUnixD
endif

c_flags =-D __UNIX__ $(extra_c_flags)

CC = gcc

.SUFFIXES:
.SUFFIXES: .c .o

include gccmod.inc

#.c.o:
#	$(CC) -c $(inc_dirs) $(c_flags) -o $(OUTD)/$*.o $<
$(OUTD)/%.o: %.c | $(OUTD)
	$(CC) -D __UNIX__ -c $(inc_dirs) $(c_flags) -o $(OUTD)/$*.o $<

all:  $(OUTD) $(OUTD)/$(TARGET1)

$(OUTD):
	mkdir $(OUTD)

$(OUTD)/$(TARGET1) : $(OUTD)/main.o $(proj_obj)
ifeq ($(DEBUG),0)
	$(CC) -D __UNIX__ $(OUTD)/main.o $(proj_obj) -s -o $@ -Wl,-Map,$(OUTD)/$(TARGET1).map
else
	$(CC) -D __UNIX__ $(OUTD)/main.o $(proj_obj) -o $@ -Wl,-Map,$(OUTD)/$(TARGET1).map
endif

$(OUTD)/msgtext.o: msgtext.c H/msgdef.h
	$(CC) -D __UNIX__ -c $(inc_dirs) $(c_flags) -o $*.o msgtext.c

$(OUTD)/reswords.o: reswords.c H/instruct.h H/special.h H/directve.h H/opndcls.h H/instravx.h
	$(CC) -D __UNIX__ -c $(inc_dirs) $(c_flags) -o $*.o reswords.c

######

clean:
	rm -f $(OUTD)/$(TARGET1)
	rm -f $(OUTD)/*.o
	rm -f $(OUTD)/*.map

