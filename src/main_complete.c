#include "completer.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <prefix>\n", argv[0]);
        return 1;
    }
    int count = 0;
    char **results = get_completions(argv[1], &count);
    for (int i = 0; i < count; ++i) {
        puts(results[i]);
        free(results[i]);
    }
    free(results);
    return 0;
}
