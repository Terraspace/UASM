.DEFAULT_GOAL := all
ASSEMBLER ?= ../../../GccUnixR/uasm
CC ?= cc
PYTHON ?= python3
ASMFLAGS ?= -q -elf64 -Zi
LINKFLAGS = -g -Wl,-z,text,-z,relro,-z,now,-z,noexecstack
ORIGIN = -Wl,-rpath,'$$ORIGIN'
.PHONY: all console gui check check-gui debug-check debug-gui gtk-deps clean
all: console gui
console: build/console
gui: build/gtk
build:
	mkdir -p build
build/%.o: %.asm api.inc | build
	env -u UASM $(ASSEMBLER) $(ASMFLAGS) -Fo$@ $<
build/gtk.o: gtk4.inc
build/libuasm_sample.so: build/samplelib.o
	$(CC) $(LINKFLAGS) -shared -Wl,-soname,libuasm_sample.so -Wl,-z,defs -o $@ $<
build/console: build/console.o build/libuasm_sample.so
	$(CC) $(LINKFLAGS) -pie -o $@ $< -Lbuild -luasm_sample $(ORIGIN)
gtk-deps:
	@pkg-config --exists gtk4 || { echo 'Install GTK4 development files (Ubuntu: sudo apt install libgtk-4-dev)'; exit 1; }
build/gtk: build/gtk.o build/libuasm_sample.so | gtk-deps
	$(CC) $(LINKFLAGS) -pie -o $@ $< -Lbuild -luasm_sample $(ORIGIN) $$(pkg-config --libs gtk4)
check: console
	$(PYTHON) verify.py
	$(MAKE) debug-check
check-gui: gui
	GDK_BACKEND=x11 GTK_A11Y=none NO_AT_BRIDGE=1 GIO_USE_VFS=local GSK_RENDERER=cairo UASM_SAMPLE_SMOKE=1 timeout 20s dbus-run-session -- xvfb-run -a ./build/gtk
	$(MAKE) debug-gui
debug-check: console
	gdb -q -batch -ex 'source debug_check.py' --args ./build/console
debug-gui: gui
	GDK_BACKEND=x11 GTK_A11Y=none NO_AT_BRIDGE=1 GIO_USE_VFS=local GSK_RENDERER=cairo UASM_SAMPLE_SMOKE=1 UASM_DEBUG_GUI=1 timeout 40s dbus-run-session -- xvfb-run -a gdb -q -batch -ex 'source debug_check.py' --args ./build/gtk
clean:
	rm -f build/*.o build/console build/gtk build/libuasm_sample.so
