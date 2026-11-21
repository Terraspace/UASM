# Shared 64-bit Linux rules. Invoke a GCC or Clang wrapper makefile.
.DEFAULT_GOAL := all
DEBUG ?= 0
TARGET1 ?= uasm
GO ?= go
ifeq ($(DEBUG),0)
OUTD ?= $(COMPILER_TAG)UnixR
MODE_FLAGS = -O2 -DNDEBUG
else
OUTD ?= $(COMPILER_TAG)UnixD
MODE_FLAGS = -O0 -g -DDEBUG_OUT
endif

# Preserve UASM's unsigned-byte bool and historical plain-char behaviour.
UASM_CFLAGS = -std=gnu99 -m64 -funsigned-char -fno-strict-aliasing $(MODE_FLAGS)
UASM_CPPFLAGS = -D__UNIX__ -IH
include gccmod.inc
objects = $(OUTD)/main.o $(proj_obj)

.PHONY: all clean test FORCE
all: $(OUTD)/$(TARGET1)

$(OUTD):
	mkdir -p "$@"

# Rebuild objects when compiler or user flags change in the same output directory.
FORCE:
$(OUTD)/.build-flags: FORCE | $(OUTD)
	@{ printf '%s\n' '$(CC)' '$(UASM_CPPFLAGS) $(CPPFLAGS) $(UASM_CFLAGS) $(CFLAGS)' '$(LDFLAGS) $(LDLIBS)'; $(CC) --version; } > $@.tmp
	@cmp -s $@.tmp $@ || cp $@.tmp $@
	@rm -f $@.tmp

$(OUTD)/%.o: %.c $(OUTD)/.build-flags | $(OUTD)
	$(CC) $(UASM_CPPFLAGS) $(CPPFLAGS) $(UASM_CFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

$(OUTD)/$(TARGET1): $(objects) $(OUTD)/.build-flags
	$(CC) -m64 $(CFLAGS) $(LDFLAGS) -o $@ $(objects) $(LDLIBS)

-include $(objects:.o=.d)

test: all
	cd regress && $(GO) test ./...
	cd regress && $(GO) run . -asm "$(abspath $(OUTD)/$(TARGET1))"

clean:
	rm -f $(objects) $(objects:.o=.d) $(OUTD)/$(TARGET1) $(OUTD)/.build-flags $(OUTD)/.build-flags.tmp
