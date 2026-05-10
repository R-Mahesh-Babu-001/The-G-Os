#include "terminal.hpp"
#include "shell.hpp"
#include "memory.hpp"
#include "vfs.hpp"

extern "C" void kernel_main();

extern "C" void kernel_main() {

    terminal_clear();
    terminal_banner();

    terminal_print("Booting The-G-Os...\n");
    terminal_print("Initializing terminal... OK\n");
    terminal_print("Initializing keyboard... OK\n");

    memory_init();
    terminal_print("Initializing bitmap memory manager... OK\n");

    vfs_init();
    terminal_print("Initializing RAM VFS... OK\n");

    terminal_print("Loading PCI scanner... OK\n");
    terminal_print("Loading shell... OK\n\n");

    shell_start();

    while (true) {
        asm volatile("hlt");
    }
}