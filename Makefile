CXX = i686-linux-gnu-g++
AS = i686-linux-gnu-as
LD = i686-linux-gnu-g++

CXXFLAGS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -Ikernel
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib

OBJECTS = \
boot/boot.o \
kernel/kernel.o \
kernel/terminal.o \
kernel/keyboard.o \
kernel/string.o \
kernel/shell.o \
kernel/ramfs.o \
kernel/memory.o \
kernel/pci.o

all: the-g-os.iso

boot/boot.o: boot/boot.s
	$(AS) boot/boot.s -o boot/boot.o

kernel/kernel.o: kernel/kernel.cpp
	$(CXX) $(CXXFLAGS) -c kernel/kernel.cpp -o kernel/kernel.o

kernel/terminal.o: kernel/terminal.cpp
	$(CXX) $(CXXFLAGS) -c kernel/terminal.cpp -o kernel/terminal.o

kernel/keyboard.o: kernel/keyboard.cpp
	$(CXX) $(CXXFLAGS) -c kernel/keyboard.cpp -o kernel/keyboard.o

kernel/string.o: kernel/string.cpp
	$(CXX) $(CXXFLAGS) -c kernel/string.cpp -o kernel/string.o

kernel/shell.o: kernel/shell.cpp
	$(CXX) $(CXXFLAGS) -c kernel/shell.cpp -o kernel/shell.o

kernel/ramfs.o: kernel/ramfs.cpp
	$(CXX) $(CXXFLAGS) -c kernel/ramfs.cpp -o kernel/ramfs.o

kernel/memory.o: kernel/memory.cpp
	$(CXX) $(CXXFLAGS) -c kernel/memory.cpp -o kernel/memory.o

kernel/pci.o: kernel/pci.cpp
	$(CXX) $(CXXFLAGS) -c kernel/pci.cpp -o kernel/pci.o

the_g_kernel.bin: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o the_g_kernel.bin -lgcc

the-g-os.iso: the_g_kernel.bin grub.cfg
	mkdir -p iso/boot/grub
	cp the_g_kernel.bin iso/boot/the_g_kernel.bin
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o the-g-os.iso iso

run: the-g-os.iso
	qemu-system-i386 -cdrom the-g-os.iso

run-net: the-g-os.iso
	qemu-system-i386 -cdrom the-g-os.iso -netdev user,id=n0 -device e1000,netdev=n0

image512: the-g-os.iso
	dd if=/dev/zero of=the-g-os-512mb.img bs=1M count=512

clean:
	rm -rf boot/*.o kernel/*.o *.bin iso *.iso *.img