
# This makefile creates the UASM Elf binary for Linux/FreeBSD.

TARGET1=uasm

ifndef DEBUG
DEBUG=0
endif

inc_dirs  = -IH

#cflags stuff

OUT_RELEASE = Release
OUT_DEBUG = Debug

ifeq ($(DEBUG),0)
extra_c_flags = -DNDEBUG -O2 -funsigned-char -Wwrite-strings
OUTD=Release
else
extra_c_flags = -DDEBUG_OUT -g -O0 -funsigned-char
OUTD=Debug
endif

# for clang
#extra_c_flags += -Wno-parentheses -Wno-switch -Wno-pointer-sign -Wno-enum-conversion

c_flags = $(CFLAGS) $(extra_c_flags)

CC ?= gcc

.SUFFIXES:
.SUFFIXES: .c .o

include gccmod.inc

$(OUTD)/%.o: %.c
	$(CC) -D__UNIX__ -c $(inc_dirs) $(c_flags) -o $(OUTD)/$*.o $<

all:  $(OUTD) $(OUTD)/$(TARGET1)

$(OUTD):
	mkdir $(OUTD)

$(OUTD)/$(TARGET1) : $(OUTD)/main.o $(proj_obj)
ifeq ($(DEBUG),0)
	$(CC) $(OUTD)/main.o $(proj_obj) $(LDFLAGS) -s -o $@ -Wl,-Map,$(OUTD)/$(TARGET1).map
else
	$(CC) $(OUTD)/main.o $(proj_obj) $(LDFLAGS) -o $@ -Wl,-Map,$(OUTD)/$(TARGET1).map
endif

$(OUTD)/msgtext.o: msgtext.c H/msgdef.h
$(OUTD)/reswords.o: reswords.c H/instruct.h H/special.h H/directve.h H/opndcls.h H/instravx.h

######

clean:
	rm -f $(OUTD)/$(TARGET1)
	rm -f $(OUTD)/*.o
	rm -f $(OUTD)/*.map

distclean:
	rm -rf $(OUT_DEBUG)
	rm -rf $(OUT_RELEASE)
