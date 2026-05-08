#include "ramfs.hpp"
#include "terminal.hpp"
#include "string.hpp"

static RamFile files[] = {
    {
        "readme",
        "Welcome to The-G-Os v0.3.\n"
        "This is an independent C++ terminal operating system kernel.\n"
        "It is designed for low-end machines like HP Mini Atom systems.\n"
    },
    {
        "system",
        "OS Name: The-G-Os\n"
        "Kernel: Independent C++ Kernel\n"
        "Boot Mode: Multiboot through GRUB\n"
        "Linux Kernel: Not used\n"
        "Current Version: v0.3\n"
    },
    {
        "network",
        "Network roadmap:\n"
        "1. PCI scanner\n"
        "2. Intel e1000 Ethernet driver\n"
        "3. Ethernet frame support\n"
        "4. ARP\n"
        "5. IPv4\n"
        "6. ICMP ping\n"
        "7. UDP, DNS, TCP\n"
        "Wi-Fi comes much later because it needs chipset drivers and WPA support.\n"
    },
    {
        "hpmini",
        "Target device: HP Mini Atom laptop with 2 GB DDR2 RAM.\n"
        "Goal: extremely lightweight terminal-first OS.\n"
        "Recommended first networking path: Ethernet before Wi-Fi.\n"
    },
    {
        "dsa",
        "DSA ideas in The-G-Os:\n"
        "Command table, command history buffer, bitmap memory allocator,\n"
        "RAM file table, future packet queues, future file-system trees,\n"
        "future scheduler linked lists, and future network ring buffers.\n"
    }
};

static int file_count = sizeof(files) / sizeof(files[0]);

void ramfs_list() {
    for (int i = 0; i < file_count; i++) {
        terminal_print(files[i].name);
        terminal_print("\n");
    }
}

void ramfs_cat(const char* filename) {
    for (int i = 0; i < file_count; i++) {
        if (kstrcmp(filename, files[i].name)) {
            terminal_print(files[i].content);
            return;
        }
    }

    terminal_print_color("File not found.\n", COLOR_RED);
}