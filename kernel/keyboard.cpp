#include "keyboard.hpp"
#include "io.hpp"

static char scancode_to_ascii(unsigned char scancode) {
    static char map[128] = {
        0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
        '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
        0, 'a','s','d','f','g','h','j','k','l',';','\'','`',
        0, '\\','z','x','c','v','b','n','m',',','.','/',
        0, '*', 0, ' '
    };

    if (scancode < 128) {
        return map[scancode];
    }

    return 0;
}

char keyboard_read_key() {
    while (true) {
        if (inb(0x64) & 1) {
            unsigned char scancode = inb(0x60);

            if (!(scancode & 0x80)) {
                char c = scancode_to_ascii(scancode);

                if (c) {
                    return c;
                }
            }
        }
    }
}