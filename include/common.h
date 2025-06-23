#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>

// Загальні утиліти
int is_valid_utf8(const char *str);
size_t utf8_strlen(const char *str);

#endif
