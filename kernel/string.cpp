#include "string.hpp"

int kstrlen(const char* s) {
    int len = 0;
    while (s && s[len]) {
        len++;
    }
    return len;
}

bool kstrcmp(const char* a, const char* b) {
    int i = 0;

    while (a[i] && b[i]) {
        if (a[i] != b[i]) {
            return false;
        }
        i++;
    }

    return a[i] == b[i];
}

bool kstartswith(const char* text, const char* prefix) {
    int i = 0;

    while (prefix[i]) {
        if (text[i] != prefix[i]) {
            return false;
        }
        i++;
    }

    return true;
}

void kstrcpy(char* dest, const char* src) {
    int i = 0;

    while (src[i]) {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
}

void kstrncpy(char* dest, const char* src, int max) {
    int i = 0;

    while (src[i] && i < max - 1) {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
}