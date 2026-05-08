#include "terminal.hpp"
#include "io.hpp"

#define VGA_MEMORY ((volatile char*)0xB8000)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static int cursor_x = 0;
static int cursor_y = 0;

static void move_cursor() {
    unsigned short pos = cursor_y * VGA_WIDTH + cursor_x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(pos & 0xFF));

    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((pos >> 8) & 0xFF));
}

static void scroll() {
    if (cursor_y < VGA_HEIGHT) {
        return;
    }

    for (int y = 1; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            int from = (y * VGA_WIDTH + x) * 2;
            int to = ((y - 1) * VGA_WIDTH + x) * 2;

            VGA_MEMORY[to] = VGA_MEMORY[from];
            VGA_MEMORY[to + 1] = VGA_MEMORY[from + 1];
        }
    }

    for (int x = 0; x < VGA_WIDTH; x++) {
        int index = ((VGA_HEIGHT - 1) * VGA_WIDTH + x) * 2;
        VGA_MEMORY[index] = ' ';
        VGA_MEMORY[index + 1] = COLOR_WHITE;
    }

    cursor_y = VGA_HEIGHT - 1;
}

static void putchar_color(char c, unsigned char color) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
        scroll();
        move_cursor();
        return;
    }

    if (c == '\b') {
        if (cursor_x > 0) {
            cursor_x--;
            int index = (cursor_y * VGA_WIDTH + cursor_x) * 2;
            VGA_MEMORY[index] = ' ';
            VGA_MEMORY[index + 1] = color;
        }

        move_cursor();
        return;
    }

    int index = (cursor_y * VGA_WIDTH + cursor_x) * 2;

    VGA_MEMORY[index] = c;
    VGA_MEMORY[index + 1] = color;

    cursor_x++;

    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }

    scroll();
    move_cursor();
}

void terminal_clear() {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            int index = (y * VGA_WIDTH + x) * 2;
            VGA_MEMORY[index] = ' ';
            VGA_MEMORY[index + 1] = COLOR_WHITE;
        }
    }

    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}

void terminal_putchar(char c) {
    putchar_color(c, COLOR_WHITE);
}

void terminal_print(const char* str) {
    terminal_print_color(str, COLOR_WHITE);
}

void terminal_print_color(const char* str, unsigned char color) {
    for (int i = 0; str[i]; i++) {
        putchar_color(str[i], color);
    }
}

void terminal_print_dec(unsigned int value) {
    if (value == 0) {
        terminal_putchar('0');
        return;
    }

    char buffer[16];
    int i = 0;

    while (value > 0) {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    }

    while (i > 0) {
        terminal_putchar(buffer[--i]);
    }
}

void terminal_print_hex(unsigned int value) {
    terminal_print("0x");

    char hex[] = "0123456789ABCDEF";

    for (int i = 28; i >= 0; i -= 4) {
        terminal_putchar(hex[(value >> i) & 0xF]);
    }
}

void terminal_banner() {
    terminal_print_color("============================================================\n", COLOR_CYAN);
    terminal_print_color("                     The-G-Os v0.7 Kernel                   \n", COLOR_GREEN);
    terminal_print_color("   Made By : R Mahesh Babu C++ Terminal Operating System    \n", COLOR_CYAN);
    terminal_print_color("============================================================\n\n", COLOR_CYAN);
}