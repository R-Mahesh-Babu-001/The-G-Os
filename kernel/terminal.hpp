#ifndef THE_G_OS_TERMINAL_HPP
#define THE_G_OS_TERMINAL_HPP

#define COLOR_WHITE   0x0F
#define COLOR_GREEN   0x0A
#define COLOR_CYAN    0x0B
#define COLOR_RED     0x0C
#define COLOR_YELLOW  0x0E

void terminal_clear();
void terminal_putchar(char c);
void terminal_print(const char* str);
void terminal_print_color(const char* str, unsigned char color);
void terminal_print_dec(unsigned int value);
void terminal_print_hex(unsigned int value);
void terminal_banner();

#endif