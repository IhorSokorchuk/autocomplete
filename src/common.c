#include "common.h"
#include <string.h>

// Перевірка, чи є рядок валідним UTF-8 (спрощена перевірка)
int is_valid_utf8(const char *str) {
    const unsigned char *s = (const unsigned char *)str;
    while (*s) {
        if (*s < 0x80) s++;
        else if ((s[0] & 0xE0) == 0xC0 && (s[1] & 0xC0) == 0x80) s += 2;
        else if ((s[0] & 0xF0) == 0xE0 && (s[1] & 0xC0) == 0x80 && (s[2] & 0xC0) == 0x80) s += 3;
        else if ((s[0] & 0xF8) == 0xF0 && (s[1] & 0xC0) == 0x80 && (s[2] & 0xC0) == 0x80 && (s[3] & 0xC0) == 0x80) s += 4;
        else return 0;
    }
    return 1;
}

// Кількість UTF-8 символів у рядку
size_t utf8_strlen(const char *str) {
    size_t len = 0;
    const unsigned char *s = (const unsigned char *)str;
    while (*s) {
        if (*s < 0x80 || (*s & 0xC0) != 0x80)
            len++;
        s++;
    }
    return len;
}
