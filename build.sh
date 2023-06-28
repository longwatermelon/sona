#!/bin/sh
cd libc && DESTDIR="../sysroot" make install && cd ..
cd kernel && DESTDIR="../sysroot" make install && cd ..

mkdir -p iso/boot/grub
cp sysroot/boot/eos.kernel iso/boot/eos.kernel
cat > iso/boot/grub/grub.cfg << EOF
menuentry "myos" {
	multiboot /boot/eos.kernel
}
EOF
grub-mkrescue -o eos.iso iso

