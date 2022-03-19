
# This makefile creates the UASM Elf binary for Linux/FreeBSD.

TARGET1=uasm

ifndef DEBUG
DEBUG=0
endif

inc_dirs  = -IH

#cflags stuff

ifeq ($(DEBUG),0)
extra_c_flags = -DNDEBUG -O2 -funsigned-char -Wwrite-strings
OUTD=GccUnixR
else
extra_c_flags = -DDEBUG_OUT -g
OUTD=GccUnixD
endif

c_flags =-D __UNIX__ $(extra_c_flags)

#From CLANG 11+, default has changed from allowing global variables to be defined in the headers (-fcommon) to not allowing it (-fno-common)."   USE: make CC="clang -fcommon" -f gccLinux64.mak
CC = gcc

.SUFFIXES:
.SUFFIXES: .c .o

include gccmod.inc

#.c.o:
#	$(CC) -c $(inc_dirs) $(c_flags) -o $(OUTD)/$*.o $<
$(OUTD)/%.o: %.c
	$(CC) -D __UNIX__ -c $(inc_dirs) $(c_flags) $(CFLAGS) $(CPPFLAGS) -o $(OUTD)/$*.o $<

all:  $(OUTD) $(OUTD)/$(TARGET1)

$(OUTD):
	mkdir $(OUTD)

$(OUTD)/$(TARGET1) : $(OUTD)/main.o $(proj_obj)
ifeq ($(DEBUG),0)
	$(CC) -D __UNIX__ $(CFLAGS) $(OUTD)/main.o $(proj_obj) -s -o $@ -Wl,-Map,$(OUTD)/$(TARGET1).map $(LDFLAGS)
else
	$(CC) -D __UNIX__ $(CFLAGS) $(OUTD)/main.o $(proj_obj) -o $@ -Wl,-Map,$(OUTD)/$(TARGET1).map $(LDFLAGS)
endif

$(OUTD)/msgtext.o: msgtext.c H/msgdef.h
	$(CC) -D __UNIX__ -c $(inc_dirs) $(c_flags) $(CFLAGS) $(CPPFLAGS) -o $*.o msgtext.c

$(OUTD)/reswords.o: reswords.c H/instruct.h H/special.h H/directve.h H/opndcls.h H/instravx.h
	$(CC) -D __UNIX__ -c $(inc_dirs) $(c_flags) $(CFLAGS) $(CPPFLAGS) -o $*.o reswords.c

######

clean:
	rm $(OUTD)/$(TARGET1)
	rm $(OUTD)/*.o
	rm $(OUTD)/*.map
