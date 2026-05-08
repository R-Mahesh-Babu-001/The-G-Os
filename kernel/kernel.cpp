#include "terminal.hpp"
#include "shell.hpp"
#include "memory.hpp"

extern "C" void kernel_main();

extern "C" void kernel_main() {
    terminal_clear();
    terminal_banner();

    terminal_print("Booting The-G-Os...\n");
    terminal_print("Initializing terminal... OK\n");
    terminal_print("Initializing keyboard... OK\n");

    memory_init();
    terminal_print("Initializing bitmap memory manager... OK\n");

    terminal_print("Loading RAM file table... OK\n");
    terminal_print("Loading PCI scanner... OK\n");
    terminal_print("Loading shell... OK\n\n");

    shell_start();

    while (true) {
        asm volatile("hlt");
    }
}