
# This makefile creates the UASM Elf binary for Linux/FreeBSD.

TARGET1=uasm
TARGET2=uasmd

inc_dirs  = -IH

#
# Compiler flags
#
CC = clang
CFLAGS = -DMACROLIB=1 -D__UNIX__ -D__LINUX__

#
# Release build settings
#
RELDIR = GccUnixR
RELEASECFLAGS = -Wno-sign-conversion -Wno-implicit-int-conversion -Wno-comment -Wno-switch -Wno-implicit-function-declaration -Wno-enum-conversion -Wformat -Werror=format-security -Wdate-time -O3 -std=gnu17 -march=x86-64 -target x86_64-pc-linux-gnu -DNDEBUG -funsigned-char -fwritable-strings -fPIC -fPIE -fstack-protector-strong -mstack-alignment=16

#
# Debug build settings
#
DBGDIR = GccUnixD
DEBUGCFLAGS = -Wno-sign-conversion -Wno-implicit-int-conversion -Wno-comment -Wno-switch -Wno-implicit-function-declaration -Wno-enum-conversion -Wformat -Werror=format-security -Wdate-time -g -O0 -std=gnu17 -march=x86-64 -target x86_64-pc-linux-gnu -D_DEBUG -DDEBUG_OUT -funsigned-char -fwritable-strings -fPIC -fPIE -fstack-protector-strong -mstack-alignment=16

.PHONY: all clean prep release debug remake

# Default build
all: prep release debug

.SUFFIXES:
.SUFFIXES: .c .o

include debianmod.inc

#
# Release rules
#
release: $(RELDIR)/$(TARGET1)

$(RELDIR)/$(TARGET1): $(RELDIR)/main.o $(relproj_obj)
	$(CC) -D __UNIX__ $(CFLAGS) $(RELEASECFLAGS) $(RELDIR)/main.o $(relproj_obj) -Wl,-Bsymbolic-functions -fPIC -fPIE -pie -Wl,-z,relro -Wl,-z,now -s -o $@ -Wl,-Map,$(RELDIR)/$(TARGET1).map $^

$(RELDIR)/%.o: %.c
	$(CC) -D __UNIX__ -c $(inc_dirs) $(CFLAGS) $(RELEASECFLAGS) -o $(RELDIR)/$*.o $<

$(RELDIR)/msgtext.o: msgtext.c H/msgdef.h
	$(CC) -D __UNIX__ -c $(inc_dirs) $(CFLAGS) $(RELEASECFLAGS) -o $*.o msgtext.c

$(RELDIR)/reswords.o: reswords.c H/instruct.h H/special.h H/directve.h H/opndcls.h H/instravx.h
	$(CC) -D __UNIX__ -c $(inc_dirs) $(CFLAGS) $(RELEASECFLAGS) -o $*.o reswords.c

#
# Debug rules
#
debug: $(DBGDIR)/$(TARGET2)

$(DBGDIR)/$(TARGET2): $(DBGDIR)/main.o $(dbgproj_obj)
	$(CC) -D __UNIX__ $(CFLAGS) $(DEBUGCFLAGS) $(DBGDIR)/main.o $(dbgproj_obj) -Wl,-Bsymbolic-functions -fPIC -fPIE -pie -Wl,-z,relro -Wl,-z,now -o $@ -Wl,-Map,$(DBGDIR)/$(TARGET2).map $^

$(DBGDIR)/%.o: %.c
	$(CC) -D __UNIX__ -c $(inc_dirs) $(CFLAGS) $(DEBUGCFLAGS) -o $(DBGDIR)/$*.o $<

$(DBGDIR)/msgtext.o: msgtext.c H/msgdef.h
	$(CC) -D __UNIX__ -c $(inc_dirs) $(CFLAGS) $(DEBUGCFLAGS) -o $*.o msgtext.c

$(DBGDIR)/reswords.o: reswords.c H/instruct.h H/special.h H/directve.h H/opndcls.h H/instravx.h
	$(CC) -D __UNIX__ -c $(inc_dirs) $(CFLAGS) $(DEBUGCFLAGS) -o $*.o reswords.c

#
# Other rules
#
prep:
	@mkdir -p $(DBGDIR) $(RELDIR)

remake: clean all

clean:
	rm -f $(DBGDIR)/$(TARGET1)
	rm -f $(DBGDIR)/*.o
	rm -f $(DBGDIR)/*.map
	rm -f $(RELDIR)/$(TARGET1)
	rm -f $(RELDIR)/*.o
	rm -f $(RELDIR)/*.map
