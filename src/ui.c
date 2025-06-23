#include "ui.h"
#include "common.h"
#include "completer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define MAX_INPUT 1024

// Отримання спільного префікса для автодоповнення через completer
static char *get_suggestion(const char *partial) {
    static char buffer[MAX_INPUT];
    int count = 0;
    char **variants = get_completions(partial, &count);

    if (count == 0) {
        buffer[0] = '\0';
        return buffer;
    }

    char *prefix = longest_common_prefix(variants, count);
    strncpy(buffer, prefix, MAX_INPUT - 1);
    buffer[MAX_INPUT - 1] = '\0';

    for (int i = 0; i < count; ++i)
        free(variants[i]);
    free(variants);
    return buffer;
}

void interactive_loop(const char *completion_command) {

    struct termios orig, raw;
    tcgetattr(STDIN_FILENO, &orig);
    raw = orig;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    char input[MAX_INPUT] = "";
    int pos = 0;
    int len = 0;
    int tab_pressed = 0;

    (void)completion_command;  // позначаємо параметр як неактивний для уникнення попереджень

    while (1) {
        printf("\r> %s\033[K", input);
        fflush(stdout);

        char *suggestion = get_suggestion(input);
        if (suggestion && strlen(suggestion) > (size_t)len) {
            printf("\033[90m%s\033[0m", &suggestion[len]); // сіра підказка
            fflush(stdout);
        }

        char c = getchar();
        if (c == '\n') {
            printf("\nFinal input: %s\n", input);
            break;
        } else if (c == '\t') {
            if (suggestion && strlen(suggestion) > (size_t)len) {
                int delta = strlen(suggestion) - len;
                memmove(&input[pos + delta], &input[pos], len - pos);
                memcpy(&input[pos], &suggestion[pos], delta);
                len += delta;
                pos += delta;
                input[len] = '\0';
                tab_pressed = 1;
            } else if (tab_pressed) {
                int count = 0;
                char **variants = get_completions(input, &count);
                printf("\n");
                for (int i = 0; i < count; ++i) {
                    printf("%s\n", variants[i]);
                    free(variants[i]);
                }
                free(variants);
                tab_pressed = 0;
            }
        } else if (c == 127 || c == 8) { // Backspace
            if (pos > 0) {
                memmove(&input[pos - 1], &input[pos], len - pos);
                pos--;
                len--;
                input[len] = '\0';
            }
        } else if (c == 3 || c == 27) { // Ctrl+C або ESC
            printf("\n[Вихід]\n");
            break;
        } else if (c >= 32 && c < 127) {
            if (len < MAX_INPUT - 1) {
                memmove(&input[pos + 1], &input[pos], len - pos);
                input[pos] = c;
                pos++;
                len++;
                input[len] = '\0';
            }
        }
    }

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig);
}
