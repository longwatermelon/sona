# Defaults
CC=i686-elf-gcc
CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=-L../libc

# Required
CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Ikernel/include -I../libc/include
LIBK_CFLAGS:=$(CFLAGS)
LIBK_CPPFLAGS:=$(CPPFLAGS) -D__is_kernel
LDFLAGS:=$(LDFLAGS) -nostdlib -lk -lgcc

ARCHDIR=arch/i386
DESTDIR?=
PREFIX?=usr
INCLUDEDIR?=$(PREFIX)/include
BOOTDIR?=boot

# Include arch specific flags
include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
kernel/kernel.o \
kernel/tty.o

OBJS=\
$(ARCHDIR)/crti.o \
$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/crtn.o

LINK_LIST=\
$(ARCHDIR)/crti.o \
$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/crtn.o \
$(LDFLAGS)

.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .s

all: sona.kernel

sona.kernel: $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot $@

$(ARCHDIR)/crtbegin.o $(ARCHDIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) --print-file-name=$(@F)` && cp "$$OBJ" $@

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.s.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -f sona.kernel
	rm -f $(OBJS)
	rm -f $(OBJS:.o=.d)

install: install-headers install-libs

install-headers:
	mkdir -p $(DESTDIR)/$(INCLUDEDIR)
	cp -R --preserve=timestamps kernel/include/. $(DESTDIR)/$(INCLUDEDIR)/.

install-libs: sona.kernel
	mkdir -p $(DESTDIR)/$(BOOTDIR)
	cp sona.kernel $(DESTDIR)/$(BOOTDIR)

-include $(OBJS:.o=.d)

