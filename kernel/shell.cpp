#include "shell.hpp"
#include "terminal.hpp"
#include "keyboard.hpp"
#include "string.hpp"
#include "memory.hpp"
#include "pci.hpp"
#include "io.hpp"
#include "vfs.hpp"

struct Command {
    const char* name;
    const char* description;
    void (*handler)(const char* args);
};

#define HISTORY_SIZE 8
#define COMMAND_BUFFER_SIZE 256

static char history[HISTORY_SIZE][COMMAND_BUFFER_SIZE];
static int history_count = 0;

static void prompt() {
    terminal_print_color("root@the-g-os", COLOR_GREEN);
    terminal_print_color(":/$ ", COLOR_CYAN);
}

static void save_history(const char* cmd) {
    if (!cmd || cmd[0] == '\0') {
        return;
    }

    int pos = history_count % HISTORY_SIZE;
    kstrncpy(history[pos], cmd, COMMAND_BUFFER_SIZE);
    history_count++;
}

static void cmd_help(const char*);
static void cmd_clear(const char*);
static void cmd_about(const char*);
static void cmd_version(const char*);
static void cmd_ls(const char*);
static void cmd_cat(const char*);
static void cmd_echo(const char*);
static void cmd_meminfo(const char*);
static void cmd_pci(const char*);
static void cmd_netinfo(const char*);
static void cmd_ping(const char*);
static void cmd_history(const char*);
static void cmd_dsa(const char*);
static void cmd_reboot(const char*);
static void cmd_pwd(const char*);
static void cmd_tree(const char*);
static void cmd_touch(const char*);
static void cmd_mkdir(const char*);
static void cmd_write(const char*);
static void cmd_cd(const char*);

static Command commands[] = {
    {"help", "Show all commands", cmd_help},
    {"clear", "Clear terminal", cmd_clear},
    {"about", "About The-G-Os", cmd_about},
    {"version", "Show version", cmd_version},
    {"ls", "List files and directories", cmd_ls},
    {"cat", "Read file from VFS", cmd_cat},
    {"echo", "Print text", cmd_echo},
    {"pwd", "Show current directory", cmd_pwd},
    {"tree", "Show VFS directory tree", cmd_tree},
    {"touch", "Create file", cmd_touch},
    {"mkdir", "Create directory", cmd_mkdir},
    {"write", "Write text into file", cmd_write},
    {"cd", "Change directory", cmd_cd},
    {"meminfo", "Show memory information", cmd_meminfo},
    {"pci", "Scan PCI devices", cmd_pci},
    {"netinfo", "Show network roadmap", cmd_netinfo},
    {"ping", "Future ICMP command placeholder", cmd_ping},
    {"history", "Show command history", cmd_history},
    {"dsa", "Show DSA concepts used", cmd_dsa},
    {"reboot", "Reboot machine", cmd_reboot}
};

static int command_count = sizeof(commands) / sizeof(commands[0]);

static void cmd_help(const char*) {
    terminal_print("Available commands:\n\n");

    for (int i = 0; i < command_count; i++) {
        terminal_print("  ");
        terminal_print(commands[i].name);
        terminal_print(" - ");
        terminal_print(commands[i].description);
        terminal_print("\n");
    }

    terminal_print("\nExamples:\n");
    terminal_print("  ls\n");
    terminal_print("  pwd\n");
    terminal_print("  tree\n");
    terminal_print("  cat readme\n");
    terminal_print("  mkdir projects\n");
    terminal_print("  cd projects\n");
    terminal_print("  touch notes\n");
    terminal_print("  write notes The-G-Os has a RAM VFS\n");
    terminal_print("  cat notes\n");
    terminal_print("  meminfo\n");
    terminal_print("  pci\n");
    terminal_print("  ping 8.8.8.8\n");
}

static void cmd_clear(const char*) {
    terminal_clear();
    terminal_banner();
}

static void cmd_about(const char*) {
    terminal_print("The-G-Os is an independent C++ kernel operating system.\n");
    terminal_print("It does not use the Linux kernel.\n");
    terminal_print("This version includes terminal shell, command history,\n");
    terminal_print("bitmap memory skeleton, PCI scanner, and RAM-based VFS.\n");
}

static void cmd_version(const char*) {
    terminal_print("The-G-Os v0.4 RAM VFS Edition\n");
}

static void cmd_ls(const char*) {
    vfs_ls();
}

static void cmd_cat(const char* args) {
    if (!args || args[0] == '\0') {
        terminal_print_color("Usage: cat filename\n", COLOR_YELLOW);
        return;
    }

    vfs_cat(args);
}

static void cmd_echo(const char* args) {
    terminal_print(args);
    terminal_print("\n");
}

static void cmd_pwd(const char*) {
    vfs_pwd();
}

static void cmd_tree(const char*) {
    vfs_tree();
}

static void cmd_touch(const char* args) {
    vfs_touch(args);
}

static void cmd_mkdir(const char* args) {
    vfs_mkdir(args);
}

