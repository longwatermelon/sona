# Defaults
CC?=i386-elf-gcc
CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=

# Required
CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_libc -Iinclude
LIBK_CFLAGS:=$(CFLAGS)
LIBK_CPPFLAGS:=$(CPPFLAGS) -D__is_libk

ARCHDIR=arch/i386
DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
INCLUDEDIR?=$(PREFIX)/include
LIBDIR?=$(PREFIX)/lib

# Include arch specific flags
include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(ARCH_CPPFLAGS)
LIBK_CFLAGS:=$(LIBK_CFLAGS) $(KERNEL_ARCH_CFLAGS)
LIBK_CPPFLAGS:=$(LIBK_CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)

# Freestanding .o files
FREEOBJS=\
$(ARCH_FREEOBJS) \
stdio/printf.o \
stdio/puts.o \
stdio/putchar.o \
stdlib/abort.o \
string/mem.o \
string/str.o

# Hosted .o files
HOSTEDOBJS=$(ARCH_HOSTEDOBJS)

# Combine both
OBJS=$(FREEOBJS) $(HOSTEDOBJS)

LIBK_OBJS=$(FREEOBJS:.o=.libk.o)

BINS=libk.a

.PHONY: all clean install install-headers install-libs
.SUFFIXES: .o .libk.o .c .s

all: $(BINS)

libc.a: $(OBJS)
	$(AR) rcs $@ $<

libk.a: $(LIBK_OBJS)
	$(AR) rcs $@ $<

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.c.s:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

.c.libk.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

.s.libk.o:
	$(CC) -MD -c $< -o $@ $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

clean:
	rm $(BINS) *.a
	rm $(OBJS) $(LIBK_OBJS) *.o */*.o */*/*.o
	rm $(OBJS:.o=.d) $(LIBK_OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-libs

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-libs: $(BINS)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(BINS) $(DESTDIR)$(LIBDIR)

-include $(OBJS:.o=.d)
-include $(LIBK_OBJS:.o=.d)

