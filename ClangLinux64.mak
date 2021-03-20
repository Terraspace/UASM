
# This makefile creates the UASM Elf binary for Linux/FreeBSD.

TARGET1=uasm
TARGET2=uasmd

inc_dirs  = -IH

#
# Compiler flags
#
CC = clang
ifndef CFLAGS
CFLAGS = 
endif
CFLAGS = -DMACROLIB=1 -D__UNIX__ -D__LINUX__

#
# Debug build settings
#
DBGDIR = GccUnixD
DEBUGCFLAGS = -Wno-sign-conversion -Wno-implicit-int-conversion -Wno-comment -Wno-switch -Wno-implicit-function-declaration -Wno-enum-conversion -Wformat -Werror=format-security -Wdate-time -g -O0 -std=gnu17 -march=x86-64 -target x86_64-pc-linux-gnu -D_DEBUG -DDEBUG_OUT -funsigned-char -fwritable-strings -fPIC -fPIE -fstack-protector-strong -mstack-alignment=16

#
# Release build settings
#
RELDIR = GccUnixR
RELEASECFLAGS = -Wno-sign-conversion -Wno-implicit-int-conversion -Wno-comment -Wno-switch -Wno-implicit-function-declaration -Wno-enum-conversion -Wformat -Werror=format-security -Wdate-time -O3 -std=gnu17 -march=x86-64 -target x86_64-pc-linux-gnu -DNDEBUG -funsigned-char -fwritable-strings -fPIC -fPIE -fstack-protector-strong -mstack-alignment=16

.PHONY: all clean prep debug release remake

# Default build
all: clean prep debug release

.SUFFIXES:
.SUFFIXES: .c .o

#
# Debug rules
#
debug:
OUTD = DBGDIR

include gccmod.inc

$(OUTD)/%.o: %.c
    $(CC) -D __UNIX__ -c $(inc_dirs) $(CFLAGS) $(extra_c_flags) -o $(OUTD)/$*.o $<

$(OUTD)/$(TARGET2) : $(OUTD)/main.o $(proj_obj)
    $(CC) -D __UNIX__ $(OUTD)/main.o $(proj_obj) -Wl,-Bsymbolic-functions -fPIC -fPIE -pie -Wl,-z,relro -Wl,-z,now -o $@ -Wl,-Map,$(OUTD)/$(TARGET2).map

$(OUTD)/msgtext.o: msgtext.c H/msgdef.h
    $(CC) -D __UNIX__ -c $(inc_dirs) $(CFLAGS) $(extra_c_flags) -o $*.o msgtext.c

$(OUTD)/reswords.o: reswords.c H/instruct.h H/special.h H/directve.h H/opndcls.h H/instravx.h
    $(CC) -D __UNIX__ -c $(inc_dirs) $(CFLAGS) $(extra_c_flags) -o $*.o reswords.c

#
# Release rules
#
release:
OUTD = RELDIR

include gccmod.inc

$(OUTD)/%.o: %.c
    $(CC) -D __UNIX__ -c $(inc_dirs) $(CFLAGS) $(extra_c_flags) -o $(OUTD)/$*.o $<

$(OUTD)/$(TARGET1) : $(OUTD)/main.o $(proj_obj)
    $(CC) -D __UNIX__ $(OUTD)/main.o $(proj_obj) -Wl,-Bsymbolic-functions -fPIC -fPIE -pie -Wl,-z,relro -Wl,-z,now -s -o $@ -Wl,-Map,$(OUTD)/$(TARGET1).map

$(OUTD)/msgtext.o: msgtext.c H/msgdef.h
    $(CC) -D __UNIX__ -c $(inc_dirs) $(CFLAGS) $(extra_c_flags) -o $*.o msgtext.c

$(OUTD)/reswords.o: reswords.c H/instruct.h H/special.h H/directve.h H/opndcls.h H/instravx.h
    $(CC) -D __UNIX__ -c $(inc_dirs) $(CFLAGS) $(extra_c_flags) -o $*.o reswords.c

#
# Other rules
#
prep:
    mkdir -p $(DBGDIR) $(RELDIR)

remake: clean all

clean:
    rm $(OUTD)/$(TARGET1)
    rm $(OUTD)/*.o
    rm $(OUTD)/*.map