static void cmd_cd(const char* args) {
    vfs_cd(args);
}

static void cmd_write(const char* args) {
    if (!args || args[0] == '\0') {
        terminal_print_color("Usage: write filename text\n", COLOR_YELLOW);
        return;
    }

    char filename[64];
    char text[256];

    int i = 0;
    int j = 0;

    while (args[i] && args[i] != ' ' && i < 63) {
        filename[i] = args[i];
        i++;
    }

    filename[i] = '\0';

    while (args[i] == ' ') {
        i++;
    }

    while (args[i] && j < 255) {
        text[j] = args[i];
        j++;
        i++;
    }

    text[j] = '\0';

    if (filename[0] == '\0' || text[0] == '\0') {
        terminal_print_color("Usage: write filename text\n", COLOR_YELLOW);
        return;
    }

    vfs_write(filename, text);
}

static void cmd_meminfo(const char*) {
    memory_info();
}

static void cmd_pci(const char*) {
    pci_scan();
}

static void cmd_netinfo(const char*) {
    terminal_print("Network stack status:\n");
    terminal_print("  PCI scan: available\n");
    terminal_print("  Ethernet driver: pending\n");
    terminal_print("  ARP: pending\n");
    terminal_print("  IPv4: pending\n");
    terminal_print("  ICMP ping: pending\n");
    terminal_print("  UDP: pending\n");
    terminal_print("  DNS: pending\n");
    terminal_print("  TCP: pending\n");
    terminal_print("  Wi-Fi: future stage, much harder than Ethernet\n");
    terminal_print("\nRecommended first NIC target: Intel e1000 in QEMU.\n");
}

static void cmd_ping(const char* args) {
    terminal_print("ping command placeholder.\n");

    if (args && args[0] != '\0') {
        terminal_print("Requested target: ");
        terminal_print(args);
        terminal_print("\n");
    }

    terminal_print("Real ping needs Ethernet + ARP + IPv4 + ICMP modules.\n");
}

static void cmd_history(const char*) {
    terminal_print("Command history:\n");

    int start = history_count > HISTORY_SIZE ? history_count - HISTORY_SIZE : 0;

    for (int i = start; i < history_count; i++) {
        int pos = i % HISTORY_SIZE;
        terminal_print("  ");
        terminal_print(history[pos]);
        terminal_print("\n");
    }
}

static void cmd_dsa(const char*) {
    terminal_print("DSA concepts used in The-G-Os v0.4:\n");
    terminal_print("  Command Table       - shell command dispatch\n");
    terminal_print("  Circular History    - recent command storage\n");
    terminal_print("  VFS Tree            - directory and file hierarchy\n");
    terminal_print("  Inode-style Table   - VFS node storage\n");
    terminal_print("  Parent Pointers     - cd .. navigation\n");
    terminal_print("  Bitmap Allocator    - memory page tracking skeleton\n");
    terminal_print("  Linear PCI Scan     - hardware discovery foundation\n");
    terminal_print("\nFuture DSA upgrades:\n");
    terminal_print("  Hash Table          - faster command and file lookup\n");
    terminal_print("  Ring Buffer         - keyboard/event queue\n");
    terminal_print("  Queue               - network packet queue\n");
    terminal_print("  Linked List         - process/task scheduler\n");
}

static void cmd_reboot(const char*) {
    terminal_print("Rebooting...\n");

    unsigned char good = 0x02;

    while (good & 0x02) {
        good = inb(0x64);
    }

    outb(0x64, 0xFE);

    while (true) {
        asm volatile("hlt");
    }
}

static void parse_command(char* input, char** command, char** args) {
    *command = input;
    *args = input;

    while (**args && **args != ' ') {
        (*args)++;
    }

    if (**args == ' ') {
        **args = '\0';
        (*args)++;

        while (**args == ' ') {
            (*args)++;
        }
    } else {
        *args = (char*)"";
    }
}

static void execute_command(char* input) {
    save_history(input);

    char* command;
    char* args;

    parse_command(input, &command, &args);

    if (command[0] == '\0') {
        return;
    }

    for (int i = 0; i < command_count; i++) {
        if (kstrcmp(command, commands[i].name)) {
            commands[i].handler(args);
            return;
        }
    }

    terminal_print_color("Unknown command. Type help.\n", COLOR_RED);
}

void shell_start() {
    char command_buffer[COMMAND_BUFFER_SIZE];
    int index = 0;

    while (true) {
        prompt();
        index = 0;

        while (true) {
            char c = keyboard_read_key();

            if (c == '\n') {
                terminal_putchar('\n');
                command_buffer[index] = '\0';
                execute_command(command_buffer);
                break;
            }

            else if (c == '\b') {
                if (index > 0) {
                    index--;
                    terminal_putchar('\b');
                }
            }

            else {
                if (index < COMMAND_BUFFER_SIZE - 1) {
                    command_buffer[index] = c;
                    index++;
                    terminal_putchar(c);
                }
            }
        }
    }
}