<div align="center">

<h1>The-G-Os</h1>

<p><strong>An independent terminal-based operating system kernel written in C++ and Assembly.</strong><br>
Built from scratch. No Linux kernel. No compromises.</p>

<p>
  <img src="https://img.shields.io/badge/Version-v0.3-blue?style=flat-square" />
  <img src="https://img.shields.io/badge/Architecture-x86%2032--bit-orange?style=flat-square" />
  <img src="https://img.shields.io/badge/Kernel-C%2B%2B%20%2B%20Assembly-green?style=flat-square" />
  <img src="https://img.shields.io/badge/Bootloader-GRUB%20Multiboot-red?style=flat-square" />
</p>

</div>

<table>
<tr>
<td width="70%">

## Overview

The-G-Os is a low-level kernel development project built entirely from scratch in C++ and x86 Assembly. The goal is simple: build an operating system I can truly understand, control, and shape — without depending on Linux or any existing kernel.

Windows feels bloated and restrictive. macOS is proprietary and closed. Linux is powerful, but fragmented across countless distributions each with their own trade-offs. The-G-Os is my answer — a lightweight, terminal-first OS that starts small, boots fast, and grows into a fully independent computing environment.

**Current capabilities include:** booting via GRUB, a VGA text-mode terminal, a functional shell with command history, RAM-based file system simulation, PCI hardware scanning, and a memory manager skeleton.

</td>

<td width="30%" align="right">

<img src="https://github.com/R-Mahesh-Babu-001/repo_for_images/blob/main/The-G-Os-logo.png" width="300"/>

</td>
</tr>
</table>

## Features

| Category | Details |
|---|---|
| **Kernel** | Independent C++ kernel, no Linux dependency |
| **Boot** | Assembly boot entry, GRUB Multiboot support |
| **Display** | VGA text-mode terminal, custom splash screen |
| **Input** | Full keyboard input handling |
| **Shell** | Built-in terminal shell with command history |
| **Storage** | RAM-based file system simulation |
| **Memory** | Bitmap memory manager skeleton |
| **Hardware** | PCI device scanner |
| **Network** | Network command placeholders (driver in progress) |
| **Platform** | QEMU and VirtualBox compatible |
| **Target** | Lightweight — runs on old x86 hardware |

## Shell Commands

```
help          Show available commands
about         About this OS
version       Display version info
ls            List files
cat readme    View the readme file
cat system    View system info
cat network   View network info
cat hpmini    View HP Mini info
cat dsa       View DSA notes
meminfo       Show memory information
pci           List PCI devices
netinfo       Show network info
ping 8.8.8.8  Ping a host (placeholder)
history       Show command history
clear         Clear the terminal
reboot        Reboot the system
```

## Technologies

- **C++** — Kernel logic and system internals
- **x86 Assembly** — Boot entry and low-level hardware control
- **GRUB Multiboot** — Bootloader standard
- **VGA Text Mode** — Terminal rendering
- **Low-level Hardware I/O** — Direct port access
- **Makefile** — Build system
- **QEMU / VirtualBox** — Emulation and virtualization
- **WSL Ubuntu** — Build environment on Windows

## Build Requirements

> **Recommended setup:** Windows + WSL Ubuntu + VS Code

Install all dependencies:

```bash
sudo apt update
sudo apt install -y \
  build-essential bison flex \
  libgmp3-dev libmpc-dev libmpfr-dev texinfo \
  grub-pc-bin xorriso qemu-system-x86 nasm make \
  gcc-i686-linux-gnu g++-i686-linux-gnu binutils-i686-linux-gnu
```

## Build & Run

**1. Navigate to the project directory:**

```bash
cd The-G-Os
```

**2. Build the ISO:**

```bash
make clean
make
```

This produces: `the-g-os.iso`

**3. Run in QEMU:**

```bash
make run
```

**4. Run with Intel e1000 virtual network card:**

```bash
make run-net
```

---

## Running in VirtualBox

1. Create a new virtual machine
2. Set **Type** → `Other`, **Version** → `Other/Unknown`
3. Assign at least **512 MB RAM**
4. Attach `the-g-os.iso` as the optical disk
5. Start the machine

## ISO Download

Replace the link with your actual GitHub release URL:

```bash
https://github.com/R-Mahesh-Babu-001/The-G-Os/releases/tag/v0.3
```

## Current Status

```
Version      :  v0.3
Architecture :  x86 32-bit
Bootloader   :  GRUB Multiboot
Kernel       :  C++ + Assembly
Interface    :  Terminal Shell
Linux Kernel :  None
```

## Networking Roadmap

Real networking is being developed step by step. Current version has placeholder commands only.

```
[✓] PCI Device Detection
[ ] Intel e1000 Ethernet Driver
[ ] Ethernet Frame Handling
[ ] ARP
[ ] IPv4
[ ] ICMP Ping
[ ] UDP
[ ] DNS
[ ] TCP
[ ] Wi-Fi (long-term — requires chipset drivers + WPA/WPA2)
```

## Planned Features

- Real physical memory map support
- Dynamic heap allocator
- Improved shell parser with autocomplete
- Real file system with disk read/write
- PCI hardware identification
- Intel e1000 Ethernet driver
- ICMP ping command
- Basic HTTP terminal client
- Improved boot splash screen
- Better support for old Intel Atom laptops

## Design Goals

- Build an independent OS entirely from scratch
- Avoid all dependency on the Linux kernel
- Keep the system lightweight and terminal-first
- Deeply understand low-level hardware and kernel internals
- Support old and resource-constrained x86 machines
- Develop custom memory, shell, file, and network subsystems
- Create a personal OS environment under full personal control


## License

This project is currently under personal development and experimentation.


## Author

<div style="display: flex; flex-direction: column; align-items: center; justify-content: center; text-align: center; gap: 20px; padding: 40px 20px;">

    <img src="https://github.com/R-Mahesh-Babu-001/repo_for_images/blob/main/G%20will%20be%20back.png" 
         alt="The-G-Os Update" 
         style="max-width: 100%; width: 700px; border-radius: 12px; box-shadow: 0 10px 30px rgba(0,0,0,0.3);">

    <div>
        <h1 style="font-size: 3rem; margin-bottom: 10px;">
            Mahesh Babu
        </h1>

        <p style="font-size: 1.3rem; color: #cfcfcf; margin-bottom: 15px;">
            <i>The-G-Os — Independent C++ Kernel Operating System</i>
        </p>

        <h2 style="font-size: 2rem; font-weight: bold; letter-spacing: 1px;">
            G Will Be Back Again With Another Update
        </h2>
    </div>

</div>
