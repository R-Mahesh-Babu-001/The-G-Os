````md
# The-G-Os

The-G-Os is an independent terminal-based operating system kernel written in C++ and Assembly without using the Linux kernel.

I started this project because I wanted to build an operating system that I could truly understand, control, and shape for my own use. Existing operating systems all have their own limitations: Windows often feels heavy and restrictive, macOS is proprietary and tightly controlled, and Linux has many distributions, each with its own strengths, weaknesses, and design choices. Instead of depending completely on any existing system, I wanted to experiment with building my own OS from the ground up — a lightweight, terminal-first system focused on simplicity, speed, learning, and full ownership of the computing environment.

The-G-Os is currently a low-level kernel development project designed to explore how an operating system works internally, including booting, terminal rendering, keyboard input, shell design, memory management, RAM-based file handling, PCI hardware discovery, and future networking support.

---

## Current Features

- Independent C++ kernel
- Assembly boot entry
- GRUB Multiboot boot support
- VGA text-mode terminal
- Custom boot splash screen
- Keyboard input handling
- Built-in terminal shell
- Shell command history
- RAM-based file system simulation
- Bitmap memory manager skeleton
- PCI device scanner
- Network command placeholders
- Lightweight design for old x86 hardware
- QEMU and VirtualBox support
- No Linux kernel used

---

## Current Commands

```txt
help
about
version
ls
cat readme
cat system
cat network
cat hpmini
cat dsa
meminfo
pci
netinfo
ping 8.8.8.8
history
clear
reboot
````

---

## Technologies Used

* C++
* x86 Assembly
* GRUB Multiboot
* VGA Text Mode
* Low-level Hardware I/O
* Makefile
* QEMU
* VirtualBox
* WSL Ubuntu for building on Windows

---

## Build Requirements

Recommended setup:

```txt
Windows + WSL Ubuntu + VS Code
```

Install dependencies:

```bash
sudo apt update

sudo apt install -y \
build-essential \
bison \
flex \
libgmp3-dev \
libmpc-dev \
libmpfr-dev \
texinfo \
grub-pc-bin \
xorriso \
qemu-system-x86 \
nasm \
make \
gcc-i686-linux-gnu \
g++-i686-linux-gnu \
binutils-i686-linux-gnu
```

---

## Build Instructions

Open the project folder:

```bash
cd The-G-Os
```

Build the ISO:

```bash
make clean
make
```

This generates:

```txt
the-g-os.iso
```

Run using QEMU:

```bash
make run
```

Run using QEMU with an Intel e1000 virtual network card:

```bash
make run-net
```

---

## Running in VirtualBox

1. Create a new virtual machine.
2. Select type as `Other`.
3. Select version as `Other/Unknown`.
4. Assign at least `512 MB` RAM.
5. Attach `the-g-os.iso` as the optical disk.
6. Start the virtual machine.

---

## ISO Download

Replace the link below with your actual GitHub release ISO link:

```txt
https://github.com/YOUR_USERNAME/The-G-Os/releases/download/v0.3/the-g-os.iso
```

Download using:

```bash
wget https://github.com/YOUR_USERNAME/The-G-Os/releases/download/v0.3/the-g-os.iso
```

---

## Current Status

```txt
Version: v0.3
Architecture: x86 32-bit
Boot Method: GRUB Multiboot
Kernel Language: C++ and Assembly
Interface: Terminal Shell
Linux Kernel Usage: None
```

---

## Networking Roadmap

The current version does not yet provide real internet access. Networking is being developed step by step.

Planned roadmap:

```txt
PCI Device Detection
↓
Intel e1000 Ethernet Driver
↓
Ethernet Frame Handling
↓
ARP
↓
IPv4
↓
ICMP Ping
↓
UDP
↓
DNS
↓
TCP
```

Wi-Fi support is planned for a later stage because it requires chipset-specific drivers, wireless protocol handling, and WPA/WPA2 authentication support.

---

## Design Goals

* Build an independent operating system from scratch
* Avoid dependency on the Linux kernel
* Keep the system lightweight and terminal-first
* Understand low-level hardware and kernel internals
* Support old and low-resource x86 machines
* Develop custom memory, shell, file, and network systems
* Create a personal OS environment with full control

---

## Why The-G-Os?

The-G-Os is not being built to copy Windows, macOS, or Linux. It is being built as a personal experiment in operating system design.

Windows can feel bloated and restrictive. macOS is polished but proprietary and closed. Linux is powerful, but the large number of distributions means every system comes with different trade-offs, configurations, package choices, and design decisions. The-G-Os is my attempt to learn from all of them while building a system that is simple, direct, lightweight, and fully under my own control.

The goal is to create a system that starts small, boots fast, gives a clean terminal interface, and gradually grows into a more capable independent operating system.

---

## Future Development

Planned features include:

* Real physical memory map support
* Dynamic heap allocator
* Improved shell parser
* Command autocomplete
* Real file system support
* Disk read/write support
* PCI hardware identification
* Intel e1000 Ethernet driver
* ICMP ping command
* Basic HTTP terminal command
* Better boot splash screen
* Improved support for old Intel Atom laptops

---

## License

This project is currently under personal development and experimentation.

---

## Author

Mahesh Babu

**The-G-Os — Independent C++ Kernel Operating System**

```
```
