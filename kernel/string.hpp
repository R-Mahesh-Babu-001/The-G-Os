#ifndef THE_G_OS_STRING_HPP
#define THE_G_OS_STRING_HPP

int kstrlen(const char* s);
bool kstrcmp(const char* a, const char* b);
bool kstartswith(const char* text, const char* prefix);
void kstrcpy(char* dest, const char* src);
void kstrncpy(char* dest, const char* src, int max);

#endif